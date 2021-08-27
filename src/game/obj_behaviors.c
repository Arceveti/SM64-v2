#include <PR/ultratypes.h>

#include "sm64.h"
#include "area.h"
#include "audio/external.h"
#include "behavior_actions.h"
#include "behavior_data.h"
#include "camera.h"
#include "cutscene.h"
#include "course_table.h"
#include "dialog_ids.h"
#include "engine/behavior_script.h"
#include "engine/math_util.h"
#include "engine/surface_collision.h"
#include "envfx_bubbles.h"
#include "game_init.h"
#include "ingame_menu.h"
#include "interaction.h"
#include "level_misc_macros.h"
#include "level_table.h"
#include "level_update.h"
#include "levels/bob/header.h"
#include "levels/ttm/header.h"
#include "mario.h"
#include "mario_actions_cutscene.h"
#include "mario_misc.h"
#include "boot/memory.h"
#include "obj_behaviors.h"
#include "object_helpers.h"
#include "object_list_processor.h"
#include "rendering_graph_node.h"
#include "save_file.h"
#include "spawn_object.h"
#include "spawn_sound.h"
#include "rumble_init.h"

/**
 * @file obj_behaviors.c
 * This file contains a portion of the obj behaviors and many helper functions for those
 * specific behaviors. Few functions besides the bhv_ functions are used elsewhere in the repo.
 */

#define o gCurrentObject

#define OBJ_COL_FLAGS_NONE          0x0
#define OBJ_COL_FLAG_GROUNDED   (1 << 0)
#define OBJ_COL_FLAG_HIT_WALL   (1 << 1)
#define OBJ_COL_FLAG_UNDERWATER (1 << 2)
#define OBJ_COL_FLAG_NO_Y_VEL   (1 << 3)
#define OBJ_COL_FLAGS_LANDED    (OBJ_COL_FLAG_GROUNDED | OBJ_COL_FLAG_NO_Y_VEL)

/**
 * Current object floor as defined in object_step.
 */
static struct Surface *sObjFloor;

/**
 * Set to false when an object close to the floor should not be oriented in reference
 * to it. Happens with boulder, falling pillar, and the rolling snowman body.
 */
static Bool8 sOrientObjWithFloor = TRUE;

/**
 * Keeps track of Mario's previous non-zero room.
 * Helps keep track of room when Mario is over an object.
 */
s16 sPrevCheckMarioRoom = 0;

/**
 * Tracks whether or not Yoshi has walked/jumped off the roof.
 */
Bool8 sYoshiDead = FALSE;

extern void *ccm_seg7_trajectory_snowman;
extern void *inside_castle_seg7_trajectory_mips;

/**
 * Resets yoshi as spawned/despawned upon new file select.
 * Possibly a function with stubbed code.
 */
void set_yoshi_as_not_dead(void) {
    sYoshiDead = FALSE;
}

/**
 * An unused geo function. Bears strong similarity to geo_bits_bowser_coloring, and relates something
 * of the opacity of an object to something else. Perhaps like, giving a parent object the same
 * opacity?
 */
Gfx UNUSED *geo_obj_transparency_something(s32 callContext, struct GraphNode *node, UNUSED Mat4 *mtx) {
    Gfx *gfxHead;
    Gfx *gfx;
    struct Object *heldObject;
    struct Object *obj;
    gfxHead = NULL;
    if (callContext == GEO_CONTEXT_RENDER) {
        heldObject = (struct Object *) gCurGraphNodeObject;
        obj = (struct Object *) node;
        if (gCurGraphNodeHeldObject != NULL) heldObject = gCurGraphNodeHeldObject->objNode;
        gfxHead                    = alloc_display_list(3 * sizeof(Gfx));
        gfx                        = gfxHead;
        obj->header.gfx.node.flags = ((obj->header.gfx.node.flags & GRAPH_NODE_TYPES_MASK) | (LAYER_TRANSPARENT << 8));
        gDPSetEnvColor(   gfx++, 255, 255, 255, heldObject->oOpacity);
        gSPEndDisplayList(gfx);
    }
    return gfxHead;
}

