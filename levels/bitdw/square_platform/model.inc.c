// 0x0700B290 - 0x0700B380
static const Vtx bitdw_seg7_vertex_0700B290[] = {
    {{{     0,    102,      0}, 0, { 31<<5,      0}, {0xb4, 0xee, 0xfe, 0xff}}},
    {{{   307,      0,    307}, 0, {     0,  63<<5}, {0xb4, 0xee, 0xfe, 0xff}}},
    {{{   307,      0,   -307}, 0, { 63<<5,  63<<5}, {0xb4, 0xee, 0xfe, 0xff}}},
    {{{     0,    102,      0}, 0, { 63<<5,      0}, {0xb4, 0xee, 0xfe, 0xff}}},
    {{{   307,      0,   -307}, 0, {     0,  63<<5}, {0xb4, 0xee, 0xfe, 0xff}}},
    {{{  -307,      0,   -307}, 0, {127<<5,  63<<5}, {0xb4, 0xee, 0xfe, 0xff}}},
    {{{     0,   -307,      0}, 0, { 31<<5,      0}, {0x52, 0x77, 0x8d, 0xff}}},
    {{{  -307,      0,    307}, 0, { 63<<5,  63<<5}, {0x52, 0x77, 0x8d, 0xff}}},
    {{{  -307,      0,   -307}, 0, {     0,  63<<5}, {0x52, 0x77, 0x8d, 0xff}}},
    {{{  -307,      0,    307}, 0, {     0,  63<<5}, {0x55, 0x86, 0x97, 0xff}}},
    {{{     0,   -307,      0}, 0, { 63<<5,      0}, {0x55, 0x86, 0x97, 0xff}}},
    {{{   307,      0,    307}, 0, {127<<5,  63<<5}, {0x55, 0x86, 0x97, 0xff}}},
    {{{   307,      0,   -307}, 0, { 31<<5,  63<<5}, {0x67, 0x9b, 0xb0, 0xff}}},
    {{{   307,      0,    307}, 0, {     0,  63<<5}, {0x67, 0x9b, 0xb0, 0xff}}},
    {{{     0,   -307,      0}, 0, { 31<<5,      0}, {0x67, 0x9b, 0xb0, 0xff}}},
};

// 0x0700B380 - 0x0700B410
static const Vtx bitdw_seg7_vertex_0700B380[] = {
    {{{  -307,      0,   -307}, 0, {127<<5,  63<<5}, {0x67, 0x9b, 0xb0, 0xff}}},
    {{{   307,      0,   -307}, 0, {     0,  63<<5}, {0x67, 0x9b, 0xb0, 0xff}}},
    {{{     0,   -307,      0}, 0, { 63<<5,      0}, {0x67, 0x9b, 0xb0, 0xff}}},
    {{{  -307,      0,   -307}, 0, {     0,  63<<5}, {0x8c, 0xbf, 0xd8, 0xff}}},
    {{{  -307,      0,    307}, 0, { 63<<5,  63<<5}, {0x8c, 0xbf, 0xd8, 0xff}}},
    {{{     0,    102,      0}, 0, { 31<<5,      0}, {0x8c, 0xbf, 0xd8, 0xff}}},
    {{{   307,      0,    307}, 0, {127<<5,  63<<5}, {0x8c, 0xbf, 0xd8, 0xff}}},
    {{{     0,    102,      0}, 0, { 63<<3,      0}, {0x8c, 0xbf, 0xd8, 0xff}}},
    {{{  -307,      0,    307}, 0, {     0,  63<<5}, {0x8c, 0xbf, 0xd8, 0xff}}},
};

// 0x0700B410 - 0x0700B480
static const Gfx bitdw_seg7_sub_dl_moving_pyramid[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sky_09002000_layered_gradient_rows),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bitdw_seg7_vertex_0700B290, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bitdw_seg7_vertex_0700B380, 9, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 6,  7,  8, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700B480 - 0x0700B4F0
const Gfx bitdw_seg7_dl_moving_pyramid[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bitdw_seg7_sub_dl_moving_pyramid),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
