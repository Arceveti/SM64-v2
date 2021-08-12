// Thwomp

// 0x050098E8
static const Lights1 thwomp_seg5_lights_050098E8 = gdSPDefLights1(
    0x4c, 0x4c, 0x4c,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x05009900
ALIGNED8 static const Texture thwomp_seg5_texture_face[] = {
#include "actors/thwomp/thwomp_face.rgba16.inc.c"
};

// 0x0500A900
ALIGNED8 static const Texture thwomp_seg5_texture_surface[] = {
#include "actors/thwomp/thwomp_surface.rgba16.inc.c"
};

// 0x0500B100
static const Vtx thwomp_seg5_vertex_0500B100[] = {
    {{{   -96,     51,   -154}, 0, {  3308,    416}, {0xce, 0xcb, 0x99, 0xff}}},
    {{{  -154,     51,    -77}, 0, {  2910,    416}, {0x93, 0xca, 0xdf, 0xff}}},
    {{{  -154,    256,    -77}, 0, {  2904,   1584}, {0x89, 0x1a, 0xde, 0xff}}},
    {{{  -102,    256,   -154}, 0, {  3316,   1584}, {0xd0, 0x46, 0xa3, 0xff}}},
    {{{   102,    256,   -154}, 0, {  4286,   1584}, {0x29, 0x39, 0x97, 0xff}}},
    {{{    96,     51,   -154}, 0, {  4292,    416}, {0x45, 0xd0, 0xa2, 0xff}}},
    {{{   154,    256,    -77}, 0, {  4698,   1584}, {0x73, 0x22, 0xd7, 0xff}}},
    {{{   154,     51,    -77}, 0, {  4692,    416}, {0x70, 0xc9, 0xea, 0xff}}},
    {{{     0,    307,   -102}, 0, {   464,    -56}, {0x00, 0x70, 0xc6, 0xff}}},
    {{{    96,    307,      0}, 0, {  1000,    544}, {0x2c, 0x76, 0x00, 0xff}}},
    {{{   102,    256,   -154}, 0, { 34<<5,   -374}, {0x29, 0x39, 0x97, 0xff}}},
    {{{   -96,    307,      0}, 0, {   -80,    544}, {0xd4, 0x76, 0x00, 0xff}}},
    {{{     0,    307,    102}, 0, {   464,   1134}, {0x00, 0x70, 0x3a, 0xff}}},
    {{{   102,    256,    154}, 0, { 34<<5,   1452}, {0x30, 0x46, 0x5d, 0xff}}},
    {{{  -102,    256,   -154}, 0, {  -160,   -374}, {0xd0, 0x46, 0xa3, 0xff}}},
};

// 0x0500B1F0
static const Vtx thwomp_seg5_vertex_0500B1F0[] = {
    {{{  -154,    256,     77}, 0, {  -448,   1000}, {0x8d, 0x22, 0x29, 0xff}}},
    {{{  -102,    256,    154}, 0, {  -160,   1452}, {0xd7, 0x39, 0x69, 0xff}}},
    {{{   -96,    307,      0}, 0, {   -80,    544}, {0xd4, 0x76, 0x00, 0xff}}},
    {{{  -154,    256,    -77}, 0, {  -448,     80}, {0x89, 0x1a, 0xde, 0xff}}},
    {{{  -102,    256,   -154}, 0, {  -160,   -374}, {0xd0, 0x46, 0xa3, 0xff}}},
    {{{     0,    307,    102}, 0, {   464,   1134}, {0x00, 0x70, 0x3a, 0xff}}},
    {{{   102,    256,    154}, 0, { 34<<5,   1452}, {0x30, 0x46, 0x5d, 0xff}}},
    {{{   -96,     51,   -154}, 0, {  -192,   1444}, {0xce, 0xcb, 0x99, 0xff}}},
    {{{    83,      0,    -83}, 0, {  1042,   1040}, {0x1e, 0x8c, 0xd7, 0xff}}},
    {{{   -83,      0,    -83}, 0, {   -80,   1040}, {0xc9, 0x92, 0xe2, 0xff}}},
    {{{    96,     51,   -154}, 0, {  1148,   1444}, {0x45, 0xd0, 0xa2, 0xff}}},
    {{{    83,      0,     83}, 0, {  1042,    -80}, {0x37, 0x92, 0x1e, 0xff}}},
    {{{   -83,      0,     83}, 0, {   -80,    -80}, {0xe2, 0x8c, 0x29, 0xff}}},
    {{{   154,     51,    -77}, 0, {  1446,    976}, {0x70, 0xc9, 0xea, 0xff}}},
    {{{    96,     51,    154}, 0, {  1148,   -480}, {0x32, 0xcb, 0x67, 0xff}}},
    {{{   -96,     51,    154}, 0, {  -192,   -480}, {0xbb, 0xd0, 0x5e, 0xff}}},
};

// 0x0500B2F0
static const Vtx thwomp_seg5_vertex_0500B2F0[] = {
    {{{   -83,      0,    -83}, 0, {   -80,   1040}, {0xc9, 0x92, 0xe2, 0xff}}},
    {{{   -83,      0,     83}, 0, {   -80,    -80}, {0xe2, 0x8c, 0x29, 0xff}}},
    {{{  -154,     51,     77}, 0, {  -480,    -16}, {0x90, 0xc9, 0x16, 0xff}}},
    {{{   -96,     51,    154}, 0, {  -192,   -480}, {0xbb, 0xd0, 0x5e, 0xff}}},
    {{{   -96,     51,   -154}, 0, {  -192,   1444}, {0xce, 0xcb, 0x99, 0xff}}},
    {{{  -154,     51,    -77}, 0, {  -480,    976}, {0x93, 0xca, 0xdf, 0xff}}},
    {{{    83,      0,     83}, 0, {  1042,    -84}, {0x37, 0x92, 0x1e, 0xff}}},
    {{{   154,     51,    -77}, 0, {  1446,    976}, {0x70, 0xc9, 0xea, 0xff}}},
    {{{   154,     51,     77}, 0, {  1446,    -16}, {0x6d, 0xca, 0x21, 0xff}}},
    {{{    96,     51,    154}, 0, {  1148,   -480}, {0x32, 0xcb, 0x67, 0xff}}},
    {{{   154,     51,    -77}, 0, {  4692,    416}, {0x70, 0xc9, 0xea, 0xff}}},
    {{{   154,    256,    -77}, 0, {  4698,   1584}, {0x73, 0x22, 0xd7, 0xff}}},
    {{{   154,    256,     77}, 0, {  5458,   1584}, {0x77, 0x1a, 0x22, 0xff}}},
    {{{   154,     51,     77}, 0, {  5464,    416}, {0x6d, 0xca, 0x21, 0xff}}},
};

// 0x0500B3D0
static const Vtx thwomp_seg5_vertex_0500B3D0[] = {
    {{{   102,    256,    154}, 0, {   768,   1584}, {0x30, 0x46, 0x5d, 0xff}}},
    {{{    96,     51,    154}, 0, {   754,    416}, {0x32, 0xcb, 0x67, 0xff}}},
    {{{   154,    256,     77}, 0, {   348,   1584}, {0x77, 0x1a, 0x22, 0xff}}},
    {{{   -96,     51,    154}, 0, {  1738,    416}, {0xbb, 0xd0, 0x5e, 0xff}}},
    {{{  -154,    256,     77}, 0, {  2142,   1584}, {0x8d, 0x22, 0x29, 0xff}}},
    {{{  -154,     51,     77}, 0, {  2136,    416}, {0x90, 0xc9, 0x16, 0xff}}},
    {{{  -154,    256,    -77}, 0, {  2904,   1584}, {0x89, 0x1a, 0xde, 0xff}}},
    {{{  -154,     51,    -77}, 0, {  2910,    416}, {0x93, 0xca, 0xdf, 0xff}}},
    {{{  -102,    256,    154}, 0, {  1730,   1584}, {0xd7, 0x39, 0x69, 0xff}}},
    {{{   102,    256,   -154}, 0, {   -24,    628}, {0x29, 0x39, 0x97, 0xff}}},
    {{{  -102,    256,   -154}, 0, { 31<<5,    628}, {0xd0, 0x46, 0xa3, 0xff}}},
    {{{     0,    307,   -102}, 0, { 15<<5,    370}, {0x00, 0x70, 0xc6, 0xff}}},
    {{{   154,    256,     77}, 0, {  1374,   1000}, {0x77, 0x1a, 0x22, 0xff}}},
    {{{    96,    307,      0}, 0, {  1000,    544}, {0x2c, 0x76, 0x00, 0xff}}},
    {{{   102,    256,    154}, 0, { 34<<5,   1452}, {0x30, 0x46, 0x5d, 0xff}}},
    {{{   154,    256,    -77}, 0, {  1374,     80}, {0x73, 0x22, 0xd7, 0xff}}},
};

// 0x0500B4D0
static const Vtx thwomp_seg5_vertex_0500B4D0[] = {
    {{{    96,     51,    154}, 0, {   754,    416}, {0x32, 0xcb, 0x67, 0xff}}},
    {{{   154,     51,     77}, 0, {   354,    416}, {0x6d, 0xca, 0x21, 0xff}}},
    {{{   154,    256,     77}, 0, {   348,   1584}, {0x77, 0x1a, 0x22, 0xff}}},
    {{{   102,    256,   -154}, 0, {  1414,    324}, {0x29, 0x39, 0x97, 0xff}}},
    {{{    96,    307,      0}, 0, { 15<<5,    -16}, {0x2c, 0x76, 0x00, 0xff}}},
    {{{   154,    256,    -77}, 0, {   944,    496}, {0x73, 0x22, 0xd7, 0xff}}},
};

// 0x0500B530
static const Vtx thwomp_seg5_vertex_0500B530[] = {
    {{{    96,     51,    154}, 0, {   976,   1976}, {0x32, 0xcb, 0x67, 0xff}}},
    {{{   102,    256,    154}, 0, {  1008,      0}, {0x30, 0x46, 0x5d, 0xff}}},
    {{{  -102,    256,    154}, 0, {   -56,    -16}, {0xd7, 0x39, 0x69, 0xff}}},
    {{{   -96,     51,    154}, 0, {   -16,   1964}, {0xbb, 0xd0, 0x5e, 0xff}}},
};

// 0x0500B570 - 0x0500B718
const Gfx thwomp_seg5_dl_body[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, thwomp_seg5_texture_surface),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&thwomp_seg5_lights_050098E8.l, 1),
    gsSPLight(&thwomp_seg5_lights_050098E8.a, 2),
    gsSPVertex(thwomp_seg5_vertex_0500B100, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 0,  3,  4, 0x0,  0,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(12, 13,  9, 0x0,  9, 11, 12, 0x0),
    gsSP1Triangle( 8, 14, 11, 0x0),
    gsSPVertex(thwomp_seg5_vertex_0500B1F0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  4, 0x0),
    gsSP2Triangles( 0,  2,  3, 0x0,  2,  1,  5, 0x0),
    gsSP2Triangles( 1,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0,  8, 11, 12, 0x0),
    gsSP2Triangles( 8, 12,  9, 0x0, 11,  8, 13, 0x0),
    gsSP2Triangles(13,  8, 10, 0x0, 14, 12, 11, 0x0),
    gsSP1Triangle(14, 15, 12, 0x0),
    gsSPVertex(thwomp_seg5_vertex_0500B2F0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 4,  0,  5, 0x0,  0,  2,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  6,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPVertex(thwomp_seg5_vertex_0500B3D0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 3,  8,  4, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 15, 13, 12, 0x0),
    gsSPVertex(thwomp_seg5_vertex_0500B4D0, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500B718 - 0x0500B750
const Gfx thwomp_seg5_dl_face[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, thwomp_seg5_texture_face),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(thwomp_seg5_vertex_0500B530, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500B750 - 0x0500B7D0
const Gfx thwomp_seg5_dl_thwomp[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(thwomp_seg5_dl_body),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(thwomp_seg5_dl_face),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
