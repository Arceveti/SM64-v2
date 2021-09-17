// 0x07012758 - 0x07012770
static const Lights1 bbh_seg7_lights_07012758 = gdSPDefLights1(
    0x3c, 0x3c, 0x3c,
    0x96, 0x96, 0x96, 0x28, 0x28, 0x28
);

// 0x07012770 - 0x07012788
static const Lights1 bbh_seg7_lights_07012770 = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x07012788 - 0x070127C8
static const Vtx bbh_seg7_vertex_07012788[] = {
    {{{  3584,    819,  -1536}, 0, { -5152, 255<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  2253,    819,  -1536}, 0, {255<<5, 255<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  2253,    819,   -102}, 0, {255<<5,  -6160}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  3584,    819,   -102}, 0, { -5152,  -6160}, {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x070127C8 - 0x07012848
static const Vtx bbh_seg7_vertex_070127C8[] = {
    {{{  3584,   1638,   -102}, 0, {     0,  31<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{  1126,   1638,  -1536}, 0, { 31<<5,      0}, {0x00, 0x81, 0x00, 0xff}}},
    {{{  3584,   1638,  -1536}, 0, { 31<<5,  31<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{  1126,   1638,   -102}, 0, {     0,      0}, {0x00, 0x81, 0x00, 0xff}}},
    {{{  2253,    819,  -1536}, 0, { 31<<5,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  1126,    819,  -1536}, 0, {     0,      0}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  1126,    819,   -102}, 0, {     0,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  2253,    819,   -102}, 0, { 31<<5,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x07012848 - 0x070128A8
static const Vtx bbh_seg7_vertex_07012848[] = {
    {{{  1331,    922,  -1229}, 0, {     0,  31<<5}, {0x41, 0x57, 0x41, 0xff}}},
    {{{  1331,   1075,  -1434}, 0, { 31<<5,      0}, {0x41, 0x57, 0x41, 0xff}}},
    {{{  1229,   1075,  -1331}, 0, {     0,      0}, {0x41, 0x57, 0x41, 0xff}}},
    {{{  1331,    922,  -1229}, 0, {     0,  31<<5}, {0x40, 0x57, 0x41, 0xff}}},
    {{{  1434,    922,  -1331}, 0, { 31<<5,  31<<5}, {0x40, 0x57, 0x41, 0xff}}},
    {{{  1331,   1075,  -1434}, 0, { 31<<5,      0}, {0x40, 0x57, 0x41, 0xff}}},
};

// 0x070128A8 - 0x070129A8
static const Vtx bbh_seg7_vertex_070128A8[] = {
    {{{  1331,    819,  -1434}, 0, { 31<<5,  63<<5}, {0x59, 0x00, 0xa7, 0xff}}},
    {{{  1331,    922,  -1434}, 0, { 31<<5,    848}, {0x59, 0x00, 0xa7, 0xff}}},
    {{{  1434,    922,  -1331}, 0, {     0,    848}, {0x59, 0x00, 0xa7, 0xff}}},
    {{{  1434,    819,  -1331}, 0, {     0,  63<<5}, {0x59, 0x00, 0xa7, 0xff}}},
    {{{  1434,    819,  -1331}, 0, { 44<<5,  63<<5}, {0x59, 0x00, 0x5a, 0xff}}},
    {{{  1434,    922,  -1331}, 0, { 44<<5,    648}, {0x59, 0x00, 0x5a, 0xff}}},
    {{{  1331,    922,  -1229}, 0, {     0,    648}, {0x59, 0x00, 0x5a, 0xff}}},
    {{{  1331,    819,  -1229}, 0, {     0,  63<<5}, {0x59, 0x00, 0x5a, 0xff}}},
    {{{  1331,    819,  -1229}, 0, {     0,  63<<5}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{  1331,    922,  -1229}, 0, {     0,    848}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{  1229,    922,  -1331}, 0, { 31<<5,    848}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{  1229,    819,  -1331}, 0, { 31<<5,  63<<5}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{  1690,   1075,   -102}, 0, { 27<<5,  43<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  1331,   1638,   -102}, 0, {     0,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  1946,   1638,   -102}, 0, { 47<<5,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  1536,   1075,   -102}, 0, { 15<<5,  43<<5}, {0x00, 0x00, 0x81, 0xff}}},
};

// 0x070129A8 - 0x07012A88
static const Vtx bbh_seg7_vertex_070129A8[] = {
    {{{  2253,    819,   -614}, 0, { 55<<5,  63<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  2150,    819,   -614}, 0, { 55<<5,  63<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  2150,   1126,   -614}, 0, { 55<<5,  39<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  2253,   1126,   -614}, 0, { 55<<5,  39<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  2253,   1126,   -614}, 0, { 55<<5,  39<<5}, {0x00, 0xa7, 0xa7, 0xff}}},
    {{{  2150,   1126,   -614}, 0, { 55<<5,  39<<5}, {0x00, 0xa7, 0xa7, 0xff}}},
    {{{  2150,   1229,   -717}, 0, { 47<<5,  31<<5}, {0x00, 0xa7, 0xa7, 0xff}}},
    {{{  2150,   1126,   -614}, 0, { 55<<5,  39<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  2150,    819,   -614}, 0, { 55<<5,  63<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  2150,    819,   -307}, 0, { 79<<5,  63<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  2150,   1229,   -717}, 0, { 47<<5,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  2150,   1638,   -307}, 0, { 79<<5,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  2150,   1229,   -922}, 0, { 31<<5,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  2150,   1638,  -1331}, 0, {     0,      0}, {0x81, 0x00, 0x00, 0xff}}},
};

// 0x07012A88 - 0x07012B88
static const Vtx bbh_seg7_vertex_07012A88[] = {
    {{{  2253,   1638,   -307}, 0, { 79<<5,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  2253,   1126,   -614}, 0, { 55<<5,  39<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  2253,   1229,   -717}, 0, { 47<<5,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  2253,   1229,   -717}, 0, { 47<<5,  31<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{  2150,   1229,   -717}, 0, { 47<<5,  31<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{  2150,   1229,   -922}, 0, { 31<<5,  31<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{  2253,   1126,   -614}, 0, { 55<<5,  39<<5}, {0x00, 0xa7, 0xa7, 0xff}}},
    {{{  2150,   1229,   -717}, 0, { 47<<5,  31<<5}, {0x00, 0xa7, 0xa7, 0xff}}},
    {{{  2253,   1229,   -717}, 0, { 47<<5,  31<<5}, {0x00, 0xa7, 0xa7, 0xff}}},
    {{{  2253,   1229,   -922}, 0, { 31<<5,  31<<5}, {0x00, 0xa7, 0x5a, 0xff}}},
    {{{  2150,   1229,   -922}, 0, { 31<<5,  31<<5}, {0x00, 0xa7, 0x5a, 0xff}}},
    {{{  2150,   1126,  -1024}, 0, { 23<<5,  39<<5}, {0x00, 0xa7, 0x5a, 0xff}}},
    {{{  2253,   1229,   -922}, 0, { 31<<5,  31<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{  2150,   1126,  -1024}, 0, { 23<<5,  39<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  2150,   1229,   -922}, 0, { 31<<5,  31<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  2150,   1638,  -1331}, 0, {     0,      0}, {0x81, 0x00, 0x00, 0xff}}},
};

// 0x07012B88 - 0x07012C78
static const Vtx bbh_seg7_vertex_07012B88[] = {
    {{{  2150,   1126,  -1024}, 0, { 23<<5,  39<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  2150,   1638,  -1331}, 0, {     0,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  2150,    819,  -1331}, 0, {     0,  63<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  2150,    819,  -1024}, 0, { 23<<5,  63<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  2253,   1229,   -922}, 0, { 31<<5,  31<<5}, {0x00, 0xa7, 0x5a, 0xff}}},
    {{{  2150,   1126,  -1024}, 0, { 23<<5,  39<<5}, {0x00, 0xa7, 0x5a, 0xff}}},
    {{{  2253,   1126,  -1024}, 0, { 23<<5,  39<<5}, {0x00, 0xa7, 0x5a, 0xff}}},
    {{{  2253,   1126,  -1024}, 0, { 23<<5,  39<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  2150,   1126,  -1024}, 0, { 23<<5,  39<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  2150,    819,  -1024}, 0, { 23<<5,  63<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  2253,    819,  -1024}, 0, { 23<<5,  63<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  2253,    819,   -307}, 0, { 79<<5,  63<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  2253,    819,   -614}, 0, { 55<<5,  63<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  2253,   1126,   -614}, 0, { 55<<5,  39<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  2253,   1638,   -307}, 0, { 79<<5,      0}, {0x7f, 0x00, 0x00, 0xff}}},
};

// 0x07012C78 - 0x07012D68
static const Vtx bbh_seg7_vertex_07012C78[] = {
    {{{  1946,    819,   -102}, 0, { 47<<5,  63<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  1690,    819,   -102}, 0, { 27<<5,  63<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  1690,   1075,   -102}, 0, { 27<<5,  43<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  2253,   1638,  -1331}, 0, {     0,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  2253,   1638,   -307}, 0, { 79<<5,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  2253,   1229,   -717}, 0, { 47<<5,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  2253,   1229,   -922}, 0, { 31<<5,  31<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  2253,    819,  -1331}, 0, {     0,  63<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  2253,   1126,  -1024}, 0, { 23<<5,  39<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  2253,    819,  -1024}, 0, { 23<<5,  63<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  1536,   1075,   -102}, 0, { 15<<5,  43<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  1536,    819,   -102}, 0, { 15<<5,  63<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  1331,    819,   -102}, 0, {     0,  63<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  1331,   1638,   -102}, 0, {     0,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  1946,   1638,   -102}, 0, { 47<<5,      0}, {0x00, 0x00, 0x81, 0xff}}},
};

// 0x07012D68 - 0x07012E58
static const Vtx bbh_seg7_vertex_07012D68[] = {
    {{{  1536,   1075,   -102}, 0, { 15<<5,  43<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{  1690,   1075,    -51}, 0, { 27<<5,  43<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{  1536,   1075,    -51}, 0, { 15<<5,  43<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{  1331,    819,  -1536}, 0, {     0,  63<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  1946,    819,  -1536}, 0, { 47<<5,  63<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  1946,   1638,  -1536}, 0, { 47<<5,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  1331,   1638,  -1536}, 0, {     0,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  1126,   1638,   -307}, 0, {     0,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  1126,    819,  -1331}, 0, { 79<<5,  63<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  1126,   1638,  -1331}, 0, { 79<<5,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  1126,    819,   -307}, 0, {     0,  63<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  1690,   1075,   -102}, 0, { 27<<5,  43<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  1690,    819,   -102}, 0, { 27<<5,  63<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  1690,    819,    -51}, 0, { 27<<5,  63<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  1690,   1075,    -51}, 0, { 27<<5,  43<<5}, {0x81, 0x00, 0x00, 0xff}}},
};

// 0x07012E58 - 0x07012F38
static const Vtx bbh_seg7_vertex_07012E58[] = {
    {{{  1536,    819,    -51}, 0, { 15<<5,  63<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  1536,   1075,   -102}, 0, { 15<<5,  43<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  1536,   1075,    -51}, 0, { 15<<5,  43<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  1536,   1075,   -102}, 0, { 15<<5,  43<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{  1690,   1075,   -102}, 0, { 27<<5,  43<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{  1690,   1075,    -51}, 0, { 27<<5,  43<<5}, {0x00, 0x81, 0x00, 0xff}}},
    {{{  1690,    819,    -51}, 0, { 27<<5,  63<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  1690,    819,   -102}, 0, { 27<<5,  63<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  1536,    819,   -102}, 0, { 15<<5,  63<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  1536,    819,    -51}, 0, { 15<<5,  63<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{  1536,    819,   -102}, 0, { 15<<5,  63<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  1331,    922,  -1434}, 0, { 31<<5,    848}, {0x59, 0x00, 0xa7, 0xff}}},
    {{{  1331,   1075,  -1434}, 0, { 31<<5,      0}, {0x59, 0x00, 0xa7, 0xff}}},
    {{{  1434,    922,  -1331}, 0, {     0,    848}, {0x59, 0x00, 0xa7, 0xff}}},
};

// 0x07012F38 - 0x07012F68
static const Vtx bbh_seg7_vertex_07012F38[] = {
    {{{  1331,    922,  -1229}, 0, {     0,    848}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{  1229,   1075,  -1331}, 0, { 31<<5,      0}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{  1229,    922,  -1331}, 0, { 31<<5,    848}, {0xa7, 0x00, 0x59, 0xff}}},
};

// 0x07012F68 - 0x07013028
static const Vtx bbh_seg7_vertex_07012F68[] = {
    {{{  3584,   1638,  -1536}, 0, {175<<5,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  2458,    819,  -1536}, 0, {     0,  63<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  3584,    819,  -1536}, 0, {175<<5,  63<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  2458,   1638,  -1536}, 0, {     0,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  3584,    819,   -102}, 0, {175<<5,  63<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  2458,    819,   -102}, 0, {     0,  63<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  2458,   1638,   -102}, 0, {     0,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  3584,   1638,   -102}, 0, {175<<5,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  3584,    819,   -102}, 0, {223<<5,  63<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  3584,   1638,   -102}, 0, {223<<5,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  3584,   1638,  -1536}, 0, {     0,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  3584,    819,  -1536}, 0, {     0,  63<<5}, {0x81, 0x00, 0x00, 0xff}}},
};

// 0x07013028 - 0x07013118
static const Vtx bbh_seg7_vertex_07013028[] = {
    {{{  2458,   1638,   -205}, 0, {  7<<5,      0}, {0x59, 0x00, 0xa6, 0xff}}},
    {{{  2458,    819,   -205}, 0, {  7<<5,  63<<5}, {0x59, 0x00, 0xa6, 0xff}}},
    {{{  2355,    819,   -307}, 0, { 23<<5,  63<<5}, {0x59, 0x00, 0xa6, 0xff}}},
    {{{  2253,   1638,  -1331}, 0, {     0,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  2355,    819,  -1331}, 0, {  7<<5,  63<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  2355,   1638,  -1331}, 0, {  7<<5,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  2355,   1638,  -1331}, 0, {  7<<5,      0}, {0x59, 0x00, 0x59, 0xff}}},
    {{{  2355,    819,  -1331}, 0, {  7<<5,  63<<5}, {0x59, 0x00, 0x59, 0xff}}},
    {{{  2458,    819,  -1434}, 0, { 23<<5,  63<<5}, {0x59, 0x00, 0x59, 0xff}}},
    {{{  2458,   1638,  -1434}, 0, { 23<<5,      0}, {0x59, 0x00, 0x59, 0xff}}},
    {{{  2458,   1638,  -1434}, 0, { 23<<5,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  2458,    819,  -1434}, 0, { 23<<5,  63<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  2458,    819,  -1536}, 0, { 31<<5,  63<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  2458,   1638,  -1536}, 0, { 31<<5,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  2253,    819,  -1331}, 0, {     0,  63<<5}, {0x00, 0x00, 0x7f, 0xff}}},
};

// 0x07013118 - 0x07013208
static const Vtx bbh_seg7_vertex_07013118[] = {
    {{{  2458,   1638,   -102}, 0, {     0,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  2458,    819,   -205}, 0, {  7<<5,  63<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  2458,   1638,   -205}, 0, {  7<<5,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  2458,    819,   -102}, 0, {     0,  63<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  1946,   1638,  -1536}, 0, {     0,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  1946,    819,  -1536}, 0, {     0,  63<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  1946,    819,  -1434}, 0, {  7<<5,  63<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  2458,   1638,   -205}, 0, {  7<<5,      0}, {0x59, 0x00, 0xa6, 0xff}}},
    {{{  2355,    819,   -307}, 0, { 23<<5,  63<<5}, {0x59, 0x00, 0xa6, 0xff}}},
    {{{  2355,   1638,   -307}, 0, { 23<<5,      0}, {0x59, 0x00, 0xa6, 0xff}}},
    {{{  2355,   1638,   -307}, 0, { 23<<5,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  2355,    819,   -307}, 0, { 23<<5,  63<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  2253,    819,   -307}, 0, { 31<<5,  63<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  2253,   1638,   -307}, 0, { 31<<5,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  1946,   1638,  -1434}, 0, {  7<<5,      0}, {0x81, 0x00, 0x00, 0xff}}},
};

// 0x07013208 - 0x070132F8
static const Vtx bbh_seg7_vertex_07013208[] = {
    {{{  1946,   1638,  -1434}, 0, {  7<<5,      0}, {0xa6, 0x00, 0x59, 0xff}}},
    {{{  1946,    819,  -1434}, 0, {  7<<5,  63<<5}, {0xa6, 0x00, 0x59, 0xff}}},
    {{{  2048,    819,  -1331}, 0, { 23<<5,  63<<5}, {0xa6, 0x00, 0x59, 0xff}}},
    {{{  2048,   1638,  -1331}, 0, { 23<<5,      0}, {0xa6, 0x00, 0x59, 0xff}}},
    {{{  2048,   1638,  -1331}, 0, { 23<<5,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  2048,    819,  -1331}, 0, { 23<<5,  63<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  2150,    819,  -1331}, 0, { 31<<5,  63<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  2150,   1638,  -1331}, 0, { 31<<5,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  1331,   1638,   -205}, 0, {  7<<5,      0}, {0x59, 0x00, 0xa7, 0xff}}},
    {{{  1229,    819,   -307}, 0, { 23<<5,  63<<5}, {0x59, 0x00, 0xa7, 0xff}}},
    {{{  1229,   1638,   -307}, 0, { 23<<5,      0}, {0x59, 0x00, 0xa7, 0xff}}},
    {{{  2048,   1638,   -307}, 0, {  7<<5,      0}, {0xa7, 0x00, 0xa7, 0xff}}},
    {{{  1946,    819,   -205}, 0, { 23<<5,  63<<5}, {0xa7, 0x00, 0xa7, 0xff}}},
    {{{  1946,   1638,   -205}, 0, { 23<<5,      0}, {0xa7, 0x00, 0xa7, 0xff}}},
    {{{  2048,    819,   -307}, 0, {  7<<5,  63<<5}, {0xa7, 0x00, 0xa7, 0xff}}},
};

// 0x070132F8 - 0x070133E8
static const Vtx bbh_seg7_vertex_070132F8[] = {
    {{{  2150,   1638,   -307}, 0, {     0,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  2048,    819,   -307}, 0, {  7<<5,  63<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  2048,   1638,   -307}, 0, {  7<<5,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  1946,   1638,   -205}, 0, { 23<<5,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  1946,    819,   -205}, 0, { 23<<5,  63<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  1946,    819,   -102}, 0, { 31<<5,  63<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  1946,   1638,   -102}, 0, { 31<<5,      0}, {0x81, 0x00, 0x00, 0xff}}},
    {{{  2150,    819,   -307}, 0, {     0,  63<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  1229,   1638,   -307}, 0, { 23<<5,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  1126,    819,   -307}, 0, { 31<<5,  63<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  1126,   1638,   -307}, 0, { 31<<5,      0}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  1229,    819,   -307}, 0, { 23<<5,  63<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{  1126,   1638,  -1331}, 0, {     0,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  1126,    819,  -1331}, 0, {     0,  63<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  1229,    819,  -1331}, 0, {  7<<5,  63<<5}, {0x00, 0x00, 0x7f, 0xff}}},
};

// 0x070133E8 - 0x070134D8
static const Vtx bbh_seg7_vertex_070133E8[] = {
    {{{  1331,   1638,   -205}, 0, {  7<<5,      0}, {0x59, 0x00, 0xa7, 0xff}}},
    {{{  1331,    819,   -205}, 0, {  7<<5,  63<<5}, {0x59, 0x00, 0xa7, 0xff}}},
    {{{  1229,    819,   -307}, 0, { 23<<5,  63<<5}, {0x59, 0x00, 0xa7, 0xff}}},
    {{{  1331,   1638,   -102}, 0, {     0,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  1331,    819,   -205}, 0, {  7<<5,  63<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  1331,   1638,   -205}, 0, {  7<<5,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  1331,    819,   -102}, 0, {     0,  63<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  1229,   1638,  -1331}, 0, {  7<<5,      0}, {0x5a, 0x00, 0x59, 0xff}}},
    {{{  1331,    819,  -1434}, 0, { 23<<5,  63<<5}, {0x5a, 0x00, 0x59, 0xff}}},
    {{{  1331,   1638,  -1434}, 0, { 23<<5,      0}, {0x5a, 0x00, 0x59, 0xff}}},
    {{{  1331,   1638,  -1434}, 0, { 23<<5,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  1331,    819,  -1434}, 0, { 23<<5,  63<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  1331,    819,  -1536}, 0, { 31<<5,  63<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  1331,   1638,  -1536}, 0, { 31<<5,      0}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{  1229,    819,  -1331}, 0, {  7<<5,  63<<5}, {0x5a, 0x00, 0x59, 0xff}}},
};

// 0x070134D8 - 0x07013508
static const Vtx bbh_seg7_vertex_070134D8[] = {
    {{{  1126,   1638,  -1331}, 0, {     0,      0}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  1229,    819,  -1331}, 0, {  7<<5,  63<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{  1229,   1638,  -1331}, 0, {  7<<5,      0}, {0x00, 0x00, 0x7f, 0xff}}},
};

// 0x07013508 - 0x07013550
static const Gfx bbh_seg7_dl_07013508[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_0900A000_metal_floor),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&bbh_seg7_lights_07012758.l, 1),
    gsSPLight(&bbh_seg7_lights_07012758.a, 2),
    gsSPVertex(bbh_seg7_vertex_07012788, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

// 0x07013550 - 0x070135A8
static const Gfx bbh_seg7_dl_07013550[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09008800_house_floor),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&bbh_seg7_lights_07012770.l, 1),
    gsSPLight(&bbh_seg7_lights_07012770.a, 2),
    gsSPVertex(bbh_seg7_vertex_070127C8, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSPEndDisplayList(),
};

// 0x070135A8 - 0x070135E0
static const Gfx bbh_seg7_dl_070135A8[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09004800_pattern_block),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_07012848, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x070135E0 - 0x070137E0
static const Gfx bbh_seg7_dl_070135E0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09003800_house_wall),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_070128A8, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 15, 13, 0x0),
    gsSPVertex(bbh_seg7_vertex_070129A8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10,  7, 11, 0x0,  7,  9, 11, 0x0),
    gsSP2Triangles(12, 10, 11, 0x0, 12, 11, 13, 0x0),
    gsSPVertex(bbh_seg7_vertex_07012A88, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles( 3,  5, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(bbh_seg7_vertex_07012B88, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  0,  2, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(14, 11, 13, 0x0),
    gsSPVertex(bbh_seg7_vertex_07012C78, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  3,  8, 0x0),
    gsSP2Triangles( 3,  6,  8, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 10, 12, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_07012D68, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_07012E58, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles( 0, 10,  1, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(bbh_seg7_vertex_07012F38, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x070137E0 - 0x07013838
static const Gfx bbh_seg7_dl_070137E0[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, bbh_seg7_texture_wooden_panel_wall),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_07012F68, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x07013838 - 0x070139A8
static const Gfx bbh_seg7_dl_07013838[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, spooky_09001800_column),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 64 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(bbh_seg7_vertex_07013028, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 3, 14,  4, 0x0),
    gsSPVertex(bbh_seg7_vertex_07013118, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 4,  6, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_07013208, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 14, 12, 0x0),
    gsSPVertex(bbh_seg7_vertex_070132F8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  0,  7,  1, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(bbh_seg7_vertex_070133E8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 12, 13, 0x0),
    gsSP1Triangle( 7, 14,  8, 0x0),
    gsSPVertex(bbh_seg7_vertex_070134D8, 3, 0),
    gsSP1Triangle( 0,  1,  2, 0x0),
    gsSPEndDisplayList(),
};

// 0x070139A8 - 0x07013AA0
const Gfx bbh_seg7_dl_coffins_room_surfaces[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_07013508),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_07013550),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_070135A8),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_070135E0),
    gsSPDisplayList(bbh_seg7_dl_070137E0),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (64 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(bbh_seg7_dl_07013838),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
