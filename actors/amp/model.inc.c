// Amp

ALIGNED8 static const Texture dAmpElectricityTexture[] = {
#include "actors/amp/amp_electricity.rgba16.inc.c"
};

ALIGNED8 static const Texture dAmpEyesTexture[] = {
#include "actors/amp/amp_eyes.rgba16.inc.c"
};

ALIGNED8 static const Texture dAmpBodyTexture[] = {
#include "actors/amp/amp_body.rgba16.inc.c"
};

ALIGNED8 static const Texture dAmpMouthTexture[] = {
#include "actors/amp/amp_mouth.rgba16.inc.c"
};

static const Vtx dAmpElectricityVertices[] = {
    {{{   224,      0,    -90}, 0, ST_B(    0,   16), {0xff, 0xff, 0xff, 0xff}}},
    {{{   187,    149,      0}, 0, ST_B(    8, 34.5), {0xff, 0xff, 0xff, 0xff}}},
    {{{   224,      0,     90}, 0, ST_B(   16,   16), {0xff, 0xff, 0xff, 0xff}}},
    {{{   187,   -149,      0}, 0, ST_B(    8,   -4), {0xff, 0xff, 0xff, 0xff}}},
    {{{   224,      0,    -90}, 0, ST_B(    0,   16), {0xff, 0xff, 0xff, 0xff}}},
};

const Gfx dAmpElectricitySubDl[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, dAmpElectricityTexture),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(16, 32), CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(dAmpElectricityVertices, 5, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSPEndDisplayList(),
};

const Gfx dAmpElectricityDl[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, (G_TX_WRAP | G_TX_NOMIRROR), G_TX_NOMASK, G_TX_NOLOD, (G_TX_WRAP | G_TX_NOMIRROR), G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 4, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, ((16 - 1) << G_TEXTURE_IMAGE_FRAC), ((32 - 1) << G_TEXTURE_IMAGE_FRAC)),
    gsSPDisplayList(dAmpElectricitySubDl),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPEndDisplayList(),
};

static const Vtx dAmpEyeVertices[] = {
    {{{    68,     72,    158}, 0, ST_B(  0,   0), {0xff, 0xff, 0xff, 0xff}}},
    {{{   -27,    -72,    164}, 0, ST_B( 32,  32), {0xff, 0xff, 0xff, 0xff}}},
    {{{    68,    -72,    158}, 0, ST_B( 32,   0), {0xff, 0xff, 0xff, 0xff}}},
    {{{   -27,     72,    164}, 0, ST_B(  0,  32), {0xff, 0xff, 0xff, 0xff}}},
};

const Gfx dAmpEyeSubDl[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, dAmpEyesTexture),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(dAmpEyeVertices, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

const Gfx dAmpEyeDl[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, (G_TX_WRAP | G_TX_NOMIRROR), G_TX_NOMASK, G_TX_NOLOD, (G_TX_WRAP | G_TX_NOMIRROR), G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, ((32 - 1) << G_TEXTURE_IMAGE_FRAC), ((32 - 1) << G_TEXTURE_IMAGE_FRAC)),
    gsSPDisplayList(dAmpEyeSubDl),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

static const Vtx dAmpMouthVertices[] = {
    {{{   -32,     72,    164}, 0, ST_B(  0,   0), {0xff, 0xff, 0xff, 0xff}}},
    {{{  -128,    -72,    121}, 0, ST_B( 32,  32), {0xff, 0xff, 0xff, 0xff}}},
    {{{   -32,    -72,    164}, 0, ST_B( 32,   0), {0xff, 0xff, 0xff, 0xff}}},
    {{{  -128,     72,    121}, 0, ST_B(  0,  32), {0xff, 0xff, 0xff, 0xff}}},
};

const Gfx dAmpMouthSubDl[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, dAmpMouthTexture),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(dAmpMouthVertices, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

const Gfx dAmpMouthDl[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, (G_TX_WRAP | G_TX_NOMIRROR), G_TX_NOMASK, G_TX_NOLOD, (G_TX_WRAP | G_TX_NOMIRROR), G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, ((32 - 1) << G_TEXTURE_IMAGE_FRAC), ((32 - 1) << G_TEXTURE_IMAGE_FRAC)),
    gsSPDisplayList(dAmpMouthSubDl),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

static const Vtx dAmpBodyVertices[] = {
    {{{   -40,    -40,      0}, 0, ST_B(  0,  32), {0xff, 0xff, 0xff, 0xff}}},
    {{{    40,     40,      0}, 0, ST_B( 32,   0), {0xff, 0xff, 0xff, 0xff}}},
    {{{   -40,     40,      0}, 0, ST_B(  0,   0), {0xff, 0xff, 0xff, 0xff}}},
    {{{    40,    -40,      0}, 0, ST_B( 32,  32), {0xff, 0xff, 0xff, 0xff}}},
};

const Gfx dAmpBodySubDl[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, dAmpBodyTexture),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(dAmpBodyVertices, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

const Gfx dAmpBodyDl[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, (G_TX_WRAP | G_TX_NOMIRROR), G_TX_NOMASK, G_TX_NOLOD, (G_TX_WRAP | G_TX_NOMIRROR), G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, ((32 - 1) << G_TEXTURE_IMAGE_FRAC), ((32 - 1) << G_TEXTURE_IMAGE_FRAC)),
    gsSPDisplayList(dAmpBodySubDl),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
