// 0x0700E950 - 0x0700E968
static const Lights1 ttc_seg7_lights_rotating_cube_base_1 = gdSPDefLights1(
    0x55, 0x55, 0x55,
    0xaa, 0xaa, 0xaa, 0x28, 0x28, 0x28
);

// 0x0700E968 - 0x0700E980
static const Lights1 ttc_seg7_lights_rotating_cube_base_2 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0700E980 - 0x0700EA20
static const Vtx ttc_seg7_vertex_rotating_cube_base_1[] = {
    {{{  -200,    200,   -200}, 0, ST_B(    64,      0), {0xd6, 0x54, 0xac, 0xff}}},
    {{{     0,      0,   -200}, 0, ST_B(    16,45.2548), {0x00, 0x00, 0x81, 0xff}}},
    {{{  -200,   -200,   -200}, 0, ST_B(   -32,      0), {0xac, 0xd6, 0xac, 0xff}}},
    {{{   200,   -200,   -200}, 0, ST_B(    64,      0), {0x2a, 0xac, 0xac, 0xff}}},
    {{{   200,    200,   -200}, 0, ST_B(   -32,      0), {0x54, 0x2a, 0xac, 0xff}}},
    {{{   200,    200,    200}, 0, ST_B(   -32,      0), {0x2a, 0x54, 0x54, 0xff}}},
    {{{     0,      0,    200}, 0, ST_B(    16,45.2548), {0x00, 0x00, 0x7f, 0xff}}},
    {{{   200,   -200,    200}, 0, ST_B(    64,      0), {0x54, 0xd6, 0x54, 0xff}}},
    {{{  -200,   -200,    200}, 0, ST_B(   -32,      0), {0xd6, 0xac, 0x54, 0xff}}},
    {{{  -200,    200,    200}, 0, ST_B(    64,      0), {0xac, 0x2a, 0x54, 0xff}}},
};

// 0x0700EA20 - 0x0700EAC0
static const Vtx ttc_seg7_vertex_rotating_cube_base_2[] = {
    {{{  -200,   -200,   -200}, 0, ST_B(    64,      0), {0xac, 0xd6, 0xac, 0xff}}},
    {{{     0,      0,   -200}, 0, ST_B(    16,45.2548), {0x00, 0x00, 0x81, 0xff}}},
    {{{   200,   -200,   -200}, 0, ST_B(   -32,      0), {0x2a, 0xac, 0xac, 0xff}}},
    {{{   200,    200,   -200}, 0, ST_B(    64,      0), {0x54, 0x2a, 0xac, 0xff}}},
    {{{  -200,    200,   -200}, 0, ST_B(   -32,      0), {0xd6, 0x54, 0xac, 0xff}}},
    {{{   200,   -200,    200}, 0, ST_B(   -32,      0), {0x54, 0xd6, 0x54, 0xff}}},
    {{{     0,      0,    200}, 0, ST_B(    16,45.2548), {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -200,   -200,    200}, 0, ST_B(    64,      0), {0xd6, 0xac, 0x54, 0xff}}},
    {{{  -200,    200,    200}, 0, ST_B(   -32,      0), {0xac, 0x2a, 0x54, 0xff}}},
    {{{   200,    200,    200}, 0, ST_B(    64,      0), {0x2a, 0x54, 0x54, 0xff}}},
};

// 0x0700EAC0 - 0x0700EBC0
static const Vtx ttc_seg7_vertex_rotating_cube_sides[] = {
    {{{   200,   -200,   -200}, 0, ST_B(     0,     32), {0x2a, 0xac, 0xac, 0xff}}},
    {{{   200,   -200,    200}, 0, ST_B(    32,     32), {0x54, 0xd6, 0x54, 0xff}}},
    {{{  -200,   -200,    200}, 0, ST_B(    32,      0), {0xd6, 0xac, 0x54, 0xff}}},
    {{{  -200,    200,   -200}, 0, ST_B(     0,     32), {0xd6, 0x54, 0xac, 0xff}}},
    {{{  -200,    200,    200}, 0, ST_B(    32,     32), {0xac, 0x2a, 0x54, 0xff}}},
    {{{   200,    200,    200}, 0, ST_B(    32,      0), {0x2a, 0x54, 0x54, 0xff}}},
    {{{   200,    200,   -200}, 0, ST_B(     0,      0), {0x54, 0x2a, 0xac, 0xff}}},
    {{{  -200,    200,    200}, 0, ST_B(    32,      0), {0xac, 0x2a, 0x54, 0xff}}},
    {{{  -200,   -200,   -200}, 0, ST_B(     0,     32), {0xac, 0xd6, 0xac, 0xff}}},
    {{{  -200,   -200,    200}, 0, ST_B(    32,     32), {0xd6, 0xac, 0x54, 0xff}}},
    {{{  -200,    200,   -200}, 0, ST_B(     0,      0), {0xd6, 0x54, 0xac, 0xff}}},
    {{{   200,    200,   -200}, 0, ST_B(     0,     32), {0x54, 0x2a, 0xac, 0xff}}},
    {{{   200,   -200,    200}, 0, ST_B(    32,      0), {0x54, 0xd6, 0x54, 0xff}}},
    {{{   200,   -200,   -200}, 0, ST_B(     0,      0), {0x2a, 0xac, 0xac, 0xff}}},
    {{{   200,    200,    200}, 0, ST_B(    32,     32), {0x2a, 0x54, 0x54, 0xff}}},
    {{{  -200,   -200,   -200}, 0, ST_B(     0,      0), {0xac, 0xd6, 0xac, 0xff}}},
};

// 0x0700EBC0 - 0x0700EC50
static const Gfx ttc_seg7_sub_dl_rotating_cube_base[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, machine_09001000_horizontal_rods),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttc_seg7_lights_rotating_cube_base_1.l, 1),
    gsSPLight(&ttc_seg7_lights_rotating_cube_base_1.a, 2),
    gsSPVertex(ttc_seg7_vertex_rotating_cube_base_1, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  4, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  8,  6,  9, 0x0),
    gsSPLight(&ttc_seg7_lights_rotating_cube_base_2.l, 1),
    gsSPLight(&ttc_seg7_lights_rotating_cube_base_2.a, 2),
    gsSPVertex(ttc_seg7_vertex_rotating_cube_base_2, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  4, 0x0),
    gsSP2Triangles( 5,  6,  7, 0x0,  8,  6,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700EC50 - 0x0700ECB8
static const Gfx ttc_seg7_sub_dl_rotating_cube_sides[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, machine_09005000_yellow_block),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ttc_seg7_vertex_rotating_cube_sides, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0,  0,  2, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700ECB8 - 0x0700ED68
const Gfx ttc_seg7_dl_rotating_cube[] = {
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
    gsSPDisplayList(ttc_seg7_sub_dl_rotating_cube_base),
    gsSPDisplayList(ttc_seg7_sub_dl_rotating_cube_sides),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
