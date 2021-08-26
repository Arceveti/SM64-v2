// tuxie.c.inc

void play_penguin_walking_sound(s32 walk) {
    s32 sound;
    if (o->oSoundStateID == 0) {
        sound = ((walk == PENGUIN_SOUND_WALK_BABY) ? SOUND_OBJ_BABY_PENGUIN_WALK : SOUND_OBJ_BIG_PENGUIN_WALK);
        set_obj_anim_with_accel_and_sound(1, 11, sound);
    }
}

void tuxies_mother_act_received_baby(void) { // act 2
    f32 dist;
    struct Object *smallPenguinObj = cur_obj_find_nearest_object_with_behavior(bhvSmallPenguin, &dist);
    if (cur_obj_find_nearby_held_actor(bhvSmallPenguinReturned, 1000.0f) != NULL) {
        if (o->oSubAction == MOTHER_PENGUIN_SUB_ACT_CHASE_MARIO) {
            cur_obj_init_animation_with_sound(PENGUIN_ANIM_WALK);
            o->oForwardVel = 10.0f;
            if (800.0f < cur_obj_lateral_dist_from_mario_to_home()) o->oSubAction = MOTHER_PENGUIN_SUB_ACT_STOP_CHASING_MARIO;
            cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x400);
        } else {
            o->oForwardVel = 0.0f;
            cur_obj_init_animation_with_sound(PENGUIN_ANIM_IDLE);
            if (cur_obj_lateral_dist_from_mario_to_home() < 700.0f) o->oSubAction = MOTHER_PENGUIN_SUB_ACT_CHASE_MARIO;
        }
    } else {
        o->oForwardVel = 0.0f;
        cur_obj_init_animation_with_sound(PENGUIN_ANIM_IDLE);
    }
    if (smallPenguinObj != NULL && dist < 300.0f && smallPenguinObj->oHeldState != HELD_FREE) {
        o->oAction = MOTHER_PENGUIN_ACT_RECEIVE_BABY;
        smallPenguinObj->oSmallPenguinReturnedToMother = TRUE;
        o->prevObj = smallPenguinObj;
    }
}

void tuxies_mother_act_receiving_baby(void) { // act 1
    s32 motherParam;
    s32 babyParam;
    DialogID dialogID;
    switch (o->oSubAction) {
        case MOTHER_PENGUIN_SUB_ACT_RECEIVE_BABY:
            cur_obj_init_animation_with_sound(PENGUIN_ANIM_IDLE);
            if (!cur_obj_is_mario_on_platform()) {
                motherParam = (o->oBehParams >> 0x10) & 0xFF;
                babyParam = (o->prevObj->oBehParams >> 0x10) & 0xFF;
                dialogID = (motherParam == babyParam) ? DIALOG_058 : DIALOG_059;
                if (cur_obj_update_dialog_with_cutscene(MARIO_DIALOG_LOOK_UP, 
                        DIALOG_FLAG_TURN_TO_MARIO, CUTSCENE_DIALOG, dialogID)) {
                    o->oSubAction = (dialogID == DIALOG_058) ? MOTHER_PENGUIN_SUB_ACT_CORRECT_BABY : MOTHER_PENGUIN_SUB_ACT_WRONG_BABY;
                    o->prevObj->oInteractionSubtype |= INT_SUBTYPE_DROP_IMMEDIATELY;
                }
            } else {
                cur_obj_init_animation_with_sound(PENGUIN_ANIM_WALK);
            }
            break;
        case MOTHER_PENGUIN_SUB_ACT_CORRECT_BABY:
            if (o->prevObj->oHeldState == HELD_FREE) {
                o->prevObj->oInteractionSubtype &= ~INT_SUBTYPE_DROP_IMMEDIATELY;
                obj_set_behavior(o->prevObj, bhvSmallPenguinReturned);
                cur_obj_spawn_star_at_y_offset(3167.0f, -4300.0f, 5108.0f, 200.0f);
                o->oAction = MOTHER_PENGUIN_ACT_RECEIVED_BABY;
            }
            break;
        case MOTHER_PENGUIN_SUB_ACT_WRONG_BABY:
            if (o->prevObj->oHeldState == HELD_FREE) {
                o->prevObj->oInteractionSubtype &= ~INT_SUBTYPE_DROP_IMMEDIATELY;
                obj_set_behavior(o->prevObj, bhvPenguinBaby);
                o->oAction = MOTHER_PENGUIN_ACT_RECEIVED_BABY;
            }
            break;
    }
}

