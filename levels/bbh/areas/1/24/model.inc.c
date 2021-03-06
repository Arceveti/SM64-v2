// 0x07013C58 - 0x07013C70
static const Lights1 bbh_seg7_lights_07013C58 = gdSPDefLights1(
    0x20, 0x20, 0x20,
    0x50, 0x50, 0x50, 0x28, 0x28, 0x28
);

// 0x07013C70 - 0x07013C88
static const Lights1 bbh_seg7_lights_07013C70 = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07013C88 - 0x07013D08
static const Vtx bbh_seg7_vertex_07013C88[] = {
    {{{   512,      0,    -51}, 0, { 15<<5,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   358,      0,   -102}, 0, {     0,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   358,      0,    -51}, 0, { 15<<5,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   512,      0,   -102}, 0, {     0,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   256,    819,    -51}, 0, { 15<<5,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   102,    819,   -102}, 0, {     0,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   102,    819,    -51}, 0, { 15<<5,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   256,    819,   -102}, 0, {     0,      0}, {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x07013D08 - 0x07013DC8
static const Vtx bbh_seg7_vertex_07013D08[] = {
    {{{  1024,   1638,   -102}, 0, {   -96,   1072}, {0x00, 0x81, 0x00, 0xff}}},
    {{{  -717,   1638,   -102}, 0, { 33<<5,   1072}, {0x00, 0x81, 0x00, 0xff}}},
    {{{  -717,   1638,  -1536}, 0, { 33<<5,   -112}, {0x00, 0x81, 0x00, 0xff}}},
    {{{  1024,   1638,  -1536}, 0, {   -96,   -112}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   358,    256,   -102}, 0, { 31<<5,  31<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   512,    256,    -51}, 0, { 15<<5,      0}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   358,    256,    -51}, 0, { 15<<5,  31<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   512,    256,   -102}, 0, { 31<<5,      0}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   102,   1075,   -102}, 0, { 31<<5,  31<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   256,   1075,   -102}, 0, { 31<<5,      0}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   256,   1075,    -51}, 0, { 15<<5,      0}, {0x00, 0x81, 0x00, 0xff}}},
    {{{   102,   1075,    -51}, 0, { 15<<5,  31<<5}, {0x00, 0x81, 0x00, 0xff}}},
};

