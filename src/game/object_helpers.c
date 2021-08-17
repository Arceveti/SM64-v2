#include <PR/ultratypes.h>

#include "sm64.h"
#include "area.h"
#include "behavior_actions.h"
#include "behavior_data.h"
#include "camera.h"
#include "cutscene.h"
#include "debug.h"
#include "dialog_ids.h"
#include "engine/behavior_script.h"
#include "engine/geo_layout.h"
#include "engine/math_util.h"
#include "engine/surface_collision.h"
#include "game_init.h"
#include "helper_macros.h"
#include "ingame_menu.h"
#include "interaction.h"
#include "level_table.h"
#include "level_update.h"
#include "mario.h"
#include "mario_actions_cutscene.h"
#include "memory.h"
#include "obj_behaviors.h"
#include "object_helpers.h"
#include "object_list_processor.h"
#include "rendering_graph_node.h"
#include "spawn_object.h"
#include "spawn_sound.h"
#ifdef PLATFORM_DISPLACEMENT_2_OBJECTS
#include "platform_displacement.h"

struct PlatformDisplacementInfo sObjectDisplacementInfo;
#endif

static s8 sBbhStairJiggleOffsets[] = { -8, 8, -4, 4 };
static s8 sLevelsWithRooms[]       = { LEVEL_BBH, LEVEL_CASTLE, LEVEL_HMC, -1 };

static s32 clear_move_flag(u32 *, s32);

#define o gCurrentObject

Gfx *geo_update_projectile_pos_from_parent(s32 callContext, UNUSED struct GraphNode *node, Mat4 mtx) {
    Mat4 mtx2;
    struct Object *projObj;
    if (callContext == GEO_CONTEXT_RENDER) {
        projObj = (struct Object *) gCurGraphNodeObject; // TODO: change global type to Object pointer
        if (projObj->prevObj) {
            create_transformation_from_matrices(mtx2, mtx, *gCurGraphNodeCamera->matrixPtr);
            obj_update_pos_from_parent_transformation(mtx2, projObj->prevObj);
            obj_set_gfx_pos_from_pos(projObj->prevObj);
        }
    }
    return NULL;
}

Gfx *geo_update_layer_transparency(s32 callContext, struct GraphNode *node, UNUSED void *context) {
    Gfx *dlStart, *dlHead;
    struct Object *objectGraphNode;
    struct GraphNodeGenerated *currentGraphNode;
    s32 objectOpacity;
    dlStart = NULL;
    if (callContext == GEO_CONTEXT_RENDER) {
        objectGraphNode  = (struct Object             *) gCurGraphNodeObject; // TODO: change this to object pointer?
        currentGraphNode = (struct GraphNodeGenerated *) node;
        if (gCurGraphNodeHeldObject) objectGraphNode = gCurGraphNodeHeldObject->objNode;
        objectOpacity = objectGraphNode->oOpacity;
        dlStart       = alloc_display_list(sizeof(Gfx) * 3);
        dlHead        = dlStart;
        if (objectOpacity == 0xFF) {
            currentGraphNode->fnNode.node.flags = ((((currentGraphNode->parameter == 20) ? LAYER_TRANSPARENT_DECAL : LAYER_OPAQUE     ) << 8) | (currentGraphNode->fnNode.node.flags & GRAPH_NODE_TYPES_MASK));
            objectGraphNode->oAnimState = 0;
        } else {
            currentGraphNode->fnNode.node.flags = ((((currentGraphNode->parameter == 20) ? LAYER_TRANSPARENT_DECAL : LAYER_TRANSPARENT) << 8) | (currentGraphNode->fnNode.node.flags & GRAPH_NODE_TYPES_MASK));
            objectGraphNode->oAnimState = 1;
#ifdef VERSION_JP
            if (currentGraphNode->parameter == 10) {
                if (gDebugInfo[DEBUG_PAGE_ENEMYINFO][3]) gDPSetAlphaCompare(dlHead++, G_AC_DITHER);
            } else {
                if (objectGraphNode->activeFlags & ACTIVE_FLAG_DITHERED_ALPHA) gDPSetAlphaCompare(dlHead++, G_AC_DITHER);
            }
#else // gDebugInfo accesses were removed in all non-JP versions.
            if ((objectOpacity == 0) && (segmented_to_virtual(bhvBowser) == objectGraphNode->behavior)) objectGraphNode->oAnimState = 2;
            // the debug info check was removed in US. so we need to
            // perform the only necessary check instead of the debuginfo
            // one.
            if ((currentGraphNode->parameter != 10) && (objectGraphNode->activeFlags & ACTIVE_FLAG_DITHERED_ALPHA)) gDPSetAlphaCompare(dlHead++, G_AC_DITHER);
#endif
        }
        gDPSetEnvColor(dlHead++, 255, 255, 255, objectOpacity);
        gSPEndDisplayList(dlHead);
    }
    return dlStart;
}


Gfx *geo_switch_anim_state(s32 callContext, struct GraphNode *node, UNUSED void *context) {
    struct Object *obj;
    struct GraphNodeSwitchCase *switchCase;
    if (callContext == GEO_CONTEXT_RENDER) {
        obj = (struct Object *) gCurGraphNodeObject; // TODO: change global type to Object pointer
        // move to a local var because GraphNodes are passed in all geo functions.
        // cast the pointer.
        switchCase = (struct GraphNodeSwitchCase *) node;
        if (gCurGraphNodeHeldObject != NULL) obj = gCurGraphNodeHeldObject->objNode;
        // if the case is greater than the number of cases, set to 0 to avoid overflowing
        // the switch.
        if (obj->oAnimState >= switchCase->numCases) obj->oAnimState = 0;
        // assign the case number for execution.
        switchCase->selectedCase = obj->oAnimState;
    }
    return NULL;
}

Gfx *geo_switch_area(s32 callContext, struct GraphNode *node, UNUSED void *context) {
    s16 areaCase;
    struct Surface *floor;
    struct GraphNodeSwitchCase *switchCase = (struct GraphNodeSwitchCase *) node;
    if (callContext == GEO_CONTEXT_RENDER) {
        if (gMarioObject == NULL) {
            switchCase->selectedCase = 0;
        } else {
#ifdef SWITCH_AREA_ALWAYS_USES_MARIO_FLOOR
            floor = gMarioState->floor; // Use Mario's floor instead of finding a new one. This skips intangible floors
#else
            // Check if there is an intangible floor in the current cell
            if (floor_type_exists_in_current_cell(gMarioObject->oPosX, gMarioObject->oPosZ, SURFACE_INTANGIBLE, FALSE)) {
                // there is an intangible floor in the current cell, so look for it.
                find_room_floor(gMarioObject->oPosX, gMarioObject->oPosY, gMarioObject->oPosZ, &floor);
            } else {
                // Since no intangible floors are nearby, use Mario's floor instead.
                floor = gMarioState->floor;
            }
#endif
            if (floor) {
                gMarioCurrentRoom =  floor->room;
                areaCase          = (floor->room - 1);
                print_debug_top_down_objectinfo("areainfo %d", floor->room);
                if (areaCase >= 0) switchCase->selectedCase = areaCase;
            }
        }
    } else {
        switchCase->selectedCase = 0;
    }
    return NULL;
}

//! move to math_util?
void obj_update_pos_from_parent_transformation(Mat4 mtx, struct Object *obj) {
    register f32 relX   = obj->oParentRelativePosX;
    register f32 relY   = obj->oParentRelativePosY;
    register f32 relZ   = obj->oParentRelativePosZ;
    obj->oPosX = ((relX * mtx[0][0]) + (relY * mtx[1][0]) + (relZ * mtx[2][0]) + mtx[3][0]);
    obj->oPosY = ((relX * mtx[0][1]) + (relY * mtx[1][1]) + (relZ * mtx[2][1]) + mtx[3][1]);
    obj->oPosZ = ((relX * mtx[0][2]) + (relY * mtx[1][2]) + (relZ * mtx[2][2]) + mtx[3][2]);
}

//! move to math_util?
void obj_apply_scale_to_matrix(struct Object *obj, Mat4 dst, Mat4 src) {
    dst[0][0] = (src[0][0] * obj->header.gfx.scale[0]);
    dst[1][0] = (src[1][0] * obj->header.gfx.scale[1]);
    dst[2][0] = (src[2][0] * obj->header.gfx.scale[2]);
    dst[3][0] =  src[3][0];

    dst[0][1] = (src[0][1] * obj->header.gfx.scale[0]);
    dst[1][1] = (src[1][1] * obj->header.gfx.scale[1]);
    dst[2][1] = (src[2][1] * obj->header.gfx.scale[2]);
    dst[3][1] =  src[3][1];

    dst[0][2] = (src[0][2] * obj->header.gfx.scale[0]);
    dst[1][2] = (src[1][2] * obj->header.gfx.scale[1]);
    dst[2][2] = (src[2][2] * obj->header.gfx.scale[2]);
    dst[3][2] =  src[3][2];

    dst[0][3] = src[0][3];
    dst[1][3] = src[1][3];
    dst[2][3] = src[2][3];
    dst[3][3] = src[3][3];
}

//! move to math_util
void create_transformation_from_matrices(Mat4 dst, Mat4 a1, Mat4 a2) {
    register f32 x     = ((a2[3][0] * a2[0][0]) + (a2[3][1] * a2[0][1]) + (a2[3][2] * a2[0][2]));
    register f32 y     = ((a2[3][0] * a2[1][0]) + (a2[3][1] * a2[1][1]) + (a2[3][2] * a2[1][2]));
    register f32 z     = ((a2[3][0] * a2[2][0]) + (a2[3][1] * a2[2][1]) + (a2[3][2] * a2[2][2]));

    dst[0][0] = ((a1[0][0] * a2[0][0]) + (a1[0][1] * a2[0][1]) + (a1[0][2] * a2[0][2]));
    dst[0][1] = ((a1[0][0] * a2[1][0]) + (a1[0][1] * a2[1][1]) + (a1[0][2] * a2[1][2]));
    dst[0][2] = ((a1[0][0] * a2[2][0]) + (a1[0][1] * a2[2][1]) + (a1[0][2] * a2[2][2]));

    dst[1][0] = ((a1[1][0] * a2[0][0]) + (a1[1][1] * a2[0][1]) + (a1[1][2] * a2[0][2]));
    dst[1][1] = ((a1[1][0] * a2[1][0]) + (a1[1][1] * a2[1][1]) + (a1[1][2] * a2[1][2]));
    dst[1][2] = ((a1[1][0] * a2[2][0]) + (a1[1][1] * a2[2][1]) + (a1[1][2] * a2[2][2]));

    dst[2][0] = ((a1[2][0] * a2[0][0]) + (a1[2][1] * a2[0][1]) + (a1[2][2] * a2[0][2]));
    dst[2][1] = ((a1[2][0] * a2[1][0]) + (a1[2][1] * a2[1][1]) + (a1[2][2] * a2[1][2]));
    dst[2][2] = ((a1[2][0] * a2[2][0]) + (a1[2][1] * a2[2][1]) + (a1[2][2] * a2[2][2]));

    dst[3][0] = ((a1[3][0] * a2[0][0]) + (a1[3][1] * a2[0][1]) + (a1[3][2] * a2[0][2]) - x);
    dst[3][1] = ((a1[3][0] * a2[1][0]) + (a1[3][1] * a2[1][1]) + (a1[3][2] * a2[1][2]) - y);
    dst[3][2] = ((a1[3][0] * a2[2][0]) + (a1[3][1] * a2[2][1]) + (a1[3][2] * a2[2][2]) - z);

    dst[0][3] = 0;
    dst[1][3] = 0;
    dst[2][3] = 0;
    dst[3][3] = 1.0f;
}

void obj_set_held_state(struct Object *obj, const BehaviorScript *heldBehavior) {
    obj->parentObj = o;
    if (obj->oFlags & OBJ_FLAG_HOLDABLE) {
        if (heldBehavior == bhvCarrySomethingHeld   ) obj->oHeldState = HELD_HELD;
        if (heldBehavior == bhvCarrySomethingThrown ) obj->oHeldState = HELD_THROWN;
        if (heldBehavior == bhvCarrySomethingDropped) obj->oHeldState = HELD_DROPPED;
    } else {
        obj->curBhvCommand = segmented_to_virtual(heldBehavior);
        obj->bhvStackIndex = 0;
    }
}

f32 lateral_dist_between_objects(struct Object *obj1, struct Object *obj2) {
    register f32 dx = (obj1->oPosX - obj2->oPosX);
    register f32 dz = (obj1->oPosZ - obj2->oPosZ);
    return sqrtf((dx * dx) + (dz * dz));
}

f32 dist_between_objects(struct Object *obj1, struct Object *obj2) {
    register f32 dx = (obj1->oPosX - obj2->oPosX);
    register f32 dy = (obj1->oPosY - obj2->oPosY);
    register f32 dz = (obj1->oPosZ - obj2->oPosZ);
    return sqrtf((dx * dx) + (dy * dy) + (dz * dz));
}

