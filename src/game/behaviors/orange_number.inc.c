// orange_number.c.inc

void bhv_orange_number_init(void) {
    o->oAnimState = o->oBehParams2ndByte;
    o->oVelY = 26.0f;
}

void bhv_orange_number_loop(void) {
    struct Object *sparkleObj;
#ifdef ORANGE_LETTERS
    if (o->oAnimState <= 0x09) {
#endif
        o->oPosY += o->oVelY;
        o->oVelY -= 2.0f;
        if (o->oVelY < -21.0f)
            o->oVelY = 14.0f;

        if (o->oTimer == 35) {
            sparkleObj = spawn_object(o, MODEL_SPARKLES, bhvGoldenCoinSparkles);
            sparkleObj->oPosY -= 30.0f;
            o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
        }
#ifdef ORANGE_LETTERS
    } else {
        if (o->oTimer >= 1 || gMarioState->action == ACT_READING_SIGN) {
            o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
        }
    }
#endif
}
