// 0x0E0009D0
const GeoLayout wf_geo_platforms_with_pole[] = {
   GEO_CULLING_RADIUS(1200),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, wf_seg7_dl_platforms_with_pole),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
