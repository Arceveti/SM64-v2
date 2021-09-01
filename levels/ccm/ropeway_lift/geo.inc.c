// 0x0E0003D0
const GeoLayout ccm_geo_ropeway_lift[] = {
   GEO_CULLING_RADIUS(500),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_ALPHA,  ccm_seg7_dl_ropeway_lift_platform),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, ccm_seg7_dl_ropeway_lift_hinge),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
