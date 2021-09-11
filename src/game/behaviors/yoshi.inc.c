// yoshi.c.inc

struct YoshiHomeLocation {
    s16 x;
    s16 z;
};

// X/Z coordinates of Yoshi's homes that he switches between.
// Note that this doesn't contain the Y coordinate since the castle roof is flat,
// so o->oHomeY is never updated.
static const struct YoshiHomeLocation sYoshiHomeLocations[] = { {     0, -5625 },
                                                                { -1364, -5912 },
                                                                { -1403, -4609 },
                                                                { -1004, -5308 } };

void bhv_yoshi_init(void) {
    o->oGravity            = 2.0f;
    o->oFriction           = 0.9f;
    o->oBuoyancy           = 1.3f;
    o->oInteractionSubtype = INT_SUBTYPE_NPC;
    if ((save_file_get_total_star_count((gCurrSaveFileNum - 1), (COURSE_MIN - 1), (COURSE_MAX - 1)) < 120) || sYoshiDead) obj_mark_for_deletion(o);
}

void yoshi_walk_loop(void) {
    AnimFrame16 animFrame = o->header.gfx.animInfo.animFrame;
    o->oForwardVel        = 10.0f;
    object_step();
    o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oYoshiTargetYaw, 0x500);
    if (is_point_close_to_object(o, o->oHomeX, 3174.0f, o->oHomeZ, 200)) o->oAction = YOSHI_ACT_IDLE;
    cur_obj_init_animation(YOSHI_ANIM_WALK);
    if ((animFrame == 0) || (animFrame == 15)) cur_obj_play_sound_2(SOUND_GENERAL_YOSHI_WALK);
    if (o->oInteractStatus == INT_STATUS_INTERACTED) o->oAction = YOSHI_ACT_TALK;
    if (o->oPosY < 2100.0f) {
        create_respawner(MODEL_YOSHI, bhvYoshi, 3000);
        obj_mark_for_deletion(o);
    }
}

void yoshi_idle_loop(void) {
    s16 chosenHome;
    if (o->oTimer > 90) {
        chosenHome = (random_float() * 3.99f);
        if (o->oYoshiChosenHome == chosenHome) {
            return;
        } else {
            o->oYoshiChosenHome = chosenHome;
        }
        o->oHomeX          = sYoshiHomeLocations[o->oYoshiChosenHome].x;
        o->oHomeZ          = sYoshiHomeLocations[o->oYoshiChosenHome].z;
        o->oYoshiTargetYaw = atan2s((o->oHomeZ - o->oPosZ), (o->oHomeX - o->oPosX));
        o->oAction         = YOSHI_ACT_WALK;
    }
    cur_obj_init_animation(YOSHI_ANIM_IDLE);
    if (o->oInteractStatus == INT_STATUS_INTERACTED) o->oAction = YOSHI_ACT_TALK;
    // Credits; Yoshi appears at this position overlooking the castle near the end of the credits
    if ((gPlayerCameraState->cameraEvent == CAM_EVENT_START_ENDING)
     || (gPlayerCameraState->cameraEvent == CAM_EVENT_START_END_WAVING)) {
        o->oAction = YOSHI_ACT_CREDITS;
        vec3_set(&o->oPosVec, -1798.0f, 3174.0f, -3644.0f);
    }
}

