// castle_cannon_grate.inc.c

void bhv_castle_cannon_grate_init(void) {
#ifdef DEBUG_LEVEL_SELECT
    o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
#else
    if (save_file_get_total_star_count(gCurrSaveFileNum - 1, COURSE_MIN - 1, COURSE_MAX - 1) >= 120) {
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }
#endif
}
