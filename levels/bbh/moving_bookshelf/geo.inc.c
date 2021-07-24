// 0x0E000610
const GeoLayout geo_bbh_moving_bookshelf[] = {
   GEO_CULLING_RADIUS(1000),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, bbh_seg7_dl_moving_bookshelf),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
