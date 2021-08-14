#ifndef MATH_UTIL_H
#define MATH_UTIL_H

#include <PR/ultratypes.h>

#include "types.h"

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

#define ABS(x) ((x) > 0.0f ? (x) : -(x))

/**
 * Converts an angle in degrees to sm64's s16 angle units. For example, DEGREES(90) == 0x4000
 * This should be used mainly to make camera code clearer at first glance.
 */
#define DEGREES(x) (s16)((x) * 0x10000 / 360)

#define sins(x) gSineTable[  (u16) (x) >> 4]
#define coss(x) gCosineTable[(u16) (x) >> 4]
#define atans(x) gArctanTable[(u16) (x) >> 4] //! is this correct?

#define min(a, b) ((a) <= (b) ? (a) : (b))
#define max(a, b) ((a) >  (b) ? (a) : (b))

#define sqr(x) ((x) * (x))

// Kaze's float functions
float slow_logf(float x);
float slow_expf(float x);
float slow_powf(float base, float exponent);
// Sign functions
s32  signum_positive(s32 x);
f64  absd(f64 x);
f32  absf(f32 x);
s32  absi(s32 x);
s16  abss(s16 x);
s8   absc(s8  x);
// Fast Inverse Square Root
#ifdef FAST_INVSQRT
float  Q_rsqrtf( float  number );
double Q_rsqrtd( double number );
#endif
// Comparison
s16  min_3s(s16 a0, s16 a1, s16 a2);
s16  max_3s(s16 a0, s16 a1, s16 a2);
s32  min_3i(s32 a0, s32 a1, s32 a2);
s32  max_3i(s32 a0, s32 a1, s32 a2);
f32  min_3f(f32 a0, f32 a1, f32 a2);
f32  max_3f(f32 a0, f32 a1, f32 a2);
// RNG
u16  random_u16(   void);
s32  random_sign(  void);
f32  random_float( void);
f32  random_f32_around_zero(f32 diameter);
void random_vec3s(                       Vec3s dest, s16 xRange, s16 yRange, s16 zRange);
// Angles
s16  abs_angle_diff(s16 angle1, s16 angle2);
// Vector Operations
void vec3f_copy(                         Vec3f dest, Vec3f src);
void vec3f_set(                          Vec3f dest, f32 x, f32 y, f32 z);
void vec3f_add(                          Vec3f dest, Vec3f a);
void vec3f_sub(                          Vec3f dst, Vec3f a);
void vec3f_sum(                          Vec3f dest, Vec3f a, Vec3f b);
void vec3f_diff(                         Vec3f dest, Vec3f a, Vec3f b);
void vec3s_copy(                         Vec3s dest, Vec3s src);
void vec3s_set(                          Vec3s dest, s16 x, s16 y, s16 z);
void vec3s_add(                          Vec3s dest, Vec3s a);
void vec3s_sum(                          Vec3s dest, Vec3s a, Vec3s b);
void vec3s_sub(                          Vec3s dest, Vec3s a);
void vec3s_to_vec3f(                     Vec3f dest, Vec3s a);
void vec3f_to_vec3s(                     Vec3s dest, Vec3f a);
void find_vector_perpendicular_to_plane( Vec3f dest, Vec3f a, Vec3f b, Vec3f c);
void vec3f_cross(                        Vec3f dest, Vec3f a, Vec3f b);
f32  vec3f_mag(                          Vec3f v);
void vec3f_normalize(                    Vec3f dest);
void vec3f_get_dist_and_angle(           Vec3f from, Vec3f to, f32 *dist, s16 *pitch, s16 *yaw);
void vec3f_set_dist_and_angle(           Vec3f from, Vec3f to, f32  dist, s16  pitch, s16  yaw);
void vec3f_scale_vec3f(                        Vec3f dest, Vec3f src, Vec3f scale, u32 doInverted);
void vec3f_rotate(                        Mat4 mat, Vec3f in, Vec3f out);
void vec3f_transform(                     Mat4 mat, Vec3f in, f32 w, Vec3f out);
void vec3f_transform_vtx(                 Mat4 mat, Vec3f in, f32 w, Vtx *out);
f32  vec3f_dot(                          Vec3f a, Vec3f b);
f32  vec4f_dot(                          Vec4f a, Vec4f b);
void vec4f_scale(                        Vec4f dest, Vec4f src, f32 scale);
void make_oblique(                        Mat4 toModify, Vec4f clipPlane);
// Matrix operations
void mtxf_copy(                           Mat4 dest,  Mat4 src);
void mtxf_identity(                       Mat4  mtx);
void mtxf_translate(                      Mat4 dest, Vec3f b);
void mtxf_lookat(                         Mat4  mtx,  Vec3f from, Vec3f to, s16 roll);
void mtxf_rotate_zxy_and_translate(       Mat4 dest, Vec3f translate, Vec3s rotate);
void mtxf_rotate_xyz_and_translate(       Mat4 dest, Vec3f b, Vec3s c);
void mtxf_billboard(                      Mat4 dest, Mat4 mtx, Vec3f position, s16 angle, s32 zOffset);
void mtxf_align_facing_view(                   Mat4 dest, Mat4 mtx, Vec3f position, s16 roll, s32 zOffset);
void mtxf_align_terrain_normal(           Mat4 dest, Vec3f upDir, Vec3f pos, s16 yaw);
void mtxf_align_terrain_triangle(         Mat4  mtx, Vec3f pos, s16 yaw, f32 radius);
void mtxf_mul(                            Mat4 dest, Mat4 a, Mat4 b);
void mtxf_scale_vec3f(                    Mat4 dest, Mat4 mtx, Vec3f s);
void mtxf_mul_vec3s(                      Mat4  mtx, Vec3s b);
void mtxf_mul_vec3f(                      Mat4  mtx, Vec3f b);
void linear_mtxf_mul_vec3f(               Mat4  mtx, Vec3f dst, Vec3f v);
void linear_mtxf_transpose_mul_vec3f(     Mat4  mtx, Vec3f dst, Vec3f v);
void mtxf_to_mtx(                         Mtx *dest, Mat4 src);
void mtxf_rotate_xy(                      Mtx  *mtx, s16 angle);
void get_pos_from_transform_mtx(         Vec3f dest, Mat4 objMtx, Mat4 camMtx);
void mtxf_inverse_rotate_translate(       Mat4   in, Mat4 out);
// Approach
s32  approach_s32(                      s32  current,   s32 target, s32 inc, s32 dec);
f32  approach_f32(                      f32  current,   f32 target, f32 inc, f32 dec);
s32  approach_f32_signed(               f32   *value,   f32 target, f32 inc);
f32  approach_f32_symmetric(            f32    value,   f32 target, f32 inc);
s16  approach_s16_symmetric(            s16    value,   s16 target, s16 inc);
s32  approach_f32_asymptotic_bool(      f32 *current,   f32 target, f32 multiplier);
f32  approach_f32_asymptotic(           f32  current,   f32 target, f32 multiplier);
s32  approach_s16_asymptotic_bool(      s16 *current,   s16 target, s16 divisor);
s32  approach_s16_asymptotic(           s16  current,   s16 target, s16 divisor);
void approach_vec3f_asymptotic(       Vec3f  current, Vec3f target, f32 xMul, f32 yMul, f32 zMul);
void approach_vec3s_asymptotic(        Vec3s current, Vec3s target, s16 xMul, s16 yMul, s16 zMul);
// Atans
s16  atan2s(f32 y, f32 x);
f32  atan2f(f32 a, f32 b);
// Curves
void spline_get_weights(Vec4f result, f32 t, UNUSED s32 c);
void anim_spline_init(Vec4s *keyFrames);
s32  anim_spline_poll( Vec3f result);

#endif // MATH_UTIL_H
