// bobomb.c.inc

static struct ObjectHitbox sBobombHitbox = {
    /* interactType:      */ INTERACT_GRABBABLE,
    /* downOffset:        */   0,
    /* damageOrCoinValue: */   0,
    /* health:            */   0,
    /* numLootCoins:      */   0,
    /* radius:            */  65,
    /* height:            */ 113,
    /* hurtboxRadius:     */   0,
    /* hurtboxHeight:     */   0,
};

void bhv_bobomb_init(void) {
    o->oGravity            = 2.5f;
    o->oFriction           = 0.8f;
    o->oBuoyancy           = 1.3f;
    o->oInteractionSubtype = INT_SUBTYPE_KICKABLE;
}

void bobomb_spawn_coin(void) {
    if (!((o->oBehParams >> 8) & 0x1)) { //! param names?
        obj_spawn_yellow_coins(o, 1);
        o->oBehParams = 0x100;
        set_object_respawn_info_bits(o, RESPAWN_INFO_TYPE_32);
    }
}

void bobomb_act_explode(void) {
    struct Object *explosion;
#ifdef FIX_BOMB_CLIP
    cur_obj_become_intangible();
#endif
    if (o->oTimer < 5) {
        cur_obj_scale(1.0f + (f32) o->oTimer / 5.0f);
    } else {
        explosion                 = spawn_object(o, MODEL_EXPLOSION, bhvExplosion);
        explosion->oGraphYOffset += 100.0f;
        bobomb_spawn_coin();
        create_respawner(MODEL_BLACK_BOBOMB, bhvBobomb, 3000);
        obj_mark_for_deletion(o);
    }
}

void bobomb_check_interactions(void) {
    obj_set_hitbox(o, &sBobombHitbox);
    if (o->oInteractStatus & INT_STATUS_INTERACTED) {
        if (o->oInteractStatus & INT_STATUS_MARIO_KNOCKBACK_DMG) {
            o->oMoveAngleYaw = gMarioObject->header.gfx.angle[1];
            o->oForwardVel   = 25.0f;
            o->oVelY         = 30.0f;
            o->oAction       = BOBOMB_ACT_LAUNCHED;
        }
        if (o->oInteractStatus & INT_STATUS_TOUCHED_BOB_OMB) o->oAction = BOBOMB_ACT_EXPLODE;
        o->oInteractStatus = INT_STATUS_NONE;
    }
    if (obj_attack_collided_from_other_object(o)) o->oAction = BOBOMB_ACT_EXPLODE;
}

void bobomb_act_patrol(void) {
    o->oForwardVel     = 5.0f;
    ColFlags collisionFlags = object_step();
    if (obj_return_home_if_safe(o, o->oHomeX, o->oHomeY, o->oHomeZ, 400) && obj_check_if_facing_toward_angle(o->oMoveAngleYaw, o->oAngleToMario, DEG(45))) {
        o->oBobombFuseLit = TRUE;
        o->oAction        = BOBOMB_ACT_CHASE_MARIO;
    }
    obj_check_floor_death(collisionFlags, sObjFloor);
}

void bobomb_act_chase_mario(void) {
    AnimFrame16 animFrame   = ++o->header.gfx.animInfo.animFrame;
    o->oForwardVel          = 20.0f;
    ColFlags collisionFlags = object_step();
    if ((animFrame == 5) || (animFrame == 16)) cur_obj_play_sound_2(SOUND_OBJ_BOBOMB_WALK);
    obj_turn_toward_object(o, gMarioObject, O_MOVE_ANGLE_YAW_INDEX, DEG(11.25));
    obj_check_floor_death(collisionFlags, sObjFloor);
}

void bobomb_act_launched(void) {
    ColFlags collisionFlags = object_step();
#ifdef FIX_BOMB_CLIP
    cur_obj_become_intangible();
#endif
    if (collisionFlags & OBJ_COL_FLAG_GROUNDED) o->oAction = BOBOMB_ACT_EXPLODE; /* bit 0 */
}

