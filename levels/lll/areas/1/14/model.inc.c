// 0x07017938 - 0x070179F8
static const Vtx lll_seg7_vertex_flamethrower_sides[] = {
    {{{  -128,      0,   -128}, 0, { 31<<5,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -128,    307,   -128}, 0, { 31<<5,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   128,    307,   -128}, 0, {   144,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   128,      0,   -128}, 0, {   144,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -128,      0,    128}, 0, {   816,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -128,    307,    128}, 0, {   816,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -128,    307,   -128}, 0, {     0,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -128,      0,   -128}, 0, {     0,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   128,      0,   -128}, 0, {   816,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   128,    307,    128}, 0, {     0,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   128,      0,    128}, 0, {     0,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   128,    307,   -128}, 0, {   816,      0}, {0x7f, 0x00, 0x00, 0xff}}},
};

// 0x070179F8 - 0x07017A38
static const Vtx lll_seg7_vertex_flamethrower_top[] = {
    {{{  -128,    307,   -128}, 0, {     0,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   128,    307,    128}, 0, {   816,    816}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   128,    307,   -128}, 0, {   816,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -128,    307,    128}, 0, {     0,    816}, {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x07017A38 - 0x07017A78
static const Vtx lll_seg7_vertex_flamethrower_front[] = {
    {{{   128,      0,    128}, 0, { 31<<5,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   128,    307,    128}, 0, { 31<<5,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -128,    307,    128}, 0, {     0,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -128,      0,    128}, 0, {     0,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
};

// 0x07017A78 - 0x07017AE0
static const Gfx lll_seg7_sub_dl_flamethrower_sides[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, fire_09006800_black_bricks_with_lava),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&lll_seg7_lights_gray_0x3f_0xff_0x28.l, 1),
    gsSPLight(&lll_seg7_lights_gray_0x3f_0xff_0x28.a, 2),
    gsSPVertex(lll_seg7_vertex_flamethrower_sides, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x07017AE0 - 0x07017B18
static const Gfx lll_seg7_sub_dl_flamethrower_top[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, fire_09006000_black_bricks),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(lll_seg7_vertex_flamethrower_top, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07017B18 - 0x07017B50
static const Gfx lll_seg7_sub_dl_flamethrower_front[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, fire_09008800_black_bricks_with_lava_and_hole),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(lll_seg7_vertex_flamethrower_front, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07017B50 - 0x07017BE8
const Gfx lll_seg7_dl_flamethrower[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(lll_seg7_sub_dl_flamethrower_sides),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(lll_seg7_sub_dl_flamethrower_top),
    gsSPDisplayList(lll_seg7_sub_dl_flamethrower_front),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
