#pragma once

#include <PR/ultratypes.h>

#include "types.h"

#define ACT_IN_CANNON_STATE_INIT            0x0
#define ACT_IN_CANNON_STATE_WAIT_FOR_CANNON 0x1
#define ACT_IN_CANNON_STATE_READY           0x2

Bool32 mario_execute_automatic_action(struct MarioState *m);
