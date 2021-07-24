// 0x16000FB4
const GeoLayout wooden_signpost_geo[] = {
   GEO_SHADOW(SHADOW_CIRCLE_4_VERTS, 0xC8, 60),
   GEO_OPEN_NODE(),
      GEO_SCALE(LAYER_FORCE, 16384),
      GEO_OPEN_NODE(),
         GEO_DISPLAY_LIST(LAYER_OPAQUE, wooden_signpost_seg3_dl_post),
         GEO_DISPLAY_LIST(LAYER_OPAQUE, wooden_signpost_seg3_dl_sign),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
