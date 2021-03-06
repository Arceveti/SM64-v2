// 0x0700EA00 - 0x0700EA18
static const Lights1 ccm_seg7_lights_lower_cabin_snow = gdSPDefLights1(
    0x7f, 0x7f, 0x7f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0700EA18 - 0x0700EA30
static const Lights1 ccm_seg7_lights_lower_cabin_outside_fake_interior_wood = gdSPDefLights1(
    0x33, 0x33, 0x33,
    0x66, 0x66, 0x66, 0x28, 0x28, 0x28
);

// 0x0700EA30 - 0x0700EA48
static const Lights1 ccm_seg7_lights_0700EA30 = gdSPDefLights1(
    0x5d, 0x5d, 0x5d,
    0xbb, 0xbb, 0xbb, 0x28, 0x28, 0x28
);

// 0x0700EA48 - 0x0700EAE8
static const Vtx ccm_seg7_vertex_lower_cabin_snow[] = {
    {{{  -116,    100,    541}, 0, { -3130,   1874}, {0x16, 0x7a, 0x17, 0xff}}},
    {{{   573,    100,    -99}, 0, {     0,   1874}, {0x16, 0x7a, 0x17, 0xff}}},
    {{{    44,    307,   -669}, 0, {     0,   -704}, {0x16, 0x7a, 0x17, 0xff}}},
    {{{  -611,    307,      9}, 0, { -3130,   -544}, {0x19, 0x7a, 0x18, 0xff}}},
    {{{  -116,    100,    541}, 0, { -3130,   1874}, {0x19, 0x7a, 0x18, 0xff}}},
    {{{    44,    307,   -669}, 0, {     0,   -704}, {0x19, 0x7a, 0x18, 0xff}}},
    {{{  -176,    565,   -440}, 0, { -1424,   1600}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   524,    565,   -137}, 0, {     0,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{    36,    565,   -662}, 0, { -1460,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   299,    565,     71}, 0, {     0,   1600}, {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x0700EAE8 - 0x0700EBD8
static const Vtx ccm_seg7_vertex_0700EAE8[] = {
    {{{   221,   -512,    214}, 0, {  4566,  31<<5}, {0x56, 0x00, 0x5d, 0xff}}},
    {{{   289,   -378,    151}, 0, {  5486,   -338}, {0x56, 0x00, 0x5d, 0xff}}},
    {{{   221,   -256,    214}, 0, {  4566,  -1566}, {0x56, 0x00, 0x5d, 0xff}}},
    {{{   364,   -378,     81}, 0, {  3442,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   219,   -378,     77}, 0, {  2420,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   289,   -378,    151}, 0, {  2420,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   294,   -378,      6}, 0, {  3442,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -115,   -512,    527}, 0, {     0,  31<<5}, {0x56, 0x00, 0x5c, 0xff}}},
    {{{   109,   -512,    318}, 0, { 95<<5,  31<<5}, {0x56, 0x00, 0x5c, 0xff}}},
    {{{  -115,     92,    527}, 0, {     0,  -5040}, {0x56, 0x00, 0x5c, 0xff}}},
    {{{   109,   -256,    318}, 0, { 95<<5,  -1566}, {0x56, 0x00, 0x5c, 0xff}}},
    {{{  -115,     92,    527}, 0, {     0,  -5040}, {0x56, 0x00, 0x5d, 0xff}}},
    {{{   109,   -256,    318}, 0, { 95<<5,  -1566}, {0x56, 0x00, 0x5d, 0xff}}},
    {{{   559,     92,    -99}, 0, {  9166,  -5040}, {0x56, 0x00, 0x5d, 0xff}}},
    {{{   289,   -275,    151}, 0, {  5486,  -1360}, {0x56, 0x00, 0x5d, 0xff}}},
};

// 0x0700EBD8 - 0x0700ECB8
static const Vtx ccm_seg7_vertex_0700EBD8[] = {
    {{{    36,   -512,   -662}, 0, { -7694,  31<<5}, {0x5d, 0x00, 0xaa, 0xff}}},
    {{{    36,    307,   -662}, 0, { -7694,  -7186}, {0x5d, 0x00, 0xaa, 0xff}}},
    {{{   559,     92,    -99}, 0, {     0,  -5040}, {0x5d, 0x00, 0xaa, 0xff}}},
    {{{   289,   -275,    151}, 0, {  5486,  -1360}, {0x56, 0x00, 0x5c, 0xff}}},
    {{{   364,   -275,     81}, 0, {  6508,  -1360}, {0x56, 0x00, 0x5c, 0xff}}},
    {{{   559,     92,    -99}, 0, {  9166,  -5040}, {0x56, 0x00, 0x5c, 0xff}}},
    {{{   559,     92,    -99}, 0, {  9166,  -5040}, {0x56, 0x00, 0x5d, 0xff}}},
    {{{   364,   -275,     81}, 0, {  6508,  -1360}, {0x56, 0x00, 0x5d, 0xff}}},
    {{{   559,   -512,    -99}, 0, {  9166,  31<<5}, {0x56, 0x00, 0x5d, 0xff}}},
    {{{   364,   -378,     81}, 0, {  6508,   -338}, {0x56, 0x00, 0x5d, 0xff}}},
    {{{   364,   -378,     81}, 0, {  6508,   -338}, {0x56, 0x00, 0x5c, 0xff}}},
    {{{   289,   -378,    151}, 0, {  5486,   -338}, {0x56, 0x00, 0x5c, 0xff}}},
    {{{   221,   -512,    214}, 0, {  4566,  31<<5}, {0x56, 0x00, 0x5c, 0xff}}},
    {{{   221,   -512,    214}, 0, {  4566,  31<<5}, {0x56, 0x00, 0x5d, 0xff}}},
};

// 0x0700ECB8 - 0x0700ED98
static const Vtx ccm_seg7_vertex_0700ECB8[] = {
    {{{  -115,   -512,    527}, 0, {     0,  31<<5}, {0xa3, 0x00, 0x56, 0xff}}},
    {{{  -115,     92,    527}, 0, {     0,  -5040}, {0xa3, 0x00, 0x56, 0xff}}},
    {{{  -603,   -512,      2}, 0, { -7184,  31<<5}, {0xa3, 0x00, 0x56, 0xff}}},
    {{{  -603,    297,      2}, 0, { -7184,  -7084}, {0xa3, 0x00, 0x56, 0xff}}},
    {{{    36,   -512,   -662}, 0, { -7694,  31<<5}, {0x5d, 0x00, 0xaa, 0xff}}},
    {{{   559,     92,    -99}, 0, {     0,  -5040}, {0x5d, 0x00, 0xaa, 0xff}}},
    {{{   559,   -512,    -99}, 0, {     0,  31<<5}, {0x5d, 0x00, 0xaa, 0xff}}},
    {{{  -176,    565,   -440}, 0, { -7006,  -3494}, {0xa3, 0x00, 0x55, 0xff}}},
    {{{  -176,    307,   -440}, 0, { -7004,   -916}, {0xa3, 0x00, 0x55, 0xff}}},
    {{{   -10,    237,   -258}, 0, { -4546,   -214}, {0xa3, 0x00, 0x55, 0xff}}},
    {{{   524,    116,   -137}, 0, {  3030,  31<<5}, {0x56, 0x00, 0x5d, 0xff}}},
    {{{   524,    565,   -137}, 0, {  3030,  -3494}, {0x56, 0x00, 0x5d, 0xff}}},
    {{{   299,    116,     71}, 0, {     0,  31<<5}, {0x56, 0x00, 0x5d, 0xff}}},
    {{{   299,    565,     71}, 0, {     0,  -3494}, {0x56, 0x00, 0x5d, 0xff}}},
};

// 0x0700ED98 - 0x0700EE38
static const Vtx ccm_seg7_vertex_0700ED98[] = {
    {{{    36,    307,   -662}, 0, { -7176,   -916}, {0x5d, 0x00, 0xaa, 0xff}}},
    {{{   524,    565,   -137}, 0, {     0,  -3494}, {0x5d, 0x00, 0xaa, 0xff}}},
    {{{   524,    116,   -137}, 0, {     0,  31<<5}, {0x5d, 0x00, 0xaa, 0xff}}},
    {{{    36,    565,   -662}, 0, { -7176,  -3494}, {0x5d, 0x00, 0xaa, 0xff}}},
    {{{   299,    116,     71}, 0, {     0,  31<<5}, {0xa4, 0x00, 0x56, 0xff}}},
    {{{   299,    565,     71}, 0, {     0,  -3494}, {0xa4, 0x00, 0x56, 0xff}}},
    {{{   -10,    237,   -258}, 0, { -4546,   -214}, {0xa4, 0x00, 0x56, 0xff}}},
    {{{   299,    565,     71}, 0, {     0,  -3494}, {0xa3, 0x00, 0x56, 0xff}}},
    {{{  -176,    565,   -440}, 0, { -7006,  -3494}, {0xa3, 0x00, 0x56, 0xff}}},
    {{{   -10,    237,   -258}, 0, { -4546,   -214}, {0xa3, 0x00, 0x56, 0xff}}},
};

// 0x0700EE38 - 0x0700EF38
static const Vtx ccm_seg7_vertex_0700EE38[] = {
    {{{   109,   -256,    318}, 0, {     0,      0}, {0x00, 0x81, 0x00, 0xff}}},
    {{{    39,   -256,    243}, 0, {     0,  31<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   221,   -256,    214}, 0, { 47<<5,      0}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   219,   -378,     77}, 0, { -1056,   -338}, {0x5c, 0x00, 0xaa, 0xff}}},
    {{{   219,   -275,     77}, 0, { -1056,  -1360}, {0x5c, 0x00, 0xaa, 0xff}}},
    {{{   289,   -275,    151}, 0, {     0,  -1360}, {0x5c, 0x00, 0xaa, 0xff}}},
    {{{   289,   -275,    151}, 0, {  2420,      0}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   219,   -275,     77}, 0, {  2420,  31<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   364,   -275,     81}, 0, {  3442,      0}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   294,   -275,      6}, 0, {  3442,  31<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   294,   -378,      6}, 0, { -1056,   -338}, {0xa4, 0x00, 0x56, 0xff}}},
    {{{   364,   -275,     81}, 0, {     0,  -1360}, {0xa4, 0x00, 0x56, 0xff}}},
    {{{   294,   -275,      6}, 0, { -1056,  -1360}, {0xa4, 0x00, 0x56, 0xff}}},
    {{{    39,   -256,    243}, 0, { -1056,  -1564}, {0x5c, 0x00, 0xaa, 0xff}}},
    {{{   109,   -256,    318}, 0, {     0,  -1564}, {0x5c, 0x00, 0xaa, 0xff}}},
    {{{    39,   -512,    243}, 0, { -1056,  31<<5}, {0x5c, 0x00, 0xaa, 0xff}}},
};

// 0x0700EF38 - 0x0700EF98
static const Vtx ccm_seg7_vertex_0700EF38[] = {
    {{{    39,   -256,    243}, 0, {     0,  31<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   152,   -256,    139}, 0, { 47<<5,  31<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   221,   -256,    214}, 0, { 47<<5,      0}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   152,   -256,    139}, 0, { -1056,  -1564}, {0xa3, 0x00, 0x55, 0xff}}},
    {{{   152,   -512,    139}, 0, { -1056,  31<<5}, {0xa3, 0x00, 0x55, 0xff}}},
    {{{   221,   -256,    214}, 0, {     0,  -1564}, {0xa3, 0x00, 0x55, 0xff}}},
};

// 0x0700EF98 - 0x0700F058
static const Vtx ccm_seg7_vertex_0700EF98[] = {
    {{{   289,   -378,    151}, 0, {     0,   -338}, {0x5c, 0x00, 0xaa, 0xff}}},
    {{{   219,   -378,     77}, 0, { -1056,   -338}, {0x5c, 0x00, 0xaa, 0xff}}},
    {{{   289,   -275,    151}, 0, {     0,  -1360}, {0x5c, 0x00, 0xaa, 0xff}}},
    {{{   294,   -378,      6}, 0, { -1056,   -338}, {0xa4, 0x00, 0x56, 0xff}}},
    {{{   364,   -378,     81}, 0, {     0,   -338}, {0xa4, 0x00, 0x56, 0xff}}},
    {{{   364,   -275,     81}, 0, {     0,  -1360}, {0xa4, 0x00, 0x56, 0xff}}},
    {{{   221,   -512,    214}, 0, {     0,  31<<5}, {0xa3, 0x00, 0x55, 0xff}}},
    {{{   221,   -256,    214}, 0, {     0,  -1564}, {0xa3, 0x00, 0x55, 0xff}}},
    {{{   152,   -512,    139}, 0, { -1056,  31<<5}, {0xa3, 0x00, 0x55, 0xff}}},
    {{{    39,   -512,    243}, 0, { -1056,  31<<5}, {0x5c, 0x00, 0xaa, 0xff}}},
    {{{   109,   -256,    318}, 0, {     0,  -1564}, {0x5c, 0x00, 0xaa, 0xff}}},
    {{{   109,   -512,    318}, 0, {     0,  31<<5}, {0x5c, 0x00, 0xaa, 0xff}}},
};

// 0x0700F058 - 0x0700F148
static const Vtx ccm_seg7_vertex_0700F058[] = {
    {{{   173,   -512,   -439}, 0, {     0,  -5654}, {0x56, 0x00, 0x5d, 0xff}}},
    {{{  -314,   -100,     13}, 0, {  3964,  33<<5}, {0x56, 0x00, 0x5d, 0xff}}},
    {{{  -314,   -512,     13}, 0, {  -132,  31<<5}, {0x56, 0x00, 0x5d, 0xff}}},
    {{{   452,   -100,   -139}, 0, {  6612,  -3098}, {0x00, 0x81, 0x00, 0xff}}},
    {{{  -314,   -100,     13}, 0, {     0,  31<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   173,   -100,   -439}, 0, {  6612,  31<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   -35,   -100,    313}, 0, {     0,  -3098}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   452,   -512,   -139}, 0, {     0,  31<<5}, {0xa4, 0x00, 0x56, 0xff}}},
    {{{   452,   -100,   -139}, 0, {127<<5,  31<<5}, {0xa4, 0x00, 0x56, 0xff}}},
    {{{   173,   -100,   -439}, 0, {127<<5,  -3098}, {0xa4, 0x00, 0x56, 0xff}}},
    {{{   173,   -512,   -439}, 0, {     0,  -3098}, {0xa4, 0x00, 0x56, 0xff}}},
    {{{  -314,   -512,     13}, 0, {     0,  -3098}, {0x5c, 0x00, 0xaa, 0xff}}},
    {{{   -35,   -100,    313}, 0, {127<<5,  31<<5}, {0x5c, 0x00, 0xaa, 0xff}}},
    {{{   -35,   -512,    313}, 0, {     0,  31<<5}, {0x5c, 0x00, 0xaa, 0xff}}},
    {{{  -314,   -100,     13}, 0, {127<<5,  -3098}, {0x5c, 0x00, 0xaa, 0xff}}},
};

