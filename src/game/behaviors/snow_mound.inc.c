// snow_mound.c.inc

void bhv_sliding_snow_mound_loop(void) {
    switch (o->oAction) {
        case SNOW_MOUND_ACT_MOVE:
            o->oVelX = -40.0f;
            o->oPosX += o->oVelX;
            if (o->oTimer >= 118) o->oAction = SNOW_MOUND_ACT_SINK;
            cur_obj_play_sound_1(SOUND_ENV_SINK_QUICKSAND);
            break;

        case SNOW_MOUND_ACT_SINK:
            o->oVelX =  -5.0f;
            o->oPosX += o->oVelX;
            o->oVelY = -10.0f;
            o->oPosY += o->oVelY;
            o->oPosZ = o->oHomeZ - 2.0f;
            if (o->oTimer > 50) o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            break;
    }
}

void bhv_snow_mound_spawn_loop(void) {
    struct Object *moundObj;

    if (!is_point_within_radius_of_mario(o->oPosX, o->oPosY, o->oPosZ, 6000)
        || o->oPosY + 1000.0f < gMarioObject->header.gfx.pos[1]) return;

    if (o->oTimer ==  64
     || o->oTimer == 128
     || o->oTimer == 192
     || o->oTimer == 224
     || o->oTimer == 256) moundObj = spawn_object(o, MODEL_SL_SNOW_TRIANGLE, bhvSlidingSnowMound);
    // if (o->oTimer % 64 == 0) moundObj = spawn_object(o, MODEL_SL_SNOW_TRIANGLE, bhvSlidingSnowMound);
    if (o->oTimer == 256) {
        moundObj->header.gfx.scale[0] = 2.0f;
        moundObj->header.gfx.scale[1] = 2.0f;
    }

    if (o->oTimer >= 256) o->oTimer = 0;
}
