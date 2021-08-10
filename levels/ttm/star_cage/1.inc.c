// 0x07012F78 - 0x07012F90
static const Lights1 ttm_seg7_lights_monkey_cage_planks_top = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xfe, 0xfe, 0xfe, 0x28, 0x28, 0x28
);

// 0x07012F90 - 0x07012FA8
static const Lights1 ttm_seg7_lights_monkey_cage_planks_sides = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07012FA8 - 0x07013028
static const Vtx ttm_seg7_vertex_monkey_cage_planks_top[] = {
    {{{   -77,    -77,    -77}, 0, {     0,   -720}, {0x00, 0x81, 0x00, 0xff}}},
    {{{    77,    -77,     77}, 0, { 63<<5,    656}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   -77,    -77,     77}, 0, {     0,    656}, {0x00, 0x81, 0x00, 0xff}}},
    {{{    77,    -77,    -77}, 0, { 63<<5,   -720}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   -77,     77,     77}, 0, {     0,    656}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   -77,     77,    -77}, 0, {     0,   -720}, {0x00, 0x81, 0x00, 0xff}}},
    {{{    77,     77,    -77}, 0, { 63<<5,   -720}, {0x00, 0x81, 0x00, 0xff}}},
    {{{    77,     77,     77}, 0, { 63<<5,    656}, {0x00, 0x81, 0x00, 0xff}}},
};

// 0x07013028 - 0x07013108
static const Vtx ttm_seg7_vertex_monkey_cage_planks_sides_1[] = {
    {{{    77,    -51,     77}, 0, { 63<<5,    656}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{    77,    -51,    -77}, 0, { 63<<5,   -720}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   -77,    -51,    -77}, 0, {     0,   -720}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   -77,    102,    -77}, 0, {     0,   -720}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   -77,    102,     77}, 0, {     0,    656}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{    77,    102,     77}, 0, { 63<<5,    656}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   -77,     77,     77}, 0, {     0,    656}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   -77,    102,    -77}, 0, {     0,   -720}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   -77,     77,    -77}, 0, {     0,   -720}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   -77,    102,     77}, 0, {     0,    656}, {0x81, 0x00, 0x00, 0xff}}},
    {{{    77,    102,    -77}, 0, { 63<<5,   -720}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   -77,     77,    -77}, 0, {     0,   -720}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   -77,    102,    -77}, 0, {     0,   -720}, {0x00, 0x00, 0x81, 0xff}}},
    {{{    77,    102,    -77}, 0, { 63<<5,   -720}, {0x00, 0x00, 0x81, 0xff}}},
};

// 0x07013108 - 0x070131E8
static const Vtx ttm_seg7_vertex_monkey_cage_planks_sides_2[] = {
    {{{    77,     77,     77}, 0, { 63<<5,    656}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{    77,    102,     77}, 0, { 63<<5,    656}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   -77,    102,     77}, 0, {     0,    656}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   -77,     77,     77}, 0, {     0,    656}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{    77,     77,    -77}, 0, { 63<<5,   -720}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{    77,    102,     77}, 0, { 63<<5,    656}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{    77,     77,     77}, 0, { 63<<5,    656}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{    77,    102,    -77}, 0, { 63<<5,   -720}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   -77,     77,    -77}, 0, {     0,   -720}, {0x00, 0x00, 0x81, 0xff}}},
    {{{    77,    102,    -77}, 0, { 63<<5,   -720}, {0x00, 0x00, 0x81, 0xff}}},
    {{{    77,     77,    -77}, 0, { 63<<5,   -720}, {0x00, 0x00, 0x81, 0xff}}},
    {{{    77,    -77,    -77}, 0, { 63<<5,   -720}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{    77,    -51,     77}, 0, { 63<<5,    656}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{    77,    -77,     77}, 0, { 63<<5,    656}, {0x7f, 0x00, 0x00, 0xff}}},
};

// 0x070131E8 - 0x070132C8
static const Vtx ttm_seg7_vertex_monkey_cage_planks_sides_3[] = {
    {{{    77,    -77,     77}, 0, { 63<<5,    656}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{    77,    -51,     77}, 0, { 63<<5,    656}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   -77,    -51,     77}, 0, {     0,    656}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{    77,    -77,    -77}, 0, { 63<<5,   -720}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{    77,    -51,    -77}, 0, { 63<<5,   -720}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{    77,    -51,     77}, 0, { 63<<5,    656}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{    77,    -51,     77}, 0, { 63<<5,    656}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   -77,    -51,    -77}, 0, {     0,   -720}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   -77,    -51,     77}, 0, {     0,    656}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   -77,    -77,     77}, 0, {     0,    656}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   -77,    -77,    -77}, 0, {     0,   -720}, {0x00, 0x00, 0x81, 0xff}}},
    {{{    77,    -51,    -77}, 0, { 63<<5,   -720}, {0x00, 0x00, 0x81, 0xff}}},
    {{{    77,    -77,    -77}, 0, { 63<<5,   -720}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   -77,    -51,    -77}, 0, {     0,   -720}, {0x00, 0x00, 0x81, 0xff}}},
};

// 0x070132C8 - 0x07013308
static const Vtx ttm_seg7_vertex_monkey_cage_planks_sides_4[] = {
    {{{   -77,    -77,     77}, 0, {     0,    656}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   -77,    -51,     77}, 0, {     0,    656}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   -77,    -51,    -77}, 0, {     0,   -720}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   -77,    -77,    -77}, 0, {     0,   -720}, {0x81, 0x00, 0x00, 0xff}}},
};

// 0x07013308 - 0x07013430
static const Gfx ttm_seg7_sub_dl_monkey_cage_planks[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_09007000_wood_planks),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttm_seg7_lights_monkey_cage_planks_top.l, 1),
    gsSPLight(&ttm_seg7_lights_monkey_cage_planks_top.a, 2),
    gsSPVertex(ttm_seg7_vertex_monkey_cage_planks_top, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPLight(&ttm_seg7_lights_monkey_cage_planks_sides.l, 1),
    gsSPLight(&ttm_seg7_lights_monkey_cage_planks_sides.a, 2),
    gsSPVertex(ttm_seg7_vertex_monkey_cage_planks_sides_1, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles( 3,  5, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_monkey_cage_planks_sides_2, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(ttm_seg7_vertex_monkey_cage_planks_sides_3, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  0,  2,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(ttm_seg7_vertex_monkey_cage_planks_sides_4, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07013430 - 0x070134A0
const Gfx ttm_seg7_dl_monkey_cage_planks[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttm_seg7_sub_dl_monkey_cage_planks),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
