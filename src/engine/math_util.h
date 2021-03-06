#pragma once

#include <PR/ultratypes.h>

#include "types.h"

// #define CLAMP_BITS(val, size) (MIN((val), BITMASK((u32)(size))))

#define NEAR_ZERO   0.00001f
#define NEARER_ZERO 0.000001f
#define NEAR_ONE    0.99999f


struct Row4 {
    f32 c0, c1, c2, c3;
};

struct InvMat4 {
    struct Row4 r0, r1, r2, r3;
};

enum RotAxis {
    X_AXIS,
    Y_AXIS,
    Z_AXIS
};

/*
 * The sine and cosine tables overlap, but "#define gCosineTable (gSineTable +
 * 0x400)" doesn't give expected codegen; gSineTable and gCosineTable need to
 * be different symbols for code to match. Most likely the tables were placed
 * adjacent to each other, and gSineTable cut short, such that reads overflow
 * into gCosineTable.
 *
 * These kinds of out of bounds reads are undefined behavior, and break on
 * e.g. GCC (which doesn't place the tables next to each other, and probably
 * exploits array sizes for range analysis-based optimizations as well).
 * Thus, for non-IDO compilers we use the standard-compliant version.
 */
extern f32 gSineTable[];
#define gCosineTable (gSineTable + 0x400)
extern s16 gArctanTable[];

extern Vec3f gVec3fX;
extern Vec3f gVec3fY;
extern Vec3f gVec3fZ;
extern Vec3f gVec3fMX;
extern Vec3f gVec3fMY;
extern Vec3f gVec3fMZ;
extern Vec3f gVec3fZero;
extern Vec3s gVec3sZero;
extern Vec3i gVec3iZero;
extern Vec3f gVec3fOne;
extern Vec3s gVec3sOne;


#define ABSF(x) ((x) > 0.0f ? (x) : -(x))
#define ABSI(x) ((x) > 0    ? (x) : -(x))

#define SIGNUM(x)   (((x) < 0) ? -1 : 1)
#define SIGNUMF(x)  (((x) > 0.0f) ? 1.0f : (((x) < 0.0f) ? -1.0f : 0.0f))
// #define SIGNUMF(x)  (((x) == 0.0f) ? 0.0f : (((x) < 0.0f) ? -1.0f : 1.0f))

/**
 * Converts an angle in degrees to sm64's s16 angle units. For example, DEG(90) == 0x4000
 * This should be used mainly to make camera code clearer at first glance.
 */
// #define DEG(x) (Angle)((x) * 0x10000 / 360)
#define DEG(x) (Angle)((x) *  0x2000 /  45)

// #define DEG30   0x1555
// #define DEG45   0x2000
// #define DEG60   0x2AAA
// #define DEG90   0x4000
// #define DEG120  0x5555
// #define DEG135  0x6000
// #define DEG180  0x8000
// #define DEGN135 0xA000
// #define DEGN120 0xAAAB
// #define DEGN90  0xC000
// #define DEGN60  0xD555
// #define DEGN45  0xE000
// #define DEGN30  0xEAAB

#define DEG_PER_RAD 57.29577950560105
#define RAD_PER_DEG (1.0 / DEG_PER_RAD)

#define angle_to_degrees(  x) (f32)(((Angle)(x) / 65536.0f) * 360.0f)
#define degrees_to_angle(  x) (Angle)(((f32)(x) * 0x10000 ) / 360   )
#define angle_to_radians(  x) (f32)(((Angle)(x) * M_PI    ) / 0x8000)
#define radians_to_angle(  x) (Angle)(((f32)(x) / M_PI    ) * 0x8000)
#define degrees_to_radians(x) (f32)(   (f32)(x) * RAD_PER_DEG       )
#define radians_to_degrees(x) (f32)(   (f32)(x) * DEG_PER_RAD       )


#define CONST_EULER_D 2.71828182845904523536028747135266249775724709369995
#define CONST_EULER_F 2.71828182845904523536028747135266249775724709369995f

#define sins(x)  gSineTable[  (u16) (x) >> 4]
#define coss(x)  gCosineTable[(u16) (x) >> 4]
#define atans(x) gArctanTable[(s32)((((x) * 1024) + 0.5f))] //! is this correct? used for atan2_lookup


#define min(a, b) MIN((a), (b))
#define max(a, b) MAX((a), (b))

