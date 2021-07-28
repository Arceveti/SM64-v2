// 0x07008838 - 0x07008850
static const Lights1 wf_seg7_lights_tower_far = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07008850 - 0x07008950
static const Vtx wf_seg7_vertex_tower_far_windows[] = {
    {{{   128,   1792,    128}, 0, { 39<<5,   1000}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   128,   2048,    128}, 0, { 39<<5,    -20}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -128,   2048,    128}, 0, {  7<<5,    -20}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -128,   1792,   -128}, 0, {  1236,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   128,   2048,   -128}, 0, {   214,    -32}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   128,   1792,   -128}, 0, {   214,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -128,   2048,   -128}, 0, {  1236,    -32}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -128,   1792,    128}, 0, {  1226,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -128,   2048,    128}, 0, {  1226,    -32}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -128,   2048,   -128}, 0, {   208,    -32}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -128,   1792,   -128}, 0, {   208,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   128,   1792,   -128}, 0, { 39<<5,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   128,   2048,   -128}, 0, { 39<<5,    -24}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   128,   2048,    128}, 0, {  7<<5,    -24}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   128,   1792,    128}, 0, {  7<<5,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -128,   1792,    128}, 0, {  7<<5,   1000}, {0x00, 0x00, 0x7f, 0xff}}},
};

