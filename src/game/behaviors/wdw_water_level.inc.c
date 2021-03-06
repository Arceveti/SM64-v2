// wdw_water_level.c.inc

// called when WDW is loaded.
void bhv_init_changing_water_level_loop(void) {
    if (o->oAction == WATER_LEVEL_ACT_INIT) {
        if (gEnvironmentRegions != NULL) o->oAction = WATER_LEVEL_ACT_IDLE;
    } else if (o->oTimer < 10) {
        *gEnvironmentLevels = gEnvironmentRegions[6];
    } else {
#ifdef WDW_DISABLE_AMBIENT_WAVES
        gEnvironmentRegions[6] = *gEnvironmentLevels;
#else
        gEnvironmentRegions[6] = (*gEnvironmentLevels + (sins(o->oWaterLevelTriggerAmbientWaves) * 20.0f));
        o->oWaterLevelTriggerAmbientWaves += 0x200;
#endif
    }
}

void bhv_water_level_diamond_loop(void) {
    if (gEnvironmentRegions != NULL) {
        switch (o->oAction) {
            case WATER_LEVEL_DIAMOND_ACT_INIT:
                o->oFaceAngleYaw = 0x0;
                o->oWaterLevelTriggerTargetWaterLevel = (s32) o->oPosY;
                if (o->oTimer > 10) o->oAction = WATER_LEVEL_DIAMOND_ACT_IDLE;
                break;
            case WATER_LEVEL_DIAMOND_ACT_IDLE:
                if (obj_check_if_collided_with_object(o, gMarioObject) && !gWDWWaterLevelChanging) {
                    o->oAction = WATER_LEVEL_DIAMOND_ACT_CHANGE_WATER_LEVEL;
                    gWDWWaterLevelChanging = TRUE;
                }
                break;
            case WATER_LEVEL_DIAMOND_ACT_CHANGE_WATER_LEVEL:
                o->oAngleVelYaw = 0x0;
                approach_s16_symmetric_bool(gEnvironmentLevels, o->oWaterLevelTriggerTargetWaterLevel, 10);
                if (*gEnvironmentLevels == o->oWaterLevelTriggerTargetWaterLevel) {
                    if ((Angle) o->oFaceAngleYaw == 0x0) {
                        o->oAction = WATER_LEVEL_DIAMOND_ACT_IDLE_SPINNING;
                    } else {
                        o->oAngleVelYaw = DEG(11.25);
                    }
                } else {
                    if (o->oTimer == 0) {
                        cur_obj_play_sound_2(SOUND_GENERAL_WATER_LEVEL_TRIG);
                    } else {
                        cur_obj_play_sound_1(SOUND_ENV_WATER_DRAIN);
                    }
                    o->oAngleVelYaw = DEG(11.25);
#if ENABLE_RUMBLE
                    reset_rumble_timers_vibrate(2);
#endif
                }
                break;
            case WATER_LEVEL_DIAMOND_ACT_IDLE_SPINNING:
                if (!obj_check_if_collided_with_object(o, gMarioObject)) {
                    gWDWWaterLevelChanging = FALSE;
                    o->oAction = WATER_LEVEL_DIAMOND_ACT_IDLE;
                    o->oAngleVelYaw = 0x0;
                }
                break;
        }
        o->oFaceAngleYaw += o->oAngleVelYaw;
    }
}