// 0x07013DC8 - 0x07013E08
static const Vtx bbh_seg7_vertex_07013DC8[] = {
    {{{  1024,      0,  -1536}, 0, { -7184,  10186}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -717,      0,  -1536}, 0, { 10188,  10186}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  -717,      0,   -102}, 0, { 10188,  -4120}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  1024,      0,   -102}, 0, { -7184,  -4120}, {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x07013E08 - 0x07013E48
static const Vtx bbh_seg7_vertex_07013E08[] = {
    {{{  -512,    205,  -1229}, 0, {     0,  31<<5}, {0x41, 0x57, 0x41, 0xff}}},
    {{{  -512,    358,  -1434}, 0, { 31<<5,      0}, {0x41, 0x57, 0x41, 0xff}}},
    {{{  -614,    358,  -1331}, 0, {     0,      0}, {0x41, 0x57, 0x41, 0xff}}},
    {{{  -410,    205,  -1331}, 0, { 31<<5,  31<<5}, {0x41, 0x57, 0x41, 0xff}}},
};

// 0x07013E48 - 0x07013F38
static const Vtx bbh_seg7_vertex_07013E48[] = {
    {{{  -512,      0,  -1229}, 0, {     0,  63<<5}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{  -614,    205,  -1331}, 0, { 31<<5,    844}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{  -614,      0,  -1331}, 0, { 31<<5,  63<<5}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{  -512,    205,  -1229}, 0, {     0,    844}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{  -410,      0,  -1331}, 0, {  1414,  63<<5}, {0x59, 0x00, 0x59, 0xff}}},
    {{{  -410,    205,  -1331}, 0, {  1414,    648}, {0x59, 0x00, 0x59, 0xff}}},
    {{{  -512,    205,  -1229}, 0, {     0,    648}, {0x59, 0x00, 0x59, 0xff}}},
    {{{  -512,      0,  -1229}, 0, {     0,  63<<5}, {0x59, 0x00, 0x59, 0xff}}},
    {{{  -512,      0,  -1434}, 0, { 31<<5,  63<<5}, {0x5a, 0x00, 0xa7, 0xff}}},
    {{{  -512,    205,  -1434}, 0, { 31<<5,    844}, {0x5a, 0x00, 0xa7, 0xff}}},
    {{{  -410,      0,  -1331}, 0, {     0,  63<<5}, {0x5a, 0x00, 0xa7, 0xff}}},
    {{{  -410,    205,  -1331}, 0, {     0,    844}, {0x5a, 0x00, 0xa7, 0xff}}},
    {{{   358,      0,    -51}, 0, { 15<<5,  63<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   358,    256,   -102}, 0, {     0,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   358,    256,    -51}, 0, { 15<<5,      0}, {0x7f, 0x00, 0x00, 0xff}}},
};

// 0x07013F38 - 0x07014028
static const Vtx bbh_seg7_vertex_07013F38[] = {
    {{{   512,    256,   -102}, 0, {     0,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   512,      0,    -51}, 0, { 15<<5,  63<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   512,    256,    -51}, 0, { 15<<5,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   512,      0,   -102}, 0, {     0,  63<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   256,   1075,   -102}, 0, { 31<<5,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   256,    819,   -102}, 0, { 31<<5,  63<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   256,    819,    -51}, 0, { 15<<5,  63<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   256,   1075,    -51}, 0, { 15<<5,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   102,    819,    -51}, 0, { 15<<5,  63<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   102,   1075,   -102}, 0, { 31<<5,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   102,   1075,    -51}, 0, { 15<<5,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   102,    819,   -102}, 0, { 31<<5,  63<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   358,      0,    -51}, 0, { 15<<5,  63<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   358,      0,   -102}, 0, {     0,  63<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   358,    256,   -102}, 0, {     0,      0}, {0x7f, 0x00, 0x00, 0xff}}},
};

// 0x07014028 - 0x07014088
static const Vtx bbh_seg7_vertex_07014028[] = {
    {{{  -512,    205,  -1434}, 0, { 31<<5,    844}, {0x5a, 0x00, 0xa7, 0xff}}},
    {{{  -512,    358,  -1434}, 0, { 31<<5,      0}, {0x5a, 0x00, 0xa7, 0xff}}},
    {{{  -410,    205,  -1331}, 0, {     0,    844}, {0x5a, 0x00, 0xa7, 0xff}}},
    {{{  -512,    205,  -1229}, 0, {     0,    844}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{  -614,    358,  -1331}, 0, { 31<<5,      0}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{  -614,    205,  -1331}, 0, { 31<<5,    844}, {0xa7, 0x00, 0x59, 0xff}}},
};

// 0x07014088 - 0x07014178
static const Vtx bbh_seg7_vertex_07014088[] = {
    {{{  -512,   1638,   -102}, 0, {     0,  84<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   102,   1075,   -102}, 0, { 95<<5,    820}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -512,    819,   -102}, 0, {     0,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   819,      0,   -102}, 0, {     0,  84<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   512,    256,   -102}, 0, { 47<<5,   1840}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   819,    819,   -102}, 0, {     0,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   512,      0,   -102}, 0, { 47<<5,  84<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   256,    819,   -102}, 0, {  2778,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   819,    819,   -102}, 0, {  6612,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   256,    819,   -102}, 0, {  3800,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   256,   1075,   -102}, 0, {  3800,    820}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   819,   1638,   -102}, 0, {  6612,  84<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -512,      0,   -102}, 0, {  6610,  84<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -512,    819,   -102}, 0, {  6610,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   102,    819,   -102}, 0, {  3544,      0}, {0x00, 0x00, 0x81, 0xff}}},
};

