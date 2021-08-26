// lll_hexagonal_ring.c.inc

void hexagonal_ring_spawn_flames(void) {
    struct Object *flameObj = spawn_object(o, MODEL_RED_FLAME, bhvVolcanoFlames);
    flameObj->oPosY        += 550.0f;
    flameObj->oMoveAngleYaw = ((random_u16()   << 0x10) >> 0x10);
    flameObj->oForwardVel   = ((random_float() * 40.0f) + 20.0f);
    flameObj->oVelY         = ((random_float() * 50.0f) + 10.0f);
    f32 size                = ((random_float() *  6.0f) +  3.0f);
    obj_scale(flameObj, size);
    if (random_float() < 0.1f) cur_obj_play_sound_2(SOUND_GENERAL_VOLCANO_EXPLOSION);
}

void bhv_lll_rotating_hexagonal_ring_loop(void) {
    o->oCollisionDistance = 4000.0f;
    o->oDrawingDistance   = 8000.0f;
    switch (o->oAction) {
        case LLL_HEXAGONAL_RING_ACT_MARIO_OFF_PLATFORM:
            if (gMarioObject->platform == o) o->oAction = LLL_HEXAGONAL_RING_ACT_MARIO_ON_PLATFORM;
            o->oAngleVelYaw = 0x100;
            break;
        case LLL_HEXAGONAL_RING_ACT_MARIO_ON_PLATFORM:
            o->oAngleVelYaw = (256.0f - (sins(o->oTimer << 7) * 256.0f));
            if (o->oTimer > 128) o->oAction = LLL_HEXAGONAL_RING_ACT_SPAWN_FLAMES;
            break;
        case LLL_HEXAGONAL_RING_ACT_SPAWN_FLAMES:
            if (gMarioObject->platform != o) o->oAction = LLL_HEXAGONAL_RING_ACT_MARIO_LEFT_PLATFORM;
            if (o->oTimer > 128) o->oAction++; // 3 or 4
            o->oAngleVelYaw = 0;
            hexagonal_ring_spawn_flames();
            break;
        case LLL_HEXAGONAL_RING_ACT_MARIO_LEFT_PLATFORM:
            o->oAngleVelYaw = (sins(o->oTimer << 7) * 256.0f);
            if (o->oTimer > 128) o->oAction = LLL_HEXAGONAL_RING_ACT_MARIO_OFF_PLATFORM;
            break;
        case LLL_HEXAGONAL_RING_ACT_RESET:
            o->oAction = LLL_HEXAGONAL_RING_ACT_MARIO_OFF_PLATFORM;
            break;
    }
    o->oAngleVelYaw   = -o->oAngleVelYaw;
    o->oMoveAngleYaw +=  o->oAngleVelYaw;
}
