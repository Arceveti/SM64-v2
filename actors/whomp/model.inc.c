// Whomp

// 0x0601C360
ALIGNED8 static const Texture whomp_seg6_texture_back[] = {
#include "actors/whomp/whomp_back.rgba16.inc.c"
};

// 0x0601D360
ALIGNED8 static const Texture whomp_seg6_texture_face[] = {
#include "actors/whomp/whomp_face.rgba16.inc.c"
};

// 0x0601D360
ALIGNED8 static const Texture whomp_seg6_texture_hand[] = {
#include "actors/whomp/whomp_hand.rgba16.inc.c"
};

// 0x0601EB60
ALIGNED8 static const Texture whomp_seg6_texture_surface[] = {
#include "actors/whomp/whomp_surface.rgba16.inc.c"
};

// 0x0601F360
static const Lights1 whomp_seg6_lights = gdSPDefLights1(
    0x4c, 0x4c, 0x4c,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0601F378
static const Vtx whomp_seg6_vertex_sides[] = {
    {{{   -51,    610,   -202}, 0, ST_B(    16,     32), {0x00, 0x7e, 0x00, 0xff}}},
    {{{   -51,    610,    202}, 0, ST_B(     0,     32), {0x00, 0x7e, 0x00, 0xff}}},
    {{{  1559,    600,    202}, 0, ST_B(     0,    -32), {0x00, 0x7e, 0x00, 0xff}}},
    {{{  1559,    600,   -202}, 0, ST_B(     0,     11), {0x7e, 0x00, 0x00, 0xff}}},
    {{{  1551,   -610,    202}, 0, ST_B(    64,     32), {0x7e, 0x00, 0x00, 0xff}}},
    {{{  1551,   -610,   -202}, 0, ST_B(    64,     11), {0x7e, 0x00, 0x00, 0xff}}},
    {{{  1559,    600,    202}, 0, ST_B(     0,     32), {0x7e, 0x00, 0x00, 0xff}}},
    {{{   -60,   -600,   -202}, 0, ST_B(    64,     11), {0x82, 0x00, 0x00, 0xff}}},
    {{{   -51,    610,    202}, 0, ST_B(     0,     32), {0x82, 0x00, 0x00, 0xff}}},
    {{{   -51,    610,   -202}, 0, ST_B(     0,     11), {0x82, 0x00, 0x00, 0xff}}},
    {{{   -60,   -600,    202}, 0, ST_B(    64,     32), {0x82, 0x00, 0x00, 0xff}}},
    {{{   -60,   -600,    202}, 0, ST_B(     0,     32), {0x00, 0x82, 0x00, 0xff}}},
    {{{   -60,   -600,   -202}, 0, ST_B(    16,     32), {0x00, 0x82, 0x00, 0xff}}},
    {{{  1551,   -610,   -202}, 0, ST_B(    16,    -32), {0x00, 0x82, 0x00, 0xff}}},
    {{{  1551,   -610,    202}, 0, ST_B(     0,    -32), {0x00, 0x82, 0x00, 0xff}}},
    {{{  1559,    600,   -202}, 0, ST_B(    16,    -32), {0x00, 0x7e, 0x00, 0xff}}},
};

// 0x0601F478
static const Vtx whomp_seg6_vertex_back[] = {
    {{{   -60,   -600,   -202}, 0, ST_B(     0,     64), {0x00, 0x00, 0x81, 0xff}}},
    {{{  1559,    600,   -202}, 0, ST_B(    32,      0), {0x00, 0x00, 0x81, 0xff}}},
    {{{  1551,   -610,   -202}, 0, ST_B(     0,      0), {0x00, 0x00, 0x81, 0xff}}},
    {{{   -51,    610,   -202}, 0, ST_B(    32,     64), {0x00, 0x00, 0x81, 0xff}}},
};

// 0x0601F4B8
static const Vtx whomp_seg6_vertex_face[] = {
    {{{   -51,    610,    202}, 0, ST_B(     0,     64), {0x00, 0x00, 0x7f, 0xff}}},
    {{{   -60,   -600,    202}, 0, ST_B(    32,     64), {0x00, 0x00, 0x7f, 0xff}}},
    {{{  1551,   -610,    202}, 0, ST_B(    32,      0), {0x00, 0x00, 0x7f, 0xff}}},
    {{{  1559,    600,    202}, 0, ST_B(     0,      0), {0x00, 0x00, 0x7f, 0xff}}},
};

// 0x0601F4F8 - 0x0601F570
const Gfx whomp_seg6_dl_sides[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, whomp_seg6_texture_surface),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&whomp_seg6_lights.l, 1),
    gsSPLight(&whomp_seg6_lights.a, 2),
    gsSPVertex(whomp_seg6_vertex_sides, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0,  2, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x0601F570 - 0x0601F5A8
const Gfx whomp_seg6_dl_back[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, whomp_seg6_texture_back),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 64), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(whomp_seg6_vertex_back, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0601F5A8 - 0x0601F5E0
const Gfx whomp_seg6_dl_face[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, whomp_seg6_texture_face),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 64), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(whomp_seg6_vertex_face, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0601F5E0 - 0x0601F678
const Gfx whomp_seg6_dl_body[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, (G_TX_WRAP | G_TX_NOMIRROR), G_TX_NOMASK, G_TX_NOLOD, (G_TX_WRAP | G_TX_NOMIRROR), G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, (G_TX_WRAP | G_TX_NOMIRROR), 5, G_TX_NOLOD, (G_TX_WRAP | G_TX_NOMIRROR), 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, ((32 - 1) << G_TEXTURE_IMAGE_FRAC), ((32 - 1) << G_TEXTURE_IMAGE_FRAC)),
    gsSPDisplayList(whomp_seg6_dl_sides),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, ((32 - 1) << G_TEXTURE_IMAGE_FRAC), ((64 - 1) << G_TEXTURE_IMAGE_FRAC)),
    gsSPDisplayList(whomp_seg6_dl_back),
    gsSPDisplayList(whomp_seg6_dl_face),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

