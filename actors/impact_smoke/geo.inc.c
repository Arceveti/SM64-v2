// 0x0D000BB8 / 0BFC
const GeoLayout bowser_impact_smoke_geo[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_ASM(0, geo_update_layer_transparency),
      GEO_SWITCH_CASE(5, geo_switch_anim_state),
      GEO_OPEN_NODE(),
         GEO_DISPLAY_LIST(LAYER_TRANSPARENT, impact_smoke_seg6_dl_0),
         GEO_DISPLAY_LIST(LAYER_TRANSPARENT, impact_smoke_seg6_dl_1),
         GEO_DISPLAY_LIST(LAYER_TRANSPARENT, impact_smoke_seg6_dl_2),
         GEO_DISPLAY_LIST(LAYER_TRANSPARENT, impact_smoke_seg6_dl_3),
         GEO_DISPLAY_LIST(LAYER_TRANSPARENT, impact_smoke_seg6_dl_1),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
