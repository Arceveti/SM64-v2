// 0x16000B10
const GeoLayout red_flame_shadow_geo[] = {
   GEO_SHADOW(SHADOW_CIRCLE_4_VERTS, 0x50, 20),
   GEO_OPEN_NODE(),
      GEO_BRANCH_AND_LINK(red_flame_geo),
   GEO_CLOSE_NODE(),
   GEO_END(),
};

// 0x16000B2C
const GeoLayout red_flame_geo[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_SWITCH_CASE(8, geo_switch_anim_state),
      GEO_OPEN_NODE(),
         GEO_DISPLAY_LIST(LAYER_TRANSPARENT, flame_seg3_dl_red_0),
         GEO_DISPLAY_LIST(LAYER_TRANSPARENT, flame_seg3_dl_red_1),
         GEO_DISPLAY_LIST(LAYER_TRANSPARENT, flame_seg3_dl_red_2),
         GEO_DISPLAY_LIST(LAYER_TRANSPARENT, flame_seg3_dl_red_3),
         GEO_DISPLAY_LIST(LAYER_TRANSPARENT, flame_seg3_dl_red_4),
         GEO_DISPLAY_LIST(LAYER_TRANSPARENT, flame_seg3_dl_red_5),
         GEO_DISPLAY_LIST(LAYER_TRANSPARENT, flame_seg3_dl_red_6),
         GEO_DISPLAY_LIST(LAYER_TRANSPARENT, flame_seg3_dl_red_7),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};

// 0x16000B8C
const GeoLayout blue_flame_geo[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_SWITCH_CASE(8, geo_switch_anim_state),
      GEO_OPEN_NODE(),
         GEO_DISPLAY_LIST(LAYER_TRANSPARENT, flame_seg3_dl_blue_0),
         GEO_DISPLAY_LIST(LAYER_TRANSPARENT, flame_seg3_dl_blue_1),
         GEO_DISPLAY_LIST(LAYER_TRANSPARENT, flame_seg3_dl_blue_2),
         GEO_DISPLAY_LIST(LAYER_TRANSPARENT, flame_seg3_dl_blue_3),
         GEO_DISPLAY_LIST(LAYER_TRANSPARENT, flame_seg3_dl_blue_4),
         GEO_DISPLAY_LIST(LAYER_TRANSPARENT, flame_seg3_dl_blue_5),
         GEO_DISPLAY_LIST(LAYER_TRANSPARENT, flame_seg3_dl_blue_6),
         GEO_DISPLAY_LIST(LAYER_TRANSPARENT, flame_seg3_dl_blue_7),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
