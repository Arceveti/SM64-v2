// boo.c.inc

static struct ObjectHitbox sBooGivingStarHitbox = {
    /* interactType: */        0,
    /* downOffset: */          0,
    /* damageOrCoinValue: */   3,
    /* health: */              3,
    /* numLootCoins: */        0,
    /* radius: */            140,
    /* height: */             80,
    /* hurtboxRadius: */      40,
    /* hurtboxHeight: */      60,
};

// Boo Roll
static Angle sBooHitRotations[] = {
    0x179F,
    0x1620,
    0x14AC,
    0x1346,
    0x11EB,
    0x109E,
    0x0B75,
    0x0E28,
    0x0D01,
    0x0BE6,
    0x0AD7,
    0x09D5,
    0x08DF,
    0x07F7,
    0x071A,
    0x064B,
    0x0588,
    0x04D1,
    0x0427,
    0x038A,
    0x02F9,
    0x0275,
    0x01FD,
    0x0192,
    0x0134,
    0x00E2,
    0x009D,
    0x0064,
    0x0038,
    0x0019,
    0x0004,
    0x0000
};

// Relative positions
static s16 sCourtyardBooTripletPositions[][3] = {
    {   0,  50,    0},
    { 210, 110,  210},
    {-210,  70, -210}
};

static void boo_stop(void) {
    o->oForwardVel = 0.0f;
    o->oVelY       = 0.0f;
    o->oGravity    = 0.0f;
}

void bhv_boo_init(void) {
    o->oBooInitialMoveYaw = o->oMoveAngleYaw;
}

static Bool32 boo_should_be_stopped(void) {
    if (cur_obj_has_behavior(bhvMerryGoRoundBigBoo) || cur_obj_has_behavior(bhvMerryGoRoundBoo)) {
        return (!gMarioOnMerryGoRound);
    } else {
        if (o->activeFlags & ACTIVE_FLAG_IN_DIFFERENT_ROOM) return TRUE;
        if ((o->oRoom == 10) && (gTimeStopState & TIME_STOP_MARIO_OPENED_DOOR)) return TRUE;
    }
    return FALSE;
}

static s32 boo_should_be_active(void) {
    f32 activationRadius = (cur_obj_has_behavior(bhvBalconyBigBoo) ? 5000.0f : 1500.0f);
    if (cur_obj_has_behavior(bhvMerryGoRoundBigBoo) || cur_obj_has_behavior(bhvMerryGoRoundBoo)) {
        return gMarioOnMerryGoRound;
    } else if (o->oRoom == -1) {
        return (o->oDistanceToMario < activationRadius);
    } else if (!boo_should_be_stopped()) {
        return ((o->oDistanceToMario < activationRadius) && ((o->oRoom == gMarioCurrentRoom) || (gMarioCurrentRoom == 0)));
    }
    return FALSE;
}

void bhv_courtyard_boo_triplet_init(void) {
    s32 i;
    struct Object *boo;
#ifndef UNLOCK_ALL
    if (gHudDisplay.stars < 12) {
        obj_mark_for_deletion(o);
    } else {
#endif
        for ((i = 0); (i < 3); (i++)) {
            boo = spawn_object_relative(
                BOO_BP_NORMAL,
                sCourtyardBooTripletPositions[i][0],
                sCourtyardBooTripletPositions[i][1],
                sCourtyardBooTripletPositions[i][2],
                o,
                MODEL_BOO,
                bhvGhostHuntBoo
            );
            boo->oMoveAngleYaw = random_u16();
        }
#ifndef UNLOCK_ALL
    }
#endif
}

