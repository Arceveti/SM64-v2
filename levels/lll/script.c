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
#include "levels/lll/header.h"

// Unlike most levels, level geometry objects in LLL are defined as regular objects instead of terrain objects.
static const LevelScript script_func_local_1[] = {
    OBJECT(          /*model*/ MODEL_LEVEL_GEOMETRY_03,                  /*pos*/  3840,    0, -5632, /*angle*/ 0,   0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvStaticObject),
    OBJECT(          /*model*/ MODEL_LEVEL_GEOMETRY_04,                  /*pos*/  4992,    0,  -640, /*angle*/ 0,   0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvStaticObject),
    OBJECT(          /*model*/ MODEL_LEVEL_GEOMETRY_05,                  /*pos*/  7168,    0,  1408, /*angle*/ 0,   0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvStaticObject),
    OBJECT(          /*model*/ MODEL_LEVEL_GEOMETRY_06,                  /*pos*/     0,    0,  3712, /*angle*/ 0,   0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvStaticObject),
    OBJECT(          /*model*/ MODEL_LEVEL_GEOMETRY_07,                  /*pos*/ -3200,    0,  3456, /*angle*/ 0,   0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvStaticObject),
    OBJECT(          /*model*/ MODEL_LEVEL_GEOMETRY_08,                  /*pos*/ -5120,    0, -2048, /*angle*/ 0,   0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvStaticObject),
    OBJECT(          /*model*/ MODEL_LEVEL_GEOMETRY_0A,                  /*pos*/     0,    0,     0, /*angle*/ 0,   0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvStaticObject),
    OBJECT(          /*model*/ MODEL_LEVEL_GEOMETRY_0B,                  /*pos*/     0,    0,  6272, /*angle*/ 0,   0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvStaticObject),
    OBJECT(          /*model*/ MODEL_LEVEL_GEOMETRY_0C,                  /*pos*/  5632,    0,  1408, /*angle*/ 0, 270, 0, /*behParam*/ 0x00000000, /*beh*/ bhvStaticObject),
    OBJECT(          /*model*/ MODEL_LEVEL_GEOMETRY_0C,                  /*pos*/  2048,    0,  3456, /*angle*/ 0, 180, 0, /*behParam*/ 0x00000000, /*beh*/ bhvStaticObject),
    OBJECT(          /*model*/ MODEL_LEVEL_GEOMETRY_0C,                  /*pos*/ -4608,    0,  3456, /*angle*/ 0, 270, 0, /*behParam*/ 0x00000000, /*beh*/ bhvStaticObject),
    OBJECT(          /*model*/ MODEL_LEVEL_GEOMETRY_0C,                  /*pos*/ -5120,    0,  -512, /*angle*/ 0,   0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvStaticObject),
    OBJECT(          /*model*/ MODEL_LEVEL_GEOMETRY_0D,                  /*pos*/     0,    0, -2048, /*angle*/ 0,   0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvStaticObject),
    OBJECT(          /*model*/ MODEL_LEVEL_GEOMETRY_0E,                  /*pos*/ -5120,  320, -3200, /*angle*/ 0,  90, 0, /*behParam*/ 0x00000000, /*beh*/ bhvStaticObject), // was bhvLllHexagonalMesh
    RETURN(),
};