void cur_obj_forward_vel_approach_upward(f32 target, f32 increment) {
    if (o->oForwardVel >= target) {
        o->oForwardVel = target;
    } else {
        o->oForwardVel += increment;
    }
}

s32 cur_obj_rotate_yaw_toward(s16 target, s16 increment) {
    s16 startYaw = (s16) o->oMoveAngleYaw;
    o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, target, increment);
    return ((o->oAngleVelYaw = (s16)((s16) o->oMoveAngleYaw - startYaw)) == 0);
}

s16 obj_angle_to_object(struct Object *obj1, struct Object *obj2) {
    register f32 z1 = obj1->oPosZ; register f32 z2 = obj2->oPosZ; // ordering of instructions...
    register f32 x1 = obj1->oPosX; register f32 x2 = obj2->oPosX;
    return atan2s((z2 - z1), (x2 - x1));
}

s16 obj_turn_toward_object(struct Object *obj, struct Object *target, s16 angleIndex, s16 turnAmount) {
    register f32 a, b, c, d;
    s16 targetAngle = 0x0;
    s16 startAngle = o->rawData.asU32[angleIndex];
    switch (angleIndex) {
        case O_MOVE_ANGLE_PITCH_INDEX:
        case O_FACE_ANGLE_PITCH_INDEX:
            a = (target->oPosX - obj->oPosX);
            c = (target->oPosZ - obj->oPosZ);
            a = sqrtf((a * a) + (c * c));
            b =    -obj->oPosY;
            d = -target->oPosY;
            targetAngle = atan2s(a, d - b);
            break;
        case O_MOVE_ANGLE_YAW_INDEX:
        case O_FACE_ANGLE_YAW_INDEX:
            a =     obj->oPosZ;
            c =  target->oPosZ;
            b =     obj->oPosX;
            d =  target->oPosX;
            targetAngle = atan2s((c - a), (d - b));
            break;
    }
    o->rawData.asU32[angleIndex] = approach_s16_symmetric(startAngle, targetAngle, turnAmount);
    return targetAngle;
}

void obj_set_parent_relative_pos(struct Object *obj, s16 relX, s16 relY, s16 relZ) {
    obj->oParentRelativePosX = relX;
    obj->oParentRelativePosY = relY;
    obj->oParentRelativePosZ = relZ;
}

void obj_set_pos(struct Object *obj, s16 x, s16 y, s16 z) {
    obj->oPosX = x;
    obj->oPosY = y;
    obj->oPosZ = z;
}

void obj_set_angle(struct Object *obj, s16 pitch, s16 yaw, s16 roll) {
    obj->oFaceAnglePitch = pitch;
    obj->oFaceAngleYaw   = yaw;
    obj->oFaceAngleRoll  = roll;

    obj->oMoveAnglePitch = pitch;
    obj->oMoveAngleYaw   = yaw;
    obj->oMoveAngleRoll  = roll;
}

/*
 * Spawns an object at an absolute location with a specified angle.
 */
struct Object *spawn_object_abs_with_rot(struct Object *parent, s16 uselessArg, u32 model, const BehaviorScript *behavior,
                                         s16 x, s16 y, s16 z, s16 rx, s16 ry, s16 rz) {
    // 'uselessArg' is unused in the function spawn_object_at_origin()
    struct Object *newObj = spawn_object_at_origin(parent, uselessArg, model, behavior);
    obj_set_pos(   newObj,  x,  y,  z);
    obj_set_angle( newObj, rx, ry, rz);
    return newObj;
}

/*
 * Spawns an object relative to the parent with a specified angle... is what it is supposed to do.
 * The rz argument is never used, and the z offset is used for z-rotation instead. This is most likely
 * a copy-paste typo by one of the programmers.
 */
struct Object *spawn_object_rel_with_rot(struct Object *parent, u32 model, const BehaviorScript *behavior,
                                         s16 xOff, s16 yOff, s16 zOff, s16 rx, s16 ry, UNUSED s16 rz) {
    struct Object *newObj = spawn_object_at_origin(parent, 0, model, behavior);
    newObj->oFlags |= OBJ_FLAG_TRANSFORM_RELATIVE_TO_PARENT;
    obj_set_parent_relative_pos(newObj, xOff, yOff, zOff);
    obj_set_angle(newObj, rx, ry, rz);
    return newObj;
}

struct Object *spawn_obj_with_transform_flags(struct Object *parent, s32 model, const BehaviorScript *behavior) {
    struct Object *newObj = spawn_object(parent, model, behavior);
    newObj->oFlags |= OBJ_FLAG_UPDATE_TRANSFORM_FOR_THROW_MATRIX | OBJ_FLAG_SET_THROW_MATRIX_FROM_TRANSFORM;
    return newObj;
}

struct Object *spawn_water_droplet(struct Object *parent, struct WaterDropletParams *params) {
    f32 randomScale;
    struct Object *newObj = spawn_object(parent, params->model, params->behavior);
    if (params->flags & WATER_DROPLET_FLAG_RAND_ANGLE               ) newObj->oMoveAngleYaw = random_u16();
    if (params->flags & WATER_DROPLET_FLAG_RAND_ANGLE_INCR_BACKWARD) newObj->oMoveAngleYaw = ((s16)(newObj->oMoveAngleYaw + 0x8000) + (s16) random_f32_around_zero(params->moveAngleRange));
    if (params->flags & WATER_DROPLET_FLAG_RAND_ANGLE_INCR_FORWARD          ) newObj->oMoveAngleYaw = ((s16) newObj->oMoveAngleYaw           + (s16) random_f32_around_zero(params->moveAngleRange));
    if (params->flags & WATER_DROPLET_FLAG_SET_Y_TO_WATER_LEVEL     ) newObj->oPosY = find_water_level(newObj->oPosX, newObj->oPosZ);
    if (params->flags & WATER_DROPLET_FLAG_RAND_OFFSET_XZ           ) obj_translate_xz_random( newObj, params->moveRange);
    if (params->flags & WATER_DROPLET_FLAG_RAND_OFFSET_XYZ          ) obj_translate_xyz_random(newObj, params->moveRange);
    newObj->oForwardVel = ((random_float() * params->randForwardVelScale) + params->randForwardVelOffset);
    newObj->oVelY       = ((random_float() * params->randYVelScale      ) + params->randYVelOffset      );
    randomScale         = ((random_float() * params->randSizeScale      ) + params->randSizeOffset      );
    obj_scale(newObj, randomScale);
    return newObj;
}

struct Object *spawn_object_at_origin(struct Object *parent, UNUSED s32 unusedArg, u32 model, const BehaviorScript *behavior) {
    struct Object *obj;
    const BehaviorScript *behaviorAddr;
    behaviorAddr   = segmented_to_virtual(behavior);
    obj            = create_object(behaviorAddr);
    obj->parentObj = parent;
    obj->header.gfx.areaIndex       = parent->header.gfx.areaIndex;
    obj->header.gfx.activeAreaIndex = parent->header.gfx.areaIndex;
    geo_obj_init((struct GraphNodeObject *) &obj->header.gfx, gLoadedGraphNodes[model], gVec3fZero, gVec3sZero);
    return obj;
}

struct Object *spawn_object(struct Object *parent, s32 model, const BehaviorScript *behavior) {
    struct Object *obj = spawn_object_at_origin(parent, 0, model, behavior);
    obj_copy_pos_and_angle(obj, parent);
    return obj;
}

struct Object *try_to_spawn_object(s16 offsetY, f32 scale, struct Object *parent, s32 model, const BehaviorScript *behavior) {
    struct Object *obj;
    if (gFreeObjectList.next != NULL) {
        obj = spawn_object(parent, model, behavior);
        obj->oPosY += offsetY;
        obj_scale(obj, scale);
        return obj;
    } else {
        return NULL;
    }
}

struct Object *spawn_object_with_scale(struct Object *parent, s32 model, const BehaviorScript *behavior, f32 scale) {
    struct Object *obj = spawn_object_at_origin(parent, 0, model, behavior);
    obj_copy_pos_and_angle(obj, parent);
    obj_scale(obj, scale);
    return obj;
}

static void obj_build_relative_transform(struct Object *obj) {
    obj_build_transform_from_pos_and_angle(obj, O_PARENT_RELATIVE_POS_INDEX,          O_FACE_ANGLE_INDEX);
    obj_translate_local(                   obj,                 O_POS_INDEX, O_PARENT_RELATIVE_POS_INDEX);
}

struct Object *spawn_object_relative(s16 behaviorParam, s16 relativePosX, s16 relativePosY, s16 relativePosZ,
                                     struct Object *parent, s32 model, const BehaviorScript *behavior) {
    struct Object *obj = spawn_object_at_origin(parent, 0, model, behavior);

    obj_copy_pos_and_angle(      obj, parent);
    obj_set_parent_relative_pos( obj, relativePosX, relativePosY, relativePosZ);
    obj_build_relative_transform(obj);
    obj->oBehParams2ndByte =  behaviorParam;
    obj->oBehParams        = (behaviorParam & 0xFF) << 16;
    return obj;
}

struct Object *spawn_object_relative_with_scale(s16 behaviorParam, s16 relativePosX, s16 relativePosY, s16 relativePosZ, f32 scale,
                                                struct Object *parent, s32 model, const BehaviorScript *behavior) {
    struct Object *obj = spawn_object_relative(behaviorParam, relativePosX, relativePosY, relativePosZ, parent, model, behavior);
    obj_scale(obj, scale);
    return obj;
}

// Unused
void cur_obj_move_using_vel(void) {
    o->oPosX += o->oVelX;
    o->oPosY += o->oVelY;
    o->oPosZ += o->oVelZ;
}

// Used for beta trampoline
void obj_copy_graph_y_offset(struct Object *dst, struct Object *src) {
    dst->oGraphYOffset = src->oGraphYOffset;
}

void obj_copy_pos_and_angle(struct Object *dst, struct Object *src) {
    obj_copy_pos(  dst, src);
    obj_copy_angle(dst, src);
}

void obj_copy_pos(struct Object *dst, struct Object *src) {
    dst->oPosX = src->oPosX;
    dst->oPosY = src->oPosY;
    dst->oPosZ = src->oPosZ;
}

void obj_copy_angle(struct Object *dst, struct Object *src) {
    dst->oMoveAnglePitch = src->oMoveAnglePitch;
    dst->oMoveAngleYaw   = src->oMoveAngleYaw;
    dst->oMoveAngleRoll  = src->oMoveAngleRoll;

    dst->oFaceAnglePitch = src->oFaceAnglePitch;
    dst->oFaceAngleYaw   = src->oFaceAngleYaw;
    dst->oFaceAngleRoll  = src->oFaceAngleRoll;
}

void obj_set_gfx_pos_from_pos(struct Object *obj) {
    obj->header.gfx.pos[0] = obj->oPosX;
    obj->header.gfx.pos[1] = obj->oPosY;
    obj->header.gfx.pos[2] = obj->oPosZ;
}

void obj_init_animation(struct Object *obj, s32 animIndex) {
    struct Animation **anims = obj->oAnimations;
    geo_obj_init_animation(&obj->header.gfx, &anims[animIndex]);
}

void obj_apply_scale_to_transform(struct Object *obj) {
    f32 scaleX = obj->header.gfx.scale[0];
    f32 scaleY = obj->header.gfx.scale[1];
    f32 scaleZ = obj->header.gfx.scale[2];

    obj->transform[0][0] *= scaleX;
    obj->transform[0][1] *= scaleX;
    obj->transform[0][2] *= scaleX;

    obj->transform[1][0] *= scaleY;
    obj->transform[1][1] *= scaleY;
    obj->transform[1][2] *= scaleY;

    obj->transform[2][0] *= scaleZ;
    obj->transform[2][1] *= scaleZ;
    obj->transform[2][2] *= scaleZ;
}

void obj_copy_scale(struct Object *dst, struct Object *src) {
    dst->header.gfx.scale[0] = src->header.gfx.scale[0];
    dst->header.gfx.scale[1] = src->header.gfx.scale[1];
    dst->header.gfx.scale[2] = src->header.gfx.scale[2];
}

void obj_scale_xyz(struct Object *obj, f32 xScale, f32 yScale, f32 zScale) {
    obj->header.gfx.scale[0] = xScale;
    obj->header.gfx.scale[1] = yScale;
    obj->header.gfx.scale[2] = zScale;
}

void obj_scale(struct Object *obj, f32 scale) {
    obj->header.gfx.scale[0] = scale;
    obj->header.gfx.scale[1] = scale;
    obj->header.gfx.scale[2] = scale;
}

void cur_obj_scale(f32 scale) {
    o->header.gfx.scale[0] = scale;
    o->header.gfx.scale[1] = scale;
    o->header.gfx.scale[2] = scale;
}

