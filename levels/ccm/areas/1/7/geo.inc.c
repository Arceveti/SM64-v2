// 0x0E00045C
const GeoLayout ccm_geo_lower_cabin[] = {
   GEO_CULLING_RADIUS(900),
   GEO_OPEN_NODE(),
      GEO_RENDER_RANGE(-1000, 7000),
      GEO_OPEN_NODE(),
         GEO_DISPLAY_LIST(LAYER_OPAQUE, ccm_seg7_dl_lower_cabin_outside),
         GEO_DISPLAY_LIST(LAYER_ALPHA, ccm_seg7_dl_lower_cabin_window_and_icicles),
         GEO_DISPLAY_LIST(LAYER_TRANSPARENT, ccm_seg7_dl_cabin_window_glass_outside),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
