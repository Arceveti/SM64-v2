// Aquarium Wall Sign

// 0x070382B0 - 0x070382C8
static const Lights1 inside_castle_seg7_lights_aquarium_wall_sign = gdSPDefLights1(
    0x5f, 0x5f, 0x5f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x070382C8 - 0x07038308
static const Vtx inside_castle_seg7_vertex_aquarium_wall_sign[] = {
    {{{  1616,    512,  -1088}, 0, {     0,      0}, {0x59, 0x00, 0x5a, 0xff}}},
    {{{  1616,    358,  -1088}, 0, {     0,  31<<5}, {0x59, 0x00, 0x5a, 0xff}}},
    {{{  1725,    358,  -1197}, 0, { 31<<5,  31<<5}, {0x59, 0x00, 0x5a, 0xff}}},
    {{{  1725,    512,  -1197}, 0, { 31<<5,      0}, {0x59, 0x00, 0x5a, 0xff}}},
};

// 0x07038308 - 0x07038350
static const Gfx inside_castle_seg7_dl_aquarium_wall_sign_model[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_castle_seg7_texture_wall_sign),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&inside_castle_seg7_lights_aquarium_wall_sign.l, 1),
    gsSPLight(&inside_castle_seg7_lights_aquarium_wall_sign.a, 2),
    gsSPVertex(inside_castle_seg7_vertex_aquarium_wall_sign, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x07038350 - 0x070383C0
const Gfx dl_castle_aquarium_wall_sign[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(inside_castle_seg7_dl_aquarium_wall_sign_model),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
