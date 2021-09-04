// Warp Pipe

// 0x030079E8
static const Lights1 warp_pipe_seg3_lights_outside = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x03007A00
static const Vtx warp_pipe_seg3_vertex_sides_1[] = {
    {{{  -102,      0,      0}, 0, ST_B(    32,     64), {0x7d, 0x00, 0xef, 0xff}}},
    {{{   -72,    205,     72}, 0, ST_B(   -32,      0), {0x65, 0x00, 0xb4, 0xff}}},
    {{{   -72,      0,     72}, 0, ST_B(   -32,     64), {0x4d, 0x00, 0x9c, 0xff}}},
    {{{    72,      0,     72}, 0, ST_B(    32,     64), {0x9b, 0x00, 0xb4, 0xff}}},
    {{{    72,    205,     72}, 0, ST_B(    32,      0), {0xb4, 0x00, 0x9b, 0xff}}},
    {{{   102,    205,      0}, 0, ST_B(   -32,      0), {0x83, 0x00, 0xef, 0xff}}},
    {{{   102,      0,      0}, 0, ST_B(   -32,     64), {0x83, 0x00, 0x11, 0xff}}},
    {{{     0,      0,    102}, 0, ST_B(    32,     64), {0xef, 0x00, 0x83, 0xff}}},
    {{{     0,    205,    102}, 0, ST_B(    32,      0), {0x11, 0x00, 0x83, 0xff}}},
    {{{    72,    205,     72}, 0, ST_B(   -32,      0), {0xb4, 0x00, 0x9b, 0xff}}},
    {{{    72,      0,     72}, 0, ST_B(   -32,     64), {0x9b, 0x00, 0xb4, 0xff}}},
    {{{   -72,      0,     72}, 0, ST_B(    32,     64), {0x4d, 0x00, 0x9c, 0xff}}},
    {{{   -72,    205,     72}, 0, ST_B(    32,      0), {0x65, 0x00, 0xb4, 0xff}}},
    {{{     0,    205,    102}, 0, ST_B(   -32,      0), {0x11, 0x00, 0x83, 0xff}}},
    {{{     0,      0,    102}, 0, ST_B(   -32,     64), {0xef, 0x00, 0x83, 0xff}}},
    {{{    72,      0,    -72}, 0, ST_B(    32,     64), {0xb4, 0x00, 0x65, 0xff}}},
    {{{     0,    205,   -102}, 0, ST_B(   -32,      0), {0xef, 0x00, 0x7d, 0xff}}},
    {{{     0,      0,   -102}, 0, ST_B(   -32,     64), {0x11, 0x00, 0x7d, 0xff}}},
    {{{  -102,    205,      0}, 0, ST_B(    32,      0), {0x7d, 0x00, 0x11, 0xff}}},
    {{{   -72,      0,    -72}, 0, ST_B(    32,     64), {0x65, 0x00, 0x4c, 0xff}}},
    {{{  -102,    205,      0}, 0, ST_B(   -32,      0), {0x7d, 0x00, 0x11, 0xff}}},
    {{{  -102,      0,      0}, 0, ST_B(   -32,     64), {0x7d, 0x00, 0xef, 0xff}}},
    {{{   -72,    205,    -72}, 0, ST_B(    32,      0), {0x4c, 0x00, 0x65, 0xff}}},
    {{{     0,      0,   -102}, 0, ST_B(    32,     64), {0x11, 0x00, 0x7d, 0xff}}},
    {{{   -72,    205,    -72}, 0, ST_B(   -32,      0), {0x4c, 0x00, 0x65, 0xff}}},
    {{{   -72,      0,    -72}, 0, ST_B(   -32,     64), {0x65, 0x00, 0x4c, 0xff}}},
    {{{     0,    205,   -102}, 0, ST_B(    32,      0), {0xef, 0x00, 0x7d, 0xff}}},
    {{{    72,    205,    -72}, 0, ST_B(    32,      0), {0x9c, 0x00, 0x4d, 0xff}}},
};

