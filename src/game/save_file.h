#ifndef SAVE_FILE_H
#define SAVE_FILE_H

#include <PR/ultratypes.h>

#include "types.h"
#include "area.h"
#ifdef PUPPYCAM
#include "puppycam2.h"
#endif

#include "course_table.h"

#if defined(SRAM)
    #define EEPROM_SIZE 0x8000
#elif defined(EEP16K)
    #define EEPROM_SIZE 0x800
#else
    #define EEPROM_SIZE 0x200
#endif

#define NUM_SAVE_FILES 4

struct SaveBlockSignature
{
    u16 magic;
    u16 chksum;
};

struct SaveFile
{
    // Location of lost cap.
    u8 capLevel;
    u8 capArea;
#ifdef SAVE_NUM_LIVES
    s8 numLives;
    u8 pad[5];
#else
    // Note: the coordinates get set, but are never actually used, since the
    // cap can always be found in a fixed spot within the course
    Vec3s capPos;
#endif

    u32 flags;

    // Star flags for each course.
    // The most significant bit of the byte *following* each course is set if the
    // cannon is open.
    u8 courseStars[COURSE_COUNT];

    u8 courseCoinScores[COURSE_STAGES_COUNT];
    struct SaveBlockSignature signature;
};

enum SaveFileIndex {
    SAVE_FILE_A,
    SAVE_FILE_B,
    SAVE_FILE_C,
    SAVE_FILE_D
};

struct MainMenuSaveData
{
    // Each save file has a 2 bit "age" for each course. The higher this value,
    // the older the high score is. This is used for tie-breaking when displaying
    // on the high score screen.
    u32 coinScoreAges[NUM_SAVE_FILES];
    u8 soundMode: 2;
#ifdef REONU_CAM_3
    u8 cameraSpeedSetting: 3;
#endif
#ifdef WIDE
    u8 wideMode: 1;
#endif
#ifdef VERSION_EU
    u8 language: 2;
#define SUBTRAHEND 8
#else
#define SUBTRAHEND 6
#endif
#ifdef PUPPYCAM
    u8 firstBoot;
#endif
    // Pad to match the EEPROM size of 0x200 (10 bytes on JP/US, 8 bytes on EU)
    //u8 filler[EEPROM_SIZE / 2 - SUBTRAHEND - NUM_SAVE_FILES * (4 + sizeof(struct SaveFile))];

#ifdef PUPPYCAM
    struct gPuppyOptions saveOptions;
#endif
    struct SaveBlockSignature signature;
};

struct SaveBuffer
{
    // Each of the four save files has two copies. If one is bad, the other is used as a backup.
    struct SaveFile files[NUM_SAVE_FILES][2];
    // The main menu data has two copies. If one is bad, the other is used as a backup.
    struct MainMenuSaveData menuData[1]; //!?
};

#ifdef PUPPYCAM
extern void puppycam_set_save(void);
extern void puppycam_get_save(void);
extern void puppycam_check_save(void);
#endif

STATIC_ASSERT(sizeof(struct SaveBuffer) <= EEPROM_SIZE, "ERROR: Save struct too big for specified save type");

extern u8    gLastCompletedCourseNum;
extern u8    gLastCompletedStarNum;
extern Bool8 sUnusedGotGlobalCoinHiScore;
extern Bool8 gGotFileCoinHiScore;
extern u8    gCurrCourseStarFlags;
extern Bool8 gSpecialTripleJump;
extern s8    gLevelToCourseNumTable[];

