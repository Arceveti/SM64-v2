// 0x0E000670
const GeoLayout geo_bbh_room_foyer[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,      bbh_seg7_dl_foyer_surfaces),
      GEO_DISPLAY_LIST(LAYER_ALPHA,       bbh_seg7_dl_foyer_railings),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,      bbh_seg7_dl_foyer_windows_and_boo_painting),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, bbh_seg7_dl_foyer_lamps_glow),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,      bbh_seg7_dl_foyer_lamps),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, bbh_seg7_dl_foyer_window_light),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E0006B0
const GeoLayout geo_bbh_room_study[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,      bbh_seg7_dl_study_surfaces),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,      bbh_seg7_dl_study_windows),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, bbh_seg7_dl_study_lamps_glow),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,      bbh_seg7_dl_study_lamps),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, bbh_seg7_dl_study_window_light),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E0006E8
const GeoLayout geo_bbh_room_piano[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,      bbh_seg7_dl_piano_room_surfaces),
      GEO_DISPLAY_LIST(LAYER_ALPHA,       bbh_seg7_dl_piano_room_railings),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,      bbh_seg7_dl_piano_room_windows),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, bbh_seg7_dl_piano_room_window_light),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,      bbh_seg7_dl_library_surfaces),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,      bbh_seg7_dl_library_window_wood),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, bbh_seg7_dl_library_window_glass),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000730
const GeoLayout geo_bbh_room_bridge[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,      bbh_seg7_dl_bridge_room_surfaces),
      GEO_DISPLAY_LIST(LAYER_ALPHA,       bbh_seg7_dl_bridge_room_railing),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000750
const GeoLayout geo_bbh_room_back_room[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,      bbh_seg7_dl_back_room_surfaces),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000768
const GeoLayout geo_bbh_room_library[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,      bbh_seg7_dl_piano_room_surfaces),
      GEO_DISPLAY_LIST(LAYER_ALPHA,       bbh_seg7_dl_piano_room_railings),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,      bbh_seg7_dl_piano_room_windows),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, bbh_seg7_dl_piano_room_window_light),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,      bbh_seg7_dl_library_surfaces),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,      bbh_seg7_dl_library_window_wood),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, bbh_seg7_dl_library_window_glass),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E0007B0
const GeoLayout geo_bbh_room_coffins[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,      bbh_seg7_dl_coffins_room_surfaces),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, bbh_seg7_dl_coffins_room_flames_glow),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E0007D0
const GeoLayout geo_bbh_room_mesh_room[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,      bbh_seg7_dl_mesh_room_surfaces),
      GEO_DISPLAY_LIST(LAYER_ALPHA,       bbh_seg7_dl_mesh_room_meshes),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, bbh_seg7_dl_mesh_room_lights_glow),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,      bbh_seg7_dl_mesh_room_lamps),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000800
const GeoLayout geo_bbh_room_attic[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,      bbh_seg7_dl_attic_surfaces),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,      bbh_seg7_dl_attic_windows),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, bbh_seg7_dl_attic_window_light),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000828
const GeoLayout geo_bbh_room_merry_go_round[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,      bbh_seg7_merry_go_round_room_surfaces),
      GEO_DISPLAY_LIST(LAYER_ALPHA,       bbh_seg7_merry_go_round_room_meshes),
      GEO_ASM(                                       0, geo_movtex_pause_control     ),
      GEO_ASM(BBH_MOVTEX_MERRY_GO_ROUND_WATER_ENTRANCE, geo_movtex_draw_water_regions),
      GEO_ASM(BBH_MOVTEX_MERRY_GO_ROUND_WATER_SIDE,     geo_movtex_draw_water_regions),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000860
const GeoLayout geo_bbh_room_basement_hallway[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,      bbh_seg7_dl_basement_hallway),
      GEO_ASM(                                       0, geo_movtex_pause_control     ),
      GEO_ASM(BBH_MOVTEX_MERRY_GO_ROUND_WATER_ENTRANCE, geo_movtex_draw_water_regions),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000888
