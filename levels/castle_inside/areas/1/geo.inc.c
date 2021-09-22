// 0x0E000F30 - Lobby
const GeoLayout castle_geo_area_1_room_lobby[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,            inside_castle_seg7_dl_07028FD0),
      GEO_DISPLAY_LIST(LAYER_ALPHA,             dl_castle_lobby_fence),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,            inside_castle_seg7_dl_0702A650),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, dl_castle_lobby_sun_carpet),
      GEO_DISPLAY_LIST(LAYER_ALPHA,             dl_castle_lobby_peach_window),
      GEO_ASM(0, geo_exec_inside_castle_light),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000F70 - Hallway to Courtyard
const GeoLayout castle_geo_area_1_room_back_hallway[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,            inside_castle_seg7_dl_area_1_back_hallway),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000F88 - Bowser 1 Hallway
const GeoLayout castle_geo_area_1_room_bowser_1[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,            inside_castle_seg7_dl_bowser_1_hallway),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,            inside_castle_seg7_dl_bowser_1_painting),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000FA8 - PSS Room
const GeoLayout castle_geo_area_1_room_pss[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,            inside_castle_seg7_dl_pss_room),
      GEO_DISPLAY_LIST(LAYER_ALPHA,             inside_castle_seg7_dl_pss_windows),
      GEO_DISPLAY_LIST(LAYER_ALPHA,             inside_castle_seg7_dl_pss_wall_sign),
#ifdef PSS_PAINTING
      GEO_ASM(  0, geo_painting_update),
      GEO_ASM(PAINTING_ID(14, 1), geo_painting_draw),
#endif
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E000FD0 - BOB Room
const GeoLayout castle_geo_area_1_room_bob[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,            inside_castle_seg7_dl_bob_room),
      GEO_DISPLAY_LIST(LAYER_ALPHA,             inside_castle_seg7_dl_bob_wall_signs),
      GEO_ASM(  0, geo_painting_update),
      GEO_ASM(PAINTING_ID(0, 1), geo_painting_draw),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E001000 - WF Room
const GeoLayout castle_geo_area_1_room_wf[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,            inside_castle_seg7_dl_wf_room),
      GEO_DISPLAY_LIST(LAYER_ALPHA,             inside_castle_seg7_dl_wf_fence),
      GEO_DISPLAY_LIST(LAYER_ALPHA,             inside_castle_seg7_dl_wf_wall_sign),
      GEO_ASM(  0, geo_painting_update),
      GEO_ASM(PAINTING_ID(2, 1), geo_painting_draw),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E001038 - Aquarium
const GeoLayout castle_geo_area_1_room_jrb[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,            inside_castle_seg7_dl_07036D88),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,            inside_castle_seg7_dl_07037988),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,            inside_castle_seg7_dl_07037BF8),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,       dl_castle_aquarium_glass),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT,       dl_castle_aquarium_light),
      GEO_DISPLAY_LIST(LAYER_ALPHA,             dl_castle_aquarium_wall_sign),
      GEO_ASM(  0, geo_painting_update),
      GEO_ASM(PAINTING_ID(3, 1), geo_painting_draw),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E001088 - CCM Room
const GeoLayout castle_geo_area_1_room_ccm[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,            inside_castle_seg7_dl_ccm_room),
      GEO_DISPLAY_LIST(LAYER_ALPHA,             inside_castle_seg7_dl_ccm_wall_sign),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,            inside_castle_seg7_dl_ccm_fake_painting_1),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,            inside_castle_seg7_dl_ccm_fake_painting_2),
      GEO_ASM(  0, geo_painting_update),
      GEO_ASM(PAINTING_ID(1, 1), geo_painting_draw),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E0010C8 - Door Room (Lobby + Fake Spiral Stairs) 1
