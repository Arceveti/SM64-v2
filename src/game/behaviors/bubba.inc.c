// bubba.inc.c

static struct ObjectHitbox sBubbaHitbox = {
    /* interactType:      */ INTERACT_CLAM_OR_BUBBA,
    /* downOffset:        */   0,
    /* damageOrCoinValue: */   1,
    /* health:            */  99,
    /* numLootCoins:      */   0,
    /* radius:            */ 300,
    /* height:            */ 200,
    /* hurtboxRadius:     */ 300,
    /* hurtboxHeight:     */ 200,
};

void bubba_act_idle(void) {
    f32 lateralDistToHome = cur_obj_lateral_dist_to_home();
    cur_obj_treat_far_home_as_mario(2000.0f);
    o->oAnimState        = BUBBA_ANIM_STATE_CLOSED_MOUTH;
    o->oBubbaTargetPitch = cur_obj_get_pitch_to_home(lateralDistToHome);
    approach_f32_ptr(&o->oBubbaMovePitch, 5.0f, 0.5f);
    if (o->oBubbaHitWall != 0) {
        if (abs_angle_diff(o->oMoveAngleYaw, o->oBubbaTargetYaw) < 800) o->oBubbaHitWall = 0;
    } else {
        if (o->oDistanceToMario >= 25000.0f) {
            o->oBubbaTargetYaw   = o->oAngleToMario;
            o->oBubbaRandomTimer = random_linear_offset(20, 30);
        }
        if ((o->oBubbaHitWall = (o->oMoveFlags & OBJ_MOVE_HIT_WALL)) != 0) {
            o->oBubbaTargetYaw = cur_obj_reflect_move_angle_off_wall();
        } else if ((o->oTimer > 30) && (o->oDistanceToMario < 2000.0f)) {
            o->oAction = BUBBA_ACT_ATTACK;
        } else if (o->oBubbaRandomTimer != 0) {
            o->oBubbaRandomTimer--;
        } else {
            o->oBubbaTargetYaw   = cur_obj_random_fixed_turn(DEG(45));
            o->oBubbaRandomTimer = random_linear_offset(100, 100);
        }
    }
}

void bubba_act_attack(void) {
    cur_obj_treat_far_home_as_mario(2500.0f);
    if (o->oDistanceToMario > 2500.0f) {
        o->oAction = BUBBA_ACT_IDLE;
    } else if (o->oBubbaLungeTimer != 0) {
        if (--o->oBubbaLungeTimer == 0) {
            cur_obj_play_sound_2(SOUND_OBJ_BUBBA_CHOMP);
            o->oAction = BUBBA_ACT_IDLE;
        } else if (o->oBubbaLungeTimer < 15) {
            o->oAnimState = BUBBA_ANIM_STATE_OPEN_MOUTH;
        } else if (o->oBubbaLungeTimer == 20) {
            Angle targetPitch = (10000 - (Angle)(20.0f * (find_water_level(o->oPosX, o->oPosZ) - o->oPosY)));
            o->oBubbaTargetPitch -= targetPitch;
            o->oMoveAnglePitch    = o->oBubbaTargetPitch;
            o->oBubbaMovePitch    = 40.0f;
            cur_obj_compute_vel_from_move_pitch(o->oBubbaMovePitch);
            o->oAnimState         = BUBBA_ANIM_STATE_CLOSED_MOUTH;
        } else {
            o->oBubbaTargetYaw    = o->oAngleToMario;
            o->oBubbaTargetPitch  = o->oBubbaNextTargetPitchTowardMario;
            cur_obj_rotate_yaw_toward(o->oBubbaTargetYaw, 0x190);
            cur_obj_move_pitch_approach(o->oBubbaTargetPitch, 0x190);
        }
    } else {
        if (abs_angle_diff(gMarioObject->oFaceAngleYaw, o->oAngleToMario) < DEG(67.5)) {
            Angle targetDYaw = (DEG(90) - atan2s(800.0f, (o->oDistanceToMario - 800.0f)));
            if ((Angle)(o->oMoveAngleYaw - o->oAngleToMario) < 0x0) targetDYaw = -targetDYaw;
            o->oBubbaTargetYaw = (o->oAngleToMario + targetDYaw);
        } else {
            o->oBubbaTargetYaw = o->oAngleToMario;
        }
        o->oBubbaTargetPitch = o->oBubbaNextTargetPitchTowardMario;
        if (cur_obj_is_near_to_and_facing_mario(500.0f, 3000)
            && abs_angle_diff(o->oBubbaTargetPitch, o->oMoveAnglePitch) < 3000) {
            o->oBubbaLungeTimer = 30;
            o->oBubbaMovePitch  = 0x0;
            o->oAnimState = BUBBA_ANIM_STATE_OPEN_MOUTH;
        } else {
            approach_f32_ptr(&o->oBubbaMovePitch, 20.0f, 0.5f);
        }
    }
}

