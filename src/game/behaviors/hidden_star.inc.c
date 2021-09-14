// hidden_star.c.inc

void bhv_hidden_star_init(void) {
    struct Object *starObj;
    s16 remainingTriggers = count_objects_with_behavior(bhvHiddenStarTrigger);
    if (remainingTriggers == 0) {
        starObj             = spawn_object_abs_with_rot(o, 0, MODEL_STAR, bhvStar, o->oPosX, o->oPosY, o->oPosZ, 0x0, 0x0, 0x0);
        starObj->oBehParams = o->oBehParams;
        obj_mark_for_deletion(o);
    }
    o->oHiddenStarTriggerCounter = (5 - remainingTriggers);
}

void bhv_hidden_star_loop(void) {
#ifdef HUD_SECRETS
    gSecretsCollected = o->oHiddenStarTriggerCounter;
#endif
    switch (o->oAction) {
        case HIDDEN_STAR_ACT_INACTIVE:
            if (o->oHiddenStarTriggerCounter == 5) o->oAction = HIDDEN_STAR_ACT_ACTIVE;
            break;
        case HIDDEN_STAR_ACT_ACTIVE:
            if (o->oTimer > 2) {
                spawn_red_coin_cutscene_star(o->oPosX, o->oPosY, o->oPosZ);
                spawn_mist_particles();
                obj_mark_for_deletion(o);
            }
            break;
    }
}

/* TODO: this is likely not a checkpoint but a Secret */
void bhv_hidden_star_trigger_loop(void) {
    struct Object *hiddenStar;
    if (obj_check_if_collided_with_object(o, gMarioObject)) {
        hiddenStar = cur_obj_nearest_object_with_behavior(bhvHiddenStar);
        if (hiddenStar != NULL) {
            hiddenStar->oHiddenStarTriggerCounter++;
            if (hiddenStar->oHiddenStarTriggerCounter != 5) spawn_orange_number(hiddenStar->oHiddenStarTriggerCounter, 0, 0, 0);
#ifdef VERSION_JP
            play_sound(SOUND_MENU_STAR_SOUND, gGlobalSoundSource);
#else
            play_sound(SOUND_MENU_COLLECT_SECRET + (((u8) hiddenStar->oHiddenStarTriggerCounter - 1) << 16), gGlobalSoundSource);
#endif
        }
        obj_mark_for_deletion(o);
    }
}

void bhv_bowser_course_red_coin_star_loop(void) {
    gRedCoinsCollected = o->oHiddenStarTriggerCounter;
    switch (o->oAction) {
        case HIDDEN_STAR_ACT_INACTIVE:
            if (o->oHiddenStarTriggerCounter == 8) o->oAction = HIDDEN_STAR_ACT_ACTIVE;
            break;
        case HIDDEN_STAR_ACT_ACTIVE:
            if (o->oTimer > 2) {
                spawn_no_exit_star(o->oPosX, o->oPosY, o->oPosZ);
                spawn_mist_particles();
                obj_mark_for_deletion(o);
            }
            break;
    }
}
