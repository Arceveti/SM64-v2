#ifdef PUPPYLIGHTS
#ifndef PUPPYLIGHTS_H
#define PUPPYLIGHTS_H

#include "types.h"
#include "command_macros_base.h"

// The maximum number of lights that can be loaded at once. Any further lights that attempt to be created past this will simply not spawn.
#define MAX_LIGHTS 32
// The maximum number of dynamic lights available at one time.
#define MAX_LIGHTS_DYNAMIC 8

// Two shapes. Choose your destiny.
#define PUPPYLIGHT_SHAPE_CUBE       (1 << 0) // 0x1
#define PUPPYLIGHT_SHAPE_CYLINDER   (1 << 1) // 0x2
#define PUPPYLIGHT_DYNAMIC          (1 << 2) // 0x4
#define PUPPYLIGHT_DIRECTIONAL      (1 << 3) // 0x8

#define PUPPYLIGHT_FLAG_SHADOW      (1 << 0) // 0x1
#define PUPPYLIGHT_FLAG_WET         (1 << 1) // 0x2

#define PUPPYLIGHT_ENVIRONMENT(ambientR, ambientG, ambientB, diffuseR, diffuseG, diffuseB, diffuseX, diffuseY, diffuseZ) \
    CMD_BBBB(0x3F, 0x0C, ambientR, ambientG),                                                                            \
    CMD_BBBB(ambientB, diffuseR, diffuseG, diffuseB),                                                                    \
    CMD_BBBB(diffuseX, diffuseY, diffuseZ, 0x0)

#define PUPPYLIGHT_NODE(r, g, b, a, x, y, z, offsetX, offsetY, offsetZ, yaw, epicentre, room, flags)\
    CMD_BBBB(0x40, 0x18, r, g),                                                                     \
    CMD_BBH(b, a, x),                                                                               \
    CMD_HH(y, z),                                                                                   \
    CMD_HH(offsetX, offsetY),                                                                       \
    CMD_HH(offsetZ, yaw),                                                                           \
    CMD_BBH(epicentre, flags, room)

// How much RAM is allocated to puppylights
#define PUPPYLIGHTS_POOL (sizeof(struct PuppyLight) * MAX_LIGHTS)

extern Lights1 gLevelLight;
extern u16 gNumLights;
extern Bool8 levelAmbient;
extern struct PuppyLight *gPuppyLights[MAX_LIGHTS];
extern struct MemoryPool *gLightsPool;
extern void puppylights_run(Lights1 *src, struct Object *obj, s32 flags, u32 baseColour);
extern void puppylights_object_emit(      struct Object *obj);
extern void cur_obj_enable_light( void);
extern void cur_obj_disable_light(void);
extern void obj_enable_light( struct Object *obj);
extern void obj_disable_light(struct Object *obj);
extern void set_light_properties(struct PuppyLight *light, s32 x, s32 y, s32 z, s32 offsetX, s32 offsetY, s32 offsetZ, Angle32 yaw, s32 epicentre, RGBA32 colour, s32 flags, RoomData room, Bool32 active);
extern void cur_obj_set_light_properties_default(s32 offset, RGBA32 colour);
extern void puppylights_allocate(void);

#endif
#endif