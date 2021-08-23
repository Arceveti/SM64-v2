// whomp.c.inc

void whomp_play_sfx_from_pound_animation(void) {
    s32 playSound = FALSE;
    if (o->oForwardVel < 5.0f) {
        playSound  = cur_obj_check_anim_frame( 0);
        playSound |= cur_obj_check_anim_frame(23);
    } else {
        playSound  = cur_obj_check_anim_frame_in_range( 0, 3);
        playSound |= cur_obj_check_anim_frame_in_range(23, 3);
    }
    if (playSound) cur_obj_play_sound_2(SOUND_OBJ_POUNDING1);
}

void whomp_init(void) {
    cur_obj_init_animation_with_accel_and_sound(WHOMP_ANIM_WALK, 1.0f);
    cur_obj_set_pos_to_home();
    if (o->oBehParams2ndByte != WHOMP_BP_NORMAL) {
        gSecondCameraFocus = o;
        cur_obj_scale(2.0f);
        if (o->oSubAction == WHOMP_SUB_ACT_INIT_IDLE) {
            if (o->oDistanceToMario < 600.0f) {
                o->oSubAction = WHOMP_SUB_ACT_INIT_DIALOG;
                seq_player_lower_volume(SEQ_PLAYER_LEVEL, 60, 40);
            } else {
                cur_obj_set_pos_to_home();
                o->oHealth = 3;
            }
        } else if (cur_obj_update_dialog_with_cutscene(MARIO_DIALOG_LOOK_UP, 
            DIALOG_FLAG_TURN_TO_MARIO, CUTSCENE_DIALOG, DIALOG_114)) {
            o->oAction = WHOMP_ACT_KING_CHASE;
        }
    } else if (o->oDistanceToMario < 500.0f) {
        o->oAction = WHOMP_ACT_PATROL;
    }
    whomp_play_sfx_from_pound_animation();
}

void whomp_turn(void) {
    if (o->oSubAction == WHOMP_SUB_ACT_TURN_TURNING) {
        o->oForwardVel = 0.0f;
        cur_obj_init_animation_with_accel_and_sound(WHOMP_ANIM_WALK, 1.0f);
        if (o->oTimer > 31) {
            o->oSubAction = WHOMP_SUB_ACT_TURN_END;
        } else {
            o->oMoveAngleYaw += 0x400;
        }
    } else {
        o->oForwardVel = 3.0f;
        if (o->oTimer > 42) o->oAction = WHOMP_ACT_PATROL;
    }
    whomp_play_sfx_from_pound_animation();
}

void whomp_patrol(void) {
    Angle marioAngle = abs_angle_diff(o->oAngleToMario, o->oMoveAngleYaw);
    f32 distWalked = cur_obj_lateral_dist_to_home();
    f32 patrolDist = (gCurrLevelNum == LEVEL_BITS) ? 200.0f : 700.0f; // should be a param?

    cur_obj_init_animation_with_accel_and_sound(WHOMP_ANIM_WALK, 1.0f);
    o->oForwardVel = 3.0f;

    if (distWalked > patrolDist) {
        o->oAction = WHOMP_ACT_TURN;
    } else if (marioAngle < 0x2000) {
        if (o->oDistanceToMario < 1500.0f) {
            o->oForwardVel = 9.0f;
            cur_obj_init_animation_with_accel_and_sound(WHOMP_ANIM_WALK, 3.0f);
        }
        if (o->oDistanceToMario < 300.0f) o->oAction = WHOMP_ACT_PREPARE_JUMP;
    }
    whomp_play_sfx_from_pound_animation();
}

