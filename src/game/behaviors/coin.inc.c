// coin.c.inc

struct ObjectHitbox sYellowCoinHitbox = {
    /* interactType:      */ INTERACT_COIN,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 1,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 100,
    /* height:            */ 64,
    /* hurtboxRadius:     */ 0,
    /* hurtboxHeight:     */ 0,
};

s16 sCoinArrowPositions[][2] = { { 0, -150 }, {    0, -50 }, {  0,  50 }, {   0, 150 },
                                { -50, 100 }, { -100,  50 }, { 50, 100 }, { 100,  50 } };

s32 bhv_coin_sparkles_init(void) {
    if (o->oInteractStatus & INT_STATUS_INTERACTED && !(o->oInteractStatus & INT_STATUS_TOUCHED_BOB_OMB)) {
        spawn_object(o, MODEL_SPARKLES, bhvGoldenCoinSparkles);
        obj_mark_for_deletion(o);
        return TRUE;
    }
    o->oInteractStatus = INT_STATUS_NONE;
    return FALSE;
}

void bhv_yellow_coin_init(void) {
    cur_obj_set_behavior(bhvYellowCoin);
    obj_set_hitbox(o, &sYellowCoinHitbox);
    bhv_init_room();
    cur_obj_update_floor_height();
    if (500.0f < absf(o->oPosY - o->oFloorHeight)) {
        if (cur_obj_has_model(MODEL_YELLOW_COIN)) {
            cur_obj_set_model(MODEL_YELLOW_COIN_NO_SHADOW);
        } else if (cur_obj_has_model(MODEL_BLUE_COIN)) {
            cur_obj_set_model(MODEL_BLUE_COIN_NO_SHADOW);
        } else if (cur_obj_has_model(MODEL_RED_COIN)) {
            cur_obj_set_model(MODEL_RED_COIN_NO_SHADOW);
#ifdef IA8_30FPS_COINS
        } else if (cur_obj_has_model(MODEL_SILVER_COIN)) {
            cur_obj_set_model(MODEL_SILVER_COIN_NO_SHADOW);
#endif
        }
    }
    if (o->oFloorHeight < FLOOR_LOWER_LIMIT_MISC) {
        obj_mark_for_deletion(o);
    }
}

void bhv_yellow_coin_loop(void) {
    bhv_coin_sparkles_init();
    o->oAnimState++;
}

void bhv_temp_coin_loop(void) {
    o->oAnimState++;
    if (cur_obj_wait_then_blink(200, 20)) {
        obj_mark_for_deletion(o);
    }
    bhv_coin_sparkles_init();
}

void bhv_coin_init(void) {
    o->oVelY = random_float() * 10.0f + 30 + o->oCoinBaseYVel;
    o->oForwardVel = random_float() * 10.0f;
    o->oMoveAngleYaw = random_u16();
    cur_obj_set_behavior(bhvYellowCoin);
    obj_set_hitbox(o, &sYellowCoinHitbox);
    cur_obj_become_intangible();
}

void bhv_coin_loop(void) {
    struct Surface *floor;
    s16 targetYaw;
    cur_obj_update_floor_and_walls();
    cur_obj_if_hit_wall_bounce_away();
    cur_obj_move_standard(-62);
    if ((floor = o->oFloor) != NULL) {
        if (o->oMoveFlags & OBJ_MOVE_ON_GROUND) {
            o->oSubAction = 1;
        }
        if (o->oSubAction == 1) {
            o->oBounciness = 0;
            if (floor->normal.y < 0.9f) {
                targetYaw = atan2s(floor->normal.z, floor->normal.x);
                cur_obj_rotate_yaw_toward(targetYaw, 0x400);
            }
        }
    }
    if (o->oTimer == 0) {
#if defined(VERSION_US)
        cur_obj_play_sound_2(SOUND_GENERAL_COIN_SPURT_2);
#elif defined(VERSION_EU) || defined(VERSION_SH)
        cur_obj_play_sound_2(SOUND_GENERAL_COIN_SPURT_EU);
#else
        cur_obj_play_sound_2(SOUND_GENERAL_COIN_SPURT);
#endif
    }
    if (o->oVelY < 0) {
        cur_obj_become_tangible();
    }
    if (o->oMoveFlags & OBJ_MOVE_LANDED) {
#ifdef COIN_LAVA_FLICKER
        if (o->oMoveFlags & OBJ_MOVE_ABOVE_DEATH_BARRIER) {
            obj_mark_for_deletion(o);
        }
        if (o->oMoveFlags & OBJ_MOVE_ABOVE_LAVA) {
            if (cur_obj_wait_then_blink(0, 20)) {
                obj_mark_for_deletion(o);
            }
        }
#else
        if (o->oMoveFlags & (OBJ_MOVE_ABOVE_DEATH_BARRIER | OBJ_MOVE_ABOVE_LAVA)) {
            obj_mark_for_deletion(o);
        }
#endif
    }
    if (o->oMoveFlags & OBJ_MOVE_BOUNCE) {
        if (o->oCoinBounceTimer < 5) {
            cur_obj_play_sound_2(SOUND_GENERAL_COIN_DROP);
        }
        o->oCoinBounceTimer++;
    }
    if (cur_obj_wait_then_blink(400, 20)) {
        obj_mark_for_deletion(o);
    }
    bhv_coin_sparkles_init();
}

