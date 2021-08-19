// intro_peach.inc.c

/**
 * Set peach's location relative to the camera focus.
 * If nonzero, make peach's opacity approach targetOpacity by increment
 */
void intro_peach_set_pos_and_opacity(struct Object *o, f32 targetOpacity, f32 increment) {
    Vec3f newPos;
    Angle focusPitch, focusYaw;
    f32 UNUSED dist, newOpacity;

    vec3f_get_dist_and_angle(gLakituState.pos, gLakituState.focus, &dist, &focusPitch, &focusYaw);
    vec3f_set_dist_and_angle(gLakituState.pos, newPos, o->oIntroPeachDistToCamera, o->oIntroPeachPitchFromFocus + focusPitch,
                             o->oIntroPeachYawFromFocus + focusYaw);
    vec3f_to_object_pos(o, newPos);
    newOpacity  = o->oOpacity;
    camera_approach_f32_symmetric_bool(&newOpacity, targetOpacity, increment);
    o->oOpacity = newOpacity;
}

void bhv_intro_peach_loop(void) {
    switch (gCurrentObject->oAction) {
        case PEACH_ACT_INIT:
            gCurrentObject->oAction                       = PEACH_ACT_FADE_1;
            gCurrentObject->oFaceAnglePitch               =    0x400;
            gCurrentObject->oFaceAngleYaw                 =   0x7500;
            gCurrentObject->oFaceAngleRoll                =  -0x3700;
            gCurrentObject->oIntroPeachDistToCamera       =   186.0f;
            gCurrentObject->oIntroPeachPitchFromFocus     = -9984.0f;
            gCurrentObject->oIntroPeachYawFromFocus       =  -768.0f;
            gCurrentObject->oOpacity                      =      255;
            gCurrentObject->header.gfx.animInfo.animFrame =      100;
            break;
        case PEACH_ACT_FADE_1:
            intro_peach_set_pos_and_opacity(gCurrentObject,   0.0f, 0.0f);
            if (gCurrentObject->oTimer > 20) gCurrentObject->oAction = PEACH_ACT_UNFADE;
            break;
        case PEACH_ACT_UNFADE:
            intro_peach_set_pos_and_opacity(gCurrentObject, 255.0f, 3.0f);
            if ((gCurrentObject->oTimer > 100) && (get_dialog_id() == DIALOG_NONE)) gCurrentObject->oAction = PEACH_ACT_FADE_2;
            break;
        case PEACH_ACT_FADE_2:
            intro_peach_set_pos_and_opacity(gCurrentObject,   0.0f, 8.0f);
            if (gCurrentObject->oTimer > 60) obj_mark_for_deletion(gCurrentObject);
            break;
    }
}