// 0x0601F690
static const Vtx whomp_seg6_vertex_0601F690[] = {
    {{{   290,      0,     85}, 0, { 30<<5,      0}, {0xed, 0x1c, 0x7a, 0xff}}},
    {{{   -10,     35,     13}, 0, {   246,    976}, {0xed, 0x6a, 0x41, 0xff}}},
    {{{   -10,      0,     38}, 0, {   672,    976}, {0xed, 0xe3, 0x79, 0xff}}},
    {{{   290,     80,     28}, 0, { 30<<5,      0}, {0xed, 0x7d, 0x08, 0xff}}},
    {{{   -10,     21,    -27}, 0, {   246,    976}, {0xed, 0x5e, 0xae, 0xff}}},
    {{{   -10,     35,     13}, 0, {   672,    976}, {0xed, 0x6a, 0x41, 0xff}}},
    {{{   290,     49,    -65}, 0, {     0,      0}, {0xed, 0x2f, 0x8c, 0xff}}},
    {{{   290,     49,    -65}, 0, { 30<<5,      0}, {0xed, 0x2f, 0x8c, 0xff}}},
    {{{   -10,    -20,    -27}, 0, {   246,    976}, {0xed, 0xd1, 0x8c, 0xff}}},
    {{{   -10,     21,    -27}, 0, {   672,    976}, {0xed, 0x5e, 0xae, 0xff}}},
    {{{   290,    -48,    -65}, 0, {     0,      0}, {0xed, 0xa2, 0xae, 0xff}}},
    {{{   290,    -79,     28}, 0, { 30<<5,      0}, {0xed, 0x95, 0x41, 0xff}}},
    {{{   290,      0,     85}, 0, {     0,      0}, {0xed, 0x1c, 0x7a, 0xff}}},
    {{{   -10,      0,     38}, 0, {   246,    976}, {0xed, 0xe3, 0x79, 0xff}}},
    {{{   -10,    -34,     13}, 0, {   672,    976}, {0xed, 0x83, 0x08, 0xff}}},
};

// 0x0601F780
static const Vtx whomp_seg6_vertex_0601F780[] = {
    {{{   290,    -48,    -65}, 0, { 30<<5,      0}, {0xed, 0xa2, 0xae, 0xff}}},
    {{{   290,    -79,     28}, 0, {     0,      0}, {0xed, 0x95, 0x41, 0xff}}},
    {{{   -10,    -34,     13}, 0, {   246,    976}, {0xed, 0x83, 0x08, 0xff}}},
    {{{   290,      0,     85}, 0, { 30<<5,      0}, {0xed, 0x1c, 0x7a, 0xff}}},
    {{{   290,     80,     28}, 0, {     0,      0}, {0xed, 0x7d, 0x08, 0xff}}},
    {{{   -10,     35,     13}, 0, {   246,    976}, {0xed, 0x6a, 0x41, 0xff}}},
    {{{   -10,    -20,    -27}, 0, {   672,    976}, {0xed, 0xd1, 0x8c, 0xff}}},
};

