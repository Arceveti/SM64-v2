#ifndef TTC_HEADER_H
#define TTC_HEADER_H

#include "types.h"

// geo
extern const GeoLayout ttc_geo_rotating_cube[];
extern const GeoLayout ttc_geo_rotating_prism[];
extern const GeoLayout ttc_geo_pendulum[];
extern const GeoLayout ttc_geo_large_treadmill[];
extern const GeoLayout ttc_geo_small_treadmill[];
extern const GeoLayout ttc_geo_push_block[];
extern const GeoLayout ttc_geo_rotating_hexagon[];
extern const GeoLayout ttc_geo_rotating_triangle[];
extern const GeoLayout ttc_geo_pit_block[];
extern const GeoLayout ttc_geo_pit_block_2[];
extern const GeoLayout ttc_geo_elevator_platform[];
extern const GeoLayout ttc_geo_clock_hand[];
extern const GeoLayout ttc_geo_spinner[];
extern const GeoLayout ttc_geo_small_gear[];
extern const GeoLayout ttc_geo_large_gear[];
extern const GeoLayout ttc_geo_area_1[];

// leveldata
extern const Gfx ttc_seg7_dl_area_1_opaque[];
extern const Gfx ttc_seg7_dl_outer_walls[];
extern const Gfx ttc_seg7_dl_area_1_alpha[];
extern const Gfx ttc_seg7_dl_rotating_cube[];
extern const Gfx ttc_seg7_dl_rotating_prism[];
extern const Gfx ttc_seg7_dl_pendulum[];
extern const Gfx ttc_seg7_dl_large_treadmill[];
extern const Gfx ttc_seg7_dl_small_treadmill[];
extern const Gfx ttc_seg7_dl_push_block[];
extern const Gfx ttc_seg7_dl_rotating_hexagon[];
extern const Gfx ttc_seg7_dl_rotating_triangle[];
extern const Gfx ttc_seg7_dl_pit_block[];
extern const Gfx ttc_seg7_dl_pit_block_2[];
extern const Gfx ttc_seg7_dl_elevator_platform[];
extern const Gfx ttc_seg7_dl_clock_hand[];
extern const Gfx ttc_seg7_dl_spinner[];
extern const Gfx ttc_seg7_dl_small_gear[];
extern const Gfx ttc_seg7_dl_large_gear[];
extern const Collision ttc_seg7_collision_level[];
extern const Collision ttc_seg7_collision_rotating_cube[];
extern const Collision ttc_seg7_collision_rotating_prism[];
extern const Collision ttc_seg7_collision_clock_pendulum[];
extern const Collision ttc_seg7_collision_large_treadmill[];
extern const Collision ttc_seg7_collision_small_treadmill[];
extern const Collision ttc_seg7_collision_sliding_surface[];
extern const Collision ttc_seg7_collision_rotating_hexagon[];
extern const Collision ttc_seg7_collision_rotating_triangle[];
extern const Collision ttc_seg7_collision_pit_block[];
extern const Collision ttc_seg7_collision_pit_block_2[];
extern const Collision ttc_seg7_collision_clock_platform[];
extern const Collision ttc_seg7_collision_clock_main_rotation[];
extern const Collision ttc_seg7_collision_rotating_clock_platform2[];
extern const MacroObject ttc_seg7_macro_objs[];
extern const u8 ttc_yellow_triangle[];
extern const Gfx ttc_dl_surface_treadmill_begin[];
extern const Gfx ttc_dl_surface_treadmill_end[];
extern Movtex ttc_movtex_tris_big_surface_treadmill[];
extern Movtex ttc_movtex_tris_small_surface_treadmill[];
extern const Gfx ttc_dl_surface_treadmill[];

// script
extern const LevelScript level_ttc_entry[];

#endif