static void boo_approach_target_opacity_and_update_scale(void) {
    f32 scale;
    if (o->oBooTargetOpacity != o->oOpacity) {
        if (o->oBooTargetOpacity > o->oOpacity) {
            o->oOpacity += 20;
            if (o->oBooTargetOpacity < o->oOpacity) o->oOpacity = o->oBooTargetOpacity;
        } else {
            o->oOpacity -= 20;
            if (o->oBooTargetOpacity > o->oOpacity) o->oOpacity = o->oBooTargetOpacity;
        }
    }
    scale = ((((o->oOpacity / 255.0f) * 0.4f) + 0.6f) * o->oBooBaseScale);
    cur_obj_scale(scale);
}

static void boo_oscillate(s32 ignoreOpacity) {
    o->oFaceAnglePitch = (sins(o->oBooOscillationTimer) * 0x400);
    if ((o->oOpacity == 0xFF) || ignoreOpacity) {
        o->header.gfx.scale[0]   = (( sins(o->oBooOscillationTimer) * 0.08f) + o->oBooBaseScale);
        o->header.gfx.scale[1]   = ((-sins(o->oBooOscillationTimer) * 0.08f) + o->oBooBaseScale);
        o->header.gfx.scale[2]   =  o->header.gfx.scale[0];
        o->oGravity              =  (sins(o->oBooOscillationTimer) * o->oBooBaseScale);
        o->oBooOscillationTimer += 0x400;
    }
}

static s32 boo_vanish_or_appear(void) {
    Angle relativeAngleToMario           = abs_angle_diff(o->oAngleToMario, o->oMoveAngleYaw);
    Angle relativeMarioFaceAngle         = abs_angle_diff(o->oMoveAngleYaw, gMarioObject->oFaceAngleYaw);
    // magic?
    Angle relativeAngleToMarioThreshhold   = 0x1568; //  5480   DEG(30)?
    Angle relativeMarioFaceAngleThreshhold = 0x6B58; // 27480   DEG(151)?
    Bool32 doneAppearing                   = FALSE;
    o->oVelY                               = 0.0f;
    if ((relativeAngleToMario > relativeAngleToMarioThreshhold)
     || (relativeMarioFaceAngle < relativeMarioFaceAngleThreshhold)) {
        if (o->oOpacity == 40) {
            o->oBooTargetOpacity = 255;
            cur_obj_play_sound_2(SOUND_OBJ_BOO_LAUGH_LONG);
        }
        if (o->oOpacity > 180) doneAppearing = TRUE;
    } else if (o->oOpacity == 255) {
        o->oBooTargetOpacity = 40;
    }
    return doneAppearing;
}

static void boo_set_move_yaw_for_during_hit(s32 hurt) {
    cur_obj_become_intangible();
    o->oFlags              &= ~OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW;
    o->oBooMoveYawBeforeHit = (f32) o->oMoveAngleYaw;
    if (hurt) {
        o->oBooMoveYawDuringHit = gMarioObject->oMoveAngleYaw;
    } else if (coss((Angle)o->oMoveAngleYaw - (Angle)o->oAngleToMario) < 0.0f) {
        o->oBooMoveYawDuringHit = o->oMoveAngleYaw;
    } else {
        o->oBooMoveYawDuringHit = (Angle)(o->oMoveAngleYaw + DEG(180));
    }
}

static void boo_move_during_hit(Bool32 doRoll, f32 fVel) {
    // Boos seem to have been supposed to oscillate up then down then back again
    // when hit. However it seems the programmers forgot to scale the cosine,
    // so the Y velocity goes from 1 to -1 and back to 1 over 32 frames.
    // This is such a small change that the Y position only changes by 5 units.
    // It's completely unnoticable in-game.
    // s32 oscillationVel = ((o->oTimer * 0x800) + 0x800);
    o->oForwardVel     = fVel;
    // o->oVelY           = coss(oscillationVel);
    o->oMoveAngleYaw   = o->oBooMoveYawDuringHit;
    if (doRoll) {
        o->oFaceAngleYaw  += sBooHitRotations[o->oTimer];
        o->oFaceAngleRoll += sBooHitRotations[o->oTimer];
    }
}

