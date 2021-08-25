#include <PR/ultratypes.h>

#include "gd_math.h"
#include "gd_macros.h"
#include "renderer.h"
#include "engine/math_util.h"

//! TODO: Combine this with math_util.c

/**
 * Set mtx to a look-at matrix for the camera. The resulting transformation
 * transforms the world as if there exists a camera at position 'from' pointed
 * at the position 'to'.
 * An effective goddard copy of mtxf_lookat.
 */
void gd_mat4f_lookat(Mat4 *mtx, f32 xFrom, f32 yFrom, f32 zFrom,
                                f32 xTo,   f32 yTo,   f32 zTo,
                                f32 zColY, f32 yColY, f32 xColY) {
    f32 invLength;
    Vec3f d;
    Vec3f colX;
    Vec3f norm;
    // No reason to do this? mtx is set lower.
    gd_set_identity_mat4(mtx);
    d[2] = (xTo - xFrom);
    d[1] = (yTo - yFrom);
    d[0] = (zTo - zFrom);
    invLength = (ABSF(d[2]) + ABSF(d[1]) + ABSF(d[0]));
    // Scales 'd' if smaller than 10 or larger than 10,000 to be
    // of a magnitude of 10,000.
    if ((invLength > 10000.0f) || (invLength < 10.0f)) {
        vec3f_copy_inverse(norm, d);
        vec3f_normalize(norm);
        vec3f_mul_f32(norm, 10000.0f);
        vec3f_copy_inverse(d, norm);
    }
#ifdef FAST_INVSQRT
    invLength = -Q_rsqrtf(sqr(d[2]) + sqr(d[1]) + sqr(d[0]));
#else
    invLength = -(1.0f / vec3f_mag(d));
#endif
    vec3f_mul_f32(d, invLength);
    colX[2] = ((yColY * d[0]) - (xColY * d[1]));
    colX[1] = ((xColY * d[2]) - (zColY * d[0]));
    colX[0] = ((zColY * d[1]) - (yColY * d[2]));
#ifdef FAST_INVSQRT
    invLength = Q_rsqrtf(sqr(colX[2]) + sqr(colX[1]) + sqr(colX[0]));
#else
    invLength = (1.0f / vev3f_mag(colX));
#endif
    vec3f_mul_f32(colX, invLength);
    zColY   = ((d[1] * colX[0]) - (d[0] * colX[1]));
    yColY   = ((d[0] * colX[2]) - (d[2] * colX[0]));
    xColY   = ((d[2] * colX[1]) - (d[1] * colX[2]));
#ifdef FAST_INVSQRT
    invLength = Q_rsqrtf(sqr(zColY) + sqr(yColY) + sqr(xColY));
#else
    invLength = (1.0f / sqrtf(sqr(zColY) + sqr(yColY) + sqr(xColY)));
#endif
    zColY *= invLength;
    yColY *= invLength;
    xColY *= invLength;

    (*mtx)[0][0] = colX[2];
    (*mtx)[1][0] = colX[1];
    (*mtx)[2][0] = colX[0];
    (*mtx)[3][0] = -((xFrom * colX[2]) + (yFrom * colX[1]) + (zFrom * colX[0]));

    (*mtx)[0][1] = zColY;
    (*mtx)[1][1] = yColY;
    (*mtx)[2][1] = xColY;
    (*mtx)[3][1] = -((xFrom * zColY) + (yFrom * yColY) + (zFrom * xColY));

    (*mtx)[0][2] = d[2];
    (*mtx)[1][2] = d[1];
    (*mtx)[2][2] = d[0];
    (*mtx)[3][2] = -((xFrom * d[2]) + (yFrom * d[1]) + (zFrom * d[0]));

    (*mtx)[0][3] = 0.0f;
    (*mtx)[1][3] = 0.0f;
    (*mtx)[2][3] = 0.0f;
    (*mtx)[3][3] = 1.0f;
}

/**
 * Scales a mat4f in each dimension by a vector.
 */
void gd_scale_mat4f_by_vec3f(Mat4 *mtx, struct GdVec3f *vec) {
    (*mtx)[0][0] *= vec->x;
    (*mtx)[0][1] *= vec->x;
    (*mtx)[0][2] *= vec->x;
    (*mtx)[1][0] *= vec->y;
    (*mtx)[1][1] *= vec->y;
    (*mtx)[1][2] *= vec->y;
    (*mtx)[2][0] *= vec->z;
    (*mtx)[2][1] *= vec->z;
    (*mtx)[2][2] *= vec->z;
}

