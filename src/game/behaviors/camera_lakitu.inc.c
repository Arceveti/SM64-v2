
/**
 * Behavior for bhvCameraLakitu. This includes both the intro lakitu and the
 * lakitu visible in the mirror room.
 * TODO: Processing order relative to bhvCloud
 */

/**
 * Init function for camera lakitu.
 * If this is the intro lakitu, despawn unless this is the start of the game.
 * Spawn cloud if not the intro lakitu.
 */
void bhv_camera_lakitu_init(void) {
    if (o->oBehParams2ndByte != CAMERA_LAKITU_BP_FOLLOW_CAMERA) {
        // Despawn unless this is the very beginning of the game
        if (!gNeverEnteredCastle) obj_mark_for_deletion(o);
    } else {
        spawn_object_relative_with_scale(CLOUD_BP_LAKITU_CLOUD, 0, 0, 0, 2.0f, o, MODEL_MIST, bhvCloud);
    }
}

/**
 * Wait for Mario to stand on the bridge, then interrupt his action and enter
 * the spawn cloud action.
 */
static void camera_lakitu_intro_act_trigger_cutscene(void) {
#ifdef FIX_LAKITU_SKIP
    if (gMarioObject->oPosX >  -544.0f && gMarioObject->oPosX <  544.0f && gMarioObject->oPosY > 800.0f
     && gMarioObject->oPosZ > -2000.0f && gMarioObject->oPosZ < -177.0f) {
#else
    // These bounds are slightly smaller than the actual bridge bounds, allowing
    // the RTA speedrunning method of lakitu skip
    if (gMarioObject->oPosX > -544.0f && gMarioObject->oPosX < 545.0f && gMarioObject->oPosY > 800.0f
        && gMarioObject->oPosZ > -2000.0f && gMarioObject->oPosZ < -177.0f) {
#endif
        if (set_mario_npc_dialog(MARIO_DIALOG_LOOK_UP) == MARIO_DIALOG_STATUS_START) o->oAction = CAMERA_LAKITU_INTRO_ACT_SPAWN_CLOUD;
    }
}

/**
 * Warp up into the air and spawn cloud, then enter the TODO action.
 */
static void camera_lakitu_intro_act_spawn_cloud(void) {
    if (set_mario_npc_dialog(MARIO_DIALOG_LOOK_UP) == MARIO_DIALOG_STATUS_SPEAK) {
        o->oAction                   = CAMERA_LAKITU_INTRO_ACT_SHOW_DIALOG;
        vec3f_set(&o->oPosVec, 1800.0f, 2400.0f, -2400.0f);
        o->oMoveAnglePitch           =  DEG(90);
        o->oCameraLakituSpeed        =   60.0f;
        o->oCameraLakituCircleRadius = 1000.0f;
        spawn_object_relative_with_scale(CLOUD_BP_LAKITU_CLOUD, 0, 0, 0, 2.0f, o, MODEL_MIST, bhvCloud);
    }
}

/**
 * Circle down to Mario, show the dialog, then fly away.
 */
static void camera_lakitu_intro_act_show_dialog(void) {
    Angle targetMovePitch = 0x0;
    Angle targetMoveYaw   = 0x0;
    cur_obj_play_sound_1(SOUND_AIR_LAKITU_FLY);
    // Face toward Mario
    o->oFaceAnglePitch  = obj_turn_pitch_toward_mario(120.0f, 0x0);
    o->oFaceAngleYaw    = o->oAngleToMario;
    // After finishing dialog, fly away and despawn
    if (o->oCameraLakituFinishedDialog) {
        approach_f32_bool(&o->oCameraLakituSpeed, 60.0f, 3.0f);
        if (o->oDistanceToMario > 6000.0f) obj_mark_for_deletion(o);
        targetMovePitch = -0x3000; // 67.5 degrees
        targetMoveYaw   = -0x6000; // 135 degrees
    } else {
        if (o->oCameraLakituSpeed != 0.0f) {
            if (o->oDistanceToMario > 5000.0f) {
                targetMovePitch = o->oMoveAnglePitch;
                targetMoveYaw   = o->oAngleToMario;
            } else {
                // Stay moving in a circle around Mario
                Angle turnAmount = (DEG(90) - atan2s(o->oCameraLakituCircleRadius, o->oDistanceToMario - o->oCameraLakituCircleRadius));
                if ((Angle)(o->oMoveAngleYaw - o->oAngleToMario) < 0x0) turnAmount = -turnAmount;
                targetMoveYaw   = (o->oAngleToMario + turnAmount);
                targetMovePitch = o->oFaceAnglePitch;
                approach_f32_bool(&o->oCameraLakituCircleRadius, 200.0f, 50.0f);
                if (o->oDistanceToMario < 1000.0f) {
                    if (!o->oCameraLakituIntroMusicPlayed) {
                        play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(15, SEQ_EVENT_CUTSCENE_LAKITU), 0);
                        o->oCameraLakituIntroMusicPlayed = TRUE;
                    }
                    // Once within 1000 units, slow down
                    approach_f32_bool(&o->oCameraLakituSpeed, 20.0f, 1.0f);
                    if ((o->oDistanceToMario < 500.0f) && (abs_angle_diff(gMarioObject->oFaceAngleYaw, o->oFaceAngleYaw) > 0x7000)) {
                        // Once within 500 units and facing toward Mario, come
                        // to a stop
                        approach_f32_bool(&o->oCameraLakituSpeed, 0.0f, 5.0f);
                    }
                }
            }
        } else if (cur_obj_update_dialog_with_cutscene(MARIO_DIALOG_LOOK_UP, 
            DIALOG_FLAG_TURN_TO_MARIO, CUTSCENE_DIALOG, DIALOG_034)) {
            o->oCameraLakituFinishedDialog = TRUE;
        }
    }
    o->oCameraLakituPitchVel = approach_s16_symmetric(o->oCameraLakituPitchVel, 0x7D0, 0x190);
    obj_move_pitch_approach(targetMovePitch, o->oCameraLakituPitchVel);
    o->oCameraLakituYawVel   = approach_s16_symmetric(o->oCameraLakituYawVel, 0x7D0, 0x64);
    cur_obj_rotate_yaw_toward(targetMoveYaw, o->oCameraLakituYawVel);
    // vel y is explicitly computed, so gravity doesn't apply
    obj_compute_vel_from_move_pitch(o->oCameraLakituSpeed);
    cur_obj_move_using_fvel_and_gravity();
}

