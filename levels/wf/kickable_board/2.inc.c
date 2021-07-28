// 0x0700F680 - 0x0700F6C0
static const Vtx wf_seg7_vertex_kickable_board_shadow[] = {
    {{{   -96,      0,    300}, 0, {  -480,   -480}, {0x00, 0x00, 0x00, 0x96}}},
    {{{    96,      0,    300}, 0, { 15<<5,   -480}, {0x00, 0x00, 0x00, 0x96}}},
    {{{    96,      0,      0}, 0, { 15<<5,  15<<5}, {0x00, 0x00, 0x00, 0x96}}},
    {{{   -96,      0,      0}, 0, {  -480,  15<<5}, {0x00, 0x00, 0x00, 0x96}}},
};

// 0x0700F6C0 - 0x0700F758
const Gfx wf_seg7_dl_kickable_board_shadow[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetCombineMode(G_CC_MODULATEIA, G_CC_MODULATEIA),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPLoadTextureBlock(wf_seg7_texture_kickable_board_shadow, G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, 0, G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(wf_seg7_vertex_kickable_board_shadow, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_LIGHTING),
    gsSPEndDisplayList(),
};
