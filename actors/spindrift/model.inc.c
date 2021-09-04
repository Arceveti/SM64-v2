// Spindrift


// 0x050006D0
ALIGNED8 static const Texture spindrift_seg5_texture_face[] = {
#include "actors/spindrift/spindrift_face.rgba16.inc.c"
};

// 0x05000ED0
ALIGNED8 static const Texture spindrift_seg5_texture_petal[] = {
#include "actors/spindrift/spindrift_petal.rgba16.inc.c"
};

// 0x050016D0
ALIGNED8 static const Texture spindrift_seg5_texture_leaf[] = {
#include "actors/spindrift/spindrift_leaf.rgba16.inc.c"
};

// 0x05001ED0
ALIGNED8 static const Texture spindrift_seg5_texture_head[] = {
#include "actors/spindrift/spindrift_head.rgba16.inc.c"
};

// 0x050026D0
static const Vtx spindrift_seg5_vertex_head[] = {
    {{{   -56,    -56,      0}, 0, ST_B(     0,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{    56,     56,      0}, 0, ST_B(    32,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{   -56,     56,      0}, 0, ST_B(     0,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{    56,    -56,      0}, 0, ST_B(    32,     32), {0xff, 0xff, 0xff, 0xff}}},
};

// 0x05002710 - 0x05002748
const Gfx spindrift_seg5_sub_dl_head[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spindrift_seg5_texture_head),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(spindrift_seg5_vertex_head, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x05002748 - 0x050027B8
const Gfx spindrift_seg5_dl_head[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(spindrift_seg5_sub_dl_head),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x050027B8
static const Vtx spindrift_seg5_vertex_eyes[] = {
    {{{    26,   -112,    -48}, 0, ST_B(     0,     17), {0xff, 0xff, 0xff, 0xff}}},
    {{{    26,   -112,     48}, 0, ST_B(    32,     17), {0xff, 0xff, 0xff, 0xff}}},
    {{{   -32,   -112,    -48}, 0, ST_B(     0,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{   -32,   -112,     48}, 0, ST_B(    32,      0), {0xff, 0xff, 0xff, 0xff}}},
};

// 0x050027F8 - 0x05002830
const Gfx spindrift_seg5_sub_dl_eyes[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spindrift_seg5_texture_face),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(spindrift_seg5_vertex_eyes, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x05002830 - 0x050028A0
const Gfx spindrift_seg5_dl_eyes[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(spindrift_seg5_sub_dl_eyes),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x050028A0
static const Vtx spindrift_seg5_vertex_mouth[] = {
    {{{    36,   -109,    -45}, 0, {   -32,    572}, {0xff, 0xff, 0xff, 0xff}}},
    {{{    83,    -79,      0}, 0, { 15<<5,   1088}, {0xff, 0xff, 0xff, 0xff}}},
    {{{    36,   -109,     45}, 0, { 31<<5,    572}, {0xff, 0xff, 0xff, 0xff}}},
};

// 0x050028D0 - 0x05002900
const Gfx spindrift_seg5_sub_dl_mouth[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spindrift_seg5_texture_face),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(spindrift_seg5_vertex_mouth, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x05002900 - 0x05002970
const Gfx spindrift_seg5_dl_mouth[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(spindrift_seg5_sub_dl_mouth),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};

// 0x05002970
static const Lights1 spindrift_seg5_lights_leaves = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x05002988
static const Vtx spindrift_seg5_vertex_sepal_leaf_1[] = {
    {{{    19,     22,    102}, 0, {   192,   1200}, {0x90, 0x25, 0x2e, 0xff}}},
    {{{    13,     -6,      4}, 0, {  1032,    456}, {0x92, 0x3e, 0xf5, 0xff}}},
    {{{   -20,    -53,     69}, 0, {   256,   -192}, {0x90, 0x25, 0x2e, 0xff}}},
    {{{    34,    -56,    120}, 0, {   -64,    336}, {0xa9, 0x04, 0x5c, 0xff}}},
};

// 0x050029C8 - 0x05002A20
const Gfx spindrift_seg5_sub_dl_sepal_leaf_1[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spindrift_seg5_texture_leaf),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPLight(&spindrift_seg5_lights_leaves.l, 1),
    gsSPLight(&spindrift_seg5_lights_leaves.a, 2),
    gsSPVertex(spindrift_seg5_vertex_sepal_leaf_1, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

// 0x05002A20 - 0x05002A80
const Gfx spindrift_seg5_dl_sepal_leaf_1[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(spindrift_seg5_sub_dl_sepal_leaf_1),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x05002A98
static const Vtx spindrift_seg5_vertex_sepal_leaf_2[] = {
    {{{     0,    -33,    -69}, 0, {   512,   1102}, {0xa0, 0x40, 0xcd, 0xff}}},
    {{{    13,     -2,      0}, 0, {  1070,    400}, {0x9c, 0x4c, 0xf1, 0xff}}},
    {{{    53,     33,    -86}, 0, {   144,   -144}, {0xa0, 0x40, 0xcd, 0xff}}},
    {{{    62,    -15,   -122}, 0, {  -144,  15<<5}, {0xac, 0x2e, 0xae, 0xff}}},
};

// 0x05002AD8 - 0x05002B30
const Gfx spindrift_seg5_sub_dl_sepal_leaf_2[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spindrift_seg5_texture_leaf),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPLight(&spindrift_seg5_lights_leaves.l, 1),
    gsSPLight(&spindrift_seg5_lights_leaves.a, 2),
    gsSPVertex(spindrift_seg5_vertex_sepal_leaf_2, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

// 0x05002B30 - 0x05002B90
const Gfx spindrift_seg5_dl_sepal_leaf_2[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(spindrift_seg5_sub_dl_sepal_leaf_2),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x05002BA8
static const Vtx spindrift_seg5_vertex_flower_petals[] = {
    {{{    28,     -6,     21}, 0, { 15<<5,   1104}, {0x7e, 0xfd, 0x0b, 0xff}}},
    {{{    42,    -20,   -134}, 0, {  -192,      0}, {0x7e, 0xfd, 0x0b, 0xff}}},
    {{{    42,     98,    -96}, 0, {  1152,      0}, {0x7e, 0xfd, 0x0b, 0xff}}},
    {{{    28,    -21,      0}, 0, { 15<<5,   1104}, {0x7e, 0xf4, 0x00, 0xff}}},
    {{{    42,    122,    -61}, 0, {  -192,      0}, {0x7e, 0xf4, 0x00, 0xff}}},
    {{{    42,    122,     63}, 0, {  1152,      0}, {0x7e, 0xf4, 0x00, 0xff}}},
    {{{    28,     -6,    -20}, 0, { 15<<5,   1104}, {0x7e, 0xfd, 0xf5, 0xff}}},
    {{{    42,     97,     97}, 0, {  -192,      0}, {0x7e, 0xfd, 0xf5, 0xff}}},
    {{{    42,    -21,    135}, 0, {  1152,      0}, {0x7e, 0xfd, 0xf5, 0xff}}},
    {{{    28,     18,    -12}, 0, { 15<<5,   1104}, {0x7e, 0x09, 0xf9, 0xff}}},
    {{{    42,    -61,    122}, 0, {  -192,      0}, {0x7e, 0x09, 0xf9, 0xff}}},
    {{{    42,   -135,     21}, 0, {  1152,      0}, {0x7e, 0x09, 0xf9, 0xff}}},
    {{{    28,     18,     13}, 0, { 15<<5,   1104}, {0x7e, 0x0a, 0x07, 0xff}}},
    {{{    42,   -134,    -21}, 0, {  -192,      0}, {0x7e, 0x0a, 0x07, 0xff}}},
    {{{    42,    -61,   -122}, 0, {  1152,      0}, {0x7e, 0x0a, 0x07, 0xff}}},
};

// 0x05002C98 - 0x05002D08
const Gfx spindrift_seg5_sub_dl_flower_petals[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spindrift_seg5_texture_petal),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPLight(&spindrift_seg5_lights_leaves.l, 1),
    gsSPLight(&spindrift_seg5_lights_leaves.a, 2),
    gsSPVertex(spindrift_seg5_vertex_flower_petals, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};

// 0x05002D08 - 0x05002D68
const Gfx spindrift_seg5_dl_flower_petals[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(spindrift_seg5_sub_dl_flower_petals),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

// 0x05000030
static const Lights1 spindrift_seg5_lights_flower_stem_green = gdSPDefLights1(
    0x12, 0x2c, 0x00,
    0x49, 0xb2, 0x00, 0x28, 0x28, 0x28
);

// 0x05000048
static const Lights1 spindrift_seg5_lights_flower_stem_yellow = gdSPDefLights1(
    0x37, 0x3f, 0x00,
    0xdd, 0xff, 0x01, 0x28, 0x28, 0x28
);

// 0x05000078
static const Lights1 spindrift_seg5_lights_base_yellow = gdSPDefLights1(
    0x3f, 0x38, 0x00,
    0xff, 0xe2, 0x00, 0x28, 0x28, 0x28
);

// 0x05000090
static const Lights1 spindrift_seg5_lights_base_green = gdSPDefLights1(
    0x00, 0x0f, 0x00,
    0x00, 0x3f, 0x00, 0x28, 0x28, 0x28
);

// 0x050000C0
static const Vtx spindrift_seg5_vertex_flower_stem_yellow[] = {
    {{{    34,     40,     30}, 0, {     0,      0}, {0x7b, 0x17, 0x11, 0x00}}},
    {{{    34,    -16,     46}, 0, {     0,      0}, {0x7b, 0xf7, 0x1c, 0x00}}},
    {{{    46,      0,      0}, 0, {     0,      0}, {0x7f, 0x00, 0x00, 0x00}}},
    {{{    34,    -50,      0}, 0, {     0,      0}, {0x7b, 0xe3, 0x00, 0xff}}},
    {{{    34,    -16,    -46}, 0, {     0,      0}, {0x7b, 0xf7, 0xe3, 0xff}}},
    {{{    34,     40,    -28}, 0, {     0,      0}, {0x7b, 0x18, 0xee, 0xff}}},
};

// 0x05000120
static const Vtx spindrift_seg5_vertex_flower_stem_green[] = {
    {{{     6,      0,      0}, 0, {     0,      0}, {0x81, 0x00, 0x00, 0x00}}},
    {{{    34,    -16,    -46}, 0, {     0,      0}, {0x92, 0xee, 0xc4, 0x00}}},
    {{{    34,    -50,      0}, 0, {     0,      0}, {0x92, 0xc2, 0x00, 0x00}}},
    {{{    34,    -16,     46}, 0, {     0,      0}, {0x92, 0xec, 0x3b, 0xff}}},
    {{{    34,     40,    -28}, 0, {     0,      0}, {0x92, 0x32, 0xdb, 0xff}}},
    {{{    34,     40,     30}, 0, {     0,      0}, {0x92, 0x31, 0x25, 0xff}}},
};

// 0x05000180
static const Vtx spindrift_seg5_vertex_base_green[] = {
    {{{    70,     50,      0}, 0, {     0,      0}, {0xcb, 0x73, 0x00, 0x00}}},
    {{{    24,    -12,     56}, 0, {     0,      0}, {0xa9, 0x22, 0x54, 0x00}}},
    {{{   128,     -2,     94}, 0, {     0,      0}, {0xda, 0x45, 0x63, 0x00}}},
    {{{     0,     -5,      0}, 0, {     0,      0}, {0x8e, 0x37, 0x00, 0xff}}},
    {{{    24,    -12,    -56}, 0, {     0,      0}, {0xa8, 0x22, 0xac, 0xff}}},
    {{{     0,    -57,      0}, 0, {     0,      0}, {0x87, 0xdd, 0x00, 0xff}}},
    {{{    55,   -113,     57}, 0, {     0,      0}, {0xa5, 0xce, 0x48, 0xff}}},
    {{{   128,     -2,    -94}, 0, {     0,      0}, {0xda, 0x45, 0x9d, 0xff}}},
    {{{    55,   -113,    -57}, 0, {     0,      0}, {0xa5, 0xce, 0xb8, 0xff}}},
};

// 0x05000210
static const Vtx spindrift_seg5_vertex_base_yellow[] = {
    {{{    55,   -113,    -57}, 0, {     0,      0}, {0xa5, 0xce, 0xb8, 0x00}}},
    {{{    55,   -113,     57}, 0, {     0,      0}, {0xa5, 0xce, 0x48, 0x00}}},
    {{{     0,    -57,      0}, 0, {     0,      0}, {0x87, 0xdd, 0x00, 0x00}}},
    {{{   128,     -2,    -94}, 0, {     0,      0}, {0xda, 0x45, 0x9d, 0xff}}},
    {{{    24,    -12,    -56}, 0, {     0,      0}, {0xa8, 0x22, 0xac, 0xff}}},
    {{{   128,     -2,     94}, 0, {     0,      0}, {0xda, 0x45, 0x63, 0xff}}},
    {{{    24,    -12,     56}, 0, {     0,      0}, {0xa9, 0x22, 0x54, 0xff}}},
    {{{   138,     66,      0}, 0, {     0,      0}, {0xe3, 0x7b, 0x00, 0xff}}},
    {{{    70,     50,      0}, 0, {     0,      0}, {0xcb, 0x73, 0x00, 0xff}}},
};

// 0x050002A0 - 0x05000328
const Gfx spindrift_seg5_dl_flower_stem[] = {
    gsSPLight(&spindrift_seg5_lights_flower_stem_yellow.l, 1),
    gsSPLight(&spindrift_seg5_lights_flower_stem_yellow.a, 2),
    gsSPVertex(spindrift_seg5_vertex_flower_stem_yellow, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  2, 0x0),
    gsSP2Triangles( 1,  3,  2, 0x0,  4,  5,  2, 0x0),
    gsSP1Triangle( 5,  0,  2, 0x0),
    gsSPLight(&spindrift_seg5_lights_flower_stem_green.l, 1),
    gsSPLight(&spindrift_seg5_lights_flower_stem_green.a, 2),
    gsSPVertex(spindrift_seg5_vertex_flower_stem_green, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 1,  0,  4, 0x0,  4,  0,  5, 0x0),
    gsSP1Triangle( 5,  0,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x05000328 - 0x050003D8
const Gfx spindrift_seg5_dl_base[] = {
    gsSPClearGeometryMode(G_CULL_BACK),
    gsSPLight(&spindrift_seg5_lights_base_green.l, 1),
    gsSPLight(&spindrift_seg5_lights_base_green.a, 2),
    gsSPVertex(spindrift_seg5_vertex_base_green, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 0,  4,  3, 0x0,  1,  5,  6, 0x0),
    gsSP2Triangles( 7,  4,  0, 0x0,  5,  4,  8, 0x0),
    gsSP2Triangles( 5,  1,  3, 0x0,  4,  5,  3, 0x0),
    gsSPLight(&spindrift_seg5_lights_base_yellow.l, 1),
    gsSPLight(&spindrift_seg5_lights_base_yellow.a, 2),
    gsSPVertex(spindrift_seg5_vertex_base_yellow, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  4, 0x0),
    gsSP2Triangles( 1,  5,  6, 0x0,  5,  7,  8, 0x0),
    gsSP1Triangle( 8,  7,  3, 0x0),
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};