static const LevelScript script_func_local_2[] = {
    OBJECT(          /*model*/ MODEL_LLL_DRAWBRIDGE_PART,                /*pos*/ -1920,  307,  3648, /*angle*/ 0,   0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvLllDrawbridgeSpawner),
    OBJECT(          /*model*/ MODEL_LLL_ROTATING_BLOCK_FIRE_BARS,       /*pos*/ -5120,  307, -4096, /*angle*/ 0,   0, 0, /*behParam*/ 0x00040000, /*beh*/ bhvLllRotatingBlockWithFireBars),
    OBJECT(          /*model*/ MODEL_LLL_ROTATING_HEXAGONAL_RING,        /*pos*/     0,    0,     0, /*angle*/ 0,   0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvLllRotatingHexagonalRing),
    OBJECT(          /*model*/ MODEL_LLL_SINKING_RECTANGULAR_PLATFORM,   /*pos*/  3968,    0,  1408, /*angle*/ 0,  90, 0, /*behParam*/ 0x00000000, /*beh*/ bhvLllSinkingRectangularPlatform),
    OBJECT(          /*model*/ MODEL_LLL_SINKING_RECTANGULAR_PLATFORM,   /*pos*/ -5760,    0,  3072, /*angle*/ 0,   0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvLllSinkingRectangularPlatform),
    OBJECT(          /*model*/ MODEL_LLL_SINKING_RECTANGULAR_PLATFORM,   /*pos*/  2816,    0,   512, /*angle*/ 0,  90, 0, /*behParam*/ 0x00000000, /*beh*/ bhvLllSinkingRectangularPlatform),
    OBJECT(          /*model*/ MODEL_LLL_SINKING_RECTANGULAR_PLATFORM,   /*pos*/ -1791,    0, -4096, /*angle*/ 0,  90, 0, /*behParam*/ 0x00000000, /*beh*/ bhvLllSinkingRectangularPlatform),
    OBJECT(          /*model*/ MODEL_LLL_SINKING_SQUARE_PLATFORMS,       /*pos*/  3840,    0, -3200, /*angle*/ 0,   0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvLllSinkingSquarePlatforms),
    OBJECT(          /*model*/ MODEL_LLL_TILTING_SQUARE_PLATFORM,        /*pos*/   922, -154,  2150, /*angle*/ 0,   0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvLllTiltingInvertedPyramid),
    OBJECT(          /*model*/ MODEL_LLL_TILTING_SQUARE_PLATFORM,        /*pos*/  1741, -154,  1741, /*angle*/ 0,   0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvLllTiltingInvertedPyramid),
    OBJECT(          /*model*/ MODEL_LLL_TILTING_SQUARE_PLATFORM,        /*pos*/  1741, -154,  2560, /*angle*/ 0,   0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvLllTiltingInvertedPyramid),
    OBJECT(          /*model*/ MODEL_LLL_TILTING_SQUARE_PLATFORM,        /*pos*/  2100, -154,  -307, /*angle*/ 0,   0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvLllTiltingInvertedPyramid),
    OBJECT(          /*model*/ MODEL_NONE,                               /*pos*/ -5120,  102,  1024, /*angle*/ 0,   0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvLllBowserPuzzle),
    RETURN(),
};

static const LevelScript script_func_local_3[] = {
    OBJECT(          /*model*/ MODEL_LLL_MOVING_OCTAGONAL_MESH_PLATFORM, /*pos*/  1124,    0, -4608, /*angle*/ 0,   0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvLllMovingOctagonalMeshPlatform),
    OBJECT(          /*model*/ MODEL_LLL_MOVING_OCTAGONAL_MESH_PLATFORM, /*pos*/  7168,    0,  2432, /*angle*/ 0,   0, 0, /*behParam*/ 0x00010000, /*beh*/ bhvLllMovingOctagonalMeshPlatform),
    OBJECT(          /*model*/ MODEL_LLL_SINKING_ROCK_BLOCK,             /*pos*/  7168,    0,  7296, /*angle*/ 0,   0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvLllSinkingRockBlock),
    OBJECT(          /*model*/ MODEL_LLL_ROLLING_LOG,                    /*pos*/  6144,  307,  6016, /*angle*/ 0,  90, 0, /*behParam*/ 0x00000000, /*beh*/ bhvLllRollingLog),
    OBJECT(          /*model*/ MODEL_LEVEL_GEOMETRY_09,                  /*pos*/ -5120,    0, -4096, /*angle*/ 0,   0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvLllRotatingHexagonalPlatform),
    OBJECT(          /*model*/ MODEL_NONE,                               /*pos*/ -3584,    0, -4096, /*angle*/ 0,   0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvLllFloatingWoodBridge),
    RETURN(),
};

