// 0x070191F0 - 0x07019230
static const Vtx lll_seg7_vertex_long_wooden_bridge_top[] = {
    {{{  -256,    154,   -576}, 0, { 31<<5,   1008}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -256,    154,    576}, 0, { 31<<5,  -8258}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   256,    154,    576}, 0, {     0,  -8258}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   256,    154,   -576}, 0, {     0,   1008}, {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x07019230 - 0x07019330
static const Vtx lll_seg7_vertex_long_wooden_bridge_sides[] = {
    {{{  -256,      0,   -576}, 0, {  3374,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -256,    154,   -576}, 0, {  3374,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   256,    154,   -576}, 0, {     0,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -256,      0,    576}, 0, {  7634,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -256,    154,   -576}, 0, {     0,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -256,      0,   -576}, 0, {     0,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -256,    154,    576}, 0, {  7634,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   256,      0,    576}, 0, {  3374,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -256,    154,    576}, 0, {     0,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -256,      0,    576}, 0, {     0,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   256,    154,    576}, 0, {  3374,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   256,      0,   -576}, 0, {  7122,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   256,    154,    576}, 0, {  -544,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   256,      0,    576}, 0, {  -544,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   256,    154,   -576}, 0, {  7122,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   256,      0,   -576}, 0, {     0,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
};

// 0x07019330 - 0x07019378
static const Gfx lll_seg7_sub_dl_long_wooden_bridge_top[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, fire_0900B800_arrows_platform),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&lll_seg7_lights_gray_0x3f_0xff_0x28.l, 1),
    gsSPLight(&lll_seg7_lights_gray_0x3f_0xff_0x28.a, 2),
    gsSPVertex(lll_seg7_vertex_long_wooden_bridge_top, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07019378 - 0x070193E0
static const Gfx lll_seg7_sub_dl_long_wooden_bridge_sides[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, fire_09007800_bricks_with_lava),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(lll_seg7_vertex_long_wooden_bridge_sides, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0,  0,  2, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x070193E0 - 0x07019470
const Gfx lll_seg7_dl_long_wooden_bridge[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(lll_seg7_sub_dl_long_wooden_bridge_top),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(lll_seg7_sub_dl_long_wooden_bridge_sides),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
