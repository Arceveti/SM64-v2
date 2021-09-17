// 0x0701E948 - 0x0701E960
static const Lights1 bbh_seg7_lights_outside_windows_roof = gdSPDefLights1(
    0x24, 0x11, 0x0b,
    0x5a, 0x2c, 0x1d, 0x28, 0x28, 0x28
);

// 0x0701E960 - 0x0701E978
static const Lights1 bbh_seg7_lights_outside_windows_walls = gdSPDefLights1(
    0x3c, 0x3c, 0x3c,
    0x96, 0x96, 0x96, 0x28, 0x28, 0x28
);

// 0x0701E978 - 0x0701E9F8
static const Vtx bbh_seg7_vertex_outside_windows_roof[] = {
    {{{  1638,   3021,    730}, 0, ST_B(    32,      0), {0x00, 0x5f, 0x54, 0xff}}},
    {{{  1229,   3021,    730}, 0, ST_B(     0,      0), {0x00, 0x5f, 0x54, 0xff}}},
    {{{  1229,   2750,   1037}, 0, ST_B(     0,     32), {0x00, 0x5f, 0x54, 0xff}}},
    {{{  1638,   2750,   1037}, 0, ST_B(    32,     32), {0x00, 0x5f, 0x54, 0xff}}},
    {{{  -307,   2750,   1037}, 0, ST_B(     0,     32), {0x00, 0x5f, 0x54, 0xff}}},
    {{{   102,   3021,    730}, 0, ST_B(    32,      0), {0x00, 0x5f, 0x54, 0xff}}},
    {{{  -307,   3021,    730}, 0, ST_B(     0,      0), {0x00, 0x5f, 0x54, 0xff}}},
    {{{   102,   2750,   1037}, 0, ST_B(    32,     32), {0x00, 0x5f, 0x54, 0xff}}},
};

//! TODO: combine these:
// 0x0701E9F8 - 0x0701EAE8
static const Vtx bbh_seg7_vertex_0701E9F8[] = {
    {{{  1843,   1536,   2161}, 0, ST_B(    32,      0), {0x00, 0x00, 0x7f, 0xff}}},
    {{{  1434,   1126,   2161}, 0, ST_B(     0,     32), {0x00, 0x00, 0x7f, 0xff}}},
    {{{  1843,   1126,   2161}, 0, ST_B(    32,     32), {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -102,    614,   2161}, 0, ST_B(    32,      0), {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -512,    205,   2161}, 0, ST_B(     0,     32), {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -102,    205,   2161}, 0, ST_B(    32,     32), {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -512,    614,   2161}, 0, ST_B(     0,      0), {0x00, 0x00, 0x7f, 0xff}}},
    {{{  1843,    614,   2161}, 0, ST_B(    32,      0), {0x00, 0x00, 0x7f, 0xff}}},
    {{{  1434,    205,   2161}, 0, ST_B(     0,     32), {0x00, 0x00, 0x7f, 0xff}}},
    {{{  1843,    205,   2161}, 0, ST_B(    32,     32), {0x00, 0x00, 0x7f, 0xff}}},
    {{{  1434,    614,   2161}, 0, ST_B(     0,      0), {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -102,   1536,   2161}, 0, ST_B(    32,      0), {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -512,   1126,   2161}, 0, ST_B(     0,     32), {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -102,   1126,   2161}, 0, ST_B(    32,     32), {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -512,   1536,   2161}, 0, ST_B(     0,      0), {0x00, 0x00, 0x7f, 0xff}}},
};

// 0x0701EAE8 - 0x0701EBD8
static const Vtx bbh_seg7_vertex_0701EAE8[] = {
    {{{  3072,    614,   2673}, 0, ST_B(    32,      0), {0x00, 0x00, 0x7f, 0xff}}},
    {{{  2662,    205,   2673}, 0, ST_B(     0,     32), {0x00, 0x00, 0x7f, 0xff}}},
    {{{  3072,    205,   2673}, 0, ST_B(    32,     32), {0x00, 0x00, 0x7f, 0xff}}},
    {{{  1843,   1536,   2161}, 0, ST_B(    32,      0), {0x00, 0x00, 0x7f, 0xff}}},
    {{{  1434,   1536,   2161}, 0, ST_B(     0,      0), {0x00, 0x00, 0x7f, 0xff}}},
    {{{  1434,   1126,   2161}, 0, ST_B(     0,     32), {0x00, 0x00, 0x7f, 0xff}}},
    {{{ -1331,    614,   2673}, 0, ST_B(    32,      0), {0x00, 0x00, 0x7f, 0xff}}},
    {{{ -1741,    205,   2673}, 0, ST_B(     0,     32), {0x00, 0x00, 0x7f, 0xff}}},
    {{{ -1331,    205,   2673}, 0, ST_B(    32,     32), {0x00, 0x00, 0x7f, 0xff}}},
    {{{ -1741,    614,   2673}, 0, ST_B(     0,      0), {0x00, 0x00, 0x7f, 0xff}}},
    {{{ -1331,   1536,   2673}, 0, ST_B(    32,      0), {0x00, 0x00, 0x7f, 0xff}}},
    {{{ -1741,   1126,   2673}, 0, ST_B(     0,     32), {0x00, 0x00, 0x7f, 0xff}}},
    {{{ -1331,   1126,   2673}, 0, ST_B(    32,     32), {0x00, 0x00, 0x7f, 0xff}}},
    {{{ -1741,   1536,   2673}, 0, ST_B(     0,      0), {0x00, 0x00, 0x7f, 0xff}}},
    {{{  2662,    614,   2673}, 0, ST_B(     0,      0), {0x00, 0x00, 0x7f, 0xff}}},
};

// 0x0701EBD8 - 0x0701EC18
static const Vtx bbh_seg7_vertex_0701EBD8[] = {
    {{{  3072,   1536,   2673}, 0, ST_B(    32,      0), {0x00, 0x00, 0x7f, 0xff}}},
    {{{  2662,   1126,   2673}, 0, ST_B(     0,     32), {0x00, 0x00, 0x7f, 0xff}}},
    {{{  3072,   1126,   2673}, 0, ST_B(    32,     32), {0x00, 0x00, 0x7f, 0xff}}},
    {{{  2662,   1536,   2673}, 0, ST_B(     0,      0), {0x00, 0x00, 0x7f, 0xff}}},
};

// 0x0701EC18 - 0x0701ED18
static const Gfx bbh_seg7_sub_dl_outside_windows[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09006000_window),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&bbh_seg7_lights_outside_windows_roof.l, 1),
    gsSPLight(&bbh_seg7_lights_outside_windows_roof.a, 2),
    gsSPVertex(bbh_seg7_vertex_outside_windows_roof, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPLight(&bbh_seg7_lights_outside_windows_walls.l, 1),
    gsSPLight(&bbh_seg7_lights_outside_windows_walls.a, 2),
    gsSPVertex(bbh_seg7_vertex_0701E9F8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(bbh_seg7_vertex_0701EAE8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(bbh_seg7_vertex_0701EBD8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0701ED18 - 0x0701ED88
const Gfx bbh_seg7_dl_outside_windows[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_sub_dl_outside_windows),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