/**
 * Rotates the matrix 'mtx' about the vector given.
 */
void gd_rot_mat_about_vec(Mat4 *mtx, struct GdVec3f *vec) {
    if (vec->x != 0.0f) gd_absrot_mat4(mtx, GD_X_AXIS, vec->x);
    if (vec->y != 0.0f) gd_absrot_mat4(mtx, GD_Y_AXIS, vec->y);
    if (vec->z != 0.0f) gd_absrot_mat4(mtx, GD_Z_AXIS, vec->z);
}

/**
 * Adds each component of a vector to the
 * translation column of a mat4f matrix.
 */
void gd_add_vec3f_to_mat4f_offset(Mat4 *mtx, struct GdVec3f *vec) {
    (*mtx)[3][0] += vec->x;
    (*mtx)[3][1] += vec->y;
    (*mtx)[3][2] += vec->z;
}

/**
 * Creates a lookat matrix, but specifically from the perspective of the origin.
 * Rolls is only ever 0 in practice, and this is really only ever used once.
 *
 * Matrix has form-  | -(cz+sxy)/h sh  (cx-syz)/h 0 |
 *                   |  (sz-cxy)/h ch -(sx+cyz)/h 0 |
 *                   |     -x      -y     -z      0 |
 *                   |      0       0      0      1 |
 */
void gd_create_origin_lookat(Mat4 *mtx, struct GdVec3f *vec, f32 roll) {
    f32 invertedHMag;
    f32 radPerDeg = RAD_PER_DEG;
    Vec3f unit;
    gdvec3f_to_vec3f(unit, vec);
    vec3f_normalize(unit);
    f32 hMag = sqrtf(sqr(unit[0]) + sqr(unit[2]));
    roll *= radPerDeg; // convert roll from degrees to radians
    f32 s = sind(roll);
    f32 c = cosd(roll);
    gd_set_identity_mat4(mtx);
    if (hMag != 0.0f) {
        invertedHMag = (1.0f / hMag); //! fast invsqrt
        (*mtx)[0][0] = (((-unit[2] * c) - (s * unit[1] * unit[0])) * invertedHMag);
        (*mtx)[1][0] = ((( unit[2] * s) - (c * unit[1] * unit[0])) * invertedHMag);
        (*mtx)[2][0] =                                  -unit[0];
        (*mtx)[3][0] = 0.0f;

        (*mtx)[0][1] = (s * hMag);
        (*mtx)[1][1] = (c * hMag);
        (*mtx)[2][1] =                       -unit[1];
        (*mtx)[3][1] = 0.0f;

        (*mtx)[0][2] = ((( c * unit[0]) - (s * unit[1] * unit[2])) * invertedHMag);
        (*mtx)[1][2] = (((-s * unit[0]) - (c * unit[1] * unit[2])) * invertedHMag);
        (*mtx)[2][2] =                                  -unit[2];
        (*mtx)[3][2] = 0.0f;

        (*mtx)[0][3] = 0.0f;
        (*mtx)[1][3] = 0.0f;
        (*mtx)[2][3] = 0.0f;
        (*mtx)[3][3] = 1.0f;
    } else {
        (*mtx)[0][0] = 0.0f;
        (*mtx)[1][0] = 1.0f;
        (*mtx)[2][0] = 0.0f;
        (*mtx)[3][0] = 0.0f;

        (*mtx)[0][1] = 0.0f;
        (*mtx)[1][1] = 0.0f;
        (*mtx)[2][1] = 1.0f;
        (*mtx)[3][1] = 0.0f;

        (*mtx)[0][2] = 1.0f;
        (*mtx)[1][2] = 0.0f;
        (*mtx)[2][2] = 0.0f;
        (*mtx)[3][2] = 0.0f;

        (*mtx)[0][3] = 0.0f;
        (*mtx)[1][3] = 0.0f;
        (*mtx)[2][3] = 0.0f;
        (*mtx)[3][3] = 1.0f;
    }
}

void gd_vec3f_copy(struct GdVec3f *dst, struct GdVec3f *src) {
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
}

void gdvec3f_to_vec3f(Vec3f dst, struct GdVec3f *src) {
    dst[0] = src->x;
    dst[1] = src->y;
    dst[2] = src->z;
}

