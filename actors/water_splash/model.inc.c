// Water Splash

// 0x0402A588
static const Vtx water_splash_seg4_vertex_0402A588[] = {
    {{{   -64,      0,      0}, 0, ST_B(     0,     64), {0xff, 0xff, 0xff, 0xff}}},
    {{{    64,      0,      0}, 0, ST_B(    32,     64), {0xff, 0xff, 0xff, 0xff}}},
    {{{    64,    256,      0}, 0, ST_B(    32,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{   -64,    256,      0}, 0, ST_B(     0,      0), {0xff, 0xff, 0xff, 0xff}}},
};

// 0x0402A5C8
ALIGNED8 static const Texture water_splash_seg4_texture_0[] = {
#include "actors/water_splash/water_splash_0.rgba16.inc.c"
};

// 0x0402B5C8
ALIGNED8 static const Texture water_splash_seg4_texture_1[] = {
#include "actors/water_splash/water_splash_1.rgba16.inc.c"
};

// 0x0402C5C8
ALIGNED8 static const Texture water_splash_seg4_texture_2[] = {
#include "actors/water_splash/water_splash_2.rgba16.inc.c"
};

// 0x0402D5C8
ALIGNED8 static const Texture water_splash_seg4_texture_3[] = {
#include "actors/water_splash/water_splash_3.rgba16.inc.c"
};

// 0x0402E5C8
ALIGNED8 static const Texture water_splash_seg4_texture_4[] = {
#include "actors/water_splash/water_splash_4.rgba16.inc.c"
};

// 0x0402F5C8
ALIGNED8 static const Texture water_splash_seg4_texture_5[] = {
#include "actors/water_splash/water_splash_5.rgba16.inc.c"
};

// 0x040305C8
ALIGNED8 static const Texture water_splash_seg4_texture_6[] = {
#include "actors/water_splash/water_splash_6.rgba16.inc.c"
};

// 0x040315C8
ALIGNED8 static const Texture water_splash_seg4_texture_7[] = {
#include "actors/water_splash/water_splash_7.rgba16.inc.c"
};

// 0x040325C8 - 0x04032640
const Gfx water_splash_seg4_sub_dl_material_model[] = {
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPVertex(water_splash_seg4_vertex_0402A588, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x04032640 - 0x04032658
const Gfx water_splash_seg4_dl_0[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_splash_seg4_texture_0),
    gsSPBranchList(water_splash_seg4_sub_dl_material_model),
};

// 0x04032658 - 0x04032670
const Gfx water_splash_seg4_dl_1[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_splash_seg4_texture_1),
    gsSPBranchList(water_splash_seg4_sub_dl_material_model),
};

// 0x04032670 - 0x04032688
const Gfx water_splash_seg4_dl_2[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_splash_seg4_texture_2),
    gsSPBranchList(water_splash_seg4_sub_dl_material_model),
};

// 0x04032688 - 0x040326A0
const Gfx water_splash_seg4_dl_3[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_splash_seg4_texture_3),
    gsSPBranchList(water_splash_seg4_sub_dl_material_model),
};

// 0x040326A0 - 0x040326B8
const Gfx water_splash_seg4_dl_4[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_splash_seg4_texture_4),
    gsSPBranchList(water_splash_seg4_sub_dl_material_model),
};

// 0x040326B8 - 0x040326D0
const Gfx water_splash_seg4_dl_5[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_splash_seg4_texture_5),
    gsSPBranchList(water_splash_seg4_sub_dl_material_model),
};

// 0x040326D0 - 0x040326E8
const Gfx water_splash_seg4_dl_6[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_splash_seg4_texture_6),
    gsSPBranchList(water_splash_seg4_sub_dl_material_model),
};

// 0x040326E8 - 0x04032700
const Gfx water_splash_seg4_dl_7[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_splash_seg4_texture_7),
    gsSPBranchList(water_splash_seg4_sub_dl_material_model),
};
