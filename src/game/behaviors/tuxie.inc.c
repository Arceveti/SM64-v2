// tuxie.c.inc

void play_penguin_walking_sound(s32 walk) {
    s32 sound;
    if (o->oSoundStateID == 0) {
        sound = ((walk == PENGUIN_WALK_BABY) ? SOUND_OBJ_BABY_PENGUIN_WALK : SOUND_OBJ_BIG_PENGUIN_WALK);
        set_obj_anim_with_accel_and_sound(1, 11, sound);
    }
}

void tuxies_mother_act_2(void) {
    f32 dist;
    struct Object *smallPenguinObj = cur_obj_find_nearest_object_with_behavior(bhvSmallPenguin, &dist);
    if (cur_obj_find_nearby_held_actor(bhvSmallPenguinReturned, 1000.0f) != NULL) {
        if (o->oSubAction == 0) {
            cur_obj_init_animation_with_sound(0);
            o->oForwardVel = 10.0f;
            if (800.0f < cur_obj_lateral_dist_from_mario_to_home()) {
                o->oSubAction = 1;
            }
            cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x400);
        } else {
            o->oForwardVel = 0.0f;
            cur_obj_init_animation_with_sound(3);
            if (cur_obj_lateral_dist_from_mario_to_home() < 700.0f) {
                o->oSubAction = 0;
            }
        }
    } else {
        o->oForwardVel = 0.0f;
        cur_obj_init_animation_with_sound(3);
    }
    if (smallPenguinObj != NULL && dist < 300.0f && smallPenguinObj->oHeldState != HELD_FREE) {
        o->oAction = 1;
        smallPenguinObj->oSmallPenguinUnk88 = TRUE;
        o->prevObj = smallPenguinObj;
    }
}

void tuxies_mother_act_1(void) {
    s32 motherParam;
    s32 babyParam;
    s32 dialogID;
    switch (o->oSubAction) {
        case 0:
            cur_obj_init_animation_with_sound(3);
            if (!cur_obj_is_mario_on_platform()) {
                motherParam = (o->oBehParams >> 0x10) & 0xFF;
                babyParam = (o->prevObj->oBehParams >> 0x10) & 0xFF;
                dialogID = (motherParam == babyParam) ? DIALOG_058 : DIALOG_059;
                if (cur_obj_update_dialog_with_cutscene(MARIO_DIALOG_LOOK_UP, 
                        DIALOG_FLAG_TURN_TO_MARIO, CUTSCENE_DIALOG, dialogID)) {
                    o->oSubAction = (dialogID == DIALOG_058) ? 1 : 2;
                    o->prevObj->oInteractionSubtype |= INT_SUBTYPE_DROP_IMMEDIATELY;
                }
            } else
                cur_obj_init_animation_with_sound(0);
            break;
        case 1:
            if (o->prevObj->oHeldState == HELD_FREE) {
                //! This line is was almost certainly supposed to be something
                // like o->prevObj->oInteractionSubtype &= ~INT_SUBTYPE_DROP_IMMEDIATELY;
                // however, this code uses the value of o->oInteractionSubtype
                // rather than its offset to rawData. For this object,
                // o->oInteractionSubtype is always 0, so the result is this:
                // o->prevObj->oUnknownUnk88 &= ~INT_SUBTYPE_DROP_IMMEDIATELY
                // which has no effect as o->prevObj->oUnknownUnk88 is always 0
                // or 1, which is not affected by the bitwise AND.
                o->prevObj->oInteractionSubtype &= ~INT_SUBTYPE_DROP_IMMEDIATELY;
                obj_set_behavior(o->prevObj, bhvSmallPenguinReturned);
                cur_obj_spawn_star_at_y_offset(3167.0f, -4300.0f, 5108.0f, 200.0f);
                o->oAction = 2;
            }
            break;
        case 2:
            if (o->prevObj->oHeldState == HELD_FREE) {
                o->prevObj->oInteractionSubtype &= ~INT_SUBTYPE_DROP_IMMEDIATELY;
                obj_set_behavior(o->prevObj, bhvPenguinBaby);
                o->oAction = 2;
            }
            break;
    }
}

