// 0x0E0004E4
const GeoLayout ccm_geo_wall_kicks_will_work[] = {
   GEO_CULLING_RADIUS(3500),
   GEO_OPEN_NODE(),
      GEO_RENDER_RANGE(-3000, 6000),
      GEO_OPEN_NODE(),
         GEO_DISPLAY_LIST(LAYER_OPAQUE, ccm_seg7_dl_wall_kicks_will_work),
         GEO_DISPLAY_LIST(LAYER_ALPHA, ccm_seg7_dl_wkww_fence_and_icicles),
         GEO_DISPLAY_LIST(LAYER_TRANSPARENT, ccm_seg7_dl_wkww_ice),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
