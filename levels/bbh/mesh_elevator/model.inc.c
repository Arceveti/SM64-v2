// 0x0701FDB8 - 0x0701FEA8
static const Vtx bbh_seg7_vertex_0701FDB8[] = {
    {{{  -307,      0,    256}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   307,   -102,    256}, 0, {191<<5,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   307,      0,    256}, 0, {191<<5,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   307,      0,    256}, 0, { 31<<5,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   307,   -102,    256}, 0, { 31<<5,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   307,   -102,   -256}, 0, { -4112,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   307,      0,   -256}, 0, { -4112,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   307,      0,   -256}, 0, {191<<5,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   307,   -102,   -256}, 0, {191<<5,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  -307,   -102,   -256}, 0, {     0,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  -307,      0,   -256}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  -307,      0,   -256}, 0, { -4112,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  -307,   -102,   -256}, 0, { -4112,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  -307,   -102,    256}, 0, { 31<<5,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  -307,      0,    256}, 0, { 31<<5,      0}, {0xff, 0xff, 0xff, 0xff}}},
};

// 0x0701FEA8 - 0x0701FF58
static const Vtx bbh_seg7_vertex_0701FEA8[] = {
    {{{   307,   -102,    256}, 0, { -2080,  -3600}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  -307,   -102,    256}, 0, {127<<5,  -3600}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  -307,   -102,   -256}, 0, {127<<5,  47<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  -307,      0,    256}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  -307,   -102,    256}, 0, {     0,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   307,   -102,    256}, 0, {191<<5,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  -307,      0,   -256}, 0, {127<<5,  47<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{  -307,      0,    256}, 0, {127<<5,  -3600}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   307,      0,    256}, 0, { -2080,  -3600}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   307,      0,   -256}, 0, { -2080,  47<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   307,   -102,   -256}, 0, { -2080,  47<<5}, {0xff, 0xff, 0xff, 0xff}}},
};

// 0x0701FF58 - 0x0701FFE8
static const Gfx bbh_seg7_dl_0701FF58[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09000000),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_0701FDB8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_0701FEA8, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP1Triangle(10,  0,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x0701FFE8 - 0x07020058
const Gfx bbh_seg7_dl_mesh_elevator[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_0701FF58),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPEndDisplayList(),
};
