// 0x0700B028 - 0x0700B040
static const Lights1 wf_seg7_lights_grass_with_flowers = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0700B070 - 0x0700B160
static const Vtx wf_seg7_vertex_grass_with_flowers_sides_1[] = {
    {{{     0,   -256,  -2304}, 0, { 31<<5,  15<<5}, {0x59, 0x00, 0xa7, 0xff}}},
    {{{   512,      0,  -1792}, 0, {  -454,      0}, {0x59, 0x00, 0xa7, 0xff}}},
    {{{   512,   -256,  -1792}, 0, {  -454,  15<<5}, {0x59, 0x00, 0xa7, 0xff}}},
    {{{  -512,   -256,  -2304}, 0, { 31<<5,  15<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -512,      0,  -2304}, 0, { 31<<5,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{     0,      0,  -2304}, 0, {     0,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{     0,   -256,  -2304}, 0, {     0,  15<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{     0,      0,  -2304}, 0, { 31<<5,      0}, {0x59, 0x00, 0xa7, 0xff}}},
};

// 0x0700B160 - 0x0700B1A0
static const Vtx wf_seg7_vertex_grass_with_flowers_sides_2[] = {
    {{{   512,   -256,  -1792}, 0, { 31<<5,  15<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   512,      0,   2304}, 0, { -7184,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   512,   -256,   2304}, 0, { -7184,  15<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   512,      0,  -1792}, 0, { 31<<5,      0}, {0x7f, 0x00, 0x00, 0xff}}},
};

// 0x0700B1A0 - 0x0700B210
static const Vtx wf_seg7_vertex_grass_with_flowers_floor[] = {
    {{{   512,      0,   2304}, 0, { 31<<5,   6354}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   512,      0,  -1792}, 0, {  9166,   6354}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -512,      0,   2304}, 0, { 31<<5,   4310}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{     0,      0,  -2304}, 0, { 10188,   5332}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -512,      0,  -2304}, 0, { 10188,   4310}, {0x00, 0x7f, 0x00, 0xff}}},

};

