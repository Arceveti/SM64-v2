// 0x0E000920
const GeoLayout rr_geo_donut_block[] = {
   GEO_CULLING_RADIUS(420),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, rr_seg7_dl_donut_block),
      GEO_DISPLAY_LIST(LAYER_ALPHA, rr_seg7_dl_donut_block_hole),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
