// Unused collision mapping for the water level diamond.

// 0x070184C8 - 0x07018528
UNUSED const Collision wdw_seg7_collision_water_level_diamond[] = {
    COL_INIT(),
    COL_VERTEX_INIT(0x6),
    COL_VERTEX( 51,  51, -51),
    COL_VERTEX(-51,  51, -51),
    COL_VERTEX(  0, 102,   0),
    COL_VERTEX(-51,  51,  51),
    COL_VERTEX(  0,   0,   0),
    COL_VERTEX( 51,  51,  51),
    COL_TRI_INIT(SURFACE_DEFAULT, 8),
    COL_TRI(0, 1, 2),
    COL_TRI(3, 1, 4),
    COL_TRI(1, 0, 4),
    COL_TRI(1, 3, 2),
    COL_TRI(5, 3, 4),
    COL_TRI(3, 5, 2),
    COL_TRI(5, 0, 2),
    COL_TRI(0, 5, 4),
    COL_TRI_STOP(),
    COL_END(),
};
