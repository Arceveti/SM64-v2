// 0x07013730 - 0x070137B0
static const Vtx ccm_seg7_vertex_snowman_head_eyes[] = {
    {{{   120,     41,    177}, 0, ST_B(    32,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{    41,     41,    200}, 0, ST_B(     0,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{   120,    -41,    176}, 0, ST_B(    32,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{    41,    -41,    198}, 0, ST_B(     0,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{  -120,    -41,    176}, 0, ST_B(     0,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{   -41,    -41,    198}, 0, ST_B(    32,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{   -41,     41,    200}, 0, ST_B(    32,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{  -120,     41,    177}, 0, ST_B(     0,      0), {0xff, 0xff, 0xff, 0xff}}},
};

// 0x070137B0 - 0x070137F0
static const Vtx ccm_seg7_vertex_snowman_head_mouth[] = {
    {{{    51,    -68,    196}, 0, ST_B(    32,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{   -51,    -68,    196}, 0, ST_B(     0,      0), {0xff, 0xff, 0xff, 0xff}}},
    {{{   -51,   -118,    160}, 0, ST_B(     0,     32), {0xff, 0xff, 0xff, 0xff}}},
    {{{    51,   -118,    160}, 0, ST_B(    32,     32), {0xff, 0xff, 0xff, 0xff}}},
};

// 0x070137F0 - 0x07013838
static const Gfx ccm_seg7_sub_dl_snowman_head_eyes[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, ccm_seg7_texture_snowman_eye),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ccm_seg7_vertex_snowman_head_eyes, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x07013838 - 0x07013870
static const Gfx ccm_seg7_sub_dl_snowman_head_mouth[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, ccm_seg7_texture_snowman_mouth),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ccm_seg7_vertex_snowman_head_mouth, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07013870 - 0x070138E8
const Gfx ccm_seg7_dl_snowman_head_face[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, (G_TX_WRAP | G_TX_NOMIRROR), G_TX_NOMASK, G_TX_NOLOD, (G_TX_WRAP | G_TX_NOMIRROR), G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, ((32 - 1) << G_TEXTURE_IMAGE_FRAC), ((32 - 1) << G_TEXTURE_IMAGE_FRAC)),
    gsSPDisplayList(ccm_seg7_sub_dl_snowman_head_eyes),
    gsSPDisplayList(ccm_seg7_sub_dl_snowman_head_mouth),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
