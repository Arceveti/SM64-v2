// rolling_log.c.inc

// why are the falling platforms and rolling logs grouped
// together? seems strange, but it also cooresponds to the
// behavior script grouping if the same file is assumed.
// hypothesis is that the object in the middle here used to be
// a rolling log of another variation.

void bhv_ttm_rolling_log_init(void) {
    o->oRollingLogX       =   3970.0f;
    o->oRollingLogZ       =   3654.0f;
    o->oRollingLogMaxDist = 271037.0f;
    o->oMoveAngleYaw      =      8810;
    o->oForwardVel        =         0;
    o->oVelX              =         0;
    o->oVelZ              =         0;
    o->oFaceAnglePitch    =         0;
    o->oAngleVelPitch     =         0;
}

void rolling_log_roll_log(void) {
    f32 rollAmount;

    if (gMarioObject->platform == o) {
        rollAmount = (gMarioObject->header.gfx.pos[2] - o->oPosZ) * coss(-o->oMoveAngleYaw)
                   - (gMarioObject->header.gfx.pos[0] - o->oPosX) * sins(-o->oMoveAngleYaw);
        if (rollAmount > 0) {
            o->oAngleVelPitch += 0x10;
        } else {
            o->oAngleVelPitch -= 0x10;
        }
        if (o->oAngleVelPitch >  0x200) o->oAngleVelPitch =  0x200;
        if (o->oAngleVelPitch < -0x200) o->oAngleVelPitch = -0x200;
    } else {
        if (is_point_close_to_object(o, o->oHomeX, o->oHomeY, o->oHomeZ, 100)) {
            if (o->oAngleVelPitch != 0) {
                if (o->oAngleVelPitch > 0) {
                    o->oAngleVelPitch -= 0x10;
                } else {
                    o->oAngleVelPitch += 0x10;
                }
                if (o->oAngleVelPitch < 0x10 && o->oAngleVelPitch > -0x10) o->oAngleVelPitch = 0;
            }
        } else {
            if (o->oAngleVelPitch != 0x100) {
                if (o->oAngleVelPitch > 0x100) {
                    o->oAngleVelPitch -= 0x10;
                } else {
                    o->oAngleVelPitch += 0x10;
                }
                if (o->oAngleVelPitch < 0x110 && o->oAngleVelPitch > 0xF0) o->oAngleVelPitch = 0x100;
            }
        }
    }
}

void bhv_rolling_log_loop(void) {
    f32 prevX = o->oPosX;
    f32 prevZ = o->oPosZ;

    rolling_log_roll_log();

    o->oForwardVel = o->oAngleVelPitch / 0x40;
    o->oVelX       = o->oForwardVel * sins(o->oMoveAngleYaw);
    o->oVelZ       = o->oForwardVel * coss(o->oMoveAngleYaw);

    o->oPosX += o->oVelX;
    o->oPosZ += o->oVelZ;

    if (o->oRollingLogMaxDist < sqr(o->oPosX - o->oRollingLogX) + sqr(o->oPosZ - o->oRollingLogZ)) {
        o->oForwardVel = 0;
        o->oPosX       = prevX;
        o->oPosZ       = prevZ;
        o->oVelX       = 0;
        o->oVelZ       = 0;
    }

    o->oFaceAnglePitch += o->oAngleVelPitch;
    if (absf_2(o->oFaceAnglePitch & 0x1FFF) < 528.0f && o->oAngleVelPitch != 0) cur_obj_play_sound_2(SOUND_GENERAL_ROLLING_LOG);
}

void volcano_trap_act_fall(void) {
    o->oVolcanoTrapPitchVel += 4.0f;
    o->oAngleVelPitch += o->oVolcanoTrapPitchVel;
    o->oFaceAnglePitch -= o->oAngleVelPitch;

    if (o->oFaceAnglePitch      < -0x4000) {
        o->oFaceAnglePitch      = -0x4000;
        o->oAngleVelPitch       = 0;
        o->oVolcanoTrapPitchVel = 0;
        o->oAction = LLL_VOLCANO_TRAP_ACT_LAND;
        cur_obj_play_sound_2(SOUND_GENERAL_BIG_POUND);
        set_camera_shake_from_point(SHAKE_POS_LARGE, o->oPosX, o->oPosY, o->oPosZ);
    }
}

void volcano_trap_act_rise(void) {
    o->oAngleVelPitch = 0x90;
    o->oFaceAnglePitch += o->oAngleVelPitch;
    if (o->oFaceAnglePitch > 0) o->oFaceAnglePitch = 0;
    if (o->oTimer == 200) o->oAction = LLL_VOLCANO_TRAP_ACT_WAIT;
}

void bhv_volcano_trap_loop(void) {
    switch (o->oAction) {
        case LLL_VOLCANO_TRAP_ACT_WAIT:
            if (is_point_within_radius_of_mario(o->oPosX, o->oPosY, o->oPosZ, 1000)) {
                o->oAction = LLL_VOLCANO_TRAP_ACT_FALL;
                cur_obj_play_sound_2(SOUND_GENERAL_VOLCANO_TRAP_FALL);
            }
            break;

        case LLL_VOLCANO_TRAP_ACT_FALL:
            volcano_trap_act_fall();
            break;

        case LLL_VOLCANO_TRAP_ACT_LAND:
            if (o->oTimer <   8) o->oPosY = o->oHomeY + sins(o->oTimer * 0x1000) * 10.0f;
            if (o->oTimer == 50) {
                cur_obj_play_sound_2(SOUND_GENERAL_VOLCANO_TRAP_RISE);
                o->oAction = LLL_VOLCANO_TRAP_ACT_RISE;
            }
            break;

        case LLL_VOLCANO_TRAP_ACT_RISE:
            volcano_trap_act_rise();
            break;
    }
}

void bhv_lll_rolling_log_init(void) {
    o->oRollingLogX       = 5120.0f;
    o->oRollingLogZ       = 6016.0f;
    o->oRollingLogMaxDist = 1048576.0f;

    o->oMoveAngleYaw   = 0x3FFF;
    o->oForwardVel     = 0;
    o->oVelX           = 0;
    o->oVelZ           = 0;
    o->oFaceAnglePitch = 0;
    o->oAngleVelPitch  = 0;
}
