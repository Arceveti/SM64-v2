// BOB Room Wall Signs

// 0x07033068 - 0x07033080
static const Lights1 inside_castle_seg7_lights_bob_wall_signs = gdSPDefLights1(
    0x5f, 0x5f, 0x5f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07033080 - 0x07033100
static const Vtx inside_castle_seg7_vertex_bob_wall_signs[] = {
    {{{ -3184,    410,   -128}, 0, {     0,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{ -3184,    256,   -128}, 0, {     0,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{ -3184,    256,     26}, 0, { 31<<5,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{ -3184,    410,     26}, 0, { 31<<5,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{ -3184,    410,   -485}, 0, {     0,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{ -3184,    256,   -332}, 0, { 31<<5,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{ -3184,    410,   -332}, 0, { 31<<5,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{ -3184,    256,   -485}, 0, {     0,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
};

// 0x07033100 - 0x07033158
static const Gfx inside_castle_seg7_sub_dl_bob_wall_signs[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, inside_castle_seg7_texture_wall_sign),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&inside_castle_seg7_lights_bob_wall_signs.l, 1),
    gsSPLight(&inside_castle_seg7_lights_bob_wall_signs.a, 2),
    gsSPVertex(inside_castle_seg7_vertex_bob_wall_signs, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x07033158 - 0x070331C8
const Gfx inside_castle_seg7_dl_bob_wall_signs[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(inside_castle_seg7_sub_dl_bob_wall_signs),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