// 0x03007BE0
static const Vtx warp_pipe_seg3_vertex_sides_2[] = {
    {{{     0,      0,    154}, 0, ST_B(    32,     64), {0xef, 0x00, 0x7d, 0xff}}},
    {{{     0,    205,    154}, 0, ST_B(    32,      0), {0x11, 0x00, 0x7d, 0xff}}},
    {{{  -109,    205,    109}, 0, ST_B(   -32,      0), {0xb4, 0x00, 0x65, 0xff}}},
    {{{   102,      0,      0}, 0, ST_B(    32,     64), {0x83, 0x00, 0x11, 0xff}}},
    {{{   102,    205,      0}, 0, ST_B(    32,      0), {0x83, 0x00, 0xef, 0xff}}},
    {{{    72,    205,    -72}, 0, ST_B(   -32,      0), {0x9c, 0x00, 0x4d, 0xff}}},
    {{{    72,      0,    -72}, 0, ST_B(   -32,     64), {0xb4, 0x00, 0x65, 0xff}}},
    {{{   154,      0,      0}, 0, ST_B(    32,     64), {0x7d, 0x00, 0x11, 0xff}}},
    {{{   154,    205,      0}, 0, ST_B(    32,      0), {0x7d, 0x00, 0xef, 0xff}}},
    {{{   109,    205,    109}, 0, ST_B(   -32,      0), {0x65, 0x00, 0x4c, 0xff}}},
    {{{   109,      0,    109}, 0, ST_B(   -32,     64), {0x4c, 0x00, 0x65, 0xff}}},
    {{{   109,      0,    109}, 0, ST_B(    32,     64), {0x4c, 0x00, 0x65, 0xff}}},
    {{{   109,    205,    109}, 0, ST_B(    32,      0), {0x65, 0x00, 0x4c, 0xff}}},
    {{{     0,    205,    154}, 0, ST_B(   -32,      0), {0x11, 0x00, 0x7d, 0xff}}},
    {{{     0,      0,    154}, 0, ST_B(   -32,     64), {0xef, 0x00, 0x7d, 0xff}}},
    {{{  -109,      0,   -109}, 0, ST_B(    32,     64), {0xb4, 0x00, 0x9b, 0xff}}},
    {{{     0,    205,   -154}, 0, ST_B(   -32,      0), {0xef, 0x00, 0x83, 0xff}}},
    {{{     0,      0,   -154}, 0, ST_B(   -32,     64), {0x11, 0x00, 0x83, 0xff}}},
    {{{  -109,      0,    109}, 0, ST_B(   -32,     64), {0x9b, 0x00, 0x4c, 0xff}}},
    {{{  -109,      0,    109}, 0, ST_B(    32,     64), {0x9b, 0x00, 0x4c, 0xff}}},
    {{{  -109,    205,    109}, 0, ST_B(    32,      0), {0xb4, 0x00, 0x65, 0xff}}},
    {{{  -154,    205,      0}, 0, ST_B(   -32,      0), {0x83, 0x00, 0x11, 0xff}}},
    {{{  -154,      0,      0}, 0, ST_B(   -32,     64), {0x83, 0x00, 0xef, 0xff}}},
    {{{  -154,      0,      0}, 0, ST_B(    32,     64), {0x83, 0x00, 0xef, 0xff}}},
    {{{  -109,    205,   -109}, 0, ST_B(   -32,      0), {0x9b, 0x00, 0xb4, 0xff}}},
    {{{  -109,      0,   -109}, 0, ST_B(   -32,     64), {0xb4, 0x00, 0x9b, 0xff}}},
    {{{  -154,    205,      0}, 0, ST_B(    32,      0), {0x83, 0x00, 0x11, 0xff}}},
    {{{  -109,    205,   -109}, 0, ST_B(    32,      0), {0x9b, 0x00, 0xb4, 0xff}}},
};

// 0x03007DC0
static const Vtx warp_pipe_seg3_vertex_sides_3[] = {
    {{{     0,      0,   -154}, 0, ST_B(    32,     64), {0x11, 0x00, 0x83, 0xff}}},
    {{{     0,    205,   -154}, 0, ST_B(    32,      0), {0xef, 0x00, 0x83, 0xff}}},
    {{{   109,    205,   -109}, 0, ST_B(   -32,      0), {0x4c, 0x00, 0x9b, 0xff}}},
    {{{   109,      0,   -109}, 0, ST_B(   -32,     64), {0x65, 0x00, 0xb4, 0xff}}},
    {{{   109,      0,   -109}, 0, ST_B(    32,     64), {0x65, 0x00, 0xb4, 0xff}}},
    {{{   109,    205,   -109}, 0, ST_B(    32,      0), {0x4c, 0x00, 0x9b, 0xff}}},
    {{{   154,    205,      0}, 0, ST_B(   -32,      0), {0x7d, 0x00, 0xef, 0xff}}},
    {{{   154,      0,      0}, 0, ST_B(   -32,     64), {0x7d, 0x00, 0x11, 0xff}}},
};

// 0x03007E40
ALIGNED8 static const Texture warp_pipe_seg3_texture_side[] = {
#include "actors/warp_pipe/warp_pipe_side.rgba16.inc.c"
};

