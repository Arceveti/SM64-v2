
/**
 * Behavior for bhvSeesawPlatform.
 */

/**
 * Collision models for the different seesaw platforms.
 */
static void const *sSeesawPlatformCollisionModels[] = {
    bitdw_seg7_collision_seesaw_platform,
    bits_seg7_collision_seesaw_platform,
    bits_seg7_collision_W_shaped_seesaw_platform,
    bob_seg7_collision_bridge,
    bitfs_seg7_collision_seesaw_platform,
    rr_seg7_collision_seesaw_platform,
    rr_seg7_collision_L_shaped_seesaw_platform,
    vcutm_seg7_collision_seesaw_platform,
};

/**
 * Init function for bhvSeesawPlatform.
 */
void bhv_seesaw_platform_init(void) {
    o->collisionData = segmented_to_virtual(sSeesawPlatformCollisionModels[o->oBehParams2ndByte]);

    // The S-shaped seesaw platform in BitS is large, so increase its collision
    // distance
    if (o->oBehParams2ndByte == SEESAW_PLATFORM_BP_BITS_W_SHAPED) o->oCollisionDistance = 2000.0f;
}

/**
 * Update function for bhvSeesawPlatform.
 */
void bhv_seesaw_platform_update(void) {
    o->oFaceAnglePitch += (s32) o->oSeesawPlatformPitchVel;

    if (absf(o->oSeesawPlatformPitchVel) > 10.0f) cur_obj_play_sound_1(SOUND_ENV_BOAT_ROCKING1);

    if (gMarioObject->platform == o) {
        // Rotate toward mario
        f32 rotation = o->oDistanceToMario * coss(o->oAngleToMario - o->oMoveAngleYaw);

        // Deceleration is faster than acceleration
        rotation *= ((o->oSeesawPlatformPitchVel * rotation) < 0) ? 0.04f : 0.02f;

        o->oSeesawPlatformPitchVel += rotation;
        clamp_f32(&o->oSeesawPlatformPitchVel, -50.0f, 50.0f);
    } else {
        // Rotate back to 0
        oscillate_toward(
            /* value          */ &o->oFaceAnglePitch,
            /* vel            */ &o->oSeesawPlatformPitchVel,
            /* target         */ 0.0f,
            /* velCloseToZero */ 6.0f,
            /* accel          */ 3.0f,
            /* slowdown       */ 3.0f);
    }
}
