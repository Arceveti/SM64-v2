// 0x17000038
const GeoLayout smoke_geo[] = {
   GEO_SWITCH_CASE(7, geo_switch_anim_state),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, smoke_seg4_dl_walk_smoke_0),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, smoke_seg4_dl_walk_smoke_1),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, smoke_seg4_dl_walk_smoke_2),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, smoke_seg4_dl_walk_smoke_3),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, smoke_seg4_dl_walk_smoke_4),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, smoke_seg4_dl_walk_smoke_5),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, smoke_seg4_dl_walk_smoke_6),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
