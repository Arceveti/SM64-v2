// 0x0E000AE0
const GeoLayout wf_geo_giant_pole[] = {
   GEO_CULLING_RADIUS(2000),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, wf_seg7_dl_giant_pole),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
