// 0x07011DE8 - 0x07011E00
static const Lights1 ttm_seg7_lights_rolling_log = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07011E00 - 0x07011F00
static const Vtx ttm_seg7_vertex_rolling_log_inside[] = {
    {{{ -1104,    236,    -96}, 0, {   674,    -96}, {0x87, 0x22, 0xf2, 0xff}}},
    {{{ -1104,     96,   -236}, 0, { 32<<5,    246}, {0xdf, 0x2f, 0x8f, 0xff}}},
    {{{ -1104,    -96,   -236}, 0, { 32<<5,  23<<5}, {0xa3, 0xe0, 0xb1, 0xff}}},
    {{{  1104,    236,    -96}, 0, {   674,    -96}, {0x6c, 0x3d, 0xe7, 0xff}}},
    {{{  1104,   -236,    -96}, 0, {   674,   1072}, {0x5d, 0xb1, 0xdf, 0xff}}},
    {{{  1104,    -96,   -236}, 0, { 32<<5,  23<<5}, {0x3c, 0xd6, 0x99, 0xff}}},
    {{{  1104,     96,   -236}, 0, { 32<<5,    246}, {0x3c, 0x2b, 0x99, 0xff}}},
    {{{  1104,    236,     96}, 0, {   186,    -96}, {0x3c, 0x67, 0x2a, 0xff}}},
    {{{  1104,     96,    236}, 0, {  -160,    246}, {0x3c, 0x2a, 0x67, 0xff}}},
    {{{  1104,    -96,    236}, 0, {  -160,  23<<5}, {0x5d, 0xe0, 0x4f, 0xff}}},
    {{{  1104,   -236,     96}, 0, {   186,   1072}, {0x3c, 0x99, 0x2a, 0xff}}},
    {{{ -1104,    -96,    236}, 0, {  -160,  23<<5}, {0xc4, 0xd6, 0x67, 0xff}}},
    {{{ -1104,     96,    236}, 0, {  -160,    246}, {0xa3, 0x20, 0x4f, 0xff}}},
    {{{ -1104,   -236,     96}, 0, {   184,   1072}, {0xa3, 0xb1, 0x20, 0xff}}},
    {{{ -1104,   -236,    -96}, 0, {   674,   1072}, {0xc4, 0x99, 0xd6, 0xff}}},
    {{{ -1104,    236,     96}, 0, {   184,    -96}, {0xdf, 0x71, 0x2f, 0xff}}},
};

// 0x07011F00 - 0x07011FF0
static const Vtx ttm_seg7_vertex_rolling_log_outside_1[] = {
    {{{ -1104,    -96,    236}, 0, {  4380,    336}, {0xc4, 0xd6, 0x67, 0xff}}},
    {{{  1104,     96,    236}, 0, {     0,  31<<5}, {0x3c, 0x2a, 0x67, 0xff}}},
    {{{ -1104,     96,    236}, 0, {  4380,  31<<5}, {0xa3, 0x20, 0x4f, 0xff}}},
    {{{ -1104,     96,   -236}, 0, {  4380,  31<<5}, {0xdf, 0x2f, 0x8f, 0xff}}},
    {{{  1104,    -96,   -236}, 0, {     0,    336}, {0x3c, 0xd6, 0x99, 0xff}}},
    {{{ -1104,    -96,   -236}, 0, {  4380,    336}, {0xa3, 0xe0, 0xb1, 0xff}}},
    {{{  1104,     96,   -236}, 0, {     0,  31<<5}, {0x3c, 0x2b, 0x99, 0xff}}},
    {{{ -1104,    236,     96}, 0, {  4380,  31<<5}, {0xdf, 0x71, 0x2f, 0xff}}},
    {{{  1104,    236,    -96}, 0, {     0,    336}, {0x6c, 0x3d, 0xe7, 0xff}}},
    {{{ -1104,    236,    -96}, 0, {  4380,    336}, {0x87, 0x22, 0xf2, 0xff}}},
    {{{  1104,    236,     96}, 0, {     0,  31<<5}, {0x3c, 0x67, 0x2a, 0xff}}},
    {{{  1104,     96,    236}, 0, {   -32,    336}, {0x3c, 0x2a, 0x67, 0xff}}},
    {{{  1104,    236,     96}, 0, {   -32,  31<<5}, {0x3c, 0x67, 0x2a, 0xff}}},
    {{{ -1104,    236,     96}, 0, {  4380,  31<<5}, {0xdf, 0x71, 0x2f, 0xff}}},
    {{{ -1104,     96,    236}, 0, {  4380,    342}, {0xa3, 0x20, 0x4f, 0xff}}},
};

