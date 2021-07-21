// 0x0D000480
const GeoLayout whomp_geo[] = {
   GEO_CULLING_RADIUS(2000),
   GEO_OPEN_NODE(),
      GEO_TRANSLATE_NODE(LAYER_FORCE, 0, 0, -50),
      GEO_OPEN_NODE(),
         GEO_SHADOW(0x01 + SHADOW_RECTANGLE_HARDCODED_OFFSET, 0xB4, 0),
         GEO_OPEN_NODE(),
            GEO_SCALE(LAYER_FORCE, 16384),
            GEO_OPEN_NODE(),
               GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, NULL),
               GEO_OPEN_NODE(),
                  GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, whomp_seg6_dl_0601F5E0),
                  GEO_OPEN_NODE(),
                     GEO_ANIMATED_PART(LAYER_OPAQUE, -12, 490, -5, NULL),
                     GEO_OPEN_NODE(),
                        GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, whomp_seg6_dl_0601FEA8),
                     GEO_CLOSE_NODE(),
                     GEO_ANIMATED_PART(LAYER_OPAQUE, -18, -479, -5, NULL),
                     GEO_OPEN_NODE(),
                        GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, whomp_seg6_dl_06020038),
                     GEO_CLOSE_NODE(),
                     GEO_ANIMATED_PART(LAYER_OPAQUE, 1075, 570, 0, NULL),
                     GEO_OPEN_NODE(),
                        GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, whomp_seg6_dl_0601F880),
                        GEO_OPEN_NODE(),
                           GEO_ANIMATED_PART(LAYER_ALPHA, 400, 0, 0, NULL),
                           GEO_OPEN_NODE(),
                              GEO_BILLBOARD(),
                              GEO_OPEN_NODE(),
                                 GEO_DISPLAY_LIST(LAYER_ALPHA, whomp_seg6_dl_0601FBC0),
                              GEO_CLOSE_NODE(),
                           GEO_CLOSE_NODE(),
                        GEO_CLOSE_NODE(),
                     GEO_CLOSE_NODE(),
                     GEO_ANIMATED_PART(LAYER_OPAQUE, 1068, -574, 0, NULL),
                     GEO_OPEN_NODE(),
                        GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, whomp_seg6_dl_0601FAE8),
                        GEO_OPEN_NODE(),
                           GEO_ANIMATED_PART(LAYER_ALPHA, 400, 0, 0, NULL),
                           GEO_OPEN_NODE(),
                              GEO_BILLBOARD(),
                              GEO_OPEN_NODE(),
                                 GEO_DISPLAY_LIST(LAYER_ALPHA, whomp_seg6_dl_0601FCA8),
                              GEO_CLOSE_NODE(),
                           GEO_CLOSE_NODE(),
                        GEO_CLOSE_NODE(),
                     GEO_CLOSE_NODE(),
                  GEO_CLOSE_NODE(),
               GEO_CLOSE_NODE(),
            GEO_CLOSE_NODE(),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
