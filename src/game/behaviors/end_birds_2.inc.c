// end_birds_2.inc.c

void bhv_end_birds_2_loop(void) {
    Vec3f sp3C;
    f32 sp34;
    s16 sp32, sp30;

    gCurrentObject->oForwardVel = (random_float() * 10.0f) + 25.0f;

    switch (gCurrentObject->oAction) {
        case 0:
            cur_obj_scale(0.7f);
            gCurrentObject->oAction++;
            break;
        case 1:
            vec3f_get_dist_and_angle(gCamera->pos, gCamera->focus, &sp34, &sp32,
                                     &sp30);
            sp30 += 0x1000;
            vec3f_set_dist_and_angle(gCamera->pos, sp3C, 14000.0f, sp32, sp30);
            obj_rotate_towards_point(gCurrentObject, sp3C, 0, 0, 8, 8);

            if ((gCurrentObject->oEndBirdCutsceneVars9PointX == 0.0f) && (gCurrentObject->oTimer == 0)) {
                cur_obj_play_sound_2(SOUND_GENERAL_BIRDS_FLY_AWAY);
            }
            break;
    }

    cur_obj_set_pos_via_transform();
}
