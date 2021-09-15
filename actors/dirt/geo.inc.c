// 0x16000ED4
const GeoLayout dirt_animation_geo[] = {
   GEO_CULLING_RADIUS(300),
   GEO_OPEN_NODE(),
      GEO_SWITCH_CASE(6, geo_switch_anim_state),
      GEO_OPEN_NODE(),
         GEO_DISPLAY_LIST(LAYER_OCCLUDE_SILHOUETTE_OPAQUE, dirt_seg3_dl_tiny_particle_red      ), // 0
         GEO_DISPLAY_LIST(LAYER_OCCLUDE_SILHOUETTE_OPAQUE, dirt_seg3_dl_tiny_particle_green    ), // 1
         GEO_DISPLAY_LIST(LAYER_OCCLUDE_SILHOUETTE_OPAQUE, dirt_seg3_dl_tiny_particle_blue     ), // 2
         GEO_DISPLAY_LIST(LAYER_OCCLUDE_SILHOUETTE_ALPHA,  dirt_seg3_dl_dirt_particle          ), // 3
         GEO_DISPLAY_LIST(LAYER_OCCLUDE_SILHOUETTE_OPAQUE, dirt_seg3_dl_tiny_particle_yellow   ), // 4
         GEO_DISPLAY_LIST(LAYER_OCCLUDE_SILHOUETTE_OPAQUE, dirt_seg3_dl_tiny_particle_billboard), // 5
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};

// This is probably wrongly named according to the Bin IDs...
// 0x16000F24
const GeoLayout cartoon_star_geo[] = {
   GEO_CULLING_RADIUS(300),
   GEO_OPEN_NODE(),
      GEO_SWITCH_CASE(5, geo_switch_anim_state),
      GEO_OPEN_NODE(),
         GEO_DISPLAY_LIST(LAYER_OCCLUDE_SILHOUETTE_OPAQUE, dirt_seg3_dl_cartoon_star_red      ), // 0
         GEO_DISPLAY_LIST(LAYER_OCCLUDE_SILHOUETTE_OPAQUE, dirt_seg3_dl_cartoon_star_green    ), // 1
         GEO_DISPLAY_LIST(LAYER_OCCLUDE_SILHOUETTE_OPAQUE, dirt_seg3_dl_cartoon_star_blue     ), // 2
         GEO_DISPLAY_LIST(LAYER_OCCLUDE_SILHOUETTE_OPAQUE, dirt_seg3_dl_cartoon_star_yellow   ), // 3
         GEO_DISPLAY_LIST(LAYER_OCCLUDE_SILHOUETTE_OPAQUE, dirt_seg3_dl_cartoon_star_billboard), // 4
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
