// 0x07007298 - 0x070072B0
static const Lights1 wf_seg7_lights_floating_brick_platform = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x070072B0 - 0x070073A0
static const Vtx wf_seg7_vertex_floating_brick_platform_sides_1[] = {
    {{{  -256,     64,    256}, 0, { -1308,    336}, {0x00, 0xe7, 0x7c, 0xff}}},
    {{{   205,    -64,    230}, 0, { 31<<5,  31<<5}, {0x00, 0xe7, 0x7c, 0xff}}},
    {{{   256,     64,    256}, 0, {  1246,    336}, {0x00, 0xe7, 0x7c, 0xff}}},
    {{{   256,     64,    256}, 0, {  -160,    304}, {0x75, 0xd1, 0x00, 0xff}}},
    {{{   205,    -64,   -230}, 0, {  2268,  31<<5}, {0x75, 0xd1, 0x00, 0xff}}},
    {{{   256,     64,   -256}, 0, {  2396,    304}, {0x75, 0xd1, 0x00, 0xff}}},
    {{{   205,    -64,    230}, 0, {     0,  31<<5}, {0x75, 0xd1, 0x00, 0xff}}},
    {{{   256,     64,   -256}, 0, { -1308,    336}, {0x00, 0xe7, 0x84, 0xff}}},
    {{{   205,    -64,   -230}, 0, { -1056,  31<<5}, {0x00, 0xe7, 0x84, 0xff}}},
    {{{  -205,    -64,   -230}, 0, { 31<<5,  31<<5}, {0x00, 0xe7, 0x84, 0xff}}},
    {{{  -256,     64,   -256}, 0, {  1246,    336}, {0x00, 0xe7, 0x84, 0xff}}},
    {{{  -256,     64,   -256}, 0, { -1562,      0}, {0x8b, 0xd1, 0x00, 0xff}}},
    {{{  -205,    -64,    230}, 0, {   864,    656}, {0x8b, 0xd1, 0x00, 0xff}}},
    {{{  -256,     64,    256}, 0, { 31<<5,      0}, {0x8b, 0xd1, 0x00, 0xff}}},
    {{{  -205,    -64,   -230}, 0, { -1436,    656}, {0x8b, 0xd1, 0x00, 0xff}}},
};

// 0x070073A0 - 0x07007410
static const Vtx wf_seg7_vertex_floating_brick_platform_sides_2[] = {
    {{{   205,    -64,    230}, 0, { -1056,  31<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{  -205,    -64,    230}, 0, { 31<<5,  31<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{  -205,    -64,   -230}, 0, { 31<<5,  -1310}, {0x00, 0x81, 0x00, 0xff}}},
    {{{  -256,     64,    256}, 0, { -1308,    336}, {0x00, 0xe7, 0x7c, 0xff}}},
    {{{  -205,    -64,    230}, 0, { -1056,  31<<5}, {0x00, 0xe7, 0x7c, 0xff}}},
    {{{   205,    -64,    230}, 0, { 31<<5,  31<<5}, {0x00, 0xe7, 0x7c, 0xff}}},
    {{{   205,    -64,   -230}, 0, { -1056,  -1310}, {0x00, 0x81, 0x00, 0xff}}},
};

// 0x07007410 - 0x07007450
static const Vtx wf_seg7_vertex_floating_brick_platform_top[] = {
    {{{   256,     64,   -256}, 0, { 31<<5,  -1566}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -256,     64,    256}, 0, { -1564,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   256,     64,    256}, 0, { 31<<5,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -256,     64,   -256}, 0, { -1564,  -1566}, {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x07007450 - 0x070074E0
static const Gfx wf_seg7_sub_dl_floating_brick_platform_sides[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09000800_brown_brick_wall),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&wf_seg7_lights_floating_brick_platform.l, 1),
    gsSPLight(&wf_seg7_lights_floating_brick_platform.a, 2),
    gsSPVertex(wf_seg7_vertex_floating_brick_platform_sides_1, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle( 11, 14, 12, 0x0),
    gsSPVertex(wf_seg7_vertex_floating_brick_platform_sides_2, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle(  0,  2,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x070074E0 - 0x07007518
static const Gfx wf_seg7_sub_dl_floating_brick_platform_top[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09001000_brown_brick_floor),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(wf_seg7_vertex_floating_brick_platform_top, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07007518 - 0x07007590
const Gfx wf_seg7_dl_floating_brick_platform[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(wf_seg7_sub_dl_floating_brick_platform_sides),
    gsSPDisplayList(wf_seg7_sub_dl_floating_brick_platform_top),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
