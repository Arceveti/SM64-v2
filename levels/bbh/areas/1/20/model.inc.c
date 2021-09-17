// 0x07012318 - 0x07012330
static const Lights1 bbh_seg7_lights_library_window_wood = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07012330 - 0x07012430
static const Vtx bbh_seg7_vertex_library_window_wood[] = {
    {{{ -1101,   1382,   1075}, 0, ST_B(    10,     64), {0x00, 0x00, 0x7f, 0xff}}}, //  0
    {{{ -1101,   1178,   1075}, 0, ST_B(    10,      6), {0x00, 0x00, 0x7f, 0xff}}}, //  1
    {{{ -1075,   1152,   1075}, 0, ST_B(     5,      0), {0x00, 0x00, 0x7f, 0xff}}}, //  2
    {{{ -1101,   1126,   1075}, 0, ST_B(     0,      6), {0x00, 0x00, 0x7f, 0xff}}}, //  3
    {{{ -1101,    922,   1075}, 0, ST_B(     0,     64), {0x00, 0x00, 0x7f, 0xff}}}, //  4
    {{{ -1050,    922,   1075}, 0, ST_B(    10,     64), {0x00, 0x00, 0x7f, 0xff}}}, //  5
    {{{ -1050,   1126,   1075}, 0, ST_B(    10,      6), {0x00, 0x00, 0x7f, 0xff}}}, //  6
    {{{ -1280,   1178,   1075}, 0, ST_B(     0,     64), {0x00, 0x00, 0x7f, 0xff}}}, //  7
    {{{ -1280,   1126,   1075}, 0, ST_B(    10,     64), {0x00, 0x00, 0x7f, 0xff}}}, //  8
    {{{ -1101,   1126,   1075}, 0, ST_B(    10,      8), {0x00, 0x00, 0x7f, 0xff}}}, //  9
    {{{ -1101,   1178,   1075}, 0, ST_B(     0,      8), {0x00, 0x00, 0x7f, 0xff}}}, // 10
    {{{ -1050,   1178,   1075}, 0, ST_B(     0,      6), {0x00, 0x00, 0x7f, 0xff}}}, // 11
    {{{ -1050,   1382,   1075}, 0, ST_B(     0,     64), {0x00, 0x00, 0x7f, 0xff}}}, // 12
    {{{ -1050,   1178,   1075}, 0, ST_B(    10,      8), {0x00, 0x00, 0x7f, 0xff}}}, // 13
    {{{  -870,   1126,   1075}, 0, ST_B(     0,     64), {0x00, 0x00, 0x7f, 0xff}}}, // 14
    {{{  -870,   1178,   1075}, 0, ST_B(    10,     64), {0x00, 0x00, 0x7f, 0xff}}}, // 15
    {{{ -1050,   1126,   1075}, 0, ST_B(     0,      8), {0x00, 0x00, 0x7f, 0xff}}}, // 18
};

// 0x07012470 - 0x07012510
static const Gfx bbh_seg7_sub_dl_library_window_wood[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bbh_seg7_texture_wooden_panel_wall),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 64), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&bbh_seg7_lights_library_window_wood.l, 1),
    gsSPLight(&bbh_seg7_lights_library_window_wood.a, 2),
    gsSPVertex(bbh_seg7_vertex_library_window_wood, 17, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  3,  6,  2, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  7,  9,  2, 0x0),
    gsSP2Triangles( 7,  2, 10, 0x0,  0,  2, 11, 0x0),
    gsSP2Triangles( 0, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSP2Triangles(13,  2, 16, 0x0, 13, 16, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x07012510 - 0x07012580
const Gfx bbh_seg7_dl_library_window_wood[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_sub_dl_library_window_wood),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
