#include <ultra64.h>
#include "types.h"
#include "boot/game_init.h"
#include "engine/math_util.h"
#include "camera.h"

#ifdef VARIABLE_FRAMERATE

#define LERP_THRESHOLD       300.0f
#define LERP_THRESHOLD_SCALE 0.05f
#define LERP_THRESHOLD_ANGLE 0x4000

void approach_pos(f32 *value[3], f32 orig) {
    f32 tempPos[3];
    // Set a temporary place to store the value, and copy it over.
    vec3_copy(tempPos, *value);
    // If the point is too far, just snap there instead, then update current, previous and target.
    if (ABSF(orig - tempPos[1]) > LERP_THRESHOLD) vec3_same(tempPos, orig);
    // Check if the target value is *not* the intended value.
    if (tempPos[2] != orig) {
        // Set previous to current target.
        tempPos[1] = tempPos[2];
        // Set current target to intended value.
        tempPos[2] = orig;
    }
    // Lerp the current value to the target value, in relation to the previous value.
    // tempPos[0] += ((tempPos[1] - tempPos[2]) * gMoveSpeed);
    tempPos[0] = approach_f32_asymptotic(tempPos[0], tempPos[2], gMoveSpeed);
    // Copy the temporary value back to the original.
    vec3_copy(*value, tempPos);
}

void approach_pos_vector(Vec3f *value, Vec3f orig, s32 index) {
    Vec3f tempPos[3];
    // Set a temporary place to store the value, and copy it over.
    vec3_copy(tempPos[0], value[0]);
    vec3_copy(tempPos[1], value[1]);
    vec3_copy(tempPos[2], value[2]);

    f32 threshold = ((index == 0) ? LERP_THRESHOLD : LERP_THRESHOLD_SCALE);

    // If the point is too far, just snap there instead, then update current, previous and target.
    if (ABSF(orig[0] - tempPos[0][0]) > threshold || ABSF(orig[0] - tempPos[1][0]) > threshold || ABSF(orig[0] - tempPos[2][0]) > threshold) {
        tempPos[0][0] = orig[0]; tempPos[1][0] = orig[0]; tempPos[2][0] = orig[0];
    } else {
        if (tempPos[2][0] != orig[0]) {
            // Set previous to current target.
            tempPos[1][0] = tempPos[2][0];
            // Set current target to intended value.
            tempPos[2][0] = orig[0];
        }
        tempPos[0][0] = approach_f32_asymptotic(tempPos[0][0], tempPos[2][0], gMoveSpeed);
    }


    if (ABSF(orig[1] - tempPos[0][1]) > threshold || ABSF(orig[1] - tempPos[1][1]) > threshold || ABSF(orig[1] - tempPos[2][1]) > threshold) {
        tempPos[0][1] = orig[1]; tempPos[1][1] = orig[1]; tempPos[2][1] = orig[1];
    } else {
        if (tempPos[2][1] != orig[1]) {
            tempPos[1][1] = tempPos[2][1];
            tempPos[2][1] = orig[1];
        }
        tempPos[0][1] = approach_f32_asymptotic(tempPos[0][1], tempPos[2][1], gMoveSpeed);
    }

    if (ABSF(orig[2] - tempPos[0][2]) > threshold || ABSF(orig[2] - tempPos[1][2]) > threshold || ABSF(orig[2] - tempPos[2][2]) > threshold) {
        tempPos[0][2] = orig[2]; tempPos[1][2] = orig[2]; tempPos[2][2] = orig[2];
    } else {
        if (tempPos[2][2] != orig[2]) {
            tempPos[1][2] = tempPos[2][2];
            tempPos[2][2] = orig[2];
        }
        tempPos[0][2] = approach_f32_asymptotic(tempPos[0][2], tempPos[2][2], gMoveSpeed);
    }

    // Copy the temporary value back to the original.
    vec3_copy(value[0], tempPos[0]);
    vec3_copy(value[1], tempPos[1]);
    vec3_copy(value[2], tempPos[2]);
}

extern s16 abs_angle_diff(s16 x0, s16 x1);

u16 angle_lerp(u16 current, u16 target) {
    if (absi(target - current) < (absi(target - current + 0x10000))) {
        if (absi(target - current) < (absi(target - current - 0x10000))) {
            return current + (target - current) * gMoveSpeed;
        } else {
            return current + (target - (current - 0x10000)) * gMoveSpeed;
        }
    } else {
        return current + (target - (current + 0x10000)) * gMoveSpeed;
    }
}

