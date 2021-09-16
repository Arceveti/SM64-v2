// 0x0E0005E8
const GeoLayout hmc_geo_room_entrance[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_entrance_surfaces),
      GEO_DISPLAY_LIST(LAYER_ALPHA,          hmc_seg7_dl_entrance_hanging_grass),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,    hmc_seg7_dl_entrance_lanterns_glow),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_entrance_lanterns),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000618
const GeoLayout hmc_geo_room_red_coins[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_red_coins_room_surfaces),
      GEO_DISPLAY_LIST(LAYER_ALPHA,          hmc_seg7_dl_red_coins_room_alpha),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,    hmc_seg7_dl_red_coins_room_lanterns_glow),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_red_coins_room_lanterns),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,    hmc_seg7_dl_red_coins_room_flame_glow),
      GEO_DISPLAY_LIST(LAYER_OPAQUE_DECAL,   hmc_seg7_dl_grass_floor_for_red_coins_star),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000658
const GeoLayout hmc_geo_room_toxic_maze[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_toxic_maze_surfaces),
      GEO_DISPLAY_LIST(LAYER_ALPHA,          hmc_seg7_dl_toxic_maze_hanging_grass),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,    hmc_seg7_dl_toxic_maze_lanterns_glow),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,    hmc_seg7_dl_toxic_maze_wall_flames),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_toxic_maze_map),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,    hmc_seg7_dl_toxic_maze_toxic_drip),
      GEO_ASM(                         0, geo_movtex_pause_control),
      GEO_ASM(HMC_MOVTEX_TOXIC_MAZE_MIST, geo_movtex_draw_water_regions),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E0006A8
const GeoLayout hmc_geo_room_black_hole[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_black_hole_room_surfaces),
      GEO_DISPLAY_LIST(LAYER_ALPHA,          hmc_seg7_dl_black_hole_room_alpha),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,    hmc_seg7_dl_black_hole_room_lanterns_glow),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_black_hole_room_lanterns),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,    hmc_seg7_dl_rolling_rocks_arrow),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E0006E0
const GeoLayout hmc_geo_room_maze_exit[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_maze_exit_surfaces),
      GEO_DISPLAY_LIST(LAYER_ALPHA,          hmc_seg7_dl_maze_exit_meshes),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000700
const GeoLayout hmc_geo_room_lake[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_lake_surfaces),
      GEO_DISPLAY_LIST(LAYER_ALPHA,          hmc_seg7_dl_lake_alpha),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,    hmc_seg7_dl_lake_sky_lights),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,    hmc_seg7_dl_lake_lanterns_glow),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_lake_lanterns),
      GEO_ASM(                           0, geo_movtex_pause_control),
      GEO_ASM(HMC_MOVTEX_DORRIE_POOL_WATER, geo_movtex_draw_water_regions),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000748
const GeoLayout hmc_geo_room_cotmc[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_room_cotmc),
      GEO_ASM(                0, geo_painting_update),
      GEO_ASM(PAINTING_ID(0, 0), geo_painting_draw),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000770
const GeoLayout hmc_geo_room_metal_mario_can_move[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_metal_mario_can_move_opaque),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,    hmc_seg7_dl_metal_mario_can_move_lanterns_glow),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_metal_mario_can_move_lanterns),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000798
const GeoLayout hmc_geo_door_room_entrance_and_red_coins[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_entrance_surfaces),
      GEO_DISPLAY_LIST(LAYER_ALPHA,          hmc_seg7_dl_entrance_hanging_grass),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,    hmc_seg7_dl_entrance_lanterns_glow),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_entrance_lanterns),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_red_coins_room_surfaces),
      GEO_DISPLAY_LIST(LAYER_ALPHA,          hmc_seg7_dl_red_coins_room_alpha),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,    hmc_seg7_dl_red_coins_room_lanterns_glow),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_red_coins_room_lanterns),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,    hmc_seg7_dl_red_coins_room_flame_glow),
      GEO_DISPLAY_LIST(LAYER_OPAQUE_DECAL,   hmc_seg7_dl_grass_floor_for_red_coins_star),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E0007F8
const GeoLayout hmc_geo_door_room_entrance_and_black_hole[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_entrance_surfaces),
      GEO_DISPLAY_LIST(LAYER_ALPHA,          hmc_seg7_dl_entrance_hanging_grass),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,    hmc_seg7_dl_entrance_lanterns_glow),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_entrance_lanterns),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_black_hole_room_surfaces),
      GEO_DISPLAY_LIST(LAYER_ALPHA,          hmc_seg7_dl_black_hole_room_alpha),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,    hmc_seg7_dl_black_hole_room_lanterns_glow),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_black_hole_room_lanterns),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,    hmc_seg7_dl_rolling_rocks_arrow),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000850
