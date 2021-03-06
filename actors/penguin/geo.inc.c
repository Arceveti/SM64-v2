// 0x0C000104
const GeoLayout penguin_geo[] = {
// #if defined(VERSION_EU) || defined(VERSION_SH)
       GEO_SHADOW(SHADOW_CIRCLE_9_VERTS, 0x96, 60),
// #else
//        GEO_SHADOW(SHADOW_CIRCLE_4_VERTS, 0x96, 100),
// #endif
       GEO_OPEN_NODE(),
          GEO_SCALE(LAYER_FORCE, 16384),
          GEO_OPEN_NODE(),
             GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 40, penguin_seg5_dl_05007540),
             GEO_OPEN_NODE(),
                GEO_ANIMATED_PART(LAYER_OPAQUE, -51, 84, -13, NULL),
                GEO_OPEN_NODE(),
                   GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, penguin_seg5_dl_05007198),
                GEO_CLOSE_NODE(),
                GEO_ANIMATED_PART(LAYER_OPAQUE, 51, 84, -13, NULL),
                GEO_OPEN_NODE(),
                   GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, penguin_seg5_dl_050071E8),
                GEO_CLOSE_NODE(),
                GEO_ANIMATED_PART(LAYER_OPAQUE, -38, -54, -13, NULL),
                GEO_OPEN_NODE(),
                   GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, penguin_seg5_dl_05007238),
                GEO_CLOSE_NODE(),
                GEO_ANIMATED_PART(LAYER_OPAQUE, 38, -54, -13, NULL),
                GEO_OPEN_NODE(),
                   GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, penguin_seg5_dl_050072C8),
                GEO_CLOSE_NODE(),
                GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 111, -19, NULL),
                GEO_OPEN_NODE(),
#ifdef PENGUIN_MOTHER_SAD_EYES
                   GEO_SWITCH_CASE(5, geo_switch_tuxie_mother_eyes),
#else
                   GEO_SWITCH_CASE(4, geo_switch_tuxie_mother_eyes),
#endif
                   GEO_OPEN_NODE(),
                      GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, penguin_seg5_dl_eye_open),
                      GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, penguin_seg5_dl_eye_half_closed),
                      GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, penguin_seg5_dl_eye_closed),
                      GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, penguin_seg5_dl_eye_angry),
#ifdef PENGUIN_MOTHER_SAD_EYES
                      GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, penguin_seg5_dl_eye_sad),
#endif
                   GEO_CLOSE_NODE(),
                GEO_CLOSE_NODE(),
             GEO_CLOSE_NODE(),
          GEO_CLOSE_NODE(),
       GEO_CLOSE_NODE(),
       GEO_END(),
};
