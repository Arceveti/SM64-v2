// thi_top.c.inc

struct SpawnParticlesInfo sThiTopPuffs = {
    0, 30, MODEL_WHITE_PARTICLE_SMALL, 0, 40, 0, 20, 40, 252, 30, 20.0f, 0.0f
};

void bhv_thi_huge_island_top_loop(void) {
    if (gTHIWaterDrained) {
        if (o->oTimer == 0) gEnvironmentRegions[18] = 3000;
        cur_obj_hide();
    } else {
        load_object_collision_model();
    }
}

void bhv_thi_tiny_island_top_loop(void) {
    if (!gTHIWaterDrained) {
        if (o->oAction == THI_TOP_ACT_IDLE) {
            if ((o->oDistanceToMario < 500.0f) && ((gMarioStates[0].action == ACT_GROUND_POUND_LAND) || (gMarioStates[0].action == ACT_WATER_GROUND_POUND_LAND))) {
                o->oAction = THI_TOP_ACT_DRAIN_WATER;
                cur_obj_spawn_particles(&sThiTopPuffs);
                spawn_triangle_break_particles(20, MODEL_DIRT_ANIMATION, 0.3f, 3);
                cur_obj_play_sound_2(SOUND_GENERAL_ACTIVATE_CAP_SWITCH);
                cur_obj_hide();
            }
        } else {
            if (o->oTimer < 50) {
                gEnvironmentRegions[18]--;
                cur_obj_play_sound_1(SOUND_ENV_WATER_DRAIN);
            } else {
                gTHIWaterDrained = TRUE;
                play_puzzle_jingle();
            }
        }
    } else {
        if (o->oTimer == 0) gEnvironmentRegions[18] = 700;
        cur_obj_hide();
    }
}
