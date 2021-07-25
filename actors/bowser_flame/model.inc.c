// Bowser Flame

//! TODO: These 64x64 textures are referenced as two different texture addresses in the DLs

// 0x06000000
ALIGNED8 static const Texture flame_seg6_texture_bowser_flame_0[] = {
#include "actors/bowser_flame/bowser_flame_0.rgba16.inc.c"
};

// 0x06002000
ALIGNED8 static const Texture flame_seg6_texture_bowser_flame_1[] = {
#include "actors/bowser_flame/bowser_flame_1.rgba16.inc.c"
};

// 0x06004000
ALIGNED8 static const Texture flame_seg6_texture_bowser_flame_2[] = {
#include "actors/bowser_flame/bowser_flame_2.rgba16.inc.c"
};

// 0x06006000
ALIGNED8 static const Texture flame_seg6_texture_bowser_flame_3[] = {
#include "actors/bowser_flame/bowser_flame_3.rgba16.inc.c"
};

// 0x06008000
ALIGNED8 static const Texture flame_seg6_texture_bowser_flame_4[] = {
#include "actors/bowser_flame/bowser_flame_4.rgba16.inc.c"
};

// 0x0600A000
ALIGNED8 static const Texture flame_seg6_texture_bowser_flame_5[] = {
#include "actors/bowser_flame/bowser_flame_5.rgba16.inc.c"
};

// 0x0600C000
ALIGNED8 static const Texture flame_seg6_texture_bowser_flame_6[] = {
#include "actors/bowser_flame/bowser_flame_6.rgba16.inc.c"
};

// 0x0600E000
ALIGNED8 static const Texture flame_seg6_texture_bowser_flame_7[] = {
#include "actors/bowser_flame/bowser_flame_7.rgba16.inc.c"
};

// 0x06010000
ALIGNED8 static const Texture flame_seg6_texture_bowser_flame_8[] = {
#include "actors/bowser_flame/bowser_flame_8.rgba16.inc.c"
};

// 0x06012000
ALIGNED8 static const Texture flame_seg6_texture_bowser_flame_9[] = {
#include "actors/bowser_flame/bowser_flame_9.rgba16.inc.c"
};

// 0x06014000
ALIGNED8 static const Texture flame_seg6_texture_bowser_flame_10[] = {
#include "actors/bowser_flame/bowser_flame_10.rgba16.inc.c"
};

// 0x06016000
ALIGNED8 static const Texture flame_seg6_texture_bowser_flame_11[] = {
#include "actors/bowser_flame/bowser_flame_11.rgba16.inc.c"
};

// 0x06018000
ALIGNED8 static const Texture flame_seg6_texture_bowser_flame_12[] = {
#include "actors/bowser_flame/bowser_flame_12.rgba16.inc.c"
};

// 0x0601A000
ALIGNED8 static const Texture flame_seg6_texture_bowser_flame_13[] = {
#include "actors/bowser_flame/bowser_flame_13.rgba16.inc.c"
};

// 0x0601C000
static const Vtx flame_seg6_vertex_bowser_flame[] = {
    {{{  -150,    150,      0}, 0, {     0,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   150,    150,      0}, 0, { 63<<5,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   150,    300,      0}, 0, { 63<<5,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  -150,    300,      0}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  -150,      0,      0}, 0, {     0,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   150,      0,      0}, 0, { 63<<5,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   150,    150,      0}, 0, { 63<<5,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  -150,    150,      0}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}},
};