void tuxies_mother_act_idle(void) { // act 0
    s32 nearBaby = FALSE;
    f32 dist;
    struct Object *smallPenguinObj = cur_obj_find_nearest_object_with_behavior(bhvSmallPenguin, &dist);
    cur_obj_scale(4.0f);
    cur_obj_init_animation_with_sound(PENGUIN_ANIM_IDLE);
    nearBaby = (dist < 500.0f);
    if (smallPenguinObj != NULL && dist < 300.0f && smallPenguinObj->oHeldState != HELD_FREE) {
        o->oAction = MOTHER_PENGUIN_ACT_RECEIVE_BABY;
        smallPenguinObj->oSmallPenguinReturnedToMother = TRUE;
        o->prevObj = smallPenguinObj;
    } else {
        switch (o->oSubAction) {
            case MOTHER_PENGUIN_SUB_ACT_READY_TO_ASK:
                if (cur_obj_can_mario_activate_textbox_2(300.0f, 100.0f) && !nearBaby) o->oSubAction = MOTHER_PENGUIN_SUB_ACT_ASK_FOR_BABY;
                break;
            case MOTHER_PENGUIN_SUB_ACT_ASK_FOR_BABY:
                if (cur_obj_update_dialog_with_cutscene(MARIO_DIALOG_LOOK_UP, 
                    DIALOG_FLAG_TURN_TO_MARIO, CUTSCENE_DIALOG, DIALOG_057)) { // "have you seen my baby"
                    o->oSubAction = MOTHER_PENGUIN_SUB_ACT_ALREADY_ASKED;
                }
                break;
            case MOTHER_PENGUIN_SUB_ACT_ALREADY_ASKED:
                if (o->oDistanceToMario > 450.0f) o->oSubAction = MOTHER_PENGUIN_SUB_ACT_READY_TO_ASK;
                break;
        }
    }
    if (cur_obj_check_anim_frame(PENGUIN_ANIM_DIVE_SLIDE)) cur_obj_play_sound_2(SOUND_OBJ_BIG_PENGUIN_YELL);
}

void (*sTuxiesMotherActions[])(void) = { tuxies_mother_act_idle,
                                         tuxies_mother_act_receiving_baby,
                                         tuxies_mother_act_received_baby };

void bhv_tuxies_mother_loop(void) {
    o->activeFlags |= ACTIVE_FLAG_IGNORE_WATER_LEVEL;
    cur_obj_update_floor_and_walls();
    cur_obj_call_action_function(sTuxiesMotherActions);
    cur_obj_move_standard(-78);
    play_penguin_walking_sound(PENGUIN_SOUND_WALK_BIG);
    o->oInteractStatus = INT_STATUS_NONE;
}

void small_penguin_dive_with_mario(void) {
    if (mario_is_dive_sliding()) {
        o->oSmallPenguinStoredAction = o->oAction;
        o->oAction = SMALL_PENGUIN_ACT_DIVE_SLIDING;
    }
}

void small_penguin_act_walking_away_from_mario(void) { // act 2
    s32 nearMother = FALSE;
    if (o->oTimer == 0) nearMother = (cur_obj_dist_to_nearest_object_with_behavior(bhvTuxiesMother) < 1000.0f);
    cur_obj_init_animation_with_sound(PENGUIN_ANIM_WALK);
    o->oForwardVel = o->oSmallPenguinNextForwardVel + 3.0f;
    cur_obj_rotate_yaw_toward(o->oAngleToMario + DEGREES(180), (o->oSmallPenguinYawIncrement + 0x600));
    if (o->oDistanceToMario > o->oSmallPenguinRandomDistanceCheck + 500.0f) o->oAction = SMALL_PENGUIN_ACT_WALKING;
    small_penguin_dive_with_mario();
    if (nearMother) o->oAction = SMALL_PENGUIN_ACT_NEAR_MOTHER;
}

