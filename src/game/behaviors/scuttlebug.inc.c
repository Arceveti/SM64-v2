// scuttlebug.c.inc

struct ObjectHitbox sScuttlebugHitbox = {
    /* interactType:      */ INTERACT_BOUNCE_TOP,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 1,
    /* health:            */ 1,
    /* numLootCoins:      */ 3,
    /* radius:            */ 130,
    /* height:            */ 70,
    /* hurtboxRadius:     */ 90,
    /* hurtboxHeight:     */ 60,
};

s32 update_angle_from_move_flags(s32 *angle) {
    if (o->oMoveFlags & OBJ_MOVE_HIT_WALL) {
        *angle = o->oWallAngle;
        return 1;
    } else if (o->oMoveFlags & OBJ_MOVE_HIT_EDGE) {
        *angle = o->oMoveAngleYaw + 0x8000;
        return -1;
    }
    return 0;
}

void bhv_scuttlebug_loop(void) {
    f32 accel;
    cur_obj_update_floor_and_walls();
    if (o->oSubAction != SCUTTLEBUG_SUB_ACT_RESET && cur_obj_set_hitbox_and_die_if_attacked(&sScuttlebugHitbox, SOUND_OBJ_DYING_ENEMY1, o->oScuttlebugHasNoLootCoins)) o->oSubAction = SCUTTLEBUG_SUB_ACT_ALERT;
    if (o->oSubAction != SCUTTLEBUG_SUB_ACT_MOVING) o->oScuttlebugIsAtttacking = FALSE;
    switch (o->oSubAction) {
        case SCUTTLEBUG_SUB_ACT_RESET:
            if (o->oMoveFlags & OBJ_MOVE_LANDED) cur_obj_play_sound_2(SOUND_OBJ_GOOMBA_ALERT);
            if (o->oMoveFlags & OBJ_MOVE_MASK_ON_GROUND) {
                o->oHomeX = o->oPosX;
                o->oHomeY = o->oPosY;
                o->oHomeZ = o->oPosZ;
                o->oSubAction = SCUTTLEBUG_SUB_ACT_MOVING;
            }
            break;
        case SCUTTLEBUG_SUB_ACT_MOVING:
            o->oForwardVel = 5.0f;
            if (cur_obj_lateral_dist_from_mario_to_home() > 1000.0f) {
                o->oAngleToMario = cur_obj_angle_to_home();
            } else if (!o->oScuttlebugIsAtttacking) {
                o->oScuttlebugTimer = 0;
                o->oAngleToMario    = obj_angle_to_object(o, gMarioObject);
                if (abs_angle_diff(o->oAngleToMario, o->oMoveAngleYaw) < 0x800) {
                    o->oScuttlebugIsAtttacking = TRUE;
                    o->oVelY = 20.0f;
                    cur_obj_play_sound_2(SOUND_OBJ2_SCUTTLEBUG_ALERT);
                }
            } else if (o->oScuttlebugIsAtttacking) {
                o->oForwardVel = 15.0f;
                o->oScuttlebugTimer++;
                if (o->oScuttlebugTimer > 50) o->oScuttlebugIsAtttacking = FALSE;
            }
            if (update_angle_from_move_flags(&o->oAngleToMario)) o->oSubAction = SCUTTLEBUG_SUB_ACT_HIT_WALL;
            cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x200);
            break;
        case SCUTTLEBUG_SUB_ACT_HIT_WALL:
            o->oForwardVel = 5.0f;
            if ((Angle) o->oMoveAngleYaw == (Angle) o->oAngleToMario) o->oSubAction = SCUTTLEBUG_SUB_ACT_MOVING;
            if (o->oPosY < o->oHomeY - 200.0f) obj_mark_for_deletion(o);
            cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x400);
            break;
        case SCUTTLEBUG_SUB_ACT_ALERT:
            o->oFlags &= ~OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW;
            o->oForwardVel = -10.0f;
            o->oVelY       =  30.0f;
            cur_obj_play_sound_2(SOUND_OBJ2_SCUTTLEBUG_ALERT);
            o->oSubAction = SCUTTLEBUG_SUB_ACT_JUMP;
            break;
        case SCUTTLEBUG_SUB_ACT_JUMP:
            o->oForwardVel = -10.0f;
            if (o->oMoveFlags & OBJ_MOVE_LANDED) {
                o->oSubAction       = SCUTTLEBUG_SUB_ACT_LAND;
                o->oVelY            = 0.0f;
                o->oScuttlebugTimer = 0;
                o->oFlags          |= OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW;
                o->oInteractStatus  = INT_STATUS_NONE;
            }
            break;
        case SCUTTLEBUG_SUB_ACT_LAND:
            o->oForwardVel = 2.0f;
            o->oScuttlebugTimer++;
            if (o->oScuttlebugTimer > 30) o->oSubAction = SCUTTLEBUG_SUB_ACT_RESET;
            break;
    }
    accel = (o->oForwardVel < 10.0f) ? 1.0f : 3.0f;
    cur_obj_init_animation_with_accel_and_sound(SCUTTLEBUG_ANIM_JUMP, accel);
    if (o->oMoveFlags & OBJ_MOVE_MASK_ON_GROUND) set_obj_anim_with_accel_and_sound(SCUTTLEBUG_ANIM_WALK, 23, SOUND_OBJ2_SCUTTLEBUG_WALK);
    if (o->parentObj != o) {
        if (obj_is_hidden(o)) obj_mark_for_deletion(o);
        if (o->activeFlags == ACTIVE_FLAG_DEACTIVATED) o->parentObj->oScuttlebugSpawnerIsDeactivated = TRUE;
    }
    cur_obj_move_standard(-50);
}

void bhv_scuttlebug_spawn_loop(void) {
    struct Object *scuttlebug;
    if (o->oAction == SCUTTLEBUG_SPAWNER_ACT_ACTIVE) {
        if (o->oTimer > 30 && 500.0f < o->oDistanceToMario && o->oDistanceToMario < 1500.0f) {
            cur_obj_play_sound_2(SOUND_OBJ2_SCUTTLEBUG_ALERT);
            scuttlebug                            = spawn_object(o, MODEL_SCUTTLEBUG, bhvScuttlebug);
            scuttlebug->oScuttlebugHasNoLootCoins = o->oScuttlebugSpawnerSpawnWithNoLootCoins;
            scuttlebug->oForwardVel               = 30.0f;
            scuttlebug->oVelY                     = 80.0f;
            o->oAction                            = SCUTTLEBUG_SPAWNER_ACT_INACTIVE;
            o->oScuttlebugHasNoLootCoins          = TRUE;
        }
    } else if (o->oScuttlebugSpawnerIsDeactivated) {
        o->oScuttlebugSpawnerIsDeactivated = FALSE;
        o->oAction                         = SCUTTLEBUG_SPAWNER_ACT_ACTIVE;
    }
}