const GeoLayout castle_geo_area_1_door_room_lobby_fake_spiral_stairs[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,            inside_castle_seg7_dl_07028FD0),
      GEO_DISPLAY_LIST(LAYER_ALPHA,             dl_castle_lobby_fence),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,            inside_castle_seg7_dl_0702A650),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, dl_castle_lobby_sun_carpet),
      GEO_DISPLAY_LIST(LAYER_ALPHA,             dl_castle_lobby_peach_window),
      GEO_ASM(0, geo_exec_inside_castle_light),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,            inside_castle_seg7_dl_fake_spiral_stairs_room),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E001110 - Door Room (Lobby + Hallway to Courtyard)
const GeoLayout castle_geo_area_1_door_room_lobby_back_hallway[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,            inside_castle_seg7_dl_07028FD0),
      GEO_DISPLAY_LIST(LAYER_ALPHA,             dl_castle_lobby_fence),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,            inside_castle_seg7_dl_0702A650),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, dl_castle_lobby_sun_carpet),
      GEO_DISPLAY_LIST(LAYER_ALPHA,             dl_castle_lobby_peach_window),
      GEO_ASM(0, geo_exec_inside_castle_light),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,            inside_castle_seg7_dl_area_1_back_hallway),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E001158 - Door Room (Lobby + Bowser 1 Hallway)
const GeoLayout castle_geo_area_1_door_room_lobby_bowser_1[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,            inside_castle_seg7_dl_07028FD0),
      GEO_DISPLAY_LIST(LAYER_ALPHA,             dl_castle_lobby_fence),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,            inside_castle_seg7_dl_0702A650),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, dl_castle_lobby_sun_carpet),
      GEO_DISPLAY_LIST(LAYER_ALPHA,             dl_castle_lobby_peach_window),
      GEO_ASM(0, geo_exec_inside_castle_light),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,            inside_castle_seg7_dl_bowser_1_hallway),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,            inside_castle_seg7_dl_bowser_1_painting),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E0011A8 - Door Room (Lobby + PSS Room)
const GeoLayout castle_geo_area_1_door_room_lobby_pss[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,            inside_castle_seg7_dl_07028FD0),
      GEO_DISPLAY_LIST(LAYER_ALPHA,             dl_castle_lobby_fence),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,            inside_castle_seg7_dl_0702A650),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, dl_castle_lobby_sun_carpet),
      GEO_DISPLAY_LIST(LAYER_ALPHA,             dl_castle_lobby_peach_window),
      GEO_ASM(0, geo_exec_inside_castle_light),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,            inside_castle_seg7_dl_pss_room),
      GEO_DISPLAY_LIST(LAYER_ALPHA,             inside_castle_seg7_dl_pss_windows),
      GEO_DISPLAY_LIST(LAYER_ALPHA,             inside_castle_seg7_dl_pss_wall_sign),
#ifdef PSS_PAINTING
      GEO_ASM(  0, geo_painting_update),
      GEO_ASM(PAINTING_ID(14, 1), geo_painting_draw),
#endif
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E001200 - Door Room (Lobby + BOB Room)
const GeoLayout castle_geo_area_1_door_room_lobby_bob[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,            inside_castle_seg7_dl_07028FD0),
      GEO_DISPLAY_LIST(LAYER_ALPHA,             dl_castle_lobby_fence),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,            inside_castle_seg7_dl_0702A650),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, dl_castle_lobby_sun_carpet),
      GEO_DISPLAY_LIST(LAYER_ALPHA,             dl_castle_lobby_peach_window),
      GEO_ASM(  0, geo_exec_inside_castle_light),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,            inside_castle_seg7_dl_bob_room),
      GEO_DISPLAY_LIST(LAYER_ALPHA,             inside_castle_seg7_dl_bob_wall_signs),
      GEO_ASM(  0, geo_painting_update),
      GEO_ASM(256, geo_painting_draw),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E001260 - Door Room (Lobby + WF Room)
