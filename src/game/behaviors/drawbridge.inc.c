// drawbridge.c.inc

void bhv_lll_drawbridge_spawner_loop(void) {
    struct Object *drawbridge1, *drawbridge2;
    drawbridge1 = spawn_object(o, MODEL_LLL_DRAWBRIDGE_PART, bhvLllDrawbridge);
    drawbridge1->oMoveAngleYaw = o->oMoveAngleYaw;
    drawbridge1->oPosX += (coss(o->oMoveAngleYaw) *  640.0f);
    drawbridge1->oPosZ += (sins(o->oMoveAngleYaw) *  640.0f);
    drawbridge2 = spawn_object(o, MODEL_LLL_DRAWBRIDGE_PART, bhvLllDrawbridge);
    drawbridge2->oMoveAngleYaw = o->oMoveAngleYaw + DEG(180);
    drawbridge2->oPosX += (coss(o->oMoveAngleYaw) * -640.0f);
    drawbridge2->oPosZ += (sins(o->oMoveAngleYaw) * -640.0f);
    o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
}

void bhv_lll_drawbridge_loop(void) {
    switch (o->oAction) {
        case LLL_DRAWBRIDGE_ACT_LOWER: o->oFaceAngleRoll += 0x100; break;
        case LLL_DRAWBRIDGE_ACT_RAISE: o->oFaceAngleRoll -= 0x100; break;
    }
    if ((Angle) o->oFaceAngleRoll < -0x1FFD) { // ~50 degrees
        o->oFaceAngleRoll = 0xDFFF; // ~315 degrees
        if ((o->oTimer >= 51) && !(o->oTimer & 0x7)) {
            o->oAction = LLL_DRAWBRIDGE_ACT_LOWER;
            cur_obj_play_sound_2(SOUND_GENERAL_DRAWBRIDGE_LOWER);
        }
    }
    if ((Angle) o->oFaceAngleRoll >= 0x0) {
        o->oFaceAngleRoll = 0x0;
        if ((o->oTimer >= 51) && !(o->oTimer & 0x7)) {
            o->oAction = LLL_DRAWBRIDGE_ACT_RAISE;
            cur_obj_play_sound_2(SOUND_GENERAL_DRAWBRIDGE_RAISE);
        }
    }
}
