// 0x070030A8 - 0x070030C0
static const Lights1 jrb_seg7_lights_070030A8 = gdSPDefLights1(
    0x10, 0x25, 0x1e,
    0x41, 0x96, 0x78, 0x28, 0x28, 0x28
);

// 0x070030C0 - 0x070030D8
static const Lights1 jrb_seg7_lights_070030C0 = gdSPDefLights1(
    0x3f, 0x3f, 0x3f,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x070030D8 - 0x070030F0
static const Lights1 jrb_seg7_lights_070030D8 = gdSPDefLights1(
    0x1e, 0x27, 0x3a,
    0x79, 0x9f, 0xeb, 0x28, 0x28, 0x28
);

// 0x070030F0 - 0x070031F0
static const Vtx jrb_seg7_vertex_070030F0[] = {
    {{{  3093,  -5120,   4015}, 0, {  1220,   2248}, {0x41, 0x63, 0xd5, 0xff}}},
    {{{  4422,  -5120,   4786}, 0, {  2268,   1970}, {0x06, 0x76, 0xd2, 0xff}}},
    {{{  4774,  -5120,   2892}, 0, { 47<<5,    852}, {0x0f, 0x78, 0xdb, 0xff}}},
    {{{  4979,  -5632,   2482}, 0, {  1396,    546}, {0x00, 0x7e, 0x00, 0xff}}},
    {{{  4569,  -5120,   2687}, 0, {  1296,    852}, {0x25, 0x78, 0xf1, 0xff}}},
    {{{  5183,  -5120,   2892}, 0, {  1704,    648}, {0xf1, 0x78, 0xdb, 0xff}}},
    {{{  4569,  -5120,   2277}, 0, {  1088,    648}, {0x25, 0x78, 0x0f, 0xff}}},
    {{{  5388,  -5120,   2277}, 0, { 47<<5,    238}, {0xdb, 0x78, 0x0f, 0xff}}},
    {{{  5388,  -5120,   2687}, 0, {  1704,    448}, {0xdb, 0x78, 0xf1, 0xff}}},
    {{{  4774,  -5120,   2073}, 0, {  1088,    448}, {0x0f, 0x78, 0x25, 0xff}}},
    {{{  5183,  -5120,   2073}, 0, {  1296,    238}, {0xf1, 0x78, 0x25, 0xff}}},
    {{{  2722,  -5120,   2615}, 0, {   336,   1736}, {0x3f, 0x69, 0x1d, 0xff}}},
    {{{  6478,  -5120,   1243}, 0, {  1528,   -822}, {0xab, 0x44, 0x41, 0xff}}},
    {{{  5821,  -5120,   4414}, 0, {  2780,   1086}, {0xc4, 0x60, 0xc9, 0xff}}},
    {{{  3750,  -5120,    844}, 0, {     0,    340}, {0x31, 0x4d, 0x57, 0xff}}},
    {{{  5150,  -5120,    472}, 0, { 15<<5,   -544}, {0xf5, 0x5b, 0x56, 0xff}}},
};

// 0x070031F0 - 0x07003250
static const Vtx jrb_seg7_vertex_070031F0[] = {
    {{{  6849,  -5120,   2643}, 0, {  2412,   -304}, {0xa1, 0x53, 0x0a, 0xff}}},
    {{{  6478,  -5120,   1243}, 0, {  1528,   -822}, {0xab, 0x44, 0x41, 0xff}}},
    {{{  5388,  -5120,   2277}, 0, { 47<<5,    238}, {0xdb, 0x78, 0x0f, 0xff}}},
    {{{  5388,  -5120,   2687}, 0, {  1704,    448}, {0xdb, 0x78, 0xf1, 0xff}}},
    {{{  5821,  -5120,   4414}, 0, {  2780,   1086}, {0xc4, 0x60, 0xc9, 0xff}}},
    {{{  5183,  -5120,   2892}, 0, {  1704,    648}, {0xf1, 0x78, 0xdb, 0xff}}},
};

// 0x07003250 - 0x07003350
static const Vtx jrb_seg7_vertex_07003250[] = {
    {{{  1888,   1024,   6165}, 0, {  1884,   3024}, {0x2a, 0x44, 0x9e, 0xff}}},
    {{{  1879,   -512,   5086}, 0, { 47<<5,  95<<5}, {0x35, 0x54, 0xb3, 0xff}}},
    {{{  1098,   1024,   6104}, 0, {  1884,   3812}, {0x01, 0x53, 0xa1, 0xff}}},
    {{{   294,   -512,   4758}, 0, { 47<<5,   4614}, {0xde, 0x71, 0xd3, 0xff}}},
    {{{  -219,    512,   5643}, 0, {  1756,   5128}, {0xe3, 0x63, 0xb7, 0xff}}},
    {{{   330,   1024,   6232}, 0, {  1884,   4578}, {0xd3, 0x6b, 0xcd, 0xff}}},
    {{{ -1662,  -1024,   3030}, 0, {  1116,   -312}, {0xfc, 0x7b, 0x1b, 0xff}}},
    {{{ -2362,  -1024,   3215}, 0, {   652,   -188}, {0x2d, 0x63, 0x3f, 0xff}}},
    {{{ -2876,  -1024,   4101}, 0, {   312,    400}, {0x43, 0x6b, 0xf9, 0xff}}},
    {{{  -777,  -1024,   3544}, 0, {  1708,     32}, {0xd4, 0x66, 0x3b, 0xff}}},
    {{{ -1848,      0,   2330}, 0, { 31<<5,   -778}, {0xfb, 0x6d, 0x40, 0xff}}},
    {{{ -2690,  -1024,   4801}, 0, {   432,    864}, {0x35, 0x6b, 0xd7, 0xff}}},
    {{{ -1805,  -1024,   5315}, 0, {  1024,   1206}, {0x16, 0x60, 0xb1, 0xff}}},
    {{{ -1105,  -1024,   5129}, 0, {  1488,   1082}, {0xe2, 0x67, 0xbd, 0xff}}},
    {{{ -3762,      0,   3587}, 0, {  -276,     58}, {0x2b, 0x77, 0xf9, 0xff}}},
    {{{ -3390,    512,   4987}, 0, {     0,  31<<5}, {0x39, 0x61, 0xc8, 0xff}}},
};

// 0x07003350 - 0x07003450
static const Vtx jrb_seg7_vertex_07003350[] = {
    {{{ -1105,  -1024,   5129}, 0, {  1488,   1082}, {0xe2, 0x67, 0xbd, 0xff}}},
    {{{  -219,    512,   5643}, 0, {  2080,   1424}, {0xe3, 0x63, 0xb7, 0xff}}},
    {{{   294,   -512,   4758}, 0, {  2420,    838}, {0xde, 0x71, 0xd3, 0xff}}},
    {{{  -591,  -1024,   4244}, 0, {  1832,    496}, {0xd8, 0x78, 0x01, 0xff}}},
    {{{ -1662,  -1024,   3030}, 0, {  1116,   -312}, {0xfc, 0x7b, 0x1b, 0xff}}},
    {{{ -1619,    512,   6015}, 0, {  1148,   1672}, {0x00, 0x6c, 0xbe, 0xff}}},
    {{{ -1805,  -1024,   5315}, 0, {  1024,   1206}, {0x16, 0x60, 0xb1, 0xff}}},
    {{{   -77,   -512,   3358}, 0, {  2172,    -94}, {0xf2, 0x7a, 0x1d, 0xff}}},
    {{{  -777,  -1024,   3544}, 0, {  1708,     30}, {0xd4, 0x66, 0x3b, 0xff}}},
    {{{ -3390,    512,   4987}, 0, {     0,  31<<5}, {0x39, 0x61, 0xc8, 0xff}}},
    {{{ -2690,  -1024,   4801}, 0, {   432,    864}, {0x35, 0x6b, 0xd7, 0xff}}},
    {{{ -2876,  -1024,   4101}, 0, {   312,    400}, {0x43, 0x6b, 0xf9, 0xff}}},
    {{{ -3762,      0,   3587}, 0, {  -276,     58}, {0x2b, 0x77, 0xf9, 0xff}}},
    {{{ -2362,  -1024,   3215}, 0, {   652,   -188}, {0x2d, 0x63, 0x3f, 0xff}}},
    {{{ -4133,      0,   2187}, 0, {  -524,   -872}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{ -3248,      0,   2701}, 0, {    64,   -530}, {0x1d, 0x74, 0x28, 0xff}}},
};

// 0x07003450 - 0x07003540
static const Vtx jrb_seg7_vertex_07003450[] = {
    {{{ -1848,      0,   2330}, 0, { 31<<5,   -778}, {0xfb, 0x6d, 0x40, 0xff}}},
    {{{ -3248,      0,   2701}, 0, {    64,   -530}, {0x1d, 0x74, 0x28, 0xff}}},
    {{{ -2362,  -1024,   3215}, 0, {   652,   -188}, {0x2d, 0x63, 0x3f, 0xff}}},
    {{{ -1619,    512,   6015}, 0, {  1148,   1672}, {0x00, 0x6c, 0xbe, 0xff}}},
    {{{ -3390,    512,   4987}, 0, {     0,  31<<5}, {0x39, 0x61, 0xc8, 0xff}}},
    {{{ -4161,    512,   6315}, 0, {  -540,   1872}, {0x1a, 0x69, 0xbf, 0xff}}},
    {{{ -5256,    512,   4733}, 0, { -1268,    820}, {0x04, 0x7b, 0xe2, 0xff}}},
    {{{ -3762,      0,   3587}, 0, {  -276,     58}, {0x2b, 0x77, 0xf9, 0xff}}},
    {{{  -219,    512,   5643}, 0, {  2080,   1424}, {0xe3, 0x63, 0xb7, 0xff}}},
    {{{  -805,    512,   7672}, 0, {  1688,   2774}, {0xea, 0x67, 0xbb, 0xff}}},
    {{{  -777,  -1024,   3544}, 0, {  1708,     32}, {0xd4, 0x66, 0x3b, 0xff}}},
    {{{   -77,   -512,   3358}, 0, {  2172,    -96}, {0xf2, 0x7a, 0x1d, 0xff}}},
    {{{  -705,      0,   2401}, 0, {  1756,   -730}, {0x14, 0x6b, 0x40, 0xff}}},
    {{{ -4133,      0,   2187}, 0, {  -524,   -872}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{ -2771,      0,   1676}, 0, {   380,  -1212}, {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x07003540 - 0x07003640
static const Vtx jrb_seg7_vertex_07003540[] = {
    {{{ -2771,    614,   1676}, 0, {  2536,    120}, {0x03, 0x7a, 0x20, 0xff}}},
    {{{  -705,    512,   2401}, 0, {  4600,    844}, {0xdb, 0x60, 0x49, 0xff}}},
    {{{ -3747,   1024,    256}, 0, {  1564,  -1296}, {0xfe, 0x79, 0x25, 0xff}}},
    {{{  1879,   -512,   5086}, 0, {  3476,  33<<5}, {0x35, 0x54, 0xb3, 0xff}}},
    {{{   -77,   -512,   3358}, 0, {  2172,    -96}, {0xf2, 0x7a, 0x1d, 0xff}}},
    {{{   294,   -512,   4758}, 0, {  2420,    838}, {0xde, 0x71, 0xd3, 0xff}}},
    {{{  1136,  -1024,   2287}, 0, {  2980,   -806}, {0x57, 0x3e, 0x43, 0xff}}},
    {{{  -705,      0,   2401}, 0, {  1756,   -730}, {0x14, 0x6b, 0x40, 0xff}}},
    {{{ -4133,      0,   2187}, 0, {  -524,   -872}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{ -5170,      0,   3362}, 0, { -1212,    -96}, {0x03, 0x7c, 0xea, 0xff}}},
    {{{ -3762,      0,   3587}, 0, {  -276,     58}, {0x2b, 0x77, 0xf9, 0xff}}},
    {{{ -5256,    512,   4733}, 0, { -1268,    820}, {0x04, 0x7b, 0xe2, 0xff}}},
    {{{ -4307,   1024,    405}, 0, {  1004,  -1146}, {0x09, 0x7b, 0x1c, 0xff}}},
    {{{ -4133,    614,   2187}, 0, {  1176,    632}, {0x11, 0x7b, 0x17, 0xff}}},
    {{{ -5345,   1024,   1011}, 0, {     0,   -544}, {0x15, 0x7b, 0x14, 0xff}}},
    {{{ -5756,   1024,   1719}, 0, {  -440,    164}, {0x19, 0x7a, 0x13, 0xff}}},
};

// 0x07003640 - 0x07003700
static const Vtx jrb_seg7_vertex_07003640[] = {
    {{{ -5170,    614,   3362}, 0, {   144,   1802}, {0x23, 0x79, 0x03, 0xff}}},
    {{{ -4133,    614,   2187}, 0, {  1176,    632}, {0x11, 0x7b, 0x17, 0xff}}},
    {{{ -5756,   1024,   1719}, 0, {  -440,    160}, {0x19, 0x7a, 0x13, 0xff}}},
    {{{ -4579,   1024,    508}, 0, {   732,  -1044}, {0x0d, 0x7b, 0x1a, 0xff}}},
    {{{ -5345,   1024,   1011}, 0, {     0,   -544}, {0x15, 0x7b, 0x14, 0xff}}},
    {{{ -4307,   1024,    405}, 0, {  1004,  -1146}, {0x09, 0x7b, 0x1c, 0xff}}},
    {{{ -5963,   1024,   1954}, 0, {  -644,    400}, {0x27, 0x78, 0x0c, 0xff}}},
    {{{ -6077,   1024,   3782}, 0, {  -760,   2222}, {0x2e, 0x75, 0xf2, 0xff}}},
    {{{ -5256,   1024,   4733}, 0, {    56,   3170}, {0x25, 0x74, 0xe0, 0xff}}},
    {{{  -705,    512,   2401}, 0, {  4600,    848}, {0xdb, 0x60, 0x49, 0xff}}},
    {{{ -3443,   1024,    320}, 0, {  1864,  -1234}, {0xcc, 0x4a, 0x57, 0xff}}},
    {{{ -3747,   1024,    256}, 0, {  1564,  -1296}, {0xfe, 0x79, 0x25, 0xff}}},
};

// 0x07003700 - 0x07003800
static const Vtx jrb_seg7_vertex_07003700[] = {
    {{{   728,   -630,   3571}, 0, { 63<<5,  31<<5}, {0x20, 0x09, 0x7a, 0xff}}},
    {{{   696,   1024,   3452}, 0, {  1604,   -662}, {0x20, 0x09, 0x7a, 0xff}}},
    {{{   519,   1024,   3349}, 0, {  1120,   -662}, {0x97, 0x08, 0x45, 0xff}}},
    {{{   800,   1024,   3275}, 0, {  1120,   -662}, {0x7a, 0x09, 0xe0, 0xff}}},
    {{{   589,   -726,   3046}, 0, {   208,   1084}, {0x07, 0x08, 0x82, 0xff}}},
    {{{   622,   1024,   3172}, 0, {   640,   -662}, {0xbb, 0x08, 0x97, 0xff}}},
    {{{   927,   -751,   3241}, 0, {  1120,   1108}, {0x7a, 0x09, 0xe0, 0xff}}},
    {{{   402,   -607,   3381}, 0, {  1120,    966}, {0x82, 0x08, 0xf9, 0xff}}},
    {{{   225,   -595,   2823}, 0, { -1112,    872}, {0x6d, 0x07, 0x3f, 0xff}}},
    {{{     2,   1024,   2812}, 0, {  -600,   -744}, {0xe7, 0x07, 0x7c, 0xff}}},
    {{{   -40,   -455,   2888}, 0, {  -164,  23<<5}, {0xa1, 0x07, 0x53, 0xff}}},
    {{{   150,   -509,   2557}, 0, { -2072,    788}, {0x3f, 0x07, 0x93, 0xff}}},
    {{{   105,   1024,   2635}, 0, { -1624,   -744}, {0x3f, 0x07, 0x93, 0xff}}},
    {{{  -105,   -376,   2631}, 0, { -1112,    654}, {0xac, 0x07, 0xa2, 0xff}}},
    {{{   -34,   1024,   2672}, 0, { -1112,   -744}, {0x84, 0x06, 0xe6, 0xff}}},
    {{{   142,   1024,   2775}, 0, { -1112,   -744}, {0x6d, 0x07, 0x3f, 0xff}}},
};

// 0x07003800 - 0x070038F0
static const Vtx jrb_seg7_vertex_07003800[] = {
    {{{ -3928,    922,   2443}, 0, { 63<<5,  -3610}, {0x57, 0x26, 0x54, 0xff}}},
    {{{ -3928,      0,   2443}, 0, { 63<<5,  31<<5}, {0x38, 0x00, 0x71, 0xff}}},
    {{{ -3928,      0,   1829}, 0, {     0,  31<<5}, {0x71, 0x00, 0xc8, 0xff}}},
    {{{  1252,   -664,   3893}, 0, {   928,    944}, {0x53, 0x07, 0x5f, 0xff}}},
    {{{  1166,   1024,   3843}, 0, {   928,   -744}, {0x7c, 0x07, 0x19, 0xff}}},
    {{{  1043,   1024,   3876}, 0, {  1380,   -744}, {0xc1, 0x07, 0x6d, 0xff}}},
    {{{  1185,   -712,   3631}, 0, {     0,  31<<5}, {0x5f, 0x07, 0xad, 0xff}}},
    {{{  1133,   1024,   3720}, 0, { 15<<5,   -744}, {0x19, 0x07, 0x84, 0xff}}},
    {{{   925,   -640,   3703}, 0, {   928,    918}, {0x93, 0x07, 0xc1, 0xff}}},
    {{{  1010,   1024,   3752}, 0, {   928,   -744}, {0x93, 0x07, 0xc1, 0xff}}},
    {{{   995,   -594,   3958}, 0, {  1856,    872}, {0xc1, 0x07, 0x6d, 0xff}}},
    {{{ -3928,    922,   1829}, 0, { 63<<5,  -3608}, {0x54, 0x26, 0xa9, 0xff}}},
    {{{ -4543,      0,   1829}, 0, { -1048,  31<<5}, {0xc8, 0x00, 0x8f, 0xff}}},
    {{{ -4543,    922,   1829}, 0, { -1056,  -3608}, {0xa9, 0x26, 0xac, 0xff}}},
    {{{ -3928,    922,   1829}, 0, {     0,  -3610}, {0x54, 0x26, 0xa9, 0xff}}},
};

// 0x070038F0 - 0x070039E0
static const Vtx jrb_seg7_vertex_070038F0[] = {
    {{{ -4543,    922,   1829}, 0, {     0,  -3610}, {0xa9, 0x26, 0xac, 0xff}}},
    {{{ -4543,      0,   1829}, 0, {     0,  31<<5}, {0xc8, 0x00, 0x8f, 0xff}}},
    {{{ -4543,      0,   2443}, 0, { 63<<5,  31<<5}, {0x8f, 0x00, 0x38, 0xff}}},
    {{{ -4543,    922,   2443}, 0, { 63<<5,  -3610}, {0xac, 0x26, 0x57, 0xff}}},
    {{{ -4543,    922,   2443}, 0, { -1056,  -3608}, {0xac, 0x26, 0x57, 0xff}}},
    {{{ -3928,      0,   2443}, 0, { 63<<5,  31<<5}, {0x38, 0x00, 0x71, 0xff}}},
    {{{ -3928,    922,   2443}, 0, { 63<<5,  -3608}, {0x57, 0x26, 0x54, 0xff}}},
    {{{ -4543,      0,   2443}, 0, { -1048,  31<<5}, {0x8f, 0x00, 0x38, 0xff}}},
    {{{ -3928,    922,   1829}, 0, { 63<<5,  -3608}, {0x54, 0x26, 0xa9, 0xff}}},
    {{{ -3928,      0,   1829}, 0, { 63<<5,  31<<5}, {0x71, 0x00, 0xc8, 0xff}}},
    {{{ -4543,      0,   1829}, 0, { -1048,  31<<5}, {0xc8, 0x00, 0x8f, 0xff}}},
    {{{ -3976,   1024,   1877}, 0, {  1772,  -4120}, {0x30, 0x43, 0xa0, 0xff}}},
    {{{ -4543,    922,   1829}, 0, { -1056,  -3608}, {0xa9, 0x26, 0xac, 0xff}}},
    {{{ -4495,   1024,   2395}, 0, {  -812,  -4120}, {0xd0, 0x43, 0x60, 0xff}}},
    {{{ -3976,   1024,   2395}, 0, {  1772,  -4120}, {0x60, 0x43, 0x30, 0xff}}},
};

// 0x070039E0 - 0x07003A90
static const Vtx jrb_seg7_vertex_070039E0[] = {
    {{{ -3928,    922,   1829}, 0, {     0,  -3610}, {0x54, 0x26, 0xa9, 0xff}}},
    {{{ -3976,   1024,   1877}, 0, {   128,  -4120}, {0x30, 0x43, 0xa0, 0xff}}},
    {{{ -3976,   1024,   2395}, 0, {  1852,  -4120}, {0x60, 0x43, 0x30, 0xff}}},
    {{{ -3928,    922,   2443}, 0, { 63<<5,  -3610}, {0x57, 0x26, 0x54, 0xff}}},
    {{{ -4495,   1024,   1877}, 0, {   128,  -4120}, {0xa0, 0x43, 0xd0, 0xff}}},
    {{{ -4543,    922,   2443}, 0, { 63<<5,  -3610}, {0xac, 0x26, 0x57, 0xff}}},
    {{{ -4495,   1024,   2395}, 0, {  1852,  -4120}, {0xd0, 0x43, 0x60, 0xff}}},
    {{{ -4543,    922,   1829}, 0, {     0,  -3610}, {0xa9, 0x26, 0xac, 0xff}}},
    {{{ -3976,   1024,   1877}, 0, {  1772,  -4120}, {0x30, 0x43, 0xa0, 0xff}}},
    {{{ -4543,    922,   1829}, 0, { -1056,  -3608}, {0xa9, 0x26, 0xac, 0xff}}},
    {{{ -4495,   1024,   1877}, 0, {  -816,  -4120}, {0xa0, 0x43, 0xd0, 0xff}}},
};

// 0x07003A90 - 0x07003B10
static const Vtx jrb_seg7_vertex_07003A90[] = {
    {{{ -2585,    512,   6165}, 0, {   780,   1090}, {0xc8, 0x05, 0x71, 0xff}}},
    {{{ -2483,    512,   6165}, 0, {  1264,   1090}, {0x71, 0x05, 0x38, 0xff}}},
    {{{ -2500,   1024,   6148}, 0, {  1444,    582}, {0x38, 0x05, 0x71, 0xff}}},
    {{{ -2500,   1024,   6080}, 0, {  1120,    582}, {0x71, 0x05, 0xc8, 0xff}}},
    {{{ -2483,    512,   6062}, 0, {   780,   1090}, {0x38, 0x05, 0x8f, 0xff}}},
    {{{ -2568,   1024,   6080}, 0, {   800,    582}, {0xc8, 0x05, 0x8f, 0xff}}},
    {{{ -2585,    512,   6062}, 0, {   300,   1090}, {0x8f, 0x05, 0xc8, 0xff}}},
    {{{ -2568,   1024,   6148}, 0, {  1120,    582}, {0x8f, 0x05, 0x38, 0xff}}},
};

// 0x07003B10 - 0x07003C10
static const Vtx jrb_seg7_vertex_07003B10[] = {
    {{{  7030,  -3325,   1838}, 0, {   564,   1274}, {0x88, 0x1a, 0x1f, 0xff}}},
    {{{  7092,  -3022,   1822}, 0, {   664,   1290}, {0x88, 0x1a, 0x1f, 0xff}}},
    {{{  7435,      0,    614}, 0, {  1672,    496}, {0x9d, 0x13, 0x4c, 0xff}}},
    {{{  6478,  -5120,   1243}, 0, {     0,    558}, {0xab, 0x44, 0x41, 0xff}}},
    {{{  7038,  -3476,   1995}, 0, { 16<<5,   1400}, {0x88, 0x1a, 0x1f, 0xff}}},
    {{{  7168,  -2871,   1962}, 0, {   720,   1432}, {0x88, 0x1a, 0x1f, 0xff}}},
    {{{  7992,      0,   2714}, 0, {  1672,   2398}, {0x83, 0x13, 0x01, 0xff}}},
    {{{  5662,  -4096,    533}, 0, {   304,   -372}, {0xc2, 0x18, 0x6b, 0xff}}},
    {{{  5221,      0,   -669}, 0, {  1672,  -1516}, {0xf7, 0x0f, 0x7d, 0xff}}},
    {{{  5457,  -3890,    366}, 0, {   376,   -594}, {0xc2, 0x18, 0x6b, 0xff}}},
    {{{  5221,   1024,   -669}, 0, { 63<<5,  -1516}, {0xdf, 0x00, 0x7a, 0xff}}},
    {{{  7435,   1024,    614}, 0, { 63<<5,    496}, {0x92, 0x00, 0x3e, 0xff}}},
    {{{  7117,  -3476,   2292}, 0, {   516,   1670}, {0x88, 0x1a, 0x1f, 0xff}}},
    {{{  6849,  -5120,   2643}, 0, {     0,   1824}, {0xa1, 0x53, 0x0a, 0xff}}},
    {{{  5662,  -4709,    675}, 0, {   104,   -260}, {0xc2, 0x18, 0x6b, 0xff}}},
    {{{  7187,  -3325,   2432}, 0, {   564,   1812}, {0x88, 0x1a, 0x1e, 0xff}}},
};

// 0x07003C10 - 0x07003D10
static const Vtx jrb_seg7_vertex_07003C10[] = {
    {{{  7249,  -3022,   2416}, 0, {   664,   1828}, {0x88, 0x1a, 0x1f, 0xff}}},
    {{{  6849,  -5120,   2643}, 0, {     0,   1824}, {0xa1, 0x53, 0x0a, 0xff}}},
    {{{  7992,      0,   2714}, 0, {  1672,   2398}, {0x83, 0x13, 0x01, 0xff}}},
    {{{  7187,  -3325,   2432}, 0, {   564,   1812}, {0x88, 0x1a, 0x1e, 0xff}}},
    {{{  7241,  -2871,   2259}, 0, {   720,   1700}, {0x88, 0x1a, 0x1f, 0xff}}},
    {{{  7168,  -2871,   1962}, 0, {   720,   1432}, {0x88, 0x1a, 0x1f, 0xff}}},
    {{{  7435,   1024,    614}, 0, { 63<<5,    496}, {0x92, 0x00, 0x3e, 0xff}}},
    {{{  7992,   1024,   2714}, 0, { 63<<5,   2398}, {0x86, 0x00, 0xdf, 0xff}}},
    {{{  -805,    512,   7672}, 0, {  1840,  -8672}, {0xea, 0x67, 0xbb, 0xff}}},
    {{{  -805,   1024,   7672}, 0, { 63<<5,  -8672}, {0x22, 0x00, 0x86, 0xff}}},
    {{{  -210,   1024,   7709}, 0, { 63<<5,  -8162}, {0xd4, 0x3b, 0x9a, 0xff}}},
    {{{ -4161,    512,   6315}, 0, {  1840, -11024}, {0x1a, 0x69, 0xbf, 0xff}}},
    {{{ -3443,   1024,    320}, 0, { 63<<5,  -9448}, {0xcc, 0x4a, 0x57, 0xff}}},
    {{{  -705,    512,   2401}, 0, {  1840,  -6164}, {0xdb, 0x60, 0x49, 0xff}}},
    {{{  -705,   1024,   2401}, 0, { 63<<5,  -6164}, {0xeb, 0x00, 0x7d, 0xff}}},
    {{{ -4161,   1024,   6315}, 0, { 63<<5, -11024}, {0x2f, 0x00, 0x8b, 0xff}}},
};

// 0x07003D10 - 0x07003E00
static const Vtx jrb_seg7_vertex_07003D10[] = {
    {{{  4279,   1024,   7071}, 0, { 63<<5,  -3890}, {0xc5, 0x00, 0x91, 0xff}}},
    {{{  4279,  -1536,   7071}, 0, {  1160,  -3890}, {0x00, 0x29, 0x88, 0xff}}},
    {{{  3190,   1024,   7360}, 0, { 63<<5,  -4988}, {0x1f, 0x1b, 0x89, 0xff}}},
    {{{  6707,   1024,   4928}, 0, { 63<<5,   -756}, {0xa3, 0x00, 0xab, 0xff}}},
    {{{  6707,  -1024,   4928}, 0, {  1332,   -756}, {0x9a, 0x0c, 0xb6, 0xff}}},
    {{{  5821,  -5120,   4414}, 0, {     0,  -1304}, {0xc4, 0x60, 0xc9, 0xff}}},
    {{{  4422,  -5120,   4786}, 0, {     0,  -2716}, {0x06, 0x76, 0xd2, 0xff}}},
    {{{  5221,      0,   -669}, 0, {  1672,  -1516}, {0xf7, 0x0f, 0x7d, 0xff}}},
    {{{  5167,  -3890,    198}, 0, {   376,   -864}, {0xf0, 0x1b, 0x7a, 0xff}}},
    {{{  5457,  -3890,    366}, 0, {   376,   -594}, {0xc2, 0x18, 0x6b, 0xff}}},
    {{{  4842,  -3890,    284}, 0, {   376,   -276}, {0x1f, 0x1a, 0x78, 0xff}}},
    {{{  5221,      0,   -669}, 0, {  1672,    496}, {0xf7, 0x0f, 0x7d, 0xff}}},
    {{{  3121,      0,   -112}, 0, {  1672,  -1618}, {0x46, 0x10, 0x68, 0xff}}},
    {{{  4638,  -4096,    384}, 0, {   304,   -502}, {0x1f, 0x1a, 0x78, 0xff}}},
    {{{  5167,  -3890,    198}, 0, {   376,     48}, {0xf0, 0x1b, 0x7a, 0xff}}},
};

// 0x07003E00 - 0x07003EF0
static const Vtx jrb_seg7_vertex_07003E00[] = {
    {{{  3121,   1024,   -112}, 0, { 63<<5,  -1618}, {0x3e, 0x00, 0x6e, 0xff}}},
    {{{  5221,      0,   -669}, 0, {  1672,    496}, {0xf7, 0x0f, 0x7d, 0xff}}},
    {{{  5221,   1024,   -669}, 0, { 63<<5,    496}, {0xdf, 0x00, 0x7a, 0xff}}},
    {{{  3121,      0,   -112}, 0, {  1672,  -1618}, {0x46, 0x10, 0x68, 0xff}}},
    {{{  3750,  -5120,    844}, 0, {     0,  -1500}, {0x31, 0x4d, 0x57, 0xff}}},
    {{{  4638,  -4096,    384}, 0, {   304,   -502}, {0x1f, 0x1a, 0x78, 0xff}}},
    {{{  4638,  -4709,    518}, 0, {   104,   -564}, {0x1f, 0x1a, 0x78, 0xff}}},
    {{{  5150,  -5120,    472}, 0, {     0,    -90}, {0xf5, 0x5b, 0x56, 0xff}}},
    {{{  4842,  -4914,    509}, 0, {    32,   -378}, {0x1f, 0x1a, 0x78, 0xff}}},
    {{{  7992,      0,   2714}, 0, {  1672,   1398}, {0x83, 0x13, 0x01, 0xff}}},
    {{{  5821,  -5120,   4414}, 0, {     0,  -1304}, {0xc4, 0x60, 0xc9, 0xff}}},
    {{{  6707,  -1024,   4928}, 0, {  1332,   -756}, {0x9a, 0x0c, 0xb6, 0xff}}},
    {{{  6478,  -5120,   1243}, 0, {     0,    558}, {0xab, 0x44, 0x41, 0xff}}},
    {{{  5662,  -4709,    675}, 0, {   104,   -256}, {0xc2, 0x18, 0x6b, 0xff}}},
    {{{  5457,  -4914,    603}, 0, {    32,   -408}, {0xc2, 0x18, 0x6b, 0xff}}},
};

// 0x07003EF0 - 0x07003FD0
static const Vtx jrb_seg7_vertex_07003EF0[] = {
    {{{  2350,      0,   1215}, 0, {  1672,    236}, {0x5f, 0x0e, 0x52, 0xff}}},
    {{{  2722,  -5120,   2615}, 0, {     0,   -304}, {0x3f, 0x69, 0x1d, 0xff}}},
    {{{  3750,  -5120,    844}, 0, {     0,   1010}, {0x31, 0x4d, 0x57, 0xff}}},
    {{{  1136,  -1024,   2287}, 0, {  1332,   -850}, {0x57, 0x3e, 0x43, 0xff}}},
    {{{  3121,      0,   -112}, 0, {  1672,   1222}, {0x46, 0x10, 0x68, 0xff}}},
    {{{  7992,   1024,   2714}, 0, { 63<<5,   1398}, {0x86, 0x00, 0xdf, 0xff}}},
    {{{  7992,      0,   2714}, 0, {  1672,   1398}, {0x83, 0x13, 0x01, 0xff}}},
    {{{  6707,  -1024,   4928}, 0, {  1332,   -756}, {0x9a, 0x0c, 0xb6, 0xff}}},
    {{{  6707,   1024,   4928}, 0, { 63<<5,   -756}, {0xa3, 0x00, 0xab, 0xff}}},
    {{{  6478,  -5120,   1243}, 0, {     0,    558}, {0xab, 0x44, 0x41, 0xff}}},
    {{{  5457,  -4914,    603}, 0, {    36,   -408}, {0xc2, 0x18, 0x6b, 0xff}}},
    {{{  5150,  -5120,    472}, 0, {     0,   -656}, {0xf5, 0x5b, 0x56, 0xff}}},
    {{{  6849,  -5120,   2643}, 0, {     0,    420}, {0xa1, 0x53, 0x0a, 0xff}}},
    {{{  5821,  -5120,   4414}, 0, {     0,  -1304}, {0xc4, 0x60, 0xc9, 0xff}}},
};

// 0x07003FD0 - 0x070040C0
static const Vtx jrb_seg7_vertex_07003FD0[] = {
    {{{  2863,   1024,   7010}, 0, { 63<<5,  -1176}, {0x52, 0x32, 0xae, 0xff}}},
    {{{  3190,   1024,   7360}, 0, { 63<<5,  -1642}, {0x1f, 0x1b, 0x89, 0xff}}},
    {{{  4279,  -1536,   7071}, 0, {  1160,  -1936}, {0x00, 0x29, 0x88, 0xff}}},
    {{{  1879,   -512,   5086}, 0, { 47<<5,    978}, {0x35, 0x54, 0xb3, 0xff}}},
    {{{  3093,  -5120,   4015}, 0, {     0,   1296}, {0x41, 0x63, 0xd5, 0xff}}},
    {{{  4422,  -5120,   4786}, 0, {     0,      0}, {0x06, 0x76, 0xd2, 0xff}}},
    {{{  1136,  -1024,   2287}, 0, {  1332,   3766}, {0x57, 0x3e, 0x43, 0xff}}},
    {{{  2722,  -5120,   2615}, 0, {     0,   2690}, {0x3f, 0x69, 0x1d, 0xff}}},
    {{{  1888,   1024,   6165}, 0, { 63<<5,     40}, {0x2a, 0x44, 0x9e, 0xff}}},
    {{{  -705,   1024,   2401}, 0, { 63<<5,  -6164}, {0xeb, 0x00, 0x7d, 0xff}}},
    {{{  1136,  -1024,   2287}, 0, {  1332,  -4478}, {0x57, 0x3e, 0x43, 0xff}}},
    {{{  1136,   1024,   2287}, 0, { 63<<5,  -4478}, {0x3d, 0x00, 0x6f, 0xff}}},
    {{{  5457,  -4914,    603}, 0, {    32,   -400}, {0xc2, 0x18, 0x6b, 0xff}}},
    {{{  5152,  -4914,    427}, 0, {    32,   -686}, {0xf0, 0x1b, 0x7a, 0xff}}},
    {{{  5150,  -5120,    472}, 0, {     0,   -656}, {0xf5, 0x5b, 0x56, 0xff}}},
};

// 0x070040C0 - 0x070041C0
static const Vtx jrb_seg7_vertex_070040C0[] = {
    {{{  5150,  -5120,    472}, 0, {     0,    -96}, {0xf5, 0x5b, 0x56, 0xff}}},
    {{{  5152,  -4914,    427}, 0, {    32,    -64}, {0xf0, 0x1b, 0x7a, 0xff}}},
    {{{  4842,  -4914,    509}, 0, {    32,   -378}, {0x1f, 0x1a, 0x78, 0xff}}},
    {{{  1136,   1024,   2287}, 0, { 63<<5,   -828}, {0x3d, 0x00, 0x6f, 0xff}}},
    {{{  2350,      0,   1215}, 0, {  1672,    236}, {0x5f, 0x0e, 0x52, 0xff}}},
    {{{  2350,   1024,   1215}, 0, { 63<<5,    248}, {0x66, 0x00, 0x4b, 0xff}}},
    {{{  3121,      0,   -112}, 0, {  1672,   1222}, {0x46, 0x10, 0x68, 0xff}}},
    {{{  3121,   1024,   -112}, 0, { 63<<5,   1234}, {0x3e, 0x00, 0x6e, 0xff}}},
    {{{  1136,  -1024,   2287}, 0, {  1332,   -848}, {0x57, 0x3e, 0x43, 0xff}}},
    {{{  -705,   1024,   2401}, 0, { 63<<5,  -6164}, {0xeb, 0x00, 0x7d, 0xff}}},
    {{{  -705,      0,   2401}, 0, {  1672,  -6164}, {0x14, 0x6b, 0x40, 0xff}}},
    {{{  1136,  -1024,   2287}, 0, {  1332,  -4478}, {0x57, 0x3e, 0x43, 0xff}}},
    {{{  -219,    512,   5643}, 0, {  1840,  -7222}, {0xe3, 0x63, 0xb7, 0xff}}},
    {{{  -805,    512,   7672}, 0, {  1840,  -8672}, {0xea, 0x67, 0xbb, 0xff}}},
    {{{   112,   1024,   6993}, 0, { 63<<5,  -7548}, {0xb6, 0x63, 0xe7, 0xff}}},
    {{{   330,   1024,   6232}, 0, { 63<<5,  -7004}, {0xd3, 0x6b, 0xcd, 0xff}}},
};

// 0x070041C0 - 0x070041F0
static const Vtx jrb_seg7_vertex_070041C0[] = {
    {{{  -805,    512,   7672}, 0, {  1840,  -8672}, {0xea, 0x67, 0xbb, 0xff}}},
    {{{  -210,   1024,   7709}, 0, { 63<<5,  -8162}, {0xd4, 0x3b, 0x9a, 0xff}}},
    {{{   112,   1024,   6993}, 0, { 63<<5,  -7548}, {0xb6, 0x63, 0xe7, 0xff}}},
};

// 0x070041F0 - 0x070044C8
static const Gfx jrb_seg7_dl_070041F0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_09003800_wall),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&jrb_seg7_lights_070030A8.l, 1),
    gsSPLight(&jrb_seg7_lights_070030A8.a, 2),
    gsSPVertex(jrb_seg7_vertex_070030F0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  2,  3,  4, 0x0),
    gsSP2Triangles( 5,  3,  2, 0x0,  4,  3,  6, 0x0),
    gsSP2Triangles( 7,  3,  8, 0x0,  6,  3,  9, 0x0),
    gsSP2Triangles( 8,  3,  5, 0x0,  9,  3, 10, 0x0),
    gsSP2Triangles( 3,  7, 10, 0x0, 11,  0,  4, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0, 12, 10,  7, 0x0),
    gsSP2Triangles(13,  5,  1, 0x0,  5,  2,  1, 0x0),
    gsSP2Triangles(11,  4,  6, 0x0, 14, 11,  6, 0x0),
    gsSP2Triangles(14,  6,  9, 0x0, 15, 14,  9, 0x0),
    gsSP2Triangles(15,  9, 10, 0x0, 12, 15, 10, 0x0),
    gsSPVertex(jrb_seg7_vertex_070031F0, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  0,  3, 0x0,  4,  3,  5, 0x0),
    gsSPLight(&jrb_seg7_lights_070030C0.l, 1),
    gsSPLight(&jrb_seg7_lights_070030C0.a, 2),
    gsSPVertex(jrb_seg7_vertex_07003250, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 1,  4,  2, 0x0,  2,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9, 10, 0x0),
    gsSP2Triangles( 6,  8, 11, 0x0,  6, 11, 12, 0x0),
    gsSP2Triangles( 6, 12, 13, 0x0,  6, 10,  7, 0x0),
    gsSP1Triangle( 8, 14, 15, 0x0),
    gsSPVertex(jrb_seg7_vertex_07003350, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  0,  3, 0x0,  0,  5,  1, 0x0),
    gsSP2Triangles( 0,  6,  5, 0x0,  7,  3,  2, 0x0),
    gsSP2Triangles( 4,  3,  8, 0x0,  7,  8,  3, 0x0),
    gsSP2Triangles( 9,  6, 10, 0x0,  9,  5,  6, 0x0),
    gsSP2Triangles(10, 11,  9, 0x0, 12, 11, 13, 0x0),
    gsSP2Triangles(14, 12, 15, 0x0, 12, 13, 15, 0x0),
    gsSPVertex(jrb_seg7_vertex_07003450, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  5,  4, 0x0,  6,  4,  7, 0x0),
    gsSP2Triangles( 8,  3,  9, 0x0,  3,  5,  9, 0x0),
    gsSP2Triangles(10, 11,  0, 0x0, 12,  0, 11, 0x0),
    gsSP2Triangles(13,  1,  0, 0x0, 14, 13,  0, 0x0),
    gsSP1Triangle(12, 14,  0, 0x0),
    gsSPVertex(jrb_seg7_vertex_07003540, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  6,  7,  4, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9, 11, 10, 0x0),
    gsSP2Triangles( 0,  2, 12, 0x0, 13,  0, 12, 0x0),
    gsSP1Triangle(13, 14, 15, 0x0),
    gsSPVertex(jrb_seg7_vertex_07003640, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  4, 0x0),
    gsSP2Triangles( 1,  5,  3, 0x0,  0,  2,  6, 0x0),
    gsSP2Triangles( 0,  7,  8, 0x0,  0,  6,  7, 0x0),
    gsSP1Triangle( 9, 10, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x070044C8 - 0x07004658
static const Gfx jrb_seg7_dl_070044C8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_09001800_rock),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&jrb_seg7_lights_070030D8.l, 1),
    gsSPLight(&jrb_seg7_lights_070030D8.a, 2),
    gsSPVertex(jrb_seg7_vertex_07003700, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  5,  4, 0x0),
    gsSP2Triangles( 7,  2,  5, 0x0,  6,  3,  0, 0x0),
    gsSP2Triangles( 3,  1,  0, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 0,  2,  7, 0x0, 11, 12,  8, 0x0),
    gsSP2Triangles(12, 11, 13, 0x0, 12, 13, 14, 0x0),
    gsSP2Triangles(12, 15,  8, 0x0, 10, 14, 13, 0x0),
    gsSP2Triangles(10,  9, 14, 0x0,  8, 15,  9, 0x0),
    gsSPVertex(jrb_seg7_vertex_07003800, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 4,  3,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  7,  6, 0x0,  8,  9,  7, 0x0),
    gsSP2Triangles( 3,  5, 10, 0x0, 10,  5,  8, 0x0),
    gsSP2Triangles( 5,  9,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(jrb_seg7_vertex_070038F0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11,  8, 12, 0x0),
    gsSP2Triangles(13,  4,  6, 0x0, 13,  6, 14, 0x0),
    gsSPVertex(jrb_seg7_vertex_070039E0, 11, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP1Triangle( 8,  9, 10, 0x0),
    gsSPEndDisplayList(),
};

// 0x07004658 - 0x070046C0
static const Gfx jrb_seg7_dl_07004658[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_09002800_sand),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(jrb_seg7_vertex_07003A90, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  3,  2, 0x0),
    gsSP2Triangles( 1,  4,  3, 0x0,  4,  5,  3, 0x0),
    gsSP2Triangles( 4,  6,  5, 0x0,  6,  0,  7, 0x0),
    gsSP2Triangles( 6,  7,  5, 0x0,  0,  2,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x070046C0 - 0x07004940
static const Gfx jrb_seg7_dl_070046C0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, water_09004800_mossy_wall),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 64 * 32 - 1, CALC_DXT(64, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&jrb_seg7_lights_070030C0.l, 1),
    gsSPLight(&jrb_seg7_lights_070030C0.a, 2),
    gsSPVertex(jrb_seg7_vertex_07003B10, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  0,  3, 0x0,  1,  5,  2, 0x0),
    gsSP2Triangles( 5,  6,  2, 0x0,  2,  7,  3, 0x0),
    gsSP2Triangles( 2,  8,  9, 0x0,  2,  9,  7, 0x0),
    gsSP2Triangles(10,  8,  2, 0x0, 10,  2, 11, 0x0),
    gsSP2Triangles(11,  2,  6, 0x0, 12,  4,  3, 0x0),
    gsSP2Triangles(12,  3, 13, 0x0,  3,  7, 14, 0x0),
    gsSP1Triangle(15, 12, 13, 0x0),
    gsSPVertex(jrb_seg7_vertex_07003C10, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  0,  2, 0x0,  5,  4,  2, 0x0),
    gsSP2Triangles( 6,  2,  7, 0x0,  8,  9, 10, 0x0),
    gsSP2Triangles( 9,  8, 11, 0x0, 12, 13, 14, 0x0),
    gsSP1Triangle( 9, 11, 15, 0x0),
    gsSPVertex(jrb_seg7_vertex_07003D10, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  1,  0, 0x0),
    gsSP2Triangles( 3,  4,  1, 0x0,  1,  4,  5, 0x0),
    gsSP2Triangles( 1,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 10, 12, 0x0),
    gsSP1Triangle(10, 14, 11, 0x0),
    gsSPVertex(jrb_seg7_vertex_07003E00, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  3, 0x0,  4,  6,  5, 0x0),
    gsSP2Triangles( 4,  7,  8, 0x0,  4,  8,  6, 0x0),
    gsSP2Triangles( 9, 10, 11, 0x0, 12, 13, 14, 0x0),
    gsSPVertex(jrb_seg7_vertex_07003EF0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  1,  0,  3, 0x0),
    gsSP2Triangles( 0,  2,  4, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 5,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle( 6, 12, 13, 0x0),
    gsSPVertex(jrb_seg7_vertex_07003FD0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 2,  4,  3, 0x0,  2,  5,  4, 0x0),
    gsSP2Triangles( 6,  3,  4, 0x0,  6,  4,  7, 0x0),
    gsSP2Triangles( 3,  8,  0, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(jrb_seg7_vertex_070040C0, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 5,  4,  6, 0x0,  5,  6,  7, 0x0),
    gsSP2Triangles( 3,  8,  4, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(jrb_seg7_vertex_070041C0, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x07004940 - 0x07004A18
const Gfx jrb_seg7_dl_07004940[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetFogColor(5, 80, 75, 255),
    gsSPFogPosition(JRB_FOG_MIN, JRB_FOG_MAX),
    gsSPSetGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_PASS2),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(jrb_seg7_dl_070041F0),
    gsSPDisplayList(jrb_seg7_dl_070044C8),
    gsSPDisplayList(jrb_seg7_dl_07004658),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_CLAMP, 6, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (64 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(jrb_seg7_dl_070046C0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_FOG),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};
