// 0x0E000BB0
const GeoLayout lll_geo_rotating_hexagonal_ring[] = {
   GEO_CULLING_RADIUS(2100),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, lll_seg7_dl_rotating_hexagonal_ring),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
