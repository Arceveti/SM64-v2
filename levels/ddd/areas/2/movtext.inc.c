// 0x0700FCC4
static Movtex ddd_movtex_area2_water_data[] = {
    MOV_TEX_INIT_LOAD(    2),
    MOV_TEX_ROT_SPEED(   20), // area 2 general water
    MOV_TEX_ROT_SPEED(   20),
    MOV_TEX_4_BOX_TRIS(    0, -5120),
    MOV_TEX_4_BOX_TRIS(    0,  7168),
    MOV_TEX_4_BOX_TRIS( 8192,  7168),
    MOV_TEX_4_BOX_TRIS( 8192, -5120),
    MOV_TEX_ROT(     ROTATE_CLOCKWISE),
    MOV_TEX_ALPHA(    0xA0),
    MOV_TEX_DEFINE(  TEXTURE_WATER),
    MOV_TEX_END(),
    MOV_TEX_ROT_SPEED(    0), // entrance to area 1 water
    MOV_TEX_ROT_SPEED(    5),
    MOV_TEX_4_BOX_TRIS(-6144,  -768),
    MOV_TEX_4_BOX_TRIS(-6144,   768),
    MOV_TEX_4_BOX_TRIS(-2048,   768),
    MOV_TEX_4_BOX_TRIS(-2048,  -768),
    MOV_TEX_ROT(     ROTATE_CLOCKWISE),
    MOV_TEX_ALPHA(    0xA0),
    MOV_TEX_DEFINE(  TEXTURE_WATER),
    MOV_TEX_END(),
};

// 0x0700FD00
const struct MovtexQuadCollection ddd_movtex_area2_water[] = {
    {0, ddd_movtex_area2_water_data},
    {-1, NULL},
};

#ifdef DDD_WARP_CURRENT_TEXTURE
// dddhole
Movtex ddd_movtex_tris_sub_hole[] = {
    MOV_TEX_SPD(  100),
    MOV_TEX_TRIS(3917, -2040, -7168, 0, 1), //  -
    MOV_TEX_TRIS(2893, -1016, -4096, 2, 0), // 'v
    MOV_TEX_TRIS(4941, -1016, -4096, 2, 2), //  v'
    MOV_TEX_TRIS(4941, -1016, -4096, 2, 0), //  <'
    MOV_TEX_TRIS(4941, -3064, -4096, 2, 2), //  <,
    MOV_TEX_TRIS(4941, -3064, -4096, 2, 0), //  ^,
    MOV_TEX_TRIS(2893, -3064, -4096, 2, 2), // ,^
    MOV_TEX_TRIS(2893, -3064, -4096, 2, 0), // ,>
    MOV_TEX_TRIS(2893, -1016, -4096, 2, 2), // '>
    MOV_TEX_END(),
};

// dddhole
const Gfx ddd_dl_movtex_sub_hole[] = {
    gsSP2Triangles(0, 1, 2, 0x0, 0, 3, 4, 0x0),
    gsSP2Triangles(0, 5, 6, 0x0, 0, 7, 8, 0x0),
    gsSPEndDisplayList(),
};
#endif