void bhv_bubba_loop(void) {
    o->oInteractionSubtype &= ~INT_SUBTYPE_EATS_MARIO;
    o->oBubbaNextTargetPitchTowardMario = cur_obj_turn_pitch_toward_mario(120.0f, 0);
    if ((abs_angle_diff(o->oAngleToMario, o->oMoveAngleYaw) < DEG(22.5))
        && (abs_angle_diff((o->oBubbaNextTargetPitchTowardMario + DEG(11.25)), o->oMoveAnglePitch) < DEG(45))) {
        if ((o->oAnimState != BUBBA_ANIM_STATE_CLOSED_MOUTH) && (o->oDistanceToMario < 250.0f)) o->oInteractionSubtype |= INT_SUBTYPE_EATS_MARIO;
        o->hurtboxRadius = 100.0f;
    } else {
        o->hurtboxRadius = 150.0f;
    }
    cur_obj_update_floor_and_walls();
    switch (o->oAction) {
        case BUBBA_ACT_IDLE:   bubba_act_idle();   break;
        case BUBBA_ACT_ATTACK: bubba_act_attack(); break;
    }
    if (o->oMoveFlags & OBJ_MOVE_MASK_IN_WATER) {
        if (o->oMoveFlags & OBJ_MOVE_ENTERED_WATER) {
            struct Object *splashObj = spawn_object(o, MODEL_WATER_SPLASH, bhvWaterSplash);
            if (splashObj != NULL) obj_scale(splashObj, 3.0f);
            o->oBubbaAirVelY    = o->oVelY;
            o->oBubbaJumpHeight = 0.0f;
        } else {
            approach_f32_ptr(&o->oBubbaAirVelY, 0.0f, 4.0f);
            if ((o->oBubbaJumpHeight -= o->oBubbaAirVelY) > 1.0f) {
                Angle rand            = random_u16();
                o->oBubbaJumpHeight  -= 1.0f;
                spawn_object_relative(OBJ_BP_NONE, (150.0f * coss(rand)), 0x64, (150.0f * sins(rand)), o, MODEL_WHITE_PARTICLE_SMALL, bhvSmallParticleSnow);
            }
        }
        cur_obj_smooth_turn(&o->oBubbaPitchVel, &o->oMoveAnglePitch, o->oBubbaTargetPitch, 0.05f, 10, 50, 2000);
        cur_obj_smooth_turn(&o->oBubbaYawVel,   &o->oMoveAngleYaw,   o->oBubbaTargetYaw,   0.05f, 10, 50, 2000);
        cur_obj_compute_vel_from_move_pitch(o->oBubbaMovePitch);
    } else {
        o->oBubbaMovePitch = sqrtf(sqr(o->oForwardVel) + sqr(o->oVelY));
        o->oMoveAnglePitch = cur_obj_get_pitch_from_vel();
        cur_obj_face_pitch_approach(o->oMoveAnglePitch, 400);
        o->oBubbaPitchVel  = 0x0;
    }
    cur_obj_face_pitch_approach(o->oMoveAnglePitch, 400);
    cur_obj_check_attacks(&sBubbaHitbox, o->oAction);
    cur_obj_move_standard(78);
    o->oFloorHeight += 150.0f;
    if (o->oPosY < o->oFloorHeight) o->oPosY = o->oFloorHeight;
}
