// Haunted Cage

// 0x0500C258
static const Lights1 haunted_cage_seg5_lights_0500C258 = gdSPDefLights1(
    0x39, 0x0c, 0x0e,
    0x90, 0x1e, 0x25, 0x28, 0x28, 0x28
);

// 0x0500C270
static const Lights1 haunted_cage_seg5_lights_0500C270 = gdSPDefLights1(
    0x47, 0x47, 0x47,
    0xb2, 0xb2, 0xb2, 0x28, 0x28, 0x28
);

// 0x0500C288
ALIGNED8 static const Texture haunted_cage_seg5_texture_floor[] = {
#include "actors/haunted_cage/bbh_cage_floor.rgba16.inc.c"
};

// 0x0500CA88
ALIGNED8 static const Texture haunted_cage_seg5_texture_double_ornament[] = {
#include "actors/haunted_cage/bbh_cage_double_ornament.rgba16.inc.c"
};

// 0x0500D288
ALIGNED8 static const Texture haunted_cage_seg5_texture_ornament[] = {
#include "actors/haunted_cage/bbh_cage_ornament.rgba16.inc.c"
};

// 0x0500D688
ALIGNED8 static const Texture haunted_cage_seg5_texture_wooden_base[] = {
#include "actors/haunted_cage/bbh_cage_wooden_base.rgba16.inc.c"
};

// 0x0500DA88
ALIGNED8 static const Texture haunted_cage_seg5_texture_bars[] = {
#include "actors/haunted_cage/bbh_cage_bars.rgba16.inc.c"
};

// // possibly garbage. does not at all appear to be a texture and is unreferenced
// // also could be some sort of shader mask from much earlier in development, considering
// // Big Boo's Haunt was a very very early level.
// // 0x0500E288
// UNUSED ALIGNED8 static const Texture haunted_cage_seg5_texture_0500E288[] = {
// #include "actors/haunted_cage/bbh_cage_garbage.rgba16.inc.c"
// };

// 0x0500EA88
static const Vtx haunted_cage_seg5_vertex_0500EA88[] = {
    {{{    48,     81,      0}, 0, {191<<5,  64<<5}, {0x31, 0x73, 0xf1, 0xff}}},
    {{{    40,     81,    -23}, 0, {  7122,  64<<5}, {0x31, 0x73, 0xf1, 0xff}}},
    {{{     0,    102,      0}, 0, {  6612,     64}, {0x31, 0x73, 0xf1, 0xff}}},
    {{{    40,     81,     23}, 0, {159<<5,  64<<5}, {0x31, 0x74, 0x0f, 0xff}}},
    {{{    48,     81,      0}, 0, {191<<5,  64<<5}, {0x31, 0x74, 0x0f, 0xff}}},
    {{{     0,    102,      0}, 0, {  5590,     64}, {0x31, 0x74, 0x0f, 0xff}}},
    {{{    40,     81,    -23}, 0, {  7122,  64<<5}, {0x25, 0x73, 0xdb, 0xff}}},
    {{{    23,     81,    -40}, 0, {  8144,  64<<5}, {0x25, 0x73, 0xdb, 0xff}}},
    {{{     0,    102,      0}, 0, {  7634,     64}, {0x25, 0x73, 0xdb, 0xff}}},
    {{{    23,     81,    -40}, 0, {  8144,  64<<5}, {0x0f, 0x73, 0xce, 0xff}}},
    {{{     0,     81,    -48}, 0, {  9166,  64<<5}, {0x0f, 0x73, 0xce, 0xff}}},
    {{{     0,    102,      0}, 0, {  8656,     64}, {0x0f, 0x73, 0xce, 0xff}}},
    {{{     0,     81,    -48}, 0, {  9166,  64<<5}, {0xf1, 0x73, 0xce, 0xff}}},
    {{{   -23,     81,    -40}, 0, { 10188,  64<<5}, {0xf1, 0x73, 0xce, 0xff}}},
    {{{     0,    102,      0}, 0, {  9678,     64}, {0xf1, 0x73, 0xce, 0xff}}},
};

