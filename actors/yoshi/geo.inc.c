// 0x0C000468
const GeoLayout yoshi_geo[] = {
   GEO_SHADOW(SHADOW_CIRCLE_4_VERTS, 0xC8, 100),
   GEO_OPEN_NODE(),
      GEO_SCALE(LAYER_FORCE, 16384),
      GEO_OPEN_NODE(),
         GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, NULL),
         GEO_OPEN_NODE(),
            GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, yoshi_seg5_dl_05022608),
            GEO_OPEN_NODE(),
               GEO_ANIMATED_PART(LAYER_OPAQUE, 100, 0, 0, yoshi_seg5_dl_05022408),
               GEO_OPEN_NODE(),
                  GEO_ANIMATED_PART(LAYER_OPAQUE, 222, 0, 0, NULL),
                  GEO_OPEN_NODE(),
                     GEO_SWITCH_CASE(2, geo_switch_anim_state),
                     GEO_OPEN_NODE(),
                        GEO_DISPLAY_LIST(LAYER_OPAQUE, yoshi_seg5_dl_eyes_open),
                        GEO_DISPLAY_LIST(LAYER_OPAQUE, yoshi_seg5_dl_eyes_closed),
                     GEO_CLOSE_NODE(),
                  GEO_CLOSE_NODE(),
                  GEO_OPEN_NODE(),
                     GEO_ANIMATED_PART(LAYER_OPAQUE, 76, 49, 0, NULL),
                     GEO_OPEN_NODE(),
                        GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, yoshi_seg5_dl_050212B0),
                     GEO_CLOSE_NODE(),
                  GEO_CLOSE_NODE(),
                  GEO_ANIMATED_PART(LAYER_OPAQUE, 51, 55, 97, NULL),
                  GEO_OPEN_NODE(),
                     GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, yoshi_seg5_dl_05021678),
                     GEO_OPEN_NODE(),
                        GEO_ANIMATED_PART(LAYER_OPAQUE, 74, 0, 0, yoshi_seg5_dl_050215D8),
                        GEO_OPEN_NODE(),
                           GEO_ANIMATED_PART(LAYER_OPAQUE, 69, 0, 0, yoshi_seg5_dl_05021490),
                        GEO_CLOSE_NODE(),
                     GEO_CLOSE_NODE(),
                  GEO_CLOSE_NODE(),
                  GEO_ANIMATED_PART(LAYER_OPAQUE, 51, 55, -97, NULL),
                  GEO_OPEN_NODE(),
                     GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, yoshi_seg5_dl_05021900),
                     GEO_OPEN_NODE(),
                        GEO_ANIMATED_PART(LAYER_OPAQUE, 74, 0, 0, yoshi_seg5_dl_05021860),
                        GEO_OPEN_NODE(),
                           GEO_ANIMATED_PART(LAYER_OPAQUE, 69, 0, 0, yoshi_seg5_dl_05021718),
                        GEO_CLOSE_NODE(),
                     GEO_CLOSE_NODE(),
                  GEO_CLOSE_NODE(),
               GEO_CLOSE_NODE(),
               GEO_ANIMATED_PART(LAYER_OPAQUE, -1, 27, 95, NULL),
               GEO_OPEN_NODE(),
                  GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, yoshi_seg5_dl_05021CD8),
                  GEO_OPEN_NODE(),
                     GEO_ANIMATED_PART(LAYER_OPAQUE, 100, 0, 0, yoshi_seg5_dl_05021B90),
                     GEO_OPEN_NODE(),
                        GEO_ANIMATED_PART(LAYER_OPAQUE, 95, 0, 0, yoshi_seg5_dl_050219A0),
                     GEO_CLOSE_NODE(),
                  GEO_CLOSE_NODE(),
               GEO_CLOSE_NODE(),
               GEO_ANIMATED_PART(LAYER_OPAQUE, -89, -62, 0, NULL),
               GEO_OPEN_NODE(),
                  GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, yoshi_seg5_dl_05021E38),
               GEO_CLOSE_NODE(),
               GEO_ANIMATED_PART(LAYER_OPAQUE, -1, 27, -95, NULL),
               GEO_OPEN_NODE(),
                  GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, yoshi_seg5_dl_050222A8),
                  GEO_OPEN_NODE(),
                     GEO_ANIMATED_PART(LAYER_OPAQUE, 100, 0, 0, yoshi_seg5_dl_05022160),
                     GEO_OPEN_NODE(),
                        GEO_ANIMATED_PART(LAYER_OPAQUE, 95, 0, 0, yoshi_seg5_dl_05021F70),
                     GEO_CLOSE_NODE(),
                  GEO_CLOSE_NODE(),
               GEO_CLOSE_NODE(),
            GEO_CLOSE_NODE(),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
