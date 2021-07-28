// 0x0E000BE0
const GeoLayout wf_geo_tower_door[] = {
   GEO_CULLING_RADIUS(320),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, wf_seg7_dl_tower_door),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
