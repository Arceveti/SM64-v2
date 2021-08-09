// 0x070183F0 - 0x07018470
static const Vtx lll_seg7_vertex_drawbridge_front[] = {
    {{{     0,   -102,   -192}, 0, {     0,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{     0,      0,    192}, 0, {  3800,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{     0,   -102,    192}, 0, {  3800,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{     0,      0,   -192}, 0, {     0,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -640,   -102,    192}, 0, {  3800,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -640,      0,   -192}, 0, {     0,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -640,   -102,   -192}, 0, {     0,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -640,      0,    192}, 0, {  3800,      0}, {0x81, 0x00, 0x00, 0xff}}},
};

// 0x07018470 - 0x070184B0
static const Vtx lll_seg7_vertex_drawbridge_top[] = {
    {{{     0,      0,   -192}, 0, { -5140,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -640,      0,   -192}, 0, {     0,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -640,      0,    192}, 0, {     0,  -2080}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{     0,      0,    192}, 0, { -5140,  -2080}, {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x070184B0 - 0x070184F0
static const Vtx lll_seg7_vertex_drawbridge_bottom[] = {
    {{{     0,   -102,    192}, 0, { -3352,    864}, {0x00, 0x81, 0x00, 0xff}}},
    {{{  -640,   -102,    192}, 0, {  -160,    864}, {0x00, 0x81, 0x00, 0xff}}},
    {{{  -640,   -102,   -192}, 0, {  -160,  -1056}, {0x00, 0x81, 0x00, 0xff}}},
    {{{     0,   -102,   -192}, 0, { -3352,  -1056}, {0x00, 0x81, 0x00, 0xff}}},
};

// 0x070184F0 - 0x07018570
static const Vtx lll_seg7_vertex_drawbridge_sides[] = {
    {{{     0,   -102,    192}, 0, {  5334,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{     0,      0,    192}, 0, {  5334,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -640,      0,    192}, 0, { -1056,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -640,   -102,    192}, 0, { -1056,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -640,   -102,   -192}, 0, {  2268,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -640,      0,   -192}, 0, {  2268,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{     0,      0,   -192}, 0, { -4118,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{     0,   -102,   -192}, 0, { -4118,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
};

// 0x07018570 - 0x070185C8
static const Gfx lll_seg7_sub_dl_drawbridge_front[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, lll_seg7_texture_drawbridge_front),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&lll_seg7_lights_gray_0x3f_0xff_0x28.l, 1),
    gsSPLight(&lll_seg7_lights_gray_0x3f_0xff_0x28.a, 2),
    gsSPVertex(lll_seg7_vertex_drawbridge_front, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x070185C8 - 0x07018600
static const Gfx lll_seg7_sub_dl_drawbridge_top[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, fire_0900A000_metal_with_rivets),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(lll_seg7_vertex_drawbridge_top, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07018600 - 0x07018638
static const Gfx lll_seg7_sub_dl_drawbridge_bottom[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, fire_09001800_gray_rock),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(lll_seg7_vertex_drawbridge_bottom, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07018638 - 0x07018680
static const Gfx lll_seg7_sub_dl_drawbridge_sides[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, lll_seg7_texture_drawbridge_side),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(lll_seg7_vertex_drawbridge_sides, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x07018680 - 0x07018708
const Gfx lll_seg7_dl_drawbridge_part[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(lll_seg7_sub_dl_drawbridge_front),
    gsSPDisplayList(lll_seg7_sub_dl_drawbridge_top),
    gsSPDisplayList(lll_seg7_sub_dl_drawbridge_bottom),
    gsSPDisplayList(lll_seg7_sub_dl_drawbridge_sides),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
