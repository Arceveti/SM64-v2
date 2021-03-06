// 0x0703BD28 - 0x0703BD40
static const Lights1 inside_castle_seg7_lights_0703BD28 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0703BD40 - 0x0703BE40
static const Vtx inside_castle_seg7_vertex_0703BD40[] = {
    {{{   -77,      0,    -16}, 0, { 16<<5,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   -77,      0,     16}, 0, { 31<<5,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   -77,    256,     16}, 0, { 31<<5,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   -77,    256,    -16}, 0, {  1100,    464}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{    77,    256,     16}, 0, {  -656,    240}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{    77,    256,    -16}, 0, {  -544,  23<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   -77,    256,     16}, 0, { 31<<5,    -32}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{    77,      0,    -16}, 0, {  1234,   -112}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   -77,      0,     16}, 0, {  -176,    864}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   -77,      0,    -16}, 0, {  -608,    496}, {0x00, 0x81, 0x00, 0xff}}},
    {{{    77,      0,     16}, 0, {  1664,    256}, {0x00, 0x81, 0x00, 0xff}}},
    {{{    77,      0,     16}, 0, {     0,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{    77,      0,    -16}, 0, {   584,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{    77,    256,    -16}, 0, {   584,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{    77,    256,     16}, 0, {     0,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   -77,    256,    -16}, 0, { 16<<5,      0}, {0x81, 0x00, 0x00, 0xff}}},
};

// 0x0703BE40 - 0x0703BE80
static const Vtx inside_castle_seg7_vertex_0703BE40[] = {
    {{{   -77,      0,     16}, 0, ST_B(     0,     64), {0x00, 0x00, 0x7f, 0xff}}},
    {{{    77,      0,     16}, 0, ST_B(    32,     64), {0x00, 0x00, 0x7f, 0xff}}},
    {{{    77,    256,     16}, 0, ST_B(    32,      0), {0x00, 0x00, 0x7f, 0xff}}},
    {{{   -77,    256,     16}, 0, ST_B(     0,      0), {0x00, 0x00, 0x7f, 0xff}}},
};

// 0x0703BE80 - 0x0703BEC0
static const Vtx inside_castle_seg7_vertex_0703BE80[] = {
    {{{    77,      0,    -16}, 0, ST_B(     0,     64), {0x00, 0x00, 0x81, 0xff}}},
    {{{   -77,    256,    -16}, 0, ST_B(    32,      0), {0x00, 0x00, 0x81, 0xff}}},
    {{{    77,    256,    -16}, 0, ST_B(     0,      0), {0x00, 0x00, 0x81, 0xff}}},
    {{{   -77,      0,    -16}, 0, ST_B(    32,     64), {0x00, 0x00, 0x81, 0xff}}},
};

// 0x0703BEC0 - 0x0703BF38
static const Gfx inside_castle_seg7_dl_0703BEC0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_castle_seg7_texture_star_door_edges),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&inside_castle_seg7_lights_0703BD28.l, 1),
    gsSPLight(&inside_castle_seg7_lights_0703BD28.a, 2),
    gsSPVertex(inside_castle_seg7_vertex_0703BD40, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0,  2, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x0703BF38 - 0x0703BF70
static const Gfx inside_castle_seg7_dl_0703BF38[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_castle_seg7_texture_star_door_left_side),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 64), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(inside_castle_seg7_vertex_0703BE40, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0703BF70 - 0x0703BFA8
static const Gfx inside_castle_seg7_dl_0703BF70[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_castle_seg7_texture_star_door_right_side),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 64), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(inside_castle_seg7_vertex_0703BE80, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0703BFA8 - 0x0703C040
const Gfx inside_castle_seg7_dl_star_door[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(inside_castle_seg7_dl_0703BEC0),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(inside_castle_seg7_dl_0703BF38),
    gsSPDisplayList(inside_castle_seg7_dl_0703BF70),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