void vec3f_to_gdvec3f(struct GdVec3f *dst, Vec3f src) {
    dst->x = src[0];
    dst->y = src[1];
    dst->z = src[2];
}

/**
 * Clamps a vector within a set range about zero.
 */
void gd_clamp_vec3f(struct GdVec3f *vec, f32 limit) {
    if (vec->x > limit) {
        vec->x = limit;
    } else if (vec->x < -limit) {
        vec->x = -limit;
    }
    if (vec->y > limit) {
        vec->y = limit;
    } else if (vec->y < -limit) {
        vec->y = -limit;
    }
    if (vec->z > limit) {
        vec->z = limit;
    } else if (vec->z < -limit) {
        vec->z = -limit;
    }
}

/**
 * Rotates a 2D vector by some angle in degrees.
 */
void gd_rot_2d_vec(f32 deg, f32 *x, f32 *y) {
    f32 rad = (deg / DEG_PER_RAD);
    f32 xP  = ((*x * cosd(rad)) - (*y * sind(rad)));
    f32 yP  = ((*x * sind(rad)) + (*y * cosd(rad)));
    *x      = xP;
    *y      = yP;
}

/**
 * Rotates a mat4f matrix about a given axis
 * by a set angle in degrees.
 */
void gd_absrot_mat4(Mat4 *mtx, s32 axisnum, f32 ang) {
    Mat4 rMat;
    struct GdVec3f rot;
    switch (axisnum) {
        case GD_X_AXIS:
            rot.x = 1.0f;
            rot.y = 0.0f;
            rot.z = 0.0f;
            break;
        case GD_Y_AXIS:
            rot.x = 0.0f;
            rot.y = 1.0f;
            rot.z = 0.0f;
            break;
        case GD_Z_AXIS:
            rot.x = 0.0f;
            rot.y = 0.0f;
            rot.z = 1.0f;
            break;
        default: gd_exit(); // Bad axis num
    }
    gd_create_rot_mat_angular(&rMat, &rot, (ang / 2.0f));
    gd_mult_mat4f(mtx, &rMat, mtx);
}

f32 gd_vec3f_magnitude(struct GdVec3f *vec) {
    return sqrtf(sqr(vec->x) + sqr(vec->y) + sqr(vec->z));
}

/**
 * Normalizes a vec3f to have a length of 1.
 */
Bool32 gd_normalize_vec3f(struct GdVec3f *vec) {
    f32 mag = (sqr(vec->x) + sqr(vec->y) + sqr(vec->z));
    if (mag == 0.0f) return FALSE;
#ifdef FAST_INVSQRT
    mag = Q_rsqrtf(mag);
#else
    mag = (1.0f / sqrtf(mag));
#endif
    // gd_sqrt_f rounds near 0 numbers to 0, so verify again.
    if (mag == 0.0f) {
        vec3f_to_gdvec3f(vec, gVec3fZero);
        return FALSE;
    }
    vec->x *= mag;
    vec->y *= mag;
    vec->z *= mag;
    return TRUE;
}

/**
 * Stores the cross product of 'a' x 'b' in 'dst'.
 */
void gd_cross_vec3f(struct GdVec3f *a, struct GdVec3f *b, struct GdVec3f *dst) {
    Vec3f result;
    result[0] = ((a->y * b->z) - (a->z * b->y));
    result[1] = ((a->z * b->x) - (a->x * b->z));
    result[2] = ((a->x * b->y) - (a->y * b->x));
    vec3f_to_gdvec3f(dst, result);
}

/**
 * Returns the dot product of 'a' and 'b'.
 */
f32 gd_dot_vec3f(struct GdVec3f *a, struct GdVec3f *b) {
    return ((a->x * b->x) + (a->y * b->y) + (a->z * b->z));
}

/**
 * Inverts a matrix from src and stores it into dst.
 * Reaches a fatal_print if the determinant is 0.
 */
void gd_inverse_mat4f(Mat4 *src, Mat4 *dst) {
    s32 i, j;
    gd_adjunct_mat4f(src, dst);
    f32 determinant = mtxf_det(dst);
    if (ABSF(determinant) < 1e-5f) gd_exit(); // Non-singular matrix, no inverse!
    for ((i = 0); (i < 4); (i++)) for ((j = 0); (j < 4); (j++)) (*dst)[i][j] /= determinant;
}

/**
 * Takes a matrix from src and converts it into its adjunct in dst.
 */
