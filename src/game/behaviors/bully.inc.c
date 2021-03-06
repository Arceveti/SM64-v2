// bully.c.inc

static struct ObjectHitbox sSmallBullyHitbox = {
    /* interactType:      */ INTERACT_BULLY,
    /* downOffset:        */   0,
    /* damageOrCoinValue: */   1,
    /* health:            */   0,
    /* numLootCoins:      */   0,
    /* radius:            */  73,
    /* height:            */ 123,
    /* hurtboxRadius:     */  63,
    /* hurtboxHeight:     */ 113,
};

static struct ObjectHitbox sBigBullyHitbox = {
    /* interactType:      */ INTERACT_BULLY,
    /* downOffset:        */   0,
    /* damageOrCoinValue: */   1,
    /* health:            */   0,
    /* numLootCoins:      */   0,
    /* radius:            */ 115,
    /* height:            */ 235,
    /* hurtboxRadius:     */ 105,
    /* hurtboxHeight:     */ 225,
};

void bhv_small_bully_init(void) {
    cur_obj_init_animation(BULLY_ANIM_WALKING);
    o->oHomeX            = o->oPosX;
    o->oHomeZ            = o->oPosZ;
    o->oBehParams2ndByte = BULLY_BP_SIZE_SMALL;
    o->oGravity          = 4.0f;
    o->oFriction         = 0.91f;
    o->oBuoyancy         = 1.3f;
    obj_set_hitbox(o, &sSmallBullyHitbox);
}

void bhv_big_bully_init(void) {
    cur_obj_init_animation(BULLY_ANIM_WALKING);
    vec3_copy(&o->oHomeVec, &o->oPosVec);
    o->oBehParams2ndByte = BULLY_BP_SIZE_BIG;
    o->oGravity          = 5.0f;
    o->oFriction         = 0.93f;
    o->oBuoyancy         = 1.3f;
    obj_set_hitbox(o, &sBigBullyHitbox);
}

void bully_check_mario_collision(void) {
    if ((o->oAction != OBJ_ACT_LAVA_DEATH)
     && (o->oAction != OBJ_ACT_DEATH_PLANE_DEATH)
     && (o->oInteractStatus & INT_STATUS_INTERACTED)) {
        cur_obj_play_sound_2((o->oBehParams2ndByte == BULLY_BP_SIZE_SMALL) ? SOUND_OBJ2_SMALL_BULLY_ATTACKED : SOUND_OBJ2_LARGE_BULLY_ATTACKED);
        o->oInteractStatus &= ~INT_STATUS_INTERACTED;
        o->oAction          = BULLY_ACT_KNOCKBACK;
        o->oFlags          &= ~OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW; /* bit 3 */
        cur_obj_init_animation(BULLY_ANIM_BOAST);
        o->oBullyMarioCollisionAngle = o->oMoveAngleYaw;
    }
}

void bully_act_chase_mario(void) {
    f32 homeX = o->oHomeX;
    f32 posY  = o->oPosY;
    f32 homeZ = o->oHomeZ;
    if (o->oTimer < 10) {
        o->oForwardVel = 3.0f;
        obj_turn_toward_object(o, gMarioObject, O_MOVE_ANGLE_YAW_INDEX, DEG(22.5));
    } else if (o->oBehParams2ndByte == BULLY_BP_SIZE_SMALL) {
        o->oForwardVel = 20.0f;
        if (o->oTimer >= 31) o->oTimer = 0;
    } else {
        o->oForwardVel = 30.0f;
        if (o->oTimer >= 36) o->oTimer = 0;
    }
    if (!is_point_within_radius_of_mario(homeX, posY, homeZ, 1000)) {
        o->oAction = BULLY_ACT_PATROL;
        cur_obj_init_animation(BULLY_ANIM_WALKING);
    }
}

void bully_act_knockback(void) {
    if ((o->oForwardVel < 10.0f) && ((s32) o->oVelY == 0.0f)) {
        o->oForwardVel   = 1.0f;
        o->oBullyKBTimerAndMinionKOCounter++;
        o->oFlags       |= OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW; /* bit 3 */
        o->oMoveAngleYaw = o->oFaceAngleYaw;
        obj_turn_toward_object(o, gMarioObject, O_MOVE_ANGLE_YAW_INDEX, 0x500);
    } else {
        o->header.gfx.animInfo.animFrame = 0;
    }
    if (o->oBullyKBTimerAndMinionKOCounter == 18) {
        o->oAction = BULLY_ACT_CHASE_MARIO;
        o->oBullyKBTimerAndMinionKOCounter = 0;
        cur_obj_init_animation(BULLY_ANIM_RUNNING);
    }
}

