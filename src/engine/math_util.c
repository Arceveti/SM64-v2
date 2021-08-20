#include <ultra64.h>

#include "sm64.h"
#include "engine/graph_node.h"
#include "math_util.h"
#include "surface_collision.h"
#include "extended_bounds.h"
#include "trig_tables.inc.c"

#include "config.h"

/**************************
 * Float functions (Kaze) *
 **************************/

#define FLOAT_MIN -3.40282e+38f

static f32 const E = 2.718281828459f;
f32 slow_logf(f32 x) {
    f32 p = 0.0f;
    f32 r = 0.0f, c = -1.0f;
    s32 i;
    if (x == 0.0f) return FLOAT_MIN;
    while (x < 0.5f) {
        x *= E;
        ++p;
    }
    x -= 1.0f;
    for (i = 1; i < 8; ++i) {
        c *= -x;
        r += (c / i);
    }
    return (r - p);
}

f32 slow_expf(f32 x) {
    f32 r = 1.0f, c = 1.0f;
    s32 i;
    x = -x;
    for (i = 1; i < 8; ++i) {
        c *= (x / i);
        r += c;
    }
    return (1.0f / r);
}

f32 slow_powf(f32 base, f32 exponent) {
    if (base <= 0.0f) return 0.0f;
    return slow_expf(exponent * slow_logf(base));
}

#ifdef FAST_INVSQRT

/****************************
 * Fast Inverse Square Root *
 ****************************/

f32 Q_rsqrtf( f32 number ) {
	long i;
	f32 x2, y;
	x2 = (number * 0.5f);
	y  =  number;
	i  = *(long *) &y;
	i  = (0x5f3759df - (i >> 1));
	y  = *(f32 *) &i;
	y  = (y * (1.5f - (x2 * y * y))); // 1st iteration
	// y  = (y * (1.5f - (x2 * y * y))); // 2nd iteration, this can be removed
	return y;
}

f64 Q_rsqrtd( f64 number ) {
	long i;
	f64 x2, y;
	x2 = (number * 0.5);
	y  =  number;
	i  = *(long *) &y;
    // The magic number is for doubles is from https://cs.uwaterloo.ca/~m32rober/rsqrt.pdf
	i  = (0x5fe6eb50c7b537a9 - (i >> 1));
	y  = *(f64 *) &i;
	y  = (y * (1.5 - (x2 * y * y))); // 1st iteration
    // y  = (y * (1.5 - (x2 * y * y))); // 2nd iteration, this can be removed
	return y;
}
#endif

/************
 * Rounding *
 ************/

/// From Wiseguy
static __inline__ s32 roundf(f32 in) {
    f32 tmp;
    s32 out;
    __asm__("round.w.s %0,%1" : "=f" (tmp) : "f" (in));
    __asm__("mfc1 %0,%1" : "=r" (out) : "f" (tmp));
    return out;
}

/// Round `num` to the nearest integer.
inline s16 round_float_to_short( f32 num) { return num + ((num >= 0.0f) ? 0.5f : -0.5f); }
inline s32 round_float_to_int(   f32 num) { return num + ((num >= 0.0f) ? 0.5f : -0.5f); }
inline s16 round_double_to_short(f64 num) { return num + ((num >= 0.0 ) ? 0.5  : -0.5 ); }
inline s32 round_double_to_int(  f64 num) { return num + ((num >= 0.0 ) ? 0.5  : -0.5 ); }

/***********************************
 * Absolute value & sign functions *
 ***********************************/

/// From Wiseguy
// http://www.terathon.com/code/oblique.html
inline f32 sgn(f32 a) {
    if (a > 0.0f) return ( 1.0f);
    if (a < 0.0f) return (-1.0f);
    return (0.0f);
}

inline s32 signum_positive(s32 x) {
    return ((x >= 0) ? 1 : -1);
}

inline s8  absc(s8  x) { return ((x < 0   ) ? -x : x); }
inline s16 abss(s16 x) { return ((x < 0   ) ? -x : x); }
inline s32 absi(s32 x) { return ((x < 0   ) ? -x : x); }
inline f32 absf(f32 x) { return ((x < 0.0f) ? -x : x); }
inline f64 absd(f64 x) { return ((x < 0.0 ) ? -x : x); }

/***********************
 * Min/Max 3 functions *
 ***********************/

/// Returns the lowest of three values.
inline s8  min_3c( s8  a0, s8  a1,  s8 a2) { if (a1 < a0) a0 = a1; if (a2 < a0) a0 = a2; return a0; }
inline u8  min_3uc(u8  a0, u8  a1,  u8 a2) { if (a1 < a0) a0 = a1; if (a2 < a0) a0 = a2; return a0; }
inline s16 min_3s( s16 a0, s16 a1, s16 a2) { if (a1 < a0) a0 = a1; if (a2 < a0) a0 = a2; return a0; }
inline u16 min_3us(s16 a0, u16 a1, u16 a2) { if (a1 < a0) a0 = a1; if (a2 < a0) a0 = a2; return a0; }
inline s32 min_3i( s32 a0, s32 a1, s32 a2) { if (a1 < a0) a0 = a1; if (a2 < a0) a0 = a2; return a0; }
inline u32 min_3ui(u32 a0, u32 a1, u32 a2) { if (a1 < a0) a0 = a1; if (a2 < a0) a0 = a2; return a0; }
inline f32 min_3f( f32 a0, f32 a1, f32 a2) { if (a1 < a0) a0 = a1; if (a2 < a0) a0 = a2; return a0; }
inline f64 min_3d( f64 a0, f64 a1, f64 a2) { if (a1 < a0) a0 = a1; if (a2 < a0) a0 = a2; return a0; }

/// Returns the highest of three values.
inline s8  max_3c( s8  a0,  s8 a1,  s8 a2) { if (a1 > a0) a0 = a1; if (a2 > a0) a0 = a2; return a0; }
inline u8  max_3uc(u8  a0,  u8 a1,  u8 a2) { if (a1 > a0) a0 = a1; if (a2 > a0) a0 = a2; return a0; }
inline s16 max_3s( s16 a0, s16 a1, s16 a2) { if (a1 > a0) a0 = a1; if (a2 > a0) a0 = a2; return a0; }
inline u16 max_3us(u16 a0, u16 a1, u16 a2) { if (a1 > a0) a0 = a1; if (a2 > a0) a0 = a2; return a0; }
inline s32 max_3i( s32 a0, s32 a1, s32 a2) { if (a1 > a0) a0 = a1; if (a2 > a0) a0 = a2; return a0; }
inline u32 max_3ui(u32 a0, u32 a1, u32 a2) { if (a1 > a0) a0 = a1; if (a2 > a0) a0 = a2; return a0; }
inline f32 max_3f( f32 a0, f32 a1, f32 a2) { if (a1 > a0) a0 = a1; if (a2 > a0) a0 = a2; return a0; }
inline f64 max_3d( f64 a0, f64 a1, f64 a2) { if (a1 > a0) a0 = a1; if (a2 > a0) a0 = a2; return a0; }

/**********
 * Angles *
 **********/

inline Angle abs_angle_diff(Angle angle1, Angle angle2) {
    Angle diff = (angle2 - angle1);
    if (diff == -0x8000) diff = -0x7FFF;
    return absi(diff);
}

/*************************
 *          RNG          *
 *************************/

static u16 gRandomSeed16;

