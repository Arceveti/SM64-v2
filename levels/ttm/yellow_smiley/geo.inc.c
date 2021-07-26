// 0x0E000D4C
const GeoLayout ttm_geo_yellow_smiley[] = {
   GEO_CULLING_RADIUS(1000),
   GEO_OPEN_NODE(),
      GEO_BILLBOARD(),
      GEO_OPEN_NODE(),
         GEO_SCALE(LAYER_FORCE, 32768),
         GEO_OPEN_NODE(),
            GEO_DISPLAY_LIST(LAYER_ALPHA, ttm_seg7_dl_yellow_smiley),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
