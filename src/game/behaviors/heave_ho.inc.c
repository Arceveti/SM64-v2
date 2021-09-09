// heave_ho.c.inc

s16 sHeaveHoTimings[][2] = { { 30, 0 }, { 42, 1 }, {  52, 0 }, {  64, 1 }, { 74, 0 },
                             { 86, 1 }, { 96, 0 }, { 108, 1 }, { 118, 0 }, { -1, 0 }, };

void bhv_heave_ho_throw_mario_loop(void) {
    vec3_set(&o->oParentRelativePosVec, 200.0f, -50.0f, 0.0f);
    o->oMoveAngleYaw = o->parentObj->oMoveAngleYaw;
    if (o->parentObj->oHeaveHoThrowState) {
        cur_obj_play_sound_2(SOUND_OBJ_HEAVEHO_TOSSED);
        gMarioObject->oInteractStatus |= INT_STATUS_MARIO_THROWN_BY_OBJ;
        gMarioStates[0].forwardVel       = -45.0f;
        gMarioStates[0].vel[1]           =  95.0f;
        o->parentObj->oHeaveHoThrowState = FALSE;
    }
}

void heave_ho_act_winding_up(void) { // act 1
    s32 i = 0;
    o->oForwardVel = 0.0f;
    cur_obj_reverse_animation();
    while (TRUE) {
        if (sHeaveHoTimings[i][0] == -1) {
            o->oAction = HEAVE_HO_ACT_MOVING;
            break;
        }
        if (o->oTimer < sHeaveHoTimings[i][0]) {
            cur_obj_init_animation_with_accel_and_sound(HEAVE_HO_ANIM_WINDING_UP, sHeaveHoTimings[i][1]);
            break;
        }
        i++;
    }
}

void heave_ho_act_moving(void) { // act 2
    Angle angleVel;
    if (cur_obj_lateral_dist_from_mario_to_home_squared() > sqr(1000.0f)) o->oAngleToMario = cur_obj_angle_to_home();
    if (o->oTimer > 150) {
        o->oHeaveHoTimedSpeed = ((302 - o->oTimer) / 152.0f);
        if (o->oHeaveHoTimedSpeed < 0.1f) {
            o->oHeaveHoTimedSpeed = 0.1f;
            o->oAction = HEAVE_HO_ACT_WINDING_UP;
        }
    } else {
        o->oHeaveHoTimedSpeed = 1.0f;
    }
    cur_obj_init_animation_with_accel_and_sound(HEAVE_HO_ANIM_MOVING, o->oHeaveHoTimedSpeed);
    o->oForwardVel = (o->oHeaveHoTimedSpeed * 10.0f);
    angleVel       = (o->oHeaveHoTimedSpeed * 0x400);
    o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oAngleToMario, angleVel);
}

void heave_ho_act_throw_mario(void) { // act 3
    o->oForwardVel = 0.0f;
    if (o->oTimer == 0) o->oHeaveHoThrowState = TRUE;
    if (o->oTimer == 1) {
        cur_obj_init_animation_with_accel_and_sound(HEAVE_HO_ANIM_THROW, 1.0f);
        o->numCollidedObjs = 20;
    }
    if (cur_obj_check_if_near_animation_end()) o->oAction = HEAVE_HO_ACT_WINDING_UP;
}

void heave_ho_act_inactive(void) { // act 0
    cur_obj_set_pos_to_home();
    if ((find_water_level(o->oPosX, o->oPosZ) < o->oPosY) && (o->oDistanceToMario < 4000.0f)) {
        cur_obj_become_tangible();
        cur_obj_unhide();
        o->oAction = HEAVE_HO_ACT_WINDING_UP;
    } else {
        cur_obj_become_intangible();
        cur_obj_hide();
    }
}

void (*sHeaveHoActions[])(void) = { heave_ho_act_inactive, heave_ho_act_winding_up, heave_ho_act_moving, heave_ho_act_throw_mario };

void heave_ho_move(void) {
    cur_obj_update_floor_and_walls();
    cur_obj_call_action_function(sHeaveHoActions);
    cur_obj_move_standard(-78);
    o->oGraphYOffset = ((o->oMoveFlags & OBJ_MOVE_MASK_IN_WATER) ? -15.0f : 0.0f);
    if (o->oForwardVel > 3.0f) cur_obj_play_sound_1(SOUND_AIR_HEAVEHO_MOVE);
    if (o->oMoveFlags & OBJ_MOVE_MASK_IN_WATER) o->oAction = HEAVE_HO_ACT_INACTIVE;
    if (o->oInteractStatus & INT_STATUS_GRABBED_MARIO) {
        o->oInteractStatus = INT_STATUS_NONE;
        o->oAction         = HEAVE_HO_ACT_THROW_MARIO;
    }
}

void bhv_heave_ho_loop(void) {
    cur_obj_scale(2.0f);
    switch (o->oHeldState) {
        case HELD_FREE:    heave_ho_move();                                                                   break;
        case HELD_HELD:    cur_obj_unrender_set_action_and_anim(HEAVE_HO_ANIM_MOVING, HEAVE_HO_ACT_INACTIVE); break;
        case HELD_THROWN:  cur_obj_get_dropped();                                                             break;
        case HELD_DROPPED: cur_obj_get_dropped();                                                             break;
    }
    o->oInteractStatus = INT_STATUS_NONE;
}