void bully_act_back_up(void) {
    if (o->oTimer == 0) {
        o->oFlags        &= ~OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW; /* bit 3 */
        o->oMoveAngleYaw += DEG(180);
    }
    o->oForwardVel = 5.0f;
    //! bully_backup_check() happens after this function, and has the potential to reset
    //  the bully's action to BULLY_ACT_BACK_UP. Because the back up action is only
    //  set to end when the timer EQUALS 15, if this happens on that frame, the bully
    //  will be stuck in BULLY_ACT_BACK_UP forever until Mario hits it or its death
    //  conditions are activated. However because its angle is set to its facing angle,
    //  it will walk forward instead of backing up.
    if (o->oTimer == 15) {
        o->oMoveAngleYaw = o->oFaceAngleYaw;
        o->oFlags |= OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW; /* bit 3 */
        o->oAction = BULLY_ACT_PATROL;
    }
}

void bully_backup_check(ColFlags collisionFlags) {
    if (!(collisionFlags & OBJ_COL_FLAG_NO_Y_VEL) && (o->oAction != BULLY_ACT_KNOCKBACK)) {/* bit 3 */
        o->oPosX   = o->oBullyPrevX;
        o->oPosZ   = o->oBullyPrevZ;
        o->oAction = BULLY_ACT_BACK_UP;
    }
}

void bully_play_stomping_sound(void) {
    AnimFrame16 animFrame = o->header.gfx.animInfo.animFrame;
    switch (o->oAction) {
        case BULLY_ACT_PATROL:      if ((animFrame == 0) || (animFrame == 12)) cur_obj_play_sound_2((o->oBehParams2ndByte == BULLY_BP_SIZE_SMALL) ? SOUND_OBJ_BULLY_WALK_SMALL : SOUND_OBJ_BULLY_WALK_LARGE); break;
        case BULLY_ACT_CHASE_MARIO: // fall through
        case BULLY_ACT_BACK_UP:     if ((animFrame == 0) || (animFrame ==  5)) cur_obj_play_sound_2((o->oBehParams2ndByte == BULLY_BP_SIZE_SMALL) ? SOUND_OBJ_BULLY_WALK_SMALL : SOUND_OBJ_BULLY_WALK_LARGE); break;
    }
}

void bully_step(void) {
    ColFlags collisionFlags = object_step();
    bully_backup_check(collisionFlags);
    bully_play_stomping_sound();
    obj_check_floor_death(collisionFlags, sObjFloor);
    if ((o->oBullySubtype & BULLY_STYPE_CHILL) && (o->oPosY < 1030.0f)) o->oAction = OBJ_ACT_LAVA_DEATH;
}

void bully_spawn_coin(void) {
    struct Object *coin = spawn_object(o, MODEL_YELLOW_COIN, bhvMovingYellowCoin);
#ifdef VERSION_JP // TODO: maybe move this ifdef logic to the header?
    cur_obj_play_sound_2(SOUND_GENERAL_COIN_SPURT_JP);
#elif defined(VERSION_EU) || defined(VERSION_SH)
    cur_obj_play_sound_2(SOUND_GENERAL_COIN_SPURT_EU_SH);
#else
    cur_obj_play_sound_2(SOUND_GENERAL_COIN_SPURT_US);
#endif
    coin->oForwardVel   =  10.0f;
    coin->oVelY         = 100.0f;
    coin->oPosY         = (o->oPosY + 310.0f);
    coin->oMoveAngleYaw = ((f32)(o->oBullyMarioCollisionAngle + DEG(180)) + (random_float() * 1024.0f));
}

void bully_act_level_death(void) {
    if (obj_lava_death()) {
        if (o->oBehParams2ndByte == BULLY_BP_SIZE_SMALL) {
            if (o->oBullySubtype == BULLY_STYPE_MINION) o->parentObj->oBullyKBTimerAndMinionKOCounter++;
            bully_spawn_coin();
        } else {
            spawn_mist_particles();
            if (o->oBullySubtype == BULLY_STYPE_CHILL) {
                spawn_default_star(130.0f, 1600.0f, -4335.0f);
            } else {
                spawn_default_star(  0.0f,  950.0f, -6800.0f);
                spawn_object_abs_with_rot(o, 0, MODEL_NONE, bhvLllTumblingBridge, 0, 154, -5631, 0x0, 0x0, 0x0);
            }
        }
    }
}

