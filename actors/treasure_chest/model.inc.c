// Treasure Chest

// 0x06013F90
static const Lights1 treasure_chest_seg6_lights_06013F90 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x06013FA8
ALIGNED8 static const Texture treasure_chest_seg6_texture_lock[] = {
#include "actors/treasure_chest/treasure_chest_lock.rgba16.inc.c"
};

// 0x060147A8
ALIGNED8 static const Texture treasure_chest_seg6_texture_side[] = {
#include "actors/treasure_chest/treasure_chest_side.rgba16.inc.c"
};

// 0x06014FA8
ALIGNED8 static const Texture treasure_chest_seg6_texture_lock_top[] = {
#include "actors/treasure_chest/treasure_chest_lock_top.rgba16.inc.c"
};

// 0x060157A8
ALIGNED8 static const Texture treasure_chest_seg6_texture_front[] = {
#include "actors/treasure_chest/treasure_chest_front.rgba16.inc.c"
};

// 0x060167A8
static const Vtx treasure_chest_seg6_vertex_060167A8[] = {
    {{{    20,    102,     87}, 0, { 31<<5,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   -20,     72,     87}, 0, {     0,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{    20,     72,     87}, 0, { 31<<5,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   -20,    102,     87}, 0, {     0,      0}, {0x00, 0x00, 0x7f, 0xff}}},
};

// 0x060167E8
static const Vtx treasure_chest_seg6_vertex_060167E8[] = {
    {{{    20,     72,     77}, 0, { 31<<5,  31<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   -20,     72,     87}, 0, {     0,      0}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   -20,     72,     77}, 0, {     0,  31<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{     0,    102,     77}, 0, { 15<<5,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{    20,    102,     87}, 0, {     0,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{    20,    102,     77}, 0, {     0,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   -20,    102,     87}, 0, { 31<<5,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   -20,    102,     77}, 0, { 31<<5,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   -20,     72,     77}, 0, {     0,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   -20,    102,     87}, 0, { 31<<5,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   -20,    102,     77}, 0, {     0,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   -20,     72,     87}, 0, { 31<<5,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{    20,     72,     87}, 0, { 31<<5,      0}, {0x00, 0x81, 0x00, 0xff}}},
    {{{    20,    102,     77}, 0, { 31<<5,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{    20,     72,     87}, 0, {     0,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{    20,     72,     77}, 0, { 31<<5,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
};

// 0x060168E8
static const Vtx treasure_chest_seg6_vertex_060168E8[] = {
    {{{    20,    102,     77}, 0, { 31<<5,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{    20,    102,     87}, 0, {     0,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{    20,     72,     87}, 0, {     0,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
};

// 0x06016918
static const Vtx treasure_chest_seg6_vertex_06016918[] = {
    {{{    77,    102,    -51}, 0, {     0,  -1736}, {0x81, 0x00, 0x00, 0xff}}},
    {{{    77,     20,    -51}, 0, {     0,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{    77,     20,     51}, 0, {  3374,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   -77,     20,    -51}, 0, {     0,  -2416}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{    77,     20,     51}, 0, {159<<5,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{    77,     20,    -51}, 0, {159<<5,  -2416}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   -77,     20,     51}, 0, {     0,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   -77,    102,     51}, 0, {     0,  -1736}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   -77,     20,    -51}, 0, {  3374,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   -77,    102,    -51}, 0, {  3374,  -1736}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   -77,     20,     51}, 0, {     0,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{    77,    102,     51}, 0, {     0,  -1736}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   -77,     20,     51}, 0, {159<<5,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   -77,    102,     51}, 0, {159<<5,  -1736}, {0x00, 0x00, 0x81, 0xff}}},
    {{{    77,     20,     51}, 0, {     0,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
};

// 0x06016A08
static const Vtx treasure_chest_seg6_vertex_06016A08[] = {
    {{{   -92,    102,    -77}, 0, {  5244,    960}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   -77,    102,    -51}, 0, {  4734,     48}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{    77,    102,    -51}, 0, {  -368,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{    77,    102,    -51}, 0, {     0,  -1736}, {0x81, 0x00, 0x00, 0xff}}},
    {{{    77,     20,     51}, 0, {  3374,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{    77,    102,     51}, 0, {  3374,  -1736}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   -77,    102,    -51}, 0, {     0,  -1736}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   -77,     20,    -51}, 0, {     0,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{    77,     20,    -51}, 0, {159<<5,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{    77,    102,    -51}, 0, {159<<5,  -1736}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   -77,    102,    -51}, 0, {  -544,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   -92,    102,    -77}, 0, { -1818,     64}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   -92,    102,     77}, 0, {  5844,     64}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   -77,    102,     51}, 0, {  4568,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{    92,    102,    -77}, 0, {  -880,    908}, {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x06016AF8
static const Vtx treasure_chest_seg6_vertex_06016AF8[] = {
    {{{    92,    102,    -77}, 0, {  6356,    960}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{    77,    102,    -51}, 0, {159<<5,     80}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{    77,    102,     51}, 0, {     0,     32}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{    92,    102,     77}, 0, { -1308,    880}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{    77,    102,     51}, 0, {  -544,     32}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   -92,    102,     77}, 0, {  7888,    944}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{    92,    102,     77}, 0, { -1308,    944}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   -77,    102,     51}, 0, {  7122,     32}, {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x06016B78
static const Vtx treasure_chest_seg6_vertex_06016B78[] = {
    {{{    92,      0,    -68}, 0, { 63<<5,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{    92,    102,      0}, 0, {   160,  -2392}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{    92,      0,      0}, 0, {   336,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{    92,    102,    -77}, 0, { 63<<5,  -2392}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{    92,    102,      0}, 0, {    64,  -2358}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{    92,    102,     77}, 0, {  1976,  -2358}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{    92,      0,     69}, 0, { 63<<5,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{    92,      0,      0}, 0, {   288,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   -92,    102,      0}, 0, {    96,  -2410}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   -92,    102,    -77}, 0, { 63<<5,  -2410}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   -92,      0,    -68}, 0, { 63<<5,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   -92,      0,      0}, 0, {   288,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   -92,      0,    -69}, 0, { 63<<5,  31<<5}, {0x00, 0xf7, 0x82, 0xff}}},
    {{{   -92,    102,    -77}, 0, { 63<<5,  -2416}, {0x00, 0xf7, 0x82, 0xff}}},
    {{{     0,    102,    -77}, 0, { -1664,  -2416}, {0x00, 0xf7, 0x82, 0xff}}},
    {{{     0,      0,    -69}, 0, { -1664,  31<<5}, {0x00, 0xf7, 0x82, 0xff}}},
};

// 0x06016C78
static const Vtx treasure_chest_seg6_vertex_06016C78[] = {
    {{{    92,      0,     69}, 0, { 63<<5,  31<<5}, {0x00, 0xf7, 0x7e, 0xff}}},
    {{{     0,    102,     77}, 0, { -1664,  -2416}, {0x00, 0xf7, 0x7e, 0xff}}},
    {{{     0,      0,     69}, 0, { -1664,  31<<5}, {0x00, 0xf7, 0x7e, 0xff}}},
    {{{   -92,      0,     69}, 0, { 63<<5,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   -92,    102,     77}, 0, {  2040,  -2428}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   -92,    102,      0}, 0, {   236,  -2428}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   -92,      0,      0}, 0, {   388,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{     0,    102,    -77}, 0, { -1664,  -2416}, {0x00, 0xf7, 0x82, 0xff}}},
    {{{    92,    102,    -77}, 0, { 63<<5,  -2416}, {0x00, 0xf7, 0x82, 0xff}}},
    {{{    92,      0,    -69}, 0, { 63<<5,  31<<5}, {0x00, 0xf7, 0x82, 0xff}}},
    {{{     0,      0,    -69}, 0, { -1664,  31<<5}, {0x00, 0xf7, 0x82, 0xff}}},
    {{{   -92,      0,     69}, 0, { 63<<5,  31<<5}, {0x00, 0xf7, 0x7e, 0xff}}},
    {{{   -92,    102,     77}, 0, { 63<<5,  -2416}, {0x00, 0xf7, 0x7e, 0xff}}},
    {{{    92,    102,     77}, 0, { 63<<5,  -2416}, {0x00, 0xf7, 0x7e, 0xff}}},
};

// 0x06016D58 - 0x06016DA0
const Gfx treasure_chest_seg6_dl_06016D58[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, treasure_chest_seg6_texture_lock),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&treasure_chest_seg6_lights_06013F90.l, 1),
    gsSPLight(&treasure_chest_seg6_lights_06013F90.a, 2),
    gsSPVertex(treasure_chest_seg6_vertex_060167A8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x06016DA0 - 0x06016E18
const Gfx treasure_chest_seg6_dl_06016DA0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, treasure_chest_seg6_texture_lock_top),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(treasure_chest_seg6_vertex_060167E8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  3,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles( 0, 12,  1, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(treasure_chest_seg6_vertex_060168E8, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x06016E18 - 0x06016EE0
const Gfx treasure_chest_seg6_dl_06016E18[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, treasure_chest_seg6_texture_side),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(treasure_chest_seg6_vertex_06016918, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(treasure_chest_seg6_vertex_06016A08, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(treasure_chest_seg6_vertex_06016AF8, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x06016EE0 - 0x06016F90
const Gfx treasure_chest_seg6_dl_06016EE0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, treasure_chest_seg6_texture_front),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(treasure_chest_seg6_vertex_06016B78, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(treasure_chest_seg6_vertex_06016C78, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  1, 11,  2, 0x0),
    gsSP2Triangles( 1, 12, 11, 0x0,  0, 13,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x06016F90 - 0x06017030
const Gfx treasure_chest_seg6_dl_06016F90[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(treasure_chest_seg6_dl_06016D58),
    gsSPDisplayList(treasure_chest_seg6_dl_06016DA0),
    gsSPDisplayList(treasure_chest_seg6_dl_06016E18),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(treasure_chest_seg6_dl_06016EE0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

// 0x06017030
static const Vtx treasure_chest_seg6_vertex_06017030[] = {
    {{{    92,      0,    154}, 0, {     0,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{    92,      0,      0}, 0, {159<<5,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{    92,     30,     27}, 0, {  4184,  -1024}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{    92,     46,     77}, 0, {  2524,  -2028}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{    92,     30,    128}, 0, {   864,  -1024}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   -92,     30,     27}, 0, {  1310,   -992}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   -92,     30,    128}, 0, {  6292,   -992}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   -92,     46,     77}, 0, {  3800,  -1978}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   -92,      0,      0}, 0, {     0,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   -92,      0,    154}, 0, {  7632,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   -74,     20,    128}, 0, {191<<5,  -2332}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   -74,     20,     27}, 0, {191<<5,  31<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{    74,     20,     27}, 0, {     0,  31<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{    74,     20,    128}, 0, {     0,  -2332}, {0x00, 0x81, 0x00, 0xff}}},
};

// 0x06017110
static const Vtx treasure_chest_seg6_vertex_06017110[] = {
    {{{   -92,      0,      0}, 0, { -1564,     32}, {0x00, 0x81, 0x00, 0xff}}},
    {{{    74,      0,     15}, 0, {  6714,    752}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   -74,      0,     15}, 0, {  -644,    752}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   -92,      0,      0}, 0, {  6180,     32}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   -74,      0,     15}, 0, {  5466,    902}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   -74,      0,    138}, 0, {  -274,    896}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   -92,      0,    154}, 0, {  -992,     24}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   -92,      0,    154}, 0, { -2176,    944}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   -74,      0,    138}, 0, { -1256,     80}, {0x00, 0x81, 0x00, 0xff}}},
    {{{    74,      0,    138}, 0, {191<<5,    -16}, {0x00, 0x81, 0x00, 0xff}}},
    {{{    92,      0,    154}, 0, {  7020,    828}, {0x00, 0x81, 0x00, 0xff}}},
    {{{    74,      0,     15}, 0, {  5590,     32}, {0x00, 0x81, 0x00, 0xff}}},
    {{{    92,      0,      0}, 0, {  6356,    896}, {0x00, 0x81, 0x00, 0xff}}},
    {{{    92,      0,    154}, 0, { -1308,    896}, {0x00, 0x81, 0x00, 0xff}}},
    {{{    74,      0,    138}, 0, {  -544,     32}, {0x00, 0x81, 0x00, 0xff}}},
};

// 0x06017200
static const Vtx treasure_chest_seg6_vertex_06017200[] = {
    {{{    74,      0,    138}, 0, { -3720,     16}, {0x81, 0x00, 0x00, 0xff}}},
    {{{    74,     20,     27}, 0, {  1206,    976}, {0x81, 0x00, 0x00, 0xff}}},
    {{{    74,      0,     15}, 0, {  1730,     32}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   -92,      0,      0}, 0, { -1564,     32}, {0x00, 0x81, 0x00, 0xff}}},
    {{{    92,      0,      0}, 0, {  7632,     32}, {0x00, 0x81, 0x00, 0xff}}},
    {{{    74,      0,     15}, 0, {  6714,    752}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   -74,      0,     15}, 0, { -4772,     16}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   -74,     20,     27}, 0, { -4174,    960}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   -74,     20,    128}, 0, {   944,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   -74,      0,    138}, 0, {  1532,     48}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{    74,      0,     15}, 0, { -3914,     64}, {0x00, 0xbf, 0x6c, 0xff}}},
    {{{   -74,     20,     27}, 0, { 31<<5,  31<<5}, {0x00, 0xbf, 0x6c, 0xff}}},
    {{{   -74,      0,     15}, 0, { 31<<5,     64}, {0x00, 0xbf, 0x6c, 0xff}}},
    {{{    74,     20,     27}, 0, { -3914,  31<<5}, {0x00, 0xbf, 0x6c, 0xff}}},
    {{{    74,     20,    128}, 0, { -3222,    960}, {0x81, 0x00, 0x00, 0xff}}},
};

// 0x060172F0
static const Vtx treasure_chest_seg6_vertex_060172F0[] = {
    {{{   -74,      0,    138}, 0, { -6024,    156}, {0x00, 0xc3, 0x91, 0xff}}},
    {{{    74,     20,    127}, 0, {  1162,    896}, {0x00, 0xc3, 0x91, 0xff}}},
    {{{    74,      0,    138}, 0, {  1212,    112}, {0x00, 0xc3, 0x91, 0xff}}},
    {{{   -74,     20,    127}, 0, { -6072,    940}, {0x00, 0xc3, 0x91, 0xff}}},
};

// 0x06017330
static const Vtx treasure_chest_seg6_vertex_06017330[] = {
    {{{   -20,     20,    136}, 0, {     0,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{    20,     20,    154}, 0, { 31<<5,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{    20,     20,    136}, 0, { 31<<5,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{    20,     20,    154}, 0, { 31<<5,      0}, {0x00, 0x38, 0x71, 0xff}}},
    {{{   -20,     20,    154}, 0, {     0,      0}, {0x00, 0x38, 0x71, 0xff}}},
    {{{   -20,      0,    164}, 0, {     0,  31<<5}, {0x00, 0x38, 0x71, 0xff}}},
    {{{    20,      0,    164}, 0, { 31<<5,  31<<5}, {0x00, 0x38, 0x71, 0xff}}},
    {{{    20,      0,    154}, 0, {   -32,    -80}, {0x00, 0x81, 0x00, 0xff}}},
    {{{    20,      0,    164}, 0, {     0,  31<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   -20,      0,    164}, 0, {   976,  31<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   -20,      0,    154}, 0, {   976,    -64}, {0x00, 0x81, 0x00, 0xff}}},
    {{{    20,     20,    136}, 0, { 31<<5,    -48}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{    20,      0,    164}, 0, {     0,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{    20,      0,    154}, 0, {   528,    980}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{    20,     20,    154}, 0, {    16,    -24}, {0x7f, 0x00, 0x00, 0xff}}},
};

// 0x06017420
static const Vtx treasure_chest_seg6_vertex_06017420[] = {
    {{{   -20,      0,    154}, 0, { 15<<5,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   -20,      0,    164}, 0, { 31<<5,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   -20,     20,    154}, 0, { 31<<5,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   -20,     20,    136}, 0, {     0,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   -20,     20,    154}, 0, {     0,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{    20,     20,    154}, 0, { 31<<5,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   -20,     20,    136}, 0, {    86,      0}, {0x81, 0x00, 0x00, 0xff}}},
};

// 0x06017490
static const Vtx treasure_chest_seg6_vertex_06017490[] = {
    {{{   -92,     46,     77}, 0, { 63<<5,  -1036}, {0x00, 0x78, 0x26, 0xff}}},
    {{{     0,     30,    128}, 0, { -1664,  31<<5}, {0x00, 0x78, 0x26, 0xff}}},
    {{{     0,     46,     77}, 0, { -1664,  -1036}, {0x00, 0x78, 0x26, 0xff}}},
    {{{     0,      0,    154}, 0, { -1664,   1992}, {0x00, 0x54, 0x5e, 0xff}}},
    {{{    92,     30,    128}, 0, { 63<<5,      0}, {0x00, 0x54, 0x5e, 0xff}}},
    {{{     0,     30,    128}, 0, { -1664,      0}, {0x00, 0x54, 0x5e, 0xff}}},
    {{{    92,      0,    154}, 0, { 63<<5,   1992}, {0x00, 0x54, 0x5e, 0xff}}},
    {{{   -92,     30,    128}, 0, { 63<<5,      0}, {0x00, 0x54, 0x5e, 0xff}}},
    {{{   -92,      0,    154}, 0, { 63<<5,   1992}, {0x00, 0x54, 0x5e, 0xff}}},
    {{{     0,     30,    128}, 0, { -1664,   1024}, {0x00, 0x78, 0x26, 0xff}}},
    {{{    92,     30,    128}, 0, { 63<<5,   1024}, {0x00, 0x78, 0x26, 0xff}}},
    {{{    92,     46,     77}, 0, { 63<<5,  -1066}, {0x00, 0x78, 0x26, 0xff}}},
    {{{     0,     46,     77}, 0, { -1664,  -1066}, {0x00, 0x78, 0x26, 0xff}}},
    {{{     0,     30,     27}, 0, { -1664,      0}, {0x00, 0x54, 0xa2, 0xff}}},
    {{{    92,     30,     27}, 0, { 63<<5,      0}, {0x00, 0x54, 0xa2, 0xff}}},
    {{{    92,      0,      0}, 0, { 63<<5,   1992}, {0x00, 0x54, 0xa2, 0xff}}},
};

// 0x06017590
static const Vtx treasure_chest_seg6_vertex_06017590[] = {
    {{{   -92,     46,     77}, 0, { 63<<5,  -1036}, {0x00, 0x78, 0x26, 0xff}}},
    {{{   -92,     30,    128}, 0, { 63<<5,  31<<5}, {0x00, 0x78, 0x26, 0xff}}},
    {{{     0,     30,    128}, 0, { -1664,  31<<5}, {0x00, 0x78, 0x26, 0xff}}},
    {{{     0,     46,     77}, 0, { -1664,  -1024}, {0x00, 0x78, 0xda, 0xff}}},
    {{{    92,     30,     27}, 0, { 63<<5,  31<<5}, {0x00, 0x78, 0xda, 0xff}}},
    {{{     0,     30,     27}, 0, { -1664,  31<<5}, {0x00, 0x78, 0xda, 0xff}}},
    {{{    92,     46,     77}, 0, { 63<<5,  -1024}, {0x00, 0x78, 0xda, 0xff}}},
    {{{   -92,     30,     27}, 0, { 63<<5,  31<<5}, {0x00, 0x78, 0xda, 0xff}}},
    {{{   -92,     46,     77}, 0, { 63<<5,  -1056}, {0x00, 0x78, 0xda, 0xff}}},
    {{{     0,     46,     77}, 0, { -1664,  -1056}, {0x00, 0x78, 0xda, 0xff}}},
    {{{     0,     30,     27}, 0, { -1664,      0}, {0x00, 0x54, 0xa2, 0xff}}},
    {{{    92,      0,      0}, 0, { 63<<5,   1992}, {0x00, 0x54, 0xa2, 0xff}}},
    {{{     0,      0,      0}, 0, { -1664,   1992}, {0x00, 0x54, 0xa2, 0xff}}},
    {{{   -92,      0,      0}, 0, { 63<<5,   1992}, {0x00, 0x54, 0xa2, 0xff}}},
    {{{   -92,     30,     27}, 0, { 63<<5,      0}, {0x00, 0x54, 0xa2, 0xff}}},
};

// 0x06017680 - 0x06017790
const Gfx treasure_chest_seg6_dl_06017680[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, treasure_chest_seg6_texture_side),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&treasure_chest_seg6_lights_06013F90.l, 1),
    gsSPLight(&treasure_chest_seg6_lights_06013F90.a, 2),
    gsSPVertex(treasure_chest_seg6_vertex_06017030, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 0,  3,  4, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  8,  9, 0x0,  5,  9,  6, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(treasure_chest_seg6_vertex_06017110, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(14, 11, 13, 0x0),
    gsSPVertex(treasure_chest_seg6_vertex_06017200, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0, 14,  1, 0x0),
    gsSPVertex(treasure_chest_seg6_vertex_060172F0, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x06017790 - 0x06017810
const Gfx treasure_chest_seg6_dl_06017790[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, treasure_chest_seg6_texture_lock_top),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(treasure_chest_seg6_vertex_06017330, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(treasure_chest_seg6_vertex_06017420, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 0,  2,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x06017810 - 0x060178C0
const Gfx treasure_chest_seg6_dl_06017810[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, treasure_chest_seg6_texture_front),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(treasure_chest_seg6_vertex_06017490, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  3,  5, 0x0),
    gsSP2Triangles( 7,  8,  3, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(treasure_chest_seg6_vertex_06017590, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9,  5, 0x0, 10, 11, 12, 0x0),
    gsSP2Triangles(13, 10, 12, 0x0, 13, 14, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x060178C0 - 0x06017958
const Gfx treasure_chest_seg6_dl_060178C0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(treasure_chest_seg6_dl_06017680),
    gsSPDisplayList(treasure_chest_seg6_dl_06017790),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(treasure_chest_seg6_dl_06017810),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
