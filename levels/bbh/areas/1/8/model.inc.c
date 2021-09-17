// 0x0700B0D8 - 0x0700B0F0
static const Lights1 bbh_seg7_lights_study_windows = gdSPDefLights1(
    0x3f, 0x51, 0x66,
    0x9e, 0xcc, 0xff, 0x28, 0x28, 0x28
);

// 0x0700B0F0 - 0x0700B170
static const Vtx bbh_seg7_vertex_study_windows[] = {
    {{{  2662,    614,   2550}, 0, ST_B(    32,      0), {0x00, 0x00, 0x81, 0xff}}},
    {{{  3072,    205,   2550}, 0, ST_B(     0,     32), {0x00, 0x00, 0x81, 0xff}}},
    {{{  2662,    205,   2550}, 0, ST_B(    32,     32), {0x00, 0x00, 0x81, 0xff}}},
    {{{  3072,    614,   2550}, 0, ST_B(     0,      0), {0x00, 0x00, 0x81, 0xff}}},
    {{{  2662,   1536,   2550}, 0, ST_B(    32,      0), {0x00, 0x00, 0x81, 0xff}}},
    {{{  3072,   1126,   2550}, 0, ST_B(     0,     32), {0x00, 0x00, 0x81, 0xff}}},
    {{{  2662,   1126,   2550}, 0, ST_B(    32,     32), {0x00, 0x00, 0x81, 0xff}}},
    {{{  3072,   1536,   2550}, 0, ST_B(     0,      0), {0x00, 0x00, 0x81, 0xff}}},
};

// 0x0700B170 - 0x0700B1C8
static const Gfx bbh_seg7_sub_dl_study_windows[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09006000_window),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&bbh_seg7_lights_study_windows.l, 1),
    gsSPLight(&bbh_seg7_lights_study_windows.a, 2),
    gsSPVertex(bbh_seg7_vertex_study_windows, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700B1C8 - 0x0700B238
const Gfx bbh_seg7_dl_study_windows[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_sub_dl_study_windows),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