// 0x07014178 - 0x07014268
static const Vtx bbh_seg7_vertex_07014178[] = {
    {{{  -717,    819,  -1331}, 0, {     0,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -717,   1638,  -1331}, 0, {     0,  84<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -717,   1638,   -307}, 0, {159<<5,  84<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   102,   1075,   -102}, 0, { 95<<5,    820}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   102,    819,   -102}, 0, { 95<<5,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -512,    819,   -102}, 0, {     0,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  1024,    819,   -307}, 0, {     0,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  1024,   1638,   -307}, 0, {     0,  84<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  1024,   1638,  -1331}, 0, {159<<5,  84<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  1024,    819,  -1331}, 0, {159<<5,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  1024,      0,   -307}, 0, {159<<5,  84<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  1024,    819,  -1331}, 0, {     0,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  1024,      0,  -1331}, 0, {     0,  84<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  1024,    819,   -307}, 0, {159<<5,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  -717,    819,   -307}, 0, {159<<5,      0}, {0x7f, 0x00, 0x00, 0xff}}},
};

// 0x07014268 - 0x07014368
static const Vtx bbh_seg7_vertex_07014268[] = {
    {{{   512,    256,   -102}, 0, { 47<<5,   1840}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   358,    256,   -102}, 0, {  2268,   1840}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   256,    819,   -102}, 0, {  2778,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -717,      0,  -1331}, 0, {159<<5,  84<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -717,    819,  -1331}, 0, {159<<5,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -717,    819,   -307}, 0, {     0,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -717,      0,   -307}, 0, {     0,  84<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   819,   1638,  -1536}, 0, {     0,  84<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -512,   1638,  -1536}, 0, {  6612,  84<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -512,    819,  -1536}, 0, {  6612,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   819,    819,  -1536}, 0, {     0,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   819,    819,  -1536}, 0, {  6612,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -512,      0,  -1536}, 0, {     0,  84<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   819,      0,  -1536}, 0, {  6612,  84<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -512,    819,  -1536}, 0, {     0,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   102,    819,   -102}, 0, {  3544,      0}, {0x00, 0x00, 0x81, 0xff}}},
};

// 0x07014368 - 0x07014458
static const Vtx bbh_seg7_vertex_07014368[] = {
    {{{   358,    256,   -102}, 0, {  2268,   1840}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   358,      0,   -102}, 0, {  2268,  84<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -512,      0,   -102}, 0, {  6610,  84<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   102,    819,   -102}, 0, {  3544,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   256,   1075,   -102}, 0, {  3800,    820}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   102,   1075,   -102}, 0, { 95<<5,    820}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -512,   1638,   -102}, 0, {     0,  84<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   819,   1638,   -102}, 0, {  6612,  84<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   819,   1638,  -1536}, 0, { 31<<5,  84<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   819,    819,  -1434}, 0, { 23<<5,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   819,   1638,  -1434}, 0, { 23<<5,  84<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   819,   1638,  -1434}, 0, { 23<<5,  84<<5}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{   819,    819,  -1434}, 0, { 23<<5,      0}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{   922,    819,  -1331}, 0, {  7<<5,    -32}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{   922,   1638,  -1331}, 0, {  7<<5,  84<<5}, {0xa7, 0x00, 0x59, 0xff}}},
};

// 0x07014458 - 0x07014538
static const Vtx bbh_seg7_vertex_07014458[] = {
    {{{   922,    819,  -1331}, 0, { 23<<5,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   922,      0,  -1331}, 0, { 23<<5,  84<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  1024,      0,  -1331}, 0, { 31<<5,  84<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   922,   1638,  -1331}, 0, {  7<<5,  84<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   922,    819,  -1331}, 0, {  7<<5,    -32}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  1024,    819,  -1331}, 0, {     0,    -32}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  1024,   1638,  -1331}, 0, {     0,  84<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   819,   1638,  -1536}, 0, { 31<<5,  84<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   819,    819,  -1536}, 0, { 31<<5,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   819,    819,  -1434}, 0, { 23<<5,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   819,    819,  -1434}, 0, {  7<<5,    -32}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{   922,      0,  -1331}, 0, { 23<<5,  84<<5}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{   922,    819,  -1331}, 0, { 23<<5,      0}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{   819,      0,  -1434}, 0, {  7<<5,  84<<5}, {0xa7, 0x00, 0x59, 0xff}}},
};

