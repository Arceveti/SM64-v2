// 0x16000EA0
const GeoLayout star_geo[] = {
   GEO_SHADOW(SHADOW_CIRCLE_4_VERTS, 0x9B, 100),
   GEO_OPEN_NODE(),
      GEO_SCALE(LAYER_FORCE, 16384),
      GEO_OPEN_NODE(),
         GEO_DISPLAY_LIST(LAYER_NO_SILHOUETTE, star_seg3_dl_body),
         GEO_DISPLAY_LIST(LAYER_NO_SILHOUETTE_ALPHA, star_seg3_dl_eyes),
#ifdef STAR_GLOW
         GEO_BILLBOARD_WITH_ZOFFSET(-48),
         GEO_OPEN_NODE(),
            GEO_DISPLAY_LIST(LAYER_TRANSPARENT_INTER, star_seg3_dl_shine),
         GEO_CLOSE_NODE(),
#endif
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
