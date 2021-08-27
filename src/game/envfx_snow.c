#include <ultra64.h>

#include "sm64.h"
#include "dialog_ids.h"
#include "game_init.h"
#include "boot/memory.h"
#include "ingame_menu.h"
#include "envfx_snow.h"
#include "envfx_bubbles.h"
#include "engine/surface_collision.h"
#include "engine/math_util.h"
#include "engine/behavior_script.h"
#include "audio/external.h"
#include "obj_behaviors.h"

/**
 * This file contains the function that handles 'environment effects',
 * which are particle effects related to the level type that, unlike
 * object-based particle effects, are rendered more efficiently by manually
 * generating display lists instead of drawing each particle separately.
 * This file implements snow effects, while in 'envfx_bubbles.c' the
 * implementation for flowers (unused), lava bubbles and jet stream bubbles
 * can be found.
 * The main entry point for envfx is at the bottom of this file, which is
 * called from geo_envfx_main in level_geo.c
 */

struct EnvFxParticle *gEnvFxBuffer;
Vec3i gSnowCylinderLastPos;
s16   gSnowParticleCount;
s16   gSnowParticleMaxCount;

/* DATA */
s8 gEnvFxMode = 0;

/// Template for a snow particle triangle
Vtx gSnowTempVtx[3] = { { { { -5,  5,  0 }, 0, {     0,     0 }, { 0x7F, 0x7F, 0x7F, 0xFF } } },
                        { { { -5, -5,  0 }, 0, {     0, 30<<5 }, { 0x7F, 0x7F, 0x7F, 0xFF } } },
                        { { {  5,  5,  0 }, 0, { 30<<5,     0 }, { 0x7F, 0x7F, 0x7F, 0xFF } } } };

// Change these to make snowflakes smaller or bigger
Vec3vs gSnowFlakeVertex1 = { -5,  5, 0 };
Vec3vs gSnowFlakeVertex2 = { -5, -5, 0 };
Vec3vs gSnowFlakeVertex3 = {  5,  5, 0 };

extern void *tiny_bubble_dl_0B006AB0;
extern void *tiny_bubble_dl_gray;
extern void *tiny_bubble_dl_blue;

/**
 * Initialize snow particles by allocating a buffer for storing their state
 * and setting a start amount.
 */
Bool32 envfx_init_snow(s32 mode) {
    switch (mode) {
        case ENVFX_MODE_NONE:     return FALSE;
        case ENVFX_SNOW_NORMAL:   gSnowParticleMaxCount = 140; gSnowParticleCount =   5; break;
        case ENVFX_SNOW_WATER:    gSnowParticleMaxCount =  30; gSnowParticleCount =  30; break;
        case ENVFX_SNOW_BLIZZARD: gSnowParticleMaxCount = 140; gSnowParticleCount = 140; break;
    }
    gEnvFxBuffer = mem_pool_alloc(gEffectsMemoryPool, (gSnowParticleMaxCount * sizeof(struct EnvFxParticle)));
    if (!gEnvFxBuffer) return FALSE;
    bzero(gEnvFxBuffer, (gSnowParticleMaxCount * sizeof(struct EnvFxParticle)));
    gEnvFxMode = mode;
    return TRUE;
}

/**
 * Update the amount of snow particles on screen.
 * Normal snow starts with few flakes and slowly increases to the maximum.
 * For water snow, this is dependent on how deep underwater you are.
 * Blizzard snows starts at the maximum amount and doesn't change.
 */
void envfx_update_snowflake_count(s32 mode, Vec3s marioPos) {
    switch (mode) {
        case ENVFX_SNOW_NORMAL:
            if ((gSnowParticleMaxCount > gSnowParticleCount) && !(gGlobalTimer & 0x3F)) gSnowParticleCount += 5;
            break;
        case ENVFX_SNOW_WATER:
            gSnowParticleCount = ((((s32)(((find_water_level(marioPos[0], marioPos[2]) - 400) - (f32) marioPos[1]) * 1.0e-3f) << 0x10) >> 0x10) * 5);
            if (gSnowParticleCount < 0) gSnowParticleCount = 0;
            if (gSnowParticleCount > gSnowParticleMaxCount) gSnowParticleCount = gSnowParticleMaxCount;
            break;
        case ENVFX_SNOW_BLIZZARD: break;
    }
}

/**
 * Deallocate the buffer storing snow particles and set the environment effect
 * to none.
 */
void envfx_cleanup_snow(void *snowParticleArray) {
    if (gEnvFxMode) {
        if (snowParticleArray) mem_pool_free(gEffectsMemoryPool, snowParticleArray);
        gEnvFxMode = ENVFX_MODE_NONE;
    }
}

