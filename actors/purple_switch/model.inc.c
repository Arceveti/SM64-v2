// Purple Switch

// 0x0800C090
static const Lights1 purple_switch_seg8_lights_0800C090 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0800C0A8
ALIGNED8 static const Texture purple_switch_seg8_texture_base[] = {
#include "actors/purple_switch/purple_switch_base.rgba16.inc.c"
};

// 0x0800C128
ALIGNED8 static const Texture purple_switch_seg8_texture_exclamation_point[] = {
#include "actors/purple_switch/purple_switch_exclamation_point.rgba16.inc.c"
};

// 0x0800C528
static const Vtx purple_switch_seg8_vertex_0800C528[] = {
    {{{   102,      0,   -102}, 0, {     0,   -544}, {0x53, 0x5f, 0x00, 0xff}}},
    {{{    64,     36,    -64}, 0, {  1328,   -288}, {0x53, 0x5f, 0x00, 0xff}}},
    {{{    64,     36,     64}, 0, {  1328,  15<<5}, {0x53, 0x5f, 0x00, 0xff}}},
    {{{  -102,      0,   -102}, 0, {     0,  23<<5}, {0x00, 0x5f, 0xad, 0xff}}},
    {{{    64,     36,    -64}, 0, {  1328,   -288}, {0x00, 0x5f, 0xad, 0xff}}},
    {{{   102,      0,   -102}, 0, {     0,   -544}, {0x00, 0x5f, 0xad, 0xff}}},
    {{{   -64,     36,    -64}, 0, {  1328,  15<<5}, {0x00, 0x5f, 0xad, 0xff}}},
    {{{  -102,      0,    102}, 0, {     0,  23<<5}, {0xad, 0x5f, 0x00, 0xff}}},
    {{{   -64,     36,    -64}, 0, {  1328,   -288}, {0xad, 0x5f, 0x00, 0xff}}},
    {{{  -102,      0,   -102}, 0, {     0,   -544}, {0xad, 0x5f, 0x00, 0xff}}},
    {{{   -64,     36,     64}, 0, {  1328,  15<<5}, {0xad, 0x5f, 0x00, 0xff}}},
    {{{   102,      0,    102}, 0, {     0,   -544}, {0x00, 0x5f, 0x53, 0xff}}},
    {{{    64,     36,     64}, 0, {  1328,   -288}, {0x00, 0x5f, 0x53, 0xff}}},
    {{{   -64,     36,     64}, 0, {  1328,  15<<5}, {0x00, 0x5f, 0x53, 0xff}}},
    {{{  -102,      0,    102}, 0, {     0,  23<<5}, {0x00, 0x5f, 0x53, 0xff}}},
    {{{   102,      0,    102}, 0, {     0,  23<<5}, {0x53, 0x5f, 0x00, 0xff}}},
};

// 0x0800C628
static const Vtx purple_switch_seg8_vertex_0800C628[] = {
    {{{    64,     36,    -64}, 0, {   608,   -128}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   -64,     36,     64}, 0, {  -160,   1088}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{    64,     36,     64}, 0, {   608,   1088}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   -64,     36,    -64}, 0, {  -160,   -128}, {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x0800C668 - 0x0800C6E0
const Gfx purple_switch_seg8_dl_0800C668[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, purple_switch_seg8_texture_base),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 4 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&purple_switch_seg8_lights_0800C090.l, 1),
    gsSPLight(&purple_switch_seg8_lights_0800C090.a, 2),
    gsSPVertex(purple_switch_seg8_vertex_0800C528, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0,  2, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x0800C6E0 - 0x0800C718
const Gfx purple_switch_seg8_dl_0800C6E0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, purple_switch_seg8_texture_exclamation_point),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 32 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(purple_switch_seg8_vertex_0800C628, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0800C718 - 0x0800C7A8
const Gfx purple_switch_seg8_dl_0800C718[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 2, G_TX_NOLOD, G_TX_CLAMP, 4, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (16 - 1) << G_TEXTURE_IMAGE_FRAC, (4 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(purple_switch_seg8_dl_0800C668),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 4, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (16 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(purple_switch_seg8_dl_0800C6E0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
