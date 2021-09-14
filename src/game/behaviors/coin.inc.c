// coin.c.inc

struct ObjectHitbox sYellowCoinHitbox = {
    /* interactType:      */ INTERACT_COIN,
    /* downOffset:        */   0,
    /* damageOrCoinValue: */   1,
    /* health:            */   0,
    /* numLootCoins:      */   0,
    /* radius:            */ 100,
    /* height:            */  64,
    /* hurtboxRadius:     */   0,
    /* hurtboxHeight:     */   0,
};

s16 sCoinArrowPositions[][2] = { {   0, -150 }, {    0, -50 }, {  0,  50 }, {   0, 150 },
                                 { -50,  100 }, { -100,  50 }, { 50, 100 }, { 100,  50 } };

Bool32 bhv_coin_sparkles_init(void) {
    if (o->oInteractStatus & INT_STATUS_INTERACTED && !(o->oInteractStatus & INT_STATUS_TOUCHED_BOB_OMB)) {
        spawn_object(o, MODEL_SPARKLES, bhvCoinSparklesSpawner);
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
    if (o->oFloorHeight < FLOOR_LOWER_LIMIT_MISC) obj_mark_for_deletion(o);
}

void bhv_yellow_coin_loop(void) {
    bhv_coin_sparkles_init();
    o->oAnimState++;
}

void bhv_temp_coin_loop(void) {
    o->oAnimState++;
    if (cur_obj_wait_then_blink(200, 20)) obj_mark_for_deletion(o);
    bhv_coin_sparkles_init();
}

void bhv_coin_init(void) {
    o->oVelY         = ((random_float() * 10.0f) + 30.0f + o->oCoinBaseYVel);
    o->oForwardVel   =  (random_float() * 10.0f);
    o->oMoveAngleYaw = random_u16();
    cur_obj_set_behavior(bhvYellowCoin);
    obj_set_hitbox(o, &sYellowCoinHitbox);
    cur_obj_become_intangible();
}

void bhv_coin_loop(void) { // bhvSingleCoinGetsSpawned, bhvMrIBlueCoin
#ifndef PLATFORM_DISPLACEMENT_2_OBJECTS
    struct Surface *floor;
    Angle targetYaw;
#endif
    cur_obj_update_floor_and_walls();
    cur_obj_if_hit_wall_bounce_away();
    cur_obj_move_standard(-62);
#ifndef PLATFORM_DISPLACEMENT_2_OBJECTS
    if (((floor = o->oFloor) != NULL) && (o->oMoveFlags & OBJ_MOVE_ON_GROUND)) {
        o->oBounciness = 0;
        if (floor->normal.y < 0.9f) {
            targetYaw = SURFACE_YAW(floor);
            cur_obj_rotate_yaw_toward(targetYaw, 0x400);
        }
    }
#endif
#if defined(VERSION_US)
    if (o->oTimer == 0) cur_obj_play_sound_2(SOUND_GENERAL_COIN_SPURT_US);
#elif defined(VERSION_EU) || defined(VERSION_SH)
    if (o->oTimer == 0) cur_obj_play_sound_2(SOUND_GENERAL_COIN_SPURT_EU_SH);
#else
    if (o->oTimer == 0) cur_obj_play_sound_2(SOUND_GENERAL_COIN_SPURT_JP);
#endif
    if (o->oVelY < 0.0f) cur_obj_become_tangible();
    if (o->oMoveFlags & OBJ_MOVE_LANDED) {
#ifdef COIN_LAVA_FLICKER
        if (o->oMoveFlags & OBJ_MOVE_ABOVE_DEATH_BARRIER) obj_mark_for_deletion(o);
        if (o->oMoveFlags & OBJ_MOVE_ABOVE_LAVA && cur_obj_wait_then_blink(0, 20)) obj_mark_for_deletion(o);
#else
        if (o->oMoveFlags & (OBJ_MOVE_ABOVE_DEATH_BARRIER | OBJ_MOVE_ABOVE_LAVA)) obj_mark_for_deletion(o);
#endif
    }
    if (o->oMoveFlags & OBJ_MOVE_BOUNCE) {
        if (o->oCoinBounceTimer < 5) cur_obj_play_sound_2(SOUND_GENERAL_COIN_DROP);
        o->oCoinBounceTimer++;
    }
    if (cur_obj_wait_then_blink(400, 20))  obj_mark_for_deletion(o);
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
            if ((o->oPosY < o->oFloorHeight) || (o->oFloorHeight < FLOOR_LOWER_LIMIT_MISC)) {
                obj_mark_for_deletion(o);
            } else {
                o->oPosY = o->oFloorHeight;
            }
        } else {
            cur_obj_update_floor_height();
            if (absf(o->oPosY - o->oFloorHeight) > 250.0f) cur_obj_set_model(MODEL_YELLOW_COIN_NO_SHADOW);
        }
    } else {
        if (bhv_coin_sparkles_init()) o->parentObj->oCoinRespawnBits |= (1 << o->oBehParams2ndByte);
        o->oAnimState++;
    }
    if (o->parentObj->oAction == COIN_FORMATION_ACT_DEACTIVATE) obj_mark_for_deletion(o);
}

