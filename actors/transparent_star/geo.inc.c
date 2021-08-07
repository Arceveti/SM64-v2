// 0x16000F6C
const GeoLayout transparent_star_geo[] = {
   GEO_SHADOW(SHADOW_CIRCLE_4_VERTS, 0x9B, 100),
   GEO_OPEN_NODE(),
      GEO_SCALE(LAYER_FORCE, 16384),
      GEO_OPEN_NODE(),
         GEO_DISPLAY_LIST(LAYER_TRANSPARENT, transparent_star_seg3_dl),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