// Generate a pseudorandom integer from 0 to 65535 from the random seed, and update the seed.
u16 random_u16(void) {
    if (gRandomSeed16 == 0x560A) gRandomSeed16 = 0x0;
    u16 temp1     = ((gRandomSeed16 & 0x00FF) << 8);
    temp1         =  (temp1 ^ gRandomSeed16);
    gRandomSeed16 = ((temp1 & 0x00FF) << 8) + ((temp1 & 0xFF00) >> 8);
    temp1         = ((temp1 & 0x00FF) << 1) ^ gRandomSeed16;
    u16 temp2     =  (temp1 >> 1) ^ 0xFF80;
    if (temp1 & 0x1) {
        gRandomSeed16 =  (temp2 ^ 0x8180);
    } else {
        gRandomSeed16 = ((temp2 == 0xAA55) ? 0 : (temp2 ^ 0x1FF4));
    }
    return gRandomSeed16;
}

// Return either -1 or 1 with a 50:50 chance.
s32 random_sign(void) {
    return ((random_u16() >= 0x7FFF) ? 1 : -1);
}

// Generate a pseudorandom float in the range [0, 1).
f32 random_float(void) {
    return ((f32)(random_u16()) / (double) 0x10000);
}

f32 random_f32_around_zero(f32 diameter) {
    return ((random_float() * diameter) - (diameter / 2));
}

/**
 * Generate a vector with all three values about zero. The
 * three ranges determine how wide the range about zero.
 */
void random_vec3s(Vec3s dest, s16 xRange, s16 yRange, s16 zRange) {
    dest[0] = ((random_float() * xRange) - (xRange / 2));
    dest[1] = ((random_float() * yRange) - (yRange / 2));
    dest[2] = ((random_float() * zRange) - (zRange / 2));
}

/*********************
 * Vector Operations *
 *********************/

/// Copy vector 'src' to 'dest'
void vec3f_copy(Vec3f dest, Vec3f src) {
    dest[0] = src[0];
    dest[1] = src[1];
    dest[2] = src[2];
}

/// Set vector 'dest' to (x, y, z)
void vec3f_set(Vec3f dest, f32 x, f32 y, f32 z) {
    dest[0] = x;
    dest[1] = y;
    dest[2] = z;
}

/// Make 'dest' the sum of vectors a and b.
void vec3f_sum(Vec3f dest, Vec3f a, Vec3f b) {
    dest[0] = (a[0] + b[0]);
    dest[1] = (a[1] + b[1]);
    dest[2] = (a[2] + b[2]);
}

/// Make 'dest' the difference of vectors a and b.
void vec3f_diff(Vec3f dest, Vec3f a, Vec3f b) {
    dest[0] = (a[0] - b[0]);
    dest[1] = (a[1] - b[1]);
    dest[2] = (a[2] - b[2]);
}

/// Add vector 'a' to 'dest'
void vec3f_add(Vec3f dest, Vec3f a) {
    vec3f_sum(dest, dest, a);
}

/// Subtract vector 'a' from 'dest'
void vec3f_sub(Vec3f dest, Vec3f a) {
    vec3f_diff(dest, dest, a);
}

/// Set vector 'dest' to (x, y, z)
void vec3i_set(Vec3i dest, s32 x, s32 y, s32 z) {
    dest[0] = x;
    dest[1] = y;
    dest[2] = z;
}

/// Copy vector src to dest
void vec3i_copy(Vec3i dest, Vec3i src) {
    dest[0] = src[0];
    dest[1] = src[1];
    dest[2] = src[2];
}

/// Copy vector src to dest
void vec3s_copy(Vec3s dest, Vec3s src) {
    dest[0] = src[0];
    dest[1] = src[1];
    dest[2] = src[2];
}

/// Set vector 'dest' to (x, y, z)
void vec3s_set(Vec3s dest, s16 x, s16 y, s16 z) {
    dest[0] = x;
    dest[1] = y;
    dest[2] = z;
}

/// Make 'dest' the sum of vectors a and b.
void vec3s_sum(Vec3s dest, Vec3s a, Vec3s b) {
    dest[0] = (a[0] + b[0]);
    dest[1] = (a[1] + b[1]);
    dest[2] = (a[2] + b[2]);
}

/// Make 'dest' the difference of vectors a and b.
void vec3s_diff(Vec3s dest, Vec3s a, Vec3s b) {
    dest[0] = (a[0] - b[0]);
    dest[1] = (a[1] - b[1]);
    dest[2] = (a[2] - b[2]);
}

/// Add vector a to 'dest'
void vec3s_add(Vec3s dest, Vec3s a) {
    vec3s_sum(dest, dest, a);
}

/// Subtract vector a from 'dest'
void vec3s_sub(Vec3s dest, Vec3s a) {
    vec3s_diff(dest, dest, a);
}

/// Convert short vector a to int vector 'dest'
void vec3s_to_vec3i(Vec3i dest, Vec3s a) {
    dest[0] = a[0];
    dest[1] = a[1];
    dest[2] = a[2];
}

/// Convert int vector a to short vector 'dest'
void vec3i_to_vec3s(Vec3s dest, Vec3i a) {
    dest[0] = a[0];
    dest[1] = a[1];
    dest[2] = a[2];
}

/// Convert short vector a to float vector 'dest'
void vec3s_to_vec3f(Vec3f dest, Vec3s a) {
    dest[0] = a[0];
    dest[1] = a[1];
    dest[2] = a[2];
}

/// Convert int vector a to float vector 'dest'
void vec3i_to_vec3f(Vec3f dest, Vec3i a) {
    dest[0] = a[0];
    dest[1] = a[1];
    dest[2] = a[2];
}

/**
 * Convert float vector a to a short vector 'dest' by rounding the components
 * to the nearest integer.
 */
void vec3f_to_vec3s(Vec3s dest, Vec3f a) {
    dest[0] = roundf(a[0]);
    dest[1] = roundf(a[1]);
    dest[2] = roundf(a[2]);
}

/**
 * Convert float vector a to a int vector 'dest' by rounding the components
 * to the nearest integer.
 */
void vec3f_to_vec3i(s32 dest[3], Vec3f a) {
    dest[0] = roundf(a[0]);
    dest[1] = roundf(a[1]);
    dest[2] = roundf(a[2]);
}

/**
 * Set 'dest' the normal vector of a triangle with vertices a, b and c.
 * It is similar to vec3f_cross, but it calculates the vectors (c-b) and (b-a)
 * at the same time.
 */
void find_vector_perpendicular_to_plane(Vec3f dest, Vec3f a, Vec3f b, Vec3f c) {
    dest[0] = ((b[1] - a[1]) * (c[2] - b[2]) - (c[1] - b[1]) * (b[2] - a[2]));
    dest[1] = ((b[2] - a[2]) * (c[0] - b[0]) - (c[2] - b[2]) * (b[0] - a[0]));
    dest[2] = ((b[0] - a[0]) * (c[1] - b[1]) - (c[0] - b[0]) * (b[1] - a[1]));
}

/// Make vector 'dest' the cross product of vectors a and b.
void vec3f_cross(Vec3f dest, Vec3f a, Vec3f b) {
    dest[0] = ((a[1] * b[2]) - (b[1] * a[2]));
    dest[1] = ((a[2] * b[0]) - (b[2] * a[0]));
    dest[2] = ((a[0] * b[1]) - (b[0] * a[1]));
}

/// Get the magnitude of vector 'v'
f32 vec3f_mag(Vec3f v) {
	return sqrtf(sqr(v[0]) + sqr(v[1]) + sqr(v[2]));
}

