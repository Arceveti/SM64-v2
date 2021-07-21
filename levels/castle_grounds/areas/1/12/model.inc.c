// Peach Letter

// 0x0700C968 - 0x0700C9A8
static const Vtx castle_grounds_seg7_vertex_peach_letter_left_side[] = {
    {{{     0,     82,      0}, 0, { 31<<5,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   -72,    -82,      0}, 0, {     0,  63<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,    -82,      0}, 0, { 31<<5,  63<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   -72,     82,      0}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}},
};

// 0x0700C9A8 - 0x0700C9E8
static const Vtx castle_grounds_seg7_vertex_peach_letter_right_side[] = {
    {{{    72,     82,      0}, 0, { 31<<5,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,    -82,      0}, 0, {     0,  63<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{    72,    -82,      0}, 0, { 31<<5,  63<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,     82,      0}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}},
};

// 0x0700C9E8 - 0x0700D9E8
ALIGNED8 static const Texture castle_grounds_seg7_texture_peach_letter_left_side[] = {
#include "levels/castle_grounds/3.rgba16.inc.c"
};

// 0x0700D9E8 - 0x0700E9E8
ALIGNED8 static const Texture castle_grounds_seg7_texture_peach_letter_right_side[] = {
#include "levels/castle_grounds/4.rgba16.inc.c"
};

// 0x0700E9E8 - 0x0700EA20
static const Gfx castle_grounds_seg7_dl_peach_letter_left_side[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, castle_grounds_seg7_texture_peach_letter_left_side),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(castle_grounds_seg7_vertex_peach_letter_left_side, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700EA20 - 0x0700EA58
static const Gfx castle_grounds_seg7_dl_peach_letter_right_side[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, castle_grounds_seg7_texture_peach_letter_right_side),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(castle_grounds_seg7_vertex_peach_letter_right_side, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700EA58 - 0x0700EAE8
const Gfx castle_grounds_seg7_dl_peach_letter[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALFADEA, G_CC_DECALFADEA),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(castle_grounds_seg7_dl_peach_letter_left_side),
    gsSPDisplayList(castle_grounds_seg7_dl_peach_letter_right_side),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
