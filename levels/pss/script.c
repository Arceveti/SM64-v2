#include <ultra64.h>
#include "sm64.h"
#include "behavior_data.h"
#include "model_ids.h"
#include "seq_ids.h"
#include "segment_symbols.h"
#include "level_commands.h"

#include "game/level_update.h"

#include "levels/scripts.h"

#include "actors/common1.h"

#include "make_const_nonconst.h"
#include "levels/pss/header.h"

const LevelScript level_pss_entry[] = {
    INIT_LEVEL(),
    LOAD_YAY0(        /*seg*/ 0x07, _pss_segment_7SegmentRomStart, _pss_segment_7SegmentRomEnd),
    LOAD_YAY0_TEXTURE(/*seg*/ 0x09, _mountain_yay0SegmentRomStart, _mountain_yay0SegmentRomEnd),
    LOAD_YAY0(        /*seg*/ 0x05, _group8_yay0SegmentRomStart, _group8_yay0SegmentRomEnd),
    LOAD_RAW(         /*seg*/ 0x0C, _group8_geoSegmentRomStart,  _group8_geoSegmentRomEnd),
    LOAD_YAY0(        /*seg*/ 0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd),
    LOAD_RAW(         /*seg*/ 0x0F, _common0_geoSegmentRomStart,  _common0_geoSegmentRomEnd),
    ALLOC_LEVEL_POOL(),
    MARIO(/*model*/ MODEL_MARIO, /*behParam*/ 0x00000001, /*beh*/ bhvMario),
    JUMP_LINK(script_func_global_1),
    JUMP_LINK(script_func_global_9),

    AREA(/*index*/ 1, pss_geo_000100),
        OBJECT(/*model*/ MODEL_NONE, /*pos*/ 5632, 6751, -5631, /*angle*/ 0, 270, 0, /*behParam*/ 0x000A0000, /*beh*/ bhvAirborneWarp),
        WARP_NODE(/*id*/ 0x0A, /*destLevel*/ LEVEL_PSS,    /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
        WARP_NODE(/*id*/ 0xF3, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x01, /*destNode*/ 0x20, /*flags*/ WARP_NO_CHECKPOINT),
        WARP_NODE(/*id*/ 0xF0, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x01, /*destNode*/ 0x26, /*flags*/ WARP_NO_CHECKPOINT),
        WARP_NODE(/*id*/ 0xF1, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x01, /*destNode*/ 0x23, /*flags*/ WARP_NO_CHECKPOINT),
        TERRAIN(/*terrainData*/ pss_seg7_collision),
        MACRO_OBJECTS(/*objList*/ pss_seg7_macro_objs),
        TERRAIN_TYPE(/*terrainType*/ TERRAIN_SLIDE),
        SET_BACKGROUND_MUSIC(/*settingsPreset*/ 0x0001, /*seq*/ SEQ_LEVEL_SLIDE),
#ifdef PUPPYLIGHTS
    #define LANTERN_SIZE 1600
    #define LANTERN_LIGHT(x, y, z) PUPPYLIGHT_NODE(255,  85,   0, 255, (x), (y), (z), LANTERN_SIZE, LANTERN_SIZE, LANTERN_SIZE, 0x0, 0, (PUPPYLIGHT_SHAPE_CYLINDER | PUPPYLIGHT_DIRECTIONAL), -1)
        LANTERN_LIGHT( 2920,  6460, -5170),
        LANTERN_LIGHT( 2920,  6460, -6092),
        LANTERN_LIGHT(-3600,  4960, -6092),
        LANTERN_LIGHT(-5720,  4740, -5448),
        LANTERN_LIGHT(-6660,  4380, -3100),
        LANTERN_LIGHT(-6660,  3970,     0),
        LANTERN_LIGHT(-5076,  3535,  2390),
        LANTERN_LIGHT(  552, -1880, -5330),
        LANTERN_LIGHT(-4560, -3300, -3300),
        LANTERN_LIGHT(-5900, -3900,   900),
        LANTERN_LIGHT(-6820, -3900,   900),
        LANTERN_LIGHT(-5900, -4032,  2300),
        LANTERN_LIGHT(-6820, -4032,  2300),
        LANTERN_LIGHT(-5900, -4164,  3700),
        LANTERN_LIGHT(-6820, -4164,  3700),
    #undef LANTERN_SIZE
    #undef LANTERN_LIGHT
#endif
    END_AREA(),

    FREE_LEVEL_POOL(),
    MARIO_POS(/*area*/ 1, /*yaw*/ 270, /*pos*/ 5632, 6451, -5631),
    CALL(/*arg*/ 0, /*func*/ lvl_init_or_update),
    CALL_LOOP(/*arg*/ 1, /*func*/ lvl_init_or_update),
    CLEAR_LEVEL(),
    SLEEP_BEFORE_EXIT(/*frames*/ 1),
    EXIT(),
};