// 0x0700F148 - 0x0700F1B8
static const Vtx ccm_seg7_vertex_0700F148[] = {
    {{{  -314,   -501,     13}, 0, {     0,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   452,   -501,   -139}, 0, {  6612,  -3098}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   173,   -501,   -439}, 0, {  6612,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   173,   -512,   -439}, 0, {     0,  -5654}, {0x56, 0x00, 0x5d, 0xff}}},
    {{{   173,   -100,   -439}, 0, {127<<5,  -5590}, {0x56, 0x00, 0x5d, 0xff}}},
    {{{  -314,   -100,     13}, 0, {  3964,  33<<5}, {0x56, 0x00, 0x5d, 0xff}}},
    {{{   -35,   -501,    313}, 0, {     0,  -3098}, {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x0700F1B8 - 0x0700F210
static const Gfx ccm_seg7_dl_lower_cabin_snow[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snow_09008800_snow),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ccm_seg7_lights_lower_cabin_snow.l, 1),
    gsSPLight(&ccm_seg7_lights_lower_cabin_snow.a, 2),
    gsSPVertex(ccm_seg7_vertex_lower_cabin_snow, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700F210 - 0x0700F3B0
static const Gfx ccm_seg7_dl_lower_cabin_bricks[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snow_09005000_bricks),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(ccm_seg7_vertex_0700EAE8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(12,  2, 13, 0x0,  2, 14, 13, 0x0),
    gsSP1Triangle(14,  2,  1, 0x0),
    gsSPVertex(ccm_seg7_vertex_0700EBD8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  7,  9,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0,  8,  9, 13, 0x0),
    gsSPVertex(ccm_seg7_vertex_0700ECB8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 11, 13, 12, 0x0),
    gsSPVertex(ccm_seg7_vertex_0700ED98, 10, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSPLight(&ccm_seg7_lights_lower_cabin_outside_fake_interior_wood.l, 1),
    gsSPLight(&ccm_seg7_lights_lower_cabin_outside_fake_interior_wood.a, 2),
    gsSPVertex(ccm_seg7_vertex_0700EE38, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  7,  9,  8, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(ccm_seg7_vertex_0700EF38, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPLight(&ccm_seg7_lights_0700EA30.l, 1),
    gsSPLight(&ccm_seg7_lights_0700EA30.a, 2),
    gsSPVertex(ccm_seg7_vertex_0700EF98, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700F3B0 - 0x0700F440
static const Gfx ccm_seg7_dl_lower_cabin_outside_fake_interior_wood[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, snow_09008000_wood_planks),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&ccm_seg7_lights_lower_cabin_outside_fake_interior_wood.l, 1),
    gsSPLight(&ccm_seg7_lights_lower_cabin_outside_fake_interior_wood.a, 2),
    gsSPVertex(ccm_seg7_vertex_0700F058, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(ccm_seg7_vertex_0700F148, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 0,  6,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x0700F440 - 0x0700F4C0
const Gfx ccm_seg7_dl_lower_cabin_outside[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(ccm_seg7_dl_lower_cabin_snow),
    gsSPDisplayList(ccm_seg7_dl_lower_cabin_bricks),
    gsSPDisplayList(ccm_seg7_dl_lower_cabin_outside_fake_interior_wood),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
