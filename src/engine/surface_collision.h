#ifndef SURFACE_COLLISION_H
#define SURFACE_COLLISION_H

#include <PR/ultratypes.h>

#include "types.h"

#include "engine/extended_bounds.h"


#define CELL_HEIGHT_LIMIT            20000
#define FLOOR_LOWER_LIMIT           -11000
#define FLOOR_LOWER_LIMIT_MISC      (FLOOR_LOWER_LIMIT + 1000)
// same as FLOOR_LOWER_LIMIT_MISC, explicitly for shadow.c
#define FLOOR_LOWER_LIMIT_SHADOW    (FLOOR_LOWER_LIMIT + 1000)

#define RAYCAST_FIND_FLOOR  (1 << 0) // 0x1
#define RAYCAST_FIND_WALL   (1 << 1) // 0x2
#define RAYCAST_FIND_CEIL   (1 << 2) // 0x4
#define RAYCAST_FIND_WATER  (1 << 3) // 0x8
#define RAYCAST_FIND_ALL    (0xFFFFFFFF)

struct WallCollisionData
{
    /*0x00*/ f32 x, y, z;
    /*0x0C*/ f32 offsetY;
    /*0x10*/ f32 radius;
    /*0x14*/ s16 unused;
    /*0x16*/ s16 numWalls;
    /*0x18*/ struct Surface *walls[4];
};

struct FloorGeometry
{
    f32 unused[4]; // possibly position data?
    f32 normalX;
    f32 normalY;
    f32 normalZ;
    f32 originOffset;
};

s32  floor_type_exists_in_current_cell(f32 xPos, f32 zPos, SurfaceType type, s32 dynamic);
s32  f32_find_wall_collision(   f32 *xPtr, f32 *yPtr, f32 *zPtr, f32 offsetY, f32 radius);
s32  find_wall_collisions(struct WallCollisionData *colData);
s32  collide_with_walls(        Vec3f pos, f32 offsetY, f32 radius);
f32  find_ceil(                 f32  xPos, f32  yPos, f32  zPos, struct Surface **pceil);
f32  find_floor_height_and_data(f32  xPos, f32  yPos, f32  zPos, struct FloorGeometry **floorGeo);
f32  find_floor_height(         f32  x,    f32  y,    f32  z);
f32  find_floor(                f32  xPos, f32  yPos, f32  zPos, struct Surface **pfloor);
f32  find_room_floor(           f32  xPos, f32  yPos, f32  zPos, struct Surface **pfloor);
s32  find_water_level_and_floor(s32  x,               s32  z,    struct Surface **pfloor);
s32  find_water_level(          s32  x,               s32  z);
s32  find_poison_gas_level(     s32  x,               s32  z);
s32 is_surf_within_bounding_box(struct Surface *surf, f32 xMax, f32 yMax, f32 zMax);
s32 is_behind_surface(            Vec3f pos, struct Surface *surf);
s32  is_range_behind_surface(     Vec3f from, Vec3f to, struct Surface *surf, s16 range, SurfaceType surfType);
void find_surface_on_ray(Vec3f orig, Vec3f dir, struct Surface **hit_surface, Vec3f hit_pos, s32 flags);
void debug_surface_list_info(   f32  xPos,            f32  zPos);

#endif // SURFACE_COLLISION_H
