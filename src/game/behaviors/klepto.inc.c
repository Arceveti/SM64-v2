static struct ObjectHitbox sKleptoHitbox = {
    /* interactType:      */ INTERACT_HIT_FROM_BELOW,
    /* downOffset:        */   0,
    /* damageOrCoinValue: */   0,
    /* health:            */   1,
    /* numLootCoins:      */   0,
    /* radius:            */ 160,
    /* height:            */ 250,
    /* hurtboxRadius:     */  80,
    /* hurtboxHeight:     */ 200,
};

static Vec3f sKleptoTargetPositions[] = {
    {  2200.0f, 1250.0f, -2820.0f },
    { -6200.0f, 1250.0f, -2800.0f },
    { -6200.0f, 1250.0f,  1150.0f },
};

static u8 sKleptoAttackHandlers[] = { 2, 2, 5, 5, 2, 2 };

static void klepto_target_mario(void) {
    o->oKleptoDistanceToTarget = lateral_dist_between_objects(gMarioObject, o);
    o->oKleptoPitchToTarget    = cur_obj_turn_pitch_toward_mario(250.0f, 0x0);
    o->oKleptoYawToTarget      = o->oAngleToMario;
    o->oKleptoDiveTimer        = -60;
}

static Bool32 klepto_set_and_check_if_anim_at_end(void) {
    if (o->oSoundStateID == KLEPTO_ANIM_DIVE_FLAP_6) {
        cur_obj_set_anim_if_at_end(KLEPTO_ANIM_DIVE_FLAP_5);
    } else if (o->oSoundStateID == KLEPTO_ANIM_DIVE_FLAP_5) {
        if (cur_obj_set_anim_if_at_end(KLEPTO_ANIM_DIVE_0)) {
            cur_obj_play_sound_2(SOUND_GENERAL_WING_FLAP);
            o->header.gfx.animInfo.animFrame = 9;
        }
    } else {
        if (cur_obj_check_anim_frame(9)) cur_obj_play_sound_2(SOUND_GENERAL_WING_FLAP);
        return TRUE;
    }
    return FALSE;
}

static void klepto_anim_dive(void) {
    if (o->oKleptoDiveTimer > 0) {
        if (o->oKleptoPitchToTarget < -400) {
            o->oKleptoDiveTimer = 0;
        } else {
            if (o->oSoundStateID == KLEPTO_ANIM_DIVE_0) {
                if (cur_obj_check_anim_frame(9)) {
                    cur_obj_play_sound_2(SOUND_GENERAL_WING_FLAP);
                    cur_obj_init_animation_with_sound(KLEPTO_ANIM_DIVE_FLAP_6);
                }
            } else if (--o->oKleptoDiveTimer == 0) {
                o->oKleptoDiveTimer = -random_linear_offset(60, 60);
            }
            cur_obj_move_pitch_approach(400, 10);
        }
    } else {
        cur_obj_move_pitch_approach(o->oKleptoPitchToTarget, 600);
        if (klepto_set_and_check_if_anim_at_end()) {
            if (o->oKleptoDiveTimer != 0) {
                o->oKleptoDiveTimer++;
            } else if (o->oKleptoPitchToTarget > -100) {
                o->oKleptoDiveTimer = random_linear_offset(60, 60);
            }
        }
    }
    cur_obj_face_pitch_approach(0, 1000);
}

void bhv_klepto_init(void) {
    if (o->oBehParams2ndByte != KLEPTO_BP_NO_STAR) {
#ifdef HELD_TRANSPARENT_STAR
        if (save_file_get_star_flags((gCurrSaveFileNum - 1), (COURSE_SSL - 1)) & 0x1) {
            o->oAnimState = KLEPTO_ANIM_STATE_HOLDING_TRANSPARENT_STAR;
        } else {
            o->oAnimState = KLEPTO_ANIM_STATE_HOLDING_STAR;
        }
#else
        o->oAnimState = KLEPTO_ANIM_STATE_HOLDING_STAR;
#endif
#ifdef PUPPYLIGHTS
        //! down offset?
        set_light_properties(&o->puppylight, o->oPosX, o->oPosY, o->oPosZ, PUPPYLIGHTS_STAR_LIGHT, PUPPYLIGHTS_STAR_LIGHT, PUPPYLIGHTS_STAR_LIGHT, 0x0, 0, COLOR_RGBA32_STAR_LIGHT, (PUPPYLIGHT_SHAPE_CYLINDER | PUPPYLIGHT_DIRECTIONAL), TRUE);
        cur_obj_enable_light();
#endif
    } else {
        vec3_copy(&o->oKleptoStartPosVec, &o->oPosVec);
        if (save_file_get_flags() & SAVE_FLAG_CAP_ON_KLEPTO) {
            o->oAnimState = KLEPTO_ANIM_STATE_HOLDING_CAP;
        } else {
            o->oAction = KLEPTO_ACT_WAIT_FOR_MARIO;
        }
    }
}

