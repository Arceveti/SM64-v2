// 0x07009458 - 0x07009470
static const Lights1 vcutm_seg7_lights_seesaw_sides = gdSPDefLights1(
    0x22, 0x22, 0x22,
    0x88, 0x88, 0x88, 0x28, 0x28, 0x28
);

// 0x07009470 - 0x07009488
static const Lights1 vcutm_seg7_lights_seesaw_top = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07009488 - 0x07009578
static const Vtx vcutm_seg7_vertex_seesaw_sides_1[] = {
    {{{   307,      0,    768}, 0, {     0,   1960}, {0x00, 0xc8, 0x71, 0xff}}},
    {{{  -307,    102,    819}, 0, {     0,    152}, {0x00, 0xc8, 0x71, 0xff}}},
    {{{  -307,      0,    768}, 0, {     0,   3<<5}, {0x00, 0xc8, 0x71, 0xff}}},
    {{{   307,    102,    819}, 0, {     0,  63<<5}, {0x00, 0xc8, 0x71, 0xff}}},
    {{{   307,      0,   -768}, 0, { 31<<5,   1960}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   307,    102,    819}, 0, {     0,  63<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   307,      0,    768}, 0, {     0,   1960}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   307,    102,   -819}, 0, { 31<<5,  63<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   307,      0,    768}, 0, {     0,   1960}, {0x00, 0x81, 0x00, 0xff}}},
    {{{  -307,      0,    768}, 0, {     0,   3<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{  -307,      0,   -768}, 0, { 31<<5,   3<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   307,      0,   -768}, 0, { 31<<5,   1960}, {0x00, 0x81, 0x00, 0xff}}},
    {{{  -307,      0,    768}, 0, {     0,   3<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -307,    102,   -819}, 0, { 31<<5,    152}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -307,      0,   -768}, 0, { 31<<5,   3<<5}, {0x81, 0x00, 0x00, 0xff}}},
};

// 0x07009578 - 0x070095E8
static const Vtx vcutm_seg7_vertex_seesaw_sides_2[] = {
    {{{  -307,      0,   -768}, 0, { 31<<5,   3<<5}, {0x00, 0xc8, 0x8f, 0xff}}},
    {{{   307,    102,   -819}, 0, { 31<<5,  63<<5}, {0x00, 0xc8, 0x8f, 0xff}}},
    {{{   307,      0,   -768}, 0, { 31<<5,   1960}, {0x00, 0xc8, 0x8f, 0xff}}},
    {{{  -307,    102,   -819}, 0, { 31<<5,    152}, {0x00, 0xc8, 0x8f, 0xff}}},
    {{{  -307,      0,    768}, 0, {     0,   3<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -307,    102,    819}, 0, {     0,    152}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -307,    102,   -819}, 0, { 31<<5,    152}, {0x81, 0x00, 0x00, 0xff}}},
};

// 0x070095E8 - 0x07009628
static const Vtx vcutm_seg7_vertex_seesaw_top[] = {
    {{{   307,    102,   -819}, 0, { 31<<5,  63<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -307,    102,   -819}, 0, { 31<<5,    152}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -307,    102,    819}, 0, {     0,    152}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   307,    102,    819}, 0, {     0,  63<<5}, {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x07009628 - 0x070096E0
static const Gfx vcutm_seg7_sub_dl_seesaw[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, vcutm_seg7_texture_wood),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&vcutm_seg7_lights_seesaw_sides.l, 1),
    gsSPLight(&vcutm_seg7_lights_seesaw_sides.a, 2),
    gsSPVertex(vcutm_seg7_vertex_seesaw_sides_1, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(vcutm_seg7_vertex_seesaw_sides_2, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP1Triangle( 4,  5,  6, 0x0),
    gsSPLight(&vcutm_seg7_lights_seesaw_top.l, 1),
    gsSPLight(&vcutm_seg7_lights_seesaw_top.a, 2),
    gsSPVertex(vcutm_seg7_vertex_seesaw_top, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x070096E0 - 0x07009750
const Gfx vcutm_seg7_dl_seesaw[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(vcutm_seg7_sub_dl_seesaw),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
