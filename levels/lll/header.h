#ifndef LLL_HEADER_H
#define LLL_HEADER_H

#include "types.h"
#include "game/moving_texture.h"

// geo
extern const GeoLayout lll_geo_0009E0[];
extern const GeoLayout lll_geo_0009F8[];
extern const GeoLayout lll_geo_000A10[];
extern const GeoLayout lll_geo_000A28[];
extern const GeoLayout lll_geo_000A40[];
extern const GeoLayout lll_geo_000A60[];
extern const GeoLayout lll_geo_rotating_hexagonal_platform[];
extern const GeoLayout lll_geo_000A90[];
extern const GeoLayout lll_geo_000AA8[];
extern const GeoLayout lll_geo_000AC0[];
extern const GeoLayout lll_geo_000AD8[];
extern const GeoLayout lll_geo_hexagonal_mesh[];
extern const GeoLayout lll_geo_moving_octagonal_mesh_platform[];
extern const GeoLayout lll_geo_drawbridge_part[];
extern const GeoLayout lll_geo_rotating_block_fire_bars[];
extern const GeoLayout lll_geo_wooden_float_small[];
extern const GeoLayout lll_geo_wooden_float_large[];
extern const GeoLayout lll_geo_collapsing_wooden_platform[];
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
extern const GeoLayout lll_geo_000E00[];
extern const GeoLayout lll_geo_volcano_falling_trap[];
extern const GeoLayout lll_geo_000EC0[];

// leveldata
extern const Gfx lll_seg7_dl_070134E0[];
extern const Gfx lll_seg7_dl_070137C0[];
extern const Gfx lll_seg7_dl_070138F8[];
extern const Gfx lll_seg7_dl_07013D28[];
extern const Gfx lll_seg7_dl_07014788[];
extern const Gfx lll_seg7_dl_07014BD8[];
extern const Gfx lll_seg7_dl_07015458[];
extern const Gfx lll_seg7_dl_07015C88[];
extern const Gfx lll_seg7_dl_07015E20[];
extern const Gfx lll_seg7_dl_07016250[];
extern const Gfx lll_seg7_dl_070165C8[];
extern const Gfx lll_seg7_dl_07016B00[];
extern const Gfx lll_seg7_dl_070174E0[];
extern const Gfx lll_seg7_dl_070178A8[];
extern const Gfx lll_seg7_dl_07017B50[];
extern const Gfx lll_seg7_dl_07017F40[];
extern const Gfx lll_seg7_dl_07018380[];
extern const Gfx lll_seg7_dl_07018680[];
extern const Gfx lll_seg7_dl_07018A30[];
extern const Gfx lll_seg7_dl_07018C90[];
extern const Gfx lll_seg7_dl_07018EF8[];
extern const Gfx lll_seg7_dl_07019160[];
extern const Gfx lll_seg7_dl_070193E0[];
extern const Gfx lll_seg7_dl_07019A08[];
extern const Gfx lll_seg7_dl_07019C08[];
extern const Gfx lll_seg7_dl_0701A010[];
extern const Gfx lll_seg7_dl_0701A1F0[];
extern const Gfx lll_seg7_dl_0701A388[];
extern const Gfx lll_seg7_dl_0701A3B8[];
extern const Gfx lll_seg7_dl_0701A3E8[];
extern const Gfx lll_seg7_dl_0701A418[];
extern const Gfx lll_seg7_dl_0701A448[];
extern const Gfx lll_seg7_dl_0701A478[];
extern const Gfx lll_seg7_dl_0701A4A8[];
extern const Gfx lll_seg7_dl_0701A4D8[];
extern const Gfx lll_seg7_dl_0701A508[];
extern const Gfx lll_seg7_dl_0701A538[];
extern const Gfx lll_seg7_dl_0701A568[];
extern const Gfx lll_seg7_dl_0701A598[];
extern const Gfx lll_seg7_dl_0701A5C8[];
extern const Gfx lll_seg7_dl_0701A5F8[];
extern const Gfx lll_seg7_dl_0701A628[];
extern const Gfx lll_seg7_dl_0701A878[];
extern const Gfx lll_seg7_dl_0701AD70[];
extern const Collision lll_seg7_area_1_collision[];
extern const MacroObject lll_seg7_area_1_macro_objs[];
extern const Collision lll_seg7_collision_octagonal_moving_platform[];
extern const Collision lll_seg7_collision_drawbridge[];
extern const Collision lll_seg7_collision_rotating_fire_bars[];
extern const Collision lll_seg7_collision_wood_piece[];
extern const Collision lll_seg7_collision_tumbling_bridge[];
extern const Collision lll_seg7_collision_rotating_platform[];
extern const Collision lll_seg7_collision_slow_tilting_platform[];
extern const Collision lll_seg7_collision_sinking_pyramids[];
extern const Collision lll_seg7_collision_inverted_pyramid[];
extern const Collision lll_seg7_collision_puzzle_piece[];
extern const Collision lll_seg7_collision_floating_block[];
extern const Collision lll_seg7_collision_pitoune[];
extern const Collision lll_seg7_collision_rotating_hexagonal_platform[];
extern const Collision lll_seg7_collision_hexagonal_mesh_platform[];
extern const Gfx lll_seg7_dl_070235C8[];
extern const Gfx lll_seg7_dl_07024C18[];
extern const Gfx lll_seg7_dl_070255D8[];
extern const Gfx lll_seg7_dl_07025A48[];
extern const Gfx lll_seg7_dl_07025BD8[];
extern const Gfx lll_seg7_dl_07025EC0[];
extern const Collision lll_seg7_area_2_collision[];
extern const MacroObject lll_seg7_area_2_macro_objs[];
extern const Collision lll_seg7_collision_falling_wall[];
extern const Trajectory lll_seg7_trajectory_0702856C[];
extern const Trajectory lll_seg7_trajectory_07028660[];
extern Movtex lll_movtex_tris_lava_floor[];
extern const Gfx lll_dl_lava_floor[];
extern const struct MovtexQuadCollection lll_movtex_volcano_floor_lava[];
extern Movtex lll_movtex_tris_lavafall_volcano[];
extern const Gfx lll_dl_lavafall_volcano[];

// script
extern const LevelScript level_lll_entry[];

#endif
