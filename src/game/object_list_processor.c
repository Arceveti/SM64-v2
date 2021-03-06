#include <PR/ultratypes.h>

#include "sm64.h"
#include "area.h"
#include "behavior_data.h"
#include "camera.h"
#include "debug.h"
#include "engine/behavior_script.h"
#include "engine/graph_node.h"
#include "engine/surface_collision.h"
#include "engine/surface_load.h"
#include "engine/math_util.h"
#include "interaction.h"
#include "level_update.h"
#include "mario.h"
#include "boot/memory.h"
#include "object_collision.h"
#include "object_helpers.h"
#include "object_list_processor.h"
#include "platform_displacement.h"
#include "profiler.h"
#include "spawn_object.h"
#if PUPPYPRINT_DEBUG
#include "puppyprint.h"
#endif
#ifdef VARIABLE_FRAMERATE
#include "engine/rendering_graph_node.h"
#endif
#ifdef PUPPYLIGHTS
#include "engine/colors.h"
#include "puppylights.h"
#endif

/**
 * Flags controlling what debug info is displayed.
 */
#ifdef DEBUG_INFO
s32 gDebugInfoFlags = DEBUG_INFO_FLAG_ALL;
#else
s32 gDebugInfoFlags = DEBUG_INFO_NOFLAGS;
#endif

/**
 * The number of times per frame find_floor found no floor beneath an
 * object, and therefore either returned a dynamic floor or NULL.
 */
s32 gNumFindFloorMisses;

/**
 * An unused debug counter with the label "WALL".
 */
s32 gUnknownWallCount;

/**
 * Roughly the number of objects that have been processed this frame so far.
 * A bug in update_terrain_objects makes this count inaccurate.
 */
u32 gObjectCounter;

/**
 * The number of times find_floor, find_ceil, and find_wall_collisions have been called respectively.
 */
struct NumTimesCalled gNumCalls;

/**
 * An array of debug controls that could be used to tweak in-game parameters.
 * The only used rows are [4] and [5] (effectinfo and enemyinfo).
 */
s16 gDebugInfo[16][8];
s16 gDebugInfoOverwrite[16][8];

/**
 * A set of flags to control which objects are updated on a given frame.
 * This is used during dialog and cutscenes to freeze most objects in place.
 */
u32 gTimeStopState;

/**
 * The pool that objects are allocated from.
 */
struct Object gObjectPool[OBJECT_POOL_CAPACITY];

/**
 * A special object whose purpose is to act as a parent for macro objects.
 */
struct Object gMacroObjectDefaultParent;

/**
 * A pointer to gObjectListArray.
 * Given an object list index idx, gObjectLists[idx] is the head of a doubly
 * linked list of all currently spawned objects in the list.
 */
struct ObjectNode *gObjectLists;

/**
 * A singly linked list of available slots in the object pool.
 */
struct ObjectNode gFreeObjectList;

/**
 * The object representing Mario.
 */
struct Object *gMarioObject;

/**
 * An object variable that may have been used to represent the planned
 * second player. This is speculation, based on its position and its usage in
 * shadow.c.
 */
struct Object *gLuigiObject;

/**
 * The object whose behavior script is currently being updated.
 * This object is used frequently in object behavior code, and so is often
 * aliased as "o".
 */
struct Object *gCurrentObject;

/**
 * The next object behavior command to be executed.
 */
const BehaviorScript *gCurBhvCommand;

/**
 * The number of objects that were processed last frame, which may miss some
 * objects that were spawned last frame and all objects that were spawned this
 * frame. It also includes objects that were unloaded last frame.
 * Besides this, a bug in update_terrain_objects makes this count inaccurate.
 */
s16 gPrevFrameObjectCount;

/**
 * The total number of surface nodes allocated (a node is allocated for each
 * spatial partition cell that a surface intersects).
 */
s32 gSurfaceNodesAllocated;

/**
 * The total number of surfaces allocated.
 */
s32 gSurfacesAllocated;

/**
 * The number of nodes that have been created for surfaces.
 */
s32 gNumStaticSurfaceNodes;

/**
 * The number of surfaces in the pool.
 */
s32 gNumStaticSurfaces;

/**
 * A pool used by chain chomp and wiggler to allocate their body parts.
 */
struct MemoryPool *gObjectMemoryPool;


