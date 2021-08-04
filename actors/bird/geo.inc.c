// 0x0C000000
const GeoLayout birds_geo[] = {
   GEO_SHADOW(SHADOW_CIRCLE_4_VERTS, 0x96, 100),
   GEO_OPEN_NODE(),
      GEO_SCALE(LAYER_FORCE, 16384),
      GEO_OPEN_NODE(),
         GEO_ANIMATED_PART(LAYER_OCCLUDE_SILHOUETTE_OPAQUE, 0, 0, 0, NULL),
         GEO_OPEN_NODE(),
            GEO_ANIMATED_PART(LAYER_OCCLUDE_SILHOUETTE_OPAQUE, 0, 0, 0, birds_seg5_dl_05000670),
            GEO_OPEN_NODE(),
               GEO_ANIMATED_PART(LAYER_OCCLUDE_SILHOUETTE_OPAQUE, 1, -12, 37, NULL),
               GEO_OPEN_NODE(),
                  GEO_ANIMATED_PART(LAYER_OCCLUDE_SILHOUETTE_OPAQUE, 0, 0, 0, birds_seg5_dl_05000528),
               GEO_CLOSE_NODE(),
               GEO_ANIMATED_PART(LAYER_OCCLUDE_SILHOUETTE_OPAQUE, 1, -12, -37, NULL),
               GEO_OPEN_NODE(),
                  GEO_ANIMATED_PART(LAYER_OCCLUDE_SILHOUETTE_OPAQUE, 0, 0, 0, birds_seg5_dl_05000600),
               GEO_CLOSE_NODE(),
            GEO_CLOSE_NODE(),
            GEO_ANIMATED_PART(LAYER_OCCLUDE_SILHOUETTE_OPAQUE, 0, 0, 0, birds_seg5_dl_05000598),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
