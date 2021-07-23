// unagi.inc.c

struct ObjectHitbox sUnagiHitbox = {
    /* interactType:      */ INTERACT_CLAM_OR_BUBBA,
    /* downOffset:        */ 50,
    /* damageOrCoinValue: */ 3,
    /* health:            */ 99,
    /* numLootCoins:      */ 0,
    /* radius:            */ 150,
    /* height:            */ 150,
    /* hurtboxRadius:     */ 150,
    /* hurtboxHeight:     */ 150,
};

void bhv_unagi_init(void) {
    if (o->oBehParams2ndByte != 1) { // not act 2
        o->oPathedStartWaypoint = segmented_to_virtual(jrb_seg7_trajectory_unagi_ship);
        if (o->oBehParams2ndByte == 0) { // act 1
            o->oFaceAnglePitch = -7600;
        } else {
            o->oAction = UNAGI_SHIP_PATH;
        }
    } else {
        o->oPathedStartWaypoint = segmented_to_virtual(jrb_seg7_trajectory_unagi_cave);
        o->oAction = UNAGI_IN_CAVE;
#ifdef HELD_TRANSPARENT_STAR
        if (save_file_get_star_flags(gCurrSaveFileNum - 1, COURSE_JRB) & 2) {
            o->oAnimState = UNAGI_ANIM_STATE_HAS_TRANSPARENT_STAR;
        } else {
            o->oAnimState = UNAGI_ANIM_STATE_HAS_STAR;
        }
#endif
        o->oUnagiInitMoveYaw = o->oMoveAngleYaw;
    }

    o->oPathedPrevWaypoint = o->oPathedStartWaypoint;
}

void unagi_go_to_start_of_path(void) { // act 0
    if (o->oDistanceToMario > 4500.0f && o->oSubAction != 0) {
        o->oAction = UNAGI_SHIP_PATH;
        o->oPosX = o->oPathedStartWaypoint->pos[0];
        o->oPosY = o->oPathedStartWaypoint->pos[1];
        o->oPosZ = o->oPathedStartWaypoint->pos[2];
    } else if (o->oUnagiDistanceToMario < 700.0f) {
        o->oSubAction = 1;
    }
}

void unagi_follow_path(s32 nextAction) { // act 1 4
    if (o->oSoundStateID == 3) {
        if (cur_obj_check_anim_frame(30)) {
            o->oForwardVel = 40.0f;
        }
    } else {
        if (cur_obj_check_if_at_animation_end()) {
            if (o->oAction != nextAction && (o->oPathedPrevWaypointFlags & 0xFF) >= 7) {
                cur_obj_init_animation_with_sound(3);
            } else {
                cur_obj_init_animation_with_sound(2);
            }
        }
    }

    if (cur_obj_check_anim_frame(6)) {
        cur_obj_play_sound_2(SOUND_GENERAL_MOVING_WATER);
    }

    if (cur_obj_follow_path(0) == -1) {
        o->oAction = nextAction;
    }

    o->oMoveAnglePitch = o->oFaceAnglePitch =
        approach_s16_symmetric(o->oMoveAnglePitch, o->oPathedTargetPitch, 50);

    cur_obj_rotate_yaw_toward(o->oPathedTargetYaw, 120);
    obj_roll_to_match_yaw_turn(o->oPathedTargetYaw, 0x2000, 100);

    obj_forward_vel_approach(10.0f, 0.2f);
    cur_obj_set_pos_via_transform();
}

void unagi_return_to_cave(void) { // act 2
    o->oPathedPrevWaypoint = o->oPathedStartWaypoint;
    o->oPathedPrevWaypointFlags = 0;

    cur_obj_set_pos_to_home();

    o->oMoveAnglePitch = o->oFaceAnglePitch = 0;
    o->oMoveAngleYaw = o->oFaceAngleYaw = o->oUnagiInitMoveYaw;
    o->oFaceAngleRoll = 0;

    o->oForwardVel = o->oVelX = o->oVelZ = o->oUnagiNextForwardVel = 0.0f;

    o->oUnagiDistFromHome = -800.0f;

    o->oAction = UNAGI_IN_CAVE;
}

