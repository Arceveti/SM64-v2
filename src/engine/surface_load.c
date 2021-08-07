#include <PR/ultratypes.h>

#include "prevent_bss_reordering.h"

#include "sm64.h"
#include "game/ingame_menu.h"
#include "graph_node.h"
#include "behavior_script.h"
#include "behavior_data.h"
#if defined(FAST_INVSQRT) && defined(FAST_INVSQRT_SURFACES)
#include "math_util.h"
#endif
#include "game/memory.h"
#include "game/object_helpers.h"
#include "game/macro_special_objects.h"
#include "surface_collision.h"
#include "game/mario.h"
#include "game/object_list_processor.h"
#include "surface_load.h"

#include "config.h"

/**
 * Partitions for course and object surfaces. The arrays represent
 * the 16x16 cells that each level is split into.
 */
SpatialPartitionCell gStaticSurfacePartition[ NUM_CELLS][NUM_CELLS];
SpatialPartitionCell gDynamicSurfacePartition[NUM_CELLS][NUM_CELLS];

/**
 * Pools of data to contain either surface nodes or surfaces.
 */
struct SurfaceNode *sSurfaceNodePool;
struct Surface     *sSurfacePool;

/**
 * The size of the surface pool (2300).
 */
s16 sSurfacePoolSize;
u8  gSurfacePoolError = 0x0;

/**
 * Allocate the part of the surface node pool to contain a surface node.
 */
static struct SurfaceNode *alloc_surface_node(void) {
    struct SurfaceNode *node = &sSurfaceNodePool[gSurfaceNodesAllocated];
    gSurfaceNodesAllocated++;
    node->next = NULL;
    if (gSurfaceNodesAllocated >= SURFACE_NODE_POOL_SIZE) gSurfacePoolError |= NOT_ENOUGH_ROOM_FOR_NODES;
    return node;
}

/**
 * Allocate the part of the surface pool to contain a surface and
 * initialize the surface.
 */
static struct Surface *alloc_surface(void) {
    struct Surface *surface = &sSurfacePool[gSurfacesAllocated];
    gSurfacesAllocated++;
    if (gSurfacesAllocated >= sSurfacePoolSize) gSurfacePoolError |= NOT_ENOUGH_ROOM_FOR_SURFACES;
    surface->type   = 0;
    surface->force  = 0;
    surface->flags  = SURFACE_FLAG_NONE;
    surface->room   = 0;
    surface->object = NULL;
    return surface;
}

/**
 * Iterates through the entire partition, clearing the surfaces.
 */
static void clear_spatial_partition(SpatialPartitionCell *cells) {
    register s32 i = NUM_CELLS * NUM_CELLS;
    while (i--) {
        (*cells)[SPATIAL_PARTITION_FLOORS].next = NULL;
        (*cells)[SPATIAL_PARTITION_CEILS ].next = NULL;
        (*cells)[SPATIAL_PARTITION_WALLS ].next = NULL;
        (*cells)[SPATIAL_PARTITION_WATER ].next = NULL;
        cells++;
    }
}

/**
 * Clears the static (level) surface partitions for new use.
 */
static void clear_static_surfaces(void) {
    clear_spatial_partition(&gStaticSurfacePartition[0][0]);
}

/**
 * Add a surface to the correct cell list of surfaces.
 * @param dynamic Determines whether the surface is static or dynamic
 * @param cellX The X position of the cell in which the surface resides
 * @param cellZ The Z position of the cell in which the surface resides
 * @param surface The surface to add
 */
