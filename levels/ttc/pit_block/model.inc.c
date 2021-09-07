// 0x07010DE8 - 0x07010E00
static const Lights1 ttc_seg7_lights_pit_block = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07010E00 - 0x07010E80
static const Vtx ttc_seg7_vertex_pit_block_top[] = {
    {{{   102,      0,    102}, 0, ST_B(    32,     32), {0x49, 0xb7, 0x49, 0xff}}},
    {{{  -102,      0,    102}, 0, ST_B(     0,     32), {0xb7, 0xb7, 0x49, 0xff}}},
    {{{   102,      0,   -102}, 0, ST_B(    32,      0), {0x49, 0xb7, 0xb7, 0xff}}},
    {{{  -102,      0,   -102}, 0, ST_B(     0,      0), {0xb7, 0xb7, 0xb7, 0xff}}},
    {{{   102,    205,   -102}, 0, ST_B(    32,      0), {0x33, 0x67, 0xcd, 0xff}}},
    {{{  -102,    205,    102}, 0, ST_B(     0,     32), {0xcd, 0x67, 0x33, 0xff}}},
    {{{   102,    205,    102}, 0, ST_B(    32,     32), {0x54, 0x2a, 0x54, 0xff}}},
    {{{  -102,    205,   -102}, 0, ST_B(     0,      0), {0xac, 0x2a, 0xac, 0xff}}},
};

// 0x07010E80 - 0x07010F80
static const Vtx ttc_seg7_vertex_pit_block_sides[] = {
    {{{   102,    205,    102}, 0, ST_B(    32,      0), {0x54, 0x2a, 0x54, 0xff}}},
    {{{  -102,    205,    102}, 0, ST_B(     0,      0), {0xcd, 0x67, 0x33, 0xff}}},
    {{{  -102,      0,    102}, 0, ST_B(     0,     32), {0xb7, 0xb7, 0x49, 0xff}}},
    {{{   102,    205,    102}, 0, ST_B(     0,      0), {0x54, 0x2a, 0x54, 0xff}}},
    {{{   102,      0,    102}, 0, ST_B(     0,     32), {0x49, 0xb7, 0x49, 0xff}}},
    {{{   102,      0,   -102}, 0, ST_B(    32,     32), {0x49, 0xb7, 0xb7, 0xff}}},
    {{{   102,    205,   -102}, 0, ST_B(    32,      0), {0x33, 0x67, 0xcd, 0xff}}},
    {{{  -102,    205,   -102}, 0, ST_B(    32,      0), {0xac, 0x2a, 0xac, 0xff}}},
    {{{   102,      0,   -102}, 0, ST_B(     0,     32), {0x49, 0xb7, 0xb7, 0xff}}},
    {{{  -102,      0,   -102}, 0, ST_B(    32,     32), {0xb7, 0xb7, 0xb7, 0xff}}},
    {{{   102,    205,   -102}, 0, ST_B(     0,      0), {0x33, 0x67, 0xcd, 0xff}}},
    {{{  -102,    205,   -102}, 0, ST_B(     0,      0), {0xac, 0x2a, 0xac, 0xff}}},
    {{{  -102,      0,   -102}, 0, ST_B(     0,     32), {0xb7, 0xb7, 0xb7, 0xff}}},
    {{{  -102,      0,    102}, 0, ST_B(    32,     32), {0xb7, 0xb7, 0x49, 0xff}}},
    {{{  -102,    205,    102}, 0, ST_B(    32,      0), {0xcd, 0x67, 0x33, 0xff}}},
    {{{   102,      0,    102}, 0, ST_B(    32,     32), {0x49, 0xb7, 0x49, 0xff}}},
};

// 0x07010F80 - 0x07010FD8
static const Gfx ttc_seg7_sub_dl_pit_block_top[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, machine_09007000_metal_block),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttc_seg7_lights_pit_block.l, 1),
    gsSPLight(&ttc_seg7_lights_pit_block.a, 2),
    gsSPVertex(ttc_seg7_vertex_pit_block_top, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x07010FD8 - 0x07011040
static const Gfx ttc_seg7_sub_dl_pit_block_sides[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, machine_09003000_block_side),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ttc_seg7_vertex_pit_block_sides, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0,  2, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x07011040 - 0x07011108
const Gfx ttc_seg7_dl_pit_block[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetFogColor(200, 255, 255, 255),
    gsSPFogPosition(970, 1000),
    gsSPSetGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_PASS2),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, (G_TX_WRAP | G_TX_NOMIRROR), G_TX_NOMASK, G_TX_NOLOD, (G_TX_WRAP | G_TX_NOMIRROR), G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, (G_TX_WRAP | G_TX_NOMIRROR), 5, G_TX_NOLOD, (G_TX_WRAP | G_TX_NOMIRROR), 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, ((32 - 1) << G_TEXTURE_IMAGE_FRAC), ((32 - 1) << G_TEXTURE_IMAGE_FRAC)),
    gsSPDisplayList(ttc_seg7_sub_dl_pit_block_top),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, (G_TX_WRAP | G_TX_NOMIRROR), 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, ((32 - 1) << G_TEXTURE_IMAGE_FRAC), ((32 - 1) << G_TEXTURE_IMAGE_FRAC)),
    gsSPDisplayList(ttc_seg7_sub_dl_pit_block_sides),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