const GeoLayout castle_geo_area_1_door_room_lobby_wf[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,            inside_castle_seg7_dl_07028FD0),
      GEO_DISPLAY_LIST(LAYER_ALPHA,             dl_castle_lobby_fence),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,            inside_castle_seg7_dl_0702A650),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, dl_castle_lobby_sun_carpet),
      GEO_DISPLAY_LIST(LAYER_ALPHA,             dl_castle_lobby_peach_window),
      GEO_ASM(  0, geo_exec_inside_castle_light),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,            inside_castle_seg7_dl_wf_room),
      GEO_DISPLAY_LIST(LAYER_ALPHA,             inside_castle_seg7_dl_wf_fence),
      GEO_DISPLAY_LIST(LAYER_ALPHA,             inside_castle_seg7_dl_wf_wall_sign),
      GEO_ASM(  0, geo_painting_update),
      GEO_ASM(258, geo_painting_draw),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E0012C8 - Door Room (Lobby + Aquarium)
const GeoLayout castle_geo_area_1_door_room_lobby_jrb[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, inside_castle_seg7_dl_07028FD0),
      GEO_DISPLAY_LIST(LAYER_ALPHA, dl_castle_lobby_fence),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, inside_castle_seg7_dl_0702A650),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, dl_castle_lobby_sun_carpet),
      GEO_DISPLAY_LIST(LAYER_ALPHA, dl_castle_lobby_peach_window),
      GEO_ASM(  0, geo_exec_inside_castle_light),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, inside_castle_seg7_dl_07036D88),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, inside_castle_seg7_dl_07037988),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, inside_castle_seg7_dl_07037BF8),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, dl_castle_aquarium_glass),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, dl_castle_aquarium_light),
      GEO_DISPLAY_LIST(LAYER_ALPHA, dl_castle_aquarium_wall_sign),
      GEO_ASM(  0, geo_painting_update),
      GEO_ASM(PAINTING_ID(3, 1), geo_painting_draw),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// 0x0E001348 - Door Room (Lobby + CCM Room)
const GeoLayout castle_geo_area_1_door_room_lobby_ccm[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,            inside_castle_seg7_dl_07028FD0),
      GEO_DISPLAY_LIST(LAYER_ALPHA,             dl_castle_lobby_fence),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,            inside_castle_seg7_dl_0702A650),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, dl_castle_lobby_sun_carpet),
      GEO_DISPLAY_LIST(LAYER_ALPHA,             dl_castle_lobby_peach_window),
      GEO_ASM(  0, geo_exec_inside_castle_light),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,            inside_castle_seg7_dl_ccm_room),
      GEO_DISPLAY_LIST(LAYER_ALPHA,             inside_castle_seg7_dl_ccm_wall_sign),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,            inside_castle_seg7_dl_ccm_fake_painting_1),
      GEO_DISPLAY_LIST(LAYER_OPAQUE,            inside_castle_seg7_dl_ccm_fake_painting_2),
      GEO_ASM(  0, geo_painting_update),
      GEO_ASM(PAINTING_ID(1, 1), geo_painting_draw),
   GEO_CLOSE_NODE(),
   GEO_RETURN(),
};

// // 0x0E0013B8 - Door Room (Lobby + Fake Spiral Stairs) 2
// const GeoLayout castle_geo_area_1_door_room_lobby_fake_spiral_stairs_2[] = {
//    GEO_NODE_START(),
//    GEO_OPEN_NODE(),
//       GEO_DISPLAY_LIST(LAYER_OPAQUE,            inside_castle_seg7_dl_07028FD0),
//       GEO_DISPLAY_LIST(LAYER_ALPHA,             dl_castle_lobby_fence),
//       GEO_DISPLAY_LIST(LAYER_OPAQUE,            inside_castle_seg7_dl_0702A650),
//       GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, dl_castle_lobby_sun_carpet),
//       GEO_DISPLAY_LIST(LAYER_ALPHA,             dl_castle_lobby_peach_window),
//       GEO_ASM(0, geo_exec_inside_castle_light),
//       GEO_DISPLAY_LIST(LAYER_OPAQUE,            inside_castle_seg7_dl_fake_spiral_stairs_room),
//    GEO_CLOSE_NODE(),
//    GEO_RETURN(),
// };

