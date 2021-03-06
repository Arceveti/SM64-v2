// 0x0F000AB0
const GeoLayout koopa_shell_geo[] = {
   GEO_SHADOW(SHADOW_CIRCLE_4_VERTS, 0xC8, 70),
   GEO_OPEN_NODE(),
      GEO_SCALE(LAYER_FORCE, 65536),
      GEO_OPEN_NODE(),
         GEO_DISPLAY_LIST(LAYER_SILHOUETTE_OPAQUE, koopa_shell_seg8_dl_green_koopa_shell),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};

// // 0x0F000ADC
// const GeoLayout koopa_shell2_geo[] = {
//    GEO_SHADOW(SHADOW_CIRCLE_4_VERTS, 0xC8, 70),
//    GEO_OPEN_NODE(),
//       GEO_SCALE(LAYER_FORCE, 16384),
//       GEO_OPEN_NODE(),
//          GEO_DISPLAY_LIST(LAYER_SILHOUETTE_OPAQUE, koopa_shell_seg8_dl_08027420),
//       GEO_CLOSE_NODE(),
//    GEO_CLOSE_NODE(),
//    GEO_END(),
// };

// // 0x0F000B08
// const GeoLayout koopa_shell3_geo[] = {
//    GEO_SHADOW(SHADOW_CIRCLE_4_VERTS, 0xC8, 70),
//    GEO_OPEN_NODE(),
//       GEO_SCALE(LAYER_FORCE, 16384),
//       GEO_OPEN_NODE(),
//          GEO_DISPLAY_LIST(LAYER_SILHOUETTE_OPAQUE, koopa_shell_seg8_dl_080273C8),
//       GEO_CLOSE_NODE(),
//    GEO_CLOSE_NODE(),
//    GEO_END(),
// };
