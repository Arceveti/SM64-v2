// seaweed.c.inc

void bhv_seaweed_init(void) {
    o->header.gfx.animInfo.animFrame = (random_float() * 80.0f);
}

void bhv_seaweed_bundle_init(void) {
    struct Object *seaweed;
    //! vec3i_set for &seaweed->oFaceAngleVec
    seaweed                                = spawn_object(o, MODEL_SEAWEED, bhvSeaweed);
    seaweed->oFaceAngleYaw                 = 0x38BB;
    seaweed->oFaceAnglePitch               = 0x157C;
    seaweed->oFaceAngleRoll                = 0x2580;
    vec3f_set(seaweed->header.gfx.scale, 1.0f, 1.0f, 1.0f);
    seaweed->header.gfx.animInfo.animFrame = 0;

    seaweed                                = spawn_object(o, MODEL_SEAWEED, bhvSeaweed);
    seaweed->oFaceAngleYaw                 = 0xA348;
    seaweed->oFaceAnglePitch               = 0x17D6;
    seaweed->oFaceAngleRoll                = 0x0000;
    vec3f_set(seaweed->header.gfx.scale, 0.8f, 0.9f, 0.8f);
    seaweed->header.gfx.animInfo.animFrame = (random_float() * 80.0f);

    seaweed                                = spawn_object(o, MODEL_SEAWEED, bhvSeaweed);
    seaweed->oFaceAngleYaw                 = 0x9E34;
    seaweed->oFaceAnglePitch               = 0x21FC;
    seaweed->oFaceAngleRoll                = 0x1004;
    vec3f_set(seaweed->header.gfx.scale, 0.8f, 0.8f, 0.8f);
    seaweed->header.gfx.animInfo.animFrame = (random_float() * 80.0f);

    seaweed                                = spawn_object(o, MODEL_SEAWEED, bhvSeaweed);
    seaweed->oFaceAngleYaw                 = 0xDF94;
    seaweed->oFaceAnglePitch               = 0x251C;
    seaweed->oFaceAngleRoll                = 0x0000;
    vec3f_set(seaweed->header.gfx.scale, 1.2f, 1.2f, 1.2f);
    seaweed->header.gfx.animInfo.animFrame = (random_float() * 80.0f);
}
