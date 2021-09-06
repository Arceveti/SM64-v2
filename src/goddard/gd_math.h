#ifndef GD_MATH_H
#define GD_MATH_H

#include <PR/ultratypes.h>

#include "gd_types.h"
#include "engine/math_util.h"

// Needed for gd_math.c itself.
void   gd_rot_mat_about_vec3f(Mat4 mtx, Vec3f vec);
void   gd_rot_2d_vec(f32 deg, f32 *x, f32 *y);
void   gd_absrot_mat4(Mat4 mtx, s32 axisnum, f32 ang);
void   gd_create_rot_mat_angular(Mat4 *mtx, Vec3f vec, f32 ang);

#endif // GD_MATH_H
