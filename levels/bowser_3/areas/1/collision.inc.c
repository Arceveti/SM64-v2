// 0x070049C8 - 0x07004B94
const Collision bowser_3_seg7_collision_level[] = {
    COL_INIT(),
    COL_VERTEX_INIT(0x18),
    COL_VERTEX(-8191, -6143, 8192),
    COL_VERTEX(8192, -6143, 8192),
    COL_VERTEX(8192, -6143, -8191),
    COL_VERTEX(-8191, -6143, -8191),
    COL_VERTEX(-1182, -2364, 394),
    COL_VERTEX(-1182, 307, 394),
    COL_VERTEX(-2364, 307, -787),
    COL_VERTEX(-2364, -1852, -787),
    COL_VERTEX(-787, 307, -1024),
    COL_VERTEX(-787, -2364, -1024),
    COL_VERTEX(-1497, -1852, 2050),
    COL_VERTEX(-1497, 307, 2050),
    COL_VERTEX(0, 307, 1262),
    COL_VERTEX(788, 307, -1024),
    COL_VERTEX(0, 307, -2522),
    COL_VERTEX(1183, 307, 394),
    COL_VERTEX(1498, -1852, 2050),
    COL_VERTEX(1498, 307, 2050),
    COL_VERTEX(0, -2364, 1262),
    COL_VERTEX(2365, 307, -787),
    COL_VERTEX(2365, -1852, -787),
    COL_VERTEX(1183, -2364, 394),
    COL_VERTEX(788, -2364, -1024),
    COL_VERTEX(0, -1852, -2522),
    COL_TRI_INIT(SURFACE_DEFAULT, 36),
    COL_TRI(4, 18, 10),
    COL_TRI(4, 5, 6),
    COL_TRI(4, 6, 7),
    COL_TRI(6, 5, 8),
    COL_TRI(6, 8, 9),
    COL_TRI(7, 6, 9),
    COL_TRI(10, 5, 4),
    COL_TRI(10, 11, 5),
    COL_TRI(5, 11, 12),
    COL_TRI(8, 5, 12),
    COL_TRI(13, 14, 8),
    COL_TRI(8, 12, 15),
    COL_TRI(8, 15, 13),
    COL_TRI(9, 8, 14),
    COL_TRI(16, 17, 12),
    COL_TRI(16, 12, 18),
    COL_TRI(18, 12, 11),
    COL_TRI(12, 17, 15),
    COL_TRI(18, 11, 10),
    COL_TRI(18, 4, 9),
    COL_TRI(4, 7, 9),
    COL_TRI(9, 23, 22),
    COL_TRI(15, 19, 13),
    COL_TRI(20, 19, 15),
    COL_TRI(20, 15, 21),
    COL_TRI(21, 15, 17),
    COL_TRI(22, 13, 19),
    COL_TRI(14, 13, 22),
    COL_TRI(23, 14, 22),
    COL_TRI(9, 14, 23),
    COL_TRI(22, 19, 20),
    COL_TRI(21, 17, 16),
    COL_TRI(21, 22, 20),
    COL_TRI(18, 22, 21),
    COL_TRI(16, 18, 21),
    COL_TRI(18, 9, 22),
    COL_TRI_INIT(SURFACE_DEATH_PLANE, 2),
    COL_TRI(0, 1, 2),
    COL_TRI(0, 2, 3),
    COL_TRI_STOP(),
    COL_SPECIAL_INIT(7),
    SPECIAL_OBJECT_WITH_YAW(/*preset*/ special_null_start,   /*pos*/     0,   307,     0, /*yaw*/  128), // unused, probably an early way to set initial position
    SPECIAL_OBJECT(         /*preset*/ special_bowser,       /*pos*/    13,   307, -1024),
    SPECIAL_OBJECT_WITH_YAW(/*preset*/ special_level_geo_03, /*pos*/ -3362,  -205,  1121, /*yaw*/    0),
    SPECIAL_OBJECT_WITH_YAW(/*preset*/ special_level_geo_03, /*pos*/     0,  -205,  3584, /*yaw*/    0),
    SPECIAL_OBJECT_WITH_YAW(/*preset*/ special_level_geo_03, /*pos*/  3362,  -205,  1126, /*yaw*/    0),
    SPECIAL_OBJECT_WITH_YAW(/*preset*/ special_level_geo_03, /*pos*/  2123,  -205, -2912, /*yaw*/    0),
    SPECIAL_OBJECT_WITH_YAW(/*preset*/ special_level_geo_03, /*pos*/ -2122,  -205, -2912, /*yaw*/    0),
    COL_END(),
};
