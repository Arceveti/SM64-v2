#include <ultra64.h>
#include "sm64.h"
#include "behavior_data.h"
#include "model_ids.h"
#include "seq_ids.h"
#include "dialog_ids.h"
#include "segment_symbols.h"
#include "level_commands.h"

#include "game/level_update.h"

#include "levels/scripts.h"

#include "actors/common1.h"

#include "make_const_nonconst.h"
#include "levels/bitdw/header.h"

static const LevelScript script_func_local_bitdw_platforms[] = {
    OBJECT(/*model*/ MODEL_BITDW_SQUARE_PLATFORM,   /*pos*/ -1966, -3154,  3586, /*angle*/ 0,  0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvSquarishPathMoving),
    OBJECT(/*model*/ MODEL_BITDW_SQUARE_PLATFORM,   /*pos*/ -1352, -3154,  4200, /*angle*/ 0,  0, 0, /*behParam*/ 0x00020000, /*beh*/ bhvSquarishPathMoving),
    OBJECT(/*model*/ MODEL_BITDW_SQUARE_PLATFORM,   /*pos*/ -2963,  1017, -2464, /*angle*/ 0,  0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvSquarishPathMoving),
    OBJECT(/*model*/ MODEL_BITDW_SQUARE_PLATFORM,   /*pos*/ -2349,  1017, -1849, /*angle*/ 0,  0, 0, /*behParam*/ 0x00020000, /*beh*/ bhvSquarishPathMoving),
    OBJECT(/*model*/ MODEL_BITDW_SQUARE_PLATFORM,   /*pos*/ -2349,  1017, -1235, /*angle*/ 0,  0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvSquarishPathMoving),
    OBJECT(/*model*/ MODEL_BITDW_SQUARE_PLATFORM,   /*pos*/ -1735,  1017,  -621, /*angle*/ 0,  0, 0, /*behParam*/ 0x00020000, /*beh*/ bhvSquarishPathMoving),
    OBJECT(/*model*/ MODEL_BITDW_SEESAW_PLATFORM,   /*pos*/  1491,  1273,   512, /*angle*/ 0, 90, 0, /*behParam*/ 0x00000000, /*beh*/ bhvSeesawPlatform),
    OBJECT(/*model*/ MODEL_BITDW_SEESAW_PLATFORM,   /*pos*/  -147,   894,   512, /*angle*/ 0, 90, 0, /*behParam*/ 0x00000000, /*beh*/ bhvSeesawPlatform),
    OBJECT(/*model*/ MODEL_BITDW_SLIDING_PLATFORM,  /*pos*/ -5728,   819, -2151, /*angle*/ 0,  0, 0, /*behParam*/ 0x03CE0000, /*beh*/ bhvSlidingPlatform2),
    OBJECT(/*model*/ MODEL_BITDW_FERRIS_WHEEL_AXLE, /*pos*/  -205, -1924,  3381, /*angle*/ 0,  0, 0, /*behParam*/ 0x00010000, /*beh*/ bhvFerrisWheelAxle),
    OBJECT(/*model*/ MODEL_BITDW_STAIRCASE,         /*pos*/  5279,  1741,     0, /*angle*/ 0,  0, 0, /*behParam*/ 0x00010000, /*beh*/ bhvAnimatesOnFloorSwitchPress),
    OBJECT(/*model*/ MODEL_PURPLE_SWITCH,           /*pos*/  3922,  1741,     0, /*angle*/ 0,  0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvFloorSwitchAnimatesObject),
    RETURN(),
};

static const LevelScript script_func_local_bitdw_flamethrowers[] = {
    OBJECT(/*model*/ MODEL_NONE, /*pos*/ -3092, -2795, 2842, /*angle*/ 0, 0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvFlamethrower),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/  2463, -2386, 2844, /*angle*/ 0, 0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvFlamethrower),
    RETURN(),
};

static const LevelScript script_func_local_bitdw_stars[] = {
    OBJECT(/*model*/ MODEL_NONE, /*pos*/  7180,  3000,    0, /*angle*/ 0, 0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvBowserCourseRedCoinStar),
    RETURN(),
};

