#ifndef MARIO_ACTIONS_SUBMERGED_H
#define MARIO_ACTIONS_SUBMERGED_H

#include <PR/ultratypes.h>

#include "types.h"

#define PLUNGE_FLAG_HOLDING_OBJ (1 << 0) // 0x1
#define PLUNGE_FLAG_DIVING      (1 << 1) // 0x2
#define PLUNGE_FLAG_METAL_CAP   (1 << 2) // 0x4

Bool32 mario_execute_submerged_action(struct MarioState *m);

#endif // MARIO_ACTIONS_SUBMERGED_H
