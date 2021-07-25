// Impact Smoke

// TODO: These 64x64 textures are referenced as two different texture addresses in the DLs

// 0x0605AA28
ALIGNED8 static const u8 impact_smoke_seg6_texture_0[] = {
#include "actors/impact_smoke/impact_smoke_0.ia16.inc.c"
};

// 0x0605CA28
ALIGNED8 static const u8 impact_smoke_seg6_texture_1[] = {
#include "actors/impact_smoke/impact_smoke_1.ia16.inc.c"
};

// 0x0605EA28
ALIGNED8 static const u8 impact_smoke_seg6_texture_2[] = {
#include "actors/impact_smoke/impact_smoke_2.ia16.inc.c"
};

// 0x06060A28
ALIGNED8 static const u8 impact_smoke_seg6_texture_3[] = {
#include "actors/impact_smoke/impact_smoke_3.ia16.inc.c"
};

// 0x06062A28
static const Vtx impact_smoke_seg6_vertex_06062A28[] = {
    {{{  -150,    150,      0}, 0, {     0,  31<<5}, {0x28, 0x19, 0x14, 0xff}}},
    {{{   150,    150,      0}, 0, { 63<<5,  31<<5}, {0x28, 0x19, 0x14, 0xff}}},
    {{{   150,    300,      0}, 0, { 63<<5,      0}, {0x28, 0x19, 0x14, 0xff}}},
    {{{  -150,    300,      0}, 0, {     0,      0}, {0x28, 0x19, 0x14, 0xff}}},
    {{{  -150,      0,      0}, 0, {     0,  31<<5}, {0x28, 0x19, 0x14, 0xff}}},
    {{{   150,      0,      0}, 0, { 63<<5,  31<<5}, {0x28, 0x19, 0x14, 0xff}}},
    {{{   150,    150,      0}, 0, { 63<<5,      0}, {0x28, 0x19, 0x14, 0xff}}},
    {{{  -150,    150,      0}, 0, {     0,      0}, {0x28, 0x19, 0x14, 0xff}}},
};

// 0x06062AA8 - 0x06062AD8
const Gfx impact_smoke_seg6_dl_start[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATEFADE, G_CC_MODULATEFADE),
    gsSPGeometryMode(G_LIGHTING, G_SHADING_SMOOTH),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

// 0x06062AD8 - 0x06062AF0
const Gfx impact_smoke_seg6_sub_dl_upper[] = {
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x06062AF0 - 0x06062B08
const Gfx impact_smoke_seg6_sub_dl_lower[] = {
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x06062B08 - 0x06062B38
const Gfx impact_smoke_seg6_dl_end[] = {
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x06062B38 - 0x06062BD8
const Gfx impact_smoke_seg6_dl_0[] = {
    gsSPDisplayList(impact_smoke_seg6_dl_start),
    gsDPLoadTextureBlock(impact_smoke_seg6_texture_0, G_IM_FMT_IA, G_IM_SIZ_16b, 64, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(impact_smoke_seg6_vertex_06062A28, 8, 0),
    gsSPDisplayList(impact_smoke_seg6_sub_dl_upper),
    gsDPLoadTextureBlock((u8*)impact_smoke_seg6_texture_0 + 0x1000, G_IM_FMT_IA, G_IM_SIZ_16b, 64, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPDisplayList(impact_smoke_seg6_sub_dl_lower),
    gsSPDisplayList(impact_smoke_seg6_dl_end),
    gsSPEndDisplayList(),
};

// 0x06062BD8 - 0x06062C78
const Gfx impact_smoke_seg6_dl_1[] = {
    gsSPDisplayList(impact_smoke_seg6_dl_start),
    gsDPLoadTextureBlock(impact_smoke_seg6_texture_1, G_IM_FMT_IA, G_IM_SIZ_16b, 64, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(impact_smoke_seg6_vertex_06062A28, 8, 0),
    gsSPDisplayList(impact_smoke_seg6_sub_dl_upper),
    gsDPLoadTextureBlock((u8*)impact_smoke_seg6_texture_1 + 0x1000, G_IM_FMT_IA, G_IM_SIZ_16b, 64, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPDisplayList(impact_smoke_seg6_sub_dl_lower),
    gsSPDisplayList(impact_smoke_seg6_dl_end),
    gsSPEndDisplayList(),
};

// 0x06062C78 - 0x06062D18
const Gfx impact_smoke_seg6_dl_2[] = {
    gsSPDisplayList(impact_smoke_seg6_dl_start),
    gsDPLoadTextureBlock(impact_smoke_seg6_texture_2, G_IM_FMT_IA, G_IM_SIZ_16b, 64, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(impact_smoke_seg6_vertex_06062A28, 8, 0),
    gsSPDisplayList(impact_smoke_seg6_sub_dl_upper),
    gsDPLoadTextureBlock((u8*)impact_smoke_seg6_texture_2 + 0x1000, G_IM_FMT_IA, G_IM_SIZ_16b, 64, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPDisplayList(impact_smoke_seg6_sub_dl_lower),
    gsSPDisplayList(impact_smoke_seg6_dl_end),
    gsSPEndDisplayList(),
};

// 0x06062D18 - 0x06062DB8
const Gfx impact_smoke_seg6_dl_3[] = {
    gsSPDisplayList(impact_smoke_seg6_dl_start),
    gsDPLoadTextureBlock(impact_smoke_seg6_texture_3, G_IM_FMT_IA, G_IM_SIZ_16b, 64, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(impact_smoke_seg6_vertex_06062A28, 8, 0),
    gsSPDisplayList(impact_smoke_seg6_sub_dl_upper),
    gsDPLoadTextureBlock((u8*)impact_smoke_seg6_texture_3 + 0x1000, G_IM_FMT_IA, G_IM_SIZ_16b, 64, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPDisplayList(impact_smoke_seg6_sub_dl_lower),
    gsSPDisplayList(impact_smoke_seg6_dl_end),
    gsSPEndDisplayList(),
};
