// lll_floating_wood_piece.c.inc

void bhv_lll_wood_piece_loop(void) {
    if (o->oTimer == 0) o->oPosY -= 100.0f;
    o->oPosY += sins(o->oLllWoodPieceOscillationTimer) * 3.0f;
    o->oLllWoodPieceOscillationTimer += 0x400;
    if (o->parentObj->oAction == LLL_FLOATING_WOOD_ACT_REMOVE_PIECES) obj_mark_for_deletion(o);
}

void bhv_lll_floating_wood_bridge_loop(void) {
    struct Object *woodPieceObj;
    s32 i;
    switch (o->oAction) {
        case LLL_FLOATING_WOOD_ACT_INACTIVE:
            if (o->oDistanceToMario < 2500.0f) {
                for (i = 1; i < 4; i++) {
                    woodPieceObj = spawn_object_relative(OBJ_BP_NONE, (i - 2) * 300, 0, 0, o, MODEL_LLL_WOOD_BRIDGE, bhvLllWoodPiece);
                    woodPieceObj->oLllWoodPieceOscillationTimer = i * 4096;
                }
                o->oAction = LLL_FLOATING_WOOD_ACT_ACTIVE;
            }
            break;
        case LLL_FLOATING_WOOD_ACT_ACTIVE:
            if (o->oDistanceToMario > 2600.0f) o->oAction = LLL_FLOATING_WOOD_ACT_REMOVE_PIECES;
            break;
        case LLL_FLOATING_WOOD_ACT_REMOVE_PIECES:
            o->oAction = LLL_FLOATING_WOOD_ACT_INACTIVE;
            break;
    }
}