static void add_surface_to_cell(s16 dynamic, s16 cellX, s16 cellZ, struct Surface *surface) {
    struct SurfaceNode *newNode = alloc_surface_node();
    struct SurfaceNode *list;
    s16 surfacePriority;
    s16 priority;
    s16 sortDir;
    s16 listIndex;
    s16 isWater = (surface->type == SURFACE_NEW_WATER || surface->type == SURFACE_NEW_WATER_BOTTOM);
    if (surface->normal.y > MIN_FLOOR_NORMAL_Y) {
        listIndex = isWater ? SPATIAL_PARTITION_WATER : SPATIAL_PARTITION_FLOORS;
        sortDir =  1; // highest to lowest, then insertion order
    } else if (surface->normal.y < MAX_CEIL_NORMAL_Y) {
        listIndex = SPATIAL_PARTITION_CEILS;
        sortDir = -1; // lowest to highest, then insertion order
    } else {
        listIndex = SPATIAL_PARTITION_WALLS;
        sortDir =  0; // insertion order
#ifndef BETTER_WALL_COLLISION
        // Vanilla is 0.707 ~cos(50)
        // Why are these cos(50) instead of cos(45)?
        if (surface->normal.x < -COS50 || surface->normal.x > COS50) surface->flags |= SURFACE_FLAG_X_PROJECTION;
#endif
    }
    surfacePriority  = surface->upperY * sortDir;
    newNode->surface = surface;
    list             = &(dynamic ? gDynamicSurfacePartition : gStaticSurfacePartition)[cellZ][cellX][listIndex];
    // Loop until we find the appropriate place for the surface in the list.
    while (list->next != NULL) {
        priority  = list->next->surface->vertex1[1] * sortDir;
        if (surfacePriority > priority) break;
        list      = list->next;
    }
    newNode->next = list->next;
    list->next    = newNode;
}

/**
 * Returns the lowest of three values.
 */
static s16 min_3(s16 a0, s16 a1, s16 a2) {
    if (a1 < a0) a0 = a1;
    if (a2 < a0) a0 = a2;
    return a0;
}

/**
 * Returns the highest of three values.
 */
static s16 max_3(s16 a0, s16 a1, s16 a2) {
    if (a1 > a0) a0 = a1;
    if (a2 > a0) a0 = a2;
    return a0;
}

/**
 * Every level is split into 16 * 16 cells of surfaces (to limit computing
 * time). This function determines the lower cell for a given x/z position.
 * @param coord The coordinate to test
 */
static s16 lower_cell_index(s32 coord) {
    s16 index;
    // Move from range [-0x2000, 0x2000) to [0, 0x4000)
    coord += LEVEL_BOUNDARY_MAX;
    if (coord < 0) coord = 0;
    // [0, 16)
    index = coord / CELL_SIZE;
    // Include extra cell if close to boundary
    //! Some wall checks are larger than the buffer, meaning wall checks can
    //  miss walls that are near a cell border.
    if (coord % CELL_SIZE < 50) index--;
    if (index < 0) index = 0;
    // Potentially > 15, but since the upper index is <= 15, not exploitable
    return index;
}

/**
 * Every level is split into 16 * 16 cells of surfaces (to limit computing
 * time). This function determines the upper cell for a given x/z position.
 * @param coord The coordinate to test
 */
static s16 upper_cell_index(s32 coord) {
    s16 index;
    // Move from range [-0x2000, 0x2000) to [0, 0x4000)
    coord += LEVEL_BOUNDARY_MAX;
    if (coord < 0) coord = 0;
    // [0, 16)
    index = coord / CELL_SIZE;
    // Include extra cell if close to boundary
    //! Some wall checks are larger than the buffer, meaning wall checks can
    //  miss walls that are near a cell border.
    if (coord % CELL_SIZE > CELL_SIZE - 50) index++;
    if (index > NUM_CELLS_INDEX) index = NUM_CELLS_INDEX;
    // Potentially < 0, but since lower index is >= 0, not exploitable
    return index;
}

#ifdef GENERAL_CELLS
// Arthurtilly
u32 gCellGridX =   5;
u32 gCellSizeX = 450;
u32 gCellGridY =   5;
u32 gCellSizeY = 450;
u32 gCellGridZ =   5;
u32 gCellSizeZ = 450;

s16 cell_index_to_array(s16 x, s16 y, s16 z) {
    return x + gCellGridX * (z + gCellGridZ * y);
}

