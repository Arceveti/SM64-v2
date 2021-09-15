// Poundable Pole

// 0x06001038
static const Lights1 poundable_pole_seg6_lights_06001038 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x06001050
ALIGNED8 static const Texture poundable_pole_seg6_texture_top[] = {
#include "actors/poundable_pole/poundable_pole_top.rgba16.inc.c"
};

// 0x06001850
ALIGNED8 static const Texture poundable_pole_seg6_texture_side[] = {
#include "actors/poundable_pole/poundable_pole_side.rgba16.inc.c"
};

// 0x06002050
static const Vtx poundable_pole_seg6_vertex_top[] = {
    {{{   -40,    410,    -96}, 0, {   112,    112}, {0xdf, 0x5c, 0xb0, 0xff}}},
    {{{   -96,    410,    -40}, 0, {   -48,    496}, {0xa1, 0x49, 0xd9, 0xff}}},
    {{{    96,    410,     40}, 0, {  1040,    496}, {0x39, 0x6e, 0x18, 0xff}}},
    {{{    96,    410,    -40}, 0, {   880,    112}, {0x5f, 0x49, 0xd9, 0xff}}},
    {{{    40,    410,    -96}, 0, {   496,    -48}, {0x2d, 0x2a, 0x92, 0xff}}},
    {{{   -96,    410,     40}, 0, {   112,    880}, {0xa1, 0x49, 0x27, 0xff}}},
    {{{   -40,    410,     96}, 0, {   496,   1040}, {0xd9, 0x49, 0x5f, 0xff}}},
    {{{    40,    410,     96}, 0, {   880,    880}, {0x2d, 0x2a, 0x6e, 0xff}}},
};

