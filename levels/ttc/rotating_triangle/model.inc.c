// 0x07010930 - 0x07010948
static const Lights1 ttc_seg7_lights_rotating_triangle = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07010948 - 0x07010A28
static const Vtx ttc_seg7_vertex_rotating_triangle_sides_1[] = {
    {{{     0,      0,    -77}, 0, {  4566,      0}, {0x00, 0x22, 0x86, 0xff}}},
    {{{     0,     77,      0}, 0, {  4566,   -544}, {0x00, 0x7e, 0x00, 0xff}}},
    {{{    77,      0,      0}, 0, {  5716,      0}, {0x5c, 0x4a, 0xd3, 0xff}}},
    {{{  -300,   -154,    300}, 0, { -4986,  31<<5}, {0xd9, 0x9e, 0x45, 0xff}}},
    {{{   300,   -154,    300}, 0, {  6968,  31<<5}, {0x27, 0x9e, 0x45, 0xff}}},
    {{{     0,      0,    300}, 0, { 31<<5,      0}, {0x00, 0x46, 0x69, 0xff}}},
    {{{   300,      0,    300}, 0, {  6968,      0}, {0x4f, 0x62, 0xf7, 0xff}}},
    {{{  -300,      0,    300}, 0, { -4986,      0}, {0xb1, 0x62, 0xf7, 0xff}}},
    {{{     0,   -154,     77}, 0, {  4566,  31<<5}, {0x00, 0x86, 0x22, 0xff}}},
    {{{   -77,   -154,      0}, 0, {  3418,  31<<5}, {0x9e, 0xce, 0xc3, 0xff}}},
    {{{     0,   -230,      0}, 0, {  4566,  47<<5}, {0x00, 0x82, 0x00, 0xff}}},
    {{{    77,   -154,      0}, 0, {  5716,  31<<5}, {0x62, 0xce, 0xc2, 0xff}}},
    {{{     0,   -154,    -77}, 0, {  4566,  31<<5}, {0x00, 0xcd, 0x8c, 0xff}}},
    {{{   -77,      0,      0}, 0, {  3418,      0}, {0xa4, 0x49, 0xd3, 0xff}}},
};

// 0x07010A28 - 0x07010B28
static const Vtx ttc_seg7_vertex_rotating_triangle_sides_2[] = {
    {{{   300,      0,    300}, 0, { -6482,      0}, {0x4f, 0x62, 0xf7, 0xff}}},
    {{{    77,   -154,      0}, 0, { 31<<5,  31<<5}, {0x62, 0xce, 0xc2, 0xff}}},
    {{{    77,      0,      0}, 0, { 31<<5,      0}, {0x5c, 0x4a, 0xd3, 0xff}}},
    {{{     0,     77,      0}, 0, {  4566,   -544}, {0x00, 0x7e, 0x00, 0xff}}},
    {{{   -77,      0,      0}, 0, {  3418,      0}, {0xa4, 0x49, 0xd3, 0xff}}},
    {{{     0,      0,     77}, 0, {  4566,      0}, {0x00, 0x7b, 0x1c, 0xff}}},
    {{{    77,      0,      0}, 0, {  5716,      0}, {0x5c, 0x4a, 0xd3, 0xff}}},
    {{{     0,      0,    -77}, 0, { -2128,      0}, {0x00, 0x22, 0x86, 0xff}}},
    {{{     0,   -154,    -77}, 0, { -2128,  31<<5}, {0x00, 0xcd, 0x8c, 0xff}}},
    {{{   -77,   -154,      0}, 0, {     0,  31<<5}, {0x9e, 0xce, 0xc3, 0xff}}},
    {{{   -77,      0,      0}, 0, {     0,      0}, {0xa4, 0x49, 0xd3, 0xff}}},
    {{{  -300,   -154,    300}, 0, {  7442,  31<<5}, {0xd9, 0x9e, 0x45, 0xff}}},
    {{{  -300,      0,    300}, 0, {  7442,      0}, {0xb1, 0x62, 0xf7, 0xff}}},
    {{{     0,      0,    -77}, 0, {  3088,      0}, {0x00, 0x22, 0x86, 0xff}}},
    {{{     0,   -154,    -77}, 0, {  3088,  31<<5}, {0x00, 0xcd, 0x8c, 0xff}}},
    {{{   300,   -154,    300}, 0, { -6482,  31<<5}, {0x27, 0x9e, 0x45, 0xff}}},
};

