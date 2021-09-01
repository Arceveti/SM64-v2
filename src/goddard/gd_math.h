#ifndef GD_MATH_H
#define GD_MATH_H

#include <PR/ultratypes.h>

#include "gd_types.h"
#include "engine/math_util.h"

// Needed for gd_math.c itself.
void   gd_rot_mat_about_vec3f(      Mat4 *mtx, Vec3f vec);
void   gd_rot_2d_vec(f32 deg, f32 *x, f32 *y);
void   gd_absrot_mat4(Mat4 *mtx, s32 axisnum, f32 ang);
void   gd_create_rot_mat_angular(Mat4 *mtx, Vec3f vec, f32 ang);
void   gd_rotate_and_translate_vec3f(Vec3f vec, const Mat4 *mtx);
void   gd_mat4f_mult_vec3f(          Vec3f vec, const Mat4 *mtx);
void   gd_mult_mat4f(const Mat4 *mA, const Mat4 *mB, Mat4 *dst);

#endif // GD_MATH_H
