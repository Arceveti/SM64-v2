// flying_bookend_switch.inc.c

struct BookSwitchPosition {
    s16 relPosX;
    s16 relPosY;
};

struct ObjectHitbox sFlyingBookendHitbox = {
    /* interactType:      */ INTERACT_HIT_FROM_BELOW,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 2,
    /* health:            */ 0,
    /* numLootCoins:      */ -1,
    /* radius:            */ 60,
    /* height:            */ 30,
    /* hurtboxRadius:     */ 40,
    /* hurtboxHeight:     */ 30,
};

struct BookSwitchPosition sBookSwitchPositions[] = {
    {  52, 150 },
    { 135,   3 },
    { -75,  78 },
};

struct ObjectHitbox sBookSwitchHitbox = {
    /* interactType:      */ INTERACT_BREAKABLE,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 99,
    /* numLootCoins:      */ 0,
    /* radius:            */ 20,
    /* height:            */ 30,
    /* hurtboxRadius:     */ 20,
    /* hurtboxHeight:     */ 30,
};

void flying_bookend_act_init(void) { // act 0
    if (obj_is_near_to_and_facing_mario(400.0f, 0x3000)) {
        cur_obj_play_sound_2(SOUND_OBJ_DEFAULT_DEATH);
        o->oAction = FLYING_BOOKEND_ACT_GROW;
        o->oBookendTargetPitch = o->oFaceAnglePitch + 0x7FFF;
        o->oBookendTargetRoll  = o->oFaceAngleRoll  - 0x7FFF;
        cur_obj_set_model(MODEL_BOOKEND_PART);
    }
}

void flying_bookend_act_grow(void) { // act 1
    if (obj_forward_vel_approach(3.0f, 1.0f)) {
        if (cur_obj_init_anim_and_check_if_end(FLYING_BOOKEND_ANIM_GROW)) {
            o->oAction = FLYING_BOOKEND_ACT_TURN_TOWARD_MARIO;
            o->oForwardVel = 0.0f;
        } else {
            o->oForwardVel = 3.0f;
            if (o->oTimer > 5) {
                obj_face_pitch_approach(o->oBookendTargetPitch, 0x7D0);
                if (o->oTimer >= 10) {
                    obj_face_roll_approach(o->oBookendTargetRoll, 0x7D0);
                    if (o->oTimer >= 20) approach_f32_ptr(&o->header.gfx.scale[0], 3.0f, 0.2f);
                }
            }
        }
    }

    cur_obj_move_using_fvel_and_gravity();
}

void flying_bookend_act_turn_toward_mario(void) { // act 2
    cur_obj_init_animation_with_sound(FLYING_BOOKEND_ANIM_BITE);
    cur_obj_update_floor_and_walls();

    if (o->oForwardVel == 0.0f) {
        obj_turn_pitch_toward_mario(120.0f, 0x3E8);
        o->oFaceAnglePitch = o->oMoveAnglePitch + 0x7FFF;
        cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x3E8);
        if (o->oTimer > 30) obj_compute_vel_from_move_pitch(50.0f);
    }

    cur_obj_move_standard(78);
}

void flying_bookend_act_fly_forward(void) { // act 3
    o->oDamageOrCoinValue = 1;
    o->oNumLootCoins      = 0;

    if (o->oTimer >= 4) {
        o->oAction = FLYING_BOOKEND_ACT_TURN_TOWARD_MARIO;
        o->oForwardVel = 50.0f;
    }

    obj_forward_vel_approach(50.0f, 2.0f);
    cur_obj_move_using_fvel_and_gravity();
}

void bhv_flying_bookend_loop(void) {
    if (!(o->activeFlags & ACTIVE_FLAG_IN_DIFFERENT_ROOM)) {
        o->oDeathSound = SOUND_OBJ_POUNDING1;
        cur_obj_scale(o->header.gfx.scale[0]);

        switch (o->oAction) {
            case FLYING_BOOKEND_ACT_INIT:              flying_bookend_act_init();              break;
            case FLYING_BOOKEND_ACT_GROW:              flying_bookend_act_grow();              break;
            case FLYING_BOOKEND_ACT_TURN_TOWARD_MARIO: flying_bookend_act_turn_toward_mario(); break;
            case FLYING_BOOKEND_ACT_FLY_FORWARD:       flying_bookend_act_fly_forward();       break;
        }

        obj_check_attacks(&sFlyingBookendHitbox, OBJ_ACT_PROJECTILE_HIT_MARIO);
        if (o->oAction == OBJ_ACT_PROJECTILE_HIT_MARIO || (o->oMoveFlags & (OBJ_MOVE_MASK_ON_GROUND | OBJ_MOVE_HIT_WALL))) {
            o->oNumLootCoins = 0;
            obj_die_if_health_non_positive();
        }

        o->oGraphYOffset = 30.0f * o->header.gfx.scale[0];
    }
}

