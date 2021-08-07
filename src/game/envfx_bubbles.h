#ifndef ENVFX_BUBBLES_H
#define ENVFX_BUBBLES_H

#include <PR/ultratypes.h>
#include <PR/gbi.h>

#define ENVFX_STATE_UNUSED          0x0
#define ENVFX_STATE_SRC_X           0x1 // whirlpool / jetsream bubble source position
#define ENVFX_STATE_SRC_Y           0x2
#define ENVFX_STATE_SRC_Z           0x3
#define ENVFX_STATE_DEST_X          0x4 // only for whirlpool, where bubbles get sucked in
#define ENVFX_STATE_DEST_Y          0x5
#define ENVFX_STATE_DEST_Z          0x6
#define ENVFX_STATE_PARTICLECOUNT   0x7
#define ENVFX_STATE_PITCH           0x8 // whirlpool can rotate around DEST point
#define ENVFX_STATE_YAW             0x9

// Used to communicate from whirlpool behavior to envfx
extern s16 gEnvFxBubbleConfig[10];
Gfx *envfx_update_bubbles(s32 mode, Vec3s marioPos, Vec3s camTo, Vec3s camFrom);

#endif // ENVFX_BUBBLES_H
