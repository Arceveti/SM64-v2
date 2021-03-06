// Blue Coin Switch

// 0x08000000
static const Lights1 blue_coin_switch_seg8_lights_08000000 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x08000018
ALIGNED8 static const Texture blue_coin_switch_seg8_texture_side[] = {
#include "actors/blue_coin_switch/blue_coin_switch_side.rgba16.inc.c"
};

// 0x08000418
ALIGNED8 static const Texture blue_coin_switch_seg8_texture_top[] = {
#include "actors/blue_coin_switch/blue_coin_switch_top.rgba16.inc.c"
};

// 0x08000C18
static const Vtx blue_coin_switch_seg8_vertex_sides[] = {
    {{{    26,      0,     26}, 0, ST_B(    32,     16), {0x00, 0x00, 0x7f, 0xff}}},
    {{{    26,     26,     26}, 0, ST_B(    32,      0), {0x00, 0x00, 0x7f, 0xff}}},
    {{{   -26,     26,     26}, 0, ST_B(     0,      0), {0x00, 0x00, 0x7f, 0xff}}},
    {{{   -26,      0,     26}, 0, ST_B(     0,     16), {0x00, 0x00, 0x7f, 0xff}}},
    {{{   -26,      0,    -26}, 0, ST_B(    32,     16), {0x00, 0x00, 0x81, 0xff}}},
    {{{    26,     26,    -26}, 0, ST_B(     0,      0), {0x00, 0x00, 0x81, 0xff}}},
    {{{    26,      0,    -26}, 0, ST_B(     0,     16), {0x00, 0x00, 0x81, 0xff}}},
    {{{   -26,     26,    -26}, 0, ST_B(    32,      0), {0x00, 0x00, 0x81, 0xff}}},
    {{{   -26,      0,     26}, 0, ST_B(    32,     16), {0x81, 0x00, 0x00, 0xff}}},
    {{{   -26,     26,    -26}, 0, ST_B(     0,      0), {0x81, 0x00, 0x00, 0xff}}},
    {{{   -26,      0,    -26}, 0, ST_B(     0,     16), {0x81, 0x00, 0x00, 0xff}}},
    {{{   -26,     26,     26}, 0, ST_B(    32,      0), {0x81, 0x00, 0x00, 0xff}}},
    {{{    26,      0,    -26}, 0, ST_B(    32,     16), {0x7f, 0x00, 0x00, 0xff}}},
    {{{    26,     26,    -26}, 0, ST_B(    32,      0), {0x7f, 0x00, 0x00, 0xff}}},
    {{{    26,     26,     26}, 0, ST_B(     0,      0), {0x7f, 0x00, 0x00, 0xff}}},
    {{{    26,      0,     26}, 0, ST_B(     0,     16), {0x7f, 0x00, 0x00, 0xff}}},
};

// 0x08000D18
static const Vtx blue_coin_switch_seg8_vertex_top[] = {
    {{{    26,     26,    -26}, 0, ST_B(    32,      0), {0x00, 0x7f, 0x00, 0xff}}},
    {{{   -26,     26,     26}, 0, ST_B(     0,     32), {0x00, 0x7f, 0x00, 0xff}}},
    {{{    26,     26,     26}, 0, ST_B(    32,     32), {0x00, 0x7f, 0x00, 0xff}}},
    {{{   -26,     26,    -26}, 0, ST_B(     0,      0), {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x08000D58 - 0x08000DD0
const Gfx blue_coin_switch_seg8_sub_dl_sides[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, blue_coin_switch_seg8_texture_side),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(16, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&blue_coin_switch_seg8_lights_08000000.l, 1),
    gsSPLight(&blue_coin_switch_seg8_lights_08000000.a, 2),
    gsSPVertex(blue_coin_switch_seg8_vertex_sides, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x08000DD0 - 0x08000E08
const Gfx blue_coin_switch_seg8_sub_dl_top[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, blue_coin_switch_seg8_texture_top),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(blue_coin_switch_seg8_vertex_top, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x08000E08 - 0x08000E98
const Gfx blue_coin_switch_seg8_dl_08000E08[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, (G_TX_WRAP | G_TX_NOMIRROR), G_TX_NOMASK, G_TX_NOLOD, (G_TX_WRAP | G_TX_NOMIRROR), G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 4, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, ((32 - 1) << G_TEXTURE_IMAGE_FRAC), ((16 - 1) << G_TEXTURE_IMAGE_FRAC)),
    gsSPDisplayList(blue_coin_switch_seg8_sub_dl_sides),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, ((32 - 1) << G_TEXTURE_IMAGE_FRAC), ((32 - 1) << G_TEXTURE_IMAGE_FRAC)),
    gsSPDisplayList(blue_coin_switch_seg8_sub_dl_top),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
