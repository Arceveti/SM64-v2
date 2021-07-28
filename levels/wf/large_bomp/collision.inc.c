// 0x0700F934 - 0x0700FA00
const Collision wf_seg7_collision_large_bomp[] = {
    COL_INIT(),
    COL_VERTEX_INIT(0xE),
    COL_VERTEX( 256,   5, -256),
    COL_VERTEX( 192, 210, -256),
    COL_VERTEX( 256, 210, -192),
    COL_VERTEX( 256, 210,  189),
    COL_VERTEX( 256,   5,  256),
    COL_VERTEX(-256, 210, -256),
    COL_VERTEX(-256,   5, -256),
    COL_VERTEX( 136, 261, -156),
    COL_VERTEX( 192, 210,  256),
    COL_VERTEX( 136, 261,  151),
    COL_VERTEX(-256,   5,  256),
    COL_VERTEX(-256, 261,  151),
    COL_VERTEX(-256, 261, -156),
    COL_VERTEX(-256, 210,  256),
    COL_TRI_INIT(SURFACE_WALL_MISC, 18),
    COL_TRI(12,  1,  5),
    COL_TRI( 0,  1,  2),
    COL_TRI( 0,  3,  4),
    COL_TRI( 0,  2,  3),
    COL_TRI( 5,  1,  0),
    COL_TRI( 5,  0,  6),
    COL_TRI( 1,  7,  2),
    COL_TRI( 7,  3,  2),
    COL_TRI( 3,  8,  4),
    COL_TRI( 3,  9,  8),
    COL_TRI( 7,  9,  3),
    COL_TRI(10,  4,  8),
    COL_TRI(11,  7, 12),
    COL_TRI(11,  9,  7),
    COL_TRI(12,  7,  1),
    COL_TRI(10,  8, 13),
    COL_TRI(13,  8,  9),
    COL_TRI(13,  9, 11),
    COL_TRI_STOP(),
    COL_END(),
};
