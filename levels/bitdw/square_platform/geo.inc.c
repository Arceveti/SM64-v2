// 0x0E000558
const GeoLayout geo_bitdw_moving_pyramid[] = {
   GEO_CULLING_RADIUS(600),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, bitdw_seg7_dl_moving_pyramid),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
