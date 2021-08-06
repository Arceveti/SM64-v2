// chuckya.c.inc

void common_anchor_mario_behavior(f32 forwardVel, f32 velY, s32 flag) {
    switch (o->parentObj->oCommonAnchorAction) {
        case COMMON_ANCHOR_ACT_INACTIVE:
            break;
        case COMMON_ANCHOR_ACT_SET_MARIO_GFX_TO_POS:
            obj_set_gfx_pos_at_obj_pos(gMarioObject, o);
            break;
        case COMMON_ANCHOR_ACT_THROW_MARIO:
            gMarioObject->oInteractStatus |= (flag + INT_STATUS_MARIO_UNK2);
            gMarioStates[0].forwardVel = forwardVel;
            gMarioStates[0].vel[1]     = velY;
            o->parentObj->oCommonAnchorAction = COMMON_ANCHOR_ACT_INACTIVE;
            break;
        case COMMON_ANCHOR_ACT_DROP_MARIO:
            gMarioObject->oInteractStatus |= (INT_STATUS_MARIO_UNK2 + INT_STATUS_MARIO_UNK6); // loads 2 interactions at once?
            gMarioStates[0].forwardVel = 10.0f;
            gMarioStates[0].vel[1]     = 10.0f;
            o->parentObj->oCommonAnchorAction = COMMON_ANCHOR_ACT_INACTIVE;
            break;
    }
    o->oMoveAngleYaw = o->parentObj->oMoveAngleYaw;
    if (o->parentObj->activeFlags == ACTIVE_FLAG_DEACTIVATED) obj_mark_for_deletion(o);
}

void bhv_chuckya_anchor_mario_loop(void) {
    common_anchor_mario_behavior(40.0f, 40.0f, INT_STATUS_MARIO_UNK6);
}

s32 approach_forward_vel(f32 *arr, f32 target, f32 amt) {
    s32 alreadyEqual = FALSE;
    if (arr[0] > target) {
        arr[0] -= amt;
        if (arr[0] < target) arr[0] = target;
    } else if (arr[0] < target) {
        arr[0] += amt;
        if (arr[0] > target) arr[0] = target;
    } else {
        alreadyEqual = TRUE;
    }
    return alreadyEqual;
}

void chuckya_act_moving(void) { // act 0
    s32 initialSubAction;
    if (o->oTimer == 0) o->oChuckyaSubActionTimer = 0;
    o->oAngleToMario = obj_angle_to_object(o, gMarioObject);
    switch (initialSubAction = o->oSubAction) {
        case CHUCKYA_SUB_ACT_TURN_TOWARD_MARIO:
            o->oForwardVel = 0.0f;
            if (cur_obj_lateral_dist_from_mario_to_home() < 2000.0f) {
                cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x400);
                if (o->oChuckyaSubActionTimer > 40 || abs_angle_diff(o->oMoveAngleYaw, o->oAngleToMario) < 0x1000) o->oSubAction = CHUCKYA_SUB_ACT_ACCELERATE;
            } else {
                o->oSubAction = CHUCKYA_SUB_ACT_TURN_TOWARD_HOME;
            }
            break;
        case CHUCKYA_SUB_ACT_ACCELERATE:
            approach_forward_vel(&o->oForwardVel, 30.0f, 4.0f);
            if (abs_angle_diff(o->oMoveAngleYaw, o->oAngleToMario) > 0x4000) o->oSubAction = CHUCKYA_SUB_ACT_STOP;
            if (cur_obj_lateral_dist_from_mario_to_home() > 2000.0f) o->oSubAction = CHUCKYA_SUB_ACT_TURN_TOWARD_HOME;
            break;
        case CHUCKYA_SUB_ACT_STOP:
            approach_forward_vel(&o->oForwardVel, 0, 4.0f);
            if (o->oChuckyaSubActionTimer > 48) o->oSubAction = CHUCKYA_SUB_ACT_TURN_TOWARD_MARIO;
            break;
        case CHUCKYA_SUB_ACT_TURN_TOWARD_HOME:
            if (cur_obj_lateral_dist_to_home() < 500.0f) {
                o->oForwardVel = 0.0f;
            } else {
                approach_forward_vel(&o->oForwardVel, 10.0f, 4.0f);
                o->oAngleToMario = cur_obj_angle_to_home();
                cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x800);
            }
            if (cur_obj_lateral_dist_from_mario_to_home() < 1900.0f) o->oSubAction = CHUCKYA_SUB_ACT_TURN_TOWARD_MARIO;
            break;
    }
    if (o->oSubAction != initialSubAction) {
        o->oChuckyaSubActionTimer = 0;
    } else {
        o->oChuckyaSubActionTimer++;
    }
    cur_obj_init_animation_with_sound(CHUCKYA_ANIM_IDLE);
    if (o->oForwardVel > 1.0f) cur_obj_play_sound_1(SOUND_AIR_CHUCKYA_MOVE);
    print_debug_bottom_up("sp %d", o->oForwardVel);
}