static void big_boo_shake_after_hit(void) {
    // Oscillate yaw
    s32 oscillationVel = ((o->oTimer * 0x2000) - 0x3E000);
    o->oFaceAngleYaw += (coss(oscillationVel) * 0x400);
}

static void boo_reset_after_hit(void) {
    o->oMoveAngleYaw   = o->oBooMoveYawBeforeHit;
    o->oFlags         |= OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW;
    o->oInteractStatus = INT_STATUS_NONE;
}

// called iff boo/big boo/cage boo is in action 2, which only occurs if it was non-attack-ly interacted with/bounced on?
static Bool32 boo_update_after_bounced_on(f32 fVel) {
    boo_stop();
    if (o->oTimer == 0) boo_set_move_yaw_for_during_hit(FALSE);
    if (o->oTimer < 32) {
        boo_move_during_hit(FALSE, ((sBooHitRotations[o->oTimer] / 5000.0f) * fVel));
    } else {
        cur_obj_become_tangible();
        boo_reset_after_hit();
        o->oAction = BOO_ACT_CHASING_MARIO;
        return TRUE;
    }
    return FALSE;
}

// called iff big boo nonlethally hit
static Bool32 big_boo_update_during_nonlethal_hit(f32 fVel) {
    boo_stop();
    if (o->oTimer == 0) boo_set_move_yaw_for_during_hit(TRUE);
    if (o->oTimer < 32) {
        boo_move_during_hit(TRUE, (sBooHitRotations[o->oTimer] / 5000.0f) * fVel);
    } else if (o->oTimer < 48) {
        big_boo_shake_after_hit();
    } else {
        cur_obj_become_tangible();
        boo_reset_after_hit();
        o->oAction = BOO_ACT_CHASING_MARIO;
        return TRUE;
    }
    return FALSE;
}

// called every frame once Mario lethally hits the boo until the boo is deleted,
// returns whether death is complete
static Bool32 boo_update_during_death(void) {
    struct Object *parentBigBoo;
    if (o->oTimer == 0) {
        o->oForwardVel     = 40.0f;
        o->oMoveAngleYaw   = gMarioObject->oMoveAngleYaw;
        o->oBooDeathStatus = BOO_DEATH_STATUS_DYING;
        o->oFlags         &= ~OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW;
    } else {
        if (o->oTimer == 5) o->oBooTargetOpacity = 0;
        if ((o->oTimer > 30) || (o->oMoveFlags & OBJ_MOVE_HIT_WALL)) {
            spawn_mist_particles();
            o->oBooDeathStatus = BOO_DEATH_STATUS_DEAD;
            if (o->oBooParentBigBoo != NULL) {
                parentBigBoo = o->oBooParentBigBoo;
                if (!cur_obj_has_behavior(bhvBoo)) parentBigBoo->oBigBooNumMinionBoosKilled++;
            }
            return TRUE;
        }
    }
    o->oVelY           = 5.0f;
    o->oFaceAngleRoll += 0x800;
    o->oFaceAngleYaw  += 0x800;
    return FALSE;
}

static s32 obj_has_attack_type(u32 attackType) {
    return ((o->oInteractStatus & INT_STATUS_ATTACK_MASK) == attackType);
}

static s32 boo_get_attack_status(void) {
    s32 attackStatus = BOO_NOT_ATTACKED;
    if (o->oInteractStatus & INT_STATUS_INTERACTED) {
        if ((o->oInteractStatus & INT_STATUS_WAS_ATTACKED) && !obj_has_attack_type(ATTACK_FROM_ABOVE)) {
            cur_obj_become_intangible();
            o->oInteractStatus = INT_STATUS_NONE;
            cur_obj_play_sound_2(SOUND_OBJ_BOO_LAUGH_SHORT);
            attackStatus       = BOO_ATTACKED;
        } else {
            cur_obj_play_sound_2(SOUND_OBJ_BOO_BOUNCE_TOP);
            o->oInteractStatus = INT_STATUS_NONE;
            attackStatus       = BOO_BOUNCED_ON;
        }
    }
    return attackStatus;
}