// 0x07008950 - 0x070089F0
static const Vtx wf_seg7_vertex_tower_far_balcony_floor[] = {
    {{{   256,   2048,    256}, 0, {127<<5, 127<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{  -256,   2048,    256}, 0, {127<<5,      0}, {0x00, 0x81, 0x00, 0xff}}},
    {{{  -256,   2048,   -256}, 0, {     0,      0}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   256,   2048,   -256}, 0, {     0, 127<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{     0,   1792,   -538}, 0, {  -800,  -1362}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   466,   1792,    269}, 0, { 33<<5,   1858}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   466,   1792,   -269}, 0, { 33<<5,   -288}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -466,   1792,   -269}, 0, { -2662,   -288}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -466,   1792,    269}, 0, { -2662,   1858}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{     0,   1792,    538}, 0, {  -800,   2932}, {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x070089F0 - 0x07008AF0
static const Vtx wf_seg7_vertex_tower_far_roof_1[] = {
    {{{   466,   1536,   -269}, 0, { 31<<5,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   466,   1792,   -269}, 0, { 31<<5,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   466,   1792,    269}, 0, {   -80,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -466,   1536,    269}, 0, {  1040,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -466,   1792,   -269}, 0, {     0,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -466,   1536,   -269}, 0, {     0,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -466,   1792,    269}, 0, {  1040,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{     0,   1536,    538}, 0, {  1040,  31<<5}, {0xc1, 0x00, 0x6d, 0xff}}},
    {{{  -466,   1792,    269}, 0, {     0,      0}, {0xc1, 0x00, 0x6d, 0xff}}},
    {{{  -466,   1536,    269}, 0, {     0,  31<<5}, {0xc1, 0x00, 0x6d, 0xff}}},
    {{{     0,   1792,    538}, 0, {  1040,      0}, {0xc1, 0x00, 0x6d, 0xff}}},
    {{{   466,   1536,    269}, 0, { 31<<5,  31<<5}, {0x3f, 0x00, 0x6d, 0xff}}},
    {{{     0,   1792,    538}, 0, {   -80,      0}, {0x3f, 0x00, 0x6d, 0xff}}},
    {{{     0,   1536,    538}, 0, {   -80,  31<<5}, {0x3f, 0x00, 0x6d, 0xff}}},
    {{{   466,   1792,    269}, 0, { 31<<5,      0}, {0x3f, 0x00, 0x6d, 0xff}}},
    {{{   466,   1536,    269}, 0, {   -80,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
};

// 0x07008AF0 - 0x07008BD0
static const Vtx wf_seg7_vertex_tower_far_roof_2[] = {
    {{{     0,   1536,   -538}, 0, { 31<<5,  31<<5}, {0x3f, 0x00, 0x93, 0xff}}},
    {{{   466,   1792,   -269}, 0, {   -80,      0}, {0x3f, 0x00, 0x93, 0xff}}},
    {{{   466,   1536,   -269}, 0, {   -80,  31<<5}, {0x3f, 0x00, 0x93, 0xff}}},
    {{{     0,   1792,   -538}, 0, { 31<<5,      0}, {0x3f, 0x00, 0x93, 0xff}}},
    {{{  -466,   1536,   -269}, 0, {  1040,  31<<5}, {0xc1, 0x00, 0x93, 0xff}}},
    {{{     0,   1792,   -538}, 0, {     0,      0}, {0xc1, 0x00, 0x93, 0xff}}},
    {{{     0,   1536,   -538}, 0, {     0,  31<<5}, {0xc1, 0x00, 0x93, 0xff}}},
    {{{  -466,   1792,   -269}, 0, {  1040,      0}, {0xc1, 0x00, 0x93, 0xff}}},
    {{{   256,   2048,   -256}, 0, { -1056,  31<<5}, {0x00, 0x38, 0x8f, 0xff}}},
    {{{  -256,   2048,   -256}, 0, { 95<<5,  31<<5}, {0x00, 0x38, 0x8f, 0xff}}},
    {{{     0,   2560,      0}, 0, { 31<<5,  -3580}, {0x00, 0x38, 0x8f, 0xff}}},
    {{{  -256,   2048,    256}, 0, { -2414,  31<<5}, {0x00, 0x38, 0x71, 0xff}}},
    {{{   256,   2048,    256}, 0, {  1672,  31<<5}, {0x00, 0x38, 0x71, 0xff}}},
    {{{     0,   2560,      0}, 0, {  -370,  -3588}, {0x00, 0x38, 0x71, 0xff}}},
};

// 0x07008BD0 - 0x07008C30
static const Vtx wf_seg7_vertex_tower_far_roof_3[] = {
    {{{  -256,   2048,   -256}, 0, {     0,  31<<5}, {0x8f, 0x38, 0x00, 0xff}}},
    {{{  -256,   2048,    256}, 0, {127<<5,  31<<5}, {0x8f, 0x38, 0x00, 0xff}}},
    {{{     0,   2560,      0}, 0, { 63<<5,  -3580}, {0x8f, 0x38, 0x00, 0xff}}},
    {{{   256,   2048,    256}, 0, {     0,  31<<5}, {0x71, 0x38, 0x00, 0xff}}},
    {{{   256,   2048,   -256}, 0, {127<<5,  31<<5}, {0x71, 0x38, 0x00, 0xff}}},
    {{{     0,   2560,      0}, 0, { 63<<5,  -3580}, {0x71, 0x38, 0x00, 0xff}}},
};

// 0x07008C30 - 0x07008D20
static const Vtx wf_seg7_vertex_tower_far_sides_1[] = {
    {{{   466,      0,   -269}, 0, { 39<<5,   7120}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   466,   1536,    269}, 0, {   -96,   -544}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   466,      0,    269}, 0, {   -96,   7120}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -466,      0,    269}, 0, { 39<<5,   7120}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -466,   1536,    269}, 0, { 39<<5,   -544}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -466,   1536,   -269}, 0, {   -96,   -544}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -466,      0,   -269}, 0, {   -96,   7120}, {0x81, 0x00, 0x00, 0xff}}},
    {{{     0,      0,    538}, 0, { 39<<5,   7120}, {0xc1, 0x00, 0x6d, 0xff}}},
    {{{     0,   1536,    538}, 0, { 39<<5,   -544}, {0xc1, 0x00, 0x6d, 0xff}}},
    {{{  -466,   1536,    269}, 0, {   -96,   -544}, {0xc1, 0x00, 0x6d, 0xff}}},
    {{{  -466,      0,    269}, 0, {   -96,   7120}, {0xc1, 0x00, 0x6d, 0xff}}},
    {{{   466,      0,    269}, 0, { 39<<5,   7120}, {0x3f, 0x00, 0x6d, 0xff}}},
    {{{   466,   1536,    269}, 0, { 39<<5,   -544}, {0x3f, 0x00, 0x6d, 0xff}}},
    {{{     0,   1536,    538}, 0, {   -96,   -544}, {0x3f, 0x00, 0x6d, 0xff}}},
    {{{     0,      0,    538}, 0, {   -96,   7120}, {0x3f, 0x00, 0x6d, 0xff}}},
};

