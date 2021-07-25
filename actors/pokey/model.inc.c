// Pokey

// 0x05011710
static const Vtx pokey_seg5_vertex_face[] = {
    {{{    26,     26,      0}, 0, { 31<<5,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   -26,     26,      0}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   -26,    -26,      0}, 0, {     0,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{    26,    -26,      0}, 0, { 31<<5,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
};

// 0x05011750
ALIGNED8 static const Texture pokey_seg5_texture_face[] = {
#include "actors/pokey/pokey_face.rgba16.inc.c"
};

// 0x05011F50
ALIGNED8 static const Texture pokey_seg5_texture_face_blink[] = {
#include "actors/pokey/pokey_face_blink.rgba16.inc.c"
};

// 0x05012750 - 0x05012798
const Gfx pokey_seg5_dl_face_material[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPEndDisplayList(),
};

// 0x05012798 - 0x050127D8
const Gfx pokey_seg5_sub_dl_head[] = {
    gsSPVertex(pokey_seg5_vertex_face, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x050127D8 - 0x05012808
const Gfx pokey_seg5_dl_face[] = {
    gsSPDisplayList(pokey_seg5_dl_face_material),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, pokey_seg5_texture_face),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(pokey_seg5_sub_dl_head),
    gsSPEndDisplayList(),
};

// 0x05012808 - 0x05012838
const Gfx pokey_seg5_dl_face_blink[] = {
    gsSPDisplayList(pokey_seg5_dl_face_material),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, pokey_seg5_texture_face_blink),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPDisplayList(pokey_seg5_sub_dl_head),
    gsSPEndDisplayList(),
};

// 0x05012838
static const Vtx pokey_seg5_vertex_body[] = {
    {{{    26,     26,      0}, 0, { 31<<5,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   -26,     26,      0}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   -26,    -26,      0}, 0, {     0,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{    26,    -26,      0}, 0, { 31<<5,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
};

// 0x05012878
ALIGNED8 static const Texture pokey_seg5_texture_body[] = {
#include "actors/pokey/pokey_body.rgba16.inc.c"
};

// 0x05013078 - 0x050130B0
const Gfx pokey_seg5_sub_dl_body[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, pokey_seg5_texture_body),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(pokey_seg5_vertex_body, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x050130B0 - 0x05013120
const Gfx pokey_seg5_dl_body[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(pokey_seg5_sub_dl_body),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
