#ifndef DEBUG_BOX_H
#define DEBUG_BOX_H

#ifdef VISUAL_DEBUG

/**
 * @file debug_box.h
 * Draws debug boxes, see debug_box.c for details
 */

#include "types.h"

/**
 * The max amount of debug boxes before debug_box() just returns.
 * You can set this to something higher, but you might run out of space in the gfx pool.
 */
#define MAX_DEBUG_BOXES      512

#define DEBUG_SHAPE_BOX      (1 << 0) // 0x01
#define DEBUG_SHAPE_CYLINDER (1 << 1) // 0x02
#define DEBUG_UCODE_DEFAULT  (1 << 2) // 0x04
#define DEBUG_UCODE_REJ      (1 << 3) // 0x08
#define DEBUG_BOX_CLEAR      (1 << 4) // 0x10

extern Bool8 hitboxView;
extern Bool8 surfaceView;
extern void debug_box_input(void);

void debug_box_color(RGBA32 color);
void debug_box(        Vec3f center, Vec3f bounds,            s32 type);
void debug_box_rot(    Vec3f center, Vec3f bounds, Angle yaw, s32 type);

void debug_box_pos(    Vec3f pMin,   Vec3f pMax,              s32 type);
void debug_box_pos_rot(Vec3f pMin,   Vec3f pMax,   Angle yaw, s32 type);

void render_debug_boxes(s32 type);
extern void visual_surface_loop(void);

#endif

#endif /* DEBUG_BOX_H */