/// Scale vector 'dest' so it has length 1
void vec3f_normalize(Vec3f dest) {
     if (dest == gVec3fZero) {
        dest[0] = dest[1] = dest[2] = 0.0f;
    } else {
#ifdef FAST_INVSQRT
        register f32 mag = Q_rsqrtf(sqr(dest[0]) + sqr(dest[1]) + sqr(dest[2]));
#else
        register f32 mag = 1.0f / vec3f_mag(dest);
#endif
        if (mag == 0.0f) {
            vec3f_copy(dest, gVec3fZero);
            return;
        }
        vec3f_mul_f32(dest, mag);
    }
}

/// Scale vector 'dest' so it has length 'max'
void vec3f_normalize_max(Vec3f dest, f32 max) {
    register f32 mag = vec3f_mag(dest); 
    if (mag > max) {
        mag = max / mag; //! fast invsqrt?
        vec3f_mul_f32(dest, mag);
    }
}

/**
 * Take the vector starting at 'from' pointed at 'to' an retrieve the length
 * of that vector, as well as the yaw and pitch angles.
 * Basically it converts the direction to spherical coordinates.
 */
void vec3f_get_dist_and_angle(Vec3f from, Vec3f to, f32 *dist, Angle *pitch, Angle *yaw) {
    register f32 dx   = (to[0] - from[0]);
    register f32 dy   = (to[1] - from[1]);
    register f32 dz   = (to[2] - from[2]);
    register f32 dxz2 = (sqr(dx) + sqr(dz));
    *dist             = sqrtf(dxz2 + sqr(dy));
    *pitch            = atan2s(sqrtf(dxz2), dy);
    *yaw              = atan2s(dz, dx);
}

/**
 * Construct the 'to' point which is distance 'dist' away from the 'from' position,
 * and has the angles pitch and yaw.
 */
void vec3f_set_dist_and_angle(Vec3f from, Vec3f to, f32 dist, Angle pitch, Angle yaw) {
    to[0] = (from[0] + (dist * coss(pitch) * sins(yaw)));
    to[1] = (from[1] + (dist * sins(pitch)            ));
    to[2] = (from[2] + (dist * coss(pitch) * coss(yaw)));
}

void vec3f_mul_f32(Vec3f dest, f32 scale) {
    dest[0] *= scale;
    dest[1] *= scale;
    dest[2] *= scale;
}

void vec3f_div_f32(Vec3f dest, f32 scale) {
    dest[0] /= scale;
    dest[1] /= scale;
    dest[2] /= scale;
}

void vec3f_scale_f32(Vec3f dest, Vec3f src, f32 scale, u32 doInverted) {
    if (doInverted) {
        dest[0] = (src[0] / scale);
        dest[1] = (src[1] / scale);
        dest[2] = (src[2] / scale);
    } else {
        dest[0] = (src[0] * scale);
        dest[1] = (src[1] * scale);
        dest[2] = (src[2] * scale);
    }
}

/**
 * Upscale or downscale a vector by another vector.
 */
void vec3f_scale_vec3f(Vec3f dest, Vec3f src, Vec3f scale, u32 doInverted) {
    if (doInverted) {
        dest[0] = (src[0] / scale[0]);
        dest[1] = (src[1] / scale[1]);
        dest[2] = (src[2] / scale[2]);
    } else {
        dest[0] = (src[0] * scale[0]);
        dest[1] = (src[1] * scale[1]);
        dest[2] = (src[2] * scale[2]);
    }
}

// Thank you rocket robot
void vec3f_rotate(Mat4 mat, Vec3f in, Vec3f out) {
    out[0] = ((mat[0][0] * in[0]) + (mat[1][0] * in[1]) + (mat[2][0] * in[2]));
    out[1] = ((mat[0][1] * in[0]) + (mat[1][1] * in[1]) + (mat[2][1] * in[2]));
    out[2] = ((mat[0][2] * in[0]) + (mat[1][2] * in[1]) + (mat[2][2] * in[2]));
}

void vec3f_transform(Mat4 mat, Vec3f in, f32 w, Vec3f out) {
    s32 i, j;
    for ((i = 0); (i < 3); (i++)) {
        out[i] = (mat[3][i] * w);
        for ((j = 0); (j < 3); (j++)) out[i] += (mat[j][i] * in[j]);
    }
}

void vec3f_transform_vtx(Mat4 mat, Vec3f in, f32 w, Vtx *out) {
    Vec3f temp;
    s32 i, j;
    for ((i = 0); (i < 3); (i++)) {
        temp[i] = (mat[3][i] * w);
        for ((j = 0); (j < 3); (j++)) temp[i] += (mat[j][i] * in[j]);
    }
    out->v.ob[0] = temp[0];
    out->v.ob[1] = temp[1];
    out->v.ob[2] = temp[2];
}

f32 vec3f_dot(Vec3f a, Vec3f b) {
    return ((a[0] * b[0]) + (a[1] * b[1]) + (a[2] * b[2]));
}

f32 vec4f_dot(Vec4f a, Vec4f b) {
    return ((a[0] * b[0]) + (a[1] * b[1]) + (a[2] * b[2]) + (a[3] * b[3]));
}

void vec4f_scale(Vec4f dest, Vec4f src, f32 scale) {
    dest[0] = (src[0] * scale);
    dest[1] = (src[1] * scale);
    dest[2] = (src[2] * scale);
    dest[3] = (src[3] * scale);
}

void make_oblique(Mat4 toModify, Vec4f clipPlane) {
    Vec4f q, c;
    // Calculate the clip-space corner point opposite the clipping plane
    // as (sgn(clipPlane.x), sgn(clipPlane.y), 1, 1) and
    // transform it into camera space by multiplying it
    // by the inverse of the projection matrix
    q[0] = (sgn(clipPlane[0]) / toModify[0][0]);
    q[1] = (sgn(clipPlane[1]) / toModify[1][1]);
    q[2] = -1.0f;
    q[3] = (1.0f + toModify[2][2]) / toModify[3][2];
    // Calculate the scaled plane vector
    vec4f_scale(c, clipPlane, (2.0f / vec4f_dot(clipPlane, q)));
    // Replace the third row of the projection matrix
    toModify[0][2] =  c[0];
    toModify[1][2] =  c[1];
    toModify[2][2] = (c[2] + 1.0f);
    toModify[3][2] =  c[3];
}

/*********************
 * Matrix Operations *
 *********************/

/**
 * [0][0]   x scale
 * [0][1]   y shear
 * [0][2]   z x shear?
 * [0][3]   width crop?
 * [1][0]   x shear
 * [1][1]   y scale
 * [1][2]   z z shear?
 * [1][3]   y crop?
 * [2][0]   z x shear?
 * [2][1]   z y shear?
 * [2][2]   z scale
 * [2][3]   z crop?
 * [3][0]   x translation
 * [3][1]   y translation
 * [3][2]   z translation
 * [3][3]   z translation scale?
 **/

/// Copy matrix 'src' to 'dest'
void mtxf_copy(Mat4 dest, Mat4 src) {
    register s32 i;
    register u32 *d = (u32 *) dest;
    register u32 *s = (u32 *) src;
    for (i = 0; i < 16; i++) *d++ = *s++;
}

/**
 * Set mtx to the identity matrix
 */
void mtxf_identity(Mat4 mtx) {
    register s32 i;
    register f32 *dest;
    // initialize everything except the first and last cells to 0
    for (dest = (f32 *) mtx + 1, i = 0; i < 14; dest++   , i++) *dest = 0;
    // initialize the diagonal cells to 1
    for (dest = (f32 *) mtx    , i = 0; i <  4; dest += 5, i++) *dest = 1;
}

