// spindel.c.inc

void bhv_spindel_init(void) {
    o->oHomeY = o->oPosY;
    o->oSpindelMoveTimer = 0;
    o->oSpindelMoveDirection = FALSE;
}

// TODO: name sp18

void bhv_spindel_loop(void) {
    f32 homeYOffset;
    s32 sp18;

    if (o->oSpindelMoveTimer == -1) {
        if (o->oTimer == 32) {
            o->oSpindelMoveTimer = 0;
            o->oTimer = 0;
        } else {
            o->oVelZ = 0.0f;
            o->oAngleVelPitch = 0;
            return;
        }
    }

    sp18 = 10 - o->oSpindelMoveTimer;

    if (sp18 < 0) {
        sp18 *= -1;
    }
    sp18 -= 6;
    if (sp18 < 0) {
        sp18 = 0;
    }
    if (o->oTimer == sp18 + 8) {
        o->oTimer = 0;
        o->oSpindelMoveTimer++;
        if (o->oSpindelMoveTimer == 20) {
            o->oSpindelMoveDirection ^= TRUE;
            o->oSpindelMoveTimer = -1;
        }
    }

    if (sp18 == 4 || sp18 == 3) {
        sp18 = 4;
    } else if (sp18 == 2 || sp18 == 1) {
        sp18 = 2;
    } else if (sp18 == 0) {
        sp18 = 1;
    }
    if (o->oTimer < sp18 * 8) {
        if (o->oSpindelMoveDirection == 0) {
            o->oVelZ = 20 / sp18;
            o->oAngleVelPitch = 1024 / sp18;
        } else {
            o->oVelZ = -20 / sp18;
            o->oAngleVelPitch = -1024 / sp18;
        }

        o->oPosZ += o->oVelZ;
        o->oMoveAnglePitch += o->oAngleVelPitch;

        if (absf_2(o->oMoveAnglePitch & 0x1fff) < 800.0f && o->oAngleVelPitch != 0) {
            cur_obj_play_sound_2(SOUND_GENERAL2_SPINDEL_ROLL);
        }

        homeYOffset = sins(o->oMoveAnglePitch * 4) * 23.0f;
        if (homeYOffset < 0.0f) {
            homeYOffset *= -1.0f;
        }
        o->oPosY = o->oHomeY + homeYOffset;

        if (o->oTimer + 1 == sp18 * 8) {
            set_camera_shake_from_point(SHAKE_POS_SMALL, o->oPosX, o->oPosY, o->oPosZ);
        }
    }
}
