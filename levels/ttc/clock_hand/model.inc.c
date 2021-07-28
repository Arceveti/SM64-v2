// 0x07011758 - 0x07011770
static const Lights1 ttc_seg7_lights_clock_hand_dark_beige = gdSPDefLights1(
    0x5a, 0x41, 0x23,
    0xb4, 0x82, 0x46, 0x28, 0x28, 0x28
);

// 0x07011770 - 0x07011788
static const Lights1 ttc_seg7_lights_clock_hand_light_beige = gdSPDefLights1(
    0x7f, 0x66, 0x32,
    0xff, 0xcc, 0x65, 0x28, 0x28, 0x28
);

// 0x07011788 - 0x070117A0
static const Lights1 ttc_seg7_lights_clock_hand_dark_red = gdSPDefLights1(
    0x49, 0x00, 0x00,
    0x93, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x070117A0 - 0x070117B8
static const Lights1 ttc_seg7_lights_clock_hand_light_red = gdSPDefLights1(
    0x7f, 0x00, 0x00,
    0xff, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x070117B8 - 0x07011838
static const Vtx ttc_seg7_vertex_clock_hand_arm_sides[] = {
    {{{    86,      0,    -82}, 0, { 31<<5,    288}, {0x54, 0xd6, 0xac, 0xff}}},
    {{{   -86,     41,    -82}, 0, { 31<<5,    670}, {0xac, 0x2a, 0xac, 0xff}}},
    {{{    86,     41,    -82}, 0, { 31<<5,    288}, {0x33, 0x67, 0xcd, 0xff}}},
    {{{   -86,      0,    -82}, 0, { 31<<5,    670}, {0xcd, 0x99, 0xcd, 0xff}}},
    {{{   -86,      0,   1336}, 0, {   136,    670}, {0xc7, 0x94, 0xdf, 0xff}}},
    {{{   -86,     41,   1336}, 0, {   136,    670}, {0xfb, 0x73, 0xcc, 0xff}}},
    {{{    86,     41,   1336}, 0, {   136,    288}, {0x39, 0x6c, 0xdf, 0xff}}},
    {{{    86,      0,   1336}, 0, {   136,    288}, {0x05, 0x8d, 0xcc, 0xff}}},
};

// 0x07011838 - 0x070118B8
static const Vtx ttc_seg7_vertex_clock_hand_arm_top[] = {
    {{{    86,     41,    -82}, 0, { 31<<5,    288}, {0x33, 0x67, 0xcd, 0xff}}},
    {{{   -86,     41,    -82}, 0, { 31<<5,    670}, {0xac, 0x2a, 0xac, 0xff}}},
    {{{   -86,     41,   1336}, 0, {   136,    670}, {0xfb, 0x73, 0xcc, 0xff}}},
    {{{    86,     41,   1336}, 0, {   136,    288}, {0x39, 0x6c, 0xdf, 0xff}}},
    {{{    86,      0,   1336}, 0, {   136,    288}, {0x05, 0x8d, 0xcc, 0xff}}},
    {{{   -86,      0,    -82}, 0, { 31<<5,    670}, {0xcd, 0x99, 0xcd, 0xff}}},
    {{{    86,      0,    -82}, 0, { 31<<5,    288}, {0x54, 0xd6, 0xac, 0xff}}},
    {{{   -86,      0,   1336}, 0, {   136,    670}, {0xc7, 0x94, 0xdf, 0xff}}},
};

// 0x070118B8 - 0x07011958
static const Vtx ttc_seg7_vertex_clock_hand_arrow_sides[] = {
    {{{   -86,     41,   1336}, 0, {   136,    670}, {0xfb, 0x73, 0xcc, 0xff}}},
    {{{   -86,      0,   1336}, 0, {   136,    670}, {0xc7, 0x94, 0xdf, 0xff}}},
    {{{  -181,      0,   1295}, 0, {   160,    880}, {0xfd, 0xb3, 0x9c, 0xff}}},
    {{{  -181,     41,   1295}, 0, {   160,    880}, {0x9d, 0x4d, 0x0c, 0xff}}},
    {{{     0,      0,   1577}, 0, {   -10,  15<<5}, {0xe2, 0x94, 0x3a, 0xff}}},
    {{{     0,     41,   1577}, 0, {   -10,  15<<5}, {0x1e, 0x6c, 0x3a, 0xff}}},
    {{{   181,      0,   1295}, 0, {   160,     80}, {0x63, 0xb3, 0x0c, 0xff}}},
    {{{   181,     41,   1295}, 0, {   160,     80}, {0x03, 0x4d, 0x9c, 0xff}}},
    {{{    86,      0,   1336}, 0, {   136,    288}, {0x05, 0x8d, 0xcc, 0xff}}},
    {{{    86,     41,   1336}, 0, {   136,    288}, {0x39, 0x6c, 0xdf, 0xff}}},
};

// 0x07011958 - 0x070119F8
static const Vtx ttc_seg7_vertex_clock_hand_arrow_top[] = {
    {{{     0,     41,   1577}, 0, {   -10,  15<<5}, {0x1e, 0x6c, 0x3a, 0xff}}},
    {{{    86,     41,   1336}, 0, {   136,    288}, {0x39, 0x6c, 0xdf, 0xff}}},
    {{{   -86,     41,   1336}, 0, {   136,    670}, {0xfb, 0x73, 0xcc, 0xff}}},
    {{{  -181,     41,   1295}, 0, {   160,    880}, {0x9d, 0x4d, 0x0c, 0xff}}},
    {{{   181,     41,   1295}, 0, {   160,     80}, {0x03, 0x4d, 0x9c, 0xff}}},
    {{{     0,      0,   1577}, 0, {   -10,  15<<5}, {0xe2, 0x94, 0x3a, 0xff}}},
    {{{    86,      0,   1336}, 0, {   136,    288}, {0x05, 0x8d, 0xcc, 0xff}}},
    {{{   181,      0,   1295}, 0, {   160,     80}, {0x63, 0xb3, 0x0c, 0xff}}},
    {{{  -181,      0,   1295}, 0, {   160,    880}, {0xfd, 0xb3, 0x9c, 0xff}}},
    {{{   -86,      0,   1336}, 0, {   136,    670}, {0xc7, 0x94, 0xdf, 0xff}}},
};

// 0x070119F8 - 0x07011B38
static const Gfx ttc_seg7_sub_dl_clock_hand[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, machine_09000800_clock_hand),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttc_seg7_lights_clock_hand_dark_beige.l, 1),
    gsSPLight(&ttc_seg7_lights_clock_hand_dark_beige.a, 2),
    gsSPVertex(ttc_seg7_vertex_clock_hand_arm_sides, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  1, 0x0,  4,  1,  3, 0x0),
    gsSP2Triangles( 0,  2,  6, 0x0,  0,  6,  7, 0x0),
    gsSPLight(&ttc_seg7_lights_clock_hand_light_beige.l, 1),
    gsSPLight(&ttc_seg7_lights_clock_hand_light_beige.a, 2),
    gsSPVertex(ttc_seg7_vertex_clock_hand_arm_top, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPLight(&ttc_seg7_lights_clock_hand_dark_red.l, 1),
    gsSPLight(&ttc_seg7_lights_clock_hand_dark_red.a, 2),
    gsSPVertex(ttc_seg7_vertex_clock_hand_arrow_sides, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 3,  2,  4, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 7,  6,  8, 0x0,  7,  8,  9, 0x0),
    gsSPLight(&ttc_seg7_lights_clock_hand_light_red.l, 1),
    gsSPLight(&ttc_seg7_lights_clock_hand_light_red.a, 2),
    gsSPVertex(ttc_seg7_vertex_clock_hand_arrow_top, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 0,  4,  1, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  8,  9, 0x0,  5,  9,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x07011B38 - 0x07011BE0
const Gfx ttc_seg7_dl_clock_hand[] = {
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
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttc_seg7_sub_dl_clock_hand),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
