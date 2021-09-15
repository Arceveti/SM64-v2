// 0x0700DE68 - 0x0700DE80
static const Lights1 ccm_seg7_lights_0700DE68 = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0700DE80 - 0x0700DE98
static const Lights1 ccm_seg7_lights_0700DE80 = gdSPDefLights1(
    0x4c, 0x4c, 0x4c,
    0x99, 0x99, 0x99, 0x28, 0x28, 0x28
);

// 0x0700DE98 - 0x0700DEB0
static const Lights1 ccm_seg7_lights_0700DE98 = gdSPDefLights1(
    0x5d, 0x5d, 0x5d,
    0xbb, 0xbb, 0xbb, 0x28, 0x28, 0x28
);

// 0x0700DEB0 - 0x0700DEC8
static const Lights1 ccm_seg7_lights_upper_cabin_outside_chimney_warp_void = gdSPDefLights1(
    0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x28, 0x28, 0x28
);

// 0x0700DEC8 - 0x0700DF88
static const Vtx ccm_seg7_vertex_upper_cabin_outside_snow[] = {
    {{{  -355,    123,    357}, 0, {  2592,   -870}, {0x00, 0x7d, 0xee, 0xff}}},
    {{{   433,    123,    357}, 0, {     0,   -870}, {0x00, 0x7d, 0xee, 0xff}}},
    {{{   433,     41,   -195}, 0, {     0,  31<<5}, {0x00, 0x7d, 0xee, 0xff}}},
    {{{  -355,     41,   -195}, 0, {  2592,  31<<5}, {0x00, 0x7d, 0xee, 0xff}}},
    {{{   433,    358,    -51}, 0, {     0,   -372}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   330,    358,     51}, 0, {   304,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   433,    358,    357}, 0, {     0,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   330,    358,    256}, 0, {   304,    656}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   128,    358,    256}, 0, { 31<<5,    656}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{    23,    358,    357}, 0, {  1328,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   128,    358,     51}, 0, { 31<<5,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{    23,    358,    -51}, 0, {  1328,   -372}, {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x0700DF88 - 0x0700E068
static const Vtx ccm_seg7_vertex_0700DF88[] = {
    {{{   351,      0,    275}, 0, { -2482,   2726}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   105,    174,    275}, 0, {     0,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   105,      0,    275}, 0, {     0,   2726}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   351,      0,    275}, 0, { -2482,   2726}, {0x01, 0x01, 0x7e, 0xff}}},
    {{{   349,    174,    273}, 0, { -2466,  31<<5}, {0x01, 0x01, 0x7e, 0xff}}},
    {{{   105,    174,    275}, 0, {     0,  31<<5}, {0x01, 0x01, 0x7e, 0xff}}},
    {{{    23,    205,    -51}, 0, {     0,   2520}, {0x81, 0x00, 0x00, 0xff}}},
    {{{    23,    358,    357}, 0, {127<<5,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{    23,    358,    -51}, 0, {     0,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{    23,    205,    357}, 0, {127<<5,   2520}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   433,    205,    -51}, 0, { -4118,   2520}, {0x00, 0x00, 0x81, 0xff}}},
    {{{    23,    205,    -51}, 0, {     0,   2520}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   433,    358,    -51}, 0, { -4118,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{    23,    358,    -51}, 0, {     0,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
};

// 0x0700E068 - 0x0700E168
static const Vtx ccm_seg7_vertex_0700E068[] = {
    {{{   128,    358,     51}, 0, { 95<<5,   -544}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   128,    154,     51}, 0, { 95<<5,  47<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   330,    154,     51}, 0, { 31<<5,  47<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   433,    205,    357}, 0, { -4118,  -3098}, {0x2c, 0x8a, 0x00, 0xff}}},
    {{{   351,    174,     29}, 0, { -3300,    176}, {0x2c, 0x8a, 0x00, 0xff}}},
    {{{   433,    205,    -51}, 0, { -4118,  31<<5}, {0x2c, 0x8a, 0x00, 0xff}}},
    {{{   433,    205,    357}, 0, { -4118,  -3098}, {0x2b, 0x89, 0x00, 0xff}}},
    {{{   349,    174,    273}, 0, { -3284,  -2264}, {0x2b, 0x89, 0x00, 0xff}}},
    {{{   351,    174,     29}, 0, { -3300,    176}, {0x2b, 0x89, 0x00, 0xff}}},
    {{{   433,    205,    -51}, 0, { -4118,  31<<5}, {0x00, 0x8a, 0xd3, 0xff}}},
    {{{   351,    174,     29}, 0, { -3300,    176}, {0x00, 0x8a, 0xd3, 0xff}}},
    {{{   105,    174,     29}, 0, {  -848,    176}, {0x00, 0x8a, 0xd3, 0xff}}},
    {{{    23,    205,    -51}, 0, {     0,  31<<5}, {0x00, 0x8a, 0xd3, 0xff}}},
    {{{   105,    174,    275}, 0, {  -848,  -2280}, {0xd4, 0x8a, 0x00, 0xff}}},
    {{{    23,    205,    357}, 0, {     0,  -3098}, {0xd4, 0x8a, 0x00, 0xff}}},
    {{{   105,    174,     29}, 0, {  -848,    176}, {0xd4, 0x8a, 0x00, 0xff}}},
};

// 0x0700E168 - 0x0700E268
static const Vtx ccm_seg7_vertex_0700E168[] = {
    {{{    23,    205,    357}, 0, {     0,  -3098}, {0xd4, 0x8a, 0x00, 0xff}}},
    {{{    23,    205,    -51}, 0, {     0,  31<<5}, {0xd4, 0x8a, 0x00, 0xff}}},
    {{{   105,    174,     29}, 0, {  -848,    176}, {0xd4, 0x8a, 0x00, 0xff}}},
    {{{   330,    358,     51}, 0, { 31<<5,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   330,    154,     51}, 0, { 31<<5,  95<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   330,    154,    256}, 0, { 95<<5,  95<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   330,    358,    256}, 0, { 95<<5,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   128,    358,    256}, 0, { 95<<5,   -544}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   330,    154,    256}, 0, { 31<<5,  47<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   128,    154,    256}, 0, { 95<<5,  47<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   128,    358,     51}, 0, { 95<<5,   -544}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   330,    154,     51}, 0, { 31<<5,  47<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   330,    358,     51}, 0, { 31<<5,   -544}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   128,    154,    256}, 0, { 95<<5,  95<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   128,    358,     51}, 0, { 31<<5,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   128,    358,    256}, 0, { 95<<5,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
};

// 0x0700E268 - 0x0700E2C8
static const Vtx ccm_seg7_vertex_0700E268[] = {
    {{{   128,    154,    256}, 0, { 95<<5,  95<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   128,    154,     51}, 0, { 31<<5,  95<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   128,    358,     51}, 0, { 31<<5,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   128,    358,    256}, 0, { 95<<5,   -544}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   330,    358,    256}, 0, { 31<<5,   -544}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   330,    154,    256}, 0, { 31<<5,  47<<5}, {0x00, 0x00, 0x81, 0xff}}},
};

// 0x0700E2C8 - 0x0700E3A8
static const Vtx ccm_seg7_vertex_0700E2C8[] = {
    {{{   351,    174,     29}, 0, { -2482,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   351,      0,     29}, 0, { -2482,   2726}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   105,      0,     29}, 0, {     0,   2726}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   105,    174,     29}, 0, {     0,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   349,    174,    273}, 0, {  2404,  31<<5}, {0x7e, 0x01, 0x01, 0xff}}},
    {{{   351,      0,    275}, 0, {  2420,   2726}, {0x7e, 0x01, 0x01, 0xff}}},
    {{{   351,    174,     29}, 0, {     0,  31<<5}, {0x7e, 0x01, 0x01, 0xff}}},
    {{{   351,      0,    275}, 0, {  2420,   2726}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   351,      0,     29}, 0, {     0,   2726}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   351,    174,     29}, 0, {     0,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   105,      0,     29}, 0, {     0,   2726}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   105,    174,    275}, 0, {  2420,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   105,    174,     29}, 0, {     0,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   105,      0,    275}, 0, {  2420,   2726}, {0x81, 0x00, 0x00, 0xff}}},
};