// boo idle/chasing movement?
static void boo_chase_mario(f32 minDY, Angle yawIncrement, f32 mul) {
    f32 dy;
    Angle targetYaw;
    if (boo_vanish_or_appear()) {
        o->oInteractType = INTERACT_BOUNCE_TOP;
        targetYaw        = ((cur_obj_lateral_dist_from_mario_to_home_squared() > sqr(1500.0f)) ? cur_obj_angle_to_home() : o->oAngleToMario);
        cur_obj_rotate_yaw_toward(targetYaw, yawIncrement);
        o->oVelY         = 0.0f;
        if (!mario_is_in_air_action()) {
            dy = (o->oPosY - gMarioObject->oPosY);
            if ((minDY < dy) && (dy < 500.0f)) o->oVelY = increment_velocity_toward_range(o->oPosY, (gMarioObject->oPosY + 50.0f), 10.0f, 2.0f);
        }
        cur_obj_set_vel_from_mario_vel((10.0f - o->oBooNegatedAggressiveness), mul);
        if (o->oForwardVel != 0.0f) boo_oscillate(FALSE);
    } else {
        o->oInteractType = INTERACT_NONE;
        boo_stop();
    }
}

static void boo_act_stopped(void) { // act 0
    o->activeFlags |= ACTIVE_FLAG_MOVE_THROUGH_GRATE;
    if (o->oBehParams2ndByte == BOO_BP_MERRY_GO_ROUND) o->oRoom = BBH_NEAR_MERRY_GO_ROUND_ROOM;
    cur_obj_set_pos_to_home();
    o->oMoveAngleYaw = o->oBooInitialMoveYaw;
    boo_stop();
    o->oBooParentBigBoo  = cur_obj_nearest_object_with_behavior(bhvGhostHuntBigBoo);
    o->oBooBaseScale     = 1.0f;
    o->oBooTargetOpacity = 255;
    if (boo_should_be_active()) { // Condition is always met if the object is bhvBalconyBigBoo or bhvMerryGoRoundBoo
        if (o->oBehParams2ndByte == BOO_BP_MERRY_GO_ROUND) {
            o->oBooParentBigBoo = NULL;
            o->oAction = BOO_ACT_MERRY_GO_ROUND_WAIT;
        } else {
            o->oAction = BOO_ACT_CHASING_MARIO;
        }
    }
}

static void boo_act_merry_go_round_wait(void) { // act 5
    if (o->oTimer < 30) {
        o->oVelY             =  0.0f;
        o->oForwardVel       = 13.0f;
        boo_oscillate(FALSE);
        o->oWallHitboxRadius =  0.0f;
    } else {
        o->oAction           = BOO_ACT_CHASING_MARIO;
        o->oWallHitboxRadius = 30.0f;
    }
}

static void boo_act_chasing_mario(void) { // act 1
    s32 attackStatus;
    if (o->oTimer == 0) {
        o->oBooNegatedAggressiveness =      (-random_float() *   5.0f);
        o->oBooTurningSpeed          = (s32)( random_float() * 128.0f);
    }
    boo_chase_mario(-100.0f, o->oBooTurningSpeed + 0x180, 0.5f);
    attackStatus = boo_get_attack_status();
    if (boo_should_be_stopped())        o->oAction = BOO_ACT_STOPPED;
    if (attackStatus == BOO_BOUNCED_ON) o->oAction = BOO_ACT_BOUNCED_ON;
    if (attackStatus == BOO_ATTACKED) {
        o->oAction = BOO_ACT_ATTACKED;
        create_sound_spawner(SOUND_OBJ_DYING_ENEMY1);
    }
}

static void boo_act_bounced_on(void) { // act 2
    if (boo_update_after_bounced_on(20.0f)) o->oAction = BOO_ACT_CHASING_MARIO;
}

