#include <PR/ultratypes.h>

#include "sm64.h"
#include "game/debug.h"
#include "game/level_update.h"
#include "game/mario.h"
#include "game/object_list_processor.h"
// #include "game/rendering_graph_node.h"
#include "surface_collision.h"
#include "surface_load.h"
#include "math_util.h"
#if PUPPYPRINT_DEBUG
#include "game/puppyprint.h"
#endif

/**************************************************
 *                      WALLS                     *
 **************************************************/

void move_towards_wall(struct MarioState *m, f32 amount) {
    m->vel[0] += (m->wall->normal.x * amount);
    m->vel[1] += (m->wall->normal.y * amount);
    m->vel[2] += (m->wall->normal.z * amount);
}

#define CALC_OFFSET(vert, next_step) {          \
    if ((vert)[1] != 0.0f) {                    \
        v = (v2[1] / (vert)[1]);                \
        if ((v < 0.0f) || (v > 1.0f)) next_step;\
        d00 = (((vert)[0] * v) - v2[0]);        \
        d01 = (((vert)[2] * v) - v2[2]);        \
        invDenom = sqrtf(sqr(d00) + sqr(d01));  \
        offset   = (invDenom - margin_radius);  \
        if (offset > 0.0f) next_step;           \
        goto check_collision;                   \
    }                                           \
    next_step;                                  \
}

/**
 * Iterate through the list of walls until all walls are checked and
 * have given their wall push.
 */
static s32 find_wall_collisions_from_list(struct SurfaceNode *surfaceNode, struct WallCollisionData *data) {
    const f32 corner_threshold = (-0.9f);
    register struct Surface *surf;
    register f32 offset;
    register f32 radius = data->radius;
    register Vec3f pos;
    vec3_copy_y_off(pos, data->pos, data->offsetY);
    register Vec3f v0, v1, v2;            // vertices
    register f32 d00, d01, d11, d20, d21; // edges
    register f32 invDenom;
    register f32 v, w;
    register f32 margin_radius = (radius - 1.0f);
    register SurfaceType type = SURFACE_DEFAULT;
    s32 numCols = 0;
// #if EXTENDED_BOUNDS_MODE > 1
//     const float down_scale = (1.0f / gWorldScale);
//     radius         *= down_scale;
//     vec3_mul_val(pos, down_scale);
//     margin_radius  *= down_scale;
// #endif
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
            if ((type == SURFACE_VANISH_CAP_WALLS) && (o != NULL)) {
                // If an object can pass through a vanish cap wall, pass through.
                if (o->activeFlags & ACTIVE_FLAG_MOVE_THROUGH_GRATE) continue;
                // If Mario has a vanish cap, pass through the vanish cap wall.
                if ((o == gMarioObject) && (gMarioState->flags & MARIO_VANISH_CAP)) continue;
            }
        }
        if ((pos[1] < surf->lowerY) || (pos[1] > surf->upperY)) continue;
 #ifdef UNDERWATER_STEEP_FLOORS_AS_WALLS
        if (gIncludeSteepFloorsInWallCollisionCheck && (surf->normal.y > MIN_UNDERWATER_FLOOR_NORMAL_Y)) continue;
 #endif
        // Dot of normal and pos, + originOffset
        offset = ((surf->normal.x * pos[0]) + (surf->normal.y * pos[1]) + (surf->normal.z * pos[2]) + surf->originOffset);
        if ((offset < -radius) || (offset > radius)) continue;
        vec3_diff(v0, surf->vertex2, surf->vertex1);
        vec3_diff(v1, surf->vertex3, surf->vertex1);
        vec3_diff(v2,           pos, surf->vertex1);
        // Face
        d00 = vec3_dot(v0, v0);
        d01 = vec3_dot(v0, v1);
        d11 = vec3_dot(v1, v1);
        d20 = vec3_dot(v2, v0);
        d21 = vec3_dot(v2, v1);
        invDenom = (1.0f / ((d00 * d11) - (d01 * d01)));
        v = (((d11 * d20) - (d01 * d21)) * invDenom);
        if ((v < 0.0f) || (v > 1.0f)) goto edge_1_2;
        w = (((d00 * d21) - (d01 * d20)) * invDenom);
        if ((w < 0.0f) || (w > 1.0f) || ((v + w) > 1.0f)) goto edge_1_2;
        pos[0] += (surf->normal.x * (radius - offset));
        pos[2] += (surf->normal.z * (radius - offset));
        goto hasCollision;
    edge_1_2:
        if (offset < 0) continue;
        CALC_OFFSET(v0, goto edge_1_3);
    edge_1_3:
        CALC_OFFSET(v1, goto edge_2_3);
    edge_2_3:
        vec3_diff(v1, surf->vertex3, surf->vertex2);
        vec3_diff(v2, pos, surf->vertex2);
        CALC_OFFSET(v1, continue);
    check_collision:
        invDenom = (offset / invDenom);
        pos[0] += (d00 *= invDenom);
        pos[2] += (d01 *= invDenom);
        margin_radius += 0.01f;
        if ((d00 * surf->normal.x) + (d01 * surf->normal.z) < (corner_threshold * offset)) continue;
    hasCollision:
        if (data->numWalls < MAX_REFEREMCED_WALLS) data->walls[data->numWalls++] = surf;
        numCols++;
    }