s16 get_cell_index(s16 pos, u16 numCells, u32 cellSize, u32 offset) {
    s16 index;
    if (numCells == 1) return 0;
    if (offset == 1) {// Lower
        pos -= 20;
    } else if (offset == 2) {// Upper
        pos += 20;
    }
    if (numCells & 0x1) pos += (cellSize / 2);
    index = ((f32)pos / cellSize) + (numCells/2);
    if (index < 0) {
        index = 0;
    } else if (index >= numCells) {
        index = numCells - 1;
    }
    return index;
}

static void add_surface(struct Surface *surface, s32 dynamic) {
    s16 minX, minY, minZ, maxX, maxY, maxZ;
    u16 minCellX, minCellY, minCellZ, maxCellX, maxCellY, maxCellZ;
    u16 cellZ, cellY, cellX;
    minX     = min_3(surface->vertex1[0], surface->vertex2[0], surface->vertex3[0]);
    minY     = min_3(surface->vertex1[1], surface->vertex2[1], surface->vertex3[1]);
    minZ     = min_3(surface->vertex1[2], surface->vertex2[2], surface->vertex3[2]);
    maxX     = max_3(surface->vertex1[0], surface->vertex2[0], surface->vertex3[0]);
    maxY     = max_3(surface->vertex1[1], surface->vertex2[1], surface->vertex3[1]);
    maxZ     = max_3(surface->vertex1[2], surface->vertex2[2], surface->vertex3[2]);
    minCellX = get_cell_index(minX, gCellGridX, gCellSizeX, 1);
    maxCellX = get_cell_index(maxX, gCellGridX, gCellSizeX, 2);
    minCellY = get_cell_index(minY, gCellGridY, gCellSizeY, 1);
    maxCellY = get_cell_index(maxY, gCellGridY, gCellSizeY, 2);
    minCellZ = get_cell_index(minZ, gCellGridZ, gCellSizeZ, 1);
    maxCellZ = get_cell_index(maxZ, gCellGridZ, gCellSizeZ, 2);
    for (cellZ = minCellZ; cellZ <= maxCellZ; cellZ++) {
        for (cellY = minCellY; cellY <= maxCellY; cellY++) {
            for (cellX = minCellX; cellX <= maxCellX; cellX++) {
                add_surface_to_cell(cellX, cellY, cellZ, surface);
            }
        }
    }
}
#else
/**
 * Every level is split into 16x16 cells, this takes a surface, finds
 * the appropriate cells (with a buffer), and adds the surface to those
 * cells.
 * @param surface The surface to check
 * @param dynamic Boolean determining whether the surface is static or dynamic
 */
static void add_surface(struct Surface *surface, s32 dynamic) {
    s16 minX, minZ, maxX, maxZ;
    s16 minCellX, minCellZ, maxCellX, maxCellZ;
    s16 cellZ, cellX;
    minX     = min_3(surface->vertex1[0], surface->vertex2[0], surface->vertex3[0]);
    minZ     = min_3(surface->vertex1[2], surface->vertex2[2], surface->vertex3[2]);
    maxX     = max_3(surface->vertex1[0], surface->vertex2[0], surface->vertex3[0]);
    maxZ     = max_3(surface->vertex1[2], surface->vertex2[2], surface->vertex3[2]);
    minCellX = lower_cell_index(minX);
    maxCellX = upper_cell_index(maxX);
    minCellZ = lower_cell_index(minZ);
    maxCellZ = upper_cell_index(maxZ);
    for (cellZ = minCellZ; cellZ <= maxCellZ; cellZ++) {
        for (cellX = minCellX; cellX <= maxCellX; cellX++) {
            add_surface_to_cell(dynamic, cellX, cellZ, surface);
        }
    }
}
#endif

/**
 * Initializes a Surface struct using the given vertex data
 * @param vertexData The raw data containing vertex positions
 * @param vertexIndices Helper which tells positions in vertexData to start reading vertices
 */
