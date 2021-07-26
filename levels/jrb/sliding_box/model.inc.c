// 0x07007EA0 - 0x07007EB8
static const Lights1 jrb_seg7_lights_sliding_box = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07007EB8 - 0x07007FB8
static const Vtx jrb_seg7_vertex_sliding_box_sides[] = {
    {{{   102,      0,     77}, 0, { 31<<5,  31<<5}, {0x33, 0xcd, 0x67, 0xff}}},
    {{{   102,    154,     77}, 0, { 31<<5,      0}, {0x54, 0x54, 0x2a, 0xff}}},
    {{{  -102,    154,     77}, 0, {     0,      0}, {0xcd, 0x33, 0x67, 0xff}}},
    {{{   102,      0,    -77}, 0, { 31<<5,  31<<5}, {0x54, 0xac, 0xd6, 0xff}}},
    {{{   102,    154,     77}, 0, {     0,      0}, {0x54, 0x54, 0x2a, 0xff}}},
    {{{   102,      0,     77}, 0, {     0,  31<<5}, {0x33, 0xcd, 0x67, 0xff}}},
    {{{   102,    154,    -77}, 0, { 31<<5,      0}, {0x33, 0x33, 0x99, 0xff}}},
    {{{  -102,      0,    -77}, 0, { 31<<5,  31<<5}, {0xcd, 0xcd, 0x99, 0xff}}},
    {{{   102,    154,    -77}, 0, {     0,      0}, {0x33, 0x33, 0x99, 0xff}}},
    {{{   102,      0,    -77}, 0, {     0,  31<<5}, {0x54, 0xac, 0xd6, 0xff}}},
    {{{  -102,    154,    -77}, 0, { 31<<5,      0}, {0xac, 0x54, 0xd6, 0xff}}},
    {{{  -102,      0,     77}, 0, { 31<<5,  31<<5}, {0xac, 0xac, 0x2a, 0xff}}},
    {{{  -102,    154,     77}, 0, { 31<<5,      0}, {0xcd, 0x33, 0x67, 0xff}}},
    {{{  -102,    154,    -77}, 0, {     0,      0}, {0xac, 0x54, 0xd6, 0xff}}},
    {{{  -102,      0,    -77}, 0, {     0,  31<<5}, {0xcd, 0xcd, 0x99, 0xff}}},
    {{{  -102,      0,     77}, 0, {     0,  31<<5}, {0xac, 0xac, 0x2a, 0xff}}},
};

// 0x07007FB8 - 0x07008038
static const Vtx jrb_seg7_vertex_sliding_box_top[] = {
    {{{  -102,      0,     77}, 0, {     0,      0}, {0xac, 0xac, 0x2a, 0xff}}},
    {{{   102,      0,    -77}, 0, { 31<<5,  31<<5}, {0x54, 0xac, 0xd6, 0xff}}},
    {{{   102,      0,     77}, 0, { 31<<5,      0}, {0x33, 0xcd, 0x67, 0xff}}},
    {{{  -102,      0,    -77}, 0, {     0,  31<<5}, {0xcd, 0xcd, 0x99, 0xff}}},
    {{{   102,    154,     77}, 0, { 31<<5,  31<<5}, {0x54, 0x54, 0x2a, 0xff}}},
    {{{   102,    154,    -77}, 0, { 31<<5,      0}, {0x33, 0x33, 0x99, 0xff}}},
    {{{  -102,    154,    -77}, 0, {     0,      0}, {0xac, 0x54, 0xd6, 0xff}}},
    {{{  -102,    154,     77}, 0, {     0,  31<<5}, {0xcd, 0x33, 0x67, 0xff}}},
};

// 0x07008038 - 0x070080B0
static const Gfx jrb_seg7_sub_dl_sliding_box_sides[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, jrb_seg7_texture_sliding_box_side),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&jrb_seg7_lights_sliding_box.l, 1),
    gsSPLight(&jrb_seg7_lights_sliding_box.a, 2),
    gsSPVertex(jrb_seg7_vertex_sliding_box_sides, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0,  2, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x070080B0 - 0x070080F8
static const Gfx jrb_seg7_sub_dl_sliding_box_top[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, jrb_seg7_texture_sliding_box_top),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(jrb_seg7_vertex_sliding_box_top, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x070080F8 - 0x070081A8
const Gfx jrb_seg7_dl_sliding_box[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetFogColor(5, 80, 75, 255),
    gsSPFogPosition(900, 1000),
    gsSPSetGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_PASS2),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(jrb_seg7_sub_dl_sliding_box_sides),
    gsSPDisplayList(jrb_seg7_sub_dl_sliding_box_top),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