// 0x0500EB78
static const Vtx haunted_cage_seg5_vertex_0500EB78[] = {
    {{{   -23,     81,    -40}, 0, { 10188,  64<<5}, {0xdb, 0x73, 0xdb, 0xff}}},
    {{{   -40,     81,    -23}, 0, { 11210,  64<<5}, {0xdb, 0x73, 0xdb, 0xff}}},
    {{{     0,    102,      0}, 0, { 10698,     64}, {0xdb, 0x73, 0xdb, 0xff}}},
    {{{   -40,     81,    -23}, 0, { 11210,  64<<5}, {0xce, 0x73, 0xf1, 0xff}}},
    {{{   -48,     81,      0}, 0, { 12232,  64<<5}, {0xce, 0x73, 0xf1, 0xff}}},
    {{{     0,    102,      0}, 0, { 11722,     64}, {0xce, 0x73, 0xf1, 0xff}}},
    {{{   -48,     81,      0}, 0, {     0,  64<<5}, {0xce, 0x73, 0x0f, 0xff}}},
    {{{   -40,     81,     23}, 0, { 31<<5,  64<<5}, {0xce, 0x73, 0x0f, 0xff}}},
    {{{     0,    102,      0}, 0, { 15<<5,     64}, {0xce, 0x73, 0x0f, 0xff}}},
    {{{   -40,     81,     23}, 0, { 31<<5,  64<<5}, {0xdb, 0x73, 0x25, 0xff}}},
    {{{   -23,     81,     40}, 0, { 63<<5,  64<<5}, {0xdb, 0x73, 0x25, 0xff}}},
    {{{     0,    102,      0}, 0, { 47<<5,     64}, {0xdb, 0x73, 0x25, 0xff}}},
    {{{   -23,     81,     40}, 0, { 63<<5,  64<<5}, {0xf1, 0x73, 0x31, 0xff}}},
    {{{     0,     81,     48}, 0, { 95<<5,  64<<5}, {0xf1, 0x73, 0x31, 0xff}}},
    {{{     0,    102,      0}, 0, {  2524,     64}, {0xf1, 0x73, 0x31, 0xff}}},
};

// 0x0500EC68
static const Vtx haunted_cage_seg5_vertex_0500EC68[] = {
    {{{     0,     81,     48}, 0, { 95<<5,  64<<5}, {0x0f, 0x74, 0x31, 0xff}}},
    {{{    23,     81,     40}, 0, {127<<5,  64<<5}, {0x0f, 0x74, 0x31, 0xff}}},
    {{{     0,    102,      0}, 0, {  3546,     64}, {0x0f, 0x74, 0x31, 0xff}}},
    {{{    23,     81,     40}, 0, {127<<5,  64<<5}, {0x24, 0x73, 0x24, 0xff}}},
    {{{    40,     81,     23}, 0, {159<<5,  64<<5}, {0x24, 0x73, 0x24, 0xff}}},
    {{{     0,    102,      0}, 0, {  4568,     64}, {0x24, 0x73, 0x24, 0xff}}},
};

// 0x0500ECC8
static const Vtx haunted_cage_seg5_vertex_0500ECC8[] = {
    {{{   -44,      0,    -26}, 0, { 11210,  15<<5}, {0xa7, 0x00, 0xa7, 0xff}}},
    {{{   -26,     10,    -44}, 0, { 10188,      0}, {0xa7, 0x00, 0xa7, 0xff}}},
    {{{   -26,      0,    -44}, 0, { 10188,  15<<5}, {0xa7, 0x00, 0xa7, 0xff}}},
    {{{    44,      0,    -26}, 0, {  7122,  15<<5}, {0x7a, 0x00, 0xde, 0xff}}},
    {{{    51,     10,      0}, 0, {191<<5,      0}, {0x7a, 0x00, 0xde, 0xff}}},
    {{{    51,      0,      0}, 0, {191<<5,  15<<5}, {0x7a, 0x00, 0xde, 0xff}}},
    {{{    26,      0,    -44}, 0, {  8144,  15<<5}, {0x59, 0x00, 0xa7, 0xff}}},
    {{{    44,     10,    -26}, 0, {  7122,      0}, {0x59, 0x00, 0xa7, 0xff}}},
    {{{    44,      0,    -26}, 0, {  7122,  15<<5}, {0x59, 0x00, 0xa7, 0xff}}},
    {{{    44,     10,    -26}, 0, {  7122,      0}, {0x7a, 0x00, 0xde, 0xff}}},
    {{{    26,     10,    -44}, 0, {  8144,      0}, {0x59, 0x00, 0xa7, 0xff}}},
    {{{    51,      0,      0}, 0, {191<<5,  15<<5}, {0x7a, 0x00, 0x21, 0xff}}},
    {{{    51,     10,      0}, 0, {191<<5,      0}, {0x7a, 0x00, 0x21, 0xff}}},
    {{{    44,     10,     26}, 0, {159<<5,      0}, {0x7a, 0x00, 0x21, 0xff}}},
    {{{    44,      0,     26}, 0, {159<<5,  15<<5}, {0x7a, 0x00, 0x21, 0xff}}},
};

// 0x0500EDB8
static const Vtx haunted_cage_seg5_vertex_0500EDB8[] = {
    {{{     0,      0,    -51}, 0, {  9166,  15<<5}, {0x21, 0x00, 0x86, 0xff}}},
    {{{    26,     10,    -44}, 0, {  8144,      0}, {0x21, 0x00, 0x86, 0xff}}},
    {{{    26,      0,    -44}, 0, {  8144,  15<<5}, {0x21, 0x00, 0x86, 0xff}}},
    {{{     0,     10,    -51}, 0, {  9166,      0}, {0x21, 0x00, 0x86, 0xff}}},
    {{{   -26,      0,    -44}, 0, { 10188,  15<<5}, {0xde, 0x00, 0x86, 0xff}}},
    {{{     0,     10,    -51}, 0, {  9166,      0}, {0xde, 0x00, 0x86, 0xff}}},
    {{{     0,      0,    -51}, 0, {  9166,  15<<5}, {0xde, 0x00, 0x86, 0xff}}},
    {{{   -26,     10,    -44}, 0, { 10188,      0}, {0xde, 0x00, 0x86, 0xff}}},
    {{{     0,      0,     51}, 0, { 95<<5,  15<<5}, {0xde, 0x00, 0x7a, 0xff}}},
    {{{     0,     10,     51}, 0, { 95<<5,      0}, {0xde, 0x00, 0x7a, 0xff}}},
    {{{   -26,     10,     44}, 0, { 63<<5,      0}, {0xde, 0x00, 0x7a, 0xff}}},
    {{{   -44,      0,    -26}, 0, { 11210,  15<<5}, {0xa7, 0x00, 0xa7, 0xff}}},
    {{{   -44,     10,    -26}, 0, { 11210,      0}, {0xa7, 0x00, 0xa7, 0xff}}},
    {{{   -26,     10,    -44}, 0, { 10188,      0}, {0xa7, 0x00, 0xa7, 0xff}}},
};

