// 0x0C000030
const GeoLayout wiggler_head_geo[] = {
   GEO_SHADOW(SHADOW_CIRCLE_4_VERTS, 0x96, 100),
   GEO_OPEN_NODE(),
      GEO_SCALE(LAYER_FORCE, 16384),
      GEO_OPEN_NODE(),
         GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, NULL),
         GEO_OPEN_NODE(),
            GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, NULL),
            GEO_OPEN_NODE(),
               GEO_BILLBOARD(),
               GEO_OPEN_NODE(),
                  GEO_DISPLAY_LIST(LAYER_ALPHA, wiggler_seg5_dl_segment),
               GEO_CLOSE_NODE(),
            GEO_CLOSE_NODE(),
            GEO_OPEN_NODE(),
               GEO_ANIMATED_PART(LAYER_OPAQUE, 157, 0, 0, NULL),
               GEO_OPEN_NODE(),
                  GEO_BILLBOARD(),
                  GEO_OPEN_NODE(),
                     GEO_DISPLAY_LIST(LAYER_ALPHA, wiggler_seg5_dl_head_sphere),
                  GEO_CLOSE_NODE(),
               GEO_CLOSE_NODE(),
               GEO_OPEN_NODE(),
                  GEO_ANIMATED_PART(LAYER_OPAQUE, 143, 0, 0, NULL),
                  GEO_OPEN_NODE(),
                     GEO_BILLBOARD(),
                     GEO_OPEN_NODE(),
                        GEO_DISPLAY_LIST(LAYER_ALPHA, wiggler_seg5_dl_nose),
                     GEO_CLOSE_NODE(),
                  GEO_CLOSE_NODE(),
                  GEO_ANIMATED_PART(LAYER_OPAQUE, 143, 0, 0, NULL),
               GEO_CLOSE_NODE(),
               GEO_ANIMATED_PART(LAYER_ALPHA, 157, 0, 0, wiggler_seg5_dl_flower),
               GEO_ANIMATED_PART(LAYER_ALPHA, 157, 0, 0, wiggler_seg5_dl_eyes),
               GEO_ANIMATED_PART(LAYER_ALPHA, 157, 0, 0, wiggler_seg5_dl_frown),
               GEO_ANIMATED_PART(LAYER_OPAQUE, -16, 23, 51, NULL),
               GEO_OPEN_NODE(),
                  GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, wiggler_seg5_dl_0500DDF8),
                  GEO_OPEN_NODE(),
                     GEO_ANIMATED_PART(LAYER_OPAQUE, 39, 0, 0, wiggler_seg5_dl_0500DD70),
                     GEO_OPEN_NODE(),
                        GEO_ANIMATED_PART(LAYER_OPAQUE, 41, 0, 0, wiggler_seg5_dl_0500DC18),
                     GEO_CLOSE_NODE(),
                  GEO_CLOSE_NODE(),
               GEO_CLOSE_NODE(),
               GEO_ANIMATED_PART(LAYER_OPAQUE, -16, 23, -49, NULL),
               GEO_OPEN_NODE(),
                  GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, wiggler_seg5_dl_0500E060),
                  GEO_OPEN_NODE(),
                     GEO_ANIMATED_PART(LAYER_OPAQUE, 39, 0, 0, wiggler_seg5_dl_0500DFD8),
                     GEO_OPEN_NODE(),
                        GEO_ANIMATED_PART(LAYER_OPAQUE, 41, 0, 0, wiggler_seg5_dl_0500DE80),
                     GEO_CLOSE_NODE(),
                  GEO_CLOSE_NODE(),
               GEO_CLOSE_NODE(),
            GEO_CLOSE_NODE(),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
