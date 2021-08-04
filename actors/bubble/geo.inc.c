// 0x17000000
const GeoLayout bubble_geo[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OCCLUDE_SILHOUETTE_ALPHA, bubble_seg4_dl_bubble),
   GEO_CLOSE_NODE(),
   GEO_END(),
};

// 0x1700001C
const GeoLayout purple_marble_geo[] = {
   GEO_NODE_START(),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OCCLUDE_SILHOUETTE_ALPHA, bubble_seg4_dl_mr_i_bubble),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