Bool16     gCheckingSurfaceCollisionsForCamera;
Bool16     gFindFloorIncludeSurfaceIntangible;
Bool16     gFindFloorExcludeDynamic;
#ifdef UNDERWATER_STEEP_FLOORS_AS_WALLS
Bool16     gIncludeSteepFloorsInWallCollisionCheck;
#endif
Collision *gEnvironmentRegions;
Collision  gEnvironmentLevels[20];
RoomData   gDoorAdjacentRooms[60][2];
RoomData   gMarioCurrentRoom;
s16        gDoorRenderingTimer;
Bool16     gTHIWaterDrained;
s16        gTTCSpeedSetting;
Bool16     gMarioShotFromCannon;
Bool16     gCCMEnteredSlide;
s16        gNumRoomedObjectsInMarioRoom;
s16        gNumRoomedObjectsNotInMarioRoom;
Bool16     gWDWWaterLevelChanging;
Bool16     gMarioOnMerryGoRound;

/**
 * Nodes used to represent the doubly linked object lists.
 */
struct ObjectNode gObjectListArray[16];

/**
 * The order that object lists are processed in a frame.
 */
s8 sObjectListUpdateOrder[] = { OBJ_LIST_SPAWNER,
                                OBJ_LIST_SURFACE,
                                OBJ_LIST_POLELIKE,
                                OBJ_LIST_PLAYER,
                                OBJ_LIST_PUSHABLE,
                                OBJ_LIST_GENACTOR,
                                OBJ_LIST_DESTRUCTIVE,
                                OBJ_LIST_LEVEL,
                                OBJ_LIST_DEFAULT,
                                OBJ_LIST_UNIMPORTANT,
                                -1 };

/**
 * Info needed to spawn particles and keep track of which have been spawned for
 * an object.
 */
struct ParticleProperties {
    u32 particleFlag;
    u32 activeParticleFlag;
    ModelID16 model;
    const BehaviorScript *behavior;
};

/**
 * A table mapping particle flags to various properties use when spawning a particle.
 */
struct ParticleProperties sParticleTypes[] = {
    { PARTICLE_DUST,                 ACTIVE_PARTICLE_DUST,                 MODEL_MIST,                 bhvMistParticleSpawner     },
    { PARTICLE_VERTICAL_STAR,        ACTIVE_PARTICLE_V_STAR,               MODEL_NONE,                 bhvVertStarParticleSpawner },
    { PARTICLE_HORIZONTAL_STAR,      ACTIVE_PARTICLE_H_STAR,               MODEL_NONE,                 bhvHorStarParticleSpawner  },
    { PARTICLE_SPARKLES,             ACTIVE_PARTICLE_SPARKLES,             MODEL_SPARKLES,             bhvSparkleParticleSpawner  },
    { PARTICLE_BUBBLE,               ACTIVE_PARTICLE_BUBBLE,               MODEL_BUBBLE,               bhvBubbleParticleSpawner   },
    { PARTICLE_WATER_SPLASH,         ACTIVE_PARTICLE_WATER_SPLASH,         MODEL_WATER_SPLASH,         bhvWaterSplash             },
    { PARTICLE_IDLE_WATER_WAVE,      ACTIVE_PARTICLE_IDLE_WATER_WAVE,      MODEL_IDLE_WATER_WAVE,      bhvIdleWaterWave           },
    { PARTICLE_PLUNGE_BUBBLE,        ACTIVE_PARTICLE_PLUNGE_BUBBLE,        MODEL_WHITE_PARTICLE_SMALL, bhvPlungeBubble            },
    { PARTICLE_WAVE_TRAIL,           ACTIVE_PARTICLE_WAVE_TRAIL,           MODEL_WAVE_TRAIL,           bhvWaveTrail               },
    { PARTICLE_FIRE,                 ACTIVE_PARTICLE_FIRE,                 MODEL_RED_FLAME,            bhvFireParticleSpawner     },
    { PARTICLE_SHALLOW_WATER_WAVE,   ACTIVE_PARTICLE_SHALLOW_WATER_WAVE,   MODEL_NONE,                 bhvShallowWaterWave        },
    { PARTICLE_SHALLOW_WATER_SPLASH, ACTIVE_PARTICLE_SHALLOW_WATER_SPLASH, MODEL_NONE,                 bhvShallowWaterSplash      },
    { PARTICLE_LEAF,                 ACTIVE_PARTICLE_LEAF,                 MODEL_NONE,                 bhvLeafParticleSpawner     },
    { PARTICLE_SNOW,                 ACTIVE_PARTICLE_SNOW,                 MODEL_NONE,                 bhvSnowParticleSpawner     },
    { PARTICLE_BREATH,               ACTIVE_PARTICLE_BREATH,               MODEL_NONE,                 bhvBreathParticleSpawner   },
    { PARTICLE_DIRT,                 ACTIVE_PARTICLE_DIRT,                 MODEL_NONE,                 bhvDirtParticleSpawner     },
    { PARTICLE_MIST_CIRCLE,          ACTIVE_PARTICLE_MIST_CIRCLE,          MODEL_NONE,                 bhvMistCircParticleSpawner },
    { PARTICLE_TRIANGLE,             ACTIVE_PARTICLE_TRIANGLE,             MODEL_NONE,                 bhvTriangleParticleSpawner },
    { 0,                             0,                                    MODEL_NONE,                 NULL                       },
};

