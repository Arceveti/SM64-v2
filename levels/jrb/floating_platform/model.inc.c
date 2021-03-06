// 0x07007B70 - 0x07007B88
static const Lights1 jrb_seg7_lights_floating_platform = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07007B88 - 0x07007C88
static const Vtx jrb_seg7_vertex_floating_platform_sides[] = {
    {{{  -256,    -64,    640}, 0, {  -882,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -256,     64,    640}, 0, {  -882,    848}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -256,     64,   -640}, 0, {  3374,    848}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   256,    -64,    640}, 0, {   138,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   256,     64,    640}, 0, {   138,    848}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -256,     64,    640}, 0, { 31<<5,    848}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -256,    -64,    640}, 0, { 31<<5,  31<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   256,    -64,   -640}, 0, {  3374,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   256,     64,    640}, 0, {  -882,    848}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   256,    -64,    640}, 0, {  -882,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   256,     64,   -640}, 0, {  3374,    848}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -256,    -64,   -640}, 0, { 31<<5,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -256,     64,   -640}, 0, { 31<<5,    848}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   256,     64,   -640}, 0, {   138,    848}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   256,    -64,   -640}, 0, {   138,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -256,    -64,   -640}, 0, {  3374,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
};

// 0x07007C88 - 0x07007D08
static const Vtx jrb_seg7_vertex_floating_platform_surface[] = {
    {{{   256,    -64,    640}, 0, { -2328,  31<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{  -256,    -64,    640}, 0, { -2328,  -1566}, {0x00, 0x81, 0x00, 0xff}}},
    {{{  -256,    -64,   -640}, 0, {127<<5,  -1566}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   256,    -64,   -640}, 0, {127<<5,  31<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   256,     64,   -640}, 0, {127<<5,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -256,     64,    640}, 0, { -2328,  -1566}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   256,     64,    640}, 0, { -2328,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -256,     64,   -640}, 0, {127<<5,  -1566}, {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x07007D08 - 0x07007D80
static const Gfx jrb_seg7_sub_dl_floating_platform_sides[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_0900A000_small_wood_planks),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&jrb_seg7_lights_floating_platform.l, 1),
    gsSPLight(&jrb_seg7_lights_floating_platform.a, 2),
    gsSPVertex(jrb_seg7_vertex_floating_platform_sides, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 13, 14, 0x0,  0,  2, 15, 0x0),
    gsSPEndDisplayList(),
};

// 0x07007D80 - 0x07007DC8
static const Gfx jrb_seg7_sub_dl_floating_platform_surface[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_0900A800_small_blue_wood_planks),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(jrb_seg7_vertex_floating_platform_surface, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x07007DC8 - 0x07007EA0
const Gfx jrb_seg7_dl_floating_platform[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetFogColor(5, 80, 75, 255),
    gsSPFogPosition(JRB_FOG_MIN, JRB_FOG_MAX),
    gsSPSetGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_PASS2),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(jrb_seg7_sub_dl_floating_platform_sides),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(jrb_seg7_sub_dl_floating_platform_surface),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
