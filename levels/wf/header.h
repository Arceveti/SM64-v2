#ifndef WF_HEADER_H
#define WF_HEADER_H

#include "types.h"
#include "game/moving_texture.h"

// geo
extern const GeoLayout wf_geo_small_rocky_staircase[];
extern const GeoLayout wf_geo_large_staircase[];
extern const GeoLayout wf_geo_platform_between_sliding_platforms[];
extern const GeoLayout wf_geo_fences[];
extern const GeoLayout wf_geo_floating_brick_platform[];
extern const GeoLayout wf_geo_tower[];
extern const GeoLayout wf_geo_bullet_bill_cannon[];
extern const GeoLayout wf_geo_platform_with_wooden_bridge[];
extern const GeoLayout wf_geo_grass_with_tree[];
extern const GeoLayout wf_geo_grass_with_flowers[];
extern const GeoLayout wf_geo_rotating_grass_platform[];
extern const GeoLayout wf_geo_platforms_with_pole[];
extern const GeoLayout wf_geo_slope_under_pole_platforms[];
extern const GeoLayout wf_geo_small_bomp[];
extern const GeoLayout wf_geo_large_bomp[];
extern const GeoLayout wf_geo_rotating_wooden_platform[];
extern const GeoLayout wf_geo_sliding_platform[];
extern const GeoLayout wf_geo_tumbling_bridge_near[];
extern const GeoLayout wf_geo_tumbling_bridge_far[];
extern const GeoLayout wf_geo_giant_pole[];
extern const GeoLayout wf_geo_beta_extending_platform[];
extern const GeoLayout wf_geo_square_platform[];
extern const GeoLayout wf_geo_square_platform_unused[];
extern const GeoLayout wf_geo_square_platform_elevator[];
extern const GeoLayout wf_geo_breakable_wall_right[];
extern const GeoLayout wf_geo_breakable_wall_left[];
extern const GeoLayout wf_geo_kickable_board_standing[];
extern const GeoLayout wf_geo_kickable_board_fallen[];
extern const GeoLayout wf_geo_tower_door[];
extern const GeoLayout wf_geo_area_1[];

// leveldata
extern const Gfx wf_seg7_dl_area_1[];
extern const Gfx wf_seg7_dl_piranha_plant_pots[];
extern const Gfx wf_seg7_dl_floor_arrows[];
extern const Gfx wf_seg7_dl_wall_arrows[];
extern const Gfx wf_seg7_dl_small_rocky_staircase_near[];
extern const Gfx wf_seg7_dl_small_rocky_staircase_far[];
extern const Gfx wf_seg7_dl_large_staircase_near[];
extern const Gfx wf_seg7_dl_large_staircase_far[];
extern const Gfx wf_seg7_dl_platform_between_sliding_platforms[];
extern const Gfx wf_seg7_dl_fences[];
extern const Gfx wf_seg7_dl_floating_brick_platform[];
extern const Gfx wf_seg7_dl_tower_near[];
extern const Gfx wf_seg7_dl_tower_far[];
extern const Gfx wf_seg7_dl_bullet_bill_cannon[];
extern const Gfx wf_seg7_dl_platform_with_wooden_bridge[];
extern const Gfx wf_seg7_dl_giant_pole[];
extern const Gfx wf_seg7_dl_grass_with_tree_near[];
extern const Gfx wf_seg7_dl_grass_with_tree_far[];
extern const Gfx wf_seg7_dl_tree_shadow[];
extern const Gfx wf_seg7_dl_grass_with_flowers[];
extern const Gfx wf_seg7_dl_rotating_grass_platform[];
extern const Gfx wf_seg7_dl_platforms_with_pole[];
extern const Gfx wf_seg7_dl_small_bomp_near[];
extern const Gfx wf_seg7_dl_small_bomp_far[];
extern const Gfx wf_seg7_dl_large_bomp[];
extern const Gfx wf_seg7_dl_tumbling_bridge_near[];
extern const Gfx wf_seg7_dl_tumbling_bridge_far[];
extern const Gfx wf_seg7_dl_rotating_wooden_platform_near[];
extern const Gfx wf_seg7_dl_rotating_wooden_platform_far[];
extern const Gfx wf_seg7_dl_sliding_platform[];
extern const Gfx wf_seg7_dl_beta_extending_platform[];
extern const Gfx wf_seg7_dl_extending_platform[];
extern const Gfx wf_seg7_dl_breakable_wall_right[];
extern const Gfx wf_seg7_dl_breakable_wall_left[];
extern const Gfx wf_seg7_dl_kickable_board[];
extern const Gfx wf_seg7_dl_kickable_board_shadow[];
extern const Gfx wf_seg7_dl_tower_door[];
extern const Collision wf_seg7_collision_small_bomp[];
extern const Collision wf_seg7_collision_large_bomp[];
extern const Collision wf_seg7_collision_clocklike_rotation[];
extern const Collision wf_seg7_collision_sliding_brick_platform[];
extern const Collision wf_seg7_collision_tumbling_bridge[];
extern const Collision wf_seg7_collision_trapezoid[];
extern const Collision wf_seg7_collision_platform[];
extern const Collision wf_seg7_collision_breakable_wall[];
extern const Collision wf_seg7_collision_breakable_wall_2[];
extern const Collision wf_seg7_collision_kickable_board[];
extern const Collision wf_seg7_collision_tower_door[];
extern const Collision wf_seg7_collision_rotating_platform[];
extern const Collision wf_seg7_collision_tower[];
extern const Collision wf_seg7_collision_bullet_bill_cannon[];
extern const Collision wf_seg7_collision_070102D8[];
extern const MacroObject wf_seg7_macro_objs[];
extern const struct MovtexQuadCollection wf_movtex_water[];

// script
extern const LevelScript level_wf_entry[];

#endif
