// 0x07013DB8 - 0x07013E38
static const Vtx hmc_seg7_vertex_toxic_maze_hanging_grass[] = {
    {{{  5671,   -307,    819}, 0, ST_B(   192,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{  5671,   -205,    205}, 0, ST_B(     0,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{  5671,   -307,    205}, 0, ST_B(     0,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{  5671,   -205,    819}, 0, ST_B(   192,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{  5466,   -512,    819}, 0, ST_B(   192,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{  5466,   -410,    205}, 0, ST_B(     0,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{  5466,   -512,    205}, 0, ST_B(     0,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{  5466,   -410,    819}, 0, ST_B(   192,      0), {0xff, 0xff, 0xff, 0xff}}},
};

// 0x07013E38 - 0x07013E80
static const Gfx hmc_seg7_sub_dl_toxic_maze_hanging_grass[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, cave_09003000_hanging_grass),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(hmc_seg7_vertex_toxic_maze_hanging_grass, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x07013E80 - 0x07013F38
const Gfx hmc_seg7_dl_toxic_maze_hanging_grass[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetFogColor(0, 0, 0, 255),
    gsSPFogPosition(HMC_FOG_MIN, HMC_FOG_MAX),
    gsSPSetGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_PASS2),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(hmc_seg7_sub_dl_toxic_maze_hanging_grass),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPEndDisplayList(),
};