// 0x07014538 - 0x07014638
static const Vtx bbh_seg7_vertex_07014538[] = {
    {{{   819,    819,  -1536}, 0, {     0,    -32}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   819,      0,  -1434}, 0, {  7<<5,  84<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   819,    819,  -1434}, 0, {  7<<5,    -32}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   819,    819,   -205}, 0, {  7<<5,    -32}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   819,      0,   -102}, 0, {     0,  84<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   819,    819,   -102}, 0, {     0,    -32}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   922,    819,  -1331}, 0, { 23<<5,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  1024,      0,  -1331}, 0, { 31<<5,  84<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  1024,    819,  -1331}, 0, { 31<<5,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   819,      0,  -1536}, 0, {     0,  84<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   922,    819,   -307}, 0, { 23<<5,      0}, {0xa7, 0x00, 0xa6, 0xff}}},
    {{{   922,      0,   -307}, 0, { 23<<5,  84<<5}, {0xa7, 0x00, 0xa6, 0xff}}},
    {{{   819,      0,   -205}, 0, {  7<<5,  84<<5}, {0xa7, 0x00, 0xa6, 0xff}}},
    {{{  1024,    819,   -307}, 0, { 31<<5,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   922,      0,   -307}, 0, { 23<<5,  84<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   922,    819,   -307}, 0, { 23<<5,      0}, {0x00, 0x00, 0x81, 0xff}}},
};

// 0x07014638 - 0x07014738
static const Vtx bbh_seg7_vertex_07014638[] = {
    {{{   922,    819,   -307}, 0, { 23<<5,      0}, {0xa7, 0x00, 0xa6, 0xff}}},
    {{{   819,      0,   -205}, 0, {  7<<5,  84<<5}, {0xa7, 0x00, 0xa6, 0xff}}},
    {{{   819,    819,   -205}, 0, {  7<<5,    -32}, {0xa7, 0x00, 0xa6, 0xff}}},
    {{{   819,    819,   -205}, 0, {  7<<5,    -32}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   819,      0,   -205}, 0, {  7<<5,  84<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   819,      0,   -102}, 0, {     0,  84<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  1024,    819,   -307}, 0, { 31<<5,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  1024,      0,   -307}, 0, { 31<<5,  84<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   922,      0,   -307}, 0, { 23<<5,  84<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   922,   1638,   -307}, 0, {  7<<5,  84<<5}, {0xa7, 0x00, 0xa6, 0xff}}},
    {{{   922,    819,   -307}, 0, {  7<<5,    -32}, {0xa7, 0x00, 0xa6, 0xff}}},
    {{{   819,    819,   -205}, 0, { 23<<5,      0}, {0xa7, 0x00, 0xa6, 0xff}}},
    {{{  1024,   1638,   -307}, 0, {     0,  84<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   922,    819,   -307}, 0, {  7<<5,    -32}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   922,   1638,   -307}, 0, {  7<<5,  84<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   819,   1638,   -205}, 0, { 23<<5,  84<<5}, {0xa7, 0x00, 0xa6, 0xff}}},
};

