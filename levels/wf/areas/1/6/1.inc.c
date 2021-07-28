// 0x07005F58 - 0x07005F70
static const Lights1 wf_seg7_lights_large_staircase_near = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07005F70 - 0x07006060
static const Vtx wf_seg7_vertex_large_staircase_near_1[] = {
    {{{   179,    458,    900}, 0, {     0,  63<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   179,    458,    520}, 0, {     0,   3526}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -179,    458,    520}, 0, {  1398,   3526}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   179,    -89,   -240}, 0, {     0,   6558}, {0x00, 0x7e, 0x02, 0xff}}},
    {{{   179,    -80,   -621}, 0, {     0,   8080}, {0x00, 0x7e, 0x02, 0xff}}},
    {{{  -179,    -89,   -240}, 0, {  1398,   6558}, {0x00, 0x7e, 0x02, 0xff}}},
    {{{  -179,    -80,   -621}, 0, {  1398,   8080}, {0x00, 0x7e, 0x02, 0xff}}},
    {{{   179,    640,   1280}, 0, {     0,    496}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -179,    640,    900}, 0, {  1398,  63<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -179,    640,   1280}, 0, {  1398,    496}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   179,    640,    900}, 0, {     0,  63<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   179,    640,    900}, 0, {    64,    262}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -179,    458,    900}, 0, { 47<<5,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -179,    640,    900}, 0, { 47<<5,    262}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   179,    458,    900}, 0, {    64,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
};

// 0x07006060 - 0x07006150
static const Vtx wf_seg7_vertex_large_staircase_near_2[] = {
    {{{   179,    275,    140}, 0, {    64,   1708}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   179,     93,    140}, 0, {    64,   2436}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -179,     93,    140}, 0, { 47<<5,   2436}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   179,    458,    900}, 0, {     0,  63<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -179,    458,    520}, 0, {  1398,   3526}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -179,    458,    900}, 0, {  1398,  63<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   179,    458,    520}, 0, {    64,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -179,    275,    520}, 0, { 47<<5,   1712}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -179,    458,    520}, 0, { 47<<5,  31<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   179,    275,    520}, 0, {    64,   1712}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   179,    275,    520}, 0, {     0,   3524}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -179,    275,    140}, 0, {  1398,   5044}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -179,    275,    520}, 0, {  1398,   3524}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   179,    275,    140}, 0, {     0,   5044}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -179,    275,    140}, 0, { 47<<5,   1708}, {0x00, 0x00, 0x81, 0xff}}},
};

// 0x07006150 - 0x07006250
static const Vtx wf_seg7_vertex_large_staircase_near_3[] = {
    {{{   179,     93,    140}, 0, {     0,   5042}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -179,     93,   -240}, 0, {  1398,   6560}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -179,     93,    140}, 0, {  1398,   5042}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   179,     93,   -240}, 0, {     0,   6560}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   179,     93,   -240}, 0, {    64,   2432}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -179,    -89,   -240}, 0, { 47<<5,   3160}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -179,     93,   -240}, 0, { 47<<5,   2432}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   179,    -89,   -240}, 0, {    64,   3160}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   179,    275,    520}, 0, {  1980,   1626}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   179,    458,    520}, 0, {  1982,    900}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   179,    458,    900}, 0, {   464,    900}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   179,    640,    900}, 0, {   464,    176}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   179,    640,   1280}, 0, { -1056,    176}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -179,   -589,  -1280}, 0, {  1398,   2234}, {0x00, 0x68, 0xb9, 0xff}}},
    {{{  -179,   -268,   -811}, 0, {  1398,      0}, {0x00, 0x68, 0xb9, 0xff}}},
    {{{   179,   -268,   -811}, 0, {     0,      0}, {0x00, 0x68, 0xb9, 0xff}}},
};

// 0x07006250 - 0x07006330
static const Vtx wf_seg7_vertex_large_staircase_near_4[] = {
    {{{   179,     93,    140}, 0, {  3496,   2354}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   179,    275,    140}, 0, {  3498,   1626}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   179,    275,    520}, 0, {  1980,   1626}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   179,    -89,   -240}, 0, {  5012,   3082}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   179,     93,   -240}, 0, {  5014,   2354}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   179,    -80,   -621}, 0, {  6534,   3046}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   179,   -272,   -621}, 0, {  6534,   3812}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   179,   -272,   -621}, 0, {    64,   3886}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -179,   -272,   -621}, 0, { 47<<5,   3884}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   179,    -80,   -621}, 0, {    64,   3118}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -179,    -80,   -621}, 0, { 47<<5,   3118}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   179,   -589,  -1280}, 0, {     0,   2236}, {0x00, 0x68, 0xb9, 0xff}}},
    {{{  -179,   -589,  -1280}, 0, {  1398,   2234}, {0x00, 0x68, 0xb9, 0xff}}},
    {{{   179,   -268,   -811}, 0, {     0,      0}, {0x00, 0x68, 0xb9, 0xff}}},
};

// 0x07006330 - 0x070063A0
static const Vtx wf_seg7_vertex_large_staircase_near_5[] = {
    {{{   179,   -272,   -621}, 0, {     0,   8080}, {0x00, 0x7e, 0x02, 0xff}}},
    {{{   179,   -268,   -811}, 0, {     0,   8840}, {0x00, 0x7e, 0x02, 0xff}}},
    {{{  -179,   -268,   -811}, 0, {  1398,   8840}, {0x00, 0x7e, 0x02, 0xff}}},
    {{{   179,   -268,   -811}, 0, {  7294,   3794}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   179,   -272,   -621}, 0, {  6534,   3812}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   179,   -589,  -1280}, 0, {  9166, 159<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -179,   -272,   -621}, 0, {  1398,   8080}, {0x00, 0x7e, 0x02, 0xff}}},
};

// 0x070063A0 - 0x070064E8
static const Gfx wf_seg7_sub_dl_large_staircase_near[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, grass_09008000_large_pink_rocks),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&wf_seg7_lights_large_staircase_near.l, 1),
    gsSPLight(&wf_seg7_lights_large_staircase_near.a, 2),
    gsSPVertex(wf_seg7_vertex_large_staircase_near_1, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle( 11, 14, 12, 0x0),
    gsSPVertex(wf_seg7_vertex_large_staircase_near_2, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle(  0,  2, 14, 0x0),
    gsSPVertex(wf_seg7_vertex_large_staircase_near_3, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 10, 11, 12, 0x0),
    gsSP1Triangle( 13, 14, 15, 0x0),
    gsSPVertex(wf_seg7_vertex_large_staircase_near_4, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  0, 0x0),
    gsSP2Triangles( 5,  3,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 8, 10,  9, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(wf_seg7_vertex_large_staircase_near_5, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle(  0,  2,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x070064E8 - 0x07006558
const Gfx wf_seg7_dl_large_staircase_near[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(wf_seg7_sub_dl_large_staircase_near),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
