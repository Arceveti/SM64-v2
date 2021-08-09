// 0x070284DC - 0x0702856C
const Collision lll_seg7_collision_falling_wall[] = {
    COL_INIT(),
    COL_VERTEX_INIT(0xA),
    COL_VERTEX( 307, -102, 102),
    COL_VERTEX( 307,  614, 102),
    COL_VERTEX( 307, -102, 700),
    COL_VERTEX(-307,  614, 102),
    COL_VERTEX(-307, -102, 700),
    COL_VERTEX(-307, -102, 102),
    COL_VERTEX(-307, -102,   3),
    COL_VERTEX(-307,  614,   3),
    COL_VERTEX( 307,  614,   3),
    COL_VERTEX( 307, -102,   3),
    COL_TRI_INIT(SURFACE_DEFAULT, 12),
    COL_TRI(0, 1, 2),
    COL_TRI(2, 1, 3),
    COL_TRI(2, 3, 4),
    COL_TRI(3, 5, 4),
    COL_TRI(6, 7, 8),
    COL_TRI(6, 8, 9),
    COL_TRI(7, 1, 8),
    COL_TRI(7, 3, 1),
    COL_TRI(7, 6, 5),
    COL_TRI(7, 5, 3),
    COL_TRI(9, 8, 1),
    COL_TRI(9, 1, 0),
    COL_TRI_STOP(),
    COL_END(),
};