// 0x0500EE98
static const Vtx haunted_cage_seg5_vertex_0500EE98[] = {
    {{{   -51,      0,      0}, 0, { 12232,  15<<5}, {0x86, 0x00, 0xde, 0xff}}},
    {{{   -44,     10,    -26}, 0, { 11210,      0}, {0x86, 0x00, 0xde, 0xff}}},
    {{{   -44,      0,    -26}, 0, { 11210,  15<<5}, {0x86, 0x00, 0xde, 0xff}}},
    {{{   -51,     10,      0}, 0, { 12232,      0}, {0x86, 0x00, 0xde, 0xff}}},
    {{{   -44,      0,     26}, 0, { 31<<5,  15<<5}, {0x86, 0x00, 0x21, 0xff}}},
    {{{   -44,     10,     26}, 0, { 31<<5,      0}, {0x86, 0x00, 0x21, 0xff}}},
    {{{   -51,     10,      0}, 0, {     0,      0}, {0x86, 0x00, 0x21, 0xff}}},
    {{{   -51,      0,      0}, 0, {     0,  15<<5}, {0x86, 0x00, 0x21, 0xff}}},
    {{{   -26,      0,     44}, 0, { 63<<5,  15<<5}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{   -44,     10,     26}, 0, { 31<<5,      0}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{   -44,      0,     26}, 0, { 31<<5,  15<<5}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{   -26,     10,     44}, 0, { 63<<5,      0}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{     0,      0,     51}, 0, { 95<<5,  15<<5}, {0xde, 0x00, 0x7a, 0xff}}},
    {{{   -26,     10,     44}, 0, { 63<<5,      0}, {0xde, 0x00, 0x7a, 0xff}}},
    {{{   -26,      0,     44}, 0, { 63<<5,  15<<5}, {0xde, 0x00, 0x7a, 0xff}}},
};

// 0x0500EF88
static const Vtx haunted_cage_seg5_vertex_0500EF88[] = {
    {{{    26,      0,     44}, 0, {127<<5,  15<<5}, {0x21, 0x00, 0x7a, 0xff}}},
    {{{     0,     10,     51}, 0, { 95<<5,      0}, {0x21, 0x00, 0x7a, 0xff}}},
    {{{     0,      0,     51}, 0, { 95<<5,  15<<5}, {0x21, 0x00, 0x7a, 0xff}}},
    {{{    26,     10,     44}, 0, {127<<5,      0}, {0x21, 0x00, 0x7a, 0xff}}},
    {{{    44,      0,     26}, 0, {159<<5,  15<<5}, {0x59, 0x00, 0x59, 0xff}}},
    {{{    26,     10,     44}, 0, {127<<5,      0}, {0x59, 0x00, 0x59, 0xff}}},
    {{{    26,      0,     44}, 0, {127<<5,  15<<5}, {0x59, 0x00, 0x59, 0xff}}},
    {{{    44,     10,     26}, 0, {159<<5,      0}, {0x59, 0x00, 0x59, 0xff}}},
};

// 0x0500F008
static const Vtx haunted_cage_seg5_vertex_0500F008[] = {
    {{{    44,     64,    -26}, 0, {  7122,  31<<5}, {0x74, 0x21, 0xdb, 0xff}}},
    {{{    40,     81,    -23}, 0, {  7122,    -72}, {0x74, 0x21, 0xdb, 0xff}}},
    {{{    48,     81,      0}, 0, {191<<5,    -72}, {0x74, 0x21, 0xdb, 0xff}}},
    {{{    26,     64,    -44}, 0, {  8144,  31<<5}, {0x56, 0x23, 0xaa, 0xff}}},
    {{{    40,     81,    -23}, 0, {  7122,    -72}, {0x56, 0x23, 0xaa, 0xff}}},
    {{{    44,     64,    -26}, 0, {  7122,  31<<5}, {0x56, 0x23, 0xaa, 0xff}}},
    {{{    44,     64,    -26}, 0, {  7122,  31<<5}, {0x77, 0x1c, 0xdf, 0xff}}},
    {{{    48,     81,      0}, 0, {191<<5,    -72}, {0x77, 0x1c, 0xdf, 0xff}}},
    {{{    51,     64,      0}, 0, {191<<5,  31<<5}, {0x77, 0x1c, 0xdf, 0xff}}},
    {{{    23,     81,    -40}, 0, {  8144,    -72}, {0x56, 0x23, 0xaa, 0xff}}},
    {{{    51,     64,      0}, 0, {191<<5,  31<<5}, {0x76, 0x1b, 0x24, 0xff}}},
    {{{    48,     81,      0}, 0, {191<<5,    -72}, {0x76, 0x1b, 0x24, 0xff}}},
    {{{    40,     81,     23}, 0, {159<<5,    -72}, {0x76, 0x1b, 0x24, 0xff}}},
    {{{    51,     64,      0}, 0, {191<<5,  31<<5}, {0x76, 0x21, 0x1f, 0xff}}},
    {{{    40,     81,     23}, 0, {159<<5,    -72}, {0x76, 0x21, 0x1f, 0xff}}},
    {{{    44,     64,     26}, 0, {159<<5,  31<<5}, {0x76, 0x21, 0x1f, 0xff}}},
};

