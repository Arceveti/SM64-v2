// 0x0E000288
const GeoLayout ttc_geo_large_treadmill[] = {
   GEO_CULLING_RADIUS(720),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, ttc_seg7_dl_large_treadmill),
      GEO_ASM(0x1400, geo_movtex_draw_colored_no_update),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
