// 0x0E0003A8
const GeoLayout sl_geo_area_1[] = {
   GEO_NODE_SCREEN_AREA(10, (SCREEN_WIDTH/2), (SCREEN_HEIGHT/2), (SCREEN_WIDTH/2), (SCREEN_HEIGHT/2)),
   GEO_OPEN_NODE(),
      GEO_ZBUFFER(0),
      GEO_OPEN_NODE(),
         GEO_NODE_ORTHO(100),
         GEO_OPEN_NODE(),
            GEO_BACKGROUND(BACKGROUND_SNOW_MOUNTAINS, geo_skybox_main),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),
      GEO_ZBUFFER(1),
      GEO_OPEN_NODE(),
         GEO_CAMERA_FRUSTUM_WITH_FUNC(45, 100, 20000, geo_camera_fov),
         GEO_OPEN_NODE(),
            GEO_CAMERA(16, 0, 2000, 6000, 0, 4400, 0, geo_camera_main),
            GEO_OPEN_NODE(),
               GEO_DISPLAY_LIST(LAYER_OPAQUE,            sl_seg7_dl_07005478),
               GEO_DISPLAY_LIST(LAYER_TRANSPARENT,       sl_seg7_dl_070056B0),
               GEO_DISPLAY_LIST(LAYER_OPAQUE,            sl_seg7_dl_070073D0),
               GEO_DISPLAY_LIST(LAYER_ALPHA,             sl_seg7_dl_07007880),
               GEO_DISPLAY_LIST(LAYER_TRANSPARENT,       sl_seg7_dl_070088B0),
               GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, sl_seg7_dl_07008D58),
               GEO_DISPLAY_LIST(LAYER_OPAQUE,            sl_seg7_dl_0700A5A0),
               GEO_ASM(              0, geo_movtex_pause_control     ),
               GEO_ASM(SL_MOVTEX_WATER, geo_movtex_draw_water_regions),
               GEO_RENDER_OBJ(),
               GEO_ASM(   1, geo_envfx_main),
            GEO_CLOSE_NODE(),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),
      GEO_ZBUFFER(0),
      GEO_OPEN_NODE(),
         GEO_ASM(0, geo_cannon_circle_base),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