/**
 * Copy position, velocity, and angle variables from MarioState to the Mario
 * object.
 */
void copy_mario_state_to_object(void) {
    s32 i = 0;
    // L is real
    if (o != gMarioObject) i++;
    vec3_copy(&o->oVelVec, gMarioStates[i].vel);
    vec3_copy(&o->oPosVec, gMarioStates[i].pos);
    vec3_copy(&o->oMoveAngleVec, o->header.gfx.angle);
    vec3_copy(&o->oFaceAngleVec, o->header.gfx.angle);
    vec3_copy(&o->oAngleVelVec, gMarioStates[i].angleVel);
}

/**
 * Spawn a particle at o's location.
 */
void spawn_particle(u32 activeParticleFlag, ModelID16 model, const BehaviorScript *behavior) {
    if (!(o->oActiveParticleFlags & activeParticleFlag)) {
        struct Object *particle;
        o->oActiveParticleFlags |= activeParticleFlag;
        particle = spawn_object_at_origin(o, 0, model, behavior);
        obj_copy_pos_and_angle(particle, o);
    }
}

#ifdef PUPPYLIGHTS
extern Lights1 mario_blue_lights_group;
extern Lights1 mario_red_lights_group;
extern Lights1 mario_white_lights_group;
extern Lights1 mario_brown1_lights_group;
extern Lights1 mario_beige_lights_group;
extern Lights1 mario_brown2_lights_group;
#endif
/**
 * Mario's primary behavior update function.
 */
void bhv_mario_update(void) {
    s32 i;
    u32 particleFlags = execute_mario_action(gMarioState);
    o->oMarioParticleFlags = particleFlags;
    // Mario code updates MarioState's versions of position etc, so we need
    // to sync it with the Mario object
    copy_mario_state_to_object();
#ifdef PUPPYLIGHTS
    puppylights_run(&mario_blue_lights_group,   gMarioState->marioObj, 0x0, COLOR_RGBA32_MARIO_LIGHTS_BLUE  );
    puppylights_run(&mario_red_lights_group,    gMarioState->marioObj, 0x0, COLOR_RGBA32_MARIO_LIGHTS_RED   );
    puppylights_run(&mario_white_lights_group,  gMarioState->marioObj, 0x0, COLOR_RGBA32_MARIO_LIGHTS_WHITE );
    puppylights_run(&mario_brown1_lights_group, gMarioState->marioObj, 0x0, COLOR_RGBA32_MARIO_LIGHTS_BROWN1);
    puppylights_run(&mario_beige_lights_group,  gMarioState->marioObj, 0x0, COLOR_RGBA32_MARIO_LIGHTS_BEIGE );
    puppylights_run(&mario_brown2_lights_group, gMarioState->marioObj, 0x0, COLOR_RGBA32_MARIO_LIGHTS_BROWN2);
#endif
    i = 0;
    while (sParticleTypes[i].particleFlag != 0x0) {
        if (particleFlags & sParticleTypes[i].particleFlag) {
            spawn_particle(sParticleTypes[i].activeParticleFlag,
                           sParticleTypes[i].model,
                           sParticleTypes[i].behavior);
        }
        i++;
    }
}

