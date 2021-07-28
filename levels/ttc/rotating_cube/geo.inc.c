// 0x0E000240
const GeoLayout ttc_geo_rotating_cube[] = {
   GEO_CULLING_RADIUS(410),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, ttc_seg7_dl_rotating_cube),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
