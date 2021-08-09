// 0x07018708 - 0x07018808
static const Vtx lll_seg7_vertex_rotating_block_fire_bars_1[] = {
    {{{  -166,      0,      0}, 0, {     0,  16<<5}, {0x95, 0x1a, 0xc2, 0xff}}},
    {{{  -116,    205,      0}, 0, {   168,  -1014}, {0x95, 0x1a, 0xc2, 0xff}}},
    {{{   -58,    205,   -102}, 0, {  1098,  -1014}, {0x95, 0x1a, 0xc2, 0xff}}},
    {{{   -83,      0,   -144}, 0, {  1296,  16<<5}, {0x95, 0x1a, 0xc2, 0xff}}},
    {{{   -58,    205,   -102}, 0, {  -496,   -832}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -116,    205,      0}, 0, {  -960,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   -58,    205,    102}, 0, {  -496,    768}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{    58,    205,    102}, 0, {   432,    768}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   116,    205,      0}, 0, {   896,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{    58,    205,   -102}, 0, {   432,   -832}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   -83,      0,    144}, 0, {  1190,   1638}, {0x95, 0x1a, 0x3e, 0xff}}},
    {{{   -58,    205,    102}, 0, { 31<<5,      0}, {0x95, 0x1a, 0x3e, 0xff}}},
    {{{  -166,      0,      0}, 0, {  -138,   1638}, {0x95, 0x1a, 0x3e, 0xff}}},
    {{{   -58,    205,    102}, 0, { 31<<5,      0}, {0x95, 0x1a, 0x3d, 0xff}}},
    {{{  -116,    205,      0}, 0, {    64,      0}, {0x95, 0x1a, 0x3d, 0xff}}},
    {{{  -166,      0,      0}, 0, {  -138,   1638}, {0x95, 0x1a, 0x3d, 0xff}}},
};

// 0x07018808 - 0x07018908
static const Vtx lll_seg7_vertex_rotating_block_fire_bars_2[] = {
    {{{   -83,      0,   -144}, 0, { -1358,  16<<5}, {0x00, 0x1a, 0x84, 0xff}}},
    {{{   -58,    205,   -102}, 0, { -1160,  -1014}, {0x00, 0x1a, 0x84, 0xff}}},
    {{{    58,    205,   -102}, 0, {  -224,  -1014}, {0x00, 0x1a, 0x84, 0xff}}},
    {{{    83,      0,    144}, 0, {     0,  31<<5}, {0x00, 0x1a, 0x7c, 0xff}}},
    {{{   -58,    205,    102}, 0, { -1160,   -682}, {0x00, 0x1a, 0x7c, 0xff}}},
    {{{   -83,      0,    144}, 0, { -1358,  31<<5}, {0x00, 0x1a, 0x7c, 0xff}}},
    {{{    58,    205,    102}, 0, {  -224,   -682}, {0x00, 0x1a, 0x7c, 0xff}}},
    {{{   166,      0,      0}, 0, {  1296,  31<<5}, {0x6b, 0x1a, 0x3d, 0xff}}},
    {{{   116,    205,      0}, 0, {  1098,   -682}, {0x6b, 0x1a, 0x3d, 0xff}}},
    {{{    58,    205,    102}, 0, {   168,   -682}, {0x6b, 0x1a, 0x3d, 0xff}}},
    {{{   166,      0,      0}, 0, {  1296,  31<<5}, {0x6b, 0x1a, 0x3e, 0xff}}},
    {{{    58,    205,    102}, 0, {   168,   -682}, {0x6b, 0x1a, 0x3e, 0xff}}},
    {{{    83,      0,    144}, 0, {     0,  31<<5}, {0x6b, 0x1a, 0x3e, 0xff}}},
    {{{    83,      0,   -144}, 0, {  -144,   1162}, {0x6b, 0x1a, 0xc2, 0xff}}},
    {{{    58,    205,   -102}, 0, {    64,   -364}, {0x6b, 0x1a, 0xc2, 0xff}}},
    {{{   116,    205,      0}, 0, { 31<<5,   -364}, {0x6b, 0x1a, 0xc2, 0xff}}},
};

// 0x07018908 - 0x07018968
static const Vtx lll_seg7_vertex_rotating_block_fire_bars_3[] = {
    {{{    83,      0,   -144}, 0, {  -144,   1162}, {0x6b, 0x1a, 0xc2, 0xff}}},
    {{{   116,    205,      0}, 0, { 31<<5,   -364}, {0x6b, 0x1a, 0xc2, 0xff}}},
    {{{   166,      0,      0}, 0, {  1190,   1162}, {0x6b, 0x1a, 0xc2, 0xff}}},
    {{{   -83,      0,   -144}, 0, { -1358,  16<<5}, {0x00, 0x1a, 0x84, 0xff}}},
    {{{    58,    205,   -102}, 0, {  -224,  -1014}, {0x00, 0x1a, 0x84, 0xff}}},
    {{{    83,      0,   -144}, 0, {     0,  16<<5}, {0x00, 0x1a, 0x84, 0xff}}},
};

// 0x07018968 - 0x07018A30
static const Gfx lll_seg7_sub_dl_rotating_block_fire_bars[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, lll_seg7_texture_dark_rock),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&lll_seg7_lights_gray_0x3f_0xff_0x28.l, 1),
    gsSPLight(&lll_seg7_lights_gray_0x3f_0xff_0x28.a, 2),
    gsSPVertex(lll_seg7_vertex_rotating_block_fire_bars_1, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 4,  7,  8, 0x0,  4,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(lll_seg7_vertex_rotating_block_fire_bars_2, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(lll_seg7_vertex_rotating_block_fire_bars_3, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x07018A30 - 0x07018AA0
const Gfx lll_seg7_dl_rotating_block_fire_bars[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(lll_seg7_sub_dl_rotating_block_fire_bars),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