void cur_obj_init_animation(s32 animIndex) {
    struct Animation **anims = o->oAnimations;
    geo_obj_init_animation(&o->header.gfx, &anims[animIndex]);
}

void cur_obj_init_animation_with_sound(s32 animIndex) {
    struct Animation **anims = o->oAnimations;
    geo_obj_init_animation(&o->header.gfx, &anims[animIndex]);
    o->oSoundStateID = animIndex;
}

void cur_obj_init_animation_with_accel_and_sound(s32 animIndex, f32 accel) {
    struct Animation **anims = o->oAnimations;
    s32 animAccel = (s32)(accel * 65536.0f);
    geo_obj_init_animation_accel(&o->header.gfx, &anims[animIndex], animAccel);
    o->oSoundStateID = animIndex;
}

void obj_init_animation_with_sound(struct Object *obj, const struct Animation * const* animations, s32 animIndex) {
    struct Animation **anims = (struct Animation **)animations;
    obj->oAnimations = (struct Animation **)animations;
    geo_obj_init_animation(&obj->header.gfx, &anims[animIndex]);
    obj->oSoundStateID = animIndex;
}

void cur_obj_enable_rendering_and_become_tangible(struct Object *obj) {
    obj->header.gfx.node.flags |= GRAPH_RENDER_ACTIVE;
    obj->oIntangibleTimer       = 0;
}

void cur_obj_enable_rendering(void) {
    o->header.gfx.node.flags |= GRAPH_RENDER_ACTIVE;
}

void cur_obj_disable_rendering_and_become_intangible(struct Object *obj) {
    obj->header.gfx.node.flags &= ~GRAPH_RENDER_ACTIVE;
    obj->oIntangibleTimer       = -1;
}

void cur_obj_disable_rendering(void) {
    o->header.gfx.node.flags &= ~GRAPH_RENDER_ACTIVE;
}

void cur_obj_unhide(void) {
    o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
}

void cur_obj_hide(void) {
    o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
}

void cur_obj_set_pos_relative(struct Object *other, f32 dleft, f32 dy, f32 dforward) {
    f32 facingZ      = coss(other->oMoveAngleYaw);
    f32 facingX      = sins(other->oMoveAngleYaw);
    f32 dz           = dforward * facingZ - dleft * facingX;
    f32 dx           = dforward * facingX + dleft * facingZ;
    o->oMoveAngleYaw = other->oMoveAngleYaw;
    o->oPosX         = other->oPosX + dx;
    o->oPosY         = other->oPosY + dy;
    o->oPosZ         = other->oPosZ + dz;
}

void cur_obj_set_pos_relative_to_parent(f32 dleft, f32 dy, f32 dforward) {
    cur_obj_set_pos_relative(o->parentObj, dleft, dy, dforward);
}

void cur_obj_enable_rendering_2(void) {
    cur_obj_enable_rendering();
}

void cur_obj_unused_init_on_floor(void) {
    cur_obj_enable_rendering();
    o->oPosY = find_floor_height(o->oPosX, o->oPosY, o->oPosZ);
    if (o->oPosY < FLOOR_LOWER_LIMIT_MISC) {
        cur_obj_set_pos_relative_to_parent(0.0f, 0.0f, -70.0f);
        o->oPosY = find_floor_height(o->oPosX, o->oPosY, o->oPosZ);
    }
}

void obj_set_face_angle_to_move_angle(struct Object *obj) {
    obj->oFaceAnglePitch = obj->oMoveAnglePitch;
    obj->oFaceAngleYaw   = obj->oMoveAngleYaw;
    obj->oFaceAngleRoll  = obj->oMoveAngleRoll;
}

u32 get_object_list_from_behavior(const BehaviorScript *behavior) {
    // If the first behavior command is "begin", then get the object list header from there
    if ((behavior[0] >> 24) == 0x0) return (behavior[0] >> 16) & 0xFFFF;
    return OBJ_LIST_DEFAULT;
}

struct Object *cur_obj_nearest_object_with_behavior(const BehaviorScript *behavior) {
    f32 dist;
    return cur_obj_find_nearest_object_with_behavior(behavior, &dist);
}

f32 cur_obj_dist_to_nearest_object_with_behavior(const BehaviorScript *behavior) {
    f32 dist;
    if (cur_obj_find_nearest_object_with_behavior(behavior, &dist) == NULL) dist = 15000.0f;
    return dist;
}

struct Object *cur_obj_find_nearest_object_with_behavior(const BehaviorScript *behavior, f32 *dist) {
    uintptr_t         *behaviorAddr = segmented_to_virtual(behavior);
    struct Object     *closestObj   = NULL;
    struct Object     *obj;
    struct ObjectNode *listHead;
    f32 minDist = 0x20000;
    listHead    = &gObjectLists[get_object_list_from_behavior(behaviorAddr)];
    obj = (struct Object *) listHead->next;
    while (obj != (struct Object *) listHead) {
        if (obj->behavior == behaviorAddr && obj->activeFlags != ACTIVE_FLAG_DEACTIVATED && obj != o) {
            f32 objDist = dist_between_objects(o, obj);
            if (objDist < minDist) {
                closestObj = obj;
                minDist = objDist;
            }
        }
        obj = (struct Object *) obj->header.next;
    }
    *dist = minDist;
    return closestObj;
}

struct Object *find_closest_obj_with_behavior_from_point(const BehaviorScript *behavior, Vec3f pos, f32 *dist) {
    uintptr_t         *behaviorAddr = segmented_to_virtual(behavior);
    struct Object     *closestObj   = NULL;
    struct Object     *obj;
    struct ObjectNode *listHead;
    f32 minDist = 0x20000;
    listHead    = &gObjectLists[get_object_list_from_behavior(behaviorAddr)];
    obj         = (struct Object *) listHead->next;
    while (obj != (struct Object *) listHead) {
        if (obj->behavior == behaviorAddr && obj->activeFlags != ACTIVE_FLAG_DEACTIVATED) {
            f32 dx = pos[0] - obj->oPosX;
            f32 dy = pos[1] - obj->oPosY;
            f32 dz = pos[2] - obj->oPosZ;
            f32 objDist = sqrtf(dx * dx + dy * dy + dz * dz);
            if (objDist < minDist) {
                closestObj = obj;
                minDist    = objDist;
            }
        }
        obj = (struct Object *) obj->header.next;
    }
    *dist = minDist;
    return closestObj;
}

// Finds the object closest to the line from [pos] toward [lookingYaw] within [yawRange]
struct Object *find_closest_obj_with_behavior_from_yaw(const BehaviorScript *behavior, Vec3f pos, s16 lookingYaw, s16 yawRange, s16 *yaw) {
    uintptr_t         *behaviorAddr = segmented_to_virtual(behavior);
    struct Object     *closestObj   = NULL;
    struct Object     *obj;
    struct ObjectNode *listHead;
    s16 minYaw  = yawRange;
    listHead    = &gObjectLists[get_object_list_from_behavior(behaviorAddr)];
    obj         = (struct Object *) listHead->next;
    while (obj != (struct Object *) listHead) {
        if (obj->behavior == behaviorAddr && obj->activeFlags != ACTIVE_FLAG_DEACTIVATED) {
            f32 dx = obj->oPosX - pos[0];
            f32 dz = obj->oPosZ - pos[2];
            s16 objYaw = atan2s(dz, dx);
            s16 objDYaw = abs_angle_diff(lookingYaw, objYaw);
            if (objDYaw < yawRange && objDYaw < abs_angle_diff(lookingYaw, minYaw)) {
                closestObj = obj;
                minYaw     = objYaw;
            }
        }
        obj = (struct Object *) obj->header.next;
    }
    *yaw = minYaw;
    return closestObj;
}

struct Object *find_unimportant_object(void) {
    struct ObjectNode *listHead = &gObjectLists[OBJ_LIST_UNIMPORTANT];
    struct ObjectNode *obj = listHead->next;
    if (listHead == obj) obj = NULL;
    return (struct Object *) obj;
}

s32 count_unimportant_objects(void) {
    struct ObjectNode *listHead = &gObjectLists[OBJ_LIST_UNIMPORTANT];
    struct ObjectNode *obj      = listHead->next;
    s32 count                   = 0;
    while (listHead != obj) {
        count++;
        obj = obj->next;
    }
    return count;
}

s32 count_objects_with_behavior(const BehaviorScript *behavior) {
    uintptr_t *behaviorAddr     = segmented_to_virtual(behavior);
    struct ObjectNode *listHead = &gObjectLists[get_object_list_from_behavior(behaviorAddr)];
    struct ObjectNode *obj      = listHead->next;
    s32 count                   = 0;
    while (listHead != obj) {
        if (((struct Object *) obj)->behavior == behaviorAddr) count++;
        obj = obj->next;
    }
    return count;
}

struct Object *cur_obj_find_nearby_held_actor(const BehaviorScript *behavior, f32 maxDist) {
    const BehaviorScript *behaviorAddr = segmented_to_virtual(behavior);
    struct ObjectNode    *listHead;
    struct Object        *obj;
    struct Object        *foundObj;
    listHead = &gObjectLists[OBJ_LIST_GENACTOR];
    obj      = (struct Object *) listHead->next;
    foundObj = NULL;
    while ((struct Object *) listHead != obj) {
        // This includes the dropped and thrown states. By combining instant
        // release, this allows us to activate mama penguin remotely
        if ((obj->behavior == behaviorAddr) && (obj->activeFlags != ACTIVE_FLAG_DEACTIVATED) && (obj->oHeldState != HELD_FREE) && (dist_between_objects(o, obj) < maxDist)) {
            foundObj = obj;
            break;
        }
        obj = (struct Object *) obj->header.next;
    }
    return foundObj;
}

static void cur_obj_reset_timer_and_subaction(void) {
    o->oTimer     = 0;
    o->oSubAction = 0;
}

void cur_obj_change_action(s32 action) {
    o->oAction     = action;
    o->oPrevAction = action;
    cur_obj_reset_timer_and_subaction();
}

void cur_obj_set_vel_from_mario_vel(f32 min, f32 mul) {
    f32 marioFwdVel = gMarioStates[0].forwardVel;
    f32 minVel      = min * mul;
    o->oForwardVel  = (marioFwdVel < minVel) ? minVel : (marioFwdVel * mul);
}

void cur_obj_reverse_animation(void) {
    if (o->header.gfx.animInfo.animFrame >= 0) o->header.gfx.animInfo.animFrame--;
}

void cur_obj_extend_animation_if_at_end(void) {
    s32 frame = o->header.gfx.animInfo.animFrame;
    s32 end   = o->header.gfx.animInfo.curAnim->loopEnd - 2;
    if (frame == end) o->header.gfx.animInfo.animFrame--;
}

s32 cur_obj_check_if_near_animation_end(void) {
    u32 animFlags   = (s32) o->header.gfx.animInfo.curAnim->flags;
    s32 animFrame   =       o->header.gfx.animInfo.animFrame;
    s32 nearLoopEnd =       o->header.gfx.animInfo.curAnim->loopEnd - 2;
    return ((animFlags & ANIM_FLAG_NOLOOP && nearLoopEnd + 1 == animFrame) || (animFrame == nearLoopEnd));
}

s32 cur_obj_check_if_at_animation_end(void) {
    return (o->header.gfx.animInfo.animFrame == o->header.gfx.animInfo.curAnim->loopEnd - 1);
}

s32 cur_obj_check_anim_frame(s32 frame) {
    return (frame == o->header.gfx.animInfo.animFrame);
}

s32 cur_obj_check_anim_frame_in_range(s32 startFrame, s32 rangeLength) {
    s32 animFrame = o->header.gfx.animInfo.animFrame;
    return (animFrame >= startFrame && animFrame < startFrame + rangeLength);
}

s32 cur_obj_check_frame_prior_current_frame(s16 *frame) {
    s16 animFrame = o->header.gfx.animInfo.animFrame;
    while (*frame != -1) {
        if (*frame == animFrame) return TRUE;
        frame++;
    }
    return FALSE;
}

s32 mario_is_in_air_action(void) {
    return (gMarioStates[0].action & ACT_FLAG_AIR);
}

s32 mario_is_dive_sliding(void) {
    return (gMarioStates[0].action == ACT_DIVE_SLIDE);
}

void cur_obj_set_y_vel_and_animation(f32 yVel, s32 animIndex) {
    o->oVelY = yVel;
    cur_obj_init_animation_with_sound(animIndex);
}

void cur_obj_unrender_set_action_and_anim(s32 animIndex, s32 action) {
    cur_obj_become_intangible();
    cur_obj_disable_rendering();
    // only set animation if non-negative value
    if (animIndex >= 0) cur_obj_init_animation_with_sound(animIndex);
    o->oAction = action;
}

