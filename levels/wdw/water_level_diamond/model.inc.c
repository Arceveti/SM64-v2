// 0x07012F18 - 0x07012F30
static const Lights1 wdw_seg7_lights_water_level_diamond_yellow = gdSPDefLights1(
    0x99, 0x99, 0x00,
    0xff, 0xff, 0x00, 0x28, 0x28, 0x28
);

// 0x07012F30 - 0x07012F48
static const Lights1 wdw_seg7_lights_water_level_diamond_blue = gdSPDefLights1(
    0x00, 0x00, 0x99,
    0x00, 0x00, 0xff, 0x28, 0x28, 0x28
);

// 0x07012F48 - 0x07012F60
static const Lights1 wdw_seg7_lights_water_level_diamond_green = gdSPDefLights1(
    0x00, 0x99, 0x00,
    0x00, 0xff, 0x00, 0x28, 0x28, 0x28
);

// 0x07012F60 - 0x07012F78
static const Lights1 wdw_seg7_lights_water_level_diamond_red = gdSPDefLights1(
    0x99, 0x00, 0x00,
    0xff, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x07012F78 - 0x07012FD8
static const Vtx wdw_seg7_vertex_water_level_diamond_yellow[] = {
    {{{   -51,     51,    -51}, 0, { 31<<5,      0}, {0xa6, 0x58, 0x00, 0xff}}},
    {{{   -51,     51,     51}, 0, {     0,      0}, {0xa6, 0x58, 0x00, 0xff}}},
    {{{     0,    102,      0}, 0, { 15<<5,  29<<5}, {0xa6, 0x58, 0x00, 0xff}}},
    {{{    51,     51,    -51}, 0, { 31<<5,      0}, {0x59, 0xa7, 0x00, 0xff}}},
    {{{    51,     51,     51}, 0, {     0,      0}, {0x59, 0xa7, 0x00, 0xff}}},
    {{{     0,      0,      0}, 0, { 15<<5,  29<<5}, {0x59, 0xa7, 0x00, 0xff}}},
};

// 0x07012FD8 - 0x07013038
static const Vtx wdw_seg7_vertex_water_level_diamond_blue[] = {
    {{{    51,     51,     51}, 0, { 31<<5,      0}, {0x59, 0x59, 0x00, 0xff}}},
    {{{    51,     51,    -51}, 0, {     0,      0}, {0x59, 0x59, 0x00, 0xff}}},
    {{{     0,    102,      0}, 0, { 15<<5,  29<<5}, {0x59, 0x59, 0x00, 0xff}}},
    {{{   -51,     51,     51}, 0, { 31<<5,      0}, {0xa6, 0xa8, 0x00, 0xff}}},
    {{{   -51,     51,    -51}, 0, {     0,      0}, {0xa6, 0xa8, 0x00, 0xff}}},
    {{{     0,      0,      0}, 0, { 15<<5,  29<<5}, {0xa6, 0xa8, 0x00, 0xff}}},
};

// 0x07013038 - 0x07013098
static const Vtx wdw_seg7_vertex_water_level_diamond_green[] = {
    {{{   -51,     51,     51}, 0, { 31<<5,      0}, {0x00, 0x59, 0x59, 0xff}}},
    {{{    51,     51,     51}, 0, {     0,      0}, {0x00, 0x59, 0x59, 0xff}}},
    {{{     0,    102,      0}, 0, { 15<<5,  29<<5}, {0x00, 0x59, 0x59, 0xff}}},
    {{{   -51,     51,    -51}, 0, { 31<<5,      0}, {0x00, 0xa8, 0xa6, 0xff}}},
    {{{    51,     51,    -51}, 0, {     0,      0}, {0x00, 0xa8, 0xa6, 0xff}}},
    {{{     0,      0,      0}, 0, { 15<<5,  29<<5}, {0x00, 0xa8, 0xa6, 0xff}}},
};

// 0x07013098 - 0x070130F8
static const Vtx wdw_seg7_vertex_water_level_diamond_red[] = {
    {{{    51,     51,     51}, 0, { 31<<5,      0}, {0x00, 0xa7, 0x59, 0xff}}},
    {{{   -51,     51,     51}, 0, {     0,      0}, {0x00, 0xa7, 0x59, 0xff}}},
    {{{     0,      0,      0}, 0, { 15<<5,  29<<5}, {0x00, 0xa7, 0x59, 0xff}}},
    {{{    51,     51,    -51}, 0, { 31<<5,      0}, {0x00, 0x58, 0xa6, 0xff}}},
    {{{   -51,     51,    -51}, 0, {     0,      0}, {0x00, 0x58, 0xa6, 0xff}}},
    {{{     0,    102,      0}, 0, { 15<<5,  29<<5}, {0x00, 0x58, 0xa6, 0xff}}},
};

// 0x070130F8 - 0x070131B8
static const Gfx wdw_seg7_sub_dl_water_level_diamond[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, wdw_seg7_texture_water_level_diamond),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&wdw_seg7_lights_water_level_diamond_yellow.l, 1),
    gsSPLight(&wdw_seg7_lights_water_level_diamond_yellow.a, 2),
    gsSPVertex(wdw_seg7_vertex_water_level_diamond_yellow, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPLight(&wdw_seg7_lights_water_level_diamond_blue.l, 1),
    gsSPLight(&wdw_seg7_lights_water_level_diamond_blue.a, 2),
    gsSPVertex(wdw_seg7_vertex_water_level_diamond_blue, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPLight(&wdw_seg7_lights_water_level_diamond_green.l, 1),
    gsSPLight(&wdw_seg7_lights_water_level_diamond_green.a, 2),
    gsSPVertex(wdw_seg7_vertex_water_level_diamond_green, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPLight(&wdw_seg7_lights_water_level_diamond_red.l, 1),
    gsSPLight(&wdw_seg7_lights_water_level_diamond_red.a, 2),
    gsSPVertex(wdw_seg7_vertex_water_level_diamond_red, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x070131B8 - 0x07013238
const Gfx wdw_seg7_dl_water_level_diamond[] = {
    gsDPPipeSync(),
    gsDPSetEnvColor(255, 255, 255, 200),
    gsDPSetCombineMode(G_CC_MODULATERGBFADE, G_CC_MODULATERGBFADE),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(wdw_seg7_sub_dl_water_level_diamond),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsDPSetEnvColor(255, 255, 255, 255),
    gsSPEndDisplayList(),
};
