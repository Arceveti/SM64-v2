#ifndef GD_DEBUGGING_UTILS_H
#define GD_DEBUGGING_UTILS_H

#include <PR/ultratypes.h>

#include "gd_types.h"
#include "macros.h"

#define GD_NUM_MEM_TRACKERS 32

// structs
struct MemTracker {
    /* 0x00 */ const char *name;  // name (used as an identifier)
    /* 0x04 */ f32 begin;         // used heap space (in bytes) before allocating memory
    /* 0x08 */ f32 end;           // used heap space (in bytes) after allocating memory
    /* 0x0C */ f32 total;         // total memory (in bytes) allocated between all start_memtracker/stop_memtracker calls
};

// functions
extern struct MemTracker *start_memtracker(const char *);
extern u32 stop_memtracker(const char *);
extern void remove_all_memtrackers(void);
extern f32 gd_rand_float(void);
extern void gd_strcpy(char *, const char *);
extern u32 gd_strlen(const char *);
extern char *gd_strcat(char *, const char *);
extern s32 gd_str_not_equal(const char *, const char *);

#endif // GD_DEBUGGING_UTILS_H
