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
extern s16 gArctanTable[];

#define ABSF(x) ((x) > 0.0f ? (x) : -(x))
#define ABSI(x) ((x) > 0    ? (x) : -(x))

/**
 * Converts an angle in degrees to sm64's s16 angle units. For example, DEGREES(90) == 0x4000
 * This should be used mainly to make camera code clearer at first glance.
 */
#define DEGREES(x) (Angle)((x) * 0x10000 / 360)

#define DEG_PER_RAD 57.29577950560105
#define RAD_PER_DEG (1.0 / DEG_PER_RAD)

#define CONST_EULER_D 2.71828182845904523536028747135266249775724709369995
#define CONST_EULER_F 2.71828182845904523536028747135266249775724709369995f

#define sins(x)  gSineTable[  (u16) (x) >> 4]
#define coss(x)  gCosineTable[(u16) (x) >> 4]
#define atans(x) gArctanTable[(u16) (x) >> 4] //! is this correct?

#define min(a, b) ((a) > (b) ? (b) : (a))
#define max(a, b) ((a) > (b) ? (a) : (b))

#define CLAMP(x, low, high)  (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))

#define sqr(x) ((x) * (x))

// Kaze's float functions
f32 slow_logf(f32 x);
f32 slow_expf(f32 x);
f32 slow_powf(f32 base, f32 exponent);
// Rounding
f32 froundf(f32 in);
s16 round_float_to_short( f32 num);
s32 round_float_to_int(   f32 num);
s16 round_double_to_short(f64 num);
s32 round_double_to_int(  f64 num);
// Sign functions
s32  signum_positive(s32 x);
s8   absc(s8  x);
s16  abss(s16 x);
s32  absi(s32 x);
f32  absf(f32 x);
f64  absd(f64 x);
// Fast Inverse Square Root
#ifdef FAST_INVSQRT
f32  Q_rsqrtf( f32 number );
f64  Q_rsqrtd( f64 number );
#endif
f64  sqrtd(f64 x);
// min_3
s8   min_3c( s8  a0, s8  a1,  s8 a2);
u8   min_3uc(u8  a0, u8  a1,  u8 a2);
s16  min_3s( s16 a0, s16 a1, s16 a2);
u16  min_3us(s16 a0, u16 a1, u16 a2);
s32  min_3i( s32 a0, s32 a1, s32 a2);
u32  min_3ui(u32 a0, u32 a1, u32 a2);
f32  min_3f( f32 a0, f32 a1, f32 a2);
f64  min_3d( f64 a0, f64 a1, f64 a2);
// max_3
s8   max_3c( s8  a0,  s8 a1,  s8 a2);
u8   max_3uc(u8  a0,  u8 a1,  u8 a2);
s16  max_3s( s16 a0, s16 a1, s16 a2);
u16  max_3us(u16 a0, u16 a1, u16 a2);
s32  max_3i( s32 a0, s32 a1, s32 a2);
u32  max_3ui(u32 a0, u32 a1, u32 a2);
f32  max_3f( f32 a0, f32 a1, f32 a2);
f64  max_3d( f64 a0, f64 a1, f64 a2);
// Clamp
Bool32 clamp_pitch(Vec3f from, Vec3f to, Angle maxPitch, Angle minPitch);
Bool32 clamp_s16(s16 *value, s16 minimum, s16 maximum);
Bool32 clamp_f32(f32 *value, f32 minimum, f32 maximum);
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
// Vector Operations
void vec3f_copy(                         Vec3f dest, Vec3f src);
void vec3f_set(                          Vec3f dest, f32 x, f32 y, f32 z);
void vec3f_sum(                          Vec3f dest, Vec3f a, Vec3f b);
void vec3f_diff(                         Vec3f dest, Vec3f a, Vec3f b);
void vec3f_add(                          Vec3f dest, Vec3f a);
void vec3f_sub(                          Vec3f dest, Vec3f a);
void vec3i_copy(                         Vec3i dest, Vec3i src);
void vec3i_set(                          Vec3i dest, s32 x, s32 y, s32 z);
void vec3i_sum(                          Vec3i dest, Vec3i a, Vec3i b);
void vec3i_diff(                         Vec3i dest, Vec3i a, Vec3i b);
void vec3i_add(                          Vec3i dest, Vec3i a);
void vec3i_sub(                          Vec3i dest, Vec3i a);
void vec3s_copy(                         Vec3s dest, Vec3s src);
void vec3s_set(                          Vec3s dest, s16 x, s16 y, s16 z);
void vec3s_sum(                          Vec3s dest, Vec3s a, Vec3s b);
void vec3s_diff(                         Vec3s dest, Vec3s a, Vec3s b);
void vec3s_add(                          Vec3s dest, Vec3s a);
void vec3s_sub(                          Vec3s dest, Vec3s a);
void vec3s_to_vec3i(                     Vec3i dest, Vec3s a);
void vec3i_to_vec3s(                     Vec3s dest, Vec3i a);
void vec3s_to_vec3f(                     Vec3f dest, Vec3s a);
void vec3i_to_vec3f(                     Vec3f dest, Vec3i a);
void vec3f_to_vec3s(                     Vec3s dest, Vec3f a);
void find_vector_perpendicular_to_plane( Vec3f dest, Vec3f a, Vec3f b, Vec3f c);
void vec3f_cross(                        Vec3f dest, Vec3f a, Vec3f b);
f32  vec3f_mag(                          Vec3f v);
void vec3f_normalize(                    Vec3f dest);
void vec3f_normalize_max(                Vec3f dest, f32 max);
void vec3f_get_lateral_dist(             Vec3f from, Vec3f to, f32 *dist);
void vec3f_get_dist(                     Vec3f from, Vec3f to, f32 *dist);
void vec3f_get_pitch(                    Vec3f from, Vec3f to,            Angle *pitch);
void vec3f_get_yaw(                      Vec3f from, Vec3f to,                          Angle *yaw);
void vec3f_get_angle(                    Vec3f from, Vec3f to, Angle *pitch, Angle *yaw);
void vec3f_get_lateral_dist_and_angle(   Vec3f from, Vec3f to, f32 *dist, Angle *pitch, Angle *yaw);
void vec3f_get_dist_and_angle(           Vec3f from, Vec3f to, f32 *dist, Angle *pitch, Angle *yaw);
void vec3f_set_dist_and_angle(           Vec3f from, Vec3f to, f32  dist, Angle  pitch, Angle  yaw);
void vec3f_mul_f32(                      Vec3f dest, f32 scale);
void vec3f_div_f32(                      Vec3f dest, f32 scale);
void vec3f_scale_f32(                        Vec3f dest, Vec3f src,   f32 scale, u32 doInverted);
void vec3f_scale_vec3f(                  Vec3f dest, Vec3f src, Vec3f scale, u32 doInverted);
void vec3f_rotate(                        Mat4 mat, Vec3f in, Vec3f out);
void vec3f_transform(                     Mat4 mat, Vec3f in, f32 w, Vec3f out);
void vec3f_transform_vtx(                 Mat4 mat, Vec3f in, f32 w, Vtx  *out);
void scale_along_line(                   Vec3f dest, Vec3f from, Vec3f to, f32 scale);
f32  vec3f_dot(                          Vec3f a, Vec3f b);
f32  vec4f_dot(                          Vec4f a, Vec4f b);
void vec4f_scale(                        Vec4f dest, Vec4f src, f32 scale);
void make_oblique(                        Mat4 toModify, Vec4f clipPlane);
// Matrix operations
void mtxf_copy(                           Mat4 dest,  Mat4 src);
void mtxf_identity(                       Mat4  mtx);
void mtxf_translate(                      Mat4 dest, Vec3f b);
#ifdef CUSTOM_FOV
void mtxf_lookat(                         Mat4  mtx,  Vec3f from, Vec3f to, Angle roll, f32 fov);
#else
void mtxf_lookat(                         Mat4  mtx,  Vec3f from, Vec3f to, Angle roll);
#endif
void mtxf_rotate_zxy_and_translate(       Mat4 dest, Vec3f translate, Vec3a rotate);
void mtxf_rotate_xyz_and_translate(       Mat4 dest, Vec3f b, Vec3s c);
void mtxf_billboard(                      Mat4 dest, Mat4 mtx, Vec3f position, Angle roll, s32 zOffset);
void mtxf_align_facing_view(              Mat4 dest, Mat4 mtx, Vec3f position, Angle roll, s32 zOffset);
void mtxf_align_terrain_normal(           Mat4 dest, Vec3f upDir, Vec3f pos, Angle yaw);
void mtxf_align_terrain_triangle(         Mat4  mtx, Vec3f pos, Angle yaw, f32 radius);
void mtxf_mul(                            Mat4 dest, Mat4 a, Mat4 b);
void mtxf_scale_vec3f(                    Mat4 dest, Mat4 mtx, Vec3f s);
void mtxf_mul_vec3s(                      Mat4  mtx, Vec3s b);
void mtxf_mul_vec3f(                      Mat4  mtx, Vec3f b);
void linear_mtxf_mul_vec3f(               Mat4  mtx, Vec3f dst, Vec3f v);
void linear_mtxf_transpose_mul_vec3f(     Mat4  mtx, Vec3f dst, Vec3f v);
void mtxf_to_mtx(                         Mtx *dest, Mat4 src);
void mtxf_rotate_xy(                      Mtx  *mtx, Angle angle);
void get_pos_from_transform_mtx(         Vec3f dest, Mat4 objMtx, Mat4 camMtx);
void mtxf_inverse_rotate_translate(       Mat4   in, Mat4 out);
// Approach
s32    approach_s32(                      s32  current,   s32 target,   s32 inc, s32 dec);
f32    approach_f32(                      f32  current,   f32 target,   f32 inc, f32 dec);
f32    approach_f32_by_increment(         f32  current,   f32 target,   f32 inc);
Bool32 approach_f32_ptr(                  f32 *current,   f32 target,   f32 inc);
Bool32 approach_f32_ptr_signed(           f32 *current,   f32 target,   f32 inc);
f32    approach_f32_symmetric(            f32  current,   f32 target,   f32 inc);
Bool32 approach_f32_symmetric_bool(       f32 *current,   f32 target,   f32 inc);
s32    approach_s16_symmetric(            s16  current,   s16 target,   s16 inc);
Bool32 approach_s16_symmetric_bool(       s16 *current,   s16 target,   s16 inc);
Bool32 approach_f32_asymptotic_bool(      f32 *current,   f32 target,   f32 multiplier);
f32    approach_f32_asymptotic(           f32  current,   f32 target,   f32 multiplier);
Bool32 approach_s16_asymptotic_bool(      s16 *current,   s16 target,   s16 divisor);
s32    approach_s16_asymptotic(           s16  current,   s16 target,   s16 divisor);
void   approach_vec3f_asymptotic(       Vec3f  current, Vec3f target, f32 xMul, f32 yMul, f32 zMul);
void   approach_vec3s_asymptotic(        Vec3s current, Vec3s target, s16 xMul, s16 yMul, s16 zMul);
// Trig
f64   sind(f64 x);
f64   cosd(f64 x);
s16   LENSIN(s16 length, Angle direction);
s16   LENCOS(s16 length, Angle direction);
Angle atan2s(f32 y, f32 x);
f32   atan2f(f32 a, f32 b);
f32   atan2_deg(f32 a, f32 b);
// Curves
void spline_get_weights(Vec4f result, f32 t, UNUSED s32 c);
void anim_spline_init(Vec4s *keyFrames);
Bool32 anim_spline_poll( Vec3f result);
void evaluate_cubic_spline(f32 u, Vec3f Q, Vec3f a0, Vec3f a1, Vec3f a2, Vec3f a3);

#endif // MATH_UTIL_H
