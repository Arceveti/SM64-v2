#include "config.h"

// spawn_default_star.c.inc

static struct ObjectHitbox sCollectStarHitbox = {
    /* interactType:      */ INTERACT_STAR_OR_KEY,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 80,
    /* height:            */ 50,
    /* hurtboxRadius:     */ 0,
    /* hurtboxHeight:     */ 0,
};

void bhv_collect_star_init(void) {
    u8 currentLevelStarFlags;
    s8 starId = ((o->oBehParams >> 24) & 0xFF);
#ifdef GLOBAL_STAR_IDS
    currentLevelStarFlags = save_file_get_star_flags((gCurrSaveFileNum - 1), ((starId / 7) - 1));
    if (currentLevelStarFlags & (1 << (starId % 7))) {
#else
    currentLevelStarFlags = save_file_get_star_flags((gCurrSaveFileNum - 1), (gCurrCourseNum - 1));
    if (currentLevelStarFlags & (1 << starId)) {
#endif
        o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_TRANSPARENT_STAR];
    } else {
        o->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_STAR];
    }
    obj_set_hitbox(o, &sCollectStarHitbox);
}

void bhv_collect_star_loop(void) {
    o->oFaceAngleYaw += 0x800;

    if (o->oInteractStatus & INT_STATUS_INTERACTED) {
        mark_obj_for_deletion(o);
        o->oInteractStatus = INT_STATUS_NONE;
    }
}

void bhv_star_spawn_arc_init(void) {
    f32 dx                   = (o->oHomeX - o->oPosX);
    f32 dz                   = (o->oHomeZ - o->oPosZ);
    o->oMoveAngleYaw         = atan2s(   dz,       dx);
    o->oStarSpawnDisFromHome = sqrtf(sqr(dx) + sqr(dz));
    o->oVelY                 = ((o->oHomeY - o->oPosY)   / 30.0f);
    o->oForwardVel           = (o->oStarSpawnDisFromHome / 30.0f); //! fast invsqrt?
    o->oStarSpawnVelY        = o->oPosY;
    cutscene_object((((o->oBehParams2ndByte == SPAWN_STAR_ARC_CUTSCENE_BP_DEFAULT_STAR) || (gCurrCourseNum == COURSE_BBH)) ? CUTSCENE_STAR_SPAWN : CUTSCENE_RED_COIN_STAR_SPAWN), o);
    set_time_stop_flags(TIME_STOP_ENABLED | TIME_STOP_MARIO_AND_DOORS);
    o->activeFlags |= ACTIVE_FLAG_INITIATED_TIME_STOP;
    cur_obj_become_intangible();
}

void bhv_star_spawn_arc_loop(void) {
    switch (o->oAction) {
        case SPAWN_STAR_ARC_CUTSCENE_ACT_START:
            o->oFaceAngleYaw += 0x1000;
            if (o->oTimer > 20) o->oAction = SPAWN_STAR_ARC_CUTSCENE_ACT_GO_TO_HOME;
            break;
        case SPAWN_STAR_ARC_CUTSCENE_ACT_GO_TO_HOME:
            obj_move_xyz_using_fvel_and_yaw(o);
            o->oStarSpawnVelY += o->oVelY;
            o->oPosY = o->oStarSpawnVelY + (sins((o->oTimer * 0x8000) / 30) * 400.0f);
            o->oFaceAngleYaw += 0x1000;
            spawn_object(o, MODEL_NONE, bhvSparkleSpawn);
            cur_obj_play_sound_1(SOUND_ENV_STAR);
            if (o->oTimer == 30) {
                o->oAction = SPAWN_STAR_ARC_CUTSCENE_ACT_BOUNCE;
                o->oForwardVel = 0.0f;
                // Set to exact home coordinates
                o->oPosX = o->oHomeX;
                o->oPosZ = o->oHomeZ;
                play_power_star_jingle(TRUE);
            }
            break;
        case SPAWN_STAR_ARC_CUTSCENE_ACT_BOUNCE:
            o->oVelY = (o->oTimer < 20) ? (20 - o->oTimer) : (-10.0f);
            spawn_object(o, MODEL_NONE, bhvSparkleSpawn);
            obj_move_xyz_using_fvel_and_yaw(o);
            o->oFaceAngleYaw = (o->oFaceAngleYaw - (o->oTimer * 0x10) + 0x1000);
            cur_obj_play_sound_1(SOUND_ENV_STAR);

            if (o->oPosY < o->oHomeY) {
                cur_obj_play_sound_2(SOUND_GENERAL_STAR_APPEARS);
                cur_obj_become_tangible();
                o->oPosY = o->oHomeY;
                o->oAction = SPAWN_STAR_ARC_CUTSCENE_ACT_END;
            }
            break;
        case SPAWN_STAR_ARC_CUTSCENE_ACT_END:
            o->oFaceAngleYaw += 0x800;
            if (o->oTimer == 20) {
                gObjCutsceneDone = TRUE;
                clear_time_stop_flags(TIME_STOP_ENABLED | TIME_STOP_MARIO_AND_DOORS);
                o->activeFlags &= ~ACTIVE_FLAG_INITIATED_TIME_STOP;
            }
            if (o->oInteractStatus & INT_STATUS_INTERACTED) {
                mark_obj_for_deletion(o);
                o->oInteractStatus = INT_STATUS_NONE;
            }
            break;
    }
}

