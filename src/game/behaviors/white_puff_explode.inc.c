// white_puff_explode.c.inc

void bhv_white_puff_exploding_loop(void) {
    f32 scale;
    if (o->oTimer == 0) {
        cur_obj_compute_vel_xz();
        o->oWhitePuffScaleX = o->header.gfx.scale[0];
        switch (o->oBehParams2ndByte) {
            case WHITE_PUFF_EXPLODE_BP_FAST_FADE:
                o->oOpacity              = 254;
                o->oWhitePuffOpacityDiff = -21;
                o->oWhitePuffSlowFade    = FALSE;
                break;
            case WHITE_PUFF_EXPLODE_BP_SLOW_FADE:
                o->oOpacity              = 254;
                o->oWhitePuffOpacityDiff = -13;
                o->oWhitePuffSlowFade    = TRUE;
                break;
        }
    }
    cur_obj_move_using_vel_and_gravity();
    cur_obj_apply_drag_xz(o->oDragStrength);
    if (o->oVelY > 100.0f) o->oVelY = 100.0f;
    if (o->oTimer > 20) obj_mark_for_deletion(o);
    if (o->oOpacity) {
        o->oOpacity += o->oWhitePuffOpacityDiff;
        if (o->oOpacity < 2) obj_mark_for_deletion(o);
        scale = o->oWhitePuffScaleX * (o->oWhitePuffSlowFade ? ((254 - o->oOpacity) / 254.0f) : (o->oOpacity / 254.0f));
        cur_obj_scale(scale);
    }
}
