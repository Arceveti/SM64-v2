// CCM Wall Sign

// 0x0703A768 - 0x0703A780
static const Lights1 inside_castle_seg7_lights_ccm_wall_sign = gdSPDefLights1(
    0x5f, 0x5f, 0x5f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0703A780 - 0x0703A7C0
static const Vtx inside_castle_seg7_vertex_ccm_wall_sign[] = {
    {{{ -2354,   -205,  -3001}, 0, { 31<<5,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{ -2201,   -205,  -3001}, 0, {     0,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{ -2201,   -357,  -3001}, 0, {     0,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{ -2354,   -357,  -3001}, 0, { 31<<5,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
};

// 0x0703A7C0 - 0x0703A808
static const Gfx inside_castle_seg7_sub_dl_wall_sign[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_castle_seg7_texture_wall_sign),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&inside_castle_seg7_lights_ccm_wall_sign.l, 1),
    gsSPLight(&inside_castle_seg7_lights_ccm_wall_sign.a, 2),
    gsSPVertex(inside_castle_seg7_vertex_ccm_wall_sign, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0703A808 - 0x0703A878
const Gfx inside_castle_seg7_dl_ccm_wall_sign[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(inside_castle_seg7_sub_dl_wall_sign),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
