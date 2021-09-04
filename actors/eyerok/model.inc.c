// Eyerok

// 0x05008D40
ALIGNED8 static const Texture eyerok_seg5_texture_bricks[] = {
#include "actors/eyerok/eyerok_bricks.rgba16.inc.c"
};

// 0x05009540
ALIGNED8 static const Texture eyerok_seg5_texture_eye_open[] = {
#include "actors/eyerok/eyerok_eye_open.rgba16.inc.c"
};

// 0x05009D40
ALIGNED8 static const Texture eyerok_seg5_texture_eye_mostly_open[] = {
#include "actors/eyerok/eyerok_eye_mostly_open.rgba16.inc.c"
};

// 0x0500A540
ALIGNED8 static const Texture eyerok_seg5_texture_eye_mostly_closed[] = {
#include "actors/eyerok/eyerok_eye_mostly_closed.rgba16.inc.c"
};

// 0x0500AD40
ALIGNED8 static const Texture eyerok_seg5_texture_eye_closed[] = {
#include "actors/eyerok/eyerok_eye_closed.rgba16.inc.c"
};

// 0x0500B540
static const Lights1 eyerok_seg5_lights_eyerok = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0500B558
static const Vtx eyerok_seg5_vertex_0500B558[] = {
    {{{   350,    200,   -200}, 0, ST_B(     0,      0), {0x00, 0x00, 0x81, 0xff}}},
    {{{   350,      0,   -200}, 0, ST_B(     0,     32), {0x00, 0x00, 0x81, 0xff}}},
    {{{     0,      0,   -200}, 0, ST_B(    54,     32), {0x00, 0x00, 0x81, 0xff}}},
    {{{   350,      0,      0}, 0, ST_B(     0,     32), {0x00, 0x00, 0x7f, 0xff}}},
    {{{   350,    200,      0}, 0, ST_B(     0,      0), {0x00, 0x00, 0x7f, 0xff}}},
    {{{     0,    200,      0}, 0, ST_B(    54,      0), {0x00, 0x00, 0x7f, 0xff}}},
    {{{     0,      0,      0}, 0, ST_B(    54,     32), {0x00, 0x00, 0x7f, 0xff}}},
    {{{   350,    200,   -200}, 0, ST_B(     0,      0), {0x7f, 0x00, 0x00, 0xff}}},
    {{{   350,      0,      0}, 0, ST_B(    32,     32), {0x7f, 0x00, 0x00, 0xff}}},
    {{{   350,      0,   -200}, 0, ST_B(    32,      0), {0x7f, 0x00, 0x00, 0xff}}},
    {{{   350,    200,      0}, 0, ST_B(     0,     32), {0x7f, 0x00, 0x00, 0xff}}},
    {{{   350,    200,   -200}, 0, ST_B(     0,      0), {0x00, 0x7f, 0x00, 0xff}}},
    {{{     0,    200,   -200}, 0, ST_B(    54,      0), {0x00, 0x7f, 0x00, 0xff}}},
    {{{   350,    200,      0}, 0, ST_B(     0,     32), {0x00, 0x7f, 0x00, 0xff}}},
    {{{     0,    200,      0}, 0, ST_B(    54,     32), {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x0500B648
static const Vtx eyerok_seg5_vertex_0500B648[] = {
    {{{   350,      0,   -200}, 0, ST_B(     0,      0), {0x00, 0x81, 0x00, 0xff}}},
    {{{   350,      0,      0}, 0, ST_B(     0,     32), {0x00, 0x81, 0x00, 0xff}}},
    {{{     0,      0,      0}, 0, ST_B(    54,     32), {0x00, 0x81, 0x00, 0xff}}},
    {{{     0,    200,   -200}, 0, ST_B(    54,      0), {0x00, 0x00, 0x81, 0xff}}},
    {{{   350,    200,   -200}, 0, ST_B(     0,      0), {0x00, 0x00, 0x81, 0xff}}},
    {{{     0,      0,   -200}, 0, ST_B(    54,     32), {0x00, 0x00, 0x81, 0xff}}},
    {{{     0,      0,   -200}, 0, ST_B(    54,      0), {0x00, 0x81, 0x00, 0xff}}},
};

// 0x0500B6B8 - 0x0500B748
const Gfx eyerok_seg5_dl_0500B6B8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, eyerok_seg5_texture_bricks),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&eyerok_seg5_lights_eyerok.l, 1),
    gsSPLight(&eyerok_seg5_lights_eyerok.a, 2),
    gsSPVertex(eyerok_seg5_vertex_0500B558, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  3,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(12, 14, 13, 0x0),
    gsSPVertex(eyerok_seg5_vertex_0500B648, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 6,  0,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500B748 - 0x0500B7B8
const Gfx eyerok_seg5_dl_0500B748[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(eyerok_seg5_dl_0500B6B8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

// 0x0500B7D0
static const Vtx eyerok_seg5_vertex_0500B7D0[] = {
    {{{   340,    200,   -200}, 0, {  1712,    -16}, {0x00, 0x00, 0x82, 0xff}}},
    {{{   340,      0,   -200}, 0, {  1712,  31<<5}, {0x00, 0x00, 0x82, 0xff}}},
    {{{     0,      0,   -200}, 0, {  3408,  31<<5}, {0x00, 0x00, 0x82, 0xff}}},
    {{{     0,      0,      0}, 0, {  3408,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   340,      0,      0}, 0, {  1712,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{     0,    200,      0}, 0, {  3408,    -16}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   340,    200,      0}, 0, {  1712,    -16}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{     0,    200,   -200}, 0, {   -16,    -16}, {0x81, 0x00, 0x00, 0xff}}},
    {{{     0,      0,   -200}, 0, { 31<<5,    -16}, {0x81, 0x00, 0x00, 0xff}}},
    {{{     0,    200,      0}, 0, {   -16,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{     0,      0,      0}, 0, { 31<<5,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   340,    200,   -200}, 0, {  1712,    -16}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{     0,    200,   -200}, 0, {  3408,    -16}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   340,    200,      0}, 0, {  1712,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{     0,    200,      0}, 0, {  3408,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x0500B8C0
static const Vtx eyerok_seg5_vertex_0500B8C0[] = {
    {{{   340,      0,   -200}, 0, {  1712,    -16}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   340,      0,      0}, 0, {  1712,  31<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{     0,      0,      0}, 0, {  3408,  31<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{     0,    200,   -200}, 0, {  3408,    -16}, {0x00, 0x00, 0x82, 0xff}}},
    {{{   340,    200,   -200}, 0, {  1712,    -16}, {0x00, 0x00, 0x82, 0xff}}},
    {{{     0,      0,   -200}, 0, {  3408,  31<<5}, {0x00, 0x00, 0x82, 0xff}}},
    {{{     0,      0,   -200}, 0, {  3408,    -16}, {0x00, 0x81, 0x00, 0xff}}},
};

// 0x0500B930 - 0x0500B9C0
const Gfx eyerok_seg5_dl_0500B930[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, eyerok_seg5_texture_bricks),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&eyerok_seg5_lights_eyerok.l, 1),
    gsSPLight(&eyerok_seg5_lights_eyerok.a, 2),
    gsSPVertex(eyerok_seg5_vertex_0500B7D0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(12, 14, 13, 0x0),
    gsSPVertex(eyerok_seg5_vertex_0500B8C0, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 6,  0,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500B9C0 - 0x0500BA30
const Gfx eyerok_seg5_dl_0500B9C0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(eyerok_seg5_dl_0500B930),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

// 0x0500BA48
static const Vtx eyerok_seg5_vertex_0500BA48[] = {
    {{{  -200,    200,   -100}, 0, { -1024,   -512}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -200,   -200,   -100}, 0, { 31<<5,   -512}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -200,    200,    200}, 0, { -1024,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -200,   -200,   -100}, 0, {179<<5,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -200,    200,   -100}, 0, {179<<5,  -1024}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   200,   -200,   -100}, 0, {116<<5,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   200,    200,   -100}, 0, {116<<5,  -1024}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   200,   -200,    200}, 0, {116<<5,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   200,    200,    200}, 0, {116<<5,  -1024}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -200,   -200,    200}, 0, {179<<5,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -200,    200,    200}, 0, {179<<5,  -1024}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -200,   -200,   -100}, 0, {179<<5,   -512}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   200,   -200,   -100}, 0, {116<<5,   -512}, {0x00, 0x81, 0x00, 0xff}}},
    {{{  -200,   -200,    200}, 0, {179<<5,  31<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   200,   -200,    200}, 0, {116<<5,  31<<5}, {0x00, 0x81, 0x00, 0xff}}},
};

// 0x0500BB38
static const Vtx eyerok_seg5_vertex_0500BB38[] = {
    {{{   200,    200,   -100}, 0, {     0,   -512}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   200,    200,    200}, 0, {     0,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   200,   -200,    200}, 0, { 62<<5,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -200,   -200,   -100}, 0, { 31<<5,   -512}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -200,   -200,    200}, 0, { 31<<5,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -200,    200,    200}, 0, { -1024,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   200,    200,   -100}, 0, {116<<5,   -512}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -200,    200,   -100}, 0, {179<<5,   -512}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   200,    200,    200}, 0, {116<<5,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -200,    200,    200}, 0, {179<<5,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   200,   -200,   -100}, 0, { 62<<5,   -512}, {0x7f, 0x00, 0x00, 0xff}}},
};

// 0x0500BBE8 - 0x0500BC88
const Gfx eyerok_seg5_dl_0500BBE8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, eyerok_seg5_texture_bricks),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&eyerok_seg5_lights_eyerok.l, 1),
    gsSPLight(&eyerok_seg5_lights_eyerok.a, 2),
    gsSPVertex(eyerok_seg5_vertex_0500BA48, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(12, 14, 13, 0x0),
    gsSPVertex(eyerok_seg5_vertex_0500BB38, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  7,  9,  8, 0x0),
    gsSP1Triangle(10,  0,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500BC88 - 0x0500BCF8
const Gfx eyerok_seg5_dl_0500BC88[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(eyerok_seg5_dl_0500BBE8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

// 0x0500BD10
static const Vtx eyerok_seg5_vertex_0500BD10[] = {
    {{{   400,      0,    100}, 0, { 31<<5,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   400,      0,   -100}, 0, {   -16,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   400,    200,    100}, 0, { 31<<5,    -16}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{     0,    200,    100}, 0, {   -32,    976}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   400,    200,    100}, 0, { 62<<5,    976}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{     0,    200,   -100}, 0, {   -32,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   400,    200,   -100}, 0, { 62<<5,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   400,      0,   -100}, 0, { 62<<5,      0}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   400,      0,    100}, 0, { 62<<5,    976}, {0x00, 0x81, 0x00, 0xff}}},
    {{{     0,      0,    100}, 0, {   -32,    976}, {0x00, 0x81, 0x00, 0xff}}},
    {{{     0,      0,   -100}, 0, {   -32,      0}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   400,      0,   -100}, 0, { 62<<5,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{     0,      0,   -100}, 0, {     0,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   400,    200,   -100}, 0, { 62<<5,    -16}, {0x00, 0x00, 0x81, 0xff}}},
    {{{     0,    200,   -100}, 0, {     0,    -16}, {0x00, 0x00, 0x81, 0xff}}},
};

// 0x0500BE00
static const Vtx eyerok_seg5_vertex_0500BE00[] = {
    {{{   400,      0,    100}, 0, { 62<<5,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   400,    200,    100}, 0, { 62<<5,    -16}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{     0,    200,    100}, 0, {     0,    -16}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   400,      0,   -100}, 0, {   -16,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   400,    200,   -100}, 0, {   -16,    -16}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   400,    200,    100}, 0, { 31<<5,    -16}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{     0,      0,    100}, 0, {     0,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
};

// 0x0500BE70 - 0x0500BF00
const Gfx eyerok_seg5_dl_0500BE70[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, eyerok_seg5_texture_bricks),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&eyerok_seg5_lights_eyerok.l, 1),
    gsSPLight(&eyerok_seg5_lights_eyerok.a, 2),
    gsSPVertex(eyerok_seg5_vertex_0500BD10, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  7,  9, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(12, 14, 13, 0x0),
    gsSPVertex(eyerok_seg5_vertex_0500BE00, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 6,  0,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500BF00 - 0x0500BF70
const Gfx eyerok_seg5_dl_0500BF00[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(eyerok_seg5_dl_0500BE70),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

// 0x0500BF88
static const Vtx eyerok_seg5_vertex_0500BF88[] = {
    {{{     0,      0,    100}, 0, {   -16,  -1024}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   400,      0,    100}, 0, {   -16,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{     0,    200,    100}, 0, { 31<<5,  -1024}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{     0,      0,   -100}, 0, {   -16,  -1024}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   400,      0,   -100}, 0, {   -16,  31<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{     0,      0,    100}, 0, { 31<<5,  -1024}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   400,      0,    100}, 0, { 31<<5,  31<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{     0,    200,    100}, 0, { 31<<5,  -1024}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   400,    200,    100}, 0, { 31<<5,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{     0,    200,   -100}, 0, {   -16,  -1024}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   400,    200,   -100}, 0, {   -16,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   400,      0,   -100}, 0, {   -16,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{     0,      0,   -100}, 0, {   -16,  -1024}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   400,    200,   -100}, 0, { 31<<5,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{     0,    200,   -100}, 0, { 31<<5,  -1024}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   400,    200,    100}, 0, { 31<<5,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
};

// 0x0500C088 - 0x0500C100
const Gfx eyerok_seg5_dl_0500C088[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, eyerok_seg5_texture_bricks),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&eyerok_seg5_lights_eyerok.l, 1),
    gsSPLight(&eyerok_seg5_lights_eyerok.a, 2),
    gsSPVertex(eyerok_seg5_vertex_0500BF88, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(12, 14, 13, 0x0,  1, 15,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500C100 - 0x0500C170
const Gfx eyerok_seg5_dl_0500C100[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(eyerok_seg5_dl_0500C088),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

// 0x0500C188
static const Vtx eyerok_seg5_vertex_0500C188[] = {
    {{{   400,      0,   -100}, 0, { 31<<5,    -16}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   400,      0,    100}, 0, { 31<<5,  31<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{     0,      0,    100}, 0, { -1024,  31<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{     0,    200,    100}, 0, { -1024,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   400,    200,    100}, 0, { 31<<5,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{     0,    200,   -100}, 0, { -1024,    -16}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   400,    200,   -100}, 0, { 31<<5,    -16}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{     0,      0,   -100}, 0, { 31<<5,    -16}, {0x81, 0x00, 0x00, 0xff}}},
    {{{     0,      0,    100}, 0, {   -16,    -16}, {0x81, 0x00, 0x00, 0xff}}},
    {{{     0,    200,   -100}, 0, { 31<<5,  -1024}, {0x81, 0x00, 0x00, 0xff}}},
    {{{     0,    200,    100}, 0, {   -16,  -1024}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   400,      0,   -100}, 0, { 31<<5,    -16}, {0x00, 0x00, 0x81, 0xff}}},
    {{{     0,      0,   -100}, 0, { -1024,    -16}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   400,    200,   -100}, 0, { 31<<5,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{     0,    200,   -100}, 0, { -1024,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
};

// 0x0500C278
static const Vtx eyerok_seg5_vertex_0500C278[] = {
    {{{   400,      0,    100}, 0, {     0,    -16}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   400,    200,    100}, 0, {     0,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{     0,    200,    100}, 0, { 62<<5,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{     0,      0,   -100}, 0, { -1024,    -16}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   400,      0,   -100}, 0, { 31<<5,    -16}, {0x00, 0x81, 0x00, 0xff}}},
    {{{     0,      0,    100}, 0, { -1024,  31<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{     0,      0,    100}, 0, { 62<<5,    -16}, {0x00, 0x00, 0x7f, 0xff}}},
};

// 0x0500C2E8 - 0x0500C378
const Gfx eyerok_seg5_dl_0500C2E8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, eyerok_seg5_texture_bricks),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&eyerok_seg5_lights_eyerok.l, 1),
    gsSPLight(&eyerok_seg5_lights_eyerok.a, 2),
    gsSPVertex(eyerok_seg5_vertex_0500C188, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(12, 14, 13, 0x0),
    gsSPVertex(eyerok_seg5_vertex_0500C278, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 6,  0,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500C378 - 0x0500C3E8
const Gfx eyerok_seg5_dl_0500C378[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(eyerok_seg5_dl_0500C2E8),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

// 0x0500C400
static const Vtx eyerok_seg5_vertex_0500C400[] = {
    {{{   464,     12,   -524}, 0, {     0,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{    -3,     -2,   -524}, 0, { 72<<5,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   330,    410,   -524}, 0, {   576,   1968}, {0x00, 0x00, 0x81, 0xff}}},
    {{{    -3,     -2,   -524}, 0, { 72<<5,  -3040}, {0x03, 0x82, 0x00, 0xff}}},
    {{{   464,     12,   -524}, 0, {     0,  -3040}, {0x03, 0x82, 0x00, 0xff}}},
    {{{    -3,     -2,    282}, 0, { 72<<5,  31<<5}, {0x03, 0x82, 0x00, 0xff}}},
    {{{   464,     12,    282}, 0, {     0,  31<<5}, {0x03, 0x82, 0x00, 0xff}}},
    {{{   -16,    400,    282}, 0, {  2368,  31<<5}, {0xfc, 0x7e, 0x00, 0xff}}},
    {{{   330,    410,    282}, 0, {   640,  31<<5}, {0xfc, 0x7e, 0x00, 0xff}}},
    {{{   -16,    400,   -524}, 0, {  2368,  -3040}, {0xfc, 0x7e, 0x00, 0xff}}},
    {{{   330,    410,   -524}, 0, {   640,  -3040}, {0xfc, 0x7e, 0x00, 0xff}}},
    {{{    -3,     -2,   -524}, 0, { -3032,    -48}, {0x82, 0xfc, 0x00, 0xff}}},
    {{{    -3,     -2,    282}, 0, { 31<<5,    -48}, {0x82, 0xfc, 0x00, 0xff}}},
    {{{   -16,    400,   -524}, 0, { -3032,  61<<5}, {0x82, 0xfc, 0x00, 0xff}}},
    {{{   -16,    400,    282}, 0, { 31<<5,  61<<5}, {0x82, 0xfc, 0x00, 0xff}}},
};

// 0x0500C4F0
static const Vtx eyerok_seg5_vertex_0500C4F0[] = {
    {{{   464,     12,    282}, 0, {     0,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   330,    410,    282}, 0, {   576,   1968}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   -16,    400,    282}, 0, { 72<<5,   1968}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{    -3,     -2,   -524}, 0, { 72<<5,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   -16,    400,   -524}, 0, { 72<<5,   1968}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   330,    410,   -524}, 0, {   576,   1968}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   464,     12,    282}, 0, { 31<<5,      0}, {0x78, 0x28, 0x00, 0xff}}},
    {{{   464,     12,   -524}, 0, { -3032,      0}, {0x78, 0x28, 0x00, 0xff}}},
    {{{   330,    410,    282}, 0, { 31<<5,  61<<5}, {0x78, 0x28, 0x00, 0xff}}},
    {{{   330,    410,   -524}, 0, { -3032,  61<<5}, {0x78, 0x28, 0x00, 0xff}}},
    {{{    -3,     -2,    282}, 0, { 72<<5,      0}, {0x00, 0x00, 0x7f, 0xff}}},
};

// 0x0500C5A0 - 0x0500C640
const Gfx eyerok_seg5_dl_0500C5A0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, eyerok_seg5_texture_bricks),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&eyerok_seg5_lights_eyerok.l, 1),
    gsSPLight(&eyerok_seg5_lights_eyerok.a, 2),
    gsSPVertex(eyerok_seg5_vertex_0500C400, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(12, 14, 13, 0x0),
    gsSPVertex(eyerok_seg5_vertex_0500C4F0, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  7,  9,  8, 0x0),
    gsSP1Triangle(10,  0,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500C640 - 0x0500C6B0
const Gfx eyerok_seg5_dl_0500C640[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(eyerok_seg5_dl_0500C5A0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

// 0x0500C6C8
static const Vtx eyerok_seg5_vertex_0500C6C8[] = {
    {{{   273,    357,    282}, 0, { 72<<5,  62<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   -89,    181,    282}, 0, {135<<5,  62<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{    86,   -181,    282}, 0, {135<<5,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{    86,   -181,   -522}, 0, {135<<5,  -3024}, {0x37, 0x8e, 0x00, 0xff}}},
    {{{   448,     -5,    282}, 0, { 72<<5,  31<<5}, {0x37, 0x8e, 0x00, 0xff}}},
    {{{    86,   -181,    282}, 0, {135<<5,  31<<5}, {0x37, 0x8e, 0x00, 0xff}}},
    {{{   448,     -5,   -522}, 0, { 72<<5,  -3024}, {0x37, 0x8e, 0x00, 0xff}}},
    {{{   -89,    181,    282}, 0, {137<<5,  31<<5}, {0xc9, 0x72, 0x00, 0xff}}},
    {{{   273,    357,   -522}, 0, {  2370,  -3024}, {0xc9, 0x72, 0x00, 0xff}}},
    {{{   -89,    181,   -522}, 0, {137<<5,  -3024}, {0xc9, 0x72, 0x00, 0xff}}},
    {{{   273,    357,    282}, 0, {  2370,  31<<5}, {0xc9, 0x72, 0x00, 0xff}}},
    {{{   -89,    181,    282}, 0, {     0,  31<<5}, {0x8e, 0xc9, 0x00, 0xff}}},
    {{{    86,   -181,   -522}, 0, {  3984,  -1024}, {0x8e, 0xc9, 0x00, 0xff}}},
    {{{    86,   -181,    282}, 0, {     0,  -1024}, {0x8e, 0xc9, 0x00, 0xff}}},
    {{{   -89,    181,   -522}, 0, {  3984,  31<<5}, {0x8e, 0xc9, 0x00, 0xff}}},
};

// 0x0500C7B8
static const Vtx eyerok_seg5_vertex_0500C7B8[] = {
    {{{   -89,    181,   -522}, 0, {135<<5,  62<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   273,    357,   -522}, 0, { 72<<5,  62<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   448,     -5,   -522}, 0, { 72<<5,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   273,    357,    282}, 0, { 72<<5,  62<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{    86,   -181,    282}, 0, {135<<5,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   448,     -5,    282}, 0, { 72<<5,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   273,    357,   -522}, 0, { -3024,  31<<5}, {0x72, 0x37, 0x00, 0xff}}},
    {{{   448,     -5,    282}, 0, { 31<<5,  -1056}, {0x72, 0x37, 0x00, 0xff}}},
    {{{   448,     -5,   -522}, 0, { -3024,  -1056}, {0x72, 0x37, 0x00, 0xff}}},
    {{{   273,    357,    282}, 0, { 31<<5,  31<<5}, {0x72, 0x37, 0x00, 0xff}}},
    {{{    86,   -181,   -522}, 0, {135<<5,      0}, {0x00, 0x00, 0x81, 0xff}}},
};

// 0x0500C868 - 0x0500C908
const Gfx eyerok_seg5_dl_0500C868[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, eyerok_seg5_texture_bricks),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&eyerok_seg5_lights_eyerok.l, 1),
    gsSPLight(&eyerok_seg5_lights_eyerok.a, 2),
    gsSPVertex(eyerok_seg5_vertex_0500C6C8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(eyerok_seg5_vertex_0500C7B8, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP1Triangle( 0,  2, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500C908 - 0x0500C978
const Gfx eyerok_seg5_dl_0500C908[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(eyerok_seg5_dl_0500C868),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

// 0x0500C978
static const Vtx eyerok_seg5_vertex_eye[] = {
    {{{   212,    365,     64}, 0, ST_B(    32,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{   212,    365,   -256}, 0, ST_B(     0,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{   -73,    192,   -256}, 0, ST_B(     0,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{   -73,    192,     64}, 0, ST_B(    32,     32), {0xff, 0xff, 0xff, 0xff}}},
};

// 0x0500C9B8 - 0x0500CA50
const Gfx eyerok_seg5_dl_eye_open[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, eyerok_seg5_texture_eye_open),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(eyerok_seg5_vertex_eye, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPEndDisplayList(),
};

// 0x0500CA50 - 0x0500CAE8
const Gfx eyerok_seg5_dl_eye_mostly_open[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, eyerok_seg5_texture_eye_mostly_open),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(eyerok_seg5_vertex_eye, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPEndDisplayList(),
};

// 0x0500CAE8 - 0x0500CB80
const Gfx eyerok_seg5_dl_eye_mostly_closed[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, eyerok_seg5_texture_eye_mostly_closed),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(eyerok_seg5_vertex_eye, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPEndDisplayList(),
};

// 0x0500CB80 - 0x0500CC18
const Gfx eyerok_seg5_dl_eye_closed[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, eyerok_seg5_texture_eye_closed),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(eyerok_seg5_vertex_eye, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPEndDisplayList(),
};

// 0x0500CC18 - 0x0500CC30
const Gfx eyerok_seg5_dl_cull_back_cull_front[] = {
    gsSPGeometryMode(G_CULL_BACK, G_CULL_FRONT),
    gsSPEndDisplayList(),
};

// 0x0500CC30 - 0x0500CC48
const Gfx eyerok_seg5_dl_cull_front_cull_back[] = {
    gsSPGeometryMode(G_CULL_FRONT, G_CULL_BACK),
    gsSPEndDisplayList(),
};