// 0x0601F7F0 - 0x0601F880
const Gfx whomp_seg6_dl_0601F7F0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, whomp_seg6_texture_surface),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&whomp_seg6_lights.l, 1),
    gsSPLight(&whomp_seg6_lights.a, 2),
    gsSPVertex(whomp_seg6_vertex_0601F690, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle( 11, 13, 14, 0x0),
    gsSPVertex(whomp_seg6_vertex_0601F780, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle(  0,  2,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x0601F880 - 0x0601F8E0
const Gfx whomp_seg6_dl_0601F880[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, (G_TX_WRAP | G_TX_NOMIRROR), G_TX_NOMASK, G_TX_NOLOD, (G_TX_WRAP | G_TX_NOMIRROR), G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, (G_TX_WRAP | G_TX_NOMIRROR), 5, G_TX_NOLOD, (G_TX_WRAP | G_TX_NOMIRROR), 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, ((32 - 1) << G_TEXTURE_IMAGE_FRAC), ((32 - 1) << G_TEXTURE_IMAGE_FRAC)),
    gsSPDisplayList(whomp_seg6_dl_0601F7F0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x0601F8F8
static const Vtx whomp_seg6_vertex_0601F8F8[] = {
    {{{   -10,      0,    -37}, 0, {   246,    976}, {0xed, 0x1c, 0x86, 0xff}}},
    {{{   290,     80,    -26}, 0, { 30<<5,      0}, {0xed, 0x6a, 0xbf, 0xff}}},
    {{{   290,      0,    -84}, 0, {     0,      0}, {0xed, 0xe2, 0x87, 0xff}}},
    {{{   -10,     35,    -12}, 0, {   246,    976}, {0xed, 0x7d, 0xf8, 0xff}}},
    {{{   290,     49,     66}, 0, { 30<<5,      0}, {0xed, 0x5e, 0x52, 0xff}}},
    {{{   290,     80,    -26}, 0, {     0,      0}, {0xed, 0x6a, 0xbf, 0xff}}},
    {{{   -10,     21,     28}, 0, {   672,    976}, {0xed, 0x2f, 0x74, 0xff}}},
    {{{   -10,     21,     28}, 0, {   246,    976}, {0xed, 0x2f, 0x74, 0xff}}},
    {{{   290,    -48,     66}, 0, { 30<<5,      0}, {0xed, 0xd1, 0x74, 0xff}}},
    {{{   290,     49,     66}, 0, {     0,      0}, {0xed, 0x5e, 0x52, 0xff}}},
    {{{   -10,    -20,     28}, 0, {   672,    976}, {0xed, 0xa2, 0x52, 0xff}}},
    {{{   -10,    -34,    -12}, 0, {   246,    976}, {0xed, 0x95, 0xc0, 0xff}}},
    {{{   -10,      0,    -37}, 0, {   672,    976}, {0xed, 0x1c, 0x86, 0xff}}},
    {{{   290,      0,    -84}, 0, { 30<<5,      0}, {0xed, 0xe2, 0x87, 0xff}}},
    {{{   290,    -79,    -26}, 0, {     0,      0}, {0xed, 0x83, 0xf9, 0xff}}},
};

// 0x0601F9E8
static const Vtx whomp_seg6_vertex_0601F9E8[] = {
    {{{   -10,    -20,     28}, 0, {   246,    976}, {0xed, 0xa2, 0x52, 0xff}}},
    {{{   -10,    -34,    -12}, 0, {   672,    976}, {0xed, 0x95, 0xc0, 0xff}}},
    {{{   290,    -79,    -26}, 0, { 30<<5,      0}, {0xed, 0x83, 0xf9, 0xff}}},
    {{{   -10,      0,    -37}, 0, {   246,    976}, {0xed, 0x1c, 0x86, 0xff}}},
    {{{   -10,     35,    -12}, 0, {   672,    976}, {0xed, 0x7d, 0xf8, 0xff}}},
    {{{   290,     80,    -26}, 0, { 30<<5,      0}, {0xed, 0x6a, 0xbf, 0xff}}},
    {{{   290,    -48,     66}, 0, {     0,      0}, {0xed, 0xd1, 0x74, 0xff}}},
};

// 0x0601FA58 - 0x0601FAE8
const Gfx whomp_seg6_dl_0601FA58[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, whomp_seg6_texture_surface),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&whomp_seg6_lights.l, 1),
    gsSPLight(&whomp_seg6_lights.a, 2),
    gsSPVertex(whomp_seg6_vertex_0601F8F8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle( 11, 13, 14, 0x0),
    gsSPVertex(whomp_seg6_vertex_0601F9E8, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle(  0,  2,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x0601FAE8 - 0x0601FB48
const Gfx whomp_seg6_dl_0601FAE8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, (G_TX_WRAP | G_TX_NOMIRROR), G_TX_NOMASK, G_TX_NOLOD, (G_TX_WRAP | G_TX_NOMIRROR), G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, (G_TX_WRAP | G_TX_NOMIRROR), 5, G_TX_NOLOD, (G_TX_WRAP | G_TX_NOMIRROR), 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, ((32 - 1) << G_TEXTURE_IMAGE_FRAC), ((32 - 1) << G_TEXTURE_IMAGE_FRAC)),
    gsSPDisplayList(whomp_seg6_dl_0601FA58),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x0601FB48
static const Vtx whomp_seg6_vertex_hand_1[] = {
    {{{   -38,    -38,      0}, 0, ST_B(     0,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{    38,    -38,      0}, 0, ST_B(    32,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{    38,     38,      0}, 0, ST_B(    32,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{   -38,     38,      0}, 0, ST_B(     0,      0), {0xff, 0xff, 0xff, 0xff}}},
};

// 0x0601FB88 - 0x0601FBC0
const Gfx whomp_seg6_sub_dl_hand_1[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, whomp_seg6_texture_hand),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(whomp_seg6_vertex_hand_1, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0601FBC0 - 0x0601FC30
const Gfx whomp_seg6_dl_hand_1[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, (G_TX_WRAP | G_TX_NOMIRROR), G_TX_NOMASK, G_TX_NOLOD, (G_TX_WRAP | G_TX_NOMIRROR), G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, ((32 - 1) << G_TEXTURE_IMAGE_FRAC), ((32 - 1) << G_TEXTURE_IMAGE_FRAC)),
    gsSPDisplayList(whomp_seg6_sub_dl_hand_1),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x0601FC30
static const Vtx whomp_seg6_vertex_hand_2[] = {
    {{{   -38,    -38,      0}, 0, ST_B(     0,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{    38,    -38,      0}, 0, ST_B(    32,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{    38,     38,      0}, 0, ST_B(    32,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{   -38,     38,      0}, 0, ST_B(     0,      0), {0xff, 0xff, 0xff, 0xff}}},
};

// 0x0601FC70 - 0x0601FCA8
const Gfx whomp_seg6_sub_dl_hand_2[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, whomp_seg6_texture_hand),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(whomp_seg6_vertex_hand_2, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0601FCA8 - 0x0601FD18
const Gfx whomp_seg6_dl_hand_2[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, (G_TX_WRAP | G_TX_NOMIRROR), G_TX_NOMASK, G_TX_NOLOD, (G_TX_WRAP | G_TX_NOMIRROR), G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, ((32 - 1) << G_TEXTURE_IMAGE_FRAC), ((32 - 1) << G_TEXTURE_IMAGE_FRAC)),
    gsSPDisplayList(whomp_seg6_sub_dl_hand_2),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x0601FD30
static const Vtx whomp_seg6_vertex_0601FD30[] = {
    {{{   174,    183,    177}, 0, {  1364,    112}, {0x01, 0x3e, 0x6e, 0xff}}},
    {{{   180,    256,      2}, 0, {   496,    -32}, {0x46, 0x69, 0x00, 0xff}}},
    {{{    22,    158,      2}, 0, {   496,    160}, {0x9b, 0x4c, 0xff, 0xff}}},
    {{{   -28,    -89,      2}, 0, {   496,    658}, {0x84, 0xe7, 0x00, 0xff}}},
    {{{   177,    182,   -171}, 0, {  -376,    112}, {0xc9, 0x39, 0x9d, 0xff}}},
    {{{   154,   -260,      2}, 0, {   496,  31<<5}, {0xe9, 0x84, 0x01, 0xff}}},
    {{{   158,   -144,    202}, 0, {  1482,    768}, {0x38, 0xc6, 0x61, 0xff}}},
    {{{   161,   -152,   -190}, 0, {  -470,    784}, {0x71, 0xdf, 0xd3, 0xff}}},
    {{{   161,   -152,   -190}, 0, {     0,    768}, {0x71, 0xdf, 0xd3, 0xff}}},
    {{{   174,    183,    177}, 0, {   912,    104}, {0x01, 0x3e, 0x6e, 0xff}}},
    {{{   158,   -144,    202}, 0, {   976,    756}, {0x38, 0xc6, 0x61, 0xff}}},
    {{{   180,    256,      2}, 0, { 15<<5,    -48}, {0x46, 0x69, 0x00, 0xff}}},
    {{{   177,    182,   -171}, 0, {    48,    104}, {0xc9, 0x39, 0x9d, 0xff}}},
    {{{   154,   -260,      2}, 0, { 15<<5,  31<<5}, {0xe9, 0x84, 0x01, 0xff}}},
};

// 0x0601FE10 - 0x0601FEA8
const Gfx whomp_seg6_dl_0601FE10[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, whomp_seg6_texture_surface),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&whomp_seg6_lights.l, 1),
    gsSPLight(&whomp_seg6_lights.a, 2),
    gsSPVertex(whomp_seg6_vertex_0601FD30, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 2,  1,  4, 0x0,  4,  3,  2, 0x0),
    gsSP2Triangles( 5,  6,  3, 0x0,  3,  6,  0, 0x0),
    gsSP2Triangles( 3,  7,  5, 0x0,  4,  7,  3, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles( 8, 12, 11, 0x0,  8, 10, 13, 0x0),
    gsSPEndDisplayList(),
};

// 0x0601FEA8 - 0x0601FF08
const Gfx whomp_seg6_dl_0601FEA8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(whomp_seg6_dl_0601FE10),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x0601FF20
static const Vtx whomp_seg6_vertex_0601FF20[] = {
    {{{   154,   -260,     -1}, 0, { 15<<5,  31<<5}, {0x6e, 0xc3, 0xff, 0xff}}},
    {{{   174,    183,   -176}, 0, {  -112,    112}, {0x01, 0x3e, 0x92, 0xff}}},
    {{{   180,    256,     -1}, 0, { 15<<5,    -32}, {0x46, 0x69, 0x00, 0xff}}},
    {{{   158,   -144,   -200}, 0, {  -188,    768}, {0xdf, 0xc4, 0x96, 0xff}}},
    {{{    22,    158,     -1}, 0, { 15<<5,    160}, {0x9b, 0x4c, 0x01, 0xff}}},
    {{{   -28,    -89,     -1}, 0, { 15<<5,    656}, {0x84, 0xe7, 0x00, 0xff}}},
    {{{   177,    182,    172}, 0, { 33<<5,    112}, {0x03, 0x3d, 0x6f, 0xff}}},
    {{{   161,   -152,    192}, 0, {  1112,    784}, {0xe1, 0xc2, 0x6a, 0xff}}},
};

// 0x0601FFA0 - 0x06020038
const Gfx whomp_seg6_dl_0601FFA0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, whomp_seg6_texture_surface),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&whomp_seg6_lights.l, 1),
    gsSPLight(&whomp_seg6_lights.a, 2),
    gsSPVertex(whomp_seg6_vertex_0601FF20, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  2,  1, 0x0,  1,  5,  4, 0x0),
    gsSP2Triangles( 1,  3,  5, 0x0,  5,  3,  0, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  0,  7,  5, 0x0),
    gsSP2Triangles( 5,  7,  6, 0x0,  6,  2,  4, 0x0),
    gsSP2Triangles( 0,  2,  6, 0x0,  0,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x06020038 - 0x06020098
const Gfx whomp_seg6_dl_06020038[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, (G_TX_WRAP | G_TX_NOMIRROR), G_TX_NOMASK, G_TX_NOLOD, (G_TX_WRAP | G_TX_NOMIRROR), G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, (G_TX_WRAP | G_TX_NOMIRROR), 5, G_TX_NOLOD, (G_TX_WRAP | G_TX_NOMIRROR), 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, ((32 - 1) << G_TEXTURE_IMAGE_FRAC), ((32 - 1) << G_TEXTURE_IMAGE_FRAC)),
    gsSPDisplayList(whomp_seg6_dl_0601FFA0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