static struct Surface *read_surface_data(s16 *vertexData, s16 **vertexIndices) {
    struct Surface *surface;
    register s32 x1, y1, z1;
    register s32 x2, y2, z2;
    register s32 x3, y3, z3;
    f32 nx, ny, nz;
    f32 mag;
    s16 offset1, offset2, offset3;

    offset1 = 3 * (*vertexIndices)[0];
    offset2 = 3 * (*vertexIndices)[1];
    offset3 = 3 * (*vertexIndices)[2];

    x1 = *(vertexData + offset1 + 0);
    y1 = *(vertexData + offset1 + 1);
    z1 = *(vertexData + offset1 + 2);

    x2 = *(vertexData + offset2 + 0);
    y2 = *(vertexData + offset2 + 1);
    z2 = *(vertexData + offset2 + 2);

    x3 = *(vertexData + offset3 + 0);
    y3 = *(vertexData + offset3 + 1);
    z3 = *(vertexData + offset3 + 2);

    // (v2 - v1) x (v3 - v2)
    nx = (y2 - y1) * (z3 - z2) - (z2 - z1) * (y3 - y2);
    ny = (z2 - z1) * (x3 - x2) - (x2 - x1) * (z3 - z2);
    nz = (x2 - x1) * (y3 - y2) - (y2 - y1) * (x3 - x2);

#if defined(FAST_INVSQRT) && defined(FAST_INVSQRT_SURFACES)
    mag = Q_rsqrtf(nx * nx + ny * ny + nz * nz);
#else
    mag = sqrtf(nx * nx + ny * ny + nz * nz);

    // Checking to make sure no DIV/0
    if (mag < 0.0001f) return NULL;
    mag = (f32)(1.0f / mag);
#endif
    nx *= mag;
    ny *= mag;
    nz *= mag;

    surface = alloc_surface();

    surface->vertex1[0] = x1;
    surface->vertex2[0] = x2;
    surface->vertex3[0] = x3;

    surface->vertex1[1] = y1;
    surface->vertex2[1] = y2;
    surface->vertex3[1] = y3;

    surface->vertex1[2] = z1;
    surface->vertex2[2] = z2;
    surface->vertex3[2] = z3;

    surface->normal.x   = nx;
    surface->normal.y   = ny;
    surface->normal.z   = nz;

    surface->originOffset = -(nx * x1 + ny * y1 + nz * z1);

    surface->lowerY = min_3(y1, y2, y3) - 5;
    surface->upperY = max_3(y1, y2, y3) + 5;

    return surface;
}

#ifndef ALL_SURFACES_HAVE_FORCE
/**
 * Returns whether a surface has exertion/moves Mario
 * based on the surface type.
 */
static s32 surface_has_force(s16 surfaceType) {
    return (surfaceType == SURFACE_0004
         || surfaceType == SURFACE_FLOWING_WATER
         || surfaceType == SURFACE_DEEP_MOVING_QUICKSAND
         || surfaceType == SURFACE_SHALLOW_MOVING_QUICKSAND
         || surfaceType == SURFACE_MOVING_QUICKSAND
         || surfaceType == SURFACE_HORIZONTAL_WIND
         || surfaceType == SURFACE_INSTANT_MOVING_QUICKSAND);
}
#endif

/**
 * Returns whether a surface should have the
 * SURFACE_FLAG_NO_CAM_COLLISION flag.
 */
static s32 surf_has_no_cam_collision(s16 surfaceType) {
    if (surfaceType == SURFACE_NO_CAM_COLLISION
     || surfaceType == SURFACE_NO_CAM_COLLISION_77
     || surfaceType == SURFACE_NO_CAM_COL_VERY_SLIPPERY
     || surfaceType == SURFACE_SWITCH) return SURFACE_FLAG_NO_CAM_COLLISION;
    return SURFACE_FLAG_NONE;
}