static const LevelScript script_func_local_4[] = {
    OBJECT(          /*model*/ MODEL_NONE,                               /*pos*/ -3200,  307,  3456, /*angle*/ 0,   0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvMrI),
    OBJECT(          /*model*/ MODEL_BULLY_BOSS,                         /*pos*/     0,  307, -4385, /*angle*/ 0,   0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvBigBully),
    OBJECT(          /*model*/ MODEL_BULLY_BOSS,                         /*pos*/  4046, 2234, -5521, /*angle*/ 0,   0, 0, /*behParam*/ 0x01000000, /*beh*/ bhvBigBullyWithMinions),
    OBJECT(          /*model*/ MODEL_BULLY,                              /*pos*/ -5120,  307, -2482, /*angle*/ 0,   0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvSmallBully),
    OBJECT(          /*model*/ MODEL_BULLY,                              /*pos*/     0,  307,  3712, /*angle*/ 0,   0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvSmallBully),
    OBJECT(          /*model*/ MODEL_BULLY,                              /*pos*/  6813,  307,  1613, /*angle*/ 0,   0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvSmallBully),
    OBJECT(          /*model*/ MODEL_BULLY,                              /*pos*/  7168,  307,   992, /*angle*/ 0,   0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvSmallBully),
    OBJECT(          /*model*/ MODEL_BULLY,                              /*pos*/ -5130,  285, -1663, /*angle*/ 0,   0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvSmallBully),
    OBJECT(          /*model*/ MODEL_NONE,                               /*pos*/     0,  200, -2048, /*angle*/ 0,   0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvFlamethrower),
    OBJECT(          /*model*/ MODEL_NONE,                               /*pos*/   500,    2,  5000, /*angle*/ 0, 270, 0, /*behParam*/ 0x00000000, /*beh*/ bhvBouncingFireballSpawner),
    OBJECT(          /*model*/ MODEL_NONE,                               /*pos*/  -700,    2,  4500, /*angle*/ 0,  90, 0, /*behParam*/ 0x00000000, /*beh*/ bhvBouncingFireballSpawner),
    OBJECT(          /*model*/ MODEL_NONE,                               /*pos*/ -6300,    2,  2625, /*angle*/ 0,  90, 0, /*behParam*/ 0x00000000, /*beh*/ bhvBouncingFireballSpawner),
    OBJECT(          /*model*/ MODEL_NONE,                               /*pos*/ -3280,    2, -4854, /*angle*/ 0,   0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvBouncingFireballSpawner),
    OBJECT(          /*model*/ MODEL_NONE,                               /*pos*/  5996,    2,  -390, /*angle*/ 0, 315, 0, /*behParam*/ 0x00000000, /*beh*/ bhvBouncingFireballSpawner),
    OBJECT(          /*model*/ MODEL_NONE,                               /*pos*/  5423,    2, -1991, /*angle*/ 0, 315, 0, /*behParam*/ 0x00000000, /*beh*/ bhvBouncingFireballSpawner),
    OBJECT(          /*model*/ MODEL_NONE,                               /*pos*/  4921,    2, -1504, /*angle*/ 0,  90, 0, /*behParam*/ 0x00000000, /*beh*/ bhvBouncingFireballSpawner),
    OBJECT_WITH_ACTS(/*model*/ MODEL_EXCLAMATION_BOX,                    /*pos*/  1050,  550,  6200, /*angle*/ 0,   0, 0, /*behParam*/ 0x00030000, /*beh*/ bhvExclamationBox, /*acts*/ ACT_5 | ACT_6),
    RETURN(),
};

static const LevelScript script_func_local_5[] = {
    OBJECT_WITH_ACTS(/*model*/ MODEL_NONE,                               /*pos*/ -4352,  350,   256, /*angle*/ 0,   0, 0, /*behParam*/ 0x02000000, /*beh*/ bhvHiddenRedCoinStar, /*acts*/ ALL_ACTS),
    OBJECT_WITH_ACTS(/*model*/ MODEL_STAR,                               /*pos*/  3100,  400,  7900, /*angle*/ 0,   0, 0, /*behParam*/ 0x03000000, /*beh*/ bhvStar,              /*acts*/ ALL_ACTS),
    RETURN(),
};

