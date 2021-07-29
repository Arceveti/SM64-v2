// exclamation_box.c.inc

struct ObjectHitbox sExclamationBoxHitbox = {
    /* interactType:      */ INTERACT_BREAKABLE,
    /* downOffset:        */  5,
    /* damageOrCoinValue: */  0,
    /* health:            */  1,
    /* numLootCoins:      */  0,
    /* radius:            */ 40,
    /* height:            */ 30,
    /* hurtboxRadius:     */ 40,
    /* hurtboxHeight:     */ 30,
};

struct ExclamationBoxContents sExclamationBoxContents[] = { {  0, 0, 0, MODEL_MARIOS_WING_CAP,  bhvWingCap               },
                                                            {  1, 0, 0, MODEL_MARIOS_METAL_CAP, bhvMetalCap              },
                                                            {  2, 0, 0, MODEL_MARIOS_CAP,       bhvVanishCap             },
                                                            {  3, 0, 0, MODEL_KOOPA_SHELL,      bhvKoopaShell            },
                                                            {  4, 0, 0, MODEL_YELLOW_COIN,      bhvSingleCoinGetsSpawned },
                                                            {  5, 0, 0, MODEL_NONE,             bhvThreeCoinsSpawn       },
                                                            {  6, 0, 0, MODEL_NONE,             bhvTenCoinsSpawn         },
                                                            {  7, 0, 0, MODEL_1UP,              bhv1upWalking            },
                                                            {  8, 0, 0, MODEL_STAR,             bhvSpawnedStar           },
                                                            {  9, 0, 0, MODEL_1UP,              bhv1upRunningAway        },
                                                            { 10, 0, 1, MODEL_STAR,             bhvSpawnedStar           },
                                                            { 11, 0, 2, MODEL_STAR,             bhvSpawnedStar           },
                                                            { 12, 0, 3, MODEL_STAR,             bhvSpawnedStar           },
                                                            { 13, 0, 4, MODEL_STAR,             bhvSpawnedStar           },
                                                            { 14, 0, 5, MODEL_STAR,             bhvSpawnedStar           },
                                                            { 99, 0, 0, 0,                      NULL                     } };

void bhv_rotating_exclamation_box_loop(void) {
    if (o->parentObj->oAction != EXCLAMATION_BOX_ACT_OUTLINE) obj_mark_for_deletion(o);
}

void exclamation_box_act_init(void) {
    if (o->oBehParams2ndByte < 3) {
        o->oAnimState = o->oBehParams2ndByte;
        if ((save_file_get_flags() & sCapSaveFlags[o->oBehParams2ndByte])
            || ((o->oBehParams >> 24) & 0xFF) != 0) {
            o->oAction = EXCLAMATION_BOX_ACT_ACTIVE;
        } else {
            o->oAction = EXCLAMATION_BOX_ACT_OUTLINE;
        }
    } else {
        o->oAnimState = 3;
        o->oAction = EXCLAMATION_BOX_ACT_ACTIVE;
    }
}

void exclamation_box_act_outline(void) {
    cur_obj_become_intangible();
    if (o->oTimer == 0) {
        spawn_object(o, MODEL_EXCLAMATION_POINT, bhvRotatingExclamationMark);
        cur_obj_set_model(MODEL_EXCLAMATION_BOX_OUTLINE);
    }
    if ((save_file_get_flags() & sCapSaveFlags[o->oBehParams2ndByte])
        || ((o->oBehParams >> 24) & 0xFF) != 0) {
        o->oAction = EXCLAMATION_BOX_ACT_ACTIVE;
        cur_obj_set_model(MODEL_EXCLAMATION_BOX);
    }
}

