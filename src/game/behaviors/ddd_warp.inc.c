// ddd_warp.c.inc

void bhv_ddd_warp_loop(void) {
#ifdef UNLOCK_ALL
    o->collisionData = segmented_to_virtual(inside_castle_seg7_collision_ddd_warp_2);
#else
    o->collisionData = segmented_to_virtual((gDddPaintingStatus & BOWSERS_SUB_BEATEN) ? inside_castle_seg7_collision_ddd_warp_2 : inside_castle_seg7_collision_ddd_warp);
#endif
}
