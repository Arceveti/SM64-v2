// 0x0E0005B0
const GeoLayout thi_geo_huge_island_top[] = {
   GEO_CULLING_RADIUS(300),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, thi_seg7_dl_07007648),
   GEO_CLOSE_NODE(),
   GEO_END(),
};

// 0x0E0005C8
const GeoLayout thi_geo_tiny_island_top[] = {
   GEO_CULLING_RADIUS(300),
   GEO_OPEN_NODE(),
      GEO_SCALE(LAYER_FORCE, 19660),
      GEO_OPEN_NODE(),
         GEO_DISPLAY_LIST(LAYER_OPAQUE, thi_seg7_dl_07007648),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