static void cur_obj_move_after_thrown_or_dropped(f32 forwardVel, f32 velY) {
    o->oMoveFlags   = OBJ_MOVE_NONE;
    o->oFloorHeight = find_floor_height(o->oPosX, o->oPosY + 160.0f, o->oPosZ);
    if (o->oFloorHeight > o->oPosY) {
        o->oPosY = o->oFloorHeight;
    } else if (o->oFloorHeight < FLOOR_LOWER_LIMIT_MISC) {
        //! OoB failsafe
        obj_copy_pos(o, gMarioObject);
        o->oFloorHeight = find_floor_height(o->oPosX, o->oPosY, o->oPosZ);
    }
    o->oForwardVel = forwardVel;
    o->oVelY       = velY;
    if (o->oForwardVel != 0.0f) cur_obj_move_y(/*gravity*/ -4.0f, /*bounciness*/ -0.1f, /*buoyancy*/ 2.0f);
}

void cur_obj_get_thrown_or_placed(f32 forwardVel, f32 velY, s32 thrownAction) {
    // Interestingly, when bowser is thrown, he is offset slightly to Mario's right
    if (o->behavior == segmented_to_virtual(bhvBowser)) cur_obj_set_pos_relative_to_parent(-41.684f, 85.859f, 321.577f);
    cur_obj_become_tangible();
    cur_obj_enable_rendering();
    o->oHeldState = HELD_FREE;
    if ((o->oInteractionSubtype & INT_SUBTYPE_HOLDABLE_NPC) || forwardVel == 0.0f) {
        cur_obj_move_after_thrown_or_dropped(0.0f, 0.0f);
    } else {
        o->oAction = thrownAction;
        cur_obj_move_after_thrown_or_dropped(forwardVel, velY);
    }
}

void cur_obj_get_dropped(void) {
    cur_obj_become_tangible();
    cur_obj_enable_rendering();
    o->oHeldState = HELD_FREE;
    cur_obj_move_after_thrown_or_dropped(0.0f, 0.0f);
}

void cur_obj_set_model(ModelID modelID) {
    o->header.gfx.sharedChild = gLoadedGraphNodes[modelID];
}

void obj_set_model(struct Object *obj, ModelID modelID) {
    obj->header.gfx.sharedChild = gLoadedGraphNodes[modelID];
}

s32 cur_obj_has_model(ModelID modelID) {
    return (o->header.gfx.sharedChild == gLoadedGraphNodes[modelID]);
}

s32 obj_has_model(struct Object *obj, ModelID modelID) {
    return (obj->header.gfx.sharedChild == gLoadedGraphNodes[modelID]);
}

void mario_set_flag(s32 flag) {
    gMarioStates[0].flags |= flag;
}

s32 cur_obj_clear_interact_status_flag(s32 flag) {
    if (o->oInteractStatus & flag) {
        o->oInteractStatus &= (flag ^ ~(0));
        return TRUE;
    }
    return FALSE;
}

/**
 * Mark an object to be unloaded at the end of the frame.
 */
void obj_mark_for_deletion(struct Object *obj) {
    //! This clears all activeFlags. Since some of these flags disable behavior,
    //  setting it to 0 could potentially enable unexpected behavior. After an
    //  object is marked for deletion, it still updates on that frame (I think),
    //  so this is worth looking into.
    obj->activeFlags = ACTIVE_FLAG_DEACTIVATED;
}

void cur_obj_disable(void) {
    cur_obj_disable_rendering();
    cur_obj_hide();
    cur_obj_become_intangible();
}

void cur_obj_become_intangible(void) {
    // When the timer is negative, the object is intangible and the timer
    // doesn't count down
    o->oIntangibleTimer = -1;
}

void obj_become_intangible(struct Object *obj) {
    // When the timer is negative, the object is intangible and the timer
    // doesn't count down
    obj->oIntangibleTimer = -1;
}

void cur_obj_become_tangible(void) {
    o->oIntangibleTimer = 0;
}

void obj_become_tangible(struct Object *obj) {
    obj->oIntangibleTimer = 0;
}

void cur_obj_update_floor_height(void) {
    struct Surface *floor;
#ifdef PLATFORM_DISPLACEMENT_2_OBJECTS
    struct Object *platform;
    s16 nextYaw   = o->oFaceAngleYaw;
    if ((platform = o->platform) != NULL) {
        apply_platform_displacement(&sObjectDisplacementInfo, &o->oPosVec, &nextYaw, platform);
        o->oFaceAngleYaw = nextYaw;
    }
    o->oFloorHeight = find_floor(o->oPosX, o->oPosY, o->oPosZ, &floor);
    o->platform     = ((floor != NULL) && (floor->object != 0)) ? floor->object : NULL;
#else
    o->oFloorHeight = find_floor(o->oPosX, o->oPosY, o->oPosZ, &floor);
#endif
}

struct Surface *cur_obj_update_floor_height_and_get_floor(void) {
    struct Surface *floor;
#ifdef PLATFORM_DISPLACEMENT_2_OBJECTS
    struct Object *platform;
    s16 nextYaw   = o->oFaceAngleYaw;
    if ((platform = o->platform) != NULL) {
        apply_platform_displacement(&sObjectDisplacementInfo, &o->oPosVec, &nextYaw, platform);
        o->oFaceAngleYaw = nextYaw;
    }
    o->oFloorHeight = find_floor(o->oPosX, o->oPosY, o->oPosZ, &floor);
    o->platform     = ((floor != NULL) && (floor->object != 0)) ? floor->object : NULL;
#else
    o->oFloorHeight = find_floor(o->oPosX, o->oPosY, o->oPosZ, &floor);
#endif
    return floor;
}

static void apply_drag_to_value(f32 *value, f32 dragStrength) {
    if (*value != 0) {
        //! Can overshoot if |*value| > 1/(dragStrength * 0.0001)
        f32 decel = (*value) * (*value) * (dragStrength * 0.0001f); // was 0.0001L
        if (*value > 0) {
            *value -= decel;
            if (*value <  0.001f) *value = 0; // was 0.001L
        } else {
            *value += decel;
            if (*value > -0.001f) *value = 0; // was -0.001L
        }
    }
}

void cur_obj_apply_drag_xz(f32 dragStrength) {
    apply_drag_to_value(&o->oVelX, dragStrength);
    apply_drag_to_value(&o->oVelZ, dragStrength);
}

static s32 cur_obj_move_xz(f32 steepSlopeNormalY, s32 careAboutEdgesAndSteepSlopes) {
    struct Surface *intendedFloor;
    f32 intendedX           = o->oPosX + o->oVelX;
    f32 intendedZ           = o->oPosZ + o->oVelZ;
    gFindFloorIncludeSurfaceIntangible = TRUE;
    f32 intendedFloorHeight = find_floor(intendedX, o->oPosY, intendedZ, &intendedFloor); // find_room_floor?
    f32 deltaFloorHeight    = intendedFloorHeight - o->oFloorHeight;
    o->oMoveFlags           &= ~OBJ_MOVE_HIT_EDGE;
    if (o->oRoom            != -1
     && intendedFloor       != NULL
     && intendedFloor->room != 0
     && o->oRoom            != intendedFloor->room
     && intendedFloor->room != 18) return FALSE; // Don't leave native room
    if (intendedFloorHeight < FLOOR_LOWER_LIMIT_MISC) {
        // Don't move into OoB
        o->oMoveFlags |= OBJ_MOVE_HIT_EDGE;
        return FALSE;
    } else if (deltaFloorHeight < 5.0f) {
        if (!careAboutEdgesAndSteepSlopes) {
            // If we don't care about edges or steep slopes, okay to move
            o->oPosX = intendedX;
            o->oPosZ = intendedZ;
            return TRUE;
        } else if (deltaFloorHeight < -50.0f && (o->oMoveFlags & OBJ_MOVE_ON_GROUND)) {
            // Don't walk off an edge
            o->oMoveFlags |= OBJ_MOVE_HIT_EDGE;
            return FALSE;
        } else if (intendedFloor->normal.y > steepSlopeNormalY) {
            // Allow movement onto a slope, provided it's not too steep
            o->oPosX = intendedX;
            o->oPosZ = intendedZ;
            return TRUE;
        } else {
            // We are likely trying to move onto a steep downward slope
            o->oMoveFlags |= OBJ_MOVE_HIT_EDGE;
            return FALSE;
        }
    } else if (intendedFloor->normal.y > steepSlopeNormalY || o->oPosY > intendedFloorHeight) {
        // Allow movement upward, provided either:
        // - The target floor is flat enough (e.g. walking up stairs)
        // - We are above the target floor (most likely in the air)
        o->oPosX = intendedX;
        o->oPosZ = intendedZ;
        return TRUE;
    }
    // We are likely trying to move onto a steep upward slope
    return FALSE;
}

static void cur_obj_move_update_underwater_flags(void) {
    f32 decelY = (f32)(sqrtf(o->oVelY * o->oVelY) * (o->oDragStrength * 7.0f)) / 100.0f; // was 100.0l
    if (o->oVelY > 0.0f) {
        o->oVelY -= decelY;
    } else {
        o->oVelY += decelY;
    }
    if (o->oPosY < o->oFloorHeight) {
        o->oPosY = o->oFloorHeight;
        o->oMoveFlags |= OBJ_MOVE_UNDERWATER_ON_GROUND;
    } else {
        o->oMoveFlags |= OBJ_MOVE_UNDERWATER_OFF_GROUND;
    }
}

static void cur_obj_move_update_ground_air_flags(UNUSED f32 gravity, f32 bounciness) {
    o->oMoveFlags &= ~OBJ_MOVE_BOUNCE;
    if (o->oPosY < o->oFloorHeight) {
        // On the first frame that we touch the ground, set OBJ_MOVE_LANDED.
        // On subsequent frames, set OBJ_MOVE_ON_GROUND
        if (!(o->oMoveFlags & OBJ_MOVE_ON_GROUND)) {
            if (clear_move_flag(&o->oMoveFlags, OBJ_MOVE_LANDED)) {
                o->oMoveFlags |= OBJ_MOVE_ON_GROUND;
            } else {
                o->oMoveFlags |= OBJ_MOVE_LANDED;
            }
        }
        o->oPosY = o->oFloorHeight;
        if (o->oVelY < 0.0f) o->oVelY *= bounciness;
        //! This overestimates since velY could be > 5 here
        //! without bounce (e.g. jump into misa).
        if (o->oVelY > 5.0f) o->oMoveFlags |= OBJ_MOVE_BOUNCE;
    } else {
        o->oMoveFlags &= ~OBJ_MOVE_LANDED;
        if (clear_move_flag(&o->oMoveFlags, OBJ_MOVE_ON_GROUND)) o->oMoveFlags |= OBJ_MOVE_LEFT_GROUND;
    }
    o->oMoveFlags &= ~OBJ_MOVE_MASK_IN_WATER;
}

static f32 cur_obj_move_y_and_get_water_level(f32 gravity, f32 buoyancy) {
    o->oVelY += gravity + buoyancy;
    if (o->oVelY < -78.0f) o->oVelY = -78.0f;
    o->oPosY += o->oVelY;
    return (o->activeFlags & ACTIVE_FLAG_IGNORE_WATER_LEVEL) ? FLOOR_LOWER_LIMIT : find_water_level(o->oPosX, o->oPosZ);
}

void cur_obj_move_y(f32 gravity, f32 bounciness, f32 buoyancy) {
    f32 waterLevel;
    o->oMoveFlags &= ~OBJ_MOVE_LEFT_GROUND;
    if (o->oMoveFlags & OBJ_MOVE_AT_WATER_SURFACE && o->oVelY > 5.0f) {
        o->oMoveFlags &= ~OBJ_MOVE_MASK_IN_WATER;
        o->oMoveFlags |=  OBJ_MOVE_LEAVING_WATER;
    }
    if (!(o->oMoveFlags & OBJ_MOVE_MASK_IN_WATER)) {
        waterLevel = cur_obj_move_y_and_get_water_level(gravity, 0.0f);
        if (o->oPosY > waterLevel) {
            //! We only handle floor collision if the object does not enter
            //  water. This allows e.g. coins to clip through floors if they
            //  enter water on the same frame.
            cur_obj_move_update_ground_air_flags(gravity, bounciness);
        } else {
            o->oMoveFlags |=  OBJ_MOVE_ENTERED_WATER;
            o->oMoveFlags &= ~OBJ_MOVE_MASK_ON_GROUND;
        }
    } else {
        o->oMoveFlags &= ~OBJ_MOVE_ENTERED_WATER;
        waterLevel = cur_obj_move_y_and_get_water_level(gravity, buoyancy);
        if (o->oPosY < waterLevel) {
            cur_obj_move_update_underwater_flags();
        } else if (o->oPosY < o->oFloorHeight) {
            o->oPosY       = o->oFloorHeight;
            o->oMoveFlags &= ~OBJ_MOVE_MASK_IN_WATER;
        } else {
            o->oPosY       = waterLevel;
            o->oVelY       = 0.0f;
            o->oMoveFlags &= ~(OBJ_MOVE_UNDERWATER_OFF_GROUND | OBJ_MOVE_UNDERWATER_ON_GROUND);
            o->oMoveFlags |= OBJ_MOVE_AT_WATER_SURFACE;
        }
    }
    if (o->oMoveFlags & (OBJ_MOVE_MASK_ON_GROUND | OBJ_MOVE_AT_WATER_SURFACE | OBJ_MOVE_UNDERWATER_OFF_GROUND)) {
        o->oMoveFlags &= ~OBJ_MOVE_IN_AIR;
    } else {
        o->oMoveFlags |= OBJ_MOVE_IN_AIR;
    }
}

