// wind.c.inc

void spawn_wind_particles(Angle pitch, Angle yaw) {
    s32 i;
    for ((i = 0); (i < 3); (i++)) {
        struct Object *wind = spawn_object(o, MODEL_MIST, bhvWind);
        wind->oMoveAngleYaw   = yaw;
        wind->oMoveAnglePitch = pitch;
    }
}

void bhv_wind_loop(void) {
    s16 size = 500;
    if (o->oTimer == 0) {
        o->oOpacity = 100;
        if (o->oMoveAnglePitch == 0x0) {
            obj_translate_xz_random(o, 900.0f);
            o->oPosX         += (sins(o->oMoveAngleYaw + DEG(180)) * size); // NOP as Pitch is 0
            o->oPosY         += 80.0f + random_f32_around_zero(200.0f);
            o->oPosZ         += (coss(o->oMoveAngleYaw + DEG(180)) * size); // -coss(a) * size
            o->oMoveAngleYaw += random_f32_around_zero(4000.0f);
            o->oForwardVel    = ((random_float() * 70.0f) + 50.0f);
        } else {
            obj_translate_xz_random(o, 600.0f);
            o->oPosY        -= (size - 200); // 300
            o->oVelY         = ((random_float() * 30.0f) + 50.0f);
            o->oMoveAngleYaw = random_u16();
            o->oForwardVel   = 10.0f;
        }
        obj_set_billboard(o);
        cur_obj_scale(1.0f);
    }
    if (o->oTimer > 8) obj_mark_for_deletion(o);
    o->oFaceAnglePitch += (4000.0f + (2000.0f * random_float()));
    o->oFaceAngleYaw   += (4000.0f + (2000.0f * random_float()));
    cur_obj_move_using_fvel_and_gravity();
}