/**
 * Check whether the snowflake with the given index is inside view, where
 * 'view' is a cylinder of radius 300 and height 400 centered at the input
 * x, y and z.
 */
Bool32 envfx_is_snowflake_alive(s32 index, s32 snowCylinderX, s32 snowCylinderY, s32 snowCylinderZ) {
    register s32 x = (gEnvFxBuffer + index)->pos[0];
    register s32 y = (gEnvFxBuffer + index)->pos[1];
    register s32 z = (gEnvFxBuffer + index)->pos[2];
    if (sqr(x - snowCylinderX) + sqr(z - snowCylinderZ) > sqr(300)) return FALSE;
    return !((y < (snowCylinderY - 201)) || ((snowCylinderY + 201) < y));
}

/**
 * Update the position of each snowflake. Snowflakes wiggle by having a
 * random value added to their position each frame. If snowflakes get out
 * of view (where view = a small cylinder in front of the camera) their
 * position is reset to somewhere in view.
 * Since the cylinder of snow is so close to the camera, snow flakes would
 * move out of view very quickly when the camera moves. To mitigate this,
 * a portion of the difference between the previous and current snowCylinder
 * position is added to snowflakes to keep them in view for longer. That's
 * why the snow looks a bit off in 3d, it's a lot closer than you'd think
 * but appears to be further by means of hacky position updates. This might
 * have been done because larger, further away snowflakes are occluded easily
 * by level geometry, wasting many particles.
 */
//? can snowCylinder be Vec3i?
void envfx_update_snow_normal(s32 snowCylinderX, s32 snowCylinderY, s32 snowCylinderZ) {
    s32 i;
    Vec3i delta;
    delta[0] = (snowCylinderX - gSnowCylinderLastPos[0]);
    delta[1] = (snowCylinderY - gSnowCylinderLastPos[1]);
    delta[2] = (snowCylinderZ - gSnowCylinderLastPos[2]);
    for ((i = 0); (i < gSnowParticleCount); (i++)) {
        (gEnvFxBuffer + i)->isAlive = envfx_is_snowflake_alive(i, snowCylinderX, snowCylinderY, snowCylinderZ);
        if (!(gEnvFxBuffer + i)->isAlive) {
            (gEnvFxBuffer + i)->pos[0]  = (((400.0f * random_float()) - 200.0f) + snowCylinderX + (s16)(delta[0] * 2));
            (gEnvFxBuffer + i)->pos[2]  = (((400.0f * random_float()) - 200.0f) + snowCylinderZ + (s16)(delta[2] * 2));
            (gEnvFxBuffer + i)->pos[1]  =  ((200.0f * random_float())           + snowCylinderY                      );
            (gEnvFxBuffer + i)->isAlive = TRUE;
        } else {
            (gEnvFxBuffer + i)->pos[0] += (((random_float() * 2) - 1.0f) + (s16)(delta[0] / 1.2f));
            (gEnvFxBuffer + i)->pos[2] += (((random_float() * 2) - 1.0f) + (s16)(delta[2] / 1.2f));
            (gEnvFxBuffer + i)->pos[1] -= (                   2  -         (s16)(delta[1] * 0.8f));
        }
    }
    gSnowCylinderLastPos[0] = snowCylinderX;
    gSnowCylinderLastPos[1] = snowCylinderY;
    gSnowCylinderLastPos[2] = snowCylinderZ;
}

/**
 * Unused function. Basically a copy-paste of envfx_update_snow_normal,
 * but an extra 20 units is added to each snowflake x and snowflakes can
 * respawn in y-range [-200, 200] instead of [0, 200] relative to snowCylinderY
 * They also fall a bit faster (with vertical speed -5 instead of -2).
 */
