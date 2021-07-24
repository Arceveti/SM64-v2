// 0x0D000B78 / 0BBC
const GeoLayout bowser_bomb_geo[] = {
   GEO_CULLING_RADIUS(1000),
   GEO_OPEN_NODE(),
      GEO_SCALE(LAYER_FORCE, 196608),
      GEO_OPEN_NODE(),
         GEO_DISPLAY_LIST(LAYER_OPAQUE, bomb_seg6_dl_spikes),
         GEO_BILLBOARD(),
         GEO_OPEN_NODE(),
            GEO_DISPLAY_LIST(LAYER_ALPHA, bomb_seg6_dl_sphere_billboard),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
