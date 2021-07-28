// 0x0700F220 - 0x0700F238
static const Lights1 wf_seg7_lights_breakable_wall_left = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0700F238 - 0x0700F268
static const Vtx wf_seg7_vertex_breakable_wall_left_top[] = {
    {{{     0,    384,   -378}, 0, { 10188, 255<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -168,    384,   -378}, 0, {  9514, 255<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{     0,    384,    128}, 0, { 10188,  10186}, {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x0700F268 - 0x0700F2C8
static const Vtx wf_seg7_vertex_breakable_wall_left_sides[] = {
    {{{     0,   -383,    128}, 0, {  1080,   3032}, {0x88, 0x00, 0x28, 0xff}}},
    {{{     0,    384,    128}, 0, {  1080,      0}, {0x88, 0x00, 0x28, 0xff}}},
    {{{  -168,    384,   -378}, 0, { -1056,      0}, {0x88, 0x00, 0x28, 0xff}}},
    {{{     0,    384,   -378}, 0, {  1992,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{     0,    384,    128}, 0, {     0,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{     0,   -383,    128}, 0, {     0,   3032}, {0x7f, 0x00, 0x00, 0xff}}},
};

// 0x0700F2C8 - 0x0700F308
static const Gfx wf_seg7_sub_dl_breakable_wall_left_top[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09001000_brown_brick_floor),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&wf_seg7_lights_breakable_wall_left.l, 1),
    gsSPLight(&wf_seg7_lights_breakable_wall_left.a, 2),
    gsSPVertex(wf_seg7_vertex_breakable_wall_left_top, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700F308 - 0x0700F340
static const Gfx wf_seg7_sub_dl_breakable_wall_left_sides[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09000800_brown_brick_wall),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(wf_seg7_vertex_breakable_wall_left_sides, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700F340 - 0x0700F3B8
const Gfx wf_seg7_dl_breakable_wall_left[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(wf_seg7_sub_dl_breakable_wall_left_top),
    gsSPDisplayList(wf_seg7_sub_dl_breakable_wall_left_sides),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
