// 0x0E000EC0
const GeoLayout lll_geo_area_2[] = {
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
         GEO_CAMERA_FRUSTUM_WITH_FUNC(45, 100, 12800, geo_camera_fov),
         GEO_OPEN_NODE(),
            GEO_CAMERA(2, 0, 2000, 6000, 0, 0, 0, geo_camera_main),
            GEO_OPEN_NODE(),
               GEO_DISPLAY_LIST(LAYER_OPAQUE,      lll_seg7_dl_area_2),
               GEO_DISPLAY_LIST(LAYER_OPAQUE,      lll_seg7_dl_volcano_decoration),
               GEO_DISPLAY_LIST(LAYER_TRANSPARENT, lll_seg7_dl_volcano_upper_wall_shadow),
               GEO_DISPLAY_LIST(LAYER_OPAQUE,      lll_seg7_dl_volcano_exit),
               GEO_DISPLAY_LIST(LAYER_ALPHA,       lll_seg7_dl_fire_spitter_hole),
               GEO_ASM(                            0, geo_movtex_pause_control     ),
               GEO_ASM(MOVTEX_VOLCANO_LAVA_FALL,      geo_movtex_draw_nocolor      ),
               GEO_ASM(LLL_MOVTEX_VOLCANO_FLOOR_LAVA, geo_movtex_draw_water_regions),
               GEO_RENDER_OBJ(),
               GEO_ASM(     0, geo_envfx_main),
            GEO_CLOSE_NODE(),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
