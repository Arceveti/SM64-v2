// 0x0E000370
const GeoLayout ttc_geo_spinner[] = {
   GEO_CULLING_RADIUS(500),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, ttc_seg7_dl_spinner),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
