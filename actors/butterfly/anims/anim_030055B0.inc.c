// 0x03005538
static const AnimValue butterfly_seg3_animvalue_03005538[] = {
    0x0000, 0x352F, 0x28EE, 0x122D, 0x05EC, 0x0D4E, 0x1D8D, 0x2DCC,
    0x352F, 0x4B1B, 0x569E, 0x6C00, 0x7784, 0x7093, 0x614F, 0x520B,
    0x4B1B, 0x0000,
};

// 0x0300555C
static const AnimIndex butterfly_seg3_animindex_0300555C[] = {
    0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0000,
    0x0001, 0x0000, 0x0001, 0x0000, 0x0008, 0x0001,
    0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0000,
    0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0000,
    0x0001, 0x0000, 0x0001, 0x0000, 0x0008, 0x0009,
    0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0000,
};

// 0x030055B0
static const struct Animation butterfly_seg3_anim_030055B0 = {
    0,
    0,
    7,
    0,
    0x08,
    ANIMINDEX_NUMPARTS(butterfly_seg3_animindex_0300555C),
    butterfly_seg3_animvalue_03005538,
    butterfly_seg3_animindex_0300555C,
    0,
};
