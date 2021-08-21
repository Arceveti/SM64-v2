#include <PR/ultratypes.h>

#include "sm64.h"
#include "game/debug.h"
#include "game/level_update.h"
#include "game/mario.h"
#include "game/object_list_processor.h"
#include "surface_collision.h"
#include "surface_load.h"
#include "math_util.h"
#ifdef PUPPYPRINT
#include "game/puppyprint.h"
#endif

/**************************************************
 *                      WALLS                     *
 **************************************************/

/**
 * Iterate through the list of walls until all walls are checked and
 * have given their wall push.
 */

#ifdef BETTER_WALL_COLLISION
static s32 find_wall_collisions_from_list(struct SurfaceNode *surfaceNode, struct WallCollisionData *data) {
    const f32 corner_threshold = (-0.9f);
    register struct Surface *surf;
    register f32 offset;
    register f32 radius = data->radius;
    register f32 x      =  data->x;
    register f32 y      = (data->y + data->offsetY);
    register f32 z      =  data->z;
    register f32 v0x, v0y, v0z;
    register f32 v1x, v1y, v1z;
    register f32 v2x, v2y, v2z;
    register f32 d00, d01, d11, d20, d21;
    register f32 invDenom;
    register f32 v, w;
    register f32 margin_radius = (radius - 1.0f);
    register SurfaceType type = SURFACE_DEFAULT;
    s32 numCols = 0;
 #if EXTENDED_BOUNDS_MODE > 1
    const float down_scale = (1.0f / WORLD_SCALE);
    radius        *= down_scale;
    x             *= down_scale;
    y             *= down_scale;
    z             *= down_scale;
    margin_radius *= down_scale;
 #endif
    // Max collision radius = 200
    if (radius > 200.0f) radius = 200.0f;
    // Stay in this loop until out of walls.
    while (surfaceNode != NULL) {
        surf        = surfaceNode->surface;
        surfaceNode = surfaceNode->next;
        type        = surf->type;
        // Exclude a large number of walls immediately to optimize.
 #ifdef NEW_WATER_SURFACES
        if ((type == SURFACE_NEW_WATER) || (type == SURFACE_NEW_WATER_BOTTOM)) continue;
 #endif
        // Determine if checking for the camera or not.
        if (gCheckingSurfaceCollisionsForCamera) {
            if (surf->flags & SURFACE_FLAG_NO_CAM_COLLISION) continue;
        } else {
            // Ignore camera only surfaces.
            if (type == SURFACE_CAMERA_BOUNDARY) continue;
            // If an object can pass through a vanish cap wall, pass through.
            if ((type == SURFACE_VANISH_CAP_WALLS) && (gCurrentObject != NULL)) {
                // If an object can pass through a vanish cap wall, pass through.
                if (gCurrentObject->activeFlags & ACTIVE_FLAG_MOVE_THROUGH_GRATE) continue;
                // If Mario has a vanish cap, pass through the vanish cap wall.
                if ((gCurrentObject == gMarioObject) && (gMarioState->flags & MARIO_VANISH_CAP)) continue;
            }
        }
        if ((y < surf->lowerY) || (y > surf->upperY)) continue;
 #ifdef UNDERWATER_STEEP_FLOORS_AS_WALLS
        if (gIncludeSteepFloorsInWallCollisionCheck && (surf->normal.y > MIN_UNDERWATER_FLOOR_NORMAL_Y)) continue;
 #endif
        offset = ((surf->normal.x * x) + (surf->normal.y * y) + (surf->normal.z * z) + surf->originOffset);
        if ((offset < -radius) || (offset > radius)) continue;
        v0x = (f32)(surf->vertex2[0] -      surf->vertex1[0]);
        v0y = (f32)(surf->vertex2[1] -      surf->vertex1[1]);
        v0z = (f32)(surf->vertex2[2] -      surf->vertex1[2]);
        v1x = (f32)(surf->vertex3[0] -      surf->vertex1[0]);
        v1y = (f32)(surf->vertex3[1] -      surf->vertex1[1]);
        v1z = (f32)(surf->vertex3[2] -      surf->vertex1[2]);
        v2x =                      x - (f32)surf->vertex1[0];
        v2y =                      y - (f32)surf->vertex1[1];
        v2z =                      z - (f32)surf->vertex1[2];
        // Face
        // d00 = ((v0x * v0x) + (v0y * v0y) + (v0z * v0z));
        d00 = (sqr(v0x) + sqr(v0y) + sqr(v0z));
        d01 = ((v0x * v1x) + (v0y * v1y) + (v0z * v1z));
        // d11 = ((v1x * v1x) + (v1y * v1y) + (v1z * v1z));
        d11 = (sqr(v1x) + sqr(v1y) + sqr(v1z));
        d20 = ((v2x * v0x) + (v2y * v0y) + (v2z * v0z));
        d21 = ((v2x * v1x) + (v2y * v1y) + (v2z * v1z));
        invDenom = (1.0f / ((d00 * d11) - (d01 * d01)));
        v = (((d11 * d20) - (d01 * d21)) * invDenom);
        if ((v < 0.0f) || (v > 1.0f)) goto edge_1_2;
        w = (((d00 * d21) - (d01 * d20)) * invDenom);
        if ((w < 0.0f) || (w > 1.0f) || ((v + w) > 1.0f)) goto edge_1_2;
        x += (surf->normal.x * (radius - offset));
        z += (surf->normal.z * (radius - offset));
        goto hasCollision;
    edge_1_2:
        if (offset < 0) continue;
        // Edge 1-2
        if (v0y != 0.0f) {
            v = (v2y / v0y);
            if ((v < 0.0f) || (v > 1.0f)) goto edge_1_3;
            d00 = ((v0x * v) - v2x);
            d01 = ((v0z * v) - v2z);
            invDenom = sqrtf(sqr(d00) + sqr(d01));
            offset   = (invDenom - margin_radius);
            if (offset > 0.0f) goto edge_1_3;
            invDenom = (offset / invDenom); // fast invsqrt?
            x += (d00 *= invDenom);
            z += (d01 *= invDenom);
            margin_radius += 0.01f;
            if ((d00 * surf->normal.x) + (d01 * surf->normal.z) < (corner_threshold * offset)) {
                continue;
            } else {
                goto hasCollision;
            }
        }
    edge_1_3:
        // Edge 1-3
        if (v1y != 0.0f) {
            v = (v2y / v1y);
            if ((v < 0.0f) || (v > 1.0f)) goto edge_2_3;
            d00 = ((v1x * v) - v2x);
            d01 = ((v1z * v) - v2z);
            invDenom = sqrtf(sqr(d00) + sqr(d01));
            offset   = (invDenom - margin_radius);
            if (offset > 0.0f) goto edge_2_3;
            invDenom = (offset / invDenom); // fast invsqrt?
            x += (d00 *= invDenom);
            z += (d01 *= invDenom);
            margin_radius += 0.01f;
            if ((d00 * surf->normal.x) + (d01 * surf->normal.z) < (corner_threshold * offset)) {
                continue;
            } else {
                goto hasCollision;
            }
        }
    edge_2_3:
        // Edge 2-3
        v1x = (f32)(surf->vertex3[0] -      surf->vertex2[0]);
        v1y = (f32)(surf->vertex3[1] -      surf->vertex2[1]);
        v1z = (f32)(surf->vertex3[2] -      surf->vertex2[2]);
        v2x =                      x - (f32)surf->vertex2[0];
        v2y =                      y - (f32)surf->vertex2[1];
        v2z =                      z - (f32)surf->vertex2[2];
        if (v1y != 0.0f) {
            v = (v2y / v1y);
            if ((v < 0.0f) || (v > 1.0f)) continue;
            d00 = ((v1x * v) - v2x);
            d01 = ((v1z * v) - v2z);
            invDenom = sqrtf(sqr(d00) + sqr(d01));
            offset   = (invDenom - margin_radius);
            if (offset > 0.0f) continue;
            invDenom = (offset / invDenom); // fast invsqrt?
            x += (d00 *= invDenom);
            z += (d01 *= invDenom);
            margin_radius += 0.01f;
            if ((d00 * surf->normal.x) + (d01 * surf->normal.z) < (corner_threshold * offset)) {
                continue;
            } else {
                goto hasCollision;
            }
        } else {
            continue;
        }
    hasCollision:
        if (data->numWalls < MAX_REFEREMCED_WALLS) data->walls[data->numWalls++] = surf;
        numCols++;
    }
 #if EXTENDED_BOUNDS_MODE > 1
    x *= WORLD_SCALE;
    y *= WORLD_SCALE;
    z *= WORLD_SCALE;
 #endif
    data->x = x;
    data->z = z;
    return numCols;
}
#else
static s32 find_wall_collisions_from_list(struct SurfaceNode *surfaceNode, struct WallCollisionData *data) {
    register struct Surface *surf;
    register f32 offset;
    register f32 radius = data->radius;
    // these are f32 in vanilla
    register s32 x = data->x;
    register s32 y = data->y + data->offsetY;
    register s32 z = data->z;
    register s32 w1, w2, w3;
    register s32 y1, y2, y3;
    s32 numCols = 0;
    SurfaceType type = SURFACE_DEFAULT;
    // Max collision radius = 200
    if (radius > 200.0f) radius = 200.0f;
    // Stay in this loop until out of walls.
    while (surfaceNode != NULL) {
        surf        = surfaceNode->surface;
        surfaceNode = surfaceNode->next;
        type        = surf->type;
 #ifdef NEW_WATER_SURFACES
        if ((type == SURFACE_NEW_WATER) || (type == SURFACE_NEW_WATER_BOTTOM)) continue;
 #endif
        // Determine if checking for the camera or not.
        if (gCheckingSurfaceCollisionsForCamera) {
            if (surf->flags & SURFACE_FLAG_NO_CAM_COLLISION) continue;
        } else {
            // Ignore camera only surfaces.
            if (type == SURFACE_CAMERA_BOUNDARY) continue;
            // If an object can pass through a vanish cap wall, pass through.
            if ((type == SURFACE_VANISH_CAP_WALLS) && (gCurrentObject != NULL)) {
                // If an object can pass through a vanish cap wall, pass through.
                if (gCurrentObject->activeFlags & ACTIVE_FLAG_MOVE_THROUGH_GRATE) continue;
                // If Mario has a vanish cap, pass through the vanish cap wall.
                if ((gCurrentObject == gMarioObject) && (gMarioState->flags & MARIO_VANISH_CAP)) continue;
            }
        }
        if ((y < surf->lowerY) || (y > surf->upperY)) continue;
        // Exclude a large number of walls immediately to optimize.
        offset = ((surf->normal.x * x) + (surf->normal.y * y) + (surf->normal.z * z) + surf->originOffset);
        if ((offset < -radius) || (offset > radius))  continue;
        //  (Quantum Tunneling) Due to issues with the vertices walls choose
        //  and the fact they are floating point, certain floating point positions
        //  along the seam of two walls may collide with neither wall or both walls.
        y1 = surf->vertex1[1]; y2 = surf->vertex2[1]; y3 = surf->vertex3[1];
        if (surf->flags & SURFACE_FLAG_X_PROJECTION) {
            w1 = -surf->vertex1[2]; w2 = -surf->vertex2[2]; w3 = -surf->vertex3[2];
            if (surf->normal.x > 0.0f) {
                if (((y1 - y) * (w2 - w1)) - ((w1 - -z) * (y2 - y1)) > 0) continue;
                if (((y2 - y) * (w3 - w2)) - ((w2 - -z) * (y3 - y2)) > 0) continue;
                if (((y3 - y) * (w1 - w3)) - ((w3 - -z) * (y1 - y3)) > 0) continue;
            } else {
                if (((y1 - y) * (w2 - w1)) - ((w1 - -z) * (y2 - y1)) < 0) continue;
                if (((y2 - y) * (w3 - w2)) - ((w2 - -z) * (y3 - y2)) < 0) continue;
                if (((y3 - y) * (w1 - w3)) - ((w3 - -z) * (y1 - y3)) < 0) continue;
            }
        } else {
            w1 =  surf->vertex1[0]; w2 =  surf->vertex2[0]; w3 =  surf->vertex3[0];
            if (surf->normal.z > 0.0f) {
                if (((y1 - y) * (w2 - w1)) - ((w1 -  x) * (y2 - y1)) > 0) continue;
                if (((y2 - y) * (w3 - w2)) - ((w2 -  x) * (y3 - y2)) > 0) continue;
                if (((y3 - y) * (w1 - w3)) - ((w3 -  x) * (y1 - y3)) > 0) continue;
            } else {
                if (((y1 - y) * (w2 - w1)) - ((w1 -  x) * (y2 - y1)) < 0) continue;
                if (((y2 - y) * (w3 - w2)) - ((w2 -  x) * (y3 - y2)) < 0) continue;
                if (((y3 - y) * (w1 - w3)) - ((w3 -  x) * (y1 - y3)) < 0) continue;
            }
        }
        data->x += (surf->normal.x * (radius - offset));
        x       += (surf->normal.x * (radius - offset));
        data->z += (surf->normal.z * (radius - offset));
        z       += (surf->normal.z * (radius - offset));
        // x = data->x;
        // z = data->z;
        if (data->numWalls < MAX_REFEREMCED_WALLS) data->walls[data->numWalls++] = surf;
        numCols++;
    }
    return numCols;
}
#endif

