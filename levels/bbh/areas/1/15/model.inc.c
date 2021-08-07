// 0x0700D500 - 0x0700D600
static const Vtx bbh_seg7_vertex_0700D500[] = {
    {{{  -538,      0,   1756}, 0, {     0,    208}, {0xff, 0xec, 0x40, 0x50}}},
    {{{  -538,    282,   2038}, 0, {     0,    752}, {0xff, 0xec, 0x40, 0x50}}},
    {{{  -538,    538,   2038}, 0, {     0,  31<<5}, {0xff, 0xec, 0x40, 0x50}}},
    {{{ -1664,   1357,   2447}, 0, { 23<<5,      0}, {0xff, 0xec, 0x40, 0x50}}},
    {{{ -1408,   1459,   2550}, 0, { 31<<5,  31<<5}, {0xff, 0xec, 0x40, 0x50}}},
    {{{ -1408,   1357,   2447}, 0, { 23<<5,      0}, {0xff, 0xec, 0x40, 0x50}}},
    {{{ -1664,   1459,   2550}, 0, { 31<<5,  31<<5}, {0xff, 0xec, 0x40, 0x50}}},
    {{{ -1664,   1101,   2447}, 0, {  3<<5,      0}, {0xff, 0xec, 0x40, 0x50}}},
    {{{ -1664,   1203,   2550}, 0, { 11<<5,  31<<5}, {0xff, 0xec, 0x40, 0x50}}},
    {{{ -1408,   1203,   2550}, 0, { 11<<5,  31<<5}, {0xff, 0xec, 0x40, 0x50}}},
    {{{ -1408,   1101,   2447}, 0, {  3<<5,      0}, {0xff, 0xec, 0x40, 0x50}}},
    {{{  -282,      0,   1756}, 0, { 31<<5,    208}, {0xff, 0xec, 0x40, 0x50}}},
    {{{  -538,      0,   1500}, 0, {     0,      0}, {0xff, 0xec, 0x40, 0x50}}},
    {{{ -1664,      0,   2268}, 0, {     0,    208}, {0xff, 0xec, 0x40, 0x50}}},
    {{{ -1664,    282,   2550}, 0, {     0,    752}, {0xff, 0xec, 0x40, 0x50}}},
    {{{ -1664,    538,   2550}, 0, {     0,  31<<5}, {0xff, 0xec, 0x40, 0x50}}},
};

// 0x0700D600 - 0x0700D6F0
static const Vtx bbh_seg7_vertex_0700D600[] = {
    {{{  -282,      0,   1756}, 0, { 31<<5,    208}, {0xff, 0xec, 0x40, 0x50}}},
    {{{  -282,    282,   2038}, 0, { 31<<5,    752}, {0xff, 0xec, 0x40, 0x50}}},
    {{{  -538,    282,   2038}, 0, {     0,    752}, {0xff, 0xec, 0x40, 0x50}}},
    {{{  -538,      0,   1500}, 0, {     0,      0}, {0xff, 0xec, 0x40, 0x50}}},
    {{{  -538,    538,   2038}, 0, {     0,  31<<5}, {0xff, 0xec, 0x40, 0x50}}},
    {{{  -282,    538,   2038}, 0, { 31<<5,  31<<5}, {0xff, 0xec, 0x40, 0x50}}},
    {{{  -282,      0,   1500}, 0, { 31<<5,      0}, {0xff, 0xec, 0x40, 0x50}}},
    {{{ -1664,      0,   2012}, 0, {     0,      0}, {0xff, 0xec, 0x40, 0x50}}},
    {{{ -1408,    538,   2550}, 0, { 31<<5,  31<<5}, {0xff, 0xec, 0x40, 0x50}}},
    {{{ -1408,      0,   2012}, 0, { 31<<5,      0}, {0xff, 0xec, 0x40, 0x50}}},
    {{{ -1664,    538,   2550}, 0, {     0,  31<<5}, {0xff, 0xec, 0x40, 0x50}}},
    {{{ -1664,      0,   2268}, 0, {     0,    208}, {0xff, 0xec, 0x40, 0x50}}},
    {{{ -1408,    282,   2550}, 0, { 31<<5,    752}, {0xff, 0xec, 0x40, 0x50}}},
    {{{ -1408,      0,   2268}, 0, { 31<<5,    208}, {0xff, 0xec, 0x40, 0x50}}},
    {{{ -1664,    282,   2550}, 0, {     0,    752}, {0xff, 0xec, 0x40, 0x50}}},
};

// 0x0700D6F0 - 0x0700D7E0
static const Gfx bbh_seg7_dl_0700D6F0[] = {
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, spooky_0900B000_light_linear),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_0700D500, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  6,  3, 0x0),
    gsSP2Triangles( 7,  8,  6, 0x0,  5,  4,  9, 0x0),
    gsSP2Triangles( 5,  9, 10, 0x0, 10,  9,  8, 0x0),
    gsSP2Triangles(10,  8,  7, 0x0, 11,  1,  0, 0x0),
    gsSP2Triangles( 0,  2, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(bbh_seg7_vertex_0700D600, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  6,  5,  1, 0x0),
    gsSP2Triangles( 6,  1,  0, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 10,  7, 0x0),
    gsSP2Triangles( 9,  8, 12, 0x0,  9, 12, 13, 0x0),
    gsSP2Triangles(13, 12, 14, 0x0, 13, 14, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700D7E0 - 0x0700D850
const Gfx bbh_seg7_dl_0700D7E0[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_0700D6F0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPEndDisplayList(),
};
