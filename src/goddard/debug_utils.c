#include <PR/ultratypes.h>
#include <stdarg.h>

#include "debug_utils.h"
#include "gd_types.h"
#include "macros.h"
#include "renderer.h"
#include "draw_objects.h"

// data
static s32 sNumActiveMemTrackers = 0;   // @ 801A82A0
static u32 sPrimarySeed = 0x12345678;   // @ 801A82A4
static u32 sSecondarySeed = 0x58374895; // @ 801A82A8

// bss
static struct MemTracker sMemTrackers[GD_NUM_MEM_TRACKERS]; // @ 801BA720
static struct MemTracker *sActiveMemTrackers[16];           // @ 801BA920

/*
 * Memtrackers
 *
 * These are used to monitor how much heap memory is being used by certain
 * operations.
 * To create a memtracker, call new_memtracker with a unique name.
 * To record the amount of memory used by a certain allocation, call
 * start_memtracker before allocating memory, and call stop_memtracker after
 * allocating memory.
 * The memtracker keeps track of the memory allocated between a single
 * start_memtracker/stop_memtracker pair as well as the total memory allocated
 * of all start_memtracker/stop_memtracker pairs.
 */

/**
 * Creates a new memtracker with the specified name
 */
struct MemTracker *new_memtracker(const char *name) {
    s32 i;
    struct MemTracker *tracker = NULL;

    for (i = 0; i < ARRAY_COUNT(sMemTrackers); i++) {
        if (sMemTrackers[i].name == NULL) {
            sMemTrackers[i].name = name;
            tracker = &sMemTrackers[i];
            break;
        }
    }

    if (tracker != NULL) {
        tracker->total = 0.0f;
    }

    return tracker;
}

/**
 * Returns the memtracker with the specified name, or NULL if it
 * does not exist
 */
struct MemTracker *get_memtracker(const char *name) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sMemTrackers); i++) {
        if (sMemTrackers[i].name != NULL) {
            if (gd_str_not_equal(sMemTrackers[i].name, name) == FALSE) {
                return &sMemTrackers[i];
            }
        }
    }

    return NULL;
}

/**
 * Records the amount of heap usage before allocating memory.
 */
struct MemTracker *start_memtracker(const char *name) {
    struct MemTracker *tracker = get_memtracker(name);

    // Create one if it doesn't exist
    if (tracker == NULL) {
        tracker = new_memtracker(name);
        if (tracker == NULL) {
            // fatal_printf("Unable to make memtracker '%s'", name);
            gd_exit();
        }
    }

    tracker->begin = (f32) get_alloc_mem_amt();
    if (sNumActiveMemTrackers >= ARRAY_COUNT(sActiveMemTrackers)) {
        // fatal_printf("too many memtracker calls");
        gd_exit();
    }

    sActiveMemTrackers[sNumActiveMemTrackers++] = tracker;

    return tracker;
}

/**
 * Records the amount of heap usage after allocating memory.
 */
u32 stop_memtracker(const char *name) {
    struct MemTracker *tracker;

    if (sNumActiveMemTrackers-- < 0) {
        // fatal_printf("bad mem tracker count");
        gd_exit();
    }

    tracker = get_memtracker(name);
    if (tracker == NULL) {
        // fatal_printf("memtracker '%s' not found", name);
        gd_exit();
    }

    tracker->end = get_alloc_mem_amt();
    tracker->total += (tracker->end - tracker->begin);

    return (u32) tracker->total;
}

/**
 * Destroys all memtrackers
 */
void remove_all_memtrackers(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sMemTrackers); i++) {
        sMemTrackers[i].name = NULL;
        sMemTrackers[i].begin = 0.0f;
        sMemTrackers[i].end = 0.0f;
        sMemTrackers[i].total = 0.0f;
    }

    sNumActiveMemTrackers = 0;
}

/**
 * Returns a random floating point number between 0 and 1 (inclusive)
 * TODO: figure out type of rng generator?
 */
f32 gd_rand_float(void) {
    u32 temp;
    u32 i;
    f32 val;

    for (i = 0; i < 4; i++) {
        if (sPrimarySeed & 0x80000000) {
            sPrimarySeed = sPrimarySeed << 1 | 1;
        } else {
            sPrimarySeed <<= 1;
        }
    }
    sPrimarySeed += 4;

    /* Seed Switch */
    if ((sPrimarySeed ^= gd_get_ostime()) & 1) {
        temp = sPrimarySeed;
        sPrimarySeed = sSecondarySeed;
        sSecondarySeed = temp;
    }

    val = (sPrimarySeed & 0xFFFF) / 65535.0f;

    return val;
}

/* 23C468 -> 23C4AC; orig name: func_8018DC98 */
void gd_strcpy(char *dst, const char *src) {
    while ((*dst++ = *src++)) {
        ;
    }
}

/* 23C5A8 -> 23C5FC; orig name: func_8018DDD8 */
u32 gd_strlen(const char *str) {
    u32 len = 0;

    while (*str++) {
        len++;
    }

    return len;
}

/* 23C5FC -> 23C680; orig name: func_8018DE2C */
char *gd_strcat(char *dst, const char *src) {
    while (*dst++) {
        ;
    }

    if (*src) {
        dst--;
        while ((*dst++ = *src++)) {
            ;
        }
    }

    return --dst;
}

/* 23C67C -> 23C728; orig name: func_8018DEB0 */
/* Returns a bool, not the position of the mismatch */
s32 gd_str_not_equal(const char *str1, const char *str2) {
    while (*str1 && *str2) {
        if (*str1++ != *str2++) {
            return TRUE;
        }
    }

    return *str1 != '\0' || *str2 != '\0';
}
