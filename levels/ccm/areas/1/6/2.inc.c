// 0x0700E790 - 0x0700E850
static const Vtx ccm_seg7_vertex_upper_cabin_fence[] = {
    {{{   433,   -205,   -410}, 0, {  4566,    224}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  -488,    -51,   -410}, 0, {     0,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   433,    -51,   -410}, 0, {  4566,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  -488,   -205,   -410}, 0, {     0,    224}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  -488,   -205,   -103}, 0, {  1528,    224}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  -488,    -51,   -410}, 0, {    -6,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  -488,   -205,   -410}, 0, {    -6,    224}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  -488,    -51,   -103}, 0, {  1528,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  -488,    -51,    203}, 0, {   680,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  -488,   -205,    357}, 0, {  1446,    224}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  -488,    -51,    357}, 0, {  1446,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  -488,   -205,    203}, 0, {   680,    224}, {0xff, 0xff, 0xff, 0xff}}},
};

// 0x0700E850 - 0x0700E8D0
static const Vtx ccm_seg7_vertex_upper_cabin_icicles[] = {
    {{{   433,     41,   -195}, 0, {     0,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  -355,     -9,   -195}, 0, { 15708,    -34}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  -355,     41,   -195}, 0, { 15708,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   433,     -9,   -195}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  -355,     41,   -195}, 0, {     0,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  -355,     -9,   -195}, 0, {   -40,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  -355,     72,    357}, 0, { 11112,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  -355,    123,    357}, 0, { 11128,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
};

// 0x0700E8D0 - 0x0700E928
static const Gfx ccm_seg7_dl_upper_cabin_fence[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snow_09000000_bridge_floor),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ccm_seg7_vertex_upper_cabin_fence, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700E928 - 0x0700E970
static const Gfx ccm_seg7_dl_upper_cabin_icicles[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snow_09007000_icicles),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(64, 32), CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ccm_seg7_vertex_upper_cabin_icicles, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700E970 - 0x0700EA00
const Gfx ccm_seg7_dl_upper_cabin_fence_and_icicles[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ccm_seg7_dl_upper_cabin_fence),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ccm_seg7_dl_upper_cabin_icicles),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPEndDisplayList(),
};