// 0x0500F108
static const Vtx haunted_cage_seg5_vertex_0500F108[] = {
    {{{     0,     81,    -48}, 0, {  9166,    -72}, {0x23, 0x21, 0x8b, 0xff}}},
    {{{    23,     81,    -40}, 0, {  8144,    -72}, {0x23, 0x21, 0x8b, 0xff}}},
    {{{    26,     64,    -44}, 0, {  8144,  31<<5}, {0x23, 0x21, 0x8b, 0xff}}},
    {{{     0,     64,    -51}, 0, {  9166,  31<<5}, {0x20, 0x1c, 0x89, 0xff}}},
    {{{     0,     81,    -48}, 0, {  9166,    -72}, {0x20, 0x1c, 0x89, 0xff}}},
    {{{    26,     64,    -44}, 0, {  8144,  31<<5}, {0x20, 0x1c, 0x89, 0xff}}},
    {{{   -26,     64,    -44}, 0, { 10188,  31<<5}, {0xdf, 0x1c, 0x89, 0xff}}},
    {{{     0,     81,    -48}, 0, {  9166,    -72}, {0xdf, 0x1c, 0x89, 0xff}}},
    {{{     0,     64,    -51}, 0, {  9166,  31<<5}, {0xdf, 0x1c, 0x89, 0xff}}},
    {{{   -26,     64,    -44}, 0, { 10188,  31<<5}, {0xdb, 0x21, 0x8c, 0xff}}},
    {{{   -23,     81,    -40}, 0, { 10188,    -72}, {0xdb, 0x21, 0x8c, 0xff}}},
    {{{     0,     81,    -48}, 0, {  9166,    -72}, {0xdb, 0x21, 0x8c, 0xff}}},
    {{{   -44,     64,    -26}, 0, { 11210,  31<<5}, {0xaa, 0x23, 0xaa, 0xff}}},
    {{{   -40,     81,    -23}, 0, { 11210,    -72}, {0xaa, 0x23, 0xaa, 0xff}}},
    {{{   -26,     64,    -44}, 0, { 10188,  31<<5}, {0xaa, 0x23, 0xaa, 0xff}}},
    {{{   -23,     81,    -40}, 0, { 10188,    -72}, {0xaa, 0x23, 0xaa, 0xff}}},
};

// 0x0500F208
static const Vtx haunted_cage_seg5_vertex_0500F208[] = {
    {{{   -51,     64,      0}, 0, { 12232,  31<<5}, {0x8b, 0x21, 0xdf, 0xff}}},
    {{{   -40,     81,    -23}, 0, { 11210,    -72}, {0x8b, 0x21, 0xdf, 0xff}}},
    {{{   -44,     64,    -26}, 0, { 11210,  31<<5}, {0x8b, 0x21, 0xdf, 0xff}}},
    {{{   -51,     64,      0}, 0, { 12232,  31<<5}, {0x8a, 0x1b, 0xdb, 0xff}}},
    {{{   -48,     81,      0}, 0, { 12232,    -72}, {0x8a, 0x1b, 0xdb, 0xff}}},
    {{{   -40,     81,    -23}, 0, { 11210,    -72}, {0x8a, 0x1b, 0xdb, 0xff}}},
    {{{   -26,     64,     44}, 0, { 63<<5,  31<<5}, {0xaa, 0x23, 0x56, 0xff}}},
    {{{   -40,     81,     23}, 0, { 31<<5,    -72}, {0xaa, 0x23, 0x56, 0xff}}},
    {{{   -44,     64,     26}, 0, { 31<<5,  31<<5}, {0xaa, 0x23, 0x56, 0xff}}},
    {{{   -44,     64,     26}, 0, { 31<<5,  31<<5}, {0x8b, 0x21, 0x23, 0xff}}},
    {{{   -40,     81,     23}, 0, { 31<<5,    -72}, {0x8b, 0x21, 0x23, 0xff}}},
    {{{   -48,     81,      0}, 0, {     0,    -72}, {0x8b, 0x21, 0x23, 0xff}}},
    {{{   -44,     64,     26}, 0, { 31<<5,  31<<5}, {0x89, 0x1c, 0x20, 0xff}}},
    {{{   -48,     81,      0}, 0, {     0,    -72}, {0x89, 0x1c, 0x20, 0xff}}},
    {{{   -51,     64,      0}, 0, {     0,  31<<5}, {0x89, 0x1c, 0x20, 0xff}}},
    {{{   -23,     81,     40}, 0, { 63<<5,    -72}, {0xaa, 0x23, 0x56, 0xff}}},
};

