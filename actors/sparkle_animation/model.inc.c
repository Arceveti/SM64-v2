// Sparkles Animation

// 0x04032A48
static const Vtx sparkles_animation_seg4_vertex_64x64_raised[] = {
    {{{   -32,      0,      0}, 0, ST_B(     0,     32), {0xff, 0xff, 0x64, 0xff}}},
    {{{    32,      0,      0}, 0, ST_B(    32,     32), {0xff, 0xff, 0x64, 0xff}}},
    {{{    32,     64,      0}, 0, ST_B(    32,      0), {0xff, 0xff, 0x64, 0xff}}},
    {{{   -32,     64,      0}, 0, ST_B(     0,      0), {0xff, 0xff, 0x64, 0xff}}},
};

// 0x04032A88
ALIGNED8 static const Texture sparkles_animation_seg4_texture_0[] = {
#include "actors/sparkle_animation/sparkle_animation_0.ia16.inc.c"
};

// 0x04033288
ALIGNED8 static const Texture sparkles_animation_seg4_texture_1[] = {
#include "actors/sparkle_animation/sparkle_animation_1.ia16.inc.c"
};

// 0x04033A88
ALIGNED8 static const Texture sparkles_animation_seg4_texture_2[] = {
#include "actors/sparkle_animation/sparkle_animation_2.ia16.inc.c"
};

// 0x04034288
ALIGNED8 static const Texture sparkles_animation_seg4_texture_3[] = {
#include "actors/sparkle_animation/sparkle_animation_3.ia16.inc.c"
};

// 0x04034A88
ALIGNED8 static const Texture sparkles_animation_seg4_texture_4[] = {
#include "actors/sparkle_animation/sparkle_animation_4.ia16.inc.c"
};

// 0x04035288 - 0x04035300
const Gfx sparkles_animation_seg4_sub_dl_material_model[] = {
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPVertex(sparkles_animation_seg4_vertex_64x64_raised, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsSPSetGeometryMode(G_LIGHTING),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x04035300 - 0x04035318
const Gfx sparkles_animation_seg4_dl_0[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, sparkles_animation_seg4_texture_0),
    gsSPBranchList(sparkles_animation_seg4_sub_dl_material_model),
};

// 0x04035318 - 0x04035330
const Gfx sparkles_animation_seg4_dl_1[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, sparkles_animation_seg4_texture_1),
    gsSPBranchList(sparkles_animation_seg4_sub_dl_material_model),
};

// 0x04035330 - 0x04035348
const Gfx sparkles_animation_seg4_dl_2[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, sparkles_animation_seg4_texture_2),
    gsSPBranchList(sparkles_animation_seg4_sub_dl_material_model),
};

// 0x04035348 - 0x04035360
const Gfx sparkles_animation_seg4_dl_3[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, sparkles_animation_seg4_texture_3),
    gsSPBranchList(sparkles_animation_seg4_sub_dl_material_model),
};

// 0x04035360 - 0x04035378
const Gfx sparkles_animation_seg4_dl_4[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, sparkles_animation_seg4_texture_4),
    gsSPBranchList(sparkles_animation_seg4_sub_dl_material_model),
};
