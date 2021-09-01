// 0x0E0004BC
const GeoLayout ccm_geo_ice_column[] = {
   GEO_CULLING_RADIUS(800),
   GEO_OPEN_NODE(),
      GEO_RENDER_RANGE(-1000, 7000),
      GEO_OPEN_NODE(),
         GEO_DISPLAY_LIST(LAYER_TRANSPARENT, ccm_seg7_dl_ice_column),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
