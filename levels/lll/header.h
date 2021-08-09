#ifndef LLL_HEADER_H
#define LLL_HEADER_H

#include "types.h"
#include "game/moving_texture.h"

// geo
extern const GeoLayout lll_geo_wide_platform_with_bullies[];
extern const GeoLayout lll_geo_w_shaped_platform[];
extern const GeoLayout lll_geo_octagonal_platform[];
extern const GeoLayout lll_geo_bridge_platform[];
extern const GeoLayout lll_geo_cage_platform[];
extern const GeoLayout lll_geo_long_platform[];
extern const GeoLayout lll_geo_rotating_hexagonal_platform[];
extern const GeoLayout lll_geo_volcano_outside[];
extern const GeoLayout lll_geo_archway_platform[];
extern const GeoLayout lll_geo_arrows_slope[];
extern const GeoLayout lll_geo_flamethrower[];
extern const GeoLayout lll_geo_hexagonal_mesh[];
extern const GeoLayout lll_geo_moving_octagonal_mesh_platform[];
extern const GeoLayout lll_geo_drawbridge_part[];
extern const GeoLayout lll_geo_rotating_block_fire_bars[];
extern const GeoLayout lll_geo_wooden_float_small[];
extern const GeoLayout lll_geo_wooden_float_large[];
extern const GeoLayout lll_geo_tumbling_bridge[];
extern const GeoLayout lll_geo_long_wooden_bridge[];
extern const GeoLayout lll_geo_rotating_hexagonal_ring[];
extern const GeoLayout lll_geo_sinking_rectangular_platform[];
extern const GeoLayout lll_geo_sinking_square_platform[];
extern const GeoLayout lll_geo_tilting_square_platform[];
extern const GeoLayout lll_geo_bowser_puzzle_piece_1[];
extern const GeoLayout lll_geo_bowser_puzzle_piece_2[];
extern const GeoLayout lll_geo_bowser_puzzle_piece_3[];
extern const GeoLayout lll_geo_bowser_puzzle_piece_4[];
extern const GeoLayout lll_geo_bowser_puzzle_piece_5[];
extern const GeoLayout lll_geo_bowser_puzzle_piece_6[];
extern const GeoLayout lll_geo_bowser_puzzle_piece_7[];
extern const GeoLayout lll_geo_bowser_puzzle_piece_8[];
extern const GeoLayout lll_geo_bowser_puzzle_piece_9[];
extern const GeoLayout lll_geo_bowser_puzzle_piece_10[];
extern const GeoLayout lll_geo_bowser_puzzle_piece_11[];
extern const GeoLayout lll_geo_bowser_puzzle_piece_12[];
extern const GeoLayout lll_geo_bowser_puzzle_piece_13[];
extern const GeoLayout lll_geo_bowser_puzzle_piece_14[];
extern const GeoLayout lll_geo_sinking_rock_block[];
extern const GeoLayout lll_geo_rolling_log[];
extern const GeoLayout lll_geo_area_1[];
extern const GeoLayout lll_geo_volcano_falling_trap[];
extern const GeoLayout lll_geo_area_2[];

