// 0x0E000F00
const GeoLayout castle_geo_star_door[] = {
   GEO_CULLING_RADIUS(400),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, inside_castle_seg7_dl_star_door),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