void small_penguin_act_walking_toward_mario(void) { // act 1
    cur_obj_init_animation_with_sound(PENGUIN_ANIM_WALK);
    o->oForwardVel = o->oSmallPenguinNextForwardVel + 3.0f;
    cur_obj_rotate_yaw_toward(o->oAngleToMario, (o->oSmallPenguinYawIncrement + 0x600));
    if (o->oDistanceToMario < o->oSmallPenguinRandomDistanceCheck + 300.0f) o->oAction = SMALL_PENGUIN_ACT_WALKING;
    if (o->oDistanceToMario > 1100.0f) o->oAction = SMALL_PENGUIN_ACT_WALKING;
    small_penguin_dive_with_mario();
}

void small_penguin_act_dive_sliding(void) { // act 3
    if (o->oTimer > 5) {
        if (o->oTimer == 6) cur_obj_play_sound_2(SOUND_OBJ_BABY_PENGUIN_DIVE);
        cur_obj_init_animation_with_sound(PENGUIN_ANIM_DIVE_SLIDE);
        if (o->oTimer > 25 && !mario_is_dive_sliding()) o->oAction = SMALL_PENGUIN_ACT_DIVE_SLIDING_STOP;
    }
}

void small_penguin_act_dive_sliding_stop(void) { // act 4
    if (o->oTimer > 20) {
        o->oForwardVel = 0.0f;
        cur_obj_init_animation_with_sound(PENGUIN_ANIM_STAND_UP);
        if (o->oTimer > 40) o->oAction = o->oSmallPenguinStoredAction;
    }
}

void small_penguin_act_walking(void) { // act 0
    s32 nearMother = FALSE;

    cur_obj_init_animation_with_sound(PENGUIN_ANIM_IDLE);
    if (o->oTimer == 0) {
        o->oSmallPenguinYawIncrement = (s32)(random_float() * 0x400);
        o->oSmallPenguinRandomDistanceCheck = random_float() * 100.0f;
        o->oSmallPenguinNextForwardVel = random_float();
        o->oForwardVel = 0.0f;
        nearMother =  (cur_obj_dist_to_nearest_object_with_behavior(bhvTuxiesMother) < 1000.0f);
    }
    if (o->oDistanceToMario < 1000.0f && o->oSmallPenguinRandomDistanceCheck + 600.0f < o->oDistanceToMario) {
        o->oAction = SMALL_PENGUIN_ACT_WALKING_TOWARD_MARIO;
    } else if (o->oDistanceToMario < o->oSmallPenguinRandomDistanceCheck + 300.0f) {
        o->oAction = SMALL_PENGUIN_ACT_WALKING_AWAY_FROM_MARIO;
    }
    if (nearMother) o->oAction = SMALL_PENGUIN_ACT_NEAR_MOTHER;
    if (cur_obj_mario_far_away()) cur_obj_set_pos_to_home();
}

void small_penguin_act_near_mother(void) { // act 5
    f32 distToMother;
    Angle angleToMother;
    struct Object *motherPenguinObj = cur_obj_nearest_object_with_behavior(bhvTuxiesMother);
    if (motherPenguinObj != NULL) {
        o->oForwardVel = (o->oDistanceToMario < 1000.0f) ? 2.0f : 0.0f;
        distToMother = dist_between_objects(o, motherPenguinObj);
        angleToMother = obj_angle_to_object(o, motherPenguinObj);
        if (distToMother > 200.0f) {
            cur_obj_rotate_yaw_toward(angleToMother, 0x400);
        } else {
            cur_obj_rotate_yaw_toward((angleToMother + DEGREES(180)), 0x400);
        }
        cur_obj_init_animation_with_sound(PENGUIN_ANIM_WALK);
    }
    small_penguin_dive_with_mario();
}

void (*sSmallPenguinActions[])(void) = {
    small_penguin_act_walking,
    small_penguin_act_walking_toward_mario,
    small_penguin_act_walking_away_from_mario,
    small_penguin_act_dive_sliding,
    small_penguin_act_dive_sliding_stop,
    small_penguin_act_near_mother
};

