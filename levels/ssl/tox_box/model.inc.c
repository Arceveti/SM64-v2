// 0x0700BF90 - 0x0700BFA8
static const Lights1 ssl_seg7_lights_0700BF90 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0700BFA8 - 0x0700C7A8
ALIGNED8 static const Texture ssl_seg7_texture_tox_box_inside[] = {
#include "levels/ssl/8.rgba16.inc.c"
};

// 0x0700C7A8 - 0x0700D7A8
ALIGNED8 static const Texture ssl_seg7_texture_tox_box_smile[] = {
#include "levels/ssl/9.rgba16.inc.c"
};

// 0x0700D7A8 - 0x0700E7A8
ALIGNED8 static const Texture ssl_seg7_texture_tox_box_top[] = {
#include "levels/ssl/10.rgba16.inc.c"
};

// 0x0700E7A8 - 0x0700F7A8
ALIGNED8 static const Texture ssl_seg7_texture_tox_box_frown[] = {
#include "levels/ssl/11.rgba16.inc.c"
};

// 0x0700F7A8 - 0x0700F898
static const Vtx ssl_seg7_vertex_tox_box_inside[] = {
    {{{  -154,   -256,   -154}, 0, ST_B(     0,     32), {0x00, 0x00, 0x7f, 0xff}}},
    {{{   154,   -256,   -154}, 0, ST_B(    32,     32), {0x00, 0x00, 0x7f, 0xff}}},
    {{{   154,    154,   -154}, 0, ST_B(    32,      0), {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -154,    154,    154}, 0, ST_B(     0,      0), {0x00, 0x81, 0x00, 0xff}}},
    {{{  -154,    154,   -154}, 0, ST_B(     0,     32), {0x00, 0x81, 0x00, 0xff}}},
    {{{   154,    154,   -154}, 0, ST_B(    32,     32), {0x00, 0x81, 0x00, 0xff}}},
    {{{   154,    154,    154}, 0, ST_B(    32,      0), {0x00, 0x81, 0x00, 0xff}}},
    {{{  -154,    154,    154}, 0, ST_B(     0,      0), {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -154,   -256,    154}, 0, ST_B(     0,     32), {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -154,   -256,   -154}, 0, ST_B(    32,     32), {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -154,    154,   -154}, 0, ST_B(    32,      0), {0x7f, 0x00, 0x00, 0xff}}},
    {{{   154,    154,   -154}, 0, ST_B(     0,      0), {0x81, 0x00, 0x00, 0xff}}},
    {{{   154,   -256,    154}, 0, ST_B(    32,     32), {0x81, 0x00, 0x00, 0xff}}},
    {{{   154,    154,    154}, 0, ST_B(    32,      0), {0x81, 0x00, 0x00, 0xff}}},
    {{{   154,   -256,   -154}, 0, ST_B(     0,     32), {0x81, 0x00, 0x00, 0xff}}},
    {{{   154,   -256,    154}, 0, ST_B(     0,     32), {0x00, 0x00, 0x81, 0xff}}},
    {{{  -154,    154,    154}, 0, ST_B(    32,      0), {0x00, 0x00, 0x81, 0xff}}},
    {{{   154,    154,    154}, 0, ST_B(     0,      0), {0x00, 0x00, 0x81, 0xff}}},
    {{{  -154,   -256,   -154}, 0, ST_B(     0,     32), {0x00, 0x00, 0x7f, 0xff}}},
    {{{   154,    154,   -154}, 0, ST_B(    32,      0), {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -154,    154,   -154}, 0, ST_B(     0,      0), {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -154,   -256,    154}, 0, ST_B(    32,     32), {0x00, 0x00, 0x81, 0xff}}},
};

// 0x0700F908 - 0x0700FA08
static const Vtx ssl_seg7_vertex_tox_box_smile[] = {
    {{{   256,   -256,   -256}, 0, ST_B(    32,     64), {0x7f, 0x00, 0x00, 0xff}}},
    {{{   256,    256,   -256}, 0, ST_B(    32,      0), {0x7f, 0x00, 0x00, 0xff}}},
    {{{   256,    256,    256}, 0, ST_B(     0,      0), {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -256,   -256,    256}, 0, ST_B(    32,     64), {0x81, 0x00, 0x00, 0xff}}},
    {{{  -256,    256,   -256}, 0, ST_B(     0,      0), {0x81, 0x00, 0x00, 0xff}}},
    {{{  -256,   -256,   -256}, 0, ST_B(     0,     64), {0x81, 0x00, 0x00, 0xff}}},
    {{{  -256,    256,    256}, 0, ST_B(    32,      0), {0x81, 0x00, 0x00, 0xff}}},
    {{{   154,   -256,    154}, 0, ST_B(     6,     64), {0x00, 0x81, 0x00, 0xff}}},
    {{{   154,   -256,   -154}, 0, ST_B(    25,     64), {0x00, 0x81, 0x00, 0xff}}},
    {{{   256,   -256,   -256}, 0, ST_B(    32,     64), {0x00, 0x81, 0x00, 0xff}}},
    {{{   256,   -256,    256}, 0, ST_B(     0,     64), {0x7f, 0x00, 0x00, 0xff}}},
    {{{   256,   -256,    256}, 0, ST_B(     0,     64), {0x00, 0x81, 0x00, 0xff}}},
    {{{  -256,   -256,   -256}, 0, ST_B(     0,     64), {0x00, 0x81, 0x00, 0xff}}},
    {{{  -154,   -256,    154}, 0, ST_B(    25,     64), {0x00, 0x81, 0x00, 0xff}}},
    {{{  -256,   -256,    256}, 0, ST_B(    32,     64), {0x00, 0x81, 0x00, 0xff}}},
    {{{  -154,   -256,   -154}, 0, ST_B(     6,     64), {0x00, 0x81, 0x00, 0xff}}},
};