static s32 clear_move_flag(u32 *bitSet, s32 flag) {
    if (*bitSet & flag) {
        *bitSet &= flag ^ 0xFFFFFFFF;
        return TRUE;
    } else {
        return FALSE;
    }
}

void cur_obj_unused_resolve_wall_collisions(f32 offsetY, f32 radius) {
    if (radius > 0.1f) f32_find_wall_collision(&o->oPosX, &o->oPosY, &o->oPosZ, offsetY, radius); // was 0.1l
}

void cur_obj_move_xz_using_fvel_and_yaw(void) {
    o->oVelX = o->oForwardVel * sins(o->oMoveAngleYaw);
    o->oVelZ = o->oForwardVel * coss(o->oMoveAngleYaw);
    o->oPosX += o->oVelX;
    o->oPosZ += o->oVelZ;
}

void cur_obj_move_y_with_terminal_vel(void) {
    if (o->oVelY < -(TERMINAL_GRAVITY_VELOCITY - 5.0f)) o->oVelY = -(TERMINAL_GRAVITY_VELOCITY - 5.0f);
    o->oPosY += o->oVelY;
}

void cur_obj_compute_vel_xz(void) {
    o->oVelX = o->oForwardVel * sins(o->oMoveAngleYaw);
    o->oVelZ = o->oForwardVel * coss(o->oMoveAngleYaw);
}

f32 increment_velocity_toward_range(f32 value, f32 center, f32 zeroThreshold, f32 increment) {
    f32 relative;
    if ((relative = value - center) > 0) {
        return ((relative <  zeroThreshold) ? 0.0f : -increment);
    } else {
        return ((relative > -zeroThreshold) ? 0.0f :  increment);
    }
}

s32 obj_check_if_collided_with_object(struct Object *obj1, struct Object *obj2) {
    s32 i;
    for (i = 0; i < obj1->numCollidedObjs; i++) if (obj1->collidedObjs[i] == obj2) return TRUE;
    return FALSE;
}

void cur_obj_set_behavior(const BehaviorScript *behavior) {
    o->behavior = segmented_to_virtual(behavior);
}

void obj_set_behavior(struct Object *obj, const BehaviorScript *behavior) {
    obj->behavior = segmented_to_virtual(behavior);
}

s32 cur_obj_has_behavior(const BehaviorScript *behavior) {
    return (o->behavior == segmented_to_virtual(behavior));
}

s32 obj_has_behavior(struct Object *obj, const BehaviorScript *behavior) {
    return (obj->behavior == segmented_to_virtual(behavior));
}

f32 cur_obj_lateral_dist_from_mario_to_home(void) {
    f32 dx = o->oHomeX - gMarioObject->oPosX;
    f32 dz = o->oHomeZ - gMarioObject->oPosZ;
    return sqrtf(dx * dx + dz * dz);
}

f32 cur_obj_lateral_dist_to_home(void) {
    f32 dx = o->oHomeX - o->oPosX;
    f32 dz = o->oHomeZ - o->oPosZ;
    return sqrtf(dx * dx + dz * dz);
}

s32 cur_obj_outside_home_square(f32 halfLength) {
    if (o->oHomeX - halfLength > o->oPosX) return TRUE;
    if (o->oHomeX + halfLength < o->oPosX) return TRUE;
    if (o->oHomeZ - halfLength > o->oPosZ) return TRUE;
    if (o->oHomeZ + halfLength < o->oPosZ) return TRUE;
    return FALSE;
}

s32 cur_obj_outside_home_rectangle(f32 minX, f32 maxX, f32 minZ, f32 maxZ) {
    if (o->oHomeX + minX > o->oPosX) return TRUE;
    if (o->oHomeX + maxX < o->oPosX) return TRUE;
    if (o->oHomeZ + minZ > o->oPosZ) return TRUE;
    if (o->oHomeZ + maxZ < o->oPosZ) return TRUE;
    return FALSE;
}

void cur_obj_set_pos_to_home(void) {
    o->oPosX = o->oHomeX;
    o->oPosY = o->oHomeY;
    o->oPosZ = o->oHomeZ;
}

void cur_obj_set_pos_to_home_and_stop(void) {
    cur_obj_set_pos_to_home();
    o->oForwardVel = 0.0f;
    o->oVelY       = 0.0f;
}

void cur_obj_shake_y(f32 amount) {
    //! Technically could cause a bit of drift, but not much
    if (o->oTimer & 0x1) {
        o->oPosY -= amount;
    } else {
        o->oPosY += amount;
    }
}

void cur_obj_start_cam_event(UNUSED struct Object *obj, s32 cameraEvent) {
    gPlayerCameraState->cameraEvent = (s16) cameraEvent;
    gSecondCameraFocus = o;
}

// unused, self explanatory, maybe oInteractStatus originally had TRUE/FALSE statements
void set_mario_interact_true_if_in_range(f32 range) {
    if (o->oDistanceToMario < range) gMarioObject->oInteractStatus = TRUE;
}

void obj_set_billboard(struct Object *obj) {
    obj->header.gfx.node.flags |= GRAPH_RENDER_BILLBOARD;
}

void cur_obj_set_hitbox_radius_and_height(f32 radius, f32 height) {
    o->hitboxRadius = radius;
    o->hitboxHeight = height;
}

void cur_obj_set_hurtbox_radius_and_height(f32 radius, f32 height) {
    o->hurtboxRadius = radius;
    o->hurtboxHeight = height;
}

static void obj_spawn_loot_coins(struct Object *obj, s32 numCoins, f32 baseYVel, const BehaviorScript *coinBehavior, s16 posJitter, s16 model) {
    s32 i;
    f32 spawnHeight;
    struct Surface *floor;
    struct Object  *coin;
    spawnHeight = find_floor(obj->oPosX, obj->oPosY, obj->oPosZ, &floor);
    if (obj->oPosY - spawnHeight > 100.0f) spawnHeight = obj->oPosY;
    for (i = 0; i < numCoins; i++) {
        if (obj->oNumLootCoins <= 0) break;
        obj->oNumLootCoins--;
        coin = spawn_object(obj, model, coinBehavior);
        obj_translate_xz_random(coin, posJitter);
        coin->oPosY = spawnHeight;
        coin->oCoinBaseYVel = baseYVel;
    }
}

void obj_spawn_loot_blue_coins(struct Object *obj, s32 numCoins, f32 baseYVel, s16 posJitter) {
    obj_spawn_loot_coins(obj, numCoins, baseYVel, bhvBlueCoinJumping, posJitter, MODEL_BLUE_COIN);
}

void obj_spawn_loot_yellow_coins(struct Object *obj, s32 numCoins, f32 baseYVel) {
    obj_spawn_loot_coins(obj, numCoins, baseYVel, bhvSingleCoinGetsSpawned, 0, MODEL_YELLOW_COIN);
}

void cur_obj_spawn_loot_coin_at_mario_pos(void) {
    struct Object *coin;
    if (o->oNumLootCoins <= 0) return;
    o->oNumLootCoins--;
    coin = spawn_object(o, MODEL_YELLOW_COIN, bhvSingleCoinGetsSpawned);
    coin->oVelY = 30.0f;
    obj_copy_pos(coin, gMarioObject);
}

f32 cur_obj_abs_y_dist_to_home(void) {
    f32 dist = o->oHomeY - o->oPosY;
    if (dist < 0) dist = -dist;
    return dist;
}

s32 cur_obj_advance_looping_anim(void) {
    s32 animFrame = o->header.gfx.animInfo.animFrame;
    s32 loopEnd   = o->header.gfx.animInfo.curAnim->loopEnd;
    if (animFrame < 0) {
        animFrame = 0;
    } else if (loopEnd - 1 == animFrame) {
        animFrame = 0;
    } else {
        animFrame++;
    }
    return ((animFrame << 16) / loopEnd);
}

static s32 cur_obj_detect_steep_floor(s16 steepAngleDegrees) {
    struct Surface *intendedFloor;
    f32 intendedX, intendedFloorHeight, intendedZ;
    f32 deltaFloorHeight;
    f32 steepNormalY = coss(DEGREES(steepAngleDegrees));
    if (o->oForwardVel != 0.0f) {
        intendedX           = o->oPosX + o->oVelX;
        intendedZ           = o->oPosZ + o->oVelZ;
        intendedFloorHeight = find_floor(intendedX, o->oPosY, intendedZ, &intendedFloor);
        deltaFloorHeight    = intendedFloorHeight - o->oFloorHeight;
        if (intendedFloorHeight < FLOOR_LOWER_LIMIT_MISC) {
            o->oWallAngle = o->oMoveAngleYaw + 0x8000;
            return 2;
        } else if (intendedFloor->normal.y < steepNormalY && deltaFloorHeight > 0 && intendedFloorHeight > o->oPosY) {
            o->oWallAngle = atan2s(intendedFloor->normal.z, intendedFloor->normal.x);
            return 1;
        }
    }
    return 0;
}

s32 cur_obj_resolve_wall_collisions(void) {
    s32 numCollisions;
    struct Surface *wall;
    struct WallCollisionData collisionData;
    f32 offsetY = 10.0f;
    f32 radius = o->oWallHitboxRadius;
    if (radius > 0.1f) { // was 0.1l
        collisionData.offsetY = offsetY;
        collisionData.radius  = radius;
        collisionData.x       = (s16) o->oPosX;
        collisionData.y       = (s16) o->oPosY;
        collisionData.z       = (s16) o->oPosZ;
        numCollisions         = find_wall_collisions(&collisionData);
        if (numCollisions != 0) {
            o->oPosX          = collisionData.x;
            o->oPosY          = collisionData.y;
            o->oPosZ          = collisionData.z;
            wall              = collisionData.walls[collisionData.numWalls - 1];
            o->oWallAngle     = atan2s(wall->normal.z, wall->normal.x);
            return (abs_angle_diff(o->oWallAngle, o->oMoveAngleYaw) > 0x4000);
        }
    }
    return FALSE;
}

static void cur_obj_update_floor(void) {
    struct Surface *floor = cur_obj_update_floor_height_and_get_floor();
    o->oFloor = floor;
    if (floor != NULL) {
        if (floor->type == SURFACE_BURNING) {
            o->oMoveFlags |= OBJ_MOVE_ABOVE_LAVA;
        } else if (floor->type == SURFACE_DEATH_PLANE || floor->type == SURFACE_VERTICAL_WIND) {
            //! This maybe misses SURFACE_WARP
            o->oMoveFlags |= OBJ_MOVE_ABOVE_DEATH_BARRIER;
        }
        o->oFloorType = floor->type;
        o->oFloorRoom = floor->room;
    } else {
        o->oFloorType = 0;
        o->oFloorRoom = 0;
    }
}

static void cur_obj_update_floor_and_resolve_wall_collisions(s16 steepSlopeDegrees) {
    o->oMoveFlags &= ~(OBJ_MOVE_ABOVE_LAVA | OBJ_MOVE_ABOVE_DEATH_BARRIER);
    if (o->activeFlags & (ACTIVE_FLAG_FAR_AWAY | ACTIVE_FLAG_IN_DIFFERENT_ROOM)) {
        cur_obj_update_floor();
        o->oMoveFlags &= ~(OBJ_MOVE_HIT_WALL | OBJ_MOVE_MASK_IN_WATER);
        if (o->oPosY > o->oFloorHeight) o->oMoveFlags |= OBJ_MOVE_IN_AIR;
    } else {
        o->oMoveFlags &= ~OBJ_MOVE_HIT_WALL;
        if (cur_obj_resolve_wall_collisions()) o->oMoveFlags |= OBJ_MOVE_HIT_WALL;
        cur_obj_update_floor();
        if (o->oPosY > o->oFloorHeight) o->oMoveFlags |= OBJ_MOVE_IN_AIR;
        if (cur_obj_detect_steep_floor(steepSlopeDegrees)) o->oMoveFlags |= OBJ_MOVE_HIT_WALL;
    }
}

void cur_obj_update_floor_and_walls(void) {
    cur_obj_update_floor_and_resolve_wall_collisions(60);
}

