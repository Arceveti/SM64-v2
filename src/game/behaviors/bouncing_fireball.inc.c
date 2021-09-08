// bouncing_fireball.c.inc

void bhv_bouncing_fireball_flame_loop(void) {
    o->activeFlags |= ACTIVE_FLAG_IGNORE_WATER_LEVEL;
    cur_obj_update_floor_and_walls();
    switch (o->oAction) {
        case BOUNCING_FLAME_ACT_SPAWNED:
            if (o->oTimer == 0) {
                o->oAnimState = (random_float() * 10.0f);
                o->oVelY      = 30.0f;
            }
            if (o->oMoveFlags & OBJ_MOVE_LANDED) o->oAction = BOUNCING_FLAME_ACT_LANDED;
            break;
        case BOUNCING_FLAME_ACT_LANDED:
            if (o->oTimer == 0) {
                o->oVelY       = 50.0f;
                o->oForwardVel = 30.0f;
            }
            if (o->oMoveFlags & (OBJ_MOVE_UNDERWATER_ON_GROUND | OBJ_MOVE_AT_WATER_SURFACE | OBJ_MOVE_ON_GROUND) && o->oTimer > 100) obj_mark_for_deletion(o);
            break;
    }
    if (o->oTimer > 300) obj_mark_for_deletion(o);
    cur_obj_move_standard(78);
    o->oInteractStatus = INT_STATUS_NONE;
}

void bhv_bouncing_fireball_spawner_loop(void) {
    struct Object *flameObj;
    f32 scale;
// #ifdef PUPPYLIGHTS
//     cur_obj_set_light_properties_default(PUPPYLIGHTS_FLAME_LIGHT, COLOR_RGBA32_FLAME_LIGHT);
//     cur_obj_enable_light();
// #endif
    switch (o->oAction) {
        case BOUNCING_FIREBALL_SPAWNER_ACT_IDLE:
            if (o->oDistanceToMario < 2000.0f) o->oAction = BOUNCING_FIREBALL_SPAWNER_ACT_SPAWN_FLAME;
            break;
        case BOUNCING_FIREBALL_SPAWNER_ACT_SPAWN_FLAME:
            flameObj = spawn_object(o, MODEL_RED_FLAME, bhvBouncingFireballSpawnerFlame);
            scale    = ((10 - o->oTimer) * 0.5f);
            obj_scale(flameObj, scale);
            if (o->oTimer == 0) obj_become_tangible(flameObj);
            if (o->oTimer > 10) o->oAction = BOUNCING_FIREBALL_SPAWNER_ACT_COOLDOWN;
            break;
        case BOUNCING_FIREBALL_SPAWNER_ACT_COOLDOWN:
            if (o->oTimer == 0) o->oBouncingFireBallSpawnerRandomCooldown = (random_float() * 100.0f);
            if ((o->oBouncingFireBallSpawnerRandomCooldown + 100) < o->oTimer) o->oAction = BOUNCING_FIREBALL_SPAWNER_ACT_IDLE;
            break;
    }
}
