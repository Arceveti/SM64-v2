// 0x0701F6A8 - 0x0701F6C0
static const Lights1 bbh_seg7_lights_tumbling_platform_far = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0701F6C0 - 0x0701F780
static const Vtx bbh_seg7_vertex_tumbling_platform_far[] = {
    {{{  -102,      0,   -461}, 0, ST_B(    32,    287), {0x81, 0x00, 0x00, 0xff}}},
    {{{  -102,   -102,    461}, 0, ST_B(     0,      0), {0x81, 0x00, 0x00, 0xff}}},
    {{{  -102,      0,    461}, 0, ST_B(    32,      0), {0x81, 0x00, 0x00, 0xff}}},
    {{{  -102,   -102,   -461}, 0, ST_B(     0,    287), {0x81, 0x00, 0x00, 0xff}}},
    {{{   102,      0,    461}, 0, ST_B(    32,      0), {0x7f, 0x00, 0x00, 0xff}}},
    {{{   102,   -102,   -461}, 0, ST_B(     0,    287), {0x7f, 0x00, 0x00, 0xff}}},
    {{{   102,      0,   -461}, 0, ST_B(    32,    287), {0x7f, 0x00, 0x00, 0xff}}},
    {{{   102,   -102,    461}, 0, ST_B(     0,      0), {0x7f, 0x00, 0x00, 0xff}}},
    {{{   102,      0,   -461}, 0, ST_B(    32,   -256), {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -102,      0,    461}, 0, ST_B(     0,     32), {0x00, 0x7f, 0x00, 0xff}}},
    {{{   102,      0,    461}, 0, ST_B(    32,     32), {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -102,      0,   -461}, 0, ST_B(     0,   -256), {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x0701F780 - 0x0701F7E8
static const Gfx bbh_seg7_sub_dl_tumbling_platform_far[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09004800_pattern_block),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&bbh_seg7_lights_tumbling_platform_far.l, 1),
    gsSPLight(&bbh_seg7_lights_tumbling_platform_far.a, 2),
    gsSPVertex(bbh_seg7_vertex_tumbling_platform_far, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x0701F7E8 - 0x0701F858
const Gfx bbh_seg7_dl_tumbling_platform_far[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_sub_dl_tumbling_platform_far),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