const GeoLayout hmc_geo_door_room_red_coins_and_toxic_maze[] = { //! doesn't include a certain door
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_red_coins_room_surfaces),
      GEO_DISPLAY_LIST(LAYER_ALPHA,          hmc_seg7_dl_red_coins_room_alpha),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,    hmc_seg7_dl_red_coins_room_lanterns_glow),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_red_coins_room_lanterns),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,    hmc_seg7_dl_red_coins_room_flame_glow),
      GEO_DISPLAY_LIST(LAYER_OPAQUE_DECAL,   hmc_seg7_dl_grass_floor_for_red_coins_star),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_toxic_maze_surfaces),
      GEO_DISPLAY_LIST(LAYER_ALPHA,          hmc_seg7_dl_toxic_maze_hanging_grass),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,    hmc_seg7_dl_toxic_maze_lanterns_glow),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,    hmc_seg7_dl_toxic_maze_wall_flames),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_toxic_maze_map),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,    hmc_seg7_dl_toxic_maze_toxic_drip),
      GEO_ASM(                         0, geo_movtex_pause_control     ),
      GEO_ASM(HMC_MOVTEX_TOXIC_MAZE_MIST, geo_movtex_draw_water_regions),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E0008D0
const GeoLayout hmc_geo_door_room_red_coins_and_black_hole[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_red_coins_room_surfaces),
      GEO_DISPLAY_LIST(LAYER_ALPHA,          hmc_seg7_dl_red_coins_room_alpha),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,    hmc_seg7_dl_red_coins_room_lanterns_glow),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_red_coins_room_lanterns),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,    hmc_seg7_dl_red_coins_room_flame_glow),
      GEO_DISPLAY_LIST(LAYER_OPAQUE_DECAL,   hmc_seg7_dl_grass_floor_for_red_coins_star),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_black_hole_room_surfaces),
      GEO_DISPLAY_LIST(LAYER_ALPHA,          hmc_seg7_dl_black_hole_room_alpha),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,    hmc_seg7_dl_black_hole_room_lanterns_glow),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_black_hole_room_lanterns),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,    hmc_seg7_dl_rolling_rocks_arrow),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000938
const GeoLayout hmc_geo_door_room_toxic_maze_and_maze_exit[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_toxic_maze_surfaces),
      GEO_DISPLAY_LIST(LAYER_ALPHA,          hmc_seg7_dl_toxic_maze_hanging_grass),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,    hmc_seg7_dl_toxic_maze_lanterns_glow),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,    hmc_seg7_dl_toxic_maze_wall_flames),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_toxic_maze_map),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,    hmc_seg7_dl_toxic_maze_toxic_drip),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_maze_exit_surfaces),
      GEO_DISPLAY_LIST(LAYER_ALPHA,          hmc_seg7_dl_maze_exit_meshes),
      GEO_ASM(                         0, geo_movtex_pause_control     ),
      GEO_ASM(HMC_MOVTEX_TOXIC_MAZE_MIST, geo_movtex_draw_water_regions),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000998
const GeoLayout hmc_geo_door_room_toxic_maze_and_lake[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_toxic_maze_surfaces),
      GEO_DISPLAY_LIST(LAYER_ALPHA,          hmc_seg7_dl_toxic_maze_hanging_grass),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,    hmc_seg7_dl_toxic_maze_lanterns_glow),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,    hmc_seg7_dl_toxic_maze_wall_flames),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_toxic_maze_map),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,    hmc_seg7_dl_toxic_maze_toxic_drip),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_lake_surfaces),
      GEO_DISPLAY_LIST(LAYER_ALPHA,          hmc_seg7_dl_lake_alpha),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,    hmc_seg7_dl_lake_sky_lights),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,    hmc_seg7_dl_lake_lanterns_glow),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_lake_lanterns),
      GEO_ASM(                           0, geo_movtex_pause_control     ),
      GEO_ASM(HMC_MOVTEX_DORRIE_POOL_WATER, geo_movtex_draw_water_regions),
      GEO_ASM(HMC_MOVTEX_TOXIC_MAZE_MIST,   geo_movtex_draw_water_regions),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000A18
const GeoLayout hmc_geo_door_room_black_hole_and_lake[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_black_hole_room_surfaces),
      GEO_DISPLAY_LIST(LAYER_ALPHA,          hmc_seg7_dl_black_hole_room_alpha),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,    hmc_seg7_dl_black_hole_room_lanterns_glow),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_black_hole_room_lanterns),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,    hmc_seg7_dl_rolling_rocks_arrow),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_lake_surfaces),
      GEO_DISPLAY_LIST(LAYER_ALPHA,          hmc_seg7_dl_lake_alpha),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,    hmc_seg7_dl_lake_sky_lights),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,    hmc_seg7_dl_lake_lanterns_glow),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_lake_lanterns),
      GEO_ASM(                           0, geo_movtex_pause_control     ),
      GEO_ASM(HMC_MOVTEX_DORRIE_POOL_WATER, geo_movtex_draw_water_regions),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000A88
const GeoLayout hmc_geo_door_room_lake_and_cotmc[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_lake_surfaces),
      GEO_DISPLAY_LIST(LAYER_ALPHA,          hmc_seg7_dl_lake_alpha),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,    hmc_seg7_dl_lake_sky_lights),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,    hmc_seg7_dl_lake_lanterns_glow),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_lake_lanterns),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_room_cotmc),
      GEO_ASM(                           0, geo_painting_update),
      GEO_ASM(           PAINTING_ID(0, 0), geo_painting_draw),
      GEO_ASM(                           0, geo_movtex_pause_control     ),
      GEO_ASM(HMC_MOVTEX_DORRIE_POOL_WATER, geo_movtex_draw_water_regions),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000AE8