/**
 * Update every object that occurs after firstObj in the given object list,
 * including firstObj itself. Return the number of objects that were updated.
 */
s32 update_objects_starting_at(struct ObjectNode *objList, struct ObjectNode *firstObj) {
    s32 count = 0;
    while (objList != firstObj) {
        o = (struct Object *) firstObj;
        o->header.gfx.node.flags |= GRAPH_RENDER_HAS_ANIMATION;
        cur_obj_update();
        firstObj = firstObj->next;
        count++;
    }
    return count;
}

/**
 * Update objects in objList starting with firstObj while time stop is active.
 * This means that only certain select objects will be updated, such as Mario,
 * doors, unimportant objects, and the object that initiated time stop.
 * The exact set of objects that are updated depends on which flags are set
 * in gTimeStopState.
 * Return the total number of objects in the list (including those that weren't
 * updated)
 */
s32 update_objects_during_time_stop(struct ObjectNode *objList, struct ObjectNode *firstObj) {
    s32 count = 0;
    s32 unfrozen;
    while (objList != firstObj) {
        o = (struct Object *) firstObj;
        unfrozen = FALSE;
        // Selectively unfreeze certain objects
        if (!(gTimeStopState & TIME_STOP_ALL_OBJECTS)) {
            if (o == gMarioObject && !(gTimeStopState & TIME_STOP_MARIO_AND_DOORS)) unfrozen = TRUE;
            if ((o->oInteractType & (INTERACT_DOOR | INTERACT_WARP_DOOR)) && !(gTimeStopState & TIME_STOP_MARIO_AND_DOORS)) unfrozen = TRUE;
            if (o->activeFlags & (ACTIVE_FLAG_UNIMPORTANT | ACTIVE_FLAG_INITIATED_TIME_STOP)) unfrozen = TRUE;
        }
        // Only update if unfrozen
        if (unfrozen) {
            o->header.gfx.node.flags |=  GRAPH_RENDER_HAS_ANIMATION;
            cur_obj_update();
        } else {
            o->header.gfx.node.flags &= ~GRAPH_RENDER_HAS_ANIMATION;
        }
        firstObj = firstObj->next;
        count++;
    }
    return count;
}

/**
 * Update every object in the given list. Return the total number of objects in
 * the list.
 */
s32 update_objects_in_list(struct ObjectNode *objList) {
    struct ObjectNode *firstObj = objList->next;
    if (gTimeStopState & TIME_STOP_ACTIVE) {
        return update_objects_during_time_stop(objList, firstObj);
    } else {
        return update_objects_starting_at(objList, firstObj);
    }
}

/**
 * Unload any objects in the list that have been deactivated.
 */
void unload_deactivated_objects_in_list(struct ObjectNode *objList) {
    struct ObjectNode *obj = objList->next;
    while (objList != obj) {
        o = (struct Object *) obj;
        obj = obj->next;
        if ((o->activeFlags & ACTIVE_FLAG_ACTIVE) != ACTIVE_FLAG_ACTIVE) {
#ifdef PUPPYLIGHTS
            if (o->oLightID != 0xFFFF) obj_disable_light(o);
#endif
            // Prevent object from respawning after exiting and re-entering the area
            if (!(o->oFlags & OBJ_FLAG_PERSISTENT_RESPAWN)) set_object_respawn_info_bits(o, RESPAWN_INFO_DONT_RESPAWN);
            unload_object(o);
        }
    }
}

/**
 * OR the object's respawn info with bits << 8. If bits = 0xFF, this prevents
 * the object from respawning after leaving and re-entering the area.
 * For macro objects, respawnInfo points to the 16 bit entry in the macro object
 * list. For other objects, it points to the 32 bit behaviorArg in the
 * SpawnInfo.
 */
void set_object_respawn_info_bits(struct Object *obj, u8 bits) {
    u32 *info32;
    u16 *info16;
    switch (obj->respawnInfoType) {
        case RESPAWN_INFO_TYPE_32: info32 = (u32 *)obj->respawnInfo; *info32 |= (bits << 8); break;
        case RESPAWN_INFO_TYPE_16: info16 = (u16 *)obj->respawnInfo; *info16 |= (bits << 8); break;
    }
}

/**
 * Unload all objects whose activeAreaIndex is areaIndex.
 */
