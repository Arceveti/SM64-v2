// 0x0E000630
const GeoLayout ssl_geo_tox_box[] = {
   GEO_CULLING_RADIUS(4000),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, ssl_seg7_dl_tox_box),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
