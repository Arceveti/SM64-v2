// fishing_boo.c.inc

// Unused behavior file for the Fishing Boo enemy.
// The fire circles around mario and would make it
// hard for him to jump or platform.
// There is also a stubbed behavior script next to
// the scripts associated with this, indicating
// a removed object associated with this flame.

void bhv_beta_moving_flames_spawn_loop(void) {
    o->oDistanceToMario = lateral_dist_between_objects(o, gMarioObject);
    o->oPosY -= 100.0f;
    switch (o->oAction) {
        case FISHING_BOO_ACT_0:
        case FISHING_BOO_ACT_1:
        case FISHING_BOO_ACT_2:
        case FISHING_BOO_ACT_3:
        case FISHING_BOO_ACT_4:
        case FISHING_BOO_ACT_5:
        case FISHING_BOO_ACT_6:
        case FISHING_BOO_ACT_SPAWN_FLAMES:
            spawn_object(o, MODEL_RED_FLAME, bhvBetaMovingFlames);
            o->oAction = FISHING_BOO_ACT_8;
            break;
        case FISHING_BOO_ACT_8:
            break;
        case FISHING_BOO_ACT_9:
            o->oAction = FISHING_BOO_ACT_10;
            break;
    }
}

void bhv_beta_moving_flames_loop(void) {
    cur_obj_scale(5.0f);
    o->oForwardVel = sins(o->oMovingFlameTimer) * 70.0f;
    o->oMovingFlameTimer += 0x800;
}