// 0x0700B210 - 0x0700B300
static const Vtx wf_seg7_vertex_grass_with_flowers_flowers_side_1[] = {
    {{{  -256,      0,   -512}, 0, {799<<5,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -256,     51,   -768}, 0, {639<<5,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -256,      0,   -768}, 0, {639<<5,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -256,      0,  -1536}, 0, {     0,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -256,     51,  -1536}, 0, {     0,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -256,     51,  -1792}, 0, {159<<5,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -256,      0,  -1792}, 0, {159<<5,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   128,      0,  -1920}, 0, {127<<5,  31<<5}, {0x59, 0x00, 0xa7, 0xff}}},
    {{{   128,     51,  -1920}, 0, {127<<5,      0}, {0x59, 0x00, 0xa7, 0xff}}},
    {{{   256,     51,  -1792}, 0, {   448,      0}, {0x59, 0x00, 0xa7, 0xff}}},
    {{{   256,      0,  -1792}, 0, {   448,  31<<5}, {0x59, 0x00, 0xa7, 0xff}}},
    {{{  -128,      0,  -1920}, 0, {     0,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -128,     51,  -1920}, 0, {     0,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   128,     51,  -1920}, 0, {159<<5,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   128,      0,  -1920}, 0, {159<<5,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
};

// 0x0700B300 - 0x0700B3F0
static const Vtx wf_seg7_vertex_grass_with_flowers_flowers_side_2[] = {
    {{{   128,      0,   -896}, 0, {-11418,  31<<5}, {0x59, 0x00, 0xa7, 0xff}}},
    {{{   256,     51,   -768}, 0, {-15040,      0}, {0x59, 0x00, 0xa7, 0xff}}},
    {{{   256,      0,   -768}, 0, {-15040,  31<<5}, {0x59, 0x00, 0xa7, 0xff}}},
    {{{  -256,      0,   -512}, 0, {799<<5,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -256,     51,   -512}, 0, {799<<5,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -256,     51,   -768}, 0, {639<<5,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -256,      0,   -768}, 0, { 18034,  31<<5}, {0xa7, 0x00, 0xa7, 0xff}}},
    {{{  -256,     51,   -768}, 0, { 18034,      0}, {0xa7, 0x00, 0xa7, 0xff}}},
    {{{  -128,     51,   -896}, 0, { 14422,      0}, {0xa7, 0x00, 0xa7, 0xff}}},
    {{{  -128,      0,   -896}, 0, { 14422,  31<<5}, {0xa7, 0x00, 0xa7, 0xff}}},
    {{{  -128,      0,   -896}, 0, {159<<5,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   128,     51,   -896}, 0, {     0,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   128,      0,   -896}, 0, {     0,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -128,     51,   -896}, 0, {159<<5,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   128,     51,   -896}, 0, {-11418,      0}, {0x59, 0x00, 0xa7, 0xff}}},
};

// 0x0700B3F0 - 0x0700B4E0
static const Vtx wf_seg7_vertex_grass_with_flowers_flowers_side_3[] = {
    {{{  -128,      0,   -384}, 0, {  3582,  31<<5}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{  -256,     51,   -512}, 0, {     0,      0}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{  -256,      0,   -512}, 0, {     0,  31<<5}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{   256,      0,   -768}, 0, { 31<<5,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   256,     51,   -512}, 0, { -4118,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   256,      0,   -512}, 0, { -4118,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   256,     51,   -768}, 0, { 31<<5,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   256,      0,   -512}, 0, { 95<<5,  31<<5}, {0x59, 0x00, 0x59, 0xff}}},
    {{{   256,     51,   -512}, 0, { 95<<5,      0}, {0x59, 0x00, 0x59, 0xff}}},
    {{{   128,     51,   -384}, 0, {  -578,      0}, {0x59, 0x00, 0x59, 0xff}}},
    {{{   128,      0,   -384}, 0, {  -578,  31<<5}, {0x59, 0x00, 0x59, 0xff}}},
    {{{   128,      0,   -384}, 0, {159<<5,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   128,     51,   -384}, 0, {159<<5,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -128,     51,   -384}, 0, {     0,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -128,      0,   -384}, 0, {     0,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
};

// 0x0700B4E0 - 0x0700B5D0
static const Vtx wf_seg7_vertex_grass_with_flowers_flowers_side_4[] = {
    {{{   256,      0,  -1536}, 0, {127<<5,  31<<5}, {0x59, 0x00, 0x59, 0xff}}},
    {{{   256,     51,  -1536}, 0, {127<<5,      0}, {0x59, 0x00, 0x59, 0xff}}},
    {{{   128,     51,  -1408}, 0, {   448,      0}, {0x59, 0x00, 0x59, 0xff}}},
    {{{  -128,      0,   -384}, 0, {  3582,  31<<5}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{  -128,     51,   -384}, 0, {  3582,      0}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{  -256,     51,   -512}, 0, {     0,      0}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{  -128,      0,  -1408}, 0, {   448,  31<<5}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{  -256,     51,  -1536}, 0, {127<<5,      0}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{  -256,      0,  -1536}, 0, {127<<5,  31<<5}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{  -128,     51,  -1408}, 0, {   448,      0}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{   128,      0,  -1408}, 0, {159<<5,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   128,     51,  -1408}, 0, {159<<5,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -128,     51,  -1408}, 0, {     0,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -128,      0,  -1408}, 0, {     0,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   128,      0,  -1408}, 0, {   448,  31<<5}, {0x59, 0x00, 0x59, 0xff}}},
};

// 0x0700B5D0 - 0x0700B650
static const Vtx wf_seg7_vertex_grass_with_flowers_flowers_side_5[] = {
    {{{   256,      0,  -1792}, 0, {159<<5,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   256,     51,  -1792}, 0, {159<<5,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   256,     51,  -1536}, 0, {     0,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   256,      0,  -1536}, 0, {     0,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -256,      0,  -1792}, 0, {   448,  31<<5}, {0xa7, 0x00, 0xa7, 0xff}}},
    {{{  -256,     51,  -1792}, 0, {   448,      0}, {0xa7, 0x00, 0xa7, 0xff}}},
    {{{  -128,     51,  -1920}, 0, {127<<5,      0}, {0xa7, 0x00, 0xa7, 0xff}}},
    {{{  -128,      0,  -1920}, 0, {127<<5,  31<<5}, {0xa7, 0x00, 0xa7, 0xff}}},
};

// 0x0700B650 - 0x0700B750
static const Vtx wf_seg7_vertex_grass_with_flowers_flowers_top[] = {
    {{{  -256,     51,   -768}, 0, { 95<<5,  -3104}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -128,     51,   -384}, 0, {     0,  -2080}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   128,     51,   -384}, 0, {     0,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   128,     51,   -896}, 0, {127<<5,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -128,     51,   -896}, 0, {127<<5,  -2080}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -256,     51,   -512}, 0, { 31<<5,  -3104}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   256,     51,   -512}, 0, { 31<<5,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   256,     51,   -768}, 0, { 95<<5,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -256,     51,  -1792}, 0, { 11210,  -3104}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   128,     51,  -1920}, 0, { 12232,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -128,     51,  -1920}, 0, { 12232,  -2080}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   256,     51,  -1792}, 0, { 11210,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -256,     51,  -1536}, 0, {  9166,  -3104}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -128,     51,  -1408}, 0, {  8144,  -2080}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   128,     51,  -1408}, 0, {  8144,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   256,     51,  -1536}, 0, {  9168,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x0700B790 - 0x0700B808
static const Gfx wf_seg7_sub_dl_grass_with_flowers_sides[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09005000_dirt_with_grass),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&wf_seg7_lights_grass_with_flowers.l, 1),
    gsSPLight(&wf_seg7_lights_grass_with_flowers.a, 2),
    gsSPVertex(wf_seg7_vertex_grass_with_flowers_sides_1, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  7,  1, 0x0),
    gsSP2Triangles( 3,  4,  5, 0x0,  3,  5,  6, 0x0),
    gsSPVertex(wf_seg7_vertex_grass_with_flowers_sides_2, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700B808 - 0x0700B858
static const Gfx wf_seg7_sub_dl_grass_with_flowers_floor[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09005800_grass),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(wf_seg7_vertex_grass_with_flowers_floor, 5, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  1, 0x0),
    gsSP1Triangle(  3,  4,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700B858 - 0x0700B9A0
static const Gfx wf_seg7_sub_dl_grass_with_flowers_flowers_side[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09002800_flowers_side),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(wf_seg7_vertex_grass_with_flowers_flowers_side_1, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle( 11, 13, 14, 0x0),
    gsSPVertex(wf_seg7_vertex_grass_with_flowers_flowers_side_2, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle(  0, 14,  1, 0x0),
    gsSPVertex(wf_seg7_vertex_grass_with_flowers_flowers_side_3, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle( 11, 13, 14, 0x0),
    gsSPVertex(wf_seg7_vertex_grass_with_flowers_flowers_side_4, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle(  0,  2, 14, 0x0),
    gsSPVertex(wf_seg7_vertex_grass_with_flowers_flowers_side_5, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700B9A0 - 0x0700BA28
static const Gfx wf_seg7_sub_dl_grass_with_flowers_flowers_top[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09002000_flowers_top),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(wf_seg7_vertex_grass_with_flowers_flowers_top, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 0,  5,  1, 0x0,  0,  2,  6, 0x0),
    gsSP2Triangles( 0,  6,  7, 0x0,  0,  7,  3, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles( 8, 12, 13, 0x0,  8, 13, 14, 0x0),
    gsSP2Triangles( 8, 15, 11, 0x0,  8, 14, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700BA28 - 0x0700BB18
const Gfx wf_seg7_dl_grass_with_flowers[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(wf_seg7_sub_dl_grass_with_flowers_sides),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(wf_seg7_sub_dl_grass_with_flowers_floor),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(wf_seg7_sub_dl_grass_with_flowers_flowers_side),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(wf_seg7_sub_dl_grass_with_flowers_flowers_top),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
