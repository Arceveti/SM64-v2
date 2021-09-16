// 0x07014CB8 - 0x07014CD0
static const Lights1 hmc_seg7_lights_toxic_maze_toxic_drip = gdSPDefLights1(
    0x23, 0x2b, 0x14,
    0x8e, 0xac, 0x52, 0x28, 0x28, 0x28
);

// 0x07014CD0 - 0x07014DD0
static const Vtx hmc_seg7_vertex_toxic_maze_toxic_drip[] = {
    {{{  3165,   -410,  -6339}, 0, ST_B(    32,     14), {0x00, 0x00, 0x7f, 0x80}}},
    {{{  3113,   -870,  -6339}, 0, ST_B(     0,     32), {0x00, 0x00, 0x7f, 0x80}}},
    {{{  3165,   -870,  -6339}, 0, ST_B(    32,     32), {0x00, 0x00, 0x7f, 0x80}}},
    {{{  3482,   -666,  -6339}, 0, ST_B(     0,     32), {0x00, 0x00, 0x7f, 0x80}}},
    {{{  3533,   -666,  -6339}, 0, ST_B(    32,     32), {0x00, 0x00, 0x7f, 0x80}}},
    {{{  3533,   -410,  -6339}, 0, ST_B(    32,     14), {0x00, 0x00, 0x7f, 0x80}}},
    {{{  3482,   -410,  -6339}, 0, ST_B(     0,     14), {0x00, 0x00, 0x7f, 0x80}}},
    {{{  3328,   -922,  -6339}, 0, ST_B(     0,     32), {0x00, 0x00, 0x7f, 0x80}}},
    {{{  3431,   -922,  -6339}, 0, ST_B(    32,     32), {0x00, 0x00, 0x7f, 0x80}}},
    {{{  3431,   -410,  -6339}, 0, ST_B(    32,     14), {0x00, 0x00, 0x7f, 0x80}}},
    {{{  3328,   -410,  -6339}, 0, ST_B(     0,     14), {0x00, 0x00, 0x7f, 0x80}}},
    {{{  3277,   -410,  -6339}, 0, ST_B(    32,     14), {0x00, 0x00, 0x7f, 0x80}}},
    {{{  3226,   -819,  -6339}, 0, ST_B(     0,     32), {0x00, 0x00, 0x7f, 0x80}}},
    {{{  3277,   -819,  -6339}, 0, ST_B(    32,     32), {0x00, 0x00, 0x7f, 0x80}}},
    {{{  3226,   -410,  -6339}, 0, ST_B(     0,     14), {0x00, 0x00, 0x7f, 0x80}}},
    {{{  3113,   -410,  -6339}, 0, ST_B(     0,     14), {0x00, 0x00, 0x7f, 0x80}}},
};

// 0x07014DD0 - 0x07014E48
static const Gfx hmc_seg7_sub_dl_toxic_maze_toxic_drip[] = {
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, cave_0900C000_light_radial),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&hmc_seg7_lights_toxic_maze_toxic_drip.l, 1),
    gsSPLight(&hmc_seg7_lights_toxic_maze_toxic_drip.a, 2),
    gsSPVertex(hmc_seg7_vertex_toxic_maze_toxic_drip, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0,  0, 15,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07014E48 - 0x07014EB8
const Gfx hmc_seg7_dl_toxic_maze_toxic_drip[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(hmc_seg7_sub_dl_toxic_maze_toxic_drip),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