void bhv_bookend_spawn_loop(void) {
    struct Object *bookendObj;

    if (!(o->activeFlags & ACTIVE_FLAG_IN_DIFFERENT_ROOM)) {
        if (o->oTimer > 40 && obj_is_near_to_and_facing_mario(600.0f, 0x2000)) {
            bookendObj = spawn_object(o, MODEL_BOOKEND, bhvFlyingBookend);
            if (bookendObj != NULL) {
                bookendObj->oAction = FLYING_BOOKEND_ACT_FLY_FORWARD;
                cur_obj_play_sound_2(SOUND_OBJ_DEFAULT_DEATH);
            }
            o->oTimer = 0;
        }
    }
}

void bookshelf_manager_act_spawn_switches(void) { // act 0
    s32 i;
    if (!(o->activeFlags & ACTIVE_FLAG_IN_DIFFERENT_ROOM)) {
        for (i = 0; i < 3; i++) spawn_object_relative(i, sBookSwitchPositions[i].relPosX, sBookSwitchPositions[i].relPosY, 0, o, MODEL_BOOKEND, bhvBookSwitch);
        o->oAction = BOOKSHELF_MANAGER_ACT_CHECK_ACTIVATE;
    }
}

void bookshelf_manager_act_check_activate(void) { // act 1
    if (!o->oBookSwitchManagerIsActive) {
        if (obj_is_near_to_and_facing_mario(500.0f, 0x3000)) o->oBookSwitchManagerIsActive = TRUE;
    } else if (o->oTimer > 60) {
        o->oAction = BOOKSHELF_MANAGER_ACT_ACTIVE;
        o->oBookSwitchManagerIsActive = FALSE;
    }
}

void bookshelf_manager_act_active(void) { // act 2
    if (!(o->activeFlags & ACTIVE_FLAG_IN_DIFFERENT_ROOM)) {
        if (o->oBookSwitchManagerNumCorrectChoices < 0) {
            if (o->oTimer > 30) {
                o->oBookSwitchManagerNumCorrectChoices = 0;
                o->oBookSwitchManagerIsActive = FALSE;
            } else if (o->oTimer > 10) {
                o->oBookSwitchManagerIsActive = TRUE;
            }
        } else {
            if (o->oBookSwitchManagerNumCorrectChoices >= 3) {
                if (o->oTimer > 100) {
                    o->parentObj = cur_obj_nearest_object_with_behavior(bhvHauntedBookshelf);
                    o->parentObj->oAction = HAUNTED_BOOKSHELF_ACT_RECEDE;
                    o->oPosX = o->parentObj->oPosX;
                    o->oAction = BOOKSHELF_MANAGER_ACT_RECEDE;
                } else if (o->oTimer == 30) {
                    play_puzzle_jingle();
                }
            } else {
                o->oTimer = 0;
            }
        }
    } else {
        o->oAction = BOOKSHELF_MANAGER_ACT_END;
    }
}

void bookshelf_manager_act_recede(void) { // act 3
    if (o->oTimer > 85) {
        o->oAction = BOOKSHELF_MANAGER_ACT_END;
    } else {
        o->oForwardVel = o->parentObj->oPosX - o->oPosX;
        o->oPosX       = o->parentObj->oPosX;
    }
}

void bookshelf_manager_act_end(void) { // act 4
    if (o->oBookSwitchManagerNumCorrectChoices >= 3) {
        // Remove when the bookshelf opens
        obj_mark_for_deletion(o);
    } else {
        // Reset
        o->oAction = BOOKSHELF_MANAGER_ACT_SPAWN_SWITCHES;
    }
}

