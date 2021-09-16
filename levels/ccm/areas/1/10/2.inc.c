// 0x070106D8 - 0x07010758
static const Vtx ccm_seg7_vertex_wkww_fence[] = {
    {{{ -1457,   -890,    550}, 0, { 23466,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  -377,   -397,    185}, 0, { 11430,     24}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  -377,   -499,    185}, 0, { 11436,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{ -1457,   -787,    550}, 0, { 23460,     24}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   703,     -6,   -178}, 0, { -2624,     24}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   703,   -108,   -178}, 0, { -2618,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  -377,   -499,    185}, 0, {  9410,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  -377,   -397,    185}, 0, {  9404,     24}, {0xff, 0xff, 0xff, 0xff}}},
};

// 0x07010758 - 0x07010848
static const Vtx ccm_seg7_vertex_wkww_icicles[] = {
    {{{ -1120,    297,    768}, 0, {  3368,      0}, {0xff, 0xff, 0xff, 0xff}}}, //  0
    {{{ -1120,    553,    768}, 0, {  3376,  31<<5}, {0xff, 0xff, 0xff, 0xff}}}, //  1
    {{{ -1586,    553,    982}, 0, {     0,  31<<5}, {0xff, 0xff, 0xff, 0xff}}}, //  2
    {{{ -1120,    348,    768}, 0, { -5376,      0}, {0xff, 0xff, 0xff, 0xff}}}, //  3
    {{{   -12,    336,    666}, 0, {  2028,      0}, {0xff, 0xff, 0xff, 0xff}}}, //  4
    {{{ -1120,    553,    768}, 0, { -5392,  31<<5}, {0xff, 0xff, 0xff, 0xff}}}, //  5
    {{{   -12,    540,    666}, 0, { 63<<5,  31<<5}, {0xff, 0xff, 0xff, 0xff}}}, //  6
    {{{   -55,    336,    574}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}}, //  7
    {{{ -1163,    348,    677}, 0, {  7372,      0}, {0xff, 0xff, 0xff, 0xff}}}, //  8
    {{{ -1163,    553,    677}, 0, {  7388,  31<<5}, {0xff, 0xff, 0xff, 0xff}}}, //  9
    {{{   -55,    540,    574}, 0, {     0,  31<<5}, {0xff, 0xff, 0xff, 0xff}}}, // 10
    {{{ -1333,    297,    307}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}}, // 11
    {{{ -1333,    553,    307}, 0, {     0,  31<<5}, {0xff, 0xff, 0xff, 0xff}}}, // 12
    {{{ -1120,    553,    768}, 0, {  3376,  31<<5}, {0xff, 0xff, 0xff, 0xff}}}, // 13
    {{{ -1120,    297,    768}, 0, {  3372,      0}, {0xff, 0xff, 0xff, 0xff}}}, // 14
    {{{ -1800,    297,    512}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}}, // 15
    {{{ -1800,    553,    512}, 0, {     0,  31<<5}, {0xff, 0xff, 0xff, 0xff}}}, // 16
    {{{ -1333,    553,    307}, 0, {  3376,  31<<5}, {0xff, 0xff, 0xff, 0xff}}}, // 17
    {{{ -1586,    297,    982}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}}, // 18
    {{{ -1586,    297,    982}, 0, {  3368,      0}, {0xff, 0xff, 0xff, 0xff}}}, // 19
    {{{ -1586,    553,    982}, 0, {  3372,  31<<5}, {0xff, 0xff, 0xff, 0xff}}}, // 20
    {{{ -1333,    297,    307}, 0, {  3368,      0}, {0xff, 0xff, 0xff, 0xff}}}, // 21
};

// 0x070108F8 - 0x07010940
static const Gfx ccm_seg7_dl_wkww_fence[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snow_09005800_fence),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ccm_seg7_vertex_wkww_fence, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  4,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x07010940 - 0x070109D0
static const Gfx ccm_seg7_dl_wkww_icicles[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snow_09007000_icicles),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(64, 32), CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ccm_seg7_vertex_wkww_icicles, 22, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(13, 14, 11, 0x0, 17, 21, 15, 0x0),
    gsSP2Triangles(15, 16, 17, 0x0,  0,  2, 18, 0x0),
    gsSP2Triangles(19, 20, 16, 0x0, 16, 15, 19, 0x0),
    gsSPEndDisplayList(),
};

// 0x070109D0 - 0x07010A60
const Gfx ccm_seg7_dl_wkww_fence_and_icicles[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ccm_seg7_dl_wkww_fence),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ccm_seg7_dl_wkww_icicles),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPEndDisplayList(),
};