void exclamation_box_act_active(void) {
    obj_set_hitbox(o, &sExclamationBoxHitbox);
    if (o->oTimer == 0) {
        cur_obj_unhide();
        cur_obj_become_tangible();
        o->oInteractStatus = INT_STATUS_NONE;
        o->oPosY = o->oHomeY;
        o->oGraphYOffset = 0.0f;
    }
    if (cur_obj_was_attacked_or_ground_pounded()) {
        cur_obj_become_intangible();
        o->oExclamationBoxScaleAngle = 0x4000;
        o->oVelY = 30.0f;
        o->oGravity = -8.0f;
        o->oFloorHeight = o->oPosY;
        o->oAction = EXCLAMATION_BOX_ACT_SCALING;
#if ENABLE_RUMBLE
        queue_rumble_data(5, 80);
#endif
    }
    load_object_collision_model();
}

void exclamation_box_act_scaling(void) {
    cur_obj_move_using_fvel_and_gravity();
    if (o->oVelY < 0.0f) {
        o->oVelY = 0.0f;
        o->oGravity = 0.0f;
    }
    o->oExclamationBoxVerticalScale   = ( sins(o->oExclamationBoxScaleAngle) + 1.0f) *  0.3f + 0.0f;
    o->oExclamationBoxHorizontalScale = (-sins(o->oExclamationBoxScaleAngle) + 1.0f) *  0.5f + 1.0f;
    o->oGraphYOffset                  = (-sins(o->oExclamationBoxScaleAngle) + 1.0f) * 26.0f;
    o->oExclamationBoxScaleAngle += 0x1000;
    o->header.gfx.scale[0] = o->oExclamationBoxHorizontalScale * 2.0f;
    o->header.gfx.scale[1] = o->oExclamationBoxVerticalScale   * 2.0f;
    o->header.gfx.scale[2] = o->oExclamationBoxHorizontalScale * 2.0f;
    if (o->oTimer == 7) o->oAction = EXCLAMATION_BOX_ACT_EXPLODE;
}

void exclamation_box_spawn_contents(struct ExclamationBoxContents *contentsList, u8 boxType) {
    struct Object *contentsObj = NULL;

    while (contentsList->id != 99) {
        if (boxType == contentsList->id) {
            contentsObj = spawn_object(o, contentsList->model, contentsList->behavior);
            contentsObj->oVelY = 20.0f;
            contentsObj->oForwardVel = 3.0f;
            contentsObj->oMoveAngleYaw = gMarioObject->oMoveAngleYaw;
            o->oBehParams |= contentsList->behParams << 24;
            if (contentsList->model == 122) o->oFlags |= OBJ_FLAG_PERSISTENT_RESPAWN;
            break;
        }
        contentsList++;
    }
}

void exclamation_box_act_explode(void) {
    exclamation_box_spawn_contents(sExclamationBoxContents, o->oBehParams2ndByte);
    spawn_mist_particles_variable(0, 0, 46.0f);
    spawn_triangle_break_particles(20, MODEL_CARTOON_STAR, 0.3f, o->oAnimState);
    create_sound_spawner(SOUND_GENERAL_BREAK_BOX);
#ifdef KOOPA_SHELL_BOXES_RESPAWN
    if (o->oBehParams2ndByte < 4) {
#else
    if (o->oBehParams2ndByte < 3) {
#endif
        o->oAction = EXCLAMATION_BOX_ACT_WAIT_FOR_RESPAWN;
        cur_obj_hide();
    } else {
        obj_mark_for_deletion(o);
    }
}

void exclamation_box_act_wait_for_respawn(void) {
    if (o->oTimer > 300) o->oAction = EXCLAMATION_BOX_ACT_ACTIVE;
}

void (*sExclamationBoxActions[])(void) = { exclamation_box_act_init,    exclamation_box_act_outline,
                                           exclamation_box_act_active,  exclamation_box_act_scaling,
                                           exclamation_box_act_explode, exclamation_box_act_wait_for_respawn };

void bhv_exclamation_box_loop(void) {
    cur_obj_scale(2.0f);
    cur_obj_call_action_function(sExclamationBoxActions);
}
