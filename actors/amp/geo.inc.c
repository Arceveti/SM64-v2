const GeoLayout dAmpGeo[] = {
   GEO_SHADOW(SHADOW_CIRCLE_4_VERTS, 0xC8, 100),
   GEO_OPEN_NODE(),
      GEO_SCALE(LAYER_FORCE, 16384),
      GEO_OPEN_NODE(),
         GEO_ANIMATED_PART(LAYER_NO_SILHOUETTE, 0, 0, 0, NULL),
         GEO_OPEN_NODE(),
            GEO_ANIMATED_PART(LAYER_NO_SILHOUETTE_ALPHA, 0, 0, 0, dAmpEyeDl),
            GEO_OPEN_NODE(),
               GEO_ANIMATED_PART(LAYER_NO_SILHOUETTE, 0, 0, 0, NULL),
               GEO_OPEN_NODE(),
                  GEO_SWITCH_CASE(2, geo_switch_anim_state),
                  GEO_OPEN_NODE(),
                     GEO_ANIMATED_PART(LAYER_NO_SILHOUETTE, 0, 0, 0, NULL),
                     GEO_ANIMATED_PART(LAYER_NO_SILHOUETTE_ALPHA, 0, 0, 0, dAmpElectricityDl),
                  GEO_CLOSE_NODE(),
               GEO_CLOSE_NODE(),
               GEO_ANIMATED_PART(LAYER_NO_SILHOUETTE, 0, 0, 0, NULL),
               GEO_OPEN_NODE(),
                  GEO_SWITCH_CASE(2, geo_switch_anim_state),
                  GEO_OPEN_NODE(),
                     GEO_ANIMATED_PART(LAYER_NO_SILHOUETTE, 0, 0, 0, NULL),
                     GEO_ANIMATED_PART(LAYER_NO_SILHOUETTE_ALPHA, 0, 0, 0, dAmpElectricityDl),
                  GEO_CLOSE_NODE(),
               GEO_CLOSE_NODE(),
               GEO_ANIMATED_PART(LAYER_NO_SILHOUETTE, 0, 0, 0, NULL),
               GEO_OPEN_NODE(),
                  GEO_SWITCH_CASE(2, geo_switch_anim_state),
                  GEO_OPEN_NODE(),
                     GEO_ANIMATED_PART(LAYER_NO_SILHOUETTE, 0, 0, 0, NULL),
                     GEO_ANIMATED_PART(LAYER_NO_SILHOUETTE_ALPHA, 0, 0, 0, dAmpElectricityDl),
                  GEO_CLOSE_NODE(),
               GEO_CLOSE_NODE(),
               GEO_ANIMATED_PART(LAYER_NO_SILHOUETTE, 0, 0, 0, NULL),
               GEO_OPEN_NODE(),
                  GEO_SWITCH_CASE(2, geo_switch_anim_state),
                  GEO_OPEN_NODE(),
                     GEO_ANIMATED_PART(LAYER_NO_SILHOUETTE, 0, 0, 0, NULL),
                     GEO_ANIMATED_PART(LAYER_NO_SILHOUETTE_ALPHA, 0, 0, 0, dAmpElectricityDl),
                  GEO_CLOSE_NODE(),
               GEO_CLOSE_NODE(),
            GEO_CLOSE_NODE(),
            GEO_ANIMATED_PART(LAYER_NO_SILHOUETTE_ALPHA, 0, 0, 0, dAmpMouthDl),
            GEO_ANIMATED_PART(LAYER_NO_SILHOUETTE, 0, 0, 0, NULL),
            GEO_OPEN_NODE(),
               GEO_BILLBOARD(),
               GEO_OPEN_NODE(),
                  GEO_DISPLAY_LIST(LAYER_ALPHA, dAmpBodyDl),
               GEO_CLOSE_NODE(),
            GEO_CLOSE_NODE(),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
