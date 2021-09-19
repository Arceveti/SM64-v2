#pragma once

#include <PR/ultratypes.h>

#include "types.h"

struct BullyCollisionData {
  /*0x00*/ f32 conversionRatio;
  /*0x04*/ f32 radius;
  /*0x08*/ f32 posX;
  /*0x0C*/ f32 posZ;
  /*0x10*/ f32 velX;
  /*0x14*/ f32 velZ;
};

extern struct Surface gWaterSurfacePseudoFloor;

f32  get_additive_y_vel_for_jumps(void);
void stub_mario_step_1(struct MarioState *m);
void stub_mario_step_2(void);

void mario_bonk_reflection(       struct MarioState *m, u32 negateSpeed);
void transfer_bully_speed(        struct BullyCollisionData *obj1, struct BullyCollisionData *obj2);
void init_bully_collision_data(   struct BullyCollisionData *data, f32 posX, f32 posZ, f32 forwardVel, Angle yaw, f32 conversionRatio, f32 radius);
Bool32 mario_update_quicksand(    struct MarioState *m, f32 sinkingSpeed);
Bool32 mario_push_off_steep_floor(struct MarioState *m, MarioAction action, u32 actionArg);
Bool32 mario_update_moving_sand(  struct MarioState *m);
Bool32 mario_update_windy_ground( struct MarioState *m);
void stop_and_set_height_to_floor(struct MarioState *m);
MarioStep stationary_ground_step( struct MarioState *m);
MarioStep perform_ground_step(    struct MarioState *m);
MarioStep perform_air_step(       struct MarioState *m, u32 stepArg);
