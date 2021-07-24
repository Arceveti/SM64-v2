// 0x0E000528
const GeoLayout geo_bitdw_sliding_platform[] = {
   GEO_CULLING_RADIUS(1500),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, bitdw_seg7_dl_sliding_platform),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
