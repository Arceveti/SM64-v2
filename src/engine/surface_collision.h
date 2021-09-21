#pragma once

#include <PR/ultratypes.h>

#include "types.h"

#include "engine/extended_bounds.h"


#define CELL_HEIGHT_LIMIT            20000
#define FLOOR_LOWER_LIMIT           -11000
#define FLOOR_LOWER_LIMIT_MISC      (FLOOR_LOWER_LIMIT + 1000)
// same as FLOOR_LOWER_LIMIT_MISC, explicitly for shadow.c
#define FLOOR_LOWER_LIMIT_SHADOW    (FLOOR_LOWER_LIMIT + 1000)

#define RAY_OFFSET 30.0f /* How many units to extrapolate surfaces when testing for a raycast */
#define RAY_STEPS      4 /* How many steps to do when casting rays, default to quartersteps.  */

#define RAYCAST_FIND_FLOOR  (1 << 0) // 0x1
#define RAYCAST_FIND_WALL   (1 << 1) // 0x2
#define RAYCAST_FIND_CEIL   (1 << 2) // 0x4
#define RAYCAST_FIND_WATER  (1 << 3) // 0x8
#define RAYCAST_FIND_ALL    (0xFFFFFFFF)

#define is_outside_level_bounds(xPos, zPos) (((xPos) <= -LEVEL_BOUNDARY_MAX) || ((xPos) >=  LEVEL_BOUNDARY_MAX) || ((zPos) <= -LEVEL_BOUNDARY_MAX) || ((zPos) >=  LEVEL_BOUNDARY_MAX))

#define get_surface_height_at_location(xPos, zPos, surf) (-((xPos) * (surf)->normal.x + (surf)->normal.z * (zPos) + (surf)->originOffset) / (surf)->normal.y)

#define SURFACE_YAW(s) (atan2s(((s)->normal.z), ((s)->normal.x)))

struct WallCollisionData
{
    /*0x00*/ Vec3f pos; // f32 x, y, z;
    /*0x0C*/ f32 offsetY;
    /*0x10*/ f32 radius;
    /*0x14*/ s16 unused;
    /*0x16*/ s16 numWalls;
    /*0x18*/ struct Surface *walls[MAX_REFEREMCED_WALLS];
};

void   move_towards_wall(struct MarioState *m, f32 amount);
s32    resolve_wall_collisions(Vec3f pos, f32 offsetY, f32 radius);
s32    find_wall_collisions(struct WallCollisionData *colData);
void   resolve_and_return_wall_collision_data(Vec3f pos, f32 offsetY, f32 radius, struct WallCollisionData *collisionData);
s32    collide_with_walls(              Vec3f pos, f32 offsetY, f32 radius);
void   resolve_geometry_collisions(     Vec3f pos, UNUSED Vec3f lastGood);
Bool32 find_wall_displacement(          Vec3f dist, f32 x, f32 y, f32 z, f32 radius);
f32    find_ceil(                                   f32 x, f32 y, f32 z, struct Surface **pceil);
Bool32 floor_type_exists_in_current_cell(           f32 x,        f32 z, SurfaceType type, Bool32 dynamic);
f32    find_floor_height(                           f32 x, f32 y, f32 z);
f32    find_floor(                                  f32 x, f32 y, f32 z, struct Surface **pfloor);
f32    find_room_floor(                             f32 x, f32 y, f32 z, struct Surface **pfloor);
s32    find_water_level_and_floor(                  s32 x,        s32 z, struct Surface **pfloor);
s32    find_water_level(                            s32 x,        s32 z);
s32    find_poison_gas_level(                       s32 x,        s32 z);
Bool32 is_surf_within_bounding_box(struct Surface *surf, f32 xMax, f32 yMax, f32 zMax);
Bool32 is_behind_surface(           Vec3f  pos, struct Surface *surf);
Bool32 is_range_behind_surface(     Vec3f from, Vec3f to,  struct Surface *surf, s16 range, SurfaceType surfType);
void   find_surface_on_ray(         Vec3f orig, Vec3f dir, struct Surface **hit_surface, Vec3f hit_pos, s32 flags);
void   debug_surface_list_info(                       f32 x,        f32 z);
