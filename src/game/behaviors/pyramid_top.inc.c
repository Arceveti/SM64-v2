/**
 * Behaviors for bhvPyramidTop, bhvPyramidTopFragment, and
 * bhvPyramidPillarTouchDetector.
 *
 * bhvPyramidTop controls Shifting Sand Land's pyramid's top piece, which
 *      rotates and explodes when Mario stands on all four pillars.
 * bhvPyramidTopFragment controls the shards that the pyramid's top emits when
 *      it is spinning and exploding.
 * bhvPyramidPillarTouchDetector controls the intangible collision boxes that
 *      Mario touches when on top of each pillar.
 */

/**
 * Spawn the four pillars' touch detectors.
 */
void bhv_pyramid_top_init(void) {
    spawn_object_abs_with_rot(o, 0, MODEL_NONE, bhvPyramidPillarTouchDetector,  1789, 1024,   764, 0x0, 0x0, 0x0);
    spawn_object_abs_with_rot(o, 0, MODEL_NONE, bhvPyramidPillarTouchDetector,  1789,  896, -2580, 0x0, 0x0, 0x0);
    spawn_object_abs_with_rot(o, 0, MODEL_NONE, bhvPyramidPillarTouchDetector, -5883, 1024, -2580, 0x0, 0x0, 0x0);
    spawn_object_abs_with_rot(o, 0, MODEL_NONE, bhvPyramidPillarTouchDetector, -5883, 1024,   764, 0x0, 0x0, 0x0);
}

/**
 * Animate the pyramid top as rising and then spinning. Generate some pyramid
 * fragments in the process.
 */
void bhv_pyramid_top_spinning(void) {
    struct Object *pyramidFragment;
    // (TODO: What is this doing)
    o->oPosX = (o->oHomeX + (sins(o->oTimer * 0x4000) * 40.0f));
    // At first, move upward smoothly without rotating.
    if (o->oTimer < 60) {
        o->oPosY = (o->oHomeY + absf(sins(o->oTimer * 0x2000) * 10.0f));
    } else {
        // Then, rotate at an accelerating rate, and move upward at a constant rate.
        o->oAngleVelYaw += 0x100;
        if (o->oAngleVelYaw > DEG(33.75)) {
            o->oAngleVelYaw = DEG(33.75);
            o->oVelY        = 5.0f;
        }
        o->oFaceAngleYaw += o->oAngleVelYaw;
        o->oPosY         += o->oVelY;
    }
    // Every frame until 90 frames have passed, generate a pyramid fragment
    // with a random velocity and angle.
    if (o->oTimer < 90) {
        pyramidFragment = spawn_object(o, MODEL_DIRT_ANIMATION, bhvPyramidTopFragment);
        pyramidFragment->oForwardVel               = ((random_float() * 10.0f) + 20.0f);
        pyramidFragment->oMoveAngleYaw             = random_u16();
        pyramidFragment->oPyramidTopFragmentsScale = 0.8f;
        pyramidFragment->oGravity                  =  (random_float() + 2.0f);
    }
    // After enough time, transition to the exploding state.
    if (o->oTimer == 150) o->oAction = PYRAMID_TOP_ACT_EXPLODE;
}

/**
 * Explode the pyramid top, generating dust and pyramid fragments.
 */
void bhv_pyramid_top_explode(void) {
    struct Object *pyramidFragment;
    s16 i;
    spawn_mist_particles_variable(0, 0, 690.0f);
    // Generate 30 pyramid fragments with random properties.
    for ((i = 0); (i < 30); (i++)) {
        pyramidFragment = spawn_object(o, MODEL_DIRT_ANIMATION, bhvPyramidTopFragment);
        pyramidFragment->oForwardVel               = ((random_float() * 50.0f) + 80.0f);
        pyramidFragment->oVelY                     = ((random_float() * 80.0f) + 20.0f);
        pyramidFragment->oMoveAngleYaw             = random_u16();
        pyramidFragment->oPyramidTopFragmentsScale = 3.0f;
        pyramidFragment->oGravity                  = ((random_float() *  2.0f) + 5.0f);
    }
#ifdef SSL_PILLARS_CUTSCENE
    if (gMarioState->action & ACT_FLAG_RIDING_SHELL) disable_time_stop_including_mario();
#endif
    // Deactivate the pyramid top.
    obj_mark_for_deletion(o);
}

void bhv_pyramid_top_loop(void) {
#ifdef HUD_SECRETS
    gSecretsCollected = o->oPyramidTopPillarsTouched;
#endif
    switch (o->oAction) {
        case PYRAMID_TOP_ACT_CHECK_IF_SOLVED:
            if (o->oPyramidTopPillarsTouched == 4) {
                play_puzzle_jingle();
#ifdef SSL_PILLARS_CUTSCENE
                cutscene_object(CUTSCENE_SSL_PYRAMID_EXPLODE, o);
#endif
                o->oAction = PYRAMID_TOP_ACT_SPINNING;
            }
            break;
        case PYRAMID_TOP_ACT_SPINNING:
            if (o->oTimer == 0) {
#ifdef SSL_PILLARS_CUTSCENE
                if (gMarioState->action & ACT_FLAG_RIDING_SHELL) {
                    gMarioState->forwardVel = 0.0f;
                    enable_time_stop_including_mario();
                }
#endif
                cur_obj_play_sound_2(SOUND_GENERAL2_PYRAMID_TOP_SPIN);
            }
            bhv_pyramid_top_spinning();
            break;
        case PYRAMID_TOP_ACT_EXPLODE:
            if (o->oTimer == 0) create_sound_spawner(SOUND_GENERAL2_PYRAMID_TOP_EXPLOSION);
            bhv_pyramid_top_explode();
            break;
    }
}

/**
 * Initialize the pyramid fragment.
 */
void bhv_pyramid_top_fragment_init(void) {
    o->oFriction  = 0.999f;
    o->oBuoyancy  = 2.0f;
    o->oAnimState = TINY_DIRT_PARTICLE_ANIM_STATE_DIRT;
    cur_obj_scale(o->oPyramidTopFragmentsScale);
}

/**
 * Rotate the pyramid fragment along the yaw and pitch axes. After some time,
 * deactivate it.
 */
void bhv_pyramid_top_fragment_loop(void) {
    object_step();
    o->oFaceAngleYaw   += DEG(22.5);
    o->oFaceAnglePitch += DEG(22.5);
    if (o->oTimer == 60) obj_mark_for_deletion(o);
}

/**
 * If Mario touches a pillar's touch detector, count it towards the pyramid
 * top's total count of touched detectors, and deactivate the detector.
 */
void bhv_pyramid_pillar_touch_detector_loop(void) {
    cur_obj_become_tangible();
    if (obj_check_if_collided_with_object(o, gMarioObject)) {
        // Increase the pyramid top's count of pillars touched.
        o->parentObj->oPyramidTopPillarsTouched++;
        obj_mark_for_deletion(o);
    }
}
