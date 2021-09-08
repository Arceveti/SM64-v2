// checkerboard_platform.c.inc

struct CheckerBoardPlatformInitPosition {
    s32   relPosZ;
    Vec3f scaleVec;
    f32   radius;
};

struct CheckerBoardPlatformInitPosition sCheckerBoardPlatformInitPositions[] = { { 145, { 0.7f, 1.5f, 0.7f },  7.0f },
                                                                                 { 235, { 1.2f, 2.0f, 1.2f }, 11.6f } };

void bhv_checkerboard_elevator_group_init(void) {
    s32 relativePosY, relativePosZ;
    s32 type;
    s32 i;
    struct Object *platformObj;
    // oBehParams2ndByte determines the relative height of the platforms
    if (o->oBehParams2ndByte == CHECKERBOARD_PLATFORM_GROUP_BP_SET_DEFAULT) o->oBehParams2ndByte = CHECKERBOARD_PLATFORM_GROUP_BP_DEFAULT_MAX;
    relativePosY = (o->oBehParams2ndByte * 10);
    type = ((o->oBehParams >> 24) & 0xFF);
    for ((i = 0); (i < 2); (i++)) {
        relativePosZ = ((i == 0) ? -sCheckerBoardPlatformInitPositions[type].relPosZ : sCheckerBoardPlatformInitPositions[type].relPosZ);
        platformObj = spawn_object_relative(i, 0, (i * relativePosY), relativePosZ, o, MODEL_CHECKERBOARD_PLATFORM, bhvCheckerboardPlatformSub);
        platformObj->oCheckerBoardPlatformRadius  = sCheckerBoardPlatformInitPositions[type].radius;
        vec3_copy(platformObj->header.gfx.scale,   sCheckerBoardPlatformInitPositions[type].scaleVec);
    }
}

void checkerboard_plat_act_move_y(f32 vel, s32 time) {
    o->oMoveAnglePitch = 0x0;
    o->oAngleVelPitch  = 0x0;
    o->oForwardVel     = 0.0f;
    o->oVelY           = vel;
    if (o->oTimer > time) o->oAction++;
}

void checkerboard_plat_act_rotate(s32 nextAction, Angle pitchAmt) {
    o->oVelY          = 0.0f;
    o->oAngleVelPitch = pitchAmt;
    if ((o->oTimer + 1) == (0x8000 / ABSI(pitchAmt))) o->oAction = nextAction;
    o->oCheckerBoardPlatformRotateAction = nextAction;
}

void bhv_checkerboard_platform_init(void) {
    o->oCheckerBoardPlatformHeight = o->parentObj->oBehParams2ndByte;
}

void bhv_checkerboard_platform_loop(void) {
    f32 radius = o->oCheckerBoardPlatformRadius;
    o->oCheckerBoardPlatformRotateAction = CHECKERBOARD_PLATFORM_ACT_MOVE_VERTICALLY;
    if (o->oDistanceToMario < 1000.0f) cur_obj_play_sound_1(SOUND_ENV_ELEVATOR4);
    switch (o->oAction) {
        case CHECKERBOARD_PLATFORM_ACT_MOVE_VERTICALLY: o->oAction = (o->oBehParams2ndByte == CHECKERBOARD_PLATFORM_BP_MOVE_UP) ? CHECKERBOARD_PLATFORM_ACT_MOVE_UP : CHECKERBOARD_PLATFORM_ACT_MOVE_DOWN; break;
        case CHECKERBOARD_PLATFORM_ACT_MOVE_UP:         checkerboard_plat_act_move_y( 10.0f, o->oCheckerBoardPlatformHeight);   break;
        case CHECKERBOARD_PLATFORM_ACT_ROTATE_UP:       checkerboard_plat_act_rotate(CHECKERBOARD_PLATFORM_ACT_MOVE_DOWN, 512); break;
        case CHECKERBOARD_PLATFORM_ACT_MOVE_DOWN:       checkerboard_plat_act_move_y(-10.0f, o->oCheckerBoardPlatformHeight);   break;
        case CHECKERBOARD_PLATFORM_ACT_ROTATE_DOWN:     checkerboard_plat_act_rotate(CHECKERBOARD_PLATFORM_ACT_MOVE_UP,  -512); break;
    }
    o->oMoveAnglePitch += ABSI(o->oAngleVelPitch);
    o->oFaceAnglePitch += ABSI(o->oAngleVelPitch);
    o->oFaceAngleYaw = o->oMoveAngleYaw;
    if (o->oMoveAnglePitch != 0x0) {
        o->oForwardVel = (SIGNUM(o->oAngleVelPitch) * sins(o->oMoveAnglePitch) * radius);
        o->oVelY       = (SIGNUM(o->oAngleVelPitch) * coss(o->oMoveAnglePitch) * radius);
    }
    // Prevent the lower platform from flipping
    if (o->oCheckerBoardPlatformRotateAction == CHECKERBOARD_PLATFORM_ACT_MOVE_UP) {
        o->oAngleVelPitch   = 0x0;
        o->oFaceAnglePitch &= ~0x7FFF;
    }
    cur_obj_move_using_fvel_and_gravity();
    load_object_collision_model();
}