void cur_obj_move_standard(s16 steepSlopeAngleDegrees) {
    f32 gravity                      = o->oGravity;
    f32 bounciness                   = o->oBounciness;
    f32 buoyancy                     = o->oBuoyancy;
    f32 dragStrength                 = o->oDragStrength;
    f32 steepSlopeNormalY;
    s32 careAboutEdgesAndSteepSlopes = FALSE;
    s32 negativeSpeed                = FALSE;
    //! Because some objects allow these active flags to be set but don't
    //  avoid updating when they are, we end up with "partial" updates, where
    //  an object's internal state will be updated, but it doesn't move.
    //  This allows numerous glitches and is typically referred to as
    //  deactivation (though this term has a different meaning in the code).
    //  Objects that do this will be marked with // PARTIAL_UPDATE.
    if (!(o->activeFlags & (ACTIVE_FLAG_FAR_AWAY | ACTIVE_FLAG_IN_DIFFERENT_ROOM))) {
        if (steepSlopeAngleDegrees < 0) {
            careAboutEdgesAndSteepSlopes = TRUE;
            steepSlopeAngleDegrees = -steepSlopeAngleDegrees;
        }
        if (steepSlopeAngleDegrees == 78) {
            steepSlopeNormalY =  COS78;
        } else if (steepSlopeAngleDegrees == -78) {
            steepSlopeNormalY = -COS78;
        } else if (steepSlopeAngleDegrees == -30) {
            steepSlopeNormalY = -COS30;
        } else {
            steepSlopeNormalY = coss(DEGREES(steepSlopeAngleDegrees));
        }
        cur_obj_compute_vel_xz();
        cur_obj_apply_drag_xz(dragStrength);
        cur_obj_move_xz(steepSlopeNormalY, careAboutEdgesAndSteepSlopes);
        cur_obj_move_y(gravity, bounciness, buoyancy);
        if (o->oForwardVel < 0.0f) negativeSpeed = TRUE;
        o->oForwardVel = sqrtf(sqr(o->oVelX) + sqr(o->oVelZ));
        if (negativeSpeed) o->oForwardVel = -o->oForwardVel;
    }
}

static s32 cur_obj_within_bounds(f32 bounds) {
    if (o->oPosX < -bounds || bounds < o->oPosX) return FALSE;
    if (o->oPosY < -bounds || bounds < o->oPosY) return FALSE;
    if (o->oPosZ < -bounds || bounds < o->oPosZ) return FALSE;
    return TRUE;
}

void cur_obj_move_using_vel_and_gravity(void) {
    if (cur_obj_within_bounds(LEVEL_BOUNDARY_MAX + 4096.0f)) {
        o->oPosX += o->oVelX;
        o->oPosZ += o->oVelZ;
        if (o->oVelY > -TERMINAL_GRAVITY_VELOCITY) {
            o->oVelY += o->oGravity;
        } else if (o->oVelY < -TERMINAL_GRAVITY_VELOCITY) {
            o->oVelY = -TERMINAL_GRAVITY_VELOCITY;
        }
        o->oPosY += o->oVelY;
    }
}

void cur_obj_move_using_fvel_and_gravity(void) {
    cur_obj_compute_vel_xz();
    cur_obj_move_using_vel_and_gravity();
}

void obj_set_pos_relative(struct Object *obj, struct Object *other, f32 dleft, f32 dy, f32 dforward) {
    f32 facingZ        = coss(other->oMoveAngleYaw);
    f32 facingX        = sins(other->oMoveAngleYaw);
    f32 dz             = dforward * facingZ - dleft * facingX;
    f32 dx             = dforward * facingX + dleft * facingZ;
    obj->oMoveAngleYaw = other->oMoveAngleYaw;
    obj->oPosX         = other->oPosX + dx;
    obj->oPosY         = other->oPosY + dy;
    obj->oPosZ         = other->oPosZ + dz;
}

s16 cur_obj_angle_to_home(void) {
    f32 dx = o->oHomeX - o->oPosX;
    f32 dz = o->oHomeZ - o->oPosZ;
    return atan2s(dz, dx);
}

void obj_set_gfx_pos_at_obj_pos(struct Object *obj1, struct Object *obj2) {
    obj1->header.gfx.pos[0]   = obj2->oPosX;
    obj1->header.gfx.pos[1]   = obj2->oPosY + obj2->oGraphYOffset;
    obj1->header.gfx.pos[2]   = obj2->oPosZ;
    obj1->header.gfx.angle[0] = obj2->oMoveAnglePitch & 0xFFFF;
    obj1->header.gfx.angle[1] = obj2->oMoveAngleYaw   & 0xFFFF;
    obj1->header.gfx.angle[2] = obj2->oMoveAngleRoll  & 0xFFFF;
}

/**
 * Transform the vector at localTranslateIndex into the object's local
 * coordinates, and then add it to the vector at posIndex.
 */
void obj_translate_local(struct Object *obj, s16 posIndex, s16 localTranslateIndex) {
    f32 dx = obj->rawData.asF32[localTranslateIndex + 0];
    f32 dy = obj->rawData.asF32[localTranslateIndex + 1];
    f32 dz = obj->rawData.asF32[localTranslateIndex + 2];
    obj->rawData.asF32[posIndex + 0] += obj->transform[0][0] * dx + obj->transform[1][0] * dy + obj->transform[2][0] * dz;
    obj->rawData.asF32[posIndex + 1] += obj->transform[0][1] * dx + obj->transform[1][1] * dy + obj->transform[2][1] * dz;
    obj->rawData.asF32[posIndex + 2] += obj->transform[0][2] * dx + obj->transform[1][2] * dy + obj->transform[2][2] * dz;
}

void obj_build_transform_from_pos_and_angle(struct Object *obj, s16 posIndex, s16 angleIndex) {
    f32 translate[3];
    s16 rotation[3];
    translate[0] = obj->rawData.asF32[posIndex   + 0];
    translate[1] = obj->rawData.asF32[posIndex   + 1];
    translate[2] = obj->rawData.asF32[posIndex   + 2];
    rotation[0]  = obj->rawData.asS32[angleIndex + 0];
    rotation[1]  = obj->rawData.asS32[angleIndex + 1];
    rotation[2]  = obj->rawData.asS32[angleIndex + 2];
    if (translate != gVec3fZero || rotation != gVec3sZero) mtxf_rotate_zxy_and_translate(obj->transform, translate, rotation);
}

void obj_set_throw_matrix_from_transform(struct Object *obj) {
    if (obj->oFlags & OBJ_FLAG_UPDATE_TRANSFORM_FOR_THROW_MATRIX) {
        obj_build_transform_from_pos_and_angle(obj, O_POS_INDEX, O_FACE_ANGLE_INDEX);
        obj_apply_scale_to_transform(obj);
    }
    obj->header.gfx.throwMatrix = &obj->transform;
    obj_scale(obj, 1.0f);
}

void obj_build_transform_relative_to_parent(struct Object *obj) {
    struct Object *parent = obj->parentObj;
    obj_build_transform_from_pos_and_angle(obj, O_PARENT_RELATIVE_POS_INDEX, O_FACE_ANGLE_INDEX);
    obj_apply_scale_to_transform(obj);
    mtxf_mul(obj->transform, obj->transform, parent->transform);
    obj->oPosX = obj->transform[3][0];
    obj->oPosY = obj->transform[3][1];
    obj->oPosZ = obj->transform[3][2];
    obj->header.gfx.throwMatrix = &obj->transform;
    obj_scale(obj, 1.0f);
}

void obj_create_transform_from_self(struct Object *obj) {
    obj->oFlags         &= ~OBJ_FLAG_TRANSFORM_RELATIVE_TO_PARENT;
    obj->oFlags         |=  OBJ_FLAG_SET_THROW_MATRIX_FROM_TRANSFORM;
    obj->transform[3][0] = obj->oPosX;
    obj->transform[3][1] = obj->oPosY;
    obj->transform[3][2] = obj->oPosZ;
}

void cur_obj_rotate_move_angle_using_vel(void) {
    o->oMoveAnglePitch += o->oAngleVelPitch;
    o->oMoveAngleYaw   += o->oAngleVelYaw;
    o->oMoveAngleRoll  += o->oAngleVelRoll;
}

void cur_obj_rotate_face_angle_using_vel(void) {
    o->oFaceAnglePitch += o->oAngleVelPitch;
    o->oFaceAngleYaw   += o->oAngleVelYaw;
    o->oFaceAngleRoll  += o->oAngleVelRoll;
}

void cur_obj_set_face_angle_to_move_angle(void) {
    o->oFaceAnglePitch = o->oMoveAnglePitch;
    o->oFaceAngleYaw   = o->oMoveAngleYaw;
    o->oFaceAngleRoll  = o->oMoveAngleRoll;
}

s32 cur_obj_follow_path(UNUSED s32 unusedArg) {
    struct Waypoint *startWaypoint;
    struct Waypoint *lastWaypoint;
    struct Waypoint *targetWaypoint;
    f32 prevToNextX, prevToNextY, prevToNextZ;
    f32 objToNextXZ;
    f32 objToNextX, objToNextY, objToNextZ;
    if (o->oPathedPrevWaypointFlags == 0) {
        o->oPathedPrevWaypoint = o->oPathedStartWaypoint;
        o->oPathedPrevWaypointFlags = WAYPOINT_FLAGS_INITIALIZED;
    }
    startWaypoint = o->oPathedStartWaypoint;
    lastWaypoint  = o->oPathedPrevWaypoint;
    if ((lastWaypoint + 1)->flags != WAYPOINT_FLAGS_END) {
        targetWaypoint = lastWaypoint + 1;
    } else {
        targetWaypoint = startWaypoint;
    }
    o->oPathedPrevWaypointFlags = lastWaypoint->flags | WAYPOINT_FLAGS_INITIALIZED;
    prevToNextX                 = targetWaypoint->pos[0] - lastWaypoint->pos[0];
    prevToNextY                 = targetWaypoint->pos[1] - lastWaypoint->pos[1];
    prevToNextZ                 = targetWaypoint->pos[2] - lastWaypoint->pos[2];
    objToNextX                  = targetWaypoint->pos[0] - o->oPosX;
    objToNextY                  = targetWaypoint->pos[1] - o->oPosY;
    objToNextZ                  = targetWaypoint->pos[2] - o->oPosZ;
    objToNextXZ                 = sqrtf(sqr(objToNextX) + sqr(objToNextZ));
    o->oPathedTargetYaw         = atan2s(objToNextZ,   objToNextX);
    o->oPathedTargetPitch       = atan2s(objToNextXZ, -objToNextY);
    // If dot(prevToNext, objToNext) <= 0 (i.e. reached other side of target waypoint)
    if (prevToNextX * objToNextX + prevToNextY * objToNextY + prevToNextZ * objToNextZ <= 0.0f) {
        o->oPathedPrevWaypoint = targetWaypoint;
        return (((targetWaypoint + 1)->flags == WAYPOINT_FLAGS_END) ? PATH_REACHED_END : PATH_REACHED_WAYPOINT);
    }
    return PATH_NONE;
}

void chain_segment_init(struct ChainSegment *segment) {
    vec3f_set(segment->pos, 0.0f, 0.0f, 0.0f);
    vec3s_set(segment->angle, 0x0, 0x0, 0x0);
}

void obj_scale_random(struct Object *obj, f32 rangeLength, f32 minScale) {
    f32 scale = random_float() * rangeLength + minScale;
    obj_scale(obj, scale);
}

void obj_translate_xyz_random(struct Object *obj, f32 rangeLength) {
    obj->oPosX += ((random_float() * rangeLength) - (rangeLength * 0.5f));
    obj->oPosY += ((random_float() * rangeLength) - (rangeLength * 0.5f));
    obj->oPosZ += ((random_float() * rangeLength) - (rangeLength * 0.5f));
}

void obj_translate_xz_random(struct Object *obj, f32 rangeLength) {
    obj->oPosX += ((random_float() * rangeLength) - (rangeLength * 0.5f));
    obj->oPosZ += ((random_float() * rangeLength) - (rangeLength * 0.5f));
}

static void obj_build_vel_from_transform(struct Object *obj) {
    f32 localY = obj->oUpVel;
    f32 localX = obj->oLeftVel;
    f32 localZ = obj->oForwardVel;
    // localX and localY were swapped originally, fixed now
    obj->oVelX = ((obj->transform[0][0] * localX) + (obj->transform[1][0] * localY) + (obj->transform[2][0] * localZ));
    obj->oVelY = ((obj->transform[0][1] * localX) + (obj->transform[1][1] * localY) + (obj->transform[2][1] * localZ));
    obj->oVelZ = ((obj->transform[0][2] * localX) + (obj->transform[1][2] * localY) + (obj->transform[2][2] * localZ));
}

void cur_obj_set_pos_via_transform(void) {
    obj_build_transform_from_pos_and_angle(o, O_PARENT_RELATIVE_POS_INDEX, O_MOVE_ANGLE_INDEX);
    obj_build_vel_from_transform(o);
    vec3f_add(&o->oPosVec, &o->oVelVec);
}

