// Capswitch

const Collision capswitch_collision_top[] = {
    COL_INIT(),
    COL_VERTEX_INIT(0x8),
    COL_VERTEX( 292,   0,  256),
    COL_VERTEX( 292,   0, -256),
    COL_VERTEX( 292, 354, -256),
    COL_VERTEX(-292,   0, -256),
    COL_VERTEX(-292, 354, -256),
    COL_VERTEX(-292,   0,  256),
    COL_VERTEX(-292, 354,  256),
    COL_VERTEX( 292, 354,  256),

    COL_TRI_INIT(SURFACE_SWITCH, 10),
    COL_TRI(0, 1, 2),
    COL_TRI(1, 3, 4),
    COL_TRI(1, 4, 2),
    COL_TRI(3, 5, 6),
    COL_TRI(3, 6, 4),
    COL_TRI(2, 4, 6),
    COL_TRI(0, 2, 7),
    COL_TRI(2, 6, 7),
    COL_TRI(5, 7, 6),
    COL_TRI(5, 0, 7),
    COL_TRI_STOP(),
    COL_END(),
};

const Collision capswitch_collision_base[] = {
    COL_INIT(),
    COL_VERTEX_INIT(0x8),
    COL_VERTEX( 292,   0,  256),
    COL_VERTEX( 292,   0, -256),
    COL_VERTEX( 292, 144, -256),
    COL_VERTEX(-292,   0, -256),
    COL_VERTEX(-292, 144, -256),
    COL_VERTEX(-292,   0,  256),
    COL_VERTEX(-292, 144,  256),
    COL_VERTEX( 292, 144,  256),

    COL_TRI_INIT(SURFACE_SWITCH, 10),
    COL_TRI(0, 1, 2),
    COL_TRI(1, 3, 4),
    COL_TRI(1, 4, 2),
    COL_TRI(3, 5, 6),
    COL_TRI(3, 6, 4),
    COL_TRI(2, 4, 6),
    COL_TRI(0, 2, 7),
    COL_TRI(2, 6, 7),
    COL_TRI(5, 7, 6),
    COL_TRI(5, 0, 7),
    COL_TRI_STOP(),
    COL_END(),
};