/**
 * Formats the position and wall search for find_wall_collisions.
 */
s32 f32_find_wall_collision(f32 *xPtr, f32 *yPtr, f32 *zPtr, f32 offsetY, f32 radius) {
    struct WallCollisionData collision;
    s32 numCollisions  = 0;
    collision.offsetY  = offsetY;
    collision.radius   = radius;
    collision.x        = *xPtr;
    collision.y        = *yPtr;
    collision.z        = *zPtr;
    collision.numWalls = 0;
    numCollisions      = find_wall_collisions(&collision);
    *xPtr              = collision.x;
    *yPtr              = collision.y;
    *zPtr              = collision.z;
    return numCollisions;
}

/**
 * Find wall collisions and receive their push.
 */
s32 find_wall_collisions(struct WallCollisionData *colData) {
    struct SurfaceNode *node;
    s32 numCollisions = 0;
    s16 x             = colData->x;
    s16 z             = colData->z;
#ifdef PUPPYPRINT
    OSTime first      = osGetTime();
#endif
    colData->numWalls = 0;
    if ((x <= -LEVEL_BOUNDARY_MAX)
     || (x >=  LEVEL_BOUNDARY_MAX)
     || (z <= -LEVEL_BOUNDARY_MAX)
     || (z >=  LEVEL_BOUNDARY_MAX)) return numCollisions;
    // World (level) consists of a 16x16 grid. Find where the collision is on
    // the grid (round toward -inf)
    register const CellIndex cellX = (((x + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX);
    register const CellIndex cellZ = (((z + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX);
    // Check for surfaces belonging to objects.
    node = gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_WALLS].next;
    numCollisions += find_wall_collisions_from_list(node, colData);
    // Check for surfaces that are a part of level geometry.
    node = gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_WALLS].next;
    numCollisions += find_wall_collisions_from_list(node, colData);
#ifdef UNDERWATER_STEEP_FLOORS_AS_WALLS
    if (gIncludeSteepFloorsInWallCollisionCheck) {
        // Check for surfaces belonging to objects.
        node = gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_FLOORS].next;
        numCollisions += find_wall_collisions_from_list(node, colData);
        // Check for surfaces that are a part of level geometry.
        node = gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_FLOORS].next;
        numCollisions += find_wall_collisions_from_list(node, colData);
    }
#endif
    // Increment the debug tracker.
    gNumCalls.wall++;
    return numCollisions;
}