// 0x07014738 - 0x07014838
static const Vtx bbh_seg7_vertex_07014738[] = {
    {{{   819,   1638,   -205}, 0, { 23<<5,  84<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   819,    819,   -205}, 0, { 23<<5,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   819,    819,   -102}, 0, { 31<<5,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   819,   1638,   -102}, 0, { 31<<5,  84<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  1024,   1638,   -307}, 0, {     0,  84<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  1024,    819,   -307}, 0, {     0,    -32}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   922,    819,   -307}, 0, {  7<<5,    -32}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -614,    819,  -1331}, 0, { 23<<5,      0}, {0x5a, 0x00, 0x59, 0xff}}},
    {{{  -512,      0,  -1434}, 0, {  7<<5,  84<<5}, {0x5a, 0x00, 0x59, 0xff}}},
    {{{  -512,    819,  -1434}, 0, {  7<<5,    -32}, {0x5a, 0x00, 0x59, 0xff}}},
    {{{  -717,    819,  -1331}, 0, { 31<<5,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -614,      0,  -1331}, 0, { 23<<5,  84<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -614,    819,  -1331}, 0, { 23<<5,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -512,    819,  -1434}, 0, {  7<<5,    -32}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -512,      0,  -1434}, 0, {  7<<5,  84<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -512,      0,  -1536}, 0, {     0,  84<<5}, {0x7f, 0x00, 0x00, 0xff}}},
};

// 0x07014838 - 0x07014938
static const Vtx bbh_seg7_vertex_07014838[] = {
    {{{  -614,    819,  -1331}, 0, { 23<<5,      0}, {0x5a, 0x00, 0x59, 0xff}}},
    {{{  -614,      0,  -1331}, 0, { 23<<5,  84<<5}, {0x5a, 0x00, 0x59, 0xff}}},
    {{{  -512,      0,  -1434}, 0, {  7<<5,  84<<5}, {0x5a, 0x00, 0x59, 0xff}}},
    {{{  -512,    819,  -1434}, 0, {  7<<5,    -32}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -512,      0,  -1536}, 0, {     0,  84<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -512,    819,  -1536}, 0, {     0,    -32}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -717,    819,  -1331}, 0, { 31<<5,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -717,      0,  -1331}, 0, { 31<<5,  84<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -614,      0,  -1331}, 0, { 23<<5,  84<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -614,   1638,  -1331}, 0, {  7<<5,  84<<5}, {0x5a, 0x00, 0x59, 0xff}}},
    {{{  -512,    819,  -1434}, 0, { 23<<5,      0}, {0x5a, 0x00, 0x59, 0xff}}},
    {{{  -512,   1638,  -1434}, 0, { 23<<5,  84<<5}, {0x5a, 0x00, 0x59, 0xff}}},
    {{{  -717,   1638,  -1331}, 0, {     0,  84<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -614,    819,  -1331}, 0, {  7<<5,    -32}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -614,   1638,  -1331}, 0, {  7<<5,  84<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -614,    819,  -1331}, 0, {  7<<5,    -32}, {0x5a, 0x00, 0x59, 0xff}}},
};

// 0x07014938 - 0x07014A28
static const Vtx bbh_seg7_vertex_07014938[] = {
    {{{  -512,   1638,   -205}, 0, { 23<<5,  84<<5}, {0x59, 0x00, 0xa7, 0xff}}},
    {{{  -512,    819,   -205}, 0, { 23<<5,      0}, {0x59, 0x00, 0xa7, 0xff}}},
    {{{  -614,    819,   -307}, 0, {  7<<5,    -32}, {0x59, 0x00, 0xa7, 0xff}}},
    {{{  -512,   1638,  -1434}, 0, { 23<<5,  84<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -512,    819,  -1434}, 0, { 23<<5,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -512,    819,  -1536}, 0, { 31<<5,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -512,   1638,  -1536}, 0, { 31<<5,  84<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -717,   1638,  -1331}, 0, {     0,  84<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -717,    819,  -1331}, 0, {     0,    -32}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -614,    819,  -1331}, 0, {  7<<5,    -32}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  -614,   1638,   -307}, 0, {  7<<5,  84<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -614,    819,   -307}, 0, {  7<<5,    -32}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -717,    819,   -307}, 0, {     0,    -32}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -614,   1638,   -307}, 0, {  7<<5,  84<<5}, {0x59, 0x00, 0xa7, 0xff}}},
    {{{  -717,   1638,   -307}, 0, {     0,  84<<5}, {0x00, 0x00, 0x81, 0xff}}},
};

