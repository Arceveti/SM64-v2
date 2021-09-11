// sparkle_spawn_star.c.inc

struct ObjectHitbox sSparkleSpawnStarHitbox = {
    /* interactType:      */ INTERACT_STAR_OR_KEY,
    /* downOffset:        */  0,
    /* damageOrCoinValue: */  0,
    /* health:            */  0,
    /* numLootCoins:      */  0,
    /* radius:            */ 80,
    /* height:            */ 50,
    /* hurtboxRadius:     */  0,
    /* hurtboxHeight:     */  0,
};

void bhv_spawned_star_init(void) {
    if (!(o->oInteractionSubtype & INT_SUBTYPE_NO_EXIT)) o->oBehParams = o->parentObj->oBehParams;
#ifdef PUPPYLIGHTS
    if (save_file_get_star_flags((gCurrSaveFileNum - 1), (gCurrCourseNum - 1)) & (1 << ((o->oBehParams >> 24) & 0xFF))) {
        cur_obj_set_model(MODEL_TRANSPARENT_STAR);
        cur_obj_set_light_properties_default(PUPPYLIGHTS_STAR_LIGHT, COLOR_RGBA32_TRANSPARENT_STAR_LIGHT);
    } else {
        cur_obj_set_light_properties_default(PUPPYLIGHTS_STAR_LIGHT, COLOR_RGBA32_STAR_LIGHT);
    }
#else
    if (save_file_get_star_flags((gCurrSaveFileNum - 1), (gCurrCourseNum - 1)) & (1 << ((o->oBehParams >> 24) & 0xFF))) cur_obj_set_model(MODEL_TRANSPARENT_STAR);
#endif
    cur_obj_play_sound_2(SOUND_GENERAL2_STAR_APPEARS);
#ifdef PUPPYLIGHTS
    cur_obj_enable_light();
#endif
}

void set_sparkle_spawn_star_hitbox(void) {
    obj_set_hitbox(o, &sSparkleSpawnStarHitbox);
    if (o->oInteractStatus & INT_STATUS_INTERACTED) {
        obj_mark_for_deletion(o);
        o->oInteractStatus = INT_STATUS_NONE;
    }
}

void set_home_to_mario(void) {
    vec3_copy(&o->oHomeVec, &gMarioObject->oPosVec);
    o->oHomeY     += 250.0f;
    o->oPosY       = o->oHomeY;
    f32 lateralDist;
    vec3f_get_lateral_dist(&o->oPosVec, &o->oHomeVec, &lateralDist);
    o->oForwardVel = (lateralDist / 23.0f); //?
}

void bhv_spawned_star_no_level_exit_loop(void) {
    switch (o->oAction) {
        case SPAWN_STAR_POS_CUTSCENE_ACT_START:
            if (o->oTimer == 0) {
                cutscene_object(CUTSCENE_STAR_SPAWN, o);
                set_time_stop_flags(TIME_STOP_ENABLED | TIME_STOP_MARIO_AND_DOORS);
                o->activeFlags |= ACTIVE_FLAG_INITIATED_TIME_STOP;
                o->oAngleVelYaw = 0x800;
                if (o->oBehParams2ndByte == SPAWN_STAR_POS_CUTSCENE_BP_SPAWN_AT_MARIO) {
                    set_home_to_mario();
                } else {
                    o->oForwardVel = 0.0f;
                    o->oHomeY      = o->oPosY;
                }
                o->oMoveAngleYaw = cur_obj_angle_to_home();
                o->oVelY         = 50.0f;
                o->oGravity      = -4.0f;
                spawn_mist_particles();
            }
            cur_obj_play_sound_1(SOUND_ENV_STAR);
            spawn_object(o, MODEL_NONE, bhvSparkleSpawn);
            if ((o->oVelY < 0) && (o->oPosY < o->oHomeY)) {
                o->oAction = SPAWN_STAR_POS_CUTSCENE_ACT_BOUNCE;
                o->oForwardVel =  0.0f;
                o->oVelY       = 20.0f;
                o->oGravity    = -1.0f;
                play_power_star_jingle(TRUE);
            }
            break;
        case SPAWN_STAR_POS_CUTSCENE_ACT_BOUNCE:
            if (o->oVelY < -4.0f) o->oVelY = -4.0f;
            if ((o->oVelY <  0.0f) && (o->oPosY < o->oHomeY)) {
                gObjCutsceneDone = TRUE;
                o->oVelY    = 0.0f;
                o->oGravity = 0.0f;
                o->oAction  = SPAWN_STAR_POS_CUTSCENE_ACT_END;
            }
            spawn_object(o, MODEL_NONE, bhvSparkleSpawn);
            break;
        case SPAWN_STAR_POS_CUTSCENE_ACT_END:
            clear_time_stop_flags(TIME_STOP_ENABLED | TIME_STOP_MARIO_AND_DOORS);
            o->activeFlags &= ~ACTIVE_FLAG_INITIATED_TIME_STOP;
            o->oAction = SPAWN_STAR_POS_CUTSCENE_ACT_SLOW_STAR_ROTATION;
            break;
        case SPAWN_STAR_POS_CUTSCENE_ACT_SLOW_STAR_ROTATION:
            set_sparkle_spawn_star_hitbox();
            if (o->oAngleVelYaw > 0x400) o->oAngleVelYaw -= 0x40; // Slow star rotation
            break;
    }
    cur_obj_move_using_fvel_and_gravity();
    o->oFaceAngleYaw  += o->oAngleVelYaw;
    o->oInteractStatus = INT_STATUS_NONE;
}

void bhv_spawn_star_no_level_exit(u32 params) {
    struct Object *starObj = spawn_object(o, MODEL_STAR, bhvSpawnedStarNoLevelExit);
    starObj->oBehParams          = (params << 24);
    starObj->oInteractionSubtype = INT_SUBTYPE_NO_EXIT;
    obj_set_angle(starObj, 0x0, 0x0, 0x0);
}