s16 cur_obj_reflect_move_angle_off_wall(void) {
    return o->oWallAngle - ((s16) o->oMoveAngleYaw - (s16) o->oWallAngle) + 0x8000;
}

void cur_obj_spawn_particles(struct SpawnParticlesInfo *info) {
    struct Object *particle;
    s32 i;
    f32 scale;
    s32 numParticles = info->count;
    // If there are a lot of objects already, limit the number of particles
    if ((gPrevFrameObjectCount > (OBJECT_POOL_CAPACITY - 90)) && (numParticles > 10)) numParticles = 10;
    // We're close to running out of object slots, so don't spawn particles at
    // all
    if (gPrevFrameObjectCount > (OBJECT_POOL_CAPACITY - 30)) numParticles = 0;
    for (i = 0; i < numParticles; i++) {
        scale                       = ((random_float() * info->sizeRange * 0.1f) + (info->sizeBase * 0.1f));
        particle                    = spawn_object(o, info->model, bhvWhitePuffExplosion);
        particle->oBehParams2ndByte = info->behParam;
        particle->oMoveAngleYaw     = random_u16();
        particle->oGravity          = info->gravity;
        particle->oDragStrength     = info->dragStrength;
        particle->oPosY            += info->offsetY;
        particle->oForwardVel       = ((random_float() * info->forwardVelRange) + info->forwardVelBase);
        particle->oVelY             = ((random_float() * info->velYRange      ) + info->velYBase      );
        obj_scale_xyz(particle, scale, scale, scale);
    }
}

void obj_set_hitbox(struct Object *obj, struct ObjectHitbox *hitbox) {
    if (!(obj->oFlags & OBJ_FLAG_HITBOX_WAS_SET)) {
        obj->oFlags            |= OBJ_FLAG_HITBOX_WAS_SET;
        obj->oInteractType      = hitbox->interactType;
        obj->oDamageOrCoinValue = hitbox->damageOrCoinValue;
        obj->oHealth            = hitbox->health;
        obj->oNumLootCoins      = hitbox->numLootCoins;
        cur_obj_become_tangible();
    }
    obj->hitboxRadius     = (obj->header.gfx.scale[0] * hitbox->radius       );
    obj->hitboxHeight     = (obj->header.gfx.scale[1] * hitbox->height       );
    obj->hurtboxRadius    = (obj->header.gfx.scale[0] * hitbox->hurtboxRadius);
    obj->hurtboxHeight    = (obj->header.gfx.scale[1] * hitbox->hurtboxHeight);
    obj->hitboxDownOffset = (obj->header.gfx.scale[1] * hitbox->downOffset   );
}

s32 cur_obj_wait_then_blink(s32 timeUntilBlinking, s32 numBlinks) {
    s32 timeBlinking;
    if (o->oTimer >= timeUntilBlinking) {
        if ((timeBlinking = o->oTimer - timeUntilBlinking) & 0x1) {
            o->header.gfx.node.flags |=  GRAPH_RENDER_INVISIBLE;
            if (timeBlinking / 2 > numBlinks) return TRUE;
        } else {
            o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
        }
    }
    return FALSE;
}

s32 cur_obj_is_mario_ground_pounding_platform(void) {
    return (gMarioObject->platform == o && (gMarioStates[0].action == ACT_GROUND_POUND_LAND || gMarioStates[0].action == ACT_WATER_GROUND_POUND_LAND));
}

void spawn_mist_particles(void) {
    spawn_mist_particles_variable(0, 0, 46.0f);
}

void spawn_mist_particles_with_sound(u32 soundMagic) {
    spawn_mist_particles_variable(0, 0, 46.0f);
    create_sound_spawner(soundMagic);
}

void cur_obj_push_mario_away(f32 radius) {
    f32 marioRelX = (gMarioObject->oPosX - o->oPosX);
    f32 marioRelZ = (gMarioObject->oPosZ - o->oPosZ);
    f32 marioDist = sqrtf(sqr(marioRelX) + sqr(marioRelZ));
    if (marioDist < radius) {
        //! If this function pushes Mario out of bounds, it will trigger Mario's
        //  oob failsafe
        gMarioStates[0].pos[0] += (((radius - marioDist) / radius) * marioRelX);
        gMarioStates[0].pos[2] += (((radius - marioDist) / radius) * marioRelZ);
    }
}

void cur_obj_push_mario_away_from_cylinder(f32 radius, f32 extentY) {
    f32 marioRelY = (gMarioObject->oPosY - o->oPosY);
    if (marioRelY <    0.0f) marioRelY = -marioRelY;
    if (marioRelY < extentY) cur_obj_push_mario_away(radius);
}

void bhv_dust_smoke_loop(void) {
    vec3f_add(&o->oPosVec, &o->oVelVec);
    if (o->oSmokeTimer == 10) obj_mark_for_deletion(o);
    o->oSmokeTimer++;
}

s32 cur_obj_set_direction_table(s8 *pattern) {
    o->oToxBoxMovementPattern = pattern;
    o->oToxBoxMovementStep    = 0;
    return *(s8 *) o->oToxBoxMovementPattern;
}

s32 cur_obj_progress_direction_table(void) {
    s8 action;
    s8 *pattern  =  o->oToxBoxMovementPattern;
    s32 nextStep = (o->oToxBoxMovementStep + 1);
    if (pattern[nextStep] != TOX_BOX_ACT_END) {
        action = pattern[nextStep];
        o->oToxBoxMovementStep++;
    } else {
        action = pattern[0];
        o->oToxBoxMovementStep = 0;
    }
    return action;
}

void cur_obj_scale_over_time(s32 axis, s32 times, f32 start, f32 end) {
    f32 scale = (((end - start) * ((f32) o->oTimer / times)) + start);
    if (axis & 0x01) o->header.gfx.scale[0] = scale;
    if (axis & 0x02) o->header.gfx.scale[1] = scale;
    if (axis & 0x04) o->header.gfx.scale[2] = scale;
}

void cur_obj_set_pos_to_home_with_debug(void) {
    o->oPosX = o->oHomeX + gDebugInfo[5][0];
    o->oPosY = o->oHomeY + gDebugInfo[5][1];
    o->oPosZ = o->oHomeZ + gDebugInfo[5][2];
    cur_obj_scale(gDebugInfo[5][3] / 100.0f + 1.0f); // was 1.0l
}

s32 cur_obj_is_mario_on_platform(void) {
    return (gMarioObject->platform == o);
}

s32 cur_obj_shake_y_until(s32 cycles, s32 amount) {
    if (o->oTimer & 0x1) {
        o->oPosY -= amount;
    } else {
        o->oPosY += amount;
    }
    return (o->oTimer == (cycles * 2));
}

s32 jiggle_bbh_stair(s32 timer) {
    if ((timer >= 4) || (timer < 0)) return TRUE;
    o->oPosY += sBbhStairJiggleOffsets[timer];
    return FALSE;
}

void cur_obj_call_action_function(void (*actionFunctions[])(void)) {
    void (*actionFunction)(void) = actionFunctions[o->oAction];
    actionFunction();
}

s32 cur_obj_mario_far_away(void) {
    Vec3f d;
    vec3f_diff(d, &o->oHomeVec, &gMarioObject->oPosVec);
    f32 marioDistToHome = vec3f_mag(d);
    return (o->oDistanceToMario > 2000.0f && marioDistToHome > 2000.0f);
}

s32 is_mario_moving_fast_or_in_air(s32 speedThreshold) {
    return ((gMarioStates[0].forwardVel > speedThreshold) || (gMarioStates[0].action & ACT_FLAG_AIR));
}

s32 is_item_in_array(s8 item, s8 *array) {
    while (*array != -1) {
        if (*array == item) return TRUE;
        array++;
    }
    return FALSE;
}