/**
 * Turns an object away from floors/walls that it runs into.
 */
void turn_obj_away_from_surface(f32 velX, f32 velZ, f32 nX, UNUSED f32 nY, f32 nZ, f32 *objYawX, f32 *objYawZ) {
    f32 nX2  =  sqr(nX);
    f32 nZ2  =  sqr(nZ);
    f32 nXZ2 = (nX2 + nZ2);
    *objYawX = ((((nZ2 - nX2) * velX) / nXZ2) - ((2 * velZ * (nX * nZ)) / nXZ2));
    *objYawZ = ((((nX2 - nZ2) * velZ) / nXZ2) - ((2 * velX * (nX * nZ)) / nXZ2));
}

/**
 * Finds any wall collisions, applies them, and turns away from the surface.
 */
Bool32 obj_find_wall(f32 objNewX, f32 objY, f32 objNewZ, f32 objVelX, f32 objVelZ) {
    struct WallCollisionData hitbox;
    register f32 wall_nX, wall_nY, wall_nZ, objVelXCopy, objVelZCopy;
    f32 objYawX, objYawZ;
    vec3f_set(hitbox.pos, objNewX, objY, objNewZ);
    hitbox.offsetY = (o->hitboxHeight / 2);
    hitbox.radius  =  o->hitboxRadius;
    if (find_wall_collisions(&hitbox) != 0) {
        vec3f_copy(&o->oPosVec, hitbox.pos);
        wall_nX     = hitbox.walls[0]->normal.x;
        wall_nY     = hitbox.walls[0]->normal.y;
        wall_nZ     = hitbox.walls[0]->normal.z;
        objVelXCopy = objVelX;
        objVelZCopy = objVelZ;
        // Turns away from the first wall only.
        turn_obj_away_from_surface(objVelXCopy, objVelZCopy, wall_nX, wall_nY, wall_nZ, &objYawX, &objYawZ);
        o->oMoveAngleYaw = atan2s(objYawZ, objYawX);
        return FALSE;
    }
    return TRUE;
}

/**
 * Turns an object away from steep floors, similarly to walls.
 */
Bool32 turn_obj_away_from_steep_floor(struct Surface *objFloor, f32 floorY, f32 objVelX, f32 objVelZ) {
    f32 floor_nY, objVelXCopy, objVelZCopy, objYawX, objYawZ;
    if (objFloor == NULL) {
        //! (OOB Object Crash) TRUNC overflow exception after 36 minutes
        o->oMoveAngleYaw += DEGREES(180); // vanilla was 32767.999200000002; /* ¯\_(ツ)_/¯ */
        return FALSE;
    }
    floor_nY = objFloor->normal.y;
    // If the floor is steep and we are below it (i.e. walking into it), turn away from the floor.
    if ((floor_nY < 0.5f) && (floorY > o->oPosY)) {
        //? are these needed?
        objVelXCopy = objVelX;
        objVelZCopy = objVelZ;
        turn_obj_away_from_surface(objVelXCopy, objVelZCopy, objFloor->normal.x, floor_nY, objFloor->normal.z, &objYawX, &objYawZ);
        o->oMoveAngleYaw = atan2s(objYawZ, objYawX);
        return FALSE;
    }
    return TRUE;
}

/**
 * Orients an object with the given normals, typically the surface under the object.
 */
void obj_orient_graph(struct Object *obj, f32 normalX, f32 normalY, f32 normalZ) {
    Vec3f objVisualPosition, surfaceNormals;
    Mat4 *throwMatrix;
    // Passes on orienting certain objects that shouldn't be oriented, like boulders.
    if (!sOrientObjWithFloor) return;
    // Passes on orienting billboard objects, i.e. coins, trees, etc.
    if (obj->header.gfx.node.flags & GRAPH_RENDER_BILLBOARD) return;
    throwMatrix = alloc_display_list(sizeof(*throwMatrix));
    // If out of memory, fail to try orienting the object.
    if (throwMatrix == NULL) return;
    objVisualPosition[0] =  obj->oPosX;
    objVisualPosition[1] = (obj->oPosY + obj->oGraphYOffset);
    objVisualPosition[2] =  obj->oPosZ;
    vec3f_set(surfaceNormals, normalX, normalY, normalZ);
    mtxf_align_terrain_normal(*throwMatrix, surfaceNormals, objVisualPosition, obj->oFaceAngleYaw);
    obj->header.gfx.throwMatrix = throwMatrix;
}