void small_penguin_free_actions(void) {
    if (o->oSmallPenguinReturnedToMother) {
        o->oAction = SMALL_PENGUIN_ACT_NEAR_MOTHER;
        o->oSmallPenguinReturnedToMother = FALSE;
    }
    cur_obj_update_floor_and_walls();
    cur_obj_call_action_function(sSmallPenguinActions);
    cur_obj_move_standard(-78);
    play_penguin_walking_sound(PENGUIN_SOUND_WALK_BABY);
}

void bhv_small_penguin_loop(void) {
    switch (o->oHeldState) {
        case HELD_FREE:
            small_penguin_free_actions();
            break;
        case HELD_HELD:
            cur_obj_unrender_set_action_and_anim(PENGUIN_ANIM_WALK, SMALL_PENGUIN_ACT_WALKING);
            if (cur_obj_has_behavior(bhvPenguinBaby)) obj_set_behavior(o, bhvSmallPenguin);
            obj_copy_pos(o, gMarioObject);
            if (!(gGlobalTimer & 0x1F)) play_sound(SOUND_OBJ2_BABY_PENGUIN_YELL, gMarioObject->header.gfx.cameraToObject); // Was % 30
            break;
        case HELD_THROWN:
            cur_obj_get_thrown_or_placed(0.0f, 0.0f, SMALL_PENGUIN_ACT_WALKING);
            break;
        case HELD_DROPPED:
            cur_obj_get_dropped();
            break;
    }
}

/** Geo switch logic for Tuxie's mother's eyes. Cases 0-4. Interestingly, case
 * 4 is unused, and is the eye state seen in Shoshinkai 1995 footage.
 */
Gfx *geo_switch_tuxie_mother_eyes(s32 callContext, struct GraphNode *node, UNUSED Mat4 *mtx) {
    struct Object *obj;
    struct GraphNodeSwitchCase *switchCase;
    s32 timer;

    if (callContext == GEO_CONTEXT_RENDER) {
        obj = (struct Object *) gCurGraphNodeObject;
        switchCase = (struct GraphNodeSwitchCase *) node;
        switchCase->selectedCase = PENGUIN_ANIM_STATE_EYES_OPEN;
#ifdef PENGUIN_MOTHER_SAD_EYES
        u32 isMother = obj_has_behavior(obj, bhvTuxiesMother);
        s32 babyDelivered = obj->oAction == MOTHER_PENGUIN_ACT_RECEIVED_BABY;
        switchCase->selectedCase = (!isMother || babyDelivered) ? PENGUIN_ANIM_STATE_EYES_OPEN : PENGUIN_ANIM_STATE_EYES_SAD;
#endif

        // timer logic for blinking. uses cases 0-2.
        timer = gGlobalTimer % 50;
        if (timer < 43) {
#ifdef PENGUIN_MOTHER_SAD_EYES
            switchCase->selectedCase = (!isMother || babyDelivered) ? PENGUIN_ANIM_STATE_EYES_OPEN : PENGUIN_ANIM_STATE_EYES_SAD;
#else
            switchCase->selectedCase = PENGUIN_ANIM_STATE_EYES_OPEN;
#endif
        } else if (timer < 45) {
            switchCase->selectedCase = PENGUIN_ANIM_STATE_EYES_HALF_CLOSED;
        } else if (timer < 47) {
            switchCase->selectedCase = PENGUIN_ANIM_STATE_EYES_CLOSED;
        } else {
            switchCase->selectedCase = PENGUIN_ANIM_STATE_EYES_HALF_CLOSED;
        }

        /** make Tuxie's Mother have angry eyes if Mario takes the correct baby
         * after giving it back. The easiest way to check this is to see if she's
         * moving, since she only does when she's chasing Mario.
         */
        if (segmented_to_virtual(bhvTuxiesMother) == obj->behavior && obj->oForwardVel > 5.0f) switchCase->selectedCase = PENGUIN_ANIM_STATE_EYES_ANGRY;
    }
    return NULL;
}
