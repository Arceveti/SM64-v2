
void bhv_swing_platform_init(void) {
    o->oSwingPlatformAngle = DEG(45);
}

void bhv_swing_platform_update(void) {
    s32 startRoll = o->oFaceAngleRoll;
    if (o->oFaceAngleRoll < 0x0) {
        o->oSwingPlatformSpeed += 4.0f;
    } else {
        o->oSwingPlatformSpeed -= 4.0f;
    }
    o->oSwingPlatformAngle += o->oSwingPlatformSpeed;
    o->oFaceAngleRoll       = o->oSwingPlatformAngle;
    o->oAngleVelRoll        = (o->oFaceAngleRoll - startRoll);
}
