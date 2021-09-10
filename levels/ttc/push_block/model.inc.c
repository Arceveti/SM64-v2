// 0x070100B0 - 0x070100C8
static const Lights1 ttc_seg7_lights_push_block = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x070100C8 - 0x070101C8
static const Vtx ttc_seg7_vertex_push_block_sides[] = {
    {{{   102,    102,   -450}, 0, {  7<<5,  31<<5}, {0x38, 0x71, 0x00, 0xff}}},
    {{{  -102,    102,     10}, 0, {  2268,      0}, {0xcd, 0x67, 0x33, 0xff}}},
    {{{   102,    102,     10}, 0, {  7<<5,      0}, {0x54, 0x2a, 0x54, 0xff}}},
    {{{   102,    102,     10}, 0, {  2268,      0}, {0x54, 0x2a, 0x54, 0xff}}},
    {{{   102,   -102,   -450}, 0, {  7<<5,  31<<5}, {0x71, 0xc8, 0x00, 0xff}}},
    {{{   102,    102,   -450}, 0, {  2268,  31<<5}, {0x38, 0x71, 0x00, 0xff}}},
    {{{   102,   -102,     10}, 0, {  7<<5,      0}, {0x33, 0x99, 0x33, 0xff}}},
    {{{  -102,    102,   -450}, 0, { -1308,  31<<5}, {0x8f, 0x38, 0x00, 0xff}}},
    {{{  -102,   -102,   -450}, 0, { 23<<5,  31<<5}, {0xc8, 0x8f, 0x00, 0xff}}},
    {{{  -102,   -102,     10}, 0, { 23<<5,      0}, {0xac, 0xd6, 0x54, 0xff}}},
    {{{  -102,    102,     10}, 0, { -1308,      0}, {0xcd, 0x67, 0x33, 0xff}}},
    {{{   102,   -102,     10}, 0, {  2268,      0}, {0x33, 0x99, 0x33, 0xff}}},
    {{{  -102,   -102,     10}, 0, {  7<<5,      0}, {0xac, 0xd6, 0x54, 0xff}}},
    {{{  -102,   -102,   -450}, 0, {  7<<5,  31<<5}, {0xc8, 0x8f, 0x00, 0xff}}},
    {{{   102,   -102,   -450}, 0, {  2268,  31<<5}, {0x71, 0xc8, 0x00, 0xff}}},
    {{{  -102,    102,   -450}, 0, {  2268,  31<<5}, {0x8f, 0x38, 0x00, 0xff}}},
};

// 0x070101C8 - 0x07010208
static const Vtx ttc_seg7_vertex_push_block_front[] = {
    {{{   102,    102,     10}, 0, ST_B(    32,      1), {0x54, 0x2a, 0x54, 0xff}}},
    {{{  -102,   -102,     10}, 0, ST_B(     0,     32), {0xac, 0xd6, 0x54, 0xff}}},
    {{{   102,   -102,     10}, 0, ST_B(    32,     32), {0x33, 0x99, 0x33, 0xff}}},
    {{{  -102,    102,     10}, 0, ST_B(     0,      1), {0xcd, 0x67, 0x33, 0xff}}},
};

// 0x07010208 - 0x07010280
static const Gfx ttc_seg7_sub_dl_push_block_sides[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, machine_09003800_vertical_rods),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttc_seg7_lights_push_block.l, 1),
    gsSPLight(&ttc_seg7_lights_push_block.a, 2),
    gsSPVertex(ttc_seg7_vertex_push_block_sides, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0, 15,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07010280 - 0x070102B8
static const Gfx ttc_seg7_sub_dl_push_block_front[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, machine_09003000_block_side),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ttc_seg7_vertex_push_block_front, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x070102B8 - 0x07010380
const Gfx ttc_seg7_dl_push_block[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetFogColor(200, 255, 255, 255),
    gsSPFogPosition(TTC_FOG_MIN, TTC_FOG_MAX),
    gsSPSetGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_PASS2),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttc_seg7_sub_dl_push_block_sides),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttc_seg7_sub_dl_push_block_front),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