/**
 * Determines an object's forward speed multiplier.
 */
void calc_obj_friction(f32 *objFriction, f32 floor_nY) {
    *objFriction = (((floor_nY < 0.2f) && (o->oFriction < 0.9999f)) ? 0 : o->oFriction);
}

/**
 * Updates an objects speed for gravity and updates Y position.
 */
void calc_new_obj_vel_and_pos_y(struct Surface *objFloor, f32 objFloorY, f32 objVelX, f32 objVelZ) {
    f32 floor_nX2, floor_nZ2, floor_nXZ;
    f32 floor_nX = objFloor->normal.x;
    f32 floor_nY = objFloor->normal.y;
    f32 floor_nZ = objFloor->normal.z;
    f32 objFriction;
    // Caps vertical speed with a terminal velocity.
    o->oVelY -= o->oGravity;
    if (o->oVelY >  TERMINAL_GRAVITY_VELOCITY) o->oVelY =  TERMINAL_GRAVITY_VELOCITY;
    if (o->oVelY < -TERMINAL_GRAVITY_VELOCITY) o->oVelY = -TERMINAL_GRAVITY_VELOCITY;
    o->oPosY += o->oVelY;
    // Snap the object up to the floor.
#ifdef OBJ_STEP_HEIGHT
    if (absf(o->oPosY - objFloorY) < OBJ_STEP_HEIGHT) {
#else
    if (o->oPosY < objFloorY) {
#endif
        o->oPosY = objFloorY;
        // Bounces an object if the ground is hit fast enough.
        o->oVelY = ((o->oVelY < -17.5f) ? -(o->oVelY / 2.0f) : 0.0f);
    }
    //! (Obj Position Crash) If you got an object with height past 2^31, the game would crash.
    if (((s32) o->oPosY >= (s32) objFloorY) && (s32) (o->oPosY < (s32) objFloorY + 37)) {
        obj_orient_graph(o, floor_nX, floor_nY, floor_nZ);
        floor_nX2 = sqr(floor_nX);
        floor_nZ2 = sqr(floor_nZ);
        floor_nXZ = ((floor_nX2 + floor_nZ2) / (floor_nX2 + sqr(floor_nY) + floor_nZ2) * o->oGravity * 2);
        // Adds horizontal component of gravity for horizontal speed.
        objVelX += floor_nX * floor_nXZ;
        objVelZ += floor_nZ * floor_nXZ;
        if ((objVelX < 0.000001f) && (objVelX > -0.000001f)) objVelX = 0;
        if ((objVelZ < 0.000001f) && (objVelZ > -0.000001f)) objVelZ = 0;
        if ((objVelX != 0) || (objVelZ != 0)) o->oMoveAngleYaw = atan2s(objVelZ, objVelX);
        calc_obj_friction(&objFriction, floor_nY);
        o->oForwardVel = (sqrtf(sqr(objVelX) + sqr(objVelZ)) * objFriction);
    }
}

void calc_new_obj_vel_and_pos_y_underwater(struct Surface *objFloor, f32 floorY, f32 objVelX, f32 objVelZ, f32 waterY) {
    f32 floor_nX2, floor_nZ2, floor_nXZ;
    f32 floor_nX  = objFloor->normal.x;
    f32 floor_nY  = objFloor->normal.y;
    f32 floor_nZ  = objFloor->normal.z;
    f32 netYAccel = ((1.0f - o->oBuoyancy) * (-o->oGravity));
    o->oVelY -= netYAccel;
    // Caps vertical speed with a terminal velocity.
    if (o->oVelY >  TERMINAL_GRAVITY_VELOCITY) o->oVelY =  TERMINAL_GRAVITY_VELOCITY;
    if (o->oVelY < -TERMINAL_GRAVITY_VELOCITY) o->oVelY = -TERMINAL_GRAVITY_VELOCITY;
    o->oPosY += o->oVelY;
    // Snap the object up to the floor.
    if (o->oPosY < floorY) {
        o->oPosY = floorY;
        // Bounces an object if the ground is hit fast enough.
        o->oVelY = ((o->oVelY < -17.5f) ? -(o->oVelY / 2.0f) : 0.0f);
    }
    // If moving fast near the surface of the water, flip vertical speed? To emulate skipping?
    if ((o->oForwardVel > 12.5f) && ((waterY + 30.0f) > o->oPosY) && ((waterY - 30.0f) < o->oPosY)) o->oVelY = -o->oVelY;
    if (((s32) o->oPosY >= (s32) floorY) && ((s32) o->oPosY < (s32) floorY + 37)) {
        obj_orient_graph(o, floor_nX, floor_nY, floor_nZ);
        floor_nX2 = sqr(floor_nX);
        floor_nZ2 = sqr(floor_nZ);
        floor_nXZ = ((floor_nX2 + floor_nZ2) / (floor_nX2 + sqr(floor_nY) + floor_nZ2) * netYAccel * 2);
        // Adds horizontal component of gravity for horizontal speed.
        objVelX  += floor_nX * floor_nXZ;
        objVelZ  += floor_nZ * floor_nXZ;
    }
    if (( objVelX < 0.000001f) && ( objVelX > -0.000001f))  objVelX = 0;
    if (( objVelZ < 0.000001f) && ( objVelZ > -0.000001f))  objVelZ = 0;
    if ((o->oVelY < 0.000001f) && (o->oVelY > -0.000001f)) o->oVelY = 0;
    if ((objVelX != 0) || (objVelZ != 0)) o->oMoveAngleYaw = atan2s(objVelZ, objVelX);
    // Decreases both vertical velocity and forward velocity. Likely so that skips above
    // don't loop infinitely.
    o->oForwardVel = (sqrtf(sqr(objVelX) + sqr(objVelZ)) * 0.8f);
    o->oVelY      *= 0.8f;
}

/**
 * Updates an objects position from oForwardVel and oMoveAngleYaw.
 */
void obj_update_pos_vel_xz(void) {
    o->oPosX += (o->oForwardVel * sins(o->oMoveAngleYaw));
    o->oPosZ += (o->oForwardVel * coss(o->oMoveAngleYaw));
}

/**
 * Generates splashes if at surface of water, entering water, or bubbles
 * if underwater.
 */
void obj_splash(s32 waterY, s32 objY) {
    // Spawns waves if near surface of water and plays a noise if entering.
    if (((f32)(waterY + 30) > o->oPosY) && (o->oPosY > (f32)(waterY - 30))) {
        spawn_object(o, MODEL_IDLE_WATER_WAVE, bhvObjectWaterWave);
        if (o->oVelY < -20.0f) cur_obj_play_sound_2(SOUND_OBJ_DIVING_INTO_WATER);
    }
    // Spawns bubbles if underwater.
    if (((objY + 50) < waterY) && !(gGlobalTimer & 0x1F)) spawn_object(o, MODEL_WHITE_PARTICLE_SMALL, bhvObjectBubble);
}

/**
 * Generic object move function. Handles walls, water, floors, and gravity.
 * Returns flags for certain interactions.
 */
ColFlags object_step(void) {
    f32 objVelX = (o->oForwardVel * sins(o->oMoveAngleYaw));
    f32 objVelZ = (o->oForwardVel * coss(o->oMoveAngleYaw));
    f32 nextX   = (o->oPosX + objVelX);
    f32 nextY   =  o->oPosY;
    f32 nextZ   = (o->oPosZ + objVelZ);
    f32 waterY  = FLOOR_LOWER_LIMIT_MISC;
    f32 floorY;
    ColFlags collisionFlags = 0x0;
    // Find any wall collisions, receive the push, and set the flag.
    if (!obj_find_wall(nextX, nextY, nextZ, objVelX, objVelZ)) collisionFlags |= OBJ_COL_FLAG_HIT_WALL;
    floorY = find_floor(nextX, nextY, nextZ, &sObjFloor);
    if (turn_obj_away_from_steep_floor(sObjFloor, floorY, objVelX, objVelZ)) {
        waterY = find_water_level(nextX, nextZ);
        if (waterY > nextY) {
            calc_new_obj_vel_and_pos_y_underwater(sObjFloor, floorY, objVelX, objVelZ, waterY);
            collisionFlags |= OBJ_COL_FLAG_UNDERWATER;
        } else {
            calc_new_obj_vel_and_pos_y(sObjFloor, floorY, objVelX, objVelZ);
        }
    } else {
        // Treat any awkward floors similar to a wall.
        collisionFlags |= ((collisionFlags & OBJ_COL_FLAG_HIT_WALL) ^ OBJ_COL_FLAG_HIT_WALL);
    }
    obj_update_pos_vel_xz();
    if ((s32) o->oPosY == (s32) floorY) collisionFlags |= OBJ_COL_FLAG_GROUNDED;
    if ((s32) o->oVelY ==         0.0f) collisionFlags |= OBJ_COL_FLAG_NO_Y_VEL;
    // Generate a splash if in water.
    obj_splash((s32) waterY, (s32) o->oPosY);
    return collisionFlags;
}

/**
 * Takes an object step but does not orient with the object's floor.
 * Used for boulders, falling pillars, and the rolling snowman body.
 */
ColFlags object_step_without_floor_orient(void) {
    sOrientObjWithFloor = FALSE;
    ColFlags collisionFlags  = object_step();
    sOrientObjWithFloor = TRUE;
    return collisionFlags;
}

/**
 * Uses an object's forward velocity and yaw to move its X, Y, and Z positions.
 * This does accept an object as an argument, though it is always called with `o`.
 * If it wasn't called with `o`, it would modify `o`'s X and Z velocities based on
 * `obj`'s forward velocity and yaw instead of `o`'s, and wouldn't update `o`'s
 * position.
 */
void obj_move_xyz_using_fvel_and_yaw(struct Object *obj) {
    o->oVelX    = (obj->oForwardVel * sins(obj->oMoveAngleYaw));
    o->oVelZ    = (obj->oForwardVel * coss(obj->oMoveAngleYaw));
    obj->oPosX +=   o->oVelX;
    obj->oPosY += obj->oVelY;
    obj->oPosZ +=   o->oVelZ;
}

/**
 * Checks if a point is within distance from Mario's graphical position. Test is exclusive.
 */
Bool32 is_point_within_radius_of_mario(f32 x, f32 y, f32 z, s32 dist) {
    register f32 dx = (x - gMarioObject->header.gfx.pos[0]);
    register f32 dy = (y - gMarioObject->header.gfx.pos[1]);
    register f32 dz = (z - gMarioObject->header.gfx.pos[2]);
    return ((sqr(dx) + sqr(dy) + sqr(dz)) < (f32)sqr(dist));
}

/**
 * Checks whether a point is within distance of a given point. Test is exclusive.
 */
Bool32 is_point_close_to_object(struct Object *obj, f32 x, f32 y, f32 z, s32 dist) {
    register f32 dx = (x - obj->oPosX);
    register f32 dy = (y - obj->oPosY);
    register f32 dz = (z - obj->oPosZ);
    return ((sqr(dx) + sqr(dy) + sqr(dz)) < (f32)sqr(dist));
}

/**
 * Sets an object as visible if within a certain distance of Mario's graphical position.
 */
void set_object_visibility(struct Object *obj, s32 dist) {
    f32 objX = obj->oPosX;
    f32 objY = obj->oPosY;
    f32 objZ = obj->oPosZ;
    if (is_point_within_radius_of_mario(objX, objY, objZ, dist)) {
        obj->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
    } else {
        obj->header.gfx.node.flags |=  GRAPH_RENDER_INVISIBLE;
    }
}

/**
 * Turns an object towards home if Mario is not near to it.
 */
Bool32 obj_return_home_if_safe(struct Object *obj, f32 homeX, f32 y, f32 homeZ, s32 dist) {
    f32 homeDistX = (homeX - obj->oPosX);
    f32 homeDistZ = (homeZ - obj->oPosZ);
    Angle angleTowardsHome = atan2s(homeDistZ, homeDistX);
    if (is_point_within_radius_of_mario(homeX, y, homeZ, dist)) {
        return TRUE;
    } else {
        obj->oMoveAngleYaw = approach_s16_symmetric(obj->oMoveAngleYaw, angleTowardsHome, 320);
    }
    return FALSE;
}

/**
 * Randomly displaces an objects home if RNG says to, and turns the object towards its home.
 */
void obj_return_and_displace_home(struct Object *obj, f32 homeX, UNUSED f32 homeY, f32 homeZ, s32 baseDisp) {
    Angle angleToNewHome;
    f32 homeDistX, homeDistZ;
    f32 disp;
    if ((s32)(random_float() * 50.0f) == 0) {
        disp        = (((f32)(baseDisp * 2) * random_float()) - (f32) baseDisp);
        obj->oHomeX = (disp + homeX);
        obj->oHomeZ = (disp + homeZ);
    }
    homeDistX          = (obj->oHomeX - obj->oPosX);
    homeDistZ          = (obj->oHomeZ - obj->oPosZ);
    angleToNewHome     = atan2s(homeDistZ, homeDistX);
    obj->oMoveAngleYaw = approach_s16_symmetric(obj->oMoveAngleYaw, angleToNewHome, 320);
}

/**
 * A series of checks using sin and cos to see if a given angle is facing in the same direction
 * of a given angle, within a certain range.
 */
Bool32 obj_check_if_facing_toward_angle(u32 base, u32 goal, Angle range) {
    Angle dAngle = ((u16) goal - (u16) base);
    return (((f32) sins(-range) < (f32) sins(dAngle)) && ((f32) sins(dAngle) < (f32) sins(range)) && (coss(dAngle) > 0));
}

//! move to surface_collision?
/**
 * Finds any wall collisions and returns what the displacement vector would be.
 */
Bool32 obj_find_wall_displacement(Vec3f dist, f32 x, f32 y, f32 z, f32 radius) {
    struct WallCollisionData hitbox;
    vec3f_set(hitbox.pos, x, y, z);
    hitbox.offsetY = 10.0f;
    hitbox.radius  = radius;
    if (find_wall_collisions(&hitbox) != 0) {
        //? can xyz be a vec
        dist[0] = (hitbox.pos[0] - x);
        dist[1] = (hitbox.pos[1] - y);
        dist[2] = (hitbox.pos[2] - z);
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * Spawns a number of coins at the location of an object
 * with a random forward velocity, y velocity, and direction.
 */
void obj_spawn_yellow_coins(struct Object *obj, s8 nCoins) {
    struct Object *coin;
    s8 count;
    for ((count = 0); (count < nCoins); (count++)) {
        coin = spawn_object(obj, MODEL_YELLOW_COIN, bhvMovingYellowCoin);
        coin->oForwardVel   =  (random_float() * 20.0f);
        coin->oVelY         = ((random_float() * 40.0f) + 20.0f);
        coin->oMoveAngleYaw = random_u16();
    }
}

/**
 * Controls whether certain objects should flicker/when to despawn.
 */
Bool32 obj_flicker_and_disappear(struct Object *obj, s16 lifeSpan) {
    if (obj->oTimer < lifeSpan) return FALSE;
    if (obj->oTimer < (lifeSpan + 40)) {
        if (obj->oTimer & 0x1) {
            obj->header.gfx.node.flags |=  GRAPH_RENDER_INVISIBLE;
        } else {
            obj->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
        }
    } else {
        obj->activeFlags = ACTIVE_FLAG_DEACTIVATED;
        return TRUE;
    }
    return FALSE;
}

/**
 * Checks if a given room is Mario's current room, even if on an object.
 */
Bool32 current_mario_room_check(RoomData room) {
    Bool32 result;
    // Since object surfaces have room 0, this tests if the surface is an
    // object first and uses the last room if so.
    if (gMarioCurrentRoom == 0) {
        return (room == sPrevCheckMarioRoom);
    } else {
        result              = (room == gMarioCurrentRoom);
        sPrevCheckMarioRoom =          gMarioCurrentRoom;
    }
    return result;
}

/**
 * Triggers dialog when Mario is facing an object and controls it while in the dialog.
 */
//! sBool32? DialogID16?
s16 trigger_obj_dialog_when_facing(s32 *inDialog, DialogID dialogID, f32 dist, s32 actionArg) {
    s16 dialogueResponse;
    if ((is_point_within_radius_of_mario(o->oPosX, o->oPosY, o->oPosZ, (s32) dist)
      && obj_check_if_facing_toward_angle(o->oFaceAngleYaw, (gMarioObject->header.gfx.angle[1] + DEGREES(180)), 0x1000)
      && obj_check_if_facing_toward_angle(o->oMoveAngleYaw, o->oAngleToMario, 0x1000)) || (*inDialog)) {
        *inDialog = TRUE;
        if (set_mario_npc_dialog(actionArg) == MARIO_DIALOG_STATUS_SPEAK) { //If Mario is speaking.
            dialogueResponse = cutscene_object_with_dialog(CUTSCENE_DIALOG, o, dialogID);
            if (dialogueResponse) {
                set_mario_npc_dialog(MARIO_DIALOG_STOP);
                *inDialog = FALSE;
                return dialogueResponse;
            }
        }
    }
    return 0;
}

/**
 *Checks if a floor is one that should cause an object to "die".
 */
void obj_check_floor_death(ColFlags collisionFlags, struct Surface *floor) {
    if (floor == NULL) return;
    if (collisionFlags & OBJ_COL_FLAG_GROUNDED) {
        switch (floor->type) {
            case SURFACE_BURNING:       o->oAction = OBJ_ACT_LAVA_DEATH;        break;
            case SURFACE_VERTICAL_WIND: // fall through
            case SURFACE_DEATH_PLANE:   o->oAction = OBJ_ACT_DEATH_PLANE_DEATH; break;
            default: break;
        }
    }
}

/**
 * Controls an object dying in lava by creating smoke, sinking the object, playing
 * audio, and eventually despawning it. Returns TRUE when the obj is dead.
 */
s8 obj_lava_death(void) {
    struct Object *deathSmoke;
    if (o->oTimer >= 31) {
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
        return TRUE;
    } else {
        // Sinking effect
        o->oPosY -= 10.0f;
    }
    if (!(o->oTimer & 0x7)) {
        cur_obj_play_sound_2(SOUND_OBJ_BULLY_EXPLODE_LAVA);
        deathSmoke = spawn_object(o, MODEL_SMOKE, bhvBobombBullyDeathSmoke);
        deathSmoke->oPosX      += (random_float() * 20.0f);
        deathSmoke->oPosY      += (random_float() * 20.0f);
        deathSmoke->oPosZ      += (random_float() * 20.0f);
        deathSmoke->oForwardVel = (random_float() * 10.0f);
    }
    return FALSE;
}

/**
 * Spawns an orange number object relatively, such as those that count up for secrets.
 */
void spawn_orange_number(s8 behParam, s16 relX, s16 relY, s16 relZ) {
    struct Object *orangeNumber;
#ifdef DIALOG_INDICATOR
    if (behParam > ORANGE_NUMBER_F) return;
#else
    if (behParam > ORANGE_NUMBER_9) return;
#endif
    orangeNumber = spawn_object_relative(behParam, relX, relY, relZ, o, MODEL_NUMBER, bhvOrangeNumber);
    orangeNumber->oPosY += 25.0f;
}

/**
 * Unused variables for debug_sequence_tracker.
 */
s8 sDebugSequenceTracker = 0;
s8 sDebugTimer           = 0;

/**
 * Unused presumably debug function that tracks for a sequence of inputs.
 */
UNUSED Bool32 debug_sequence_tracker(s16 debugInputSequence[]) {
    // If end of sequence reached, return true.
    if (debugInputSequence[sDebugSequenceTracker] == 0) {
        sDebugSequenceTracker = 0;
        return TRUE;
    }
    // If the third controller button pressed is next in sequence, reset timer and progress to next value.
    if (debugInputSequence[sDebugSequenceTracker] & gPlayer3Controller->buttonPressed) {
        sDebugSequenceTracker++;
        sDebugTimer = 0;
    // If wrong input or timer reaches 10, reset sequence progress.
    } else if ((sDebugTimer == 10) || (gPlayer3Controller->buttonPressed != 0)) {
        sDebugSequenceTracker = 0;
        sDebugTimer           = 0;
        return FALSE;
    }
    sDebugTimer++;
    return FALSE;
}

#include "behaviors/moving_coin.inc.c"
#include "behaviors/seaweed.inc.c"
#include "behaviors/bobomb.inc.c"
#include "behaviors/cannon_door.inc.c"
#include "behaviors/whirlpool.inc.c"
#include "behaviors/amp.inc.c"
#include "behaviors/butterfly.inc.c"
#include "behaviors/hoot.inc.c"
#include "behaviors/beta_holdable_object.inc.c"
#include "behaviors/bubble.inc.c"
#include "behaviors/water_wave.inc.c"
#include "behaviors/explosion.inc.c"
#include "behaviors/respawner.inc.c"
#include "behaviors/bully.inc.c"
#include "behaviors/water_ring.inc.c"
#include "behaviors/bowser_bomb.inc.c"
#include "behaviors/celebration_star.inc.c"
#include "behaviors/drawbridge.inc.c"
#include "behaviors/bomp.inc.c"
#include "behaviors/sliding_platform.inc.c"
#include "behaviors/moneybag.inc.c"
#include "behaviors/bowling_ball.inc.c"
#include "behaviors/cruiser.inc.c"
#include "behaviors/spindel.inc.c"
#include "behaviors/pyramid_wall.inc.c"
#include "behaviors/pyramid_elevator.inc.c"
#include "behaviors/pyramid_top.inc.c"
#include "behaviors/sound_waterfall.inc.c"
#include "behaviors/sound_volcano.inc.c"
#include "behaviors/castle_flag.inc.c"
#include "behaviors/sound_birds.inc.c"
#include "behaviors/sound_ambient.inc.c"
#include "behaviors/sound_sand.inc.c"
#include "behaviors/castle_cannon_grate.inc.c"
#include "behaviors/snowman.inc.c"
#include "behaviors/boulder.inc.c"
#include "behaviors/cap.inc.c"
#include "behaviors/koopa_shell.inc.c"
#include "behaviors/spawn_star.inc.c"
#include "behaviors/red_coin.inc.c"
#include "behaviors/hidden_star.inc.c"
#include "behaviors/rolling_log.inc.c"
#include "behaviors/mushroom_1up.inc.c"
#include "behaviors/controllable_platform.inc.c"
#include "behaviors/breakable_box_small.inc.c"
#include "behaviors/snow_mound.inc.c"
#include "behaviors/floating_platform.inc.c"
#include "behaviors/arrow_lift.inc.c"
#include "behaviors/orange_number.inc.c"
#include "behaviors/manta_ray.inc.c"
#include "behaviors/falling_pillar.inc.c"
#include "behaviors/floating_box.inc.c"
#include "behaviors/decorative_pendulum.inc.c"
#include "behaviors/treasure_chest.inc.c"
#include "behaviors/mips.inc.c"
#include "behaviors/yoshi.inc.c"