// leveldata
extern const Gfx lll_seg7_dl_area_1[];
extern const Gfx lll_seg7_dl_corner_cage[];
extern const Gfx lll_seg7_dl_small_mesh_bridges[];
extern const Gfx lll_seg7_dl_wide_platform_with_bullies[];
extern const Gfx lll_seg7_dl_w_shaped_platform[];
extern const Gfx lll_seg7_dl_octagonal_platform[];
extern const Gfx lll_seg7_dl_bridge_platform[];
extern const Gfx lll_seg7_dl_cage_platform_bearings[];
extern const Gfx lll_seg7_dl_cage_platform[];
extern const Gfx lll_seg7_dl_long_platform[];
extern const Gfx lll_seg7_dl_rotating_hexagonal_platform[];
extern const Gfx lll_seg7_dl_volcano_outside[];
extern const Gfx lll_seg7_dl_archway_platform[];
extern const Gfx lll_seg7_dl_arrows_slope[];
extern const Gfx lll_seg7_dl_flamethrower[];
extern const Gfx lll_seg7_dl_hexagonal_mesh[];
extern const Gfx lll_seg7_dl_moving_octagonal_mesh_platform[];
extern const Gfx lll_seg7_dl_drawbridge_part[];
extern const Gfx lll_seg7_dl_rotating_block_fire_bars[];
extern const Gfx lll_seg7_dl_wooden_float_small[];
extern const Gfx lll_seg7_dl_wooden_float_large[];
extern const Gfx lll_seg7_dl_tumbling_bridge[];
extern const Gfx lll_seg7_dl_long_wooden_bridge[];
extern const Gfx lll_seg7_dl_rotating_hexagonal_ring[];
extern const Gfx lll_seg7_dl_sinking_rectangular_platform[];
extern const Gfx lll_seg7_dl_sinking_pyramids[];
extern const Gfx lll_seg7_dl_tilting_square_platform[];
extern const Gfx lll_seg7_dl_bowser_puzzle_piece_1[];
extern const Gfx lll_seg7_dl_bowser_puzzle_piece_2[];
extern const Gfx lll_seg7_dl_bowser_puzzle_piece_3[];
extern const Gfx lll_seg7_dl_bowser_puzzle_piece_4[];
extern const Gfx lll_seg7_dl_bowser_puzzle_piece_5[];
extern const Gfx lll_seg7_dl_bowser_puzzle_piece_6[];
extern const Gfx lll_seg7_dl_bowser_puzzle_piece_7[];
extern const Gfx lll_seg7_dl_bowser_puzzle_piece_8[];
extern const Gfx lll_seg7_dl_bowser_puzzle_piece_9[];
extern const Gfx lll_seg7_dl_bowser_puzzle_piece_10[];
extern const Gfx lll_seg7_dl_bowser_puzzle_piece_11[];
extern const Gfx lll_seg7_dl_bowser_puzzle_piece_12[];
extern const Gfx lll_seg7_dl_bowser_puzzle_piece_13[];
extern const Gfx lll_seg7_dl_bowser_puzzle_piece_14[];
extern const Gfx lll_seg7_dl_bowser_puzzle_piece_shadow[];
extern const Gfx lll_seg7_dl_sinking_rock_block[];
extern const Gfx lll_seg7_dl_rolling_log[];
extern const Collision   lll_seg7_area_1_collision[];
extern const MacroObject lll_seg7_area_1_macro_objs[];
extern const Collision   lll_seg7_collision_octagonal_moving_platform[];
extern const Collision   lll_seg7_collision_drawbridge[];
extern const Collision   lll_seg7_collision_rotating_fire_bars[];
extern const Collision   lll_seg7_collision_wood_piece[];
extern const Collision   lll_seg7_collision_tumbling_bridge[];
extern const Collision   lll_seg7_collision_rotating_hexagonal_ring[];
extern const Collision   lll_seg7_collision_slow_tilting_platform[];
extern const Collision   lll_seg7_collision_sinking_pyramids[];
extern const Collision   lll_seg7_collision_inverted_pyramid[];
extern const Collision   lll_seg7_collision_puzzle_piece[];
extern const Collision   lll_seg7_collision_floating_block[];
extern const Collision   lll_seg7_collision_rolling_log[];
extern const Collision   lll_seg7_collision_rotating_hexagonal_platform[];
extern const Gfx         lll_seg7_dl_area_2[];
extern const Gfx         lll_seg7_dl_volcano_decoration[];
extern const Gfx         lll_seg7_dl_volcano_upper_wall_shadow[];
extern const Gfx         lll_seg7_dl_volcano_exit[];
extern const Gfx         lll_seg7_dl_fire_spitter_hole[];
extern const Gfx         lll_seg7_dl_volcano_falling_trap[];
extern const Collision   lll_seg7_area_2_collision[];
extern const MacroObject lll_seg7_area_2_macro_objs[];
extern const Collision   lll_seg7_collision_falling_wall[];
extern const Trajectory  lll_seg7_trajectory_0702856C[];
extern const Trajectory  lll_seg7_trajectory_07028660[];
extern Movtex                            lll_movtex_tris_lava_floor[];
extern const Gfx                         lll_dl_lava_floor[];
extern const struct MovtexQuadCollection lll_movtex_volcano_floor_lava[];
extern Movtex                            lll_movtex_tris_lavafall_volcano[];
extern const Gfx                         lll_dl_lavafall_volcano[];

// script
extern const LevelScript level_lll_entry[];

#endif
