// mushroom_1up.c.inc

void bhv_1up_interact(void) {
    if (obj_check_if_collided_with_object(o, gMarioObject)) {
#ifdef MUSHROOMS_HEAL
         gMarioState->healCounter = 31;
#endif
        play_sound(SOUND_GENERAL_COLLECT_1UP, gGlobalSoundSource);
        gMarioState->numLives++;
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
#if ENABLE_RUMBLE
        queue_rumble_data(5, 80);
#endif
    }
}

void bhv_1up_common_init(void) {
    o->oMoveAnglePitch = -0x4000;
    o->oGravity        = 3.0f;
    o->oFriction       = 1.0f;
    o->oBuoyancy       = 1.0f;
}

void bhv_1up_init(void) {
    bhv_1up_common_init();
    if (o->oBehParams2ndByte == MUSHROOM_BP_REQUIRES_BOWSER_1) {
        if (!(save_file_get_flags() & (SAVE_FLAG_HAVE_KEY_1 | SAVE_FLAG_UNLOCKED_BASEMENT_DOOR))) o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    } else if (o->oBehParams2ndByte == MUSHROOM_BP_REQUIRES_BOWSER_2) {
        if (!(save_file_get_flags() & (SAVE_FLAG_HAVE_KEY_2 | SAVE_FLAG_UNLOCKED_UPSTAIRS_DOOR))) o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }
}

void one_up_loop_in_air(void) {
    if (o->oTimer < 5) {
        o->oVelY = 40.0f;
    } else {
        o->oAngleVelPitch = -0x1000;
        o->oMoveAnglePitch += o->oAngleVelPitch;
        o->oVelY       =  coss(o->oMoveAnglePitch) * 30.0f + 2.0f;
        o->oForwardVel = -sins(o->oMoveAnglePitch) * 30.0f;
    }
}

void pole_1up_move_towards_mario(void) {
    f32 dx = gMarioObject->header.gfx.pos[0] - o->oPosX;
    f32 dy = gMarioObject->header.gfx.pos[1] + 120.0f - o->oPosY;
    f32 dz = gMarioObject->header.gfx.pos[2] - o->oPosZ;
    s16 targetPitch = atan2s(sqrtf(sqr(dx) + sqr(dz)), dy);

    obj_turn_toward_object(o, gMarioObject, 16, 0x1000);
    o->oMoveAnglePitch = approach_s16_symmetric(o->oMoveAnglePitch, targetPitch, 0x1000);
    o->oVelY           = sins(o->oMoveAnglePitch) * 30.0f;
    o->oForwardVel     = coss(o->oMoveAnglePitch) * 30.0f;
    bhv_1up_interact();
}

void one_up_move_away_from_mario(s16 stepResult) {
    o->oForwardVel = 8.0f;
    o->oMoveAngleYaw = o->oAngleToMario + 0x8000;
    bhv_1up_interact();
    if (stepResult & OBJ_COL_FLAG_HIT_WALL) o->oAction = MUSHROOM_ACT_DISAPPEARING;
    if (!is_point_within_radius_of_mario(o->oPosX, o->oPosY, o->oPosZ, 3000)) o->oAction = MUSHROOM_ACT_DISAPPEARING;
}

void bhv_1up_walking_loop(void) {
    object_step();

    switch (o->oAction) {
        case MUSHROOM_ACT_INIT:
            if (o->oTimer >= 18) spawn_object(o, MODEL_NONE, bhvSparkleSpawn);
            if (o->oTimer ==  0) play_sound(SOUND_GENERAL2_1UP_APPEAR, gGlobalSoundSource);
            one_up_loop_in_air();

            if (o->oTimer == 37) {
                cur_obj_become_tangible();
                o->oAction = MUSHROOM_ACT_MOVING;
                o->oForwardVel = 2.0f;
            }
            break;

        case MUSHROOM_ACT_MOVING:
            if (o->oTimer > 300) o->oAction = MUSHROOM_ACT_DISAPPEARING;
            bhv_1up_interact();
            break;

        case MUSHROOM_ACT_DISAPPEARING:
            obj_flicker_and_disappear(o, 30);
            bhv_1up_interact();
            break;
    }

    set_object_visibility(o, 3000);
}

void bhv_1up_running_away_loop(void) {
    s16 stepResult = object_step();
    switch (o->oAction) {
        case MUSHROOM_ACT_INIT:
            if (o->oTimer >= 18) spawn_object(o, MODEL_NONE, bhvSparkleSpawn);
            if (o->oTimer ==  0) play_sound(SOUND_GENERAL2_1UP_APPEAR, gGlobalSoundSource);
            one_up_loop_in_air();

            if (o->oTimer == 37) {
                cur_obj_become_tangible();
                o->oAction = MUSHROOM_ACT_MOVING;
                o->oForwardVel = 8.0f;
            }
            break;

        case MUSHROOM_ACT_MOVING:
            spawn_object(o, MODEL_NONE, bhvSparkleSpawn);
            one_up_move_away_from_mario(stepResult);
            break;

        case MUSHROOM_ACT_DISAPPEARING:
            obj_flicker_and_disappear(o, 30);
            bhv_1up_interact();
            break;
    }

    set_object_visibility(o, 3000);
}

void sliding_1up_move(void) {
    s16 stepResult = object_step();
    if (stepResult & OBJ_COL_FLAG_GROUNDED) {
        o->oForwardVel += 25.0f;
        o->oVelY = 0;
    } else {
        o->oForwardVel *= 0.98f;
    }

    if (o->oForwardVel > 40.0f) o->oForwardVel = 40.0f;
    if (!is_point_within_radius_of_mario(o->oPosX, o->oPosY, o->oPosZ, 5000)) o->oAction = MUSHROOM_ACT_DISAPPEARING;
}

