// 0x0700F800 - 0x0700F818
static const Lights1 ccm_seg7_lights_snowman_platform = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0700F818 - 0x0700F878
static const Vtx ccm_seg7_vertex_snowman_platform_top[] = {
    {{{  -177,    102,   -154}, 0, {  2906,  -3104}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{     0,    102,    154}, 0, {  1832,  -4510}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   177,    102,     51}, 0, {  1020,  -3890}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -177,    102,     51}, 0, {  2776,  -4112}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   177,    102,   -154}, 0, {  1152,  -2876}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{     0,    102,   -256}, 0, {  2094,  -2482}, {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x0700F878 - 0x0700F968
static const Vtx ccm_seg7_vertex_snowman_platform_sides_1[] = {
    {{{   177,      0,     51}, 0, {     0,  31<<5}, {0x3f, 0x00, 0x6d, 0xff}}},
    {{{     0,    102,    154}, 0, { 63<<5,      0}, {0x3f, 0x00, 0x6d, 0xff}}},
    {{{     0,      0,    154}, 0, { 63<<5,  31<<5}, {0x3f, 0x00, 0x6d, 0xff}}},
    {{{  -177,      0,   -154}, 0, { 63<<5,  31<<5}, {0xc1, 0x00, 0x92, 0xff}}},
    {{{  -177,    102,   -154}, 0, { 63<<5,      0}, {0xc1, 0x00, 0x92, 0xff}}},
    {{{     0,    102,   -256}, 0, {     0,      0}, {0xc1, 0x00, 0x92, 0xff}}},
    {{{     0,      0,   -256}, 0, {     0,  31<<5}, {0xc1, 0x00, 0x92, 0xff}}},
    {{{  -177,      0,     51}, 0, { 63<<5,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -177,    102,     51}, 0, { 63<<5,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -177,    102,   -154}, 0, {     0,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -177,      0,   -154}, 0, {     0,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{     0,      0,    154}, 0, { 63<<5,  31<<5}, {0xc1, 0x00, 0x6d, 0xff}}},
    {{{  -177,    102,     51}, 0, {     0,      0}, {0xc1, 0x00, 0x6d, 0xff}}},
    {{{  -177,      0,     51}, 0, {     0,  31<<5}, {0xc1, 0x00, 0x6d, 0xff}}},
    {{{     0,    102,    154}, 0, { 63<<5,      0}, {0xc1, 0x00, 0x6d, 0xff}}},
};

// 0x0700F968 - 0x0700FA18
static const Vtx ccm_seg7_vertex_snowman_platform_sides_2[] = {
    {{{     0,      0,   -256}, 0, {     0,  31<<5}, {0x3f, 0x00, 0x92, 0xff}}},
    {{{     0,    102,   -256}, 0, {     0,      0}, {0x3f, 0x00, 0x92, 0xff}}},
    {{{   177,    102,   -154}, 0, { 63<<5,      0}, {0x3f, 0x00, 0x92, 0xff}}},
    {{{   177,      0,     51}, 0, {     0,  31<<5}, {0x3f, 0x00, 0x6d, 0xff}}},
    {{{   177,    102,     51}, 0, {     0,      0}, {0x3f, 0x00, 0x6d, 0xff}}},
    {{{     0,    102,    154}, 0, { 63<<5,      0}, {0x3f, 0x00, 0x6d, 0xff}}},
    {{{   177,      0,   -154}, 0, {     0,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   177,    102,     51}, 0, { 63<<5,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   177,      0,     51}, 0, { 63<<5,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   177,    102,   -154}, 0, {     0,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   177,      0,   -154}, 0, { 63<<5,  31<<5}, {0x3f, 0x00, 0x92, 0xff}}},
};

// 0x0700FA18 - 0x0700FA70
static const Gfx ccm_seg7_dl_snowman_platform_top[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snow_09008000_wood_planks),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ccm_seg7_lights_snowman_platform.l, 1),
    gsSPLight(&ccm_seg7_lights_snowman_platform.a, 2),
    gsSPVertex(ccm_seg7_vertex_snowman_platform_top, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  0,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700FA70 - 0x0700FB00
static const Gfx ccm_seg7_dl_snowman_platform_sides[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, ccm_seg7_texture_snowman_platform_face),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ccm_seg7_vertex_snowman_platform_sides_1, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ccm_seg7_vertex_snowman_platform_sides_2, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP1Triangle( 0,  2, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700FB00 - 0x0700FB78
const Gfx ccm_seg7_dl_snowman_platform[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ccm_seg7_dl_snowman_platform_top),
    gsSPDisplayList(ccm_seg7_dl_snowman_platform_sides),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