void generic_bobomb_free_loop(void) {
    switch (o->oAction) {
        case BOBOMB_ACT_PATROL:      bobomb_act_patrol();      break;
        case BOBOMB_ACT_LAUNCHED:    bobomb_act_launched();    break;
        case BOBOMB_ACT_CHASE_MARIO: bobomb_act_chase_mario(); break;
        case BOBOMB_ACT_EXPLODE:     bobomb_act_explode();     break;
        case OBJ_ACT_LAVA_DEATH:
            if (obj_lava_death()) create_respawner(MODEL_BLACK_BOBOMB, bhvBobomb, 3000);
            break;
        case OBJ_ACT_DEATH_PLANE_DEATH:
            obj_mark_for_deletion(o);
            create_respawner(MODEL_BLACK_BOBOMB, bhvBobomb, 3000);
            break;
    }
    bobomb_check_interactions();
    if (o->oBobombFuseTimer >= 151) o->oAction = BOBOMB_ACT_EXPLODE;
}

void stationary_bobomb_free_loop(void) {
    switch (o->oAction) {
        case BOBOMB_ACT_LAUNCHED: bobomb_act_launched(); break;
        case BOBOMB_ACT_EXPLODE:  bobomb_act_explode();  break;
        case OBJ_ACT_LAVA_DEATH:
            if (obj_lava_death()) create_respawner(MODEL_BLACK_BOBOMB, bhvBobomb, 3000);
            break;
        case OBJ_ACT_DEATH_PLANE_DEATH:
            obj_mark_for_deletion(o);
            create_respawner(MODEL_BLACK_BOBOMB, bhvBobomb, 3000);
            break;
    }
    bobomb_check_interactions();
    if (o->oBobombFuseTimer >= 151) o->oAction = BOBOMB_ACT_EXPLODE;
}

void bobomb_free_loop(void) {
    if (o->oBehParams2ndByte == BOBOMB_BP_STYPE_GENERIC) {
        generic_bobomb_free_loop();
    } else {
        stationary_bobomb_free_loop();
    }
}

void bobomb_held_loop(void) {
    o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
    cur_obj_init_animation(BOBOMB_ANIM_HELD);
    cur_obj_set_pos_relative(gMarioObject, 0.0f, 60.0f, 100.0f);
    o->oBobombFuseLit = TRUE;
    if (o->oBobombFuseTimer >= 151) {
        // Although the Bob-omb's action is set to explode when the fuse timer expires,
        // bobomb_act_explode() will not execute until the bob-omb's held state changes.
        // This allows the Bob-omb to be regrabbed indefinitely.
        gMarioObject->oInteractStatus |= INT_STATUS_MARIO_DROP_OBJECT;
        o->oAction = BOBOMB_ACT_EXPLODE;
#ifdef FIX_BOMB_CLIP
        bobomb_act_explode();
#endif
    }
}

void bobomb_dropped_loop(void) {
    cur_obj_get_dropped();
    o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
    cur_obj_init_animation(BOBOMB_ANIM_WALKING);
    o->oHeldState = HELD_FREE;
    o->oAction    = BOBOMB_ACT_PATROL;
}

void bobomb_thrown_loop(void) {
    cur_obj_enable_rendering();
    o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
    o->oHeldState             =  HELD_FREE;
    o->oFlags                &= ~OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW; /* bit 3 */
    o->oForwardVel            = 25.0f;
    o->oVelY                  = 20.0f;
    o->oAction                = BOBOMB_ACT_LAUNCHED;
}

