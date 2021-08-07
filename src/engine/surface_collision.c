#include <PR/ultratypes.h>

#include "sm64.h"
#include "game/debug.h"
#include "game/level_update.h"
#include "game/mario.h"
#include "game/object_list_processor.h"
#include "surface_collision.h"
#include "surface_load.h"
// #include "config.h"

/**************************************************
 *                      WALLS                     *
 **************************************************/

/**
 * Iterate through the list of walls until all walls are checked and
 * have given their wall push.
 */

#ifdef BETTER_WALL_COLLISION
static s32 find_wall_collisions_from_list(struct SurfaceNode *surfaceNode, struct WallCollisionData *data) {
    const f32 corner_threshold = -0.9f;
    register struct Surface *surf;
    register f32 offset;
    register f32 radius = data->radius;
    register f32 x      = data->x;
    register f32 y      = data->y + data->offsetY;
    register f32 z      = data->z;
    register f32 v0x, v0y, v0z;
    register f32 v1x, v1y, v1z;
    register f32 v2x, v2y, v2z;
    register f32 d00, d01, d11, d20, d21;
    register f32 invDenom;
    register f32 v, w;
    register f32 margin_radius = radius - 1.0f;
    register s16 type;
    s32 numCols = 0;
#if EXTENDED_BOUNDS_MODE > 1
    const float down_scale = 1.0f / WORLD_SCALE;
    radius *= down_scale;
    x *= down_scale;
    y *= down_scale;
    z *= down_scale;
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
        if (y < surf->lowerY || y > surf->upperY) continue;
        offset = surf->normal.x * x + surf->normal.y * y + surf->normal.z * z + surf->originOffset;
        if (offset < 0 || offset > radius) continue;
        if (type == SURFACE_NEW_WATER || type == SURFACE_NEW_WATER_BOTTOM) continue;
        // Determine if checking for the camera or not.
        if (gCheckingSurfaceCollisionsForCamera) {
            if (surf->flags & SURFACE_FLAG_NO_CAM_COLLISION) continue;
        } else {
            // Ignore camera only surfaces.
            if (type == SURFACE_CAMERA_BOUNDARY) continue;
            // If an object can pass through a vanish cap wall, pass through.
            if (type == SURFACE_VANISH_CAP_WALLS && gCurrentObject != NULL) {
                // If an object can pass through a vanish cap wall, pass through.
                if (gCurrentObject->activeFlags & ACTIVE_FLAG_MOVE_THROUGH_GRATE) continue;
                // If Mario has a vanish cap, pass through the vanish cap wall.
                if (gCurrentObject == gMarioObject && (gMarioState->flags & MARIO_VANISH_CAP)) continue;
            }
        }
        v0x = (f32)(surf->vertex2[0] - surf->vertex1[0]);
        v0y = (f32)(surf->vertex2[1] - surf->vertex1[1]);
        v0z = (f32)(surf->vertex2[2] - surf->vertex1[2]);
        v1x = (f32)(surf->vertex3[0] - surf->vertex1[0]);
        v1y = (f32)(surf->vertex3[1] - surf->vertex1[1]);
        v1z = (f32)(surf->vertex3[2] - surf->vertex1[2]);
        v2x = x - (f32)surf->vertex1[0];
        v2y = y - (f32)surf->vertex1[1];
        v2z = z - (f32)surf->vertex1[2];
        //Face
        d00 = v0x * v0x + v0y * v0y + v0z * v0z;
        d01 = v0x * v1x + v0y * v1y + v0z * v1z;
        d11 = v1x * v1x + v1y * v1y + v1z * v1z;
        d20 = v2x * v0x + v2y * v0y + v2z * v0z;
        d21 = v2x * v1x + v2y * v1y + v2z * v1z;
        invDenom = 1.0f / (d00 * d11 - d01 * d01);
        v = (d11 * d20 - d01 * d21) * invDenom;
        if (v < 0.0f || v > 1.0f) goto edge_1_2;
        w = (d00 * d21 - d01 * d20) * invDenom;
        if (w < 0.0f || w > 1.0f || v + w > 1.0f) goto edge_1_2;
        x += surf->normal.x * (radius - offset);
        z += surf->normal.z * (radius - offset);
        goto hasCollision;
    edge_1_2:
        if (offset < 0) continue;
        //Edge 1-2
        if (v0y != 0.0f) {
            v = (v2y / v0y);
            if (v < 0.0f || v > 1.0f) goto edge_1_3;
            d00 = v0x * v - v2x;
            d01 = v0z * v - v2z;
            invDenom = sqrtf(d00 * d00 + d01 * d01);
            offset = invDenom - margin_radius;
            if (offset > 0.0f) goto edge_1_3;
            invDenom = offset / invDenom;
            x += (d00 *= invDenom);
            z += (d01 *= invDenom);
            margin_radius += 0.01f;
            if (d00 * surf->normal.x + d01 * surf->normal.z < corner_threshold * offset) {
                continue;
            } else {
                goto hasCollision;
            }
        }
    edge_1_3:
        //Edge 1-3
        if (v1y != 0.0f) {
            v = (v2y / v1y);
            if (v < 0.0f || v > 1.0f) goto edge_2_3;
            d00 = v1x * v - v2x;
            d01 = v1z * v - v2z;
            invDenom = sqrtf(d00 * d00 + d01 * d01);
            offset = invDenom - margin_radius;
            if (offset > 0.0f) goto edge_2_3;
            invDenom = offset / invDenom;
            x += (d00 *= invDenom);
            z += (d01 *= invDenom);
            margin_radius += 0.01f;
            if (d00 * surf->normal.x + d01 * surf->normal.z < corner_threshold * offset) {
                continue;
            } else {
                goto hasCollision;
            }
        }
    edge_2_3:
        //Edge 2-3
        v1x = (f32)(surf->vertex3[0] - surf->vertex2[0]);
        v1y = (f32)(surf->vertex3[1] - surf->vertex2[1]);
        v1z = (f32)(surf->vertex3[2] - surf->vertex2[2]);
        v2x = x - (f32)surf->vertex2[0];
        v2y = y - (f32)surf->vertex2[1];
        v2z = z - (f32)surf->vertex2[2];
        if (v1y != 0.0f) {
            v = (v2y / v1y);
            if (v < 0.0f || v > 1.0f) continue;
            d00 = v1x * v - v2x;
            d01 = v1z * v - v2z;
            invDenom = sqrtf(d00 * d00 + d01 * d01);
            offset = invDenom - margin_radius;
            if (offset > 0.0f) continue;
            invDenom = offset / invDenom;
            x += (d00 *= invDenom);
            z += (d01 *= invDenom);
            margin_radius += 0.01f;
            if (d00 * surf->normal.x + d01 * surf->normal.z < corner_threshold * offset) {
                continue;
            } else {
                goto hasCollision;
            }
        } else {
            continue;
        }
    hasCollision:
        //! (Unreferenced Walls) Since this only returns the first four walls,
        //  this can lead to wall interaction being missed. Typically unreferenced walls
        //  come from only using one wall, however.
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
    s16 type;
    // Max collision radius = 200
    if (radius > 200.0f) radius = 200.0f;
    // Stay in this loop until out of walls.
    while (surfaceNode != NULL) {
        surf        = surfaceNode->surface;
        surfaceNode = surfaceNode->next;
        type        = surf->type;
        // Exclude a large number of walls immediately to optimize.
        if (y < surf->lowerY || y > surf->upperY) continue;
        offset = (surf->normal.x * x) + (surf->normal.y * y) + (surf->normal.z * z) + surf->originOffset;
        if (offset < -radius || offset > radius)  continue;
        if (type == SURFACE_NEW_WATER || type == SURFACE_NEW_WATER_BOTTOM) continue;
        // Determine if checking for the camera or not.
        if (gCheckingSurfaceCollisionsForCamera) {
            if (surf->flags & SURFACE_FLAG_NO_CAM_COLLISION) continue;
        } else {
            // Ignore camera only surfaces.
            if (type == SURFACE_CAMERA_BOUNDARY) continue;
            // If an object can pass through a vanish cap wall, pass through.
            if (type == SURFACE_VANISH_CAP_WALLS && gCurrentObject != NULL) {
                // If an object can pass through a vanish cap wall, pass through.
                if (gCurrentObject->activeFlags & ACTIVE_FLAG_MOVE_THROUGH_GRATE) continue;
                // If Mario has a vanish cap, pass through the vanish cap wall.
                if (gCurrentObject == gMarioObject && (gMarioState->flags & MARIO_VANISH_CAP)) continue;
            }
        }
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
        data->x += surf->normal.x * (radius - offset);
        data->z += surf->normal.z * (radius - offset);
        x = data->x;
        z = data->z;
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
    s16 cellX, cellZ;
    s32 numCollisions = 0;
    s16 x             = colData->x;
    s16 z             = colData->z;
    colData->numWalls = 0;
    if (x <= -LEVEL_BOUNDARY_MAX
     || x >=  LEVEL_BOUNDARY_MAX
     || z <= -LEVEL_BOUNDARY_MAX
     || z >=  LEVEL_BOUNDARY_MAX) return numCollisions;
    // World (level) consists of a 16x16 grid. Find where the collision is on
    // the grid (round toward -inf)
    cellX = ((x + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX;
    cellZ = ((z + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX;
    // Check for surfaces belonging to objects.
    node = gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_WALLS].next;
    numCollisions += find_wall_collisions_from_list(node, colData);
    // Check for surfaces that are a part of level geometry.
    node = gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_WALLS].next;
    numCollisions += find_wall_collisions_from_list(node, colData);
    // Increment the debug tracker.
    gNumCalls.wall++;
    return numCollisions;
}

/**************************************************
 *                     CEILINGS                   *
 **************************************************/


// Find the height of the surface at a given location
static f32 get_surface_height_at_location(s32 x, s32 z, struct Surface *surf) {
    return -(x * surf->normal.x + surf->normal.z * z + surf->originOffset) / surf->normal.y;
}

#ifdef BETTER_WALL_COLLISION
void add_ceil_margin(f32 *x, f32 *z, Vec3s target1, Vec3s target2, f32 margin) {
    register f32 diff_x, diff_z, invDenom;
    diff_x   = target1[0] - *x + target2[0] - *x;
    diff_z   = target1[2] - *z + target2[2] - *z;
    invDenom = margin / sqrtf(diff_x * diff_x + diff_z * diff_z);
    *x      += diff_x * invDenom;
    *z      += diff_z * invDenom;
}
#endif

/**
 * Iterate through the list of ceilings and find the first ceiling over a given point.
 */

#ifdef BETTER_WALL_COLLISION
static struct Surface *find_ceil_from_list(struct SurfaceNode *surfaceNode, f32 x, f32 y, f32 z, f32 *pheight) {
#else
static struct Surface *find_ceil_from_list(struct SurfaceNode *surfaceNode, s32 x, s32 y, s32 z, f32 *pheight) {
#endif
    register struct Surface *surf;
    f32 x1, z1, x2, z2, x3, z3;
    f32 height;
    s16 type = SURFACE_DEFAULT;
    struct Surface *ceil = NULL;
#ifdef BETTER_WALL_COLLISION
    const f32 margin = 1.5f;
#endif
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
        if (type == SURFACE_NEW_WATER || type == SURFACE_NEW_WATER_BOTTOM) continue;
        x1 = surf->vertex1[0];
        z1 = surf->vertex1[2];
#ifdef BETTER_WALL_COLLISION
        if (surf->type != SURFACE_HANGABLE) add_ceil_margin(&x1, &z1, surf->vertex2, surf->vertex3, margin);
        z2 = surf->vertex2[2];
        x2 = surf->vertex2[0];
        if (surf->type != SURFACE_HANGABLE) add_ceil_margin(&x2, &z2, surf->vertex3, surf->vertex1, margin);
        // Checking if point is in bounds of the triangle laterally.
        if ((z1 - z) * (x2 - x1) - (x1 - x) * (z2 - z1) > 0) continue;
        // Slight optimization by checking these later.
        x3 = surf->vertex3[0];
        z3 = surf->vertex3[2];
        if (surf->type != SURFACE_HANGABLE) add_ceil_margin(&x3, &z3, surf->vertex1, surf->vertex2, margin);
#else
        z2 = surf->vertex2[2];
        x2 = surf->vertex2[0];
        // Checking if point is in bounds of the triangle laterally.
        if ((z1 - z) * (x2 - x1) - (x1 - x) * (z2 - z1) > 0) continue;
        // Slight optimization by checking these later.
        x3 = surf->vertex3[0];
        z3 = surf->vertex3[2];
#endif
        if ((z2 - z) * (x3 - x2) - (x2 - x) * (z3 - z2) > 0) continue;
        if ((z3 - z) * (x1 - x3) - (x3 - x) * (z1 - z3) > 0) continue;
        // Find the ceil height at the specific point.
        height = get_surface_height_at_location(x, z, surf);
        if (height >= *pheight) continue;
        // if (y > (height + 78.0f)) continue;
        // Checks for ceiling interaction
        if (y > height) continue;
        if (y >= surf->upperY) continue;
        *pheight = height;
        ceil     = surf;
        if (height == y) break;
    }
    return ceil;
}

/**
 * Find the lowest ceiling above a given position and return the height.
 */
#ifdef BETTER_WALL_COLLISION
f32 find_ceil(f32 xPos, f32 yPos, f32 zPos, struct Surface **pceil) {
    s16 cellZ, cellX;
    struct Surface *ceil, *dynamicCeil;
    struct SurfaceNode *surfaceList;
    f32 height        = CELL_HEIGHT_LIMIT;
    f32 dynamicHeight = CELL_HEIGHT_LIMIT;
    *pceil = NULL;
    if (xPos <= -LEVEL_BOUNDARY_MAX
     || xPos >=  LEVEL_BOUNDARY_MAX
     || zPos <= -LEVEL_BOUNDARY_MAX
     || zPos >=  LEVEL_BOUNDARY_MAX) return height;
    // Each level is split into cells to limit load, find the appropriate cell.
    cellX = (((s32)xPos + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX;
    cellZ = (((s32)zPos + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX;
    // Check for surfaces that are a part of level geometry.
    surfaceList = gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_CEILS].next;
    ceil        = find_ceil_from_list(surfaceList, xPos, yPos, zPos, &height);
    dynamicHeight = height;
    // Check for surfaces belonging to objects.
    surfaceList = gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_CEILS].next;
    dynamicCeil = find_ceil_from_list(surfaceList, xPos, yPos, zPos, &dynamicHeight);
    if (dynamicHeight < height) {
        ceil   = dynamicCeil;
        height = dynamicHeight;
    }
    *pceil = ceil;
    // Increment the debug tracker.
    gNumCalls.ceil++;
    return height;
}
#else
f32 find_ceil(f32 xPos, f32 yPos, f32 zPos, struct Surface **pceil) {
    s16 cellZ, cellX;
    struct Surface *ceil, *dynamicCeil;
    struct SurfaceNode *surfaceList;
    f32 height        = CELL_HEIGHT_LIMIT;
    f32 dynamicHeight = CELL_HEIGHT_LIMIT;
    s16 x, y, z;
    // (Parallel Universes) Because position is casted to an s16, reaching higher
    // float locations  can return ceilings despite them not existing there.
    // (Dynamic ceilings will unload due to the range.)
    x = (s16) xPos;
    y = (s16) yPos;
    z = (s16) zPos;
    *pceil = NULL;
    // Check if position is within level bounds
    if (x <= -LEVEL_BOUNDARY_MAX
     || x >=  LEVEL_BOUNDARY_MAX
     || z <= -LEVEL_BOUNDARY_MAX
     || z >=  LEVEL_BOUNDARY_MAX) return height;
    // Each level is split into cells to limit load, find the appropriate cell.
    cellX = ((x + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX;
    cellZ = ((z + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX;
    // Check for surfaces that are a part of level geometry.
    surfaceList = gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_CEILS].next;
    ceil = find_ceil_from_list(surfaceList, x, y, z, &height);
    dynamicHeight = height;
    // Check for surfaces belonging to objects.
    surfaceList = gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_CEILS].next;
    dynamicCeil = find_ceil_from_list(surfaceList, x, y, z, &dynamicHeight);
    if (dynamicHeight < height) {
        ceil = dynamicCeil;
        height = dynamicHeight;
    }
    *pceil = ceil;
    // Increment the debug tracker.
    gNumCalls.ceil++;
    return height;
}
#endif

/**************************************************
 *                     FLOORS                     *
 **************************************************/

/**
 * Basically a local variable that passes through floor geo info.
 */
struct FloorGeometry sFloorGeo;

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
        sFloorGeo.normalX = floor->normal.x;
        sFloorGeo.normalY = floor->normal.y;
        sFloorGeo.normalZ = floor->normal.z;
        sFloorGeo.originOffset = floor->originOffset;
        *floorGeo = &sFloorGeo;
    }
    return floorHeight;
}

/**
 * Iterate through the list of floors and find the highest floor above pheight and below y.
 */
#ifdef BETTER_WALL_COLLISION
static struct Surface *find_floor_from_list(struct SurfaceNode *surfaceNode, f32 x, f32 maxY, f32 z, f32 *pheight) {
#else
static struct Surface *find_floor_from_list(struct SurfaceNode *surfaceNode, s32 x, s32 maxY, s32 z, f32 *pheight) {
#endif
    register struct Surface *surf;
    f32 height;
    s16 type = SURFACE_DEFAULT;
    struct Surface *floor = NULL;
    // Iterate through the list of floors until there are no more floors.
    while (surfaceNode != NULL) {
        surf        = surfaceNode->surface;
        surfaceNode = surfaceNode->next;
        type        = surf->type;
        // To prevent the Merry-Go-Round room from loading when Mario passes above the hole that leads
        // there, SURFACE_INTANGIBLE is used. This prevent the wrong room from loading, but can also allow
        // Mario to pass through.
        if (!gFindFloorIncludeSurfaceIntangible && type == SURFACE_INTANGIBLE) continue;
        // Determine if we are checking for the camera or not.
        if (gCheckingSurfaceCollisionsForCamera) {
            if (surf->flags & SURFACE_FLAG_NO_CAM_COLLISION || type == SURFACE_NEW_WATER || type == SURFACE_NEW_WATER_BOTTOM) continue;
        // If we are not checking for the camera, ignore camera only floors.
        } else if (type == SURFACE_CAMERA_BOUNDARY) continue;
        // Check if point is within tri laterally
        if (!check_within_floor_triangle_bounds(x, z, surf)) continue;
        // Get the height of the point on the tri
        height = get_surface_height_at_location(x, z, surf);
        // Ignore if the height is below or the same as the current surface height, without the buffer
        if (height <= *pheight) continue;
        // Check if the original location is more than 78 units above the floor height
        if (maxY < (height - 78.0f)) continue;
        // Set current surface and height for next iteration
        *pheight = height;
        floor    = surf;
        // Exit the loop if it's not possible for another floor to be closer to the original point
        if (maxY == (height - 78.0f)) break;
    }
    return floor;
}

s16 check_within_triangle_bounds(s32 x, s32 z, struct Surface *surf) {
    register s32 x1, z1, x2, z2, x3, z3;
    x1 = surf->vertex1[0];
    z1 = surf->vertex1[2];
    x2 = surf->vertex2[0];
    z2 = surf->vertex2[2];
    if ((z1 - z) * (x2 - x1) - (x1 - x) * (z2 - z1) < 0) return FALSE;
    x3 = surf->vertex3[0];
    z3 = surf->vertex3[2];
    if ((z2 - z) * (x3 - x2) - (x2 - x) * (z3 - z2) < 0) return FALSE;
    if ((z3 - z) * (x1 - x3) - (x3 - x) * (z1 - z3) < 0) return FALSE;
    return TRUE;
}

/**
 * Iterate through the list of water floors and find the first water floor under a given point.
 */
struct Surface *find_water_floor_from_list(struct SurfaceNode *surfaceNode, s32 x, s32 y, s32 z, f32 *pheight, f32 *pBottomHeight) {
    register struct Surface *surf;
    struct Surface *floor = NULL;
    struct SurfaceNode *topSurfaceNode = surfaceNode;
    struct SurfaceNode *bottomSurfaceNode = surfaceNode;
    f32 height          = FLOOR_LOWER_LIMIT;
    f32 bottomHeight    = FLOOR_LOWER_LIMIT;
    f32 topBottomHeight = FLOOR_LOWER_LIMIT;
    // Iterate through the list of water floors until there are no more water floors.
    while (bottomSurfaceNode != NULL) {
        f32 curBottomHeight = FLOOR_LOWER_LIMIT;
        surf                = bottomSurfaceNode->surface;
        bottomSurfaceNode   = bottomSurfaceNode->next;
        if (surf->type != SURFACE_NEW_WATER_BOTTOM || !check_within_triangle_bounds(x, z, surf)) continue;
        curBottomHeight = get_surface_height_at_location(x, z, surf);
        // if (curBottomHeight <  (y - 78.0f)) continue;
        // if (curBottomHeight >= (y - 78.0f)) bottomHeight = curBottomHeight;
        if (curBottomHeight < y + 78.0f) {
            if (curBottomHeight > topBottomHeight) topBottomHeight = curBottomHeight;
            continue;
        }
        if (curBottomHeight >= y + 78.0f) bottomHeight = curBottomHeight;
    }
    // Iterate through the list of water tops until there are no more water tops.
    while (topSurfaceNode != NULL) {
        f32 curHeight  = FLOOR_LOWER_LIMIT;
        surf           = topSurfaceNode->surface;
        topSurfaceNode = topSurfaceNode->next;
        if (surf->type == SURFACE_NEW_WATER_BOTTOM || !check_within_triangle_bounds(x, z, surf)) continue;
        curHeight = get_surface_height_at_location(x, z, surf);
        if (bottomHeight != FLOOR_LOWER_LIMIT && curHeight > bottomHeight) continue;
        if (curHeight > height) {
            height   = curHeight;
            *pheight = curHeight;
            floor    = surf;
        }
    }
    *pBottomHeight = topBottomHeight;
    return floor;
}

/**
 * Find the height of the highest floor below a point.
 */
f32 find_floor_height(f32 x, f32 y, f32 z) {
    struct Surface *floor;
    return find_floor(x, y, z, &floor);
}

/**
 * Find the highest floor under a given position and return the height.
 */
#ifdef BETTER_WALL_COLLISION
f32 find_floor(f32 xPos, f32 yPos, f32 zPos, struct Surface **pfloor) {
    s16 cellZ, cellX;
    struct Surface *floor, *dynamicFloor;
    struct SurfaceNode *surfaceList;
    f32 height        = FLOOR_LOWER_LIMIT;
    f32 dynamicHeight = FLOOR_LOWER_LIMIT;
    *pfloor = NULL;
    // Exclude floors outside of level boundaries
    if (xPos <= -LEVEL_BOUNDARY_MAX
     || xPos >=  LEVEL_BOUNDARY_MAX
     || zPos <= -LEVEL_BOUNDARY_MAX
     || zPos >=  LEVEL_BOUNDARY_MAX) return height;
    // Each level is split into cells to limit load, find the appropriate cell.
    cellX = (((s32)xPos + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX;
    cellZ = (((s32)zPos + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX;
    // Check for surfaces that are a part of level geometry.
    surfaceList  = gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_FLOORS].next;
    floor        = find_floor_from_list(surfaceList, xPos, yPos, zPos, &height);
    // In the next check, only check for floors higher than the previous check
    dynamicHeight = height;
    // Check for surfaces belonging to objects.
    surfaceList  = gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_FLOORS].next;
    dynamicFloor = find_floor_from_list(surfaceList, xPos, yPos, zPos, &dynamicHeight);
    // To prevent the Merry-Go-Round room from loading when Mario passes above the hole that leads
    // there, SURFACE_INTANGIBLE is used. This prevent the wrong room from loading, but can also allow
    // Mario to pass through.
    // To prevent accidentally leaving the floor tangible, stop checking for it.
    gFindFloorIncludeSurfaceIntangible = FALSE;
    // If a floor was missed, increment the debug counter.
    if (floor == NULL) gNumFindFloorMisses++;
    // Use the dynamic floor if it's higher
    if (dynamicHeight > height) {
        floor  = dynamicFloor;
        height = dynamicHeight;
    }
    *pfloor = floor;
    // Increment the debug tracker.
    gNumCalls.floor++;
    return height;
}
#else
f32 find_floor(f32 xPos, f32 yPos, f32 zPos, struct Surface **pfloor) {
    s16 cellZ, cellX;
    struct Surface *floor, *dynamicFloor;
    struct SurfaceNode *surfaceList;
    f32 height        = FLOOR_LOWER_LIMIT;
    f32 dynamicHeight = FLOOR_LOWER_LIMIT;
    // (Parallel Universes) Because position is casted to an s16, reaching higher
    // float locations  can return floors despite them not existing there.
    // (Dynamic floors will unload due to the range.)
    s16 x = (s16) xPos;
    s16 y = (s16) yPos;
    s16 z = (s16) zPos;
    *pfloor = NULL;
    // Check if position is within level bounds
    if (x <= -LEVEL_BOUNDARY_MAX
     || x >=  LEVEL_BOUNDARY_MAX
     || z <= -LEVEL_BOUNDARY_MAX
     || z >=  LEVEL_BOUNDARY_MAX) return height;
    // Each level is split into cells to limit load, find the appropriate cell.
    cellX = ((x + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX;
    cellZ = ((z + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX;
    // Check for surfaces that are a part of level geometry.
    surfaceList   = gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_FLOORS].next;
    floor         = find_floor_from_list(surfaceList, x, y, z, &height);
    // In the next check, only check for floors higher than the previous check
    dynamicHeight = height;
    // Check for surfaces belonging to objects.
    surfaceList   = gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_FLOORS].next;
    dynamicFloor  = find_floor_from_list(surfaceList, x, y, z, &dynamicHeight);
    // To prevent the Merry-Go-Round room from loading when Mario passes above the hole that leads
    // there, SURFACE_INTANGIBLE is used. This prevent the wrong room from loading, but can also allow
    // Mario to pass through.
    // To prevent accidentally leaving the floor tangible, stop checking for it.
    gFindFloorIncludeSurfaceIntangible = FALSE;
    // If a floor was missed, increment the debug counter.
    if (floor == NULL) gNumFindFloorMisses++;
    // Use the dynamic floor if it's higher
    if (dynamicHeight > height) {
        floor  = dynamicFloor;
        height = dynamicHeight;
    }
    *pfloor = floor;
    // Increment the debug tracker.
    gNumCalls.floor++;
    return height;
}
#endif

/**
 * Find the highest water floor under a given position and return the height.
 */
#ifdef BETTER_WALL_COLLISION
f32 find_water_floor(f32 xPos, f32 yPos, f32 zPos, struct Surface **pfloor) {
    s16 cellZ, cellX;
    struct Surface     *floor = NULL;
    struct SurfaceNode *surfaceList;
    f32 height       = FLOOR_LOWER_LIMIT;
    f32 bottomheight = FLOOR_LOWER_LIMIT;
    // Check if position is within level bounds
    if (xPos <= -LEVEL_BOUNDARY_MAX
     || xPos >=  LEVEL_BOUNDARY_MAX
     || zPos <= -LEVEL_BOUNDARY_MAX
     || zPos >=  LEVEL_BOUNDARY_MAX) return height;
    // Each level is split into cells to limit load, find the appropriate cell.
    cellX = (((s32)xPos + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX;
    cellZ = (((s32)zPos + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX;
    // Check for surfaces that are a part of level geometry.
    surfaceList = gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_WATER].next;
    floor = find_water_floor_from_list(surfaceList, xPos, yPos, zPos, &height, &bottomheight);
    if (floor == NULL) {
        height       = FLOOR_LOWER_LIMIT;
        bottomheight = FLOOR_LOWER_LIMIT;
    } else {
        *pfloor = floor;
    }
    return height;
}
#else
f32 find_water_floor(f32 xPos, f32 yPos, f32 zPos, struct Surface **pfloor) {
    s16 cellZ, cellX;
    struct Surface     *floor = NULL;
    struct SurfaceNode *surfaceList;
    f32 height       = FLOOR_LOWER_LIMIT;
    f32 bottomheight = FLOOR_LOWER_LIMIT;
    // (Parallel Universes) Because position is casted to an s16, reaching higher
    // float locations  can return floors despite them not existing there.
    // (Dynamic floors will unload due to the range.)
    s16 x = (s16) xPos;
    s16 y = (s16) yPos;
    s16 z = (s16) zPos;
    // Check if position is within level bounds
    if (x <= -LEVEL_BOUNDARY_MAX
     || x >=  LEVEL_BOUNDARY_MAX
     || z <= -LEVEL_BOUNDARY_MAX
     || z >=  LEVEL_BOUNDARY_MAX) return height;
    // Each level is split into cells to limit load, find the appropriate cell.
    cellX = ((x + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX;
    cellZ = ((z + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX;
    // Check for surfaces that are a part of level geometry.
    surfaceList = gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_WATER].next;
    floor = find_water_floor_from_list(surfaceList, x, y, z, &height, &bottomheight);
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
f32 find_water_level_and_floor(f32 x, f32 z, struct Surface **pfloor) {
    s32 i;
    s32 numRegions;
    s16 val;
    f32 loX, hiX, loZ, hiZ;
    f32 waterLevel = FLOOR_LOWER_LIMIT;
    s16 *p = gEnvironmentRegions;
    struct Surface *floor = NULL;
    waterLevel = find_water_floor(x, gCheckingSurfaceCollisionsForCamera ? gLakituState.pos[1] : gMarioState->pos[1], z, &floor);
    if (p != NULL && waterLevel == FLOOR_LOWER_LIMIT) {
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
            if (loX < x && x < hiX && loZ < z && z < hiZ && val < 50) {
                // Set the water height. Since this breaks, only return the first height.
                waterLevel = *p;
                break;
            }
            p++;
        }
    } else {
        *pfloor = floor;
    }
    return waterLevel;
}

/**
 * Finds the height of water at a given location.
 */
f32 find_water_level(f32 x, f32 z) {
    s32 i;
    s32 numRegions;
    s16 val;
    f32 loX, hiX, loZ, hiZ;
    f32 waterLevel = FLOOR_LOWER_LIMIT;
    s16 *p = gEnvironmentRegions;
    struct Surface *floor;
    waterLevel = find_water_floor(x, gCheckingSurfaceCollisionsForCamera ? gLakituState.pos[1] : gMarioState->pos[1], z, &floor);
    if (p != NULL && waterLevel == FLOOR_LOWER_LIMIT) {
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
            if (loX < x && x < hiX && loZ < z && z < hiZ && val < 50) {
                // Set the water height. Since this breaks, only return the first height.
                waterLevel = *p;
                break;
            }
            p++;
        }
    }
    return waterLevel;
}

/**
 * Finds the height of the poison gas (used only in HMC) at a given location.
 */
f32 find_poison_gas_level(f32 x, f32 z) {
    s32 i;
    s32 numRegions;
    s16 val;
    f32 loX, hiX, loZ, hiZ;
    f32 gasLevel = FLOOR_LOWER_LIMIT;
    s16 *p = gEnvironmentRegions;
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
                if (loX < x && x < hiX && loZ < z && z < hiZ && val % 10 == 0) {
                    // Set the gas height. Since this breaks, only return the first height.
                    gasLevel = p[5];
                    break;
                }
            }
            p += 6;
        }
    }
    return gasLevel;
}

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
    s32 cellX = (xPos + LEVEL_BOUNDARY_MAX) / CELL_SIZE;
    s32 cellZ = (zPos + LEVEL_BOUNDARY_MAX) / CELL_SIZE;
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
    print_debug_top_down_mapinfo("area   %x", cellZ * NUM_CELLS + cellX);
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
    print_debug_top_down_mapinfo("movebg %d", gSurfacesAllocated - gNumStaticSurfaces);
    gNumCalls.floor = 0;
    gNumCalls.ceil  = 0;
    gNumCalls.wall  = 0;
}
