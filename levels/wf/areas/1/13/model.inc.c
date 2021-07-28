// 0x07009900 - 0x07009918
static const Lights1 wf_seg7_lights_platform_with_wooden_bridge = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07009918 - 0x07009958
static const Vtx wf_seg7_vertex_bridge_platform_top[] = {
    {{{   794,     38,   -256}, 0, { 22452,   6608}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   128,     38,   -256}, 0, { 20408,   6608}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   128,     38,    512}, 0, { 20408,   8650}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   794,     38,    512}, 0, { 22452,   8650}, {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x07009958 - 0x07009A48
static const Vtx wf_seg7_vertex_bridge_platform_sides_1[] = {
    {{{   794,    -89,    512}, 0, { -3104,  31<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   128,    -89,   -256}, 0, { 31<<5,  -3104}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   794,    -89,   -256}, 0, { -3104,  -3104}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   794,     38,    512}, 0, {     0,  15<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   794,    -89,    512}, 0, {     0,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   794,    -89,   -256}, 0, { 63<<5,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   794,     38,   -256}, 0, { 63<<5,  15<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   128,     38,    512}, 0, {     0,  15<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   128,    -89,    512}, 0, {     0,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   794,    -89,    512}, 0, { 63<<5,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   794,     38,    512}, 0, { 63<<5,  15<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   128,     38,   -256}, 0, { -1056,  15<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   128,    -89,   -256}, 0, { -1056,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   128,    -89,    512}, 0, { 31<<5,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   128,     38,    512}, 0, { 31<<5,  15<<5}, {0x81, 0x00, 0x00, 0xff}}},
};

// 0x07009A48 - 0x07009AB8
static const Vtx wf_seg7_vertex_bridge_platform_sides_2[] = {
    {{{   794,     38,   -256}, 0, {     0,  15<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   128,    -89,   -256}, 0, { 63<<5,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   128,     38,   -256}, 0, { 63<<5,  15<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   794,    -89,    512}, 0, { -3104,  31<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   128,    -89,    512}, 0, { 31<<5,  31<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   128,    -89,   -256}, 0, { 31<<5,  -3104}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   794,    -89,   -256}, 0, {     0,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
};

// 0x07009AB8 - 0x07009BA8
static const Vtx wf_seg7_vertex__wooden_bridge_1[] = {
    {{{  -666,     38,   -179}, 0, {  7122,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -666,     64,   -179}, 0, {  7122,  18<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   358,     64,   -179}, 0, {     0,  18<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -666,     38,    -77}, 0, { 31<<5,    376}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -666,     64,    -77}, 0, { 31<<5,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -666,     64,   -179}, 0, {   176,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -666,     38,   -179}, 0, {   176,    376}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   358,     64,   -179}, 0, {  4568,  -1310}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -666,     64,   -179}, 0, {-13316,  -1310}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -666,     64,    -77}, 0, {-13316,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   358,     64,    -77}, 0, {  4568,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   358,     38,    -77}, 0, { 63<<5,   1396}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   358,     64,    -77}, 0, { 63<<5,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -666,     64,    -77}, 0, { -5140,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -666,     38,    -77}, 0, { -5140,   1396}, {0x00, 0x00, 0x7f, 0xff}}},
};

// 0x07009BA8 - 0x07009C58
static const Vtx wf_seg7_vertex__wooden_bridge_2[] = {
    {{{   358,     38,   -179}, 0, { 31<<5,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   358,     64,   -179}, 0, { 31<<5,    582}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   358,     64,    -77}, 0, {     0,    582}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -666,     38,   -179}, 0, {  7122,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   358,     64,   -179}, 0, {     0,    582}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   358,     38,   -179}, 0, {     0,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   358,     38,    -77}, 0, {  4568,      0}, {0x00, 0x81, 0x00, 0xff}}},
    {{{  -666,     38,    -77}, 0, {-13316,      0}, {0x00, 0x81, 0x00, 0xff}}},
    {{{  -666,     38,   -179}, 0, {-13316,  -1310}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   358,     38,   -179}, 0, {  4568,  -1310}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   358,     38,    -77}, 0, {     0,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
};

// 0x07009C58 - 0x07009CA0
static const Gfx wf_seg7_sub_dl_bridge_platform_top[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09001000_brown_brick_floor),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&wf_seg7_lights_platform_with_wooden_bridge.l, 1),
    gsSPLight(&wf_seg7_lights_platform_with_wooden_bridge.a, 2),
    gsSPVertex(wf_seg7_vertex_bridge_platform_top, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07009CA0 - 0x07009D20
static const Gfx wf_seg7_sub_dl_bridge_platform_sides[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09000800_brown_brick_wall),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(wf_seg7_vertex_bridge_platform_sides_1, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle( 11, 13, 14, 0x0),
    gsSPVertex(wf_seg7_vertex_bridge_platform_sides_2, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle(  0,  6,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07009D20 - 0x07009DB0
static const Gfx wf_seg7_sub_dl_wooden_bridge[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09006800_wood),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(wf_seg7_vertex__wooden_bridge_1, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle( 11, 13, 14, 0x0),
    gsSPVertex(wf_seg7_vertex__wooden_bridge_2, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP1Triangle(  0,  2, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x07009DB0 - 0x07009E30
const Gfx wf_seg7_dl_platform_with_wooden_bridge[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(wf_seg7_sub_dl_bridge_platform_top),
    gsSPDisplayList(wf_seg7_sub_dl_bridge_platform_sides),
    gsSPDisplayList(wf_seg7_sub_dl_wooden_bridge),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
