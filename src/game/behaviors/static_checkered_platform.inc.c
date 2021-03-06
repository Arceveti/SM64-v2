// static_checkered_platform.c.inc

void bhv_unused_static_checkered_platform_loop(void) {
    if (gDebugInfo[5][0] == 1) {
        obj_set_angle(o, 0x0, 0x0, 0x0);
        vec3_zero(&o->oAngleVelVec);
    }
    if (gDebugInfo[5][0] == 2) {
        o->oFaceAnglePitch = (gDebugInfo[5][1] << 12);
        o->oFaceAngleYaw   = (gDebugInfo[5][2] << 12);
        o->oFaceAngleRoll  = (gDebugInfo[5][3] << 12);
    }
    vec3_copy(&o->oAngleVelVec, &gDebugInfo[5][4]);
    if (gDebugInfo[5][0] == 3) cur_obj_rotate_face_angle_using_vel();
}
