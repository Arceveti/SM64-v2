// 0x0700F090 - 0x0700F0A8
static const Lights1 ttc_seg7_lights_pendulum = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0700F0A8 - 0x0700F188
static const Vtx ttc_seg7_vertex_pendulum_arm[] = {
    {{{    19,   -666,     19}, 0, ST_B(     4,     48), {0x38, 0x00, 0x71, 0xff}}},
    {{{   -19,      0,     19}, 0, ST_B(     0,      0), {0xc8, 0x00, 0x71, 0xff}}},
    {{{   -19,   -666,     19}, 0, ST_B(     0,     48), {0x8f, 0x00, 0x38, 0xff}}},
    {{{   -19,   -666,     19}, 0, ST_B(    16,     48), {0x8f, 0x00, 0x38, 0xff}}},
    {{{   -19,      0,     19}, 0, ST_B(    16,      0), {0xc8, 0x00, 0x71, 0xff}}},
    {{{   -19,      0,    -19}, 0, ST_B(    12,      0), {0x8f, 0x00, 0xc8, 0xff}}},
    {{{   -19,   -666,    -19}, 0, ST_B(    12,     48), {0xc8, 0x00, 0x8f, 0xff}}},
    {{{   -19,   -666,    -19}, 0, ST_B(    12,     48), {0xc8, 0x00, 0x8f, 0xff}}},
    {{{    19,      0,    -19}, 0, ST_B(     8,      0), {0x38, 0x00, 0x8f, 0xff}}},
    {{{    19,   -666,    -19}, 0, ST_B(     8,     48), {0x71, 0x00, 0xc8, 0xff}}},
    {{{   -19,      0,    -19}, 0, ST_B(    12,      0), {0x8f, 0x00, 0xc8, 0xff}}},
    {{{    19,      0,     19}, 0, ST_B(     4,      0), {0x71, 0x00, 0x38, 0xff}}},
    {{{    19,   -666,     19}, 0, ST_B(     4,     48), {0x38, 0x00, 0x71, 0xff}}},
    {{{    19,      0,     19}, 0, ST_B(     4,      0), {0x71, 0x00, 0x38, 0xff}}},
};

// 0x0700F188 - 0x0700F278
static const Vtx ttc_seg7_vertex_pendulum_weight_front_1[] = {
    {{{  -144,   -768,     67}, 0, {     0,    344}, {0xde, 0x06, 0x79, 0xff}}},
    {{{   102,   -916,     67}, 0, {   852,    856}, {0x50, 0xbd, 0x48, 0xff}}},
    {{{   144,   -848,     67}, 0, { 31<<5,    618}, {0x67, 0xef, 0x47, 0xff}}},
    {{{  -102,   -916,    -67}, 0, {   102,    856}, {0xe5, 0xea, 0x87, 0xff}}},
    {{{  -144,   -848,    -67}, 0, {     0,    618}, {0x8a, 0xec, 0xd7, 0xff}}},
    {{{  -144,   -768,    -67}, 0, {     0,    344}, {0x9e, 0x24, 0xb9, 0xff}}},
    {{{  -102,   -704,    -67}, 0, {   102,    102}, {0xbd, 0x50, 0xb9, 0xff}}},
    {{{   144,   -768,    -67}, 0, { 31<<5,    344}, {0x67, 0x12, 0xb9, 0xff}}},
    {{{   144,   -848,    -67}, 0, { 31<<5,    618}, {0x62, 0xdd, 0xb9, 0xff}}},
    {{{   -38,   -666,    -67}, 0, {   340,      0}, {0xee, 0x67, 0xb9, 0xff}}},
    {{{   102,   -916,    -67}, 0, {   852,    856}, {0x42, 0xb0, 0xb8, 0xff}}},
    {{{    38,   -954,    -67}, 0, {   614,  31<<5}, {0x11, 0x99, 0xb9, 0xff}}},
    {{{   -38,   -954,    -67}, 0, {   340,  31<<5}, {0xd8, 0x8f, 0xd7, 0xff}}},
    {{{    38,   -666,    -67}, 0, {   614,      0}, {0x24, 0x62, 0xb9, 0xff}}},
    {{{   102,   -704,    -67}, 0, {   852,    102}, {0x50, 0x43, 0xb9, 0xff}}},
};

