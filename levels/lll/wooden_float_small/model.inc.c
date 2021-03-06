// 0x07018AA0 - 0x07018B20
static const Vtx lll_seg7_vertex_wooden_float_small_inside[] = {
    {{{   154,      0,    384}, 0, { 31<<5,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   154,    154,    384}, 0, { 31<<5,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -154,    154,    384}, 0, { -1056,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -154,      0,    384}, 0, { -1056,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -154,      0,   -384}, 0, { 63<<5,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   154,    154,   -384}, 0, {     0,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   154,      0,   -384}, 0, {     0,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -154,    154,   -384}, 0, { 63<<5,      0}, {0x00, 0x00, 0x81, 0xff}}},
};

// 0x07018B20 - 0x07018BE0
static const Vtx lll_seg7_vertex_wooden_float_small_outside[] = {
    {{{   154,    154,   -384}, 0, { 31<<5,  -1564}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -154,    154,   -384}, 0, {     0,  -1564}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -154,    154,    384}, 0, {     0,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   154,    154,    384}, 0, { 31<<5,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   154,      0,   -384}, 0, { 31<<5,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   154,    154,   -384}, 0, { 31<<5,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   154,    154,    384}, 0, { -4118,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   154,      0,    384}, 0, { -4118,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -154,      0,    384}, 0, { 31<<5,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -154,    154,   -384}, 0, { -4118,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -154,      0,   -384}, 0, { -4118,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -154,    154,    384}, 0, { 31<<5,      0}, {0x81, 0x00, 0x00, 0xff}}},
};

// 0x07018BE0 - 0x07018C38
static const Gfx lll_seg7_sub_dl_wooden_float_small_inside[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, lll_seg7_texture_wood_inside),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&lll_seg7_lights_gray_0x3f_0xff_0x28.l, 1),
    gsSPLight(&lll_seg7_lights_gray_0x3f_0xff_0x28.a, 2),
    gsSPVertex(lll_seg7_vertex_wooden_float_small_inside, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x07018C38 - 0x07018C90
static const Gfx lll_seg7_sub_dl_wooden_float_small_outside[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, lll_seg7_texture_wood_outside),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(lll_seg7_vertex_wooden_float_small_outside, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x07018C90 - 0x07018D08
const Gfx lll_seg7_dl_wooden_float_small[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(lll_seg7_sub_dl_wooden_float_small_inside),
    gsSPDisplayList(lll_seg7_sub_dl_wooden_float_small_outside),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
