// Bomb

// 0x06057AA8
static const Lights1 bomb_seg6_lights_spikes = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x06057AC0
ALIGNED8 static const Texture bomb_seg6_texture_left_side[] = {
#include "actors/bomb/bomb_left_side.rgba16.inc.c"
};

// 0x06058AC0
ALIGNED8 static const Texture bomb_seg6_texture_right_side[] = {
#include "actors/bomb/bomb_right_side.rgba16.inc.c"
};

// 0x06059AC0
ALIGNED8 static const Texture bomb_seg6_texture_spike[] = {
#include "actors/bomb/bomb_spike.rgba16.inc.c"
};

// 0x0605A2C0
static const Vtx bomb_seg6_vertex_sphere[] = {
    {{{     0,    120,      0}, 0, ST_B(32-0.5,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{  -120,   -120,      0}, 0, ST_B(  -0.5,     64), {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,   -120,      0}, 0, ST_B(32-0.5,     64), {0xff, 0xff, 0xff, 0xff}}},
    {{{  -120,    120,      0}, 0, ST_B(  -0.5,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{   120,    120,      0}, 0, ST_B(32+0.5,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,   -120,      0}, 0, ST_B(   0.5,     64), {0xff, 0xff, 0xff, 0xff}}},
    {{{   120,   -120,      0}, 0, ST_B(32+0.5,     64), {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,    120,      0}, 0, ST_B(   0.5,      0), {0xff, 0xff, 0xff, 0xff}}},
};

// 0x0605A340
static const Vtx bomb_seg6_vertex_spike_1[] = {
    {{{     0,    -59,      0}, 0, {   502,    -16}, {0xf7, 0x82, 0xf7, 0xff}}},
    {{{    -9,    -36,      0}, 0, {    16,    976}, {0x8a, 0xd2, 0xfd, 0xff}}},
    {{{     0,    -36,     -8}, 0, {   938,    976}, {0xfd, 0xd7, 0x89, 0xff}}},
    {{{     0,     37,     -8}, 0, {     0,    976}, {0xfd, 0x29, 0x89, 0xff}}},
    {{{    -9,     37,      0}, 0, {   972,  30<<5}, {0x8a, 0x2e, 0xfd, 0xff}}},
    {{{     0,     60,      0}, 0, {   432,    -16}, {0xf7, 0x7e, 0xf7, 0xff}}},
    {{{    10,     37,      0}, 0, {   -16,  30<<5}, {0x74, 0x32, 0xfd, 0xff}}},
    {{{     0,     37,     -8}, 0, { 30<<5,  30<<5}, {0xfd, 0x29, 0x89, 0xff}}},
    {{{     0,     60,      0}, 0, {   468,    -16}, {0xf7, 0x7e, 0xf7, 0xff}}},
    {{{    -9,     37,      0}, 0, {     0,    976}, {0x8a, 0x2e, 0xfd, 0xff}}},
    {{{     0,     37,      9}, 0, {   976,    968}, {0xfd, 0x2e, 0x76, 0xff}}},
    {{{     0,     60,      0}, 0, {   470,      0}, {0xf7, 0x7e, 0xf7, 0xff}}},
    {{{     0,     37,      9}, 0, {     0,    976}, {0xfd, 0x2e, 0x76, 0xff}}},
    {{{    10,     37,      0}, 0, { 30<<5,  31<<5}, {0x74, 0x32, 0xfd, 0xff}}},
    {{{     0,     60,      0}, 0, {   496,     32}, {0xf7, 0x7e, 0xf7, 0xff}}},
};

// 0x0605A430
static const Vtx bomb_seg6_vertex_spike_2[] = {
    {{{     0,     10,     37}, 0, {   -16,    976}, {0xfd, 0x74, 0x32, 0xff}}},
    {{{    -9,      0,     37}, 0, {   976,    976}, {0x8a, 0xf9, 0x2e, 0xff}}},
    {{{     0,      0,     60}, 0, {   428,      0}, {0xf8, 0xee, 0x7d, 0xff}}},
    {{{     0,    -59,      0}, 0, {   496,    -16}, {0xf7, 0x82, 0xf7, 0xff}}},
    {{{     0,    -36,     -8}, 0, {     0,    944}, {0xfd, 0xd7, 0x89, 0xff}}},
    {{{    10,    -36,      0}, 0, { 30<<5,  30<<5}, {0x74, 0xce, 0xfd, 0xff}}},
    {{{     0,    -59,      0}, 0, {   458,    -16}, {0xf7, 0x82, 0xf7, 0xff}}},
    {{{     0,    -36,      9}, 0, {    16,    944}, {0xfd, 0xd2, 0x76, 0xff}}},
    {{{    -9,    -36,      0}, 0, {   916,  30<<5}, {0x8a, 0xd2, 0xfd, 0xff}}},
    {{{     0,    -59,      0}, 0, {   486,      0}, {0xf7, 0x82, 0xf7, 0xff}}},
    {{{    10,    -36,      0}, 0, {     0,  30<<5}, {0x74, 0xce, 0xfd, 0xff}}},
    {{{     0,    -36,      9}, 0, { 30<<5,    952}, {0xfd, 0xd2, 0x76, 0xff}}},
    {{{    10,      0,     37}, 0, {     0,    976}, {0x74, 0xf9, 0x32, 0xff}}},
    {{{     0,     10,     37}, 0, {   952,    976}, {0xfd, 0x74, 0x32, 0xff}}},
    {{{     0,      0,     60}, 0, {   428,    -16}, {0xf8, 0xee, 0x7d, 0xff}}},
};

// 0x0605A520
static const Vtx bomb_seg6_vertex_spike_3[] = {
    {{{    37,      0,     -9}, 0, {    16,  30<<5}, {0x2e, 0xf9, 0x8a, 0xff}}},
    {{{    37,     10,      0}, 0, {   928,    976}, {0x32, 0x74, 0xfd, 0xff}}},
    {{{    60,      0,      0}, 0, {   496,      0}, {0x7d, 0xee, 0xf8, 0xff}}},
    {{{     0,     -8,     37}, 0, {   -16,    976}, {0xfd, 0x89, 0x29, 0xff}}},
    {{{    10,      0,     37}, 0, { 30<<5,    980}, {0x74, 0xf9, 0x32, 0xff}}},
    {{{     0,      0,     60}, 0, {   428,    -16}, {0xf8, 0xee, 0x7d, 0xff}}},
    {{{    -9,      0,     37}, 0, {   -24,    976}, {0x8a, 0xf9, 0x2e, 0xff}}},
    {{{     0,     -8,     37}, 0, {   976,    976}, {0xfd, 0x89, 0x29, 0xff}}},
    {{{     0,      0,     60}, 0, { 15<<5,      0}, {0xf8, 0xee, 0x7d, 0xff}}},
    {{{    37,     -8,      0}, 0, {   -16,    968}, {0x29, 0x89, 0xfd, 0xff}}},
    {{{    37,      0,     -9}, 0, { 30<<5,    972}, {0x2e, 0xf9, 0x8a, 0xff}}},
    {{{    60,      0,      0}, 0, {   400,    -16}, {0x7d, 0xee, 0xf8, 0xff}}},
    {{{    37,     10,      0}, 0, {     0,  30<<5}, {0x32, 0x74, 0xfd, 0xff}}},
    {{{    37,      0,     10}, 0, {   978,  30<<5}, {0x32, 0xf9, 0x74, 0xff}}},
    {{{    60,      0,      0}, 0, {   464,    -16}, {0x7d, 0xee, 0xf8, 0xff}}},
};

// 0x0605A610
static const Vtx bomb_seg6_vertex_spike_4[] = {
    {{{   -59,      0,      0}, 0, {   448,     16}, {0x83, 0xee, 0xf8, 0xff}}},
    {{{   -36,      0,     -9}, 0, {     0,    976}, {0xd2, 0xf9, 0x8a, 0xff}}},
    {{{   -36,     -8,      0}, 0, {   944,    980}, {0xd7, 0x89, 0xfd, 0xff}}},
    {{{    37,      0,     10}, 0, {   -16,    970}, {0x32, 0xf9, 0x74, 0xff}}},
    {{{    37,     -8,      0}, 0, { 30<<5,  30<<5}, {0x29, 0x89, 0xfd, 0xff}}},
    {{{    60,      0,      0}, 0, {   488,      0}, {0x7d, 0xee, 0xf8, 0xff}}},
    {{{   -59,      0,      0}, 0, {   370,     16}, {0x83, 0xee, 0xf8, 0xff}}},
    {{{   -36,      0,     10}, 0, {     0,  30<<5}, {0xce, 0xf9, 0x74, 0xff}}},
    {{{   -36,     10,      0}, 0, {   944,    968}, {0xce, 0x74, 0xfd, 0xff}}},
    {{{   -59,      0,      0}, 0, {   428,     16}, {0x83, 0xee, 0xf8, 0xff}}},
    {{{   -36,     10,      0}, 0, {     8,    968}, {0xce, 0x74, 0xfd, 0xff}}},
    {{{   -36,      0,     -9}, 0, {   944,    976}, {0xd2, 0xf9, 0x8a, 0xff}}},
    {{{   -59,      0,      0}, 0, {   464,    -16}, {0x83, 0xee, 0xf8, 0xff}}},
    {{{   -36,     -8,      0}, 0, {     0,  30<<5}, {0xd7, 0x89, 0xfd, 0xff}}},
    {{{   -36,      0,     10}, 0, { 30<<5,    976}, {0xce, 0xf9, 0x74, 0xff}}},
};

// 0x0605A700
static const Vtx bomb_seg6_vertex_spike_5[] = {
    {{{     0,      0,    -59}, 0, {   464,      0}, {0xf8, 0xee, 0x83, 0xff}}},
    {{{     0,     10,    -36}, 0, {   -16,    968}, {0xfd, 0x74, 0xce, 0xff}}},
    {{{    10,      0,    -36}, 0, {   944,    976}, {0x74, 0xf9, 0xce, 0xff}}},
    {{{     0,      0,    -59}, 0, { 15<<5,    -16}, {0xf8, 0xee, 0x83, 0xff}}},
    {{{    -9,      0,    -36}, 0, {    16,  30<<5}, {0x8a, 0xf9, 0xd2, 0xff}}},
    {{{     0,     10,    -36}, 0, {   944,  30<<5}, {0xfd, 0x74, 0xce, 0xff}}},
    {{{     0,      0,    -59}, 0, {   416,      0}, {0xf8, 0xee, 0x83, 0xff}}},
    {{{    10,      0,    -36}, 0, {   -16,    970}, {0x74, 0xf9, 0xce, 0xff}}},
    {{{     0,     -8,    -36}, 0, {   968,    968}, {0xfd, 0x89, 0xd7, 0xff}}},
    {{{     0,      0,    -59}, 0, {   400,      8}, {0xf8, 0xee, 0x83, 0xff}}},
    {{{     0,     -8,    -36}, 0, {     0,    976}, {0xfd, 0x89, 0xd7, 0xff}}},
    {{{    -9,      0,    -36}, 0, {   952,  30<<5}, {0x8a, 0xf9, 0xd2, 0xff}}},
};

// 0x0605A7C0 - 0x0605A7F8
const Gfx bomb_seg6_sub_dl_sphere[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bomb_seg6_texture_left_side),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 64), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bomb_seg6_vertex_sphere, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bomb_seg6_texture_right_side),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 64), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x0605A830 - 0x0605A8A8
const Gfx bomb_seg6_dl_sphere[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, (G_TX_WRAP | G_TX_NOMIRROR), G_TX_NOMASK, G_TX_NOLOD, (G_TX_WRAP | G_TX_NOMIRROR), G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, ((32 - 1) << G_TEXTURE_IMAGE_FRAC), ((64 - 1) << G_TEXTURE_IMAGE_FRAC)),
    gsSPDisplayList(bomb_seg6_sub_dl_sphere),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x0605A8A8 - 0x0605A9C0
