#pragma once

#include <PR/ultratypes.h>

#include "types.h"

// act_idle
#define ACT_IDLE_STATE_HEAD_LEFT            0x0
#define ACT_IDLE_STATE_HEAD_RIGHT           0x1
#define ACT_IDLE_STATE_HEAD_CENTER          0x2
#define ACT_IDLE_STATE_SLEEP                0x3
// act_start_sleeping
#define ACT_START_SLEEPING_STATE_IDLE       0x0
#define ACT_START_SLEEPING_STATE_SCRATCH    0x1
#define ACT_START_SLEEPING_STATE_YAWN       0x2
#define ACT_START_SLEEPING_STATE_SITTING    0x3
#define ACT_START_SLEEPING_STATE_SLEEP      0x4
// act_sleeping
#define ACT_SLEEPING_STATE_IDLE             0x0
#define ACT_SLEEPING_STATE_START_LYING      0x1
#define ACT_SLEEPING_STATE_LYING            0x2
// act_shivering
#define ACT_SHIVERING_STATE_WARMING_HAND    0x0
#define ACT_SHIVERING_STATE_SHAKE           0x1
#define ACT_SHIVERING_STATE_RETURN_TO_IDLE  0x2
// act_twirl_land
// act_ground_pound_land
// act_first_person
#define ACT_FIRST_PERSON_STATE_SET_MODE     0x0
#define ACT_FIRST_PERSON_STATE_IDLE         0x1

Bool32 check_common_idle_cancels(      struct MarioState *m);
Bool32 check_common_hold_idle_cancels( struct MarioState *m);
Bool32 act_idle(                       struct MarioState *m);
void   play_anim_sound(                struct MarioState *m, u32 actionState, AnimFrame32 animFrame, u32 sound);
Bool32 act_start_sleeping(             struct MarioState *m);
Bool32 act_sleeping(                   struct MarioState *m);
Bool32 act_waking_up(                  struct MarioState *m);
Bool32 act_shivering(                  struct MarioState *m);
Bool32 act_coughing(                   struct MarioState *m);
Bool32 act_standing_against_wall(      struct MarioState *m);
Bool32 act_in_quicksand(               struct MarioState *m);
Bool32 act_crouching(                  struct MarioState *m);
Bool32 act_panting(                    struct MarioState *m);
void   stopping_step(                  struct MarioState *m, AnimID32 animID, MarioAction action);
Bool32 act_braking_stop(               struct MarioState *m);
Bool32 act_butt_slide_stop(            struct MarioState *m);
Bool32 act_hold_butt_slide_stop(       struct MarioState *m);
Bool32 act_slide_kick_slide_stop(      struct MarioState *m);
Bool32 act_start_crouching(            struct MarioState *m);
Bool32 act_stop_crouching(             struct MarioState *m);
Bool32 act_start_crawling(             struct MarioState *m);
Bool32 act_stop_crawling(              struct MarioState *m);
Bool32 act_shockwave_bounce(           struct MarioState *m);
Bool32 landing_step(                   struct MarioState *m, AnimID32 animID, MarioAction action);
Bool32 check_common_landing_cancels(   struct MarioState *m,                  MarioAction action);
Bool32 act_jump_land_stop(             struct MarioState *m);
Bool32 act_double_jump_land_stop(      struct MarioState *m);
Bool32 act_side_flip_land_stop(        struct MarioState *m);
Bool32 act_freefall_land_stop(         struct MarioState *m);
Bool32 act_triple_jump_land_stop(      struct MarioState *m);
Bool32 act_backflip_land_stop(         struct MarioState *m);
Bool32 act_lava_boost_land(            struct MarioState *m);
Bool32 act_long_jump_land_stop(        struct MarioState *m);
Bool32 act_hold_jump_land_stop(        struct MarioState *m);
Bool32 act_hold_freefall_land_stop(    struct MarioState *m);
Bool32 act_air_throw_land(             struct MarioState *m);
Bool32 act_twirl_land(                 struct MarioState *m);
Bool32 act_ground_pound_land(          struct MarioState *m);
Bool32 act_first_person(               struct MarioState *m);
Bool32 check_common_stationary_cancels(struct MarioState *m);
Bool32 mario_execute_stationary_action(struct MarioState *m);
