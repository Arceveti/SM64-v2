#include "config.h"

/**
 * This is the behavior file for the tilting inverted pyramids in BitFS/LLL.
 * The object essentially just tilts and moves Mario with it.
 */

/**
 * Initialize the object's transform matrix with Y being up.
 */
void bhv_platform_normals_init(void) {
    Mat4 *transform = &o->transform;
    vec3_copy(&o->oTiltingPyramidNormalVec, gVec3fY);
    mtxf_transform_from_normals(*transform, &o->oPosVec, 0.0f, 1.0f, 0.0f);
}

/**
 * Main behavior for the tilting pyramids in LLL/BitFS. These platforms calculate rough normals from Mario's position,
 * then gradually tilt back moving Mario with them.
 */
void bhv_tilting_inverted_pyramid_loop(void) {
    Vec3f d;
#ifndef PLATFORM_DISPLACEMENT_2
    Vec3f dist;
    Vec3f posBeforeRotation;
    Vec3f posAfterRotation;
    // Mario's position
    f32 mx, my, mz;
#endif
    Mat4 *transform = &o->transform;
    if (gMarioObject->platform == o) {
#ifndef PLATFORM_DISPLACEMENT_2
        get_mario_pos(&mx, &my, &mz);
        vec3_diff(dist, &gMarioObject->oPosVec, &o->oPosVec);
        linear_mtxf_mul_vec3f(*transform, posBeforeRotation, dist);
#endif
        vec3_diff(d, &gMarioObject->oPosVec, &o->oPosVec);
        vec3f_normalize(d);
        o->oTiltingPyramidMarioOnPlatform = TRUE;
    } else {
        vec3_copy(d, gVec3fY);
        o->oTiltingPyramidMarioOnPlatform = FALSE;
    }
    // Approach the normals by 0.01f towards the new goal, then create a transform matrix and orient the object.
    // Outside of the other conditionals since it needs to tilt regardless of whether Mario is on.
    approach_f32_ptr(&o->oTiltingPyramidNormalX, d[0], 0.01f);
    approach_f32_ptr(&o->oTiltingPyramidNormalY, d[1], 0.01f);
    approach_f32_ptr(&o->oTiltingPyramidNormalZ, d[2], 0.01f);
    mtxf_transform_from_normals(*transform, &o->oPosVec, o->oTiltingPyramidNormalX, o->oTiltingPyramidNormalY, o->oTiltingPyramidNormalZ);
#ifndef PLATFORM_DISPLACEMENT_2
    // If Mario is on the platform, adjust his position for the platform tilt.
    if (o->oTiltingPyramidMarioOnPlatform) {
        linear_mtxf_mul_vec3f(*transform, posAfterRotation, dist);
        mx += (posAfterRotation[0] - posBeforeRotation[0]);
        my += (posAfterRotation[1] - posBeforeRotation[1]);
        mz += (posAfterRotation[2] - posBeforeRotation[2]);
        set_mario_pos(mx, my, mz);
    }
#endif
    o->header.gfx.throwMatrix = transform;
}