void tuxies_mother_act_0(void) {
    s32 nearBaby = FALSE;
    f32 dist;
    struct Object *smallPenguinObj = cur_obj_find_nearest_object_with_behavior(bhvSmallPenguin, &dist);
    cur_obj_scale(4.0f);
    cur_obj_init_animation_with_sound(3);
    nearBaby = (dist < 500.0f);
    if (smallPenguinObj != NULL && dist < 300.0f && smallPenguinObj->oHeldState != HELD_FREE) {
        o->oAction = 1;
        smallPenguinObj->oSmallPenguinUnk88 = TRUE;
        o->prevObj = smallPenguinObj;
    } else {
        switch (o->oSubAction) {
            case 0:
                if (cur_obj_can_mario_activate_textbox_2(300.0f, 100.0f) && !nearBaby) {
                    o->oSubAction++;
                }
                break;
            case 1:
                if (cur_obj_update_dialog_with_cutscene(MARIO_DIALOG_LOOK_UP, 
                    DIALOG_FLAG_TURN_TO_MARIO, CUTSCENE_DIALOG, DIALOG_057)) {
                    o->oSubAction++;
                }
                break;
            case 2:
                if (o->oDistanceToMario > 450.0f) {
                    o->oSubAction = 0;
                }
                break;
        }
    }
    if (cur_obj_check_anim_frame(1)) {
        cur_obj_play_sound_2(SOUND_OBJ_BIG_PENGUIN_YELL);
    }
}

void (*sTuxiesMotherActions[])(void) = { tuxies_mother_act_0,
                                         tuxies_mother_act_1,
                                         tuxies_mother_act_2 };

void bhv_tuxies_mother_loop(void) {
    o->activeFlags |= ACTIVE_FLAG_IGNORE_WATER_LEVEL;
    cur_obj_update_floor_and_walls();
    cur_obj_call_action_function(sTuxiesMotherActions);
    cur_obj_move_standard(-78);
    play_penguin_walking_sound(PENGUIN_WALK_BIG);
    o->oInteractStatus = INT_STATUS_NONE;
}

void small_penguin_dive_with_mario(void) {
    if (mario_is_dive_sliding()) {
        o->oSmallPenguinUnk100 = o->oAction;
        o->oAction = 3;
    }
}

void small_penguin_act_2(void) {
    s32 nearMother = FALSE;
    if (o->oTimer == 0) {
        nearMother = (cur_obj_dist_to_nearest_object_with_behavior(bhvTuxiesMother) < 1000.0f);
    }
    cur_obj_init_animation_with_sound(0);
    o->oForwardVel = o->oSmallPenguinUnk104 + 3.0f;
    cur_obj_rotate_yaw_toward(o->oAngleToMario + 0x8000, o->oSmallPenguinUnk110 + 0x600);
    if (o->oDistanceToMario > o->oSmallPenguinUnk108 + 500.0f) {
        o->oAction = 0;
    }
    small_penguin_dive_with_mario();
    if (nearMother) {
        o->oAction = 5;
    }
}

void small_penguin_act_1(void) {
    cur_obj_init_animation_with_sound(0);
    o->oForwardVel = o->oSmallPenguinUnk104 + 3.0f;
    cur_obj_rotate_yaw_toward(o->oAngleToMario, o->oSmallPenguinUnk110 + 0x600);
    if (o->oDistanceToMario < o->oSmallPenguinUnk108 + 300.0f) {
        o->oAction = 0;
    }
    if (o->oDistanceToMario > 1100.0f) {
        o->oAction = 0;
    }
    small_penguin_dive_with_mario();
}

void small_penguin_act_3(void) {
    if (o->oTimer > 5) {
        if (o->oTimer == 6) {
            cur_obj_play_sound_2(SOUND_OBJ_BABY_PENGUIN_DIVE);
        }
        cur_obj_init_animation_with_sound(1);
        if (o->oTimer > 25) {
            if (!mario_is_dive_sliding()) {
                o->oAction = 4;
            }
        }
    }
}

void small_penguin_act_4(void) {
    if (o->oTimer > 20) {
        o->oForwardVel = 0.0f;
        cur_obj_init_animation_with_sound(2);
        if (o->oTimer > 40) {
            o->oAction = o->oSmallPenguinUnk100;
        }
    }
}

void small_penguin_act_0(void) {
    s32 nearMother = FALSE;

    cur_obj_init_animation_with_sound(3);
    if (o->oTimer == 0) {
        o->oSmallPenguinUnk110 = (s32)(random_float() * 0x400);
        o->oSmallPenguinUnk108 = random_float() * 100.0f;
        o->oSmallPenguinUnk104 = random_float();
        o->oForwardVel = 0.0f;
        nearMother =  (cur_obj_dist_to_nearest_object_with_behavior(bhvTuxiesMother) < 1000.0f);
    }
    if (o->oDistanceToMario < 1000.0f && o->oSmallPenguinUnk108 + 600.0f < o->oDistanceToMario) {
        o->oAction = 1;
    } else if (o->oDistanceToMario < o->oSmallPenguinUnk108 + 300.0f) {
        o->oAction = 2;
    }
    if (nearMother) {
        o->oAction = 5;
    }
    if (cur_obj_mario_far_away()) {
        cur_obj_set_pos_to_home();
    }
}

