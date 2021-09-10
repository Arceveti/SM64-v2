// 0x07011BE0 - 0x07011BF8
static const Lights1 ttc_seg7_lights_spinner_1 = gdSPDefLights1(
    0x46, 0x46, 0x46,
    0x8c, 0x8c, 0x8c, 0x28, 0x28, 0x28
);

// 0x07011BF8 - 0x07011C10
static const Lights1 ttc_seg7_lights_spinner_2 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07011C10 - 0x07011D10
static const Vtx ttc_seg7_vertex_spinner_1[] = {
    {{{  -154,    -26,     26}, 0, { 23<<5,    432}, {0xd6, 0x98, 0x3b, 0xff}}},
    {{{   154,    -51,      0}, 0, {  7<<5,  15<<5}, {0x33, 0x92, 0x22, 0xff}}},
    {{{   154,    -26,     26}, 0, {  7<<5,    432}, {0x75, 0xd3, 0x0b, 0xff}}},
    {{{   154,     26,     26}, 0, {  7<<5,    432}, {0x3c, 0x67, 0x29, 0xff}}},
    {{{  -154,     51,      0}, 0, { 23<<5,  15<<5}, {0xac, 0x5a, 0x1c, 0xff}}},
    {{{  -154,     26,     26}, 0, { 23<<5,    432}, {0xa3, 0x50, 0x20, 0xff}}},
    {{{   154,     51,      0}, 0, {  7<<5,  15<<5}, {0x54, 0x59, 0xe2, 0xff}}},
    {{{   154,     26,    -26}, 0, {  7<<5,    528}, {0x49, 0x63, 0xe6, 0xff}}},
    {{{  -154,     26,    -26}, 0, { 23<<5,    528}, {0xb7, 0x59, 0xcc, 0xff}}},
    {{{  -154,    -26,    -26}, 0, { 23<<5,    528}, {0x86, 0xe3, 0xf4, 0xff}}},
    {{{   154,    -26,   -307}, 0, {  7<<5,  31<<5}, {0x49, 0xb7, 0xb7, 0xff}}},
    {{{   154,     26,   -307}, 0, {  7<<5,  31<<5}, {0x54, 0x2a, 0xac, 0xff}}},
    {{{  -154,    -51,      0}, 0, { 23<<5,  15<<5}, {0xcd, 0x93, 0xdb, 0xff}}},
    {{{   154,    -26,    -26}, 0, {  7<<5,    528}, {0x21, 0x8f, 0xd2, 0xff}}},
    {{{   154,     26,    307}, 0, {  7<<5,      0}, {0x67, 0x33, 0x33, 0xff}}},
    {{{   154,    -26,    307}, 0, {  7<<5,      0}, {0x33, 0xcd, 0x67, 0xff}}},
};

// 0x07011D10 - 0x07011DC0
static const Vtx ttc_seg7_vertex_spinner_2[] = {
    {{{   154,     26,   -307}, 0, {  7<<5,  31<<5}, {0x54, 0x2a, 0xac, 0xff}}},
    {{{   154,    -26,   -307}, 0, {  7<<5,  31<<5}, {0x49, 0xb7, 0xb7, 0xff}}},
    {{{  -154,    -26,   -307}, 0, { 23<<5,  31<<5}, {0xd6, 0xac, 0xac, 0xff}}},
    {{{  -154,     26,   -307}, 0, { 23<<5,  31<<5}, {0xac, 0x54, 0xd6, 0xff}}},
    {{{  -154,     26,    307}, 0, { 23<<5,      0}, {0xb7, 0x49, 0x49, 0xff}}},
    {{{   154,    -26,    307}, 0, {  7<<5,      0}, {0x33, 0xcd, 0x67, 0xff}}},
    {{{   154,     26,    307}, 0, {  7<<5,      0}, {0x67, 0x33, 0x33, 0xff}}},
    {{{  -154,    -26,    307}, 0, { 23<<5,      0}, {0xcd, 0x99, 0x33, 0xff}}},
    {{{  -154,    -26,    -26}, 0, { 23<<5,    528}, {0x86, 0xe3, 0xf4, 0xff}}},
    {{{  -154,     26,     26}, 0, { 23<<5,    432}, {0xa3, 0x50, 0x20, 0xff}}},
    {{{  -154,     26,    -26}, 0, { 23<<5,    528}, {0xb7, 0x59, 0xcc, 0xff}}},
};

