#include <ultra64.h>
#include <math.h>

#include "sm64.h"
#include "math_util.h"
#include "surface_collision.h"
#include "extended_bounds.h"
#include "trig_tables.inc.c"
#include "rendering_graph_node.h"
#include "boot/game_init.h"

#include "config.h"

// UNUSED static const Mat4 identityMtx = {
//     { 1, 0, 0, 0 },
//     { 0, 1, 0, 0 },
//     { 0, 0, 1, 0 },
//     { 0, 0, 0, 1 }
// };
// UNUSED static const Mat4 zeroMtx = {
//     { 0, 0, 0, 0 },
//     { 0, 0, 0, 0 },
//     { 0, 0, 0, 0 },
//     { 0, 0, 0, 0 }
// };

Vec3f gVec3fX    = {  1.0f,  0.0f,  0.0f };
Vec3f gVec3fY    = {  0.0f,  1.0f,  0.0f };
Vec3f gVec3fZ    = {  0.0f,  0.0f,  1.0f };
Vec3f gVec3fMX   = { -1.0f,  0.0f,  0.0f };
Vec3f gVec3fMY   = {  0.0f, -1.0f,  0.0f };
Vec3f gVec3fMZ   = {  0.0f,  0.0f, -1.0f };
Vec3f gVec3fZero = {  0.0f,  0.0f,  0.0f };
Vec3f gVec3fOne  = {  1.0f,  1.0f,  1.0f };
Vec3s gVec3sZero = {     0,     0,     0 };
Vec3i gVec3iZero = {     0,     0,     0 };
Vec3s gVec3sOne  = {     1,     1,     1 }; // unused

/**************************
 * Float functions (Kaze) *
 **************************/

f32 slow_logf(f32 x) {
    f32 p = 0.0f;
    f32 r = 0.0f, c = -1.0f;
    s32 i;
    if (x == 0.0f) return F32_MIN;
    while (x < 0.5f) {
        x *= CONST_EULER_F;
        ++p;
    }
    x -= 1.0f;
    for ((i = 1); (i < 8); (++i)) {
        c *= -x;
        r += (c / i);
    }
    return (r - p);
}

f32 slow_expf(f32 x) {
    f32 r = 1.0f, c = 1.0f;
    s32 i;
    x = -x;
    for ((i = 1); (i < 8); (++i)) {
        c *= (x / i);
        r += c;
    }
    return (1.0f / r);
}

f32 slow_powf(f32 base, f32 exponent) {
    if (base <= 0.0f) return 0.0f;
    return slow_expf(exponent * slow_logf(base));
}

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
inline s16 round_float_to_short( f32 num) { return roundf(num); } // (num + ((num >= 0.0f) ? 0.5f : -0.5f)); }
inline s32 round_float_to_int(   f32 num) { return roundf(num); } // (num + ((num >= 0.0f) ? 0.5f : -0.5f)); }
inline s16 round_double_to_short(f64 num) { return (num + ((num >= 0.0 ) ? 0.5  : -0.5 )); }
inline s32 round_double_to_int(  f64 num) { return (num + ((num >= 0.0 ) ? 0.5  : -0.5 )); }

/**
 * Rounds a floating-point component of a normal vector to an s8 by multiplying it by 127 or 128 and
 * rounding away from 0.
 */
s8 normalize_component(f32 comp) {
    if (comp > 0.0) {
        return ((comp * 127.0) + 0.5); // round up
    } else if (comp < 0.0) {
        return ((comp * 128.0) - 0.5); // round down
    } else {
        return 0;                      // don't round 0
    }
}

/****************************
 * Absolute value functions *
 ****************************/

inline s8  absc(s8  x) { return ((x < 0   ) ? -x : x); }
inline s16 abss(s16 x) { return ((x < 0   ) ? -x : x); }
inline s32 absi(s32 x) { return ((x < 0   ) ? -x : x); }
inline f32 absf(f32 x) { return ((x < 0.0f) ? -x : x); }
inline f64 absd(f64 x) { return ((x < 0.0 ) ? -x : x); }

/*******************
 * Clamp functions *
 *******************/

Bool32 clamp_pitch(Vec3f from, Vec3f to, Angle maxPitch, Angle minPitch) {
    Bool32 outOfRange = FALSE;
    Angle pitch, yaw;
    f32 dist;
    vec3f_get_dist_and_angle(from, to, &dist, &pitch, &yaw);
    if (pitch > maxPitch) { pitch = maxPitch; outOfRange = TRUE; }
    if (pitch < minPitch) { pitch = minPitch; outOfRange = TRUE; }
    vec3f_set_dist_and_angle(from, to,  dist,  pitch,  yaw);
    return outOfRange;
}

Bool32 clamp_s16(s16 *value, s16 minimum, s16 maximum) {
    if (*value <= minimum) {
        *value = minimum;
    } else if (*value >= maximum) {
        *value = maximum;
    } else {
        return FALSE;
    }
    return TRUE;
}

Bool32 clamp_f32(f32 *value, f32 minimum, f32 maximum) {
    if (*value <= minimum) {
        *value = minimum;
    } else if (*value >= maximum) {
        *value = maximum;
    } else {
        return FALSE;
    }
    return TRUE;
}

/**
 * Clamps a float within a set range about zero.
 */
UNUSED f32 clamp_f32_abs(f32 a, f32 b) {
    if (b < a) {
        a =  b;
    } else if (a < -b) {
        a = -b;
    }
    return a;
}

/**
 * Clamps a vector within a set range about zero.
 */
UNUSED void vec3f_clamp(Vec3f vec, f32 limit) {
    if (vec[0] > limit) {
        vec[0] =  limit;
    } else if (vec[0] < -limit) {
        vec[0] = -limit;
    }
    if (vec[1] > limit) {
        vec[1] =  limit;
    } else if (vec[1] < -limit) {
        vec[1] = -limit;
    }
    if (vec[2] > limit) {
        vec[2] =  limit;
    } else if (vec[2] < -limit) {
        vec[2] = -limit;
    }
}

inline f32 smooth(f32 x) {
    x = CLAMP(x, 0, 1);
    return (sqr(x) * (3.0f - (2.0f * x)));
}

inline f32 softClamp(f32 x, f32 a, f32 b) {
    return ((smooth((2.0f / 3.0f) * (x - a) / (b - a) + (1.0f / 6.0f)) * (b - a)) + a);
}

/**********
 * Angles *
 **********/

inline Angle abs_angle_diff(Angle angle1, Angle angle2) {
    Angle diff = (angle2 - angle1);
    if (diff == -0x8000) diff = -0x7FFF;
    return ABSI(diff);
}

