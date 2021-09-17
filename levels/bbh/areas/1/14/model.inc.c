// 0x0700D350 - 0x0700D368
static const Lights1 bbh_seg7_lights_piano_room_windows = gdSPDefLights1(
    0x3f, 0x51, 0x66,
    0x9e, 0xcc, 0xff, 0x28, 0x28, 0x28
);

// 0x0700D368 - 0x0700D428
static const Vtx bbh_seg7_vertex_piano_room_windows[] = {
    {{{ -1741,   1536,   2550}, 0, ST_B(    32,      0), {0x00, 0x00, 0x81, 0xff}}},
    {{{ -1331,   1536,   2550}, 0, ST_B(     0,      0), {0x00, 0x00, 0x81, 0xff}}},
    {{{ -1331,   1126,   2550}, 0, ST_B(     0,     32), {0x00, 0x00, 0x81, 0xff}}},
    {{{ -1741,   1126,   2550}, 0, ST_B(    32,     32), {0x00, 0x00, 0x81, 0xff}}},
    {{{ -1741,    614,   2550}, 0, ST_B(    32,      0), {0x00, 0x00, 0x81, 0xff}}},
    {{{ -1331,    614,   2550}, 0, ST_B(     0,      0), {0x00, 0x00, 0x81, 0xff}}},
    {{{ -1331,    205,   2550}, 0, ST_B(     0,     32), {0x00, 0x00, 0x81, 0xff}}},
    {{{ -1741,    205,   2550}, 0, ST_B(    32,     32), {0x00, 0x00, 0x81, 0xff}}},
    {{{  -614,    614,   2038}, 0, ST_B(    32,      0), {0x00, 0x00, 0x81, 0xff}}},
    {{{  -205,    614,   2038}, 0, ST_B(     0,      0), {0x00, 0x00, 0x81, 0xff}}},
    {{{  -205,    205,   2038}, 0, ST_B(     0,     32), {0x00, 0x00, 0x81, 0xff}}},
    {{{  -614,    205,   2038}, 0, ST_B(    32,     32), {0x00, 0x00, 0x81, 0xff}}},
};

// 0x0700D428 - 0x0700D490
static const Gfx bbh_seg7_sub_dl_piano_room_windows[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09006000_window),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&bbh_seg7_lights_piano_room_windows.l, 1),
    gsSPLight(&bbh_seg7_lights_piano_room_windows.a, 2),
    gsSPVertex(bbh_seg7_vertex_piano_room_windows, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700D490 - 0x0700D500
const Gfx bbh_seg7_dl_piano_room_windows[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_sub_dl_piano_room_windows),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
