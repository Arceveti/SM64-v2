// coin.c.inc

static struct ObjectHitbox sMovingYellowCoinHitbox = {
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

static struct ObjectHitbox sMovingBlueCoinHitbox = {
    /* interactType:      */ INTERACT_COIN,
    /* downOffset:        */   0,
    /* damageOrCoinValue: */   5,
    /* health:            */   0,
    /* numLootCoins:      */   0,
    /* radius:            */ 100,
    /* height:            */  64,
    /* hurtboxRadius:     */   0,
    /* hurtboxHeight:     */   0,
};

Bool32 coin_step(ColFlags *collisionFlagsPtr) {
    *collisionFlagsPtr = object_step();
    obj_check_floor_death(*collisionFlagsPtr, sObjFloor);
    if ((*collisionFlagsPtr & OBJ_COL_FLAG_GROUNDED)  && !(*collisionFlagsPtr & OBJ_COL_FLAG_NO_Y_VEL)) { /* bit 0, bit 3 */
        cur_obj_play_sound_2(SOUND_GENERAL_COIN_DROP);
        return TRUE;
    }
    return FALSE;
}

void moving_coin_flicker(void) {
    ColFlags collisionFlags;
    coin_step(&collisionFlags);
    obj_flicker_and_disappear(o, 0);
}

void coin_collected(void) {
    spawn_object(o, MODEL_SPARKLES, bhvCoinSparklesSpawner);
    obj_mark_for_deletion(o);
}

void bhv_moving_yellow_coin_init(void) {
    o->oGravity  = 3.0f;
    o->oFriction = 1.0f;
    o->oBuoyancy = 1.5f;
    obj_set_hitbox(o, &sMovingYellowCoinHitbox);
}

void bhv_moving_yellow_coin_loop(void) {
    ColFlags collisionFlags;
    switch (o->oAction) {
        case MOV_YCOIN_ACT_IDLE:
            coin_step(&collisionFlags);
            if (o->oTimer < 10) {
                cur_obj_become_intangible();
            } else {
                cur_obj_become_tangible();
            }
            if (o->oTimer >= 301) o->oAction = MOV_YCOIN_ACT_BLINKING;
            break;
        case MOV_YCOIN_ACT_BLINKING:
            moving_coin_flicker();
            break;
        case OBJ_ACT_LAVA_DEATH:
#ifdef COIN_LAVA_FLICKER
            moving_coin_flicker();
#else
            obj_mark_for_deletion(o);
#endif
            break;
        case OBJ_ACT_DEATH_PLANE_DEATH:
            obj_mark_for_deletion(o);
            break;
    }
#ifdef COIN_LAVA_FLICKER
    if (o->oMoveFlags & OBJ_MOVE_ABOVE_LAVA) moving_coin_flicker();
#endif
    if (o->oInteractStatus & INT_STATUS_INTERACTED) {/* bit 15 */
        coin_collected();
        o->oInteractStatus = INT_STATUS_NONE;
    }
}

void bhv_moving_blue_coin_init(void) {
    o->oGravity  = 5.0f;
    o->oFriction = 1.0f;
    o->oBuoyancy = 1.5f;
    obj_set_hitbox(o, &sMovingBlueCoinHitbox);
}

void bhv_moving_blue_coin_loop(void) {
    ColFlags collisionFlags;
    switch (o->oAction) {
        case MOV_BCOIN_ACT_STILL:
            if (is_point_within_radius_of_mario(o->oPosX, o->oPosY, o->oPosZ, 1500)) o->oAction = MOV_BCOIN_ACT_MOVING;
            break;
        case MOV_BCOIN_ACT_MOVING:
            collisionFlags = object_step();
            if (collisionFlags & OBJ_COL_FLAG_GROUNDED) {/* bit 0 */
                o->oForwardVel += 25.0f;
                if (!(collisionFlags & OBJ_COL_FLAG_NO_Y_VEL)) cur_obj_play_sound_2(SOUND_GENERAL_COIN_DROP); /* bit 3 */
            } else {
                o->oForwardVel *= 0.98f;
            }
            if (o->oForwardVel > TERMINAL_GRAVITY_VELOCITY) o->oForwardVel = TERMINAL_GRAVITY_VELOCITY;
            obj_flicker_and_disappear(o, 600);
            break;
    }
    if (o->oInteractStatus & INT_STATUS_INTERACTED) {/* bit 15 */
        coin_collected();
        o->oInteractStatus = INT_STATUS_NONE;
    }
}

void bhv_blue_coin_sliding_jumping_init(void) {
    o->oGravity  = 3.0f;
    o->oFriction = 0.98f;
    o->oBuoyancy = 1.5f;
    obj_set_hitbox(o, &sMovingBlueCoinHitbox);
}

void blue_coin_sliding_away_from_mario(void) {
    ColFlags collisionFlags;
    o->oForwardVel   = 15.0f;
    o->oMoveAngleYaw = (o->oAngleToMario + DEG(180));
    if (coin_step(&collisionFlags)) o->oVelY += 18.0f;
    if (collisionFlags & OBJ_COL_FLAG_HIT_WALL) o->oAction = MOV_BCOIN_ACT_STOPPED; /* bit 1 */
    if (!is_point_within_radius_of_mario(o->oPosX, o->oPosY, o->oPosZ, 1000)) o->oAction = MOV_BCOIN_ACT_SLOWING_DOWN;
}

void blue_coin_sliding_slow_down(void) {
    ColFlags collisionFlags;
    coin_step(&collisionFlags);
    if (is_point_within_radius_of_mario(o->oPosX, o->oPosY, o->oPosZ, 500)) o->oAction = MOV_BCOIN_ACT_MOVING;
    if (o->oTimer >= 151) o->oAction = MOV_BCOIN_ACT_STOPPED;
}

void bhv_blue_coin_sliding_loop(void) {
    ColFlags collisionFlags;
    switch (o->oAction) {
        case MOV_BCOIN_ACT_STILL:
            if (is_point_within_radius_of_mario(o->oPosX, o->oPosY, o->oPosZ, 500)) o->oAction = 1;
            set_object_visibility(o, 3000);
            break;
        case MOV_BCOIN_ACT_MOVING:
            blue_coin_sliding_away_from_mario();
            break;
        case MOV_BCOIN_ACT_SLOWING_DOWN:
            blue_coin_sliding_slow_down();
            set_object_visibility(o, 3000);
            break;
        case MOV_BCOIN_ACT_STOPPED:
            coin_step(&collisionFlags);
            if (o->oTimer >= 61) o->oAction = MOV_BCOIN_ACT_FLICKERING;
            break;
        case MOV_BCOIN_ACT_FLICKERING:
            moving_coin_flicker();
            break;
        case OBJ_ACT_LAVA_DEATH:
#ifdef COIN_LAVA_FLICKER
            o->oAction = MOV_BCOIN_ACT_FLICKERING;
#else
            obj_mark_for_deletion(o);
#endif
            break;
        case OBJ_ACT_DEATH_PLANE_DEATH:
            obj_mark_for_deletion(o);
            break;
    }
    if (o->oInteractStatus & INT_STATUS_INTERACTED) { /* bit 15 */
        coin_collected();
        o->oInteractStatus = INT_STATUS_NONE;
    }
}

void bhv_blue_coin_jumping_loop(void) {
    ColFlags collisionFlags;
    switch (o->oAction) {
        case MOV_BCOIN_ACT_STILL:
            if (o->oTimer == 0) {
                cur_obj_become_intangible();
                o->oVelY = 50.0f;
            }
            object_step();
            if (o->oTimer == 15) {
                cur_obj_become_tangible();
                o->oAction = MOV_BCOIN_ACT_MOVING;
            }
            break;
        case MOV_BCOIN_ACT_MOVING:
            blue_coin_sliding_away_from_mario();
            break;
        case MOV_BCOIN_ACT_SLOWING_DOWN:
            blue_coin_sliding_slow_down();
            set_object_visibility(o, 3000);
            break;
        case MOV_BCOIN_ACT_STOPPED:
            coin_step(&collisionFlags);
            if (o->oTimer >= 61) o->oAction = MOV_BCOIN_ACT_FLICKERING;
            break;
        case MOV_BCOIN_ACT_FLICKERING:
            moving_coin_flicker();
            break;
    }
    if (o->oInteractStatus & INT_STATUS_INTERACTED) {/* bit 15 */
        coin_collected();
        o->oInteractStatus = INT_STATUS_NONE;
    }
}
