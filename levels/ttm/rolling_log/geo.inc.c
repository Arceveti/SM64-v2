// 0x0E000730
const GeoLayout ttm_geo_rolling_log[] = {
   GEO_CULLING_RADIUS(1200),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, ttm_seg7_dl_rolling_log),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
