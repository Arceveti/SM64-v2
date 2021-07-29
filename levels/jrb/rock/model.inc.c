// 0x070077F0 - 0x07007808
static const Lights1 jrb_seg7_lights_rock = gdSPDefLights1(
    0x32, 0x38, 0x3f,
    0xc8, 0xe1, 0xff, 0x28, 0x28, 0x28
);

// 0x07007808 - 0x07007908
static const Vtx jrb_seg7_vertex_rock_1[] = {
    {{{    32,   -410,   -339}, 0, {  3096,      0}, {0xf9, 0x0a, 0x82, 0xff}}},
    {{{   216,   -809,    -54}, 0, {  3896,  -1024}, {0x4e, 0x9c, 0xfd, 0xff}}},
    {{{     8,   -823,   -219}, 0, {  3060,  -1064}, {0xfd, 0xa7, 0xa7, 0xff}}},
    {{{  -109,     -8,    -54}, 0, {  2308,    960}, {0xc5, 0x5e, 0xc4, 0xff}}},
    {{{  -307,   -410,      0}, 0, { 63<<5,      0}, {0x87, 0xfd, 0x23, 0xff}}},
    {{{     8,     29,     82}, 0, {   928,  33<<5}, {0xdc, 0x5a, 0x51, 0xff}}},
    {{{    28,   -144,   -183}, 0, {  3132,    632}, {0x2c, 0x46, 0xa0, 0xff}}},
    {{{   307,   -410,      0}, 0, {127<<5,      0}, {0x7d, 0x0b, 0x0a, 0xff}}},
    {{{    84,     29,      8}, 0, {  4108,  33<<5}, {0x4a, 0x66, 0xff, 0xff}}},
    {{{   -67,   -823,   -144}, 0, {  2752,  -1056}, {0xb3, 0x9d, 0xf4, 0xff}}},
    {{{  -109,     -8,    -54}, 0, {  1592,    210}, {0xc5, 0x5e, 0xc4, 0xff}}},
    {{{     8,     29,     82}, 0, {   808,   -336}, {0xdc, 0x5a, 0x51, 0xff}}},
    {{{    84,     29,      8}, 0, {   304,      0}, {0x4a, 0x66, 0xff, 0xff}}},
    {{{    28,   -676,    134}, 0, {   864,   -696}, {0xfe, 0xb5, 0x66, 0xff}}},
    {{{    32,   -410,    264}, 0, {   912,      0}, {0x1c, 0x07, 0x7b, 0xff}}},
    {{{    84,     29,      8}, 0, {    20,  33<<5}, {0x4a, 0x66, 0xff, 0xff}}},
};

// 0x07007908 - 0x070079E8
static const Vtx jrb_seg7_vertex_rock_2[] = {
    {{{    32,   -410,    264}, 0, {   912,      0}, {0x1c, 0x07, 0x7b, 0xff}}},
    {{{   307,   -410,      0}, 0, {     0,      0}, {0x7d, 0x0b, 0x0a, 0xff}}},
    {{{    84,     29,      8}, 0, {    16,  33<<5}, {0x4a, 0x66, 0xff, 0xff}}},
    {{{    28,   -144,   -183}, 0, {   680,    720}, {0x2c, 0x46, 0xa0, 0xff}}},
    {{{  -109,     -8,    -54}, 0, {  1592,    210}, {0xc5, 0x5e, 0xc4, 0xff}}},
    {{{    84,     29,      8}, 0, {   304,      0}, {0x4a, 0x66, 0xff, 0xff}}},
    {{{    28,   -676,    134}, 0, {   864,   -696}, {0xfe, 0xb5, 0x66, 0xff}}},
    {{{   216,   -809,    -54}, 0, {  3896,  -1024}, {0x4e, 0x9c, 0xfd, 0xff}}},
    {{{   307,   -410,      0}, 0, {127<<5,      0}, {0x7d, 0x0b, 0x0a, 0xff}}},
    {{{    28,   -676,    134}, 0, {  4948,   -696}, {0xfe, 0xb5, 0x66, 0xff}}},
    {{{   -67,   -823,   -144}, 0, {  1312,    570}, {0xb3, 0x9d, 0xf4, 0xff}}},
    {{{     8,   -823,   -219}, 0, {   808,    870}, {0xfd, 0xa7, 0xa7, 0xff}}},
    {{{   216,   -809,    -54}, 0, {  -568,    210}, {0x4e, 0x9c, 0xfd, 0xff}}},
    {{{    28,   -676,    134}, 0, {   680,   -544}, {0xfe, 0xb5, 0x66, 0xff}}},
};

// 0x070079E8 - 0x07007AC8
static const Gfx jrb_seg7_sub_dl_rock[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_09001800_rock),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&jrb_seg7_lights_rock.l, 1),
    gsSPLight(&jrb_seg7_lights_rock.a, 2),
    gsSPVertex(jrb_seg7_vertex_rock_1, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 0,  4,  3, 0x0,  3,  6,  0, 0x0),
    gsSP2Triangles( 7,  0,  6, 0x0,  8,  7,  6, 0x0),
    gsSP2Triangles( 9,  4,  0, 0x0,  9,  0,  2, 0x0),
    gsSP2Triangles( 7,  1,  0, 0x0, 10, 11, 12, 0x0),
    gsSP2Triangles(13, 14,  4, 0x0, 13,  4,  9, 0x0),
    gsSP2Triangles( 4, 14,  5, 0x0,  5, 14, 15, 0x0),
    gsSPVertex(jrb_seg7_vertex_rock_2, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 1,  0,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSPEndDisplayList(),
};

// 0x07007AC8 - 0x07007B70
const Gfx jrb_seg7_dl_rock[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetFogColor(5, 80, 75, 255),
    gsSPFogPosition(900, 1000),
    gsSPSetGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_PASS2),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(jrb_seg7_sub_dl_rock),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