void curr_obj_random_blink(s32 *blinkTimer) {
    if (*blinkTimer == 0) {
        if ((s16)(random_float() * 100.0f) == 0) {
            o->oAnimState = BOBOMB_ANIM_STATE_EYES_CLOSED;
            *blinkTimer = 1;
        }
    } else {
        (*blinkTimer)++;
        if (*blinkTimer >=  6) o->oAnimState = BOBOMB_ANIM_STATE_EYES_OPEN;
        if (*blinkTimer >= 11) o->oAnimState = BOBOMB_ANIM_STATE_EYES_CLOSED;
        if (*blinkTimer >= 16) {
            o->oAnimState = BOBOMB_ANIM_STATE_EYES_OPEN;
            *blinkTimer   = 0;
        }
    }
}

void bhv_bobomb_loop(void) {
    s8 dustPeriodMinus1;
    if (is_point_within_radius_of_mario(o->oPosX, o->oPosY, o->oPosZ, 4000)) {
        switch (o->oHeldState) {
            case HELD_FREE:    bobomb_free_loop();    break;
            case HELD_HELD:    bobomb_held_loop();    break;
            case HELD_THROWN:  bobomb_thrown_loop();  break;
            case HELD_DROPPED: bobomb_dropped_loop(); break;
        }
        curr_obj_random_blink(&o->oBobombBlinkTimer);
        if (o->oBobombFuseLit) {
            dustPeriodMinus1 = ((o->oBobombFuseTimer >= 121) ? 1 : 7);
            if (!(dustPeriodMinus1 & o->oBobombFuseTimer)) spawn_object(o, MODEL_SMOKE, bhvBobombFuseSmoke); /* oBobombFuseTimer % 2 or oBobombFuseTimer % 8 */
            cur_obj_play_sound_1(SOUND_AIR_BOBOMB_LIT_FUSE);
            o->oBobombFuseTimer++;
        }
    }
}

void bhv_bobomb_fuse_smoke_init(void) {
    o->oPosX += ((s32)(random_float() * 80.0f) - 40);
    o->oPosY += ((s32)(random_float() * 80.0f) + 60);
    o->oPosZ += ((s32)(random_float() * 80.0f) - 40);
    cur_obj_scale(1.2f);
}

void bhv_bobomb_buddy_init(void) {
    o->oGravity            = 2.5f;
    o->oFriction           = 0.8f;
    o->oBuoyancy           = 1.3f;
    o->oInteractionSubtype = INT_SUBTYPE_NPC;
}

void bobomb_buddy_act_idle(void) {
    AnimFrame16 animFrame = o->header.gfx.animInfo.animFrame;
    vec3_copy(&o->oBobombBuddyPosCopyVec, &o->oPosVec);
    object_step();
    if ((animFrame == 5) || (animFrame == 16))       cur_obj_play_sound_2(SOUND_OBJ_BOBOMB_WALK);
    if (o->oDistanceToMario < 1000.0f)               o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oAngleToMario, 0x140);
    if (o->oInteractStatus == INT_STATUS_INTERACTED) o->oAction       = BOBOMB_BUDDY_ACT_TURN_TO_TALK;
}

/**
 * Function for the Bob-omb Buddy cannon guy.
 * dialogFirstText is the first dialogID called when Bob-omb Buddy
 * starts to talk to Mario to prepare the cannon(s) for him.
 * Then the camera goes to the nearest cannon, to play the "prepare cannon" cutscene
 * dialogSecondText is called after Bob-omb Buddy has the cannon(s) ready and
 * then tells Mario that is "Ready for blastoff".
 */
