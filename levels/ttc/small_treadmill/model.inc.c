// 0x0700FC80 - 0x0700FC98
static const Lights1 ttc_seg7_lights_small_treadmill_sides = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0700FC98 - 0x0700FCB0
static const Lights1 ttc_seg7_lights_small_treadmill_bottom = gdSPDefLights1(
    0x46, 0x46, 0x46,
    0x8c, 0x8c, 0x8c, 0x28, 0x28, 0x28
);

// 0x0700FCB0 - 0x0700FD30
static const Vtx ttc_seg7_vertex_small_treadmill_sides[] = {
    {{{  -230,      0,   -307}, 0, {  4510,    -32}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -230,   -138,   -307}, 0, {  4510,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -230,   -138,    307}, 0, {     0,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -230,      0,    307}, 0, {     0,    -32}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   230,      0,    307}, 0, {     0,    -32}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   230,   -138,   -307}, 0, {  4510,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   230,      0,   -307}, 0, {  4510,    -32}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   230,   -138,    307}, 0, {     0,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
};

// 0x0700FD30 - 0x0700FE30
static const Vtx ttc_seg7_vertex_small_treadmill_corners_1[] = {
    {{{  -230,   -138,    307}, 0, { 31<<5,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -230,    -36,    343}, 0, {   336,    240}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -230,      0,    307}, 0, { 31<<5,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   230,      0,    307}, 0, { 31<<5,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   230,    -36,    343}, 0, {   336,    240}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   230,   -138,    343}, 0, {   336,  31<<5}, {0x54, 0xd6, 0x54, 0xff}}},
    {{{   230,   -138,    307}, 0, { 31<<5,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   230,   -138,   -307}, 0, { 31<<5,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   230,   -138,   -343}, 0, {   336,  31<<5}, {0x33, 0x99, 0xcd, 0xff}}},
    {{{   230,    -36,   -343}, 0, {   336,    240}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   230,      0,   -307}, 0, { 31<<5,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -230,    -87,    343}, 0, {   336,  19<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -230,   -138,    343}, 0, {   336,  31<<5}, {0xcd, 0x99, 0x33, 0xff}}},
    {{{   230,    -87,    343}, 0, {   336,  19<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -230,   -138,   -343}, 0, {   336,  31<<5}, {0xac, 0xd6, 0xac, 0xff}}},
    {{{   230,    -87,   -343}, 0, {   336,  19<<5}, {0x00, 0x00, 0x81, 0xff}}},
};

// 0x0700FE30 - 0x0700FE90
static const Vtx ttc_seg7_vertex_small_treadmill_corners_2[] = {
    {{{  -230,      0,   -307}, 0, { 31<<5,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -230,    -36,   -343}, 0, {   336,    240}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -230,   -138,   -343}, 0, {   336,  31<<5}, {0xac, 0xd6, 0xac, 0xff}}},
    {{{  -230,   -138,   -307}, 0, { 31<<5,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -230,    -87,   -343}, 0, {   336,  19<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   230,    -87,   -343}, 0, {   336,  19<<5}, {0x00, 0x00, 0x81, 0xff}}},
};

// 0x0700FE90 - 0x0700FED0
static const Vtx ttc_seg7_vertex_small_treadmill_bottom[] = {
    {{{   230,   -138,   -343}, 0, {     0,      0}, {0x33, 0x99, 0xcd, 0xff}}},
    {{{  -230,   -138,    343}, 0, {     0,      0}, {0xcd, 0x99, 0x33, 0xff}}},
    {{{  -230,   -138,   -343}, 0, {     0,      0}, {0xac, 0xd6, 0xac, 0xff}}},
    {{{   230,   -138,    343}, 0, {     0,      0}, {0x54, 0xd6, 0x54, 0xff}}},
};

// 0x0700FED0 - 0x0700FF28
static const Gfx ttc_seg7_sub_dl_small_treadmill_sides[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, machine_09005800_treadmill_side),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttc_seg7_lights_small_treadmill_sides.l, 1),
    gsSPLight(&ttc_seg7_lights_small_treadmill_sides.a, 2),
    gsSPVertex(ttc_seg7_vertex_small_treadmill_sides, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700FF28 - 0x0700FFB8
static const Gfx ttc_seg7_sub_dl_small_treadmill_corners[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, machine_09006000_treadmill_corner),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ttc_seg7_vertex_small_treadmill_corners_1, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  5, 11, 12, 0x0),
    gsSP2Triangles( 5, 13, 11, 0x0, 14, 15,  8, 0x0),
    gsSP1Triangle( 0, 12,  1, 0x0),
    gsSPVertex(ttc_seg7_vertex_small_treadmill_corners_2, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP1Triangle(  2,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700FFB8 - 0x0700FFE8
static const Gfx ttc_seg7_sub_dl_small_treadmill_bottom[] = {
    gsSPLight(&ttc_seg7_lights_small_treadmill_bottom.l, 1),
    gsSPLight(&ttc_seg7_lights_small_treadmill_bottom.a, 2),
    gsSPVertex(ttc_seg7_vertex_small_treadmill_bottom, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700FFE8 - 0x070100B0
const Gfx ttc_seg7_dl_small_treadmill[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetFogColor(200, 255, 255, 255),
    gsSPFogPosition(900, 1000),
    gsSPSetGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_PASS2),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttc_seg7_sub_dl_small_treadmill_sides),
    gsSPDisplayList(ttc_seg7_sub_dl_small_treadmill_corners),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_PASS2),
    gsSPDisplayList(ttc_seg7_sub_dl_small_treadmill_bottom),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
