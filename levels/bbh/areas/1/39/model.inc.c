// 0x0701EF58 - 0x0701F018
static const Vtx bbh_seg7_vertex_outside_lantern[] = {
    {{{ -1562,    538,  -1674}, 0, ST_B(    16,     32), {0xff, 0xcc, 0x90, 0xff}}},
    {{{ -1536,    614,  -1649}, 0, ST_B(     0,      0), {0xff, 0xcc, 0x90, 0xff}}},
    {{{ -1536,    538,  -1649}, 0, ST_B(     0,     32), {0xff, 0xcc, 0x90, 0xff}}},
    {{{ -1562,    614,  -1674}, 0, ST_B(    16,      0), {0xff, 0xcc, 0x90, 0xff}}},
    {{{ -1587,    538,  -1649}, 0, ST_B(    32,     32), {0xff, 0xcc, 0x90, 0xff}}},
    {{{ -1562,    538,  -1674}, 0, ST_B(    16,     32), {0xff, 0xcc, 0x90, 0xff}}},
    {{{ -1587,    614,  -1649}, 0, ST_B(    32,      0), {0xff, 0xcc, 0x90, 0xff}}},
    {{{ -1562,    614,  -1674}, 0, ST_B(    16,     32), {0xff, 0xcc, 0x90, 0xff}}},
    {{{ -1587,    614,  -1649}, 0, ST_B(    32,     16), {0xff, 0xcc, 0x90, 0xff}}},
    {{{ -1536,    614,  -1649}, 0, ST_B(     0,     16), {0xff, 0xcc, 0x90, 0xff}}},
    {{{ -1587,    538,  -1649}, 0, ST_B(    32,     16), {0xff, 0xcc, 0x90, 0xff}}},
    {{{ -1536,    538,  -1649}, 0, ST_B(     0,     16), {0xff, 0xcc, 0x90, 0xff}}},
};

// 0x0701F018 - 0x0701F070
static const Gfx bbh_seg7_sub_dl_outside_lantern[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09006800_lamp),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_outside_lantern, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  3,  5, 0x0,  4,  6,  3, 0x0),
    gsSP2Triangles( 7,  8,  9, 0x0, 10,  5, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x0701F070 - 0x0701F0E0
const Gfx bbh_seg7_dl_outside_lantern[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_sub_dl_outside_lantern),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
