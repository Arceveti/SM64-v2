// 0x0700AC70 - 0x0700AC88
static const Lights1 wf_seg7_lights_grass_with_tree_far = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0700AC88 - 0x0700ACE8
static const Vtx wf_seg7_vertex_grass_with_tree_far_floor[] = {
    {{{  1536,    102,   -768}, 0, { 31<<5, 159<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{ -1024,    102,    768}, 0, { -2080,   1244}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  1024,    102,    768}, 0, { -2080,   5332}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{ -1536,    102,    256}, 0, { -1056,   7<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  1536,    102,    256}, 0, { -1056,   6354}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{ -1536,    102,   -768}, 0, { 31<<5,   7<<5}, {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x0700ACE8 - 0x0700ADE8
static const Vtx wf_seg7_vertex_grass_with_tree_far_flowers_top[] = {
    {{{  -696,    133,    292}, 0, { -2080,  -2080}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -420,    133,    568}, 0, { 31<<5,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -327,    133,    476}, 0, { 63<<5,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -327,    133,    292}, 0, { 63<<5,  -2080}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -420,    133,    200}, 0, { 31<<5,  -3104}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -604,    133,    200}, 0, { -1056,  -3104}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -604,    133,    568}, 0, { -1056,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -696,    133,    476}, 0, { -2080,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   768,    154,      0}, 0, { 95<<5,  -3104}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   896,    154,    384}, 0, {     0,  -2080}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  1152,    154,    384}, 0, {     0,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   768,    154,    256}, 0, { 31<<5,  -3104}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  1152,    154,   -128}, 0, {127<<5,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   896,    154,   -128}, 0, {127<<5,  -2080}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  1280,    154,      0}, 0, { 95<<5,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  1280,    154,    256}, 0, { 31<<5,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x0700ADE8 - 0x0700AE40
static const Gfx wf_seg7_sub_dl_grass_with_tree_far_floor[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09005800_grass),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&wf_seg7_lights_grass_with_tree_far.l, 1),
    gsSPLight(&wf_seg7_lights_grass_with_tree_far.a, 2),
    gsSPVertex(wf_seg7_vertex_grass_with_tree_far_floor, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  0,  5,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700AE40 - 0x0700AEC8
static const Gfx wf_seg7_sub_dl_grass_with_tree_far_flowers_top[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09002000_flowers_top),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(wf_seg7_vertex_grass_with_tree_far_flowers_top, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 0,  4,  5, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 0,  6,  1, 0x0,  0,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles( 8, 12, 13, 0x0,  8, 14, 12, 0x0),
    gsSP2Triangles( 8, 10, 15, 0x0,  8, 15, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700AEC8 - 0x0700AF40
const Gfx wf_seg7_dl_grass_with_tree_far[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(wf_seg7_sub_dl_grass_with_tree_far_floor),
    gsSPDisplayList(wf_seg7_sub_dl_grass_with_tree_far_flowers_top),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
