#ifndef MARIO_ACTIONS_AIRBORNE_H
#define MARIO_ACTIONS_AIRBORNE_H

#include <PR/ultratypes.h>

#include "types.h"

// act_long_jump
#define ACT_LONG_JUMP_STATE_PLAY_SOUND_HERE_WE_GO   0x0
#define ACT_LONG_JUMP_STATE_PLAYED_SOUND_HERE_WE_GO 0x1
// act_ground_pound
#define ACT_GROUND_POUND_STATE_SPIN                 0x0
#define ACT_GROUND_POUND_STATE_FALL                 0x1
// act_getting_blown
#define ACT_GETTING_BLOWN_STATE_ACCEL_BACKWARDS     0x0
#define ACT_GETTING_BLOWN_STATE_SLOW_DOWN           0x1
// act_forward_rollout
#define ACT_FORWARD_ROLLOUT_STATE_START_HOP         0x0
#define ACT_FORWARD_ROLLOUT_STATE_SPIN              0x1
#define ACT_FORWARD_ROLLOUT_STATE_SPIN_END          0x2
// act_backward_rollout
#define ACT_BACKWARD_ROLLOUT_STATE_START_HOP        0x0
#define ACT_BACKWARD_ROLLOUT_STATE_SPIN             0x1
#define ACT_BACKWARD_ROLLOUT_STATE_SPIN_END         0x2
// act_butt_slide_air
#define ACT_BUTT_SLIDE_AIR_STATE_SMALL_BOUNCE       0x0
#define ACT_BUTT_SLIDE_AIR_STATE_START_SLIDING      0x1
// act_hold_butt_slide_air
#define ACT_HOLD_BUTT_SLIDE_AIR_STATE_SMALL_BOUNCE  0x0
#define ACT_HOLD_BUTT_SLIDE_AIR_STATE_START_SLIDING 0x1
// act_lava_boost
#define ACT_LAVA_BOOST_STATE_HIT_LAVA               0x0
#define ACT_LAVA_BOOST_STATE_SLOW_DOWN              0x1
#define ACT_LAVA_BOOST_STATE_SET_LANDING_ACTION     0x2
// act_slide_kick
#define ACT_SLIDE_KICK_STATE_SLIDING                0x0
#define ACT_SLIDE_KICK_STATE_END                    0x1
// act_jump_kick
#define ACT_JUMP_KICK_STATE_PLAY_SOUND_AND_ANIM     0x0
#define ACT_JUMP_KICK_STATE_KICKING                 0x1
// act_flying
#define ACT_FLYING_STATE_SPIN                       0x0
#define ACT_FLYING_STATE_FLY                        0x1
// act_riding_hoot
#define ACT_RIDING_HOOT_STATE_GRABBING              0x0
#define ACT_RIDING_HOOT_STATE_HANGING               0x1
// act_flying_triple_jump
#define ACT_FLYING_TRIPLE_JUMP_STATE_START          0x0
#define ACT_FLYING_TRIPLE_JUMP_STATE_SPIN           0x1
// act_vertical_wind
#define ACT_VERTICAL_WIND_STATE_SPINNING            0x0
#define ACT_VERTICAL_WIND_STATE_AIRBORNE            0x1
// act_special_triple_jump
#define ACT_SPECIAL_TRIPLE_JUMP_STATE_SPINNING      0x0
#define ACT_SPECIAL_TRIPLE_JUMP_STATE_LANDING       0x1

Bool32 mario_execute_airborne_action(struct MarioState *m);

#endif // MARIO_ACTIONS_AIRBORNE_H