static void klepto_change_target(void) {
    s32 newTarget = 0;
    s32 i;
    f32 dx, dz;
    f32 sqTargetDist, minTargetDist;
    if (o->oDistanceToMario > 2000.0f) {
        minTargetDist = F32_MAX;
        for ((i = 0); (i < 3); (i++)) {
            dx = (gMarioObject->oPosX - sKleptoTargetPositions[i][0]);
            dz = (gMarioObject->oPosZ - sKleptoTargetPositions[i][2]);
            sqTargetDist = (sqr(dx) + sqr(dz));
            if (sqTargetDist < minTargetDist) {
                minTargetDist = sqTargetDist;
                newTarget     = i;
            }
        }
    } else {
        newTarget = (random_u16() % 0x3);
    }
    o->oKleptoHomeYOffset           = (400 * absi(newTarget - o->oKleptoTargetNumber));
    o->oKleptoTargetNumber          = newTarget;
    vec3_copy_y_off(&o->oHomeVec, sKleptoTargetPositions[o->oKleptoTargetNumber], o->oKleptoHomeYOffset);
    o->oKleptoHalfLateralDistToHome = (cur_obj_lateral_dist_to_home() / 2);
}

static void klepto_circle_target(f32 radius, f32 targetSpeed) {
    Angle turnAmount;
    f32 accel;
    if (o->oAnimState != KLEPTO_ANIM_STATE_HOLDING_NOTHING
     && (((o->oTimer > 60) && (o->oDistanceToMario > 2000.0f)) || (o->oTimer >= o->oKleptoTimeUntilTargetChange))) {
        klepto_change_target();
        o->oKleptoTimeUntilTargetChange = random_linear_offset(300, 300);
        o->oAction                      = KLEPTO_ACT_APPROACH_TARGET_HOLDING;
    } else {
        turnAmount = (DEG(90) - atan2s(radius, o->oKleptoDistanceToTarget - radius));
        accel      = 0.05f;
        if ((Angle)(o->oMoveAngleYaw - o->oKleptoYawToTarget) < 0) turnAmount = -turnAmount;
        o->oKleptoYawToTarget += turnAmount;
        klepto_anim_dive();
        turnAmount = (abs_angle_diff(o->oKleptoYawToTarget, o->oMoveAngleYaw) * (0.03f * o->oKleptoSpeed));
        clamp_s16(&turnAmount, 400, 700);
        cur_obj_rotate_yaw_and_bounce_off_walls(o->oKleptoYawToTarget, turnAmount);
        if (o->oKleptoSpeed > 50.0f) accel = 2.0f;
        approach_f32_ptr(&o->oKleptoSpeed, targetSpeed, accel);
    }
}

static void klepto_approach_target(f32 targetSpeed) {
    if (o->oKleptoDistanceToTarget < 1800.0f) {
        o->oAction = KLEPTO_ACT_CIRCLE_TARGET_HOLDING;
    } else {
        if ((o->oKleptoHalfLateralDistToHome > 0.0f) && ((o->oKleptoHalfLateralDistToHome -= o->oForwardVel) <= 0.0f)) o->oHomeY -= o->oKleptoHomeYOffset;
        klepto_anim_dive();
        cur_obj_rotate_yaw_and_bounce_off_walls(o->oKleptoYawToTarget, 400);
        approach_f32_ptr(&o->oKleptoSpeed, targetSpeed, 0.05f);
    }
}

static void klepto_act_wait_for_mario(void) {
    if (o->oKleptoDistanceToTarget < 1000.0f) {
        klepto_target_mario();
        if (o->oKleptoDistanceToTarget < 1000.0f) {
            o->oAction = KLEPTO_ACT_TURN_TOWARD_MARIO;
            o->oFlags &= ~OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW;
        }
    }
    klepto_circle_target(300.0f, 40.0f);
}

