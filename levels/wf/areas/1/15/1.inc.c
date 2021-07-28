// 0x0700A1E0 - 0x0700A1F8
static const Lights1 wf_seg7_lights_grass_with_tree_near = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0700A1F8 - 0x0700A2E8
static const Vtx wf_seg7_vertex_grass_with_tree_near_sides_1[] = {
    {{{ -1024,   -154,    768}, 0, {  1414,  15<<5}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{ -1536,    102,    256}, 0, {     0,      0}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{ -1536,   -154,    256}, 0, {     0,  15<<5}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{  1536,    102,   -768}, 0, { -7184,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  1536,    102,    256}, 0, { -9228,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  1536,   -154,    256}, 0, { -9228,  15<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  1536,   -154,   -768}, 0, { -7184,  15<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  1536,   -154,    256}, 0, { 31<<5,  15<<5}, {0x59, 0x00, 0x59, 0xff}}},
    {{{  1536,    102,    256}, 0, { 31<<5,      0}, {0x59, 0x00, 0x59, 0xff}}},
    {{{  1024,    102,    768}, 0, {  -456,      0}, {0x59, 0x00, 0x59, 0xff}}},
    {{{  1024,   -154,    768}, 0, {  -456,  15<<5}, {0x59, 0x00, 0x59, 0xff}}},
    {{{ -1536,   -154,    256}, 0, { 31<<5,  15<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{ -1536,    102,   -768}, 0, { -1056,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{ -1536,   -154,   -768}, 0, { -1056,  15<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{ -1536,    102,    256}, 0, { 31<<5,      0}, {0x81, 0x00, 0x00, 0xff}}},
};

// 0x0700A2E8 - 0x0700A358
static const Vtx wf_seg7_vertex_grass_with_tree_near_sides_2[] = {
    {{{  1024,   -154,    768}, 0, { 31<<5,  15<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{ -1024,    102,    768}, 0, { -3104,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{ -1024,   -154,    768}, 0, { -3104,  15<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{ -1024,   -154,    768}, 0, {  1414,  15<<5}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{ -1024,    102,    768}, 0, {  1414,      0}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{ -1536,    102,    256}, 0, {     0,      0}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{  1024,    102,    768}, 0, { 31<<5,      0}, {0x00, 0x00, 0x7f, 0xff}}},
};

// 0x0700A358 - 0x0700A3B8
static const Vtx wf_seg7_vertex_grass_with_tree_near_floor[] = {
    {{{  1536,    102,   -768}, 0, { 31<<5, 159<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{ -1024,    102,    768}, 0, { -2080,   1244}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  1024,    102,    768}, 0, { -2080,   5332}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{ -1536,    102,    256}, 0, { -1056,   7<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  1536,    102,    256}, 0, { -1056,   6354}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{ -1536,    102,   -768}, 0, { 31<<5,   7<<5}, {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x0700A3B8 - 0x0700A4A8
static const Vtx wf_seg7_vertex_grass_with_tree_near_flowers_sides_1[] = {
    {{{  -696,    102,    476}, 0, {     0,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -696,    133,    476}, 0, {     0,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -696,    133,    292}, 0, {191<<5,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  1280,    102,      0}, 0, {159<<5,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  1280,    154,    256}, 0, {     0,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  1280,    102,    256}, 0, {     0,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  1280,    154,      0}, 0, {159<<5,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  1152,    102,   -128}, 0, { 95<<5,  31<<5}, {0x59, 0x00, 0xa6, 0xff}}},
    {{{  1280,    154,      0}, 0, {  -578,      0}, {0x59, 0x00, 0xa6, 0xff}}},
    {{{  1280,    102,      0}, 0, {  -578,  31<<5}, {0x59, 0x00, 0xa6, 0xff}}},
    {{{  1152,    154,   -128}, 0, { 95<<5,      0}, {0x59, 0x00, 0xa6, 0xff}}},
    {{{  1280,    102,    256}, 0, { 95<<5,  31<<5}, {0x59, 0x00, 0x59, 0xff}}},
    {{{  1280,    154,    256}, 0, { 95<<5,      0}, {0x59, 0x00, 0x59, 0xff}}},
    {{{  1152,    154,    384}, 0, {  -578,      0}, {0x59, 0x00, 0x59, 0xff}}},
    {{{  1152,    102,    384}, 0, {  -578,  31<<5}, {0x59, 0x00, 0x59, 0xff}}},
};

// 0x0700A4A8 - 0x0700A598
static const Vtx wf_seg7_vertex_grass_with_tree_near_flowers_sides_2[] = {
    {{{  -420,    102,    200}, 0, {  4304,  31<<5}, {0x59, 0x00, 0xa7, 0xff}}},
    {{{  -328,    133,    292}, 0, {     0,      0}, {0x59, 0x00, 0xa7, 0xff}}},
    {{{  -328,    102,    292}, 0, {     0,  31<<5}, {0x59, 0x00, 0xa7, 0xff}}},
    {{{  -696,    102,    476}, 0, {     0,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -696,    133,    292}, 0, {191<<5,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -696,    102,    292}, 0, {191<<5,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -696,    102,    292}, 0, {  4304,  31<<5}, {0xa7, 0x00, 0xa7, 0xff}}},
    {{{  -696,    133,    292}, 0, {  4304,      0}, {0xa7, 0x00, 0xa7, 0xff}}},
    {{{  -604,    133,    200}, 0, {     0,      0}, {0xa7, 0x00, 0xa7, 0xff}}},
    {{{  -604,    102,    200}, 0, {     0,  31<<5}, {0xa7, 0x00, 0xa7, 0xff}}},
    {{{  -604,    102,    200}, 0, {191<<5,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -604,    133,    200}, 0, {191<<5,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -420,    133,    200}, 0, {     0,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -420,    102,    200}, 0, {     0,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -420,    133,    200}, 0, {  4304,      0}, {0x59, 0x00, 0xa7, 0xff}}},
};

// 0x0700A598 - 0x0700A688
static const Vtx wf_seg7_vertex_grass_with_tree_near_flowers_sides_3[] = {
    {{{  -604,    102,    568}, 0, {     0,  31<<5}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{  -604,    133,    568}, 0, {     0,      0}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{  -696,    133,    476}, 0, {  4304,      0}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{  -328,    102,    292}, 0, {191<<5,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -328,    133,    476}, 0, {     0,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -328,    102,    476}, 0, {     0,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -328,    133,    292}, 0, {191<<5,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -328,    102,    476}, 0, {     0,  31<<5}, {0x59, 0x00, 0x59, 0xff}}},
    {{{  -328,    133,    476}, 0, {     0,      0}, {0x59, 0x00, 0x59, 0xff}}},
    {{{  -420,    133,    568}, 0, {  4304,      0}, {0x59, 0x00, 0x59, 0xff}}},
    {{{  -420,    102,    568}, 0, {  4304,  31<<5}, {0x59, 0x00, 0x59, 0xff}}},
    {{{  -420,    102,    568}, 0, {     0,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -604,    133,    568}, 0, {191<<5,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -604,    102,    568}, 0, {191<<5,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -420,    133,    568}, 0, {     0,      0}, {0x00, 0x00, 0x7f, 0xff}}},
};

// 0x0700A688 - 0x0700A778
static const Vtx wf_seg7_vertex_grass_with_tree_near_flowers_sides_4[] = {
    {{{   768,    102,    256}, 0, {159<<5,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   768,    154,      0}, 0, {     0,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   768,    102,      0}, 0, {     0,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -604,    102,    568}, 0, {     0,  31<<5}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{  -696,    133,    476}, 0, {  4304,      0}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{  -696,    102,    476}, 0, {  4304,  31<<5}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{   896,    102,   -128}, 0, {159<<5,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   896,    154,   -128}, 0, {159<<5,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  1152,    154,   -128}, 0, {     0,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  1152,    102,   -128}, 0, {     0,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   768,    102,      0}, 0, {  3582,  31<<5}, {0xa7, 0x00, 0xa6, 0xff}}},
    {{{   768,    154,      0}, 0, {  3582,      0}, {0xa7, 0x00, 0xa6, 0xff}}},
    {{{   896,    154,   -128}, 0, {     0,      0}, {0xa7, 0x00, 0xa6, 0xff}}},
    {{{   896,    102,   -128}, 0, {     0,  31<<5}, {0xa7, 0x00, 0xa6, 0xff}}},
    {{{   768,    154,    256}, 0, {159<<5,      0}, {0x81, 0x00, 0x00, 0xff}}},
};

// 0x0700A778 - 0x0700A7F8
static const Vtx wf_seg7_vertex_grass_with_tree_near_flowers_sides_5[] = {
    {{{   896,    102,    384}, 0, {  3582,  31<<5}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{   896,    154,    384}, 0, {  3582,      0}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{   768,    154,    256}, 0, {     0,      0}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{   768,    102,    256}, 0, {     0,  31<<5}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{  1152,    102,    384}, 0, {159<<5,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   896,    154,    384}, 0, {     0,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   896,    102,    384}, 0, {     0,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  1152,    154,    384}, 0, {159<<5,      0}, {0x00, 0x00, 0x7f, 0xff}}},
};

// 0x0700A7F8 - 0x0700A8F8
static const Vtx wf_seg7_vertex_0700A7F8[] = {
    {{{  -696,    133,    292}, 0, { -2080,  -2080}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -420,    133,    568}, 0, { 31<<5,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -328,    133,    476}, 0, { 63<<5,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -328,    133,    292}, 0, { 63<<5,  -2080}, {0x00, 0x7f, 0x00, 0xff}}},
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

// 0x0700A8F8 - 0x0700A988
static const Gfx wf_seg7_sub_dl_grass_with_tree_near_sides[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09005000_dirt_with_grass),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&wf_seg7_lights_grass_with_tree_near.l, 1),
    gsSPLight(&wf_seg7_lights_grass_with_tree_near.a, 2),
    gsSPVertex(wf_seg7_vertex_grass_with_tree_near_sides_1, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle( 11, 14, 12, 0x0),
    gsSPVertex(wf_seg7_vertex_grass_with_tree_near_sides_2, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle(  0,  6,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700A988 - 0x0700A9D0
static const Gfx wf_seg7_sub_dl_grass_with_tree_near_floor[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09005800_grass),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(wf_seg7_vertex_grass_with_tree_near_floor, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  0,  5,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700A9D0 - 0x0700AB18
static const Gfx wf_seg7_sub_dl_grass_with_tree_near_flowers_sides[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09002800_flowers_side),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(wf_seg7_vertex_grass_with_tree_near_flowers_sides_1, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle( 11, 13, 14, 0x0),
    gsSPVertex(wf_seg7_vertex_grass_with_tree_near_flowers_sides_2, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle(  0, 14,  1, 0x0),
    gsSPVertex(wf_seg7_vertex_grass_with_tree_near_flowers_sides_3, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle( 11, 14, 12, 0x0),
    gsSPVertex(wf_seg7_vertex_grass_with_tree_near_flowers_sides_4, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle(  0, 14,  1, 0x0),
    gsSPVertex(wf_seg7_vertex_grass_with_tree_near_flowers_sides_5, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700AB18 - 0x0700ABA0
static const Gfx wf_seg7_sub_dl_grass_with_tree_near_flowers_top[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09002000_flowers_top),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(wf_seg7_vertex_0700A7F8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 0,  4,  5, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 0,  6,  1, 0x0,  0,  7,  6, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles( 8, 12, 13, 0x0,  8, 14, 12, 0x0),
    gsSP2Triangles( 8, 10, 15, 0x0,  8, 15, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700ABA0 - 0x0700AC70
const Gfx wf_seg7_dl_grass_with_tree_near[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(wf_seg7_sub_dl_grass_with_tree_near_sides),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(wf_seg7_sub_dl_grass_with_tree_near_floor),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(wf_seg7_sub_dl_grass_with_tree_near_flowers_sides),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(wf_seg7_sub_dl_grass_with_tree_near_flowers_top),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
