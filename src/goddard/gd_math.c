#include <PR/ultratypes.h>

#include "gd_math.h"
#include "renderer.h"
#include "engine/math_util.h"

//! TODO: Combine this with math_util.c

/// Rotates the matrix 'mtx' about the vector given.
void gd_rot_mat_about_vec3f(Mat4 mtx, Vec3f vec) {
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
void gd_absrot_mat4(Mat4 mtx, s32 axisnum, f32 ang) {
    Mat4 rMat;
    Vec3f rot;
    switch (axisnum) {
        case X_AXIS: vec3_copy(rot, gVec3fX   ); break;
        case Y_AXIS: vec3_copy(rot, gVec3fY   ); break;
        case Z_AXIS: vec3_copy(rot, gVec3fZ   ); break;
        default:     vec3_copy(rot, gVec3fZero); break;
    }
    gd_create_rot_mat_angular(&rMat, rot, (ang / 2.0f));
    Mat4 temp;
    mtxf_copy(temp, mtx);
    mtxf_mul(mtx, temp, rMat);
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
    vec3_copy_inverse(rev, vec);
    vec3_copy(srev, rev);
    vec3_mul_val(srev, s);
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
    vec3_zero((*mtx)[3]);
    MTXF_END(*mtx);
}

/// Creates a rotation matrix about vector 'vec' with ang in degrees.
void gd_create_rot_mat_angular(Mat4 *mtx, Vec3f vec, f32 ang) {
    f32 rad = (ang / (DEG_PER_RAD / 2.0f));
    gd_create_rot_matrix(mtx, vec, sind(rad), cosd(rad));
}
