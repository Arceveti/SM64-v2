// 0x0E000958
const GeoLayout wf_geo_grass_with_tree[] = {
   GEO_CULLING_RADIUS(2000),
   GEO_OPEN_NODE(),
      GEO_RENDER_RANGE(-2000, 8000),
      GEO_OPEN_NODE(),
         GEO_DISPLAY_LIST(LAYER_OPAQUE, wf_seg7_dl_grass_with_tree_near),
         GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, wf_seg7_dl_tree_shadow),
      GEO_CLOSE_NODE(),
      GEO_RENDER_RANGE(8000, 20000),
      GEO_OPEN_NODE(),
         GEO_DISPLAY_LIST(LAYER_OPAQUE, wf_seg7_dl_grass_with_tree_far),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
