// 0x0D000000
const GeoLayout mr_i_body_geo[] = {
   GEO_SHADOW(SHADOW_CIRCLE_4_VERTS, 0x9B, 200),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_ALPHA, mr_i_eyeball_seg6_dl_body),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
