#pragma once

#include <PR/ultratypes.h>
#include "types.h"

#define ENVFX_MODE_NONE         0x0  // no effects
#define ENVFX_SNOW_NORMAL       0x1  // CCM, SL
#define ENVFX_SNOW_WATER        0x2  // Secret Aquarium, Sunken Ship
#define ENVFX_SNOW_BLIZZARD     0x3  // unused
#define ENVFX_SNOW_LAVA         0x4  //! TODO: Lava embers

#define ENVFX_BUBBLE_START      0xA // Separates snow effects and flower/bubble effects

#define ENVFX_FLOWERS           0xB // unused
#define ENVFX_LAVA_BUBBLES      0xC // LLL, BitFS, Bowser 2
#define ENVFX_WHIRLPOOL_BUBBLES 0xD // DDD
#define ENVFX_JETSTREAM_BUBBLES 0xE // JRB, DDD (submarine area)

struct EnvFxParticle {
    Bool8 isAlive;
    AnimFrame16 animFrame; // lava bubbles and flowers have frame animations
    Vec3i pos;
    // for whirpools
    s32 whirlpoolAngle;  // angle from center
    s32 whirlpoolDist;   // distance from center
    s32 unusedBubbleVar; // set to zero for bubbles when respawning, never used elsewhere
    s32 bubbleY; // for Bubbles, yPos is always set to this
    s8  filler20[56 - 0x20];
};

extern s8 gEnvFxMode;

extern struct EnvFxParticle *gEnvFxBuffer;
extern Vec3i gSnowCylinderLastPos;
extern s16   gSnowParticleCount;

Gfx *envfx_update_particles(s32 snowMode, Vec3s marioPos, Vec3s camTo, Vec3s camFrom);
