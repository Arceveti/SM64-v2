// 0x0E000918
const GeoLayout jrb_geo_falling_pillar_base[] = {
   GEO_CULLING_RADIUS(300),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, jrb_seg7_dl_falling_pillar_base),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