void envfx_update_snow_blizzard(s32 snowCylinderX, s32 snowCylinderY, s32 snowCylinderZ) {
    s32 i;
    Vec3i delta;
    delta[0] = (snowCylinderX - gSnowCylinderLastPos[0]);
    delta[1] = (snowCylinderY - gSnowCylinderLastPos[1]);
    delta[2] = (snowCylinderZ - gSnowCylinderLastPos[2]);
    for ((i = 0); (i < gSnowParticleCount); (i++)) {
        (gEnvFxBuffer + i)->isAlive = envfx_is_snowflake_alive(i, snowCylinderX, snowCylinderY, snowCylinderZ);
        if (!(gEnvFxBuffer + i)->isAlive) {
            (gEnvFxBuffer + i)->pos[0]  = (((400.0f * random_float()) - 200.0f) + snowCylinderX + (s16)(delta[0] * 2));
            (gEnvFxBuffer + i)->pos[2]  = (((400.0f * random_float()) - 200.0f) + snowCylinderZ + (s16)(delta[2] * 2));
            (gEnvFxBuffer + i)->pos[1]  = (((400.0f * random_float()) - 200.0f) + snowCylinderY                      );
            (gEnvFxBuffer + i)->isAlive = TRUE;
        } else {
            (gEnvFxBuffer + i)->pos[0] += ((random_float() * 2) - 1.0f + (s16)(delta[0] / 1.2f) + 20.0f);
            (gEnvFxBuffer + i)->pos[2] += ((random_float() * 2) - 1.0f + (s16)(delta[2] / 1.2f));
            (gEnvFxBuffer + i)->pos[1] -=                            5 - (s16)(delta[1] * 0.8f);
        }
    }
    gSnowCylinderLastPos[0] = snowCylinderX;
    gSnowCylinderLastPos[1] = snowCylinderY;
    gSnowCylinderLastPos[2] = snowCylinderZ;
}

/**
 * Update the position of underwater snow particles. Since they are stationary,
 * they merely jump back into view when they are out of view.
 */
void envfx_update_snow_water(s32 snowCylinderX, s32 snowCylinderY, s32 snowCylinderZ) {
    s32 i;
    for ((i = 0); (i < gSnowParticleCount); (i++)) {
        (gEnvFxBuffer + i)->isAlive = envfx_is_snowflake_alive(i, snowCylinderX, snowCylinderY, snowCylinderZ);
        if (!(gEnvFxBuffer + i)->isAlive) {
            (gEnvFxBuffer + i)->pos[0]  = (((400.0f * random_float()) - 200.0f) + snowCylinderX);
            (gEnvFxBuffer + i)->pos[2]  = (((400.0f * random_float()) - 200.0f) + snowCylinderZ);
            (gEnvFxBuffer + i)->pos[1]  = (((400.0f * random_float()) - 200.0f) + snowCylinderY);
            (gEnvFxBuffer + i)->isAlive = TRUE;
        }
    }
}

/**
 * Append 15 vertices to 'gfx', which is enough for 5 snowflakes starting at
 * 'index' in the buffer. The 3 input vertices represent the rotated triangle
 * around (0,0,0) that will be translated to snowflake positions to draw the
 * snowflake image.
 */
void append_snowflake_vertex_buffer(Gfx *gfx, s32 index, Vec3s vertex1, Vec3s vertex2, Vec3s vertex3) {
    s32 i = 0;
    Vtx *vertBuf = (Vtx *) alloc_display_list(15 * sizeof(Vtx));
    if (vertBuf == NULL) return;
    for ((i = 0); (i < 15); (i += 3)) {
        vertBuf[i] = gSnowTempVtx[0];
        (vertBuf + i    )->v.ob[0] = ((gEnvFxBuffer + (index + i / 3))->pos[0] + vertex1[0]);
        (vertBuf + i    )->v.ob[1] = ((gEnvFxBuffer + (index + i / 3))->pos[1] + vertex1[1]);
        (vertBuf + i    )->v.ob[2] = ((gEnvFxBuffer + (index + i / 3))->pos[2] + vertex1[2]);
        vertBuf[i + 1] = gSnowTempVtx[1];
        (vertBuf + i + 1)->v.ob[0] = ((gEnvFxBuffer + (index + i / 3))->pos[0] + vertex2[0]);
        (vertBuf + i + 1)->v.ob[1] = ((gEnvFxBuffer + (index + i / 3))->pos[1] + vertex2[1]);
        (vertBuf + i + 1)->v.ob[2] = ((gEnvFxBuffer + (index + i / 3))->pos[2] + vertex2[2]);
        vertBuf[i + 2] = gSnowTempVtx[2];
        (vertBuf + i + 2)->v.ob[0] = ((gEnvFxBuffer + (index + i / 3))->pos[0] + vertex3[0]);
        (vertBuf + i + 2)->v.ob[1] = ((gEnvFxBuffer + (index + i / 3))->pos[1] + vertex3[1]);
        (vertBuf + i + 2)->v.ob[2] = ((gEnvFxBuffer + (index + i / 3))->pos[2] + vertex3[2]);
    }
    gSPVertex(gfx, VIRTUAL_TO_PHYSICAL(vertBuf), 15, 0);
}

/**
 * Updates positions of snow particles and returns a pointer to a display list
 * drawing all snowflakes.
 */