const GeoLayout hmc_geo_door_room_lake_and_metal_mario_can_move[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_lake_surfaces),
      GEO_DISPLAY_LIST(LAYER_ALPHA,          hmc_seg7_dl_lake_alpha),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,    hmc_seg7_dl_lake_sky_lights),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,    hmc_seg7_dl_lake_lanterns_glow),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_lake_lanterns),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_metal_mario_can_move_opaque),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,    hmc_seg7_dl_metal_mario_can_move_lanterns_glow),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,         hmc_seg7_dl_metal_mario_can_move_lanterns),
      GEO_ASM(                           0, geo_movtex_pause_control     ),
      GEO_ASM(HMC_MOVTEX_DORRIE_POOL_WATER, geo_movtex_draw_water_regions),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000B48
const GeoLayout hmc_geo_door_room_black_hole_and_maze_exit[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,      hmc_seg7_dl_black_hole_room_surfaces),
      GEO_DISPLAY_LIST(LAYER_ALPHA,       hmc_seg7_dl_black_hole_room_alpha),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, hmc_seg7_dl_black_hole_room_lanterns_glow),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,      hmc_seg7_dl_black_hole_room_lanterns),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, hmc_seg7_dl_rolling_rocks_arrow),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,      hmc_seg7_dl_maze_exit_surfaces),
      GEO_DISPLAY_LIST(LAYER_ALPHA,       hmc_seg7_dl_maze_exit_meshes),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000B90
const GeoLayout hmc_geo_area_1[] = {
   GEO_NODE_SCREEN_AREA(10, (SCREEN_WIDTH/2), (SCREEN_HEIGHT/2), (SCREEN_WIDTH/2), (SCREEN_HEIGHT/2)),
   GEO_OPEN_NODE(),
      GEO_ZBUFFER(0),
      GEO_OPEN_NODE(),
         GEO_NODE_ORTHO(100),
         GEO_OPEN_NODE(),
            GEO_BACKGROUND_COLOR(0x0001),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),
      GEO_ZBUFFER(1),
      GEO_OPEN_NODE(),
         GEO_CAMERA_FRUSTUM_WITH_FUNC(45, 100, 12800, geo_camera_fov),
         GEO_OPEN_NODE(),
            GEO_CAMERA(16, 0, 2000, 6000, 0, 0, 0, geo_camera_main),
            GEO_OPEN_NODE(),
               GEO_SWITCH_CASE(18, geo_switch_room),
               GEO_OPEN_NODE(),
                  GEO_BRANCH(1, hmc_geo_room_entrance                          ), // 0x0E0005E8 //  1
                  GEO_BRANCH(1, hmc_geo_room_red_coins                         ), // 0x0E000618 //  2
                  GEO_BRANCH(1, hmc_geo_room_toxic_maze                        ), // 0x0E000658 //  3
                  GEO_BRANCH(1, hmc_geo_room_black_hole                        ), // 0x0E0006A8 //  4
                  GEO_BRANCH(1, hmc_geo_room_maze_exit                         ), // 0x0E0006E0 //  5
                  GEO_BRANCH(1, hmc_geo_room_lake                              ), // 0x0E000700 //  6
                  GEO_BRANCH(1, hmc_geo_room_cotmc                             ), // 0x0E000748 //  7
                  GEO_BRANCH(1, hmc_geo_room_metal_mario_can_move              ), // 0x0E000770 //  8
                  GEO_BRANCH(1, hmc_geo_door_room_entrance_and_red_coins       ), // 0x0E000798 //  9
                  GEO_BRANCH(1, hmc_geo_door_room_entrance_and_black_hole      ), // 0x0E0007F8 // 10
                  GEO_BRANCH(1, hmc_geo_door_room_red_coins_and_toxic_maze     ), // 0x0E000850 // 11
                  GEO_BRANCH(1, hmc_geo_door_room_red_coins_and_black_hole     ), // 0x0E0008D0 // 12
                  GEO_BRANCH(1, hmc_geo_door_room_toxic_maze_and_maze_exit     ), // 0x0E000938 // 13
                  GEO_BRANCH(1, hmc_geo_door_room_toxic_maze_and_lake          ), // 0x0E000998 // 14
                  GEO_BRANCH(1, hmc_geo_door_room_black_hole_and_lake          ), // 0x0E000A18 // 15
                  GEO_BRANCH(1, hmc_geo_door_room_lake_and_cotmc               ), // 0x0E000A88 // 16
                  GEO_BRANCH(1, hmc_geo_door_room_lake_and_metal_mario_can_move), // 0x0E000AE8 // 17
                  GEO_BRANCH(1, hmc_geo_door_room_black_hole_and_maze_exit     ), // 0x0E000B48 // 18
               GEO_CLOSE_NODE(),
               GEO_RENDER_OBJ(),
               GEO_ASM(0, geo_envfx_main),
            GEO_CLOSE_NODE(),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