/**
 * Check `pos` for collisions within `radius`, and update `pos`
 * Used for the camera
 *
 * @return the number of collisions found
 */
s32 collide_with_walls(Vec3f pos, f32 offsetY, f32 radius) {
    struct WallCollisionData collisionData;
    struct Surface *wall = NULL;
    register f32 normX, normY, normZ;
    register f32 originOffset, offset, offsetAbsolute;
    Vec3f newPos[4];
    s32 i;
    s32 numCollisions     = 0;
    collisionData.x       = pos[0];
    collisionData.y       = pos[1];
    collisionData.z       = pos[2];
    collisionData.radius  = radius;
    collisionData.offsetY = offsetY;
    numCollisions         = find_wall_collisions(&collisionData);
    if (numCollisions != 0) {
        for (i = 0; i < collisionData.numWalls; i++) {
            wall = collisionData.walls[collisionData.numWalls - 1];
            vec3f_copy(newPos[i], pos);
            normX          = wall->normal.x;
            normY          = wall->normal.y;
            normZ          = wall->normal.z;
            originOffset   = wall->originOffset;
            offset         = ((normX * newPos[i][0]) + (normY * newPos[i][1]) + (normZ * newPos[i][2]) + originOffset);
            offsetAbsolute = absf(offset);
            if (offsetAbsolute < radius) {
                newPos[i][0] += (normX * (radius - offset));
                newPos[i][2] += (normZ * (radius - offset));
                vec3f_copy(pos, newPos[i]);
            }
        }
    }
#ifdef PUPPYPRINT
    collisionTime[perfIteration] += (osGetTime() - first);
#endif
    return numCollisions;
}


/**************************************************
 *                     CEILINGS                   *
 **************************************************/

