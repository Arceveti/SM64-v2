// 0x0700ED68 - 0x0700ED80
static const Lights1 ttc_seg7_lights_rotating_prism = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0700ED80 - 0x0700EE60
static const Vtx ttc_seg7_vertex_rotating_prism_base[] = {
    {{{     0,   -230,    200}, 0, { -1056,      0}, {0x29, 0xb8, 0x5f, 0xff}}},
    {{{     0,      0,    200}, 0, { 31<<5,  24<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -200,    112,    200}, 0, { 63<<5,      0}, {0xad, 0x00, 0x5f, 0xff}}},
    {{{  -200,    112,   -200}, 0, { -1056,      0}, {0xd7, 0x48, 0xa1, 0xff}}},
    {{{     0,      0,   -200}, 0, { 31<<5,  24<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{     0,   -230,   -200}, 0, { 63<<5,      0}, {0xd7, 0xb8, 0xa1, 0xff}}},
    {{{     0,   -230,   -200}, 0, { -1056,      0}, {0xd7, 0xb8, 0xa1, 0xff}}},
    {{{   200,    112,   -200}, 0, { 63<<5,      0}, {0x53, 0x00, 0xa0, 0xff}}},
    {{{   200,    112,   -200}, 0, { -1056,      0}, {0x53, 0x00, 0xa0, 0xff}}},
    {{{  -200,    112,   -200}, 0, { 63<<5,      0}, {0xd7, 0x48, 0xa1, 0xff}}},
    {{{   200,    112,    200}, 0, { -1056,      0}, {0x29, 0x47, 0x60, 0xff}}},
    {{{     0,   -230,    200}, 0, { 63<<5,      0}, {0x29, 0xb8, 0x5f, 0xff}}},
    {{{  -200,    112,    200}, 0, { -1056,      0}, {0xad, 0x00, 0x5f, 0xff}}},
    {{{   200,    112,    200}, 0, { 63<<5,      0}, {0x29, 0x47, 0x60, 0xff}}},
};

// 0x0700EE60 - 0x0700EF20
static const Vtx ttc_seg7_vertex_rotating_prism_lateral_sides[] = {
    {{{   200,    112,    200}, 0, { 31<<5,      0}, {0x29, 0x47, 0x60, 0xff}}},
    {{{  -200,    112,   -200}, 0, {     0,  31<<5}, {0xd7, 0x48, 0xa1, 0xff}}},
    {{{  -200,    112,    200}, 0, { 31<<5,  31<<5}, {0xad, 0x00, 0x5f, 0xff}}},
    {{{   200,    112,   -200}, 0, {     0,      0}, {0x53, 0x00, 0xa0, 0xff}}},
    {{{  -200,    112,    200}, 0, { 31<<5,      0}, {0xad, 0x00, 0x5f, 0xff}}},
    {{{  -200,    112,   -200}, 0, {     0,      0}, {0xd7, 0x48, 0xa1, 0xff}}},
    {{{     0,   -230,   -200}, 0, {     0,  31<<5}, {0xd7, 0xb8, 0xa1, 0xff}}},
    {{{     0,   -230,    200}, 0, { 31<<5,  31<<5}, {0x29, 0xb8, 0x5f, 0xff}}},
    {{{     0,   -230,    200}, 0, { 31<<5,      0}, {0x29, 0xb8, 0x5f, 0xff}}},
    {{{     0,   -230,   -200}, 0, {     0,      0}, {0xd7, 0xb8, 0xa1, 0xff}}},
    {{{   200,    112,   -200}, 0, {     0,  31<<5}, {0x53, 0x00, 0xa0, 0xff}}},
    {{{   200,    112,    200}, 0, { 31<<5,  31<<5}, {0x29, 0x47, 0x60, 0xff}}},
};

// 0x0700EF20 - 0x0700EF88
static const Gfx ttc_seg7_sub_dl_rotating_prism_base[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, machine_09001000_horizontal_rods),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttc_seg7_lights_rotating_prism.l, 1),
    gsSPLight(&ttc_seg7_lights_rotating_prism.a, 2),
    gsSPVertex(ttc_seg7_vertex_rotating_prism_base, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  4,  7, 0x0,  8,  4,  9, 0x0),
    gsSP2Triangles(10,  1, 11, 0x0, 12,  1, 13, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700EF88 - 0x0700EFE0
static const Gfx ttc_seg7_sub_dl_rotating_prism_lateral_sides[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, machine_09005000_yellow_block),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ttc_seg7_vertex_rotating_prism_lateral_sides, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700EFE0 - 0x0700F090
const Gfx ttc_seg7_dl_rotating_prism[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetFogColor(200, 255, 255, 255),
    gsSPFogPosition(900, 1000),
    gsSPSetGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_PASS2),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttc_seg7_sub_dl_rotating_prism_base),
    gsSPDisplayList(ttc_seg7_sub_dl_rotating_prism_lateral_sides),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
