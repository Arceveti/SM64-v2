// 0x0E000A98
const GeoLayout wf_geo_sliding_platform[] = {
   GEO_CULLING_RADIUS(500),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, wf_seg7_dl_sliding_platform),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