#define min_3(a, b, c)  ((((a) > (b)) || ((a) > (c))) ? (((b) > (c)) ? (c) : (b)) : (a))
#define max_3(a, b, c)  ((((a) < (b)) || ((a) < (c))) ? (((b) < (c)) ? (c) : (b)) : (a))

#define CLAMP(x, low, high)  (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))

#define sind(x)  sinf(x)
#define cosd(x)  cosf(x)
#define sqrtd(x) sqrtf(x)

// From Puppycam
#define LENSIN(length, direction) ((length) * sins((direction)))
#define LENCOS(length, direction) ((length) * coss((direction)))

// from limits.h
#define S8_MAX __SCHAR_MAX__
#define S8_MIN (-S8_MAX - 1)
#define U8_MAX (S8_MAX * 2 + 1)
#define S16_MAX __SHRT_MAX__
#define S16_MIN (-S16_MAX - 1)
#define U16_MAX (S16_MAX * 2 + 1)
#define S32_MAX __INT_MAX__
#define S32_MIN (-S32_MAX - 1)
#define U32_MAX (S32_MAX * 2U + 1U)
#define S64_MAX __LONG_LONG_MAX__
#define S64_MIN (-S64_MAX - 1LL)
#define U64_MAX (S64_MAX * 2ULL + 1ULL)
#define F32_MAX __FLT_MAX__
#define F32_MIN __FLT_MIN__
#define F64_MAX __DBL_MAX__
#define F64_MIN __DBL_MIN__

#define CLAMP_U8( x)        CLAMP((x),     0x0,  U8_MAX)
#define CLAMP_S8( x)        CLAMP((x),  S8_MIN,  S8_MAX)
#define CLAMP_U16(x)        CLAMP((x),     0x0, U16_MAX)
#define CLAMP_S16(x)        CLAMP((x), S16_MIN, S16_MAX)
#define CLAMP_U32(x)        CLAMP((x),     0x0, U32_MAX)
#define CLAMP_S32(x)        CLAMP((x), S32_MIN, S32_MAX)
#define CLAMP_U64(x)        CLAMP((x),     0x0, U64_MAX)
#define CLAMP_S64(x)        CLAMP((x), S64_MIN, S64_MAX)
#define CLAMP_F32(x)        CLAMP((x), F32_MIN, F32_MAX)
#define CLAMP_F64(x)        CLAMP((x), F64_MIN, F64_MAX)

#define SWAP(a, b)          { ((a) ^= (b)); ((b) ^= (a)); ((a) ^= (b)); }

#define sqr(x)              (    (x) * (x))
#define cube(x)             ( sqr(x) * (x))
#define quad(x)             (cube(x) * (x))

#define average_2(a, b      )   (((a) + (b)            ) / 2.0f)
#define average_3(a, b, c   )   (((a) + (b) + (c)      ) / 3.0f)
#define average_4(a, b, c, d)   (((a) + (b) + (c) + (d)) / 4.0f)

#define vec2_same(v, s)     (((v)[0]) = ((v)[1])                       = (s))
#define vec3_same(v, s)     (((v)[0]) = ((v)[1]) = ((v)[2])            = (s))
#define vec4_same(v, s)     (((v)[0]) = ((v)[1]) = ((v)[2]) = ((v)[3]) = (s))

#define vec2_zero(v)        (vec2_same((v), 0))
#define vec3_zero(v)        (vec3_same((v), 0))
#define vec4_zero(v)        (vec4_same((v), 0))

#define vec2_c(v)           (   (v)[0] + (v)[1])
#define vec3_c(v)           (vec2_c(v) + (v)[2])
#define vec4_c(v)           (vec3_c(v) + (v)[3])

#define vec2_average(v)     (vec2_c(v) / 2.0f)
#define vec3_average(v)     (vec3_c(v) / 3.0f)
#define vec4_average(v)     (vec4_c(v) / 4.0f)

#define vec2_sumsq(v)       (  sqr((v)[0]) + sqr((v)[1]))
#define vec3_sumsq(v)       (vec2_sumsq(v) + sqr((v)[2]))
#define vec4_sumsq(v)       (vec3_sumsq(v) + sqr((v)[3]))

#define vec2_mag(v)         (sqrtf(vec2_sumsq(v)))
#define vec3_mag(v)         (sqrtf(vec3_sumsq(v)))
#define vec4_mag(v)         (sqrtf(vec4_sumsq(v)))

#define vec3_yaw(from, to)  (atan2s(((to)[2] - (from)[2]), ((to)[0] - (from)[0])))

