// 0x07006668 - 0x07006680
static const Lights1 wf_seg7_lights_platform_between_sliding_platforms = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07006680 - 0x070066C0
static const Vtx wf_seg7_vertex_platform_between_sliding_platforms_top[] = {
    {{{   256,   1075,   -256}, 0, { -9228,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -256,   1075,   -256}, 0, { -9228,  -1056}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -256,   1075,    256}, 0, {-11272,  -1056}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   256,   1075,    256}, 0, {-11272,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x070066C0 - 0x07006780
static const Vtx wf_seg7_vertex_platform_between_sliding_platforms_sides[] = {
    {{{   256,   1075,    256}, 0, { 95<<5,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   256,      0,   -256}, 0, {159<<5,   4258}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   256,   1075,   -256}, 0, {159<<5,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   256,      0,    256}, 0, { 95<<5,   4258}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -256,   1075,    256}, 0, { -1056,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   256,      0,    256}, 0, { 31<<5,   4258}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   256,   1075,    256}, 0, { 31<<5,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -256,      0,    256}, 0, { -1056,   4258}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   256,   1075,   -256}, 0, { -1056,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -256,      0,   -256}, 0, { 31<<5,   4258}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -256,   1075,   -256}, 0, { 31<<5,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   256,      0,   -256}, 0, { -1056,   4258}, {0x00, 0x00, 0x81, 0xff}}},
};

// 0x07006780 - 0x070067C8
static const Gfx wf_seg7_sub_dl_platform_between_sliding_platforms_top[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09001000_brown_brick_floor),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&wf_seg7_lights_platform_between_sliding_platforms.l, 1),
    gsSPLight(&wf_seg7_lights_platform_between_sliding_platforms.a, 2),
    gsSPVertex(wf_seg7_vertex_platform_between_sliding_platforms_top, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x070067C8 - 0x07006820
static const Gfx wf_seg7_sub_dl_platform_between_sliding_platforms_sides[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09000800_brown_brick_wall),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(wf_seg7_vertex_platform_between_sliding_platforms_sides, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x07006820 - 0x07006898
const Gfx wf_seg7_dl_platform_between_sliding_platforms[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(wf_seg7_sub_dl_platform_between_sliding_platforms_top),
    gsSPDisplayList(wf_seg7_sub_dl_platform_between_sliding_platforms_sides),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
