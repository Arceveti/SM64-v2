// 0x0600E060
static const AnimValue dorrie_seg6_animvalue_0600E060[] = {
    0x0000, 0xFFF6, 0xFFDA, 0x3FFF, 0x9614, 0xFCCB, 0xFBE7, 0xEE13,
    0xE187, 0x0072, 0x01FC, 0xECD3, 0x1255, 0xE11F, 0xFF89, 0xFE05,
    0xECD3, 0xC001, 0xC9C6, 0xC001, 0xC9C6, 0xEF81, 0xEDE4, 0xC9C6,
    0xC001, 0xC9C6, 0x363A, 0x3FFF, 0xC9C6, 0x363A, 0x3FFF, 0xC9C6,
    0x938B, 0xF41D, 0x6C75, 0x0000,
};

// 0x0600E0A8
static const AnimIndex dorrie_seg6_animindex_0600E0A8[] = {
    0x0001, 0x0000, 0x0001, 0x0001, 0x0001, 0x0002, 0x0001, 0x0000, 0x0001, 0x0003, 0x0001, 0x0000,
    0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0022,
    0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0021,
    0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0016,
    0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0015,
    0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0011,
    0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0004,
    0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0020,
    0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0006,
    0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0005,
    0x0001, 0x001D, 0x0001, 0x001E, 0x0001, 0x001F,
    0x0001, 0x0000, 0x0001, 0x0007, 0x0001, 0x0008,
    0x0001, 0x001A, 0x0001, 0x001B, 0x0001, 0x001C,
    0x0001, 0x0009, 0x0001, 0x000A, 0x0001, 0x000B,
    0x0001, 0x0017, 0x0001, 0x0018, 0x0001, 0x0019,
    0x0001, 0x0000, 0x0001, 0x000C, 0x0001, 0x000D,
    0x0001, 0x0012, 0x0001, 0x0013, 0x0001, 0x0014,
    0x0001, 0x000E, 0x0001, 0x000F, 0x0001, 0x0010,
};

// 0x0600E18C
static const struct Animation dorrie_seg6_anim_0600E18C = {
    0,
    0,
    0,
    0,
    0x3C,
    ANIMINDEX_NUMPARTS(dorrie_seg6_animindex_0600E0A8),
    dorrie_seg6_animvalue_0600E060,
    dorrie_seg6_animindex_0600E0A8,
    0,
};
