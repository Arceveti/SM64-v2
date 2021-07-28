// 0x0700F758 - 0x0700F770
static const Lights1 wf_seg7_lights_tower_door = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0700F770 - 0x0700F7B0
static const Vtx wf_seg7_vertex_tower_door[] = {
    {{{     0,      0,   -108}, 0, {   186,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{     0,      0,    108}, 0, {   720,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{     0,    205,    108}, 0, {   720,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{     0,    205,   -108}, 0, {   186,      0}, {0x81, 0x00, 0x00, 0xff}}},
};

// 0x0700F7B0 - 0x0700F7F8
static const Gfx wf_seg7_sub_dl_tower_door[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09007000_beige_bricks),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&wf_seg7_lights_tower_door.l, 1),
    gsSPLight(&wf_seg7_lights_tower_door.a, 2),
    gsSPVertex(wf_seg7_vertex_tower_door, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700F7F8 - 0x0700F868
const Gfx wf_seg7_dl_tower_door[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(wf_seg7_sub_dl_tower_door),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