// 0x07010B28 - 0x07010B78
static const Vtx ttc_seg7_vertex_rotating_triangle_bottom[] = {
    {{{   300,   -154,    300}, 0, {  9166,  31<<5}, {0x27, 0x9e, 0x45, 0xff}}},
    {{{  -300,   -154,    300}, 0, {     0,  31<<5}, {0xd9, 0x9e, 0x45, 0xff}}},
    {{{     0,   -154,     77}, 0, {  4566,  31<<5}, {0x00, 0x86, 0x22, 0xff}}},
    {{{   -77,   -154,      0}, 0, {  3418,  31<<5}, {0x9e, 0xce, 0xc3, 0xff}}},
    {{{    77,   -154,      0}, 0, {  5716,  31<<5}, {0x62, 0xce, 0xc2, 0xff}}},
};

// 0x07010B78 - 0x07010BF8
static const Vtx ttc_seg7_vertex_rotating_triangle_top[] = {
    {{{   300,      0,    300}, 0, { 31<<5,  31<<5}, {0x4f, 0x62, 0xf7, 0xff}}},
    {{{    77,      0,      0}, 0, {   -80,  31<<5}, {0x5c, 0x4a, 0xd3, 0xff}}},
    {{{     0,      0,     77}, 0, {  6<<5,   1362}, {0x00, 0x7b, 0x1c, 0xff}}},
    {{{     0,      0,    300}, 0, { 31<<5,   1842}, {0x00, 0x46, 0x69, 0xff}}},
    {{{  -300,      0,    300}, 0, { 31<<5,  31<<5}, {0xb1, 0x62, 0xf7, 0xff}}},
    {{{     0,      0,    300}, 0, { 31<<5,    136}, {0x00, 0x46, 0x69, 0xff}}},
    {{{     0,      0,     77}, 0, {  6<<5,    614}, {0x00, 0x7b, 0x1c, 0xff}}},
    {{{   -77,      0,      0}, 0, {   -80,  31<<5}, {0xa4, 0x49, 0xd3, 0xff}}},
};

// 0x07010BF8 - 0x07010CF0
static const Gfx ttc_seg7_sub_dl_rotating_triangle_sides[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, machine_09003800_vertical_rods),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttc_seg7_lights_rotating_triangle.l, 1),
    gsSPLight(&ttc_seg7_lights_rotating_triangle.a, 2),
    gsSPVertex(ttc_seg7_vertex_rotating_triangle_sides_1, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  3,  5,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10, 11,  8, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0, 11, 10, 12, 0x0),
    gsSP1Triangle(  1,  0, 13, 0x0),
    gsSPVertex(ttc_seg7_vertex_rotating_triangle_sides_2, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  6,  3, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0,  9, 11, 12, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0,  1, 13,  2, 0x0),
    gsSP2Triangles( 1, 14, 13, 0x0,  0, 15,  1, 0x0),
    gsSPVertex(ttc_seg7_vertex_rotating_triangle_bottom, 5, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP1Triangle(  0,  2,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x07010CF0 - 0x07010D38
static const Gfx ttc_seg7_sub_dl_rotating_triangle_top[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, machine_09005000_yellow_block),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ttc_seg7_vertex_rotating_triangle_top, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  4,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x07010D38 - 0x07010DE8
const Gfx ttc_seg7_dl_rotating_triangle[] = {
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
    gsSPDisplayList(ttc_seg7_sub_dl_rotating_triangle_sides),
    gsSPDisplayList(ttc_seg7_sub_dl_rotating_triangle_top),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
