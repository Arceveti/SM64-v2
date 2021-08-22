#ifndef WDW_HEADER_H
#define WDW_HEADER_H

#include "types.h"
#include "game/moving_texture.h"

// geo
extern const GeoLayout wdw_geo_square_floating_platform[];
extern const GeoLayout wdw_geo_arrow_lift[];
extern const GeoLayout wdw_geo_water_level_diamond[];
extern const GeoLayout wdw_geo_hidden_platform[];
extern const GeoLayout wdw_geo_express_elevator[];
extern const GeoLayout wdw_geo_rectangular_floating_platform[];
extern const GeoLayout wdw_geo_rotating_platform[];
extern const GeoLayout wdw_geo_000658[];
extern const GeoLayout wdw_geo_000724[];

// leveldata
extern const Gfx wdw_seg7_dl_07009AB0[];
extern const Gfx wdw_seg7_dl_0700A138[];
extern const Gfx wdw_seg7_dl_07011E48[];
extern const Gfx wdw_seg7_dl_07012258[];
extern const Gfx wdw_seg7_dl_07012798[];
extern const Gfx wdw_seg7_dl_07012908[];
extern const Gfx wdw_seg7_dl_square_floating_platform[];
extern const Gfx wdw_seg7_dl_arrow_lift[];
extern const Gfx wdw_seg7_dl_water_level_diamond[];
extern const Gfx wdw_seg7_dl_07013490[];
extern const Gfx wdw_seg7_dl_07013B70[];
extern const Gfx wdw_seg7_dl_07013E40[];
extern const Gfx wdw_seg7_dl_070140E0[];
extern const Collision wdw_seg7_area_1_collision[];
extern const MacroObject wdw_seg7_area_1_macro_objs[];
extern const Collision wdw_seg7_area_2_collision[];
extern const MacroObject wdw_seg7_area_2_macro_objs[];
extern const Collision wdw_seg7_collision_square_floating_platform[];
extern const Collision wdw_seg7_collision_arrow_lift[];
extern const Collision wdw_seg7_collision_water_level_diamond[];
extern const Collision wdw_seg7_collision_hidden_platform[];
extern const Collision wdw_seg7_collision_express_elevator_platform[];
extern const Collision wdw_seg7_collision_rect_floating_platform[];
extern const Collision wdw_seg7_collision_rotating_platform[];
extern const struct MovtexQuadCollection wdw_movtex_area1_water[];
extern const struct MovtexQuadCollection wdw_movtex_area2_water[];

// script
extern const LevelScript level_wdw_entry[];

#endif