#define vec2_dot(a, b)       (((a)[0] * (b)[0]) + ((a)[1] * (b)[1]))
#define vec3_dot(a, b)      (vec2_dot((a), (b)) + ((a)[2] * (b)[2]))
#define vec4_dot(a, b)      (vec3_dot((a), (b)) + ((a)[3] * (b)[3]))

/// Make vector 'dest' the cross product of vectors a and b.
#define vec3_cross(dst, a, b) {                         \
    (dst)[0] = (((a)[1] * (b)[2]) - ((a)[2] * (b)[1])); \
    (dst)[1] = (((a)[2] * (b)[0]) - ((a)[0] * (b)[2])); \
    (dst)[2] = (((a)[0] * (b)[1]) - ((a)[1] * (b)[0])); \
}

/**
 * | ? ? ? 0 |
 * | ? ? ? 0 |
 * | ? ? ? 0 |
 * | 0 0 0 1 |
 * i.e. a matrix representing a linear transformation over 3 space.
 */
// Multiply a vector by a matrix of the form
#define linear_mtxf_mul_vec3f(mtx, dstV, srcV) {                                                    \
    (dstV)[0] = (((mtx)[0][0] * (srcV)[0]) + ((mtx)[1][0] * (srcV)[1]) + ((mtx)[2][0] * (srcV)[2]));\
    (dstV)[1] = (((mtx)[0][1] * (srcV)[0]) + ((mtx)[1][1] * (srcV)[1]) + ((mtx)[2][1] * (srcV)[2]));\
    (dstV)[2] = (((mtx)[0][2] * (srcV)[0]) + ((mtx)[1][2] * (srcV)[1]) + ((mtx)[2][2] * (srcV)[2]));\
}

#define linear_mtxf_mul_vec3f_and_translate(mtx, dstV, srcV) {  \
    linear_mtxf_mul_vec3f((mtx), (dstV), (srcV));               \
    vec3_add((dstV), (mtx)[3]);                                 \
}

// Multiply a vector by the transpose of a matrix of the form
#define linear_mtxf_transpose_mul_vec3f(mtx, dstV, srcV) {  \
    (dstV)[0] = vec3_dot((mtx)[0], (srcV));                 \
    (dstV)[1] = vec3_dot((mtx)[1], (srcV));                 \
    (dstV)[2] = vec3_dot((mtx)[2], (srcV));                 \
}

#define vec2_set(dst, x, y) {           \
    (dst)[0] = (x);                     \
    (dst)[1] = (y);                     \
}
#define vec3_set(dst, x, y, z) {        \
    vec2_set((dst), (x), (y));          \
    (dst)[2] = (z);                     \
}
#define vec4_set(dst, x, y, z, w) {     \
    vec3_set((dst), (x), (y), (z));     \
    (dst)[3] = (w);                     \
}

#define vec2_copy(dst, src) {           \
    (dst)[0] = (src)[0];                \
    (dst)[1] = (src)[1];                \
}
#define vec3_copy(dst, src) {           \
    vec2_copy((dst), (src));            \
    (dst)[2] = (src)[2];                \
}
#define vec4_copy(dst, src) {           \
    vec3_copy((dst), (src));            \
    (dst)[3] = (src)[3];                \
}

#define vec3_copy_y_off(dst, src, y) {  \
    (dst)[0] =  (src)[0];               \
    (dst)[1] = ((src)[1] + (y));        \
    (dst)[2] =  (src)[2];               \
}

#define vec2_copy_roundf(dst, src) {    \
    (dst)[0] = roundf((src)[0]);        \
    (dst)[1] = roundf((src)[1]);        \
}
#define vec3_copy_roundf(dst, src) {    \
    vec2_copy_roundf((dst), (src));     \
    (dst)[2] = roundf((src)[2]);        \
}
#define vec4_copy_roundf(dst, src) {    \
    vec3_copy_roundf((dst), (src));     \
    (dst)[3] = roundf((src)[3]);        \
}

#define vec2_copy_inverse(dst, src) {   \
    (dst)[0] = (src)[1];                \
    (dst)[1] = (src)[0];                \
}
#define vec3_copy_inverse(dst, src) {   \
    (dst)[0] = (src)[2];                \
    (dst)[1] = (src)[1];                \
    (dst)[2] = (src)[0];                \
}
#define vec4_copy_inverse(dst, src) {   \
    (dst)[0] = (src)[3];                \
    (dst)[1] = (src)[2];                \
    (dst)[2] = (src)[1];                \
    (dst)[3] = (src)[0];                \
}