// #if EXTENDED_BOUNDS_MODE > 1
//     vec3_mul_val(pos, gWorldScale);
// #endif
    data->pos[0] = pos[0];
    data->pos[2] = pos[2];
    return numCols;
}

#undef CALC_OFFSET

/**
 * Find wall collisions and receive their push.
 */
s32 find_wall_collisions(struct WallCollisionData *colData) {
    struct SurfaceNode *node;
    s32 numCollisions = 0;
    s32 x = colData->pos[0];
    s32 z = colData->pos[2];
#if PUPPYPRINT_DEBUG
    OSTime first = osGetTime();
#endif
    colData->numWalls = 0;
    if (is_outside_level_bounds(x, z)) return numCollisions;
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
#if PUPPYPRINT_DEBUG
    collisionTime[perfIteration] += (osGetTime() - first);
#endif
    return numCollisions;
}

/**
 * Formats the position and wall search for find_wall_collisions.
 */
s32 resolve_wall_collisions(Vec3f pos, f32 offsetY, f32 radius) {
    struct WallCollisionData collision;
    collision.offsetY  = offsetY;
    collision.radius   = radius;
    vec3_copy(collision.pos, pos);
    collision.numWalls = 0;
    s32 numCollisions  = find_wall_collisions(&collision);
    vec3_copy(pos, collision.pos);
    return numCollisions;
}

/**
 * Collides with walls and returns the most recent wall.
 */
void resolve_and_return_wall_collision_data(Vec3f pos, f32 offsetY, f32 radius, struct WallCollisionData *collisionData) {
    vec3_copy(collisionData->pos, pos);
    collisionData->radius  = radius;
    collisionData->offsetY = offsetY;
    find_wall_collisions(collisionData);
    vec3_copy(pos, collisionData->pos);
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
    Vec3n norm;
    register f32 originOffset, offset, offsetAbsolute;
    Vec3f newPos[MAX_REFEREMCED_WALLS];
    s32 i;
    s32 numCollisions     = 0;
#if PUPPYPRINT_DEBUG
    OSTime first = osGetTime();
#endif
    vec3_copy(collisionData.pos, pos);
    collisionData.radius  = radius;
    collisionData.offsetY = offsetY;
    numCollisions         = find_wall_collisions(&collisionData);
    if (numCollisions != 0) {
        for ((i = 0); (i < collisionData.numWalls); (i++)) {
            wall = collisionData.walls[collisionData.numWalls - 1];
            vec3_copy(newPos[i], pos);
            vec3_set(norm, wall->normal.x, wall->normal.y, wall->normal.z);
            originOffset   = wall->originOffset;
            offset         = (vec3_dot(norm, newPos[i]) + originOffset);
            offsetAbsolute = ABSF(offset);
            if (offsetAbsolute < radius) {
                newPos[i][0] += (norm[0] * (radius - offset));
                newPos[i][2] += (norm[2] * (radius - offset));
                vec3_copy(pos, newPos[i]);
            }
        }
    }
#if PUPPYPRINT_DEBUG
    collisionTime[perfIteration] += (osGetTime() - first);
#endif
    return numCollisions;
}