// game progress flags
#define SAVE_FLAG_FILE_EXISTS            /* 0x00000001 */ (1 <<  0)
#define SAVE_FLAG_HAVE_WING_CAP          /* 0x00000002 */ (1 <<  1)
#define SAVE_FLAG_HAVE_METAL_CAP         /* 0x00000004 */ (1 <<  2)
#define SAVE_FLAG_HAVE_VANISH_CAP        /* 0x00000008 */ (1 <<  3)
#define SAVE_FLAG_HAVE_KEY_1             /* 0x00000010 */ (1 <<  4)
#define SAVE_FLAG_HAVE_KEY_2             /* 0x00000020 */ (1 <<  5)
#define SAVE_FLAG_UNLOCKED_BASEMENT_DOOR /* 0x00000040 */ (1 <<  6)
#define SAVE_FLAG_UNLOCKED_UPSTAIRS_DOOR /* 0x00000080 */ (1 <<  7)
#define SAVE_FLAG_DDD_MOVED_BACK         /* 0x00000100 */ (1 <<  8)
#define SAVE_FLAG_MOAT_DRAINED           /* 0x00000200 */ (1 <<  9)
#define SAVE_FLAG_UNLOCKED_PSS_DOOR      /* 0x00000400 */ (1 << 10)
#define SAVE_FLAG_UNLOCKED_WF_DOOR       /* 0x00000800 */ (1 << 11)
#define SAVE_FLAG_UNLOCKED_CCM_DOOR      /* 0x00001000 */ (1 << 12)
#define SAVE_FLAG_UNLOCKED_JRB_DOOR      /* 0x00002000 */ (1 << 13)
#define SAVE_FLAG_UNLOCKED_BITDW_DOOR    /* 0x00004000 */ (1 << 14)
#define SAVE_FLAG_UNLOCKED_BITFS_DOOR    /* 0x00008000 */ (1 << 15)
#define SAVE_FLAG_CAP_ON_GROUND          /* 0x00010000 */ (1 << 16)
#define SAVE_FLAG_CAP_ON_KLEPTO          /* 0x00020000 */ (1 << 17)
#define SAVE_FLAG_CAP_ON_UKIKI           /* 0x00040000 */ (1 << 18)
#define SAVE_FLAG_CAP_ON_MR_BLIZZARD     /* 0x00080000 */ (1 << 19)
#define SAVE_FLAG_UNLOCKED_50_STAR_DOOR  /* 0x00100000 */ (1 << 20)
#define SAVE_FLAG_COLLECTED_TOAD_STAR_1  /* 0x01000000 */ (1 << 24)
#define SAVE_FLAG_COLLECTED_TOAD_STAR_2  /* 0x02000000 */ (1 << 25)
#define SAVE_FLAG_COLLECTED_TOAD_STAR_3  /* 0x04000000 */ (1 << 26)
#define SAVE_FLAG_COLLECTED_MIPS_STAR_1  /* 0x08000000 */ (1 << 27)
#define SAVE_FLAG_COLLECTED_MIPS_STAR_2  /* 0x10000000 */ (1 << 28)

#define SAVE_FLAG_TO_STAR_FLAG(cmd) (((cmd) >> 24) & 0x7F)
#define STAR_FLAG_TO_SAVE_FLAG(cmd)  ((cmd) << 24)

// Variable for setting a warp checkpoint.

// possibly a WarpDest struct where arg is a union. TODO: Check?
struct WarpCheckpoint {
    /*0x00*/ u8 actNum;
    /*0x01*/ u8 courseNum;
    /*0x02*/ u8 levelID;
    /*0x03*/ u8 areaNum;
    /*0x04*/ u8 warpNode;
};

extern struct WarpCheckpoint gWarpCheckpoint;

extern Bool8 gMainMenuDataModified;
extern Bool8 gSaveFileModified;

void   save_file_do_save(s32 fileIndex);
void   save_file_erase(  s32 fileIndex);
void   save_file_copy(s32 srcFileIndex, s32 destFileIndex);
void   save_file_load_all(void);
void   save_file_reload(  void);
void   save_file_collect_star_or_key(s16 coinScore, s16 starIndex);
s32    save_file_exists(s32 fileIndex);
u32    save_file_get_max_coin_score(                  s32 courseIndex);
s32    save_file_get_course_star_count(s32 fileIndex, s32 courseIndex);
s32    save_file_get_total_star_count( s32 fileIndex, s32 minCourse, s32 maxCourse);
void   save_file_set_flags(  u32 flags);
void   save_file_clear_flags(u32 flags);
u32    save_file_get_flags(void);
u32    save_file_get_star_flags(       s32 fileIndex, s32 courseIndex);
void   save_file_set_star_flags(       s32 fileIndex, s32 courseIndex, u32 starFlags);
s32    save_file_get_course_coin_score(s32 fileIndex, s32 courseIndex);
s32    save_file_is_cannon_unlocked( void);
void   save_file_set_cannon_unlocked(void);
void   save_file_set_cap_pos(s16 x, s16 y, s16 z);
Bool32 save_file_get_cap_pos(Vec3s capPos);
#ifdef SAVE_NUM_LIVES
s8     save_file_get_num_lives(void);
void   save_file_set_num_lives(s8 numLives);
#endif
void   save_file_set_sound_mode(u16 mode);
u16    save_file_get_sound_mode(void);
#ifdef REONU_CAM_3
u8     save_file_get_camera_speed(void);
void   save_file_set_camera_speed(u8 speed);
#endif
#ifdef WIDE
void   save_file_set_widescreen_mode(u8 mode);
u8     save_file_get_widescreen_mode(void);
#endif
void   save_file_move_cap_to_default_location(void);

void   disable_warp_checkpoint(void);
void   check_if_should_set_warp_checkpoint(struct WarpNode *warpNode);
s32    check_warp_checkpoint(              struct WarpNode *warpNode);

#ifdef VERSION_EU
enum EuLanguages {
    LANGUAGE_ENGLISH,
    LANGUAGE_FRENCH,
    LANGUAGE_GERMAN
};

void eu_set_language(u16 language);
u16  eu_get_language(void);
#endif

#endif // SAVE_FILE_H
