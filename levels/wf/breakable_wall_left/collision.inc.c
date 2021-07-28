// 0x0700FC44 - 0x0700FC7A
const Collision wf_seg7_collision_breakable_wall_2[] = {
    COL_INIT(),
    COL_VERTEX_INIT(0x4),
    COL_VERTEX(   0, -384,  128),
    COL_VERTEX(   0,  384,  128),
    COL_VERTEX(-169,  384, -379),
    COL_VERTEX(   0,  384, -379),
    COL_TRI_INIT(SURFACE_DEFAULT, 3),
    COL_TRI(3, 2, 1),
    COL_TRI(0, 1, 2),
    COL_TRI(3, 1, 0),
    COL_TRI_STOP(),
    COL_END(),
};