static void boo_act_attacked(void) { // act 3
    if (boo_update_during_death()) {
        if (o->oBehParams2ndByte != BOO_BP_GHOST_HUNT) { // normal
            obj_mark_for_deletion(o);
        } else { // ghost hunt
            o->oAction = BOO_ACT_DEATH;
            cur_obj_disable();
        }
    }
}

// Called when a Go on a Ghost Hunt boo dies
static void boo_act_ghost_hunt_dialog(void) { // act 4
    // If there are no remaining "minion" boos, show the dialog of the Big Boo
    DialogID dialogID = ((cur_obj_nearest_object_with_behavior(bhvGhostHuntBoo) == NULL) ? DIALOG_108 : DIALOG_107);
    if (cur_obj_update_dialog(MARIO_DIALOG_LOOK_UP, DIALOG_FLAG_TEXT_DEFAULT, dialogID, 0)) {
        create_sound_spawner(SOUND_OBJ_DYING_ENEMY1);
        obj_mark_for_deletion(o);
        if (dialogID == DIALOG_108) play_puzzle_jingle(); // If the Big Boo should spawn, play the jingle
    }
}

static void (*sBooActions[])(void) = {
    boo_act_stopped,
    boo_act_chasing_mario,
    boo_act_bounced_on,
    boo_act_attacked,
    boo_act_ghost_hunt_dialog,
    boo_act_merry_go_round_wait
};

void bhv_boo_loop(void) {
    // PARTIAL_UPDATE
    cur_obj_update_floor_and_walls();
    cur_obj_call_action_function(sBooActions);
    cur_obj_move_standard(78);
    boo_approach_target_opacity_and_update_scale();
    if (obj_has_behavior(o->parentObj, bhvMerryGoRoundBooManager) && !(o->activeFlags & ACTIVE_FLAG_ACTIVE)) o->parentObj->oMerryGoRoundBooManagerNumBoosKilled++;
    o->oInteractStatus = INT_STATUS_NONE;
}

static void big_boo_act_stopped(void) {
    if (cur_obj_has_behavior(bhvBalconyBigBoo)) {
        gSecondCameraFocus = o;
        // number of killed boos set > 5 so that boo always loads
        //! redundant? this is also done in behavior_data.s
        o->oBigBooNumMinionBoosKilled = 10;
    }
    o->oBooParentBigBoo = NULL;
    if (boo_should_be_active() && ((gDebugInfo[5][0] + 5) <= o->oBigBooNumMinionBoosKilled)) {
        o->oAction = BOO_ACT_CHASING_MARIO;
        cur_obj_set_pos_to_home();
        o->oMoveAngleYaw     = o->oBooInitialMoveYaw;
        cur_obj_unhide();
        o->oBooTargetOpacity = 0xFF;
        o->oBooBaseScale     = 3.0f;
        o->oHealth           = 3;
        cur_obj_scale(3.0f);
        cur_obj_become_tangible();
    } else {
        cur_obj_hide();
        cur_obj_become_intangible();
        boo_stop();
    }
}

static void big_boo_act_chasing_mario(void) { // act 1
    s32 attackStatus;
    Angle yawIncrement;
    f32 mul;
    if (o->oHealth == 3) {
        yawIncrement = 0x180; mul = 0.5f;
    } else if (o->oHealth == 2) {
        yawIncrement = 0x240; mul = 0.6f;
    } else {
        yawIncrement = 0x300; mul = 0.8f;
    }
    boo_chase_mario(-100.0f, yawIncrement, mul);
    attackStatus = boo_get_attack_status();
    //! redundant; this check is in boo_should_be_stopped
    if (cur_obj_has_behavior(bhvMerryGoRoundBigBoo)) {
        if (!gMarioOnMerryGoRound) o->oAction = BOO_ACT_STOPPED;
    } else if (boo_should_be_stopped()) {
        o->oAction = BOO_ACT_STOPPED;
    }
    if (attackStatus == BOO_BOUNCED_ON) o->oAction = BOO_ACT_BOUNCED_ON;
    if (attackStatus == BOO_ATTACKED) {
        o->oAction = BOO_ACT_ATTACKED;
        create_sound_spawner(SOUND_OBJ_THWOMP);
    }
}