const GeoLayout geo_bbh_room_shed[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,      bbh_seg7_dl_shed_with_elevator),
      GEO_ASM(                                       0, geo_movtex_pause_control     ),
      GEO_ASM(BBH_MOVTEX_MERRY_GO_ROUND_WATER_ENTRANCE, geo_movtex_draw_water_regions),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E0008B0
const GeoLayout geo_bbh_room_outside[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,      bbh_seg7_dl_outside_surfaces),
      GEO_DISPLAY_LIST(LAYER_ALPHA,       bbh_seg7_dl_outside_cage_walls),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,      bbh_seg7_dl_outside_windows),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, bbh_seg7_dl_outside_flames_glow),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,      bbh_seg7_dl_outside_lantern),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E0008E8
const GeoLayout geo_bbh_door_room_foyer_and_study[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_BRANCH(1, geo_bbh_room_foyer),
      GEO_BRANCH(1, geo_bbh_room_study),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000950
const GeoLayout geo_bbh_door_room_foyer_and_piano[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_BRANCH(1, geo_bbh_room_foyer),
      GEO_BRANCH(1, geo_bbh_room_piano),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E0009C8
const GeoLayout geo_bbh_door_room_foyer_and_bridge[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_BRANCH(1, geo_bbh_room_foyer),
      GEO_BRANCH(1, geo_bbh_room_bridge),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000A18
const GeoLayout geo_bbh_door_room_foyer_and_back_room[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_BRANCH(1, geo_bbh_room_foyer),
      GEO_BRANCH(1, geo_bbh_room_back_room),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000A60
const GeoLayout geo_bbh_door_room_foyer_and_library[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_BRANCH(1, geo_bbh_room_foyer),
      GEO_BRANCH(1, geo_bbh_room_library),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000AD8
const GeoLayout geo_bbh_door_room_foyer_and_coffins[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_BRANCH(1, geo_bbh_room_foyer),
      GEO_BRANCH(1, geo_bbh_room_coffins),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000B28
const GeoLayout geo_bbh_door_room_foyer_and_mesh_room[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_BRANCH(1, geo_bbh_room_foyer),
      GEO_BRANCH(1, geo_bbh_room_mesh_room),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000B88
const GeoLayout geo_bbh_door_room_foyer_and_outside[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_BRANCH(1, geo_bbh_room_foyer),
      GEO_BRANCH(1, geo_bbh_room_outside),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000BF0
const GeoLayout geo_bbh_door_room_study_and_bridge[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_BRANCH(1, geo_bbh_room_study),
      GEO_BRANCH(1, geo_bbh_room_bridge),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000C38
const GeoLayout geo_bbh_door_room_study_and_attic[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_BRANCH(1, geo_bbh_room_study),
      GEO_BRANCH(1, geo_bbh_room_attic),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000C88
const GeoLayout geo_bbh_000C88[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,      bbh_seg7_dl_study_surfaces),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,      bbh_seg7_dl_study_windows),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, bbh_seg7_dl_study_lamps_glow),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,      bbh_seg7_dl_study_lamps),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, bbh_seg7_dl_study_window_light),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,      bbh_seg7_merry_go_round_room_surfaces),
      GEO_DISPLAY_LIST(LAYER_ALPHA,       bbh_seg7_merry_go_round_room_meshes),
      GEO_ASM(                                       0, geo_movtex_pause_control     ),
      GEO_ASM(BBH_MOVTEX_MERRY_GO_ROUND_WATER_ENTRANCE, geo_movtex_draw_water_regions),
      GEO_ASM(BBH_MOVTEX_MERRY_GO_ROUND_WATER_SIDE,     geo_movtex_draw_water_regions),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000CE8
const GeoLayout geo_bbh_door_room_piano_and_back_room[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_BRANCH(1, geo_bbh_room_piano),
      GEO_BRANCH(1, geo_bbh_room_back_room),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000D20
const GeoLayout geo_bbh_door_room_piano_and_library[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_BRANCH(1, geo_bbh_room_piano),
      GEO_BRANCH(1, geo_bbh_room_library),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000D68
const GeoLayout geo_bbh_000D68[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,      bbh_seg7_dl_bridge_room_surfaces),
      GEO_DISPLAY_LIST(LAYER_ALPHA,       bbh_seg7_dl_bridge_room_railing),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,      bbh_seg7_merry_go_round_room_surfaces),
      GEO_DISPLAY_LIST(LAYER_ALPHA,       bbh_seg7_merry_go_round_room_meshes),
      GEO_ASM(                                       0, geo_movtex_pause_control     ),
      GEO_ASM(BBH_MOVTEX_MERRY_GO_ROUND_WATER_ENTRANCE, geo_movtex_draw_water_regions),
      GEO_ASM(BBH_MOVTEX_MERRY_GO_ROUND_WATER_SIDE,     geo_movtex_draw_water_regions),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000DB0
const GeoLayout geo_bbh_door_room_back_room_and_outside[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_BRANCH(1, geo_bbh_room_back_room),
      GEO_BRANCH(1, geo_bbh_room_outside),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000DF0
const GeoLayout geo_bbh_door_room_attic_and_outside[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_BRANCH(1, geo_bbh_room_attic),
      GEO_BRANCH(1, geo_bbh_room_outside),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000E40
const GeoLayout geo_bbh_door_room_merry_go_round_and_basement_hallway[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      // //! renders water twice
      // GEO_BRANCH(1, geo_bbh_room_merry_go_round),
      // GEO_BRANCH(1, geo_bbh_room_basement_hallway),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,      bbh_seg7_merry_go_round_room_surfaces),
      GEO_DISPLAY_LIST(LAYER_ALPHA,       bbh_seg7_merry_go_round_room_meshes),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,      bbh_seg7_dl_basement_hallway),
      GEO_ASM(                                       0, geo_movtex_pause_control     ),
      GEO_ASM(BBH_MOVTEX_MERRY_GO_ROUND_WATER_ENTRANCE, geo_movtex_draw_water_regions),
      GEO_ASM(BBH_MOVTEX_MERRY_GO_ROUND_WATER_SIDE,     geo_movtex_draw_water_regions),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000E80
const GeoLayout geo_bbh_door_room_basement_hallway_and_shed[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      // //! renders water twice
      // GEO_BRANCH(1, geo_bbh_room_basement_hallway),
      // GEO_BRANCH(1, geo_bbh_room_shed),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,      bbh_seg7_dl_basement_hallway),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,      bbh_seg7_dl_shed_with_elevator),
      GEO_ASM(                                       0, geo_movtex_pause_control     ),
      GEO_ASM(BBH_MOVTEX_MERRY_GO_ROUND_WATER_ENTRANCE, geo_movtex_draw_water_regions),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000EB0
const GeoLayout geo_bbh_door_room_shed_and_outside[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      // //! renders water twice
      // GEO_BRANCH(1, geo_bbh_room_shed),
      // GEO_BRANCH(1, geo_bbh_room_outside),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,      bbh_seg7_dl_shed_with_elevator),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,      bbh_seg7_dl_outside_surfaces),
      GEO_DISPLAY_LIST(LAYER_ALPHA,       bbh_seg7_dl_outside_cage_walls),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,      bbh_seg7_dl_outside_windows),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, bbh_seg7_dl_outside_flames_glow),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,      bbh_seg7_dl_outside_lantern),
      GEO_ASM(                                       0, geo_movtex_pause_control     ),
      GEO_ASM(BBH_MOVTEX_MERRY_GO_ROUND_WATER_ENTRANCE, geo_movtex_draw_water_regions),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000F00
const GeoLayout geo_bbh_area_1[] = {
   GEO_NODE_SCREEN_AREA(10, SCREEN_CENTER_X, SCREEN_CENTER_Y, SCREEN_CENTER_X, SCREEN_CENTER_Y),
   GEO_OPEN_NODE(),
      GEO_ZBUFFER(0),
      GEO_OPEN_NODE(),
         GEO_NODE_ORTHO(100),
         GEO_OPEN_NODE(),
            GEO_BACKGROUND(BACKGROUND_HAUNTED, geo_skybox_main),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),
      GEO_ZBUFFER(1),
      GEO_OPEN_NODE(),
         GEO_CAMERA_FRUSTUM_WITH_FUNC(45, 50, 10000, geo_camera_fov),
         GEO_OPEN_NODE(),
            GEO_CAMERA(4, 0, 2000, 6000, 0, 0, 0, geo_camera_main),
            GEO_OPEN_NODE(),
               GEO_SWITCH_CASE(32, geo_switch_room),
               GEO_OPEN_NODE(),
                  GEO_BRANCH(1, geo_bbh_room_foyer                                   ), // 0x0E000670 //  1
                  GEO_BRANCH(1, geo_bbh_room_study                                   ), // 0x0E0006B0 //  2
                  GEO_BRANCH(1, geo_bbh_room_piano                                   ), // 0x0E0006E8 //  3
                  GEO_BRANCH(1, geo_bbh_room_bridge                                  ), // 0x0E000730 //  4
                  GEO_BRANCH(1, geo_bbh_room_back_room                               ), // 0x0E000750 //  5
                  GEO_BRANCH(1, geo_bbh_room_library                                 ), // 0x0E000768 //  6
                  GEO_BRANCH(1, geo_bbh_room_coffins                                 ), // 0x0E0007B0 //  7
                  GEO_BRANCH(1, geo_bbh_room_mesh_room                               ), // 0x0E0007D0 //  8
                  GEO_BRANCH(1, geo_bbh_room_attic                                   ), // 0x0E000800 //  9
                  GEO_BRANCH(1, geo_bbh_room_merry_go_round                          ), // 0x0E000828 // 10
                  GEO_BRANCH(1, geo_bbh_room_basement_hallway                        ), // 0x0E000860 // 11
                  GEO_BRANCH(1, geo_bbh_room_shed                                    ), // 0x0E000888 // 12
                  GEO_BRANCH(1, geo_bbh_room_outside                                 ), // 0x0E0008B0 // 13
                  GEO_BRANCH(1, geo_bbh_door_room_foyer_and_study                    ), // 0x0E0008E8 // 14
                  GEO_BRANCH(1, geo_bbh_door_room_foyer_and_piano                    ), // 0x0E000950 // 15
                  GEO_BRANCH(1, geo_bbh_door_room_foyer_and_bridge                   ), // 0x0E0009C8 // 16
                  GEO_BRANCH(1, geo_bbh_door_room_foyer_and_back_room                ), // 0x0E000A18 // 17
                  GEO_BRANCH(1, geo_bbh_door_room_foyer_and_library                  ), // 0x0E000A60 // 18
                  GEO_BRANCH(1, geo_bbh_door_room_foyer_and_coffins                  ), // 0x0E000AD8 // 19
                  GEO_BRANCH(1, geo_bbh_door_room_foyer_and_mesh_room                ), // 0x0E000B28 // 20
                  GEO_BRANCH(1, geo_bbh_door_room_foyer_and_outside                  ), // 0x0E000B88 // 21
                  GEO_BRANCH(1, geo_bbh_door_room_study_and_bridge                   ), // 0x0E000BF0 // 22
                  GEO_BRANCH(1, geo_bbh_door_room_study_and_attic                    ), // 0x0E000C38 // 23
                  GEO_BRANCH(1, geo_bbh_000C88), // 0x0E000C88 // 24
                  GEO_BRANCH(1, geo_bbh_door_room_piano_and_back_room                ), // 0x0E000CE8 // 25
                  GEO_BRANCH(1, geo_bbh_door_room_piano_and_library                  ), // 0x0E000D20 // 26
                  GEO_BRANCH(1, geo_bbh_000D68), // 0x0E000D68 // 27
                  GEO_BRANCH(1, geo_bbh_door_room_back_room_and_outside              ), // 0x0E000DB0 // 28
                  GEO_BRANCH(1, geo_bbh_door_room_attic_and_outside                  ), // 0x0E000DF0 // 29
                  GEO_BRANCH(1, geo_bbh_door_room_merry_go_round_and_basement_hallway), // 0x0E000E40 // 30
                  GEO_BRANCH(1, geo_bbh_door_room_basement_hallway_and_shed          ), // 0x0E000E80 // 31
                  GEO_BRANCH(1, geo_bbh_door_room_shed_and_outside                   ), // 0x0E000EB0 // 32
               GEO_CLOSE_NODE(),
               GEO_RENDER_OBJ(),
               GEO_ASM(0, geo_envfx_main),
            GEO_CLOSE_NODE(),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