const Gfx bomb_seg6_sub_dl_spikes[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bomb_seg6_texture_spike),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&bomb_seg6_lights_spikes.l, 1),
    gsSPLight(&bomb_seg6_lights_spikes.a, 2),
    gsSPVertex(bomb_seg6_vertex_spike_1, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle( 12, 13, 14, 0x0),
    gsSPVertex(bomb_seg6_vertex_spike_2, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle( 12, 13, 14, 0x0),
    gsSPVertex(bomb_seg6_vertex_spike_3, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle( 12, 13, 14, 0x0),
    gsSPVertex(bomb_seg6_vertex_spike_4, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle( 12, 13, 14, 0x0),
    gsSPVertex(bomb_seg6_vertex_spike_5, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x0605A9C0 - 0x0605AA20
const Gfx bomb_seg6_dl_spikes[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, (G_TX_WRAP | G_TX_NOMIRROR), G_TX_NOMASK, G_TX_NOLOD, (G_TX_WRAP | G_TX_NOMIRROR), G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, (G_TX_WRAP | G_TX_NOMIRROR), 5, G_TX_NOLOD, (G_TX_WRAP | G_TX_NOMIRROR), 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, ((32 - 1) << G_TEXTURE_IMAGE_FRAC), ((32 - 1) << G_TEXTURE_IMAGE_FRAC)),
    gsSPDisplayList(bomb_seg6_sub_dl_spikes),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
