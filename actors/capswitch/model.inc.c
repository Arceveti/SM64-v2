// Capswitch

// 0x05001BB8
static const Lights1 capswitch_seg5_lights_white = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x05001BE8
static const Lights1 capswitch_seg5_lights_red = gdSPDefLights1(
    0x3f, 0x00, 0x00,
    0xff, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x05001C00
static const Lights1 capswitch_seg5_lights_green = gdSPDefLights1(
    0x01, 0x2a, 0x09,
    0x07, 0xa9, 0x25, 0x28, 0x28, 0x28
);

// 0x05001C18
static const Lights1 capswitch_seg5_lights_blue = gdSPDefLights1(
    0x00, 0x00, 0x3f,
    0x00, 0x00, 0xff, 0x28, 0x28, 0x28
);

// 0x05001C30
static const Lights1 capswitch_seg5_lights_yellow = gdSPDefLights1(
    0x3f, 0x25, 0x02,
    0xff, 0x96, 0x08, 0x28, 0x28, 0x28
);

// 0x05001C48
ALIGNED8 static const Texture capswitch_seg5_texture_exclamation_mark[] = {
#include "actors/capswitch/cap_switch_head.ia16.inc.c"
};

// 0x05002C48
ALIGNED8 static const Texture capswitch_seg5_texture_base[] = {
#include "actors/capswitch/cap_switch_base.rgba16.inc.c"
};

// 0x05002CC8
static const Vtx capswitch_seg5_vertex_exclamation_mark[] = {
    {{{  -120,    262,   -205}, 0, {  -128,    364}, {0x00, 0x36, 0x8e, 0xff}}},
    {{{   128,      0,   -224}, 0, {  1144,   2144}, {0x00, 0x0a, 0x82, 0xff}}},
    {{{  -128,      0,   -224}, 0, {  -184,   2144}, {0x00, 0x0a, 0x82, 0xff}}},
    {{{   120,    262,   -205}, 0, {  1088,    364}, {0x00, 0x36, 0x8e, 0xff}}},
    {{{   109,    352,   -109}, 0, {  1034,   -256}, {0x00, 0x5c, 0xa9, 0xff}}},
    {{{  -109,    352,   -109}, 0, {   -80,   -256}, {0x00, 0x5c, 0xa9, 0xff}}},
    {{{  -128,      0,    224}, 0, {  -184,   2144}, {0x00, 0x0a, 0x7e, 0xff}}},
    {{{   120,    262,    205}, 0, {  1088,    364}, {0x00, 0x36, 0x72, 0xff}}},
    {{{  -120,    262,    205}, 0, {  -128,    364}, {0x00, 0x36, 0x72, 0xff}}},
    {{{  -109,    352,    109}, 0, {   -80,   -256}, {0x00, 0x5c, 0x57, 0xff}}},
    {{{   128,      0,    224}, 0, {  1144,   2144}, {0x00, 0x0a, 0x7e, 0xff}}},
    {{{   109,    352,    109}, 0, {  1034,   -256}, {0x00, 0x5c, 0x57, 0xff}}},
};

// 0x05002D88 - 0x05002E00
const Gfx cap_switch_exclamation_seg5_sub_dl_exclamation_mark[] = {
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, capswitch_seg5_texture_exclamation_mark),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 64), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&capswitch_seg5_lights_white.l, 1),
    gsSPLight(&capswitch_seg5_lights_white.a, 2),
    gsSPVertex(capswitch_seg5_vertex_exclamation_mark, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 4,  3,  0, 0x0,  5,  4,  0, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 7,  6, 10, 0x0, 11,  9,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x05002E00 - 0x05002E60
const Gfx cap_switch_exclamation_seg5_dl_exclamation_mark[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(cap_switch_exclamation_seg5_sub_dl_exclamation_mark),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x05002E60
static const Vtx capswitch_seg5_vertex_base[] = {
    {{{   147,      0,   -256}, 0, {     0,    496}, {0x29, 0x00, 0x88, 0xff}}}, //  0
    {{{  -147,      0,   -256}, 0, {     0,   -432}, {0xad, 0x00, 0xa1, 0xff}}}, //  1
    {{{  -147,    137,   -256}, 0, {   400,   -432}, {0xd3, 0x48, 0xa3, 0xff}}}, //  2
    {{{  -147,      0,    256}, 0, {     0,   -432}, {0xd7, 0x00, 0x77, 0xff}}}, //  3
    {{{   147,      0,    256}, 0, {     0,    496}, {0x53, 0x00, 0x5f, 0xff}}}, //  4
    {{{   147,    137,    256}, 0, {   400,    496}, {0x2d, 0x48, 0x5d, 0xff}}}, //  5
    {{{   288,    137,      0}, 0, {   400,    960}, {0x68, 0x48, 0x07, 0xff}}}, //  6
    {{{   288,      0,      0}, 0, {     0,    960}, {0x7c, 0x00, 0xe8, 0xff}}}, //  7
    {{{   147,    137,   -256}, 0, {   400,    496}, {0x3a, 0x47, 0xaa, 0xff}}}, //  8
    {{{   112,    170,   -192}, 0, {   512,    384}, {0x23, 0x72, 0xd7, 0xff}}}, //  9
    {{{   224,    170,      0}, 0, {   512,    741}, {0x35, 0x72, 0x0a, 0xff}}}, // 10
    {{{  -147,    137,    256}, 0, {   400,   -432}, {0xc6, 0x47, 0x56, 0xff}}}, // 11
    {{{   112,    170,    192}, 0, {   512,    384}, {0x11, 0x72, 0x33, 0xff}}}, // 12
    {{{  -288,    137,      0}, 0, {   400,   -904}, {0x98, 0x48, 0xf9, 0xff}}}, // 13
    {{{  -112,    170,    192}, 0, {   512,   -320}, {0xdd, 0x72, 0x29, 0xff}}}, // 14
    {{{  -224,    170,      0}, 0, {   512,   -678}, {0xcb, 0x72, 0xf6, 0xff}}}, // 15
    {{{  -288,      0,      0}, 0, {     0,   -904}, {0x84, 0x00, 0x17, 0xff}}}, // 16
    {{{  -112,    170,   -192}, 0, {   512,   -320}, {0xef, 0x72, 0xcd, 0xff}}}, // 17
};

// 0x05003020 - 0x05003120
const Gfx cap_switch_base_seg5_sub_dl_base[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, capswitch_seg5_texture_base),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(16, 4), CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&capswitch_seg5_lights_white.l, 1),
    gsSPLight(&capswitch_seg5_lights_white.a, 2),
    gsSPVertex(capswitch_seg5_vertex_base, 18, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  4,  7,  6, 0x0),
    gsSP2Triangles( 7,  8,  6, 0x0,  6,  9, 10, 0x0),
    gsSP2Triangles( 6,  8,  9, 0x0,  5,  6, 10, 0x0),
    gsSP2Triangles(11,  5, 12, 0x0,  3,  5, 11, 0x0),
    gsSP2Triangles( 5, 10, 12, 0x0,  7,  0,  8, 0x0),
    gsSP2Triangles( 0,  2,  8, 0x0, 13, 14, 15, 0x0),
    gsSP2Triangles( 1, 13,  2, 0x0, 13, 11, 14, 0x0),
    gsSP2Triangles( 1, 16, 13, 0x0,  8,  2, 17, 0x0),
    gsSP2Triangles( 2, 15, 17, 0x0,  2, 13, 15, 0x0),
    gsSP2Triangles( 8, 17,  9, 0x0, 11, 12, 14, 0x0),
    gsSP2Triangles(16, 11, 13, 0x0, 16,  3, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x05003120 - 0x05003180
const Gfx cap_switch_base_seg5_dl_base[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 2, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 4, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (16 - 1) << G_TEXTURE_IMAGE_FRAC, (4 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(cap_switch_base_seg5_sub_dl_base),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x05003180
static const Vtx capswitch_seg5_vertex_switch[] = {
    {{{  -120,    262,   -205}, 0, {     0,      0}, {0xd9, 0x37, 0x95, 0xff}}},
    {{{   128,      0,   -224}, 0, {     0,      0}, {0x29, 0x0b, 0x89, 0xff}}},
    {{{  -128,      0,   -224}, 0, {     0,      0}, {0xae, 0x0a, 0xa0, 0xff}}},
    {{{   120,    262,   -205}, 0, {     0,      0}, {0x49, 0x2c, 0xa3, 0xff}}},
    {{{   256,      0,      0}, 0, {     0,      0}, {0x7c, 0x0a, 0xe8, 0xff}}},
    {{{  -240,    262,      0}, 0, {     0,      0}, {0x8e, 0x34, 0xf4, 0xff}}},
    {{{  -109,    352,   -109}, 0, {     0,      0}, {0xdb, 0x75, 0xe0, 0xff}}},
    {{{   109,    352,   -109}, 0, {     0,      0}, {0x25, 0x6d, 0xcd, 0xff}}},
    {{{   240,    262,      0}, 0, {     0,      0}, {0x72, 0x34, 0x0c, 0xff}}},
    {{{  -256,      0,      0}, 0, {     0,      0}, {0x84, 0x0a, 0x18, 0xff}}},
    {{{  -120,    262,    205}, 0, {     0,      0}, {0xb7, 0x2c, 0x5d, 0xff}}},
    {{{  -109,    352,    109}, 0, {     0,      0}, {0xdb, 0x6d, 0x33, 0xff}}},
    {{{  -128,      0,    224}, 0, {     0,      0}, {0xd7, 0x0b, 0x77, 0xff}}},
    {{{   120,    262,    204}, 0, {     0,      0}, {0x27, 0x37, 0x6b, 0xff}}},
    {{{   109,    352,    109}, 0, {     0,      0}, {0x25, 0x75, 0x20, 0xff}}},
    {{{   128,      0,    224}, 0, {     0,      0}, {0x52, 0x0a, 0x5f, 0xff}}},
};

// 0x05003280 - 0x05003350
const Gfx capswitch_seg5_sub_dl_switch[] = {
    gsSPVertex(capswitch_seg5_vertex_switch, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 1,  0,  3, 0x0,  2,  5,  0, 0x0),
    gsSP2Triangles( 0,  5,  6, 0x0,  7,  3,  0, 0x0),
    gsSP2Triangles( 6,  7,  0, 0x0,  8,  3,  7, 0x0),
    gsSP2Triangles( 4,  3,  8, 0x0,  9, 10,  5, 0x0),
    gsSP2Triangles(11,  6,  5, 0x0,  5, 10, 11, 0x0),
    gsSP2Triangles( 5,  2,  9, 0x0, 10,  9, 12, 0x0),
    gsSP2Triangles(12, 13, 10, 0x0, 10, 13, 11, 0x0),
    gsSP2Triangles( 6, 11, 14, 0x0, 14, 11, 13, 0x0),
    gsSP2Triangles( 6, 14,  7, 0x0, 15,  8, 13, 0x0),
    gsSP2Triangles(13,  8, 14, 0x0, 13, 12, 15, 0x0),
    gsSP2Triangles( 8, 15,  4, 0x0,  7, 14,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x05003350 - 0x05003370
const Gfx capswitch_seg5_dl_red[] = {
    gsSPLight(&capswitch_seg5_lights_red.l, 1),
    gsSPLight(&capswitch_seg5_lights_red.a, 2),
    gsSPDisplayList(capswitch_seg5_sub_dl_switch),
    gsSPEndDisplayList(),
};

// 0x05003370 - 0x05003390
const Gfx capswitch_seg5_dl_green[] = {
    gsSPLight(&capswitch_seg5_lights_green.l, 1),
    gsSPLight(&capswitch_seg5_lights_green.a, 2),
    gsSPDisplayList(capswitch_seg5_sub_dl_switch),
    gsSPEndDisplayList(),
};

// 0x05003390 - 0x050033B0
const Gfx capswitch_seg5_dl_blue[] = {
    gsSPLight(&capswitch_seg5_lights_blue.l, 1),
    gsSPLight(&capswitch_seg5_lights_blue.a, 2),
    gsSPDisplayList(capswitch_seg5_sub_dl_switch),
    gsSPEndDisplayList(),
};

// 0x050033B0 - 0x050033D0
const Gfx capswitch_seg5_dl_yellow[] = {
    gsSPLight(&capswitch_seg5_lights_yellow.l, 1),
    gsSPLight(&capswitch_seg5_lights_yellow.a, 2),
    gsSPDisplayList(capswitch_seg5_sub_dl_switch),
    gsSPEndDisplayList(),
};
