// Warp Pipe

// 0x03009AC8 - 0x03009CD8
const Collision warp_pipe_seg3_collision_warp_pipe[] = {
    COL_INIT(),
    COL_VERTEX_INIT(0x24),
    COL_VERTEX(-101, 0, 102),
    COL_VERTEX(102, 0, -101),
    COL_VERTEX(-101, 0, -101),
    COL_VERTEX(102, 0, 102),
    COL_VERTEX(0, 0, 154),
    COL_VERTEX(-108, 205, 109),
    COL_VERTEX(-108, 0, 109),
    COL_VERTEX(0, 205, 154),
    COL_VERTEX(-153, 205, 0),
    COL_VERTEX(0, 205, 102),
    COL_VERTEX(-71, 205, 72),
    COL_VERTEX(0, 0, 102),
    COL_VERTEX(72, 205, 72),
    COL_VERTEX(-71, 0, 72),
    COL_VERTEX(109, 205, 109),
    COL_VERTEX(-101, 0, 0),
    COL_VERTEX(-101, 205, 0),
    COL_VERTEX(109, 0, 109),
    COL_VERTEX(-153, 0, 0),
    COL_VERTEX(-108, 205, -108),
    COL_VERTEX(-71, 0, -71),
    COL_VERTEX(-108, 0, -108),
    COL_VERTEX(0, 205, -153),
    COL_VERTEX(0, 0, -101),
    COL_VERTEX(0, 0, -153),
    COL_VERTEX(109, 205, -108),
    COL_VERTEX(72, 0, -71),
    COL_VERTEX(109, 0, -108),
    COL_VERTEX(154, 205, 0),
    COL_VERTEX(102, 0, 0),
    COL_VERTEX(154, 0, 0),
    COL_VERTEX(72, 0, 72),
    COL_VERTEX(-71, 205, -71),
    COL_VERTEX(0, 205, -101),
    COL_VERTEX(72, 205, -71),
    COL_VERTEX(102, 205, 0),

    COL_TRI_INIT(SURFACE_WALL_MISC, 50),
    COL_TRI(14, 12, 9),
    COL_TRI(0, 1, 2),
    COL_TRI(0, 3, 1),
    COL_TRI(4, 5, 6),
    COL_TRI(4, 7, 5),
    COL_TRI(6, 5, 8),
    COL_TRI(5, 9, 10),
    COL_TRI(5, 7, 9),
    COL_TRI(8, 5, 10),
    COL_TRI(11, 9, 12),
    COL_TRI(13, 9, 11),
    COL_TRI(13, 10, 9),
    COL_TRI(14, 9, 7),
    COL_TRI(19, 16, 32),
    COL_TRI(15, 16, 10),
    COL_TRI(8, 10, 16),
    COL_TRI(15, 10, 13),
    COL_TRI(17, 7, 4),
    COL_TRI(17, 14, 7),
    COL_TRI(6, 8, 18),
    COL_TRI(18, 8, 19),
    COL_TRI(19, 8, 16),
    COL_TRI(20, 16, 15),
    COL_TRI(20, 32, 16),
    COL_TRI(28, 25, 34),
    COL_TRI(21, 19, 22),
    COL_TRI(18, 19, 21),
    COL_TRI(22, 19, 32),
    COL_TRI(23, 32, 20),
    COL_TRI(23, 33, 32),
    COL_TRI(22, 32, 33),
    COL_TRI(24, 22, 25),
    COL_TRI(21, 22, 24),
    COL_TRI(25, 22, 33),
    COL_TRI(26, 34, 33),
    COL_TRI(26, 33, 23),
    COL_TRI(25, 33, 34),
    COL_TRI(24, 25, 27),
    COL_TRI(27, 25, 28),
    COL_TRI(30, 14, 17),
    COL_TRI(29, 34, 26),
    COL_TRI(29, 35, 34),
    COL_TRI(28, 34, 35),
    COL_TRI(30, 28, 14),
    COL_TRI(27, 28, 30),
    COL_TRI(28, 12, 14),
    COL_TRI(28, 35, 12),
    COL_TRI(31, 12, 35),
    COL_TRI(31, 35, 29),
    COL_TRI(11, 12, 31),
    COL_TRI_STOP(),
    COL_END(),
};