Bool32 oscillate_toward(s32 *value, f32 *vel, s32 target, f32 velCloseToZero, f32 accel, f32 slowdown) {
    s32 startValue = *value;
    *value += (s32) *vel;
    if ((*value == target) || (((*value - target) * (startValue - target) < 0) && (*vel > -velCloseToZero) && (*vel < velCloseToZero))) {
        *value = target;
        *vel   = 0.0f;
        return TRUE;
    } else {
        if (*value >= target) accel = -accel;
        if ((*vel * accel) < 0.0f) accel *= slowdown;
        *vel += accel;
    }
    return FALSE;
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


static u32 sPrimarySeed   = 0x12345678;
static u32 sSecondarySeed = 0x58374895;

/**
 * Returns a random floating point number between 0 and 1 (inclusive)
 * TODO: figure out type of rng generator?
 */
f32 gd_rand_float(void) {
    u32 temp;
    u32 i;
    for ((i = 0); (i < 4); (i++)) {
        if (sPrimarySeed & 0x80000000) {
            sPrimarySeed = ((sPrimarySeed << 1) | 0x1);
        } else {
            sPrimarySeed <<= 1;
        }
    }
    sPrimarySeed += 4;
    /* Seed Switch */
    if ((sPrimarySeed ^= osGetTime()) & 0x1) {
        temp           = sPrimarySeed;
        sPrimarySeed   = sSecondarySeed;
        sSecondarySeed = temp;
    }
    return ((sPrimarySeed & 0xFFFF) / 65535.0f);
}

// Generate a pseudorandom float in the range [0, 1).
f32 random_float(void) {
    return ((f32)(random_u16()) / (double) 0x10000);
}

f32 random_f32_around_zero(f32 diameter) {
    return ((random_float() * diameter) - (diameter / 2));
}

s16 random_linear_offset(s16 base, s16 range) {
    return (base + (s16)(range * random_float()));
}

s16 random_mod_offset(s16 base, s16 step, s16 mod) {
    return (base + (step * (random_u16() % mod)));
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

/// Convert float vector 'src' to vector 'dst' by rounding the components to the nearest integer.
void vec3f_to_vec3c(Vec3c dst, Vec3f src) { vec3_copy_roundf(dst, src); }
void vec3f_to_vec3s(Vec3s dst, Vec3f src) { vec3_copy_roundf(dst, src); }
void vec3f_to_vec3i(Vec3i dst, Vec3f src) { vec3_copy_roundf(dst, src); }

/// Get the inverse magnitude of vector 'v'
f32 vec3f_invmag(Vec3f v) {
    register f32 mag = vec3_mag(v);
    return (1.0f / MAX(mag, NEAR_ZERO));
}

/// Scale vector 'v' so it has length 1
void vec3f_normalize(Vec3f v) { f32 invMag = vec3f_invmag(v); vec3_mul_val(v, invMag); }

Bool32 vec3f_are_coords_within_radius_of_point(Vec3f pos, f32 x, f32 y, f32 z, f32 dist) {
    Vec3f d = { x, y, z };
    vec3_sub(d, pos);
    return(vec3_sumsq(d) < sqr(dist));
}

Bool32 vec3f_are_points_within_radius(Vec3f pos1, Vec3f pos2, f32 dist) {
    Vec3f d;
    vec3_diff(d, pos2, pos1);
    return(vec3_sumsq(d) < sqr(dist));
}

/// Finds the horizontal distance between two vectors.
void vec2f_get_lateral_dist(Vec2f from, Vec2f to, f32 *lateralDist) {
    Vec2f d;
    vec2_diff(d, to, from);
    *lateralDist = vec2_mag(d);
}
void vec3f_get_lateral_dist(Vec3f from, Vec3f to, f32 *lateralDist) {
    MAKE_DXZ(from, to, f32)
    *lateralDist = sqrtf(sqr(dx) + sqr(dz));
}

/// Finds the distance between two vectors.
void vec3f_get_dist(Vec3f from, Vec3f to, f32 *dist) {
    Vec3f d;
    vec3_diff(d, to, from);
    *dist = vec3_mag(d);
}

/// Finds the distance between two vectors.
void vec3f_get_dist_squared(Vec3f from, Vec3f to, f32 *dist) {
    Vec3f d;
    vec3_diff(d, to, from);
    *dist = vec3_sumsq(d);
}

/// Finds the distance between two vectors.
void vec3f_get_dist_and_yaw(Vec3f from, Vec3f to, f32 *dist, Angle *yaw) {
    Vec3f d;
    vec3_diff(d, to, from);
    *dist = vec3_mag(d);
    *yaw  = atan2s(d[2], d[0]);
}

/// Finds the pitch between two vectors.
void vec3f_get_pitch(Vec3f from, Vec3f to, Angle *pitch) {
    Vec3f d;
    vec3_diff(d, to, from);
    *pitch = atan2s(sqrtf(sqr(d[0]) + sqr(d[2])), d[1]);
}

/// Finds the yaw between two vectors.
void vec3f_get_yaw(Vec3f from, Vec3f to, Angle *yaw) {
    MAKE_DXZ(from, to, f32)
    *yaw = atan2s(dz, dx);
}

/// Calculates the pitch and yaw between two vectors.
void vec3f_get_angle(Vec3f from, Vec3f to, Angle *pitch, Angle *yaw) {
    Vec3f d;
    vec3_diff(d, to, from);
    *pitch = atan2s(sqrtf(sqr(d[0]) + sqr(d[2])), d[1]);
    *yaw   = atan2s(d[2], d[0]);
}

/// Finds the horizontal distance and pitch between two vectors.
void vec3f_get_lateral_dist_and_pitch(Vec3f from, Vec3f to, f32 *lateralDist, Angle *pitch) {
    Vec3f d;
    vec3_diff(d, to, from);
    *lateralDist = sqrtf(sqr(d[0]) + sqr(d[2]));
    *pitch          = atan2s(*lateralDist, d[1]);
}


/// Finds the horizontal distance and yaw between two vectors.
void vec3f_get_lateral_dist_and_yaw(Vec3f from, Vec3f to, f32 *lateralDist, Angle *yaw) {
    MAKE_DXZ(from, to, f32)
    *lateralDist = sqrtf(sqr(dx) + sqr(dz));
    *yaw         = atan2s(dz, dx);
}

/// Finds the horizontal distance and angles between two vectors.
void vec3f_get_lateral_dist_and_angle(Vec3f from, Vec3f to, f32 *lateralDist, Angle *pitch, Angle *yaw) {
    Vec3f d;
    vec3_diff(d, to, from);
    *lateralDist = sqrtf(sqr(d[0]) + sqr(d[2]));
    *pitch       = atan2s(*lateralDist, d[1]);
    *yaw         = atan2s(d[2], d[0]);
}

void vec3f_get_dist_and_lateral_dist_and_angle(Vec3f from, Vec3f to, f32 *dist, f32 *lateralDist, Angle *pitch, Angle *yaw) {
    Vec3f d;
    vec3_diff(d, to, from);
    register f32 ld = (sqr(d[0]) + sqr(d[2]));
    *dist           = sqrtf(ld + sqr(d[1]));
    *lateralDist    = sqrtf(ld);
    *pitch          = atan2s(*lateralDist, d[1]);
    *yaw            = atan2s(d[2], d[0]);
}

/**
 * Take the vector starting at 'from' pointed at 'to' an retrieve the length
 * of that vector, as well as the yaw and pitch angles.
 * Basically it converts the direction to spherical coordinates.
 * Given two points, return the vector from one to the other represented
 * as Euler angles and a length
 */
void vec3s_get_dist_and_angle(Vec3s from, Vec3s to, s16 *dist, Angle *pitch, Angle *yaw) {
    Vec3s d;
    vec3_diff(d, to, from);
    register f32 ld = (sqr(d[0]) + sqr(d[2]));
    *dist           = sqrtf(ld + sqr(d[1]));
    *pitch          = atan2s(sqrtf(ld), d[1]);
    *yaw            = atan2s(d[2], d[0]);
}
void vec3f_get_dist_and_angle(Vec3f from, Vec3f to, f32 *dist, Angle *pitch, Angle *yaw) {
    Vec3f d;
    vec3_diff(d, to, from);
    register f32 ld = (sqr(d[0]) + sqr(d[2]));
    *dist           = sqrtf(ld + sqr(d[1]));
    *pitch          = atan2s(sqrtf(ld), d[1]);
    *yaw            = atan2s(d[2], d[0]);
}

/**
 * Construct the 'to' point which is distance 'dist' away from the 'from' position,
 * and has the angles pitch and yaw.
 */
void vec3s_set_dist_and_angle(Vec3s from, Vec3s to, s16 dist, Angle32 pitch, Angle32 yaw) {
    register f32 dc  = (dist * coss(pitch));
    to[0] = (from[0] + (  dc * sins(yaw  )));
    to[1] = (from[1] + (dist * sins(pitch)));
    to[2] = (from[2] + (  dc * coss(yaw  )));
}
void vec3f_set_dist_and_angle(Vec3f from, Vec3f to, f32 dist, Angle32 pitch, Angle32 yaw) {
    register f32 dc  = (dist * coss(pitch) );
    to[0] = (from[0] + (  dc * sins(yaw  )));
    to[1] = (from[1] + (dist * sins(pitch)));
    to[2] = (from[2] + (  dc * coss(yaw  )));
}

/**
 * Set 'dest' the normal vector of a triangle with vertices a, b and c.
 * It is similar to vec3_cross, but it calculates the vectors (c-b) and (b-a)
 * at the same time.
 */
void find_vector_perpendicular_to_plane(Vec3f dest, Vec3f a, Vec3f b, Vec3f c) {
    dest[0] = ((b[1] - a[1]) * (c[2] - b[2]) - (c[1] - b[1]) * (b[2] - a[2]));
    dest[1] = ((b[2] - a[2]) * (c[0] - b[0]) - (c[2] - b[2]) * (b[0] - a[0]));
    dest[2] = ((b[0] - a[0]) * (c[1] - b[1]) - (c[0] - b[0]) * (b[1] - a[1]));
}

// Thank you rocket robot
void vec3f_rotate(Mat4 mat, Vec3f in, Vec3f out) {
    out[0] = ((mat[0][0] * in[0]) + (mat[1][0] * in[1]) + (mat[2][0] * in[2]));
    out[1] = ((mat[0][1] * in[0]) + (mat[1][1] * in[1]) + (mat[2][1] * in[2]));
    out[2] = ((mat[0][2] * in[0]) + (mat[1][2] * in[1]) + (mat[2][2] * in[2]));
}

UNUSED void vec3f_transform(Mat4 mat, Vec3f in, f32 w, Vec3f out) {
    s32 i, j;
    for ((i = 0); (i < 3); (i++)) {
        out[i] = (mat[3][i] * w);
        for ((j = 0); (j < 3); (j++)) out[i] += (mat[j][i] * in[j]);
    }
}

UNUSED void vec3f_transform_vtx(Mat4 mat, Vec3f in, f32 w, Vtx *out) {
    Vec3f temp;
    vec3f_transform(mat, in, w, temp);
    vec3_copy(out->v.ob, temp);
}

/**
 * Rotates the input vertices according to the give pitch and yaw. This
 * is needed for billboarding of particles.
 */
void rotate_triangle_vertices(Vec3s vertex1, Vec3s vertex2, Vec3s vertex3, Angle pitch, Angle yaw) {
    f32 cosPitch = coss(pitch);
    f32 sinPitch = sins(pitch);
    f32 cosMYaw  = coss(-yaw);
    f32 sinMYaw  = sins(-yaw);
    f32 spsy = (sinPitch * sinMYaw );
    f32 spcy = (sinPitch * cosMYaw );
    f32 sycp = (sinMYaw  * cosPitch);
    f32 cpcm = (cosPitch * cosMYaw );
    Vec3f v1, v2, v3;
    vec3_copy(v1, vertex1);
    vertex1[0] = ((v1[0] * cosMYaw ) + (v1[1] * spsy) - (v1[2] * sycp));
    vertex1[1] = ((v1[1] * cosPitch) + (v1[2] * sinPitch));
    vertex1[2] = ((v1[0] * sinMYaw ) - (v1[1] * spcy) + (v1[2] * cpcm));
    vec3_copy(v2, vertex2);
    vertex2[0] = ((v2[0] * cosMYaw ) + (v2[1] * spsy) - (v2[2] * sycp));
    vertex2[1] = ((v2[1] * cosPitch) + (v2[2] * sinPitch));
    vertex2[2] = ((v2[0] * sinMYaw ) - (v2[1] * spcy) + (v2[2] * cpcm));
    vec3_copy(v3, vertex3);
    vertex3[0] = ((v3[0] * cosMYaw ) + (v3[1] * spsy) - (v3[2] * sycp));
    vertex3[1] = ((v3[1] * cosPitch) + (v3[2] * sinPitch));
    vertex3[2] = ((v3[0] * sinMYaw ) - (v3[1] * spcy) + (v3[2] * cpcm));
}

/**
 * Calculates the distance between two points and sets a vector to a point
 * scaled along a line between them. Typically, somewhere in the middle.
 */
void scale_along_line(Vec3f dst, Vec3f from, Vec3f to, f32 scale) {
    dst[0] = (((to[0] - from[0]) * scale) + from[0]);
    dst[1] = (((to[1] - from[1]) * scale) + from[1]);
    dst[2] = (((to[2] - from[2]) * scale) + from[2]);
}

/*********************
 * Matrix Operations *
 *********************/

/**
 * [0][0]   x scale
 * [0][1]   y shear
 * [0][2]   z x shear?
 * [0][3]   x divisor?
 * [1][0]   x shear
 * [1][1]   y scale
 * [1][2]   z z shear?
 * [1][3]   y divisor?
 * [2][0]   z x shear?
 * [2][1]   z y shear?
 * [2][2]   z scale
 * [2][3]   z divisor?
 * [3][0]   x translation
 * [3][1]   y translation
 * [3][2]   z translation
 * [3][3]   translation scale divisor
 **/

/// Copy matrix 'src' to 'dest'
void mtxf_copy(Mat4 dest, const Mat4 src) {
    register s32 i;
    register u32 *d = (u32 *) dest;
    register u32 *s = (u32 *) src;
    for ((i = 0); (i < 16); (i++)) *d++ = *s++;
}

/// Shifts a matrix up by one row, putting the top row on bottom.
void mtxf_shift_up(Mat4 mtx) {
    s32 i, j;
    Vec3f temp;
    for ((i = 0); (i < 3); (i++)) temp[i] = mtx[0][i + 1];
    for ((i = 1); (i < 4); (i++)) for ((j = 1); (j < 4); (j++)) mtx[i - 1][j - 1] = mtx[i][j];
    MTXF_END(mtx);
    for ((i = 0); (i < 3); (i++)) mtx[3][i] = temp[i];
}

/**
 * Set mtx to the identity matrix
 */
void mtxf_identity(Mat4 mtx) {
    vec3_copy(mtx[0], gVec3fX);
    vec3_copy(mtx[1], gVec3fY);
    vec3_copy(mtx[2], gVec3fZ);
    vec3_zero(mtx[3]);
    MTXF_END(mtx);
    // mtxf_copy(mtx, identityMtx);
}

/**
 * Set dest to a translation matrix of vector b
 */
void mtxf_translate(Mat4 dest, Vec3f b) {
    mtxf_identity(dest);
    vec3_copy(dest[3], b);
}

/**
 * Set mtx to a look-at matrix for the camera. The resulting transformation
 * transforms the world as if there exists a camera at position 'from' pointed
 * at the position 'to'. The up-vector is assumed to be (0, 1, 0), but the 'roll'
 * angle allows a bank rotation of the camera.
 */
void mtxf_lookat(Mat4 mtx, Vec3f from, Vec3f to, Angle32 roll) {
    Vec3f colX, colY, colZ;
    register f32 dx = (to[0] - from[0]);
    register f32 dz = (to[2] - from[2]);
    register f32 invLength = sqrtf(sqr(dx) + sqr(dz));
    invLength = -(1.0f / MAX(invLength, NEAR_ZERO));
    dx *= invLength;
    dz *= invLength;
    f32 sr  = sins(roll);
    colY[1] = coss(roll);
    colY[0] = ( sr * dz);
    colY[2] = (-sr * dx);
    vec3_diff(colZ, to, from);
    vec3_normalize_negative(colZ);
    vec3_cross(colX, colY, colZ);
    vec3_normalize(colX);
    vec3_cross(colY, colZ, colX);
    vec3_normalize(colY);
    mtx[0][0] = colX[0];
    mtx[1][0] = colX[1];
    mtx[2][0] = colX[2];
    mtx[0][1] = colY[0];
    mtx[1][1] = colY[1];
    mtx[2][1] = colY[2];
    mtx[0][2] = colZ[0];
    mtx[1][2] = colZ[1];
    mtx[2][2] = colZ[2];
    mtx[3][0] = -vec3_dot(from, colX);
    mtx[3][1] = -vec3_dot(from, colY);
    mtx[3][2] = -vec3_dot(from, colZ);
    MTXF_END(mtx);
}

/**
 * Creates a lookat matrix, but specifically from the perspective of the origin.
 *
 * Matrix has form-  | -(cz+sxy)/h sh  (cx-syz)/h 0 |
 *                   |  (sz-cxy)/h ch -(sx+cyz)/h 0 |
 *                   |     -x      -y     -z      0 |
 *                   |      0       0      0      1 |
 */
void mtxf_origin_lookat(Mat4 mtx, Vec3f vec, f32 roll) {
    Vec3f unit;
    vec3_copy(unit, vec);
    vec3_normalize(unit);
    f32 hMag = sqrtf(sqr(unit[0]) + sqr(unit[2]));
    if (hMag != 0.0f) {
        roll *= RAD_PER_DEG; // convert roll from degrees to radians
        f32 s = sind(roll);
        f32 c = cosd(roll);
        f32 su1 = (s * unit[1]);
        f32 cu1 = (s * unit[1]);
        f32 invertedHMag = (1.0f / hMag);
        mtx[0][0] = (((-unit[2] * c) - (su1 * unit[0])) * invertedHMag);
        mtx[1][0] = ((( unit[2] * s) - (cu1 * unit[0])) * invertedHMag);
        mtx[2][0] =                          -unit[0];

        mtx[0][1] = (s * hMag);
        mtx[1][1] = (c * hMag);
        mtx[2][1] = -unit[1];

        mtx[0][2] = ((( c * unit[0]) - (su1 * unit[2])) * invertedHMag);
        mtx[1][2] = (((-s * unit[0]) - (cu1 * unit[2])) * invertedHMag);
        mtx[2][2] =                          -unit[2];
    } else {
        vec3_copy(mtx[0], gVec3fZ);
        vec3_copy(mtx[1], gVec3fX);
        vec3_copy(mtx[2], gVec3fY);
    }
    vec3_zero(mtx[3]);
    MTXF_END(mtx);
}

/**
 * Build a matrix that rotates around the z axis, then the x axis, then the y
 * axis, and then translates.
 */
void mtxf_rotate_zxy_and_translate(Mat4 dest, Vec3f translate, Vec3a rotate) {
    register f32 sx   = sins(rotate[0]);
    register f32 cx   = coss(rotate[0]);
    register f32 sy   = sins(rotate[1]);
    register f32 cy   = coss(rotate[1]);
    register f32 sz   = sins(rotate[2]);
    register f32 cz   = coss(rotate[2]);
    register f32 cycz = (cy * cz);
    register f32 cysz = (cy * sz);
    register f32 sycz = (sy * cz);
    register f32 sysz = (sy * sz);
    dest[0][0] = ((sx * sysz) + cycz);
    dest[1][0] = ((sx * sycz) - cysz);
    dest[2][0] = ( cx * sy          );
    dest[0][1] = ( cx * sz          );
    dest[1][1] = ( cx * cz          );
    dest[2][1] = -sx;
    dest[0][2] = ((sx * cysz) - sycz);
    dest[1][2] = ((sx * cycz) + sysz);
    dest[2][2] = ( cx * cy           );
    vec3_copy(dest[3], translate);
    MTXF_END(dest);
}

void mtxf_rotate_xyz(Mat4 dest, Vec3a rotate) {
    register f32 sx   = sins(rotate[0]);
    register f32 cx   = coss(rotate[0]);
    register f32 sy   = sins(rotate[1]);
    register f32 cy   = coss(rotate[1]);
    register f32 sz   = sins(rotate[2]);
    register f32 cz   = coss(rotate[2]);
    register f32 cxsz = (cx * sz);
    register f32 cxcz = (cx * cz);
    register f32 sxsz = (sx * sz);
    register f32 sxcz = (sx * cz);
    dest[0][0] = (   cy * cz        );
    dest[0][1] = (   cy * sz        );
    dest[0][2] = -sy;
    dest[1][0] = ((sxcz * sy) - cxsz);
    dest[1][1] = ((sxsz * sy) + cxcz);
    dest[1][2] = (   sx * cy        );
    dest[2][0] = ((cxcz * sy) + sxsz);
    dest[2][1] = ((cxsz * sy) - sxcz);
    dest[2][2] = (   cx * cy        );
    dest[0][3] = 0;
    dest[1][3] = 0;
    dest[2][3] = 0;
}

/**
 * Build a matrix that rotates around the x axis, then the y axis, then the z
 * axis, and then translates.
 */
void mtxf_rotate_xyz_and_translate(Mat4 dest, Vec3f translate, Vec3a rotate) {
    register f32 sx   = sins(rotate[0]);
    register f32 cx   = coss(rotate[0]);
    register f32 sy   = sins(rotate[1]);
    register f32 cy   = coss(rotate[1]);
    register f32 sz   = sins(rotate[2]);
    register f32 cz   = coss(rotate[2]);
    register f32 cxsz = (cx * sz);
    register f32 cxcz = (cx * cz);
    register f32 sxsz = (sx * sz);
    register f32 sxcz = (sx * cz);
    dest[0][0] = (   cy * cz        );
    dest[0][1] = (   cy * sz        );
    dest[0][2] = -sy;
    dest[1][0] = ((sxcz * sy) - cxsz);
    dest[1][1] = ((sxsz * sy) + cxcz);
    dest[1][2] = (   sx * cy        );
    dest[2][0] = ((cxcz * sy) + sxsz);
    dest[2][1] = ((cxsz * sy) - sxcz);
    dest[2][2] = (   cx * cy        );
    vec3_copy(dest[3], translate);
    MTXF_END(dest);
}

/**
 * Set 'dest' to a transformation matrix that turns an object to face parallel to the camera.
 * 'mtx' is the look-at matrix from the camera
 * 'position' is the position of the object in the world
 * 'roll' rotates the object while still facing the camera.
 */
void mtxf_billboard(Mat4 dest, Mat4 mtx, Vec3f position, Angle32 roll, s32 zOffset) {
    if (roll == 0x0) {
        dest[0][0] = 1;
        dest[0][1] = 0;
    } else {
        dest[0][0] = coss(roll);
        dest[0][1] = sins(roll);
    }
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
    if ((position[0] == 0) && (position[1] == 0) && (position[2] == 0)) {
        vec3_copy(dest[3], mtx[3]);
    } else {
        dest[3][0] = ((mtx[0][0] * position[0]) + (mtx[1][0] * position[1]) + (mtx[2][0] * position[2]) + mtx[3][0]);
        dest[3][1] = ((mtx[0][1] * position[0]) + (mtx[1][1] * position[1]) + (mtx[2][1] * position[2]) + mtx[3][1]);
        dest[3][2] = ((mtx[0][2] * position[0]) + (mtx[1][2] * position[1]) + (mtx[2][2] * position[2]) + mtx[3][2]);
    }
    dest[3][3] = (((zOffset == 0) || (dest[3][2] == 0)) ? 1 : ((dest[3][2] - zOffset) / dest[3][2]));
}

/**
 * Set 'dest' to a transformation matrix that aligns an object with the terrain
 * based on the normal. Used for enemies.
 * 'upDir' is the terrain normal
 * 'yaw' is the angle which it should face
 * 'pos' is the object's position in the world
 */
void mtxf_align_terrain_normal(Mat4 dest, Vec3f upDir, Vec3f pos, Angle32 yaw) {
    Vec3f lateralDir, leftDir, forwardDir;
    vec3_set(lateralDir, sins(yaw), 0x0, coss(yaw));
    vec3_normalize(upDir);
    vec3_cross(leftDir, upDir, lateralDir);
    vec3_normalize(leftDir);
    vec3_cross(forwardDir, leftDir, upDir);
    vec3_normalize(forwardDir);
    vec3_copy(dest[0], leftDir);
    vec3_copy(dest[1], upDir);
    vec3_copy(dest[2], forwardDir);
    vec3_copy(dest[3], pos);
    MTXF_END(dest);
}

/**
 * Set 'mtx' to a transformation matrix that aligns an object with the terrain
 * based on 3 height samples in an equilateral triangle around the object.
 * Used for Mario when crawling or sliding.
 * 'yaw' is the angle which it should face
 * 'pos' is the object's position in the world
 * 'radius' is the distance from each triangle vertex to the center
 */
void mtxf_align_terrain_triangle(Mat4 mtx, Vec3f pos, Angle32 yaw, f32 radius) {
    struct Surface *floor;
    Vec3f point0, point1, point2;
    Vec3f forward;
    Vec3f xColumn, yColumn, zColumn;
    f32 minY  = (-radius * 3);
    point0[0] = (pos[0] + (radius * sins(yaw + DEG( 60))));
    point0[2] = (pos[2] + (radius * coss(yaw + DEG( 60))));
    point1[0] = (pos[0] + (radius * sins(yaw + DEG(180))));
    point1[2] = (pos[2] + (radius * coss(yaw + DEG(180))));
    point2[0] = (pos[0] + (radius * sins(yaw + DEG(-60))));
    point2[2] = (pos[2] + (radius * coss(yaw + DEG(-60))));
    point0[1] =           find_floor(point0[0], (pos[1] + 150.0f), point0[2], &floor);
    point1[1] =           find_floor(point1[0], (pos[1] + 150.0f), point1[2], &floor);
    point2[1] =           find_floor(point2[0], (pos[1] + 150.0f), point2[2], &floor);
    if ((point0[1] - pos[1]) < minY) point0[1] = pos[1];
    if ((point1[1] - pos[1]) < minY) point1[1] = pos[1];
    if ((point2[1] - pos[1]) < minY) point2[1] = pos[1];
    f32 avgY = average_3(point0[1], point1[1], point2[1]);
    vec3_set(forward, sins(yaw), 0x0, coss(yaw));
    find_vector_perpendicular_to_plane(yColumn, point0, point1, point2);
    vec3_normalize(yColumn);
    vec3_cross(xColumn, yColumn, forward);
    vec3_normalize(xColumn);
    vec3_cross(zColumn, xColumn, yColumn);
    vec3_normalize(zColumn);
    vec3_copy(mtx[0], xColumn);
    vec3_copy(mtx[1], yColumn);
    vec3_copy(mtx[2], zColumn);
    mtx[3][0] = pos[0];
    mtx[3][1] = MAX(pos[1], avgY);
    mtx[3][2] = pos[2];
    MTXF_END(mtx);
}

/**
 * Creates a transform matrix on a variable passed in from given normals
 * and the object's position.
 */
void mtxf_transform_from_normals(Mat4 dest, Vec3f pos, f32 xNorm, f32 yNorm, f32 zNorm) {
    Vec3n normal;
    vec3_set(normal, xNorm, yNorm, zNorm);
    mtxf_align_terrain_normal(dest, normal, pos, 0);
}

/**
 * Set matrix 'dest' to 'mtx' scaled by vector s
 */
void mtxf_scale_vec3f(Mat4 dest, Mat4 mtx, Vec3f s) {
    register s32 i;
    for ((i = 0); (i < 4); (i++)) {
        dest[0][i] = (mtx[0][i] * s[0]);
        dest[1][i] = (mtx[1][i] * s[1]);
        dest[2][i] = (mtx[2][i] * s[2]);
        dest[3][i] =  mtx[3][i];
    }
}

/**
 * Scales a mat4f in each dimension by a vector.
 */
void mtxf_scale_self_vec3f(Mat4 mtx, Vec3f vec) {
    vec3_mul_val(mtx[0], vec[0]);
    vec3_mul_val(mtx[1], vec[1]);
    vec3_mul_val(mtx[2], vec[2]);
}

/**
 * Multiply a vector with a transformation matrix, which applies the transformation
 * to the point. Note that the bottom row is assumed to be [0, 0, 0, 1], which is
 * true for transformation matrices if the translation has a w component of 1.
 */
void linear_mtxf_self_mul_vec3f_self(Mat4 mtx, Vec3f b) {
    Vec3f tmp;
    linear_mtxf_mul_vec3f(mtx, tmp, b);
    vec3_copy(b, tmp);
}

/**
 * Multiply a vector with a transformation matrix, which applies the transformation
 * to the point. Note that the bottom row is assumed to be [0, 0, 0, 1], which is
 * true for transformation matrices if the translation has a w component of 1.
 */
/// Transforms a vec3f, rotating with the main 3x3 portion of the mat4f and translating with the 4th column.
void linear_mtxf_mul_vec3f_self_and_translate(Mat4 mtx, Vec3f b) {
    Vec3f tmp;
    linear_mtxf_mul_vec3f_and_translate(mtx, tmp, b);
    vec3_copy(b, tmp);
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
    linear_mtxf_mul_vec3f(              b, temp[0], a[0]);
    linear_mtxf_mul_vec3f(              b, temp[1], a[1]);
    linear_mtxf_mul_vec3f(              b, temp[2], a[2]);
    linear_mtxf_mul_vec3f_and_translate(b, temp[3], a[3]);
    MTXF_END(temp);
    mtxf_copy(dest, temp);
}

/// Multiplies two Mat4 matrices and puts it in dst.
void gd_mult_mat4f(Mat4 dst, const Mat4 mA, const Mat4 mB) {
    Mat4 res;
    MAT4_MULTIPLY(res, mA, mB);
    mtxf_copy(dst, res);
}

/**
 * Convert float matrix 'src' to fixed point matrix 'dest'.
 * The float matrix may not contain entries larger than 65536 or the console
 * crashes. The fixed point matrix has entries with a 16-bit integer part, so
 * the floating point numbers are multiplied by 2^16 before being cast to a s32
 * integer. If this doesn't fit, the N64 and iQue consoles will throw an
 * exception. On Wii and Wii U Virtual Console the value will simply be clamped
 * and no crashes occur.

 * Modified into a hybrid of the original function and the worldscale altered function.
 * Will check if the worldscale is below what's considered safe in vanilla bounds and
 * just run the faster vanilla function, otherwise it'll run the slower, but safer scale
 * function, for extended boundaries.
 */
void mtxf_to_mtx_scale(Mtx *dest, Mat4 src) {
#if EXTENDED_BOUNDS_MODE > 1
    Mat4 temp;
    register s32 i;
    register f32 invScale = (1.0f / gWorldScale);
    for((i = 0); (i < 4); (i++)) {
        vec3_prod_val(temp[i], src[i], invScale);
        temp[i][3] = src[i][3];
    }
    guMtxF2L(temp, dest);
#else
    guMtxF2L(src, dest);
#endif
}

void mtxf_to_mtx_constant(register s16 *dest, register f32 *src) {
    s32 asFixedPoint;
    s32 i;
    for (i = 0; i < 16; i++) {
        asFixedPoint = (src[i] * (1 << 16));
        dest[i     ] = (asFixedPoint >> 16);
        dest[i + 16] = (asFixedPoint & 0xFFFF);
    }
}

void mtxf_to_mtx(void *dest, void *src) {
    if (gWorldScale > 2.0f) {
        mtxf_to_mtx_scale(dest, src);
    } else {
        mtxf_to_mtx_constant(dest, src);
    }
}

/**
 * Set 'mtx' to a transformation matrix that rotates around the z axis.
 */
void mtxf_rotate_xy(Mtx *mtx, Angle32 angle, Bool32 doScale) {
    Mat4 temp;
    mtxf_identity(temp);
    temp[0][0] = coss(angle);
    temp[0][1] = sins(angle);
    temp[1][0] = -temp[0][1];
    temp[1][1] =  temp[0][0];
    if (doScale) {
        mtxf_to_mtx(mtx, temp);
    } else {
        guMtxF2L(temp, mtx);
    }
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
    dest[0] = (vec3_dot(objMtx[3], camMtx[0]) - vec3_dot(camMtx[3], camMtx[0]));
    dest[1] = (vec3_dot(objMtx[3], camMtx[1]) - vec3_dot(camMtx[3], camMtx[1]));
    dest[2] = (vec3_dot(objMtx[3], camMtx[2]) - vec3_dot(camMtx[3], camMtx[2]));
}

void create_transformation_from_matrices(Mat4 dst, Mat4 a1, Mat4 a2) {
    dst[0][0] =  vec3_dot(a1[0], a2[0]);
    dst[0][1] =  vec3_dot(a1[0], a2[1]);
    dst[0][2] =  vec3_dot(a1[0], a2[2]);
    dst[1][0] =  vec3_dot(a1[1], a2[0]);
    dst[1][1] =  vec3_dot(a1[1], a2[1]);
    dst[1][2] =  vec3_dot(a1[1], a2[2]);
    dst[2][0] =  vec3_dot(a1[2], a2[0]);
    dst[2][1] =  vec3_dot(a1[2], a2[1]);
    dst[2][2] =  vec3_dot(a1[2], a2[2]);
    dst[3][0] = (vec3_dot(a1[3], a2[0]) - vec3_dot(a2[3], a2[0]));
    dst[3][1] = (vec3_dot(a1[3], a2[1]) - vec3_dot(a2[3], a2[1]));
    dst[3][2] = (vec3_dot(a1[3], a2[2]) - vec3_dot(a2[3], a2[2]));
    MTXF_END(dst);
}

// Rotation/translation matrix inverse
void mtxf_inverse_rotate_translate(Mat4 in, Mat4 out) {
    Mat4 invRot;
    Vec3f negTranslate;
    Mat4 invTranslate;
    invRot[0][0]    = in[0][0];
    invRot[0][1]    = in[1][0];
    invRot[0][2]    = in[2][0];
    invRot[1][0]    = in[0][1];
    invRot[1][1]    = in[1][1];
    invRot[1][2]    = in[2][1];
    invRot[2][0]    = in[0][2];
    invRot[2][1]    = in[1][2];
    invRot[2][2]    = in[2][2];
    vec3_zero(invRot[3]);
    MTXF_END(invRot);
    negTranslate[0] = -in[3][0];
    negTranslate[1] = -in[3][1];
    negTranslate[2] = -in[3][2];
    mtxf_translate(invTranslate, negTranslate);
    mtxf_mul(out, invTranslate, invRot);
}

/**
 * Takes the individual values of a 2 by 2 matrix and
 * returns the determinant.
 */
f32 det_2x2(f32 a, f32 b, f32 c, f32 d) {
    return ((a * d) - (b * c));
}

/**
 * Takes the individual values of a 3 by 3 matrix and
 * returns the determinant.
 */
f32 det_3x3(f32 r0c0, f32 r0c1, f32 r0c2,
            f32 r1c0, f32 r1c1, f32 r1c2,
            f32 r2c0, f32 r2c1, f32 r2c2) {
    return ((r0c0 * det_2x2(r1c1, r1c2, r2c1, r2c2))
          - (r1c0 * det_2x2(r0c1, r0c2, r2c1, r2c2))
          + (r2c0 * det_2x2(r0c1, r0c2, r1c1, r1c2)));
}

/**
 * Takes a matrix from src and converts it into its adjunct in dst.
 */
void mtxf_adjunct(Mat4 *dst, Mat4 *src) {
    struct InvMat4 inv;
    inv.r3.c3 = (*src)[0][0];
    inv.r2.c3 = (*src)[0][1];
    inv.r1.c3 = (*src)[0][2];
    inv.r0.c3 = (*src)[0][3];
    inv.r3.c2 = (*src)[1][0];
    inv.r2.c2 = (*src)[1][1];
    inv.r1.c2 = (*src)[1][2];
    inv.r0.c2 = (*src)[1][3];
    inv.r3.c1 = (*src)[2][0];
    inv.r2.c1 = (*src)[2][1];
    inv.r1.c1 = (*src)[2][2];
    inv.r0.c1 = (*src)[2][3];
    inv.r3.c0 = (*src)[3][0];
    inv.r2.c0 = (*src)[3][1];
    inv.r1.c0 = (*src)[3][2];
    inv.r0.c0 = (*src)[3][3];
    (*dst)[0][0] =  det_3x3(inv.r2.c2, inv.r2.c1, inv.r2.c0, inv.r1.c2, inv.r1.c1, inv.r1.c0, inv.r0.c2, inv.r0.c1, inv.r0.c0);
    (*dst)[1][0] = -det_3x3(inv.r3.c2, inv.r3.c1, inv.r3.c0, inv.r1.c2, inv.r1.c1, inv.r1.c0, inv.r0.c2, inv.r0.c1, inv.r0.c0);
    (*dst)[2][0] =  det_3x3(inv.r3.c2, inv.r3.c1, inv.r3.c0, inv.r2.c2, inv.r2.c1, inv.r2.c0, inv.r0.c2, inv.r0.c1, inv.r0.c0);
    (*dst)[3][0] = -det_3x3(inv.r3.c2, inv.r3.c1, inv.r3.c0, inv.r2.c2, inv.r2.c1, inv.r2.c0, inv.r1.c2, inv.r1.c1, inv.r1.c0);
    (*dst)[0][1] = -det_3x3(inv.r2.c3, inv.r2.c1, inv.r2.c0, inv.r1.c3, inv.r1.c1, inv.r1.c0, inv.r0.c3, inv.r0.c1, inv.r0.c0);
    (*dst)[1][1] =  det_3x3(inv.r3.c3, inv.r3.c1, inv.r3.c0, inv.r1.c3, inv.r1.c1, inv.r1.c0, inv.r0.c3, inv.r0.c1, inv.r0.c0);
    (*dst)[2][1] = -det_3x3(inv.r3.c3, inv.r3.c1, inv.r3.c0, inv.r2.c3, inv.r2.c1, inv.r2.c0, inv.r0.c3, inv.r0.c1, inv.r0.c0);
    (*dst)[3][1] =  det_3x3(inv.r3.c3, inv.r3.c1, inv.r3.c0, inv.r2.c3, inv.r2.c1, inv.r2.c0, inv.r1.c3, inv.r1.c1, inv.r1.c0);
    (*dst)[0][2] =  det_3x3(inv.r2.c3, inv.r2.c2, inv.r2.c0, inv.r1.c3, inv.r1.c2, inv.r1.c0, inv.r0.c3, inv.r0.c2, inv.r0.c0);
    (*dst)[1][2] = -det_3x3(inv.r3.c3, inv.r3.c2, inv.r3.c0, inv.r1.c3, inv.r1.c2, inv.r1.c0, inv.r0.c3, inv.r0.c2, inv.r0.c0);
    (*dst)[2][2] =  det_3x3(inv.r3.c3, inv.r3.c2, inv.r3.c0, inv.r2.c3, inv.r2.c2, inv.r2.c0, inv.r0.c3, inv.r0.c2, inv.r0.c0);
    (*dst)[3][2] = -det_3x3(inv.r3.c3, inv.r3.c2, inv.r3.c0, inv.r2.c3, inv.r2.c2, inv.r2.c0, inv.r1.c3, inv.r1.c2, inv.r1.c0);
    (*dst)[0][3] = -det_3x3(inv.r2.c3, inv.r2.c2, inv.r2.c1, inv.r1.c3, inv.r1.c2, inv.r1.c1, inv.r0.c3, inv.r0.c2, inv.r0.c1);
    (*dst)[1][3] =  det_3x3(inv.r3.c3, inv.r3.c2, inv.r3.c1, inv.r1.c3, inv.r1.c2, inv.r1.c1, inv.r0.c3, inv.r0.c2, inv.r0.c1);
    (*dst)[2][3] = -det_3x3(inv.r3.c3, inv.r3.c2, inv.r3.c1, inv.r2.c3, inv.r2.c2, inv.r2.c1, inv.r0.c3, inv.r0.c2, inv.r0.c1);
    (*dst)[3][3] =  det_3x3(inv.r3.c3, inv.r3.c2, inv.r3.c1, inv.r2.c3, inv.r2.c2, inv.r2.c1, inv.r1.c3, inv.r1.c2, inv.r1.c1);
}

/**
 * Returns the determinant of a mat4f matrix.
 */
f32 mtxf_det(Mat4 *mtx) {
    f32 det;
    struct InvMat4 inv;
    inv.r3.c3 = (*mtx)[0][0];
    inv.r2.c3 = (*mtx)[0][1];
    inv.r1.c3 = (*mtx)[0][2];
    inv.r0.c3 = (*mtx)[0][3];
    inv.r3.c2 = (*mtx)[1][0];
    inv.r2.c2 = (*mtx)[1][1];
    inv.r1.c2 = (*mtx)[1][2];
    inv.r0.c2 = (*mtx)[1][3];
    inv.r3.c1 = (*mtx)[2][0];
    inv.r2.c1 = (*mtx)[2][1];
    inv.r1.c1 = (*mtx)[2][2];
    inv.r0.c1 = (*mtx)[2][3];
    inv.r3.c0 = (*mtx)[3][0];
    inv.r2.c0 = (*mtx)[3][1];
    inv.r1.c0 = (*mtx)[3][2];
    inv.r0.c0 = (*mtx)[3][3];
    det = ((inv.r3.c3 * det_3x3(inv.r2.c2, inv.r2.c1, inv.r2.c0,
                                inv.r1.c2, inv.r1.c1, inv.r1.c0,
                                inv.r0.c2, inv.r0.c1, inv.r0.c0))
         - (inv.r2.c3 * det_3x3(inv.r3.c2, inv.r3.c1, inv.r3.c0,
                                inv.r1.c2, inv.r1.c1, inv.r1.c0,
                                inv.r0.c2, inv.r0.c1, inv.r0.c0)))
         + (inv.r1.c3 * det_3x3(inv.r3.c2, inv.r3.c1, inv.r3.c0,
                                inv.r2.c2, inv.r2.c1, inv.r2.c0,
                                inv.r0.c2, inv.r0.c1, inv.r0.c0))
         - (inv.r0.c3 * det_3x3(inv.r3.c2, inv.r3.c1, inv.r3.c0,
                                inv.r2.c2, inv.r2.c1, inv.r2.c0,
                                inv.r1.c2, inv.r1.c1, inv.r1.c0));
    return det;
}

/**
 * Inverts a matrix from src and stores it into dst.
 * Reaches a fatal_print if the determinant is 0.
 */
void mtxf_inverse(Mat4 *dst, Mat4 *src) {
    s32 i, j;
    mtxf_adjunct(dst, src);
    f32 determinant = mtxf_det(dst);
    determinant = MAX(determinant, NEAR_ZERO); // If 0, non-singular matrix, no inverse!
    for ((i = 0); (i < 4); (i++)) for ((j = 0); (j < 4); (j++)) (*dst)[i][j] /= determinant;
}

/**
 * Creates a rotation matrix to multiply the primary matrix by.
 * s/c are sin(angle)/cos(angle). That angular rotation is about vector
 * 'vec'.
 *
 * Matrix has form-
 *
 * | (1-c)z^2+c (1-c)zy-sx (1-c)xz-sy 0 |
 * | (1-c)zy-sx (1-c)y^2+c (1-c)xy-sz 0 |
 * | (1-c)xz-sy (1-c)xy-sz (1-c)x^2+c 0 |
 * |      0          0          0     1 |
 */
void mtxf_create_rot(Mat4 mtx, Vec3f vec, f32 s, f32 c) {
    Vec3f rev, srev;
    vec3_copy_inverse(rev, vec);
    vec3_copy(srev, rev);
    vec3_mul_val(srev, s);
    register f32 oneMinusCos = (1.0f - c);
    register f32 omc10 = (oneMinusCos * rev[1] * rev[0]);
    register f32 omc20 = (oneMinusCos * rev[2] * rev[0]);
    register f32 omc21 = (oneMinusCos * rev[2] * rev[1]);
    mtx[0][0] = ((oneMinusCos * sqr(rev[2])) + c);
    mtx[0][1] = (omc21 + srev[0]);
    mtx[0][2] = (omc20 - srev[1]);
    mtx[1][0] = (omc21 - srev[0]);
    mtx[1][1] = ((oneMinusCos * sqr(rev[1])) + c);
    mtx[1][2] = (omc10 + srev[2]);
    mtx[2][0] = (omc20 + srev[1]);
    mtx[2][1] = (omc10 - srev[2]);
    mtx[2][2] = ((oneMinusCos * sqr(rev[0])) + c);
    vec3_zero(mtx[3]);
    MTXF_END(mtx);
}

/// Creates a rotation matrix about vector 'vec' with ang in degrees.
void mtxf_create_rot_angular(Mat4 mtx, Vec3f vec, f32 ang) {
    f32 rad = (ang / (DEG_PER_RAD / 2.0f));
    mtxf_create_rot(mtx, vec, sind(rad), cosd(rad));
}

/// Rotates a mat4f matrix about a given axis by a set angle in degrees.
void mtxf_absrot(Mat4 mtx, s32 axisnum, f32 ang) {
    Mat4 rMat;
    Vec3f rot;
    switch (axisnum) {
        case X_AXIS: vec3_copy(rot, gVec3fX   ); break;
        case Y_AXIS: vec3_copy(rot, gVec3fY   ); break;
        case Z_AXIS: vec3_copy(rot, gVec3fZ   ); break;
        default:     vec3_copy(rot, gVec3fZero); break;
    }
    mtxf_create_rot_angular(rMat, rot, (ang / 2.0f));
    Mat4 temp;
    mtxf_copy(temp, mtx);
    mtxf_mul(mtx, temp, rMat);
}

/// Rotates the matrix 'mtx' about the vector given.
void mtxf_rot_about_vec3f(Mat4 mtx, Vec3f vec) {
    if (vec[0] != 0.0f) mtxf_absrot(mtx, X_AXIS, vec[0]);
    if (vec[1] != 0.0f) mtxf_absrot(mtx, Y_AXIS, vec[1]);
    if (vec[2] != 0.0f) mtxf_absrot(mtx, Z_AXIS, vec[2]);
}

/// From Wiseguy
/// http://www.terathon.com/code/oblique.html
void make_oblique(Mat4 toModify, Vec4f clipPlane) {
    Vec4f q, c;
    // Calculate the clip-space corner point opposite the clipping plane
    // as (SIGNUMF(clipPlane.x), SIGNUMF(clipPlane.y), 1, 1) and
    // transform it into camera space by multiplying it
    // by the inverse of the projection matrix
    q[0] = (SIGNUMF(clipPlane[0]) / toModify[0][0]);
    q[1] = (SIGNUMF(clipPlane[1]) / toModify[1][1]);
    q[2] = -1.0f;
    q[3] = (1.0f + toModify[2][2]) / toModify[3][2];
    // Calculate the scaled plane vector
    f32 scale = (2.0f / vec4_dot(clipPlane, q));
    vec4_prod_val(c, clipPlane, scale);
    // Replace the third row of the projection matrix
    toModify[0][2] =  c[0];
    toModify[1][2] =  c[1];
    toModify[2][2] = (c[2] + 1.0f);
    toModify[3][2] =  c[3];
}


/**********************
 * Approach functions *
 **********************/

/**
 * Return the value 'current' after it tries to approach target, going up at
 * most 'inc' and going down at most 'dec'.
 */

//! TODO: does symmetric need to be separate?
//! The non-bool ones are also mostly unused on their own

// s32
s32 approach_s32(s32 current, s32 target, s32 inc, s32 dec) {
    s32 dist = (target - current);
    if (dist > 0) { // current < target
        current = ((dist >  inc) ? (current + inc) : target);
    } else if (dist < 0) { // current > target
        current = ((dist < -dec) ? (current - dec) : target);
    }
    return current;
}

Bool32 approach_s32_bool(s32 *current, s32 target, s32 inc, s32 dec) {
    *current = approach_s32(*current, target, inc, dec);
    return !(*current == target);
}


// s16
s32 approach_s16(s16 current, s16 target, s16 inc, s16 dec) {
    s16 dist = (target - current);
    if (dist >= 0) { // target >= current
        current = ((dist >  inc) ? (current + inc) : target);
    } else { // target < current
        current = ((dist < -dec) ? (current - dec) : target);
    }
    return current;
}

Bool32 approach_s16_bool(s16 *current, s16 target, s16 inc, s16 dec) {
    *current = approach_s16(*current, target, inc, dec);
    return !(*current == target);
}

/// Similar to approach_s32, but converts to s16 and allows for overflow between 32767 and -32768
s32 approach_angle(s32 current, s32 target, s32 inc) {
    s32 dist = (s16)(target - current);
    if (dist < 0) {
        dist += inc;
        if (dist > 0) dist = 0;
    } else if (dist > 0) {
        dist -= inc;
        if (dist < 0) dist = 0;
    }
    return (target - dist);
}

Bool32 approach_angle_bool(s32 *current, s32 target, s32 inc) {
    *current = approach_angle(*current, target, inc);
    return !(*current == target);
}

// f32
f32 approach_f32(f32 current, f32 target, f32 inc, f32 dec) {
    f32 dist = (target - current);
    if (dist >= 0.0f) { // target >= current
        current = ((dist >  inc) ? (current + inc) : target);
    } else { // target < current
        current = ((dist < -dec) ? (current - dec) : target);
    }
    return current;
}

Bool32 approach_f32_bool(f32 *current, f32 target, f32 inc, f32 dec) {
    *current = approach_f32(*current, target, inc, dec);
    return !(*current == target);
}



//! TODO: why does this one look so different but seems to do the exact same as approach_f32_bool,
// other than the bool returning TRUE only once when it reaches
Bool32 approach_f32_ptr(f32 *current, f32 target, f32 inc) {
    if (*current > target) inc = -inc;
    *current += inc;
    if (((*current - target) * inc) >= 0) {
        *current = target;
        return TRUE;
    }
    return FALSE;
}

//! TODO: why is this one approach differently than the others?
// It also returns TRUE only once when it reaches
Bool32 approach_f32_signed(f32 *current, f32 target, f32 inc) {
    *current += inc;
    if (inc >= 0.0f) {
        if (*current > target) {
            *current = target;
            return TRUE;
        }
    } else {
        if (*current < target) {
            *current = target;
            return TRUE;
        }
    }
    return FALSE;
}

/**
 * Approaches an f32 value by taking the difference between the target and current value
 * and adding a fraction of that to the current value.
 * Edits the current value directly, returns TRUE if the target has been reached, FALSE otherwise.
 */
Bool32 approach_f32_asymptotic_bool(f32 *current, f32 target, f32 multiplier) {
    if (multiplier > 1.0f) multiplier = 1.0f;
    *current = (*current + ((target - *current) * multiplier));
    return !(*current == target);
}

/**
 * Nearly the same as the above function, returns new value instead.
 */
f32 approach_f32_asymptotic(f32 current, f32 target, f32 multiplier) {
    return (current = (current + ((target - current) * multiplier)));
}

/**
 * Approaches an s16 value in the same fashion as approach_f32_asymptotic_bool, returns TRUE if target
 * is reached. Note: Since this function takes integers as parameters, the last argument is the
 * reciprocal of what it would be in the previous two functions.
 */
Bool32 approach_s16_asymptotic_bool(s16 *current, s16 target, s16 divisor) {
    *current = approach_s16_asymptotic(*current, target, divisor);
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
        temp   -= target;
        temp   -= (temp / divisor);
        temp   += target;
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

/**
 * Helper function for atan2s. Does a look up of the arctangent of y/x assuming
 * the resulting angle is in range [0, 0x2000] (1/8 of a circle).
 */
// static inline u16 atan2_lookup(f32 y, f32 x) {
//     return ((x == 0) ? 0x0 : atans(y / x));
// }
#define atan2_lookup(y, x) ((x == 0) ? 0x0 : atans((y) / (x)))

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

#undef atan2_lookup

/**
 * Compute the atan2 in radians by calling atan2s and converting the result.
 */
f32 atan2f(f32 y, f32 x) {
    // return (((f32) atan2s(y, x) * M_PI) / 0x8000);
    return angle_to_radians(atan2s(y, x));
}

/**
 * Return atan2(a, b) in degrees. Note that the argument order is swapped from
 * the standard atan2.
 * Used for shadows.
 */
f32 atan2_deg(f32 a, f32 b) {
    // return (((f32) atan2s(a, b) / 65535.0f) * 360.0f);
    return angle_to_degrees(atan2s(a, b));
}

/// Rotates a 2D vector by some angle in degrees.
void rot_xy_deg(f32 deg, f32 *x, f32 *y) {
    f32 rad = (deg / DEG_PER_RAD);
    f32 sr  = sind(rad);
    f32 cr  = cosd(rad);
    f32 xP  = ((*x * cr) - (*y * sr));
    f32 yP  = ((*x * sr) + (*y * cr));
    *x      = xP;
    *y      = yP;
}

/**********
 * Curves *
 **********/

// Variables for a spline curve animation (used for the flight path in the grand star cutscene)
Vec4s *gSplineKeyframe;
f32 gSplineKeyframeFraction;
int gSplineState;

#define CURVE_BEGIN_1 0x1
#define CURVE_BEGIN_2 0x2
#define CURVE_MIDDLE  0x3
#define CURVE_END_1   0x4
#define CURVE_END_2   0x5

#define ONE_SIXTH      (1 /  6.0f)
#define SEVEN_TWELVTHS (7 / 12.0f)

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
static void spline_get_weights(Vec4f result, f32 t, UNUSED s32 c) {
    register f32 tinv = (1 - t);
    register f32 tinv2 = (tinv  * tinv);
    register f32 tinv3 = (tinv2 * tinv);
    register f32 t2 = (t  * t);
    register f32 t3 = (t2 * t);
    switch (gSplineState) {
        case CURVE_BEGIN_1:
            result[0] =   tinv3;
            result[1] =   (( t3 *        1.75f) - (t2 * 4.5f) + (t * 3.0f));
            result[2] =   ((-t3 * (11 / 12.0f)) + (t2 * 1.5f));
            result[3] =    ( t3 *  ONE_SIXTH  );
            break;
        case CURVE_BEGIN_2:
            result[0] = ( tinv3 * 0.25f);
            result[1] = (  ( t3 * SEVEN_TWELVTHS) - (t2 * 1.25f) + (t * 0.25f) + SEVEN_TWELVTHS);
            result[2] = (  (-t3 *           0.5f) + (t2 * 0.5f ) + (t * 0.5f ) + ONE_SIXTH);
            result[3] =    ( t3 *   ONE_SIXTH   );
            break;
        case CURVE_MIDDLE:
            result[0] = ( tinv3 * ONE_SIXTH);
            result[1] = (  ( t3 * 0.5f) - t2                   + (4 / 6.0f));
            result[2] = (  (-t3 * 0.5f) + (t2 * 0.5f) + (t * 0.5f) + ONE_SIXTH);
            result[3] = (  ( t3 * ONE_SIXTH));
            break;
        case CURVE_END_1:
            result[0] =  ( tinv3 *   ONE_SIXTH   );
            result[1] = ((-tinv3 *          0.5f ) + (tinv2 * 0.5f ) + (tinv * 0.5f ) +   ONE_SIXTH   );
            result[2] = (( tinv3 * SEVEN_TWELVTHS) - (tinv2 * 1.25f) + (tinv * 0.25f) + SEVEN_TWELVTHS);
            result[3] =      (t3 *         0.25f);
            break;
        case CURVE_END_2:
            result[0] =  ( tinv3 *    ONE_SIXTH);
            result[1] = ((-tinv3 * (11 / 12.0f)) + (tinv2 * 1.5f));
            result[2] = (( tinv3 *        1.75f) - (tinv2 * 4.5f) + (tinv * 3.0f));
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
    gSplineState            = CURVE_BEGIN_1;
}

/**
 * Poll the next point from a spline animation.
 * anim_spline_init should be called before polling for vectors.
 * Returns TRUE when the last point is reached, FALSE otherwise.
 */
Bool32 anim_spline_poll(Vec3f result) {
    Vec4f weights;
    s32 i;
    Bool32 hasEnded = FALSE;
    vec3_zero(result);
    spline_get_weights(weights, gSplineKeyframeFraction, gSplineState);
    for ((i = 0); (i < 4); (i++)) {
        result[0] += (weights[i] * gSplineKeyframe[i][1]);
        result[1] += (weights[i] * gSplineKeyframe[i][2]);
        result[2] += (weights[i] * gSplineKeyframe[i][3]);
    }
    if ((gSplineKeyframeFraction += (gSplineKeyframe[0][0] / 1000.0f)) >= 1) {
        gSplineKeyframe++;
        gSplineKeyframeFraction--;
        switch (gSplineState) {
            case CURVE_END_2:                                  hasEnded     = TRUE;        break;
            case CURVE_MIDDLE: if (gSplineKeyframe[2][0] == 0) gSplineState = CURVE_END_1; break;
            default:                                           gSplineState++;             break;
        }
    }
    return hasEnded;
}

/**
 * It's a standard B spline
 * Produces values using a cubic b-spline curve. Basically Q is the used output,
 * u is a value between 0 and 1 that represents the position along the spline,
 * and s1-a4 are parameters that define the spline.
 * It takes the next 4 spline points and extrapolates a curvature based positioning of the camera vector that's passed through.
 * The spline is described at www2.cs.uregina.ca/~anima/408/Notes/Interpolation/UniformBSpline.htm
 */
void vec3s_evaluate_cubic_spline(f32 u, Vec3s Q, Vec3f s1, Vec3f s2, Vec3f s3, Vec3f s4) {
    register f32 B[4];
    if (u > 1.0f) u = 1.0f;
    register f32 nu  = (1.0f - u);
    register f32 su  = sqr(u);
    register f32 hcu = (cube(u) / 2.0f);
    B[0] = (cube(nu) / 6.0f);
    B[1] = (( hcu       ) -  su                      + 0.66666667f);
    B[2] = ((-hcu       ) + (su / 2.0f) + (u / 2.0f) + 0.16666667f);
    B[3] =  ( hcu / 3.0f);
    Q[0] = ((B[0] * s1[0]) + (B[1] * s2[0]) + (B[2] * s3[0]) + (B[3] * s4[0]));
    Q[1] = ((B[0] * s1[1]) + (B[1] * s2[1]) + (B[2] * s3[1]) + (B[3] * s4[1]));
    Q[2] = ((B[0] * s1[2]) + (B[1] * s2[2]) + (B[2] * s3[2]) + (B[3] * s4[2]));
}
void vec3f_evaluate_cubic_spline(f32 u, Vec3f Q, Vec3f s1, Vec3f s2, Vec3f s3, Vec3f s4) {
    register f32 B[4];
    if (u > 1.0f) u  = 1.0f;
    register f32 nu  = (1.0f - u);
    register f32 su  = sqr(u);
    register f32 hcu = (cube(u) / 2.0f);
    B[0] = (  cube(nu) / 6.0f);
    B[1] = (( hcu       ) -  su                      + 0.66666667f);
    B[2] = ((-hcu       ) + (su / 2.0f) + (u / 2.0f) + 0.16666667f);
    B[3] = (( hcu / 3.0f)                                         );
    Q[0] = ((B[0] * s1[0]) + (B[1] * s2[0]) + (B[2] * s3[0]) + (B[3] * s4[0]));
    Q[1] = ((B[0] * s1[1]) + (B[1] * s2[1]) + (B[2] * s3[1]) + (B[3] * s4[1]));
    Q[2] = ((B[0] * s1[2]) + (B[1] * s2[2]) + (B[2] * s3[2]) + (B[3] * s4[2]));
}
