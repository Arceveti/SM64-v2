// lll_sinking_rectangle.c.inc

void sinking_rectangular_plat_actions(f32 dist, s32 speed) {
    o->oPosY -= (sins(o->oLllWoodPieceOscillationTimer) * dist);
    o->oLllWoodPieceOscillationTimer += speed;
}

void bhv_lll_sinking_rectangular_platform_loop(void) {
    if (o->oMoveAngleYaw != 0x0) {
        sinking_rectangular_plat_actions(0.4f, 0x100);
    } else {
        o->oFaceAnglePitch = (sins(o->oLllWoodPieceOscillationTimer) * 512.0f);
        o->oLllWoodPieceOscillationTimer += 0x100;
    }
}

void bhv_lll_sinking_square_platforms_loop(void) {
    sinking_rectangular_plat_actions(0.5f, 0x100);
}
