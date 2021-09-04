// Snowman

// 0x05008C70
ALIGNED8 static const Texture snowman_seg5_texture_mitten[] = {
#include "actors/snowman/mr_blizzard_mitten.rgba16.inc.c"
};

// 0x05009470
ALIGNED8 static const Texture snowman_seg5_texture_left_side[] = {
#include "actors/snowman/mr_blizzard_left_side.rgba16.inc.c"
};

// 0x0500A470
ALIGNED8 static const Texture snowman_seg5_texture_right_side[] = {
#include "actors/snowman/mr_blizzard_right_side.rgba16.inc.c"
};

// 0x0500B470
ALIGNED8 static const Texture snowman_seg5_texture_eye[] = {
#include "actors/snowman/mr_blizzard_eye.rgba16.inc.c"
};

// 0x0500BC70
ALIGNED8 static const Texture snowman_seg5_texture_mouth[] = {
#include "actors/snowman/mr_blizzard_mouth.rgba16.inc.c"
};

// 0x0500C470
static const Lights1 snowman_seg5_lights_0500C470 = gdSPDefLights1(
    0x1c, 0x0f, 0x07,
    0x38, 0x1e, 0x0e, 0x28, 0x28, 0x28
);

// 0x0500C488
static const Vtx snowman_seg5_vertex_0500C488[] = {
    {{{   -24,      0,     -6}, 0, ST_B(     0,      0), {0x82, 0xfd, 0xfd, 0xff}}},
    {{{    77,    -16,     -6}, 0, ST_B(     0,      0), {0xea, 0x84, 0xf9, 0xff}}},
    {{{    77,     16,     15}, 0, ST_B(     0,      0), {0xe1, 0x36, 0x6e, 0xff}}},
    {{{    77,     16,    -24}, 0, ST_B(     0,      0), {0xe4, 0x42, 0x99, 0xff}}},
};

