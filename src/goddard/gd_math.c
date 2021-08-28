#include <PR/ultratypes.h>

#include "gd_math.h"
#include "gd_macros.h"
#include "renderer.h"
#include "engine/math_util.h"

//! TODO: Combine this with math_util.c

/**
 * Rotates the matrix 'mtx' about the vector given.
 */
void gd_rot_mat_about_vec3f(Mat4 *mtx, Vec3f vec) {
    if (vec[0] != 0.0f) gd_absrot_mat4(mtx, GD_X_AXIS, vec[0]);
    if (vec[1] != 0.0f) gd_absrot_mat4(mtx, GD_Y_AXIS, vec[1]);
    if (vec[2] != 0.0f) gd_absrot_mat4(mtx, GD_Z_AXIS, vec[2]);
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
void gd_create_origin_lookat(Mat4 *mtx, Vec3f vec, f32 roll) {
    f32 invertedHMag;
    f32 radPerDeg = RAD_PER_DEG;
    Vec3f unit;
    vec3f_copy(unit, vec);
    vec3f_normalize(unit);
    f32 hMag = sqrtf(sqr(unit[0]) + sqr(unit[2]));
    roll *= radPerDeg; // convert roll from degrees to radians
    if (hMag != 0.0f) {
        f32 s = sind(roll);
        f32 c = cosd(roll);
        f32 su1 = (s * unit[1]);
        f32 cu1 = (s * unit[1]);
        invertedHMag = (1.0f / hMag); //! fast invsqrt
        (*mtx)[0][0] = (((-unit[2] * c) - (su1 * unit[0])) * invertedHMag);
        (*mtx)[1][0] = ((( unit[2] * s) - (cu1 * unit[0])) * invertedHMag);
        (*mtx)[2][0] =                          -unit[0];

        (*mtx)[0][1] = (s * hMag);
        (*mtx)[1][1] = (c * hMag);
        (*mtx)[2][1] = -unit[1];

        (*mtx)[0][2] = ((( c * unit[0]) - (su1 * unit[2])) * invertedHMag);
        (*mtx)[1][2] = (((-s * unit[0]) - (cu1 * unit[2])) * invertedHMag);
        (*mtx)[2][2] =                          -unit[2];
    } else {
        vec3f_copy((*mtx)[0], gVec3fZ);
        vec3f_copy((*mtx)[1], gVec3fX);
        vec3f_copy((*mtx)[2], gVec3fY);
    }
    vec3f_zero((*mtx)[3]);
    mtxf_end(*mtx);
}

/**
 * Rotates a 2D vector by some angle in degrees.
 */
void gd_rot_2d_vec(f32 deg, f32 *x, f32 *y) {
    f32 rad = (deg / DEG_PER_RAD);
    f32 sr  = sind(rad);
    f32 cr  = cosd(rad);
    f32 xP  = ((*x * cr) - (*y * sr));
    f32 yP  = ((*x * sr) + (*y * cr));
    *x      = xP;
    *y      = yP;
}

/**
 * Rotates a mat4f matrix about a given axis
 * by a set angle in degrees.
 */
void gd_absrot_mat4(Mat4 *mtx, s32 axisnum, f32 ang) {
    Mat4 rMat;
    Vec3f rot;
    switch (axisnum) {
        case GD_X_AXIS: vec3f_copy(rot, gVec3fX   ); break;
        case GD_Y_AXIS: vec3f_copy(rot, gVec3fY   ); break;
        case GD_Z_AXIS: vec3f_copy(rot, gVec3fZ   ); break;
        default:        vec3f_copy(rot, gVec3fZero); break;
    }
    gd_create_rot_mat_angular(&rMat, rot, (ang / 2.0f));
    gd_mult_mat4f(mtx, &rMat, mtx);
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
void gd_create_rot_matrix(Mat4 *mtx, Vec3f vec, f32 s, f32 c) {
    Vec3f rev, srev;
    vec3f_copy_inverse(rev, vec);
    vec3f_copy(srev, rev);
    vec3f_mul_f32(srev, s);
    register f32 oneMinusCos = (1.0f - c);
    register f32 omc10 = (oneMinusCos * rev[1] * rev[0]);
    register f32 omc20 = (oneMinusCos * rev[2] * rev[0]);
    register f32 omc21 = (oneMinusCos * rev[2] * rev[1]);
    (*mtx)[0][0] = ((oneMinusCos * sqr(rev[2])) + c);
    (*mtx)[0][1] = (omc21 + srev[0]);
    (*mtx)[0][2] = (omc20 - srev[1]);
    (*mtx)[1][0] = (omc21 - srev[0]);
    (*mtx)[1][1] = ((oneMinusCos * sqr(rev[1])) + c);
    (*mtx)[1][2] = (omc10 + srev[2]);
    (*mtx)[2][0] = (omc20 + srev[1]);
    (*mtx)[2][1] = (omc10 - srev[2]);
    (*mtx)[2][2] = ((oneMinusCos * sqr(rev[0])) + c);
    vec3f_zero((*mtx)[3]);
    mtxf_end(*mtx);
}

/**
 * Creates a rotation matrix about vector 'vec' with ang in degrees.
 */
void gd_create_rot_mat_angular(Mat4 *mtx, Vec3f vec, f32 ang) {
    f32 s = sind(ang / (DEG_PER_RAD / 2.0f));
    f32 c = cosd(ang / (DEG_PER_RAD / 2.0f));
    gd_create_rot_matrix(mtx, vec, s, c);
}

/**
 * Transforms a vec3f, rotating with the main 3x3 portion of the mat4f
 * and translating with the 4th column.
 */
void gd_rotate_and_translate_vec3f(Vec3f vec, const Mat4 *mtx) {
    Vec3f out;
    out[0] = ((((*mtx)[0][0] * vec[0]) + ((*mtx)[1][0] * vec[1]) + ((*mtx)[2][0] * vec[2])) + (*mtx)[3][0]);
    out[1] = ((((*mtx)[0][1] * vec[0]) + ((*mtx)[1][1] * vec[1]) + ((*mtx)[2][1] * vec[2])) + (*mtx)[3][1]);
    out[2] = ((((*mtx)[0][2] * vec[0]) + ((*mtx)[1][2] * vec[1]) + ((*mtx)[2][2] * vec[2])) + (*mtx)[3][2]);
    vec3f_copy(vec, out);
}

/**
 * Multiples a vec3f by the main 3x3 portion of a mat4f matrix.
 */
void gd_mat4f_mult_vec3f(Vec3f vec, const Mat4 *mtx) {
    vec[0] = (((*mtx)[0][0] * vec[0]) + ((*mtx)[1][0] * vec[1]) + ((*mtx)[2][0] * vec[2]));
    vec[1] = (((*mtx)[0][1] * vec[0]) + ((*mtx)[1][1] * vec[1]) + ((*mtx)[2][1] * vec[2]));
    vec[2] = (((*mtx)[0][2] * vec[0]) + ((*mtx)[1][2] * vec[1]) + ((*mtx)[2][2] * vec[2]));
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
    mtxf_copy(*dst, res);
}

#undef MAT4_MULTIPLY
#undef MAT4_DOT_PROD