void yoshi_talk_loop(void) {
    if ((Angle) o->oMoveAngleYaw == (Angle) o->oAngleToMario) {
        cur_obj_init_animation(YOSHI_ANIM_IDLE);
        if (set_mario_npc_dialog(MARIO_DIALOG_LOOK_FRONT) == MARIO_DIALOG_STATUS_SPEAK) {
            o->activeFlags |= ACTIVE_FLAG_INITIATED_TIME_STOP;
            if (cutscene_object_with_dialog(CUTSCENE_DIALOG, o, DIALOG_161)) {
                o->activeFlags &= ~ACTIVE_FLAG_INITIATED_TIME_STOP;
                o->oInteractStatus = INT_STATUS_NONE;
                o->oHomeX          = sYoshiHomeLocations[1].x;
                o->oHomeZ          = sYoshiHomeLocations[1].z;
                o->oYoshiTargetYaw = atan2s((o->oHomeZ - o->oPosZ), (o->oHomeX - o->oPosX));
                o->oAction         = YOSHI_ACT_GIVE_PRESENT;
            }
        }
    } else {
        cur_obj_init_animation(YOSHI_ANIM_WALK);
        play_puzzle_jingle();
        o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oAngleToMario, 0x500);
    }
}

void yoshi_walk_and_jump_off_roof_loop(void) {
    AnimFrame16 animFrame = o->header.gfx.animInfo.animFrame;
    o->oForwardVel        = 10.0f;
    object_step();
    cur_obj_init_animation(YOSHI_ANIM_WALK);
    if (o->oTimer == 0) cutscene_object(CUTSCENE_STAR_SPAWN, o);
    o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oYoshiTargetYaw, 0x500);
    if (is_point_close_to_object(o, o->oHomeX, 3174.0f, o->oHomeZ, 200)) {
        cur_obj_init_animation(YOSHI_ANIM_JUMP);
        cur_obj_play_sound_2(SOUND_GENERAL_ENEMY_ALERT1);
        o->oForwardVel   = 50.0f;
        o->oVelY         = 40.0f;
        o->oMoveAngleYaw = -(DEG(90) - 1);
        o->oAction       = YOSHI_ACT_FINISH_JUMPING_AND_DESPAWN;
    }
    //! play footstep sound function?
    if ((animFrame == 0) || (animFrame == 15)) cur_obj_play_sound_2(SOUND_GENERAL_YOSHI_WALK);
}

void yoshi_finish_jumping_and_despawn_loop(void) {
    cur_obj_extend_animation_if_at_end();
    obj_move_xyz_using_fvel_and_yaw(o);
    o->oVelY -= 2.0f;
    if (o->oPosY < 2100.0f) {
        set_mario_npc_dialog(MARIO_DIALOG_STOP);
        gObjCutsceneDone = TRUE;
        sYoshiDead       = TRUE;
        obj_mark_for_deletion(o);
    }
}

void yoshi_give_present_loop(void) {
    s32 timer = gGlobalTimer;
    if (gHudDisplay.lives == 100) {
#ifdef SAVE_NUM_LIVES
        save_file_set_num_lives(gMarioState->numLives);
#endif
        play_sound(SOUND_GENERAL_COLLECT_1UP, gGlobalSoundSource);
        gSpecialTripleJump = TRUE;
        o->oAction = YOSHI_ACT_WALK_JUMP_OFF_ROOF;
        return;
    }
    if (!(timer & 0x03)) {
        play_sound(SOUND_MENU_YOSHI_GAIN_LIVES, gGlobalSoundSource);
        gMarioState->numLives++;
    }
}

void bhv_yoshi_loop(void) {
    switch (o->oAction) {
        case YOSHI_ACT_IDLE:                       yoshi_idle_loop();                       break;
        case YOSHI_ACT_WALK:                       yoshi_walk_loop();                       break;
        case YOSHI_ACT_TALK:                       yoshi_talk_loop();                       break;
        case YOSHI_ACT_WALK_JUMP_OFF_ROOF:         yoshi_walk_and_jump_off_roof_loop();     break;
        case YOSHI_ACT_FINISH_JUMPING_AND_DESPAWN: yoshi_finish_jumping_and_despawn_loop(); break;
        case YOSHI_ACT_GIVE_PRESENT:               yoshi_give_present_loop();               break;
        case YOSHI_ACT_CREDITS:                    cur_obj_init_animation(YOSHI_ANIM_IDLE); break;
    }
    curr_obj_random_blink(&o->oYoshiBlinkTimer);
}