static void klepto_act_turn_toward_mario(void) {
    klepto_target_mario();
    if (klepto_set_and_check_if_anim_at_end()
     && cur_obj_check_if_at_animation_end()
     && (o->oKleptoDistanceToTarget > 800.0f)
     && (abs_angle_diff(o->oAngleToMario, o->oFaceAngleYaw) < 0x800)
     && (o->oKleptoPitchToTarget < 0x400)) {
        cur_obj_play_sound_2(SOUND_OBJ_KLEPTO_TURN);
        o->oAction       = KLEPTO_ACT_DIVE_AT_MARIO;
        o->oMoveAngleYaw = o->oFaceAngleYaw;
        o->oFlags       |= OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW;
        cur_obj_init_animation_with_sound(KLEPTO_ANIM_DIVE_AT_MARIO_3);
    }
    klepto_circle_target(1000.0f, 40.0f);
    cur_obj_face_yaw_approach(o->oAngleToMario, 1000);
}

static void klepto_act_dive_at_mario(void) {
    approach_f32_ptr(&o->oKleptoSpeed, 60.0f, 10.0f);
    if (o->oSoundStateID == KLEPTO_ANIM_DIVE_AT_MARIO_2) {
        if (cur_obj_check_anim_frame(11)) cur_obj_play_sound_2(SOUND_GENERAL_WING_FLAP);
        if (cur_obj_set_anim_if_at_end(KLEPTO_ANIM_DIVE_0)) {
            if (o->oAnimState != KLEPTO_ANIM_STATE_HOLDING_NOTHING) {
                o->oAction = KLEPTO_ACT_CIRCLE_TARGET_HOLDING;
                o->oKleptoTimeUntilTargetChange = 0;
            } else {
                o->oAction = KLEPTO_ACT_WAIT_FOR_MARIO;
            }
        }
    } else {
        f32 dy = (o->oPosY - gMarioObject->oPosY);
        if (o->oSoundStateID == KLEPTO_ANIM_DIVE_AT_MARIO_3) {
            cur_obj_set_anim_if_at_end(KLEPTO_ANIM_DIVE_AT_MARIO_4);
        } else if ((o->oVelY > 0.0f) && (dy > 200.0f)) {
            cur_obj_init_animation_with_sound(KLEPTO_ANIM_DIVE_AT_MARIO_2);
        }
        o->oKleptoPitchToTarget = -0x3000;
        if (o->oAnimState == KLEPTO_ANIM_STATE_HOLDING_NOTHING) {
            if (o->oSubAction == KLEPTO_SUB_ACT_DIVE_TURN_PITCH) {
                o->oKleptoPitchToTarget = cur_obj_turn_pitch_toward_mario(0.0f, 0x0);
                o->oKleptoYawToTarget   = o->oAngleToMario;
                if (dy < 160.0f) o->oSubAction = KLEPTO_SUB_ACT_DIVE_STOP;
            }
            if ((gMarioStates[0].action != ACT_SLEEPING)
                && !(gMarioStates[0].action & (ACT_FLAG_SHORT_HITBOX | ACT_FLAG_BUTT_OR_STOMACH_SLIDE))
                && (o->oDistanceToMario < 200.0f) && (dy > 50.0f) && (dy < 90.0f)) {
                if (mario_lose_cap_to_enemy(1)) o->oAnimState = KLEPTO_ANIM_STATE_HOLDING_CAP;
            }
        }
    }
    cur_obj_move_pitch_approach(            o->oKleptoPitchToTarget, 0x258); // 600
    cur_obj_face_pitch_approach(            o->oMoveAnglePitch,      0x258);
    cur_obj_rotate_yaw_and_bounce_off_walls(o->oKleptoYawToTarget,   0x258);
}

static void klepto_act_struck_by_mario(void) {
    cur_obj_init_animation_with_sound(KLEPTO_ANIM_STRUCK_BY_MARIO);
    cur_obj_face_pitch_approach(                        0x0, 800);
    cur_obj_face_yaw_approach((o->oMoveAngleYaw + DEG(180)), 800);
    cur_obj_face_roll_approach(                         0x0, 800);
    if (cur_obj_check_if_near_animation_end()) {
        o->oAction         = KLEPTO_ACT_RETREAT;
        o->oGravity        = 0.0f;
        o->oMoveAnglePitch = -cur_obj_get_pitch_from_vel();
        o->oKleptoSpeed    = sqrtf(sqr(o->oForwardVel) + sqr(o->oVelY));
        vec3_copy_y_off(&o->oHomeVec, &o->oPosVec, 500.0f);
    }
}

