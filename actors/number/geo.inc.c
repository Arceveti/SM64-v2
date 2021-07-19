// 0x16000E14
const GeoLayout number_geo[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
#ifdef DIALOG_INDICATOR
      GEO_SWITCH_CASE(16, geo_switch_anim_state),
#else
      GEO_SWITCH_CASE(10, geo_switch_anim_state),
#endif
      GEO_OPEN_NODE(),
         GEO_DISPLAY_LIST(LAYER_NO_SILHOUETTE_ALPHA, dl_billboard_num_0),
         GEO_DISPLAY_LIST(LAYER_NO_SILHOUETTE_ALPHA, dl_billboard_num_1),
         GEO_DISPLAY_LIST(LAYER_NO_SILHOUETTE_ALPHA, dl_billboard_num_2),
         GEO_DISPLAY_LIST(LAYER_NO_SILHOUETTE_ALPHA, dl_billboard_num_3),
         GEO_DISPLAY_LIST(LAYER_NO_SILHOUETTE_ALPHA, dl_billboard_num_4),
         GEO_DISPLAY_LIST(LAYER_NO_SILHOUETTE_ALPHA, dl_billboard_num_5),
         GEO_DISPLAY_LIST(LAYER_NO_SILHOUETTE_ALPHA, dl_billboard_num_6),
         GEO_DISPLAY_LIST(LAYER_NO_SILHOUETTE_ALPHA, dl_billboard_num_7),
         GEO_DISPLAY_LIST(LAYER_NO_SILHOUETTE_ALPHA, dl_billboard_num_8),
         GEO_DISPLAY_LIST(LAYER_NO_SILHOUETTE_ALPHA, dl_billboard_num_9),
#ifdef DIALOG_INDICATOR
         GEO_DISPLAY_LIST(LAYER_NO_SILHOUETTE_ALPHA, dl_billboard_num_A),
         GEO_DISPLAY_LIST(LAYER_NO_SILHOUETTE_ALPHA, dl_billboard_num_B),
         GEO_DISPLAY_LIST(LAYER_NO_SILHOUETTE_ALPHA, dl_billboard_num_C),
         GEO_DISPLAY_LIST(LAYER_NO_SILHOUETTE_ALPHA, dl_billboard_num_D),
         GEO_DISPLAY_LIST(LAYER_NO_SILHOUETTE_ALPHA, dl_billboard_num_E),
         GEO_DISPLAY_LIST(LAYER_NO_SILHOUETTE_ALPHA, dl_billboard_num_F),
#endif
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