/**
 * Load in the surfaces for a given surface type. This includes setting the flags,
 * exertion, and room.
 */
static void load_static_surfaces(s16 **data, s16 *vertexData, s16 surfaceType, s8 **surfaceRooms) {
    s32 i;
    s32 numSurfaces;
    struct Surface *surface;
    s8 room = 0;
#ifndef ALL_SURFACES_HAVE_FORCE
    s16 hasForce = surface_has_force(surfaceType);
#endif
    s16 flags = surf_has_no_cam_collision(surfaceType);
    numSurfaces = *(*data);
    (*data)++;
    for (i = 0; i < numSurfaces; i++) {
        if (*surfaceRooms != NULL) room = *(*surfaceRooms)++;
        surface = read_surface_data(vertexData, data);
        if (surface != NULL) {
            surface->room  = room;
            surface->type  = surfaceType;
            surface->flags = (s8) flags;
#ifdef ALL_SURFACES_HAVE_FORCE
            surface->force = *(*data + 3);
#else
            surface->force = (hasForce ? *(*data + 3) : 0);
#endif
            add_surface(surface, FALSE);
        }
#ifdef ALL_SURFACES_HAVE_FORCE
        *data += 4;
#else
        *data += (hasForce ? 4 : 3);
#endif
    }
}

/**
 * Read the data for vertices for reference by triangles.
 */
static s16 *read_vertex_data(s16 **data) {
    s32 numVertices;
    s16 *vertexData;
    numVertices = *(*data);
    (*data)++;
    vertexData  =   *data;
    *data += 3 * numVertices;
    return vertexData;
}

/**
 * Loads in special environmental regions, such as water, poison gas, and JRB fog.
 */
static void load_environmental_regions(s16 **data) {
    s32 numRegions;
    s32 i;
    gEnvironmentRegions =   *data;
    numRegions          = *(*data)++;
    for (i = 0; i < numRegions; i++) {
        *data += 5;
        gEnvironmentLevels[i] = *(*data)++;
    }
}

/**
 * Allocate some of the main pool for surfaces (2300 surf) and for surface nodes (7000 nodes).
 */
void alloc_surface_pools(void) {
    sSurfacePoolSize = SURFACE_POOL_SIZE;
    sSurfaceNodePool = main_pool_alloc(SURFACE_NODE_POOL_SIZE * sizeof(struct SurfaceNode), MEMORY_POOL_LEFT);
    sSurfacePool     = main_pool_alloc(      sSurfacePoolSize * sizeof(struct Surface    ), MEMORY_POOL_LEFT);
    gCCMEnteredSlide = FALSE;
    reset_red_coins_collected();
}

#ifdef NO_SEGMENTED_MEMORY
/**
 * Get the size of the terrain data, to get the correct size when copying later.
 */
u32 get_area_terrain_size(s16 *data) {
    s16 *startPos = data;
    s32 end = FALSE;
    s16 terrainLoadType;
    s32 numVertices;
    s32 numRegions;
    s32 numSurfaces;
#ifndef ALL_SURFACES_HAVE_FORCE
    s16 hasForce;
#endif
    while (!end) {
        terrainLoadType = *data++;
        switch (terrainLoadType) {
            case TERRAIN_LOAD_VERTICES:
                numVertices = *data++;
                data += 3 * numVertices;
                break;
            case TERRAIN_LOAD_OBJECTS:
                data += get_special_objects_size(data);
                break;
            case TERRAIN_LOAD_ENVIRONMENT:
                numRegions = *data++;
                data += 6 * numRegions;
                break;
            case TERRAIN_LOAD_CONTINUE:
                continue;
            case TERRAIN_LOAD_END:
                end = TRUE;
                break;
            default:
                numSurfaces = *data++;
#ifdef ALL_SURFACES_HAVE_FORCE
                data += 4 * numSurfaces;
#else
                hasForce = surface_has_force(terrainLoadType);
                data += (3 + hasForce) * numSurfaces;
#endif
                break;
        }
    }
    return data - startPos;
}
#endif


