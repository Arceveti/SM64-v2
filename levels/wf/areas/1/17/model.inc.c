// 0x0700BB18 - 0x0700BB30
static const Lights1 wf_seg7_lights_rotating_grass_platform = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0700BB30 - 0x0700BC20
static const Vtx wf_seg7_vertex_rotating_grass_platform_sides_1[] = {
    {{{   443,      0,   -256}, 0, { 32<<5,      0}, {0x38, 0x90, 0xf1, 0xff}}},
    {{{   512,      0,      0}, 0, {     0,      0}, {0x38, 0x90, 0xf1, 0xff}}},
    {{{     0,   -256,      0}, 0, {   496,  31<<5}, {0x38, 0x90, 0xf1, 0xff}}},
    {{{  -256,      0,   -443}, 0, {   -64,      0}, {0xd7, 0x90, 0xd7, 0xff}}},
    {{{     0,   -256,      0}, 0, {   464,  31<<5}, {0xd7, 0x90, 0xd7, 0xff}}},
    {{{  -443,      0,   -256}, 0, { 31<<5,      0}, {0xd7, 0x90, 0xd7, 0xff}}},
    {{{  -256,      0,   -443}, 0, { 31<<5,      0}, {0xf1, 0x90, 0xc8, 0xff}}},
    {{{     0,      0,   -512}, 0, {   -64,      0}, {0xf1, 0x90, 0xc8, 0xff}}},
    {{{     0,   -256,      0}, 0, {   464,  31<<5}, {0xf1, 0x90, 0xc8, 0xff}}},
    {{{     0,      0,   -512}, 0, { 32<<5,      0}, {0x0f, 0x90, 0xc8, 0xff}}},
    {{{   256,      0,   -443}, 0, {     0,      0}, {0x0f, 0x90, 0xc8, 0xff}}},
    {{{     0,   -256,      0}, 0, {   496,  31<<5}, {0x0f, 0x90, 0xc8, 0xff}}},
    {{{   256,      0,   -443}, 0, { 32<<5,      0}, {0x29, 0x90, 0xd7, 0xff}}},
    {{{   443,      0,   -256}, 0, {     0,      0}, {0x29, 0x90, 0xd7, 0xff}}},
    {{{     0,   -256,      0}, 0, {   496,  31<<5}, {0x29, 0x90, 0xd7, 0xff}}},
};

// 0x0700BC20 - 0x0700BD10
static const Vtx wf_seg7_vertex_rotating_grass_platform_sides_2[] = {
    {{{  -256,      0,    443}, 0, { 32<<5,      0}, {0xd7, 0x90, 0x29, 0xff}}},
    {{{  -443,      0,    256}, 0, {     0,      0}, {0xd7, 0x90, 0x29, 0xff}}},
    {{{     0,   -256,      0}, 0, {   496,  31<<5}, {0xd7, 0x90, 0x29, 0xff}}},
    {{{   512,      0,      0}, 0, { 32<<5,      0}, {0x38, 0x90, 0x0f, 0xff}}},
    {{{   443,      0,    256}, 0, {     0,      0}, {0x38, 0x90, 0x0f, 0xff}}},
    {{{     0,   -256,      0}, 0, {   496,  31<<5}, {0x38, 0x90, 0x0f, 0xff}}},
    {{{   443,      0,    256}, 0, { 32<<5,      0}, {0x29, 0x90, 0x29, 0xff}}},
    {{{   256,      0,    443}, 0, {     0,      0}, {0x29, 0x90, 0x29, 0xff}}},
    {{{     0,   -256,      0}, 0, {   496,  31<<5}, {0x29, 0x90, 0x29, 0xff}}},
    {{{   256,      0,    443}, 0, { 32<<5,      0}, {0x0f, 0x90, 0x38, 0xff}}},
    {{{     0,      0,    512}, 0, {     0,      0}, {0x0f, 0x90, 0x38, 0xff}}},
    {{{     0,   -256,      0}, 0, {   496,  31<<5}, {0x0f, 0x90, 0x38, 0xff}}},
    {{{     0,      0,    512}, 0, { 32<<5,      0}, {0xf1, 0x90, 0x38, 0xff}}},
    {{{  -256,      0,    443}, 0, {     0,      0}, {0xf1, 0x90, 0x38, 0xff}}},
    {{{     0,   -256,      0}, 0, {   496,  31<<5}, {0xf1, 0x90, 0x38, 0xff}}},
};

// 0x0700BD10 - 0x0700BD70
static const Vtx wf_seg7_vertex_rotating_grass_platform_sides_3[] = {
    {{{  -443,      0,    256}, 0, { 32<<5,      0}, {0xc8, 0x90, 0x0f, 0xff}}},
    {{{  -512,      0,      0}, 0, {     0,      0}, {0xc8, 0x90, 0x0f, 0xff}}},
    {{{     0,   -256,      0}, 0, {   496,  31<<5}, {0xc8, 0x90, 0x0f, 0xff}}},
    {{{  -443,      0,   -256}, 0, {     0,      0}, {0xc8, 0x90, 0xf1, 0xff}}},
    {{{     0,   -256,      0}, 0, {   496,  31<<5}, {0xc8, 0x90, 0xf1, 0xff}}},
    {{{  -512,      0,      0}, 0, { 32<<5,      0}, {0xc8, 0x90, 0xf1, 0xff}}},
};

// 0x0700BD70 - 0x0700BE30
static const Vtx wf_seg7_vertex_rotating_grass_platform_top[] = {
    {{{  -443,      0,   -256}, 0, {  -192,   -720}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   443,      0,    256}, 0, {  2170,    656}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   512,      0,      0}, 0, {  2352,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   443,      0,   -256}, 0, {  2170,   -720}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   256,      0,   -443}, 0, {  1672,  -1212}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{     0,      0,   -512}, 0, { 31<<5,  -1394}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -256,      0,   -443}, 0, {   304,  -1212}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -256,      0,    443}, 0, {   304,   1146}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{     0,      0,    512}, 0, { 31<<5,   1328}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -512,      0,      0}, 0, {  -370,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -443,      0,    256}, 0, {  -192,    656}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   256,      0,    443}, 0, {  1672,   1146}, {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x0700BE30 - 0x0700BED8
static const Gfx wf_seg7_sub_dl_rotating_grass_platform_sides[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09005000_dirt_with_grass),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&wf_seg7_lights_rotating_grass_platform.l, 1),
    gsSPLight(&wf_seg7_lights_rotating_grass_platform.a, 2),
    gsSPVertex(wf_seg7_vertex_rotating_grass_platform_sides_1, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle( 12, 13, 14, 0x0),
    gsSPVertex(wf_seg7_vertex_rotating_grass_platform_sides_2, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle( 12, 13, 14, 0x0),
    gsSPVertex(wf_seg7_vertex_rotating_grass_platform_sides_3, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700BED8 - 0x0700BF50
static const Gfx wf_seg7_sub_dl_rotating_grass_platform_top[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09005800_grass),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(wf_seg7_vertex_rotating_grass_platform_top, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 0,  4,  5, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 0,  5,  6, 0x0,  0,  7,  8, 0x0),
    gsSP2Triangles( 0,  9, 10, 0x0,  0, 10,  7, 0x0),
    gsSP2Triangles( 0,  8, 11, 0x0,  0, 11,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700BF50 - 0x0700BFE0
const Gfx wf_seg7_dl_rotating_grass_platform[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(wf_seg7_sub_dl_rotating_grass_platform_sides),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(wf_seg7_sub_dl_rotating_grass_platform_top),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
