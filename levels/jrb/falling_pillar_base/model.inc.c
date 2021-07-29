// 0x0700AEF0 - 0x0700AF08
static const Lights1 jrb_seg7_lights_falling_pillar_base = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0700AF08 - 0x0700AF58
static const Vtx jrb_seg7_vertex_falling_pillar_base[] = {
    {{{   102,      0,   -102}, 0, { 63<<5,  -1056}, {0x33, 0x67, 0xcc, 0xff}}},
    {{{     0,    102,      0}, 0, { 31<<5,      0}, {0x00, 0x7e, 0x00, 0xff}}},
    {{{   102,      0,    102}, 0, { 63<<5,  31<<5}, {0x33, 0x67, 0x33, 0xff}}},
    {{{  -102,      0,   -102}, 0, {     0,  -1056}, {0xcc, 0x67, 0xcc, 0xff}}},
    {{{  -102,      0,    102}, 0, {     0,  31<<5}, {0xcc, 0x67, 0x33, 0xff}}},
};

// 0x0700AF58 - 0x0700AFB0
static const Gfx jrb_seg7_sub_dl_falling_pillar_base[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_09001800_rock),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&jrb_seg7_lights_falling_pillar_base.l, 1),
    gsSPLight(&jrb_seg7_lights_falling_pillar_base.a, 2),
    gsSPVertex(jrb_seg7_vertex_falling_pillar_base, 5, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  1, 0x0),
    gsSP2Triangles( 2,  1,  4, 0x0,  1,  0,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700AFB0 - 0x0700B058
const Gfx jrb_seg7_dl_falling_pillar_base[] = {
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
    gsSPDisplayList(jrb_seg7_sub_dl_falling_pillar_base),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsSPEndDisplayList(),
};
