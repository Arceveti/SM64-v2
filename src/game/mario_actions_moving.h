#ifndef MARIO_ACTIONS_MOVING
#define MARIO_ACTIONS_MOVING

#include <PR/ultratypes.h>

#include "types.h"

void play_step_sound(            struct MarioState *m, AnimFrame16 frame1, AnimFrame16 frame2);
Bool32 mario_execute_moving_action(struct MarioState *m);

#endif // MARIO_ACTIONS_MOVING
