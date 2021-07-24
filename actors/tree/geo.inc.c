// 0x16000FE8
const GeoLayout bubbly_tree_geo[] = {
   GEO_CULLING_RADIUS(800),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_ALPHA, tree_seg3_dl_bubbly),
   GEO_CLOSE_NODE(),
   GEO_END(),
};

// 0x16001000
const GeoLayout spiky_tree_geo[] = {
   GEO_CULLING_RADIUS(800),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_ALPHA, tree_seg3_dl_spiky),
   GEO_CLOSE_NODE(),
   GEO_END(),
};

// 0x16001018
const GeoLayout snow_tree_geo[] = {
   GEO_CULLING_RADIUS(800),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_ALPHA, tree_seg3_dl_snowy_pine),
   GEO_CLOSE_NODE(),
   GEO_END(),
};

// 0x16001030
const GeoLayout spiky_tree1_geo[] = {
   GEO_CULLING_RADIUS(800),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_ALPHA, tree_seg3_dl_spiky1),
   GEO_CLOSE_NODE(),
   GEO_END(),
};

// 0x16001048
const GeoLayout palm_tree_geo[] = {
   GEO_CULLING_RADIUS(800),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_ALPHA, tree_seg3_dl_palm),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
