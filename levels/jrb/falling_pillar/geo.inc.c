// 0x0E000900
const GeoLayout jrb_geo_falling_pillar[] = {
   GEO_CULLING_RADIUS(1600),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, jrb_seg7_dl_falling_pillar),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
