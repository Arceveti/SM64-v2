// 0x0E000494
const GeoLayout ccm_geo_snowman_platform[] = {
   GEO_CULLING_RADIUS(400),
   GEO_OPEN_NODE(),
      GEO_RENDER_RANGE(-500, 7000),
      GEO_OPEN_NODE(),
         GEO_DISPLAY_LIST(LAYER_OPAQUE, ccm_seg7_dl_snowman_platform),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