#define vec3_copy_offset_m1(dst, src) { \
    (dst)[0] = (src)[1];                \
    (dst)[1] = (src)[2];                \
    (dst)[2] = (src)[0];                \
}

#define vec2_copy_negative(dst, src) {  \
    (dst)[0] = -(src)[0];               \
    (dst)[1] = -(src)[1];               \
}
#define vec3_copy_negative(dst, src) {  \
    vec2_copy_negative((dst), (src));   \
    (dst)[2] = -(src)[2];               \
}
#define vec4_copy_negative(dst, src) {  \
    vec3_copy_negative((dst), (src));   \
    (dst)[3] = -(src)[3];               \
}

#define vec2_sum(dst, src1, src2) {     \
    (dst)[0] = ((src1)[0] + (src2)[0]); \
    (dst)[1] = ((src1)[1] + (src2)[1]); \
}
#define vec3_sum(dst, src1, src2) {     \
    vec2_sum((dst), (src1), (src2));    \
    (dst)[2] = ((src1)[2] + (src2)[2]); \
}
#define vec4_sum(dst, src1, src2) {     \
    vec3_sum((dst), (src1), (src2));    \
    (dst)[3] = ((src1)[3] + (src2)[3]); \
}

#define vec2_add(dst, src) vec2_sum((dst), (dst), (src))
#define vec3_add(dst, src) vec3_sum((dst), (dst), (src))
#define vec4_add(dst, src) vec4_sum((dst), (dst), (src))

#define vec2_sum_val(dst, src, x) {     \
    (dst)[0] = ((src)[0] + (x));        \
    (dst)[1] = ((src)[1] + (x));        \
}
#define vec3_sum_val(dst, src, x) {     \
    vec2_sum_val((dst), (src), (x));    \
    (dst)[2] = ((src)[2] + (x));        \
}
#define vec4_sum_val(dst, src, x) {     \
    vec3_sum_val((dst), (src), (x));    \
    (dst)[3] = ((src)[2] + (x));        \
}

#define vec2_add_val(dst, x) vec2_sum_val((dst), (dst), (x))
#define vec3_add_val(dst, x) vec3_sum_val((dst), (dst), (x))
#define vec4_add_val(dst, x) vec4_sum_val((dst), (dst), (x))

#define vec2_diff(dst, src1, src2) {    \
    (dst)[0] = ((src1)[0] - (src2)[0]); \
    (dst)[1] = ((src1)[1] - (src2)[1]); \
}
#define vec3_diff(dst, src1, src2) {    \
    vec2_diff((dst), (src1), (src2));   \
    (dst)[2] = ((src1)[2] - (src2)[2]); \
}
#define vec4_diff(dst, src1, src2) {    \
    vec3_diff((dst), (src1), (src2));   \
    (dst)[3] = ((src1)[3] - (src2)[3]); \
}

#define vec2_sub(dst, src) vec2_diff((dst), (dst), (src))
#define vec3_sub(dst, src) vec3_diff((dst), (dst), (src))
#define vec4_sub(dst, src) vec4_diff((dst), (dst), (src))

#define vec2_diff_val(dst, src, x) {    \
    (dst)[0] = ((src)[0] - (x));        \
    (dst)[1] = ((src)[1] - (x));        \
}
#define vec3_diff_val(dst, src, x) {    \
    vec2_diff_val((dst), (src), (x));   \
    (dst)[2] = ((src)[2] - (x));        \
}
#define vec4_diff_val(dst, src, x) {    \
    vec3_diff_val((dst), (src), (x));   \
    (dst)[3] = ((src)[3] - (x));        \
}

#define vec2_sub_val(dst, x) vec2_diff_val((dst), (dst), (x))
#define vec3_sub_val(dst, x) vec3_diff_val((dst), (dst), (x))
#define vec4_sub_val(dst, x) vec4_diff_val((dst), (dst), (x))

#define vec2_prod(dst, src1, src2) {    \
    (dst)[0] = ((src1)[0] * (src2)[0]); \
    (dst)[1] = ((src1)[1] * (src2)[1]); \
}
#define vec3_prod(dst, src1, src2) {    \
    vec2_prod((dst), (src1), (src2));   \
    (dst)[2] = ((src1)[2] * (src2)[2]); \
}
#define vec4_prod(dst, src1, src2) {    \
    vec3_prod((dst), (src1), (src2));   \
    (dst)[3] = ((src1)[3] * (src2)[3]); \
}