/**
 * Update function for camera lakitu.
 */
void bhv_camera_lakitu_update(void) {
    if (!(o->activeFlags & ACTIVE_FLAG_IN_DIFFERENT_ROOM)) {
        obj_update_blinking(&o->oCameraLakituBlinkTimer, 20, 40, 4);
        if (o->oBehParams2ndByte != CAMERA_LAKITU_BP_FOLLOW_CAMERA) {
            switch (o->oAction) {
                case CAMERA_LAKITU_INTRO_ACT_TRIGGER_CUTSCENE: camera_lakitu_intro_act_trigger_cutscene(); break;
                case CAMERA_LAKITU_INTRO_ACT_SPAWN_CLOUD:      camera_lakitu_intro_act_spawn_cloud();      break;
                case CAMERA_LAKITU_INTRO_ACT_SHOW_DIALOG:      camera_lakitu_intro_act_show_dialog();      break;
            }
        } else {
            f32 val0C = (((f32) 0x875C3D / 0x800) - gLakituState.curPos[0]); //! name?
            if ((gLakituState.curPos[0] < 1700.0f) || (val0C < 0.0f)) {
                cur_obj_hide();
            } else {
                cur_obj_unhide();
                vec3f_copy(&o->oPosVec, gLakituState.curPos);
                o->oHomeX          = gLakituState.curFocus[0];
                o->oHomeZ          = gLakituState.curFocus[2];
                o->oFaceAngleYaw   = -cur_obj_angle_to_home();
                o->oFaceAnglePitch = atan2s(cur_obj_lateral_dist_to_home(), o->oPosY - gLakituState.curFocus[1]);
                o->oPosX           = (((f32) 0x875C3D / 0x800) + val0C);
            }
        }
    }
}
