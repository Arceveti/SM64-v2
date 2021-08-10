// 0x0E000710
const GeoLayout ttm_geo_star_cage[] = {
   GEO_CULLING_RADIUS(300),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, ttm_seg7_dl_monkey_cage_planks),
      GEO_DISPLAY_LIST(LAYER_ALPHA, ttm_seg7_dl_monkey_cage_sides),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