#define vec2_mul(dst, src) vec2_prod((dst), (dst), (src))
#define vec3_mul(dst, src) vec3_prod((dst), (dst), (src))
#define vec4_mul(dst, src) vec4_prod((dst), (dst), (src))

#define vec2_prod_val(dst, src, x) {    \
    (dst)[0] = ((src)[0] * (x));        \
    (dst)[1] = ((src)[1] * (x));        \
}
#define vec3_prod_val(dst, src, x) {    \
    vec2_prod_val((dst), (src), (x));   \
    (dst)[2] = ((src)[2] * (x));        \
}
#define vec4_prod_val(dst, src, x) {    \
    vec3_prod_val((dst), (src), (x));   \
    (dst)[3] = ((src)[3] * (x));        \
}

#define vec2_mul_val(dst, x) vec2_prod_val(dst, dst, x)
#define vec3_mul_val(dst, x) vec3_prod_val(dst, dst, x)
#define vec4_mul_val(dst, x) vec4_prod_val(dst, dst, x)

#define vec2_quot(dst, src1, src2) {    \
    (dst)[0] = ((src1)[0] / (src2)[0]); \
    (dst)[1] = ((src1)[1] / (src2)[1]); \
}
#define vec3_quot(dst, src1, src2) {    \
    vec2_quot((dst), (src1), (src2));   \
    (dst)[2] = ((src1)[2] / (src2)[2]); \
}
#define vec4_quot(dst, src1, src2) {    \
    vec3_quot((dst), (src1), (src2));   \
    (dst)[3] = ((src1)[3] / (src2)[3]); \
}

#define vec2_div(dst, src) vec2_quot((dst), (dst), (src))
#define vec3_div(dst, src) vec3_quot((dst), (dst), (src))
#define vec4_div(dst, src) vec4_quot((dst), (dst), (src))

#define vec2_quot_val(dst, src, x) {    \
    (dst)[0] = ((src)[0] / (x));        \
    (dst)[1] = ((src)[1] / (x));        \
}
#define vec3_quot_val(dst, src, x) {    \
    vec2_quot_val((dst), (src), (x));   \
    (dst)[2] = ((src)[2] / (x));        \
}
#define vec4_quot_val(dst, src, x) {    \
    vec3_quot_val((dst), (src), (x));   \
    (dst)[3] = ((src)[3] / (x));        \
}

#define vec2_div_val(dst, x) vec2_quot_val((dst), (dst), (x))
#define vec3_div_val(dst, x) vec3_quot_val((dst), (dst), (x))
#define vec4_div_val(dst, x) vec4_quot_val((dst), (dst), (x))

#define MAKE_DXZ(from, to, fmt)     \
    fmt dx = ((to)[0] - (from)[0]); \
    fmt dz = ((to)[2] - (from)[2]);
#define MAKE_DXYZ(from, to, fmt)    \
    MAKE_DXZ((from), (to), fmt);    \
    fmt dy = ((to)[1] - (from)[1]);


#define MAT4_VEC_DOT_PROD(R, A, B, row, col)                    \
    {                                                           \
        (R)[(row)][(col)]  = ((A)[(row)][0] * (B)[0][(col)]);   \
        (R)[(row)][(col)] += ((A)[(row)][1] * (B)[1][(col)]);   \
        (R)[(row)][(col)] += ((A)[(row)][2] * (B)[2][(col)]);   \
    }
#define MAT4_DOT_PROD(R, A, B, row, col)                        \
    {                                                           \
        (R)[(row)][(col)]  = ((A)[(row)][0] * (B)[0][(col)]);   \
        (R)[(row)][(col)] += ((A)[(row)][1] * (B)[1][(col)]);   \
        (R)[(row)][(col)] += ((A)[(row)][2] * (B)[2][(col)]);   \
        (R)[(row)][(col)] += ((A)[(row)][3] * (B)[3][(col)]);   \
    }

