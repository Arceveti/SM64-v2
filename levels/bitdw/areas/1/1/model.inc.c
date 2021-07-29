// 0x07002000 - 0x07002080
static const Vtx bitdw_seg7_vertex_07002000[] = {
    {{{  2516,  -2358,   2961}, 0, { 31<<5,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  2414,  -2440,   3024}, 0, {     0,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  2516,  -2440,   3024}, 0, { 31<<5,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  2414,  -2358,   2961}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{ -3040,  -2767,   2961}, 0, { 31<<5,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{ -3140,  -2848,   3024}, 0, {     0,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{ -3040,  -2848,   3024}, 0, { 31<<5,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{ -3140,  -2767,   2961}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}},
};

// 0x07002080 - 0x070020C8
static const Gfx bitdw_seg7_dl_07002080[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_texture_metal_hole),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bitdw_seg7_vertex_07002000, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x070020C8 - 0x07002138
const Gfx bitdw_seg7_dl_070020C8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bitdw_seg7_dl_07002080),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
