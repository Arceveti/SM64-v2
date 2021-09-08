#include <PR/ultratypes.h>

#include "engine/math_util.h"
#include "engine/surface_collision.h"
#include "level_update.h"
#include "object_fields.h"
#include "object_helpers.h"
#include "object_list_processor.h"
#include "platform_displacement.h"
#include "types.h"
#include "sm64.h"
#include "behavior_data.h"

#include "config.h"

struct Object *gMarioPlatform = NULL;

/**
 * Determine if Mario is standing on a platform object, meaning that he is
 * within 4 units of the floor. Set his referenced platform object accordingly.
 */
void update_mario_platform(void) {
    struct Surface *floor;
    if (gMarioObject == NULL) return;
    floor = gMarioState->floor;
    if ((absf(gMarioState->pos[1] - gMarioState->floorHeight) < 4.0f) && (floor != NULL) && (floor->object != NULL)) {
        gMarioPlatform 		   = floor->object;
        gMarioObject->platform = floor->object;
    } else {
        gMarioPlatform 		   = NULL;
        gMarioObject->platform = NULL;
    }
}

/**
 * Get Mario's position and store it in x, y, and z.
 */
void get_mario_pos(f32 *x, f32 *y, f32 *z) {
    *x = gMarioStates[0].pos[0];
    *y = gMarioStates[0].pos[1];
    *z = gMarioStates[0].pos[2];
}

/**
 * Set Mario's position.
 */
void set_mario_pos(f32 x, f32 y, f32 z) {
    vec3_set(gMarioStates[0].pos, x, y, z);
}

#ifdef PLATFORM_DISPLACEMENT_2
static struct PlatformDisplacementInfo sMarioDisplacementInfo;
static Vec3f sMarioAmountDisplaced;

extern s32 gGlobalTimer;

/**
 * Apply one frame of platform displacement to Mario or an object using the given
 * platform.
 */
void apply_platform_displacement(struct PlatformDisplacementInfo *displaceInfo, Vec3f pos, Angle *yaw, struct Object *platform) {
    Vec3f platformPos, posDifference, scaledPos, yawVec;
    // Determine how much Mario turned on his own since last frame
    Angle yawDifference = (*yaw - displaceInfo->prevYaw);
    // Avoid a crash if the platform unloaded its collision while stood on
    if (platform->header.gfx.throwMatrix == NULL) return;
    vec3_copy(platformPos, (*platform->header.gfx.throwMatrix)[3]);
    // Determine how far Mario moved on his own since last frame
    vec3_copy(posDifference, pos);
    vec3_sub(posDifference, displaceInfo->prevPos);
    if ((platform == displaceInfo->prevPlatform) && (gGlobalTimer == (displaceInfo->prevTimer + 1))) {
        // Transform from relative positions to world positions
        vec3_prod(scaledPos, displaceInfo->prevTransformedPos, platform->header.gfx.scale);
        linear_mtxf_mul_vec3f(*platform->header.gfx.throwMatrix, pos, scaledPos);
        // Add on how much Mario moved in the previous frame
        vec3_add(pos, posDifference);
        // Calculate new yaw
        linear_mtxf_mul_vec3f(*platform->header.gfx.throwMatrix, yawVec, displaceInfo->prevTransformedYawVec);
        *yaw = (atan2s(yawVec[2], yawVec[0]) + yawDifference);
    } else {
        // First frame of standing on the platform, don't calculate a new position
        vec3_sub(pos, platformPos);
    }
    //! Apply displacement specifically for TTC Treadmills
    if (platform->behavior == segmented_to_virtual(bhvTTCTreadmill)) vec3_add(pos, &platform->oVelVec);
    // Transform from world positions to relative positions for use next frame
    linear_mtxf_transpose_mul_vec3f(*platform->header.gfx.throwMatrix, scaledPos, pos);
    vec3_quot(displaceInfo->prevTransformedPos, scaledPos, platform->header.gfx.scale);
    vec3_add(pos, platformPos);
    // If the object is Mario, set inertia
    if (pos == gMarioState->pos) {
        vec3_copy(sMarioAmountDisplaced, pos);
        vec3_sub(sMarioAmountDisplaced, displaceInfo->prevPos);
        vec3_sub(sMarioAmountDisplaced, posDifference);
        // Make sure inertia isn't set on the first frame otherwise the previous value isn't cleared
        if ((platform != displaceInfo->prevPlatform) || (gGlobalTimer != (displaceInfo->prevTimer + 1))) vec3_zero(sMarioAmountDisplaced);
    }
    // Update info for next frame
    // Update position
    vec3_copy(displaceInfo->prevPos, pos);
    // Set yaw info
    vec3_set(yawVec, sins(*yaw), 0, coss(*yaw));
    linear_mtxf_transpose_mul_vec3f(*platform->header.gfx.throwMatrix, displaceInfo->prevTransformedYawVec, yawVec);
    displaceInfo->prevYaw      = *yaw;
    // Update platform and timer
    displaceInfo->prevPlatform = platform;
    displaceInfo->prevTimer    = gGlobalTimer;
}

