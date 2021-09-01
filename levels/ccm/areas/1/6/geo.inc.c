// 0x0E00042C
const GeoLayout ccm_geo_upper_cabin[] = {
   GEO_CULLING_RADIUS(800),
   GEO_OPEN_NODE(),
      GEO_RENDER_RANGE(-1000, 4000),
      GEO_OPEN_NODE(),
         GEO_DISPLAY_LIST(LAYER_OPAQUE, ccm_seg7_dl_upper_cabin_outside),
         GEO_DISPLAY_LIST(LAYER_ALPHA, ccm_seg7_dl_upper_cabin_fence_and_icicles),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
