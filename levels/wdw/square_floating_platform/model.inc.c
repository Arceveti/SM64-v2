// 0x07012938 - 0x07012950
static const Lights1 wdw_seg7_lights_07012938 = gdSPDefLights1(
    0x99, 0x99, 0x99,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07012950 - 0x07012A50
static const Vtx wdw_seg7_vertex_07012950[] = {
    {{{   256,    -64,    256}, 0, ST_B(     0,      0), {0x00, 0x00, 0x7f, 0xff}}},
    {{{   256,     64,    256}, 0, ST_B(    32,      0), {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -256,     64,    256}, 0, ST_B(    32,     32), {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -256,    -64,    256}, 0, ST_B(     0,     32), {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -256,    -64,    256}, 0, ST_B(     0,     32), {0x81, 0x00, 0x00, 0xff}}},
    {{{  -256,     64,    256}, 0, ST_B(    32,     32), {0x81, 0x00, 0x00, 0xff}}},
    {{{  -256,     64,   -256}, 0, ST_B(    32,      0), {0x81, 0x00, 0x00, 0xff}}},
    {{{  -256,    -64,   -256}, 0, ST_B(     0,      0), {0x81, 0x00, 0x00, 0xff}}},
    {{{  -256,    -64,   -256}, 0, ST_B(     0,     32), {0x00, 0x00, 0x81, 0xff}}},
    {{{   256,     64,   -256}, 0, ST_B(    32,      0), {0x00, 0x00, 0x81, 0xff}}},
    {{{   256,    -64,   -256}, 0, ST_B(     0,      0), {0x00, 0x00, 0x81, 0xff}}},
    {{{   256,    -64,   -256}, 0, ST_B(     0,      0), {0x7f, 0x00, 0x00, 0xff}}},
    {{{   256,     64,    256}, 0, ST_B(    32,     32), {0x7f, 0x00, 0x00, 0xff}}},
    {{{   256,    -64,    256}, 0, ST_B(     0,     32), {0x7f, 0x00, 0x00, 0xff}}},
    {{{   256,     64,   -256}, 0, ST_B(    32,      0), {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -256,     64,   -256}, 0, ST_B(    32,     32), {0x00, 0x00, 0x81, 0xff}}},
};

// 0x07012A50 - 0x07012AD0
static const Vtx wdw_seg7_vertex_07012A50[] = {
    {{{   256,    -64,    256}, 0, ST_B(    32,     32), {0x00, 0x81, 0x00, 0xff}}},
    {{{  -256,    -64,    256}, 0, ST_B(    32,      0), {0x00, 0x81, 0x00, 0xff}}},
    {{{  -256,    -64,   -256}, 0, ST_B(     0,      0), {0x00, 0x81, 0x00, 0xff}}},
    {{{   256,    -64,   -256}, 0, ST_B(     0,     32), {0x00, 0x81, 0x00, 0xff}}},
    {{{   256,     64,   -256}, 0, ST_B(     0,     32), {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -256,     64,    256}, 0, ST_B(    32,      0), {0x00, 0x7f, 0x00, 0xff}}},
    {{{   256,     64,    256}, 0, ST_B(    32,     32), {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -256,     64,   -256}, 0, ST_B(     0,      0), {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x07012AD0 - 0x07012B48
static const Gfx wdw_seg7_dl_07012AD0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, wdw_seg7_texture_wooden_beams),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&wdw_seg7_lights_07012938.l, 1),
    gsSPLight(&wdw_seg7_lights_07012938.a, 2),
    gsSPVertex(wdw_seg7_vertex_07012950, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0,  8, 15,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x07012B48 - 0x07012B90
static const Gfx wdw_seg7_dl_07012B48[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09006800_wood),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(wdw_seg7_vertex_07012A50, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x07012B90 - 0x07012C08
const Gfx wdw_seg7_dl_square_floating_platform[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(wdw_seg7_dl_07012AD0),
    gsSPDisplayList(wdw_seg7_dl_07012B48),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