void bhv_haunted_bookshelf_manager_loop(void) {
    switch (o->oAction) {
        case BOOKSHELF_MANAGER_ACT_SPAWN_SWITCHES: bookshelf_manager_act_spawn_switches(); break;
        case BOOKSHELF_MANAGER_ACT_ACTIVE:         bookshelf_manager_act_active();         break;
        case BOOKSHELF_MANAGER_ACT_CHECK_ACTIVATE: bookshelf_manager_act_check_activate(); break;
        case BOOKSHELF_MANAGER_ACT_RECEDE:         bookshelf_manager_act_recede();         break;
        case BOOKSHELF_MANAGER_ACT_END:            bookshelf_manager_act_end();            break;
    }
}

void bhv_book_switch_loop(void) {
    s32 attackType;
    struct Object *bookendObj;
    s16 rand01;
    s16 z;

    o->header.gfx.scale[0] = 2.0f;
    o->header.gfx.scale[1] = 0.9f;

    if (o->parentObj->oAction == BOOKSHELF_MANAGER_ACT_END) {
        // Remove switches when the bookshelf opens
        obj_mark_for_deletion(o);
    } else {
        attackType = obj_check_attacks(&sBookSwitchHitbox, o->oAction);
        if (o->parentObj->oBookSwitchManagerIsActive || o->oAction == BOOK_SWITCH_ACT_ACTIVE) {
            // Hardcoded collision distance?
            if (o->oDistanceToMario < 100.0f) {
                cur_obj_become_tangible();
            } else {
                cur_obj_become_intangible();
            }
            o->oAction = BOOK_SWITCH_ACT_ACTIVE;

            if (o->oBookSwitchDistFromHome == 0.0f) cur_obj_play_sound_2(SOUND_OBJ_DEFAULT_DEATH);

            if (approach_f32_ptr(&o->oBookSwitchDistFromHome, 50.0f, 20.0f)) {
                // Check for hits
                if (o->parentObj->oBookSwitchManagerNumCorrectChoices >= 0
                 && o->oTimer > 60
                 && (attackType == ATTACK_PUNCH
                  || attackType == ATTACK_KICK_OR_TRIP
                  || attackType == ATTACK_FROM_BELOW)) {
                    o->oAction = BOOK_SWITCH_ACT_PRESSED;
                }
            } else {
                o->oTimer = 0;
            }
        } else {
            cur_obj_become_intangible();
            if (approach_f32_ptr(&o->oBookSwitchDistFromHome, 0.0f, 20.0f) && o->oAction != BOOK_SWITCH_ACT_UNPRESSED) {
                if (o->parentObj->oBookSwitchManagerNumCorrectChoices == o->oBehParams2ndByte) {
                    // Correct choice

                    // Right answer sound
                    play_sound(SOUND_GENERAL2_RIGHT_ANSWER, gGlobalSoundSource);
                    // Increment choice counter
                    o->parentObj->oBookSwitchManagerNumCorrectChoices++;
                } else {
                    // Wrong choice

                    // Choose a side of the hallway to spawn the projectile book from
                    rand01 = random_u16() & 0x1;

                    // Wrong answer sound
                    play_sound(SOUND_MENU_CAMERA_BUZZ, gGlobalSoundSource);

                    // Get Mario's Z position for the projectile book
                    z = gMarioObject->oPosZ + 1.5f * gMarioStates[0].vel[2];
                    if (z > 0) z = 0;

                    // Spawn the projectile book
                    bookendObj = spawn_object_abs_with_rot(o, 0, MODEL_BOOKEND, bhvFlyingBookend,
                                                            (0x1FC * rand01 - 0x8CA), 890, z,
                                                            0x0, (0x8000 * rand01 + 0x4000), 0x0);
                    // Set its action
                    if (bookendObj != NULL) bookendObj->oAction = FLYING_BOOKEND_ACT_FLY_FORWARD;

                    // Reset the counter
                    o->parentObj->oBookSwitchManagerNumCorrectChoices = -1;
                }
                o->oAction = BOOK_SWITCH_ACT_UNPRESSED;
            }
        }
        o->oPosX += o->parentObj->oForwardVel;
        o->oPosZ = o->oHomeZ - o->oBookSwitchDistFromHome;
        cur_obj_push_mario_away_from_cylinder(70.0f, 70.0f);
    }
}
