// Flame

// 0x030172E0
static const Vtx flame_seg3_vertex_50x50_billboard[] = {
    {{{   -25,    -25,      0}, 0, ST_B(     0,     32), {0x00, 0x00, 0x00, 0x00}}},
    {{{    25,    -25,      0}, 0, ST_B(    32,     32), {0x00, 0x00, 0x00, 0x00}}},
    {{{    25,     25,      0}, 0, ST_B(    32,      0), {0x00, 0x00, 0x00, 0x00}}},
    {{{   -25,     25,      0}, 0, ST_B(     0,      0), {0x00, 0x00, 0x00, 0x00}}},
};

// 0x03017320
ALIGNED8 static const Texture flame_seg3_texture_0[] = {
#include "actors/flame/flame_0.ia16.inc.c"
};

// 0x03017B20
ALIGNED8 static const Texture flame_seg3_texture_1[] = {
#include "actors/flame/flame_1.ia16.inc.c"
};

// 0x03018320
ALIGNED8 static const Texture flame_seg3_texture_2[] = {
#include "actors/flame/flame_2.ia16.inc.c"
};

// 0x03018B20
ALIGNED8 static const Texture flame_seg3_texture_3[] = {
#include "actors/flame/flame_3.ia16.inc.c"
};

// 0x03019320
ALIGNED8 static const Texture flame_seg3_texture_4[] = {
#include "actors/flame/flame_4.ia16.inc.c"
};

// 0x03019B20
ALIGNED8 static const Texture flame_seg3_texture_5[] = {
#include "actors/flame/flame_5.ia16.inc.c"
};

// 0x0301A320
ALIGNED8 static const Texture flame_seg3_texture_6[] = {
#include "actors/flame/flame_6.ia16.inc.c"
};

// 0x0301AB20
ALIGNED8 static const Texture flame_seg3_texture_7[] = {
#include "actors/flame/flame_7.ia16.inc.c"
};

// 0x0301B320 - 0x0301B3B0
const Gfx flame_seg3_dl_red_flame[] = {
    gsSPClearGeometryMode(G_LIGHTING | G_SHADING_SMOOTH),
    gsDPSetEnvColor(255, 50, 0, 200),
    gsDPSetCombineMode(G_CC_FADEA, G_CC_FADEA),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, ((32 - 1) << G_TEXTURE_IMAGE_FRAC), ((32 - 1) << G_TEXTURE_IMAGE_FRAC)),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPVertex(flame_seg3_vertex_50x50_billboard, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_LIGHTING | G_SHADING_SMOOTH),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x0301B3B0 - 0x0301B3C8
const Gfx flame_seg3_dl_red_0[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, flame_seg3_texture_0),
    gsSPBranchList(flame_seg3_dl_red_flame),
};

// 0x0301B3C8 - 0x0301B3E0
const Gfx flame_seg3_dl_red_1[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, flame_seg3_texture_1),
    gsSPBranchList(flame_seg3_dl_red_flame),
};

// 0x0301B3E0 - 0x0301B3F8
const Gfx flame_seg3_dl_red_2[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, flame_seg3_texture_2),
    gsSPBranchList(flame_seg3_dl_red_flame),
};

// 0x0301B3F8 - 0x0301B410
const Gfx flame_seg3_dl_red_3[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, flame_seg3_texture_3),
    gsSPBranchList(flame_seg3_dl_red_flame),
};

// 0x0301B410 - 0x0301B428
const Gfx flame_seg3_dl_red_4[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, flame_seg3_texture_4),
    gsSPBranchList(flame_seg3_dl_red_flame),
};

// 0x0301B428 - 0x0301B440
const Gfx flame_seg3_dl_red_5[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, flame_seg3_texture_5),
    gsSPBranchList(flame_seg3_dl_red_flame),
};

// 0x0301B440 - 0x0301B458
const Gfx flame_seg3_dl_red_6[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, flame_seg3_texture_6),
    gsSPBranchList(flame_seg3_dl_red_flame),
};

// 0x0301B458 - 0x0301B470
const Gfx flame_seg3_dl_red_7[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, flame_seg3_texture_7),
    gsSPBranchList(flame_seg3_dl_red_flame),
};

