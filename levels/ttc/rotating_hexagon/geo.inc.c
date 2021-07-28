// 0x0E0002E0
const GeoLayout ttc_geo_rotating_hexagon[] = {
   GEO_CULLING_RADIUS(400),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, ttc_seg7_dl_rotating_hexagon),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
