// 0x0701A080 - 0x0701A120
static const Vtx lll_seg7_vertex_tilting_square_platform_sides[] = {
    {{{     0,      0,      0}, 0, ST_B(    16,     16), {0xff, 0x00, 0x00, 0xff}}},
    {{{  -307,    307,   -307}, 0, ST_B(     0,     32), {0xff, 0x00, 0x00, 0xff}}},
    {{{   307,    307,   -307}, 0, ST_B(    32,     32), {0xff, 0x00, 0x00, 0xff}}},
    {{{   307,    307,    307}, 0, ST_B(    32,      0), {0xff, 0x00, 0x00, 0xff}}},
    {{{  -307,    307,    307}, 0, ST_B(     0,      0), {0xff, 0x00, 0x00, 0xff}}},
    {{{     0,      0,      0}, 0, ST_B(    16,     16), {0xc8, 0x00, 0x00, 0xff}}},
    {{{  -307,    307,    307}, 0, ST_B(     0,      0), {0xc8, 0x00, 0x00, 0xff}}},
    {{{  -307,    307,   -307}, 0, ST_B(     0,     32), {0xc8, 0x00, 0x00, 0xff}}},
    {{{   307,    307,   -307}, 0, ST_B(    32,     32), {0xc8, 0x00, 0x00, 0xff}}},
    {{{   307,    307,    307}, 0, ST_B(    32,      0), {0xc8, 0x00, 0x00, 0xff}}},
};

// 0x0701A120 - 0x0701A160
static const Vtx lll_seg7_vertex_tilting_square_platform_top[] = {
    {{{   307,    307,    307}, 0, ST_B(    32,     32), {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -307,    307,   -307}, 0, ST_B(     0,      0), {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -307,    307,    307}, 0, ST_B(     0,     32), {0x00, 0x7f, 0x00, 0xff}}},
    {{{   307,    307,   -307}, 0, ST_B(    32,      0), {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x0701A160 - 0x0701A1A8
static const Gfx lll_seg7_sub_dl_tilting_square_platform_sides[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, fire_09001800_gray_rock),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(lll_seg7_vertex_tilting_square_platform_sides, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  5,  8,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x0701A1A8 - 0x0701A1F0
static const Gfx lll_seg7_sub_dl_tilting_square_platform_top[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, fire_09004000_gray_diagonal_checker),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&lll_seg7_lights_gray_0x3f_0xff_0x28.l, 1),
    gsSPLight(&lll_seg7_lights_gray_0x3f_0xff_0x28.a, 2),
    gsSPVertex(lll_seg7_vertex_tilting_square_platform_top, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0701A1F0 - 0x0701A270
const Gfx lll_seg7_dl_tilting_square_platform[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(lll_seg7_sub_dl_tilting_square_platform_sides),
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPDisplayList(lll_seg7_sub_dl_tilting_square_platform_top),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
