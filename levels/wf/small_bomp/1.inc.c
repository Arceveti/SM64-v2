// 0x0700D370 - 0x0700D388
static const Lights1 wf_seg7_lights_small_bomp_near = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0700D388 - 0x0700D488
static const Vtx wf_seg7_vertex_small_bomp_near_sides_1[] = {
    {{{  -256,    261,     77}, 0, {     0,  -3138}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   136,    261,    -77}, 0, {  1194,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -256,    261,    -77}, 0, {  1194,  -3138}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   136,    261,    -77}, 0, {   582,    -72}, {0x30, 0x75, 0x00, 0xff}}},
    {{{   136,    261,     77}, 0, {  -644,    -72}, {0x30, 0x75, 0x00, 0xff}}},
    {{{   256,    210,     96}, 0, {  -800,  31<<5}, {0x30, 0x75, 0x00, 0xff}}},
    {{{   256,    210,    -96}, 0, { 23<<5,  31<<5}, {0x30, 0x75, 0x00, 0xff}}},
    {{{  -256,    210,   -128}, 0, { 24<<5,   -144}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   256,      5,   -128}, 0, { -2080,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -256,      5,   -128}, 0, { 24<<5,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   195,    210,   -128}, 0, { -1720,   -144}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -256,    261,    -77}, 0, {127<<5,    416}, {0x00, 0x59, 0xa7, 0xff}}},
    {{{   195,    210,   -128}, 0, { 15<<5,  31<<5}, {0x00, 0x59, 0xa7, 0xff}}},
    {{{  -256,    210,   -128}, 0, {127<<5,  31<<5}, {0x00, 0x59, 0xa7, 0xff}}},
    {{{   136,    261,    -77}, 0, {   944,    416}, {0x00, 0x59, 0xa7, 0xff}}},
    {{{   136,    261,     77}, 0, {     0,      0}, {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x0700D488 - 0x0700D568
static const Vtx wf_seg7_vertex_small_bomp_near_sides_2[] = {
    {{{   195,    210,    128}, 0, { 15<<5,  31<<5}, {0x00, 0x5a, 0x58, 0xff}}},
    {{{   136,    261,     77}, 0, {     8,    412}, {0x00, 0x5a, 0x58, 0xff}}},
    {{{  -256,    261,     77}, 0, { -3104,    412}, {0x00, 0x5a, 0x58, 0xff}}},
    {{{  -256,    210,    128}, 0, { -3104,  31<<5}, {0x00, 0x5a, 0x58, 0xff}}},
    {{{  -256,      5,    128}, 0, { -2080,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   256,      5,    128}, 0, { 24<<5,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   195,    210,    128}, 0, {   408,   -144}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -256,    210,    128}, 0, { -2074,   -144}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   256,    210,     96}, 0, { 31<<5,  31<<5}, {0x20, 0x68, 0x41, 0xff}}},
    {{{   136,    261,     77}, 0, { 31<<5,   -352}, {0x20, 0x68, 0x41, 0xff}}},
    {{{   195,    210,    128}, 0, {   528,    452}, {0x20, 0x68, 0x41, 0xff}}},
    {{{   256,      5,   -128}, 0, {   544,   1116}, {0x38, 0x11, 0x90, 0xff}}},
    {{{   195,    210,   -128}, 0, {   544,    -72}, {0x38, 0x11, 0x90, 0xff}}},
    {{{   256,    210,    -96}, 0, {   160,     32}, {0x38, 0x11, 0x90, 0xff}}},
};

// 0x0700D568 - 0x0700D5C8
static const Vtx wf_seg7_vertex_small_bomp_near_sides_3[] = {
    {{{   256,    210,     96}, 0, {   768,   -144}, {0x38, 0x11, 0x70, 0xff}}},
    {{{   195,    210,    128}, 0, {   368,   -112}, {0x38, 0x11, 0x70, 0xff}}},
    {{{   256,      5,    128}, 0, {   768,   1008}, {0x38, 0x11, 0x70, 0xff}}},
    {{{   195,    210,   -128}, 0, {   364,  31<<5}, {0x20, 0x67, 0xbf, 0xff}}},
    {{{   136,    261,    -77}, 0, {   528,    496}, {0x20, 0x67, 0xbf, 0xff}}},
    {{{   256,    210,    -96}, 0, {     0,  31<<5}, {0x20, 0x67, 0xbf, 0xff}}},
};

// 0x0700D5C8 - 0x0700D608
static const Vtx wf_seg7_vertex_small_bomp_near_face[] = {
    {{{   256,      5,   -128}, 0, {  1118,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   256,    210,     96}, 0, {     0,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   256,      5,    128}, 0, {  -160,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   256,    210,    -96}, 0, {   960,      0}, {0x7f, 0x00, 0x00, 0xff}}},
};

// 0x0700D608 - 0x0700D6D0
static const Gfx wf_seg7_sub_dl_small_bomp_near_sides[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09008000_large_pink_rocks),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&wf_seg7_lights_small_bomp_near.l, 1),
    gsSPLight(&wf_seg7_lights_small_bomp_near.a, 2),
    gsSPVertex(wf_seg7_vertex_small_bomp_near_sides_1, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0,  0, 15,  1, 0x0),
    gsSPVertex(wf_seg7_vertex_small_bomp_near_sides_2, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(wf_seg7_vertex_small_bomp_near_sides_3, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700D6D0 - 0x0700D708
static const Gfx wf_seg7_sub_dl_small_bomp_near_face[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, wf_seg7_texture_bomp_face),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(wf_seg7_vertex_small_bomp_near_face, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700D708 - 0x0700D780
const Gfx wf_seg7_dl_small_bomp_near[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(wf_seg7_sub_dl_small_bomp_near_sides),
    gsSPDisplayList(wf_seg7_sub_dl_small_bomp_near_face),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
