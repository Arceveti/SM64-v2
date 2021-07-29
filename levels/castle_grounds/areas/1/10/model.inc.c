// 0x0700C2A0 - 0x0700C2E0
static const Vtx castle_grounds_seg7_vertex_red_carpet_outside[] = {
    {{{   256,    803,  -3206}, 0, { 31<<5,    336}, {0xc4, 0xc4, 0xd0, 0xff}}},
    {{{  -256,    803,  -3206}, 0, {     0,    336}, {0xc4, 0xc4, 0xd0, 0xff}}},
    {{{  -256,    803,  -2844}, 0, {     0,    970}, {0xc4, 0xc4, 0xd0, 0xff}}},
    {{{   256,    803,  -2844}, 0, { 31<<5,    960}, {0xc4, 0xc4, 0xd0, 0xff}}},
};

// 0x0700C2E0 - 0x0700C3A0
static const Vtx castle_grounds_seg7_vertex_door_frame[] = {
    {{{   205,   1110,  -3104}, 0, { -4534,      0}, {0x9c, 0x9c, 0xae, 0xff}}},
    {{{   154,    803,  -3104}, 0, {  1596,  31<<5}, {0x9c, 0x9c, 0xae, 0xff}}},
    {{{   205,    803,  -3104}, 0, {  1596,      0}, {0x9c, 0x9c, 0xae, 0xff}}},
    {{{   154,   1059,  -3104}, 0, { -3512,  31<<5}, {0x9c, 0x9c, 0xae, 0xff}}},
    {{{   205,   1110,  -3104}, 0, {  6610,      0}, {0x9c, 0x9c, 0xae, 0xff}}},
    {{{  -154,   1059,  -3104}, 0, {  -544,  31<<5}, {0x9c, 0x9c, 0xae, 0xff}}},
    {{{   154,   1059,  -3104}, 0, {  5588,  31<<5}, {0x9c, 0x9c, 0xae, 0xff}}},
    {{{  -205,   1110,  -3104}, 0, { -1564,      0}, {0x9c, 0x9c, 0xae, 0xff}}},
    {{{  -154,   1059,  -3104}, 0, {  4564,  31<<5}, {0x9c, 0x9c, 0xae, 0xff}}},
    {{{  -205,    803,  -3104}, 0, {  -544,      0}, {0x9c, 0x9c, 0xae, 0xff}}},
    {{{  -154,    803,  -3104}, 0, {  -544,  31<<5}, {0x9c, 0x9c, 0xae, 0xff}}},
    {{{  -205,   1110,  -3104}, 0, {  5586,      0}, {0x9c, 0x9c, 0xae, 0xff}}},
};

// 0x0700C3A0 - 0x0700C3D8
static const Gfx castle_grounds_seg7_dl_red_carpet_outside[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, outside_09006000_red_carpet),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(castle_grounds_seg7_vertex_red_carpet_outside, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700C3D8 - 0x0700C430
static const Gfx castle_grounds_seg7_dl_door_frame[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, outside_09003000_stars_pattern),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(castle_grounds_seg7_vertex_door_frame, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700C430 - 0x0700C4C0
const Gfx castle_grounds_seg7_dl_door_frame_and_carpet_outside[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(castle_grounds_seg7_dl_red_carpet_outside),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(castle_grounds_seg7_dl_door_frame),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
