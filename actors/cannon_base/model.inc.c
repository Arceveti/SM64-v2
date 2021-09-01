// Cannon Base

// 0x08004988
static const Lights1 cannon_base_seg8_lights_faces = gdSPDefLights1(
    0x4c, 0x4c, 0x4c,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x080049A0
static const Lights1 cannon_base_seg8_lights_edges = gdSPDefLights1(
    0x0e, 0x10, 0x4c,
    0x30, 0x37, 0xff, 0x28, 0x28, 0x28
);

// 0x080049B8
ALIGNED8 static const Texture dCannonBaseTexture[] = {
#include "actors/cannon_base/cannon_base.rgba16.inc.c"
};

// 0x080051B8
static const Vtx cannon_base_seg8_vertex_faces[] = {
    {{{   102,   -102,     51}, 0, ST_B(     0,     55), {0x7f, 0x00, 0x00, 0xff}}},
    {{{   102,   -102,    -51}, 0, ST_B(    32,     55), {0x7f, 0x00, 0x00, 0xff}}},
    {{{   102,     51,    -51}, 0, ST_B(    32,      7), {0x7f, 0x00, 0x00, 0xff}}},
    {{{   102,     77,     26}, 0, ST_B(     7,     -1), {0x7f, 0x00, 0x00, 0xff}}},
    {{{   102,     51,     51}, 0, ST_B(     0,      7), {0x7f, 0x00, 0x00, 0xff}}},
    {{{   102,     77,    -26}, 0, ST_B(    23,     -1), {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -102,     51,    -51}, 0, ST_B(     0,      7), {0x81, 0x00, 0x00, 0xff}}},
    {{{  -102,     77,     26}, 0, ST_B(    23,      0), {0x81, 0x00, 0x00, 0xff}}},
    {{{  -102,     77,    -26}, 0, ST_B(     7,      0), {0x81, 0x00, 0x00, 0xff}}},
    {{{  -102,   -102,    -51}, 0, ST_B(     0,     55), {0x81, 0x00, 0x00, 0xff}}},
    {{{  -102,   -102,     51}, 0, ST_B(    32,     55), {0x81, 0x00, 0x00, 0xff}}},
    {{{  -102,     51,     51}, 0, ST_B(    32,      7), {0x81, 0x00, 0x00, 0xff}}},
};

// 0x08005278
static const Vtx cannon_base_seg8_vertex_08005278[] = {
    {{{   -61,   -102,     51}, 0, ST_B(     0,      0), {0x00, 0x7f, 0x00, 0xff}}},
    {{{    61,   -102,     51}, 0, ST_B(     0,      0), {0x00, 0x7f, 0x00, 0xff}}},
    {{{    61,   -102,    -51}, 0, ST_B(     0,      0), {0x00, 0x7f, 0x00, 0xff}}},
    {{{   102,   -102,    -51}, 0, ST_B(     0,      0), {0x00, 0x00, 0x81, 0xff}}},
    {{{    61,     51,    -51}, 0, ST_B(     0,      0), {0x00, 0x00, 0x81, 0xff}}},
    {{{   102,     51,    -51}, 0, ST_B(     0,      0), {0x00, 0x00, 0x81, 0xff}}},
    {{{    61,   -102,    -51}, 0, ST_B(     0,      0), {0x00, 0x00, 0x81, 0xff}}},
    {{{    61,     51,    -51}, 0, ST_B(     0,      0), {0x81, 0x00, 0x00, 0xff}}},
    {{{    61,   -102,    -51}, 0, ST_B(     0,      0), {0x81, 0x00, 0x00, 0xff}}},
    {{{    61,   -102,     51}, 0, ST_B(     0,      0), {0x81, 0x00, 0x00, 0xff}}},
    {{{    61,     77,     26}, 0, ST_B(     0,      0), {0x81, 0x00, 0x00, 0xff}}},
    {{{    61,     77,    -26}, 0, ST_B(     0,      0), {0x81, 0x00, 0x00, 0xff}}},
    {{{    61,     51,     51}, 0, ST_B(     0,      0), {0x81, 0x00, 0x00, 0xff}}},
    {{{   102,     51,    -51}, 0, ST_B(     0,      0), {0x00, 0x58, 0xa5, 0xff}}},
    {{{    61,     51,    -51}, 0, ST_B(     0,      0), {0x00, 0x58, 0xa5, 0xff}}},
    {{{    61,     77,    -26}, 0, ST_B(     0,      0), {0x00, 0x58, 0xa5, 0xff}}},
    {{{   102,     51,    -51}, 0, ST_B(     0,      0), {0x00, 0x58, 0xa5, 0xff}}},
    {{{    61,     77,    -26}, 0, ST_B(     0,      0), {0x00, 0x58, 0xa5, 0xff}}},
    {{{   102,     77,    -26}, 0, ST_B(     0,      0), {0x00, 0x58, 0xa5, 0xff}}},
    {{{   102,     77,    -26}, 0, ST_B(     0,      0), {0x00, 0x7f, 0x00, 0xff}}},
    {{{    61,     77,    -26}, 0, ST_B(     0,      0), {0x00, 0x7f, 0x00, 0xff}}},
    {{{    61,     77,     26}, 0, ST_B(     0,      0), {0x00, 0x7f, 0x00, 0xff}}},
    {{{   102,     77,     26}, 0, ST_B(     0,      0), {0x00, 0x7f, 0x00, 0xff}}},
    {{{   102,     77,     26}, 0, ST_B(     0,      0), {0x00, 0x58, 0x5b, 0xff}}},
    {{{    61,     77,     26}, 0, ST_B(     0,      0), {0x00, 0x58, 0x5b, 0xff}}},
    {{{    61,     51,     51}, 0, ST_B(     0,      0), {0x00, 0x58, 0x5b, 0xff}}},
    {{{   102,     51,     51}, 0, ST_B(     0,      0), {0x00, 0x58, 0x5b, 0xff}}},
    {{{   102,     51,     51}, 0, ST_B(     0,      0), {0x00, 0x00, 0x7f, 0xff}}},
    {{{    61,     51,     51}, 0, ST_B(     0,      0), {0x00, 0x00, 0x7f, 0xff}}},
    {{{    61,   -102,     51}, 0, ST_B(     0,      0), {0x00, 0x00, 0x7f, 0xff}}},
    {{{   102,   -102,     51}, 0, ST_B(     0,      0), {0x00, 0x00, 0x7f, 0xff}}},
};

// 0x08005468
static const Vtx cannon_base_seg8_vertex_08005468[] = {
    {{{   -61,   -102,     51}, 0, ST_B(     0,      0), {0x00, 0x7f, 0x00, 0xff}}},
    {{{    61,   -102,    -51}, 0, ST_B(     0,      0), {0x00, 0x7f, 0x00, 0xff}}},
    {{{   -61,   -102,    -51}, 0, ST_B(     0,      0), {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -102,     77,    -26}, 0, ST_B(     0,      0), {0x00, 0x58, 0xa5, 0xff}}},
    {{{   -61,     51,    -51}, 0, ST_B(     0,      0), {0x00, 0x58, 0xa5, 0xff}}},
    {{{  -102,     51,    -51}, 0, ST_B(     0,      0), {0x00, 0x58, 0xa5, 0xff}}},
    {{{  -102,     51,    -51}, 0, ST_B(     0,      0), {0x00, 0x00, 0x81, 0xff}}},
    {{{   -61,   -102,    -51}, 0, ST_B(     0,      0), {0x00, 0x00, 0x81, 0xff}}},
    {{{  -102,   -102,    -51}, 0, ST_B(     0,      0), {0x00, 0x00, 0x81, 0xff}}},
    {{{   -61,     51,    -51}, 0, ST_B(     0,      0), {0x00, 0x00, 0x81, 0xff}}},
    {{{   -61,   -102,     51}, 0, ST_B(     0,      0), {0x7f, 0x00, 0x00, 0xff}}},
    {{{   -61,   -102,    -51}, 0, ST_B(     0,      0), {0x7f, 0x00, 0x00, 0xff}}},
    {{{   -61,     51,    -51}, 0, ST_B(     0,      0), {0x7f, 0x00, 0x00, 0xff}}},
    {{{   -61,     77,    -26}, 0, ST_B(     0,      0), {0x00, 0x58, 0xa5, 0xff}}},
    {{{   -61,     77,    -26}, 0, ST_B(     0,      0), {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -102,   -102,     51}, 0, ST_B(     0,      0), {0x00, 0x00, 0x7f, 0xff}}},
    {{{   -61,     51,     51}, 0, ST_B(     0,      0), {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -102,     51,     51}, 0, ST_B(     0,      0), {0x00, 0x00, 0x7f, 0xff}}},
    {{{   -61,   -102,     51}, 0, ST_B(     0,      0), {0x00, 0x00, 0x7f, 0xff}}},
    {{{   -61,   -102,     51}, 0, ST_B(     0,      0), {0x7f, 0x00, 0x00, 0xff}}},
    {{{   -61,     77,    -26}, 0, ST_B(     0,      0), {0x7f, 0x00, 0x00, 0xff}}},
    {{{   -61,     77,     26}, 0, ST_B(     0,      0), {0x7f, 0x00, 0x00, 0xff}}},
    {{{   -61,     51,     51}, 0, ST_B(     0,      0), {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -102,     51,     51}, 0, ST_B(     0,      0), {0x00, 0x58, 0x5b, 0xff}}},
    {{{   -61,     51,     51}, 0, ST_B(     0,      0), {0x00, 0x58, 0x5b, 0xff}}},
    {{{   -61,     77,     26}, 0, ST_B(     0,      0), {0x00, 0x58, 0x5b, 0xff}}},
    {{{  -102,     77,     26}, 0, ST_B(     0,      0), {0x00, 0x58, 0x5b, 0xff}}},
    {{{  -102,     77,     26}, 0, ST_B(     0,      0), {0x00, 0x7f, 0x00, 0xff}}},
    {{{   -61,     77,     26}, 0, ST_B(     0,      0), {0x00, 0x7f, 0x00, 0xff}}},
    {{{   -61,     77,    -26}, 0, ST_B(     0,      0), {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -102,     77,    -26}, 0, ST_B(     0,      0), {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x08005658 - 0x080056D0
const Gfx cannon_base_seg8_sub_dl_faces[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, dCannonBaseTexture),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&cannon_base_seg8_lights_faces.l, 1),
    gsSPLight(&cannon_base_seg8_lights_faces.a, 2),
    gsSPVertex(cannon_base_seg8_vertex_faces, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 0,  2,  5, 0x0,  0,  5,  3, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9, 10, 0x0),
    gsSP2Triangles( 6, 10, 11, 0x0,  6, 11,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x080056D0 - 0x080057F8
const Gfx cannon_base_seg8_sub_dl_edges[] = {
    gsSPLight(&cannon_base_seg8_lights_edges.l, 1),
    gsSPLight(&cannon_base_seg8_lights_edges.a, 2),
    gsSPVertex(cannon_base_seg8_vertex_08005278, 31, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10, 11, 0x0,  7, 12, 10, 0x0),
    gsSP2Triangles( 7,  9, 12, 0x0, 13, 14, 15, 0x0),
    gsSP2Triangles(16, 17, 18, 0x0, 19, 20, 21, 0x0),
    gsSP2Triangles(19, 21, 22, 0x0, 23, 24, 25, 0x0),
    gsSP2Triangles(23, 25, 26, 0x0, 27, 28, 29, 0x0),
    gsSP1Triangle( 27, 29, 30, 0x0),
    gsSPVertex(cannon_base_seg8_vertex_08005468, 31, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0,  3, 13,  4, 0x0),
    gsSP2Triangles(10, 12, 14, 0x0, 15, 16, 17, 0x0),
    gsSP2Triangles(15, 18, 16, 0x0, 19, 20, 21, 0x0),
    gsSP2Triangles(19, 21, 22, 0x0, 23, 24, 25, 0x0),
    gsSP2Triangles(23, 25, 26, 0x0, 27, 28, 29, 0x0),
    gsSP1Triangle( 27, 29, 30, 0x0),
    gsSPEndDisplayList(),
};

// 0x080057F8 - 0x08005870
const Gfx cannon_base_seg8_dl_080057F8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, (G_TX_WRAP | G_TX_NOMIRROR), G_TX_NOMASK, G_TX_NOLOD, (G_TX_WRAP | G_TX_NOMIRROR), G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, ((32 - 1) << G_TEXTURE_IMAGE_FRAC), ((32 - 1) << G_TEXTURE_IMAGE_FRAC)),
    gsSPDisplayList(cannon_base_seg8_sub_dl_faces),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(cannon_base_seg8_sub_dl_edges),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
