// 0x16000040
const GeoLayout explosion_geo[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_SWITCH_CASE(9, geo_switch_anim_state),
      GEO_OPEN_NODE(),
         GEO_DISPLAY_LIST(LAYER_TRANSPARENT, explosion_seg3_dl_0),
         GEO_DISPLAY_LIST(LAYER_TRANSPARENT, explosion_seg3_dl_0),
         GEO_DISPLAY_LIST(LAYER_TRANSPARENT, explosion_seg3_dl_1),
         GEO_DISPLAY_LIST(LAYER_TRANSPARENT, explosion_seg3_dl_1),
         GEO_DISPLAY_LIST(LAYER_TRANSPARENT, explosion_seg3_dl_2),
         GEO_DISPLAY_LIST(LAYER_TRANSPARENT, explosion_seg3_dl_3),
         GEO_DISPLAY_LIST(LAYER_TRANSPARENT, explosion_seg3_dl_4),
         GEO_DISPLAY_LIST(LAYER_TRANSPARENT, explosion_seg3_dl_5),
         GEO_DISPLAY_LIST(LAYER_TRANSPARENT, explosion_seg3_dl_6),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