/**
 * Move `pos` between the nearest floor and ceiling
 * @param lastGood unused, passed as the last position the camera was in
 */
void resolve_geometry_collisions(Vec3f pos, UNUSED Vec3f lastGood) {
    struct Surface *surf;
    resolve_wall_collisions(pos, 0.0f, 100.0f);
    f32 floorY = find_floor(pos[0], (pos[1] + 50.0f), pos[2], &surf);
    f32 ceilY  = find_ceil( pos[0], (pos[1] - 50.0f), pos[2], &surf);
    if ((FLOOR_LOWER_LIMIT != floorY) && (CELL_HEIGHT_LIMIT == ceilY) && pos[1] < (floorY += 125.0f)) pos[1] = floorY;
    if ((FLOOR_LOWER_LIMIT == floorY) && (CELL_HEIGHT_LIMIT != ceilY) && pos[1] > ( ceilY -= 125.0f)) pos[1] =  ceilY;
    if ((FLOOR_LOWER_LIMIT != floorY) && (CELL_HEIGHT_LIMIT != ceilY)) {
        floorY += 125.0f;
        ceilY  -= 125.0f;
        if ((pos[1] <= floorY) && (pos[1] <  ceilY)) pos[1] = floorY;
        if ((pos[1] >  floorY) && (pos[1] >= ceilY)) pos[1] =  ceilY;
        if ((pos[1] <= floorY) && (pos[1] >= ceilY)) pos[1] = ((floorY + ceilY) * 0.5f);
    }
}

/**
 * Finds any wall collisions and returns what the displacement vector would be.
 */
Bool32 find_wall_displacement(Vec3f dist, f32 x, f32 y, f32 z, f32 radius) {
    struct WallCollisionData hitbox;
    vec3_set(hitbox.pos, x, y, z);
    hitbox.offsetY = 10.0f;
    hitbox.radius  = radius;
    if (find_wall_collisions(&hitbox) != 0) {
        Vec3f pos = { x, y, z };
        vec3_diff(dist, hitbox.pos, pos);
        return TRUE;
    } else {
        return FALSE;
    }
}

/**************************************************
 *                     CEILINGS                   *
 **************************************************/

void add_ceil_margin(f32 *x, f32 *z, Vec3s target1, Vec3s target2, f32 margin) {
    register f32 diff_x   = (target1[0] - *x + target2[0] - *x);
    register f32 diff_z   = (target1[2] - *z + target2[2] - *z);
    register f32 invDenom = (margin / sqrtf(sqr(diff_x) + sqr(diff_z)));
    *x += (diff_x * invDenom);
    *z += (diff_z * invDenom);
}

/**
 * Iterate through the list of ceilings and find the first ceiling over a given point.
 */
