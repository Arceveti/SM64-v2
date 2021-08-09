// 0x07019A98 - 0x07019B18
static const Vtx lll_seg7_vertex_sinking_rectangular_platform_top[] = {
    {{{     5,     41,   1024}, 0, {   -26,   1000}, {0x0d, 0x7e, 0x00, 0xff}}},
    {{{   384,      0,  -1024}, 0, {  1008,  -4112}, {0x0d, 0x7e, 0x00, 0xff}}},
    {{{     5,     41,  -1024}, 0, {   -16,  -4108}, {0x0d, 0x7e, 0x00, 0xff}}},
    {{{   384,      0,   1024}, 0, { 31<<5,  31<<5}, {0x0d, 0x7e, 0x00, 0xff}}},
    {{{  -384,      0,  -1024}, 0, {   -48,  -4040}, {0xf3, 0x7e, 0x00, 0xff}}},
    {{{     5,     41,   1024}, 0, {  1008,  31<<5}, {0xf3, 0x7e, 0x00, 0xff}}},
    {{{     5,     41,  -1024}, 0, { 31<<5,  -4052}, {0xf3, 0x7e, 0x00, 0xff}}},
    {{{  -384,      0,   1024}, 0, {   -26,   1006}, {0xf3, 0x7e, 0x00, 0xff}}},
};

// 0x07019B18 - 0x07019B78
static const Vtx lll_seg7_vertex_sinking_rectangular_platform_sides[] = {
    {{{  -384,      0,  -1024}, 0, {  7122,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{     5,     41,  -1024}, 0, {  4016,    662}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   384,      0,  -1024}, 0, { 31<<5,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   384,      0,   1024}, 0, {191<<5,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{     5,     41,   1024}, 0, { 96<<5,   -360}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -380,      0,   1024}, 0, {     0,    -32}, {0x00, 0x00, 0x7f, 0xff}}},
};

// 0x07019B78 - 0x07019BD0
static const Gfx lll_seg7_sub_dl_sinking_rectangular_platform_top[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, fire_09004000_gray_diagonal_checker),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&lll_seg7_lights_gray_0x3f_0xff_0x28.l, 1),
    gsSPLight(&lll_seg7_lights_gray_0x3f_0xff_0x28.a, 2),
    gsSPVertex(lll_seg7_vertex_sinking_rectangular_platform_top, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x07019BD0 - 0x07019C08
static const Gfx lll_seg7_sub_dl_sinking_rectangular_platform_sides[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, fire_09006000_black_bricks),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(lll_seg7_vertex_sinking_rectangular_platform_sides, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x07019C08 - 0x07019C80
const Gfx lll_seg7_dl_sinking_rectangular_platform[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(lll_seg7_sub_dl_sinking_rectangular_platform_top),
    gsSPDisplayList(lll_seg7_sub_dl_sinking_rectangular_platform_sides),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
