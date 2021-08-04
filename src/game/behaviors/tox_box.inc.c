// tox_box.c.inc

s8 sToxBoxDirectionPattern1[] = { TOX_BOX_ACT_MOVE_FORWARD,  TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_FORWARD,  TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_DOWN,     TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_DOWN,     TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_BACKWARD, TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_BACKWARD, TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_DOWN,     TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_DOWN,     TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_BACKWARD, TOX_BOX_ACT_STEP, TOX_BOX_ACT_WAIT,
                                  TOX_BOX_ACT_MOVE_FORWARD,  TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_FORWARD,  TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_FORWARD,  TOX_BOX_ACT_STEP, TOX_BOX_ACT_WAIT,
                                  TOX_BOX_ACT_MOVE_BACKWARD, TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_BACKWARD, TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_UP,       TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_UP,       TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_FORWARD,  TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_FORWARD,  TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_UP,       TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_UP,       TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_BACKWARD, TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_BACKWARD, TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_BACKWARD, TOX_BOX_ACT_STEP, TOX_BOX_ACT_WAIT,
                                  TOX_BOX_ACT_MOVE_FORWARD,  TOX_BOX_ACT_STEP, TOX_BOX_ACT_END };

s8 sToxBoxDirectionPattern2[] = { TOX_BOX_ACT_MOVE_FORWARD,  TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_FORWARD,  TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_UP,       TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_UP,       TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_UP,       TOX_BOX_ACT_STEP, TOX_BOX_ACT_WAIT,
                                  TOX_BOX_ACT_MOVE_DOWN,     TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_DOWN,     TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_DOWN,     TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_BACKWARD, TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_BACKWARD, TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_DOWN,     TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_BACKWARD, TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_BACKWARD, TOX_BOX_ACT_STEP, TOX_BOX_ACT_WAIT,
                                  TOX_BOX_ACT_MOVE_FORWARD,  TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_FORWARD,  TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_UP,       TOX_BOX_ACT_STEP, TOX_BOX_ACT_END };

s8 sToxBoxDirectionPattern3[] = { TOX_BOX_ACT_MOVE_FORWARD,  TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_FORWARD,  TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_FORWARD,  TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_FORWARD,  TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_FORWARD,  TOX_BOX_ACT_STEP, TOX_BOX_ACT_WAIT,
                                  TOX_BOX_ACT_MOVE_BACKWARD, TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_BACKWARD, TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_BACKWARD, TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_BACKWARD, TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_BACKWARD, TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_UP,       TOX_BOX_ACT_STEP, TOX_BOX_ACT_WAIT,
                                  TOX_BOX_ACT_MOVE_DOWN,     TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_DOWN,     TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_BACKWARD, TOX_BOX_ACT_STEP, TOX_BOX_ACT_WAIT,
                                  TOX_BOX_ACT_MOVE_FORWARD,  TOX_BOX_ACT_STEP,
                                  TOX_BOX_ACT_MOVE_UP,       TOX_BOX_ACT_STEP, TOX_BOX_ACT_END };

s8 *sToxBoxDirectionPatterns[] = { sToxBoxDirectionPattern1, sToxBoxDirectionPattern2, sToxBoxDirectionPattern3 };

void tox_box_shake_screen(void) {
    if (o->oDistanceToMario < 3000.0f) cur_obj_shake_screen(SHAKE_POS_SMALL);
}

void tox_box_move(f32 forwardVel, f32 leftVel, s16 deltaPitch, s16 deltaRoll) {
    o->oPosY = 99.41124f * sins((f32)(o->oTimer + 1) / 8 * 0x8000) + o->oHomeY + 3.0f;
    o->oForwardVel      = forwardVel;
    o->oLeftVel         = leftVel;
    o->oFaceAnglePitch += deltaPitch;
    if ((s16) o->oFaceAnglePitch < 0) deltaRoll = -deltaRoll;
    o->oFaceAngleRoll += deltaRoll;
    cur_obj_set_pos_via_transform();
    if (o->oTimer == 7) {
        o->oAction = cur_obj_progress_direction_table();
#ifndef VERSION_JP
        cur_obj_play_sound_2(SOUND_GENERAL_TOX_BOX_MOVE);
#else
        cur_obj_play_sound_2(SOUND_GENERAL_TOX_BOX_MOVE_LOWPRIO);
#endif
    }
}

void tox_box_act_move_forward(void)  { tox_box_move( 64.0f,   0.0f,  0x800,      0); } // act 4
void tox_box_act_move_backward(void) { tox_box_move(-64.0f,   0.0f, -0x800,      0); } // act 5
void tox_box_act_move_down(void)     { tox_box_move(  0.0f, -64.0f,      0,  0x800); } // act 6
void tox_box_act_move_up(void)       { tox_box_move(  0.0f,  64.0f,      0, -0x800); } // act 7

void tox_box_act_step(void) { // act 1
    o->oForwardVel = 0.0f;
    if (o->oTimer == 0) tox_box_shake_screen();
    o->oPosY = o->oHomeY + 3.0f;
    if (o->oTimer == 20) o->oAction = cur_obj_progress_direction_table();
}

void tox_box_act_wait(void) { // act 2
    if (o->oTimer == 20) o->oAction = cur_obj_progress_direction_table();
}

void tox_box_act_init(void) { // act 0
    s8 *pattern = sToxBoxDirectionPatterns[o->oBehParams2ndByte];
    o->oAction = cur_obj_set_direction_table(pattern);
}

void (*sToxBoxActions[])(void) = { tox_box_act_init,
                                   tox_box_act_step,
                                   tox_box_act_wait,
                                   tox_box_act_move_forward,
                                   tox_box_act_move_backward,
                                   tox_box_act_move_down,
                                   tox_box_act_move_up };

void bhv_tox_box_loop(void) {
    cur_obj_call_action_function(sToxBoxActions);
    load_object_collision_model();
}
