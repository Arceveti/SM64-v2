#ifndef MARIO_ACTIONS_CUTSCENE_H
#define MARIO_ACTIONS_CUTSCENE_H

#include <PR/ultratypes.h>

#include "macros.h"
#include "types.h"

// set_mario_npc_dialog
// actionArg
#define MARIO_DIALOG_STOP           0x0
#define MARIO_DIALOG_LOOK_FRONT     0x1 // no head turn
#define MARIO_DIALOG_LOOK_UP        0x2
#define MARIO_DIALOG_LOOK_DOWN      0x3
// dialogState
#define MARIO_DIALOG_STATUS_NONE    0x0
#define MARIO_DIALOG_STATUS_START   0x1
#define MARIO_DIALOG_STATUS_SPEAK   0x2

void print_displaying_credits_entry(void);
void bhv_end_peach_loop(            void);
void bhv_end_toad_loop(             void);
s32  geo_switch_peach_eyes(s32 callContext, struct GraphNode *node, UNUSED s32 context);
s32  mario_ready_to_speak(          void);
s32  set_mario_npc_dialog(s32 actionArg);
MarioAction mario_execute_cutscene_action(struct MarioState *m);

#endif // MARIO_ACTIONS_CUTSCENE_H
