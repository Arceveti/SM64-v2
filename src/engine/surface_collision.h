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

s32  floor_type_exists_in_current_cell(f32 xPos, f32 zPos, s16 type, s32 dynamic);
s32  f32_find_wall_collision(   f32 *xPtr, f32 *yPtr, f32 *zPtr, f32 offsetY, f32 radius);
s32  find_wall_collisions(struct WallCollisionData *colData);
s32  collide_with_walls(        Vec3f pos, f32 offsetY, f32 radius);
f32  find_ceil(                 f32  xPos, f32  yPos, f32  zPos, struct Surface **pceil);
f32  find_floor_height_and_data(f32  xPos, f32  yPos, f32  zPos, struct FloorGeometry **floorGeo);
f32  find_floor_height(         f32  x,    f32  y,    f32  z);
f32  find_floor(                f32  xPos, f32  yPos, f32  zPos, struct Surface **pfloor);
f32  find_water_level_and_floor(f32  x,               f32  z,    struct Surface **pfloor);
f32  find_water_level(          f32  x,               f32  z);
f32  find_poison_gas_level(     f32  x,               f32  z);
void debug_surface_list_info(   f32  xPos,            f32  zPos);

#endif // SURFACE_COLLISION_H