// 0x0500F308
static const Vtx haunted_cage_seg5_vertex_0500F308[] = {
    {{{     0,     64,     51}, 0, { 95<<5,  31<<5}, {0xdf, 0x1c, 0x77, 0xff}}},
    {{{     0,     81,     48}, 0, { 95<<5,    -72}, {0xdf, 0x1c, 0x77, 0xff}}},
    {{{   -26,     64,     44}, 0, { 63<<5,  31<<5}, {0xdf, 0x1c, 0x77, 0xff}}},
    {{{     0,     81,     48}, 0, { 95<<5,    -72}, {0xdb, 0x21, 0x74, 0xff}}},
    {{{   -23,     81,     40}, 0, { 63<<5,    -72}, {0xdb, 0x21, 0x74, 0xff}}},
    {{{   -26,     64,     44}, 0, { 63<<5,  31<<5}, {0xdb, 0x21, 0x74, 0xff}}},
    {{{    26,     64,     44}, 0, {127<<5,  31<<5}, {0x23, 0x21, 0x75, 0xff}}},
    {{{    23,     81,     40}, 0, {127<<5,    -72}, {0x23, 0x21, 0x75, 0xff}}},
    {{{     0,     81,     48}, 0, { 95<<5,    -72}, {0x23, 0x21, 0x75, 0xff}}},
    {{{    26,     64,     44}, 0, {127<<5,  31<<5}, {0x20, 0x1c, 0x77, 0xff}}},
    {{{     0,     81,     48}, 0, { 95<<5,    -72}, {0x20, 0x1c, 0x77, 0xff}}},
    {{{     0,     64,     51}, 0, { 95<<5,  31<<5}, {0x20, 0x1c, 0x77, 0xff}}},
    {{{    40,     81,     23}, 0, {159<<5,    -72}, {0x56, 0x23, 0x56, 0xff}}},
    {{{    23,     81,     40}, 0, {127<<5,    -72}, {0x56, 0x23, 0x56, 0xff}}},
    {{{    26,     64,     44}, 0, {127<<5,  31<<5}, {0x56, 0x23, 0x56, 0xff}}},
    {{{    44,     64,     26}, 0, {159<<5,  31<<5}, {0x56, 0x23, 0x56, 0xff}}},
};

