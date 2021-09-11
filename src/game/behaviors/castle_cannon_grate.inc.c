// castle_cannon_grate.inc.c

void bhv_castle_cannon_grate_init(void) {
#ifdef DEBUG_LEVEL_SELECT
    obj_mark_for_deletion(o);
#else
    if (save_file_get_total_star_count((gCurrSaveFileNum - 1), (COURSE_MIN - 1), (COURSE_MAX - 1)) >= 120) obj_mark_for_deletion(o);
#endif
}
