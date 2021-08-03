// sliding_platform_2.inc.c

static void const *sSlidingPlatform2CollisionData[] = {
    bits_seg7_collision_sliding_platform,
    bits_seg7_collision_twin_sliding_platforms,
    bitfs_seg7_collision_moving_square_platform,
    bitfs_seg7_collision_sliding_platform,
    rr_seg7_collision_sliding_platform,
    rr_seg7_collision_pyramid_platform,
    NULL,
    bitdw_seg7_collision_sliding_platform,
};

void bhv_sliding_plat_2_init(void) {
    u16 params = (u16)(o->oBehParams >> 16);
    s32 collisionDataIndex;

    collisionDataIndex = (params & SLIDING_PLATFORM_TYPE_MASK) >> 7;
    o->collisionData = segmented_to_virtual(sSlidingPlatform2CollisionData[collisionDataIndex]);
    o->oBackAndForthPlatformPathLength = 50.0f * (params & SLIDING_PLATFORM_LENGTH_MASK);

    if (collisionDataIndex < SLIDING_PLATFORM_BP_RR_PYRAMID || collisionDataIndex > SLIDING_PLATFORM_BP_NULL) {
        o->oBackAndForthPlatformVel = 15.0f;
        if (params & SLIDING_PLATFORM_DIRECTION_MASK) o->oMoveAngleYaw += 0x8000;
    } else {
        o->oBackAndForthPlatformVel = 10.0f;
        o->oBackAndForthPlatformDirection = (params & SLIDING_PLATFORM_DIRECTION_MASK) ? -1.0f : 1.0f;
    }
}

void bhv_sliding_plat_2_loop(void) {
    if (o->oTimer > 10) {
        o->oBackAndForthPlatformDistance += o->oBackAndForthPlatformVel;
        if (clamp_f32(&o->oBackAndForthPlatformDistance, -o->oBackAndForthPlatformPathLength, 0.0f)) {
            o->oBackAndForthPlatformVel = -o->oBackAndForthPlatformVel;
            o->oTimer = 0;
        }
    }

    obj_perform_position_op(POS_OP_SAVE_POSITION);

    if (o->oBackAndForthPlatformDirection != 0.0f) {
        o->oPosY = o->oHomeY + o->oBackAndForthPlatformDistance * o->oBackAndForthPlatformDirection;
    } else {
        obj_set_dist_from_home(o->oBackAndForthPlatformDistance);
    }

    obj_perform_position_op(POS_OP_COMPUTE_VELOCITY);
}
