// 0x0E0005D0
const GeoLayout hmc_geo_elevator_platform[] = {
   GEO_CULLING_RADIUS(500),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, hmc_seg7_dl_elevator_platform),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