struct Object *spawn_star(struct Object *starObj, f32 x, f32 y, f32 z) {
    starObj = spawn_object_abs_with_rot(o, 0, MODEL_STAR, bhvStarSpawnCoordinates,
                                        o->oPosX, o->oPosY, o->oPosZ,
                                        0x0, 0x0, 0x0);
    starObj->oBehParams      = o->oBehParams;
    starObj->oHomeX          = x;
    starObj->oHomeY          = y;
    starObj->oHomeZ          = z;
    starObj->oFaceAnglePitch = 0x0;
    starObj->oFaceAngleRoll  = 0x0;
    return starObj;
}

void spawn_default_star(f32 x, f32 y, f32 z) {
    struct Object *starObj = NULL;
    starObj = spawn_star(starObj, x, y, z);
    starObj->oBehParams2ndByte = SPAWN_STAR_ARC_CUTSCENE_BP_DEFAULT_STAR;
}

void spawn_red_coin_cutscene_star(f32 x, f32 y, f32 z) {
    struct Object *starObj = NULL;
    starObj = spawn_star(starObj, x, y, z);
    starObj->oBehParams2ndByte = SPAWN_STAR_ARC_CUTSCENE_BP_HIDDEN_STAR;
}

void spawn_no_exit_star(f32 x, f32 y, f32 z) {
    struct Object *starObj = NULL;
    starObj = spawn_star(starObj, x, y, z);
    starObj->oBehParams2ndByte = SPAWN_STAR_ARC_CUTSCENE_BP_HIDDEN_STAR;
    starObj->oInteractionSubtype |= INT_SUBTYPE_NO_EXIT;
}

void bhv_hidden_red_coin_star_init(void) {
    s16 numRedCoinsRemaining;
    struct Object *starObj = NULL;
    spawn_object(o, MODEL_TRANSPARENT_STAR, bhvRedCoinStarMarker);
    numRedCoinsRemaining = count_objects_with_behavior(bhvRedCoin);
    if (numRedCoinsRemaining == 0) {
        starObj = spawn_object_abs_with_rot(o, 0, MODEL_STAR, bhvStar, o->oPosX, o->oPosY, o->oPosZ, 0x0, 0x0, 0x0);
        starObj->oBehParams = o->oBehParams;
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }
    o->oHiddenStarTriggerCounter = (8 - numRedCoinsRemaining);
}

void bhv_hidden_red_coin_star_loop(void) {
    struct Object *starMarker = cur_obj_nearest_object_with_behavior(bhvRedCoinStarMarker);
    if (starMarker != NULL && (o->oPosY - starMarker->oPosY) > 2000.0f) obj_mark_for_deletion(starMarker);
    gRedCoinsCollected = o->oHiddenStarTriggerCounter;
    switch (o->oAction) {
        case HIDDEN_STAR_ACT_INACTIVE:
            if (o->oHiddenStarTriggerCounter == 8) o->oAction = HIDDEN_STAR_ACT_ACTIVE;
            break;
        case HIDDEN_STAR_ACT_ACTIVE:
            if (o->oTimer > 2) {
                spawn_red_coin_cutscene_star(o->oPosX, o->oPosY, o->oPosZ);
                spawn_mist_particles();
                o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
            }
            break;
    }
}
