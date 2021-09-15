/**
 * Behavior for bhvSlCrackedIce.
 *
 * This unused behavior controls a platform that shatters into small triangles
 * if Mario ground pounds it.
 *
 * Its collision model perfectly aligns with the hole leading to In the
 * Deep Freeze in Snowman's Land. It is likely that players early in development
 * would have to ground pound this platform before being able to access the star.
 *
 * Curiously, the triangles spawned when the platform breaks use a model that
 * is not used anywhere else.
 */

void bhv_sl_cracked_ice_loop(void) {
    if (cur_obj_is_mario_ground_pounding_platform()) {
        gMarioStates[0].vel[1] = 0.0f;
        spawn_mist_particles();
        spawn_triangle_break_particles(20, MODEL_SL_CRACKED_ICE_CHUNK, 3.0f, OBJ_ANIM_STATE_DEFAULT);
        create_sound_spawner(SOUND_GENERAL_BREAK_BOX);
        obj_mark_for_deletion(o);
    } else {
        load_object_collision_model();
    }
}
