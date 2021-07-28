// 0x0E000270
const GeoLayout ttc_geo_pendulum[] = {
   GEO_CULLING_RADIUS(1100),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, ttc_seg7_dl_pendulum),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
