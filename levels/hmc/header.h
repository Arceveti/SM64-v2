#ifndef HMC_HEADER_H
#define HMC_HEADER_H

#include "types.h"
#include "game/moving_texture.h"

// geo
extern const GeoLayout hmc_geo_grill_door[];
extern const GeoLayout hmc_geo_rolling_rock[];
extern const GeoLayout hmc_geo_rolling_rock_fragment_large[];
extern const GeoLayout hmc_geo_rolling_rock_fragment_small[];
extern const GeoLayout hmc_geo_controllable_arrow_platform[];
extern const GeoLayout hmc_geo_controllable_arrow_platform_button[];
extern const GeoLayout hmc_geo_elevator_platform[];
extern const GeoLayout hmc_geo_room_entrance[];
extern const GeoLayout hmc_geo_room_red_coins[];
extern const GeoLayout hmc_geo_room_toxic_maze[];
extern const GeoLayout hmc_geo_room_black_hole[];
extern const GeoLayout hmc_geo_room_maze_exit[];
extern const GeoLayout hmc_geo_room_lake[];
extern const GeoLayout hmc_geo_room_cotmc[];
extern const GeoLayout hmc_geo_room_metal_mario_can_move[];
extern const GeoLayout hmc_geo_door_room_entrance_and_red_coins[];
extern const GeoLayout hmc_geo_door_room_entrance_and_black_hole[];
extern const GeoLayout hmc_geo_door_room_red_coins_and_toxic_maze[];
extern const GeoLayout hmc_geo_door_room_red_coins_and_black_hole[];
extern const GeoLayout hmc_geo_door_room_toxic_maze_and_maze_exit[];
extern const GeoLayout hmc_geo_door_room_toxic_maze_and_lake[];
extern const GeoLayout hmc_geo_door_room_black_hole_and_lake[];
extern const GeoLayout hmc_geo_door_room_lake_and_cotmc[];
extern const GeoLayout hmc_geo_door_room_lake_and_metal_mario_can_move[];
extern const GeoLayout hmc_geo_door_room_black_hole_and_maze_exit[];
extern const GeoLayout hmc_geo_area_1[];

// leveldata
extern const Gfx hmc_seg7_dl_entrance_surfaces[];
extern const Gfx hmc_seg7_dl_entrance_hanging_grass[];
extern const Gfx hmc_seg7_dl_entrance_lanterns_glow[];
extern const Gfx hmc_seg7_dl_entrance_lanterns[];
extern const Gfx hmc_seg7_dl_red_coins_room_surfaces[];
extern const Gfx hmc_seg7_dl_red_coins_room_alpha[];
extern const Gfx hmc_seg7_dl_red_coins_room_lanterns_glow[];
extern const Gfx hmc_seg7_dl_red_coins_room_lanterns[];
extern const Gfx hmc_seg7_dl_red_coins_room_flame_glow[];
extern const Gfx hmc_seg7_dl_grass_floor_for_red_coins_star[];
extern const Gfx hmc_seg7_dl_toxic_maze_surfaces[];
extern const Gfx hmc_seg7_dl_toxic_maze_hanging_grass[];
extern const Gfx hmc_seg7_dl_toxic_maze_lanterns_glow[];
extern const Gfx hmc_seg7_dl_toxic_maze_wall_flames[];
extern const Gfx hmc_seg7_dl_toxic_maze_map[];
extern const Gfx hmc_seg7_dl_toxic_maze_toxic_drip[];
extern const Gfx hmc_seg7_dl_black_hole_room_surfaces[];
extern const Gfx hmc_seg7_dl_black_hole_room_alpha[];
extern const Gfx hmc_seg7_dl_black_hole_room_lanterns_glow[];
extern const Gfx hmc_seg7_dl_black_hole_room_lanterns[];
extern const Gfx hmc_seg7_dl_rolling_rocks_arrow[];
extern const Gfx hmc_seg7_dl_maze_exit_surfaces[];
extern const Gfx hmc_seg7_dl_maze_exit_meshes[];
extern const Gfx hmc_seg7_dl_lake_surfaces[];
extern const Gfx hmc_seg7_dl_lake_alpha[];
extern const Gfx hmc_seg7_dl_lake_sky_lights[];
extern const Gfx hmc_seg7_dl_lake_lanterns_glow[];
extern const Gfx hmc_seg7_dl_lake_lanterns[];
extern const Gfx hmc_seg7_dl_grill_door[];
extern const Gfx hmc_seg7_dl_room_cotmc[];
extern const Gfx hmc_seg7_dl_metal_mario_can_move_opaque[];
extern const Gfx hmc_seg7_dl_metal_mario_can_move_lanterns_glow[];
extern const Gfx hmc_seg7_dl_metal_mario_can_move_lanterns[];
extern const Gfx hmc_seg7_dl_elevator_platform[];
extern const Gfx hmc_seg7_dl_controllable_arrow_platform[];
extern const Gfx hmc_seg7_dl_controllable_arrow_platform_button[];
extern const Gfx hmc_seg7_dl_07023BC8[];
extern const Gfx hmc_seg7_dl_07023E10[];
extern const Gfx hmc_seg7_dl_07024110[];
extern const Texture *const hmc_seg7_painting_textures_cotmc[];
extern struct Painting cotmc_painting;
extern const Collision hmc_seg7_collision_level[];
extern const MacroObject hmc_seg7_macro_objs[];
extern const RoomData hmc_seg7_rooms[];
extern const Collision hmc_seg7_collision_elevator[];
extern const Collision hmc_seg7_collision_grill_door[];
extern const Collision hmc_seg7_collision_controllable_platform[];
extern const Collision hmc_seg7_collision_controllable_platform_sub[];
extern const Trajectory hmc_seg7_trajectory_checkerboard_platform[];
extern const struct MovtexQuadCollection hmc_movtex_dorrie_pool_water[];
extern const struct MovtexQuadCollection hmc_movtex_toxic_maze_mist[];

// script
extern const LevelScript level_hmc_entry[];

#endif