void bobomb_buddy_cannon_dialog(DialogID dialogFirstText, DialogID dialogSecondText) {
    switch (o->oBobombBuddyCannonStatus) {
        case BOBOMB_BUDDY_CANNON_UNOPENED:
            if (cutscene_object_with_dialog(CUTSCENE_DIALOG, o, dialogFirstText) != 0) {
                save_file_set_cannon_unlocked();
                o->oBobombBuddyCannonStatus = ((cur_obj_nearest_object_with_behavior(bhvCannonClosed)) ? BOBOMB_BUDDY_CANNON_OPENING : BOBOMB_BUDDY_CANNON_STOP_TALKING);
            }
            break;
        case BOBOMB_BUDDY_CANNON_OPENING:
            if (cutscene_object(CUTSCENE_PREPARE_CANNON, cur_obj_nearest_object_with_behavior(bhvCannonClosed)) == -1) o->oBobombBuddyCannonStatus = BOBOMB_BUDDY_CANNON_OPENED;
            break;
        case BOBOMB_BUDDY_CANNON_OPENED:
            if (cutscene_object_with_dialog(CUTSCENE_DIALOG, o, dialogSecondText)) o->oBobombBuddyCannonStatus = BOBOMB_BUDDY_CANNON_STOP_TALKING;
            break;
        case BOBOMB_BUDDY_CANNON_STOP_TALKING:
            set_mario_npc_dialog(MARIO_DIALOG_STOP);
            o->activeFlags                 &= ~ACTIVE_FLAG_INITIATED_TIME_STOP;
            o->oBobombBuddyHasTalkedToMario =  BOBOMB_BUDDY_HAS_TALKED;
            o->oInteractStatus              =  INT_STATUS_NONE;
            o->oAction                      =  BOBOMB_BUDDY_ACT_IDLE;
            o->oBobombBuddyCannonStatus     =  BOBOMB_BUDDY_CANNON_OPENED;
            break;
    }
}

void bobomb_buddy_act_talk(void) {
    if (set_mario_npc_dialog(MARIO_DIALOG_LOOK_FRONT) == MARIO_DIALOG_STATUS_SPEAK) {
        o->activeFlags |= ACTIVE_FLAG_INITIATED_TIME_STOP;
        switch (o->oBobombBuddyRole) {
            case BOBOMB_BUDDY_ROLE_ADVICE:
                if (cutscene_object_with_dialog(CUTSCENE_DIALOG, o, o->oBehParams2ndByte) != BOBOMB_BUDDY_BP_STYPE_GENERIC) {
                    set_mario_npc_dialog(MARIO_DIALOG_STOP);
                    o->activeFlags                 &= ~ACTIVE_FLAG_INITIATED_TIME_STOP;
                    o->oBobombBuddyHasTalkedToMario =  BOBOMB_BUDDY_HAS_TALKED;
                    o->oInteractStatus              =  INT_STATUS_NONE;
                    o->oAction                      =  BOBOMB_BUDDY_ACT_IDLE;
                }
                break;
            case BOBOMB_BUDDY_ROLE_CANNON:
                if (gCurrCourseNum == COURSE_BOB) {
                    bobomb_buddy_cannon_dialog(DIALOG_004, DIALOG_105);
                } else {
                    bobomb_buddy_cannon_dialog(DIALOG_047, DIALOG_106);
                }
                break;
        }
    }
}

void bobomb_buddy_act_turn_to_talk(void) {
    AnimFrame16 animFrame = o->header.gfx.animInfo.animFrame;
    if ((animFrame == 5) || (animFrame == 16)) cur_obj_play_sound_2(SOUND_OBJ_BOBOMB_WALK);
    o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oAngleToMario, DEG(22.5));
    if ((Angle) o->oMoveAngleYaw == (Angle) o->oAngleToMario) o->oAction = BOBOMB_BUDDY_ACT_TALK;
    cur_obj_play_sound_2(SOUND_ACTION_READ_SIGN);
}

void bobomb_buddy_actions(void) {
    switch (o->oAction) {
        case BOBOMB_BUDDY_ACT_IDLE:         bobomb_buddy_act_idle();         break;
        case BOBOMB_BUDDY_ACT_TURN_TO_TALK: bobomb_buddy_act_turn_to_talk(); break;
        case BOBOMB_BUDDY_ACT_TALK:         bobomb_buddy_act_talk();         break;
    }
    set_object_visibility(o, 3000);
}

void bhv_bobomb_buddy_loop(void) {
    bobomb_buddy_actions();
    curr_obj_random_blink(&o->oBobombBuddyBlinkTimer);
    o->oInteractStatus = INT_STATUS_NONE;
}
