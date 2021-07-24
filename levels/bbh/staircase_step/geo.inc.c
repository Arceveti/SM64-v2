// 0x0E0005B0
const GeoLayout geo_bbh_staircase_step[] = {
   GEO_CULLING_RADIUS(700),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, bbh_seg7_dl_staircase_step),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
