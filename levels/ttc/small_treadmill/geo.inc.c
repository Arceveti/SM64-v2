// 0x0E0002A8
const GeoLayout ttc_geo_small_treadmill[] = {
   GEO_CULLING_RADIUS(520),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, ttc_seg7_dl_small_treadmill),
      GEO_ASM(MOVTEX_TREADMILL_SMALL, geo_movtex_draw_colored_no_update),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
