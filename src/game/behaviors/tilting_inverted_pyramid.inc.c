#include "config.h"

/**
 * This is the behavior file for the tilting inverted pyramids in BitFS/LLL.
 * The object essentially just tilts and moves Mario with it.
 */

//! move to math_util?
/**
 * Creates a transform matrix on a variable passed in from given normals
 * and the object's position.
 */
void create_transform_from_normals(Mat4 transform, f32 xNorm, f32 yNorm, f32 zNorm) {
    Vec3n normal;
    Vec3f pos;
    vec3f_copy(pos, &o->oPosVec);
    vec3f_set(normal, xNorm, yNorm, zNorm);
    mtxf_align_terrain_normal(transform, normal, pos, 0);
}

/**
 * Initialize the object's transform matrix with Y being up.
 */
void bhv_platform_normals_init(void) {
    Mat4 *transform = &o->transform;
    vec3f_set(&o->oTiltingPyramidNormalVec,   0.0f, 1.0f, 0.0f);
    create_transform_from_normals(*transform, 0.0f, 1.0f, 0.0f);
}

/**
 * Main behavior for the tilting pyramids in LLL/BitFS. These platforms calculate rough normals from Mario's position,
 * then gradually tilt back moving Mario with them.
 */
void bhv_tilting_inverted_pyramid_loop(void) {
    f32 mag;
    Vec3f d;
    Vec3f dist;
    Vec3f posBeforeRotation;
    Vec3f posAfterRotation;
    // Mario's position
    f32 mx, my, mz;
    Mat4 *transform = &o->transform;
    if (gMarioObject->platform == o) {
        get_mario_pos(&mx, &my, &mz);
        vec3f_diff(dist, &gMarioObject->oPosVec, &o->oPosVec);
        linear_mtxf_mul_vec3f(*transform, posBeforeRotation, dist);
        vec3f_diff(d, &gMarioObject->oPosVec, &o->oPosVec);
#ifdef FAST_INVSQRT
        mag = Q_rsqrtf(sqr(d[0]) + sqr(d[1]) + sqr(d[2]));
        if (mag != 0.0f) {
#else
        mag = sqrtf(sqr(d[0]) + sqr(d[1]) + sqr(d[2]));
        if (mag != 0.0f) {
            // Normalizing
            mag = (1.0f / mag);
#endif
            vec3f_mul_f32(d, mag);
        } else {
            vec3f_set(d, 0.0f, 1.0f, 0.0f);
        }
        o->oTiltingPyramidMarioOnPlatform = TRUE;
    } else {
        vec3f_set(d, 0.0f, 1.0f, 0.0f);
        o->oTiltingPyramidMarioOnPlatform = FALSE;
    }
    // Approach the normals by 0.01f towards the new goal, then create a transform matrix and orient the object. 
    // Outside of the other conditionals since it needs to tilt regardless of whether Mario is on.
    o->oTiltingPyramidNormalX = approach_f32_by_increment(o->oTiltingPyramidNormalX, d[0], 0.01f);
    o->oTiltingPyramidNormalY = approach_f32_by_increment(o->oTiltingPyramidNormalY, d[1], 0.01f);
    o->oTiltingPyramidNormalZ = approach_f32_by_increment(o->oTiltingPyramidNormalZ, d[2], 0.01f);
    create_transform_from_normals(*transform, o->oTiltingPyramidNormalX, o->oTiltingPyramidNormalY, o->oTiltingPyramidNormalZ);
    // If Mario is on the platform, adjust his position for the platform tilt.
    if (o->oTiltingPyramidMarioOnPlatform) {
        linear_mtxf_mul_vec3f(*transform, posAfterRotation, dist);
#ifndef PLATFORM_DISPLACEMENT_2
        mx += (posAfterRotation[0] - posBeforeRotation[0]);
        my += (posAfterRotation[1] - posBeforeRotation[1]);
        mz += (posAfterRotation[2] - posBeforeRotation[2]);
        set_mario_pos(mx, my, mz);
#endif
    }
    o->header.gfx.throwMatrix = transform;
}
