// 0x05002350
static const AnimValue bookend_seg5_animvalue_05002350[] = {
    0x0000, 0xC001, 0x071C, 0x0D90, 0x198B, 0x1FFF, 0x198B, 0x0D90,
    0x0AAA, 0x1032, 0x1A77, 0x1FFF, 0x1A77, 0x1032, 0x3FFF, 0x8001,
};

// 0x05002370
static const AnimIndex bookend_seg5_animindex_05002370[] = {
    0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0001, 0x0001, 0x0000, 0x0001, 0x0000,
    0x0001, 0x0000, 0x0001, 0x0000, 0x0006, 0x0002,
    0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0000,
    0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0000,
    0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0000,
    0x0001, 0x000E, 0x0001, 0x000F, 0x0001, 0x0000,
    0x0001, 0x0000, 0x0001, 0x0000, 0x0006, 0x0008,
    0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0000,
    0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0000,
    0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0000,
};

// 0x050023F4
static const struct Animation bookend_seg5_anim_050023F4 = {
    0,
    0,
    0,
    0,
    0x06,
    ANIMINDEX_NUMPARTS(bookend_seg5_animindex_05002370),
    bookend_seg5_animvalue_05002350,
    bookend_seg5_animindex_05002370,
    0,
};
