#ifndef MARIO_ACTIONS_CUTSCENE_H
#define MARIO_ACTIONS_CUTSCENE_H

#include <PR/ultratypes.h>

#include "macros.h"
#include "types.h"

// act_reading_sign
#define ACT_READING_SIGN_STATE_START_DIALOG                     0x0
#define ACT_READING_SIGN_STATE_TURN_TOWARD_SIGN                 0x1
#define ACT_READING_SIGN_STATE_IN_DIALOG                        0x2
// general_star_dance_handler, act_star_dance, act_star_dance_water
#define ACT_STAR_DANCE_STATE_CUTSCENE                           0x0
#define ACT_STAR_DANCE_STATE_DO_SAVE                            0x1
#define ACT_STAR_DANCE_STATE_RETURN                             0x2
// act_quicksand_death
#define ACT_QUICKSAND_DEATH_INIT                                0x0
#define ACT_QUICKSAND_DEATH_SINK                                0x1
#define ACT_QUICKSAND_DEATH_DEAD                                0x2
// act_unlocking_star_door
#define ACT_UNLOCKING_STAR_DOOR_STATE_MOVE_POS                  0x0
#define ACT_UNLOCKING_STAR_DOOR_STATE_SUMMON_STAR               0x1
#define ACT_UNLOCKING_STAR_DOOR_STATE_APPROACH_DOOR             0x2
#define ACT_UNLOCKING_STAR_DOOR_STATE_IN_DIALOG                 0x3
// act_warp_door_spawn
#define ACT_WARP_DOOR_SPAWN_SET_INTERACT_STATUS                 0x0
#define ACT_WARP_DOOR_EXIT_DOOR                                 0x1
// act_spawn_spin_airborne
#define ACT_SPAWN_SPIN_AIRBORNE_STATE_SPINNING                  0x0
#define ACT_SPAWN_SPIN_AIRBORNE_STATE_FALLING                   0x1
// act_exit_land_save_dialog
#define ACT_EXIT_LAND_SAVE_DIALOG_STATE_DETERMINE_TYPE          0x0
#define ACT_EXIT_LAND_SAVE_DIALOG_STATE_KEY                     0x1
#define ACT_EXIT_LAND_SAVE_DIALOG_STATE_NO_CAP                  0x2
#define ACT_EXIT_LAND_SAVE_DIALOG_STATE_WITH_CAP                0x3
// act_bbh_enter_spin
#define ACT_BBH_ENTER_SPIN_STATE_SET_Y_VEL                      0x0
#define ACT_BBH_ENTER_SPIN_STATE_SPINNING                       0x1
#define ACT_BBH_ENTER_SPIN_STATE_WAIT_FOR_ANIM                  0x2
#define ACT_BBH_ENTER_SPIN_STATE_DIVE                           0x3
#define ACT_BBH_ENTER_SPIN_STATE_END                            0x4
// act_bbh_enter_jump
#define ACT_BBH_ENTER_JUMP_STATE_INIT                           0x0
#define ACT_BBH_ENTER_JUMP_STATE_MOVE                           0x1
// act_squished
#define ACT_SQUISHED_STATE_SCALING                              0x0
#define ACT_SQUISHED_STATE_CHECK_HEIGHT                         0x1
#define ACT_SQUISHED_STATE_UNSQUISH                             0x2
// jumbo_star_cutscene_falling
#define JUMBO_STAR_CUTSCENE_FALLING_STATE_FALL                  0x0
#define JUMBO_STAR_CUTSCENE_FALLING_STATE_LAND                  0x1
// jumbo_star_cutscene_taking_off
#define JUMBO_STAR_CUTSCENE_TAKING_OFF_STATE_DANCE              0x0
#define JUMBO_STAR_CUTSCENE_TAKING_OFF_STATE_JUMPING            0x1
// jumbo_star_cutscene_flying
#define JUMBO_STAR_CUTSCENE_FLYING_STATE_INIT                   0x0
#define JUMBO_STAR_CUTSCENE_FLYING_STATE_ANGLES                 0x1
#define JUMBO_STAR_CUTSCENE_FLYING_STATE_FALL                   0x2
// end_peach_cutscene_summon_jumbo_star
#define END_PEACH_CUTSCENE_SUMMON_JUMBO_STAR_STATE_RAISE_HAND   0x0
#define END_PEACH_CUTSCENE_SUMMON_JUMBO_STAR_STATE_LOWER_HAND   0x1
// end_peach_cutscene_dialog_1
#define END_PEACH_CUTSCENE_DIALOG_1_STATE_TAKE_OFF_CAP          0x0
#define END_PEACH_CUTSCENE_DIALOG_1_STATE_LOOK_UP               0x1
// end_peach_cutscene_run_to_castle
#define END_PEACH_CUTSCENE_RUN_TO_CASTLE_STATE_WALK_LOOK_UP     0x0
#define END_PEACH_CUTSCENE_RUN_TO_CASTLE_STATE_LOOK_BACK_RUN    0x1
// end_peach_cutscene_fade_out
#define END_PEACH_CUTSCENE_FADE_OUT_STATE_WARP                  0x0
#define END_PEACH_CUTSCENE_FADE_OUT_STATE_END                   0x1
// act_end_waving_cutscene
#define ACT_END_WAVING_CUTSCENE_INIT                            0x0
#define ACT_END_WAVING_CUTSCENE_WAVING                          0x1

// set_mario_npc_dialog
// actionArg
#define MARIO_DIALOG_STOP                                       0x0
#define MARIO_DIALOG_LOOK_FRONT                                 0x1 // no head turn
#define MARIO_DIALOG_LOOK_UP                                    0x2
#define MARIO_DIALOG_LOOK_DOWN                                  0x3
// dialogState
#define MARIO_DIALOG_STATUS_NONE                                0x0
#define MARIO_DIALOG_STATUS_START                               0x1
#define MARIO_DIALOG_STATUS_SPEAK                               0x2

void print_displaying_credits_entry(void);
void bhv_end_peach_loop(            void);
void bhv_end_toad_loop(             void);
Gfx *geo_switch_peach_eyes(s32 callContext, struct GraphNode *node, UNUSED s32 context);
s32  mario_ready_to_speak(          void);
s32  set_mario_npc_dialog(s32 actionArg);
Bool32 mario_execute_cutscene_action(struct MarioState *m);

#endif // MARIO_ACTIONS_CUTSCENE_H
