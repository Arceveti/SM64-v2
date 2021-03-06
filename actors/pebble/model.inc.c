// Pebble

// 0x0301C2C0
static const Vtx pebble_seg3_vertex_30x30[] = {
    {{{   -15,    -15,      0}, 0, ST_B(     0,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{    15,    -15,      0}, 0, ST_B(    32,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{    15,     15,      0}, 0, ST_B(    32,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{   -15,     15,      0}, 0, ST_B(     0,      0), {0xff, 0xff, 0xff, 0xff}}},
};

// 0x0301C300
ALIGNED8 static const Texture pebble_seg3_texture_pebble[] = {
#include "actors/pebble/pebble.rgba16.inc.c"
};

// 0x0301CB00 - 0x0301CB98
const Gfx pebble_seg3_dl_pebble[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPLoadTextureBlock(pebble_seg3_texture_pebble, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_CLAMP, G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPVertex(pebble_seg3_vertex_30x30, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
