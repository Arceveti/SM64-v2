// sound_birds.inc.c

void bhv_birds_sound_loop(void) {
    if (gCamera->mode == CAMERA_MODE_BEHIND_MARIO) return;

    switch (o->oBehParams2ndByte) {
        case SOUND_BIRDS_BP_OBJ2_BIRD_CHIRP1:     cur_obj_play_sound_1(SOUND_OBJ2_BIRD_CHIRP1    ); break;
        case SOUND_BIRDS_BP_GENERAL2_BIRD_CHIRP2: cur_obj_play_sound_1(SOUND_GENERAL2_BIRD_CHIRP2); break;
        case SOUND_BIRDS_BP_OBJ_BIRD_CHIRP3:      cur_obj_play_sound_1(SOUND_OBJ_BIRD_CHIRP3     ); break;
    }
}