void approach_angle_vector(Vec3s *value, Vec3s orig) {
    Vec3a tempAngle[3];
    // Set a temporary place to store the value, and copy it over.
    vec3_copy(tempAngle[0], value[0]);
    vec3_copy(tempAngle[1], value[1]);
    vec3_copy(tempAngle[2], value[2]);
    // If the point is too far, just snap there instead, then update current, previous and target.
    if (abs_angle_diff(orig[0], tempAngle[0][0]) > LERP_THRESHOLD_ANGLE || abs_angle_diff(orig[0], tempAngle[2][0]) > LERP_THRESHOLD_ANGLE) {
        tempAngle[0][0] = orig[0]; tempAngle[1][0] = orig[0]; tempAngle[2][0] = orig[0];
    } else {
        if (tempAngle[2][0] != orig[0]) {
            // Set previous to current target.
            tempAngle[1][0] = tempAngle[2][0];
            // Set current target to intended value.
            tempAngle[2][0] = orig[0];
        }
        tempAngle[0][0] = approach_s16_asymptotic(tempAngle[0][0], tempAngle[2][0], 1.0f/gMoveSpeed);
    }

    if (abs_angle_diff(orig[1], tempAngle[0][1]) > LERP_THRESHOLD_ANGLE || abs_angle_diff(orig[1], tempAngle[2][1]) > LERP_THRESHOLD_ANGLE) {
        tempAngle[0][1] = orig[1]; tempAngle[1][1] = orig[1]; tempAngle[2][1] = orig[1];
    } else {
        if (tempAngle[2][1] != orig[1]) {
            tempAngle[1][1] = tempAngle[2][1];
            tempAngle[2][1] = orig[1];
        }
        tempAngle[0][1] = approach_s16_asymptotic(tempAngle[0][1], tempAngle[2][1], 1.0f/gMoveSpeed);
    }

    if (abs_angle_diff(orig[2], tempAngle[0][2]) > LERP_THRESHOLD_ANGLE || abs_angle_diff(orig[2], tempAngle[2][2]) > LERP_THRESHOLD_ANGLE) {
        tempAngle[0][2] = orig[2]; tempAngle[1][2] = orig[2]; tempAngle[2][2] = orig[2];
    } else {
        if (tempAngle[2][2] != orig[2]) {
            tempAngle[1][2] = tempAngle[2][2];
            tempAngle[2][2] = orig[2];
        }
        tempAngle[0][2] = approach_s16_asymptotic(tempAngle[0][2], tempAngle[2][2], (1.0f / gMoveSpeed));
    }

    // Copy the temporary value back to the original.
    vec3_copy(value[0], tempAngle[0]);
    vec3_copy(value[1], tempAngle[1]);
    vec3_copy(value[2], tempAngle[2]);
}

void approach_angle(s16 *value[3], s16 orig) {
    Vec3s tempPos;
    // Set a temporary place to store the value, and copy it over.
    vec3_copy(tempPos, *value);
    // If the point is too far, just snap there instead, then update current, previous and target.
    if (ABSF(orig - tempPos[1]) > 0x1000) vec3_same(tempPos, orig);
    // Check if the target value is *not* the intended value.
    if (tempPos[2] != orig) {
        // Set previous to current target.
        tempPos[1] = tempPos[2];
        // Set current target to intended value.
        tempPos[2] = orig;
    }
    // Lerp the current value to the target value, in relation to the previous value.
    tempPos[0] += ((tempPos[1] - tempPos[2]) * gMoveSpeed);
    // Copy the temporary value back to the original.
    vec3_copy(*value, tempPos);
}

void warp_node(struct Object *node) {
    vec3f_copy(node->header.gfx.lerpPos[0], node->header.gfx.pos);
    vec3f_copy(node->header.gfx.lerpPos[1], node->header.gfx.pos);
    vec3f_copy(node->header.gfx.lerpPos[2], node->header.gfx.pos);

    vec3a_copy(node->header.gfx.lerpAngle[0], node->header.gfx.angle);
    vec3a_copy(node->header.gfx.lerpAngle[1], node->header.gfx.angle);
    vec3a_copy(node->header.gfx.lerpAngle[2], node->header.gfx.angle);

    vec3f_copy(node->header.gfx.lerpScale[0], node->header.gfx.scale);
    vec3f_copy(node->header.gfx.lerpScale[1], node->header.gfx.scale);
    vec3f_copy(node->header.gfx.lerpScale[2], node->header.gfx.scale);
}
#endif
