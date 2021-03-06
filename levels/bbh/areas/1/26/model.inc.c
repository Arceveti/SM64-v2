// 0x07015408 - 0x07015508
static const Vtx bbh_seg7_vertex_07015408[] = {
    {{{   358,   1434,  -1526}, 0, { 31<<5,      0}, {0xff, 0x00, 0x00, 0x9a}}},
    {{{   -51,   1024,  -1526}, 0, {     0,  31<<5}, {0xff, 0x00, 0x00, 0x9a}}},
    {{{   358,   1024,  -1526}, 0, { 31<<5,  31<<5}, {0xff, 0x00, 0x00, 0x9a}}},
    {{{  -410,    563,  -1520}, 0, { 31<<5,      0}, {0xff, 0x00, 0x00, 0x9a}}},
    {{{  -700,    563,  -1229}, 0, {     0,      0}, {0xff, 0x00, 0x00, 0x9a}}},
    {{{  -700,    358,  -1229}, 0, {     0,  15<<5}, {0xff, 0x00, 0x00, 0x9a}}},
    {{{  -410,    358,  -1520}, 0, { 31<<5,  15<<5}, {0xff, 0x00, 0x00, 0x9a}}},
    {{{  -600,    211,  -1126}, 0, {     0,  31<<5}, {0xff, 0x00, 0x00, 0x9a}}},
    {{{  -310,    211,  -1419}, 0, { 31<<5,  31<<5}, {0xff, 0x00, 0x00, 0x9a}}},
    {{{   358,    614,  -1526}, 0, { 31<<5,      0}, {0xff, 0x00, 0x00, 0x9a}}},
    {{{   -51,    205,  -1526}, 0, {     0,  31<<5}, {0xff, 0x00, 0x00, 0x9a}}},
    {{{   358,    205,  -1526}, 0, { 31<<5,  31<<5}, {0xff, 0x00, 0x00, 0x9a}}},
    {{{   -51,    614,  -1526}, 0, {     0,      0}, {0xff, 0x00, 0x00, 0x9a}}},
    {{{  1014,    205,   -614}, 0, { 31<<5,  31<<5}, {0xff, 0x00, 0x00, 0x9a}}},
    {{{  1014,    614,  -1024}, 0, {     0,      0}, {0xff, 0x00, 0x00, 0x9a}}},
    {{{  1014,    205,  -1024}, 0, {     0,  31<<5}, {0xff, 0x00, 0x00, 0x9a}}},
};

// 0x07015508 - 0x070155E8
static const Vtx bbh_seg7_vertex_07015508[] = {
    {{{   358,   1434,  -1526}, 0, { 31<<5,      0}, {0xff, 0x00, 0x00, 0x9a}}},
    {{{   -51,   1434,  -1526}, 0, {     0,      0}, {0xff, 0x00, 0x00, 0x9a}}},
    {{{   -51,   1024,  -1526}, 0, {     0,  31<<5}, {0xff, 0x00, 0x00, 0x9a}}},
    {{{  -707,    205,  -1024}, 0, { 31<<5,  31<<5}, {0xff, 0x00, 0x00, 0x9a}}},
    {{{  -707,    614,   -614}, 0, {     0,      0}, {0xff, 0x00, 0x00, 0x9a}}},
    {{{  -707,    205,   -614}, 0, {     0,  31<<5}, {0xff, 0x00, 0x00, 0x9a}}},
    {{{  -707,    614,  -1024}, 0, { 31<<5,      0}, {0xff, 0x00, 0x00, 0x9a}}},
    {{{  -707,   1024,  -1024}, 0, { 31<<5,  31<<5}, {0xff, 0x00, 0x00, 0x9a}}},
    {{{  -707,   1434,  -1024}, 0, { 31<<5,      0}, {0xff, 0x00, 0x00, 0x9a}}},
    {{{  -707,   1434,   -614}, 0, {     0,      0}, {0xff, 0x00, 0x00, 0x9a}}},
    {{{  -707,   1024,   -614}, 0, {     0,  31<<5}, {0xff, 0x00, 0x00, 0x9a}}},
    {{{  1014,    205,   -614}, 0, { 31<<5,  31<<5}, {0xff, 0x00, 0x00, 0x9a}}},
    {{{  1014,    614,   -614}, 0, { 31<<5,      0}, {0xff, 0x00, 0x00, 0x9a}}},
    {{{  1014,    614,  -1024}, 0, {     0,      0}, {0xff, 0x00, 0x00, 0x9a}}},
};

// 0x070155E8 - 0x07015628
static const Vtx bbh_seg7_vertex_070155E8[] = {
    {{{  1014,   1024,   -614}, 0, { 31<<5,  31<<5}, {0xff, 0x00, 0x00, 0x9a}}},
    {{{  1014,   1434,   -614}, 0, { 31<<5,      0}, {0xff, 0x00, 0x00, 0x9a}}},
    {{{  1014,   1434,  -1024}, 0, {     0,      0}, {0xff, 0x00, 0x00, 0x9a}}},
    {{{  1014,   1024,  -1024}, 0, {     0,  31<<5}, {0xff, 0x00, 0x00, 0x9a}}},
};

// 0x07015628 - 0x070156E0
static const Gfx bbh_seg7_dl_07015628[] = {
    gsDPSetTextureImage(G_IM_FMT_IA, G_IM_SIZ_16b, 1, spooky_0900A800_light_radial),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_07015408, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  5,  7,  8, 0x0),
    gsSP2Triangles( 5,  8,  6, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 12, 10, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(bbh_seg7_vertex_07015508, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(bbh_seg7_vertex_070155E8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x070156E0 - 0x07015750
const Gfx bbh_seg7_dl_mesh_room_lights_glow[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_IA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_07015628),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