// 0x0E001400
const GeoLayout castle_geo_area_1[] = {
   GEO_NODE_SCREEN_AREA(10, SCREEN_CENTER_X, SCREEN_CENTER_Y, SCREEN_CENTER_X, SCREEN_CENTER_Y),
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
         GEO_CAMERA_FRUSTUM_WITH_FUNC(64, 50, 7000, geo_camera_fov),
         GEO_OPEN_NODE(),
            GEO_CAMERA(13, 0, 2000, 6000, 0, 0, 0, geo_camera_main),
            GEO_OPEN_NODE(),
               GEO_SWITCH_CASE(17, geo_switch_room),
               GEO_OPEN_NODE(),
                  GEO_BRANCH(1, castle_geo_area_1_room_lobby),                            // 0x0E000F30 - Lobby
                  GEO_BRANCH(1, castle_geo_area_1_room_back_hallway),                     // 0x0E000F70 - Hallway to Courtyard
                  GEO_BRANCH(1, castle_geo_area_1_room_bowser_1),                         // 0x0E000F88 - Bowser 1 Hallway
                  GEO_BRANCH(1, castle_geo_area_1_room_pss),                              // 0x0E000FA8 - PSS Room
                  GEO_BRANCH(1, castle_geo_area_1_room_bob),                              // 0x0E000FD0 - BOB Room
                  GEO_BRANCH(1, castle_geo_area_1_room_wf),                               // 0x0E001000 - WF Room
                  GEO_BRANCH(1, castle_geo_area_1_room_jrb),                              // 0x0E001038 - Aquarium
                  GEO_BRANCH(1, castle_geo_area_1_room_ccm),                              // 0x0E001088 - CCM Room
                  GEO_BRANCH(1, castle_geo_area_1_door_room_lobby_fake_spiral_stairs),    // 0x0E0010C8 - Door Room (Lobby + Fake Spiral Stairs) 1
                  GEO_BRANCH(1, castle_geo_area_1_door_room_lobby_back_hallway),          // 0x0E001110 - Door Room (Lobby + Hallway to Courtyard)
                  GEO_BRANCH(1, castle_geo_area_1_door_room_lobby_bowser_1),              // 0x0E001158 - Door Room (Lobby + Bowser 1 Hallway)
                  GEO_BRANCH(1, castle_geo_area_1_door_room_lobby_pss),                   // 0x0E0011A8 - Door Room (Lobby + PSS Room)
                  GEO_BRANCH(1, castle_geo_area_1_door_room_lobby_bob),                   // 0x0E001200 - Door Room (Lobby + BOB Room)
                  GEO_BRANCH(1, castle_geo_area_1_door_room_lobby_wf),                    // 0x0E001260 - Door Room (Lobby + WF Room)
                  GEO_BRANCH(1, castle_geo_area_1_door_room_lobby_jrb),                   // 0x0E0012C8 - Door Room (Lobby + Aquarium)
                  GEO_BRANCH(1, castle_geo_area_1_door_room_lobby_ccm),                   // 0x0E001348 - Door Room (Lobby + CCM Room)
                  GEO_BRANCH(1, castle_geo_area_1_door_room_lobby_fake_spiral_stairs),    // 0x0E0010C8 - Door Room (Lobby + Fake Spiral Stairs) 1
                  // GEO_BRANCH(1, castle_geo_area_1_door_room_lobby_fake_spiral_stairs_2),  // 0x0E0013B8
               GEO_CLOSE_NODE(),
               GEO_RENDER_OBJ(),
               GEO_ASM(0, geo_envfx_main),
            GEO_CLOSE_NODE(),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