/**
 * Set dest to a translation matrix of vector b
 */
void mtxf_translate(Mat4 dest, Vec3f b) {
    mtxf_identity(dest);
    dest[3][0] = b[0];
    dest[3][1] = b[1];
    dest[3][2] = b[2];
}

/**
 * Set mtx to a look-at matrix for the camera. The resulting transformation
 * transforms the world as if there exists a camera at position 'from' pointed
 * at the position 'to'. The up-vector is assumed to be (0, 1, 0), but the 'roll'
 * angle allows a bank rotation of the camera.
 */
#ifdef CUSTOM_FOV
void mtxf_lookat(Mat4 mtx, Vec3f from, Vec3f to, Angle roll, f32 fov) {
#else
void mtxf_lookat(Mat4 mtx, Vec3f from, Vec3f to, Angle roll) {
#endif
    register f32 invLength;
    register f32 xColY, yColY, zColY;
    register f32 xColZ, yColZ, zColZ;
    register f32 xColX, yColX, zColX;
    register f32 dx = (to[0] - from[0]);
    register f32 dz = (to[2] - from[2]);
#ifdef FAST_INVSQRT_MTXF_LOOKAT
    invLength = -Q_rsqrtf(sqr(dx) + sqr(dz));
#else
    invLength = -(1.0f / MAX(sqrtf(sqr(dx) + sqr(dz)), 0.00001f));
#endif
    dx *= invLength;
    dz *= invLength;
    yColY =   coss(roll);
    xColY = ( sins(roll) * dz);
    zColY = (-sins(roll) * dx);
    xColZ = (to[0] - from[0]);
    yColZ = (to[1] - from[1]);
    zColZ = (to[2] - from[2]);
#ifdef CUSTOM_FOV
#ifdef FAST_INVSQRT_MTXF_LOOKAT
    invLength = -Q_rsqrtf(sqr(xColZ) + sqr(yColZ) + sqr(zColZ)) * fov;
#else
    invLength = -(fov / MAX(sqrtf(sqr(xColZ) + sqr(yColZ) + sqr(zColZ)), 0.00001f));
#endif
#else
#ifdef FAST_INVSQRT_MTXF_LOOKAT
    invLength = -Q_rsqrtf(sqr(xColZ) + sqr(yColZ) + sqr(zColZ));
#else
    invLength = -(1.0f / MAX(sqrtf(sqr(xColZ) + sqr(yColZ) + sqr(zColZ)), 0.00001f));
#endif
#endif
    xColZ *= invLength;
    yColZ *= invLength;
    zColZ *= invLength;
    xColX = ((yColY * zColZ) - (zColY * yColZ));
    yColX = ((zColY * xColZ) - (xColY * zColZ));
    zColX = ((xColY * yColZ) - (yColY * xColZ));
#ifdef FAST_INVSQRT_MTXF_LOOKAT
    invLength = Q_rsqrtf(sqr(xColX) + sqr(yColX) + sqr(zColX));
#else
    invLength = (1.0f / MAX(sqrtf(sqr(xColX) + sqr(yColX) + sqr(zColX)), 0.00001f));
#endif
    xColX *= invLength;
    yColX *= invLength;
    zColX *= invLength;
    xColY = ((yColZ * zColX) - (zColZ * yColX));
    yColY = ((zColZ * xColX) - (xColZ * zColX));
    zColY = ((xColZ * yColX) - (yColZ * xColX));
#ifdef FAST_INVSQRT_MTXF_LOOKAT
    invLength = Q_rsqrtf(sqr(xColY) + sqr(yColY) + sqr(zColY));
#else
    invLength = (1.0f / MAX(sqrtf(sqr(xColY) + sqr(yColY) + sqr(zColY)), 0.00001f));
#endif
    xColY *= invLength;
    yColY *= invLength;
    zColY *= invLength;
    mtx[0][0] = xColX;
    mtx[1][0] = yColX;
    mtx[2][0] = zColX;
    mtx[3][0] = -((from[0] * xColX) + (from[1] * yColX) + (from[2] * zColX));
    mtx[0][1] = xColY;
    mtx[1][1] = yColY;
    mtx[2][1] = zColY;
    mtx[3][1] = -((from[0] * xColY) + (from[1] * yColY) + (from[2] * zColY));
    mtx[0][2] = xColZ;
    mtx[1][2] = yColZ;
    mtx[2][2] = zColZ;
    mtx[3][2] = -((from[0] * xColZ) + (from[1] * yColZ) + (from[2] * zColZ));
    mtx[0][3] = 0;
    mtx[1][3] = 0;
    mtx[2][3] = 0;
    mtx[3][3] = 1;
}

/**
 * Build a matrix that rotates around the z axis, then the x axis, then the y
 * axis, and then translates.
 */
void mtxf_rotate_zxy_and_translate(Mat4 dest, Vec3f translate, Vec3a rotate) {
    register f32 sx = sins(rotate[0]);
    register f32 cx = coss(rotate[0]);
    register f32 sy = sins(rotate[1]);
    register f32 cy = coss(rotate[1]);
    register f32 sz = sins(rotate[2]);
    register f32 cz = coss(rotate[2]);
    dest[0][0] = (( cy * cz) + (sx * sy * sz));
    dest[1][0] = ((-cy * sz) + (sx * sy * cz));
    dest[2][0] =  ( cx * sy);
    dest[3][0] = translate[0];
    dest[0][1] =  ( cx * sz);
    dest[1][1] =  ( cx * cz);
    dest[2][1] = -sx;
    dest[3][1] = translate[1];
    dest[0][2] = ((-sy * cz) + (sx * cy * sz));
    dest[1][2] = (( sy * sz) + (sx * cy * cz));
    dest[2][2] =  ( cx * cy);
    dest[3][2] = translate[2];
    dest[0][3] = dest[1][3] = dest[2][3] = 0.0f;
    dest[3][3] = 1.0f;
}

/**
 * Build a matrix that rotates around the x axis, then the y axis, then the z
 * axis, and then translates.
 */
void mtxf_rotate_xyz_and_translate(Mat4 dest, Vec3f b, Vec3s c) {
    register f32 sx = sins(c[0]);
    register f32 cx = coss(c[0]);
    register f32 sy = sins(c[1]);
    register f32 cy = coss(c[1]);
    register f32 sz = sins(c[2]);
    register f32 cz = coss(c[2]);
    dest[0][0] = (cy * cz);
    dest[0][1] = (cy * sz);
    dest[0][2] = -sy;
    dest[0][3] = 0;
    dest[1][0] = ((sx * sy * cz) - (cx * sz));
    dest[1][1] = ((sx * sy * sz) + (cx * cz));
    dest[1][2] = (sx * cy);
    dest[1][3] = 0;
    dest[2][0] = ((cx * sy * cz) + (sx * sz));
    dest[2][1] = ((cx * sy * sz) - (sx * cz));
    dest[2][2] = (cx * cy);
    dest[2][3] = 0;
    dest[3][0] =  b[0];
    dest[3][1] =  b[1];
    dest[3][2] =  b[2];
    dest[3][3] = 1;
}

/**
 * Set 'dest' to a transformation matrix that turns an object to face parallel to the camera.
 * 'mtx' is the look-at matrix from the camera
 * 'position' is the position of the object in the world
 * 'angle' rotates the object while still facing the camera.
 */
void mtxf_billboard(Mat4 dest, Mat4 mtx, Vec3f position, Angle angle, s32 zOffset) {
    dest[0][0] = coss(angle);
    dest[0][1] = sins(angle);
    dest[0][2] = 0;
    dest[0][3] = 0;
    dest[1][0] = -dest[0][1];
    dest[1][1] =  dest[0][0];
    dest[1][2] = 0;
    dest[1][3] = 0;
    dest[2][0] = 0;
    dest[2][1] = 0;
    dest[2][2] = 1;
    dest[2][3] = 0;
    if (position[0] == 0 && position[1] == 0 && position[2] == 0) {
        dest[3][0] = mtx[3][0];
        dest[3][1] = mtx[3][1];
        dest[3][2] = mtx[3][2];
    } else {
        dest[3][0] = ((mtx[0][0] * position[0]) + (mtx[1][0] * position[1]) + (mtx[2][0] * position[2]) + mtx[3][0]);
        dest[3][1] = ((mtx[0][1] * position[0]) + (mtx[1][1] * position[1]) + (mtx[2][1] * position[2]) + mtx[3][1]);
        dest[3][2] = ((mtx[0][2] * position[0]) + (mtx[1][2] * position[1]) + (mtx[2][2] * position[2]) + mtx[3][2]);
    }
    dest[3][3] = (((zOffset == 0) || (dest[3][2] == 0)) ? 1 : ((dest[3][2] - zOffset) / dest[3][2]));
}

/**
 * Set 'dest' to a transformation matrix that turns an object to face directly at the camera
 * 'mtx' is the look-at matrix from the camera
 * 'position' is the position of the object in the world
 * 'angle' rotates the object while still facing the camera.
 */
void mtxf_align_facing_view(Mat4 dest, Mat4 mtx, Vec3f position, Angle roll, s32 zOffset) {
    register Angle xrot, yrot;
    register f32 cx, cy, cz;
    if (position[0] == 0 && position[1] == 0 && position[2] == 0) {
        dest[3][0] = mtx[3][0];
        dest[3][1] = mtx[3][1];
        dest[3][2] = mtx[3][2];
    } else {
        dest[3][0] = ((mtx[0][0] * position[0]) + (mtx[1][0] * position[1]) + (mtx[2][0] * position[2]) + mtx[3][0]);
        dest[3][1] = ((mtx[0][1] * position[0]) + (mtx[1][1] * position[1]) + (mtx[2][1] * position[2]) + mtx[3][1]);
        dest[3][2] = ((mtx[0][2] * position[0]) + (mtx[1][2] * position[1]) + (mtx[2][2] * position[2]) + mtx[3][2]);
    }
    dest[3][3] = ((zOffset == 0 || dest[3][2] == 0) ? 1 : ((dest[3][2] - zOffset) / dest[3][2]));
    // angle to camera pos
    xrot       = -atan2s(dest[3][2], dest[3][0]);
    yrot       =  atan2s(dest[3][2], dest[3][1]);
    cx         = coss(xrot);
    cy         = coss(yrot);
    cz         = coss(roll);
    dest[2][0] = sins(xrot);
    dest[0][2] = -dest[2][0];
    dest[1][2] = sins(yrot);
    dest[2][1] = -dest[1][2];
    dest[0][1] = sins(roll);
    dest[1][0] = -dest[0][1];
    dest[0][0] = (-cx *  cz);
    dest[1][1] = (-cy *  cz);
    dest[2][2] = (-cx * -cy);
    dest[0][3] = 0;
    dest[1][3] = 0;
    dest[2][3] = 0;
}

/**
 * Set 'dest' to a transformation matrix that aligns an object with the terrain
 * based on the normal. Used for enemies.
 * 'upDir' is the terrain normal
 * 'yaw' is the angle which it should face
 * 'pos' is the object's position in the world
 */
void mtxf_align_terrain_normal(Mat4 dest, Vec3f upDir, Vec3f pos, Angle yaw) {
    Vec3f lateralDir, leftDir, forwardDir;
    vec3f_set(                                  lateralDir, sins(yaw), 0x0, coss(yaw));
    vec3f_normalize(                     upDir                                       );
    vec3f_cross(                leftDir, upDir, lateralDir                           );
    vec3f_normalize(            leftDir                                              );
    vec3f_cross(    forwardDir, leftDir, upDir                                       );
    vec3f_normalize(forwardDir                                                       );
    dest[0][0] = leftDir[0];
    dest[0][1] = leftDir[1];
    dest[0][2] = leftDir[2];
    dest[3][0] = pos[0];
    dest[1][0] = upDir[0];
    dest[1][1] = upDir[1];
    dest[1][2] = upDir[2];
    dest[3][1] = pos[1];
    dest[2][0] = forwardDir[0];
    dest[2][1] = forwardDir[1];
    dest[2][2] = forwardDir[2];
    dest[3][2] = pos[2];
    dest[0][3] = 0.0f;
    dest[1][3] = 0.0f;
    dest[2][3] = 0.0f;
    dest[3][3] = 1.0f;
}

/**
 * Set 'mtx' to a transformation matrix that aligns an object with the terrain
 * based on 3 height samples in an equilateral triangle around the object.
 * Used for Mario when crawling or sliding.
 * 'yaw' is the angle which it should face
 * 'pos' is the object's position in the world
 * 'radius' is the distance from each triangle vertex to the center
 */
void mtxf_align_terrain_triangle(Mat4 mtx, Vec3f pos, Angle yaw, f32 radius) {
    struct Surface *floor;
    Vec3f point0, point1, point2;
    Vec3f forward;
    Vec3f xColumn, yColumn, zColumn;
    f32 avgY;
    f32 minY  = -radius * 3;
    point0[0] = (pos[0] + (radius * sins(yaw + 0x2AAA)));
    point0[2] = (pos[2] + (radius * coss(yaw + 0x2AAA)));
    point1[0] = (pos[0] + (radius * sins(yaw + 0x8000)));
    point1[2] = (pos[2] + (radius * coss(yaw + 0x8000)));
    point2[0] = (pos[0] + (radius * sins(yaw + 0xD555)));
    point2[2] = (pos[2] + (radius * coss(yaw + 0xD555)));
    point0[1] =           find_floor(point0[0], (pos[1] + 150.0f), point0[2], &floor);
    point1[1] =           find_floor(point1[0], (pos[1] + 150.0f), point1[2], &floor);
    point2[1] =           find_floor(point2[0], (pos[1] + 150.0f), point2[2], &floor);
    if ((point0[1] - pos[1]) < minY) point0[1] = pos[1];
    if ((point1[1] - pos[1]) < minY) point1[1] = pos[1];
    if ((point2[1] - pos[1]) < minY) point2[1] = pos[1];
    avgY = ((point0[1] + point1[1] + point2[1]) / 3.0f);
    vec3f_set(forward, sins(yaw), 0, coss(yaw));
    find_vector_perpendicular_to_plane(yColumn, point0, point1, point2);
    vec3f_normalize(                   yColumn                        );
    vec3f_cross(              xColumn, yColumn, forward               );
    vec3f_normalize(          xColumn                                 );
    vec3f_cross(     zColumn, xColumn, yColumn                        );
    vec3f_normalize( zColumn                                          );
    mtx[0][0] = xColumn[0];
    mtx[0][1] = xColumn[1];
    mtx[0][2] = xColumn[2];
    mtx[3][0] = pos[0];
    mtx[1][0] = yColumn[0];
    mtx[1][1] = yColumn[1];
    mtx[1][2] = yColumn[2];
    mtx[3][1] = ((avgY < pos[1]) ? pos[1] : avgY);
    mtx[2][0] = zColumn[0];
    mtx[2][1] = zColumn[1];
    mtx[2][2] = zColumn[2];
    mtx[3][2] = pos[2];
    mtx[0][3] = 0;
    mtx[1][3] = 0;
    mtx[2][3] = 0;
    mtx[3][3] = 1;
}

/**
 * Sets matrix 'dest' to the matrix product b * a assuming they are both
 * transformation matrices with a w-component of 1. Since the bottom row
 * is assumed to equal [0, 0, 0, 1], it saves some multiplications and
 * addition.
 * The resulting matrix represents first applying transformation b and
 * then a.
 */
void mtxf_mul(Mat4 dest, Mat4 a, Mat4 b) {
    Mat4 temp;
    register f32 entry0, entry1, entry2;
    // column 0
    entry0     = a[0][0];
    entry1     = a[0][1];
    entry2     = a[0][2];
    temp[0][0] = ((entry0 * b[0][0]) + (entry1 * b[1][0]) + (entry2 * b[2][0]));
    temp[0][1] = ((entry0 * b[0][1]) + (entry1 * b[1][1]) + (entry2 * b[2][1]));
    temp[0][2] = ((entry0 * b[0][2]) + (entry1 * b[1][2]) + (entry2 * b[2][2]));
    // column 1
    entry0     = a[1][0];
    entry1     = a[1][1];
    entry2     = a[1][2];
    temp[1][0] = ((entry0 * b[0][0]) + (entry1 * b[1][0]) + (entry2 * b[2][0]));
    temp[1][1] = ((entry0 * b[0][1]) + (entry1 * b[1][1]) + (entry2 * b[2][1]));
    temp[1][2] = ((entry0 * b[0][2]) + (entry1 * b[1][2]) + (entry2 * b[2][2]));
    // column 2
    entry0     = a[2][0];
    entry1     = a[2][1];
    entry2     = a[2][2];
    temp[2][0] = ((entry0 * b[0][0]) + (entry1 * b[1][0]) + (entry2 * b[2][0]));
    temp[2][1] = ((entry0 * b[0][1]) + (entry1 * b[1][1]) + (entry2 * b[2][1]));
    temp[2][2] = ((entry0 * b[0][2]) + (entry1 * b[1][2]) + (entry2 * b[2][2]));
    // column 3
    entry0     = a[3][0];
    entry1     = a[3][1];
    entry2     = a[3][2];
    temp[3][0] = ((entry0 * b[0][0]) + (entry1 * b[1][0]) + (entry2 * b[2][0]) + b[3][0]);
    temp[3][1] = ((entry0 * b[0][1]) + (entry1 * b[1][1]) + (entry2 * b[2][1]) + b[3][1]);
    temp[3][2] = ((entry0 * b[0][2]) + (entry1 * b[1][2]) + (entry2 * b[2][2]) + b[3][2]);
    temp[0][3] = temp[1][3] = temp[2][3] = 0;
    temp[3][3] = 1;
    mtxf_copy(dest, temp);
}

/**
 * Set matrix 'dest' to 'mtx' scaled by vector s
 */
void mtxf_scale_vec3f(Mat4 dest, Mat4 mtx, Vec3f s) {
    register s32 i;
    for (i = 0; i < 4; i++) {
        dest[0][i] = (mtx[0][i] * s[0]);
        dest[1][i] = (mtx[1][i] * s[1]);
        dest[2][i] = (mtx[2][i] * s[2]);
        dest[3][i] =  mtx[3][i];
    }
}

/**
 * Multiply a vector with a transformation matrix, which applies the transformation
 * to the point. Note that the bottom row is assumed to be [0, 0, 0, 1], which is
 * true for transformation matrices if the translation has a w component of 1.
 */
void mtxf_mul_vec3s(Mat4 mtx, Vec3s b) {
    register f32 x = b[0];
    register f32 y = b[1];
    register f32 z = b[2];
    b[0] = ((x * mtx[0][0]) + (y * mtx[1][0]) + (z * mtx[2][0]) + mtx[3][0]);
    b[1] = ((x * mtx[0][1]) + (y * mtx[1][1]) + (z * mtx[2][1]) + mtx[3][1]);
    b[2] = ((x * mtx[0][2]) + (y * mtx[1][2]) + (z * mtx[2][2]) + mtx[3][2]);
}

/**
 * Need to be able to multiply a vec3f by a matrix for transformation, mostly the same as the above function.
 */
void mtxf_mul_vec3f(Mat4 mtx, Vec3f b) {
    register f32 x = b[0];
    register f32 y = b[1];
    register f32 z = b[2];
    b[0] = ((x * mtx[0][0]) + (y * mtx[1][0]) + (z * mtx[2][0]) + mtx[3][0]);
    b[1] = ((x * mtx[0][1]) + (y * mtx[1][1]) + (z * mtx[2][1]) + mtx[3][1]);
    b[2] = ((x * mtx[0][2]) + (y * mtx[1][2]) + (z * mtx[2][2]) + mtx[3][2]);
}

/**
 * Multiply a vector by a matrix of the form
 * | ? ? ? 0 |
 * | ? ? ? 0 |
 * | ? ? ? 0 |
 * | 0 0 0 1 |
 * i.e. a matrix representing a linear transformation over 3 space.
 */
void linear_mtxf_mul_vec3f(Mat4 mtx, Vec3f dst, Vec3f v) {
    s32 i;
    for (i = 0; i < 3; i++) dst[i] = ((mtx[0][i] * v[0]) + (mtx[1][i] * v[1]) + (mtx[2][i] * v[2]));
}

/**
 * Multiply a vector by the transpose of a matrix of the form
 * | ? ? ? 0 |
 * | ? ? ? 0 |
 * | ? ? ? 0 |
 * | 0 0 0 1 |
 * i.e. a matrix representing a linear transformation over 3 space.
 */
void linear_mtxf_transpose_mul_vec3f(Mat4 mtx, Vec3f dst, Vec3f v) {
    s32 i;
    for (i = 0; i < 3; i++) dst[i] = ((mtx[i][0] * v[0]) + (mtx[i][1] * v[1]) + (mtx[i][2] * v[2]));
}

/**
 * Convert float matrix 'src' to fixed point matrix 'dest'.
 * The float matrix may not contain entries larger than 65536 or the console
 * crashes. The fixed point matrix has entries with a 16-bit integer part, so
 * the floating point numbers are multiplied by 2^16 before being cast to a s32
 * integer. If this doesn't fit, the N64 and iQue consoles will throw an
 * exception. On Wii and Wii U Virtual Console the value will simply be clamped
 * and no crashes occur.
 */
void mtxf_to_mtx(Mtx *dest, Mat4 src) {
	Mat4 temp;
	register s32 i, j;
	for( i = 0; i < 4; i++ ) {
		for( j = 0; j < 3; j++ ) temp[i][j] = (src[i][j] / WORLD_SCALE);
		temp[i][3] = src[i][3];
	}
	guMtxF2L( temp, dest );
}

/**
 * Set 'mtx' to a transformation matrix that rotates around the z axis.
 */
void mtxf_rotate_xy(Mtx *mtx, Angle angle) {
    Mat4 temp;
    mtxf_identity(temp);
    temp[0][0] = coss(angle);
    temp[0][1] = sins(angle);
    temp[1][0] = -temp[0][1];
    temp[1][1] =  temp[0][0];
    mtxf_to_mtx(mtx, temp);
}

/**
 * Extract a position given an object's transformation matrix and a camera matrix.
 * This is used for determining the world position of the held object: since objMtx
 * inherits the transformation from both the camera and Mario, it calculates this
 * by taking the camera matrix and inverting its transformation by first rotating
 * objMtx back from screen orientation to world orientation, and then subtracting
 * the camera position.
 */
void get_pos_from_transform_mtx(Vec3f dest, Mat4 objMtx, Mat4 camMtx) {
    f32 camX = ((camMtx[3][0] * camMtx[0][0]) + (camMtx[3][1] * camMtx[0][1]) + (camMtx[3][2] * camMtx[0][2]));
    f32 camY = ((camMtx[3][0] * camMtx[1][0]) + (camMtx[3][1] * camMtx[1][1]) + (camMtx[3][2] * camMtx[1][2]));
    f32 camZ = ((camMtx[3][0] * camMtx[2][0]) + (camMtx[3][1] * camMtx[2][1]) + (camMtx[3][2] * camMtx[2][2]));
    dest[0]  = ((objMtx[3][0] * camMtx[0][0]) + (objMtx[3][1] * camMtx[0][1]) + (objMtx[3][2] * camMtx[0][2]) - camX);
    dest[1]  = ((objMtx[3][0] * camMtx[1][0]) + (objMtx[3][1] * camMtx[1][1]) + (objMtx[3][2] * camMtx[1][2]) - camY);
    dest[2]  = ((objMtx[3][0] * camMtx[2][0]) + (objMtx[3][1] * camMtx[2][1]) + (objMtx[3][2] * camMtx[2][2]) - camZ);
}

// Rotation/translation matrix inverse
void mtxf_inverse_rotate_translate(Mat4 in, Mat4 out) {
    Mat4 invRot;
    Vec3f negTranslate;
    Mat4 invTranslate;
    invRot[0][0]    = in[0][0];
    invRot[0][1]    = in[1][0];
    invRot[0][2]    = in[2][0];
    invRot[0][3]    = 0.0f;
    invRot[1][0]    = in[0][1];
    invRot[1][1]    = in[1][1];
    invRot[1][2]    = in[2][1];
    invRot[1][3]    = 0.0f;
    invRot[2][0]    = in[0][2];
    invRot[2][1]    = in[1][2];
    invRot[2][2]    = in[2][2];
    invRot[2][3]    = 0.0f;
    invRot[3][0]    = 0.0f;
    invRot[3][1]    = 0.0f;
    invRot[3][2]    = 0.0f;
    invRot[3][3]    = 1.0f;
    negTranslate[0] = -in[3][0];
    negTranslate[1] = -in[3][1];
    negTranslate[2] = -in[3][2];
    mtxf_translate(invTranslate, negTranslate);
    mtxf_mul(out, invTranslate, invRot);
}

/**********************
 * Approach functions *
 **********************/

/**
 * Return the value 'current' after it tries to approach target, going up at
 * most 'inc' and going down at most 'dec'.
 */
s32 approach_s32(s32 current, s32 target, s32 inc, s32 dec) {
    //! If target is close to the max or min s32, then it's possible to overflow
    // past it without stopping.
    if (current < target) {
        current += inc;
        if (current > target) current = target;
    } else {
        current -= dec;
        if (current < target) current = target;
    }
    return current;
}

/**
 * Return the value 'current' after it tries to approach target, going up at
 * most 'inc' and going down at most 'dec'.
 */
f32 approach_f32(f32 current, f32 target, f32 inc, f32 dec) {
    if (current < target) {
        current += inc;
        if (current > target) current = target;
    } else {
        current -= dec;
        if (current < target) current = target;
    }
    return current;
}

s32 approach_f32_signed(f32 *value, f32 target, f32 inc) {
    s32 reachedTarget = FALSE;
    *value += inc;
    if (inc >= 0.0f) {
        if (*value > target) {
            *value = target;
            reachedTarget = TRUE;
        }
    } else {
        if (*value < target) {
            *value = target;
            reachedTarget = TRUE;
        }
    }
    return reachedTarget;
}

f32 approach_f32_symmetric(f32 value, f32 target, f32 inc) {
    f32 dist;
    if ((dist = (target - value)) >= 0.0f) {
        if (dist > inc) {
            value += inc;
        } else {
            value = target;
        }
    } else {
        if (dist < -inc) {
            value -= inc;
        } else {
            value = target;
        }
    }
    return value;
}

s16 approach_s16_symmetric(s16 value, s16 target, s16 inc) {
    s16 dist = (target - value);
    if (dist >= 0) {
        if (dist > inc) {
            value += inc;
        } else {
            value = target;
        }
    } else {
        if (dist < -inc) {
            value -= inc;
        } else {
            value = target;
        }
    }
    return value;
}

/**
 * Approaches an f32 value by taking the difference between the target and current value
 * and adding a fraction of that to the current value.
 * Edits the current value directly, returns TRUE if the target has been reached, FALSE otherwise.
 */
s32 approach_f32_asymptotic_bool(f32 *current, f32 target, f32 multiplier) {
    if (multiplier > 1.0f) multiplier = 1.0f;
    *current = (*current + ((target - *current) * multiplier));
    return !(*current == target);
}

/**
 * Nearly the same as the above function, returns new value instead.
 */
f32 approach_f32_asymptotic(f32 current, f32 target, f32 multiplier) {
    current = (current + ((target - current) * multiplier));
    return current;
}

/**
 * Approaches an s16 value in the same fashion as approach_f32_asymptotic_bool, returns TRUE if target
 * is reached. Note: Since this function takes integers as parameters, the last argument is the
 * reciprocal of what it would be in the previous two functions.
 */
s32 approach_s16_asymptotic_bool(s16 *current, s16 target, s16 divisor) {
    s16 temp = *current;
    if (divisor == 0) {
        *current = target;
    } else {
        temp    -= target;
        temp    -= (temp / divisor);
        temp    += target;
        *current = temp;
    }
    return !(*current == target);
}

/**
 * Approaches an s16 value in the same fashion as approach_f32_asymptotic, returns the new value.
 * Note: last parameter is the reciprocal of what it would be in the f32 functions
 */
s32 approach_s16_asymptotic(s16 current, s16 target, s16 divisor) {
    s16 temp = current;
    if (divisor == 0) {
        current = target;
    } else {
        temp -= target;
        temp -= (temp / divisor);
        temp += target;
        current = temp;
    }
    return current;
}

/**
 * Applies the approach_f32_asymptotic_bool function to each of the X, Y, & Z components of the given
 * vector.
 */
void approach_vec3f_asymptotic(Vec3f current, Vec3f target, f32 xMul, f32 yMul, f32 zMul) {
    approach_f32_asymptotic_bool(&current[0], target[0], xMul);
    approach_f32_asymptotic_bool(&current[1], target[1], yMul);
    approach_f32_asymptotic_bool(&current[2], target[2], zMul);
}

/**
 * Applies the approach_s32_asymptotic function to each of the X, Y, & Z components of the given
 * vector.
 */
void approach_vec3s_asymptotic(Vec3s current, Vec3s target, s16 xMul, s16 yMul, s16 zMul) {
    approach_s16_asymptotic_bool(&current[0], target[0], xMul);
    approach_s16_asymptotic_bool(&current[1], target[1], yMul);
    approach_s16_asymptotic_bool(&current[2], target[2], zMul);
}

/******************
 * Trig Functions *
 ******************/

s16 LENSIN(s16 length, Angle direction) {
    return (length * sins(direction));
}

s16 LENCOS(s16 length, Angle direction) {
    return (length * coss(direction));
}

/**
 * Helper function for atan2s. Does a look up of the arctangent of y/x assuming
 * the resulting angle is in range [0, 0x2000] (1/8 of a circle).
 */
static u16 atan2_lookup(f32 y, f32 x) {
    u16 ret;
    if (x == 0) {
        ret = gArctanTable[0];
    } else {
        ret = gArctanTable[(s32)((((y / x) * 1024) + 0.5f))];
    }
    return ret;
}

/**
 * Compute the angle from (0, 0) to (x, y) as a s16. Given that terrain is in
 * the xz-plane, this is commonly called with (z, x) to get a yaw angle.
 */
Angle atan2s(f32 y, f32 x) {
    u16 ret;
    if (x >= 0) {
        if (y >= 0) {
            if (y >= x) {
                ret = (         atan2_lookup(x, y));
            } else {
                ret = (0x4000 - atan2_lookup(y, x));
            }
        } else {
            y = -y;
            if (y < x) {
                ret = (0x4000 + atan2_lookup(y, x));
            } else {
                ret = (0x8000 - atan2_lookup(x, y));
            }
        }
    } else {
        x = -x;
        if (y < 0) {
            y = -y;
            if (y >= x) {
                ret = (0x8000 + atan2_lookup(x, y));
            } else {
                ret = (0xC000 - atan2_lookup(y, x));
            }
        } else {
            if (y < x) {
                ret = (0xC000 + atan2_lookup(y, x));
            } else {
                ret = (        -atan2_lookup(x, y));
            }
        }
    }
    return ret;
}

/**
 * Compute the atan2 in radians by calling atan2s and converting the result.
 */
f32 atan2f(f32 y, f32 x) {
    return (((f32) atan2s(y, x) * M_PI) / 0x8000);
}

/**********
 * Curves *
 **********/

// Variables for a spline curve animation (used for the flight path in the grand star cutscene)
Vec4s *gSplineKeyframe;
float gSplineKeyframeFraction;
int gSplineState;

#define CURVE_BEGIN_1 0x1
#define CURVE_BEGIN_2 0x2
#define CURVE_MIDDLE  0x3
#define CURVE_END_1   0x4
#define CURVE_END_2   0x5

/**
 * Set 'result' to a 4-vector with weights corresponding to interpolation
 * value t in [0, 1] and gSplineState. Given the current control point P, these
 * weights are for P[0], P[1], P[2] and P[3] to obtain an interpolated point.
 * The weights naturally sum to 1, and they are also always in range [0, 1] so
 * the interpolated point will never overshoot. The curve is guaranteed to go
 * through the first and last point, but not through intermediate points.
 *
 * gSplineState ensures that the curve is clamped: the first two points
 * and last two points have different weight formulas. These are the weights
 * just before gSplineState transitions:
 * 1:    [1,    0,    0,    0]
 * 1->2: [0, 3/12, 7/12, 2/12]
 * 2->3: [0,  1/6,  4/6,  1/6]
 * 3->3: [0,  1/6,  4/6,  1/6] (repeats)
 * 3->4: [0,  1/6,  4/6,  1/6]
 * 4->5: [0, 2/12, 7/12, 3/12]
 * 5:    [0,    0,    0,    1]
 *
 * I suspect that the weight formulas will give a 3rd degree B-spline with the
 * common uniform clamped knot vector, e.g. for n points:
 * [0, 0, 0, 0, 1, 2, ... n-1, n, n, n, n]
 * TODO: verify the classification of the spline / figure out how polynomials were computed
 */
void spline_get_weights(Vec4f result, f32 t, UNUSED s32 c) {
    f32 tinv = 1 - t;
    f32 tinv2 = (tinv  * tinv);
    f32 tinv3 = (tinv2 * tinv);
    f32 t2 = (t  * t);
    f32 t3 = (t2 * t);
    switch (gSplineState) {
        case CURVE_BEGIN_1:
            result[0] =   tinv3;
            result[1] =    (( t3 *        1.75f) - (t2 * 4.5f) + (t * 3.0f));
            result[2] =    ((-t3 * (11 / 12.0f)) + (t2 * 1.5f));
            result[3] =     ( t3 * ( 1 /  6.0f));
            break;
        case CURVE_BEGIN_2:
            result[0] = ( tinv3 * 0.25f);
            result[1] =   (( t3 * (7 / 12.0f)) - (t2 * 1.25f) + (t * 0.25f) + (7 / 12.0f));
            result[2] =   ((-t3 *        0.5f) + (t2 * 0.5f ) + (t * 0.5f ) + (1 /  6.0f));
            result[3] =    ( t3 * (1 /  6.0f));
            break;
        case CURVE_MIDDLE:
            result[0] = ( tinv3 * (1 / 6.0f));
            result[1] =    ( t3 * 0.5f) - t2                   + (4 / 6.0f);
            result[2] =    (-t3 * 0.5f) + (t2 * 0.5f) + (t * 0.5f) + (1 / 6.0f);
            result[3] =    ( t3 * (1 / 6.0f));
            break;
        case CURVE_END_1:
            result[0] = (  tinv3 * (1 /  6.0f));
            result[1] = ((-tinv3 *       0.5f)  + (tinv2 * 0.5f ) + tinv * 0.5f  + (1 /  6.0f));
            result[2] = (( tinv3 * (7 / 12.0f)) - (tinv2 * 1.25f) + tinv * 0.25f + (7 / 12.0f));
            result[3] =      (t3 *       0.25f);
            break;
        case CURVE_END_2:
            result[0] = ( tinv3 * ( 1 /  6.0f));
            result[1] = (-tinv3 * (11 / 12.0f)) + (tinv2 * 1.5f);
            result[2] = ( tinv3 *        1.75f) - (tinv2 * 4.5f) + (tinv * 3.0f);
            result[3] =      t3;
            break;
    }
}

/**
 * Initialize a spline animation.
 * 'keyFrames' should be an array of (s, x, y, z) vectors
 *  s: the speed of the keyframe in 1000/frames, e.g. s=100 means the keyframe lasts 10 frames
 *  (x, y, z): point in 3D space on the curve
 * The array should end with three entries with s=0 (infinite keyframe duration).
 * That's because the spline has a 3rd degree polynomial, so it looks 3 points ahead.
 */
void anim_spline_init(Vec4s *keyFrames) {
    gSplineKeyframe         = keyFrames;
    gSplineKeyframeFraction = 0;
    gSplineState            = 1;
}

/**
 * Poll the next point from a spline animation.
 * anim_spline_init should be called before polling for vectors.
 * Returns TRUE when the last point is reached, FALSE otherwise.
 */
s32 anim_spline_poll(Vec3f result) {
    Vec4f weights;
    s32 i;
    s32 hasEnded = FALSE;
    vec3f_copy(result, gVec3fZero);
    spline_get_weights(weights, gSplineKeyframeFraction, gSplineState);
    for (i = 0; i < 4; i++) {
        result[0] += (weights[i] * gSplineKeyframe[i][1]);
        result[1] += (weights[i] * gSplineKeyframe[i][2]);
        result[2] += (weights[i] * gSplineKeyframe[i][3]);
    }
    if ((gSplineKeyframeFraction += (gSplineKeyframe[0][0] / 1000.0f)) >= 1) {
        gSplineKeyframe++;
        gSplineKeyframeFraction--;
        switch (gSplineState) {
            case CURVE_END_2:                                  hasEnded = TRUE;            break;
            case CURVE_MIDDLE: if (gSplineKeyframe[2][0] == 0) gSplineState = CURVE_END_1; break;
            default:                                           gSplineState++;             break;
        }
    }
    return hasEnded;
}
