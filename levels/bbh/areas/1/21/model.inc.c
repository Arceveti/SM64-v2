// 0x07012580 - 0x07012680
static const Vtx bbh_seg7_vertex_library_window_glass[] = {
    {{{ -1050,   1178,   1075}, 0, { 17<<5,  17<<5}, {0x09, 0xb3, 0xff, 0x80}}},
    {{{  -870,   1382,   1075}, 0, { 31<<5,  31<<5}, {0x09, 0xb3, 0xff, 0x80}}},
    {{{ -1050,   1382,   1075}, 0, { 17<<5,  31<<5}, {0x09, 0xb3, 0xff, 0x80}}},
    {{{ -1280,    922,   1075}, 0, {     0,      0}, {0x09, 0xb3, 0xff, 0x80}}},
    {{{ -1101,    922,   1075}, 0, {   416,      0}, {0x09, 0xb3, 0xff, 0x80}}},
    {{{ -1101,   1126,   1075}, 0, {   416,    416}, {0x09, 0xb3, 0xff, 0x80}}},
    {{{ -1280,   1126,   1075}, 0, {     0,    416}, {0x09, 0xb3, 0xff, 0x80}}},
    {{{ -1050,    922,   1075}, 0, { 17<<5,      0}, {0x09, 0xb3, 0xff, 0x80}}},
    {{{  -870,    922,   1075}, 0, { 31<<5,      0}, {0x09, 0xb3, 0xff, 0x80}}},
    {{{  -870,   1126,   1075}, 0, { 31<<5,    416}, {0x09, 0xb3, 0xff, 0x80}}},
    {{{ -1050,   1126,   1075}, 0, { 17<<5,    416}, {0x09, 0xb3, 0xff, 0x80}}},
    {{{ -1280,   1178,   1075}, 0, {     0,  17<<5}, {0x09, 0xb3, 0xff, 0x80}}},
    {{{ -1101,   1382,   1075}, 0, {   416,  31<<5}, {0x09, 0xb3, 0xff, 0x80}}},
    {{{ -1280,   1382,   1075}, 0, {     0,  31<<5}, {0x09, 0xb3, 0xff, 0x80}}},
    {{{ -1101,   1178,   1075}, 0, {   416,  17<<5}, {0x09, 0xb3, 0xff, 0x80}}},
    {{{  -870,   1178,   1075}, 0, { 31<<5,  17<<5}, {0x09, 0xb3, 0xff, 0x80}}},
};

// 0x07012680 - 0x070126E8
static const Gfx bbh_seg7_sub_dl_library_window_glass[] = {
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, spooky_0900B000_light_linear),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_library_window_glass, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0,  0, 15,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x070126E8 - 0x07012758
const Gfx bbh_seg7_dl_library_window_glass[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_sub_dl_library_window_glass),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPEndDisplayList(),
};