void unload_objects_from_area(s32 areaIndex) {
    struct Object *obj;
    struct ObjectNode *node;
    struct ObjectNode *list;
    s32 i;
    gObjectLists = gObjectListArray;
    for ((i = 0); (i < NUM_OBJ_LISTS); (i++)) {
        list = gObjectLists + i;
        node = list->next;
        while (node != list) {
            obj = (struct Object *) node;
            node = node->next;
            if (obj->header.gfx.activeAreaIndex == areaIndex) unload_object(obj);
        }
    }
}

/**
 * Spawn objects given a list of SpawnInfos. Called when loading an area.
 */
void spawn_objects_from_info(struct SpawnInfo *spawnInfo) {
    gObjectLists           = gObjectListArray;
    gTimeStopState         = 0;
    gWDWWaterLevelChanging = FALSE;
    gMarioOnMerryGoRound   = FALSE;
    clear_mario_platform();
    if (gCurrAreaIndex == 2) gCCMEnteredSlide = TRUE;
    while (spawnInfo != NULL) {
        struct Object *object;
        const BehaviorScript *script;
        script = segmented_to_virtual(spawnInfo->behaviorScript);
        // If the object was previously killed/collected, don't respawn it
        if ((spawnInfo->behaviorArg & (RESPAWN_INFO_DONT_RESPAWN << 8)) != (RESPAWN_INFO_DONT_RESPAWN << 8)) {
            object = create_object(script);
            // Behavior parameters are often treated as four separate bytes, but
            // are stored as an s32.
            object->oBehParams        = spawnInfo->behaviorArg;
            // The second byte of the behavior parameters is copied over to a special field
            // as it is the most frequently used by objects.
            object->oBehParams2ndByte = (((spawnInfo->behaviorArg) >> 16) & 0xFF);
            object->behavior          = script;
            // object->unused1           = 0;
            // Record death/collection in the SpawnInfo
            object->respawnInfoType   = RESPAWN_INFO_TYPE_32;
            object->respawnInfo       = &spawnInfo->behaviorArg;
            if (object->behavior == segmented_to_virtual(bhvMario)) {
                gMarioObject          = object;
                geo_make_first_child(&object->header.gfx.node);
            }
            geo_obj_init_spawninfo(&object->header.gfx, spawnInfo);
            vec3_copy(&object->oPosVec, spawnInfo->startPos);
            vec3_copy(&object->oFaceAngleVec, spawnInfo->startAngle);
            vec3_copy(&object->oMoveAngleVec, spawnInfo->startAngle);
        }
        spawnInfo = spawnInfo->next;
    }
}

/**
 * Clear objects, dynamic surfaces, and some miscellaneous level data used by objects.
 */
void clear_objects(void) {
    s32 i;
    gTHIWaterDrained  = FALSE;
    gTimeStopState    = 0;
    gMarioObject      = NULL;
    gMarioCurrentRoom = 0;
    for ((i = 0); (i < 60); (i++)) {
        gDoorAdjacentRooms[i][0] = 0;
        gDoorAdjacentRooms[i][1] = 0;
    }
    debug_unknown_level_select_check();
    init_free_object_list();
    clear_object_lists(gObjectListArray);
    for ((i = 0); (i < OBJECT_POOL_CAPACITY); (i++)) {
        gObjectPool[i].activeFlags = ACTIVE_FLAG_DEACTIVATED;
        geo_reset_object_node(&gObjectPool[i].header.gfx);
    }
    gObjectMemoryPool = mem_pool_init(0x800, MEMORY_POOL_LEFT);
    gObjectLists      = gObjectListArray;
    clear_dynamic_surfaces();
}

/**
 * Update spawner and surface objects.
 */
void update_terrain_objects(void) {
    gObjectCounter  = update_objects_in_list(&gObjectLists[OBJ_LIST_SPAWNER]);
    gObjectCounter += update_objects_in_list(&gObjectLists[OBJ_LIST_SURFACE]);
}

/**
 * Update all other object lists besides spawner and surface objects, using
 * the order specified by sObjectListUpdateOrder.
 */
void update_non_terrain_objects(void) {
    s32 listIndex;
    s32 i = 2;
    while ((listIndex = sObjectListUpdateOrder[i]) != -1) {
        gObjectCounter += update_objects_in_list(&gObjectLists[listIndex]);
        i++;
    }
}

