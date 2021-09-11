#ifndef SL_HEADER_H
#define SL_HEADER_H

#include "types.h"
#include "game/moving_texture.h"

// geo
extern const GeoLayout sl_geo_cracked_ice[];
extern const GeoLayout sl_geo_ice_shard[];
extern const GeoLayout sl_geo_snow_mound[];
extern const GeoLayout sl_geo_area_1[];
extern const GeoLayout sl_geo_area_2[];

// leveldata
extern const Gfx sl_seg7_dl_07005478[];
extern const Gfx sl_seg7_dl_070056B0[];
extern const Gfx sl_seg7_dl_070073D0[];
extern const Gfx sl_seg7_dl_07007880[];
extern const Gfx sl_seg7_dl_070088B0[];
extern const Gfx sl_seg7_dl_07008D58[];
extern const Gfx sl_seg7_dl_0700A5A0[];
extern const Gfx sl_seg7_dl_0700A780[];
extern const Gfx sl_seg7_dl_cracked_ice[];
extern const Gfx sl_seg7_dl_ice_shard[];
extern const Gfx sl_seg7_dl_0700BAE8[];
extern const Gfx sl_seg7_dl_0700BCF8[];
extern const Gfx sl_seg7_dl_0700C9E8[];
extern const Gfx sl_seg7_dl_0700CB58[];
extern const Collision sl_seg7_area_1_collision[];
extern const MacroObject sl_seg7_area_1_macro_objs[];
extern const Collision sl_seg7_collision_sliding_snow_mound[];
extern const Collision sl_seg7_collision_pound_explodes[];
extern const Collision sl_seg7_area_2_collision[];
extern const MacroObject sl_seg7_area_2_macro_objs[];
extern const struct MovtexQuadCollection sl_movtex_water[];

// script
extern const LevelScript level_sl_entry[];

#endif
