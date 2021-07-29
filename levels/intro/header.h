#ifndef INTRO_HEADER_H
#define INTRO_HEADER_H

#include "types.h"

// geo
extern const GeoLayout intro_geo_splash_screen[];
extern const GeoLayout intro_geo_mario_head_regular[];
extern const GeoLayout intro_geo_mario_head_dizzy[];
extern const GeoLayout intro_geo_debug_level_select[];

// leveldata
extern const Gfx intro_seg7_dl_main_logo[];
extern const Gfx intro_seg7_dl_copyright_trademark[];
extern const f32 intro_seg7_table_0700C790[];
extern const f32 intro_seg7_table_0700C880[];

// script
extern const LevelScript level_intro_splash_screen[];
extern const LevelScript level_intro_mario_head_regular[];
extern const LevelScript level_intro_mario_head_dizzy[];
extern const LevelScript level_intro_entry_4[];
extern const LevelScript script_intro_L1[];
extern const LevelScript script_intro_L2[];
extern const LevelScript script_intro_L3[];
extern const LevelScript script_intro_L4[];
extern const LevelScript script_intro_L5[];

// #ifdef USE_EXT_RAM
extern const GeoLayout intro_geo_error_screen[];
extern const LevelScript level_intro_entry_error_screen[];
extern Gfx *geo18_display_error_message(u32 callContext, UNUSED struct GraphNode *node, UNUSED u32 context);
// #endif

#endif
