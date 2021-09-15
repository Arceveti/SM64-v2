// Capswitch

//! TODO: Combine these into one collision model that moves/scales

const Collision capswitch_collision_top[] = {
    COL_INIT(),
    COL_VERTEX_INIT(0xC),
    COL_VERTEX(-256,    0,    0), // 0
    COL_VERTEX(-128,    0,  224), // 1
    COL_VERTEX( 128,    0,  224), // 2
    COL_VERTEX( 256,    0,    0), // 3
    COL_VERTEX( 128,    0, -224), // 4
    COL_VERTEX(-128,    0, -224), // 5
    COL_VERTEX(-256,  354,    0), // 6
    COL_VERTEX(-128,  354,  224), // 7
    COL_VERTEX( 128,  354,  224), // 8
    COL_VERTEX( 256,  354,    0), // 9
    COL_VERTEX( 128,  354, -224), // 10
    COL_VERTEX(-128,  354, -224), // 11

    COL_TRI_INIT(SURFACE_SWITCH, 16),
    COL_TRI(0,  6, 11),
    COL_TRI(0, 11,  5),
    COL_TRI(1,  7,  6),
    COL_TRI(1,  6,  0),
    COL_TRI(2,  8,  7),
    COL_TRI(2,  7,  1),
    COL_TRI(3,  9,  8),
    COL_TRI(3,  8,  2),
    COL_TRI(4, 10,  9),
    COL_TRI(4,  9,  3),
    COL_TRI(5, 11, 10),
    COL_TRI(5, 10,  4),
    COL_TRI(6,  7,  8),
    COL_TRI(6,  8,  9),
    COL_TRI(6, 10, 11),
    COL_TRI(6,  9, 10),
    COL_TRI_STOP(),
    COL_END(),
};

const Collision capswitch_collision_base[] = {
    COL_INIT(),
    COL_VERTEX_INIT(0xC),
    COL_VERTEX(-288,    0,    0), // 0
    COL_VERTEX(-147,    0,  256), // 1
    COL_VERTEX( 147,    0,  256), // 2
    COL_VERTEX( 288,    0,    0), // 3
    COL_VERTEX( 147,    0, -256), // 4
    COL_VERTEX(-147,    0, -256), // 5
    COL_VERTEX(-288,  144,    0), // 6
    COL_VERTEX(-147,  144,  256), // 7
    COL_VERTEX( 147,  144,  256), // 8
    COL_VERTEX( 288,  144,    0), // 9
    COL_VERTEX( 147,  144, -256), // 10
    COL_VERTEX(-147,  144, -256), // 11

    COL_TRI_INIT(SURFACE_SWITCH, 16),
    COL_TRI(0,  6, 11),
    COL_TRI(0, 11,  5),
    COL_TRI(1,  7,  6),
    COL_TRI(1,  6,  0),
    COL_TRI(2,  8,  7),
    COL_TRI(2,  7,  1),
    COL_TRI(3,  9,  8),
    COL_TRI(3,  8,  2),
    COL_TRI(4, 10,  9),
    COL_TRI(4,  9,  3),
    COL_TRI(5, 11, 10),
    COL_TRI(5, 10,  4),
    COL_TRI(6,  7,  8),
    COL_TRI(6,  8,  9),
    COL_TRI(6, 10, 11),
    COL_TRI(6,  9, 10),
    COL_TRI_STOP(),
    COL_END(),
};