void bhv_coin_formation_spawn_loop(void) {
    if (o->oTimer == 0) {
        cur_obj_set_behavior(bhvYellowCoin);
        obj_set_hitbox(o, &sYellowCoinHitbox);
        bhv_init_room();
        if (o->oCoinSnapToGround) {
            o->oPosY += 300.0f;
            cur_obj_update_floor_height();
            if (o->oPosY < o->oFloorHeight || o->oFloorHeight < FLOOR_LOWER_LIMIT_MISC) {
                obj_mark_for_deletion(o);
            } else {
                o->oPosY = o->oFloorHeight;
            }
        } else {
            cur_obj_update_floor_height();
            if (absf(o->oPosY - o->oFloorHeight) > 250.0f) {
                cur_obj_set_model(MODEL_YELLOW_COIN_NO_SHADOW);
            }
        }
    } else {
        if (bhv_coin_sparkles_init()) {
            o->parentObj->oCoinRespawnBits |= bit_shift_left(o->oBehParams2ndByte);
        }
        o->oAnimState++;
    }
    if (o->parentObj->oAction == 2) {
        obj_mark_for_deletion(o);
    }
}

void spawn_coin_in_formation(s32 index, s32 shape) {
    struct Object *newCoin;
    Vec3i pos;
    s32 spawnCoin = TRUE;
    s32 snapToGround = TRUE;
    pos[0] = pos[1] = pos[2] = 0;
    switch (shape & 0x7) {
        case 0: // horizontal line
            pos[2] = 160 * (index - 2);
            if (index > 4) {
                spawnCoin = FALSE;
            }
            break;
        case 1: // vertical line
            snapToGround = FALSE;
            pos[1] = 160 * index * 0.8f; // 128 * index
            if (index > 4) {
                spawnCoin = FALSE;
            }
            break;
        case 2: // horizontal ring
            pos[0] = sins(index << 13) * 300.0f;
            pos[2] = coss(index << 13) * 300.0f;
            break;
        case 3: // vertical ring
            snapToGround = FALSE;
            pos[0] = coss(index << 13) * 200.0f;
            pos[1] = sins(index << 13) * 200.0f + 200.0f;
            break;
        case 4: // arrow
            pos[0] = sCoinArrowPositions[index][0];
            pos[2] = sCoinArrowPositions[index][1];
            break;
    }
    if (shape & COIN_FORMATION_FLAG_RING) {
        snapToGround = FALSE;
    }
    if (spawnCoin) {
        newCoin = spawn_object_relative(index, pos[0], pos[1], pos[2], o, MODEL_YELLOW_COIN,
                                        bhvCoinFormationSpawn);
        newCoin->oCoinSnapToGround = snapToGround;
    }
}

void bhv_coin_formation_init(void) {
    o->oCoinRespawnBits = (o->oBehParams >> 8) & 0xFF;
}

void bhv_coin_formation_loop(void) {
    s32 bitIndex;
    switch (o->oAction) {
        case 0:
            if (o->oDistanceToMario < 4000.0f) { //! hardcoded draw distance
                for (bitIndex = 0; bitIndex < 8; bitIndex++) {
                    if (!(o->oCoinRespawnBits & (1 << bitIndex))) {
                        spawn_coin_in_formation(bitIndex, o->oBehParams2ndByte);
                    }
                }
                o->oAction++;
            }
            break;
        case 1:
            if (o->oDistanceToMario > 4100.0f) { //! hardcoded draw distance
                o->oAction++;
            }
            break;
        case 2:
            o->oAction = 0;
            break;
    }

    // Casting to u8 doesn't seem to match
    set_object_respawn_info_bits(o, o->oCoinRespawnBits & RESPAWN_INFO_DONT_RESPAWN);
}

void coin_inside_boo_act_1(void) {
    cur_obj_update_floor_and_walls();
    cur_obj_if_hit_wall_bounce_away();
    if (o->oMoveFlags & OBJ_MOVE_BOUNCE) {
        cur_obj_play_sound_2(SOUND_GENERAL_COIN_DROP);
    }
    if (o->oTimer > 90 || (o->oMoveFlags & OBJ_MOVE_LANDED)) {
        obj_set_hitbox(o, &sYellowCoinHitbox);
        cur_obj_become_tangible();
        cur_obj_set_behavior(bhvYellowCoin);
    }
    cur_obj_move_standard(-30);
    bhv_coin_sparkles_init();
    if (cur_obj_has_model(MODEL_BLUE_COIN)) {
        o->oDamageOrCoinValue = 5;
    }
    if (cur_obj_wait_then_blink(400, 20)) {
        obj_mark_for_deletion(o);
    }
}

void coin_inside_boo_act_0(void) {
    s16 marioMoveYaw;
    struct Object *parent = o->parentObj;
    cur_obj_become_intangible();
    if (o->oTimer == 0 && gCurrLevelNum == LEVEL_BBH) {
        cur_obj_set_model(MODEL_BLUE_COIN);
        cur_obj_scale(0.7f);
    }
    obj_copy_pos(o, parent);
    if (parent->oBooDeathStatus == BOO_DEATH_STATUS_DYING) {
        o->oAction = 1;
        marioMoveYaw = gMarioObject->oMoveAngleYaw;
        o->oVelX = sins(marioMoveYaw) * 3.0f;
        o->oVelZ = coss(marioMoveYaw) * 3.0f;
        o->oVelY = 35.0f;
    }
}

void (*sCoinInsideBooActions[])(void) = { coin_inside_boo_act_0, coin_inside_boo_act_1 };

void bhv_coin_inside_boo_loop(void) {
    cur_obj_call_action_function(sCoinInsideBooActions);
}

void bhv_coin_sparkles_loop(void) {
    cur_obj_scale(0.6f);
}

void bhv_golden_coin_sparkles_loop(void) {
    struct Object *sparkleObj;
    sparkleObj = spawn_object(o, MODEL_SPARKLES, bhvCoinSparkles);
    sparkleObj->oPosX += random_float() * 30.0f - 15.0f;
    sparkleObj->oPosZ += random_float() * 30.0f - 15.0f;
}