#define MAT4_MULTIPLY(R, A, B)                                  \
    {                                                           \
        MAT4_DOT_PROD((R), (A), (B), 0, 0);                     \
        MAT4_DOT_PROD((R), (A), (B), 0, 1);                     \
        MAT4_DOT_PROD((R), (A), (B), 0, 2);                     \
        MAT4_DOT_PROD((R), (A), (B), 0, 3);                     \
        MAT4_DOT_PROD((R), (A), (B), 1, 0);                     \
        MAT4_DOT_PROD((R), (A), (B), 1, 1);                     \
        MAT4_DOT_PROD((R), (A), (B), 1, 2);                     \
        MAT4_DOT_PROD((R), (A), (B), 1, 3);                     \
        MAT4_DOT_PROD((R), (A), (B), 2, 0);                     \
        MAT4_DOT_PROD((R), (A), (B), 2, 1);                     \
        MAT4_DOT_PROD((R), (A), (B), 2, 2);                     \
        MAT4_DOT_PROD((R), (A), (B), 2, 3);                     \
        MAT4_DOT_PROD((R), (A), (B), 3, 0);                     \
        MAT4_DOT_PROD((R), (A), (B), 3, 1);                     \
        MAT4_DOT_PROD((R), (A), (B), 3, 2);                     \
        MAT4_DOT_PROD((R), (A), (B), 3, 3);                     \
    }

#define MTXF_END(mtx) { \
    (mtx)[0][3] = 0.0f; \
    (mtx)[1][3] = 0.0f; \
    (mtx)[2][3] = 0.0f; \
    (mtx)[3][3] = 1.0f; \
}

#define NAME_INVMAG(v) v##_invmag

/// Scale vector 'v' so it has length  1
#define vec3_normalize(v) {                             \
    register f32 NAME_INVMAG(v) = vec3_mag((v));            \
    NAME_INVMAG(v) = (1.0f / MAX(NAME_INVMAG(v), NEAR_ZERO));   \
    vec3_mul_val((v), NAME_INVMAG(v));                      \
}

/// Scale vector 'v' so it has length -1
#define vec3_normalize_negative(v) {                    \
    register f32 v##_invmag = vec3_mag((v));            \
    v##_invmag = -(1.0f / MAX(v##_invmag, NEAR_ZERO));  \
    vec3_mul_val((v), v##_invmag);                      \
}

#define vec3_normalize_max(v, max) {    \
    register f32 v##_mag = vec3_mag(v); \
    v##_mag = MAX(v##_mag, NEAR_ZERO);  \
    if (v##_mag > max) {                \
        v##_mag = (max / v##_mag);      \
        vec3_mul_val(v, v##_mag);       \
    }                                   \
}

// Kaze's float functions
f32 slow_logf(f32 x);
f32 slow_expf(f32 x);
f32 slow_powf(f32 base, f32 exponent);
// Rounding
s16 round_float_to_short( f32 num);
s32 round_float_to_int(   f32 num);
s16 round_double_to_short(f64 num);
s32 round_double_to_int(  f64 num);
s8  normalize_component(  f32 comp);
// Abs functions
s8   absc(s8  x);
s16  abss(s16 x);
s32  absi(s32 x);
f32  absf(f32 x);
f64  absd(f64 x);
// Clamp
Bool32 clamp_pitch(Vec3f from, Vec3f to, Angle maxPitch, Angle minPitch);
Bool32 clamp_s16(s16 *value, s16 minimum, s16 maximum);
Bool32 clamp_f32(f32 *value, f32 minimum, f32 maximum);
f32    clamp_f32_abs(f32 a, f32 b);
void   vec3f_clamp(Vec3f vec, f32 limit);
f32    smooth(   f32 x);
f32    softClamp(f32 x, f32 a, f32 b);
// RNG
u16  random_u16(   void);
s32  random_sign(  void);
f32  gd_rand_float(void);
f32  random_float( void);
s16  random_linear_offset(s16 base, s16 range);
s16  random_mod_offset(s16 base, s16 step, s16 mod);
f32  random_f32_around_zero(f32 diameter);
void random_vec3s(                       Vec3s dest, s16 xRange, s16 yRange, s16 zRange);
// Angles
Angle  abs_angle_diff(Angle angle1, Angle angle2);
Bool32 oscillate_toward(s32 *value, f32 *vel, s32 target, f32 velCloseToZero, f32 accel, f32 slowdown);

void vec3f_to_vec3c(     Vec3c dst, Vec3f src);
void vec3f_to_vec3s(     Vec3s dst, Vec3f src);
void vec3f_to_vec3i(     Vec3i dst, Vec3f src);

