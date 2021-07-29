// Moat Grills

// 0x0700BAB8 - 0x0700BB38
static const Vtx castle_grounds_seg7_vertex_moat_grills[] = {
    {{{ -3533,  -1331,  -6070}, 0, { 31<<5,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{ -4045,  -1331,  -5558}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{ -3533,  -1331,  -5558}, 0, {     0,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{ -4045,  -1331,  -6070}, 0, { 31<<5,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{ -3226,   -563,  -2179}, 0, { 31<<5,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{ -3533,   -563,  -2179}, 0, { 31<<5,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{ -3226,   -563,  -1872}, 0, {     0,  31<<5}, {0xff, 0xff, 0xff, 0xff}}},
    {{{ -3533,   -563,  -1872}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}},
};

// 0x0700BB38 - 0x0700BB80
static const Gfx castle_grounds_seg7_sub_dl_moat_grills[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, outside_09005800_mesh),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(castle_grounds_seg7_vertex_moat_grills, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700BB80 - 0x0700BBF0
const Gfx castle_grounds_seg7_dl_moat_grills[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(castle_grounds_seg7_sub_dl_moat_grills),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