// 0x0500F408
static const Vtx haunted_cage_seg5_vertex_0500F408[] = {
    {{{   -44,      0,    -26}, 0, {  5204,  -2624}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{     0,      0,     51}, 0, { -1056,  -8882}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{    26,      0,     44}, 0, { -3342,  -7560}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   -26,      0,     44}, 0, {  1592,  -8882}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   -51,      0,      0}, 0, {  5204,  -5268}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   -44,      0,     26}, 0, {  3882,  -7560}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{    26,      0,    -44}, 0, { -1056,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{     0,      0,    -51}, 0, {  1592,  31<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{    44,      0,    -26}, 0, { -3342,   -336}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   -26,      0,    -44}, 0, {  3882,   -336}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{    51,      0,      0}, 0, { -4666,  -2624}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{    44,      0,     26}, 0, { -4666,  -5268}, {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x0500F4C8 - 0x0500F660
const Gfx haunted_cage_seg5_dl_ornament[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, haunted_cage_seg5_texture_ornament),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&haunted_cage_seg5_lights_0500C258.l, 1),
    gsSPLight(&haunted_cage_seg5_lights_0500C258.a, 2),
    gsSPVertex(haunted_cage_seg5_vertex_0500EA88, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(haunted_cage_seg5_vertex_0500EB78, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(haunted_cage_seg5_vertex_0500EC68, 6, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSPLight(&haunted_cage_seg5_lights_0500C270.l, 1),
    gsSPLight(&haunted_cage_seg5_lights_0500C270.a, 2),
    gsSPVertex(haunted_cage_seg5_vertex_0500ECC8, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  3,  9,  4, 0x0),
    gsSP2Triangles( 6, 10,  7, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(haunted_cage_seg5_vertex_0500EDB8, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(haunted_cage_seg5_vertex_0500EE98, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSP1Triangle(12, 13, 14, 0x0),
    gsSPVertex(haunted_cage_seg5_vertex_0500EF88, 8, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500F660 - 0x0500F760
const Gfx haunted_cage_seg5_dl_double_ornament[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, haunted_cage_seg5_texture_double_ornament),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(haunted_cage_seg5_vertex_0500F008, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  3,  9,  4, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 13, 14, 15, 0x0),
    gsSPVertex(haunted_cage_seg5_vertex_0500F108, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 13, 15, 14, 0x0),
    gsSPVertex(haunted_cage_seg5_vertex_0500F208, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0,  6, 15,  7, 0x0),
    gsSPVertex(haunted_cage_seg5_vertex_0500F308, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  9, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 15, 12, 14, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500F760 - 0x0500F7D8
const Gfx haunted_cage_seg5_dl_floor[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, haunted_cage_seg5_texture_floor),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPVertex(haunted_cage_seg5_vertex_0500F408, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  3,  1, 0x0),
    gsSP2Triangles( 0,  4,  5, 0x0,  0,  5,  3, 0x0),
    gsSP2Triangles( 0,  6,  7, 0x0,  0,  8,  6, 0x0),
    gsSP2Triangles( 0,  7,  9, 0x0,  0, 10,  8, 0x0),
    gsSP2Triangles( 0, 11, 10, 0x0,  0,  2, 11, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500F7D8 - 0x0500F888
const Gfx haunted_cage_seg5_dl_0500F7D8[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 4, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (16 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(haunted_cage_seg5_dl_ornament),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(haunted_cage_seg5_dl_double_ornament),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(haunted_cage_seg5_dl_floor),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

// 0x0500F888
static const Lights1 haunted_cage_seg5_lights_0500F888 = gdSPDefLights1(
    0x66, 0x66, 0x66,
    0xff, 0xff, 0xff, 0x28, 0x28, 0x28
);

// 0x0500F8A0
static const Vtx haunted_cage_seg5_vertex_0500F8A0[] = {
    {{{   -19,      0,     10}, 0, { 95<<5,  15<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   -19,     28,    -19}, 0, {     0,  -2350}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   -19,      0,    -19}, 0, {     0,  15<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{    20,      0,     10}, 0, {127<<5,  15<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   -19,     28,     10}, 0, {     0,  -2350}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   -19,      0,     10}, 0, {     0,  15<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{    20,     28,     10}, 0, {127<<5,  -2350}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   -19,      0,    -19}, 0, {127<<5,  15<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{    20,     28,    -19}, 0, {     0,  -2350}, {0x00, 0x00, 0x81, 0xff}}},
    {{{    20,      0,    -19}, 0, {     0,  15<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   -19,     28,    -19}, 0, {127<<5,  -2350}, {0x00, 0x00, 0x81, 0xff}}},
    {{{    20,     28,    -19}, 0, {127<<5,  -2587}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   -19,     28,    -19}, 0, {     0,  -2587}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   -19,     28,     10}, 0, {     0,  15<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{    20,     28,     10}, 0, {127<<5,  15<<5}, {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x0500F990
static const Vtx haunted_cage_seg5_vertex_0500F990[] = {
    {{{   -30,      0,     39}, 0, { 31<<5,  15<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   -30,     10,     39}, 0, { 31<<5,   -544}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   -30,     10,     29}, 0, {     0,   -544}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   -19,      0,     10}, 0, { 95<<5,  15<<5}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   -19,     28,     10}, 0, { 95<<5,  -2350}, {0x81, 0x00, 0x00, 0xff}}},
    {{{   -19,     28,    -19}, 0, {     0,  -2350}, {0x81, 0x00, 0x00, 0xff}}},
    {{{    20,      0,    -19}, 0, { 95<<5,  15<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{    20,     28,     10}, 0, {     0,  -2350}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{    20,      0,     10}, 0, {     0,  15<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{    20,     28,    -19}, 0, { 95<<5,  -2350}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   -19,      0,     39}, 0, { 31<<5,  15<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   -30,     10,     39}, 0, {     0,   -544}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   -30,      0,     39}, 0, {     0,  15<<5}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   -19,     10,     39}, 0, { 31<<5,   -544}, {0x00, 0x00, 0x7f, 0xff}}},
    {{{   -30,      0,     29}, 0, {     0,  15<<5}, {0x81, 0x00, 0x00, 0xff}}},
};

// 0x0500FA80
static const Vtx haunted_cage_seg5_vertex_0500FA80[] = {
    {{{   -30,      0,     29}, 0, { 31<<5,  15<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   -30,     10,     29}, 0, { 31<<5,   -544}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   -19,     10,     29}, 0, {     0,   -544}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   -19,      0,     29}, 0, {     0,  15<<5}, {0x00, 0x00, 0x81, 0xff}}},
    {{{   -19,      0,     29}, 0, { 31<<5,  15<<5}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   -19,     10,     39}, 0, {    38,   -616}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   -19,      0,     39}, 0, {     0,    408}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   -19,     10,     29}, 0, { 33<<5,   -544}, {0x7f, 0x00, 0x00, 0xff}}},
    {{{   -19,     10,     39}, 0, { 31<<5,  15<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   -30,     10,     29}, 0, {     0,   -544}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   -30,     10,     39}, 0, {     0,  15<<5}, {0x00, 0x7f, 0x00, 0xff}}},
    {{{   -19,     10,     29}, 0, { 31<<5,   -544}, {0x00, 0x7f, 0x00, 0xff}}},
};

// 0x0500FB40 - 0x0500FC28
const Gfx haunted_cage_seg5_sub_dl_wooden_base[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, haunted_cage_seg5_texture_wooden_base),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 16 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&haunted_cage_seg5_lights_0500F888.l, 1),
    gsSPLight(&haunted_cage_seg5_lights_0500F888.a, 2),
    gsSPVertex(haunted_cage_seg5_vertex_0500F8A0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  6,  4, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7, 10,  8, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(haunted_cage_seg5_vertex_0500F990, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 6,  7,  8, 0x0,  6,  9,  7, 0x0),
    gsSP2Triangles(10, 11, 12, 0x0, 10, 13, 11, 0x0),
    gsSP1Triangle( 0,  2, 14, 0x0),
    gsSPVertex(haunted_cage_seg5_vertex_0500FA80, 12, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  7,  5, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 11,  9, 0x0),
    gsSPEndDisplayList(),
};

// 0x0500FC28 - 0x0500FC98
const Gfx haunted_cage_seg5_dl_wooden_base[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGB, G_CC_MODULATERGB),
    gsSPClearGeometryMode(G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 4, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (16 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(haunted_cage_seg5_sub_dl_wooden_base),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

// 0x0500FC98
static const Lights1 haunted_cage_seg5_lights_0500FC98 = gdSPDefLights1(
    0x2c, 0x2c, 0x2c,
    0xb2, 0xb2, 0xb2, 0x28, 0x28, 0x28
);

// 0x0500FCB0
static const Vtx haunted_cage_seg5_vertex_0500FCB0[] = {
    {{{   -44,     10,     26}, 0, {  8484,  31<<5}, {0x86, 0x00, 0x21, 0xff}}},
    {{{   -44,     64,     26}, 0, {  8484,   6370}, {0x86, 0x00, 0x21, 0xff}}},
    {{{   -51,     64,      0}, 0, { 10188,   6370}, {0x86, 0x00, 0x21, 0xff}}},
    {{{    51,     10,      0}, 0, {     0,  31<<5}, {0x7a, 0x00, 0x21, 0xff}}},
    {{{    51,     64,      0}, 0, {     0,   6370}, {0x7a, 0x00, 0x21, 0xff}}},
    {{{    44,     64,     26}, 0, {  1672,   6370}, {0x7a, 0x00, 0x21, 0xff}}},
    {{{    44,     10,     26}, 0, {  1672,  31<<5}, {0x7a, 0x00, 0x21, 0xff}}},
    {{{    44,     10,     26}, 0, {  1672,  31<<5}, {0x59, 0x00, 0x59, 0xff}}},
    {{{    44,     64,     26}, 0, {  1672,   6370}, {0x59, 0x00, 0x59, 0xff}}},
    {{{    26,     64,     44}, 0, {  3374,   6370}, {0x59, 0x00, 0x59, 0xff}}},
    {{{    26,     10,     44}, 0, {  3374,  31<<5}, {0x59, 0x00, 0x59, 0xff}}},
    {{{    26,     10,     44}, 0, {  3374,  31<<5}, {0x21, 0x00, 0x7a, 0xff}}},
    {{{    26,     64,     44}, 0, {  3374,   6370}, {0x21, 0x00, 0x7a, 0xff}}},
    {{{     0,     64,     51}, 0, {159<<5,   6370}, {0x21, 0x00, 0x7a, 0xff}}},
    {{{     0,     10,     51}, 0, {159<<5,  31<<5}, {0x21, 0x00, 0x7a, 0xff}}},
};

// 0x0500FDA0
static const Vtx haunted_cage_seg5_vertex_0500FDA0[] = {
    {{{     0,     10,     51}, 0, {159<<5,  31<<5}, {0xde, 0x00, 0x7a, 0xff}}},
    {{{     0,     64,     51}, 0, {159<<5,   6370}, {0xde, 0x00, 0x7a, 0xff}}},
    {{{   -26,     64,     44}, 0, {  6782,   6370}, {0xde, 0x00, 0x7a, 0xff}}},
    {{{   -26,     10,     44}, 0, {  6782,  31<<5}, {0xde, 0x00, 0x7a, 0xff}}},
    {{{   -26,     10,     44}, 0, {  6782,  31<<5}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{   -26,     64,     44}, 0, {  6782,   6370}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{   -44,     64,     26}, 0, {  8484,   6370}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{   -44,     10,     26}, 0, {  8484,  31<<5}, {0xa7, 0x00, 0x59, 0xff}}},
    {{{    26,     10,    -44}, 0, { 17002,  31<<5}, {0x59, 0x00, 0xa7, 0xff}}},
    {{{    44,     64,    -26}, 0, { 18704,   6370}, {0x59, 0x00, 0xa7, 0xff}}},
    {{{    44,     10,    -26}, 0, { 18704,  31<<5}, {0x59, 0x00, 0xa7, 0xff}}},
    {{{   -44,     10,     26}, 0, {  8484,  31<<5}, {0x86, 0x00, 0x21, 0xff}}},
    {{{   -51,     64,      0}, 0, { 10188,   6370}, {0x86, 0x00, 0x21, 0xff}}},
    {{{   -51,     10,      0}, 0, { 10188,  31<<5}, {0x86, 0x00, 0x21, 0xff}}},
};

// 0x0500FE80
static const Vtx haunted_cage_seg5_vertex_0500FE80[] = {
    {{{   -51,     10,      0}, 0, { 10188,  31<<5}, {0x86, 0x00, 0xde, 0xff}}},
    {{{   -51,     64,      0}, 0, { 10188,   6370}, {0x86, 0x00, 0xde, 0xff}}},
    {{{   -44,     64,    -26}, 0, { 11892,   6370}, {0x86, 0x00, 0xde, 0xff}}},
    {{{   -44,     10,    -26}, 0, { 11892,  31<<5}, {0x86, 0x00, 0xde, 0xff}}},
    {{{   -44,     10,    -26}, 0, { 11892,  31<<5}, {0xa7, 0x00, 0xa7, 0xff}}},
    {{{   -44,     64,    -26}, 0, { 11892,   6370}, {0xa7, 0x00, 0xa7, 0xff}}},
    {{{   -26,     64,    -44}, 0, { 13594,   6370}, {0xa7, 0x00, 0xa7, 0xff}}},
    {{{   -26,     10,    -44}, 0, { 13594,  31<<5}, {0xa7, 0x00, 0xa7, 0xff}}},
    {{{   -26,     10,    -44}, 0, { 13594,  31<<5}, {0xde, 0x00, 0x86, 0xff}}},
    {{{   -26,     64,    -44}, 0, { 13594,   6370}, {0xde, 0x00, 0x86, 0xff}}},
    {{{     0,     64,    -51}, 0, { 15298,   6370}, {0xde, 0x00, 0x86, 0xff}}},
    {{{     0,     10,    -51}, 0, { 15298,  31<<5}, {0xde, 0x00, 0x86, 0xff}}},
    {{{     0,     10,    -51}, 0, { 15298,  31<<5}, {0x21, 0x00, 0x86, 0xff}}},
    {{{     0,     64,    -51}, 0, { 15298,   6370}, {0x21, 0x00, 0x86, 0xff}}},
    {{{    26,     64,    -44}, 0, { 17002,   6370}, {0x21, 0x00, 0x86, 0xff}}},
    {{{    26,     10,    -44}, 0, { 17002,  31<<5}, {0x21, 0x00, 0x86, 0xff}}},
};

// 0x0500FF80
static const Vtx haunted_cage_seg5_vertex_0500FF80[] = {
    {{{    26,     10,    -44}, 0, { 17002,  31<<5}, {0x59, 0x00, 0xa7, 0xff}}},
    {{{    26,     64,    -44}, 0, { 17002,   6370}, {0x59, 0x00, 0xa7, 0xff}}},
    {{{    44,     64,    -26}, 0, { 18704,   6370}, {0x59, 0x00, 0xa7, 0xff}}},
    {{{    44,     10,    -26}, 0, { 18704,  31<<5}, {0x7a, 0x00, 0xde, 0xff}}},
    {{{    44,     64,    -26}, 0, { 18704,   6370}, {0x7a, 0x00, 0xde, 0xff}}},
    {{{    51,     64,      0}, 0, { 20408,   6370}, {0x7a, 0x00, 0xde, 0xff}}},
    {{{    51,     10,      0}, 0, { 20408,  31<<5}, {0x7a, 0x00, 0xde, 0xff}}},
};

// 0x0500FFF0 - 0x05010100
const Gfx haunted_cage_seg5_sub_dl_bars[] = {
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, haunted_cage_seg5_texture_bars),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsSPLight(&haunted_cage_seg5_lights_0500FC98.l, 1),
    gsSPLight(&haunted_cage_seg5_lights_0500FC98.a, 2),
    gsSPVertex(haunted_cage_seg5_vertex_0500FCB0, 15, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP2Triangles( 3,  5,  6, 0x0,  7,  8,  9, 0x0),
    gsSP2Triangles( 7,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSP1Triangle(11, 13, 14, 0x0),
    gsSPVertex(haunted_cage_seg5_vertex_0500FDA0, 14, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0, 11, 12, 13, 0x0),
    gsSPVertex(haunted_cage_seg5_vertex_0500FE80, 16, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSP2Triangles( 4,  5,  6, 0x0,  4,  6,  7, 0x0),
    gsSP2Triangles( 8,  9, 10, 0x0,  8, 10, 11, 0x0),
    gsSP2Triangles(12, 13, 14, 0x0, 12, 14, 15, 0x0),
    gsSPVertex(haunted_cage_seg5_vertex_0500FF80, 7, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  3,  4,  5, 0x0),
    gsSP1Triangle( 3,  5,  6, 0x0),
    gsSPEndDisplayList(),
};

// 0x05010100 - 0x05010170
const Gfx haunted_cage_seg5_dl_bars[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_MODULATERGBA, G_CC_MODULATERGBA),
    gsSPClearGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPTileSync(),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, (32 - 1) << G_TEXTURE_IMAGE_FRAC, (32 - 1) << G_TEXTURE_IMAGE_FRAC),
    gsSPDisplayList(haunted_cage_seg5_sub_dl_bars),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPSetGeometryMode(G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
