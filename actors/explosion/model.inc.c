// Explosion

// 0x030009C8
static const Vtx explosion_seg3_vertex_030009C8[] = {
    {{{  -128,   -128,      0}, 0, ST_B(     0,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{   128,   -128,      0}, 0, ST_B(    32,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{   128,    128,      0}, 0, ST_B(    32,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{  -128,    128,      0}, 0, ST_B(     0,      0), {0xff, 0xff, 0xff, 0xff}}},
};

// 0x03000A08
ALIGNED8 static const Texture explosion_seg3_texture_0[] = {
#include "actors/explosion/explosion_0.rgba16.inc.c"
};

// 0x03001208
ALIGNED8 static const Texture explosion_seg3_texture_1[] = {
#include "actors/explosion/explosion_1.rgba16.inc.c"
};

// 0x03001A08
ALIGNED8 static const Texture explosion_seg3_texture_2[] = {
#include "actors/explosion/explosion_2.rgba16.inc.c"
};

// 0x03002208
ALIGNED8 static const Texture explosion_seg3_texture_3[] = {
#include "actors/explosion/explosion_3.rgba16.inc.c"
};

// 0x03002A08
ALIGNED8 static const Texture explosion_seg3_texture_4[] = {
#include "actors/explosion/explosion_4.rgba16.inc.c"
};

// 0x03003208
ALIGNED8 static const Texture explosion_seg3_texture_5[] = {
#include "actors/explosion/explosion_5.rgba16.inc.c"
};

// 0x03003A08
ALIGNED8 static const Texture explosion_seg3_texture_6[] = {
#include "actors/explosion/explosion_6.rgba16.inc.c"
};

// 0x03004208 - 0x03004298
const Gfx explosion_seg3_sub_dl_material_model[] = {
    gsDPSetCombineMode(G_CC_DECALFADEA, G_CC_DECALFADEA),
    gsDPSetEnvColor(255, 255, 255, 150),
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPVertex(explosion_seg3_vertex_030009C8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_LIGHTING),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x03004298 - 0x030042B0
const Gfx explosion_seg3_dl_0[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, explosion_seg3_texture_0),
    gsSPBranchList(explosion_seg3_sub_dl_material_model),
};

// 0x030042B0 - 0x030042C8
const Gfx explosion_seg3_dl_1[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, explosion_seg3_texture_1),
    gsSPBranchList(explosion_seg3_sub_dl_material_model),
};

// 0x030042C8 - 0x030042E0
const Gfx explosion_seg3_dl_2[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, explosion_seg3_texture_2),
    gsSPBranchList(explosion_seg3_sub_dl_material_model),
};

// 0x030042E0 - 0x030042F8
const Gfx explosion_seg3_dl_3[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, explosion_seg3_texture_3),
    gsSPBranchList(explosion_seg3_sub_dl_material_model),
};

// 0x030042F8 - 0x03004310
const Gfx explosion_seg3_dl_4[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, explosion_seg3_texture_4),
    gsSPBranchList(explosion_seg3_sub_dl_material_model),
};

// 0x03004310 - 0x03004328
const Gfx explosion_seg3_dl_5[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, explosion_seg3_texture_5),
    gsSPBranchList(explosion_seg3_sub_dl_material_model),
};

// 0x03004328 - 0x03004340
const Gfx explosion_seg3_dl_6[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, explosion_seg3_texture_6),
    gsSPBranchList(explosion_seg3_sub_dl_material_model),
};
