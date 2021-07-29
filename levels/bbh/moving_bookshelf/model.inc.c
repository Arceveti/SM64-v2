// 0x0701FB20 - 0x0701FB38
static const Lights1 bbh_seg7_lights_moving_bookshelf = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0701FB38 - 0x0701FB78
static const Vtx bbh_seg7_vertex_0701FB38[] = {
    {{{  -256,    819,   -205}, 0, { 31<<5,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -154,    819,   -205}, 0, { 23<<5,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -154,      0,   -205}, 0, { 23<<5,  63<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -256,      0,   -205}, 0, { 31<<5,  63<<5}, {0x00, 0x00, 0x81, 0xff}}},
};

// 0x0701FB78 - 0x0701FC78
static const Vtx bbh_seg7_vertex_0701FB78[] = {
    {{{  -256,      0,    205}, 0, { 63<<5,  63<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -256,    512,    205}, 0, { 63<<5,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -256,    512,   -205}, 0, {     0,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -154,    512,   -205}, 0, { 63<<5,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   256,      0,   -205}, 0, {     0,  63<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -154,      0,   -205}, 0, { 63<<5,  63<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   256,    512,   -205}, 0, {     0,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -154,    819,   -205}, 0, { 63<<5,  18<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   256,    512,   -205}, 0, {     0,   1808}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -154,    512,   -205}, 0, { 63<<5,   1808}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   256,    819,   -205}, 0, {     0,  18<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -256,    512,    205}, 0, { 63<<5,   1808}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -256,    819,   -205}, 0, {     0,  18<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -256,    512,   -205}, 0, {     0,   1808}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -256,    819,    205}, 0, { 63<<5,  18<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -256,      0,   -205}, 0, {     0,  63<<5}, {0x81, 0x00, 0x00, 0xff}}},
};

// 0x0701FC78 - 0x0701FCC0
static const Gfx bbh_seg7_dl_0701FC78[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09003800_house_wall),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&bbh_seg7_lights_moving_bookshelf.l, 1),
    gsSPLight(&bbh_seg7_lights_moving_bookshelf.a, 2),
    gsSPVertex(bbh_seg7_vertex_0701FB38, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0701FCC0 - 0x0701FD28
static const Gfx bbh_seg7_dl_0701FCC0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09002800_bookshelf),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_0701FB78, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0,  0,  2, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x0701FD28 - 0x0701FDB8
const Gfx bbh_seg7_dl_moving_bookshelf[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_0701FC78),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_0701FCC0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