Gfx *envfx_update_snow(s32 snowMode, Vec3s marioPos, Vec3s camFrom, Vec3s camTo) {
    s32 i;
    s16 radius;
    Angle pitch, yaw;
    Vec3s snowCylinderPos;
    Vec3vs vertex1, vertex2, vertex3;
    Gfx *gfxStart;
    Gfx *gfx;
    vec3s_copy(vertex1, gSnowFlakeVertex1);
    vec3s_copy(vertex2, gSnowFlakeVertex2);
    vec3s_copy(vertex3, gSnowFlakeVertex3);
    gfxStart = ((Gfx *) alloc_display_list(((gSnowParticleCount * 6) + 3) * sizeof(Gfx)));
    gfx      = gfxStart;
    if (gfxStart == NULL) return NULL;
    envfx_update_snowflake_count(snowMode, marioPos);
    // Note: to and from are inverted here, so the resulting vector goes towards the camera
    vec3s_get_dist_and_angle(camTo, camFrom, &radius, &pitch, &yaw);
    switch (snowMode) {
        case ENVFX_SNOW_NORMAL:
            // ensure the snow cylinder is no further than 250 units in front
            // of the camera, and no closer than 1 unit.
            if (radius > 250) {
                radius -= 250;
            } else {
                radius = 1;
            }
            vec3s_set_dist_and_angle(camTo, snowCylinderPos, radius, pitch, yaw);
            envfx_update_snow_normal(snowCylinderPos[0], snowCylinderPos[1], snowCylinderPos[2]);
            break;
        case ENVFX_SNOW_WATER:
            if (radius > 500) {
                radius -= 500;
            } else {
                radius = 1;
            }
            vec3s_set_dist_and_angle(camTo, snowCylinderPos, radius, pitch, yaw);
            envfx_update_snow_water(snowCylinderPos[0], snowCylinderPos[1], snowCylinderPos[2]);
            break;
        case ENVFX_SNOW_BLIZZARD:
            if (radius > 250) {
                radius -= 250;
            } else {
                radius = 1;
            }
            vec3s_set_dist_and_angle(camTo, snowCylinderPos, radius, pitch, yaw);
            envfx_update_snow_blizzard(snowCylinderPos[0], snowCylinderPos[1], snowCylinderPos[2]);
            break;
    }
    rotate_triangle_vertices((RawVertexData *) &vertex1, (RawVertexData *) &vertex2, (RawVertexData *) &vertex3, pitch, yaw);
    gSPDisplayList(gfx++, (((snowMode == ENVFX_SNOW_NORMAL) || (snowMode == ENVFX_SNOW_BLIZZARD)) ? &tiny_bubble_dl_gray : &tiny_bubble_dl_blue)); 
    for ((i = 0); (i < gSnowParticleCount); (i += 5)) {
        append_snowflake_vertex_buffer(gfx++, i, (RawVertexData *) &vertex1, (RawVertexData *) &vertex2, (RawVertexData *) &vertex3);
        gSP1Triangle(gfx++,  0,  1,  2, 0);
        gSP1Triangle(gfx++,  3,  4,  5, 0);
        gSP1Triangle(gfx++,  6,  7,  8, 0);
        gSP1Triangle(gfx++,  9, 10, 11, 0);
        gSP1Triangle(gfx++, 12, 13, 14, 0);
    }
    gSPDisplayList(gfx++, &tiny_bubble_dl_0B006AB0) gSPEndDisplayList(gfx++);
    return gfxStart;
}

/**
 * Updates the environment effects (snow, flowers, bubbles)
 * and returns a display list drawing them.
 */
Gfx *envfx_update_particles(s32 mode, Vec3s marioPos, Vec3s camTo, Vec3s camFrom) {
    Gfx *gfx;
    if (get_dialog_id() != DIALOG_NONE) return NULL;
    if ((gEnvFxMode != 0) && (mode != gEnvFxMode)) mode = 0;
    if (mode >= ENVFX_BUBBLE_START) {
        gfx = envfx_update_bubbles(mode, marioPos, camTo, camFrom);
        return gfx;
    }
    if ((gEnvFxMode == 0) && !envfx_init_snow(mode)) return NULL;
    switch (mode) {
        case ENVFX_MODE_NONE:           envfx_cleanup_snow(gEnvFxBuffer); return NULL;
        case ENVFX_SNOW_NORMAL:   gfx = envfx_update_snow(1, marioPos, camFrom, camTo); break;
        case ENVFX_SNOW_WATER:    gfx = envfx_update_snow(2, marioPos, camFrom, camTo); break;
        case ENVFX_SNOW_BLIZZARD: gfx = envfx_update_snow(3, marioPos, camFrom, camTo); break;
        default: return NULL;
    }
    return gfx;
}
