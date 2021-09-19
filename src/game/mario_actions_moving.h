#pragma once

#include <PR/ultratypes.h>

#include "types.h"

// act_walking
#define ACT_WALKING_STATE_NO_WALL               0x0
#define ACT_WALKING_STATE_REACH_WALL            0x1
// act_move_punching
#define ACT_MOVE_PUNCHING_STATE_CAN_JUMP_KICK   0x0
#define ACT_MOVE_PUNCHING_STATE_NO_JUMP_KICK    0x1
// push_or_sidle_wall
#define PUSH_OR_SIDLE_WALL_STATE_PUSHING        0x0
#define PUSH_OR_SIDLE_WALL_STATE_SIDLING        0x1

void play_step_sound(              struct MarioState *m, AnimFrame16 frame1, AnimFrame16 frame2);
Bool32 mario_execute_moving_action(struct MarioState *m);
