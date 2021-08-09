// 0x0E0005C0
const GeoLayout wdw_geo_water_level_diamond[] = {
   GEO_CULLING_RADIUS(200),
   GEO_OPEN_NODE(),
      GEO_SHADOW(SHADOW_SQUARE_SCALABLE, 0x96, 90),
      GEO_OPEN_NODE(),
         GEO_DISPLAY_LIST(LAYER_OPAQUE, wdw_seg7_dl_water_level_diamond),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
