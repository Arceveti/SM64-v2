// 0x0C00010C
const GeoLayout unagi_geo[] = {
   GEO_CULLING_RADIUS(2000),
   GEO_OPEN_NODE(),
      GEO_SCALE(LAYER_FORCE, 49152),
      GEO_OPEN_NODE(),
         GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, NULL),
         GEO_OPEN_NODE(),
            GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, unagi_seg5_dl_0500D268),
            GEO_OPEN_NODE(),
               GEO_ANIMATED_PART(LAYER_OPAQUE, 245, 0, 0, unagi_seg5_dl_0500D468),
               GEO_OPEN_NODE(),
                  GEO_ANIMATED_PART(LAYER_OPAQUE, 494, 0, 0, unagi_seg5_dl_0500D668),
                  GEO_OPEN_NODE(),
                     GEO_ANIMATED_PART(LAYER_OPAQUE, 475, 0, 0, unagi_seg5_dl_0500D828),
                     GEO_OPEN_NODE(),
#ifdef HELD_TRANSPARENT_STAR
                        GEO_SWITCH_CASE(3, geo_switch_anim_state),
#else
                        GEO_SWITCH_CASE(2, geo_switch_anim_state),
#endif
                        GEO_OPEN_NODE(),
                           GEO_NODE_START(),
                           GEO_NODE_START(),
                           GEO_OPEN_NODE(),
                              GEO_SCALE(LAYER_FORCE, 16384),
                              GEO_OPEN_NODE(),
                                 GEO_TRANSLATE_ROTATE_WITH_DL(LAYER_OCCLUDE_SILHOUETTE_OPAQUE, 2000, 0, 0, 0, 0, 0, star_seg3_dl_body),
                                 GEO_TRANSLATE_ROTATE_WITH_DL(LAYER_OCCLUDE_SILHOUETTE_ALPHA, 2000, 0, 0, 0, 0, 0, star_seg3_dl_eyes),
#ifdef STAR_GLOW
                                 GEO_TRANSLATE_ROTATE(LAYER_FORCE, 2000, 0, 0, 0, 0, 0),
                                 GEO_OPEN_NODE(),
                                    GEO_BILLBOARD_WITH_ZOFFSET(-48),
                                    GEO_OPEN_NODE(),
                                       GEO_DISPLAY_LIST(LAYER_TRANSPARENT_INTER, star_seg3_dl_shine),
                                    GEO_CLOSE_NODE(),
                                 GEO_CLOSE_NODE(),
#endif
                              GEO_CLOSE_NODE(),
                           GEO_CLOSE_NODE(),
#ifdef HELD_TRANSPARENT_STAR
                           GEO_NODE_START(),
                           GEO_OPEN_NODE(),
                              GEO_SCALE(LAYER_FORCE, 16384),
                              GEO_OPEN_NODE(),
                                 GEO_TRANSLATE_ROTATE_WITH_DL(LAYER_TRANSPARENT, 2000, 0, 0, 0, 0, 0, transparent_star_seg3_dl),
                              GEO_CLOSE_NODE(),
                           GEO_CLOSE_NODE(),
#endif
                        GEO_CLOSE_NODE(),
                     GEO_CLOSE_NODE(),
                  GEO_CLOSE_NODE(),
               GEO_CLOSE_NODE(),
               GEO_ANIMATED_PART(LAYER_OPAQUE, -254, 0, 0, NULL),
               GEO_OPEN_NODE(),
                  GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, unagi_seg5_dl_0500D050),
                  GEO_OPEN_NODE(),
                     GEO_ANIMATED_PART(LAYER_ALPHA, 527, 0, 0, unagi_seg5_dl_0500DEB8),
                     GEO_OPEN_NODE(),
                        GEO_ANIMATED_PART(LAYER_OPAQUE, 226, 65, 0, NULL),
                        GEO_OPEN_NODE(),
                           GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 0, unagi_seg5_dl_0500E258),
                           GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, unagi_seg5_dl_0500CDD0),
                           GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, NULL),
                        GEO_CLOSE_NODE(),
                     GEO_CLOSE_NODE(),
                     GEO_ANIMATED_PART(LAYER_ALPHA, 527, 0, 0, unagi_seg5_dl_0500E088),
                     GEO_ANIMATED_PART(LAYER_OPAQUE, 527, 0, 0, unagi_seg5_dl_0500DD08),
                     GEO_ANIMATED_PART(LAYER_OPAQUE, 527, 0, 0, NULL),
                  GEO_CLOSE_NODE(),
               GEO_CLOSE_NODE(),
            GEO_CLOSE_NODE(),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
