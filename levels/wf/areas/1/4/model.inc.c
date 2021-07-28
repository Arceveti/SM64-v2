// Wall Arrows

// 0x07005568 - 0x07005658
static const Vtx wf_seg7_vertex_wall_arrows[] = {
    {{{  1270,   2944,   -773}, 0, {     0,      0}, {0xff, 0xff, 0x00, 0x80}}},
    {{{  1343,   2739,   -845}, 0, {     0,      0}, {0xff, 0xff, 0x00, 0x80}}},
    {{{  1198,   2739,   -700}, 0, {     0,      0}, {0xff, 0xff, 0x00, 0x80}}},
    {{{  3594,   1459,    870}, 0, {     0,      0}, {0xff, 0xff, 0x00, 0x80}}},
    {{{  3594,   1587,   1126}, 0, {     0,      0}, {0xff, 0xff, 0x00, 0x80}}},
    {{{  3594,   1331,   1126}, 0, {     0,      0}, {0xff, 0xff, 0x00, 0x80}}},
    {{{  3594,   1459,   -512}, 0, {     0,      0}, {0xff, 0xff, 0x00, 0x80}}},
    {{{  3594,   1587,   -256}, 0, {     0,      0}, {0xff, 0xff, 0x00, 0x80}}},
    {{{  3594,   1331,   -256}, 0, {     0,      0}, {0xff, 0xff, 0x00, 0x80}}},
    {{{ -1034,   2944,    512}, 0, {     0,      0}, {0xff, 0xff, 0x00, 0x80}}},
    {{{ -1034,   2816,    256}, 0, {     0,      0}, {0xff, 0xff, 0x00, 0x80}}},
    {{{ -1034,   2688,    512}, 0, {     0,      0}, {0xff, 0xff, 0x00, 0x80}}},
    {{{  -825,   2944,  -1018}, 0, {     0,      0}, {0xff, 0xff, 0x00, 0x80}}},
    {{{  -728,   2816,  -1255}, 0, {     0,      0}, {0xff, 0xff, 0x00, 0x80}}},
    {{{  -825,   2688,  -1018}, 0, {     0,      0}, {0xff, 0xff, 0x00, 0x80}}},
};

// 0x07005658 - 0x07005690
static const Gfx wf_seg7_sub_dl_wall_arrows[] = {
    gsSPVertex(wf_seg7_vertex_wall_arrows, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle( 12, 13, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x07005690 - 0x070056C0
const Gfx wf_seg7_dl_wall_arrows[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPDisplayList(wf_seg7_sub_dl_wall_arrows),
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
