// 0x0301CECC - 0x0301CEFC
const Collision lll_seg7_collision_hexagonal_mesh_platform[] = {
    COL_INIT(),
    COL_VERTEX_INIT(0x4),
    COL_VERTEX(-200, 0, -200),
    COL_VERTEX( 200, 0, -200),
    COL_VERTEX( 200, 0,  200),
    COL_VERTEX(-200, 0,  200),

    COL_TRI_INIT(SURFACE_DEFAULT, 2),
    COL_TRI(2, 1, 0),
    COL_TRI(3, 2, 0),
    COL_TRI_STOP(),
    COL_END(),
};
