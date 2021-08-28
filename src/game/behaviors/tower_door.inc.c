// tower_door.c.inc

void bhv_tower_door_loop(void) {
    if (o->oTimer == 0) o->oMoveAngleYaw -= DEG(90);
    if (check_mario_attacking()) {
        obj_explode_and_spawn_coins(80.0f, COIN_TYPE_NONE);
        create_sound_spawner(SOUND_GENERAL_WALL_EXPLOSION);
    }
}
