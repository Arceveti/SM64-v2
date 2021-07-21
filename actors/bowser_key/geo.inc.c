// 0x16000A84
const GeoLayout bowser_key_geo[] = {
   GEO_SHADOW(SHADOW_CIRCLE_4_VERTS, 0x9B, 300),
   GEO_OPEN_NODE(),
      GEO_SCALE(LAYER_FORCE, 65536),
      GEO_OPEN_NODE(),
         GEO_DISPLAY_LIST(LAYER_NO_SILHOUETTE, bowser_key_dl),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};

// 0x16000AB0
const GeoLayout bowser_key_cutscene_geo[] = {
   GEO_SCALE(LAYER_FORCE, 16384),
   GEO_OPEN_NODE(),
      GEO_ANIMATED_PART(LAYER_NO_SILHOUETTE, 0, 0, 0, NULL),
      GEO_OPEN_NODE(),
         GEO_ANIMATED_PART(LAYER_NO_SILHOUETTE, 0, 0, 0, NULL),
         GEO_OPEN_NODE(),
            GEO_ASM(0, geo_scale_bowser_key),
            GEO_SCALE(LAYER_FORCE, 65536),
            GEO_OPEN_NODE(),
               GEO_DISPLAY_LIST(LAYER_NO_SILHOUETTE, bowser_key_dl),
            GEO_CLOSE_NODE(),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