// 0x07014A28 - 0x07014B28
static const Vtx bbh_seg7_vertex_07014A28[] = {
    {{{  -614,    819,   -307}, 0, { 23<<5,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -614,      0,   -307}, 0, { 23<<5,  84<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -717,      0,   -307}, 0, { 31<<5,  84<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -717,    819,   -307}, 0, { 31<<5,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  -512,    819,   -205}, 0, {  7<<5,    -32}, {0x59, 0x00, 0xa7, 0xff}}},
    {{{  -614,      0,   -307}, 0, { 23<<5,  84<<5}, {0x59, 0x00, 0xa7, 0xff}}},
    {{{  -614,    819,   -307}, 0, { 23<<5,      0}, {0x59, 0x00, 0xa7, 0xff}}},
    {{{  -512,      0,   -205}, 0, {  7<<5,  84<<5}, {0x59, 0x00, 0xa7, 0xff}}},
    {{{  -512,   1638,   -102}, 0, { 31<<5,  84<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -512,    819,   -102}, 0, { 31<<5,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -512,    819,   -205}, 0, { 23<<5,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -512,   1638,   -205}, 0, { 23<<5,  84<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -512,    819,   -102}, 0, {     0,    -32}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -512,      0,   -205}, 0, {  7<<5,  84<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -512,    819,   -205}, 0, {  7<<5,    -32}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  -512,      0,   -102}, 0, {     0,  84<<5}, {0x7f, 0x00, 0x00, 0xff}}},
};

// 0x07014B28 - 0x07014BC8
static const Gfx bbh_seg7_dl_07014B28[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09008800_house_floor),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&bbh_seg7_lights_07013C58.l, 1),
    gsSPLight(&bbh_seg7_lights_07013C58.a, 2),
    gsSPVertex(bbh_seg7_vertex_07013C88, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPLight(&bbh_seg7_lights_07013C70.l, 1),
    gsSPLight(&bbh_seg7_lights_07013C70.a, 2),
    gsSPVertex(bbh_seg7_vertex_07013D08, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x07014BC8 - 0x07014C10
static const Gfx bbh_seg7_dl_07014BC8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_0900A000_metal_floor),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&bbh_seg7_lights_07013C58.l, 1),
    gsSPLight(&bbh_seg7_lights_07013C58.a, 2),
    gsSPVertex(bbh_seg7_vertex_07013DC8, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07014C10 - 0x07014C58
static const Gfx bbh_seg7_dl_07014C10[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09004800_pattern_block),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&bbh_seg7_lights_07013C70.l, 1),
    gsSPLight(&bbh_seg7_lights_07013C70.a, 2),
    gsSPVertex(bbh_seg7_vertex_07013E08, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSPEndDisplayList(),
};

// 0x07014C58 - 0x07014D10
static const Gfx bbh_seg7_dl_07014C58[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09003800_house_wall),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_07013E48, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  9, 11, 10, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_07013F38, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_07014028, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x07014D10 - 0x07014FD8
static const Gfx bbh_seg7_dl_07014D10[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09005000_bricks_with_floor),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_07014088, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_07014178, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_07014268, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP2Triangles(11, 14, 12, 0x0,  1, 15,  2, 0x0),
    gsSPVertex(bbh_seg7_vertex_07014368, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_07014458, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSPVertex(bbh_seg7_vertex_07014538, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  0,  9,  1, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(bbh_seg7_vertex_07014638, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0,  9, 11, 15, 0x0),
    gsSPVertex(bbh_seg7_vertex_07014738, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(bbh_seg7_vertex_07014838, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0,  9, 15, 10, 0x0),
    gsSPVertex(bbh_seg7_vertex_07014938, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0,  0,  2, 13, 0x0),
    gsSP1Triangle(10, 12, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_07014A28, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPEndDisplayList(),
};

// 0x07014FD8 - 0x07015098
const Gfx bbh_seg7_dl_mesh_room_surfaces[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_07014B28),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_07014BC8),
    gsSPDisplayList(bbh_seg7_dl_07014C10),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_07014C58),
    gsSPDisplayList(bbh_seg7_dl_07014D10),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
