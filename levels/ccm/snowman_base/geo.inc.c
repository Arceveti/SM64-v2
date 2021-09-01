// 0x0E0003F0
const GeoLayout ccm_geo_snowman_base[] = {
   GEO_SHADOW(SHADOW_CIRCLE_4_VERTS, 0xC8, 400),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, ccm_seg7_dl_snowman_base),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