static void big_boo_act_bounced_on(void) {
    if (boo_update_after_bounced_on(20.0f)) o->oAction = BOO_ACT_CHASING_MARIO;
}

static void big_boo_spawn_ghost_hunt_star(void) {
    spawn_default_star(980.0f, 1100.0f, 250.0f);
}

static void big_boo_spawn_balcony_star(void) {
    spawn_default_star(700.0f, 3200.0f, 1900.0f);
}

static void big_boo_spawn_merry_go_round_star(void) {
    struct Object *merryGoRound = cur_obj_nearest_object_with_behavior(bhvMerryGoRound);
    spawn_default_star(-1600.0f, -2100.0f, 205.0f);
    if (merryGoRound != NULL) merryGoRound->oMerryGoRoundStopped = TRUE;
}

static void big_boo_act_attacked(void) { // act 3
    if (o->oTimer  == 0) o->oHealth--;
    if (o->oHealth == 0) {
        if (boo_update_during_death()) {
            cur_obj_disable();
            o->oAction = BOO_ACT_DEATH;
            obj_set_angle(o, 0x0, 0x0, 0x0);
            if (o->oBehParams2ndByte == BIG_BOO_BP_GHOST_HUNT) {
                big_boo_spawn_ghost_hunt_star();
            } else if (o->oBehParams2ndByte == BIG_BOO_BP_MERRY_GO_ROUND) {
                big_boo_spawn_merry_go_round_star();
            } else {
                big_boo_spawn_balcony_star();
            }
        }
    } else {
        if (o->oTimer == 0) {
            spawn_mist_particles();
            o->oBooBaseScale -= 0.5f;
        }
        if (big_boo_update_during_nonlethal_hit(40.0f)) o->oAction = BOO_ACT_CHASING_MARIO;
    }
}

static void big_boo_act_4(void) { // act 4
    boo_stop();
    if (o->oBehParams2ndByte == BIG_BOO_BP_GHOST_HUNT) {
        obj_set_pos(o, 973, 0, 626);
        if ((o->oTimer > 60) && (o->oDistanceToMario < 600.0f)) {
            obj_set_pos(o,  973, 0, 717);
            spawn_object_relative(BOO_STAIRCASE_BP_0, 0, 0,    0, o, MODEL_BBH_STAIRCASE_STEP, bhvBooStaircase);
            spawn_object_relative(BOO_STAIRCASE_BP_1, 0, 0, -200, o, MODEL_BBH_STAIRCASE_STEP, bhvBooStaircase);
            spawn_object_relative(BOO_STAIRCASE_BP_2, 0, 0,  200, o, MODEL_BBH_STAIRCASE_STEP, bhvBooStaircase);
            obj_mark_for_deletion(o);
        }
    } else {
        obj_mark_for_deletion(o);
    }
}

static void (*sBooGivingStarActions[])(void) = {
    big_boo_act_stopped,
    big_boo_act_chasing_mario,
    big_boo_act_bounced_on,
    big_boo_act_attacked,
    big_boo_act_4
};

void bhv_big_boo_loop(void) {
    // PARTIAL_UPDATE
    obj_set_hitbox(o, &sBooGivingStarHitbox);
    o->oGraphYOffset = (o->oBooBaseScale * 60.0f);
    cur_obj_update_floor_and_walls();
    cur_obj_call_action_function(sBooGivingStarActions);
    cur_obj_move_standard(78);

    boo_approach_target_opacity_and_update_scale();
    o->oInteractStatus = INT_STATUS_NONE;
}