// 0x060020D0
static const Vtx poundable_pole_seg6_vertex_sides[] = {
    {{{   -71,    -19,     72}, 0, {     0,  31<<5}, {0xa7, 0xff, 0x59, 0xff}}}, //  0
    {{{   -40,    410,     96}, 0, { 31<<5,  -1008}, {0xd9, 0x49, 0x5f, 0xff}}}, //  1
    {{{   -96,    410,     40}, 0, {     0,  -1008}, {0xa1, 0x49, 0x27, 0xff}}}, //  2
    {{{   -71,    -19,    -71}, 0, {   -32,  31<<5}, {0xa7, 0x00, 0xa7, 0xff}}}, //  3
    {{{  -102,    -19,      0}, 0, { 31<<5,  31<<5}, {0x82, 0xff, 0x00, 0xff}}}, //  4
    {{{   -96,    410,    -40}, 0, { 31<<5,  -1056}, {0xa1, 0x49, 0xd9, 0xff}}}, //  5
    {{{   -40,    410,    -96}, 0, {   -32,  -1056}, {0xdf, 0x5c, 0xb0, 0xff}}}, //  6
    {{{     0,    -19,   -102}, 0, {   -32,  31<<5}, {0x00, 0xff, 0x82, 0xff}}}, //  7
    {{{   -71,    -19,    -71}, 0, { 31<<5,  31<<5}, {0xa7, 0x00, 0xa7, 0xff}}}, //  8
    {{{   -40,    410,    -96}, 0, { 31<<5,  -1056}, {0xdf, 0x5c, 0xb0, 0xff}}}, //  9
    {{{    40,    410,    -96}, 0, {   -32,  -1056}, {0x2d, 0x2a, 0x92, 0xff}}}, // 10
    {{{   -96,    410,     40}, 0, { 31<<5,  -1056}, {0xa1, 0x49, 0x27, 0xff}}}, // 11
    {{{  -102,    -19,      0}, 0, {     0,  31<<5}, {0x82, 0xff, 0x00, 0xff}}}, // 12
    {{{   -71,    -19,     72}, 0, { 31<<5,  31<<5}, {0xa7, 0xff, 0x59, 0xff}}}, // 13
    {{{   -96,    410,    -40}, 0, {     0,  -1056}, {0xa1, 0x49, 0xd9, 0xff}}}, // 14
    {{{   102,    -19,      0}, 0, {   -32,  31<<5}, {0x7e, 0xff, 0x00, 0xff}}}, // 15
    {{{    96,    410,    -40}, 0, { 31<<5,  -1056}, {0x5f, 0x49, 0xd9, 0xff}}}, // 16
    {{{    96,    410,     40}, 0, {   -32,  -1056}, {0x39, 0x6e, 0x18, 0xff}}}, // 17
    {{{     0,    -19,    102}, 0, { 31<<5,  31<<5}, {0x00, 0xff, 0x7e, 0xff}}}, // 18
    {{{     0,    -19,    102}, 0, {   -32,  31<<5}, {0x00, 0xff, 0x7e, 0xff}}}, // 19
    {{{    40,    410,     96}, 0, { 31<<5,  -1056}, {0x2d, 0x2a, 0x6e, 0xff}}}, // 20
    {{{   -40,    410,     96}, 0, {   -32,  -1056}, {0xd9, 0x49, 0x5f, 0xff}}}, // 21
    {{{    72,    -19,     72}, 0, { 31<<5,  31<<5}, {0x59, 0xff, 0x59, 0xff}}}, // 22
    {{{    96,    410,     40}, 0, { 31<<5,  -1056}, {0x39, 0x6e, 0x18, 0xff}}}, // 23
    {{{    72,    -19,     72}, 0, {     0,  31<<5}, {0x59, 0xff, 0x59, 0xff}}}, // 24
    {{{   102,    -19,      0}, 0, { 31<<5,  31<<5}, {0x7e, 0xff, 0x00, 0xff}}}, // 25
    {{{    40,    410,     96}, 0, {     0,  -1056}, {0x2d, 0x2a, 0x6e, 0xff}}}, // 26
    {{{    72,    -19,    -71}, 0, { 31<<5,  31<<5}, {0x59, 0xff, 0xa7, 0xff}}}, // 27
    {{{    40,    410,    -96}, 0, { 31<<5,  -1056}, {0x2d, 0x2a, 0x92, 0xff}}}, // 28
    {{{    96,    410,    -40}, 0, {   -32,  -1056}, {0x5f, 0x49, 0xd9, 0xff}}}, // 29
    {{{    72,    -19,    -71}, 0, {   -32,  31<<5}, {0x59, 0xff, 0xa7, 0xff}}}, // 30
    {{{     0,    -19,   -102}, 0, { 31<<5,  31<<5}, {0x00, 0xff, 0x82, 0xff}}}, // 31
};

// 0x060022F0 - 0x06002358
const Gfx poundable_pole_seg6_sub_dl_top[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, poundable_pole_seg6_texture_top),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&poundable_pole_seg6_lights_06001038.l, 1),
    gsSPLight(&poundable_pole_seg6_lights_06001038.a, 2),
    gsSPVertex(poundable_pole_seg6_vertex_top, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 0,  2,  3, 0x0,  2,  1,  5, 0x0),
    gsSP2Triangles( 2,  5,  6, 0x0,  2,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x06002358 - 0x06002410
const Gfx poundable_pole_seg6_sub_dl_sides[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, poundable_pole_seg6_texture_side),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(poundable_pole_seg6_vertex_sides, 32, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(12, 11, 14, 0x0, 16, 15, 27, 0x0),
    gsSP2Triangles(15, 16, 17, 0x0,  0, 18,  1, 0x0),
    gsSP2Triangles(19, 20, 21, 0x0, 19, 22, 20, 0x0),
    gsSP2Triangles(23, 24, 25, 0x0, 24, 23, 26, 0x0),
    gsSP2Triangles(28, 29, 30, 0x0, 31, 28, 30, 0x0),
    gsSPEndDisplayList(),
};

// 0x06002410 - 0x06002490
const Gfx poundable_pole_seg6_dl_06002410[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(poundable_pole_seg6_sub_dl_top),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(poundable_pole_seg6_sub_dl_sides),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
