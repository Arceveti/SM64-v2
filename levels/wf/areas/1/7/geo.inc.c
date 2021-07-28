// 0x0E000860
const GeoLayout wf_geo_platform_between_sliding_platforms[] = {
   GEO_CULLING_RADIUS(1400),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, wf_seg7_dl_platform_between_sliding_platforms),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
