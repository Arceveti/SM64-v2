// Bobomb

// 0x0801DA60
ALIGNED8 static const Texture bobomb_seg8_texture_left_side[] = {
#include "actors/bobomb/bob-omb_left_side.rgba16.inc.c"
};

// 0x0801EA60
ALIGNED8 static const Texture bobomb_seg8_texture_right_side[] = {
#include "actors/bobomb/bob-omb_right_side.rgba16.inc.c"
};

// 0x0801FA60
ALIGNED8 static const Texture bobomb_seg8_texture_pink_left_side[] = {
#include "actors/bobomb/bob-omb_buddy_left_side.rgba16.inc.c"
};

// 0x08020A60
ALIGNED8 static const Texture bobomb_seg8_texture_pink_right_side[] = {
#include "actors/bobomb/bob-omb_buddy_right_side.rgba16.inc.c"
};

// 0x08021A60
ALIGNED8 static const Texture bobomb_seg8_texture_eyes[] = {
#include "actors/bobomb/bob-omb_eyes.rgba16.inc.c"
};

// 0x08022260
ALIGNED8 static const Texture bobomb_seg8_texture_eyes_blink[] = {
#include "actors/bobomb/bob-omb_eyes_blink.rgba16.inc.c"
};

// 0x08022A60
static const Vtx bobomb_seg8_vertex_eyes[] = {
    {{{   133,    -48,      0}, 0, ST_B(    16,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{   133,     32,      0}, 0, ST_B(    16,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{   128,     32,     50}, 0, ST_B(    32,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{   128,    -48,    -50}, 0, ST_B(     0,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{   128,    -48,     50}, 0, ST_B(    32,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{   128,     32,    -50}, 0, ST_B(     0,     32), {0xff, 0xff, 0xff, 0xff}}},
};

// 0x08022AC0 - 0x08022B08
const Gfx bobomb_seg8_sub_dl_eyes_start[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPEndDisplayList(),
};

// 0x08022B08 - 0x08022B58
const Gfx bobomb_seg8_sub_dl_eyes[] = {
    gsSPVertex(bobomb_seg8_vertex_eyes, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  3,  5,  1, 0x0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x08022B58 - 0x08022B88
const Gfx bobomb_seg8_dl_eyes[] = {
    gsSPDisplayList(bobomb_seg8_sub_dl_eyes_start),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bobomb_seg8_texture_eyes),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(bobomb_seg8_sub_dl_eyes),
    gsSPEndDisplayList(),
};

// 0x08022B88 - 0x08022BB8
const Gfx bobomb_seg8_dl_eyes_blink[] = {
    gsSPDisplayList(bobomb_seg8_sub_dl_eyes_start),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bobomb_seg8_texture_eyes_blink),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(bobomb_seg8_sub_dl_eyes),
    gsSPEndDisplayList(),
};

// 0x08022BB8
static const Vtx bobomb_seg8_vertex_body[] = {
    {{{     0,     48,      0}, 0, ST_B(32-0.5,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{   -48,    -48,      0}, 0, ST_B(  -0.5,     64), {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,    -48,      0}, 0, ST_B(32-0.5,     64), {0xff, 0xff, 0xff, 0xff}}},
    {{{   -48,     48,      0}, 0, ST_B(  -0.5,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{    48,     48,      0}, 0, ST_B(32+0.5,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,    -48,      0}, 0, ST_B(   0.5,     64), {0xff, 0xff, 0xff, 0xff}}},
    {{{    48,    -48,      0}, 0, ST_B(32+0.5,     64), {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,     48,      0}, 0, ST_B(   0.5,      0), {0xff, 0xff, 0xff, 0xff}}},
};

// 0x08022C38 - 0x08022CA0
const Gfx bobomb_seg8_sub_dl_body_black[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bobomb_seg8_texture_left_side),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 64), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bobomb_seg8_vertex_body, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bobomb_seg8_texture_right_side),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 64), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x08022CA0 - 0x08022D08
const Gfx bobomb_seg8_sub_dl_body_pink[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bobomb_seg8_texture_pink_left_side),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 64), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bobomb_seg8_vertex_body, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bobomb_seg8_texture_pink_right_side),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 64), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x08022D08 - 0x08022D78
const Gfx bobomb_seg8_dl_body_black[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bobomb_seg8_sub_dl_body_black),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x08022D78 - 0x08022DE8
const Gfx bobomb_seg8_dl_body_pink[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bobomb_seg8_sub_dl_body_pink),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x08022DE8
static const Lights1 bobomb_seg8_lights_feet = gdSPDefLights1(
    0x3f, 0x26, 0x04,
    0xff, 0x99, 0x12, 0x28, 0x28, 0x28
);

// 0x08022E00
static const Lights1 bobomb_seg8_lights_cap = gdSPDefLights1(
    0x2c, 0x2c, 0x2c,
    0xb2, 0xb2, 0xb2, 0x28, 0x28, 0x28
);

// 0x08022E30
static const Vtx bobomb_seg8_vertex_right_foot[] = {
    {{{    27,    -27,    -32}, 0, {     0,      0}, {0xeb, 0x96, 0xbf, 0x00}}},
    {{{   -36,      0,    -20}, 0, {     0,      0}, {0xb1, 0xd0, 0xaa, 0x00}}},
    {{{    32,      0,    -40}, 0, {     0,      0}, {0xfc, 0xfb, 0x82, 0x00}}},
    {{{    85,      0,    -32}, 0, {     0,      0}, {0x50, 0xf1, 0xa0, 0xff}}},
    {{{    80,     27,    -20}, 0, {     0,      0}, {0x34, 0x62, 0xc4, 0xff}}},
    {{{    80,     27,     16}, 0, {     0,      0}, {0x34, 0x62, 0x3c, 0xff}}},
    {{{    85,      0,     27}, 0, {     0,      0}, {0x50, 0xf1, 0x60, 0xff}}},
    {{{    32,     27,     27}, 0, {     0,      0}, {0xff, 0x69, 0x47, 0xff}}},
    {{{   -27,     27,     16}, 0, {     0,      0}, {0xc8, 0x60, 0x3c, 0xff}}},
    {{{   -36,      0,     16}, 0, {     0,      0}, {0xb1, 0xd0, 0x56, 0xff}}},
    {{{    32,      0,     37}, 0, {     0,      0}, {0xfc, 0xfb, 0x7e, 0xff}}},
    {{{    32,     27,    -32}, 0, {     0,      0}, {0xff, 0x69, 0xb9, 0xff}}},
    {{{   -27,     27,    -16}, 0, {     0,      0}, {0xc8, 0x60, 0xc4, 0xff}}},
    {{{    68,    -27,     16}, 0, {     0,      0}, {0x26, 0x95, 0x36, 0xff}}},
    {{{    68,    -27,    -20}, 0, {     0,      0}, {0x26, 0x95, 0xca, 0xff}}},
    {{{    27,    -27,     27}, 0, {     0,      0}, {0xeb, 0x96, 0x41, 0xff}}},
    {{{    27,    -27,    -32}, 0, {     0,      0}, {0xed, 0x90, 0xc8, 0xff}}},
    {{{    27,    -27,     27}, 0, {     0,      0}, {0xf5, 0xa2, 0x53, 0x00}}},
    {{{   -36,      0,     16}, 0, {     0,      0}, {0xa2, 0xf8, 0x54, 0x00}}},
    {{{   -36,      0,    -20}, 0, {     0,      0}, {0xa9, 0xdd, 0xac, 0xff}}},
};

// 0x08022F70
static const Vtx bobomb_seg8_vertex_left_foot[] = {
    {{{    32,      0,     40}, 0, {     0,      0}, {0xfc, 0xfb, 0x7e, 0x00}}},
    {{{   -36,      0,     20}, 0, {     0,      0}, {0xb1, 0xd0, 0x56, 0x00}}},
    {{{    27,    -27,     32}, 0, {     0,      0}, {0xeb, 0x96, 0x41, 0x00}}},
    {{{    84,      0,    -27}, 0, {     0,      0}, {0x50, 0xf1, 0xa0, 0xff}}},
    {{{    80,     27,    -16}, 0, {     0,      0}, {0x34, 0x62, 0xc4, 0xff}}},
    {{{    80,     27,     20}, 0, {     0,      0}, {0x34, 0x62, 0x3c, 0xff}}},
    {{{    84,      0,     32}, 0, {     0,      0}, {0x50, 0xf1, 0x60, 0xff}}},
    {{{    32,      0,    -37}, 0, {     0,      0}, {0xfc, 0xfb, 0x82, 0xff}}},
    {{{   -36,      0,    -16}, 0, {     0,      0}, {0xb1, 0xd0, 0xaa, 0xff}}},
    {{{   -28,     27,    -16}, 0, {     0,      0}, {0xc8, 0x60, 0xc4, 0xff}}},
    {{{    32,     27,    -27}, 0, {     0,      0}, {0xff, 0x69, 0xb9, 0xff}}},
    {{{   -27,     27,     16}, 0, {     0,      0}, {0xc8, 0x60, 0x3c, 0xff}}},
    {{{    32,     27,     32}, 0, {     0,      0}, {0xff, 0x69, 0x47, 0xff}}},
    {{{    68,    -27,     20}, 0, {     0,      0}, {0x26, 0x95, 0x36, 0xff}}},
    {{{    68,    -27,    -16}, 0, {     0,      0}, {0x26, 0x95, 0xca, 0xff}}},
    {{{    27,    -27,    -27}, 0, {     0,      0}, {0xeb, 0x96, 0xbf, 0xff}}},
    {{{    27,    -27,    -27}, 0, {     0,      0}, {0xed, 0x90, 0xc8, 0xff}}},
    {{{    27,    -27,     32}, 0, {     0,      0}, {0xf5, 0xa2, 0x53, 0x00}}},
    {{{   -36,      0,     20}, 0, {     0,      0}, {0xa2, 0xf8, 0x54, 0x00}}},
    {{{   -36,      0,    -16}, 0, {     0,      0}, {0xa9, 0xdd, 0xac, 0xff}}},
};

// 0x080230B0
static const Vtx bobomb_seg8_vertex_cap[] = {
    {{{     0,   -100,     64}, 0, {     0,      0}, {0x00, 0xfe, 0x7f, 0x00}}},
    {{{   -54,   -100,     32}, 0, {     0,      0}, {0xc1, 0xfe, 0x6d, 0x00}}},
    {{{   -54,   -140,     32}, 0, {     0,      0}, {0xc1, 0xfe, 0x6d, 0x00}}},
    {{{     0,   -140,     64}, 0, {     0,      0}, {0x00, 0xfe, 0x7f, 0xff}}},
    {{{    54,   -100,     32}, 0, {     0,      0}, {0x3f, 0xfe, 0x6d, 0xff}}},
    {{{    54,   -140,     32}, 0, {     0,      0}, {0x3f, 0xfe, 0x6d, 0xff}}},
    {{{   -54,   -100,     32}, 0, {     0,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   -54,   -100,    -32}, 0, {     0,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   -54,   -140,    -32}, 0, {     0,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   -54,   -140,     32}, 0, {     0,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   -54,   -100,    -32}, 0, {     0,      0}, {0xc1, 0x02, 0x93, 0xff}}},
    {{{     0,   -100,    -64}, 0, {     0,      0}, {0xc1, 0x02, 0x93, 0xff}}},
    {{{     0,   -140,    -64}, 0, {     0,      0}, {0xc1, 0x02, 0x93, 0xff}}},
    {{{   -54,   -140,    -32}, 0, {     0,      0}, {0xc1, 0x02, 0x93, 0xff}}},
    {{{    54,   -100,    -32}, 0, {     0,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{    54,   -100,     32}, 0, {     0,      0}, {0x7f, 0x00, 0x00, 0x00}}},
    {{{    54,   -140,     32}, 0, {     0,      0}, {0x7f, 0x00, 0x00, 0x00}}},
    {{{    54,   -140,    -32}, 0, {     0,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{     0,   -100,    -64}, 0, {     0,      0}, {0x3f, 0x02, 0x93, 0xff}}},
    {{{    54,   -100,    -32}, 0, {     0,      0}, {0x3f, 0x02, 0x93, 0xff}}},
    {{{    54,   -140,    -32}, 0, {     0,      0}, {0x3f, 0x02, 0x93, 0xff}}},
    {{{     0,   -140,    -64}, 0, {     0,      0}, {0x3f, 0x02, 0x93, 0xff}}},
    {{{     0,   -140,    -64}, 0, {     0,      0}, {0x00, 0x81, 0xfe, 0xff}}},
    {{{    54,   -140,    -32}, 0, {     0,      0}, {0x00, 0x81, 0xfe, 0xff}}},
    {{{    54,   -140,     32}, 0, {     0,      0}, {0x00, 0x81, 0xfe, 0xff}}},
    {{{     0,   -140,     64}, 0, {     0,      0}, {0x00, 0x81, 0xfe, 0xff}}},
    {{{   -54,   -140,     32}, 0, {     0,      0}, {0x00, 0x81, 0xfe, 0xff}}},
    {{{   -54,   -140,    -32}, 0, {     0,      0}, {0x00, 0x81, 0xfe, 0xff}}},
};

// 0x08023270 - 0x08023378
const Gfx bobomb_seg8_dl_right_foot[] = {
    gsSPLight(&bobomb_seg8_lights_feet.l, 1),
    gsSPLight(&bobomb_seg8_lights_feet.a, 2),
    gsSPVertex(bobomb_seg8_vertex_right_foot, 20, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12,  8, 0x0),
    gsSP2Triangles(11,  8,  7, 0x0,  6, 13, 14, 0x0),
    gsSP2Triangles( 6, 14,  3, 0x0,  9,  8, 12, 0x0),
    gsSP2Triangles( 9, 12,  1, 0x0, 10,  9, 15, 0x0),
    gsSP2Triangles( 2,  1, 12, 0x0,  2, 12, 11, 0x0),
    gsSP2Triangles(10,  6,  5, 0x0, 10,  5,  7, 0x0),
    gsSP2Triangles( 0, 14, 13, 0x0,  0, 13, 15, 0x0),
    gsSP2Triangles(11,  4,  3, 0x0, 11,  3,  2, 0x0),
    gsSP2Triangles( 2,  3, 14, 0x0,  2, 14,  0, 0x0),
    gsSP2Triangles( 7,  5,  4, 0x0,  7,  4, 11, 0x0),
    gsSP2Triangles(15, 13,  6, 0x0, 15,  6, 10, 0x0),
    gsSP2Triangles(16, 17, 18, 0x0, 16, 18, 19, 0x0),
    gsSPEndDisplayList(),
};

// 0x08023378 - 0x08023480
const Gfx bobomb_seg8_dl_eft_foot[] = {
    gsSPLight(&bobomb_seg8_lights_feet.l, 1),
    gsSPLight(&bobomb_seg8_lights_feet.a, 2),
    gsSPVertex(bobomb_seg8_vertex_left_foot, 20, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0,  6, 13, 14, 0x0),
    gsSP2Triangles( 6, 14,  3, 0x0,  1, 11,  9, 0x0),
    gsSP2Triangles( 1,  9,  8, 0x0, 15,  8,  7, 0x0),
    gsSP2Triangles(12, 11,  1, 0x0, 12,  1,  0, 0x0),
    gsSP2Triangles(10,  4,  3, 0x0, 10,  3,  7, 0x0),
    gsSP2Triangles(15, 14, 13, 0x0, 15, 13,  2, 0x0),
    gsSP2Triangles( 0,  6,  5, 0x0,  0,  5, 12, 0x0),
    gsSP2Triangles( 2, 13,  6, 0x0,  2,  6,  0, 0x0),
    gsSP2Triangles(12,  5,  4, 0x0, 12,  4, 10, 0x0),
    gsSP2Triangles( 7,  3, 14, 0x0,  7, 14, 15, 0x0),
    gsSP2Triangles(16, 17, 18, 0x0, 16, 18, 19, 0x0),
    gsSPEndDisplayList(),
};

// 0x08023480 - 0x08023528
const Gfx bobomb_seg8_dl_cap[] = {
    gsSPLight(&bobomb_seg8_lights_cap.l, 1),
    gsSPLight(&bobomb_seg8_lights_cap.a, 2),
    gsSPVertex(bobomb_seg8_vertex_cap, 28, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  0,  3, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP2Triangles(14, 15, 16, 0x0, 14, 16, 17, 0x0),
    gsSP2Triangles(18, 19, 20, 0x0, 18, 20, 21, 0x0),
    gsSP2Triangles(22, 23, 24, 0x0, 22, 24, 25, 0x0),
    gsSP2Triangles(22, 25, 26, 0x0, 22, 26, 27, 0x0),
    gsSPEndDisplayList(),
};
