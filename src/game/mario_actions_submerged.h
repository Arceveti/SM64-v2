#pragma once

#include <PR/ultratypes.h>

#include "types.h"

#define PLUNGE_FLAG_HOLDING_OBJ (1 << 0) // 0x1
#define PLUNGE_FLAG_DIVING      (1 << 1) // 0x2
#define PLUNGE_FLAG_METAL_CAP   (1 << 2) // 0x4

// act_water_ground_pound
#define ACT_WATER_GROUND_POUND_STATE_SPIN       0x0
#define ACT_WATER_GROUND_POUND_STATE_FALL       0x1
// act_water_ground_pound_land
// act_breaststroke
#define ACT_BREASTSTROKE_STATE_START            0x0
#define ACT_BREASTSTROKE_STATE_CONTINUE         0x1
// act_hold_breaststroke
#define ACT_HOLD_BREASTSTROKE_STATE_START       0x0
#define ACT_HOLD_BREASTSTROKE_STATE_CONTINUE    0x1
// act_water_punch
#define ACT_WATER_PUNCH_STATE_START             0x0
#define ACT_WATER_PUNCH_STATE_MISSED            0x1
#define ACT_WATER_PUNCH_STATE_PICK_UP           0x2
// act_drowning
#define ACT_DROWNING_STATE_EYES_HALF_CLOSED     0x0
#define ACT_DROWNING_STATE_EYES_DEAD            0x1
// act_water_plunge
#define ACT_WATER_PLUNGE_STATE_FALL             0x0
#define ACT_WATER_PLUNGE_STATE_SINK             0x1

Bool32 mario_execute_submerged_action(struct MarioState *m);
