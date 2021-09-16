// 0x0701FDB8 - 0x0701FEA8
static const Vtx bbh_seg7_vertex_mesh_elevator[] = {
    {{{  -307,      0,    256}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}}, //  0
    {{{   307,   -102,    256}, 0, {191<<5,  31<<5}, {0xff, 0xff, 0xff, 0xff}}}, //  1
    {{{   307,      0,    256}, 0, {191<<5,      0}, {0xff, 0xff, 0xff, 0xff}}}, //  2
    {{{   307,      0,    256}, 0, { 31<<5,      0}, {0xff, 0xff, 0xff, 0xff}}}, //  3
    {{{   307,   -102,    256}, 0, { 31<<5,  31<<5}, {0xff, 0xff, 0xff, 0xff}}}, //  4
    {{{   307,   -102,   -256}, 0, { -4112,  31<<5}, {0xff, 0xff, 0xff, 0xff}}}, //  5
    {{{   307,      0,   -256}, 0, { -4112,      0}, {0xff, 0xff, 0xff, 0xff}}}, //  6
    {{{   307,      0,   -256}, 0, {191<<5,      0}, {0xff, 0xff, 0xff, 0xff}}}, //  7
    {{{   307,   -102,   -256}, 0, {191<<5,  31<<5}, {0xff, 0xff, 0xff, 0xff}}}, //  8
    {{{  -307,   -102,   -256}, 0, {     0,  31<<5}, {0xff, 0xff, 0xff, 0xff}}}, //  9
    {{{  -307,      0,   -256}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}}, // 10
    {{{  -307,      0,   -256}, 0, { -4112,      0}, {0xff, 0xff, 0xff, 0xff}}}, // 11
    {{{  -307,   -102,   -256}, 0, { -4112,  31<<5}, {0xff, 0xff, 0xff, 0xff}}}, // 12
    {{{  -307,   -102,    256}, 0, { 31<<5,  31<<5}, {0xff, 0xff, 0xff, 0xff}}}, // 13
    {{{  -307,      0,    256}, 0, { 31<<5,      0}, {0xff, 0xff, 0xff, 0xff}}}, // 14
    {{{   307,   -102,    256}, 0, { -2080,  -3600}, {0xff, 0xff, 0xff, 0xff}}}, // 15
    {{{  -307,   -102,    256}, 0, {127<<5,  -3600}, {0xff, 0xff, 0xff, 0xff}}}, // 16
    {{{  -307,   -102,   -256}, 0, {127<<5,  47<<5}, {0xff, 0xff, 0xff, 0xff}}}, // 17
    {{{  -307,   -102,    256}, 0, {     0,  31<<5}, {0xff, 0xff, 0xff, 0xff}}}, // 18
    {{{  -307,      0,   -256}, 0, {127<<5,  47<<5}, {0xff, 0xff, 0xff, 0xff}}}, // 19
    {{{  -307,      0,    256}, 0, {127<<5,  -3600}, {0xff, 0xff, 0xff, 0xff}}}, // 20
    {{{   307,      0,    256}, 0, { -2080,  -3600}, {0xff, 0xff, 0xff, 0xff}}}, // 21
    {{{   307,      0,   -256}, 0, { -2080,  47<<5}, {0xff, 0xff, 0xff, 0xff}}}, // 22
    {{{   307,   -102,   -256}, 0, { -2080,  47<<5}, {0xff, 0xff, 0xff, 0xff}}}, // 23
};

// 0x0701FF58 - 0x0701FFE8
static const Gfx bbh_seg7_sub_dl_mesh_elevator[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09000000_mesh),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_mesh_elevator, 24, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0, 15, 16, 17, 0x0),
    gsSP2Triangles( 0, 18,  1, 0x0, 19, 20, 21, 0x0),
    gsSP2Triangles(19, 21, 22, 0x0, 23, 15, 17, 0x0),
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
    gsSPDisplayList(bbh_seg7_sub_dl_mesh_elevator),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPEndDisplayList(),
};
