// 0x07020368 - 0x07020380
static const Lights1 bbh_seg7_lights_coffin = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07020380 - 0x07020480
static const Vtx bbh_seg7_vertex_sides[] = {
    {{{    58,      0,      0}, 0, ST_B(    32,     16), {0x00, 0x00, 0x7f, 0xff}}},
    {{{   -58,     77,      0}, 0, ST_B(     0,      0), {0x00, 0x00, 0x7f, 0xff}}},
    {{{   -58,      0,      0}, 0, ST_B(     0,     16), {0x00, 0x00, 0x7f, 0xff}}},
    {{{    58,     77,      0}, 0, ST_B(    32,      0), {0x00, 0x00, 0x7f, 0xff}}},
    {{{   115,      0,   -307}, 0, ST_B(    64,     16), {0x7c, 0x00, 0x17, 0xff}}},
    {{{    58,     77,      0}, 0, ST_B(     0,      0), {0x7c, 0x00, 0x17, 0xff}}},
    {{{    58,      0,      0}, 0, ST_B(     0,     16), {0x7c, 0x00, 0x17, 0xff}}},
    {{{   115,     77,   -307}, 0, ST_B(    64,      0), {0x7c, 0x00, 0x17, 0xff}}},
    {{{    58,      0,   -461}, 0, ST_B(    32,     16), {0x77, 0x00, 0xd4, 0xff}}},
    {{{   115,     77,   -307}, 0, ST_B(     0,      0), {0x77, 0x00, 0xd4, 0xff}}},
    {{{   115,      0,   -307}, 0, ST_B(     0,     16), {0x77, 0x00, 0xd4, 0xff}}},
    {{{    58,     77,   -461}, 0, ST_B(    32,      0), {0x77, 0x00, 0xd4, 0xff}}},
    {{{   -58,      0,   -461}, 0, ST_B(     0,     16), {0x00, 0x00, 0x81, 0xff}}},
    {{{    58,     77,   -461}, 0, ST_B(    32,      0), {0x00, 0x00, 0x81, 0xff}}},
    {{{    58,      0,   -461}, 0, ST_B(    32,     16), {0x00, 0x00, 0x81, 0xff}}},
    {{{   -58,     77,   -461}, 0, ST_B(     0,      0), {0x00, 0x00, 0x81, 0xff}}},
    {{{  -115,      0,   -307}, 0, ST_B(     0,     16), {0x89, 0x00, 0xd4, 0xff}}},
    {{{  -115,     77,   -307}, 0, ST_B(     0,      0), {0x89, 0x00, 0xd4, 0xff}}},
    {{{   -58,     77,   -461}, 0, ST_B(    32,      0), {0x89, 0x00, 0xd4, 0xff}}},
    {{{   -58,      0,   -461}, 0, ST_B(    32,     16), {0x89, 0x00, 0xd4, 0xff}}},
    {{{   -58,      0,      0}, 0, ST_B(     0,     16), {0x84, 0x00, 0x17, 0xff}}},
    {{{  -115,     77,   -307}, 0, ST_B(    64,      0), {0x84, 0x00, 0x17, 0xff}}},
    {{{  -115,      0,   -307}, 0, ST_B(    64,     16), {0x84, 0x00, 0x17, 0xff}}},
    {{{   -58,     77,      0}, 0, ST_B(     0,      0), {0x84, 0x00, 0x17, 0xff}}},
};

// 0x07020500 - 0x07020560
static const Vtx bbh_seg7_vertex_coffin_inside[] = {
    {{{   -58,      0,   -461}, 0, ST_B(    96,     36), {0x00, 0x81, 0x00, 0xff}}},
    {{{    58,      0,   -461}, 0, ST_B(    96,     12), {0x00, 0x81, 0x00, 0xff}}},
    {{{   115,      0,   -307}, 0, ST_B(    64,      0), {0x00, 0x81, 0x00, 0xff}}},
    {{{  -115,      0,   -307}, 0, ST_B(    64,     48), {0x00, 0x81, 0x00, 0xff}}},
    {{{   -58,      0,      0}, 0, ST_B(     0,     36), {0x00, 0x81, 0x00, 0xff}}},
    {{{    58,      0,      0}, 0, ST_B(     0,     12), {0x00, 0x81, 0x00, 0xff}}},
};

// 0x07020560 - 0x070205C0
static const Vtx bbh_seg7_vertex_coffin_back[] = {
    {{{   -58,     77,      0}, 0, ST_B(     8,     64), {0x00, 0x7f, 0x00, 0xff}}},
    {{{   115,     77,   -307}, 0, ST_B(    32,     21), {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -115,     77,   -307}, 0, ST_B(     0,     21), {0x00, 0x7f, 0x00, 0xff}}},
    {{{    58,     77,      0}, 0, ST_B(    24,     64), {0x00, 0x7f, 0x00, 0xff}}},
    {{{    58,     77,   -461}, 0, ST_B(    24,      0), {0x00, 0x7f, 0x00, 0xff}}},
    {{{   -58,     77,   -461}, 0, ST_B(     8,      0), {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x070205C0 - 0x07020660
static const Gfx bbh_seg7_sub_dl_coffin_sides[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bbh_seg7_texture_coffin_side),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 16), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&bbh_seg7_lights_coffin.l, 1),
    gsSPLight(&bbh_seg7_lights_coffin.a, 2),
    gsSPVertex(bbh_seg7_vertex_sides, 24, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSP2Triangles(16, 17, 18, 0x0, 16, 18, 19, 0x0),
    gsSP2Triangles(20, 21, 22, 0x0, 20, 23, 21, 0x0),
    gsSPEndDisplayList(),
};

// 0x07020660 - 0x070206A8
static const Gfx bbh_seg7_sub_dl_coffin_inside[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bbh_seg7_texture_coffin_inside),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 16), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_coffin_inside, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 2,  4,  3, 0x0,  2,  5,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x070206A8 - 0x070206F0
static const Gfx bbh_seg7_sub_dl_coffin_back[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bbh_seg7_texture_coffin_back),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 64), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_coffin_back, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 1,  4,  5, 0x0,  1,  5,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x070206F0 - 0x070207A0
const Gfx bbh_seg7_dl_coffin[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 4, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (16 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_sub_dl_coffin_sides),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 4, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (16 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_sub_dl_coffin_inside),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_sub_dl_coffin_back),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
