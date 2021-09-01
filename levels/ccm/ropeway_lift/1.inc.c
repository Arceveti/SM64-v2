// 0x07010BD0 - 0x07010CC0
static const Vtx ccm_seg7_vertex_07010BD0[] = {
    {{{     0,   -154,   -133}, 0, ST_B(     0,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{  -205,   -154,   -133}, 0, ST_B(     0,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{  -205,   -154,    133}, 0, ST_B(    32,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{  -205,   -154,   -133}, 0, ST_B(     0,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{  -205,   -205,    133}, 0, ST_B(    32,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{  -205,   -154,    133}, 0, ST_B(    32,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{  -205,   -205,   -133}, 0, ST_B(     0,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{   205,   -154,    133}, 0, ST_B(    32,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{   205,   -205,    133}, 0, ST_B(    32,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{   205,   -205,   -133}, 0, ST_B(     0,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{   205,   -154,   -133}, 0, ST_B(     0,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,   -154,   -133}, 0, ST_B(     0,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,   -154,    133}, 0, ST_B(    32,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,   -205,   -133}, 0, ST_B(     0,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,   -154,    133}, 0, ST_B(    32,      0), {0xff, 0xff, 0xff, 0xff}}},
};

// 0x07010CC0 - 0x07010D30
static const Vtx ccm_seg7_vertex_07010CC0[] = {
    {{{   205,   -205,   -133}, 0, ST_B(     0,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,   -205,   -133}, 0, ST_B(     0,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,   -205,    133}, 0, ST_B(    32,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{   205,   -205,    133}, 0, ST_B(    32,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,   -205,   -133}, 0, ST_B(     0,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{  -205,   -205,    133}, 0, ST_B(    32,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,   -205,    133}, 0, ST_B(    32,      0), {0xff, 0xff, 0xff, 0xff}}},
};

// 0x07010D30 - 0x07010E30
static const Vtx ccm_seg7_vertex_07010D30[] = {
    {{{     0,   -256,   -133}, 0, ST_B(     0,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{   205,      0,   -133}, 0, ST_B(    32,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,      0,   -133}, 0, ST_B(     0,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{  -205,      0,    133}, 0, ST_B(    32,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,   -256,    133}, 0, ST_B(     0,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,      0,    133}, 0, ST_B(     0,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{  -205,   -256,    133}, 0, ST_B(    32,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,   -256,    133}, 0, ST_B(     0,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{   205,      0,    133}, 0, ST_B(    32,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,      0,    133}, 0, ST_B(     0,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{   205,   -256,    133}, 0, ST_B(    32,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{  -205,      0,   -133}, 0, ST_B(    32,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{  -205,   -256,   -133}, 0, ST_B(    32,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,   -256,   -133}, 0, ST_B(     0,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,      0,   -133}, 0, ST_B(     0,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{   205,   -256,   -133}, 0, ST_B(    32,      0), {0xff, 0xff, 0xff, 0xff}}},
};

// 0x07010E30 - 0x07010EC0
static const Gfx ccm_seg7_dl_07010E30[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snow_09000000_bridge_floor),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ccm_seg7_vertex_07010BD0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 10, 11, 12, 0x0),
    gsSP2Triangles(10, 12,  7, 0x0, 13,  6,  4, 0x0),
    gsSP1Triangle(  0,  2, 14, 0x0),
    gsSPVertex(ccm_seg7_vertex_07010CC0, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP1Triangle(  4,  5,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x07010EC0 - 0x07010F28
static const Gfx ccm_seg7_dl_07010EC0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, ccm_seg7_texture_broken_bridge_sides),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ccm_seg7_vertex_07010D30, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0, 15,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07010F28 - 0x07010FB8
const Gfx ccm_seg7_dl_ropeway_lift_platform[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, (G_TX_WRAP | G_TX_NOMIRROR), G_TX_NOMASK, G_TX_NOLOD, (G_TX_WRAP | G_TX_NOMIRROR), G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ccm_seg7_dl_07010E30),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, ((32 - 1) << G_TEXTURE_IMAGE_FRAC), ((32 - 1) << G_TEXTURE_IMAGE_FRAC)),
    gsSPDisplayList(ccm_seg7_dl_07010EC0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPEndDisplayList(),
};