void bhv_init_room(void) {
    struct Surface *floor = NULL;
#ifdef FIX_FIND_ROOM_FLOOR
    UNUSED f32 floorHeight;
    if (is_item_in_array(gCurrLevelNum, sLevelsWithRooms)) {
        floorHeight = find_room_floor(o->oPosX, o->oPosY, o->oPosZ, &floor);
        if (floor != NULL) o->oRoom = floor->room;
#else
    f32 floorHeight;
    if (is_item_in_array(gCurrLevelNum, sLevelsWithRooms)) {
        floorHeight = find_floor(o->oPosX, o->oPosY, o->oPosZ, &floor);
        if (floor != NULL) {
            if (floor->room != 0) {
                o->oRoom = floor->room;
            } else {
                // Floor probably belongs to a platform object. Try looking
                // underneath it
                find_floor(o->oPosX, floorHeight - 100.0f, o->oPosZ, &floor);
                //! Technically possible that the room could still be 0 here
                if (floor != NULL) o->oRoom = floor->room;
            }
        }
#endif
    } else {
        o->oRoom = -1;
    }
}

void cur_obj_enable_rendering_if_mario_in_room(void) {
    if (o->oRoom != -1 && gMarioCurrentRoom != 0) {
        if (gMarioCurrentRoom == o->oRoom
         || gDoorAdjacentRooms[gMarioCurrentRoom][0] == o->oRoom
         || gDoorAdjacentRooms[gMarioCurrentRoom][1] == o->oRoom) {
            cur_obj_enable_rendering();
            o->activeFlags &= ~ACTIVE_FLAG_IN_DIFFERENT_ROOM;
            gNumRoomedObjectsInMarioRoom++;
        } else {
            cur_obj_disable_rendering();
            o->activeFlags |= ACTIVE_FLAG_IN_DIFFERENT_ROOM;
            gNumRoomedObjectsNotInMarioRoom++;
        }
    }
}

s32 cur_obj_set_hitbox_and_die_if_attacked(struct ObjectHitbox *hitbox, s32 deathSound, s32 noLootCoins) {
    s32 interacted = FALSE;
    obj_set_hitbox(o, hitbox);
    if (noLootCoins) o->oNumLootCoins = 0;
    if (o->oInteractStatus & INT_STATUS_INTERACTED) {
        if (o->oInteractStatus & INT_STATUS_WAS_ATTACKED) {
            spawn_mist_particles();
            obj_spawn_loot_yellow_coins(o, o->oNumLootCoins, 20.0f);
            obj_mark_for_deletion(o);
            create_sound_spawner(deathSound);
        } else {
            interacted = TRUE;
        }
    }
    o->oInteractStatus = INT_STATUS_NONE;
    return interacted;
}


void obj_explode_and_spawn_coins(f32 mistSize, s32 coinType) {
    spawn_mist_particles_variable(0, 0, mistSize);
    spawn_triangle_break_particles(30, MODEL_DIRT_ANIMATION, 3.0f, 4);
    obj_mark_for_deletion(o);
    if (coinType == COIN_TYPE_YELLOW) {
        obj_spawn_loot_yellow_coins(o, o->oNumLootCoins, 20.0f);
    } else if (coinType == COIN_TYPE_BLUE) {
        obj_spawn_loot_blue_coins(o, o->oNumLootCoins, 20.0f, 150);
    }
}

void obj_set_collision_data(struct Object *obj, const void *segAddr) {
    obj->collisionData = segmented_to_virtual(segAddr);
}

void cur_obj_if_hit_wall_bounce_away(void) {
    if (o->oMoveFlags & OBJ_MOVE_HIT_WALL) o->oMoveAngleYaw = o->oWallAngle;
}

s32 cur_obj_hide_if_mario_far_away_y(f32 distY) {
    if (absf(o->oPosY - gMarioObject->oPosY) < distY) {
        cur_obj_unhide();
        return FALSE;
    } else {
        cur_obj_hide();
        return TRUE;
    }
}

Gfx *geo_offset_klepto_held_object(s32 callContext, struct GraphNode *node, UNUSED Mat4 mtx) {
    if (callContext == GEO_CONTEXT_RENDER) {
        ((struct GraphNodeTranslationRotation *) node->next)->translation[0] = 300;
        ((struct GraphNodeTranslationRotation *) node->next)->translation[1] = 300;
        ((struct GraphNodeTranslationRotation *) node->next)->translation[2] = 0;
    }

    return NULL;
}

s32 obj_is_hidden(struct Object *obj) {
    return (obj->header.gfx.node.flags & GRAPH_RENDER_INVISIBLE);
}

void enable_time_stop(void) {
    gTimeStopState |= TIME_STOP_ENABLED;
}

void disable_time_stop(void) {
    gTimeStopState &= ~TIME_STOP_ENABLED;
}

void set_time_stop_flags(s32 flags) {
    gTimeStopState |= flags;
}

void clear_time_stop_flags(s32 flags) {
    gTimeStopState = gTimeStopState & (flags ^ 0xFFFFFFFF);
}

s32 cur_obj_can_mario_activate_textbox(f32 radius, f32 height, UNUSED s32 unused) {
    return (o->oDistanceToMario < 1500.0f
         && lateral_dist_between_objects(o, gMarioObject) < radius
         && o->oPosY < gMarioObject->oPosY + 160.0f
         && gMarioObject->oPosY < o->oPosY + height
         && !(gMarioStates[0].action & ACT_FLAG_AIR)
         && mario_ready_to_speak());
}

s32 cur_obj_can_mario_activate_textbox_2(f32 radius, f32 height) {
    // The last argument here is unused. When this function is called directly the argument is always set to 0x7FFF.
    return cur_obj_can_mario_activate_textbox(radius, height, 0x1000);
}

static void cur_obj_end_dialog(s32 dialogFlags, s32 dialogResult) {
    o->oDialogResponse = dialogResult;
    o->oDialogState++;
    if (!(dialogFlags & DIALOG_FLAG_TIME_STOP_ENABLED)) set_mario_npc_dialog(MARIO_DIALOG_STOP);
}

s32 cur_obj_update_dialog(s32 actionArg, s32 dialogFlags, s32 dialogID, UNUSED s32 unused) {
    s32 dialogResponse = DIALOG_RESPONSE_NONE;
    switch (o->oDialogState) {
        case DIALOG_STATUS_ENABLE_TIME_STOP:
            // Patched :(
            // Wait for Mario to be ready to speak, and then enable time stop
            if (mario_ready_to_speak() || gMarioState->action == ACT_READING_NPC_DIALOG) {
                gTimeStopState |= TIME_STOP_ENABLED;
                o->activeFlags |= ACTIVE_FLAG_INITIATED_TIME_STOP;
                o->oDialogState++;
                // fall through
            } else {
                break;
            }
            // Fall through so that Mario's action is interrupted immediately
            // after time is stopped
        case DIALOG_STATUS_INTERRUPT:
            // Interrupt until Mario is actually speaking with the NPC
            if (set_mario_npc_dialog(actionArg) == MARIO_DIALOG_STATUS_SPEAK) {
                o->oDialogState++;
            }
            break;
        case DIALOG_STATUS_START_DIALOG:
            // Starts dialog, depending of the flag defined, it calls
            // a default dialog or a dialog with response.
            if (dialogFlags & DIALOG_FLAG_TEXT_RESPONSE) {
                create_dialog_box_with_response(dialogID);
            } else if (dialogFlags & DIALOG_FLAG_TEXT_DEFAULT) {
                create_dialog_box(dialogID);
            }
            o->oDialogState++;
            break;
        case DIALOG_STATUS_STOP_DIALOG:
            // Stops dialog, if the flag dialog response was called
            // then it defines the value to let the object do the rest.
            if (dialogFlags & DIALOG_FLAG_TEXT_RESPONSE) {
                if (gDialogResponse != DIALOG_RESPONSE_NONE) {
                    cur_obj_end_dialog(dialogFlags, gDialogResponse);
                }
            } else if (dialogFlags & DIALOG_FLAG_TEXT_DEFAULT) {
                if (get_dialog_id() == DIALOG_NONE) cur_obj_end_dialog(dialogFlags, DIALOG_RESPONSE_NOT_DEFINED);
            } else {
                cur_obj_end_dialog(dialogFlags, DIALOG_RESPONSE_NOT_DEFINED);
            }
            break;
        case DIALOG_STATUS_DISABLE_TIME_STOP:
            // We disable time stop for a few seconds when Mario is no longer
            // speaking or the flag is defined, then we enable it again.
            // Usually, an object disables time stop using a separate function
            // after a certain condition is met.
            if (gMarioState->action != ACT_READING_NPC_DIALOG || (dialogFlags & DIALOG_FLAG_TIME_STOP_ENABLED)) {
                gTimeStopState &= ~TIME_STOP_ENABLED;
                o->activeFlags &= ~ACTIVE_FLAG_INITIATED_TIME_STOP;
                dialogResponse  = o->oDialogResponse;
                o->oDialogState = DIALOG_STATUS_ENABLE_TIME_STOP;
            }
            break;
        default:
            o->oDialogState = DIALOG_STATUS_ENABLE_TIME_STOP;
            break;
    }
    return dialogResponse;
}

s32 cur_obj_update_dialog_with_cutscene(s32 actionArg, s32 dialogFlags, s32 cutsceneTable, s32 dialogID) {
    s32 dialogResponse = DIALOG_RESPONSE_NONE;
    s32 doneTurning    = TRUE;
    switch (o->oDialogState) {
        case DIALOG_STATUS_ENABLE_TIME_STOP:
            // Wait for Mario to be ready to speak, and then enable time stop
            if (mario_ready_to_speak() || gMarioState->action == ACT_READING_NPC_DIALOG) {
                gTimeStopState |= TIME_STOP_ENABLED;
                o->activeFlags |= ACTIVE_FLAG_INITIATED_TIME_STOP;
                o->oDialogState++;
                o->oDialogResponse = DIALOG_RESPONSE_NONE;
                // fall through
            } else {
                break;
            }
            // Fall through so that Mario's action is interrupted immediately
            // after time is stopped
        case DIALOG_STATUS_INTERRUPT:
            // Additional flag that makes the NPC rotate towards to Mario
            if (dialogFlags & DIALOG_FLAG_TURN_TO_MARIO) {
                doneTurning = cur_obj_rotate_yaw_toward(obj_angle_to_object(o, gMarioObject), 0x800);
                // Failsafe just in case it takes more than 33 frames somehow
                if (o->oDialogResponse >= 33) doneTurning = TRUE;
            }
            // Interrupt status until Mario is actually speaking with the NPC and if the
            // object is done turning to Mario
            if (set_mario_npc_dialog(actionArg) == MARIO_DIALOG_STATUS_SPEAK && doneTurning) {
                o->oDialogResponse = 0;
                o->oDialogState++;
            } else {
                o->oDialogResponse++; // treated as a timer for the failsafe
            }
            break;
        case DIALOG_STATUS_START_DIALOG:
            // Special check for Cap Switch cutscene since the cutscene itself
            // handles what dialog should use
            if (cutsceneTable == CUTSCENE_CAP_SWITCH_PRESS) {
                if ((o->oDialogResponse = cutscene_object_without_dialog(cutsceneTable, o))) o->oDialogState++;
            } else {
                // General dialog cutscene function, most of the time
                // the "CUTSCENE_DIALOG" cutscene is called
                if ((o->oDialogResponse = cutscene_object_with_dialog(cutsceneTable, o, dialogID))) o->oDialogState++;
            }
            break;
        case DIALOG_STATUS_STOP_DIALOG:
            // If flag defined, keep time stop enabled until the object
            // decided to disable it independently
            if (dialogFlags & DIALOG_FLAG_TIME_STOP_ENABLED) {
                dialogResponse = o->oDialogResponse;
                o->oDialogState = DIALOG_STATUS_ENABLE_TIME_STOP;
            } else if (gMarioState->action != ACT_READING_NPC_DIALOG) {
                // Disable time stop, then enable time stop for a frame
                // until the set_mario_npc_dialog function disables it
                gTimeStopState &= ~TIME_STOP_ENABLED;
                o->activeFlags &= ~ACTIVE_FLAG_INITIATED_TIME_STOP;
                dialogResponse = o->oDialogResponse;
                o->oDialogState = DIALOG_STATUS_ENABLE_TIME_STOP;
            } else {
                // And finally stop Mario dialog status
                set_mario_npc_dialog(MARIO_DIALOG_STOP);
            }
            break;
    }
    return dialogResponse;
}

void cur_obj_align_gfx_with_floor(void) {
    struct Surface *floor;
    Vec3f floorNormal;
    Vec3f position;
    position[0] = o->oPosX;
    position[1] = o->oPosY;
    position[2] = o->oPosZ;
    find_floor(position[0], position[1], position[2], &floor);
    if (floor != NULL) {
        floorNormal[0] = floor->normal.x;
        floorNormal[1] = floor->normal.y;
        floorNormal[2] = floor->normal.z;
        mtxf_align_terrain_normal(o->transform, floorNormal, position, o->oFaceAngleYaw);
        o->header.gfx.throwMatrix = &o->transform;
    }
}

s32 mario_is_within_rectangle(s16 minX, s16 maxX, s16 minZ, s16 maxZ) {
    return !(gMarioObject->oPosX < minX || maxX < gMarioObject->oPosX
          || gMarioObject->oPosZ < minZ || maxZ < gMarioObject->oPosZ);
}

void cur_obj_shake_screen(s32 shake) {
    set_camera_shake_from_point(shake, o->oPosX, o->oPosY, o->oPosZ);
}

s32 obj_attack_collided_from_other_object(struct Object *obj) {
    s32 numCollidedObjs;
    struct Object *other;
    s32 touchedOtherObject = FALSE;
    numCollidedObjs = obj->numCollidedObjs;
    if (numCollidedObjs != 0) {
        other = obj->collidedObjs[0];
        if (other != gMarioObject) {
            other->oInteractStatus |= ATTACK_PUNCH | INT_STATUS_WAS_ATTACKED | INT_STATUS_INTERACTED | INT_STATUS_TOUCHED_BOB_OMB;
            touchedOtherObject = TRUE;
        }
    }
    return touchedOtherObject;
}

s32 cur_obj_was_attacked_or_ground_pounded(void) {
    s32 attacked = FALSE;
    if ((o->oInteractStatus & INT_STATUS_INTERACTED)
        && (o->oInteractStatus & INT_STATUS_WAS_ATTACKED)) attacked = TRUE;
    if (cur_obj_is_mario_ground_pounding_platform()) attacked = TRUE;
    o->oInteractStatus = INT_STATUS_NONE;
    return attacked;
}

void obj_copy_behavior_params(struct Object *dst, struct Object *src) {
    dst->oBehParams = src->oBehParams;
    dst->oBehParams2ndByte = src->oBehParams2ndByte;
}

void cur_obj_init_animation_and_anim_frame(s32 animIndex, s32 animFrame) {
    cur_obj_init_animation_with_sound(animIndex);
    o->header.gfx.animInfo.animFrame = animFrame;
}

s32 cur_obj_init_animation_and_check_if_near_end(s32 animIndex) {
    cur_obj_init_animation_with_sound(animIndex);
    return cur_obj_check_if_near_animation_end();
}

void cur_obj_init_animation_and_extend_if_at_end(s32 animIndex) {
    cur_obj_init_animation_with_sound(animIndex);
    cur_obj_extend_animation_if_at_end();
}

s32 cur_obj_check_grabbed_mario(void) {
    if (o->oInteractStatus & INT_STATUS_GRABBED_MARIO) {
        o->oKingBobombHoldingMarioState = HELD_HELD;
        cur_obj_become_intangible();
        return TRUE;
    }
    return FALSE;
}

s32 player_performed_grab_escape_action(void) {
    static s32 grabReleaseState;
    s32 result = FALSE;
    if (gPlayer1Controller->stickMag < 30.0f) grabReleaseState = FALSE;
    if (grabReleaseState == 0 && gPlayer1Controller->stickMag > 40.0f) {
        grabReleaseState = TRUE;
        result = TRUE;
    }
    if (gPlayer1Controller->buttonPressed & (A_BUTTON | B_BUTTON | Z_TRIG)) return TRUE;
    return result;
}

void cur_obj_unused_play_footstep_sound(s32 animFrame1, s32 animFrame2, s32 sound) {
    if (cur_obj_check_anim_frame(animFrame1)
     || cur_obj_check_anim_frame(animFrame2)) cur_obj_play_sound_2(sound);
}

void enable_time_stop_including_mario(void) {
    gTimeStopState |= TIME_STOP_ENABLED | TIME_STOP_MARIO_AND_DOORS;
    o->activeFlags |= ACTIVE_FLAG_INITIATED_TIME_STOP;
}

void disable_time_stop_including_mario(void) {
    gTimeStopState &= ~(TIME_STOP_ENABLED | TIME_STOP_MARIO_AND_DOORS);
    o->activeFlags &= ~ACTIVE_FLAG_INITIATED_TIME_STOP;
}

s32 cur_obj_check_interacted(void) {
    if (o->oInteractStatus & INT_STATUS_INTERACTED) {
        o->oInteractStatus = INT_STATUS_NONE;
        return TRUE;
    } else {
        return FALSE;
    }
}

void cur_obj_spawn_loot_blue_coin(void) {
    if (o->oNumLootCoins >= 5) {
        spawn_object(o, MODEL_BLUE_COIN, bhvMrIBlueCoin);
        o->oNumLootCoins -= 5;
    }
}

void cur_obj_spawn_star_at_y_offset(f32 targetX, f32 targetY, f32 targetZ, f32 offsetY) {
    f32 objectPosY = o->oPosY;
    o->oPosY += offsetY + gDebugInfo[5][0];
    spawn_default_star(targetX, targetY, targetZ);
    o->oPosY = objectPosY;
}
