// 0x0700D780 - 0x0700D798
static const Lights1 wf_seg7_lights_small_bomp_far = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0700D798 - 0x0700D898
static const Vtx wf_seg7_vertex_small_bomp_far_sides_1[] = {
    {{{  -256,    261,     77}, 0, {     0,  -3138}, {0x0c, 0x7e, 0x00, 0xff}}},
    {{{   256,    210,    -96}, 0, {  1194,      0}, {0x0c, 0x7e, 0x00, 0xff}}},
    {{{  -256,    261,    -77}, 0, {  1194,  -3138}, {0x0c, 0x7e, 0x00, 0xff}}},
    {{{   256,    210,     96}, 0, {     0,      0}, {0x0c, 0x7e, 0x00, 0xff}}},
    {{{  -256,    210,   -128}, 0, {  2522,    -32}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   256,      5,   -128}, 0, {     0,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -256,      5,   -128}, 0, {  2520,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -256,    210,   -128}, 0, {  2522,    -32}, {0x07, 0x13, 0x83, 0xff}}},
    {{{   256,    210,    -96}, 0, {   464,    -32}, {0x07, 0x13, 0x83, 0xff}}},
    {{{   256,      5,   -128}, 0, {     0,  31<<5}, {0x07, 0x13, 0x83, 0xff}}},
    {{{  -256,    261,    -77}, 0, {127<<5,    416}, {0x05, 0x59, 0xa7, 0xff}}},
    {{{   256,    210,    -96}, 0, { 15<<5,  31<<5}, {0x05, 0x59, 0xa7, 0xff}}},
    {{{  -256,    210,   -128}, 0, {127<<5,  31<<5}, {0x05, 0x59, 0xa7, 0xff}}},
    {{{  -256,    210,    128}, 0, { -3104,  31<<5}, {0x05, 0x5a, 0x58, 0xff}}},
    {{{   256,    210,     96}, 0, { 15<<5,  31<<5}, {0x05, 0x5a, 0x58, 0xff}}},
    {{{  -256,    261,     77}, 0, { -3104,    416}, {0x05, 0x5a, 0x58, 0xff}}},
};

// 0x0700D898 - 0x0700D8F8
static const Vtx wf_seg7_vertex_small_bomp_far_sides_2[] = {
    {{{  -256,      5,    128}, 0, {     0,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   256,      5,    128}, 0, { 63<<5,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -256,    210,    128}, 0, {     0,    182}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   256,      5,    128}, 0, { 63<<5,  31<<5}, {0x07, 0x13, 0x7d, 0xff}}},
    {{{   256,    210,     96}, 0, { 63<<5,    160}, {0x07, 0x13, 0x7d, 0xff}}},
    {{{  -256,    210,    128}, 0, {     0,    182}, {0x07, 0x13, 0x7d, 0xff}}},
};

// 0x0700D8F8 - 0x0700D938
static const Vtx wf_seg7_vertex_small_bomp_far_face[] = {
    {{{   256,      5,   -128}, 0, { 31<<5,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   256,    210,     96}, 0, {    96,    176}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   256,      5,    128}, 0, {     0,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   256,    210,    -96}, 0, {   864,    176}, {0x7f, 0x00, 0x00, 0xff}}},
};

// 0x0700D938 - 0x0700D9B8
static const Gfx wf_seg7_sub_dl_small_bomp_far_sides[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09008000_large_pink_rocks),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&wf_seg7_lights_small_bomp_far.l, 1),
    gsSPLight(&wf_seg7_lights_small_bomp_far.a, 2),
    gsSPVertex(wf_seg7_vertex_small_bomp_far_sides_1, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(wf_seg7_vertex_small_bomp_far_sides_2, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700D9B8 - 0x0700D9F0
static const Gfx wf_seg7_sub_dl_small_bomp_far_face[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, wf_seg7_texture_bomp_face),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(wf_seg7_vertex_small_bomp_far_face, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700D9F0 - 0x0700DA68
const Gfx wf_seg7_dl_small_bomp_far[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(wf_seg7_sub_dl_small_bomp_far_sides),
    gsSPDisplayList(wf_seg7_sub_dl_small_bomp_far_face),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
