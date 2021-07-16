// floating_platform.c.inc

f32 floating_platform_find_home_y(void) {
    struct Surface *sp24;
    f32 sp20;
    f32 sp1C;

    sp20 = find_water_level(o->oPosX, o->oPosZ);
    sp1C = find_floor(o->oPosX, o->oPosY, o->oPosZ, &sp24);
    if (sp20 > sp1C + o->oFloatingPlatformHeightOffset) {
        o->oFloatingPlatformIsOnFloor = 0;
        return sp20 + o->oFloatingPlatformHeightOffset;
    } else {
        o->oFloatingPlatformIsOnFloor = 1;
        return sp1C + o->oFloatingPlatformHeightOffset;
    }
}

void floating_platform_act_0(void) {
    s16 sp6 = (gMarioObject->header.gfx.pos[0] - o->oPosX) * coss(-1*o->oMoveAngleYaw)
              + (gMarioObject->header.gfx.pos[2] - o->oPosZ) * sins(-1*o->oMoveAngleYaw);
    s16 sp4 = (gMarioObject->header.gfx.pos[2] - o->oPosZ) * coss(-1*o->oMoveAngleYaw)
              - (gMarioObject->header.gfx.pos[0] - o->oPosX) * sins(-1*o->oMoveAngleYaw);

    if (gMarioObject->platform == o) {
        o->oFaceAnglePitch = sp4 * 2;
        o->oFaceAngleRoll = -sp6 * 2;
        o->oVelY -= 1.0f;
        if (o->oVelY < 0.0f)
            o->oVelY = 0.0f;

        o->oFloatingPlatformMarioWeightWobbleOffset += o->oVelY;
        if (o->oFloatingPlatformMarioWeightWobbleOffset > 90.0f)
            o->oFloatingPlatformMarioWeightWobbleOffset = 90.0f;
    } else {
        o->oFaceAnglePitch /= 2;
        o->oFaceAngleRoll /= 2;
        o->oFloatingPlatformMarioWeightWobbleOffset -= 5.0;
        o->oVelY = 10.0f;
        if (o->oFloatingPlatformMarioWeightWobbleOffset < 0.0f)
            o->oFloatingPlatformMarioWeightWobbleOffset = 0.0f;
    }

    o->oPosY = o->oHomeY - 64.0f - o->oFloatingPlatformMarioWeightWobbleOffset + sins(o->oFloatingPlatformWaterSurfaceWobbleOffset * 0x800) * 10.0f;
    o->oFloatingPlatformWaterSurfaceWobbleOffset++;
    if (o->oFloatingPlatformWaterSurfaceWobbleOffset == 32)
        o->oFloatingPlatformWaterSurfaceWobbleOffset = 0;
}

void bhv_floating_platform_loop(void) {
    o->oHomeY = floating_platform_find_home_y();
    if (o->oFloatingPlatformIsOnFloor == 0)
        o->oAction = 0;
    else
        o->oAction = 1;

    switch (o->oAction) {
        case 0:
            floating_platform_act_0();
            break;

        case 1:
            o->oPosY = o->oHomeY;
            break;
    }
}