/**
 * Process the level file, loading in vertices, surfaces, some objects, and environmental
 * boxes (water, gas, JRB fog).
 */
void load_area_terrain(s16 index, s16 *data, s8 *surfaceRooms, s16 *macroObjects) {
    s16 terrainLoadType;
    s16 *vertexData        = NULL;
    // Initialize the data for this.
    gEnvironmentRegions    = NULL;
    gSurfaceNodesAllocated = 0;
    gSurfacesAllocated     = 0;
    clear_static_surfaces();
    // A while loop iterating through each section of the level data. Sections of data
    // are prefixed by a terrain "type." This type is reused for surfaces as the surface
    // type.
    while (TRUE) {
        terrainLoadType = *data;
        data++;
        if (TERRAIN_LOAD_IS_SURFACE_TYPE_LOW(terrainLoadType)) {
            load_static_surfaces(&data, vertexData, terrainLoadType, &surfaceRooms);
        } else if (terrainLoadType == TERRAIN_LOAD_VERTICES) {
            vertexData = read_vertex_data(&data);
        } else if (terrainLoadType == TERRAIN_LOAD_OBJECTS) {
            spawn_special_objects(index, &data);
        } else if (terrainLoadType == TERRAIN_LOAD_ENVIRONMENT) {
            load_environmental_regions(&data);
        } else if (terrainLoadType == TERRAIN_LOAD_CONTINUE) {
            continue;
        } else if (terrainLoadType == TERRAIN_LOAD_END) {
            break;
        } else if (TERRAIN_LOAD_IS_SURFACE_TYPE_HIGH(terrainLoadType)) {
            load_static_surfaces(&data, vertexData, terrainLoadType, &surfaceRooms);
            continue;
        }
    }
    if (macroObjects != NULL && *macroObjects != -1) {
        // If the first macro object presetID is within the range [0, 29].
        // Generally an early spawning method, every object is in BBH (the first level).
        if (0 <= *macroObjects && *macroObjects < 30) {
            spawn_macro_objects_hardcoded(index, macroObjects);
        } else { // A more general version that can spawn more objects.
            spawn_macro_objects(index, macroObjects);
        }
    }
    gNumStaticSurfaceNodes = gSurfaceNodesAllocated;
    gNumStaticSurfaces     = gSurfacesAllocated;
}

/**
 * If not in time stop, clear the surface partitions.
 */
void clear_dynamic_surfaces(void) {
    if (!(gTimeStopState & TIME_STOP_ACTIVE)) {
        gSurfacesAllocated     = gNumStaticSurfaces;
        gSurfaceNodesAllocated = gNumStaticSurfaceNodes;
        clear_spatial_partition(&gDynamicSurfacePartition[0][0]);
    }
}

/**
 * Applies an object's transformation to the object's vertices.
 */
void transform_object_vertices(s16 **data, s16 *vertexData) {
    register s16 *vertices;
    register f32 vx, vy, vz;
    register s32 numVertices;
    Mat4 *objectTransform;
    Mat4 m;
    objectTransform = &gCurrentObject->transform;
    numVertices     = *(*data);
    (*data)++;
    vertices        =   *data;
    if (gCurrentObject->header.gfx.throwMatrix == NULL) {
        gCurrentObject->header.gfx.throwMatrix = objectTransform;
        obj_build_transform_from_pos_and_angle(gCurrentObject, O_POS_INDEX, O_FACE_ANGLE_INDEX);
    }
    obj_apply_scale_to_matrix(gCurrentObject, m, *objectTransform);
    // Go through all vertices, rotating and translating them to transform the object.
    while (numVertices--) {
        vx = *(vertices++);
        vy = *(vertices++);
        vz = *(vertices++);
        //! No bounds check on vertex data
        if (vx == 0 && vy == 0 && vz == 0) {
            *vertexData++ = (s16)(m[3][0]);
            *vertexData++ = (s16)(m[3][1]);
            *vertexData++ = (s16)(m[3][2]);
        } else {
            *vertexData++ = (s16)(vx * m[0][0] + vy * m[1][0] + vz * m[2][0] + m[3][0]);
            *vertexData++ = (s16)(vx * m[0][1] + vy * m[1][1] + vz * m[2][1] + m[3][1]);
            *vertexData++ = (s16)(vx * m[0][2] + vy * m[1][2] + vz * m[2][2] + m[3][2]);
        }
    }
    *data = vertices;
}