// 0x03008E40 - 0x03008F98
const Gfx warp_pipe_seg3_sub_dl_sides[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, warp_pipe_seg3_texture_side),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 64), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&warp_pipe_seg3_lights_outside.l, 1),
    gsSPLight(&warp_pipe_seg3_lights_outside.a, 2),
    gsSPVertex(warp_pipe_seg3_vertex_sides_1, 28, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0, 15, 27, 16, 0x0),
    gsSP2Triangles(15, 16, 17, 0x0,  0, 18,  1, 0x0),
    gsSP2Triangles(19, 20, 21, 0x0, 19, 22, 20, 0x0),
    gsSP2Triangles(23, 24, 25, 0x0, 23, 26, 24, 0x0),
    gsSPVertex(warp_pipe_seg3_vertex_sides_2, 28, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0, 15, 27, 16, 0x0),
    gsSP2Triangles(15, 16, 17, 0x0,  0,  2, 18, 0x0),
    gsSP2Triangles(19, 20, 21, 0x0, 19, 21, 22, 0x0),
    gsSP2Triangles(23, 24, 25, 0x0, 23, 26, 24, 0x0),
    gsSPVertex(warp_pipe_seg3_vertex_sides_3, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x03008F98 - 0x03008FF8
const Gfx warp_pipe_seg3_dl_sides[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(warp_pipe_seg3_sub_dl_sides),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x03009010
static const Lights1 warp_pipe_seg3_lights_inside = gdSPDefLights1(
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x03009028
static const Vtx warp_pipe_seg3_vertex_top[] = {
    {{{   109,    205,   -109}, 0, {   400,   -176}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{     0,    205,   -154}, 0, {    16,     48}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{     0,    205,   -102}, 0, {  6<<5,   6<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -109,    205,    109}, 0, { 20<<5,  34<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{     0,    205,    102}, 0, { 27<<5,    720}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   -72,    205,     72}, 0, {   608,    880}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{     0,    205,    154}, 0, {  1040,  27<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -154,    205,      0}, 0, {  6<<5,    944}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   109,    205,    109}, 0, {  1120,    400}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{    72,    205,     72}, 0, { 29<<5,    416}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -102,    205,      0}, 0, {   304,    784}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -109,    205,   -109}, 0, {   -72,  16<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   -72,    205,    -72}, 0, {  4<<5,    496}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   154,    205,      0}, 0, { 27<<5,    -32}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   102,    205,      0}, 0, {   744,   4<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{    72,    205,    -72}, 0, {   448,   1<<5}, {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x03009128
static const Vtx warp_pipe_seg3_vertex_inside[] = {
    {{{  -102,     10,    102}, 0, {     0,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   102,     10,   -102}, 0, {     0,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -102,     10,   -102}, 0, {     0,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   102,     10,    102}, 0, {     0,      0}, {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x03009168
ALIGNED8 static const Texture warp_pipe_seg3_texture_top[] = {
#include "actors/warp_pipe/warp_pipe_top.rgba16.inc.c"
};

// 0x03009968 - 0x03009A20
const Gfx warp_pipe_seg3_sub_dl_top[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, warp_pipe_seg3_texture_top),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&warp_pipe_seg3_lights_outside.l, 1),
    gsSPLight(&warp_pipe_seg3_lights_outside.a, 2),
    gsSPVertex(warp_pipe_seg3_vertex_top, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  3,  5, 0x0),
    gsSP2Triangles( 8,  4,  6, 0x0,  8,  9,  4, 0x0),
    gsSP2Triangles( 7,  5, 10, 0x0, 11,  7, 10, 0x0),
    gsSP2Triangles(11, 10, 12, 0x0,  1, 11, 12, 0x0),
    gsSP2Triangles( 1, 12,  2, 0x0, 13, 14,  9, 0x0),
    gsSP2Triangles( 0,  2, 15, 0x0, 13,  0, 15, 0x0),
    gsSP2Triangles(13, 15, 14, 0x0, 13,  9,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x03009A20 - 0x03009A50
const Gfx warp_pipe_seg3_sub_dl_inside[] = {
    gsSPLight(&warp_pipe_seg3_lights_inside.l, 1),
    gsSPLight(&warp_pipe_seg3_lights_inside.a, 2),
    gsSPVertex(warp_pipe_seg3_vertex_inside, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x03009A50 - 0x03009AC8
const Gfx warp_pipe_seg3_dl_top_inside[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(warp_pipe_seg3_sub_dl_top),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(warp_pipe_seg3_sub_dl_inside),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
