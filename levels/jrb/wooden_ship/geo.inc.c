// 0x0E000978
const GeoLayout jrb_geo_ship_left_half_part[] = {
   GEO_CULLING_RADIUS(5000),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, jrb_seg7_dl_07008FD8),
   GEO_CLOSE_NODE(),
   GEO_END(),
};

// 0x0E000990
const GeoLayout jrb_geo_sunken_ship[] = {
   GEO_CULLING_RADIUS(5000),
   GEO_OPEN_NODE(),
      GEO_ASM(0, geo_update_layer_transparency),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, jrb_seg7_dl_070090B0),
   GEO_CLOSE_NODE(),
   GEO_END(),
};

// 0x0E0009B0
const GeoLayout jrb_geo_ship_back_left_part[] = {
   GEO_CULLING_RADIUS(5000),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, jrb_seg7_dl_07009A58),
   GEO_CLOSE_NODE(),
   GEO_END(),
};

// 0x0E0009C8
const GeoLayout jrb_geo_sunken_ship_back[] = {
   GEO_CULLING_RADIUS(5000),
   GEO_OPEN_NODE(),
      GEO_ASM(0, geo_update_layer_transparency),
      GEO_DISPLAY_LIST(LAYER_TRANSPARENT, jrb_seg7_dl_07009B30),
   GEO_CLOSE_NODE(),
   GEO_END(),
};

// 0x0E0009E8
const GeoLayout jrb_geo_ship_right_half_part[] = {
   GEO_CULLING_RADIUS(5000),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, jrb_seg7_dl_0700A608),
   GEO_CLOSE_NODE(),
   GEO_END(),
};

// 0x0E000A00
const GeoLayout jrb_geo_ship_back_right_part[] = {
   GEO_CULLING_RADIUS(5000),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, jrb_seg7_dl_0700AC68),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