// 0x0301B470 - 0x0301B500
const Gfx flame_seg3_dl_blue_flame[] = {
    gsSPClearGeometryMode(G_LIGHTING | G_SHADING_SMOOTH),
    gsDPSetEnvColor(100, 100, 255, 255),
    gsDPSetCombineMode(G_CC_FADEA, G_CC_FADEA),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, ((32 - 1) << G_TEXTURE_IMAGE_FRAC), ((32 - 1) << G_TEXTURE_IMAGE_FRAC)),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPVertex(flame_seg3_vertex_50x50_billboard, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_LIGHTING | G_SHADING_SMOOTH),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x0301B500 - 0x0301B518
const Gfx flame_seg3_dl_blue_0[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, flame_seg3_texture_0),
    gsSPBranchList(flame_seg3_dl_blue_flame),
};

// 0x0301B518 - 0x0301B530
const Gfx flame_seg3_dl_blue_1[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, flame_seg3_texture_1),
    gsSPBranchList(flame_seg3_dl_blue_flame),
};

// 0x0301B530 - 0x0301B548
const Gfx flame_seg3_dl_blue_2[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, flame_seg3_texture_2),
    gsSPBranchList(flame_seg3_dl_blue_flame),
};

// 0x0301B548 - 0x0301B560
const Gfx flame_seg3_dl_blue_3[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, flame_seg3_texture_3),
    gsSPBranchList(flame_seg3_dl_blue_flame),
};

// 0x0301B560 - 0x0301B578
const Gfx flame_seg3_dl_blue_4[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, flame_seg3_texture_4),
    gsSPBranchList(flame_seg3_dl_blue_flame),
};

// 0x0301B578 - 0x0301B590
const Gfx flame_seg3_dl_blue_5[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, flame_seg3_texture_5),
    gsSPBranchList(flame_seg3_dl_blue_flame),
};

// 0x0301B590 - 0x0301B5A8
const Gfx flame_seg3_dl_blue_6[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, flame_seg3_texture_6),
    gsSPBranchList(flame_seg3_dl_blue_flame),
};

// 0x0301B5A8 - 0x0301B5C0
const Gfx flame_seg3_dl_blue_7[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, flame_seg3_texture_7),
    gsSPBranchList(flame_seg3_dl_blue_flame),
};
#if FLAME_GLOW
// 0x0302C288 - 0x0302C2C8
const Vtx flame_seg3_vertex_glow[] = {
    {{{ -FLAME_GLOW, -FLAME_GLOW,      0}, 0, ST_B(     0,     64), {0x00, 0x00, 0x00, 0x00}}},
    {{{  FLAME_GLOW, -FLAME_GLOW,      0}, 0, ST_B(    64,     64), {0x00, 0x00, 0x00, 0x00}}},
    {{{  FLAME_GLOW,  FLAME_GLOW,      0}, 0, ST_B(    64,      0), {0x00, 0x00, 0x00, 0x00}}},
    {{{ -FLAME_GLOW,  FLAME_GLOW,      0}, 0, ST_B(     0,      0), {0x00, 0x00, 0x00, 0x00}}},
};

// 0x0302C2C8 - 0x0302C300
const Gfx flame_seg3_sub_dl_glow[] = {
    gsDPSetCombineMode(G_CC_FADEA, G_CC_FADEA),
    gsSPClearGeometryMode(G_LIGHTING | G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, (G_TX_WRAP | G_TX_MIRROR), 5, G_TX_NOLOD, (G_TX_WRAP | G_TX_MIRROR), 5, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, (G_TX_WRAP | G_TX_MIRROR), 5, G_TX_NOLOD, (G_TX_WRAP | G_TX_MIRROR), 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, ((32 - 1) << G_TEXTURE_IMAGE_FRAC), ((32 - 1) << G_TEXTURE_IMAGE_FRAC)),
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, seg3_texture_radial_light),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(flame_seg3_vertex_glow, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsDPTileSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

// 0x0302C300 - 0x0302C
const Gfx flame_seg3_dl_red_glow[] = {
    gsDPPipeSync(),
    gsDPSetEnvColor(255, 50, 0, 200),
    gsSPDisplayList(flame_seg3_sub_dl_glow),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsSPEndDisplayList(),
};

// 0x0302C300 - 0x0302C
const Gfx flame_seg3_dl_blue_glow[] = {
    gsDPPipeSync(),
    gsDPSetEnvColor(100, 100, 255, 255),
    gsSPDisplayList(flame_seg3_sub_dl_glow),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsSPEndDisplayList(),
};
#endif
