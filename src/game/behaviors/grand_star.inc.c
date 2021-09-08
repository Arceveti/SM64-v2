// grand_star.c.inc

s32 arc_to_goal_pos(Vec3f dest, Vec3f src, f32 yVel, f32 gravity) {
    f32 planarDist;
    Angle yaw;
    vec3f_get_lateral_dist_and_yaw(src, dest, &planarDist, &yaw);
    o->oMoveAngleYaw = yaw;
    o->oVelY         = yVel;
    o->oGravity      = gravity;
    s32 time         = (((-2.0f / o->oGravity) * yVel) - 1.0f);
    o->oForwardVel   = (planarDist / time);
    return time;
}

void grand_star_zero_velocity(void) {
    o->oGravity    = 0.0f;
    o->oVelY       = 0.0f;
    o->oForwardVel = 0.0f;
}

void bhv_grand_star_loop(void) {
    Vec3f dest = { 0.0f, 0.0f, 0.0f };
    if (o->oAction == GRAND_STAR_ACT_APPEAR) {
        if (o->oTimer == 0) {
            obj_set_angle(o, 0x0, 0x0, 0x0);
            o->oAngleVelYaw = 0x400;
            cur_obj_play_sound_2(SOUND_GENERAL2_STAR_APPEARS);
        }
        if (o->oTimer > 70) o->oAction = GRAND_STAR_ACT_JUMP;
        spawn_sparkle_particles(3, 200, 80, -60);
    } else if (o->oAction == GRAND_STAR_ACT_JUMP) {
        if (o->oTimer == 0) {
            cur_obj_play_sound_2(SOUND_GENERAL_GRAND_STAR);
            cutscene_object(CUTSCENE_STAR_SPAWN, o);
            o->oGrandStarArcTime = arc_to_goal_pos(dest, &o->oPosVec, 80.0f, -2.0f);
        }
        cur_obj_move_using_fvel_and_gravity();
        if (o->oSubAction == GRAND_STAR_SUB_ACT_START_JUMP) {
            if (o->oPosY       < o->oHomeY) {
                o->oPosY       = o->oHomeY;
                o->oVelY       = 60.0f;
                o->oForwardVel = 0.0f;
                o->oSubAction  = GRAND_STAR_SUB_ACT_CONTINUE_JUMP;
                cur_obj_play_sound_2(SOUND_GENERAL_GRAND_STAR_JUMP);
            }
        } else if ((o->oVelY < 0.0f) && (o->oPosY < (o->oHomeY + 200.0f))) {
            o->oPosY = (o->oHomeY + 200.0f);
            grand_star_zero_velocity();
            gObjCutsceneDone = TRUE;
            set_mario_npc_dialog(MARIO_DIALOG_STOP);
            o->oAction         = GRAND_STAR_ACT_WAIT_FOR_INTERACTION;
            o->oInteractStatus = INT_STATUS_NONE;
            cur_obj_play_sound_2(SOUND_GENERAL_GRAND_STAR_JUMP);
        }
        spawn_sparkle_particles(3, 200, 80, -60);
    } else { // act 2
        cur_obj_become_tangible();
        if (o->oInteractStatus & INT_STATUS_INTERACTED) {
            obj_mark_for_deletion(o);
            o->oInteractStatus = INT_STATUS_NONE;
        }
    }
    if (o->oAngleVelYaw > 0x400) o->oAngleVelYaw -= 0x100;
    o->oFaceAngleYaw += o->oAngleVelYaw;
    cur_obj_scale(2.0f);
    o->oGraphYOffset = 110.0f;
#ifdef PUPPYLIGHTS
    cur_obj_set_light_properties_default(PUPPYLIGHTS_GRAND_STAR_LIGHT, COLOR_RGBA32_STAR_LIGHT);
    cur_obj_enable_light();
#endif
}
