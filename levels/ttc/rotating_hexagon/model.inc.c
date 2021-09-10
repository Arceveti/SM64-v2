// 0x07010380 - 0x07010398
static const Lights1 ttc_seg7_lights_rotating_hexagon = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07010398 - 0x07010488
static const Vtx ttc_seg7_vertex_rotating_hexagon_sides_1[] = {
    {{{  -154,      0,   -266}, 0, { -2080,      0}, {0xbe, 0x4c, 0xb4, 0xff}}},
    {{{  -307,   -154,      0}, 0, {127<<5,  31<<5}, {0x9d, 0xb4, 0xed, 0xff}}},
    {{{  -307,      0,      0}, 0, {127<<5,      0}, {0x9d, 0x4c, 0x13, 0xff}}},
    {{{  -154,      0,    266}, 0, { -3104,      0}, {0xdf, 0x4c, 0x5f, 0xff}}},
    {{{   154,   -154,    266}, 0, { 95<<5,  31<<5}, {0x21, 0xb4, 0x5f, 0xff}}},
    {{{   154,      0,    266}, 0, { 95<<5,      0}, {0x42, 0x4c, 0x4c, 0xff}}},
    {{{  -154,   -154,    266}, 0, { -3104,  31<<5}, {0xbe, 0xb4, 0x4c, 0xff}}},
    {{{   154,      0,   -266}, 0, { -3104,      0}, {0x21, 0x4c, 0xa1, 0xff}}},
    {{{  -154,   -154,   -266}, 0, { 95<<5,  31<<5}, {0xdf, 0xb4, 0xa1, 0xff}}},
    {{{  -154,      0,   -266}, 0, { 95<<5,      0}, {0xbe, 0x4c, 0xb4, 0xff}}},
    {{{   154,   -154,   -266}, 0, { -3104,  31<<5}, {0x42, 0xb4, 0xb4, 0xff}}},
    {{{   154,      0,    266}, 0, { -2080,      0}, {0x42, 0x4c, 0x4c, 0xff}}},
    {{{   307,   -154,      0}, 0, {127<<5,  31<<5}, {0x63, 0xb4, 0x13, 0xff}}},
    {{{   307,      0,      0}, 0, {127<<5,      0}, {0x63, 0x4c, 0xed, 0xff}}},
    {{{   154,   -154,    266}, 0, { -2080,  31<<5}, {0x21, 0xb4, 0x5f, 0xff}}},
};

// 0x07010488 - 0x07010538
static const Vtx ttc_seg7_vertex_rotating_hexagon_sides_2[] = {
    {{{  -307,      0,      0}, 0, { -2080,      0}, {0x9d, 0x4c, 0x13, 0xff}}},
    {{{  -307,   -154,      0}, 0, { -2080,  31<<5}, {0x9d, 0xb4, 0xed, 0xff}}},
    {{{  -154,   -154,    266}, 0, {127<<5,  31<<5}, {0xbe, 0xb4, 0x4c, 0xff}}},
    {{{  -154,      0,   -266}, 0, { -2080,      0}, {0xbe, 0x4c, 0xb4, 0xff}}},
    {{{  -154,   -154,   -266}, 0, { -2080,  31<<5}, {0xdf, 0xb4, 0xa1, 0xff}}},
    {{{  -307,   -154,      0}, 0, {127<<5,  31<<5}, {0x9d, 0xb4, 0xed, 0xff}}},
    {{{   307,      0,      0}, 0, { -3104,      0}, {0x63, 0x4c, 0xed, 0xff}}},
    {{{   154,   -154,   -266}, 0, { 95<<5,  31<<5}, {0x42, 0xb4, 0xb4, 0xff}}},
    {{{   154,      0,   -266}, 0, { 95<<5,      0}, {0x21, 0x4c, 0xa1, 0xff}}},
    {{{   307,   -154,      0}, 0, { -3104,  31<<5}, {0x63, 0xb4, 0x13, 0xff}}},
    {{{  -154,      0,    266}, 0, {127<<5,      0}, {0xdf, 0x4c, 0x5f, 0xff}}},
};

