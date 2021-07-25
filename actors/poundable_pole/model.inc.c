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
static const Vtx poundable_pole_seg6_vertex_sides_1[] = {
    {{{   -71,    -19,     72}, 0, {     0,  31<<5}, {0xa7, 0xff, 0x59, 0xff}}},
    {{{   -40,    410,     96}, 0, { 31<<5,  -1008}, {0xd9, 0x49, 0x5f, 0xff}}},
    {{{   -96,    410,     40}, 0, {     0,  -1008}, {0xa1, 0x49, 0x27, 0xff}}},
    {{{   -71,    -19,    -71}, 0, {   -32,  31<<5}, {0xa7, 0x00, 0xa7, 0xff}}},
    {{{  -102,    -19,      0}, 0, { 31<<5,  31<<5}, {0x82, 0xff, 0x00, 0xff}}},
    {{{   -96,    410,    -40}, 0, { 31<<5,  -1056}, {0xa1, 0x49, 0xd9, 0xff}}},
    {{{   -40,    410,    -96}, 0, {   -32,  -1056}, {0xdf, 0x5c, 0xb0, 0xff}}},
    {{{     0,    -19,   -102}, 0, {   -32,  31<<5}, {0x00, 0xff, 0x82, 0xff}}},
    {{{   -71,    -19,    -71}, 0, { 31<<5,  31<<5}, {0xa7, 0x00, 0xa7, 0xff}}},
    {{{   -40,    410,    -96}, 0, { 31<<5,  -1056}, {0xdf, 0x5c, 0xb0, 0xff}}},
    {{{    40,    410,    -96}, 0, {   -32,  -1056}, {0x2d, 0x2a, 0x92, 0xff}}},
    {{{   -96,    410,     40}, 0, { 31<<5,  -1056}, {0xa1, 0x49, 0x27, 0xff}}},
    {{{  -102,    -19,      0}, 0, {     0,  31<<5}, {0x82, 0xff, 0x00, 0xff}}},
    {{{   -71,    -19,     72}, 0, { 31<<5,  31<<5}, {0xa7, 0xff, 0x59, 0xff}}},
    {{{   -96,    410,    -40}, 0, {     0,  -1056}, {0xa1, 0x49, 0xd9, 0xff}}},
};

// 0x060021C0
static const Vtx poundable_pole_seg6_vertex_sides_2[] = {
    {{{   102,    -19,      0}, 0, {   -32,  31<<5}, {0x7e, 0xff, 0x00, 0xff}}},
    {{{    96,    410,    -40}, 0, { 31<<5,  -1056}, {0x5f, 0x49, 0xd9, 0xff}}},
    {{{    96,    410,     40}, 0, {   -32,  -1056}, {0x39, 0x6e, 0x18, 0xff}}},
    {{{   -71,    -19,     72}, 0, {     0,  31<<5}, {0xa7, 0xff, 0x59, 0xff}}},
    {{{     0,    -19,    102}, 0, { 31<<5,  31<<5}, {0x00, 0xff, 0x7e, 0xff}}},
    {{{   -40,    410,     96}, 0, { 31<<5,  -1012}, {0xd9, 0x49, 0x5f, 0xff}}},
    {{{     0,    -19,    102}, 0, {   -32,  31<<5}, {0x00, 0xff, 0x7e, 0xff}}},
    {{{    40,    410,     96}, 0, { 31<<5,  -1056}, {0x2d, 0x2a, 0x6e, 0xff}}},
    {{{   -40,    410,     96}, 0, {   -32,  -1056}, {0xd9, 0x49, 0x5f, 0xff}}},
    {{{    72,    -19,     72}, 0, { 31<<5,  31<<5}, {0x59, 0xff, 0x59, 0xff}}},
    {{{    96,    410,     40}, 0, { 31<<5,  -1056}, {0x39, 0x6e, 0x18, 0xff}}},
    {{{    72,    -19,     72}, 0, {     0,  31<<5}, {0x59, 0xff, 0x59, 0xff}}},
    {{{   102,    -19,      0}, 0, { 31<<5,  31<<5}, {0x7e, 0xff, 0x00, 0xff}}},
    {{{    40,    410,     96}, 0, {     0,  -1056}, {0x2d, 0x2a, 0x6e, 0xff}}},
    {{{    72,    -19,    -71}, 0, { 31<<5,  31<<5}, {0x59, 0xff, 0xa7, 0xff}}},
};

// 0x060022B0
static const Vtx poundable_pole_seg6_vertex_sides_3[] = {
    {{{    40,    410,    -96}, 0, { 31<<5,  -1056}, {0x2d, 0x2a, 0x92, 0xff}}},
    {{{    96,    410,    -40}, 0, {   -32,  -1056}, {0x5f, 0x49, 0xd9, 0xff}}},
    {{{    72,    -19,    -71}, 0, {   -32,  31<<5}, {0x59, 0xff, 0xa7, 0xff}}},
    {{{     0,    -19,   -102}, 0, { 31<<5,  31<<5}, {0x00, 0xff, 0x82, 0xff}}},
};

// 0x060022F0 - 0x06002358
const Gfx poundable_pole_seg6_sub_dl_top[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, poundable_pole_seg6_texture_top),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
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
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(poundable_pole_seg6_vertex_sides_1, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(12, 11, 14, 0x0),
    gsSPVertex(poundable_pole_seg6_vertex_sides_2, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 11, 10, 13, 0x0),
    gsSP1Triangle( 1,  0, 14, 0x0),
    gsSPVertex(poundable_pole_seg6_vertex_sides_3, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
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
