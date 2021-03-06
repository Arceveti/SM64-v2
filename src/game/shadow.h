#pragma once

#include <PR/ultratypes.h>
#include <PR/gbi.h>
#include "types.h"

/**
 * Shadow types. Shadows are circles, squares, or hardcoded rectangles, and
 * can be composed of either 4 or 9 vertices.
 */
enum ShadowType
{
    SHADOW_CIRCLE_9_VERTS             =  0,
    SHADOW_CIRCLE_4_VERTS             =  1,
    SHADOW_CIRCLE_4_VERTS_FLAT_UNUSED =  2,
    SHADOW_SQUARE_PERMANENT           = 10,
    SHADOW_SQUARE_SCALABLE            = 11,
    SHADOW_SQUARE_TOGGLABLE           = 12,
    /**
     * This defines an offset after which rectangular shadows with custom
     * widths and heights can be defined.
     */
    SHADOW_RECTANGLE_HARDCODED_OFFSET = 50,
    SHADOW_CIRCLE_PLAYER              = 99
};

/**
 * Flag for if Mario is on a flying carpet.
 */
extern Bool8 sMarioOnFlyingCarpet;

/**
 * The surface type below the current shadow.
 */
extern SurfaceType sSurfaceTypeBelowShadow;

/**
 * Flag for if the current shadow is above water or lava.
 */
extern Bool8 gShadowAboveWaterOrLava;
extern Bool8 gShadowAboveCustomWater;

/**
 * Flag for if Mario is on ice or a flying carpet.
 */
extern Bool8 gMarioOnIceOrCarpet;

/**
 * Given the (x, y, z) location of an object, create a shadow below that object
 * with the given initial solidity and "shadowType" (described above).
 */
Gfx *create_shadow_below_xyz(Vec3f pos, s16 shadowScale, Alpha shadowSolidity, s8 shadowType);
