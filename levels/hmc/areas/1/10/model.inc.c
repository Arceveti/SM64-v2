// 0x0700FF70 - 0x0700FF88
static const Lights1 hmc_seg7_lights_grass_floor_for_red_coins_star = gdSPDefLights1(
    0x79, 0x79, 0x79,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0700FF88 - 0x07010008
static const Vtx hmc_seg7_vertex_grass_floor_for_red_coins_star[] = {
    {{{  3891,      0,   4608}, 0, {  1756,   -800}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  4403,      0,   4813}, 0, {  2522,    992}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  4198,      0,   4608}, 0, {  2522,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  4403,      0,   5120}, 0, {  1756,   1754}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  4198,      0,   5325}, 0, {   736,   1754}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  3891,      0,   5325}, 0, {     0,    992}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  3686,      0,   5120}, 0, {     0,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  3686,      0,   4813}, 0, {   736,   -800}, {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x07010008 - 0x07010070
static const Gfx hmc_seg7_sub_dl_grass_floor_for_red_coins_star[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09006800_grass_floor),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&hmc_seg7_lights_grass_floor_for_red_coins_star.l, 1),
    gsSPLight(&hmc_seg7_lights_grass_floor_for_red_coins_star.a, 2),
    gsSPVertex(hmc_seg7_vertex_grass_floor_for_red_coins_star, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 0,  4,  3, 0x0,  0,  5,  4, 0x0),
    gsSP2Triangles( 0,  6,  5, 0x0,  0,  7,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x07010070 - 0x07010118
const Gfx hmc_seg7_dl_grass_floor_for_red_coins_star[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_DECAL2),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetFogColor(0, 0, 0, 255),
    gsSPFogPosition(HMC_FOG_MIN, HMC_FOG_MAX),
    gsSPSetGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_PASS2),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(hmc_seg7_sub_dl_grass_floor_for_red_coins_star),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_DECAL, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
