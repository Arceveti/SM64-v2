// Exclamation Box Outline

// 0x08024CB8
static const Lights1 exclamation_box_outline_seg8_lights_red = gdSPDefLights1(
    0x7f, 0x00, 0x00,
    0xff, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x08024CD0
static const Lights1 exclamation_box_outline_seg8_lights_green = gdSPDefLights1(
    0x00, 0x7f, 0x00,
    0x00, 0xff, 0x00, 0x28, 0x28, 0x28
);

// 0x08024CE8
static const Lights1 exclamation_box_outline_seg8_lights_blue = gdSPDefLights1(
    0x00, 0x00, 0x7f,
    0x00, 0x00, 0xff, 0x28, 0x28, 0x28
);

// 0x08024D00
static const Lights1 exclamation_box_outline_seg8_lights_yellow = gdSPDefLights1(
    0x7f, 0x6a, 0x00,
    0xff, 0xd4, 0x00, 0x28, 0x28, 0x28
);

// 0x08024D18
static const Vtx exclamation_box_outline_seg8_vertex_shade_0[] = {
    {{{    26,      0,    -26}, 0, {     0,      0}, {0x7f, 0x00, 0x00, 0x50}}},
    {{{    26,     51,     26}, 0, {     0,      0}, {0x7f, 0x00, 0x00, 0x50}}},
    {{{    26,      0,     26}, 0, {     0,      0}, {0x7f, 0x00, 0x00, 0x50}}},
    {{{    26,      0,     26}, 0, {     0,      0}, {0x00, 0x81, 0x00, 0x50}}},
    {{{   -26,      0,     26}, 0, {     0,      0}, {0x00, 0x81, 0x00, 0x50}}},
    {{{   -26,      0,    -26}, 0, {     0,      0}, {0x00, 0x81, 0x00, 0x50}}},
    {{{    26,      0,    -26}, 0, {     0,      0}, {0x00, 0x81, 0x00, 0x50}}},
    {{{    26,      0,     26}, 0, {     0,      0}, {0x00, 0x00, 0x7f, 0x50}}},
    {{{    26,     51,     26}, 0, {     0,      0}, {0x00, 0x00, 0x7f, 0x50}}},
    {{{   -26,     51,     26}, 0, {     0,      0}, {0x00, 0x00, 0x7f, 0x50}}},
    {{{   -26,      0,     26}, 0, {     0,      0}, {0x00, 0x00, 0x7f, 0x50}}},
    {{{   -26,      0,     26}, 0, {     0,      0}, {0x81, 0x00, 0x00, 0x50}}},
    {{{   -26,     51,     26}, 0, {     0,      0}, {0x81, 0x00, 0x00, 0x50}}},
    {{{   -26,     51,    -26}, 0, {     0,      0}, {0x81, 0x00, 0x00, 0x50}}},
    {{{   -26,      0,    -26}, 0, {     0,      0}, {0x81, 0x00, 0x00, 0x50}}},
};

// 0x08024E08
static const Vtx exclamation_box_outline_seg8_vertex_shade_1[] = {
    {{{   -26,      0,    -26}, 0, {     0,      0}, {0x00, 0x00, 0x81, 0x50}}},
    {{{   -26,     51,    -26}, 0, {     0,      0}, {0x00, 0x00, 0x81, 0x50}}},
    {{{    26,     51,    -26}, 0, {     0,      0}, {0x00, 0x00, 0x81, 0x50}}},
    {{{    26,      0,    -26}, 0, {     0,      0}, {0x00, 0x00, 0x81, 0x50}}},
    {{{    26,      0,    -26}, 0, {     0,      0}, {0x7f, 0x00, 0x00, 0x50}}},
    {{{    26,     51,    -26}, 0, {     0,      0}, {0x7f, 0x00, 0x00, 0x50}}},
    {{{    26,     51,     26}, 0, {     0,      0}, {0x7f, 0x00, 0x00, 0x50}}},
    {{{   -26,     51,     26}, 0, {     0,      0}, {0x00, 0x7f, 0x00, 0x50}}},
    {{{    26,     51,     26}, 0, {     0,      0}, {0x00, 0x7f, 0x00, 0x50}}},
    {{{    26,     51,    -26}, 0, {     0,      0}, {0x00, 0x7f, 0x00, 0x50}}},
    {{{   -26,     51,    -26}, 0, {     0,      0}, {0x00, 0x7f, 0x00, 0x50}}},
};

// 0x08024EB8 - 0x08024F30
const Gfx exclamation_box_outline_seg8_sub_dl_shade[] = {
    gsSPVertex(exclamation_box_outline_seg8_vertex_shade_0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(exclamation_box_outline_seg8_vertex_shade_1, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP1Triangle( 7,  9, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x08024F30 - 0x08024F58
const Gfx exclamation_box_outline_seg8_dl_shade_begin[] = {
    gsDPPipeSync(),
    gsDPSetEnvColor(255, 255, 255, 80),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetCombineMode(G_CC_SHADEFADEA, G_CC_SHADEFADEA),
    gsSPEndDisplayList(),
};

// 0x08024F58 - 0x08024F88
const Gfx exclamation_box_outline_seg8_dl_shade_end[] = {
    gsSPDisplayList(exclamation_box_outline_seg8_sub_dl_shade),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsSPEndDisplayList(),
};

// 0x08024F88 - 0x08024FA8
const Gfx exclamation_box_outline_seg8_dl_shade_red[] = {
    gsSPDisplayList(exclamation_box_outline_seg8_dl_shade_begin),
    gsSPLight(&exclamation_box_outline_seg8_lights_red.l, 1),
    gsSPLight(&exclamation_box_outline_seg8_lights_red.a, 2),
    gsSPBranchList(exclamation_box_outline_seg8_dl_shade_end),
};

// 0x08024FA8 - 0x08024FC8
const Gfx exclamation_box_outline_seg8_dl_shade_green[] = {
    gsSPDisplayList(exclamation_box_outline_seg8_dl_shade_begin),
    gsSPLight(&exclamation_box_outline_seg8_lights_green.l, 1),
    gsSPLight(&exclamation_box_outline_seg8_lights_green.a, 2),
    gsSPBranchList(exclamation_box_outline_seg8_dl_shade_end),
};

// 0x08024FC8 - 0x08024FE8
const Gfx exclamation_box_outline_seg8_dl_shade_blue[] = {
    gsSPDisplayList(exclamation_box_outline_seg8_dl_shade_begin),
    gsSPLight(&exclamation_box_outline_seg8_lights_blue.l, 1),
    gsSPLight(&exclamation_box_outline_seg8_lights_blue.a, 2),
    gsSPBranchList(exclamation_box_outline_seg8_dl_shade_end),
};

// 0x08024FE8 - 0x08025008
const Gfx exclamation_box_outline_seg8_dl_shade_yellow[] = {
    gsSPDisplayList(exclamation_box_outline_seg8_dl_shade_begin),
    gsSPLight(&exclamation_box_outline_seg8_lights_yellow.l, 1),
    gsSPLight(&exclamation_box_outline_seg8_lights_yellow.a, 2),
    gsSPBranchList(exclamation_box_outline_seg8_dl_shade_end),
};

// 0x08025008
static const Vtx exclamation_box_outline_seg8_vertex_outline_0[] = {
    {{{   -26,     51,     26}, 0, ST_B(    32,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{    26,     51,     26}, 0, ST_B(    32,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{    26,     51,    -26}, 0, ST_B(     0,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{   -26,     51,    -26}, 0, ST_B(     0,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{    26,      0,     26}, 0, ST_B(    32,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{   -26,     51,     26}, 0, ST_B(     0,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{   -26,      0,     26}, 0, ST_B(     0,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{    26,      0,    -26}, 0, ST_B(    32,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{    26,     51,    -26}, 0, ST_B(    32,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{    26,     51,     26}, 0, ST_B(     0,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{    26,      0,     26}, 0, ST_B(     0,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{   -26,      0,    -26}, 0, ST_B(     0,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{    26,      0,    -26}, 0, ST_B(     0,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{   -26,     51,    -26}, 0, ST_B(    32,     32), {0xff, 0xff, 0xff, 0xff}}},
};

// 0x080250E8
static const Vtx exclamation_box_outline_seg8_vertex_outline_1[] = {
    {{{   -26,      0,     26}, 0, ST_B(    32,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{   -26,     51,     26}, 0, ST_B(    32,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{   -26,     51,    -26}, 0, ST_B(     0,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{   -26,      0,    -26}, 0, ST_B(     0,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{   -26,      0,     26}, 0, ST_B(     0,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{   -26,      0,    -26}, 0, ST_B(    32,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{    26,      0,    -26}, 0, ST_B(    32,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{    26,      0,     26}, 0, ST_B(     0,      0), {0xff, 0xff, 0xff, 0xff}}},
};

// 0x08025168
ALIGNED8 static const Texture exclamation_box_outline_seg8_texture_outline[] = {
#include "actors/exclamation_box_outline/exclamation_box_outline.rgba16.inc.c"
};

// 0x08025968 - 0x080259F8
const Gfx exclamation_box_outline_seg8_sub_dl_outline[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, exclamation_box_outline_seg8_texture_outline),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(exclamation_box_outline_seg8_vertex_outline_0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  1,  5, 0x0,  4,  5,  6, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0,  7,  9, 10, 0x0),
    gsSP2Triangles(11,  8, 12, 0x0, 11, 13,  8, 0x0),
    gsSPVertex(exclamation_box_outline_seg8_vertex_outline_1, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x080259F8 - 0x08025A68
const Gfx exclamation_box_outline_seg8_dl_outline[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(exclamation_box_outline_seg8_sub_dl_outline),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPEndDisplayList(),
};

// 0x08025A68
static const Lights1 exclamation_box_outline_seg8_lights_exclamation_point = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x08025A80
ALIGNED8 static const Texture exclamation_box_outline_seg8_texture_exclamation_point[] = {
#include "actors/exclamation_box_outline/exclamation_point.rgba16.inc.c"
};

// 0x08025E80
static const Vtx exclamation_box_outline_seg8_vertex_exclamation_point[] = {
    {{{   -22,     48,      0}, 0, {  -160,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   -22,      4,      0}, 0, {  -160,   1056}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{    23,      4,      0}, 0, {   608,   1056}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{    23,     48,      0}, 0, {   608,      0}, {0x00, 0x00, 0x7f, 0xff}}},
};

// 0x08025EC0 - 0x08025F08
const Gfx exclamation_box_outline_seg8_sub_dl_exclamation_point[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, exclamation_box_outline_seg8_texture_exclamation_point),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 32 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&exclamation_box_outline_seg8_lights_exclamation_point.l, 1),
    gsSPLight(&exclamation_box_outline_seg8_lights_exclamation_point.a, 2),
    gsSPVertex(exclamation_box_outline_seg8_vertex_exclamation_point, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x08025F08 - 0x08025F78
const Gfx exclamation_box_outline_seg8_dl_exclamation_point[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 4, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (16 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(exclamation_box_outline_seg8_sub_dl_exclamation_point),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