// 0x0500C4C8 - 0x0500C500
const Gfx snowman_seg5_dl_0500C4C8[] = {
    gsSPLight(&snowman_seg5_lights_0500C470.l, 1),
    gsSPLight(&snowman_seg5_lights_0500C470.a, 2),
    gsSPVertex(snowman_seg5_vertex_0500C488, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP1Triangle( 0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500C500 - 0x0500C530
const Gfx snowman_seg5_dl_0500C500[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(snowman_seg5_dl_0500C4C8),
    gsSPEndDisplayList(),
};

// 0x0500C530
static const Vtx snowman_seg5_vertex_0500C530[] = {
    {{{     0,     77,      0}, 0, ST_B(32-0.5,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{   -77,    -77,      0}, 0, ST_B(  -0.5,     64), {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,    -77,      0}, 0, ST_B(32-0.5,     64), {0xff, 0xff, 0xff, 0xff}}},
    {{{   -77,     77,      0}, 0, ST_B(  -0.5,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{    77,     77,      0}, 0, ST_B(32+0.5,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,    -77,      0}, 0, ST_B(   0.5,     64), {0xff, 0xff, 0xff, 0xff}}},
    {{{    77,    -77,      0}, 0, ST_B(32+0.5,     64), {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,     77,      0}, 0, ST_B(   0.5,      0), {0xff, 0xff, 0xff, 0xff}}},
};

// 0x0500C5B0 - 0x0500C5E8
const Gfx snowman_seg5_dl_0500C5B0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snowman_seg5_texture_left_side),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(snowman_seg5_vertex_0500C530, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snowman_seg5_texture_right_side),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500C620 - 0x0500C698
const Gfx snowman_seg5_dl_0500C620[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(snowman_seg5_dl_0500C5B0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x0500C698
static const Vtx snowman_seg5_vertex_0500C698[] = {
    {{{    69,    192,   -133}, 0, {  -370,   -440}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   -64,    230,      0}, 0, {  1472,   1328}, {0xff, 0xff, 0xff, 0xff}}},
    {{{    69,    230,      0}, 0, {  1472,   -440}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   -64,    192,   -133}, 0, {  -370,   1328}, {0xff, 0xff, 0xff, 0xff}}},
    {{{    69,    230,      0}, 0, {  -370,   -440}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   -64,    192,    133}, 0, {  1472,   1328}, {0xff, 0xff, 0xff, 0xff}}},
    {{{    69,    192,    133}, 0, {  1472,   -440}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   -64,    230,      0}, 0, {  -370,   1328}, {0xff, 0xff, 0xff, 0xff}}},
};

// 0x0500C718 - 0x0500C760
const Gfx snowman_seg5_dl_0500C718[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snowman_seg5_texture_eye),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(snowman_seg5_vertex_0500C698, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500C760 - 0x0500C7D0
const Gfx snowman_seg5_dl_0500C760[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(snowman_seg5_dl_0500C718),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x0500C7D0
static const Lights1 snowman_seg5_lights_0500C7D0 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0500C7E8
static const Vtx snowman_seg5_vertex_0500C7E8[] = {
    {{{     3,    -44,    -24}, 0, {   672,   1148}, {0xc1, 0xb9, 0xad, 0xff}}},
    {{{   105,    -64,    -17}, 0, {   720,    626}, {0x31, 0xca, 0x99, 0xff}}},
    {{{   116,   -102,     11}, 0, {   888,    570}, {0x2d, 0x8c, 0xeb, 0xff}}},
    {{{    -4,      4,    -29}, 0, {   458,   1184}, {0xad, 0x03, 0xa1, 0xff}}},
    {{{    96,    -30,    -36}, 0, {   578,    662}, {0x1e, 0xde, 0x8a, 0xff}}},
    {{{    97,     16,    -36}, 0, {   364,    654}, {0x13, 0x2a, 0x8a, 0xff}}},
    {{{   208,    -42,     25}, 0, {   588,     84}, {0x57, 0xa8, 0x19, 0xff}}},
    {{{   128,    -61,      9}, 0, {   704,    502}, {0x69, 0xbf, 0x1b, 0xff}}},
    {{{    56,    -20,     36}, 0, {   546,    864}, {0x02, 0xf8, 0x7e, 0xff}}},
    {{{   133,     90,     32}, 0, {    20,    460}, {0x13, 0x52, 0x5e, 0xff}}},
    {{{   215,     42,     28}, 0, {   206,     32}, {0x45, 0x40, 0xac, 0xff}}},
    {{{    69,    -56,     36}, 0, {   704,    816}, {0x04, 0xe8, 0x7c, 0xff}}},
    {{{    -2,     45,    -14}, 0, {   270,   1168}, {0xa1, 0x42, 0xce, 0xff}}},
    {{{    33,     83,     26}, 0, {    88,    976}, {0xcd, 0x72, 0x0f, 0xff}}},
    {{{   107,     64,     -2}, 0, {   144,    596}, {0x0f, 0x52, 0xa1, 0xff}}},
    {{{    36,    -86,     11}, 0, {   850,    992}, {0xbd, 0xa8, 0x3d, 0xff}}},
};

// 0x0500C8E8
static const Vtx snowman_seg5_vertex_0500C8E8[] = {
    {{{    69,    -56,     36}, 0, {   704,    816}, {0x04, 0xe8, 0x7c, 0xff}}},
    {{{    56,    -20,     36}, 0, {   544,    864}, {0x02, 0xf8, 0x7e, 0xff}}},
    {{{     6,      0,     28}, 0, { 15<<5,   1124}, {0xa3, 0xf5, 0x55, 0xff}}},
    {{{    33,     83,     26}, 0, {    88,    976}, {0xcd, 0x72, 0x0f, 0xff}}},
    {{{    -4,      4,    -29}, 0, {   458,   1184}, {0xad, 0x03, 0xa1, 0xff}}},
    {{{     3,    -44,    -24}, 0, {   672,   1148}, {0xc1, 0xb9, 0xad, 0xff}}},
    {{{    -2,     45,    -14}, 0, {   270,   1168}, {0xa1, 0x42, 0xce, 0xff}}},
    {{{    36,    -86,     11}, 0, {   850,    992}, {0xbd, 0xa8, 0x3d, 0xff}}},
    {{{   116,   -102,     11}, 0, {   888,    570}, {0x2d, 0x8c, 0xeb, 0xff}}},
};

// 0x0500C978 - 0x0500CAA8
const Gfx snowman_seg5_dl_0500C978[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snowman_seg5_texture_mitten),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&snowman_seg5_lights_0500C7D0.l, 1),
    gsSPLight(&snowman_seg5_lights_0500C7D0.a, 2),
    gsSPVertex(snowman_seg5_vertex_0500C7E8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 4,  1,  0, 0x0,  5,  4,  3, 0x0),
    gsSP2Triangles( 5,  6,  4, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 7,  1,  4, 0x0,  7,  6,  8, 0x0),
    gsSP2Triangles( 9,  8,  6, 0x0,  9,  6, 10, 0x0),
    gsSP2Triangles( 5, 10,  6, 0x0,  7,  2,  1, 0x0),
    gsSP2Triangles( 8, 11,  7, 0x0, 11,  2,  7, 0x0),
    gsSP2Triangles( 5, 12, 13, 0x0, 13, 14,  5, 0x0),
    gsSP2Triangles( 5,  3, 12, 0x0,  5, 14, 10, 0x0),
    gsSP2Triangles(10, 14,  9, 0x0, 13,  9, 14, 0x0),
    gsSP2Triangles( 8,  9, 13, 0x0,  2, 15,  0, 0x0),
    gsSPVertex(snowman_seg5_vertex_0500C8E8, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  1, 0x0),
    gsSP2Triangles( 4,  5,  2, 0x0,  2,  6,  4, 0x0),
    gsSP2Triangles( 2,  5,  7, 0x0,  0,  2,  7, 0x0),
    gsSP2Triangles( 3,  6,  2, 0x0,  7,  8,  0, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500CAA8 - 0x0500CB08
const Gfx snowman_seg5_dl_0500CAA8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(snowman_seg5_dl_0500C978),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x0500CB08
static const Vtx snowman_seg5_vertex_0500CB08[] = {
    {{{     0,     56,      0}, 0, ST_B(    32,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{   -56,    -56,      0}, 0, ST_B(     0,     64), {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,    -56,      0}, 0, ST_B(    32,     64), {0xff, 0xff, 0xff, 0xff}}},
    {{{   -56,     56,      0}, 0, ST_B(     0,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{    56,     56,      0}, 0, ST_B(    32,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,    -56,      0}, 0, ST_B(     0,     64), {0xff, 0xff, 0xff, 0xff}}},
    {{{    56,    -56,      0}, 0, ST_B(    32,     64), {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,     56,      0}, 0, ST_B(     0,      0), {0xff, 0xff, 0xff, 0xff}}},
};

// 0x0500CB88 - 0x0500CBC0
const Gfx snowman_seg5_dl_0500CB88[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snowman_seg5_texture_left_side),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(snowman_seg5_vertex_0500CB08, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snowman_seg5_texture_right_side),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500CBF8 - 0x0500CC70
const Gfx snowman_seg5_dl_0500CBF8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(snowman_seg5_dl_0500CB88),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x0500CC70
static const Vtx snowman_seg5_vertex_0500CC70[] = {
    {{{   -90,    210,    -56}, 0, ST_B(     0,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{  -134,    182,    -56}, 0, ST_B(     0,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{  -134,    182,     56}, 0, ST_B(    32,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{   -90,    210,     56}, 0, ST_B(    32,      0), {0xff, 0xff, 0xff, 0xff}}},
};

// 0x0500CCB0 - 0x0500CCE8
const Gfx snowman_seg5_sub_dl_mouth[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snowman_seg5_texture_mouth),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(snowman_seg5_vertex_0500CC70, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500CCE8 - 0x0500CD58
const Gfx snowman_seg5_dl_mouth[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(snowman_seg5_sub_dl_mouth),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