static void klepto_act_retreat(void) {
    cur_obj_init_animation_with_sound(KLEPTO_ANIM_DIVE_0);
    approach_f32_ptr(&o->oKleptoSpeed, 40.0f, 10.0f);
    cur_obj_move_pitch_approach(o->oKleptoPitchToTarget, 1000);
    cur_obj_face_pitch_approach(o->oMoveAnglePitch, 1000);
    cur_obj_rotate_yaw_and_bounce_off_walls(o->oKleptoYawToTarget, 600);
    if (cur_obj_face_yaw_approach(o->oMoveAngleYaw, 1000) && abs_angle_diff(o->oFaceAnglePitch, o->oMoveAnglePitch) == 0x0) {
        o->oAction          = KLEPTO_ACT_RESET_POSITION;
        o->oHomeY           = 1500.0f;
        o->oKleptoDiveTimer = -100;
        o->oFlags          |= OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW;
        cur_obj_become_tangible();
    }
}

static void klepto_act_reset_position(void) {
    if (o->oTimer < 300) {
        klepto_circle_target(300.0f, 20.0f);
    } else if (o->oBehParams2ndByte != KLEPTO_BP_NO_STAR) {
        vec3_set(&o->oHomeVec, -2000.0f, 9999.0f, -1000.0f);
        o->oKleptoDistanceToTarget = o->oHomeY;
        if (o->oPosY > 5000.0f) {
            obj_mark_for_deletion(o);
        } else {
            klepto_approach_target(20.0f);
        }
    } else {
        o->oAction = KLEPTO_ACT_WAIT_FOR_MARIO;
        vec3_copy(&o->oHomeVec, &o->oKleptoStartPosVec);
    }
}

void obj_set_speed_to_zero(void) {
    o->oForwardVel = o->oVelY = 0.0f;
}

void bhv_klepto_update(void) {
    cur_obj_update_floor_and_walls();
    o->oKleptoDistanceToTarget = cur_obj_lateral_dist_to_home();
    o->oKleptoPitchToTarget    = cur_obj_get_pitch_to_home(o->oKleptoDistanceToTarget);
    o->oKleptoYawToTarget      = cur_obj_angle_to_home();
    if (o->oAction == KLEPTO_ACT_STRUCK_BY_MARIO) {
        klepto_act_struck_by_mario();
    } else {
        cur_obj_compute_vel_from_move_pitch(o->oKleptoSpeed);
        switch (o->oAction) {
            case KLEPTO_ACT_CIRCLE_TARGET_HOLDING:   klepto_circle_target(300.0f, 40.0f); break;
            case KLEPTO_ACT_APPROACH_TARGET_HOLDING: klepto_approach_target(50.0f);       break;
            case KLEPTO_ACT_WAIT_FOR_MARIO:          klepto_act_wait_for_mario();         break;
            case KLEPTO_ACT_TURN_TOWARD_MARIO:       klepto_act_turn_toward_mario();      break;
            case KLEPTO_ACT_DIVE_AT_MARIO:           klepto_act_dive_at_mario();          break;
            case KLEPTO_ACT_RESET_POSITION:          klepto_act_reset_position();         break;
            case KLEPTO_ACT_RETREAT:                 klepto_act_retreat();                break;
        }
        if (cur_obj_handle_attacks(&sKleptoHitbox, o->oAction, sKleptoAttackHandlers)) {
            cur_obj_play_sound_2(SOUND_OBJ_KLEPTO_ATTACKED);
            if (o->oAnimState == KLEPTO_ANIM_STATE_HOLDING_CAP) {
                save_file_clear_flags(SAVE_FLAG_CAP_ON_KLEPTO);
                spawn_object(o, MODEL_MARIOS_CAP, bhvNormalCap);
            } else if ((o->oAnimState == KLEPTO_ANIM_STATE_HOLDING_STAR) || (o->oAnimState == KLEPTO_ANIM_STATE_HOLDING_TRANSPARENT_STAR)) {
#ifdef PUPPYLIGHTS
                cur_obj_disable_light();
#endif
                spawn_default_star(-5550.0f, 300.0f, -930.0f);
            }
            o->oAnimState    = KLEPTO_ANIM_STATE_HOLDING_NOTHING;
            o->oAction       = KLEPTO_ACT_STRUCK_BY_MARIO;
            o->oGravity      = -2.0f;
            o->oMoveAngleYaw = (o->oAngleToMario + DEG(180));
            o->oFlags &= ~OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW;
            cur_obj_become_intangible();
        } else if ((gMarioStates[0].action == ACT_SLEEPING) || (gMarioStates[0].action & (ACT_FLAG_SHORT_HITBOX | ACT_FLAG_BUTT_OR_STOMACH_SLIDE))) {
            cur_obj_become_intangible();
        } else {
            cur_obj_become_tangible();
        }
    }
    cur_obj_roll_to_match_yaw_turn(o->oKleptoYawToTarget, 0x3000, 600);
    cur_obj_move_standard(78);
}
