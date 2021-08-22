// 0x0700C7C8 - 0x0700C8F0
static const AnimValue castle_grounds_seg7_animvalue_flags[] = {
        0,   480, 16383,  4835,  3907,  2463,   721, -1101, -2789, -4125, -4928, -5481, -5883, -6121, -6182, -6054,
    -5723, -5177, -4309, -2785,  -812,  1339,  3401,  5102,  6174,  6692,  6939,  6952,  6769,  6428,  5967,  5423,
     3581,  2871,  1610,   109, -1318, -2361, -2855, -3215, -3491, -3677, -3768, -3758, -3642, -3414, -3068, -2526,
    -1519,  -188,  1277,  2685,  3848,  4573,  4906,  5041,  5011,  4851,  4594,  4274,  3925, -3009, -3210, -3342,
    -3401, -3389, -3303, -3143, -2907, -2485, -1816,  -982,   -59,   871,  1731,  2443,  2931,  3205,  3300,  3237,
     3037,  2722,  2296,  1701,   979,   182,  -633, -1414, -2107, -2657, -2628, -2534, -2270, -1862, -1337,  -720,
      -40,   678,  1408,  2089,  2618,  3004,  3257,  3391,  3404,  3140,  2619,  1925,  1144,   361,  -339,  -873,
    -1218, -1535, -1829, -2091, -2312, -2481, -2590,  1258,  1203,  1057,   844,   592,   327,    75,  -137,  -342,
     -573,  -807, -1022, -1195, -1305, -1328, -1243, -1060,  -810,  -524,  -233,    32,   242,   418,   595,   766,
      922,  1058,  1164,  1233,
};

// 0x0700C8F0 - 0x0700C944
static const AnimIndex castle_grounds_seg7_animindex_flags[] = {
    0x0001, 0x0000, 0x0001, 0x0001, 0x0001, 0x0000, 0x0001, 0x0002, 0x0001, 0x0000, 0x0001, 0x0000,
    0x0001, 0x0000, 0x0001, 0x0000, 0x001D, 0x0077,
    0x0001, 0x0000, 0x0001, 0x0000, 0x001D, 0x005A,
    0x0001, 0x0000, 0x0001, 0x0000, 0x001D, 0x003D,
    0x0001, 0x0000, 0x0001, 0x0000, 0x001D, 0x0020,
    0x0001, 0x0000, 0x0001, 0x0000, 0x001D, 0x0003,
};

// 0x0700C944 - 0x0700C95C
static const struct Animation castle_grounds_seg7_anim_flags = {
    0,
    0,
    0,
    0,
    0x1D,
    ANIMINDEX_NUMPARTS(castle_grounds_seg7_animindex_flags),
    castle_grounds_seg7_animvalue_flags,
    castle_grounds_seg7_animindex_flags,
    0,
};

// 0x0700C95C - 0x0700C960
const struct Animation *const castle_grounds_seg7_anims_flags[] = {
    &castle_grounds_seg7_anim_flags, // 0x0700C944
};
