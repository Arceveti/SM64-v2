// 0x0E00040C
const GeoLayout ccm_geo_snowman_head[] = {
   GEO_CULLING_RADIUS(300),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, ccm_seg7_dl_snowman_head_snow),
      GEO_DISPLAY_LIST(LAYER_ALPHA,  ccm_seg7_dl_snowman_head_face),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
