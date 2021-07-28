// 0x0E0009A0
const GeoLayout wf_geo_grass_with_flowers[] = {
   GEO_CULLING_RADIUS(3000),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, wf_seg7_dl_grass_with_flowers),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
