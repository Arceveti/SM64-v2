// capswitch.c.inc

// UNUSED uchar sCapSwitchText[] = { DIALOG_010, DIALOG_011, DIALOG_012 };

void cap_switch_act_init(void) {
    o->oAnimState = o->oBehParams2ndByte;
    cur_obj_scale(0.5f);
    o->oPosY += 71.0f;
    spawn_object_relative_with_scale(OBJ_BP_NONE, 0, -71, 0, 0.5f, o, MODEL_CAP_SWITCH_BASE, bhvCapSwitchBase);
    if (gCurrLevelNum != LEVEL_UNKNOWN_32) {
        if (save_file_get_flags() & sCapSaveFlags[o->oBehParams2ndByte]) {
            o->oAction             = CAP_SWITCH_ACT_DONE;
            o->header.gfx.scale[1] = 0.1f;
        } else {
            o->oAction = CAP_SWITCH_ACT_IDLE;
        }
    } else {
        o->oAction = CAP_SWITCH_ACT_IDLE;
    }
}

void cap_switch_act_idle(void) {
    if (cur_obj_is_mario_on_platform()) {
        save_file_set_flags(sCapSaveFlags[o->oBehParams2ndByte]);
        o->oAction = CAP_SWITCH_ACT_BEING_PRESSED;
        cur_obj_play_sound_2(SOUND_GENERAL_ACTIVATE_CAP_SWITCH);
    }
}

void cap_switch_act_being_pressed(void) {
    if (o->oTimer < 5) {
        cur_obj_scale_over_time(2, 4, 0.5f, 0.1f);
        if (o->oTimer == 4) {
            cur_obj_shake_screen(SHAKE_POS_SMALL);
            spawn_mist_particles();
            spawn_triangle_break_particles(60, MODEL_CARTOON_STAR, 0.3f, o->oBehParams2ndByte);
#if ENABLE_RUMBLE
            queue_rumble_data(5, 80);
#endif
        }
    } else {
        //! Neither of these flags are defined in this function so they do nothing.
        //  On an extra note, there's a specific check for this cutscene and 
        //  there's no dialog defined since the cutscene itself calls the dialog.
        if (cur_obj_update_dialog_with_cutscene(MARIO_DIALOG_LOOK_FRONT, 
            (DIALOG_FLAG_TEXT_RESPONSE | DIALOG_FLAG_UNK_CAPSWITCH), CUTSCENE_CAP_SWITCH_PRESS, 0)) o->oAction = CAP_SWITCH_ACT_DONE;
    }
}

void cap_switch_act_done(void) {
    // do nothing
}

void (*sCapSwitchActions[])(void) = { cap_switch_act_init,
                                      cap_switch_act_idle,
                                      cap_switch_act_being_pressed,
                                      cap_switch_act_done };

void bhv_cap_switch_loop(void) {
    cur_obj_call_action_function(sCapSwitchActions);
}
