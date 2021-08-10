// 0x0702AA30 - 0x0702AA70
static const Vtx ttm_seg7_vertex_yellow_smiley[] = {
    {{{  1024,   2048,      0}, 0, { 31<<5,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{ -1024,   2048,      0}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{ -1024,      0,      0}, 0, {     0,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  1024,      0,      0}, 0, { 31<<5,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
};

// 0x0702AA70 - 0x0702AAA8
static const Gfx ttm_seg7_sub_dl_yellow_smiley[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, mountain_09003000_yellow_smiley),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ttm_seg7_vertex_yellow_smiley, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0702AAA8 - 0x0702AB18
const Gfx ttm_seg7_dl_yellow_smiley[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttm_seg7_sub_dl_yellow_smiley),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