static void boo_with_cage_act_stopped(void) { // act 0
    o->oBooParentBigBoo  = NULL;
    o->oBooTargetOpacity = 0xFF;
    o->oBooBaseScale     = 2.0f;
    cur_obj_scale(2.0f);
    cur_obj_become_tangible();
    if (boo_should_be_active()) o->oAction = BOO_ACT_CHASING_MARIO;
}

static void boo_with_cage_act_chasing_mario(void) { // act 1
    s32 attackStatus;
    boo_chase_mario(100.0f, 512, 0.5f);
    attackStatus = boo_get_attack_status();
    if (boo_should_be_stopped()       ) o->oAction = BOO_ACT_STOPPED;
    if (attackStatus == BOO_BOUNCED_ON) o->oAction = BOO_ACT_BOUNCED_ON;
    if (attackStatus == BOO_ATTACKED  ) o->oAction = BOO_ACT_ATTACKED;
}

static void boo_with_cage_act_bounced_on(void) {
    if (boo_update_after_bounced_on(20.0f)) {
        o->oAction = BOO_ACT_CHASING_MARIO;
    }
}

static void boo_with_cage_act_attacked(void) { // act 3
    if (boo_update_during_death()) obj_mark_for_deletion(o);
}

void bhv_boo_with_cage_init(void) {
    struct Object* cage;
#ifndef UNLOCK_ALL
    if (gHudDisplay.stars < 12) {
        obj_mark_for_deletion(o);
    } else {
#endif
        cage             = spawn_object(o, MODEL_HAUNTED_CAGE, bhvBooCage);
        cage->oBehParams = o->oBehParams;
#ifndef UNLOCK_ALL
    }
#endif
}

static void (*sBooWithCageActions[])(void) = {
    boo_with_cage_act_stopped,
    boo_with_cage_act_chasing_mario,
    boo_with_cage_act_bounced_on,
    boo_with_cage_act_attacked
};

void bhv_boo_with_cage_loop(void) {
    // PARTIAL_UPDATE
    cur_obj_update_floor_and_walls();
    cur_obj_call_action_function(sBooWithCageActions);
    cur_obj_move_standard(78);
    boo_approach_target_opacity_and_update_scale();
    o->oInteractStatus = INT_STATUS_NONE;
}

void bhv_merry_go_round_boo_manager_loop(void) {
    switch (o->oAction) {
        case BBH_MERRY_GO_ROUND_ACT_SPAWN_BOOS:
            if (o->oDistanceToMario < 1000.0f) {
                if (o->oMerryGoRoundBooManagerNumBoosKilled < 5) {
                    if ((o->oMerryGoRoundBooManagerNumBoosSpawned != 5) && ((o->oMerryGoRoundBooManagerNumBoosSpawned - o->oMerryGoRoundBooManagerNumBoosKilled) < 2)) {
                        spawn_object(o, MODEL_BOO, bhvMerryGoRoundBoo);
                        o->oMerryGoRoundBooManagerNumBoosSpawned++;
                    }
                    o->oAction = BBH_MERRY_GO_ROUND_ACT_WAIT;
                }
                if (o->oMerryGoRoundBooManagerNumBoosKilled > 4) {
                    struct Object *boo = spawn_object(o, MODEL_BOO, bhvMerryGoRoundBigBoo);
                    obj_copy_behavior_params(boo, o);
                    o->oAction = BBH_MERRY_GO_ROUND_ACT_STOPPED;
                    play_puzzle_jingle();
                }
            }
            break;
        case BBH_MERRY_GO_ROUND_ACT_WAIT:
            if (o->oTimer > 60) o->oAction = BBH_MERRY_GO_ROUND_ACT_SPAWN_BOOS;
            break;
        case BBH_MERRY_GO_ROUND_ACT_STOPPED:
            break;
    }
}

void bhv_animated_texture_loop(void) {
    cur_obj_set_pos_to_home_with_debug();
}