// 0x0700F278 - 0x0700F338
static const Vtx ttc_seg7_vertex_pendulum_weight_front_2[] = {
    {{{  -144,   -768,     67}, 0, {     0,    344}, {0xde, 0x06, 0x79, 0xff}}},
    {{{   -38,   -666,     67}, 0, {   340,      0}, {0xdc, 0x62, 0x47, 0xff}}},
    {{{  -102,   -704,     67}, 0, {   102,    102}, {0xa4, 0x4d, 0x29, 0xff}}},
    {{{    38,   -954,     67}, 0, {   614,  31<<5}, {0x23, 0x9e, 0x47, 0xff}}},
    {{{   102,   -916,     67}, 0, {   852,    856}, {0x50, 0xbd, 0x48, 0xff}}},
    {{{   144,   -848,     67}, 0, { 31<<5,    624}, {0x67, 0xef, 0x47, 0xff}}},
    {{{   144,   -768,     67}, 0, { 31<<5,    344}, {0x62, 0x24, 0x47, 0xff}}},
    {{{    38,   -666,     67}, 0, {   614,      0}, {0x12, 0x67, 0x47, 0xff}}},
    {{{   102,   -704,     67}, 0, {   852,    102}, {0x43, 0x50, 0x47, 0xff}}},
    {{{  -144,   -848,     67}, 0, {     0,    624}, {0x90, 0xd7, 0x29, 0xff}}},
    {{{  -102,   -916,     67}, 0, {   102,    856}, {0xbe, 0xb0, 0x48, 0xff}}},
    {{{   -38,   -954,     67}, 0, {   340,  31<<5}, {0xef, 0x99, 0x47, 0xff}}},
};

// 0x0700F338 - 0x0700F438
static const Vtx ttc_seg7_vertex_pendulum_weight_sides_1[] = {
    {{{   102,   -916,    -67}, 0, {     0,    694}, {0x42, 0xb0, 0xb8, 0xff}}},
    {{{   102,   -916,     67}, 0, { 31<<5,    694}, {0x50, 0xbd, 0x48, 0xff}}},
    {{{    38,   -954,     67}, 0, { 31<<5,    780}, {0x23, 0x9e, 0x47, 0xff}}},
    {{{   102,   -704,     67}, 0, { 31<<5,   7<<5}, {0x43, 0x50, 0x47, 0xff}}},
    {{{   102,   -704,    -67}, 0, {     0,   7<<5}, {0x50, 0x43, 0xb9, 0xff}}},
    {{{    38,   -666,    -67}, 0, {     0,    138}, {0x24, 0x62, 0xb9, 0xff}}},
    {{{    38,   -666,     67}, 0, { 31<<5,    138}, {0x12, 0x67, 0x47, 0xff}}},
    {{{   144,   -768,     67}, 0, { 31<<5,    374}, {0x62, 0x24, 0x47, 0xff}}},
    {{{   144,   -768,    -67}, 0, {     0,    374}, {0x67, 0x12, 0xb9, 0xff}}},
    {{{   -38,   -666,    -67}, 0, {     0,    138}, {0xee, 0x67, 0xb9, 0xff}}},
    {{{   -38,   -666,     67}, 0, { 31<<5,    138}, {0xdc, 0x62, 0x47, 0xff}}},
    {{{   144,   -848,     67}, 0, { 31<<5,    544}, {0x67, 0xef, 0x47, 0xff}}},
    {{{   144,   -848,    -67}, 0, {     0,    544}, {0x62, 0xdd, 0xb9, 0xff}}},
    {{{  -144,   -768,    -67}, 0, {     0,    374}, {0x9e, 0x24, 0xb9, 0xff}}},
    {{{  -102,   -704,     67}, 0, { 31<<5,   7<<5}, {0xa4, 0x4d, 0x29, 0xff}}},
    {{{  -102,   -704,    -67}, 0, {     0,   7<<5}, {0xbd, 0x50, 0xb9, 0xff}}},
};