void gd_adjunct_mat4f(Mat4 *src, Mat4 *dst) {
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
 * Shifts a matrix up by one row, putting the top row on bottom.
 */
void gd_shift_mat_up(Mat4 *mtx) {
    s32 i, j;
    f32 temp[3];
    for ((i = 0); (i < 3); (i++)) temp[i] = (*mtx)[0][i + 1];
    for ((i = 1); (i < 4); (i++)) for ((j = 1); (j < 4); (j++)) (*mtx)[i - 1][j - 1] = (*mtx)[i][j];
    (*mtx)[0][3] = 0.0f;
    (*mtx)[1][3] = 0.0f;
    (*mtx)[2][3] = 0.0f;
    (*mtx)[3][3] = 1.0f;
    for ((i = 0); (i < 3); (i++)) (*mtx)[3][i] = temp[i];
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
void gd_create_rot_matrix(Mat4 *mtx, struct GdVec3f *vec, f32 s, f32 c) {
    Vec3f rev;
    rev[2] = vec->x;
    rev[1] = vec->y;
    rev[0] = vec->z;
    f32 oneMinusCos = (1.0f - c);

    (*mtx)[0][0] = ((oneMinusCos * rev[2] * rev[2]) + c);
    (*mtx)[0][1] = ((oneMinusCos * rev[2] * rev[1]) + (s * rev[0]));
    (*mtx)[0][2] = ((oneMinusCos * rev[2] * rev[0]) - (s * rev[1]));
    (*mtx)[0][3] = 0.0f;

    (*mtx)[1][0] = ((oneMinusCos * rev[2] * rev[1]) - s * rev[0]);
    (*mtx)[1][1] = ((oneMinusCos * rev[1] * rev[1]) + c);
    (*mtx)[1][2] = ((oneMinusCos * rev[1] * rev[0]) + s * rev[2]);
    (*mtx)[1][3] = 0.0f;

    (*mtx)[2][0] = ((oneMinusCos * rev[2] * rev[0]) + (s * rev[1]));
    (*mtx)[2][1] = ((oneMinusCos * rev[1] * rev[0]) - (s * rev[2]));
    (*mtx)[2][2] = ((oneMinusCos * rev[0] * rev[0]) + c);
    (*mtx)[2][3] = 0.0f;

    vec3f_copy((*mtx)[3], gVec3fZero);
    (*mtx)[3][3] = 1.0f;
}

/**
 * Creates a rotation matrix about vector 'vec' with ang in degrees.
 */
void gd_create_rot_mat_angular(Mat4 *mtx, struct GdVec3f *vec, f32 ang) {
    f32 s = sind(ang / (DEG_PER_RAD / 2.0f));
    f32 c = cosd(ang / (DEG_PER_RAD / 2.0f));
    gd_create_rot_matrix(mtx, vec, s, c);
}

/**
 * Sets a mat4f matrix to an identity matrix.
 */
void gd_set_identity_mat4(Mat4 *mtx) {
    (*mtx)[0][0] = 1.0f;
    (*mtx)[0][1] = 0.0f;
    (*mtx)[0][2] = 0.0f;
    (*mtx)[0][3] = 0.0f;
    (*mtx)[1][0] = 0.0f;
    (*mtx)[1][1] = 1.0f;
    (*mtx)[1][2] = 0.0f;
    (*mtx)[1][3] = 0.0f;
    (*mtx)[2][0] = 0.0f;
    (*mtx)[2][1] = 0.0f;
    (*mtx)[2][2] = 1.0f;
    (*mtx)[2][3] = 0.0f;
    (*mtx)[3][0] = 0.0f;
    (*mtx)[3][1] = 0.0f;
    (*mtx)[3][2] = 0.0f;
    (*mtx)[3][3] = 1.0f;
}

/**
 * Copies a mat4f from src to dst.
 */
void gd_copy_mat4f(const Mat4 *src, Mat4 *dst) {
    (*dst)[0][0] = (*src)[0][0];
    (*dst)[0][1] = (*src)[0][1];
    (*dst)[0][2] = (*src)[0][2];
    (*dst)[0][3] = (*src)[0][3];
    (*dst)[1][0] = (*src)[1][0];
    (*dst)[1][1] = (*src)[1][1];
    (*dst)[1][2] = (*src)[1][2];
    (*dst)[1][3] = (*src)[1][3];
    (*dst)[2][0] = (*src)[2][0];
    (*dst)[2][1] = (*src)[2][1];
    (*dst)[2][2] = (*src)[2][2];
    (*dst)[2][3] = (*src)[2][3];
    (*dst)[3][0] = (*src)[3][0];
    (*dst)[3][1] = (*src)[3][1];
    (*dst)[3][2] = (*src)[3][2];
    (*dst)[3][3] = (*src)[3][3];
}

/**
 * Transforms a vec3f, rotating with the main 3x3 portion of the mat4f
 * and translating with the 4th column.
 */
void gd_rotate_and_translate_vec3f(struct GdVec3f *vec, const Mat4 *mtx) {
    //! Setting vec directly breaks things somehow
    Vec3f out;
    out[0] = ((((*mtx)[0][0] * vec->x) + ((*mtx)[1][0] * vec->y) + ((*mtx)[2][0] * vec->z)) + (*mtx)[3][0]);
    out[1] = ((((*mtx)[0][1] * vec->x) + ((*mtx)[1][1] * vec->y) + ((*mtx)[2][1] * vec->z)) + (*mtx)[3][1]);
    out[2] = ((((*mtx)[0][2] * vec->x) + ((*mtx)[1][2] * vec->y) + ((*mtx)[2][2] * vec->z)) + (*mtx)[3][2]);
    vec3f_to_gdvec3f(vec, out);
}

/**
 * Multiples a vec3f by the main 3x3 portion of a mat4f matrix.
 */
void gd_mat4f_mult_vec3f(struct GdVec3f *vec, const Mat4 *mtx) {
    vec->x = (((*mtx)[0][0] * vec->x) + ((*mtx)[1][0] * vec->y) + ((*mtx)[2][0] * vec->z));
    vec->y = (((*mtx)[0][1] * vec->x) + ((*mtx)[1][1] * vec->y) + ((*mtx)[2][1] * vec->z));
    vec->z = (((*mtx)[0][2] * vec->x) + ((*mtx)[1][2] * vec->y) + ((*mtx)[2][2] * vec->z));
}

#define MAT4_DOT_PROD(A, B, R, row, col)                                                               \
    {                                                                                                  \
        (R)[(row)][(col)]  = ((A)[(row)][0] * (B)[0][(col)]);                                          \
        (R)[(row)][(col)] += ((A)[(row)][1] * (B)[1][(col)]);                                          \
        (R)[(row)][(col)] += ((A)[(row)][2] * (B)[2][(col)]);                                          \
        (R)[(row)][(col)] += ((A)[(row)][3] * (B)[3][(col)]);                                          \
    }

#define MAT4_MULTIPLY(A, B, R)                                                                         \
    {                                                                                                  \
        MAT4_DOT_PROD((A), (B), (R), 0, 0);                                                            \
        MAT4_DOT_PROD((A), (B), (R), 0, 1);                                                            \
        MAT4_DOT_PROD((A), (B), (R), 0, 2);                                                            \
        MAT4_DOT_PROD((A), (B), (R), 0, 3);                                                            \
        MAT4_DOT_PROD((A), (B), (R), 1, 0);                                                            \
        MAT4_DOT_PROD((A), (B), (R), 1, 1);                                                            \
        MAT4_DOT_PROD((A), (B), (R), 1, 2);                                                            \
        MAT4_DOT_PROD((A), (B), (R), 1, 3);                                                            \
        MAT4_DOT_PROD((A), (B), (R), 2, 0);                                                            \
        MAT4_DOT_PROD((A), (B), (R), 2, 1);                                                            \
        MAT4_DOT_PROD((A), (B), (R), 2, 2);                                                            \
        MAT4_DOT_PROD((A), (B), (R), 2, 3);                                                            \
        MAT4_DOT_PROD((A), (B), (R), 3, 0);                                                            \
        MAT4_DOT_PROD((A), (B), (R), 3, 1);                                                            \
        MAT4_DOT_PROD((A), (B), (R), 3, 2);                                                            \
        MAT4_DOT_PROD((A), (B), (R), 3, 3);                                                            \
    }

/**
 * Multiplies two Mat4 matrices and puts it in dst.
 */
void gd_mult_mat4f(const Mat4 *mA, const Mat4 *mB, Mat4 *dst) {
    Mat4 res;
    MAT4_MULTIPLY((*mA), (*mB), res);
    gd_copy_mat4f(&res, dst);
}

#undef MAT4_MULTIPLY
#undef MAT4_DOT_PROD
