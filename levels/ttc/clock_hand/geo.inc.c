// 0x0E000358
const GeoLayout ttc_geo_clock_hand[] = {
   GEO_CULLING_RADIUS(1700),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, ttc_seg7_dl_clock_hand),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
