// spindel.c.inc

void bhv_spindel_init(void) {
    o->oHomeY                = o->oPosY;
    o->oSpindelMoveTimer     = 0;
    o->oSpindelMoveDirection = FALSE;
}

void bhv_spindel_loop(void) {
    f32 homeYOffset;
    s32 shake;
    if (o->oSpindelMoveTimer == -1) {
        if (o->oTimer == 32) {
            o->oSpindelMoveTimer = 0;
            o->oTimer            = 0;
        } else {
            o->oVelZ          = 0.0f;
            o->oAngleVelPitch = 0x0;
            return;
        }
    }
    shake = (10 - o->oSpindelMoveTimer);
    if (shake < 0) shake *= -1;
    shake -= 6;
    if (shake < 0) shake = 0;
    if (o->oTimer == (shake + 8)) {
        o->oTimer = 0;
        o->oSpindelMoveTimer++;
        if (o->oSpindelMoveTimer == 20) {
            o->oSpindelMoveDirection ^= TRUE;
            o->oSpindelMoveTimer = -1;
        }
    }
    if ((shake == 4) || (shake == 3)) {
        shake = 4;
    } else if ((shake == 2) || (shake == 1)) {
        shake = 2;
    } else if (shake == 0) {
        shake = 1;
    }
    if (o->oTimer < (shake * 8)) {
        if (o->oSpindelMoveDirection == 0) {
            o->oVelZ          = (    20 / shake);
            o->oAngleVelPitch = ( 0x400 / shake);
        } else {
            o->oVelZ          = (   -20 / shake);
            o->oAngleVelPitch = (-0x400 / shake);
        }
        o->oPosZ += o->oVelZ;
        o->oMoveAnglePitch += o->oAngleVelPitch;
        if ((absf(o->oMoveAnglePitch & 0x1fff) < 800.0f) && (o->oAngleVelPitch != 0x0)) cur_obj_play_sound_2(SOUND_GENERAL2_SPINDEL_ROLL);
        homeYOffset = (sins(o->oMoveAnglePitch * 4) * 23.0f);
        if (homeYOffset < 0.0f) homeYOffset *= -1.0f;
        o->oPosY = (o->oHomeY + homeYOffset);
        if ((o->oTimer + 1) == (shake * 8)) set_camera_shake_from_point(SHAKE_POS_SMALL, &o->oPosVec);
    }
}