const LevelScript level_bitdw_entry[] = {
    INIT_LEVEL(),
    LOAD_YAY0(        /*seg*/ 0x07,  _bitdw_segment_7SegmentRomStart,  _bitdw_segment_7SegmentRomEnd),
    LOAD_YAY0(        /*seg*/ 0x0A, _bidw_skybox_yay0SegmentRomStart, _bidw_skybox_yay0SegmentRomEnd),
    LOAD_YAY0_TEXTURE(/*seg*/ 0x09,         _sky_yay0SegmentRomStart,         _sky_yay0SegmentRomEnd),
    LOAD_YAY0(        /*seg*/ 0x05,     _group11_yay0SegmentRomStart,     _group11_yay0SegmentRomEnd),
    LOAD_RAW(         /*seg*/ 0x0C,      _group11_geoSegmentRomStart,      _group11_geoSegmentRomEnd),
    LOAD_YAY0(        /*seg*/ 0x06,     _group17_yay0SegmentRomStart,     _group17_yay0SegmentRomEnd),
    LOAD_RAW(         /*seg*/ 0x0D,      _group17_geoSegmentRomStart,      _group17_geoSegmentRomEnd),
    LOAD_YAY0(        /*seg*/ 0x08,     _common0_yay0SegmentRomStart,     _common0_yay0SegmentRomEnd),
    LOAD_RAW(         /*seg*/ 0x0F,      _common0_geoSegmentRomStart,      _common0_geoSegmentRomEnd),
    ALLOC_LEVEL_POOL(),
    MARIO(/*model*/ MODEL_MARIO, /*behParam*/ 0x00000001, /*beh*/ bhvMario),
    JUMP_LINK(script_func_global_12),
    JUMP_LINK(script_func_global_18),
    JUMP_LINK(script_func_global_1 ),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_03,       geo_bitdw_0003C0),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_04,       geo_bitdw_0003D8),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_05,       geo_bitdw_0003F0),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_06,       geo_bitdw_000408),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_07,       geo_bitdw_000420),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_08,       geo_bitdw_000438),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_09,       geo_bitdw_000450),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_0A,       geo_bitdw_000468),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_0B,       geo_bitdw_000480),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_0C,       geo_bitdw_000498),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_0D,       geo_bitdw_0004B0),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_0E,       geo_bitdw_quartz_crystal),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_0F,       geo_bitdw_0004E0),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_10,       geo_bitdw_0004F8),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_11,       geo_bitdw_000510),
    LOAD_MODEL_FROM_GEO(MODEL_BITDW_WARP_PIPE,         warp_pipe_geo),
    LOAD_MODEL_FROM_GEO(MODEL_BITDW_SQUARE_PLATFORM,   geo_bitdw_moving_pyramid),
    LOAD_MODEL_FROM_GEO(MODEL_BITDW_SEESAW_PLATFORM,   geo_bitdw_seesaw_platform),
    LOAD_MODEL_FROM_GEO(MODEL_BITDW_SLIDING_PLATFORM,  geo_bitdw_sliding_platform),
    LOAD_MODEL_FROM_GEO(MODEL_BITDW_FERRIS_WHEEL_AXLE, geo_bitdw_ferris_wheel_axle),
    LOAD_MODEL_FROM_GEO(MODEL_BITDW_BLUE_PLATFORM,     geo_bitdw_ferris_platform),
    LOAD_MODEL_FROM_GEO(MODEL_BITDW_STAIRCASE_FRAME4,  geo_bitdw_collapsing_stairs_1),
    LOAD_MODEL_FROM_GEO(MODEL_BITDW_STAIRCASE_FRAME3,  geo_bitdw_collapsing_stairs_2),
    LOAD_MODEL_FROM_GEO(MODEL_BITDW_STAIRCASE_FRAME2,  geo_bitdw_collapsing_stairs_3),
    LOAD_MODEL_FROM_GEO(MODEL_BITDW_STAIRCASE_FRAME1,  geo_bitdw_collapsing_stairs_4),
    LOAD_MODEL_FROM_GEO(MODEL_BITDW_STAIRCASE,         geo_bitdw_collapsing_stairs_5),

    AREA(/*index*/ 1, geo_bitdw_area_1),
        OBJECT(/*model*/ MODEL_NONE,            /*pos*/ -7444, -2154, 3886, /*angle*/ 0, 90, 0, /*behParam*/ 0x000A0000, /*beh*/ bhvAirborneWarp),
        OBJECT(/*model*/ MODEL_BITDW_WARP_PIPE, /*pos*/  6816,  2860,    0, /*angle*/ 0, 0, 0,  /*behParam*/ 0x000B0000, /*beh*/ bhvWarpPipe),
        OBJECT(/*model*/ MODEL_NONE,            /*pos*/  5910,  3500,    0, /*angle*/ 0, 90, 0, /*behParam*/ 0x000C0000, /*beh*/ bhvDeathWarp),
        WARP_NODE(/*id*/ 0x0A, /*destLevel*/ LEVEL_BITDW,    /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
        WARP_NODE(/*id*/ 0x0B, /*destLevel*/ LEVEL_BOWSER_1, /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
        WARP_NODE(/*id*/ 0x0C, /*destLevel*/ LEVEL_BITDW,    /*destArea*/ 0x01, /*destNode*/ 0x0C, /*flags*/ WARP_NO_CHECKPOINT),
        WARP_NODE(/*id*/ 0xF1, /*destLevel*/ LEVEL_CASTLE,   /*destArea*/ 0x01, /*destNode*/ 0x25, /*flags*/ WARP_NO_CHECKPOINT),
        JUMP_LINK(script_func_local_bitdw_platforms),
        JUMP_LINK(script_func_local_bitdw_flamethrowers),
        JUMP_LINK(script_func_local_bitdw_stars),
        TERRAIN(/*terrainData*/ bitdw_seg7_collision_level),
        MACRO_OBJECTS(/*objList*/ bitdw_seg7_macro_objs),
        SHOW_DIALOG(/*index*/ 0x00, DIALOG_090),
        SET_BACKGROUND_MUSIC(/*settingsPreset*/ 0x0000, /*seq*/ SEQ_LEVEL_KOOPA_ROAD),
        TERRAIN_TYPE(/*terrainType*/ TERRAIN_STONE),
#ifdef PUPPYLIGHTS
    #define CRYSTAL_LIGHT_SIZE  400
    #define CRYSTAL_LIGHT(x, y, z) PUPPYLIGHT_NODE(0xB6, 0xCD, 0xF6, 0xFF, (x), (y), (z), CRYSTAL_LIGHT_SIZE, CRYSTAL_LIGHT_SIZE, CRYSTAL_LIGHT_SIZE, 0x0, 0, (PUPPYLIGHT_SHAPE_CYLINDER | PUPPYLIGHT_DIRECTIONAL), -1)
        CRYSTAL_LIGHT(-7104,   205,   356),
        CRYSTAL_LIGHT(-7104,   844, -2088),
        CRYSTAL_LIGHT(-6466,     9,   986),
        CRYSTAL_LIGHT(-4013,  -670,   990),
        CRYSTAL_LIGHT(-5251,  -276,   967),
        CRYSTAL_LIGHT(-7665,   502,  -256),
    #undef CRYSTAL_LIGHT_SIZE
    #undef CRYSTAL_LIGHT
#endif
    END_AREA(),

    FREE_LEVEL_POOL(),
    MARIO_POS(/*area*/ 1, /*yaw*/ 90, /*pos*/ -7444, -3154, 3886),
    CALL(     /*arg*/ 0, /*func*/ lvl_init_or_update),
    CALL_LOOP(/*arg*/ 1, /*func*/ lvl_init_or_update),
    CLEAR_LEVEL(),
    SLEEP_BEFORE_EXIT(/*frames*/ 1),
    EXIT(),
};