// 0x0700F438 - 0x0700F528
static const Vtx ttc_seg7_vertex_pendulum_weight_sides_2[] = {
    {{{   102,   -916,    -67}, 0, {     0,    694}, {0x42, 0xb0, 0xb8, 0xff}}},
    {{{    38,   -954,     67}, 0, { 31<<5,    780}, {0x23, 0x9e, 0x47, 0xff}}},
    {{{    38,   -954,    -67}, 0, {     0,    780}, {0x11, 0x99, 0xb9, 0xff}}},
    {{{   -38,   -954,     67}, 0, { 31<<5,    780}, {0xef, 0x99, 0x47, 0xff}}},
    {{{   -38,   -954,    -67}, 0, {     0,    780}, {0xd8, 0x8f, 0xd7, 0xff}}},
    {{{  -102,   -916,     67}, 0, { 31<<5,    694}, {0xbe, 0xb0, 0x48, 0xff}}},
    {{{  -102,   -916,    -67}, 0, {     0,    694}, {0xe5, 0xea, 0x87, 0xff}}},
    {{{  -144,   -848,     67}, 0, { 31<<5,    544}, {0x90, 0xd7, 0x29, 0xff}}},
    {{{  -144,   -848,    -67}, 0, {     0,    544}, {0x8a, 0xec, 0xd7, 0xff}}},
    {{{  -144,   -768,     67}, 0, { 31<<5,    374}, {0xde, 0x06, 0x79, 0xff}}},
    {{{  -144,   -768,    -67}, 0, {     0,    374}, {0x9e, 0x24, 0xb9, 0xff}}},
    {{{  -102,   -704,     67}, 0, { 31<<5,    224}, {0xa4, 0x4d, 0x29, 0xff}}},
    {{{  -102,   -704,    -67}, 0, {     0,    224}, {0xbd, 0x50, 0xb9, 0xff}}},
    {{{   -38,   -666,     67}, 0, { 31<<5,    138}, {0xdc, 0x62, 0x47, 0xff}}},
    {{{   -38,   -666,    -67}, 0, {     0,    138}, {0xee, 0x67, 0xb9, 0xff}}},
};

// 0x0700F528 - 0x0700F5A0
static const Gfx ttc_seg7_sub_dl_pendulum_arm[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, ttc_seg7_texture_wood_lower),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 64 - 1, CALC_DXT(16, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ttc_seg7_lights_pendulum.l, 1),
    gsSPLight(&ttc_seg7_lights_pendulum.a, 2),
    gsSPVertex(ttc_seg7_vertex_pendulum_arm, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0,  9, 11, 12, 0x0),
    gsSP2Triangles( 9,  8, 11, 0x0,  0, 13,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700F5A0 - 0x0700F670
static const Gfx ttc_seg7_sub_dl_pendulum_weight_front[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, machine_09001800_pendulum),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ttc_seg7_vertex_pendulum_weight_front_1, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  3,  7,  8, 0x0),
    gsSP2Triangles( 3,  6,  9, 0x0,  3, 10, 11, 0x0),
    gsSP2Triangles( 3, 11, 12, 0x0,  3,  8, 10, 0x0),
    gsSP2Triangles( 3,  9, 13, 0x0,  3, 13, 14, 0x0),
    gsSP1Triangle(  3, 14,  7, 0x0),
    gsSPVertex(ttc_seg7_vertex_pendulum_weight_front_2, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  4, 0x0),
    gsSP2Triangles( 0,  5,  6, 0x0,  0,  7,  1, 0x0),
    gsSP2Triangles( 0,  8,  7, 0x0,  0,  6,  8, 0x0),
    gsSP2Triangles( 0,  9, 10, 0x0,  0, 10, 11, 0x0),
    gsSP1Triangle(  0, 11,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700F670 - 0x0700F760
static const Gfx ttc_seg7_sub_dl_pendulum_weight_sides[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, machine_09005000_yellow_block),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ttc_seg7_vertex_pendulum_weight_sides_1, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  4,  3, 0x0),
    gsSP2Triangles( 7,  8,  4, 0x0,  9,  6,  5, 0x0),
    gsSP2Triangles( 9, 10,  6, 0x0,  8,  7, 11, 0x0),
    gsSP2Triangles( 8, 11, 12, 0x0,  1, 12, 11, 0x0),
    gsSP2Triangles( 1,  0, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ttc_seg7_vertex_pendulum_weight_sides_2, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  1,  3, 0x0),
    gsSP2Triangles( 2,  3,  4, 0x0,  4,  3,  5, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  6,  5,  7, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  8,  7,  9, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10,  9, 11, 0x0),
    gsSP2Triangles(12, 11, 13, 0x0, 12, 13, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700F760 - 0x0700F830
const Gfx ttc_seg7_dl_pendulum[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetFogColor(200, 255, 255, 255),
    gsSPFogPosition(970, 1000),
    gsSPSetGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_PASS2),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 4, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_CLAMP, 4, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (16 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttc_seg7_sub_dl_pendulum_arm),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ttc_seg7_sub_dl_pendulum_weight_front),
    gsSPDisplayList(ttc_seg7_sub_dl_pendulum_weight_sides),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