void chuckya_act_grabbed_mario(void) { // act 1
    switch (o->oSubAction) {
        case CHUCKYA_SUB_ACT_GRAB_MARIO:
            if (cur_obj_init_animation_and_check_if_near_end(CHUCKYA_ANIM_GRAB_MARIO)) o->oSubAction = CHUCKYA_SUB_ACT_HOLD_MARIO;
            o->oChuckyaSubActionTimer = random_float() * 30.0f + 10.0f;
            o->oChuckyaNumPlayerEscapeActions = 0;
            o->oForwardVel = 0.0f;
            break;
        case CHUCKYA_SUB_ACT_HOLD_MARIO:
            o->oChuckyaNumPlayerEscapeActions += player_performed_grab_escape_action();
            print_debug_bottom_up("%d", o->oChuckyaNumPlayerEscapeActions);
            if (o->oChuckyaNumPlayerEscapeActions > 10) {
                o->oCommonAnchorAction = COMMON_ANCHOR_ACT_DROP_MARIO;
                o->oAction             = CHUCKYA_ACT_RELEASE_MARIO; // drop mario
                o->oInteractStatus &= ~(INT_STATUS_GRABBED_MARIO);
            } else {
                cur_obj_init_animation_with_sound(CHUCKYA_ANIM_THROW_1);
                o->oMoveAngleYaw += INT_STATUS_GRABBED_MARIO;
                if (o->oChuckyaSubActionTimer-- < 0 && (check_if_moving_over_floor(50.0f, 150.0f) || o->oChuckyaSubActionTimer < -16)) o->oSubAction = CHUCKYA_SUB_ACT_THROW_MARIO;
            }
            break;
        case CHUCKYA_SUB_ACT_THROW_MARIO:
        default:
            cur_obj_init_animation_with_sound(CHUCKYA_ANIM_THROW_2);
            if (cur_obj_check_anim_frame(18)) {
                cur_obj_play_sound_2(SOUND_OBJ_RELEASE_MARIO);
                o->oCommonAnchorAction = COMMON_ANCHOR_ACT_THROW_MARIO;
                o->oAction             = CHUCKYA_ACT_RELEASE_MARIO; // drop mario
                o->oInteractStatus &= ~(INT_STATUS_GRABBED_MARIO);
            }
            break;
    }
}

void chuckya_act_release_mario(void) { // act 3
    o->oForwardVel = 0;
    o->oVelY       = 0;
    cur_obj_init_animation_with_sound(CHUCKYA_ANIM_IDLE);
    if (o->oTimer > 100) o->oAction = CHUCKYA_ACT_MOVING;
}

void chuckya_act_thrown(void) {
    if (o->oMoveFlags & (OBJ_MOVE_HIT_WALL | OBJ_MOVE_MASK_IN_WATER | OBJ_MOVE_LANDED)) {
        obj_mark_for_deletion(o);
        obj_spawn_loot_yellow_coins(o, 5, 20.0f);
        spawn_mist_particles_with_sound(SOUND_OBJ_CHUCKYA_DEATH);
    }
}

void (*sChuckyaActions[])(void) = { chuckya_act_moving,
                                    chuckya_act_grabbed_mario,
                                    chuckya_act_thrown,
                                    chuckya_act_release_mario };

void chuckya_move(void) {
    cur_obj_update_floor_and_walls();
    cur_obj_call_action_function(sChuckyaActions);
    cur_obj_move_standard(-30);
    if (o->oInteractStatus & INT_STATUS_GRABBED_MARIO) {
        o->oAction = CHUCKYA_ACT_GRABBED_MARIO;
        o->oCommonAnchorAction = COMMON_ANCHOR_ACT_SET_MARIO_GFX_TO_POS;
        cur_obj_play_sound_2(SOUND_OBJ_GRAB_MARIO);
    }
}

void bhv_chuckya_loop(void) {
    cur_obj_scale(2.0f);
    o->oInteractionSubtype |= INT_SUBTYPE_GRABS_MARIO;
    switch (o->oHeldState) {
        case HELD_FREE:
            chuckya_move();
            break;
        case HELD_HELD:
            cur_obj_unrender_set_action_and_anim(CHUCKYA_ANIM_HELD, CHUCKYA_ACT_MOVING);
            break;
        case HELD_THROWN:
        case HELD_DROPPED:
            cur_obj_get_thrown_or_placed(20.0f, 50.0f, CHUCKYA_ACT_THROWN);
            break;
    }
    o->oInteractStatus = INT_STATUS_NONE;
    print_debug_bottom_up("md %d", o->oAction);
}