// 0x0601C080 - 0x0601C0B0
const Gfx flame_seg6_dl_bowser_flame_start[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPGeometryMode(G_LIGHTING, G_SHADING_SMOOTH),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

// 0x0601C0B0 - 0x0601C0C8
const Gfx flame_seg6_sub_dl_bowser_flame_upper[] = {
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0601C0C8 - 0x0601C0E0
const Gfx flame_seg6_sub_dl_bowser_flame_lower[] = {
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x0601C0E0 - 0x0601C108
const Gfx flame_seg6_dl_bowser_flame_end[] = {
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x0601C108 - 0x0601C1A8
const Gfx flame_seg6_dl_0[] = {
    gsSPDisplayList(flame_seg6_dl_bowser_flame_start),
    gsDPLoadTextureBlock(flame_seg6_texture_bowser_flame_0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(flame_seg6_vertex_bowser_flame, 8, 0),
    gsSPDisplayList(flame_seg6_sub_dl_bowser_flame_upper),
    gsDPLoadTextureBlock((u8*)flame_seg6_texture_bowser_flame_0 + 0x1000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPDisplayList(flame_seg6_sub_dl_bowser_flame_lower),
    gsSPDisplayList(flame_seg6_dl_bowser_flame_end),
    gsSPEndDisplayList(),
};

// 0x0601C1A8 - 0x0601C248
const Gfx flame_seg6_dl_1[] = {
    gsSPDisplayList(flame_seg6_dl_bowser_flame_start),
    gsDPLoadTextureBlock(flame_seg6_texture_bowser_flame_1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(flame_seg6_vertex_bowser_flame, 8, 0),
    gsSPDisplayList(flame_seg6_sub_dl_bowser_flame_upper),
    gsDPLoadTextureBlock((u8*)flame_seg6_texture_bowser_flame_1 + 0x1000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPDisplayList(flame_seg6_sub_dl_bowser_flame_lower),
    gsSPDisplayList(flame_seg6_dl_bowser_flame_end),
    gsSPEndDisplayList(),
};

// 0x0601C248 - 0x0601C2E8
const Gfx flame_seg6_dl_2[] = {
    gsSPDisplayList(flame_seg6_dl_bowser_flame_start),
    gsDPLoadTextureBlock(flame_seg6_texture_bowser_flame_2, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(flame_seg6_vertex_bowser_flame, 8, 0),
    gsSPDisplayList(flame_seg6_sub_dl_bowser_flame_upper),
    gsDPLoadTextureBlock((u8*)flame_seg6_texture_bowser_flame_2 + 0x1000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPDisplayList(flame_seg6_sub_dl_bowser_flame_lower),
    gsSPDisplayList(flame_seg6_dl_bowser_flame_end),
    gsSPEndDisplayList(),
};

// 0x0601C2E8 - 0x0601C388
const Gfx flame_seg6_dl_3[] = {
    gsSPDisplayList(flame_seg6_dl_bowser_flame_start),
    gsDPLoadTextureBlock(flame_seg6_texture_bowser_flame_3, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(flame_seg6_vertex_bowser_flame, 8, 0),
    gsSPDisplayList(flame_seg6_sub_dl_bowser_flame_upper),
    gsDPLoadTextureBlock((u8*)flame_seg6_texture_bowser_flame_3 + 0x1000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPDisplayList(flame_seg6_sub_dl_bowser_flame_lower),
    gsSPDisplayList(flame_seg6_dl_bowser_flame_end),
    gsSPEndDisplayList(),
};

// 0x0601C388 - 0x0601C428
const Gfx flame_seg6_dl_4[] = {
    gsSPDisplayList(flame_seg6_dl_bowser_flame_start),
    gsDPLoadTextureBlock(flame_seg6_texture_bowser_flame_4, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(flame_seg6_vertex_bowser_flame, 8, 0),
    gsSPDisplayList(flame_seg6_sub_dl_bowser_flame_upper),
    gsDPLoadTextureBlock((u8*)flame_seg6_texture_bowser_flame_4 + 0x1000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPDisplayList(flame_seg6_sub_dl_bowser_flame_lower),
    gsSPDisplayList(flame_seg6_dl_bowser_flame_end),
    gsSPEndDisplayList(),
};

// 0x0601C428 - 0x0601C4C8
const Gfx flame_seg6_dl_5[] = {
    gsSPDisplayList(flame_seg6_dl_bowser_flame_start),
    gsDPLoadTextureBlock(flame_seg6_texture_bowser_flame_5, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(flame_seg6_vertex_bowser_flame, 8, 0),
    gsSPDisplayList(flame_seg6_sub_dl_bowser_flame_upper),
    gsDPLoadTextureBlock((u8*)flame_seg6_texture_bowser_flame_5 + 0x1000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPDisplayList(flame_seg6_sub_dl_bowser_flame_lower),
    gsSPDisplayList(flame_seg6_dl_bowser_flame_end),
    gsSPEndDisplayList(),
};

// 0x0601C4C8 - 0x0601C568
const Gfx flame_seg6_dl_6[] = {
    gsSPDisplayList(flame_seg6_dl_bowser_flame_start),
    gsDPLoadTextureBlock(flame_seg6_texture_bowser_flame_6, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(flame_seg6_vertex_bowser_flame, 8, 0),
    gsSPDisplayList(flame_seg6_sub_dl_bowser_flame_upper),
    gsDPLoadTextureBlock((u8*)flame_seg6_texture_bowser_flame_6 + 0x1000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPDisplayList(flame_seg6_sub_dl_bowser_flame_lower),
    gsSPDisplayList(flame_seg6_dl_bowser_flame_end),
    gsSPEndDisplayList(),
};

// 0x0601C568 - 0x0601C608
const Gfx flame_seg6_dl_7[] = {
    gsSPDisplayList(flame_seg6_dl_bowser_flame_start),
    gsDPLoadTextureBlock(flame_seg6_texture_bowser_flame_7, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(flame_seg6_vertex_bowser_flame, 8, 0),
    gsSPDisplayList(flame_seg6_sub_dl_bowser_flame_upper),
    gsDPLoadTextureBlock((u8*)flame_seg6_texture_bowser_flame_7 + 0x1000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPDisplayList(flame_seg6_sub_dl_bowser_flame_lower),
    gsSPDisplayList(flame_seg6_dl_bowser_flame_end),
    gsSPEndDisplayList(),
};

// 0x0601C608 - 0x0601C6A8
const Gfx flame_seg6_dl_8[] = {
    gsSPDisplayList(flame_seg6_dl_bowser_flame_start),
    gsDPLoadTextureBlock(flame_seg6_texture_bowser_flame_8, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(flame_seg6_vertex_bowser_flame, 8, 0),
    gsSPDisplayList(flame_seg6_sub_dl_bowser_flame_upper),
    gsDPLoadTextureBlock((u8*)flame_seg6_texture_bowser_flame_8 + 0x1000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPDisplayList(flame_seg6_sub_dl_bowser_flame_lower),
    gsSPDisplayList(flame_seg6_dl_bowser_flame_end),
    gsSPEndDisplayList(),
};

// 0x0601C6A8 - 0x0601C748
const Gfx flame_seg6_dl_9[] = {
    gsSPDisplayList(flame_seg6_dl_bowser_flame_start),
    gsDPLoadTextureBlock(flame_seg6_texture_bowser_flame_9, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(flame_seg6_vertex_bowser_flame, 8, 0),
    gsSPDisplayList(flame_seg6_sub_dl_bowser_flame_upper),
    gsDPLoadTextureBlock((u8*)flame_seg6_texture_bowser_flame_9 + 0x1000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPDisplayList(flame_seg6_sub_dl_bowser_flame_lower),
    gsSPDisplayList(flame_seg6_dl_bowser_flame_end),
    gsSPEndDisplayList(),
};

// 0x0601C748 - 0x0601C7E8
const Gfx flame_seg6_dl_10[] = {
    gsSPDisplayList(flame_seg6_dl_bowser_flame_start),
    gsDPLoadTextureBlock(flame_seg6_texture_bowser_flame_10, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(flame_seg6_vertex_bowser_flame, 8, 0),
    gsSPDisplayList(flame_seg6_sub_dl_bowser_flame_upper),
    gsDPLoadTextureBlock((u8*)flame_seg6_texture_bowser_flame_10 + 0x1000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPDisplayList(flame_seg6_sub_dl_bowser_flame_lower),
    gsSPDisplayList(flame_seg6_dl_bowser_flame_end),
    gsSPEndDisplayList(),
};

// 0x0601C7E8 - 0x0601C888
const Gfx flame_seg6_dl_11[] = {
    gsSPDisplayList(flame_seg6_dl_bowser_flame_start),
    gsDPLoadTextureBlock(flame_seg6_texture_bowser_flame_11, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(flame_seg6_vertex_bowser_flame, 8, 0),
    gsSPDisplayList(flame_seg6_sub_dl_bowser_flame_upper),
    gsDPLoadTextureBlock((u8*)flame_seg6_texture_bowser_flame_11 + 0x1000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPDisplayList(flame_seg6_sub_dl_bowser_flame_lower),
    gsSPDisplayList(flame_seg6_dl_bowser_flame_end),
    gsSPEndDisplayList(),
};

// 0x0601C888 - 0x0601C928
const Gfx flame_seg6_dl_12[] = {
    gsSPDisplayList(flame_seg6_dl_bowser_flame_start),
    gsDPLoadTextureBlock(flame_seg6_texture_bowser_flame_12, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(flame_seg6_vertex_bowser_flame, 8, 0),
    gsSPDisplayList(flame_seg6_sub_dl_bowser_flame_upper),
    gsDPLoadTextureBlock((u8*)flame_seg6_texture_bowser_flame_12 + 0x1000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPDisplayList(flame_seg6_sub_dl_bowser_flame_lower),
    gsSPDisplayList(flame_seg6_dl_bowser_flame_end),
    gsSPEndDisplayList(),
};

// 0x0601C928 - 0x0601C9C8
const Gfx flame_seg6_dl_13[] = {
    gsSPDisplayList(flame_seg6_dl_bowser_flame_start),
    gsDPLoadTextureBlock(flame_seg6_texture_bowser_flame_13, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(flame_seg6_vertex_bowser_flame, 8, 0),
    gsSPDisplayList(flame_seg6_sub_dl_bowser_flame_upper),
    gsDPLoadTextureBlock((u8*)flame_seg6_texture_bowser_flame_13 + 0x1000, G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPDisplayList(flame_seg6_sub_dl_bowser_flame_lower),
    gsSPDisplayList(flame_seg6_dl_bowser_flame_end),
    gsSPEndDisplayList(),
};