// 0x07008D20 - 0x07008DD0
static const Vtx wf_seg7_vertex_tower_far_sides_2[] = {
    {{{  -466,      0,   -269}, 0, { 39<<5,   7120}, {0xc1, 0x00, 0x93, 0xff}}},
    {{{  -466,   1536,   -269}, 0, { 39<<5,   -544}, {0xc1, 0x00, 0x93, 0xff}}},
    {{{     0,   1536,   -538}, 0, {   -96,   -544}, {0xc1, 0x00, 0x93, 0xff}}},
    {{{   466,      0,   -269}, 0, { 39<<5,   7120}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   466,   1536,   -269}, 0, { 39<<5,   -544}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   466,   1536,    269}, 0, {   -96,   -544}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{     0,      0,   -538}, 0, { 39<<5,   7120}, {0x3f, 0x00, 0x93, 0xff}}},
    {{{     0,   1536,   -538}, 0, { 39<<5,   -544}, {0x3f, 0x00, 0x93, 0xff}}},
    {{{   466,   1536,   -269}, 0, {   -96,   -544}, {0x3f, 0x00, 0x93, 0xff}}},
    {{{   466,      0,   -269}, 0, {   -96,   7120}, {0x3f, 0x00, 0x93, 0xff}}},
    {{{     0,      0,   -538}, 0, {   -96,   7120}, {0xc1, 0x00, 0x93, 0xff}}},
};

// 0x07008DD0 - 0x07008E48
static const Gfx wf_seg7_sub_dl_tower_far_windows[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, wf_seg7_texture_tower_window),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&wf_seg7_lights_tower_far.l, 1),
    gsSPLight(&wf_seg7_lights_tower_far.a, 2),
    gsSPVertex(wf_seg7_vertex_tower_far_windows, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0,  2, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x07008E48 - 0x07008EA0
static const Gfx wf_seg7_sub_dl_tower_far_balcony_floor[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09007800_gray_diagonal_checker),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(wf_seg7_vertex_tower_far_balcony_floor, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  8, 0x0),
    gsSP2Triangles( 4,  8,  9, 0x0,  4,  9,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x07008EA0 - 0x07008F58
static const Gfx wf_seg7_sub_dl_tower_far_roof[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09009000_orange_brick),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(wf_seg7_vertex_tower_far_roof_1, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0,  0,  2, 15, 0x0),
    gsSPVertex(wf_seg7_vertex_tower_far_roof_2, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(wf_seg7_vertex_tower_far_roof_3, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x07008F58 - 0x07008FE8
static const Gfx wf_seg7_sub_dl_tower_far_sides[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09007000_beige_bricks),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(wf_seg7_vertex_tower_far_sides_1, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle( 11, 13, 14, 0x0),
    gsSPVertex(wf_seg7_vertex_tower_far_sides_2, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP1Triangle(  0,  2, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x07008FE8 - 0x07009070
const Gfx wf_seg7_dl_tower_far[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(wf_seg7_sub_dl_tower_far_windows),
    gsSPDisplayList(wf_seg7_sub_dl_tower_far_balcony_floor),
    gsSPDisplayList(wf_seg7_sub_dl_tower_far_roof),
    gsSPDisplayList(wf_seg7_sub_dl_tower_far_sides),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