// Find the height of the surface at a given location
#ifdef BETTER_WALL_COLLISION
static f32 get_surface_height_at_location(f32 x, f32 z, struct Surface *surf) {
#else
static f32 get_surface_height_at_location(s32 x, s32 z, struct Surface *surf) {
#endif
    return -((x * surf->normal.x) + (surf->normal.z * z) + surf->originOffset) / surf->normal.y;
}

#ifdef BETTER_WALL_COLLISION
void add_ceil_margin(f32 *x, f32 *z, Vec3s target1, Vec3s target2, f32 margin) {
    register f32 diff_x   = (target1[0] - *x + target2[0] - *x);
    register f32 diff_z   = (target1[2] - *z + target2[2] - *z);
#ifdef FAST_INVSQRT
    register f32 invDenom = margin * Q_rsqrtf(sqr(diff_x) + sqr(diff_z));
#else
    register f32 invDenom = margin / sqrtf(sqr(diff_x) + sqr(diff_z));
#endif
    *x += (diff_x * invDenom);
    *z += (diff_z * invDenom);
}
#endif

/**
 * Iterate through the list of ceilings and find the first ceiling over a given point.
 */

#ifdef BETTER_WALL_COLLISION
static struct Surface *find_ceil_from_list(struct SurfaceNode *surfaceNode, f32 x, f32 y, f32 z, f32 *pheight) {
    const f32 margin = 1.5f;
#else
static struct Surface *find_ceil_from_list(struct SurfaceNode *surfaceNode, s32 x, s32 y, s32 z, f32 *pheight) {
#endif
    register struct Surface *surf;
    f32 x1, z1, x2, z2, x3, z3;
    f32 height;
    SurfaceType type = SURFACE_DEFAULT;
    struct Surface *ceil = NULL;
    // *pheight = CELL_HEIGHT_LIMIT;
    // Stay in this loop until out of ceilings.
    while (surfaceNode != NULL) {
        surf        = surfaceNode->surface;
        surfaceNode = surfaceNode->next;
        type        = surf->type;
        // Determine if checking for the camera or not.
        if (gCheckingSurfaceCollisionsForCamera) {
            if (surf->flags & SURFACE_FLAG_NO_CAM_COLLISION) continue;
        // Ignore camera only surfaces.
        } else if (type == SURFACE_CAMERA_BOUNDARY) {
            continue;
        }
#ifdef NEW_WATER_SURFACES
        if ((type == SURFACE_NEW_WATER) || (type == SURFACE_NEW_WATER_BOTTOM)) continue;
#endif
        x1 = surf->vertex1[0];
        z1 = surf->vertex1[2];
#ifdef BETTER_WALL_COLLISION
        if (type != SURFACE_HANGABLE) add_ceil_margin(&x1, &z1, surf->vertex2, surf->vertex3, margin);
#endif
        z2 = surf->vertex2[2];
        x2 = surf->vertex2[0];
#ifdef BETTER_WALL_COLLISION
        if (type != SURFACE_HANGABLE) add_ceil_margin(&x2, &z2, surf->vertex3, surf->vertex1, margin);
#endif
        // Checking if point is in bounds of the triangle laterally.
        if ((z1 - z) * (x2 - x1) - (x1 - x) * (z2 - z1) > 0) continue;
        // Slight optimization by checking these later.
        x3 = surf->vertex3[0];
        z3 = surf->vertex3[2];
#ifdef BETTER_WALL_COLLISION
        if (type != SURFACE_HANGABLE) add_ceil_margin(&x3, &z3, surf->vertex1, surf->vertex2, margin);
#endif
        if ((z2 - z) * (x3 - x2) - (x2 - x) * (z3 - z2) > 0) continue;
        if ((z3 - z) * (x1 - x3) - (x3 - x) * (z1 - z3) > 0) continue;
        // Find the ceil height at the specific point.
        height = get_surface_height_at_location(x, z, surf);
        if (height >= *pheight) continue;
        // if (y > (height + 78.0f)) continue;
        // Checks for ceiling interaction
        if (y > height      ) continue;
        if (y > surf->upperY) continue;
        *pheight = height;
        ceil     = surf;
        if (height == y) break;
    }
    return ceil;
}

/**
 * Find the lowest ceiling above a given position and return the height.
 */
f32 find_ceil(f32 xPos, f32 yPos, f32 zPos, struct Surface **pceil) {
    struct Surface *ceil, *dynamicCeil;
    struct SurfaceNode *surfaceList;
    f32 height        = CELL_HEIGHT_LIMIT;
    f32 dynamicHeight = CELL_HEIGHT_LIMIT;
#ifdef PUPPYPRINT
    OSTime first = osGetTime();
#endif
    *pceil            = NULL;
#ifdef BETTER_WALL_COLLISION
    if ((xPos <= -LEVEL_BOUNDARY_MAX)
     || (xPos >=  LEVEL_BOUNDARY_MAX)
     || (zPos <= -LEVEL_BOUNDARY_MAX)
     || (zPos >=  LEVEL_BOUNDARY_MAX)) return height;
    // Each level is split into cells to limit load, find the appropriate cell.
    register const CellIndex cellX = ((((CellIndex)xPos + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX);
    register const CellIndex cellZ = ((((CellIndex)zPos + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX);
    // Check for surfaces that are a part of level geometry.
    surfaceList = gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_CEILS].next;
    ceil        = find_ceil_from_list(surfaceList, xPos, yPos, zPos, &height);
    dynamicHeight = height;
    // Check for surfaces belonging to objects.
    surfaceList = gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_CEILS].next;
    dynamicCeil = find_ceil_from_list(surfaceList, xPos, yPos, zPos, &dynamicHeight);
#else
    // (Parallel Universes?) Because position is casted to an s16, reaching higher
    // float locations  can return ceilings despite them not existing there.
    // (Dynamic ceilings will unload due to the range.)
    s32 x = xPos;
    s32 y = yPos;
    s32 z = zPos;
    // Check if position is within level bounds
    if ((x <= -LEVEL_BOUNDARY_MAX)
     || (x >=  LEVEL_BOUNDARY_MAX)
     || (z <= -LEVEL_BOUNDARY_MAX)
     || (z >=  LEVEL_BOUNDARY_MAX)) return height;
    // Each level is split into cells to limit load, find the appropriate cell.
    register const CellIndex cellX = (((x + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX);
    register const CellIndex cellZ = (((z + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX);
    // Check for surfaces that are a part of level geometry.
    surfaceList = gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_CEILS].next;
    ceil = find_ceil_from_list(surfaceList, x, y, z, &height);
    dynamicHeight = height;
    // Check for surfaces belonging to objects.
    surfaceList = gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_CEILS].next;
    dynamicCeil = find_ceil_from_list(surfaceList, x, y, z, &dynamicHeight);
#endif
    // Use the dynamic ceiling if it is lower
    if (dynamicHeight < height) {
        ceil   = dynamicCeil;
        height = dynamicHeight;
    }
    *pceil = ceil;
    // Increment the debug tracker.
    gNumCalls.ceil++;
#ifdef PUPPYPRINT
    collisionTime[perfIteration] += (osGetTime() - first);
#endif
    return height;
}

/**************************************************
 *                     FLOORS                     *
 **************************************************/

Bool32 floor_type_exists_in_current_cell(f32 xPos, f32 zPos, SurfaceType type, Bool32 dynamic) {
    register const CellIndex cellX = ((((CellIndex)xPos + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX);
    register const CellIndex cellZ = ((((CellIndex)zPos + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX);
    struct SurfaceNode *surfaceNode;
    surfaceNode = gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_FLOORS].next;
    // Check for surfaces that are a part of level geometry.
    while (surfaceNode != NULL) {
        if (surfaceNode->surface->type == type) return TRUE;
        surfaceNode = surfaceNode->next;
    }
    if (dynamic) {
        // Check for surfaces belonging to objects.
        surfaceNode = gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_FLOORS].next;
        while (surfaceNode != NULL) {
            if (surfaceNode->surface->type == type) return TRUE;
            surfaceNode = surfaceNode->next;
        }
    }
    return FALSE;
}

/**
 * Basically a local variable that passes through floor geo info.
 */
struct FloorGeometry sFloorGeo;

#ifdef BETTER_WALL_COLLISION
static s32 check_within_floor_triangle_bounds(f32 x, f32 z, struct Surface *surf) {
    register f32 x1 = surf->vertex1[0];
    register f32 z1 = surf->vertex1[2];
    register f32 x2 = surf->vertex2[0];
    register f32 z2 = surf->vertex2[2];
    // Checking if point is in bounds of the triangle laterally.
    if ((z1 - z) * (x2 - x1) - (x1 - x) * (z2 - z1) < 0.0f) return FALSE; // 12
    // Slight optimization by checking these later.
    register f32 x3 = surf->vertex3[0];
    register f32 z3 = surf->vertex3[2];
    if ((z2 - z) * (x3 - x2) - (x2 - x) * (z3 - z2) < 0.0f) return FALSE; // 23
    if ((z3 - z) * (x1 - x3) - (x3 - x) * (z1 - z3) < 0.0f) return FALSE; // 31
    return TRUE;
}
#else
static s32 check_within_floor_triangle_bounds(s32 x, s32 z, struct Surface *surf) {
    register s32 x1 = surf->vertex1[0];
    register s32 z1 = surf->vertex1[2];
    register s32 x2 = surf->vertex2[0];
    register s32 z2 = surf->vertex2[2];
    // Checking if point is in bounds of the triangle laterally.
    if ((z1 - z) * (x2 - x1) - (x1 - x) * (z2 - z1) < 0) return FALSE; // 12
    // Slight optimization by checking these later.
    register s32 x3 = surf->vertex3[0];
    register s32 z3 = surf->vertex3[2];
    if ((z2 - z) * (x3 - x2) - (x2 - x) * (z3 - z2) < 0) return FALSE; // 23
    if ((z3 - z) * (x1 - x3) - (x3 - x) * (z1 - z3) < 0) return FALSE; // 31
    return TRUE;
}
#endif

/**
 * Return the floor height underneath (xPos, yPos, zPos) and populate `floorGeo`
 * with data about the floor's normal vector and origin offset. Also update
 * sFloorGeo.
 */
f32 find_floor_height_and_data(f32 xPos, f32 yPos, f32 zPos, struct FloorGeometry **floorGeo) {
    struct Surface *floor;
    f32 floorHeight = find_floor(xPos, yPos, zPos, &floor);
    *floorGeo = NULL;
    if (floor != NULL) {
        sFloorGeo.normalX      = floor->normal.x;
        sFloorGeo.normalY      = floor->normal.y;
        sFloorGeo.normalZ      = floor->normal.z;
        sFloorGeo.originOffset = floor->originOffset;
        *floorGeo              = &sFloorGeo;
    }
    return floorHeight;
}

/**
 * Iterate through the list of floors and find the highest floor above pheight and below y.
 */
#ifdef BETTER_WALL_COLLISION
static struct Surface *find_floor_from_list(struct SurfaceNode *surfaceNode, f32 x, f32 y, f32 z, f32 *pheight) {
#else
static struct Surface *find_floor_from_list(struct SurfaceNode *surfaceNode, s32 x, s32 y, s32 z, f32 *pheight) {
#endif
    register struct Surface *surf;
    f32 height;
    SurfaceType type = SURFACE_DEFAULT;
    struct Surface *floor = NULL;
    // Iterate through the list of floors until there are no more floors.
    while (surfaceNode != NULL) {
        surf        = surfaceNode->surface;
        surfaceNode = surfaceNode->next;
        type        = surf->type;
        // To prevent the Merry-Go-Round room from loading when Mario passes above the hole that leads
        // there, SURFACE_INTANGIBLE is used. This prevent the wrong room from loading, but can also allow
        // Mario to pass through.
        if (!gFindFloorIncludeSurfaceIntangible && (type == SURFACE_INTANGIBLE)) continue;
        // Determine if we are checking for the camera or not.
        if (gCheckingSurfaceCollisionsForCamera) {
#ifdef NEW_WATER_SURFACES
            if (surf->flags & SURFACE_FLAG_NO_CAM_COLLISION || type == SURFACE_NEW_WATER || type == SURFACE_NEW_WATER_BOTTOM) continue;
#else
            if (surf->flags & SURFACE_FLAG_NO_CAM_COLLISION) continue;
#endif
        // If we are not checking for the camera, ignore camera only floors.
        } else if (type == SURFACE_CAMERA_BOUNDARY) continue;
        // Check if point is within tri laterally
        if (!check_within_floor_triangle_bounds(x, z, surf)) continue;
        // Get the height of the point on the tri
        height = get_surface_height_at_location(x, z, surf);
        // Ignore if the height is below or the same as the current surface height, without the buffer
        if (height <= *pheight) continue;
        // Check if the original location is more than 78 units above the floor height
        if (y < (height - 78.0f)) continue;
        // Set current surface and height for next iteration
        *pheight = height;
        floor    = surf;
        // Exit the loop if it's not possible for another floor to be closer to the original point
        if (y == (height - 78.0f)) break;
    }
    return floor;
}

#ifdef NEW_WATER_SURFACES
/**
 * Iterate through the list of water floors and find the first water floor under a given point.
 */
struct Surface *find_water_floor_from_list(struct SurfaceNode *surfaceNode, s32 x, s32 y, s32 z, f32 *pheight, s32 *pBottomHeight) {
    register struct Surface *surf;
    struct Surface *floor = NULL;
    struct SurfaceNode *topSurfaceNode    = surfaceNode;
    struct SurfaceNode *bottomSurfaceNode = surfaceNode;
    s32 height          = FLOOR_LOWER_LIMIT;
    s32 bottomHeight    = FLOOR_LOWER_LIMIT;
    s32 topBottomHeight = FLOOR_LOWER_LIMIT;
    // Iterate through the list of water floors until there are no more water floors.
    while (bottomSurfaceNode != NULL) {
        s32 curBottomHeight = FLOOR_LOWER_LIMIT;
        surf                = bottomSurfaceNode->surface;
        bottomSurfaceNode   = bottomSurfaceNode->next;
        if (surf->type != SURFACE_NEW_WATER_BOTTOM || !check_within_floor_triangle_bounds(x, z, surf)) continue;
        curBottomHeight = get_surface_height_at_location(x, z, surf);
        // if (curBottomHeight <  (y - 78.0f)) continue;
        // if (curBottomHeight >= (y - 78.0f)) bottomHeight = curBottomHeight;
        if (curBottomHeight < y + 78.0f) {
            if (curBottomHeight > topBottomHeight) topBottomHeight = curBottomHeight;
            continue;
        }
        if (curBottomHeight >= (y + 78.0f)) bottomHeight = curBottomHeight;
    }
    // Iterate through the list of water tops until there are no more water tops.
    while (topSurfaceNode != NULL) {
        s32 curHeight  = FLOOR_LOWER_LIMIT;
        surf           = topSurfaceNode->surface;
        topSurfaceNode = topSurfaceNode->next;
        if (surf->type == SURFACE_NEW_WATER_BOTTOM || !check_within_floor_triangle_bounds(x, z, surf)) continue;
        curHeight = get_surface_height_at_location(x, z, surf);
        if ((bottomHeight != FLOOR_LOWER_LIMIT) && (curHeight > bottomHeight)) continue;
        if (curHeight > height) {
            height   = curHeight;
            *pheight = curHeight;
            floor    = surf;
        }
    }
    *pBottomHeight = topBottomHeight;
    return floor;
}
#endif

/**
 * Find the height of the highest floor below a point.
 */
f32 find_floor_height(f32 x, f32 y, f32 z) {
    struct Surface *floor;
    return find_floor(x, y, z, &floor);
}

/**
 * Find the highest dynamic floor under a given position. Perhaps originally static
 * and dynamic floors were checked separately.
 */
f32 unused_find_dynamic_floor(f32 xPos, f32 yPos, f32 zPos, struct Surface **pfloor) {
    struct SurfaceNode *surfaceList;
    struct Surface *floor;
    f32 floorHeight = FLOOR_LOWER_LIMIT;
    // Each level is split into cells to limit load, find the appropriate cell.
    register const CellIndex cellX = (((CellIndex)xPos + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX;
    register const CellIndex cellZ = (((CellIndex)zPos + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX;
    surfaceList              = gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_FLOORS].next;
    floor                    = find_floor_from_list(surfaceList, xPos, yPos, zPos, &floorHeight);
    *pfloor                  = floor;
    return floorHeight;
}

/**
 * Find the highest floor under a given position and return the height.
 */
f32 find_floor(f32 xPos, f32 yPos, f32 zPos, struct Surface **pfloor) {
#ifdef PUPPYPRINT
    OSTime first = osGetTime();
#endif
    struct Surface *floor, *dynamicFloor;
    struct SurfaceNode *surfaceList;
    f32 height        = FLOOR_LOWER_LIMIT;
    f32 dynamicHeight = FLOOR_LOWER_LIMIT;
#ifdef BETTER_WALL_COLLISION
    *pfloor = NULL;
    // Exclude floors outside of level boundaries
    if ((xPos <= -LEVEL_BOUNDARY_MAX)
     || (xPos >=  LEVEL_BOUNDARY_MAX)
     || (zPos <= -LEVEL_BOUNDARY_MAX)
     || (zPos >=  LEVEL_BOUNDARY_MAX)) return height;
    // Each level is split into cells to limit load, find the appropriate cell.
    register const CellIndex cellX = ((((CellIndex)xPos + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX);
    register const CellIndex cellZ = ((((CellIndex)zPos + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX);
    // Check for surfaces that are a part of level geometry.
    surfaceList  = gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_FLOORS].next;
    floor        = find_floor_from_list(surfaceList, xPos, yPos, zPos, &height);
    if (!gFindFloorExcludeDynamic) {
        // In the next check, only check for floors higher than the previous check
        dynamicHeight = height;
        // Check for surfaces belonging to objects.
        surfaceList  = gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_FLOORS].next;
        dynamicFloor = find_floor_from_list(surfaceList, xPos, yPos, zPos, &dynamicHeight);
#else
    // (Parallel Universes) Because position is casted to an s16, reaching higher
    // float locations  can return floors despite them not existing there.
    // (Dynamic floors will unload due to the range.)
    s32 x = xPos;
    s32 y = yPos;
    s32 z = zPos;
    *pfloor = NULL;
    // Check if position is within level bounds
    if ((x <= -LEVEL_BOUNDARY_MAX)
     || (x >=  LEVEL_BOUNDARY_MAX)
     || (z <= -LEVEL_BOUNDARY_MAX)
     || (z >=  LEVEL_BOUNDARY_MAX)) {
#ifdef PUPPYPRINT
        collisionTime[perfIteration] += (osGetTime() - first);
#endif
        return height;
    }
    // Each level is split into cells to limit load, find the appropriate cell.
    register const CellIndex cellX = (((x + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX);
    register const CellIndex cellZ = (((z + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX);
    // Check for surfaces that are a part of level geometry.
    surfaceList   = gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_FLOORS].next;
    floor         = find_floor_from_list(surfaceList, x, y, z, &height);
    if (!gFindFloorExcludeDynamic) {
        // In the next check, only check for floors higher than the previous check
        dynamicHeight = height;
        // Check for surfaces belonging to objects.
        surfaceList   = gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_FLOORS].next;
        dynamicFloor  = find_floor_from_list(surfaceList, x, y, z, &dynamicHeight);
#endif
        // Use the dynamic floor if it's higher
        if (dynamicHeight > height) {
            floor  = dynamicFloor;
            height = dynamicHeight;
        }
    }
    // If a floor was missed, increment the debug counter.
    if (floor == NULL) gNumFindFloorMisses++;
    *pfloor = floor;
    // To prevent the Merry-Go-Round room from loading when Mario passes above the hole that leads
    // there, SURFACE_INTANGIBLE is used. This prevent the wrong room from loading, but can also allow
    // Mario to pass through.
    // To prevent accidentally leaving the floor tangible, stop checking for it.
    gFindFloorIncludeSurfaceIntangible = FALSE;
    gFindFloorExcludeDynamic           = FALSE;
    // Increment the debug tracker.
    gNumCalls.floor++;
#ifdef PUPPYPRINT
    collisionTime[perfIteration] += (osGetTime() - first);
#endif
    return height;
}

f32 find_room_floor(f32 xPos, f32 yPos, f32 zPos, struct Surface **pfloor) {
    gFindFloorIncludeSurfaceIntangible = TRUE;
    gFindFloorExcludeDynamic           = TRUE;
    return find_floor(xPos, yPos, zPos, pfloor);
}

#ifdef NEW_WATER_SURFACES
/**
 * Find the highest water floor under a given position and return the height.
 */
f32 find_water_floor(f32 xPos, f32 yPos, f32 zPos, struct Surface **pfloor) {
    struct Surface     *floor = NULL;
    struct SurfaceNode *surfaceList;
    s32 height       = FLOOR_LOWER_LIMIT;
    s32 bottomheight = FLOOR_LOWER_LIMIT;
#ifdef BETTER_WALL_COLLISION
    // Check if position is within level bounds
    if ((xPos <= -LEVEL_BOUNDARY_MAX)
     || (xPos >=  LEVEL_BOUNDARY_MAX)
     || (zPos <= -LEVEL_BOUNDARY_MAX)
     || (zPos >=  LEVEL_BOUNDARY_MAX)) return height;
    // Each level is split into cells to limit load, find the appropriate cell.
    register const CellIndex cellX = (((CellIndex)xPos + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX;
    register const CellIndex cellZ = (((CellIndex)zPos + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX;
    // Check for surfaces that are a part of level geometry.
    surfaceList = gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_WATER].next;
    floor = find_water_floor_from_list(surfaceList, xPos, yPos, zPos, &height, &bottomheight);
#else
    // (Parallel Universes) Because position is casted to an s16, reaching higher
    // float locations  can return floors despite them not existing there.
    // (Dynamic floors will unload due to the range.)
    s32 x = xPos;
    s32 y = yPos;
    s32 z = zPos;
    // Check if position is within level bounds
    if ((x <= -LEVEL_BOUNDARY_MAX)
     || (x >=  LEVEL_BOUNDARY_MAX)
     || (z <= -LEVEL_BOUNDARY_MAX)
     || (z >=  LEVEL_BOUNDARY_MAX)) return height;
    // Each level is split into cells to limit load, find the appropriate cell.
    register const CellIndex cellX = ((x + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX;
    register const CellIndex cellZ = ((z + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX;
    // Check for surfaces that are a part of level geometry.
    surfaceList = gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_WATER].next;
    floor = find_water_floor_from_list(surfaceList, x, y, z, &height, &bottomheight);
#endif
    if (floor == NULL) {
        height       = FLOOR_LOWER_LIMIT;
        bottomheight = FLOOR_LOWER_LIMIT;
    } else {
        *pfloor = floor;
    }
    return height;
}
#endif

/**************************************************
 *               ENVIRONMENTAL BOXES              *
 **************************************************/

/**
 * Finds the height of water at a given location.
 */
s32 find_water_level_and_floor(s32 x, s32 z, struct Surface **pfloor) {
    s32 i, numRegions;
    register s32 val, loX, hiX, loZ, hiZ;
    s32 waterLevel = FLOOR_LOWER_LIMIT;
    Collision *p = gEnvironmentRegions;
#ifdef NEW_WATER_SURFACES
    struct Surface *floor = NULL;
#ifdef PUPPYPRINT
    OSTime first = osGetTime();
#endif
    waterLevel = find_water_floor(x, gCheckingSurfaceCollisionsForCamera ? gLakituState.pos[1] : gMarioState->pos[1], z, &floor);
    if (p != NULL && waterLevel == FLOOR_LOWER_LIMIT) {
#else
    if (p != NULL) {
#endif
        numRegions = *p++;
        for (i = 0; i < numRegions; i++) {
            // Read the data
            val = *p++;
            loX = *p++;
            loZ = *p++;
            hiX = *p++;
            hiZ = *p++;
            // If the location is within a water box and it is a water box.
            // Water is less than 50 val only, while above is gas and such.
            if ((loX < x) && (x < hiX) && (loZ < z) && (z < hiZ) && (val < 50)) {
                // Set the water height. Since this breaks, only return the first height.
                waterLevel = *p;
                break;
            }
            p++;
        }
    } else {
#ifdef NEW_WATER_SURFACES
        *pfloor = floor;
#else
        *pfloor = NULL;
#endif
    }
#ifdef PUPPYPRINT
    collisionTime[perfIteration] += (osGetTime()-first);
#endif
    return waterLevel;
}

/**
 * Finds the height of water at a given location.
 */
s32 find_water_level(s32 x, s32 z) {
    s32 i, numRegions;
    register s32 val, loX, hiX, loZ, hiZ;
    s32 waterLevel = FLOOR_LOWER_LIMIT;
    Collision *p = gEnvironmentRegions;
#ifdef NEW_WATER_SURFACES
    struct Surface *floor;
#ifdef PUPPYPRINT
    OSTime first = osGetTime();
#endif
    waterLevel = find_water_floor(x, gCheckingSurfaceCollisionsForCamera ? gLakituState.pos[1] : gMarioState->pos[1], z, &floor);
    if (p != NULL && waterLevel == FLOOR_LOWER_LIMIT) {
#else
    if (p != NULL) {
#endif
        numRegions = *p++;
        for (i = 0; i < numRegions; i++) {
            // Read the data
            val = *p++;
            loX = *p++;
            loZ = *p++;
            hiX = *p++;
            hiZ = *p++;
            // If the location is within a water box and it is a water box.
            // Water is less than 50 val only, while above is gas and such.
            if ((loX < x) && (x < hiX) && (loZ < z) && (z < hiZ) && (val < 50)) {
                // Set the water height. Since this breaks, only return the first height.
                waterLevel = *p;
                break;
            }
            p++;
        }
    }
#ifdef PUPPYPRINT
    collisionTime[perfIteration] += (osGetTime() - first);
#endif
    return waterLevel;
}

/**
 * Finds the height of the poison gas (used only in HMC) at a given location.
 */
s32 find_poison_gas_level(s32 x, s32 z) {
    s32 i, numRegions;
    register s32 val, loX, hiX, loZ, hiZ;
    s32 gasLevel = FLOOR_LOWER_LIMIT;
    Collision *p = gEnvironmentRegions;
#ifdef PUPPYPRINT
    OSTime first = osGetTime();
#endif
    if (p != NULL) {
        numRegions = *p++;
        for (i = 0; i < numRegions; i++) {
            val = *p;
            if (val >= 50) {
                loX = p[1];
                loZ = p[2];
                hiX = p[3];
                hiZ = p[4];
                // If the location is within a gas's box and it is a gas box.
                // Gas has a value of 50, 60, etc.
                if ((loX < x) && (x < hiX) && (loZ < z) && (z < hiZ) && ((val % 10) == 0)) {
                    // Set the gas height. Since this breaks, only return the first height.
                    gasLevel = p[5];
                    break;
                }
            }
            p += 6;
        }
    }
#ifdef PUPPYPRINT
    collisionTime[perfIteration] += (osGetTime() - first);
#endif
    return gasLevel;
}

/**************************************************
 *                General Surfaces                *
 **************************************************/

/**
 * Checks if `surf` is within the rect prism defined by xMax, yMax, and zMax
 *
 * @param surf surface to check
 * @param xMax absolute-value max size in x, set to -1 to ignore
 * @param yMax absolute-value max size in y, set to -1 to ignore
 * @param zMax absolute-value max size in z, set to -1 to ignore
 */
Bool32 is_surf_within_bounding_box(struct Surface *surf, f32 xMax, f32 yMax, f32 zMax) {
    // Surface vertex coordinates
    Vec3s sx, sy, sz;
    // Max delta between x, y, and z
    register s16 dxMax = 0, dyMax = 0, dzMax = 0;
    // Current deltas between x, y, and z
    register f32 dx, dy, dz;
    register s32 i, j;
    sx[0] = surf->vertex1[0];
    sx[1] = surf->vertex2[0];
    sx[2] = surf->vertex3[0];
    sy[0] = surf->vertex1[1];
    sy[1] = surf->vertex2[1];
    sy[2] = surf->vertex3[1];
    sz[0] = surf->vertex1[2];
    sz[1] = surf->vertex2[2];
    sz[2] = surf->vertex3[2];
    for (i = 0; i < 3; i++) {
        j = (i + 1);
        if (j >= 3) j = 0;
        dx = ABS(sx[i] - sx[j]);
        if (dx > dxMax) dxMax = dx;
        dy = ABS(sy[i] - sy[j]);
        if (dy > dyMax) dyMax = dy;
        dz = ABS(sz[i] - sz[j]);
        if (dz > dzMax) dzMax = dz;
    }
    return (((yMax != -1.0f) && (dyMax < yMax)) || ((xMax != -1.0f) && (zMax != -1.0f) && (dxMax < xMax) && (dzMax < zMax)));
}

/**
 * Checks if `pos` is behind the surface, using the dot product.
 *
 * Because the function only uses `surf`s first vertex, some surfaces can shadow others.
 */
Bool32 is_behind_surface(Vec3f pos, struct Surface *surf) {
    // Surface normal
    f32 normX = (surf->vertex2[1] - surf->vertex1[1]) * (surf->vertex3[2] - surf->vertex2[2]) -
                (surf->vertex3[1] - surf->vertex2[1]) * (surf->vertex2[2] - surf->vertex1[2]);
    f32 normY = (surf->vertex2[2] - surf->vertex1[2]) * (surf->vertex3[0] - surf->vertex2[0]) -
                (surf->vertex3[2] - surf->vertex2[2]) * (surf->vertex2[0] - surf->vertex1[0]);
    f32 normZ = (surf->vertex2[0] - surf->vertex1[0]) * (surf->vertex3[1] - surf->vertex2[1]) -
                (surf->vertex3[0] - surf->vertex2[0]) * (surf->vertex2[1] - surf->vertex1[1]);
    f32 dirX  = (surf->vertex1[0] - pos[0]);
    f32 dirY  = (surf->vertex1[1] - pos[1]);
    f32 dirZ  = (surf->vertex1[2] - pos[2]);
    return ((dirX * normX) + (dirY * normY) + (dirZ * normZ) < 0);
}

/**
 * Checks if the whole circular sector is behind the surface.
 */
Bool32 is_range_behind_surface(Vec3f from, Vec3f to, struct Surface *surf, s16 range, SurfaceType surfType) {
    Bool32 behindSurface = TRUE;
    s32 leftBehind    = 0;
    s32 rightBehind   = 0;
    f32 checkDist;
    Angle checkPitch, checkYaw;
    Vec3f checkPos;
    if (surf != NULL) {
        if ((surfType == -1) || (surf->type != surfType)) {
            if (range == 0) {
                behindSurface = is_behind_surface(to, surf);
            } else {
                vec3f_get_dist_and_angle(from, to, &checkDist, &checkPitch, &checkYaw);
                vec3f_set_dist_and_angle(from, checkPos, checkDist, checkPitch, (checkYaw + range));
                leftBehind = is_behind_surface(checkPos, surf);
                vec3f_set_dist_and_angle(from, checkPos, checkDist, checkPitch, (checkYaw - range));
                rightBehind = is_behind_surface(checkPos, surf);
                behindSurface = (leftBehind * rightBehind);
            }
        }
    }
    return behindSurface;
}

/**************************************************
 *                   RAYCASTING                   *
 **************************************************/

s32 ray_surface_intersect(Vec3f orig, Vec3f dir, f32 dir_length, struct Surface *surface, Vec3f hit_pos, f32 *length) {
    Vec3f v0, v1, v2, e1, e2, h, s, q;
    register f32 a, f, u, v;
    Vec3f add_dir;
    Vec3f norm;
    // Get surface normal and some other stuff
    norm[0] = 0;
    norm[1] = surface->normal.y;
    norm[2] = 0;
    vec3f_mul_f32(norm, 30.0f); //! OFFSET
    vec3s_to_vec3f(v0, surface->vertex1);
    vec3s_to_vec3f(v1, surface->vertex2);
    vec3s_to_vec3f(v2, surface->vertex3);
    vec3f_add(v0, norm);
    vec3f_add(v1, norm);
    vec3f_add(v2, norm);
    vec3f_diff(e1, v1, v0);
    vec3f_diff(e2, v2, v0);
    vec3f_cross(h, dir, e2);
    // Check if we're perpendicular from the surface
    a = vec3f_dot(e1, h);
    if ((a > -0.00001f) && (a < 0.00001f)) return FALSE;
    // Check if we're making contact with the surface
    f = (1.0f / a);
    vec3f_diff(s, orig, v0);
    u = (f * vec3f_dot(s, h));
    if ((u < 0.0f) || (u > 1.0f)) return FALSE;
    vec3f_cross(q, s, e1);
    v = (f * vec3f_dot(dir, q));
    if ((v < 0.0f) || ((u + v) > 1.0f)) return FALSE;
    // Get the length between our origin and the surface contact point
    *length = (f * vec3f_dot(e2, q));
    if ((*length <= 0.00001) || (*length > dir_length)) return FALSE;
    // Successful contact
    vec3f_copy(add_dir, dir);
    vec3f_mul_f32(add_dir, *length);
    vec3f_sum(hit_pos, orig, add_dir);
    return TRUE;
}

void find_surface_on_ray_list(struct SurfaceNode *list, Vec3f orig, Vec3f dir, f32 dir_length, struct Surface **hit_surface, Vec3f hit_pos, f32 *max_length) {
    s32 hit;
    f32 length;
    Vec3f chk_hit_pos;
    register f32 top, bottom;
#ifdef PUPPYPRINT
    OSTime first = osGetTime();
#endif
    // Get upper and lower bounds of ray
    if (dir[1] >= 0.0f) {
        top    = (orig[1] + (dir[1] * dir_length));
        bottom =  orig[1];
    } else {
        top    =  orig[1];
        bottom = (orig[1] + (dir[1] * dir_length));
    }
    // Iterate through every surface of the list
    for (; (list != NULL); (list = list->next)) {
        // Ignore certain surface types.
        if (gCheckingSurfaceCollisionsForCamera) {
 #ifdef NEW_WATER_SURFACES
            if ((type == SURFACE_NEW_WATER) || (type == SURFACE_NEW_WATER_BOTTOM)) continue;
 #endif
            if ((list->surface->type == SURFACE_INTANGIBLE) || (list->surface->flags & SURFACE_FLAG_NO_CAM_COLLISION)) continue;
        }
        // Reject surface if out of vertical bounds
        if ((list->surface->lowerY > top) || (list->surface->upperY < bottom)) continue;
        // Check intersection between the ray and this surface
        if (((hit = ray_surface_intersect(orig, dir, dir_length, list->surface, chk_hit_pos, &length)) != 0) && (length <= *max_length)) {
            *hit_surface = list->surface;
            vec3f_copy(hit_pos, chk_hit_pos);
            *max_length = length;
        }
    }
#ifdef PUPPYPRINT
    collisionTime[perfIteration] += (osGetTime() - first);
#endif
}

void find_surface_on_ray_cell(CellIndex cellX, CellIndex cellZ, Vec3f orig, Vec3f normalized_dir, f32 dir_length, struct Surface **hit_surface, Vec3f hit_pos, f32 *max_length, s32 flags) {
	// Skip if OOB
	if ((cellX >= 0) && (cellX <= (NUM_CELLS - 1)) && (cellZ >= 0) && (cellZ <= (NUM_CELLS - 1))) {
		// Iterate through each surface in this partition
		if (normalized_dir[1] > -0.99999f && flags & RAYCAST_FIND_CEIL) {
			find_surface_on_ray_list(gStaticSurfacePartition [cellZ][cellX][SPATIAL_PARTITION_CEILS ].next, orig, normalized_dir, dir_length, hit_surface, hit_pos, max_length);
			find_surface_on_ray_list(gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_CEILS ].next, orig, normalized_dir, dir_length, hit_surface, hit_pos, max_length);
		}
		if (normalized_dir[1] < 0.99999f && flags & RAYCAST_FIND_FLOOR) {
			find_surface_on_ray_list(gStaticSurfacePartition [cellZ][cellX][SPATIAL_PARTITION_FLOORS].next, orig, normalized_dir, dir_length, hit_surface, hit_pos, max_length);
			find_surface_on_ray_list(gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_FLOORS].next, orig, normalized_dir, dir_length, hit_surface, hit_pos, max_length);
		}
		if (flags & RAYCAST_FIND_WALL) {
            find_surface_on_ray_list(gStaticSurfacePartition [cellZ][cellX][SPATIAL_PARTITION_WALLS].next, orig, normalized_dir, dir_length, hit_surface, hit_pos, max_length);
            find_surface_on_ray_list(gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_WALLS].next, orig, normalized_dir, dir_length, hit_surface, hit_pos, max_length);
        }
#ifdef NEW_WATER_SURFACES
        if (flags & RAYCAST_FIND_WATER) {
            find_surface_on_ray_list(gStaticSurfacePartition [cellZ][cellX][SPATIAL_PARTITION_WATER].next, orig, normalized_dir, dir_length, hit_surface, hit_pos, max_length);
            find_surface_on_ray_list(gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_WATER].next, orig, normalized_dir, dir_length, hit_surface, hit_pos, max_length);
        }
#endif
	}
}

#define STEPS 4

void find_surface_on_ray(Vec3f orig, Vec3f dir, struct Surface **hit_surface, Vec3f hit_pos, s32 flags) {
    Vec3f normalized_dir;
    register f32 step, dx, dz;
    s32 i;
    // Set that no surface has been hit
    *hit_surface = NULL;
    vec3f_sum(hit_pos, orig, dir);
    // Get normalized direction
    register f32 dir_length = vec3f_mag(dir);
    f32 max_length = dir_length;
    vec3f_copy(normalized_dir, dir);
    vec3f_normalize(normalized_dir);
    // Get our cell coordinate
    register f32 fCellX          = ((orig[0] + LEVEL_BOUNDARY_MAX) / CELL_SIZE);
    register f32 fCellZ          = ((orig[2] + LEVEL_BOUNDARY_MAX) / CELL_SIZE);
    register CellIndex cellX     = fCellX;
    register CellIndex cellZ     = fCellZ;
    register CellIndex cellPrevX = cellX;
    register CellIndex cellPrevZ = cellZ;
    // Don't do DDA if straight down
    if ((normalized_dir[1] >= 0.99999f) || (normalized_dir[1] <= -0.99999f)) {
		find_surface_on_ray_cell(cellX, cellZ, orig, normalized_dir, dir_length, hit_surface, hit_pos, &max_length, flags);
		return;
	}
    // Get cells we cross using DDA
    if (absf(dir[0]) >= absf(dir[2])) {
        step = ((STEPS * absf(dir[0])) / CELL_SIZE);
    } else {
        step = ((STEPS * absf(dir[2])) / CELL_SIZE);
    }
    dx = ((dir[0] / step) / CELL_SIZE);
    dz = ((dir[2] / step) / CELL_SIZE);
    for ((i = 0); ((i < step) && (*hit_surface == NULL)); (i++)) {
		find_surface_on_ray_cell(cellX, cellZ, orig, normalized_dir, dir_length, hit_surface, hit_pos, &max_length, flags);
        // Move cell coordinate
        fCellX   += dx;
        fCellZ   += dz;
        cellPrevX = cellX;
        cellPrevZ = cellZ;
        cellX     = fCellX;
        cellZ     = fCellZ;
        if ((cellPrevX != cellX) && (cellPrevZ != cellZ)) {
            find_surface_on_ray_cell(cellX, cellPrevZ, orig, normalized_dir, dir_length, hit_surface, hit_pos, &max_length, flags);
            find_surface_on_ray_cell(cellPrevX, cellZ, orig, normalized_dir, dir_length, hit_surface, hit_pos, &max_length, flags);
        }
    }
}

#undef STEPS

/**************************************************
 *                      DEBUG                     *
 **************************************************/

/**
 * Finds the length of a surface list for debug purposes.
 */
static s32 surface_list_length(struct SurfaceNode *list) {
    s32 count = 0;
    while (list != NULL) {
        list = list->next;
        count++;
    }
    return count;
}

/**
 * Print the area,number of walls, how many times they were called,
 * and some allocation information.
 */
void debug_surface_list_info(f32 xPos, f32 zPos) {
    struct SurfaceNode *list;
    s32 numFloors = 0;
    s32 numWalls  = 0;
    s32 numCeils  = 0;
    register const CellIndex cellX = (xPos + LEVEL_BOUNDARY_MAX) / CELL_SIZE;
    register const CellIndex cellZ = (zPos + LEVEL_BOUNDARY_MAX) / CELL_SIZE;
    // Check static floors
    list = gStaticSurfacePartition[cellZ & NUM_CELLS_INDEX][cellX & NUM_CELLS_INDEX][SPATIAL_PARTITION_FLOORS].next;
    numFloors += surface_list_length(list);
    // Check dynamic floors
    list = gDynamicSurfacePartition[cellZ & NUM_CELLS_INDEX][cellX & NUM_CELLS_INDEX][SPATIAL_PARTITION_FLOORS].next;
    numFloors += surface_list_length(list);
    // Check static walls
    list = gStaticSurfacePartition[cellZ & NUM_CELLS_INDEX][cellX & NUM_CELLS_INDEX][SPATIAL_PARTITION_WALLS].next;
    numWalls += surface_list_length(list);
    // Check dynamic walls
    list = gDynamicSurfacePartition[cellZ & NUM_CELLS_INDEX][cellX & NUM_CELLS_INDEX][SPATIAL_PARTITION_WALLS].next;
    numWalls += surface_list_length(list);
    // Check static ceilings
    list = gStaticSurfacePartition[cellZ & NUM_CELLS_INDEX][cellX & NUM_CELLS_INDEX][SPATIAL_PARTITION_CEILS].next;
    numCeils += surface_list_length(list);
    // Check dynamic ceilings
    list = gDynamicSurfacePartition[cellZ & NUM_CELLS_INDEX][cellX & NUM_CELLS_INDEX][SPATIAL_PARTITION_CEILS].next;
    numCeils += surface_list_length(list);
    print_debug_top_down_mapinfo("area   %x", ((cellZ * NUM_CELLS) + cellX));
    // Names represent ground, walls, and roofs as found in SMS.
    print_debug_top_down_mapinfo("dg %d", numFloors);
    print_debug_top_down_mapinfo("dw %d", numWalls);
    print_debug_top_down_mapinfo("dr %d", numCeils);
    set_text_array_x_y(80, -3);
    print_debug_top_down_mapinfo("%d", gNumCalls.floor);
    print_debug_top_down_mapinfo("%d", gNumCalls.wall);
    print_debug_top_down_mapinfo("%d", gNumCalls.ceil);
    set_text_array_x_y(-80, 0);
    // listal- List Allocated?, statbg- Static Background?, movebg- Moving Background?
    print_debug_top_down_mapinfo("listal %d", gSurfaceNodesAllocated);
    print_debug_top_down_mapinfo("statbg %d", gNumStaticSurfaces);
    print_debug_top_down_mapinfo("movebg %d", (gSurfacesAllocated - gNumStaticSurfaces));
    gNumCalls.floor = 0;
    gNumCalls.ceil  = 0;
    gNumCalls.wall  = 0;
}
