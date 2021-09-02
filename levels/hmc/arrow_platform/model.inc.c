// 0x07022B48 - 0x07022B60
static const Lights1 hmc_seg7_lights_controllable_arrow_platform = gdSPDefLights1(
    0x79, 0x79, 0x79,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07022B60 - 0x07022C60
static const Vtx hmc_seg7_vertex_controllable_arrow_platform_sides[] = {
    {{{   307,     51,    307}, 0, ST_B(    96,      0), {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -307,      0,    307}, 0, ST_B(     0,     32), {0x00, 0x00, 0x7f, 0xff}}},
    {{{   307,      0,    307}, 0, ST_B(    96,     32), {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -307,     51,    307}, 0, ST_B(     0,      0), {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -307,      0,   -307}, 0, ST_B(     0,     32), {0x00, 0x00, 0x81, 0xff}}},
    {{{   307,     51,   -307}, 0, ST_B(    96,      0), {0x00, 0x00, 0x81, 0xff}}},
    {{{   307,      0,   -307}, 0, ST_B(    96,     32), {0x00, 0x00, 0x81, 0xff}}},
    {{{  -307,     51,   -307}, 0, ST_B(     0,      0), {0x00, 0x00, 0x81, 0xff}}},
    {{{   307,      0,   -307}, 0, ST_B(    96,     32), {0x7f, 0x00, 0x00, 0xff}}},
    {{{   307,     51,   -307}, 0, ST_B(    96,      0), {0x7f, 0x00, 0x00, 0xff}}},
    {{{   307,     51,    307}, 0, ST_B(     0,      0), {0x7f, 0x00, 0x00, 0xff}}},
    {{{   307,      0,    307}, 0, ST_B(     0,     32), {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -307,      0,    307}, 0, ST_B(     0,     32), {0x81, 0x00, 0x00, 0xff}}},
    {{{  -307,     51,    307}, 0, ST_B(     0,      0), {0x81, 0x00, 0x00, 0xff}}},
    {{{  -307,     51,   -307}, 0, ST_B(    96,      0), {0x81, 0x00, 0x00, 0xff}}},
    {{{  -307,      0,   -307}, 0, ST_B(    96,     32), {0x81, 0x00, 0x00, 0xff}}},
};

// 0x07022C60 - 0x07022CE0
static const Vtx hmc_seg7_vertex_controllable_arrow_platform_surface[] = {
    {{{   307,      0,    307}, 0, ST_B(    96,    -64), {0x00, 0x81, 0x00, 0xff}}},
    {{{  -307,      0,   -307}, 0, ST_B(     0,     30), {0x00, 0x81, 0x00, 0xff}}},
    {{{   307,      0,   -307}, 0, ST_B(    96,     30), {0x00, 0x81, 0x00, 0xff}}},
    {{{  -307,      0,    307}, 0, ST_B(     0,    -64), {0x00, 0x81, 0x00, 0xff}}},
    {{{   307,     51,   -307}, 0, ST_B(    64,    -32), {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -307,     51,   -307}, 0, ST_B(   -32,    -32), {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -307,     51,    307}, 0, ST_B(   -32,     64), {0x00, 0x7f, 0x00, 0xff}}},
    {{{   307,     51,    307}, 0, ST_B(    64,     64), {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x07022CE0 - 0x07022D58
static const Gfx hmc_seg7_sub_dl_controllable_arrow_platform_sides[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, hmc_seg7_texture_arrow_platform_sides),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&hmc_seg7_lights_controllable_arrow_platform.l, 1),
    gsSPLight(&hmc_seg7_lights_controllable_arrow_platform.a, 2),
    gsSPVertex(hmc_seg7_vertex_controllable_arrow_platform_sides, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x07022D58 - 0x07022DA0
static const Gfx hmc_seg7_sub_dl_controllable_arrow_platform_surface[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, hmc_seg7_texture_arrow_platform_surface),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(hmc_seg7_vertex_controllable_arrow_platform_surface, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x07022DA0 - 0x07022E78
const Gfx hmc_seg7_dl_controllable_arrow_platform[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetFogColor(0, 0, 0, 255),
    gsSPFogPosition(960, 1000),
    gsSPSetGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_PASS2),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, (G_TX_WRAP | G_TX_NOMIRROR), G_TX_NOMASK, G_TX_NOLOD, (G_TX_WRAP | G_TX_NOMIRROR), G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, (G_TX_WRAP | G_TX_NOMIRROR), 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, ((32 - 1) << G_TEXTURE_IMAGE_FRAC), ((32 - 1) << G_TEXTURE_IMAGE_FRAC)),
    gsSPDisplayList(hmc_seg7_sub_dl_controllable_arrow_platform_sides),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, (G_TX_WRAP | G_TX_NOMIRROR), 5, G_TX_NOLOD, (G_TX_WRAP | G_TX_NOMIRROR), 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, ((32 - 1) << G_TEXTURE_IMAGE_FRAC), ((32 - 1) << G_TEXTURE_IMAGE_FRAC)),
    gsSPDisplayList(hmc_seg7_sub_dl_controllable_arrow_platform_surface),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
