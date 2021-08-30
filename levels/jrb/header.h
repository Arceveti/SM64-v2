#ifndef JRB_HEADER_H
#define JRB_HEADER_H

#include "types.h"
#include "game/moving_texture.h"

// geo
extern const GeoLayout jrb_geo_falling_pillar[];
extern const GeoLayout jrb_geo_falling_pillar_base[];
extern const GeoLayout jrb_geo_rock[];
extern const GeoLayout jrb_geo_floating_platform[];
extern const GeoLayout jrb_geo_sliding_box[];
extern const GeoLayout jrb_geo_ship_left_half_part[];
extern const GeoLayout jrb_geo_sunken_ship[];
extern const GeoLayout jrb_geo_ship_back_left_part[];
extern const GeoLayout jrb_geo_sunken_ship_back[];
extern const GeoLayout jrb_geo_ship_right_half_part[];
extern const GeoLayout jrb_geo_ship_back_right_part[];
extern const GeoLayout jrb_geo_000A18[];
extern const GeoLayout jrb_geo_000AFC[];

// leveldata
extern const Gfx jrb_seg7_dl_07002FD0[];
extern const Gfx jrb_seg7_dl_07004940[];
extern const Gfx jrb_seg7_dl_07004C78[];
extern const Gfx jrb_seg7_dl_070058C8[];
extern const Gfx jrb_seg7_dl_070069B0[];
extern const Gfx jrb_seg7_dl_07007570[];
extern const Gfx jrb_seg7_dl_07007718[];
extern const Gfx jrb_seg7_dl_rock[];
extern const Gfx jrb_seg7_dl_floating_platform[];
extern const Gfx jrb_seg7_dl_sliding_box[];
extern const Gfx jrb_seg7_dl_ship_left_half_part[];
extern const Gfx jrb_seg7_dl_sunken_ship[];
extern const Gfx jrb_seg7_dl_ship_back_left_part[];
extern const Gfx jrb_seg7_dl_sunken_ship_back[];
extern const Gfx jrb_seg7_dl_ship_right_half_part[];
extern const Gfx jrb_seg7_dl_ship_back_right_part[];
extern const Gfx jrb_seg7_dl_falling_pillar[];
extern const Gfx jrb_seg7_dl_falling_pillar_base[];
extern const Collision jrb_seg7_area_1_collision[];
extern const MacroObject jrb_seg7_area_1_macro_objs[];
extern const Collision jrb_seg7_collision_rock_solid[];
extern const Collision jrb_seg7_collision_floating_platform[];
extern const Collision jrb_seg7_collision_floating_box[];
extern const Collision jrb_seg7_collision_floating_ship[];
extern const Collision jrb_seg7_collision_in_sunken_ship[];
extern const Collision jrb_seg7_collision_in_sunken_ship_2[];
extern const Collision jrb_seg7_collision_pillar_base[];
extern const Collision jrb_seg7_collision_unused_lid[];
extern const Trajectory jrb_seg7_trajectory_unagi_ship[];
extern const Trajectory jrb_seg7_trajectory_unagi_cave[];
extern const struct MovtexQuadCollection jrb_movtex_water[];
extern const struct MovtexQuadCollection jrb_movtex_initial_mist[];
extern const Gfx jrb_seg7_dl_0700EF00[];
extern const Gfx jrb_seg7_dl_0700FE48[];
extern const Gfx jrb_seg7_dl_07010548[];
extern const Collision jrb_seg7_area_2_collision[];
extern const MacroObject jrb_seg7_area_2_macro_objs[];
extern const struct MovtexQuadCollection jrb_movtex_sinked_boat_water[];

// script
extern const LevelScript level_jrb_entry[];

#endif
