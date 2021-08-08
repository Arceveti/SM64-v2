// Swoop

// 0x06004270
ALIGNED8 static const Texture dSwoopBodyTexture[] = {
#include "actors/swoop/swoop_body.rgba16.inc.c"
};

// 0x06004A70
ALIGNED8 static const Texture dSwoopEyeTexture[] = {
#include "actors/swoop/swoop_eye.rgba16.inc.c"
};

// 0x06005270
ALIGNED8 static const Texture dSwoopNoseTexture[] = {
#include "actors/swoop/swoop_nose.rgba16.inc.c"
};

// 0x06005A70
ALIGNED8 static const Texture dSwoopWingTexture[] = {
#include "actors/swoop/swoop_wing.rgba16.inc.c"
};

// 0x06006270
static const Lights1 dSwoopLights = gdSPDefLights1(
    0x79, 0x79, 0x79,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x06006288
static const Vtx dSwoopEyeVertices1[] = {
    {{{    80,     38,    -45}, 0, {    40,     80}, {0x3f, 0x30, 0x9e, 0xff}}},
    {{{    65,     77,    -25}, 0, {  1104,  25<<5}, {0x44, 0x59, 0xc6, 0xff}}},
    {{{   112,     54,      0}, 0, { 24<<5,   -456}, {0x69, 0x46, 0x00, 0xff}}},
    {{{   -14,     56,     28}, 0, {   624,   8<<5}, {0x96, 0x31, 0x30, 0xff}}},
    {{{   -11,    -13,      0}, 0, {   536,    232}, {0x8d, 0xcc, 0x00, 0xff}}},
    {{{    17,    -18,     89}, 0, { 25<<5,     80}, {0xcc, 0xed, 0x72, 0xff}}},
    {{{    29,     71,     45}, 0, { 21<<5,      0}, {0x05, 0x44, 0x6a, 0xff}}},
    {{{   -14,     56,    -28}, 0, { 14<<5,    246}, {0x96, 0x31, 0xd0, 0xff}}},
    {{{    17,    -18,    -89}, 0, {  8<<5,     56}, {0xe5, 0xdf, 0x89, 0xff}}},
    {{{    29,     71,    -45}, 0, {   386,    -16}, {0x05, 0x44, 0x95, 0xff}}},
    {{{    82,      4,    -53}, 0, {  -728,   -328}, {0x3f, 0xfe, 0x93, 0xff}}},
    {{{    17,    -18,    -89}, 0, { -1332,    816}, {0xe5, 0xdf, 0x89, 0xff}}},
    {{{    29,     71,    -45}, 0, {   880,   1484}, {0x05, 0x44, 0x95, 0xff}}},
    {{{   114,      5,    -25}, 0, {  -496,  -1008}, {0x71, 0xe7, 0xce, 0xff}}},
};

// 0x06006368
static const Vtx dSwoopEyeVertices2[] = {
    {{{    82,      4,     53}, 0, {   758,   1080}, {0x40, 0xf1, 0x6c, 0xff}}},
    {{{    83,    -37,     25}, 0, {   624,   1080}, {0x54, 0xab, 0x27, 0xff}}},
    {{{   114,      5,     25}, 0, {   624,  29<<5}, {0x6f, 0xf4, 0x3c, 0xff}}},
    {{{    29,     71,     45}, 0, {   386,   1344}, {0x05, 0x44, 0x6a, 0xff}}},
    {{{    80,     38,     45}, 0, {   184,     96}, {0x40, 0x31, 0x62, 0xff}}},
    {{{    65,     77,     25}, 0, {  1194,    792}, {0x44, 0x59, 0x3a, 0xff}}},
    {{{   112,     54,      0}, 0, {  1590,   -282}, {0x69, 0x46, 0x00, 0xff}}},
    {{{    17,    -18,     89}, 0, { -2258,  18<<5}, {0xcc, 0xed, 0x72, 0xff}}},
    {{{    82,      4,     53}, 0, {  -608,   -320}, {0x40, 0xf1, 0x6c, 0xff}}},
    {{{   112,     54,      0}, 0, { 16<<5,    944}, {0x69, 0x46, 0x00, 0xff}}},
    {{{    80,     38,     45}, 0, {   720,  34<<5}, {0x40, 0x31, 0x62, 0xff}}},
    {{{    34,    -55,     45}, 0, {   720,  41<<5}, {0x06, 0x8a, 0x2c, 0xff}}},
    {{{    17,    -18,     89}, 0, { 29<<5,   1392}, {0xcc, 0xed, 0x72, 0xff}}},
    {{{    83,    -37,    -25}, 0, {   400,   1080}, {0x48, 0xa4, 0xd1, 0xff}}},
    {{{    82,      4,    -53}, 0, {   272,  34<<5}, {0x3f, 0xfe, 0x93, 0xff}}},
    {{{   114,      5,    -25}, 0, {   400,  29<<5}, {0x71, 0xe7, 0xce, 0xff}}},
};

// 0x06006468
static const Vtx dSwoopEyeVertices3[] = {
    {{{    34,    -55,     45}, 0, {   720,  41<<5}, {0x06, 0x8a, 0x2c, 0xff}}},
    {{{    34,    -55,    -45}, 0, { 10<<5,  41<<5}, {0xe6, 0x8a, 0xdc, 0xff}}},
    {{{    83,    -37,    -25}, 0, {   400,   1080}, {0x48, 0xa4, 0xd1, 0xff}}},
    {{{    83,    -37,     25}, 0, {   624,   1080}, {0x54, 0xab, 0x27, 0xff}}},
    {{{   114,      5,    -25}, 0, {   400,  29<<5}, {0x71, 0xe7, 0xce, 0xff}}},
    {{{   114,      5,     25}, 0, {   624,  29<<5}, {0x6f, 0xf4, 0x3c, 0xff}}},
    {{{   112,     54,      0}, 0, { 16<<5,    944}, {0x69, 0x46, 0x00, 0xff}}},
    {{{   -11,    -13,      0}, 0, {   522,  48<<5}, {0x8d, 0xcc, 0x00, 0xff}}},
    {{{    17,    -18,     89}, 0, { 29<<5,   1394}, {0xcc, 0xed, 0x72, 0xff}}},
    {{{    17,    -18,    -89}, 0, {   112,   1406}, {0xe5, 0xdf, 0x89, 0xff}}},
    {{{    82,      4,    -53}, 0, {   272,  34<<5}, {0x3f, 0xfe, 0x93, 0xff}}},
};

// 0x06006518
static const Vtx dSwoopNoseVertices[] = {
    {{{   112,     54,      0}, 0, { 22<<5,      0}, {0x69, 0x46, 0x00, 0xff}}},
    {{{    65,     77,    -25}, 0, {   382,    266}, {0x44, 0x59, 0xc6, 0xff}}},
    {{{    65,     77,     25}, 0, {   880,    288}, {0x44, 0x59, 0x3a, 0xff}}},
    {{{    40,    113,      0}, 0, { 15<<5,  15<<5}, {0xf9, 0x7e, 0x00, 0xff}}},
    {{{    65,     77,     25}, 0, {   720,   7<<5}, {0x44, 0x59, 0x3a, 0xff}}},
    {{{    65,     77,    -25}, 0, {   232,   7<<5}, {0x44, 0x59, 0xc6, 0xff}}},
    {{{    29,     71,     45}, 0, { 29<<5,    586}, {0x05, 0x44, 0x6a, 0xff}}},
    {{{    29,     71,    -45}, 0, {    24,    586}, {0x05, 0x44, 0x95, 0xff}}},
    {{{   -14,     56,     28}, 0, {   752,  32<<5}, {0x96, 0x31, 0x30, 0xff}}},
    {{{   -14,     56,    -28}, 0, {   200,  32<<5}, {0x96, 0x31, 0xd0, 0xff}}},
};

// 0x060065B8 - 0x060066F8
const Gfx dSwoopEyesSubDl[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, dSwoopEyeTexture),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&dSwoopLights.l, 1),
    gsSPLight(&dSwoopLights.a, 2),
    gsSPVertex(dSwoopEyeVertices1, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  6,  3, 0x0,  3,  7,  4, 0x0),
    gsSP2Triangles( 8,  4,  7, 0x0,  7,  9,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12,  0, 0x0),
    gsSP2Triangles( 0,  2, 13, 0x0,  0, 13, 10, 0x0),
    gsSP1Triangle( 1,  0, 12, 0x0),
    gsSPVertex(dSwoopEyeVertices2, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  3,  7,  8, 0x0),
    gsSP2Triangles( 3,  8,  4, 0x0,  2,  9, 10, 0x0),
    gsSP2Triangles( 2, 10,  0, 0x0, 11,  1,  0, 0x0),
    gsSP2Triangles(11,  0, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(dSwoopEyeVertices3, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  3, 0x0,  4,  3,  2, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  1,  0, 0x0),
    gsSP2Triangles( 0,  8,  7, 0x0,  9,  1,  7, 0x0),
    gsSP2Triangles( 2,  1,  9, 0x0,  2,  9, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x060066F8 - 0x06006758
const Gfx dSwoopNoseSubDl[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, dSwoopNoseTexture),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(dSwoopNoseVertices, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  3,  6, 0x0,  7,  3,  5, 0x0),
    gsSP2Triangles( 6,  3,  8, 0x0,  3,  9,  8, 0x0),
    gsSP1Triangle(  7,  9,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x06006758 - 0x06006808
const Gfx dSwoopHeadDl[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(dSwoopEyesSubDl),
    gsSPDisplayList(dSwoopNoseSubDl),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// Body

// 0x06006808
static const Vtx dSwoopBodyVertices[] = {
    {{{    15,     15,      0}, 0, { 31<<5,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   -15,     15,      0}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   -15,    -15,      0}, 0, {     0,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{    15,    -15,      0}, 0, { 31<<5,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
};

// 0x06006848 - 0x06006880
const Gfx dSwoopBodySubDl[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, dSwoopBodyTexture),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(dSwoopBodyVertices, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x06006880 - 0x06006938
const Gfx dSwoopBodyDl[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(dSwoopBodySubDl),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x06006950
static const Vtx dSwoopEarsVertices[] = {
    {{{   187,     48,    -56}, 0, {   424,    720}, {0xc6, 0x6b, 0xdf, 0xff}}},
    {{{   194,     32,   -120}, 0, {   336,  22<<5}, {0xdf, 0x7a, 0x05, 0xff}}},
    {{{    80,     -3,    -33}, 0, {   456,  31<<5}, {0xdf, 0x7a, 0x05, 0xff}}},
    {{{   116,     34,   -131}, 0, { 10<<5,  28<<5}, {0xfd, 0x77, 0x2b, 0xff}}},
    {{{    80,     -3,     33}, 0, {   552,  31<<5}, {0xdf, 0x7a, 0xfb, 0xff}}},
    {{{   194,     32,    120}, 0, { 21<<5,  22<<5}, {0xdf, 0x7a, 0xfb, 0xff}}},
    {{{   187,     48,     56}, 0, {   584,    720}, {0xc6, 0x6b, 0x21, 0xff}}},
    {{{   116,     34,    131}, 0, {   688,  28<<5}, {0xfd, 0x77, 0xd5, 0xff}}},
};

// 0x060069D0
static const Vtx dSwoopToothVertices[] = {
    {{{    13,     79,    -16}, 0, {     0,      0}, {0xec, 0x7d, 0x00, 0xff}}},
    {{{   -17,     74,     -9}, 0, {     0,      0}, {0xec, 0x7d, 0x00, 0xff}}},
    {{{   -17,     74,      9}, 0, {     0,      0}, {0xec, 0x7d, 0x00, 0xff}}},
    {{{    13,     79,     16}, 0, {     0,      0}, {0xec, 0x7d, 0x00, 0xff}}},
};

// 0x06006A10 - 0x06006A68
const Gfx dSwoopEarsSubDl[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, dSwoopNoseTexture),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&dSwoopLights.l, 1),
    gsSPLight(&dSwoopLights.a, 2),
    gsSPVertex(dSwoopEarsVertices, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x06006A68 - 0x06006A88
const Gfx dSwoopToothSubDl[] = {
    gsSPVertex(dSwoopToothVertices, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x06006A88 - 0x06006B58
const Gfx dSwoopFaceEarsToothDl[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(dSwoopEarsSubDl),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(dSwoopToothSubDl),
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

// Wings

// 0x06006B58
static const Vtx dSwoopWing1Vertices[] = {
    {{{     0,      1,    133}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,      1,   -133}, 0, {     0,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   265,      1,   -133}, 0, { 31<<5,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   265,      1,    133}, 0, { 31<<5,      0}, {0xff, 0xff, 0xff, 0xff}}},
};

// 0x06006B98 - 0x06006BD0
const Gfx dSwoopWing1SubDl[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, dSwoopWingTexture),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(dSwoopWing1Vertices, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x06006BD0 - 0x06006C88
const Gfx dSwoopWing1Dl[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(dSwoopWing1SubDl),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPEndDisplayList(),
};

// 0x06006C88
static const Vtx dSwoopWing2Vertices[] = {
    {{{   265,      1,   -133}, 0, { 31<<5,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   265,      1,    133}, 0, { 31<<5,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,      1,    133}, 0, {     0,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,      1,   -133}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}},
};

// 0x06006CC8 - 0x06006D00
const Gfx dSwoopWing2SubDl[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, dSwoopWingTexture),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(dSwoopWing2Vertices, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x06006D00 - 0x06006DB8
const Gfx dSwoopWing2Dl[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(dSwoopWing2SubDl),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPEndDisplayList(),
};