// 0x0700FA08 - 0x0700FB08
static const Vtx ssl_seg7_vertex_tox_box_frown[] = {
    {{{  -256,   -256,   -256}, 0, ST_B(    32,     64), {0x00, 0x00, 0x81, 0xff}}},
    {{{  -256,    256,   -256}, 0, ST_B(    32,      0), {0x00, 0x00, 0x81, 0xff}}},
    {{{   256,    256,   -256}, 0, ST_B(     0,      0), {0x00, 0x00, 0x81, 0xff}}},
    {{{   256,   -256,   -256}, 0, ST_B(     0,     64), {0x00, 0x00, 0x81, 0xff}}},
    {{{  -256,   -256,   -256}, 0, ST_B(    32,     64), {0x00, 0x81, 0x00, 0xff}}},
    {{{   256,   -256,   -256}, 0, ST_B(     0,     64), {0x00, 0x81, 0x00, 0xff}}},
    {{{   154,   -256,   -154}, 0, ST_B(     6,     64), {0x00, 0x81, 0x00, 0xff}}},
    {{{  -154,   -256,   -154}, 0, ST_B(    25,     64), {0x00, 0x81, 0x00, 0xff}}},
    {{{   256,   -256,    256}, 0, ST_B(    32,     64), {0x00, 0x00, 0x7f, 0xff}}},
    {{{   256,    256,    256}, 0, ST_B(    32,      0), {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -256,    256,    256}, 0, ST_B(     0,      0), {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -256,   -256,    256}, 0, ST_B(     0,     64), {0x00, 0x81, 0x00, 0xff}}},
    {{{   154,   -256,    154}, 0, ST_B(    25,     64), {0x00, 0x81, 0x00, 0xff}}},
    {{{   256,   -256,    256}, 0, ST_B(    32,     64), {0x00, 0x81, 0x00, 0xff}}},
    {{{  -256,   -256,    256}, 0, ST_B(     0,     64), {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -154,   -256,    154}, 0, ST_B(     6,     64), {0x00, 0x81, 0x00, 0xff}}},
};

// 0x0700FB08 - 0x0700FB48
static const Vtx ssl_seg7_vertex_tox_box_top[] = {
    {{{  -256,    256,    256}, 0, ST_B(     0,     64), {0x00, 0x7f, 0x00, 0xff}}},
    {{{   256,    256,    256}, 0, ST_B(    32,     64), {0x00, 0x7f, 0x00, 0xff}}},
    {{{   256,    256,   -256}, 0, ST_B(    32,      0), {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -256,    256,   -256}, 0, ST_B(     0,      0), {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x0700FB48 - 0x0700FBD8
static const Gfx ssl_seg7_sub_dl_tox_box_inside[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, ssl_seg7_texture_tox_box_inside),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ssl_seg7_lights_0700BF90.l, 1),
    gsSPLight(&ssl_seg7_lights_0700BF90.a, 2),
    gsSPVertex(ssl_seg7_vertex_tox_box_inside, 22, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0, 15, 16, 17, 0x0),
    gsSP2Triangles(18, 19, 20, 0x0, 15, 21, 16, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700FBD8 - 0x0700FC40
static const Gfx ssl_seg7_sub_dl_tox_box_smile[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, ssl_seg7_texture_tox_box_smile),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 64), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ssl_seg7_vertex_tox_box_smile, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 0,  2, 10, 0x0,  7,  9, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700FC40 - 0x0700FCA8
static const Gfx ssl_seg7_sub_dl_tox_box_frown[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, ssl_seg7_texture_tox_box_frown),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 64), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ssl_seg7_vertex_tox_box_frown, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles( 8, 10, 14, 0x0, 11, 15, 12, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700FCA8 - 0x0700FCE0
static const Gfx ssl_seg7_sub_dl_tox_box_top[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, ssl_seg7_texture_tox_box_top),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 64), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ssl_seg7_vertex_tox_box_top, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700FCE0 - 0x0700FD80
const Gfx ssl_seg7_dl_tox_box[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ssl_seg7_sub_dl_tox_box_inside),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ssl_seg7_sub_dl_tox_box_smile),
    gsSPDisplayList(ssl_seg7_sub_dl_tox_box_frown),
    gsSPDisplayList(ssl_seg7_sub_dl_tox_box_top),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