// 0x07010538 - 0x07010638
static const Vtx ttc_seg7_vertex_rotating_hexagon_top_1[] = {
    {{{   307,      0,      0}, 0, { -1056,  31<<5}, {0x63, 0x4c, 0xed, 0xff}}},
    {{{   154,      0,   -266}, 0, { 63<<5,  31<<5}, {0x21, 0x4c, 0xa1, 0xff}}},
    {{{     0,      0,      0}, 0, { 15<<5,  -1056}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -154,      0,    266}, 0, { 63<<5,  31<<5}, {0xdf, 0x4c, 0x5f, 0xff}}},
    {{{  -307,      0,      0}, 0, { -1056,  31<<5}, {0x9d, 0x4c, 0x13, 0xff}}},
    {{{  -154,      0,    266}, 0, { -1056,  31<<5}, {0xdf, 0x4c, 0x5f, 0xff}}},
    {{{   154,      0,    266}, 0, { 63<<5,  31<<5}, {0x42, 0x4c, 0x4c, 0xff}}},
    {{{     0,      0,      0}, 0, { 15<<5,  -1056}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{     0,      0,      0}, 0, { 15<<5,  -1056}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -154,      0,   -266}, 0, { -1056,  31<<5}, {0xbe, 0x4c, 0xb4, 0xff}}},
    {{{  -307,      0,      0}, 0, { 63<<5,  31<<5}, {0x9d, 0x4c, 0x13, 0xff}}},
    {{{   154,      0,    266}, 0, { -1056,  31<<5}, {0x42, 0x4c, 0x4c, 0xff}}},
    {{{   307,      0,      0}, 0, { 63<<5,  31<<5}, {0x63, 0x4c, 0xed, 0xff}}},
    {{{  -307,   -154,      0}, 0, { 63<<5,  31<<5}, {0x9d, 0xb4, 0xed, 0xff}}},
    {{{  -154,   -154,   -266}, 0, { -1056,  31<<5}, {0xdf, 0xb4, 0xa1, 0xff}}},
    {{{     0,   -154,      0}, 0, { 15<<5,  -1056}, {0x00, 0x81, 0x00, 0xff}}},
};

// 0x07010638 - 0x07010738
static const Vtx ttc_seg7_vertex_rotating_hexagon_top_2[] = {
    {{{   154,      0,   -266}, 0, { -1056,  31<<5}, {0x21, 0x4c, 0xa1, 0xff}}},
    {{{  -154,      0,   -266}, 0, { 63<<5,  31<<5}, {0xbe, 0x4c, 0xb4, 0xff}}},
    {{{     0,      0,      0}, 0, { 15<<5,  -1056}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{     0,   -154,      0}, 0, { 15<<5,  -1056}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   307,   -154,      0}, 0, { 63<<5,  31<<5}, {0x63, 0xb4, 0x13, 0xff}}},
    {{{   154,   -154,    266}, 0, { -1056,  31<<5}, {0x21, 0xb4, 0x5f, 0xff}}},
    {{{     0,   -154,      0}, 0, { 15<<5,  -1056}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   154,   -154,   -266}, 0, { 63<<5,  31<<5}, {0x42, 0xb4, 0xb4, 0xff}}},
    {{{   307,   -154,      0}, 0, { -1056,  31<<5}, {0x63, 0xb4, 0x13, 0xff}}},
    {{{  -154,   -154,   -266}, 0, { 63<<5,  31<<5}, {0xdf, 0xb4, 0xa1, 0xff}}},
    {{{   154,   -154,   -266}, 0, { -1056,  31<<5}, {0x42, 0xb4, 0xb4, 0xff}}},
    {{{     0,   -154,      0}, 0, { 15<<5,  -1056}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   154,   -154,    266}, 0, { 63<<5,  31<<5}, {0x21, 0xb4, 0x5f, 0xff}}},
    {{{  -154,   -154,    266}, 0, { -1056,  31<<5}, {0xbe, 0xb4, 0x4c, 0xff}}},
    {{{  -307,   -154,      0}, 0, { -1056,  31<<5}, {0x9d, 0xb4, 0xed, 0xff}}},
    {{{  -154,   -154,    266}, 0, { 63<<5,  31<<5}, {0xbe, 0xb4, 0x4c, 0xff}}},
};

// 0x07010738 - 0x070107D8
static const Gfx ttc_seg7_sub_dl_rotating_hexagon_sides[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, machine_09003800_vertical_rods),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttc_seg7_lights_rotating_hexagon.l, 1),
    gsSPLight(&ttc_seg7_lights_rotating_hexagon.a, 2),
    gsSPVertex(ttc_seg7_vertex_rotating_hexagon_sides_1, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle( 11, 14, 12, 0x0),
    gsSPVertex(ttc_seg7_vertex_rotating_hexagon_sides_2, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP1Triangle(  0,  2, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x070107D8 - 0x07010868
static const Gfx ttc_seg7_sub_dl_rotating_hexagon_top[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, machine_09001000_horizontal_rods),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ttc_seg7_vertex_rotating_hexagon_top_1, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  4, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles(11, 12,  8, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ttc_seg7_vertex_rotating_hexagon_top_2, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  3,  9, 10, 0x0),
    gsSP2Triangles(11, 12, 13, 0x0, 14,  6, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x07010868 - 0x07010930
const Gfx ttc_seg7_dl_rotating_hexagon[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetFogColor(200, 255, 255, 255),
    gsSPFogPosition(TTC_FOG_MIN, TTC_FOG_MAX),
    gsSPSetGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_PASS2),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttc_seg7_sub_dl_rotating_hexagon_sides),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttc_seg7_sub_dl_rotating_hexagon_top),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