static const LevelScript script_func_local_6[] = {
    OBJECT(          /*model*/ MODEL_NONE,                               /*pos*/   728, 2606, -2754, /*angle*/ 0,   0, 0, /*behParam*/ 0x00380000, /*beh*/ bhvPoleGrabbing),
    OBJECT(          /*model*/ MODEL_NONE,                               /*pos*/  1043, 2972, -2679, /*angle*/ 0,   0, 0, /*behParam*/ 0x004E0000, /*beh*/ bhvPoleGrabbing),
    OBJECT(          /*model*/ MODEL_NONE,                               /*pos*/  1078, 3078, -2269, /*angle*/ 0,   0, 0, /*behParam*/ 0x00660000, /*beh*/ bhvPoleGrabbing),
    OBJECT(          /*model*/ MODEL_NONE,                               /*pos*/  1413, 3222, -2190, /*angle*/ 0,   0, 0, /*behParam*/ 0x00520000, /*beh*/ bhvPoleGrabbing),
    OBJECT(          /*model*/ MODEL_NONE,                               /*pos*/   783, 1126,   -48, /*angle*/ 0,   0, 0, /*behParam*/ 0x00660000, /*beh*/ bhvPoleGrabbing),
    OBJECT(          /*model*/ MODEL_NONE,                               /*pos*/   666, 2150,   708, /*angle*/ 0,   0, 0, /*behParam*/ 0x00660000, /*beh*/ bhvPoleGrabbing),
    OBJECT(          /*model*/ MODEL_NONE,                               /*pos*/  2943,  480,    10, /*angle*/ 0, 270, 0, /*behParam*/ 0x00020000, /*beh*/ bhvFlamethrower),
    OBJECT(          /*model*/ MODEL_NONE,                               /*pos*/ -2759, 2350, -1108, /*angle*/ 0,  60, 0, /*behParam*/ 0x00020000, /*beh*/ bhvFlamethrower),
    OBJECT(          /*model*/ MODEL_NONE,                               /*pos*/ -2472, 2350, -1605, /*angle*/ 0,  60, 0, /*behParam*/ 0x00020000, /*beh*/ bhvFlamethrower),
    OBJECT(          /*model*/ MODEL_LLL_VOLCANO_FALLING_TRAP,           /*pos*/  -485, 1203,  2933, /*angle*/ 0,   0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvLllVolcanoFallingTrap),
    OBJECT(          /*model*/ MODEL_LLL_ROTATING_BLOCK_FIRE_BARS,       /*pos*/   417, 2150,   583, /*angle*/ 0,   0, 0, /*behParam*/ 0x00040000, /*beh*/ bhvLllRotatingBlockWithFireBars),
    OBJECT(          /*model*/ MODEL_CHECKERBOARD_PLATFORM,              /*pos*/  -764,    0,  1664, /*angle*/ 0, 180, 0, /*behParam*/ 0x08A50000, /*beh*/ bhvPlatformOnTrack),
    OBJECT(          /*model*/ MODEL_CHECKERBOARD_PLATFORM,              /*pos*/   184,  980, -1366, /*angle*/ 0, 180, 0, /*behParam*/ 0x08A60000, /*beh*/ bhvPlatformOnTrack),
    OBJECT(          /*model*/ MODEL_NONE,                               /*pos*/   -26,  102, -2649, /*angle*/ 0,   0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvVolcanoSoundLoop),
    RETURN(),
};

