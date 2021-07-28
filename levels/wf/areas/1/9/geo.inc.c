// 0x0E000890
const GeoLayout wf_geo_floating_brick_platform[] = {
   GEO_CULLING_RADIUS(1000),
   GEO_OPEN_NODE(),
      GEO_DISPLAY_LIST(LAYER_OPAQUE, wf_seg7_dl_floating_brick_platform),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