// 0x07011FF0 - 0x070120E0
static const Vtx ttm_seg7_vertex_rolling_log_outside_2[] = {
    {{{  1104,    236,    -96}, 0, {     0,  31<<5}, {0x6c, 0x3d, 0xe7, 0xff}}},
    {{{ -1104,     96,   -236}, 0, {  4380,    336}, {0xdf, 0x2f, 0x8f, 0xff}}},
    {{{ -1104,    236,    -96}, 0, {  4380,  31<<5}, {0x87, 0x22, 0xf2, 0xff}}},
    {{{ -1104,    -96,    236}, 0, {  4380,    336}, {0xc4, 0xd6, 0x67, 0xff}}},
    {{{  1104,    -96,    236}, 0, {     0,    336}, {0x5d, 0xe0, 0x4f, 0xff}}},
    {{{  1104,     96,    236}, 0, {     0,  31<<5}, {0x3c, 0x2a, 0x67, 0xff}}},
    {{{  1104,   -236,     96}, 0, {     0,    336}, {0x3c, 0x99, 0x2a, 0xff}}},
    {{{  1104,    -96,    236}, 0, {     0,  31<<5}, {0x5d, 0xe0, 0x4f, 0xff}}},
    {{{ -1104,    -96,    236}, 0, {  4380,  31<<5}, {0xc4, 0xd6, 0x67, 0xff}}},
    {{{ -1104,   -236,     96}, 0, {  4380,    336}, {0xa3, 0xb1, 0x20, 0xff}}},
    {{{  1104,   -236,    -96}, 0, {     0,    336}, {0x5d, 0xb1, 0xdf, 0xff}}},
    {{{  1104,   -236,     96}, 0, {     0,  31<<5}, {0x3c, 0x99, 0x2a, 0xff}}},
    {{{ -1104,   -236,    -96}, 0, {  4380,    336}, {0xc4, 0x99, 0xd6, 0xff}}},
    {{{ -1104,   -236,     96}, 0, {  4380,  31<<5}, {0xa3, 0xb1, 0x20, 0xff}}},
    {{{  1104,     96,   -236}, 0, {     0,    336}, {0x3c, 0x2b, 0x99, 0xff}}},
};

// 0x070120E0 - 0x07012120
static const Vtx ttm_seg7_vertex_rolling_log_outside_3[] = {
    {{{ -1104,   -236,    -96}, 0, {  4382,    342}, {0xc4, 0x99, 0xd6, 0xff}}},
    {{{  1104,    -96,   -236}, 0, {     0,  31<<5}, {0x3c, 0xd6, 0x99, 0xff}}},
    {{{  1104,   -236,    -96}, 0, {     0,    336}, {0x5d, 0xb1, 0xdf, 0xff}}},
    {{{ -1104,    -96,   -236}, 0, {  4382,  31<<5}, {0xa3, 0xe0, 0xb1, 0xff}}},
};

// 0x07012120 - 0x070121B8
static const Gfx ttm_seg7_sub_dl_rolling_log_inside[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, ttm_seg7_texture_log_inside),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttm_seg7_lights_rolling_log.l, 1),
    gsSPLight(&ttm_seg7_lights_rolling_log.a, 2),
    gsSPVertex(ttm_seg7_vertex_rolling_log_inside, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  3,  7,  8, 0x0),
    gsSP2Triangles( 3,  8,  9, 0x0,  3,  9, 10, 0x0),
    gsSP2Triangles( 3, 10,  4, 0x0,  0, 11, 12, 0x0),
    gsSP2Triangles( 0, 13, 11, 0x0,  0, 14, 13, 0x0),
    gsSP2Triangles( 0,  2, 14, 0x0,  0, 12, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x070121B8 - 0x07012270
static const Gfx ttm_seg7_sub_dl_rolling_log_outside[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_09005000_wood_bark),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ttm_seg7_vertex_rolling_log_outside_1, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle( 14, 11, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_rolling_log_outside_2, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  6,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 11, 13, 12, 0x0),
    gsSP1Triangle(  0, 14,  1, 0x0),
    gsSPVertex(ttm_seg7_vertex_rolling_log_outside_3, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07012270 - 0x070122F0
const Gfx ttm_seg7_dl_rolling_log[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttm_seg7_sub_dl_rolling_log_inside),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttm_seg7_sub_dl_rolling_log_outside),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
