// 0x0E000530
const GeoLayout hmc_geo_grill_door[] = {
   GEO_CULLING_RADIUS(1000),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_ALPHA, hmc_seg7_dl_grill_door),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