// Doesn't change in the code, set this to FALSE if you don't want inertia
const  Bool8 gDoInertia          = TRUE;

static Bool8 sShouldApplyInertia = FALSE;
static Bool8 sInertiaFirstFrame  = FALSE;

/**
 * Apply inertia based on Mario's last platform.
 */
static void apply_mario_inertia(void) {
    // On the first frame of leaving the ground, boost Mario's y velocity
    if (sInertiaFirstFrame) gMarioState->vel[1] += sMarioAmountDisplaced[1];
    // Apply sideways inertia
    gMarioState->pos[0]                         += sMarioAmountDisplaced[0];
    gMarioState->pos[2]                         += sMarioAmountDisplaced[2];
    // Drag
    sMarioAmountDisplaced[0]                    *= 0.97f;
    sMarioAmountDisplaced[2]                    *= 0.97f;
    // Stop applying inertia once Mario has landed, or when ground pounding
    if (!(gMarioState->action & ACT_FLAG_AIR) || (gMarioState->action == ACT_GROUND_POUND)) sShouldApplyInertia = FALSE;
}

/**
 * Apply platform displacement or inertia if required.
 */
void apply_mario_platform_displacement(void) {
    struct Object *platform;
    platform = gMarioPlatform;
    if (!(gTimeStopState & TIME_STOP_ACTIVE) && (gMarioObject != NULL)) {
        if (platform != NULL) {
            apply_platform_displacement(&sMarioDisplacementInfo, gMarioState->pos, &gMarioState->faceAngle[1], platform);
            sShouldApplyInertia = TRUE;
            sInertiaFirstFrame  = TRUE;
        } else if (sShouldApplyInertia && gDoInertia) {
            apply_mario_inertia();
            sInertiaFirstFrame = FALSE;
        }
    }
}
#else
/**
 * Apply one frame of platform rotation to Mario or an object using the given
 * platform. If isMario is false, use gCurrentObject.
 */
void apply_platform_displacement(u32 isMario, struct Object *platform) {
    Vec3f objPos, platformPos;
    Vec3f currentObjectOffset, relativeOffset, newObjectOffset;
    Vec3a rotation;
    f32 displaceMatrix[4][4];
    vec3_copy(rotation, &platform->oAngleVelVec);
    if (isMario) {
        get_mario_pos(&objPos[0], &objPos[1], &objPos[2]);
    } else {
        vec3_copy(objPos, &o->oPosVec);
    }
    objPos[0] += platform->oVelX;
    objPos[2] += platform->oVelZ;
    if ((rotation[0] != 0x0) || (rotation[1] != 0x0) || (rotation[2] != 0x0)) {
        if (isMario) gMarioStates[0].faceAngle[1] += rotation[1];
        vec3_copy(platformPos, &platform->oPosVec);
        vec3_diff(currentObjectOffset, objPos, platformPos);
        vec3_diff(rotation, &platform->oFaceAngleVec, rotation);
        mtxf_rotate_zxy_and_translate(  displaceMatrix, currentObjectOffset, rotation);
        linear_mtxf_transpose_mul_vec3f(displaceMatrix,      relativeOffset, currentObjectOffset);
        vec3_copy(rotation, &platform->oFaceAngleVec);
        mtxf_rotate_zxy_and_translate(displaceMatrix, currentObjectOffset, rotation);
        linear_mtxf_mul_vec3f(displaceMatrix, newObjectOffset, relativeOffset);
        vec3_sum(objPos, platformPos, newObjectOffset);
    }
    if (isMario) {
        set_mario_pos(objPos[0], objPos[1], objPos[2]);
    } else {
        vec3_copy(&o->oPosVec, objPos);
    }
}

/**
* If Mario's platform is not null, apply platform displacement.
*/
void apply_mario_platform_displacement(void) {
    struct Object *platform = gMarioPlatform;
    if (!(gTimeStopState & TIME_STOP_ACTIVE) && (gMarioObject != NULL) && (platform != NULL)) apply_platform_displacement(TRUE, platform);
}
#endif

/**
 * Set Mario's platform to NULL.
 */
void clear_mario_platform(void) {
    gMarioPlatform = NULL;
}
