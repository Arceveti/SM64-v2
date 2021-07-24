// 0x0C000610
const GeoLayout pokey_head_geo[] = {
   GEO_SHADOW(SHADOW_CIRCLE_4_VERTS, 0x96, 50),
   GEO_OPEN_NODE(),
      GEO_SWITCH_CASE(2, geo_switch_anim_state),
      GEO_OPEN_NODE(),
         GEO_DISPLAY_LIST(LAYER_ALPHA, pokey_seg5_dl_face),
         GEO_DISPLAY_LIST(LAYER_ALPHA, pokey_seg5_dl_face_blink),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};

// 0x0C000644
const GeoLayout pokey_body_part_geo[] = {
   GEO_SHADOW(SHADOW_CIRCLE_4_VERTS, 0x96, 50),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_ALPHA, pokey_seg5_dl_body),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