void vec3f_normalize(         Vec3f v);
void vec3f_normalize_negative(Vec3f v);
Bool32 vec3f_are_coords_within_radius_of_point(Vec3f pos, f32 x, f32 y, f32 z, f32 dist);
Bool32 vec3f_are_points_within_radius(         Vec3f pos1, Vec3f pos2,         f32 dist);
void vec2f_get_lateral_dist(                   Vec2f from, Vec2f to,            f32 *lateralDist                          );
void vec3f_get_lateral_dist(                   Vec3f from, Vec3f to,            f32 *lateralDist                          );
void vec3f_get_dist(                           Vec3f from, Vec3f to, f32 *dist                                            );
void vec3f_get_dist_squared(                   Vec3f from, Vec3f to, f32 *dist                                            );
void vec3f_get_dist_and_yaw(                   Vec3f from, Vec3f to, f32 *dist,                                 Angle *yaw);
void vec3f_get_pitch(                          Vec3f from, Vec3f to,                              Angle *pitch            );
void vec3f_get_yaw(                            Vec3f from, Vec3f to,                                            Angle *yaw);
void vec3f_get_angle(                          Vec3f from, Vec3f to,                              Angle *pitch, Angle *yaw);
void vec3f_get_lateral_dist_and_pitch(         Vec3f from, Vec3f to,            f32 *lateralDist, Angle *pitch            );
void vec3f_get_lateral_dist_and_yaw(           Vec3f from, Vec3f to,            f32 *lateralDist,               Angle *yaw);
void vec3f_get_lateral_dist_and_angle(         Vec3f from, Vec3f to,            f32 *lateralDist, Angle *pitch, Angle *yaw);
void vec3f_get_dist_and_lateral_dist_and_angle(Vec3f from, Vec3f to, f32 *dist, f32 *lateralDist, Angle *pitch, Angle *yaw);
void vec3s_get_dist_and_angle(                 Vec3s from, Vec3s to, s16 *dist,                   Angle *pitch, Angle *yaw);
void vec3f_get_dist_and_angle(                 Vec3f from, Vec3f to, f32 *dist,                   Angle *pitch, Angle *yaw);
void vec3s_set_dist_and_angle(                 Vec3s from, Vec3s to, s16  dist,                   Angle32 pitch, Angle32 yaw);
void vec3f_set_dist_and_angle(                 Vec3f from, Vec3f to, f32  dist,                   Angle32 pitch, Angle32 yaw);

void find_vector_perpendicular_to_plane( Vec3f dest, Vec3f a, Vec3f b, Vec3f c);
void vec3f_rotate(                        Mat4 mat, Vec3f in, Vec3f out);
void vec3f_transform(                     Mat4 mat, Vec3f in, f32 w, Vec3f out);
void vec3f_transform_vtx(                 Mat4 mat, Vec3f in, f32 w, Vtx  *out);
void rotate_triangle_vertices(           Vec3s vertex1, Vec3s vertex2, Vec3s vertex3, Angle pitch, Angle yaw);
void scale_along_line(                   Vec3f dest, Vec3f from, Vec3f to, f32 scale);
// Matrix operations
void mtxf_copy(                           Mat4 dest, const Mat4 src);
void mtxf_shift_up(                       Mat4 mtx);
void mtxf_identity(                       Mat4 mtx);
void mtxf_translate(                      Mat4 dest, Vec3f b);
void mtxf_lookat(                         Mat4  mtx,  Vec3f from, Vec3f to, Angle32 roll);
void mtxf_origin_lookat(                  Mat4  mtx, Vec3f vec, f32 roll);
void mtxf_rotate_xy(                      Mtx  *mtx, Angle32 angle, Bool32 doScale);
void mtxf_rotate_xyz(                     Mat4 dest,                  Vec3a rotate);
void mtxf_rotate_zxy_and_translate(       Mat4 dest, Vec3f translate, Vec3a rotate);
void mtxf_rotate_xyz_and_translate(       Mat4 dest, Vec3f translate, Vec3a rotate);
void mtxf_billboard(                      Mat4 dest, Mat4 mtx, Vec3f position, Angle32 roll, s32 zOffset);
void mtxf_align_terrain_normal(           Mat4 dest, Vec3f upDir, Vec3f pos, Angle32 yaw);
void mtxf_align_terrain_triangle(         Mat4  mtx, Vec3f pos, Angle32 yaw, f32 radius);
void mtxf_mul(                            Mat4 dest, Mat4 a, Mat4 b);
void gd_mult_mat4f(                       Mat4 dst, const Mat4 mA, const Mat4 mB);
void mtxf_transform_from_normals(         Mat4 dest, Vec3f pos, f32 xNorm, f32 yNorm, f32 zNorm);
void mtxf_scale_vec3f(                    Mat4 dest, Mat4 mtx, Vec3f s);
void mtxf_scale_self_vec3f(               Mat4  mtx, Vec3f vec);
void linear_mtxf_self_mul_vec3f_self(         Mat4 mtx, Vec3f b);
void linear_mtxf_mul_vec3f_self_and_translate(Mat4 mtx, Vec3f b);
void mtxf_to_mtx(                         void *dest, void *src);
void get_pos_from_transform_mtx(         Vec3f dest, Mat4 objMtx, Mat4 camMtx);
void create_transformation_from_matrices( Mat4  dst, Mat4 a1, Mat4 a2);
void mtxf_inverse_rotate_translate(       Mat4   in, Mat4 out);

