// 0x0E000B78
const GeoLayout wf_geo_breakable_wall_right[] = {
   GEO_CULLING_RADIUS(750),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, wf_seg7_dl_breakable_wall_right),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