void bhv_boo_in_castle_loop(void) {
    Angle targetAngle;
    o->oBooBaseScale = 2.0f;
    switch (o->oAction) {
        case BOO_IN_CASTLE_ACT_INIT:
            cur_obj_hide();
#ifndef UNLOCK_ALL
            if (gHudDisplay.stars < 12) obj_mark_for_deletion(o);
#endif
            if (gMarioCurrentRoom == 1) o->oAction = BOO_IN_CASTLE_ACT_IDLE;
            break;
        case BOO_IN_CASTLE_ACT_IDLE:
            cur_obj_unhide();
            o->oOpacity = 180;
            if (o->oTimer == 0) cur_obj_scale(o->oBooBaseScale);
            if (o->oDistanceToMario < 1000.0f) {
                o->oAction = BOO_IN_CASTLE_ACT_FLEE;
                cur_obj_play_sound_2(SOUND_OBJ_BOO_LAUGH_LONG);
            }
            o->oForwardVel = 0.0f;
            targetAngle    = o->oAngleToMario;
            break;
        case BOO_IN_CASTLE_ACT_FLEE:
            cur_obj_forward_vel_approach_upward(32.0f, 1.0f);
            o->oHomeX   = -1000.0f;
            o->oHomeZ   = -9000.0f;
            targetAngle = cur_obj_angle_to_home();
            if (o->oPosZ < -5000.0f) {
                if (o->oOpacity > 0) {
                    o->oOpacity -= 20;
                } else {
                    o->oOpacity  =  0;
                }
            }
            if (o->activeFlags & ACTIVE_FLAG_IN_DIFFERENT_ROOM) o->oAction = BOO_IN_CASTLE_ACT_IDLE;
            break;
    }
    o->oVelY    = 0.0f;
    targetAngle = cur_obj_angle_to_home();
    cur_obj_rotate_yaw_toward(targetAngle, 0x5A8);
    boo_oscillate(TRUE);
    cur_obj_move_using_fvel_and_gravity();
}

static s8 sBbhStairJiggleOffsets[] = { -8, 8, -4, 4 };

Bool32 jiggle_bbh_stair(s32 timer) {
    if ((timer >= 4) || (timer < 0)) return TRUE;
    o->oPosY += sBbhStairJiggleOffsets[timer];
    return FALSE;
}

void bhv_boo_staircase(void) {
    f32 targetY = 0.0f;
    switch (o->oBehParams2ndByte) {
        case BOO_STAIRCASE_BP_1: targetY =    0.0f; break;
        case BOO_STAIRCASE_BP_0: targetY = -206.0f; break;
        case BOO_STAIRCASE_BP_2: targetY = -413.0f; break;
        default:                 targetY =    0.0f; break;
    }
    switch(o->oAction) {
        case BOO_STAIRCASE_ACT_INIT:
            o->oPosY   = (o->oHomeY - 620.0f);
            o->oAction = BOO_STAIRCASE_ACT_RISE;
            // fallthrough
        case BOO_STAIRCASE_ACT_RISE:
            o->oPosY += 8.0f;
            cur_obj_play_sound_1(SOUND_ENV_ELEVATOR2);
            if (o->oPosY   > targetY) {
                o->oPosY   = targetY;
                o->oAction = BOO_STAIRCASE_ACT_WOBBLE;
            }
            break;
        case BOO_STAIRCASE_ACT_WOBBLE:
            if (o->oTimer == 0) cur_obj_play_sound_2(SOUND_GENERAL_ELEVATOR_WOBBLE_LOWPRIO);
            if (jiggle_bbh_stair(o->oTimer)) o->oAction = BOO_STAIRCASE_ACT_PLAY_JINGLE;
            break;
        case BOO_STAIRCASE_ACT_PLAY_JINGLE:
            if ((o->oTimer == 0) && (o->oBehParams2ndByte == BOO_STAIRCASE_BP_1)) play_puzzle_jingle();
            break;
    }
}