void unagi_in_cave(void) { // act 3
    if (o->oUnagiDistFromHome < 0.0f) {
        cur_obj_init_animation_with_sound(6);

        if ((o->oUnagiDistFromHome += 10.0f) > 0.0f) {
            o->oUnagiDistFromHome = 0.0f;
        }
    } else {
        if (o->oUnagiDistFromHome == 0.0f) {
            cur_obj_init_animation_with_sound(6);

            if (o->oTimer > 60 && o->oUnagiDistanceToMario < 1000.0f) {
                cur_obj_play_sound_2(SOUND_OBJ_EEL_2);
                o->oUnagiNextForwardVel = o->oUnagiTargetNextForwardVel = 30.0f;
            } else {
                o->oUnagiTargetNextForwardVel = 0.0f;
            }
        } else if (o->oUnagiTargetNextForwardVel > 0.0f) {
            if (cur_obj_init_anim_and_check_if_end(5)) {
                o->oUnagiTargetNextForwardVel = 0.0f;
            }
        } else if (o->oUnagiTargetNextForwardVel == 0.0f) {
            cur_obj_init_animation_with_sound(0);
            if (cur_obj_check_if_at_animation_end()) {
                if (o->oUnagiDistanceToMario < 1000.0f) {
                    o->oAction = UNAGI_CAVE_PATH;
                    o->oForwardVel = o->oUnagiNextForwardVel;
                    cur_obj_init_animation_with_sound(1);
                } else {
                    o->oUnagiTargetNextForwardVel = -50.0f;
                    cur_obj_init_animation_with_sound(4);
                }
            }
        }

        approach_f32_ptr(&o->oUnagiNextForwardVel, o->oUnagiTargetNextForwardVel, 4.0f);

        if ((o->oUnagiDistFromHome += o->oUnagiNextForwardVel) < 0.0f) {
            o->oUnagiDistFromHome = o->oUnagiNextForwardVel = 0.0f;
            o->oTimer = 0;
        }
    }

    o->oPosX = o->oHomeX + o->oUnagiDistFromHome * sins(o->oMoveAngleYaw);
    o->oPosZ = o->oHomeZ + o->oUnagiDistFromHome * coss(o->oMoveAngleYaw);
}

void bhv_unagi_loop(void) {
    s32 i;

    if (!o->oUnagiHasStar) {
        o->oUnagiDistanceToMario = 99999.0f;
        if (o->oDistanceToMario < 3000.0f) {
            for (i = -4; i < 4; i++) {
                spawn_object_relative(i, 0, 0, 0, o, MODEL_NONE, bhvUnagiSubobject);
            }
            o->oUnagiHasStar = TRUE;
        }
    } else if (o->oDistanceToMario > 4000.0f) {
        o->oUnagiHasStar = FALSE;
    }

    switch (o->oAction) {
        case UNAGI_SHIP_RESET_PATH:
            unagi_go_to_start_of_path();
            break;
        case UNAGI_SHIP_PATH:
            unagi_follow_path(o->oAction);
            break;
        case UNAGI_RETURN_TO_CAVE:
            unagi_return_to_cave();
            // fall through
        case UNAGI_IN_CAVE:
            unagi_in_cave();
            break;
        case UNAGI_CAVE_PATH:
            unagi_follow_path(2);
            break;
    }
}

void bhv_unagi_subobject_loop(void) { // unagi star
    f32 val04;

    if (o->parentObj->oUnagiHasStar == 0) {
        obj_mark_for_deletion(o);
    } else {
        val04 = 300.0f * o->oBehParams2ndByte;

        o->oPosY = o->parentObj->oPosY - val04 * sins(o->parentObj->oFaceAnglePitch) * 1.13f;

        val04 = coss(o->parentObj->oFaceAnglePitch / 2) * val04;

        o->oPosX = o->parentObj->oPosX + val04 * sins(o->parentObj->oFaceAngleYaw);
        o->oPosZ = o->parentObj->oPosZ + val04 * coss(o->parentObj->oFaceAngleYaw);

        if (o->oBehParams2ndByte == -4) {
            if (o->parentObj->oAnimState != UNAGI_ANIM_STATE_NO_STAR && o->oDistanceToMario < 150.0f) {
                o->oBehParams = o->parentObj->oBehParams;
                spawn_default_star(6833.0f, -3654.0f, 2230.0f);
                o->parentObj->oAnimState = UNAGI_ANIM_STATE_NO_STAR;
            }
        } else {
            obj_check_attacks(&sUnagiHitbox, o->oAction);
            if (o->oBehParams2ndByte == 3) {
                o->parentObj->oUnagiDistanceToMario = o->oDistanceToMario;
            }
        }
    }
}