// 0x07011DC0 - 0x07011EC0
static const Vtx ttc_seg7_vertex_spinner_3[] = {
    {{{  -154,    -26,   -307}, 0, { 23<<5,  31<<5}, {0xd6, 0xac, 0xac, 0xff}}},
    {{{   154,    -26,   -307}, 0, {  7<<5,  31<<5}, {0x49, 0xb7, 0xb7, 0xff}}},
    {{{   154,    -26,    -26}, 0, {  7<<5,    528}, {0x21, 0x8f, 0xd2, 0xff}}},
    {{{  -154,     26,    307}, 0, { 23<<5,      0}, {0xb7, 0x49, 0x49, 0xff}}},
    {{{   154,     26,    307}, 0, {  7<<5,      0}, {0x67, 0x33, 0x33, 0xff}}},
    {{{   154,     26,     26}, 0, {  7<<5,    432}, {0x3c, 0x67, 0x29, 0xff}}},
    {{{  -154,     26,     26}, 0, { 23<<5,    432}, {0xa3, 0x50, 0x20, 0xff}}},
    {{{   154,     26,    -26}, 0, {  7<<5,    528}, {0x49, 0x63, 0xe6, 0xff}}},
    {{{  -154,     26,   -307}, 0, { 23<<5,  31<<5}, {0xac, 0x54, 0xd6, 0xff}}},
    {{{  -154,     26,    -26}, 0, { 23<<5,    528}, {0xb7, 0x59, 0xcc, 0xff}}},
    {{{   154,     26,   -307}, 0, {  7<<5,  31<<5}, {0x54, 0x2a, 0xac, 0xff}}},
    {{{   154,    -26,     26}, 0, {  7<<5,    432}, {0x75, 0xd3, 0x0b, 0xff}}},
    {{{  -154,    -26,    307}, 0, { 23<<5,      0}, {0xcd, 0x99, 0x33, 0xff}}},
    {{{  -154,    -26,     26}, 0, { 23<<5,    432}, {0xd6, 0x98, 0x3b, 0xff}}},
    {{{   154,    -26,    307}, 0, {  7<<5,      0}, {0x33, 0xcd, 0x67, 0xff}}},
    {{{  -154,    -26,    -26}, 0, { 23<<5,    528}, {0x86, 0xe3, 0xf4, 0xff}}},
};

// 0x07011EC0 - 0x07012028
static const Gfx ttc_seg7_sub_dl_spinner[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, machine_09006800_pole_top),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttc_seg7_lights_spinner_1.l, 1),
    gsSPLight(&ttc_seg7_lights_spinner_1.a, 2),
    gsSPVertex(ttc_seg7_vertex_spinner_1, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  2,  6,  3, 0x0),
    gsSP2Triangles( 2,  7,  6, 0x0,  6,  8,  4, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9,  5,  4, 0x0),
    gsSP2Triangles( 9,  4,  8, 0x0,  2, 10, 11, 0x0),
    gsSP2Triangles( 9, 12,  0, 0x0, 13,  1, 12, 0x0),
    gsSP2Triangles( 0, 12,  1, 0x0, 13, 12,  9, 0x0),
    gsSP2Triangles( 2,  1, 13, 0x0,  2, 14, 15, 0x0),
    gsSP2Triangles( 2,  3, 14, 0x0,  2, 11,  7, 0x0),
    gsSPVertex(ttc_seg7_vertex_spinner_2, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  7,  4, 0x0,  8,  4,  9, 0x0),
    gsSP2Triangles( 8, 10,  3, 0x0,  8,  3,  2, 0x0),
    gsSPLight(&ttc_seg7_lights_spinner_2.l, 1),
    gsSPLight(&ttc_seg7_lights_spinner_2.a, 2),
    gsSPVertex(ttc_seg7_vertex_spinner_3, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0,  0,  2, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x07012028 - 0x070120D0
const Gfx ttc_seg7_dl_spinner[] = {
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
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttc_seg7_sub_dl_spinner),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
