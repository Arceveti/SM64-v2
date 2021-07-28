// 0x0E000B10
const GeoLayout wf_geo_square_platform[] = {
   GEO_CULLING_RADIUS(650),
   GEO_OPEN_NODE(),
      GEO_SHADOW(SHADOW_SQUARE_PERMANENT, 0x96, 480),
      GEO_OPEN_NODE(),
         GEO_DISPLAY_LIST(LAYER_OPAQUE, wf_seg7_dl_extending_platform),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};

// 0x0E000B38
const GeoLayout wf_geo_square_platform_unused[] = {
   GEO_CULLING_RADIUS(650),
   GEO_OPEN_NODE(),
      GEO_SHADOW(SHADOW_SQUARE_PERMANENT, 0x96, 480),
      GEO_OPEN_NODE(),
         GEO_DISPLAY_LIST(LAYER_OPAQUE, wf_seg7_dl_extending_platform),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};

// 0x0E000B60
const GeoLayout wf_geo_square_platform_elevator[] = {
   GEO_CULLING_RADIUS(650),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, wf_seg7_dl_extending_platform),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
