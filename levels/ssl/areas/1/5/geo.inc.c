// 0x0E0005C0
const GeoLayout ssl_geo_quicksand_pit_outside[] = {
   GEO_CULLING_RADIUS(2000),
   GEO_OPEN_NODE(),
      GEO_ASM(MOVTEX_SSL_SAND_PIT_OUTSIDE, geo_movtex_draw_colored_2_no_update),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
