// 0x0E000340
const GeoLayout ttc_geo_elevator_platform[] = {
   GEO_CULLING_RADIUS(380),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, ttc_seg7_dl_elevator_platform),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