f32  det_2x2(f32 a, f32 b, f32 c, f32 d);
f32  det_3x3(f32 r0c0, f32 r0c1, f32 r0c2,
             f32 r1c0, f32 r1c1, f32 r1c2,
             f32 r2c0, f32 r2c1, f32 r2c2);
void mtxf_adjunct(                      Mat4 *src, Mat4 *dst);
f32  mtxf_det(                          Mat4 *mtx);
void mtxf_inverse(                      Mat4 *dst, Mat4 *src);

void mtxf_absrot(            Mat4 mtx, s32 axisnum, f32 ang);
void mtxf_create_rot_angular(Mat4 mtx, Vec3f vec,   f32 ang);
void mtxf_rot_about_vec3f(   Mat4 mtx, Vec3f vec           );

void make_oblique(                        Mat4 toModify, Vec4f clipPlane);

// Approach s32
s32     approach_s32(                     s32  current,   s32 target,   s32 inc, s32 dec);
Bool32  approach_s32_bool(                s32 *current,   s32 target,   s32 inc, s32 dec);
#define approach_s32_symmetric(                current,       target,       inc) approach_s32(     (current), (target), (inc), (inc))
#define approach_s32_symmetric_bool(           current,       target,       inc) approach_s32_bool((current), (target), (inc), (inc))
// Approach s16
s32     approach_s16(                     s16  current,   s16 target,   s16 inc, s16 dec);
Bool32  approach_s16_bool(                s16 *current,   s16 target,   s16 inc, s16 dec);
#define approach_s16_symmetric(                current,       target,       inc) approach_s16(     (current), (target), (inc), (inc))
#define approach_s16_symmetric_bool(           current,       target,       inc) approach_s16_bool((current), (target), (inc), (inc))
Angle32 approach_angle(               Angle32  current, Angle32 target, Angle32 inc);
Bool32  approach_angle_bool(            Angle *current, Angle32 target, Angle32 inc);
// Approach f32
f32     approach_f32(                     f32  current,   f32 target,   f32 inc, f32 dec);
Bool32  approach_f32_bool(                f32 *current,   f32 target,   f32 inc, f32 dec);
#define approach_f32_symmetric(                current,       target,       inc) approach_f32(     (current), (target), (inc), (inc))
#define approach_f32_symmetric_bool(           current,       target,       inc) approach_f32_bool((current), (target), (inc), (inc))
Bool32  approach_f32_ptr(                 f32 *current,   f32 target,   f32 inc);
Bool32  approach_f32_signed(              f32 *current,   f32 target,   f32 inc);
// Approach asymptotic
s32     approach_s16_asymptotic(          s16  current,   s16 target,   s16 divisor);
Bool32  approach_s16_asymptotic_bool(     s16 *current,   s16 target,   s16 divisor);
f32     approach_f32_asymptotic(          f32  current,   f32 target,   f32 multiplier);
Bool32  approach_f32_asymptotic_bool(     f32 *current,   f32 target,   f32 multiplier);
void    approach_vec3s_asymptotic(      Vec3s  current, Vec3s target, s16 xMul, s16 yMul, s16 zMul);
void    approach_vec3f_asymptotic(      Vec3f  current, Vec3f target, f32 xMul, f32 yMul, f32 zMul);
// Trig
Angle atan2s(f32 y, f32 x);
f32   atan2f(f32 a, f32 b);
f32   atan2_deg(f32 a, f32 b);
void  rot_xy_deg(f32 deg, f32 *x, f32 *y);
// Curves
void anim_spline_init(Vec4s *keyFrames);
Bool32 anim_spline_poll(Vec3f result);
void vec3s_evaluate_cubic_spline(f32 u, Vec3s Q, Vec3f s1, Vec3f s2, Vec3f s3, Vec3f s4);
void vec3f_evaluate_cubic_spline(f32 u, Vec3f Q, Vec3f s1, Vec3f s2, Vec3f s3, Vec3f s4);
