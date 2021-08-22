// water_pillar.c.inc

void water_level_pillar_undrained(void) {
    struct Object *otherWaterPillar;
    switch (o->oAction) {
        case WATER_PILLAR_ACT_UNPOUNDED_IDLE:
            if (cur_obj_is_mario_ground_pounding_platform()) {
                o->oAction = WATER_PILLAR_ACT_LOWER_SELF;
                spawn_mist_particles();
            }
            break;
        case WATER_PILLAR_ACT_LOWER_SELF:
            if (o->oTimer < 4) {
                o->oPosY -= 20.0f;
            } else {
                o->oAction = WATER_PILLAR_ACT_POUNDED_1;
            }
            break;
        case WATER_PILLAR_ACT_POUNDED_1:
            otherWaterPillar = cur_obj_nearest_object_with_behavior(bhvWaterLevelPillar);
            if (otherWaterPillar != NULL && otherWaterPillar->oAction < WATER_PILLAR_ACT_POUNDED_1) o->oAction = WATER_PILLAR_ACT_POUNDED_2;
            break;
        case WATER_PILLAR_ACT_POUNDED_2:
            otherWaterPillar = cur_obj_nearest_object_with_behavior(bhvWaterLevelPillar);
            if (otherWaterPillar != NULL && otherWaterPillar->oAction > WATER_PILLAR_ACT_LOWER_SELF) {
                o->oAction = WATER_PILLAR_ACT_DRAIN_WATER;

                save_file_set_flags(SAVE_FLAG_MOAT_DRAINED);
                play_puzzle_jingle();
            }
            break;
        case WATER_PILLAR_ACT_DRAIN_WATER:
            cur_obj_play_sound_1(SOUND_ENV_WATER_DRAIN);
            if (o->oTimer < 300) {
                gEnvironmentLevels[2] = approach_f32_symmetric(gEnvironmentLevels[2], -2450.0f, 5.0f);
                gEnvironmentLevels[0] = approach_f32_symmetric(gEnvironmentLevels[0], -2450.0f, 5.0f);
#if ENABLE_RUMBLE
                reset_rumble_timers_vibrate(2);
#endif
            } else {
                o->oAction = WATER_PILLAR_ACT_END;
            }
            break;
        case WATER_PILLAR_ACT_END:
            break;
    }
}

void water_level_pillar_drained(void) {
    if (o->oTimer == 0) {
        o->oPosY -= 80.0f;
        gEnvironmentLevels[2] = -2450;
        gEnvironmentLevels[0] = -2450;
    }
}

void bhv_water_level_pillar_init(void) {
    if (save_file_get_flags() & SAVE_FLAG_MOAT_DRAINED) o->oWaterLevelPillarDrained = 1;
}

void bhv_water_level_pillar_loop(void) {
    if (o->oWaterLevelPillarDrained) {
        water_level_pillar_drained();
    } else {
        water_level_pillar_undrained();
    }
    gEnvironmentRegions[18] = gEnvironmentLevels[2];
    gEnvironmentRegions[ 6] = gEnvironmentLevels[0];
}