static struct Surface *find_ceil_from_list(struct SurfaceNode *surfaceNode, f32 x, f32 y, f32 z, f32 *pheight) {
    const f32 margin = 1.5f;
    register struct Surface *surf;
    Vec3f vx, vz;
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
        // Skip if ceil is too low
        if (y > surf->upperY) continue;
        vx[0] = surf->vertex1[0];
        vz[0] = surf->vertex1[2];
        if (type != SURFACE_HANGABLE) add_ceil_margin(&vx[0], &vz[0], surf->vertex2, surf->vertex3, margin);
        vz[1] = surf->vertex2[2];
        vx[1] = surf->vertex2[0];
        if (type != SURFACE_HANGABLE) add_ceil_margin(&vx[1], &vz[1], surf->vertex3, surf->vertex1, margin);
        // Checking if point is in bounds of the triangle laterally.
        if ((vz[0] - z) * (vx[1] - vx[0]) - (vx[0] - x) * (vz[1] - vz[0]) > 0) continue;
        // Slight optimization by checking these later.
        vx[2] = surf->vertex3[0];
        vz[2] = surf->vertex3[2];
        if (type != SURFACE_HANGABLE) add_ceil_margin(&vx[2], &vz[2], surf->vertex1, surf->vertex2, margin);
        if ((vz[1] - z) * (vx[2] - vx[1]) - (vx[1] - x) * (vz[2] - vz[1]) > 0) continue;
        if ((vz[2] - z) * (vx[0] - vx[2]) - (vx[2] - x) * (vz[0] - vz[2]) > 0) continue;
        // Find the ceil height at the specific point.
        height = get_surface_height_at_location(x, z, surf);
        if (height >= *pheight) continue;
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
f32 find_ceil(f32 x, f32 y, f32 z, struct Surface **pceil) {
    struct Surface *ceil, *dynamicCeil;
    struct SurfaceNode *surfaceList;
    f32 height        = CELL_HEIGHT_LIMIT;
    f32 dynamicHeight = CELL_HEIGHT_LIMIT;
#if PUPPYPRINT_DEBUG
    OSTime first = osGetTime();
#endif
    *pceil            = NULL;
    if (is_outside_level_bounds(x, z)) return height;
    // Each level is split into cells to limit load, find the appropriate cell.
    register const CellIndex cellX = ((((CellIndex)x + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX);
    register const CellIndex cellZ = ((((CellIndex)z + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX);
    // Check for surfaces that are a part of level geometry.
    surfaceList = gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_CEILS].next;
    ceil        = find_ceil_from_list(surfaceList, x, y, z, &height);
    dynamicHeight = height;
    // Check for surfaces belonging to objects.
    surfaceList = gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_CEILS].next;
    dynamicCeil = find_ceil_from_list(surfaceList, x, y, z, &dynamicHeight);
    // Use the dynamic ceiling if it is lower
    if (dynamicHeight < height) {
        ceil   = dynamicCeil;
        height = dynamicHeight;
    }
    *pceil = ceil;
    // Increment the debug tracker.
    gNumCalls.ceil++;
#if PUPPYPRINT_DEBUG
    collisionTime[perfIteration] += (osGetTime() - first);
#endif
    return height;
}

/**************************************************
 *                     FLOORS                     *
 **************************************************/

Bool32 floor_type_exists_in_current_cell(f32 x, f32 z, SurfaceType type, Bool32 includeDynamic) {
    register const CellIndex cellX = ((((CellIndex)x + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX);
    register const CellIndex cellZ = ((((CellIndex)z + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX);
    struct SurfaceNode *surfaceNode;
    surfaceNode = gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_FLOORS].next;
    // Check for surfaces that are a part of level geometry.
    while (surfaceNode != NULL) {
        if (surfaceNode->surface->type == type) return TRUE;
        surfaceNode = surfaceNode->next;
    }
    if (includeDynamic) {
        // Check for surfaces belonging to objects.
        surfaceNode = gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_FLOORS].next;
        while (surfaceNode != NULL) {
            if (surfaceNode->surface->type == type) return TRUE;
            surfaceNode = surfaceNode->next;
        }
    }
    return FALSE;
}

static Bool32 check_within_floor_triangle_bounds(f32 x, f32 z, struct Surface *surf) {
    register Vec3f vx, vz;
    vx[0] = surf->vertex1[0];
    vz[0] = surf->vertex1[2];
    vx[1] = surf->vertex2[0];
    vz[1] = surf->vertex2[2];
    // Checking if point is in bounds of the triangle laterally.
    if ((vz[0] - z) * (vx[1] - vx[0]) - (vx[0] - x) * (vz[1] - vz[0]) < 0.0f) return FALSE; // 12
    // Slight optimization by checking these later.
    vx[2] = surf->vertex3[0];
    vz[2] = surf->vertex3[2];
    if ((vz[1] - z) * (vx[2] - vx[1]) - (vx[1] - x) * (vz[2] - vz[1]) < 0.0f) return FALSE; // 23
    if ((vz[2] - z) * (vx[0] - vx[2]) - (vx[2] - x) * (vz[0] - vz[2]) < 0.0f) return FALSE; // 31
    return TRUE;
}

/**
 * Iterate through the list of floors and find the highest floor above pheight and below y.
 */
static struct Surface *find_floor_from_list(struct SurfaceNode *surfaceNode, f32 x, f32 y, f32 z, f32 *pheight) {
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
            if ((surf->flags & SURFACE_FLAG_NO_CAM_COLLISION) || (type == SURFACE_NEW_WATER) || (type == SURFACE_NEW_WATER_BOTTOM)) continue;
#else
            if (surf->flags & SURFACE_FLAG_NO_CAM_COLLISION) continue;
#endif
        // If we are not checking for the camera, ignore camera only floors.
        } else if (type == SURFACE_CAMERA_BOUNDARY) continue;
        // Skip if floor is too high
        if (y < (surf->lowerY - 30)) continue; //! why 30?
        // Check if point is within tri laterally
        if (!check_within_floor_triangle_bounds(x, z, surf)) continue;
        // Get the height of the point on the tri
        height = get_surface_height_at_location(x, z, surf);
        // Ignore if the height is below or the same as the current surface height
        if (height <= *pheight) continue;
        // Check if the original location is above the floor height
        if (y < height) continue;
        // Set current surface and height for next iteration
        *pheight = height;
        floor    = surf;
        // Exit the loop if it's not possible for another floor to be closer to the original point
        if (y == height) break;
    }
    return floor;
}

#ifdef NEW_WATER_SURFACES
/**
 * Iterate through the list of water floors and find the first water floor under a given point.
 */
struct Surface *find_water_floor_from_list(struct SurfaceNode *surfaceNode, s32 x, s32 y, s32 z, s32 *pheight, s32 *pBottomHeight) {
    register struct Surface *surf;
    struct Surface     *floor             = NULL;
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
        if ((surf->type != SURFACE_NEW_WATER_BOTTOM) || !check_within_floor_triangle_bounds(x, z, surf)) continue;
        curBottomHeight = get_surface_height_at_location(x, z, surf);
        if (curBottomHeight < y) {
            if (curBottomHeight > topBottomHeight) topBottomHeight = curBottomHeight;
            continue;
        }
        if (curBottomHeight >= y) bottomHeight = curBottomHeight;
    }
    // Iterate through the list of water tops until there are no more water tops.
    while (topSurfaceNode != NULL) {
        s32 curHeight  = FLOOR_LOWER_LIMIT;
        surf           = topSurfaceNode->surface;
        topSurfaceNode = topSurfaceNode->next;
        if ((surf->type == SURFACE_NEW_WATER_BOTTOM) || !check_within_floor_triangle_bounds(x, z, surf)) continue;
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
UNUSED f32 unused_find_dynamic_floor(f32 x, f32 y, f32 z, struct Surface **pfloor) {
    struct SurfaceNode *surfaceList;
    struct Surface *floor;
    f32 floorHeight = FLOOR_LOWER_LIMIT;
    // Each level is split into cells to limit load, find the appropriate cell.
    register const CellIndex cellX = (((CellIndex)x + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX;
    register const CellIndex cellZ = (((CellIndex)z + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX;
    surfaceList                    = gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_FLOORS].next;
    floor                          = find_floor_from_list(surfaceList, x, y, z, &floorHeight);
    *pfloor                        = floor;
    return floorHeight;
}

/**
 * Find the highest floor under a given position and return the height.
 */
f32 find_floor(f32 x, f32 y, f32 z, struct Surface **pfloor) {
#if PUPPYPRINT_DEBUG
    OSTime first = osGetTime();
#endif
    struct Surface *floor, *dynamicFloor;
    struct SurfaceNode *surfaceList;
    f32 height        = FLOOR_LOWER_LIMIT;
    f32 dynamicHeight = FLOOR_LOWER_LIMIT;
    *pfloor = NULL;
    // Exclude floors outside of level boundaries
    if (is_outside_level_bounds(x, z)) {
#if PUPPYPRINT_DEBUG
        collisionTime[perfIteration] += (osGetTime() - first);
#endif
        return height;
    }
    // Each level is split into cells to limit load, find the appropriate cell.
    register const CellIndex cellX = ((((CellIndex)x + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX);
    register const CellIndex cellZ = ((((CellIndex)z + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX);
    // Check for surfaces that are a part of level geometry.
    surfaceList  = gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_FLOORS].next;
    floor        = find_floor_from_list(surfaceList, x, y, z, &height);
    if (!gFindFloorExcludeDynamic) {
        // In the next check, only check for floors higher than the previous check
        dynamicHeight = height;
        // Check for surfaces belonging to objects.
        surfaceList  = gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_FLOORS].next;
        dynamicFloor = find_floor_from_list(surfaceList, x, y, z, &dynamicHeight);
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
#if PUPPYPRINT_DEBUG
    collisionTime[perfIteration] += (osGetTime() - first);
#endif
    return height;
}

f32 find_room_floor(f32 x, f32 y, f32 z, struct Surface **pfloor) {
    gFindFloorIncludeSurfaceIntangible = TRUE;
    gFindFloorExcludeDynamic           = TRUE;
    return find_floor(x, y, z, pfloor);
}

#ifdef NEW_WATER_SURFACES
/**
 * Find the highest water floor under a given position and return the height.
 */
f32 find_water_floor(f32 x, f32 y, f32 z, struct Surface **pfloor) {
    struct Surface     *floor = NULL;
    struct SurfaceNode *surfaceList;
    s32 height       = FLOOR_LOWER_LIMIT;
    s32 bottomheight = FLOOR_LOWER_LIMIT;
    // Check if position is within level bounds
    if (is_outside_level_bounds(x, z)) return height;
    // Each level is split into cells to limit load, find the appropriate cell.
    register const CellIndex cellX = (((CellIndex)x + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX;
    register const CellIndex cellZ = (((CellIndex)z + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX;
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
s32 find_water_level_and_floor(s32 x, s32 z, struct Surface **pfloor) {
    s32 i, numRegions;
    register s32 val, loX, hiX, loZ, hiZ;
    s32 waterLevel = FLOOR_LOWER_LIMIT;
    Collision *p = gEnvironmentRegions;
#if PUPPYPRINT_DEBUG
    OSTime first = osGetTime();
#endif
#ifdef NEW_WATER_SURFACES
    struct Surface *floor = NULL;
    waterLevel = find_water_floor(x, (gCheckingSurfaceCollisionsForCamera ? gLakituState.pos[1] : gMarioState->pos[1]), z, &floor);
    if ((p != NULL) && (waterLevel == FLOOR_LOWER_LIMIT)) {
#else
    if (p != NULL) {
#endif
        numRegions = *p++;
        for ((i = 0); (i < numRegions); (i++)) {
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
#if PUPPYPRINT_DEBUG
    collisionTime[perfIteration] += (osGetTime() - first);
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
#if PUPPYPRINT_DEBUG
    OSTime first = osGetTime();
#endif
#ifdef NEW_WATER_SURFACES
    struct Surface *floor;
    waterLevel = find_water_floor(x, (gCheckingSurfaceCollisionsForCamera ? gLakituState.pos[1] : gMarioState->pos[1]), z, &floor);
    if ((p != NULL) && (waterLevel == FLOOR_LOWER_LIMIT)) {
#else
    if (p != NULL) {
#endif
        numRegions = *p++;
        for ((i = 0); (i < numRegions); (i++)) {
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
#if PUPPYPRINT_DEBUG
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
#if PUPPYPRINT_DEBUG
    OSTime first = osGetTime();
#endif
    if (p != NULL) {
        numRegions = *p++;
        for ((i = 0); (i < numRegions); (i++)) {
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
#if PUPPYPRINT_DEBUG
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
    for ((i = 0); (i < 3); (i++)) {
        j = (i + 1);
        if (j >= 3) j = 0;
        dx = ABSF(sx[i] - sx[j]);
        if (dx > dxMax) dxMax = dx;
        dy = ABSF(sy[i] - sy[j]);
        if (dy > dyMax) dyMax = dy;
        dz = ABSF(sz[i] - sz[j]);
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

// Check if the ray intersects a specific surface
Bool32 ray_surface_intersect(Vec3f orig, Vec3f dir, f32 dir_length, struct Surface *surface, Vec3f hit_pos, f32 *length) {
    Vec3f v0, v1, v2; // vertices
    Vec3f e1, e2;     // edges
    Vec3f h, s, q;
    register f32 a, f, u, v;
    Vec3f add_dir;
    Vec3n norm;
    // Get surface normal and some other stuff
    norm[0] = surface->normal.x;
    norm[1] = surface->normal.y;
    norm[2] = surface->normal.z;
    vec3_mul_val(norm, RAY_OFFSET);
    vec3_copy(v0, surface->vertex1);
    vec3_copy(v1, surface->vertex2);
    vec3_copy(v2, surface->vertex3);
    vec3_add( v0, norm);
    vec3_add( v1, norm);
    vec3_add( v2, norm);
    vec3_diff(e1, v1, v0); // edge 1
    vec3_diff(e2, v2, v0); // edge 2
    vec3_cross(h, dir, e2);
    // Check if we're perpendicular from the surface
    a = vec3_dot(e1, h);
    if ((a > -NEAR_ZERO) && (a < NEAR_ZERO)) return FALSE;
    // Check if we're making contact with the surface
    f = (1.0f / a); // inverse dot of edge 1
    vec3_diff(s, orig, v0);
    u = (f * vec3_dot(s, h));
    if ((u < 0.0f) || (u > 1.0f)) return FALSE;
    vec3_cross(q, s, e1);
    v = (f * vec3_dot(dir, q));
    if ((v < 0.0f) || ((u + v) > 1.0f)) return FALSE;
    // Get the length between our origin and the surface contact point
    *length = (f * vec3_dot(e2, q));
    if ((*length <= NEAR_ZERO) || (*length > dir_length)) return FALSE;
    // Successful contact
    vec3_copy(add_dir, dir);
    vec3_mul_val(add_dir, *length);
    vec3_sum(hit_pos, orig, add_dir);
    return TRUE;
}

void find_surface_on_ray_list(struct SurfaceNode *list, Vec3f orig, Vec3f dir, f32 dir_length, struct Surface **hit_surface, Vec3f hit_pos, f32 *max_length) {
    Bool32 hit;
    f32 length;
    Vec3f chk_hit_pos;
    register f32 top, bottom;
#if PUPPYPRINT_DEBUG
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
            if ((list->surface->type == SURFACE_NEW_WATER) || (list->surface->type == SURFACE_NEW_WATER_BOTTOM)) continue;
#endif
            if ((list->surface->type == SURFACE_INTANGIBLE) || (list->surface->flags & SURFACE_FLAG_NO_CAM_COLLISION)) continue;
        }
        // Reject surface if out of vertical bounds
        if ((list->surface->lowerY > top) || (list->surface->upperY < bottom)) continue;
        // Check intersection between the ray and this surface
        if (((hit = ray_surface_intersect(orig, dir, dir_length, list->surface, chk_hit_pos, &length)) != 0) && (length <= *max_length)) {
            *hit_surface = list->surface;
            vec3_copy(hit_pos, chk_hit_pos);
            *max_length = length;
        }
    }
#if PUPPYPRINT_DEBUG
    collisionTime[perfIteration] += (osGetTime() - first);
#endif
}

void find_surface_on_ray_cell(CellIndex cellX, CellIndex cellZ, Vec3f orig, Vec3n normalized_dir, f32 dir_length, struct Surface **hit_surface, Vec3f hit_pos, f32 *max_length, s32 flags) {
    // Skip if OOB
    if ((cellX >= 0) && (cellX <= (NUM_CELLS - 1)) && (cellZ >= 0) && (cellZ <= (NUM_CELLS - 1))) {
        // Iterate through each surface in this partition
        if ((normalized_dir[1] > -NEAR_ONE) && (flags & RAYCAST_FIND_CEIL)) {
            find_surface_on_ray_list(gStaticSurfacePartition [cellZ][cellX][SPATIAL_PARTITION_CEILS ].next, orig, normalized_dir, dir_length, hit_surface, hit_pos, max_length);
            find_surface_on_ray_list(gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_CEILS ].next, orig, normalized_dir, dir_length, hit_surface, hit_pos, max_length);
        }
        if ((normalized_dir[1] <  NEAR_ONE) && (flags & RAYCAST_FIND_FLOOR)) {
            find_surface_on_ray_list(gStaticSurfacePartition [cellZ][cellX][SPATIAL_PARTITION_FLOORS].next, orig, normalized_dir, dir_length, hit_surface, hit_pos, max_length);
            find_surface_on_ray_list(gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_FLOORS].next, orig, normalized_dir, dir_length, hit_surface, hit_pos, max_length);
        }
        if (flags & RAYCAST_FIND_WALL) {
            find_surface_on_ray_list(gStaticSurfacePartition [cellZ][cellX][SPATIAL_PARTITION_WALLS ].next, orig, normalized_dir, dir_length, hit_surface, hit_pos, max_length);
            find_surface_on_ray_list(gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_WALLS ].next, orig, normalized_dir, dir_length, hit_surface, hit_pos, max_length);
        }
#ifdef NEW_WATER_SURFACES
        if (flags & RAYCAST_FIND_WATER) {
            find_surface_on_ray_list(gStaticSurfacePartition [cellZ][cellX][SPATIAL_PARTITION_WATER ].next, orig, normalized_dir, dir_length, hit_surface, hit_pos, max_length);
            find_surface_on_ray_list(gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_WATER ].next, orig, normalized_dir, dir_length, hit_surface, hit_pos, max_length);
        }
#endif
    }
}

void find_surface_on_ray(Vec3f orig, Vec3f dir, struct Surface **hit_surface, Vec3f hit_pos, s32 flags) {
    Vec3n normalized_dir;
    register f32 step, dx, dz;
    s32 i;
    // Set that no surface has been hit
    *hit_surface = NULL;
    vec3_sum(hit_pos, orig, dir);
    // Get normalized direction
    register f32 dir_length = vec3_mag(dir);
    f32 max_length = dir_length;
    vec3_copy(normalized_dir, dir);
    vec3_normalize(normalized_dir);
    // Get our cell coordinate
    register f32 fCellX          = ((orig[0] + LEVEL_BOUNDARY_MAX) / CELL_SIZE);
    register f32 fCellZ          = ((orig[2] + LEVEL_BOUNDARY_MAX) / CELL_SIZE);
    register CellIndex cellX     = fCellX;
    register CellIndex cellZ     = fCellZ;
    register CellIndex cellPrevX = cellX;
    register CellIndex cellPrevZ = cellZ;
    // Don't do DDA if straight down
    if ((normalized_dir[1] >= NEAR_ONE) || (normalized_dir[1] <= -NEAR_ONE)) {
        find_surface_on_ray_cell(cellX, cellZ, orig, normalized_dir, dir_length, hit_surface, hit_pos, &max_length, flags);
        return;
    }
    // Get cells we cross using DDA
    if (ABSF(dir[0]) >= ABSF(dir[2])) {
        step = ((RAY_STEPS * ABSF(dir[0])) / CELL_SIZE);
    } else {
        step = ((RAY_STEPS * ABSF(dir[2])) / CELL_SIZE);
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
void debug_surface_list_info(f32 x, f32 z) {
    struct SurfaceNode *list;
    s32 numFloors = 0;
    s32 numWalls  = 0;
    s32 numCeils  = 0;
    register const CellIndex cellX = ((x + LEVEL_BOUNDARY_MAX) / CELL_SIZE);
    register const CellIndex cellZ = ((z + LEVEL_BOUNDARY_MAX) / CELL_SIZE);
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
