// 0x0C0001E4
const GeoLayout yoshi_egg_geo[] = {
   GEO_SCALE(LAYER_FORCE, 16384),
   GEO_OPEN_NODE(),
      GEO_SWITCH_CASE(8, geo_switch_anim_state),
      GEO_OPEN_NODE(),
         GEO_DISPLAY_LIST(LAYER_ALPHA, yoshi_egg_seg5_dl_0),
         GEO_DISPLAY_LIST(LAYER_ALPHA, yoshi_egg_seg5_dl_1),
         GEO_DISPLAY_LIST(LAYER_ALPHA, yoshi_egg_seg5_dl_2),
         GEO_DISPLAY_LIST(LAYER_ALPHA, yoshi_egg_seg5_dl_3),
         GEO_DISPLAY_LIST(LAYER_ALPHA, yoshi_egg_seg5_dl_4),
         GEO_DISPLAY_LIST(LAYER_ALPHA, yoshi_egg_seg5_dl_5),
         GEO_DISPLAY_LIST(LAYER_ALPHA, yoshi_egg_seg5_dl_6),
         GEO_DISPLAY_LIST(LAYER_ALPHA, yoshi_egg_seg5_dl_7),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