void small_penguin_act_5(void) {
    f32 distToMother;
    s16 angleToMother;
    struct Object *motherPenguinObj = cur_obj_nearest_object_with_behavior(bhvTuxiesMother);
    if (motherPenguinObj != NULL) {
        if (o->oDistanceToMario < 1000.0f) {
            o->oForwardVel = 2.0f;
        } else {
            o->oForwardVel = 0.0f;
        }
        distToMother = dist_between_objects(o, motherPenguinObj);
        angleToMother = obj_angle_to_object(o, motherPenguinObj);
        if (distToMother > 200.0f) {
            cur_obj_rotate_yaw_toward(angleToMother, 0x400);
        } else {
            cur_obj_rotate_yaw_toward(angleToMother + 0x8000, 0x400);
        }
        cur_obj_init_animation_with_sound(0);
    }
    small_penguin_dive_with_mario();
}

void (*sSmallPenguinActions[])(void) = {
    small_penguin_act_0, small_penguin_act_1, small_penguin_act_2,
    small_penguin_act_3, small_penguin_act_4, small_penguin_act_5
};

void small_penguin_free_actions(void) {
    if (o->oSmallPenguinUnk88) {
        o->oAction = 5;
        o->oSmallPenguinUnk88 = FALSE;
    }
    cur_obj_update_floor_and_walls();
    cur_obj_call_action_function(sSmallPenguinActions);
    cur_obj_move_standard(-78);
    play_penguin_walking_sound(PENGUIN_WALK_BABY);
}

void bhv_small_penguin_loop(void) {
    switch (o->oHeldState) {
        case HELD_FREE:
            small_penguin_free_actions();
            break;
        case HELD_HELD:
            cur_obj_unrender_set_action_and_anim(0, 0);
            if (cur_obj_has_behavior(bhvPenguinBaby)) {
                obj_set_behavior(o, bhvSmallPenguin);
            }
            obj_copy_pos(o, gMarioObject);
            if (gGlobalTimer % 30 == 0) {
                play_sound(SOUND_OBJ2_BABY_PENGUIN_YELL, gMarioObject->header.gfx.cameraToObject);
            }
            break;
        case HELD_THROWN:
            cur_obj_get_thrown_or_placed(0, 0, 0);
            break;
        case HELD_DROPPED:
            cur_obj_get_dropped();
            break;
    }
}

/** Geo switch logic for Tuxie's mother's eyes. Cases 0-4. Interestingly, case
 * 4 is unused, and is the eye state seen in Shoshinkai 1995 footage.
 */
Gfx *geo_switch_tuxie_mother_eyes(s32 run, struct GraphNode *node, UNUSED Mat4 *mtx) {
    struct Object *obj;
    struct GraphNodeSwitchCase *switchCase;
    s32 timer;

    if (run == TRUE) {
        obj = (struct Object *) gCurGraphNodeObject;
        switchCase = (struct GraphNodeSwitchCase *) node;
        switchCase->selectedCase = 0;
        u32 isMother = obj_has_behavior(obj, bhvTuxiesMother);
        s32 babyDelivered = obj->oAction == 2;
        switchCase->selectedCase = (!isMother || babyDelivered) ? 0 : 4;

        // timer logic for blinking. uses cases 0-2.
        timer = gGlobalTimer % 50;
        if (timer < 43) {
            switchCase->selectedCase = (!isMother || babyDelivered) ? 0 : 4;
        } else if (timer < 45) {
            switchCase->selectedCase = 1;
        } else if (timer < 47) {
            switchCase->selectedCase = 2;
        } else {
            switchCase->selectedCase = 1;
        }

        /** make Tuxie's Mother have angry eyes if Mario takes the correct baby
         * after giving it back. The easiest way to check this is to see if she's
         * moving, since she only does when she's chasing Mario.
         */
        if (segmented_to_virtual(bhvTuxiesMother) == obj->behavior) {
            if (obj->oForwardVel > 5.0f) {
                switchCase->selectedCase = 3;
            }
        }
    }
    return NULL;
}
