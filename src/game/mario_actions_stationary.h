#ifndef MARIO_ACTIONS_STATIONARY
#define MARIO_ACTIONS_STATIONARY

#include <PR/ultratypes.h>

#include "types.h"

MarioAction check_common_idle_cancels(      struct MarioState *m);
MarioAction check_common_hold_idle_cancels( struct MarioState *m);
MarioAction act_idle(                       struct MarioState *m);
void        play_anim_sound(                struct MarioState *m, u32 actionState, AnimFrame32 animFrame, u32 sound);
MarioAction act_start_sleeping(             struct MarioState *m);
MarioAction act_sleeping(                   struct MarioState *m);
MarioAction act_waking_up(                  struct MarioState *m);
MarioAction act_shivering(                  struct MarioState *m);
MarioAction act_coughing(                   struct MarioState *m);
MarioAction act_standing_against_wall(      struct MarioState *m);
MarioAction act_in_quicksand(               struct MarioState *m);
MarioAction act_crouching(                  struct MarioState *m);
MarioAction act_panting(                    struct MarioState *m);
void        stopping_step(                  struct MarioState *m, AnimID32 animID, MarioAction action);
MarioAction act_braking_stop(               struct MarioState *m);
MarioAction act_butt_slide_stop(            struct MarioState *m);
MarioAction act_hold_butt_slide_stop(       struct MarioState *m);
MarioAction act_slide_kick_slide_stop(      struct MarioState *m);
MarioAction act_start_crouching(            struct MarioState *m);
MarioAction act_stop_crouching(             struct MarioState *m);
MarioAction act_start_crawling(             struct MarioState *m);
MarioAction act_stop_crawling(              struct MarioState *m);
MarioAction act_shockwave_bounce(           struct MarioState *m);
MarioAction landing_step(                   struct MarioState *m, AnimID32 animID, MarioAction action);
MarioAction check_common_landing_cancels(   struct MarioState *m,                  MarioAction action);
MarioAction act_jump_land_stop(             struct MarioState *m);
MarioAction act_double_jump_land_stop(      struct MarioState *m);
MarioAction act_side_flip_land_stop(        struct MarioState *m);
MarioAction act_freefall_land_stop(         struct MarioState *m);
MarioAction act_triple_jump_land_stop(      struct MarioState *m);
MarioAction act_backflip_land_stop(         struct MarioState *m);
MarioAction act_lava_boost_land(            struct MarioState *m);
MarioAction act_long_jump_land_stop(        struct MarioState *m);
MarioAction act_hold_jump_land_stop(        struct MarioState *m);
MarioAction act_hold_freefall_land_stop(    struct MarioState *m);
MarioAction act_air_throw_land(             struct MarioState *m);
MarioAction act_twirl_land(                 struct MarioState *m);
MarioAction act_ground_pound_land(          struct MarioState *m);
MarioAction act_first_person(               struct MarioState *m);
MarioAction check_common_stationary_cancels(struct MarioState *m);
MarioAction mario_execute_stationary_action(struct MarioState *m);

#endif // MARIO_ACTIONS_STATIONARY
