// 0x070153E0 - 0x0701550C
const Collision ttc_seg7_collision_small_treadmill[] = {
    COL_INIT(),
    COL_VERTEX_INIT(0x14),
    COL_VERTEX(-230,    0, -307),
    COL_VERTEX(-230, -138,  307),
    COL_VERTEX(-230,    0,  307),
    COL_VERTEX(-230, -138, -307),
    COL_VERTEX( 230,    0,  307),
    COL_VERTEX( 230, -138, -307),
    COL_VERTEX( 230,    0, -307),
    COL_VERTEX( 230, -138,  307),
    COL_VERTEX( 230, -138,  343),
    COL_VERTEX( 230,  -36,  343),
    COL_VERTEX( 230, -138, -343),
    COL_VERTEX( 230,  -36, -343),
    COL_VERTEX(-230, -138, -343),
    COL_VERTEX(-230,  -36, -343),
    COL_VERTEX(-230,  -87,  343),
    COL_VERTEX(-230,  -36,  343),
    COL_VERTEX(-230, -138,  343),
    COL_VERTEX( 230,  -87,  343),
    COL_VERTEX( 230,  -87, -343),
    COL_VERTEX(-230,  -87, -343),
    COL_TRI_INIT(SURFACE_NOT_SLIPPERY, 28),
    COL_TRI( 5, 10, 11),
    COL_TRI( 0,  1,  2),
    COL_TRI( 0,  3,  1),
    COL_TRI( 4,  5,  6),
    COL_TRI( 4,  7,  5),
    COL_TRI( 4,  8,  7),
    COL_TRI( 4,  9,  8),
    COL_TRI( 0, 13, 12),
    COL_TRI( 5, 11,  6),
    COL_TRI( 8, 14, 16),
    COL_TRI( 8, 17, 14),
    COL_TRI( 1, 15,  2),
    COL_TRI( 1, 16, 15),
    COL_TRI( 0, 12,  3),
    COL_TRI(13, 11, 18),
    COL_TRI(12, 18, 10),
    COL_TRI(12, 19, 18),
    COL_TRI(10, 16, 12),
    COL_TRI(10,  8, 16),
    COL_TRI( 0, 11, 13),
    COL_TRI( 0,  6, 11),
    COL_TRI( 2,  4,  6),
    COL_TRI(13, 18, 19),
    COL_TRI(14,  9, 15),
    COL_TRI(14, 17,  9),
    COL_TRI(15,  4,  2),
    COL_TRI(15,  9,  4),
    COL_TRI( 2,  6,  0),
    COL_TRI_STOP(),
    COL_END(),
};
