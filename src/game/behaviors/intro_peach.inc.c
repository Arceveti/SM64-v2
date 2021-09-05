// intro_peach.inc.c

/**
 * Set peach's location relative to the camera focus.
 * If nonzero, make peach's opacity approach targetOpacity by increment
 */
void intro_peach_set_pos_and_opacity(struct Object *o, f32 targetOpacity, f32 increment) {
    Vec3f newPos;
    Angle focusPitch, focusYaw;
    AlphaF newOpacity;
    vec3f_get_angle(gLakituState.pos, gLakituState.focus, &focusPitch, &focusYaw);
    vec3f_set_dist_and_angle(gLakituState.pos, newPos, o->oIntroPeachDistToCamera, (o->oIntroPeachPitchFromFocus + focusPitch), (o->oIntroPeachYawFromFocus + focusYaw));
    vec3f_copy(&o->oPosVec, newPos);
    newOpacity  = o->oOpacity;
    approach_f32_symmetric_bool(&newOpacity, targetOpacity, increment);
    o->oOpacity = newOpacity;
}

void bhv_intro_peach_loop(void) {
    switch (o->oAction) {
        case PEACH_ACT_INIT:
            o->oAction                       = PEACH_ACT_FADE_1;
            vec3i_set(&o->oFaceAngleVec, 0x400, 0x7500, -0x3700);
            o->oIntroPeachDistToCamera       =   186.0f;
            o->oIntroPeachPitchFromFocus     = -9984.0f;
            o->oIntroPeachYawFromFocus       =  -768.0f;
            o->oOpacity                      =      255;
            o->header.gfx.animInfo.animFrame =      100;
            break;
        case PEACH_ACT_FADE_1:
            intro_peach_set_pos_and_opacity(o,   0.0f, 0.0f);
            if (o->oTimer > 20) o->oAction = PEACH_ACT_UNFADE;
            break;
        case PEACH_ACT_UNFADE:
            intro_peach_set_pos_and_opacity(o, 255.0f, 3.0f);
            if ((o->oTimer > 100) && (get_dialog_id() == DIALOG_NONE)) o->oAction = PEACH_ACT_FADE_2;
            break;
        case PEACH_ACT_FADE_2:
            intro_peach_set_pos_and_opacity(o,   0.0f, 8.0f);
            if (o->oTimer > 60) obj_mark_for_deletion(o);
            break;
    }
}