void king_whomp_chase(void) {
    Angle marioAngle;
    cur_obj_init_animation_with_accel_and_sound(WHOMP_ANIM_WALK, 1.0f);
    o->oForwardVel = 3.0f;
    cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x200);

    if (o->oTimer > 30) {
        marioAngle = abs_angle_diff(o->oAngleToMario, o->oMoveAngleYaw);
        if (marioAngle < 0x2000) {
            if (o->oDistanceToMario < 1500.0f) {
                o->oForwardVel = 9.0f;
                cur_obj_init_animation_with_accel_and_sound(WHOMP_ANIM_WALK, 3.0f);
            }
            if (o->oDistanceToMario < 300.0f) o->oAction = WHOMP_ACT_PREPARE_JUMP;
        }
    }

    whomp_play_sfx_from_pound_animation();
    if (mario_is_far_below_object(1000.0f)) {
        o->oAction = WHOMP_ACT_INIT;
        stop_background_music(SEQUENCE_ARGS(4, SEQ_EVENT_BOSS));
    }
}

void whomp_prepare_jump(void) {
    o->oForwardVel = 0.0f;
    cur_obj_init_animation_with_accel_and_sound(WHOMP_ANIM_JUMP, 1.0f);
    if (cur_obj_check_if_near_animation_end()) o->oAction = WHOMP_ACT_JUMP;
}

void whomp_jump(void) {
    if (o->oTimer == 0) o->oVelY = 40.0f;
    if (o->oTimer >= 8) {
        o->oAngleVelPitch += 0x100;
        o->oFaceAnglePitch += o->oAngleVelPitch;
        if (o->oFaceAnglePitch > 0x4000) {
            o->oAngleVelPitch  = 0x0;
            o->oFaceAnglePitch = 0x4000;
            o->oAction = WHOMP_ACT_LAND;
        }
    }
}

void whomp_land(void) {
    if (o->oSubAction == WHOMP_SUB_ACT_LAND_EFFECTS && o->oMoveFlags & OBJ_MOVE_LANDED) {
        cur_obj_play_sound_2(SOUND_OBJ_WHOMP_LOWPRIO);
        cur_obj_shake_screen(SHAKE_POS_SMALL);
        o->oVelY      = 0.0f;
        o->oSubAction = WHOMP_SUB_ACT_LAND_ON_GROUND;
    }
    if (o->oMoveFlags & OBJ_MOVE_ON_GROUND) o->oAction = WHOMP_ACT_ON_GROUND_GENERAL;
}

void king_whomp_on_ground(void) {
    Vec3f pos;
    if (o->oSubAction == WHOMP_SUB_ACT_GROUND_LYING_DOWN) {
        if (cur_obj_is_mario_ground_pounding_platform()) {
            o->oHealth--;
            cur_obj_play_sound_2(SOUND_OBJ2_WHOMP_SOUND_SHORT);
            cur_obj_play_sound_2(SOUND_OBJ_KING_WHOMP_DEATH);
            if (o->oHealth == 0) {
                o->oAction = WHOMP_ACT_DIE;
            } else {
                vec3f_copy(pos, &o->oPosVec);
                vec3f_copy(&o->oPosVec, &gMarioObject->oPosVec);
                spawn_mist_particles_variable(0, 0, 100.0f);
                spawn_triangle_break_particles(20, MODEL_DIRT_ANIMATION, 3.0f, 4);
                cur_obj_shake_screen(SHAKE_POS_SMALL);
                vec3f_copy(&o->oPosVec, pos);
            }
            o->oSubAction = WHOMP_SUB_ACT_GROUND_PREPARE_STAND_UP;
        }
        o->oWhompShakeVal = 0;
    } else {
        if (o->oWhompShakeVal < 10) {
            if (o->oWhompShakeVal & 0x1) {
                o->oPosY += 8.0f;
            } else {
                o->oPosY -= 8.0f;
            }
        } else {
            o->oSubAction = WHOMP_SUB_ACT_GROUND_STAND_UP;
        }
        o->oWhompShakeVal++;
    }
}