/**
 * Unload deactivated objects in any object list.
 */
void unload_deactivated_objects(void) {
    s32 listIndex;
    s32 i = 0;
    while ((listIndex = sObjectListUpdateOrder[i]) != -1) {
        unload_deactivated_objects_in_list(&gObjectLists[listIndex]);
        i++;
    }
    // TIME_STOP_UNKNOWN_0 was most likely intended to be used to track whether
    // any objects had been deactivated
    gTimeStopState &= ~TIME_STOP_UNKNOWN_0;
}

// /**
//  * Unused profiling function.
//  */
// UNUSED static u16 unused_get_elapsed_time(u64 *cycleCounts, s32 index) {
//     u16 time;
//     f64 cycles;

//     cycles = cycleCounts[index] - cycleCounts[index - 1];
//     if (cycles < 0) {
//         cycles = 0;
//     }

//     time = (u16)(((u64) cycles * 1000000 / osClockRate) / 16667.0 * 1000.0);
//     if (time > 999) {
//         time = 999;
//     }

//     return time;
// }

/**
 * Update all objects. This includes script execution, object collision detection,
 * and object surface management.
 */
void update_objects(void) {
#ifdef VARIABLE_FRAMERATE
    s32 i = 0;
    Mat4 zero = {0, 0, 0, 0};
#endif
    // s64 cycleCounts[30];
#if PUPPYPRINT_DEBUG
    OSTime first   = osGetTime();
    OSTime colTime = collisionTime[perfIteration];
#endif
    // cycleCounts[0] = get_current_clock();
    gTimeStopState &= ~TIME_STOP_MARIO_OPENED_DOOR;
    gNumRoomedObjectsInMarioRoom        = 0;
    gNumRoomedObjectsNotInMarioRoom     = 0;
    gCheckingSurfaceCollisionsForCamera = FALSE;
#ifdef UNDERWATER_STEEP_FLOORS_AS_WALLS
    gIncludeSteepFloorsInWallCollisionCheck = FALSE;
#endif
    reset_debug_objectinfo();
#ifdef DEBUG_INFO
    show_debug_info();
#endif
    gObjectLists = gObjectListArray;
    // If time stop is not active, unload object surfaces
    // cycleCounts[1] = get_clock_difference(cycleCounts[0]);
    clear_dynamic_surfaces();
    // Update spawners and objects with surfaces
    // cycleCounts[2] = get_clock_difference(cycleCounts[0]);
    update_terrain_objects();
    // If Mario was touching a moving platform at the end of last frame, apply displacement now
    //! If the platform object unloaded and a different object took its place, displacement could be applied incorrectly
    apply_mario_platform_displacement();
    // Detect which objects are intersecting
    // cycleCounts[3] = get_clock_difference(cycleCounts[0]);
    detect_object_collisions();
    // Update all other objects that haven't been updated yet
    // cycleCounts[4] = get_clock_difference(cycleCounts[0]);
    update_non_terrain_objects();
    // Unload any objects that have been deactivated
    // cycleCounts[5] = get_clock_difference(cycleCounts[0]);
    unload_deactivated_objects();
    // Check if Mario is on a platform object and save this object
    // cycleCounts[6] = get_clock_difference(cycleCounts[0]);
    update_mario_platform();
    // cycleCounts[7] = get_clock_difference(cycleCounts[0]);
    // cycleCounts[0] = 0;
    try_print_debug_mario_object_info();
    // If time stop was enabled this frame, activate it now so that it will
    // take effect next frame
    if (gTimeStopState & TIME_STOP_ENABLED) {
        gTimeStopState |=  TIME_STOP_ACTIVE;
    } else {
        gTimeStopState &= ~TIME_STOP_ACTIVE;
    }
    gPrevFrameObjectCount = gObjectCounter;
#ifdef VARIABLE_FRAMERATE
    gThrowMatIndex = 0;
    gThrowMatSwap ^= 1;
    for ((i = 0); (i < THROWMATSTACK); (i++)) mtxf_copy(gThrowMatStack[gThrowMatSwap][i], zero);
#endif
#if PUPPYPRINT_DEBUG
    profiler_update(behaviourTime, first);
    behaviourTime[perfIteration] -= (collisionTime[perfIteration] + colTime);
#endif
}
