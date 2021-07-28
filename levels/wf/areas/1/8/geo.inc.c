// 0x0E000878
const GeoLayout wf_geo_fences[] = {
   GEO_CULLING_RADIUS(9000),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_ALPHA, wf_seg7_dl_fences),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
