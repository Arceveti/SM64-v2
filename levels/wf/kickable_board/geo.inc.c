// 0x0E000BA8
const GeoLayout wf_geo_kickable_board_standing[] = {
   GEO_CULLING_RADIUS(1300),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, wf_seg7_dl_kickable_board),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, wf_seg7_dl_kickable_board_shadow),
   GEO_CLOSE_NODE(),
   GEO_END(),
};

// 0x0E000BC8
const GeoLayout wf_geo_kickable_board_fallen[] = {
   GEO_CULLING_RADIUS(1300),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, wf_seg7_dl_kickable_board),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