void spawn_coin_in_formation(s32 index, s32 shape) {
    struct Object *newCoin;
    Vec3i pos;
    Bool32 spawnCoin    = TRUE;
    Bool32 snapToGround = TRUE;
    vec3_zero(pos);
    switch (shape & 0x7) {
        case COIN_FORMATION_BP_HORIZONTAL_LINE:
            pos[2] = (160 * (index - 2));
            if (index > 4) spawnCoin = FALSE;
            break;
        case COIN_FORMATION_BP_VERTICAL_LINE:
            snapToGround = FALSE;
            pos[1] = (160 * index * 0.8f); // 128 * index
            if (index > 4) spawnCoin = FALSE;
            break;
        case COIN_FORMATION_BP_HORIZONTAL_RING:
            pos[0] = (sins(index << 13) * 300.0f);
            pos[2] = (coss(index << 13) * 300.0f);
            break;
        case COIN_FORMATION_BP_VERTICAL_RING:
            snapToGround = FALSE;
            pos[0] =  (coss(index << 13) * 200.0f);
            pos[1] = ((sins(index << 13) * 200.0f) + 200.0f);
            break;
        case COIN_FORMATION_BP_ARROW:
            pos[0] = sCoinArrowPositions[index][0];
            pos[2] = sCoinArrowPositions[index][1];
            break;
    }
    if (shape & 0x10) snapToGround = FALSE;
    if (spawnCoin) {
        // Spawn the coin at the index's location
        newCoin = spawn_object_relative(index, pos[0], pos[1], pos[2], o, MODEL_YELLOW_COIN, bhvCoinFormationSpawn);
        newCoin->oCoinSnapToGround = snapToGround;
    }
}

void bhv_coin_formation_init(void) {
    o->oCoinRespawnBits = ((o->oBehParams >> 8) & 0xFF);
}

void bhv_coin_formation_loop(void) {
    s32 bitIndex;
    switch (o->oAction) {
        case COIN_FORMATION_ACT_INACTIVE:
            if (o->oDistanceToMario < 4000.0f) { //! hardcoded draw distance
                for ((bitIndex = 0); (bitIndex < 8); (bitIndex++)) if (!(o->oCoinRespawnBits & (1 << bitIndex))) spawn_coin_in_formation(bitIndex, o->oBehParams2ndByte);
                o->oAction = COIN_FORMATION_ACT_ACTIVE;
            }
            break;
        case COIN_FORMATION_ACT_ACTIVE:
            if (o->oDistanceToMario > 4100.0f) o->oAction = COIN_FORMATION_ACT_DEACTIVATE; //! hardcoded draw distance
            break;
        case COIN_FORMATION_ACT_DEACTIVATE:
            o->oAction = COIN_FORMATION_ACT_INACTIVE;
            break;
    }
    //? Casting to u8 doesn't seem to match
    set_object_respawn_info_bits(o, (o->oCoinRespawnBits & RESPAWN_INFO_DONT_RESPAWN));
}

void coin_inside_boo_act_dropped(void) {
    cur_obj_update_floor_and_walls();
    cur_obj_if_hit_wall_bounce_away();
    if (o->oMoveFlags & OBJ_MOVE_BOUNCE) cur_obj_play_sound_2(SOUND_GENERAL_COIN_DROP);
    if ((o->oTimer > 90) || (o->oMoveFlags & OBJ_MOVE_LANDED)) {
        obj_set_hitbox(o, &sYellowCoinHitbox);
        cur_obj_become_tangible();
        cur_obj_set_behavior(bhvYellowCoin);
    }
    cur_obj_move_standard(-30);
    bhv_coin_sparkles_init();
    if (cur_obj_has_model(MODEL_BLUE_COIN)) o->oDamageOrCoinValue = 5;
    if (cur_obj_wait_then_blink(400, 20)) obj_mark_for_deletion(o);
}

void coin_inside_boo_act_carried(void) {
    Angle marioMoveYaw;
    struct Object *parent = o->parentObj;
    cur_obj_become_intangible();
    if ((o->oTimer == 0) && (gCurrLevelNum == LEVEL_BBH)) {
        cur_obj_set_model(MODEL_BLUE_COIN);
        cur_obj_scale(0.7f);
    }
    obj_copy_pos(o, parent);
    if (parent->oBooDeathStatus == BOO_DEATH_STATUS_DYING) {
        o->oAction   = COIN_INSIDE_BOO_ACT_DROPPED;
        marioMoveYaw = gMarioObject->oMoveAngleYaw;
        o->oVelX     = (sins(marioMoveYaw) * 3.0f);
        o->oVelZ     = (coss(marioMoveYaw) * 3.0f);
        o->oVelY     = 35.0f;
    }
}

void (*sCoinInsideBooActions[])(void) = { coin_inside_boo_act_carried, coin_inside_boo_act_dropped };

void bhv_coin_inside_boo_loop(void) {
    cur_obj_call_action_function(sCoinInsideBooActions);
}

void bhv_coin_sparkles_loop(void) {
    cur_obj_scale(0.6f);
}

void bhv_coin_sparkles_spawner_loop(void) {
#ifdef PUPPYLIGHTS
    cur_obj_set_light_properties_default(160, COLOR_RGBA32_COIN_YELLOW_LIGHT);
    cur_obj_enable_light();
#endif
    struct Object *sparkleObj;
    sparkleObj = spawn_object(o, MODEL_SPARKLES, bhvCoinSparkles);
    sparkleObj->oPosX += ((random_float() * 30.0f) - 15.0f);
    sparkleObj->oPosZ += ((random_float() * 30.0f) - 15.0f);
}
