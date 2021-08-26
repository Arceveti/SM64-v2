// square_platform_cycle.c.inc

//! s16/Angle for yaw param?
Bool32 square_plat_set_yaw_until_timer(u16 yaw, s32 time) {
    o->oMoveAngleYaw = yaw;
    return (time < o->oTimer);
}

void bhv_squarish_path_moving_loop(void) {
    o->oForwardVel = 10.0f;
    switch (o->oAction) {
        case BITDW_PYRAMID_PLATFORM_ACT_INIT_DIRECTION: o->oAction = ((o->oBehParams2ndByte & 0x3) + 1);                                                   break;
        case BITDW_PYRAMID_PLATFORM_ACT_MOVE_0:   if (square_plat_set_yaw_until_timer(         0x0, 60)) o->oAction = BITDW_PYRAMID_PLATFORM_ACT_MOVE_90;  break;
        case BITDW_PYRAMID_PLATFORM_ACT_MOVE_90:  if (square_plat_set_yaw_until_timer(DEGREES( 90), 60)) o->oAction = BITDW_PYRAMID_PLATFORM_ACT_MOVE_180; break;
        case BITDW_PYRAMID_PLATFORM_ACT_MOVE_180: if (square_plat_set_yaw_until_timer(DEGREES(180), 60)) o->oAction = BITDW_PYRAMID_PLATFORM_ACT_MOVE_270; break;
        case BITDW_PYRAMID_PLATFORM_ACT_MOVE_270: if (square_plat_set_yaw_until_timer(DEGREES(-90), 60)) o->oAction = BITDW_PYRAMID_PLATFORM_ACT_MOVE_0;   break;
        default:                                                                                                                                           break;
    }
    cur_obj_move_using_fvel_and_gravity();
    load_object_collision_model();
}
