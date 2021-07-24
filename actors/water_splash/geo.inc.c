// 0x17000230
const GeoLayout water_splash_geo[] = {
   GEO_SWITCH_CASE(8, geo_switch_anim_state),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_NO_SILHOUETTE_ALPHA, water_splash_seg4_dl_0),
      GEO_DISPLAY_LIST(LAYER_NO_SILHOUETTE_ALPHA, water_splash_seg4_dl_1),
      GEO_DISPLAY_LIST(LAYER_NO_SILHOUETTE_ALPHA, water_splash_seg4_dl_2),
      GEO_DISPLAY_LIST(LAYER_NO_SILHOUETTE_ALPHA, water_splash_seg4_dl_3),
      GEO_DISPLAY_LIST(LAYER_NO_SILHOUETTE_ALPHA, water_splash_seg4_dl_4),
      GEO_DISPLAY_LIST(LAYER_NO_SILHOUETTE_ALPHA, water_splash_seg4_dl_5),
      GEO_DISPLAY_LIST(LAYER_NO_SILHOUETTE_ALPHA, water_splash_seg4_dl_6),
      GEO_DISPLAY_LIST(LAYER_NO_SILHOUETTE_ALPHA, water_splash_seg4_dl_7),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
