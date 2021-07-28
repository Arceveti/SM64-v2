// 0x0700DA68 - 0x0700DA80
static const Lights1 wf_seg7_lights_large_bomp = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0700DA80 - 0x0700DB70
static const Vtx wf_seg7_vertex_large_bomp_sides_1[] = {
    {{{  -256,      5,    256}, 0, { -2080,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   256,      5,    256}, 0, { 24<<5,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   192,    210,    256}, 0, {   408,   -144}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   256,      5,   -256}, 0, {   544,   1116}, {0x57, 0x1b, 0xa9, 0xff}}},
    {{{   192,    210,   -256}, 0, {   544,    -72}, {0x57, 0x1b, 0xa9, 0xff}}},
    {{{   256,    210,   -192}, 0, {   160,     32}, {0x57, 0x1b, 0xa9, 0xff}}},
    {{{   192,    210,   -256}, 0, {   364,  31<<5}, {0x24, 0x74, 0xdc, 0xff}}},
    {{{   136,    261,   -156}, 0, {   528,    496}, {0x24, 0x74, 0xdc, 0xff}}},
    {{{   256,    210,   -192}, 0, {     0,  31<<5}, {0x24, 0x74, 0xdc, 0xff}}},
    {{{   256,    210,    189}, 0, { 24<<5,   -144}, {0x57, 0x1b, 0x57, 0xff}}},
    {{{   192,    210,    256}, 0, {   368,   -112}, {0x57, 0x1b, 0x57, 0xff}}},
    {{{   256,      5,    256}, 0, { 24<<5,   1008}, {0x57, 0x1b, 0x57, 0xff}}},
    {{{   256,    210,    189}, 0, { 31<<5,  31<<5}, {0x24, 0x73, 0x24, 0xff}}},
    {{{   136,    261,    151}, 0, { 31<<5,   -352}, {0x24, 0x73, 0x24, 0xff}}},
    {{{   192,    210,    256}, 0, {   520,    452}, {0x24, 0x73, 0x24, 0xff}}},
};

// 0x0700DB70 - 0x0700DC60
static const Vtx wf_seg7_vertex_large_bomp_sides_2[] = {
    {{{  -256,    261,   -156}, 0, {127<<5,    416}, {0x00, 0x71, 0xc8, 0xff}}},
    {{{   136,    261,   -156}, 0, {   944,    416}, {0x00, 0x71, 0xc8, 0xff}}},
    {{{   192,    210,   -256}, 0, { 15<<5,  31<<5}, {0x00, 0x71, 0xc8, 0xff}}},
    {{{  -256,      5,    256}, 0, { -2080,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   192,    210,    256}, 0, {   408,   -144}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -256,    210,    256}, 0, { -2080,   -144}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -256,    210,    256}, 0, { -3104,  31<<5}, {0x00, 0x71, 0x38, 0xff}}},
    {{{   192,    210,    256}, 0, { 15<<5,  31<<5}, {0x00, 0x71, 0x38, 0xff}}},
    {{{  -256,    261,    151}, 0, { -3104,    412}, {0x00, 0x71, 0x38, 0xff}}},
    {{{   136,    261,    151}, 0, {     8,    412}, {0x00, 0x71, 0x38, 0xff}}},
    {{{  -256,    261,    151}, 0, {     0,  -3138}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   136,    261,   -156}, 0, {  1194,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -256,    261,   -156}, 0, {  1194,  -3138}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   136,    261,    151}, 0, {     0,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -256,    210,   -256}, 0, {127<<5,  31<<5}, {0x00, 0x71, 0xc8, 0xff}}},
};

// 0x0700DC60 - 0x0700DCE0
static const Vtx wf_seg7_vertex_large_bomp_sides_3[] = {
    {{{  -256,    210,   -256}, 0, {   768,   -144}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   256,      5,   -256}, 0, { -2080,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -256,      5,   -256}, 0, {   768,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   192,    210,   -256}, 0, { -1720,   -144}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   136,    261,   -156}, 0, {   582,    -72}, {0x30, 0x75, 0x00, 0xff}}},
    {{{   256,    210,    189}, 0, {  -796,  31<<5}, {0x30, 0x75, 0x00, 0xff}}},
    {{{   256,    210,   -192}, 0, { 23<<5,  31<<5}, {0x30, 0x75, 0x00, 0xff}}},
    {{{   136,    261,    151}, 0, {  -644,    -72}, {0x30, 0x75, 0x00, 0xff}}},
};

// 0x0700DCE0 - 0x0700DD20
static const Vtx wf_seg7_vertex_large_bomp_face[] = {
    {{{   256,      5,   -256}, 0, {  1118,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   256,    210,   -192}, 0, { 30<<5,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   256,    210,    189}, 0, {     0,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   256,      5,    256}, 0, {  -160,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
};

// 0x0700DD20 - 0x0700DDE8
static const Gfx wf_seg7_sub_dl_large_bomp_sides[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09008000_large_pink_rocks),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&wf_seg7_lights_large_bomp.l, 1),
    gsSPLight(&wf_seg7_lights_large_bomp.a, 2),
    gsSPVertex(wf_seg7_vertex_large_bomp_sides_1, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(wf_seg7_vertex_large_bomp_sides_2, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  7,  9,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(wf_seg7_vertex_large_bomp_sides_3, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700DDE8 - 0x0700DE20
static const Gfx wf_seg7_sub_dl_large_bomp_face[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, wf_seg7_texture_bomp_face),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(wf_seg7_vertex_large_bomp_face, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700DE20 - 0x0700DE98
const Gfx wf_seg7_dl_large_bomp[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(wf_seg7_sub_dl_large_bomp_sides),
    gsSPDisplayList(wf_seg7_sub_dl_large_bomp_face),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
