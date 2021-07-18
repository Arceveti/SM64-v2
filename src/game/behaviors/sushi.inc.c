// sushi.c.inc

void bhv_sushi_shark_collision_loop(void) {
}

void bhv_sushi_shark_loop(void) {
    f32 sp1C = find_water_level(o->oPosX, o->oPosZ);
    o->oPosX = o->oHomeX + sins(o->oSushiSharkAngleFromHome) * 1700.0f;
    o->oPosZ = o->oHomeZ + coss(o->oSushiSharkAngleFromHome) * 1700.0f;
    o->oPosY = sp1C + o->oHomeY + sins(o->oSushiSharkAngleFromHome) * 200.0f;
    o->oMoveAngleYaw = o->oSushiSharkAngleFromHome + 0x4000;
    o->oSushiSharkAngleFromHome += 0x80;
    if (gMarioObject->oPosY - sp1C > -500.0f) {
        if (o->oPosY - sp1C > -200.0f) {
            spawn_object_with_scale(o, MODEL_WAVE_TRAIL, bhvObjectWaveTrail, 4.0f);
        }
    }
    if ((o->oTimer & 0xF) == 0) {
        cur_obj_play_sound_2(SOUND_OBJ_SUSHI_SHARK_WATER_SOUND);
    }
    o->oInteractStatus = INT_STATUS_NONE;
}