static const LevelScript script_func_local_7[] = {
    OBJECT_WITH_ACTS(/*model*/ MODEL_STAR,                               /*pos*/  2523, 3850,  -901, /*angle*/ 0,   0, 0, /*behParam*/ 0x04000000, /*beh*/ bhvStar, /*acts*/ ALL_ACTS),
    OBJECT_WITH_ACTS(/*model*/ MODEL_STAR,                               /*pos*/  1800, 3400,  1450, /*angle*/ 0,   0, 0, /*behParam*/ 0x05000000, /*beh*/ bhvStar, /*acts*/ ALL_ACTS),
    RETURN(),
};

const LevelScript level_lll_entry[] = {
    INIT_LEVEL(),
    LOAD_YAY0(        /*seg*/ 0x07,     _lll_segment_7SegmentRomStart,     _lll_segment_7SegmentRomEnd),
    LOAD_YAY0_TEXTURE(/*seg*/ 0x09,         _fire_yay0SegmentRomStart,         _fire_yay0SegmentRomEnd),
    LOAD_YAY0(        /*seg*/ 0x0A, _bitfs_skybox_yay0SegmentRomStart, _bitfs_skybox_yay0SegmentRomEnd),
    LOAD_YAY0(        /*seg*/ 0x0B,       _effect_yay0SegmentRomStart,       _effect_yay0SegmentRomEnd),
    LOAD_YAY0(        /*seg*/ 0x05,       _group2_yay0SegmentRomStart,       _group2_yay0SegmentRomEnd),
    LOAD_RAW(         /*seg*/ 0x0C,        _group2_geoSegmentRomStart,        _group2_geoSegmentRomEnd),
    LOAD_YAY0(        /*seg*/ 0x06,      _group17_yay0SegmentRomStart,      _group17_yay0SegmentRomEnd),
    LOAD_RAW(         /*seg*/ 0x0D,       _group17_geoSegmentRomStart,       _group17_geoSegmentRomEnd),
    LOAD_YAY0(        /*seg*/ 0x08,      _common0_yay0SegmentRomStart,      _common0_yay0SegmentRomEnd),
    LOAD_RAW(         /*seg*/ 0x0F,       _common0_geoSegmentRomStart,       _common0_geoSegmentRomEnd),
    ALLOC_LEVEL_POOL(),
    MARIO(/*model*/ MODEL_MARIO, /*behParam*/ 0x00000001, /*beh*/ bhvMario),
    JUMP_LINK(script_func_global_1),
    JUMP_LINK(script_func_global_3),
    JUMP_LINK(script_func_global_18),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_03,                  lll_geo_wide_platform_with_bullies),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_04,                  lll_geo_w_shaped_platform),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_05,                  lll_geo_octagonal_platform),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_06,                  lll_geo_bridge_platform),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_07,                  lll_geo_cage_platform),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_08,                  lll_geo_long_platform),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_09,                  lll_geo_rotating_hexagonal_platform),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_0A,                  lll_geo_volcano_outside),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_0B,                  lll_geo_archway_platform),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_0C,                  lll_geo_arrows_slope),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_0D,                  lll_geo_flamethrower),
    LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_0E,                  lll_geo_hexagonal_mesh),
    LOAD_MODEL_FROM_GEO(MODEL_LLL_DRAWBRIDGE_PART,                lll_geo_drawbridge_part),
    LOAD_MODEL_FROM_GEO(MODEL_LLL_ROTATING_BLOCK_FIRE_BARS,       lll_geo_rotating_block_fire_bars),
    LOAD_MODEL_FROM_GEO(MODEL_LLL_ROTATING_HEXAGONAL_RING,        lll_geo_rotating_hexagonal_ring),
    LOAD_MODEL_FROM_GEO(MODEL_LLL_SINKING_RECTANGULAR_PLATFORM,   lll_geo_sinking_rectangular_platform),
    LOAD_MODEL_FROM_GEO(MODEL_LLL_SINKING_SQUARE_PLATFORMS,       lll_geo_sinking_square_platform),
    LOAD_MODEL_FROM_GEO(MODEL_LLL_TILTING_SQUARE_PLATFORM,        lll_geo_tilting_square_platform),
    LOAD_MODEL_FROM_GEO(MODEL_LLL_BOWSER_PIECE_1,                 lll_geo_bowser_puzzle_piece_1),
    LOAD_MODEL_FROM_GEO(MODEL_LLL_BOWSER_PIECE_2,                 lll_geo_bowser_puzzle_piece_2),
    LOAD_MODEL_FROM_GEO(MODEL_LLL_BOWSER_PIECE_3,                 lll_geo_bowser_puzzle_piece_3),
    LOAD_MODEL_FROM_GEO(MODEL_LLL_BOWSER_PIECE_4,                 lll_geo_bowser_puzzle_piece_4),
    LOAD_MODEL_FROM_GEO(MODEL_LLL_BOWSER_PIECE_5,                 lll_geo_bowser_puzzle_piece_5),
    LOAD_MODEL_FROM_GEO(MODEL_LLL_BOWSER_PIECE_6,                 lll_geo_bowser_puzzle_piece_6),
    LOAD_MODEL_FROM_GEO(MODEL_LLL_BOWSER_PIECE_7,                 lll_geo_bowser_puzzle_piece_7),
    LOAD_MODEL_FROM_GEO(MODEL_LLL_BOWSER_PIECE_8,                 lll_geo_bowser_puzzle_piece_8),
    LOAD_MODEL_FROM_GEO(MODEL_LLL_BOWSER_PIECE_9,                 lll_geo_bowser_puzzle_piece_9),
    LOAD_MODEL_FROM_GEO(MODEL_LLL_BOWSER_PIECE_10,                lll_geo_bowser_puzzle_piece_10),
    LOAD_MODEL_FROM_GEO(MODEL_LLL_BOWSER_PIECE_11,                lll_geo_bowser_puzzle_piece_11),
    LOAD_MODEL_FROM_GEO(MODEL_LLL_BOWSER_PIECE_12,                lll_geo_bowser_puzzle_piece_12),
    LOAD_MODEL_FROM_GEO(MODEL_LLL_BOWSER_PIECE_13,                lll_geo_bowser_puzzle_piece_13),
    LOAD_MODEL_FROM_GEO(MODEL_LLL_BOWSER_PIECE_14,                lll_geo_bowser_puzzle_piece_14),
    LOAD_MODEL_FROM_GEO(MODEL_LLL_MOVING_OCTAGONAL_MESH_PLATFORM, lll_geo_moving_octagonal_mesh_platform),
    LOAD_MODEL_FROM_GEO(MODEL_LLL_SINKING_ROCK_BLOCK,             lll_geo_sinking_rock_block),
    LOAD_MODEL_FROM_GEO(MODEL_LLL_ROLLING_LOG,                    lll_geo_rolling_log),
    LOAD_MODEL_FROM_GEO(MODEL_LLL_WOOD_BRIDGE,                    lll_geo_wooden_float_small),
    LOAD_MODEL_FROM_GEO(MODEL_LLL_LARGE_WOOD_BRIDGE,              lll_geo_wooden_float_large),
    LOAD_MODEL_FROM_GEO(MODEL_LLL_FALLING_PLATFORM,               lll_geo_tumbling_bridge),
    LOAD_MODEL_FROM_GEO(MODEL_LLL_LARGE_FALLING_PLATFORM,         lll_geo_long_wooden_bridge),
    LOAD_MODEL_FROM_GEO(MODEL_LLL_VOLCANO_FALLING_TRAP,           lll_geo_volcano_falling_trap),

    AREA(/*index*/ 1, lll_geo_area_1),
        OBJECT(/*model*/ MODEL_NONE, /*pos*/ -3839, 1154, 6272, /*angle*/ 0,   90, 0, /*behParam*/ 0x000A0000, /*beh*/ bhvSpinAirborneWarp),
        OBJECT(/*model*/ MODEL_NONE, /*pos*/     0,  102,    0, /*angle*/ 0,    0, 0, /*behParam*/ 0x190B0000, /*beh*/ bhvWarp),
        OBJECT(/*model*/ MODEL_NONE, /*pos*/ -3200,   11, 3456, /*angle*/ 0, -100, 0, /*behParam*/ 0x000C0000, /*beh*/ bhvFadingWarp),
        OBJECT(/*model*/ MODEL_NONE, /*pos*/ -5888,  154, 6656, /*angle*/ 0,  100, 0, /*behParam*/ 0x000D0000, /*beh*/ bhvFadingWarp),
        WARP_NODE(/*id*/ 0x0A, /*destLevel*/ LEVEL_LLL,    /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
        WARP_NODE(/*id*/ 0x0B, /*destLevel*/ LEVEL_LLL,    /*destArea*/ 0x02, /*destNode*/ 0x0A, /*flags*/ WARP_CHECKPOINT),
        WARP_NODE(/*id*/ 0x0C, /*destLevel*/ LEVEL_LLL,    /*destArea*/ 0x01, /*destNode*/ 0x0D, /*flags*/ WARP_NO_CHECKPOINT),
        WARP_NODE(/*id*/ 0x0D, /*destLevel*/ LEVEL_LLL,    /*destArea*/ 0x01, /*destNode*/ 0x0C, /*flags*/ WARP_NO_CHECKPOINT),
        WARP_NODE(/*id*/ 0xF0, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x03, /*destNode*/ 0x32, /*flags*/ WARP_NO_CHECKPOINT),
        WARP_NODE(/*id*/ 0xF1, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x03, /*destNode*/ 0x64, /*flags*/ WARP_NO_CHECKPOINT),
        JUMP_LINK(script_func_local_1),
        JUMP_LINK(script_func_local_2),
        JUMP_LINK(script_func_local_3),
        JUMP_LINK(script_func_local_4),
        JUMP_LINK(script_func_local_5),
        TERRAIN(/*terrainData*/ lll_seg7_area_1_collision),
        MACRO_OBJECTS(/*objList*/ lll_seg7_area_1_macro_objs),
        SHOW_DIALOG(/*index*/ 0x00, DIALOG_097),
        SET_BACKGROUND_MUSIC(/*settingsPreset*/ 0x0000, /*seq*/ SEQ_LEVEL_HOT),
        TERRAIN_TYPE(/*terrainType*/ TERRAIN_STONE),
    END_AREA(),

    AREA(/*index*/ 2, lll_geo_area_2),
        OBJECT(/*model*/ MODEL_NONE, /*pos*/ -955, 1103, -1024, /*angle*/ 0, 118, 0, /*behParam*/ 0x000A0000, /*beh*/ bhvAirborneWarp),
        WARP_NODE(/*id*/ 0x0A, /*destLevel*/ LEVEL_LLL,    /*destArea*/ 0x02, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
        WARP_NODE(/*id*/ 0xF0, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x03, /*destNode*/ 0x32, /*flags*/ WARP_NO_CHECKPOINT),
        WARP_NODE(/*id*/ 0xF1, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x03, /*destNode*/ 0x64, /*flags*/ WARP_NO_CHECKPOINT),
        JUMP_LINK(script_func_local_6),
        JUMP_LINK(script_func_local_7),
        TERRAIN(/*terrainData*/ lll_seg7_area_2_collision),
        MACRO_OBJECTS(/*objList*/ lll_seg7_area_2_macro_objs),
        SET_BACKGROUND_MUSIC(/*settingsPreset*/ 0x0004, /*seq*/ SEQ_LEVEL_HOT),
        TERRAIN_TYPE(/*terrainType*/ TERRAIN_STONE),
    END_AREA(),

    FREE_LEVEL_POOL(),
    MARIO_POS(/*area*/ 1, /*yaw*/ 90, /*pos*/ -3840, 154, 6272),
    CALL(     /*arg*/ 0, /*func*/ lvl_init_or_update),
    CALL_LOOP(/*arg*/ 1, /*func*/ lvl_init_or_update),
    CLEAR_LEVEL(),
    SLEEP_BEFORE_EXIT(/*frames*/ 1),
    EXIT(),
};
