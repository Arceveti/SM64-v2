// 0x07017590 - 0x07017650
static const Vtx lll_seg7_vertex_arrows_slope_top[] = {
    {{{  -512,    154,    128}, 0, {   -16,   7<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -512,    154,    512}, 0, {   -16,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   512,    154,    512}, 0, { 31<<5,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   512,    154,    128}, 0, { 31<<5,   7<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -512,    307,   -128}, 0, {   -16,  23<<5}, {0x00, 0x6c, 0x41, 0xff}}},
    {{{  -512,    154,    128}, 0, {   -16,   1248}, {0x00, 0x6c, 0x41, 0xff}}},
    {{{   512,    154,    128}, 0, { 31<<5,   1248}, {0x00, 0x6c, 0x41, 0xff}}},
    {{{   512,    307,   -128}, 0, { 31<<5,  23<<5}, {0x00, 0x6c, 0x41, 0xff}}},
    {{{  -512,    307,   -512}, 0, {   -16,  -1056}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -512,    307,   -128}, 0, {   -16,   -288}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   512,    307,   -128}, 0, { 31<<5,   -288}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   512,    307,   -512}, 0, { 31<<5,  -1056}, {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x07017650 - 0x07017740
static const Vtx lll_seg7_vertex_arrows_slope_sides_1[] = {
    {{{  -512,      0,   -512}, 0, {127<<5,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   512,    307,   -512}, 0, {   656,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   512,      0,   -512}, 0, {   656,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   512,      0,   -512}, 0, {  2352,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   512,    307,   -512}, 0, {  2352,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   512,    307,   -128}, 0, {  1072,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   512,    154,    128}, 0, {  7<<5,  15<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   512,      0,    512}, 0, { -1056,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   512,    154,    512}, 0, { -1056,  15<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -512,    154,    128}, 0, {  2096,  15<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -512,    307,   -128}, 0, {  1248,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -512,      0,   -512}, 0, {     0,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -512,      0,    512}, 0, {  3376,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -512,    154,    512}, 0, {  3376,  15<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -512,    307,   -512}, 0, {     0,      0}, {0x81, 0x00, 0x00, 0xff}}},
};

// 0x07017740 - 0x070177B0
static const Vtx lll_seg7_vertex_arrows_slope_sides_2[] = {
    {{{   512,      0,    512}, 0, {  3376,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -512,    154,    512}, 0, {     0,  15<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -512,      0,    512}, 0, {     0,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -512,      0,   -512}, 0, {127<<5,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -512,    307,   -512}, 0, {127<<5,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   512,    307,   -512}, 0, {   656,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   512,    154,    512}, 0, {  3376,  15<<5}, {0x00, 0x00, 0x7f, 0xff}}},
};

// 0x070177B0 - 0x07017818
static const Gfx lll_seg7_sub_dl_arrows_slope_top[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, fire_0900B800_arrows_platform),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&lll_seg7_lights_gray_0x3f_0xff_0x28.l, 1),
    gsSPLight(&lll_seg7_lights_gray_0x3f_0xff_0x28.a, 2),
    gsSPVertex(lll_seg7_vertex_arrows_slope_top, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x07017818 - 0x070178A8
static const Gfx lll_seg7_sub_dl_arrows_slope_sides[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, fire_09007800_bricks_with_lava),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(lll_seg7_vertex_arrows_slope_sides_1, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  3,  6,  7, 0x0),
    gsSP2Triangles( 6,  8,  7, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13,  9, 0x0, 12,  9, 11, 0x0),
    gsSP1Triangle( 10, 14, 11, 0x0),
    gsSPVertex(lll_seg7_vertex_arrows_slope_sides_2, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle(  0,  6,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x070178A8 - 0x07017938
const Gfx lll_seg7_dl_arrows_slope[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(lll_seg7_sub_dl_arrows_slope_top),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(lll_seg7_sub_dl_arrows_slope_sides),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
