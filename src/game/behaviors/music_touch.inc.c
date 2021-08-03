// music_touch.c.inc

void bhv_play_music_track_when_touched_loop(void) {
    if (o->oAction == MUSIC_TOUCH_ACT_PLAY_SOUND && o->oDistanceToMario < 200.0f) {
        play_puzzle_jingle();
        o->oAction = MUSIC_TOUCH_ACT_DONE;
    }
}
