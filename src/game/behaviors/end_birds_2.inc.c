// end_birds_2.inc.c

void bhv_end_birds_2_loop(void) {
    Vec3f pos;
    Angle pitch, yaw;
    o->oForwardVel = ((random_float() * 10.0f) + 25.0f);
    switch (o->oAction) {
        case END_BIRDS_ACT_INIT:
            cur_obj_scale(0.7f);
            o->oAction = END_BIRDS_ACT_ACTIVE;
            break;
        case END_BIRDS_ACT_ACTIVE:
            vec3f_get_angle(gCamera->pos, gCamera->focus, &pitch, &yaw);
            yaw += DEG(22.5);
            vec3f_set_dist_and_angle(gCamera->pos, pos, 14000.0f, pitch, yaw);
            obj_rotate_towards_point(o, pos, 0, 0, 8, 8);
            if ((o->oEndBirdCutsceneVars9PointX == 0.0f) && (o->oTimer == 0)) cur_obj_play_sound_2(SOUND_GENERAL_BIRDS_FLY_AWAY);
            break;
    }
    cur_obj_set_pos_via_transform();
}