void bhv_bully_loop(void) {
    vec3_copy(&o->oBullyPrevVec, &o->oPosVec);
    //! Because this function runs no matter what, Mario is able to interrupt the bully's
    //  death action by colliding with it. Since the bully hitbox is tall enough to collide
    //  with Mario even when it is under a lava floor, this can get the bully stuck OOB
    //  if there is nothing under the lava floor.
    bully_check_mario_collision();
    switch (o->oAction) {
        case BULLY_ACT_PATROL:
            o->oForwardVel = 5.0f;
            if (obj_return_home_if_safe(o, o->oHomeX, o->oPosY, o->oHomeZ, 800)) {
                o->oAction = BULLY_ACT_CHASE_MARIO;
                cur_obj_init_animation(BULLY_ANIM_RUNNING);
            }
                                                                    bully_step(); break;
        case BULLY_ACT_CHASE_MARIO:     bully_act_chase_mario();    bully_step(); break;
        case BULLY_ACT_KNOCKBACK:       bully_act_knockback();      bully_step(); break;
        case BULLY_ACT_BACK_UP:         bully_act_back_up();        bully_step(); break;
        case OBJ_ACT_LAVA_DEATH:        bully_act_level_death();                  break;
        case OBJ_ACT_DEATH_PLANE_DEATH: obj_mark_for_deletion(o);                 break;
    }
    set_object_visibility(o, 3000);
}

void big_bully_spawn_minion(s32 x, s32 y, s32 z, Angle ry) {
    struct Object *bully     = spawn_object_abs_with_rot(o, 0, MODEL_BULLY, bhvSmallBully, x, y, z, 0x0, ry, 0x0);
    bully->oBullySubtype     = BULLY_STYPE_MINION;
    bully->oBehParams2ndByte = BULLY_BP_SIZE_SMALL;
}

void bhv_big_bully_with_minions_init(void) {
    big_bully_spawn_minion(4454, 307, -5426, 0x0);
    big_bully_spawn_minion(3840, 307, -6041, 0x0);
    big_bully_spawn_minion(3226, 307, -5426, 0x0);
    o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
    cur_obj_become_intangible();
    o->oAction = BULLY_ACT_INACTIVE;
}

void big_bully_spawn_star(void) {
    if (obj_lava_death()) {
        spawn_mist_particles();
        spawn_default_star(3700.0f, 600.0f, -5500.0f);
    }
}

void bhv_big_bully_with_minions_loop(void) {
    ColFlags collisionFlags;
    vec3_copy(&o->oBullyPrevVec, &o->oPosVec);
    bully_check_mario_collision();
    switch (o->oAction) {
        case BULLY_ACT_PATROL:
            o->oForwardVel = 5.0f;
            if (obj_return_home_if_safe(o, o->oHomeX, o->oPosY, o->oHomeZ, 1000)) {
                o->oAction = BULLY_ACT_CHASE_MARIO;
                cur_obj_init_animation(BULLY_ANIM_RUNNING);
            }
                                                             bully_step(); break;
        case BULLY_ACT_CHASE_MARIO: bully_act_chase_mario(); bully_step(); break;
        case BULLY_ACT_KNOCKBACK:   bully_act_knockback();   bully_step(); break;
        case BULLY_ACT_BACK_UP:     bully_act_back_up();     bully_step(); break;
        case BULLY_ACT_INACTIVE:
            //! The Big Bully that spawns from killing its 3 minions uses the knockback timer
            //  for counting the number of dead minions. This means that when it activates,
            //  the knockback timer is at 3 instead of 0. So the bully knockback time will
            //  be reduced by 3 frames (16.67%) on the first hit.
            if (o->oBullyKBTimerAndMinionKOCounter == 3) {
                play_puzzle_jingle();
                if (o->oTimer >= 91) {
                    o->oAction                         = BULLY_ACT_ACTIVATE_AND_FALL;
                    o->oBullyKBTimerAndMinionKOCounter = 0;
                }
            }
            break;
        case BULLY_ACT_ACTIVATE_AND_FALL:
            collisionFlags = object_step();
            /* bits 0 and 3 */
            if ((collisionFlags & OBJ_COL_FLAGS_LANDED) == OBJ_COL_FLAGS_LANDED) o->oAction = BULLY_ACT_PATROL;
            if (collisionFlags == OBJ_COL_FLAG_GROUNDED) {
                cur_obj_play_sound_2(SOUND_OBJ_THWOMP);
                set_camera_shake_from_point(SHAKE_POS_SMALL, &o->oPosVec);
                spawn_mist_particles();
            }
            o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
            cur_obj_become_tangible();
            break;
        case OBJ_ACT_LAVA_DEATH:        big_bully_spawn_star();   break;
        case OBJ_ACT_DEATH_PLANE_DEATH: obj_mark_for_deletion(o); break;
    }
}
