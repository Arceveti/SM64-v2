// checkerboard_platform.c.inc

struct CheckerBoardPlatformInitPosition sCheckerBoardPlatformInitPositions[] = { { 145, { 0.7f, 1.5f, 0.7f }, 7.0f },
                                       { 235, { 1.2f, 2.0f, 1.2f }, 11.6f } };

void bhv_checkerboard_elevator_group_init(void) {
    s32 relativePosY;
    s32 relativePosZ;
    s32 type;
    s32 i;
    struct Object *sp2C;
    if (o->oBehParams2ndByte == 0) {
        o->oBehParams2ndByte = 65;
    }
    relativePosY = o->oBehParams2ndByte * 10;
    type = (o->oBehParams >> 24) & 0XFF;
    for (i = 0; i < 2; i++) {
        if (i == 0) {
            relativePosZ = -sCheckerBoardPlatformInitPositions[type].relPosZ;
        } else {
            relativePosZ = sCheckerBoardPlatformInitPositions[type].relPosZ;
        }
        sp2C = spawn_object_relative(i, 0, i * relativePosY, relativePosZ, o, MODEL_CHECKERBOARD_PLATFORM,
                                     bhvCheckerboardPlatformSub);
        sp2C->oCheckerBoardPlatformRadius = sCheckerBoardPlatformInitPositions[type].radius;
        vec3f_copy_2(sp2C->header.gfx.scale, sCheckerBoardPlatformInitPositions[type].scaleVec);
    }
}

void checkerboard_plat_act_move_y(UNUSED s32 unused, f32 vel, s32 time) {
    o->oMoveAnglePitch = 0;
    o->oAngleVelPitch = 0;
    o->oForwardVel = 0.0f;
    o->oVelY = vel;
    if (o->oTimer > time)
        o->oAction++;
}

void checkerboard_plat_act_rotate(s32 nextAction, s16 pitchAmt) {
    o->oVelY = 0.0f;
    o->oAngleVelPitch = pitchAmt;
    if (o->oTimer + 1 == 0x8000 / absi(pitchAmt)) {
        o->oAction = nextAction;
    }
    o->oCheckerBoardPlatformRotateAction = nextAction;
}

void bhv_checkerboard_platform_init(void) {
    o->oCheckerBoardPlatformHeight = o->parentObj->oBehParams2ndByte;
}

void bhv_checkerboard_platform_loop(void) {
    f32 radius = o->oCheckerBoardPlatformRadius;
    o->oCheckerBoardPlatformRotateAction = 0;
    if (o->oDistanceToMario < 1000.0f)
        cur_obj_play_sound_1(SOUND_ENV_ELEVATOR4);
    switch (o->oAction) {
        case 0:
            if (o->oBehParams2ndByte == 0) {
                o->oAction = 1;
            } else {
                o->oAction = 3;
            }
            break;
        case 1:
            checkerboard_plat_act_move_y(2, 10.0f, o->oCheckerBoardPlatformHeight);
            break;
        case 2:
            checkerboard_plat_act_rotate(3, 512);
            break;
        case 3:
            checkerboard_plat_act_move_y(4, -10.0f, o->oCheckerBoardPlatformHeight);
            break;
        case 4:
            checkerboard_plat_act_rotate(1, -512);
            break;
    }
    o->oMoveAnglePitch += absi(o->oAngleVelPitch);
    o->oFaceAnglePitch += absi(o->oAngleVelPitch);
    o->oFaceAngleYaw = o->oMoveAngleYaw;
    if (o->oMoveAnglePitch != 0) {
        o->oForwardVel = signum_positive(o->oAngleVelPitch) * sins(o->oMoveAnglePitch) * radius;
        o->oVelY = signum_positive(o->oAngleVelPitch) * coss(o->oMoveAnglePitch) * radius;
    }
    if (o->oCheckerBoardPlatformRotateAction == 1) {
        o->oAngleVelPitch = 0;
        o->oFaceAnglePitch &= ~0x7FFF;
        cur_obj_move_using_fvel_and_gravity();
    } else
        cur_obj_move_using_fvel_and_gravity();
    load_object_collision_model();
}
