// 0x0E0002C8
const GeoLayout ttc_geo_push_block[] = {
   GEO_CULLING_RADIUS(500),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, ttc_seg7_dl_push_block),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