/**
 * Load in the surfaces for the gCurrentObject. This includes setting the flags, exertion, and room.
 */
void load_object_surfaces(s16 **data, s16 *vertexData) {
    s32 surfaceType;
    s32 i;
    s32 numSurfaces;
#ifndef ALL_SURFACES_HAVE_FORCE
    s16 hasForce;
#endif
    s16 flags;
    s16 room;
    surfaceType = *(*data);
    (*data)++;
    numSurfaces = *(*data);
    (*data)++;
#ifndef ALL_SURFACES_HAVE_FORCE
    hasForce = surface_has_force(surfaceType);
#endif
    flags  = surf_has_no_cam_collision(surfaceType);
    flags |= SURFACE_FLAG_DYNAMIC;
    // The DDD warp is initially loaded at the origin and moved to the proper
    // position in paintings.c and doesn't update its room, so set it here.
    room = (gCurrentObject->behavior == segmented_to_virtual(bhvDddWarp) ? 5 : 0);
    for (i = 0; i < numSurfaces; i++) {
        struct Surface *surface = read_surface_data(vertexData, data);
        if (surface != NULL) {
            surface->object = gCurrentObject;
            surface->type   = surfaceType;
#ifdef ALL_SURFACES_HAVE_FORCE
            surface->force = *(*data + 3);
#else
            surface->force  = (hasForce ? *(*data + 3) : 0);
#endif
            surface->flags |= flags;
            surface->room   = (s8) room;
            add_surface(surface, TRUE);
        }
#ifdef ALL_SURFACES_HAVE_FORCE
        *data += 4;
#else
        *data += (hasForce ? 4 : 3);
#endif
    }
}

/**
 * Transform an object's vertices, reload them, and render the object.
 */
void load_object_collision_model(void) {
    s16 vertexData[600];
    s16 *collisionData = gCurrentObject->collisionData;
    f32 marioDist      = gCurrentObject->oDistanceToMario;
    f32 tangibleDist   = gCurrentObject->oCollisionDistance;
    // On an object's first frame, the distance is set to 19000.0f.
    // If the distance hasn't been updated, update it now.
    if (gCurrentObject->oDistanceToMario == 19000.0f) marioDist = dist_between_objects(gCurrentObject, gMarioObject);
    // If the object collision is supposed to be loaded more than the
    // drawing distance, extend the drawing range.
    if (gCurrentObject->oCollisionDistance > gCurrentObject->oDrawingDistance) gCurrentObject->oDrawingDistance = gCurrentObject->oCollisionDistance;
    // Update if no Time Stop, in range, and in the current room.
    if (!(gTimeStopState & TIME_STOP_ACTIVE) && marioDist < tangibleDist
        && !(gCurrentObject->activeFlags & ACTIVE_FLAG_IN_DIFFERENT_ROOM)) {
        collisionData++;
        transform_object_vertices(&collisionData, vertexData);
        // TERRAIN_LOAD_CONTINUE acts as an "end" to the terrain data.
        while (*collisionData != TERRAIN_LOAD_CONTINUE) load_object_surfaces(&collisionData, vertexData);
    }
    if (marioDist < gCurrentObject->oDrawingDistance) {
        gCurrentObject->header.gfx.node.flags |=  GRAPH_RENDER_ACTIVE;
    } else {
        gCurrentObject->header.gfx.node.flags &= ~GRAPH_RENDER_ACTIVE;
    }
}
