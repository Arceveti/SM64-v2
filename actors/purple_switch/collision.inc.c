// Purple Switch

// 0x0800C7A8 - 0x0800C820
const Collision purple_switch_seg8_collision_purple_switch[] = {
    COL_INIT(),
    COL_VERTEX_INIT(0x8),
    COL_VERTEX(  64, 36,  -64),
    COL_VERTEX( -64, 36,  -64),
    COL_VERTEX( -64, 36,   64),
    COL_VERTEX(  64, 36,   64),
    COL_VERTEX(-102,  0, -102),
    COL_VERTEX( 102,  0, -102),
    COL_VERTEX(-102,  0,  102),
    COL_VERTEX( 102,  0,  102),

    COL_TRI_INIT(SURFACE_SWITCH, 10),
    COL_TRI(0, 1, 2),
    COL_TRI(0, 2, 3),
    COL_TRI(4, 1, 0),
    COL_TRI(4, 0, 5),
    COL_TRI(6, 1, 4),
    COL_TRI(6, 2, 1),
    COL_TRI(7, 3, 2),
    COL_TRI(7, 2, 6),
    COL_TRI(5, 0, 3),
    COL_TRI(5, 3, 7),
    COL_TRI_STOP(),
    COL_END(),
};
