// 0x0700EA28 - 0x0700EA40
static const Lights1 wf_seg7_lights_sliding_platform = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0700EA40 - 0x0700EA80
static const Vtx wf_seg7_vertex_sliding_platform_sides[] = {
    {{{   256,      0,    256}, 0, ST_B(     0,     -7), {0x7f, 0x00, 0x00, 0xff}}},
    {{{   256,    -51,    256}, 0, ST_B(     0,      0), {0x7f, 0x00, 0x00, 0xff}}},
    {{{   256,    -51,   -256}, 0, ST_B(    64,      0), {0x7f, 0x00, 0x00, 0xff}}},
    {{{   256,      0,   -256}, 0, ST_B(    64,     -7), {0x7f, 0x00, 0x00, 0xff}}},
};

// 0x0700EA80 - 0x0700EAC0
static const Vtx wf_seg7_vertex_sliding_platform_top[] = {
    {{{   256,      0,    256}, 0, ST_B(     0,     32), {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -256,      0,   -256}, 0, ST_B(    64,    -32), {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -256,      0,    256}, 0, ST_B(     0,    -32), {0x00, 0x7f, 0x00, 0xff}}},
    {{{   256,      0,   -256}, 0, ST_B(    64,     32), {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x0700EAC0 - 0x0700EB08
static const Gfx wf_seg7_sub_dl_sliding_platform_sides[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09000800_brown_brick_wall),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&wf_seg7_lights_sliding_platform.l, 1),
    gsSPLight(&wf_seg7_lights_sliding_platform.a, 2),
    gsSPVertex(wf_seg7_vertex_sliding_platform_sides, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700EB08 - 0x0700EB40
static const Gfx wf_seg7_sub_dl_sliding_platform_top[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09001000_brown_brick_floor),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(wf_seg7_vertex_sliding_platform_top, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700EB40 - 0x0700EBB8
const Gfx wf_seg7_dl_sliding_platform[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(wf_seg7_sub_dl_sliding_platform_sides),
    gsSPDisplayList(wf_seg7_sub_dl_sliding_platform_top),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
