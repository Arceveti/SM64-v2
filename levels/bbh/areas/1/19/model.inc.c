// 0x07011228 - 0x07011240
static const Lights1 bbh_seg7_lights_07011228 = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07011240 - 0x070112C0
static const Vtx bbh_seg7_vertex_07011240[] = {
    {{{ -1075,    819,    819}, 0, {127<<5,  -3104}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -819,    819,    819}, 0, { -1056,  -3104}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -819,    819,    461}, 0, { -1056, 127<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{ -1075,    819,    461}, 0, {127<<5, 127<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -819,    819,    717}, 0, { -1056,  -1056}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -768,    819,    717}, 0, { -2080,  -1056}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -768,    819,    563}, 0, { -2080,  63<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -819,    819,    563}, 0, { -1056,  63<<5}, {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x070112C0 - 0x070113A0
static const Vtx bbh_seg7_vertex_070112C0[] = {
    {{{  -819,   1075,    563}, 0, {     0,  31<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{  -768,   1075,    563}, 0, { 15<<5,  31<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{  -768,   1075,    717}, 0, { 15<<5,      0}, {0x00, 0x81, 0x00, 0xff}}},
    {{{  -819,   1075,    717}, 0, {     0,      0}, {0x00, 0x81, 0x00, 0xff}}},
    {{{ -2253,   1331,  -1331}, 0, { 31<<5,    908}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{ -2048,   1331,  -1536}, 0, {   844,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{ -2253,   1331,  -1536}, 0, { 31<<5,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -819,   1331,  -1331}, 0, {     0,    908}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -819,   1331,  -1536}, 0, {     0,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{ -1024,   1331,  -1536}, 0, {   112,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{ -2253,   1638,  -1536}, 0, { 31<<5,  31<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{  -819,   1638,   1024}, 0, {     0,      0}, {0x00, 0x81, 0x00, 0xff}}},
    {{{ -2253,   1638,   1024}, 0, { 31<<5,      0}, {0x00, 0x81, 0x00, 0xff}}},
    {{{  -819,   1638,  -1536}, 0, {     0,  31<<5}, {0x00, 0x81, 0x00, 0xff}}},
};

// 0x070113A0 - 0x07011490
static const Vtx bbh_seg7_vertex_070113A0[] = {
    {{{ -1280,   1382,   1024}, 0, {     0,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{ -1280,    922,   1126}, 0, { 31<<5,  63<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{ -1280,    922,   1024}, 0, {     0,  63<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -870,   1382,   1024}, 0, { 31<<5,      0}, {0x00, 0x81, 0x00, 0xff}}},
    {{{  -870,   1382,   1126}, 0, {     0,      0}, {0x00, 0x81, 0x00, 0xff}}},
    {{{ -1280,   1382,   1126}, 0, {     0,  63<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{ -1280,   1382,   1024}, 0, { 31<<5,  63<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{  -870,    922,   1024}, 0, {     0,  63<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -870,   1382,   1126}, 0, { 31<<5,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -870,   1382,   1024}, 0, {     0,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -870,    922,   1126}, 0, { 31<<5,  63<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{ -1280,    922,   1024}, 0, { 31<<5,  63<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{ -1280,    922,   1126}, 0, {     0,  63<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -870,    922,   1126}, 0, {     0,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -870,    922,   1024}, 0, { 31<<5,      0}, {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x07011490 - 0x07011570
static const Vtx bbh_seg7_vertex_07011490[] = {
    {{{ -1280,    922,   1024}, 0, {  1118,   1756}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -870,    922,   1024}, 0, {    96,   1756}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -819,    819,   1024}, 0, {     0,  63<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{ -1280,   1382,   1024}, 0, {     0,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{ -1280,   1382,   1126}, 0, { 31<<5,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{ -1280,    922,   1126}, 0, { 31<<5,  63<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{ -2253,   1638,   1024}, 0, {  3546,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -819,   1638,   1024}, 0, {     0,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{ -1280,   1382,   1024}, 0, {  1118,    608}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -870,   1382,   1024}, 0, {    96,    608}, {0x00, 0x00, 0x81, 0xff}}},
    {{{ -2253,    819,   1024}, 0, {  3546,  63<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{ -2048,   1280,   1024}, 0, { 95<<5,    864}, {0x00, 0x81, 0x00, 0xff}}},
    {{{ -1894,   1280,   1024}, 0, {  2650,    864}, {0x00, 0x81, 0x00, 0xff}}},
    {{{ -1894,   1280,   1075}, 0, {  2650,    864}, {0x00, 0x81, 0x00, 0xff}}},
};

// 0x07011570 - 0x07011660
static const Vtx bbh_seg7_vertex_07011570[] = {
    {{{  -819,   1075,    717}, 0, { 31<<5,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -768,   1075,    717}, 0, { 15<<5,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -768,    819,    717}, 0, { 15<<5,  63<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -819,    819,    717}, 0, { 31<<5,  63<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -768,   1075,    563}, 0, { 15<<5,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -819,    819,    563}, 0, {     0,  63<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -768,    819,    563}, 0, { 15<<5,  63<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -819,   1075,    563}, 0, {     0,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{ -1894,   1280,   1024}, 0, {  2650,    864}, {0x81, 0x00, 0x00, 0xff}}},
    {{{ -1894,   1024,   1075}, 0, {  2650,  47<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{ -1894,   1280,   1075}, 0, {  2650,    864}, {0x81, 0x00, 0x00, 0xff}}},
    {{{ -1894,   1024,   1024}, 0, {  2650,  47<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{ -2253,    819,   1024}, 0, {  3546,  63<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{ -1894,    973,   1024}, 0, {  2650,   1628}, {0x00, 0x00, 0x81, 0xff}}},
    {{{ -1280,    922,   1024}, 0, {  1118,   1756}, {0x00, 0x00, 0x81, 0xff}}},
};

// 0x07011660 - 0x07011740
static const Vtx bbh_seg7_vertex_07011660[] = {
    {{{ -2048,   1280,   1024}, 0, { 95<<5,    864}, {0x00, 0x81, 0x00, 0xff}}},
    {{{ -1894,   1280,   1075}, 0, {  2650,    864}, {0x00, 0x81, 0x00, 0xff}}},
    {{{ -2048,   1280,   1075}, 0, { 95<<5,    864}, {0x00, 0x81, 0x00, 0xff}}},
    {{{ -2048,   1024,   1075}, 0, { 95<<5,  47<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{ -2048,   1024,   1024}, 0, { 95<<5,  47<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{ -2048,   1280,   1024}, 0, { 95<<5,    864}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{ -1894,   1024,   1075}, 0, {  2650,  47<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{ -2048,   1024,   1024}, 0, { 95<<5,  47<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{ -2048,   1024,   1075}, 0, { 95<<5,  47<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{ -2048,   1280,   1075}, 0, { 95<<5,    864}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{ -1894,   1024,   1024}, 0, {  2650,  47<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{ -2253,    819,   1024}, 0, {  3546,  63<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{ -2048,    973,   1024}, 0, { 95<<5,   1628}, {0x00, 0x00, 0x81, 0xff}}},
    {{{ -1894,    973,   1024}, 0, {  2650,   1628}, {0x00, 0x00, 0x81, 0xff}}},
};

// 0x07011740 - 0x07011830
static const Vtx bbh_seg7_vertex_07011740[] = {
    {{{  -819,    819,   1024}, 0, {  3800,  63<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -819,   1331,   1024}, 0, {  3800,  23<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -819,   1075,    717}, 0, { 95<<5,   1372}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -819,    819,    717}, 0, { 95<<5,  63<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -819,   1638,   1024}, 0, {  3800,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -819,   1638,  -1536}, 0, { -2586,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -819,   1331,  -1536}, 0, { -2586,  23<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -819,   1638,  -1536}, 0, {  3544,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{ -2253,   1331,  -1536}, 0, {     0,  23<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -819,   1331,  -1536}, 0, {  3544,  23<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{ -2253,   1638,  -1536}, 0, {     0,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{ -2253,   1331,  -1536}, 0, {  3546,  23<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{ -2253,   1638,   1024}, 0, { -2840,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{ -2253,   1331,   1024}, 0, { -2840,  23<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{ -2253,   1638,  -1536}, 0, {  3546,      0}, {0x7f, 0x00, 0x00, 0xff}}},
};

// 0x07011830 - 0x07011930
static const Vtx bbh_seg7_vertex_07011830[] = {
    {{{  -819,   1075,    563}, 0, {  2650,   1372}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -819,   1331,    358}, 0, {  2140,  23<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -819,    819,    358}, 0, {  2140,  63<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{ -1894,   1280,   1024}, 0, {  2650,    864}, {0x00, 0x00, 0x81, 0xff}}},
    {{{ -2048,   1280,   1024}, 0, { 95<<5,    864}, {0x00, 0x00, 0x81, 0xff}}},
    {{{ -2253,   1638,   1024}, 0, {  3546,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{ -1280,   1382,   1024}, 0, {  1118,    608}, {0x00, 0x00, 0x81, 0xff}}},
    {{{ -1280,    922,   1024}, 0, {  1118,   1756}, {0x00, 0x00, 0x81, 0xff}}},
    {{{ -1894,    973,   1024}, 0, {  2650,   1628}, {0x00, 0x00, 0x81, 0xff}}},
    {{{ -2048,    973,   1024}, 0, { 95<<5,   1628}, {0x00, 0x00, 0x81, 0xff}}},
    {{{ -2253,    819,   1024}, 0, {  3546,  63<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -819,   1075,    717}, 0, { 95<<5,   1372}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -819,    819,    563}, 0, {  2650,  63<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{ -1741,   1638,  -1024}, 0, { 31<<5,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{ -1331,   1638,  -1024}, 0, {     0,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{ -1331,    819,  -1024}, 0, {     0,  63<<5}, {0x00, 0x00, 0x81, 0xff}}},
};

// 0x07011930 - 0x07011990
static const Vtx bbh_seg7_vertex_07011930[] = {
    {{{  -819,   1075,    717}, 0, { 95<<5,   1372}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -819,   1331,   1024}, 0, {  3800,  23<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -819,   1331,    358}, 0, {  2140,  23<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{ -1741,   1638,  -1024}, 0, { 31<<5,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{ -1331,    819,  -1024}, 0, {     0,  63<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{ -1741,    819,  -1024}, 0, { 31<<5,  63<<5}, {0x00, 0x00, 0x81, 0xff}}},
};

// 0x07011990 - 0x07011A90
static const Vtx bbh_seg7_vertex_07011990[] = {
    {{{ -1894,    819,    512}, 0, {     0,    648}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{ -1894,    922,    512}, 0, {     0,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{ -1894,    922,    614}, 0, { 15<<5,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{ -2253,   1024,    614}, 0, { 31<<5,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{ -1741,   1024,    614}, 0, { -1562,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{ -1741,    819,    614}, 0, { -1562,   1332}, {0x00, 0x00, 0x81, 0xff}}},
    {{{ -2253,    819,    614}, 0, { 31<<5,   1332}, {0x00, 0x00, 0x81, 0xff}}},
    {{{ -2099,    922,    512}, 0, { 31<<5,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{ -1894,    819,    512}, 0, {     0,    648}, {0x00, 0x00, 0x81, 0xff}}},
    {{{ -2099,    819,    512}, 0, { 31<<5,    648}, {0x00, 0x00, 0x81, 0xff}}},
    {{{ -1894,    922,    512}, 0, {     0,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{ -2099,    922,    512}, 0, {     0,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{ -2099,    819,    512}, 0, {     0,    648}, {0x81, 0x00, 0x00, 0xff}}},
    {{{ -2099,    819,    614}, 0, { 15<<5,    648}, {0x81, 0x00, 0x00, 0xff}}},
    {{{ -2099,    922,    614}, 0, { 15<<5,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{ -1894,    819,    614}, 0, { 15<<5,    648}, {0x7f, 0x00, 0x00, 0xff}}},
};

// 0x07011A90 - 0x07011B80
static const Vtx bbh_seg7_vertex_07011A90[] = {
    {{{ -2253,   1331,  -1331}, 0, {     0,      0}, {0x59, 0x00, 0x59, 0xff}}},
    {{{ -2253,    819,  -1331}, 0, {     0,  63<<5}, {0x59, 0x00, 0x59, 0xff}}},
    {{{ -2048,    819,  -1536}, 0, { 31<<5,  63<<5}, {0x59, 0x00, 0x59, 0xff}}},
    {{{ -1331,   1331,   1024}, 0, { -4628,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{ -1331,    819,  -1024}, 0, {  5588,  63<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{ -1331,   1331,  -1024}, 0, {  5588,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{ -1331,    819,   1024}, 0, { -4630,  63<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{ -1741,   1331,  -1024}, 0, { -4118,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{ -1741,    819,   1024}, 0, {191<<5,  63<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{ -1741,   1331,   1024}, 0, {191<<5,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{ -1741,    819,  -1024}, 0, { -4118,  63<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{ -1024,   1331,  -1536}, 0, {     0,      0}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{ -1024,    819,  -1536}, 0, {     0,  63<<5}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{  -819,    819,  -1331}, 0, { 31<<5,  63<<5}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{  -819,   1331,  -1331}, 0, { 31<<5,      0}, {0xa7, 0x00, 0x59, 0xff}}},
};

// 0x07011B80 - 0x07011C70
static const Vtx bbh_seg7_vertex_07011B80[] = {
    {{{  -819,   1331,  -1331}, 0, { -7440,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -819,    819,    358}, 0, { 31<<5,  63<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -819,   1331,    358}, 0, { 31<<5,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{ -2253,   1331,  -1331}, 0, {     0,      0}, {0x59, 0x00, 0x59, 0xff}}},
    {{{ -2048,    819,  -1536}, 0, { 31<<5,  63<<5}, {0x59, 0x00, 0x59, 0xff}}},
    {{{ -2048,   1331,  -1536}, 0, { 31<<5,      0}, {0x59, 0x00, 0x59, 0xff}}},
    {{{ -1024,   1331,  -1536}, 0, {159<<5,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{ -2048,    819,  -1536}, 0, {     0,  63<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{ -1024,    819,  -1536}, 0, {159<<5,  63<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{ -2048,   1331,  -1536}, 0, {     0,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{ -2253,    819,  -1331}, 0, {  7122,  63<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{ -2253,   1331,  -1331}, 0, {  7122,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{ -2253,   1331,   1024}, 0, { -4630,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{ -2253,    819,   1024}, 0, { -4630,  63<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -819,    819,  -1331}, 0, { -7440,  63<<5}, {0x81, 0x00, 0x00, 0xff}}},
};

// 0x07011C70 - 0x07011CF0
static const Vtx bbh_seg7_vertex_07011C70[] = {
    {{{ -1741,   1638,  -1024}, 0, {     0,    580}, {0x81, 0x00, 0x00, 0xff}}},
    {{{ -1741,   1331,   1024}, 0, { 10188,   1808}, {0x81, 0x00, 0x00, 0xff}}},
    {{{ -1741,   1638,   1024}, 0, { 10188,    580}, {0x81, 0x00, 0x00, 0xff}}},
    {{{ -1741,   1331,  -1024}, 0, {     0,   1808}, {0x81, 0x00, 0x00, 0xff}}},
    {{{ -1331,   1638,   1024}, 0, { 10188,    580}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{ -1331,   1331,  -1024}, 0, {     0,   1808}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{ -1331,   1638,  -1024}, 0, {     0,    580}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{ -1331,   1331,   1024}, 0, { 10188,   1808}, {0x7f, 0x00, 0x00, 0xff}}},
};

// 0x07011CF0 - 0x07011DF0
static const Vtx bbh_seg7_vertex_07011CF0[] = {
    {{{ -2253,    819,  -1536}, 0, {-12292,  12230}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{ -2253,    819,   1024}, 0, { 13256,  12230}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{ -1075,    819,    461}, 0, {  7632,  15<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -819,    819,  -1536}, 0, {-12292,  -2080}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{ -1075,    819,    819}, 0, { 11212,  15<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -819,    819,    461}, 0, {  7632,  -2080}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -819,    819,   1024}, 0, { 13256,  -2080}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -819,    819,    819}, 0, { 11212,  -2080}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{ -2253,   1024,   1024}, 0, { -2072,  63<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{ -1741,   1024,   1024}, 0, { -2072,  -3104}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{ -1741,   1024,    614}, 0, { -6160,  -3104}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{ -2253,   1024,    614}, 0, { -6160,  63<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{ -2099,    922,    614}, 0, { -6160,  15<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{ -1894,    922,    614}, 0, { -6160,  -1566}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{ -1894,    922,    512}, 0, { -7184,  -1564}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{ -2099,    922,    512}, 0, { -7184,  15<<5}, {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x07011DF0 - 0x07011E48
static const Gfx bbh_seg7_dl_07011DF0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_0900A000_metal_floor),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&bbh_seg7_lights_07011228.l, 1),
    gsSPLight(&bbh_seg7_lights_07011228.a, 2),
    gsSPVertex(bbh_seg7_vertex_07011240, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x07011E48 - 0x07011EA0
static const Gfx bbh_seg7_dl_07011E48[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09008800_house_floor),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_070112C0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x07011EA0 - 0x07012078
static const Gfx bbh_seg7_dl_07011EA0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09003800_house_wall),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_070113A0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_07011490, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  1,  7,  2, 0x0),
    gsSP2Triangles( 1,  9,  7, 0x0,  9,  8,  7, 0x0),
    gsSP2Triangles( 0,  2, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(bbh_seg7_vertex_07011570, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_07011660, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  3,  5,  9, 0x0),
    gsSP2Triangles( 6, 10,  7, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(bbh_seg7_vertex_07011740, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 1,  4,  5, 0x0,  1,  5,  6, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  7, 10,  8, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 11, 14, 12, 0x0),
    gsSPVertex(bbh_seg7_vertex_07011830, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  3, 0x0),
    gsSP2Triangles( 7,  3,  6, 0x0,  5,  4,  9, 0x0),
    gsSP2Triangles( 5,  9, 10, 0x0,  0, 11,  1, 0x0),
    gsSP2Triangles( 2, 12,  0, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(bbh_seg7_vertex_07011930, 6, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSP1Triangle( 3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x07012078 - 0x070120E0
static const Gfx bbh_seg7_dl_07012078[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09005000_bricks_with_floor),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_07011990, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0,  2, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x070120E0 - 0x070121A8
static const Gfx bbh_seg7_dl_070120E0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09002800_bookshelf),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_07011A90, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_07011B80, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(bbh_seg7_vertex_07011C70, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x070121A8 - 0x07012220
static const Gfx bbh_seg7_dl_070121A8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09009000_small_dark_wood_planks),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_07011CF0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0,  2,  5,  3, 0x0),
    gsSP2Triangles( 1,  6,  4, 0x0,  6,  7,  4, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x07012220 - 0x07012318
const Gfx bbh_seg7_dl_library_surfaces[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_07011DF0),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_07011E48),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_07011EA0),
    gsSPDisplayList(bbh_seg7_dl_07012078),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_070120E0),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_070121A8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
