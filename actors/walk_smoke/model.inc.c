// Walk Smoke

// 0x0401DE60
static const Vtx smoke_seg4_vertex_64x64_raised[] = {
    {{{   -32,      0,      0}, 0, {     0,  31<<5}, {0xff, 0xff, 0xff, 0x64}}},
    {{{    32,      0,      0}, 0, { 31<<5,  31<<5}, {0xff, 0xff, 0xff, 0x64}}},
    {{{    32,     64,      0}, 0, { 31<<5,      0}, {0xff, 0xff, 0xff, 0x64}}},
    {{{   -32,     64,      0}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0x64}}},
};

// 0x0401DEA0
ALIGNED8 static const Texture smoke_seg4_texture_walk_smoke_0[] = {
#include "actors/walk_smoke/walk_smoke_0.ia16.inc.c"
};

// 0x0401E6A0
ALIGNED8 static const Texture smoke_seg4_texture_walk_smoke_1[] = {
#include "actors/walk_smoke/walk_smoke_1.ia16.inc.c"
};

// 0x0401EEA0
ALIGNED8 static const Texture smoke_seg4_texture_walk_smoke_2[] = {
#include "actors/walk_smoke/walk_smoke_2.ia16.inc.c"
};

// 0x0401F6A0
ALIGNED8 static const Texture smoke_seg4_texture_walk_smoke_3[] = {
#include "actors/walk_smoke/walk_smoke_3.ia16.inc.c"
};

// 0x0401FEA0
ALIGNED8 static const Texture smoke_seg4_texture_walk_smoke_4[] = {
#include "actors/walk_smoke/walk_smoke_4.ia16.inc.c"
};

// 0x040206A0
ALIGNED8 static const Texture smoke_seg4_texture_walk_smoke_5[] = {
#include "actors/walk_smoke/walk_smoke_5.ia16.inc.c"
};

// 0x04020EA0
ALIGNED8 static const Texture smoke_seg4_texture_walk_smoke_6[] = {
#include "actors/walk_smoke/walk_smoke_6.ia16.inc.c"
};

// 0x040216A0 - 0x04021718
const Gfx smoke_seg4_sub_dl_material_model[] = {
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPVertex(smoke_seg4_vertex_64x64_raised, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x04021718 - 0x04021730
const Gfx smoke_seg4_dl_walk_smoke_0[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, smoke_seg4_texture_walk_smoke_0),
    gsSPBranchList(smoke_seg4_sub_dl_material_model),
};

// 0x04021730 - 0x04021748
const Gfx smoke_seg4_dl_walk_smoke_1[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, smoke_seg4_texture_walk_smoke_1),
    gsSPBranchList(smoke_seg4_sub_dl_material_model),
};

// 0x04021748 - 0x04021760
const Gfx smoke_seg4_dl_walk_smoke_2[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, smoke_seg4_texture_walk_smoke_2),
    gsSPBranchList(smoke_seg4_sub_dl_material_model),
};

// 0x04021760 - 0x04021778
const Gfx smoke_seg4_dl_walk_smoke_3[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, smoke_seg4_texture_walk_smoke_3),
    gsSPBranchList(smoke_seg4_sub_dl_material_model),
};

// 0x04021778 - 0x04021790
const Gfx smoke_seg4_dl_walk_smoke_4[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, smoke_seg4_texture_walk_smoke_4),
    gsSPBranchList(smoke_seg4_sub_dl_material_model),
};

// 0x04021790 - 0x040217A8
const Gfx smoke_seg4_dl_walk_smoke_5[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, smoke_seg4_texture_walk_smoke_5),
    gsSPBranchList(smoke_seg4_sub_dl_material_model),
};

// 0x040217A8 - 0x040217C0
const Gfx smoke_seg4_dl_walk_smoke_6[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, smoke_seg4_texture_walk_smoke_6),
    gsSPBranchList(smoke_seg4_sub_dl_material_model),
};
