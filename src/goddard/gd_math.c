#include <PR/ultratypes.h>

#include "gd_math.h"
#include "renderer.h"
#include "engine/math_util.h"

//! TODO: Combine this with math_util.c

/// Rotates the matrix 'mtx' about the vector given.
void gd_rot_mat_about_vec3f(Mat4 *mtx, Vec3f vec) {
    if (vec[0] != 0.0f) gd_absrot_mat4(mtx, X_AXIS, vec[0]);
    if (vec[1] != 0.0f) gd_absrot_mat4(mtx, Y_AXIS, vec[1]);
    if (vec[2] != 0.0f) gd_absrot_mat4(mtx, Z_AXIS, vec[2]);
}

/// Rotates a 2D vector by some angle in degrees.
void gd_rot_2d_vec(f32 deg, f32 *x, f32 *y) {
    f32 rad = (deg / DEG_PER_RAD);
    f32 sr  = sind(rad);
    f32 cr  = cosd(rad);
    f32 xP  = ((*x * cr) - (*y * sr));
    f32 yP  = ((*x * sr) + (*y * cr));
    *x      = xP;
    *y      = yP;
}

/// Rotates a mat4f matrix about a given axis by a set angle in degrees.
void gd_absrot_mat4(Mat4 *mtx, s32 axisnum, f32 ang) {
    Mat4 rMat;
    Vec3f rot;
    switch (axisnum) {
        case X_AXIS: vec3f_copy(rot, gVec3fX   ); break;
        case Y_AXIS: vec3f_copy(rot, gVec3fY   ); break;
        case Z_AXIS: vec3f_copy(rot, gVec3fZ   ); break;
        default:     vec3f_copy(rot, gVec3fZero); break;
    }
    gd_create_rot_mat_angular(&rMat, rot, (ang / 2.0f));
    gd_mult_mat4f(mtx, &rMat, mtx);
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
    vec3f_mul_val(srev, s);
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

/// Creates a rotation matrix about vector 'vec' with ang in degrees.
void gd_create_rot_mat_angular(Mat4 *mtx, Vec3f vec, f32 ang) {
    f32 rad = (ang / (DEG_PER_RAD / 2.0f));
    gd_create_rot_matrix(mtx, vec, sind(rad), cosd(rad));
}

/// Transforms a vec3f, rotating with the main 3x3 portion of the mat4f and translating with the 4th column.
void gd_rotate_and_translate_vec3f(Vec3f vec, const Mat4 *mtx) {
    Vec3f out;
    out[0] = ((((*mtx)[0][0] * vec[0]) + ((*mtx)[1][0] * vec[1]) + ((*mtx)[2][0] * vec[2])) + (*mtx)[3][0]);
    out[1] = ((((*mtx)[0][1] * vec[0]) + ((*mtx)[1][1] * vec[1]) + ((*mtx)[2][1] * vec[2])) + (*mtx)[3][1]);
    out[2] = ((((*mtx)[0][2] * vec[0]) + ((*mtx)[1][2] * vec[1]) + ((*mtx)[2][2] * vec[2])) + (*mtx)[3][2]);
    vec3f_copy(vec, out);
}

/// Multiples a vec3f by the main 3x3 portion of a mat4f matrix.
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

/// Multiplies two Mat4 matrices and puts it in dst.
void gd_mult_mat4f(const Mat4 *mA, const Mat4 *mB, Mat4 *dst) {
    Mat4 res;
    MAT4_MULTIPLY((*mA), (*mB), res);
    mtxf_copy(*dst, res);
}

#undef MAT4_MULTIPLY
#undef MAT4_DOT_PROD
