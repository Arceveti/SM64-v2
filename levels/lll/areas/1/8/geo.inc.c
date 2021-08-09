// 0x0E000A40
const GeoLayout lll_geo_cage_platform[] = {
   GEO_CULLING_RADIUS(1700),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, lll_seg7_dl_cage_platform_bearings),
      GEO_DISPLAY_LIST(LAYER_ALPHA, lll_seg7_dl_cage_platform),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