void bhv_1up_sliding_loop(void) {
    switch (o->oAction) {
        case MUSHROOM_ACT_INIT:
            set_object_visibility(o, 3000);
            if (is_point_within_radius_of_mario(o->oPosX, o->oPosY, o->oPosZ, 1000)) o->oAction = MUSHROOM_ACT_MOVING;
            break;

        case MUSHROOM_ACT_MOVING:
            sliding_1up_move();
            break;

        case MUSHROOM_ACT_DISAPPEARING:
            obj_flicker_and_disappear(o, 30);
            bhv_1up_interact();
            break;
    }

    bhv_1up_interact();
    spawn_object(o, MODEL_NONE, bhvSparkleSpawn);
}

void bhv_1up_loop(void) {
    bhv_1up_interact();
    set_object_visibility(o, 3000);
}

void bhv_1up_jump_on_approach_loop(void) {
    s16 stepResult;

    switch (o->oAction) {
        case MUSHROOM_ACT_INIT:
            if (is_point_within_radius_of_mario(o->oPosX, o->oPosY, o->oPosZ, 1000)) {
                o->oVelY = 40.0f;
                o->oAction = MUSHROOM_ACT_MOVING;
            }
            break;

        case MUSHROOM_ACT_MOVING:
            stepResult = object_step();
            one_up_move_away_from_mario(stepResult);
            spawn_object(o, MODEL_NONE, bhvSparkleSpawn);
            break;

        case MUSHROOM_ACT_DISAPPEARING:
            stepResult = object_step();
            bhv_1up_interact();
            obj_flicker_and_disappear(o, 30);
            break;
    }

    set_object_visibility(o, 3000);
}

void bhv_1up_hidden_loop(void) {
    s16 stepResult;
    switch (o->oAction) {
        case MUSHROOM_ACT_INIT:
            o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
            if (o->o1UpHiddenTimesTriggered == o->oBehParams2ndByte) {
                o->oVelY   = 40.0f;
                o->oAction = MUSHROOM_ACT_LOOP_IN_AIR;
                o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
                play_sound(SOUND_GENERAL2_1UP_APPEAR, gGlobalSoundSource);
            }
            break;

        case MUSHROOM_ACT_MOVING:
            stepResult = object_step();
            one_up_move_away_from_mario(stepResult);
            spawn_object(o, MODEL_NONE, bhvSparkleSpawn);
            break;

        case MUSHROOM_ACT_DISAPPEARING:
            stepResult = object_step();
            bhv_1up_interact();
            obj_flicker_and_disappear(o, 30);
            break;

        case MUSHROOM_ACT_LOOP_IN_AIR:
            stepResult = object_step();
            if (o->oTimer >= 18) spawn_object(o, MODEL_NONE, bhvSparkleSpawn);
            one_up_loop_in_air();

            if (o->oTimer == 37) {
                cur_obj_become_tangible();
                o->oAction = MUSHROOM_ACT_MOVING;
                o->oForwardVel = 8.0f;
            }
            break;
    }
}

void bhv_1up_hidden_trigger_loop(void) {
    struct Object *nearestHidden1up;
    if (obj_check_if_collided_with_object(o, gMarioObject)) {
        nearestHidden1up = cur_obj_nearest_object_with_behavior(bhvHidden1up);
        if (nearestHidden1up != NULL) nearestHidden1up->o1UpHiddenTimesTriggered++;
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }
}

void bhv_1up_hidden_in_pole_loop(void) {
    UNUSED s16 stepResult;
    switch (o->oAction) {
        case MUSHROOM_ACT_INIT:
            o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
            if (o->o1UpHiddenTimesTriggered == o->oBehParams2ndByte) {
                o->oVelY = 40.0f;
                o->oAction = MUSHROOM_ACT_LOOP_IN_AIR;
                o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
                play_sound(SOUND_GENERAL2_1UP_APPEAR, gGlobalSoundSource);
            }
            break;

        case MUSHROOM_ACT_MOVING:
            pole_1up_move_towards_mario();
            stepResult = object_step();
            break;

        case MUSHROOM_ACT_LOOP_IN_AIR:
            stepResult = object_step();
            if (o->oTimer >= 18) spawn_object(o, MODEL_NONE, bhvSparkleSpawn);
            one_up_loop_in_air();

            if (o->oTimer == 37) {
                cur_obj_become_tangible();
                o->oAction = MUSHROOM_ACT_MOVING;
                o->oForwardVel = 10.0f;
            }
            break;
    }
}

void bhv_1up_hidden_in_pole_trigger_loop(void) {
    struct Object *nearestHidden1upInPole;
    if (obj_check_if_collided_with_object(o, gMarioObject)) {
        nearestHidden1upInPole = cur_obj_nearest_object_with_behavior(bhvHidden1upInPole);
        if (nearestHidden1upInPole != NULL) nearestHidden1upInPole->o1UpHiddenTimesTriggered++;
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }
}

void bhv_1up_hidden_in_pole_spawner_loop(void) {
    s8 i;
    if (is_point_within_radius_of_mario(o->oPosX, o->oPosY, o->oPosZ, 700)) {
        // For bhvHidden1upInPole, oBehParams2ndByte is used for how many frames is
        // required for Mario to activate it, instead of the Bowser requirement.
        spawn_object_relative(0x2, 0, 50, 0, o, MODEL_1UP, bhvHidden1upInPole);
        for (i = 0; i < 2; i++) spawn_object_relative(0x0, 0, i * -200, 0, o, MODEL_NONE, bhvHidden1upInPoleTrigger);
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }
}