// 0x0700E3A8 - 0x0700E428
static const Vtx ccm_seg7_vertex_upper_cabin_outside_wood[] = {
    {{{  -334,   -205,   -154}, 0, { -2340,  -6676}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -334,     27,   -154}, 0, {     0,  -6676}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   433,     27,   -154}, 0, {     0,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   433,   -205,   -154}, 0, { -2338,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -334,   -205,    357}, 0, { -2340,  -4120}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -334,    102,    357}, 0, {   720,  -4122}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -334,     27,   -154}, 0, {     0,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -334,   -205,   -154}, 0, { -2340,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
};

// // 0x0700E428 - 0x0700E468
// static const Vtx ccm_seg7_vertex_0700E428[] = {
//     {{{   433,     21,   -192}, 0, {     0,      0}, {0x00, 0x83, 0x12, 0xff}}},
//     {{{   433,    102,    360}, 0, {     0,      0}, {0x00, 0x83, 0x12, 0xff}}},
//     {{{  -355,    102,    360}, 0, {     0,      0}, {0x00, 0x83, 0x12, 0xff}}},
//     {{{  -355,     21,   -192}, 0, {     0,      0}, {0x00, 0x83, 0x12, 0xff}}},
// };

// 0x0700E468 - 0x0700E4A8
static const Vtx ccm_seg7_vertex_upper_cabin_outside_chimney_warp_void[] = {
    {{{   128,    154,     51}, 0, {     0,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   128,    154,    256}, 0, {     0,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   330,    154,     51}, 0, {     0,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   330,    154,    256}, 0, {     0,      0}, {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x0700E4A8 - 0x0700E530
static const Gfx ccm_seg7_dl_upper_cabin_outside_snow[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snow_09008800_snow),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ccm_seg7_lights_0700DE68.l, 1),
    gsSPLight(&ccm_seg7_lights_0700DE68.a, 2),
    gsSPVertex(ccm_seg7_vertex_upper_cabin_outside_snow, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  5,  7,  6, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10,  9,  8, 0x0, 10, 11,  9, 0x0),
    gsSP2Triangles(11, 10,  4, 0x0, 10,  5,  4, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700E530 - 0x0700E668
static const Gfx ccm_seg7_dl_upper_cabin_outside_bricks[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snow_09005000_bricks),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ccm_seg7_vertex_0700DF88, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 11, 13, 12, 0x0),
    gsSPLight(&ccm_seg7_lights_0700DE80.l, 1),
    gsSPLight(&ccm_seg7_lights_0700DE80.a, 2),
    gsSPVertex(ccm_seg7_vertex_0700E068, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 9, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_0700E168, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_0700E268, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPLight(&ccm_seg7_lights_0700DE98.l, 1),
    gsSPLight(&ccm_seg7_lights_0700DE98.a, 2),
    gsSPVertex(ccm_seg7_vertex_0700E2C8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  0, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700E668 - 0x0700E6C0
static const Gfx ccm_seg7_dl_upper_cabin_outside_wood[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snow_09008000_wood_planks),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ccm_seg7_lights_0700DE68.l, 1),
    gsSPLight(&ccm_seg7_lights_0700DE68.a, 2),
    gsSPVertex(ccm_seg7_vertex_upper_cabin_outside_wood, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700E6C0 - 0x0700E708
static const Gfx ccm_seg7_dl_upper_cabin_outside_chimney_warp_void[] = {
    // gsSPVertex(ccm_seg7_vertex_0700E428, 4, 0),
    // gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSPLight(&ccm_seg7_lights_upper_cabin_outside_chimney_warp_void.l, 1),
    gsSPLight(&ccm_seg7_lights_upper_cabin_outside_chimney_warp_void.a, 2),
    gsSPVertex(ccm_seg7_vertex_upper_cabin_outside_chimney_warp_void, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  2,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700E708 - 0x0700E790
const Gfx ccm_seg7_dl_upper_cabin_outside[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ccm_seg7_dl_upper_cabin_outside_snow),
    gsSPDisplayList(ccm_seg7_dl_upper_cabin_outside_bricks),
    gsSPDisplayList(ccm_seg7_dl_upper_cabin_outside_wood),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPDisplayList(ccm_seg7_dl_upper_cabin_outside_chimney_warp_void),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