void whomp_on_ground(void) {
    if (o->oSubAction == WHOMP_SUB_ACT_GROUND_LYING_DOWN) {
        if (gMarioObject->platform == o) {
            if (cur_obj_is_mario_ground_pounding_platform()) {
                o->oNumLootCoins = 5;
                obj_spawn_loot_yellow_coins(o, 5, 20.0f);
                o->oAction = WHOMP_ACT_DIE;
            } else {
                cur_obj_spawn_loot_coin_at_mario_pos();
                o->oSubAction = WHOMP_SUB_ACT_GROUND_PREPARE_STAND_UP;
            }
        }
    } else if (!cur_obj_is_mario_on_platform()) {
        o->oSubAction = WHOMP_SUB_ACT_GROUND_LYING_DOWN;
    }
}

void whomp_on_ground_general(void) {
    if (o->oSubAction != WHOMP_SUB_ACT_GROUND_STAND_UP) {
        o->oForwardVel    = 0.0f;
        o->oAngleVelPitch = 0x0;
        o->oAngleVelYaw   = 0x0;
        o->oAngleVelRoll  = 0x0;

        if (o->oBehParams2ndByte != WHOMP_BP_NORMAL) {
            king_whomp_on_ground();
        } else {
            whomp_on_ground();
        }
        if (o->oTimer > 100 || (gMarioState->action == ACT_SQUISHED && o->oTimer > 30)) o->oSubAction = WHOMP_SUB_ACT_GROUND_STAND_UP;
    } else {
        if (o->oFaceAnglePitch > 0x0) {
            o->oAngleVelPitch = -0x200;
            o->oFaceAnglePitch += o->oAngleVelPitch;
        } else {
            o->oAngleVelPitch  = 0x0;
            o->oFaceAnglePitch = 0x0;
            if (o->oBehParams2ndByte != WHOMP_BP_NORMAL) {
                o->oAction = WHOMP_ACT_KING_CHASE;
            } else {
                o->oAction = WHOMP_ACT_PATROL;
            }
        }
    }
}

void whomp_die(void) {
    if (o->oBehParams2ndByte != WHOMP_BP_NORMAL) {
        if (cur_obj_update_dialog_with_cutscene(MARIO_DIALOG_LOOK_UP, 
            DIALOG_FLAG_TEXT_DEFAULT, CUTSCENE_DIALOG, DIALOG_115)) {
            obj_set_angle(o, 0x0, 0x0, 0x0);
            cur_obj_hide();
            cur_obj_become_intangible();
            spawn_mist_particles_variable(0, 0, 200.0f);
            spawn_triangle_break_particles(20, MODEL_DIRT_ANIMATION, 3.0f, 4);
            cur_obj_shake_screen(SHAKE_POS_SMALL);
            o->oPosY += 100.0f;
            spawn_default_star(180.0f, 3880.0f, 340.0f);
            cur_obj_play_sound_2(SOUND_OBJ_KING_WHOMP_DEATH);
            o->oAction = WHOMP_ACT_STOP_MUSIC;
        }
    } else {
        spawn_mist_particles_variable(0, 0, 100.0f);
        spawn_triangle_break_particles(20, MODEL_DIRT_ANIMATION, 3.0f, 4);
        cur_obj_shake_screen(SHAKE_POS_SMALL);
        create_sound_spawner(SOUND_OBJ_THWOMP);
        obj_mark_for_deletion(o);
    }
}

void king_whomp_stop_music(void) {
    if (o->oTimer == 60) stop_background_music(SEQUENCE_ARGS(4, SEQ_EVENT_BOSS));
}

void (*sWhompActions[])(void) = {
    whomp_init,
    whomp_patrol,
    king_whomp_chase,
    whomp_prepare_jump,
    whomp_jump,
    whomp_land,
    whomp_on_ground_general,
    whomp_turn,
    whomp_die,
    king_whomp_stop_music
};

// MM
void bhv_whomp_loop(void) {
    cur_obj_update_floor_and_walls();
    cur_obj_call_action_function(sWhompActions);
    cur_obj_move_standard(-20);
    if (o->oAction != WHOMP_ACT_STOP_MUSIC) {
        cur_obj_hide_if_mario_far_away_y((o->oBehParams2ndByte != WHOMP_BP_NORMAL) ? 2000.0f : 1000.0f);
        load_object_collision_model();
    }
}
