#pragma once

#include <PR/ultratypes.h>

#include "types.h"

#include "config.h"
#ifdef PLATFORM_DISPLACEMENT_2
    struct PlatformDisplacementInfo {
        Vec3f prevPos;
        Vec3f prevTransformedPos;
        Vec3f prevTransformedYawVec;
        Angle prevYaw;
        struct Object *prevPlatform;
        s32 prevTimer;
    };
#endif
void update_mario_platform(void);
void get_mario_pos(f32 *x, f32 *y, f32 *z);
void set_mario_pos(f32  x, f32  y, f32  z);
#ifdef PLATFORM_DISPLACEMENT_2
void apply_platform_displacement(struct PlatformDisplacementInfo *displaceInfo, Vec3f pos, Angle *yaw, struct Object *platform);
#else
void apply_platform_displacement(u32 isMario, struct Object *platform);
#endif
void apply_mario_platform_displacement(void);
void clear_mario_platform(void);
