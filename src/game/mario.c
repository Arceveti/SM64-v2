#include <PR/ultratypes.h>

#include "sm64.h"
#include "area.h"
#include "audio/external.h"
#include "behavior_actions.h"
#include "behavior_data.h"
#include "camera.h"
#include "engine/graph_node.h"
#include "engine/math_util.h"
#include "engine/surface_collision.h"
#include "game_init.h"
#include "interaction.h"
#include "level_table.h"
#include "level_update.h"
#include "main.h"
#include "mario.h"
#include "mario_actions_airborne.h"
#include "mario_actions_automatic.h"
#include "mario_actions_cutscene.h"
#include "mario_actions_moving.h"
#include "mario_actions_object.h"
#include "mario_actions_stationary.h"
#include "mario_actions_submerged.h"
#include "mario_misc.h"
#include "mario_step.h"
#include "memory.h"
#include "object_fields.h"
#include "object_helpers.h"
#include "object_list_processor.h"
#include "print.h"
#include "save_file.h"
#include "sound_init.h"
#include "rumble_init.h"

u32 sDebugMode;

/**************************************************
 *                    ANIMATIONS                  *
 **************************************************/

/**
 * Checks if Mario's animation has reached its end point.
 */
s32 is_anim_at_end(struct MarioState *m) {
    struct Object *o = m->marioObj;
    return (o->header.gfx.animInfo.animFrame + 1) == o->header.gfx.animInfo.curAnim->loopEnd;
}

/**
 * Checks if Mario's animation has surpassed 2 frames before its end point.
 */
s32 is_anim_past_end(struct MarioState *m) {
    struct Object *o = m->marioObj;
    return o->header.gfx.animInfo.animFrame >= (o->header.gfx.animInfo.curAnim->loopEnd - 2);
}

/**
 * Sets Mario's animation without any acceleration, running at its default rate.
 */
s16 set_mario_animation(struct MarioState *m, s32 targetAnimID) {
    struct Object    *o          = m->marioObj;
    struct Animation *targetAnim = m->animList->bufTarget;
    if (load_patchable_table(m->animList, targetAnimID)) {
        targetAnim->values = (void *) VIRTUAL_TO_PHYSICAL((u8 *) targetAnim + (uintptr_t) targetAnim->values);
        targetAnim->index  = (void *) VIRTUAL_TO_PHYSICAL((u8 *) targetAnim + (uintptr_t) targetAnim->index);
    }
    if (o->header.gfx.animInfo.animID != targetAnimID) {
        o->header.gfx.animInfo.animID     = targetAnimID;
        o->header.gfx.animInfo.curAnim    = targetAnim;
        o->header.gfx.animInfo.animAccel  = 0;
        o->header.gfx.animInfo.animYTrans = m->animYTrans;
        if (targetAnim->flags & ANIM_FLAG_2) {
            o->header.gfx.animInfo.animFrame = targetAnim->startFrame;
        } else {
            if (targetAnim->flags & ANIM_FLAG_FORWARD) {
                o->header.gfx.animInfo.animFrame = targetAnim->startFrame + 1;
            } else {
                o->header.gfx.animInfo.animFrame = targetAnim->startFrame - 1;
            }
        }
    }
    return o->header.gfx.animInfo.animFrame;
}

/**
 * Sets Mario's animation where the animation is sped up or
 * slowed down via acceleration.
 */
s16 set_mario_anim_with_accel(struct MarioState *m, s32 targetAnimID, s32 accel) {
    struct Object *o = m->marioObj;
    struct Animation *targetAnim = m->animList->bufTarget;
    if (load_patchable_table(m->animList, targetAnimID)) {
        targetAnim->values = (void *) VIRTUAL_TO_PHYSICAL((u8 *) targetAnim + (uintptr_t) targetAnim->values);
        targetAnim->index  = (void *) VIRTUAL_TO_PHYSICAL((u8 *) targetAnim + (uintptr_t) targetAnim->index);
    }
    if (o->header.gfx.animInfo.animID != targetAnimID) {
        o->header.gfx.animInfo.animID     = targetAnimID;
        o->header.gfx.animInfo.curAnim    = targetAnim;
        o->header.gfx.animInfo.animYTrans = m->animYTrans;
        if (targetAnim->flags & ANIM_FLAG_2) {
            o->header.gfx.animInfo.animFrameAccelAssist = (targetAnim->startFrame << 0x10);
        } else {
            if (targetAnim->flags & ANIM_FLAG_FORWARD) {
                o->header.gfx.animInfo.animFrameAccelAssist = (targetAnim->startFrame << 0x10) + accel;
            } else {
                o->header.gfx.animInfo.animFrameAccelAssist = (targetAnim->startFrame << 0x10) - accel;
            }
        }
        o->header.gfx.animInfo.animFrame = (o->header.gfx.animInfo.animFrameAccelAssist >> 0x10);
    }
    o->header.gfx.animInfo.animAccel = accel;
    return o->header.gfx.animInfo.animFrame;
}

/**
 * Sets the animation to a specific "next" frame from the frame given.
 */
void set_anim_to_frame(struct MarioState *m, s16 animFrame) {
    struct AnimInfo *animInfo = &m->marioObj->header.gfx.animInfo;
    struct Animation *curAnim = animInfo->curAnim;
    if (animInfo->animAccel) {
        if (curAnim->flags & ANIM_FLAG_FORWARD) {
            animInfo->animFrameAccelAssist = (animFrame << 0x10) + animInfo->animAccel;
        } else {
            animInfo->animFrameAccelAssist = (animFrame << 0x10) - animInfo->animAccel;
        }
    } else {
        if (curAnim->flags & ANIM_FLAG_FORWARD) {
            animInfo->animFrame = animFrame + 1;
        } else {
            animInfo->animFrame = animFrame - 1;
        }
    }
}

s32 is_anim_past_frame(struct MarioState *m, s16 animFrame) {
    s32 isPastFrame;
    s32 acceleratedFrame = animFrame << 0x10;
    struct AnimInfo *animInfo = &m->marioObj->header.gfx.animInfo;
    struct Animation *curAnim = animInfo->curAnim;
    if (animInfo->animAccel) {
        if (curAnim->flags & ANIM_FLAG_FORWARD) {
            isPastFrame = (animInfo->animFrameAccelAssist > acceleratedFrame) && (acceleratedFrame >= (animInfo->animFrameAccelAssist - animInfo->animAccel));
        } else {
            isPastFrame = (animInfo->animFrameAccelAssist < acceleratedFrame) && (acceleratedFrame <= (animInfo->animFrameAccelAssist + animInfo->animAccel));
        }
    } else {
        if (curAnim->flags & ANIM_FLAG_FORWARD) {
            isPastFrame = (animInfo->animFrame == (animFrame + 1));
        } else {
            isPastFrame = ((animInfo->animFrame + 1) == animFrame);
        }
    }
    return isPastFrame;
}

/**
 * Rotates the animation's translation into the global coordinate system
 * and returns the animation's flags.
 */
s16 find_mario_anim_flags_and_translation(struct Object *obj, s32 yaw, Vec3s translation) {
    struct Animation *curAnim = (void *) obj->header.gfx.animInfo.curAnim;
    s16 animFrame   = geo_update_animation_frame(&obj->header.gfx.animInfo, NULL);
    u16 *animIndex  = segmented_to_virtual((void *) curAnim->index);
    s16 *animValues = segmented_to_virtual((void *) curAnim->values);
    f32 s           = (f32) sins(yaw);
    f32 c           = (f32) coss(yaw);
    f32 dx          = *(animValues + (retrieve_animation_index(animFrame, &animIndex))) / 4.0f;
    translation[1]  = *(animValues + (retrieve_animation_index(animFrame, &animIndex))) / 4.0f;
    f32 dz          = *(animValues + (retrieve_animation_index(animFrame, &animIndex))) / 4.0f;
    translation[0]  = ( dx * c) + (dz * s);
    translation[2]  = (-dx * s) + (dz * c);
    return curAnim->flags;
}

/**
 * Updates Mario's position from his animation's translation.
 */
void update_mario_pos_for_anim(struct MarioState *m) {
    Vec3s translation;
    s16 flags = find_mario_anim_flags_and_translation(m->marioObj, m->faceAngle[1], translation);
    if (flags & (ANIM_FLAG_HOR_TRANS | ANIM_FLAG_6)) {
        m->pos[0] += (f32) translation[0];
        m->pos[2] += (f32) translation[2];
    }
    if (flags & (ANIM_FLAG_VERT_TRANS | ANIM_FLAG_6)) m->pos[1] += (f32) translation[1];
}

/**
 * Finds the vertical translation from Mario's animation.
 */
s16 return_mario_anim_y_translation(struct MarioState *m) {
    Vec3s translation;
    find_mario_anim_flags_and_translation(m->marioObj, 0, translation);
    return translation[1];
}

/**************************************************
 *                      AUDIO                     *
 **************************************************/

/**
 * Plays a sound if if Mario doesn't have the flag being checked.
 */
void play_sound_if_no_flag(struct MarioState *m, u32 soundBits, u32 flags) {
    if (!(m->flags & flags)) {
        play_sound(soundBits, m->marioObj->header.gfx.cameraToObject);
        m->flags |= flags;
    }
}

/**
 * Plays a jump sound if one has not been played since the last action change.
 */
void play_mario_jump_sound(struct MarioState *m) {
    if (!(m->flags & MARIO_MARIO_SOUND_PLAYED)) {
#ifndef VERSION_JP
        if (m->action == ACT_TRIPLE_JUMP) {
            play_sound(SOUND_MARIO_YAHOO_WAHA_YIPPEE + ((gAudioRandom % 5) << 16), m->marioObj->header.gfx.cameraToObject);
        } else {
#endif
            play_sound(SOUND_MARIO_YAH_WAH_HOO + ((gAudioRandom % 3) << 16), m->marioObj->header.gfx.cameraToObject);
#ifndef VERSION_JP
        }
#endif
        m->flags |= MARIO_MARIO_SOUND_PLAYED;
    }
}

/**
 * Adjusts the volume/pitch of sounds from Mario's speed.
 */
void adjust_sound_for_speed(struct MarioState *m) {
    s32 absForwardVel = (m->forwardVel > 0.0f) ? m->forwardVel : -m->forwardVel;
    set_sound_moving_speed(SOUND_BANK_MOVING, (absForwardVel > 100) ? 100 : absForwardVel);
}

/**
 * Spawns particles if the step sound says to, then either plays a step sound or relevant other sound.
 */
void play_sound_and_spawn_particles(struct MarioState *m, u32 soundBits, u32 waveParticleType) {
    if (m->terrainSoundAddend == (SOUND_TERRAIN_WATER << 16)) {
        m->particleFlags |= ((waveParticleType != 0) ? PARTICLE_SHALLOW_WATER_SPLASH : PARTICLE_SHALLOW_WATER_WAVE);
    } else {
        if (m->terrainSoundAddend == (SOUND_TERRAIN_SAND << 16)) {
            m->particleFlags |= PARTICLE_DIRT;
        } else if (m->terrainSoundAddend == (SOUND_TERRAIN_SNOW << 16)) {
            m->particleFlags |= PARTICLE_SNOW;
        }
    }
    if ((m->flags & MARIO_METAL_CAP)
     || soundBits == SOUND_ACTION_UNSTUCK_FROM_GROUND
     || soundBits == SOUND_MARIO_PUNCH_HOO) {
        play_sound(soundBits, m->marioObj->header.gfx.cameraToObject);
    } else {
        play_sound(m->terrainSoundAddend + soundBits, m->marioObj->header.gfx.cameraToObject);
    }
}

/**
 * Plays an environmental sound if one has not been played since the last action change.
 */
void play_mario_action_sound(struct MarioState *m, u32 soundBits, u32 waveParticleType) {
    if (!(m->flags & MARIO_ACTION_SOUND_PLAYED)) {
        play_sound_and_spawn_particles(m, soundBits, waveParticleType);
        m->flags |= MARIO_ACTION_SOUND_PLAYED;
    }
}

/**
 * Plays a landing sound, accounting for metal cap.
 */
void play_mario_landing_sound(struct MarioState *m, u32 soundBits) {
    play_sound_and_spawn_particles(m, (m->flags & MARIO_METAL_CAP) ? SOUND_ACTION_METAL_LANDING : soundBits, 1);
}

/**
 * Plays a landing sound, accounting for metal cap. Unlike play_mario_landing_sound,
 * this function uses play_mario_action_sound, making sure the sound is only
 * played once per action.
 */
void play_mario_landing_sound_once(struct MarioState *m, u32 soundBits) {
    play_mario_action_sound(m, (m->flags & MARIO_METAL_CAP) ? SOUND_ACTION_METAL_LANDING : soundBits, 1);
}

/**
 * Plays a heavy landing (ground pound, etc.) sound, accounting for metal cap.
 */
void play_mario_heavy_landing_sound(struct MarioState *m, u32 soundBits) {
    play_sound_and_spawn_particles(m, (m->flags & MARIO_METAL_CAP) ? SOUND_ACTION_METAL_HEAVY_LANDING : soundBits, 1);
}

/**
 * Plays a heavy landing (ground pound, etc.) sound, accounting for metal cap.
 * Unlike play_mario_heavy_landing_sound, this function uses play_mario_action_sound,
 * making sure the sound is only played once per action.
 */
void play_mario_heavy_landing_sound_once(struct MarioState *m, u32 soundBits) {
    play_mario_action_sound(m, (m->flags & MARIO_METAL_CAP) ? SOUND_ACTION_METAL_HEAVY_LANDING : soundBits, 1);
}

/**
 * Plays action and Mario sounds relevant to what was passed into the function.
 */
void play_mario_sound(struct MarioState *m, s32 actionSound, s32 marioSound) {
    if (actionSound == SOUND_ACTION_TERRAIN_JUMP) {
        play_mario_action_sound(m, (m->flags & MARIO_METAL_CAP) ? (s32) SOUND_ACTION_METAL_JUMP : (s32) SOUND_ACTION_TERRAIN_JUMP, 1);
    } else {
        play_sound_if_no_flag(m, actionSound, MARIO_ACTION_SOUND_PLAYED);
    }
    if (marioSound ==  0) play_mario_jump_sound(m);
    if (marioSound != -1) play_sound_if_no_flag(m, marioSound, MARIO_MARIO_SOUND_PLAYED);
}

/**************************************************
 *                     ACTIONS                    *
 **************************************************/

/**
 * Sets Mario's other velocities from his forward speed.
 */
void mario_set_forward_vel(struct MarioState *m, f32 forwardVel) {
    m->forwardVel = forwardVel;
    m->slideVelX  = sins(m->faceAngle[1]) * m->forwardVel;
    m->slideVelZ  = coss(m->faceAngle[1]) * m->forwardVel;
    m->vel[0]     = (f32) m->slideVelX;
    m->vel[2]     = (f32) m->slideVelZ;
}

/**
 * Returns the slipperiness class of Mario's floor.
 */
s32 mario_get_floor_class(struct MarioState *m) {
    // The slide terrain type defaults to slide slipperiness.
    // This doesn't matter too much since normally the slide terrain
    // is checked for anyways.
    s32 floorClass = ((m->area->terrainType & TERRAIN_MASK) == TERRAIN_SLIDE) ? SURFACE_CLASS_VERY_SLIPPERY : SURFACE_CLASS_DEFAULT;

    if (m->floor != NULL) {
        switch (m->floor->type) {
            case SURFACE_NOT_SLIPPERY:
            case SURFACE_HARD_NOT_SLIPPERY:
            case SURFACE_SWITCH:
                floorClass = SURFACE_CLASS_NOT_SLIPPERY;
                break;
            case SURFACE_SLIPPERY:
            case SURFACE_NOISE_SLIPPERY:
            case SURFACE_HARD_SLIPPERY:
            case SURFACE_NO_CAM_COL_SLIPPERY:
                floorClass = SURFACE_CLASS_SLIPPERY;
                break;
            case SURFACE_VERY_SLIPPERY:
            case SURFACE_ICE:
            case SURFACE_HARD_VERY_SLIPPERY:
            case SURFACE_NOISE_VERY_SLIPPERY_73:
            case SURFACE_NOISE_VERY_SLIPPERY_74:
            case SURFACE_NOISE_VERY_SLIPPERY:
            case SURFACE_NO_CAM_COL_VERY_SLIPPERY:
                floorClass = SURFACE_CLASS_VERY_SLIPPERY;
                break;
        }
    }
    // Crawling allows Mario to not slide on certain steeper surfaces.
    if (m->action == ACT_CRAWLING && m->floor->normal.y > 0.5f && floorClass == SURFACE_CLASS_DEFAULT) floorClass = SURFACE_CLASS_NOT_SLIPPERY;
    return floorClass;
}

// clang-format off
s8 sTerrainSounds[7][6] = {
    // default,              hard,                 slippery,
    // very slippery,        noisy default,        noisy slippery
    { SOUND_TERRAIN_DEFAULT, SOUND_TERRAIN_STONE , SOUND_TERRAIN_GRASS  ,
      SOUND_TERRAIN_GRASS  , SOUND_TERRAIN_GRASS , SOUND_TERRAIN_DEFAULT }, // TERRAIN_GRASS
    { SOUND_TERRAIN_STONE  , SOUND_TERRAIN_STONE , SOUND_TERRAIN_STONE  ,
      SOUND_TERRAIN_STONE  , SOUND_TERRAIN_GRASS , SOUND_TERRAIN_GRASS   }, // TERRAIN_STONE
    { SOUND_TERRAIN_SNOW   , SOUND_TERRAIN_ICE   , SOUND_TERRAIN_SNOW   ,
      SOUND_TERRAIN_ICE    , SOUND_TERRAIN_STONE , SOUND_TERRAIN_STONE   }, // TERRAIN_SNOW
    { SOUND_TERRAIN_SAND   , SOUND_TERRAIN_STONE , SOUND_TERRAIN_SAND   ,
      SOUND_TERRAIN_SAND   , SOUND_TERRAIN_STONE , SOUND_TERRAIN_STONE   }, // TERRAIN_SAND
    { SOUND_TERRAIN_SPOOKY , SOUND_TERRAIN_SPOOKY, SOUND_TERRAIN_SPOOKY ,
      SOUND_TERRAIN_SPOOKY , SOUND_TERRAIN_STONE , SOUND_TERRAIN_STONE   }, // TERRAIN_SPOOKY
    { SOUND_TERRAIN_DEFAULT, SOUND_TERRAIN_STONE , SOUND_TERRAIN_GRASS  ,
      SOUND_TERRAIN_ICE    , SOUND_TERRAIN_STONE , SOUND_TERRAIN_ICE     }, // TERRAIN_WATER
    { SOUND_TERRAIN_STONE  , SOUND_TERRAIN_STONE , SOUND_TERRAIN_STONE  ,
      SOUND_TERRAIN_STONE  , SOUND_TERRAIN_ICE   , SOUND_TERRAIN_ICE     }, // TERRAIN_SLIDE
};
// clang-format on

/**
 * Computes a value that should be added to terrain sounds before playing them.
 * This depends on surfaces and terrain.
 */
u32 mario_get_terrain_sound_addend(struct MarioState *m) {
    s16 floorSoundType;
    s16 terrainType = m->area->terrainType & TERRAIN_MASK;
    s32 ret = SOUND_TERRAIN_DEFAULT << 16;
    s32 floorType;
    if (m->floor != NULL) {
        floorType = m->floor->type;

        if ((gCurrLevelNum != LEVEL_LLL) && (m->floorHeight < (m->waterLevel - 10))) {
            // Water terrain sound, excluding LLL since it uses water in the volcano.
            ret = SOUND_TERRAIN_WATER << 16;
        } else if (SURFACE_IS_QUICKSAND(floorType)) {
            ret = SOUND_TERRAIN_SAND << 16;
        } else {
            switch (floorType) {
                default:
                    floorSoundType = 0;
                    break;
                case SURFACE_NOT_SLIPPERY:
                case SURFACE_HARD:
                case SURFACE_HARD_NOT_SLIPPERY:
                case SURFACE_SWITCH:
                    floorSoundType = 1;
                    break;
                case SURFACE_SLIPPERY:
                case SURFACE_HARD_SLIPPERY:
                case SURFACE_NO_CAM_COL_SLIPPERY:
                    floorSoundType = 2;
                    break;
                case SURFACE_VERY_SLIPPERY:
                case SURFACE_ICE:
                case SURFACE_HARD_VERY_SLIPPERY:
                case SURFACE_NOISE_VERY_SLIPPERY_73:
                case SURFACE_NOISE_VERY_SLIPPERY_74:
                case SURFACE_NOISE_VERY_SLIPPERY:
                case SURFACE_NO_CAM_COL_VERY_SLIPPERY:
                    floorSoundType = 3;
                    break;
                case SURFACE_NOISE_DEFAULT:
                    floorSoundType = 4;
                    break;
                case SURFACE_NOISE_SLIPPERY:
                    floorSoundType = 5;
                    break;
            }
            ret = sTerrainSounds[terrainType][floorSoundType] << 16;
        }
    }
    return ret;
}

/**
 * Collides with walls and returns the most recent wall.
 */
#ifdef BETTER_WALL_COLLISION
void resolve_and_return_wall_collisions(Vec3f pos, f32 offset, f32 radius, struct WallCollisionData *collisionData) {
    collisionData->x       = pos[0];
    collisionData->y       = pos[1];
    collisionData->z       = pos[2];
    collisionData->radius  = radius;
    collisionData->offsetY = offset;
    find_wall_collisions(collisionData);
    pos[0] = collisionData->x;
    pos[1] = collisionData->y;
    pos[2] = collisionData->z;
}
#else
struct Surface *resolve_and_return_wall_collisions(Vec3f pos, f32 offset, f32 radius) {
    struct WallCollisionData collisionData;
    struct Surface *wall  = NULL;
    collisionData.x       = pos[0];
    collisionData.y       = pos[1];
    collisionData.z       = pos[2];
    collisionData.radius  = radius;
    collisionData.offsetY = offset;
    if (find_wall_collisions(&collisionData)) wall = collisionData.walls[collisionData.numWalls - 1];
    pos[0] = collisionData.x;
    pos[1] = collisionData.y;
    pos[2] = collisionData.z;
    //! This only returns the most recent wall and can also return NULL
    //! there are no wall collisions.
    return wall;
}
#endif

/**
 * Finds the ceiling from a vec3f horizontally and a height (with 3.0f vertical buffer).
 */
f32 vec3f_find_ceil(Vec3f pos, f32 height, struct Surface **ceil) {
    return find_ceil(pos[0], height + 3.0f, pos[2], ceil);
}

/**
 * Determines if Mario is facing "downhill."
 */
s32 mario_facing_downhill(struct MarioState *m, s32 turnYaw) {
    s16 faceAngleYaw = m->faceAngle[1];
    // This is never used in practice, as turnYaw is
    // always passed as zero.
    if (turnYaw && m->forwardVel < 0.0f) faceAngleYaw += 0x8000;
    faceAngleYaw = m->floorAngle - faceAngleYaw;
    return (-0x4000 < faceAngleYaw) && (faceAngleYaw < 0x4000);
}

/**
 * Determines if a surface is slippery based on the surface class.
 */
u32 mario_floor_is_slippery(struct MarioState *m) {
    f32 normY;
    if ((m->area->terrainType & TERRAIN_MASK) == TERRAIN_SLIDE && m->floor->normal.y < COS1) return TRUE;
    switch (mario_get_floor_class(m)) {
        case SURFACE_VERY_SLIPPERY: normY = COS10; break;
        case SURFACE_SLIPPERY:      normY = COS20; break;
        default:                    normY = COS38; break;
        case SURFACE_NOT_SLIPPERY:  normY =  0.0f; break;
    }
    return m->floor->normal.y <= normY;
}

/**
 * Determines if a surface is a slope based on the surface class.
 */
s32 mario_floor_is_slope(struct MarioState *m) {
    f32 normY;
    if ((m->area->terrainType & TERRAIN_MASK) == TERRAIN_SLIDE && m->floor->normal.y < COS1) return TRUE;
    switch (mario_get_floor_class(m)) {
        case SURFACE_VERY_SLIPPERY: normY = COS5;  break;
        case SURFACE_SLIPPERY:      normY = COS10; break;
        default:                    normY = COS15; break;
        case SURFACE_NOT_SLIPPERY:  normY = COS20; break;
    }
    return m->floor->normal.y <= normY;
}

/**
 * Determines if a surface is steep based on the surface class.
 */
s32 mario_floor_is_steep(struct MarioState *m) {
    f32 normY;
    s32 result = FALSE;
#ifdef JUMP_KICK_FIX
    if (m->floor->type == SURFACE_NOT_SLIPPERY) return FALSE;
#endif
    // Interestingly, this function does not check for the
    // slide terrain type. This means that steep behavior persists for
    // non-slippery and slippery surfaces.
    // This does not matter in vanilla game practice.
    if (!mario_facing_downhill(m, FALSE)) {
        switch (mario_get_floor_class(m)) {
            case SURFACE_VERY_SLIPPERY: normY = COS15; break;
            case SURFACE_SLIPPERY:      normY = COS20; break;
            default:                    normY = COS30; break;
            case SURFACE_NOT_SLIPPERY:  normY = COS30; break;
        }
        result = m->floor->normal.y <= normY;
    }
    return result;
}

/**
 * Finds the floor height relative from Mario given polar displacement.
 */
f32 find_floor_height_relative_polar(struct MarioState *m, s16 angleFromMario, f32 distFromMario) {
    struct Surface *floor;
    f32 y = sins(m->faceAngle[1] + angleFromMario) * distFromMario;
    f32 x = coss(m->faceAngle[1] + angleFromMario) * distFromMario;
    return find_floor(m->pos[0] + y, m->pos[1] + 100.0f, m->pos[2] + x, &floor);
}

/**
 * Returns the slope of the floor based off points around Mario.
 */
s16 find_floor_slope(struct MarioState *m, s16 yawOffset) {
    struct Surface *floor;
    f32 forwardFloorY, backwardFloorY;
    f32 forwardYDelta, backwardYDelta;
    f32 x                             = sins(m->faceAngle[1] + yawOffset) * 5.0f;
    f32 z                             = coss(m->faceAngle[1] + yawOffset) * 5.0f;
    forwardFloorY                     = find_floor(m->pos[0] + x, m->pos[1] + 100.0f, m->pos[2] + z, &floor);
    if (floor == NULL) forwardFloorY  = m->floorHeight; // handle OOB slopes
    backwardFloorY                    = find_floor(m->pos[0] - x, m->pos[1] + 100.0f, m->pos[2] - z, &floor);
    if (floor == NULL) backwardFloorY = m->floorHeight; // handle OOB slopes
    //! If Mario is near OOB, these floorY's can sometimes be -11000.
    //  This will cause these to be off and give improper slopes.
    forwardYDelta                     = forwardFloorY - m->pos[1];
    backwardYDelta                    = m->pos[1] - backwardFloorY;
    return atan2s(5.0f, (forwardYDelta * forwardYDelta < backwardYDelta * backwardYDelta) ? forwardYDelta : backwardYDelta);
}

// default range is 0x471C
s32 analog_stick_held_back(struct MarioState *m, s16 range) {
    s16 intendedDYaw = m->intendedYaw - m->faceAngle[1];
    return intendedDYaw < -range || intendedDYaw > range;
}

/**
 * Adjusts Mario's camera and sound based on his action status.
 */
void update_mario_sound_and_camera(struct MarioState *m) {
    u32 action    = m->action;
    s32 camPreset = m->area->camera->mode;
    if (action == ACT_FIRST_PERSON) {
        raise_background_noise(2);
        gCameraMovementFlags &= ~CAM_MOVE_C_UP_MODE;
        // Go back to the last camera mode
        set_camera_mode(m->area->camera, -1, 1);
    } else if (action == ACT_SLEEPING) {
        raise_background_noise(2);
    }
    if (!(action & (ACT_FLAG_SWIMMING | ACT_FLAG_METAL_WATER)) && (camPreset == CAMERA_MODE_BEHIND_MARIO || camPreset == CAMERA_MODE_WATER_SURFACE)) set_camera_mode(m->area->camera, m->area->camera->defMode, 1);
}

/**
 * Transitions Mario to a steep jump action.
 */
void set_steep_jump_action(struct MarioState *m) {
    m->marioObj->oMarioSteepJumpYaw = m->faceAngle[1];
    if (m->forwardVel > 0.0f) {
        //! ((s16)0x8000) has undefined behavior. Therefore, this downcast has
        // undefined behavior if m->floorAngle >= 0.
        s16 angleTemp     = m->floorAngle + 0x8000;
        s16 faceAngleTemp = m->faceAngle[1] - angleTemp;
        f32 y             = sins(faceAngleTemp) * m->forwardVel;
        f32 x             = coss(faceAngleTemp) * m->forwardVel * 0.75f;
        m->forwardVel     = sqrtf(y * y + x * x);
        m->faceAngle[1]   = atan2s(x, y) + angleTemp;
    }
    drop_and_set_mario_action(m, ACT_STEEP_JUMP, 0);
}

/**
 * Sets Mario's vertical speed from his forward speed.
 */
static void set_mario_y_vel_based_on_fspeed(struct MarioState *m, f32 initialVelY, f32 multiplier) {
    // get_additive_y_vel_for_jumps is always 0 and a stubbed function.
    // It was likely trampoline related based on code location.
    m->vel[1] = initialVelY + get_additive_y_vel_for_jumps() + m->forwardVel * multiplier;
    if (m->squishTimer != 0 || m->quicksandDepth > 1.0f) m->vel[1] *= 0.5f;
}

/**
 * Transitions for a variety of airborne actions.
 */
static u32 set_mario_action_airborne(struct MarioState *m, u32 action, u32 actionArg) {
    f32 forwardVel;
    if ((m->squishTimer != 0 || m->quicksandDepth >= 1.0f)  && (action == ACT_DOUBLE_JUMP || action == ACT_TWIRLING)) action = ACT_JUMP;
    switch (action) {
        case ACT_DOUBLE_JUMP:
            set_mario_y_vel_based_on_fspeed(m, 52.0f, 0.25f);
            m->forwardVel *= 0.8f;
            break;
        case ACT_BACKFLIP:
            m->marioObj->header.gfx.animInfo.animID = -1;
            m->forwardVel = -16.0f;
            set_mario_y_vel_based_on_fspeed(m, 62.0f, 0.0f);
            break;
        case ACT_TRIPLE_JUMP:
            set_mario_y_vel_based_on_fspeed(m, 69.0f, 0.0f);
            m->forwardVel *= 0.8f;
            break;
        case ACT_FLYING_TRIPLE_JUMP:
            set_mario_y_vel_based_on_fspeed(m, 82.0f, 0.0f);
            break;
#ifdef GROUND_POUND_JUMP
        case ACT_GROUND_POUND_JUMP:
            set_mario_y_vel_based_on_fspeed(m, 56.0f, 0.0f);
            break;
#endif
        case ACT_WATER_JUMP:
        case ACT_HOLD_WATER_JUMP:
            if (actionArg == 0) set_mario_y_vel_based_on_fspeed(m, 42.0f, 0.0f);
            break;
        case ACT_BURNING_JUMP:
            m->vel[1] = 31.5f;
            m->forwardVel = 8.0f;
            break;
        case ACT_RIDING_SHELL_JUMP:
            set_mario_y_vel_based_on_fspeed(m, 42.0f, 0.25f);
            break;
        case ACT_JUMP:
        case ACT_HOLD_JUMP:
            m->marioObj->header.gfx.animInfo.animID = -1;
            set_mario_y_vel_based_on_fspeed(m, 42.0f, 0.25f);
            m->forwardVel *= 0.8f;
            break;
        case ACT_WALL_KICK_AIR:
        case ACT_TOP_OF_POLE_JUMP:
            set_mario_y_vel_based_on_fspeed(m, 62.0f, 0.0f);
            if (m->forwardVel < 24.0f) m->forwardVel = 24.0f;
            m->wallKickTimer = 0;
            break;
        case ACT_SIDE_FLIP:
            set_mario_y_vel_based_on_fspeed(m, 62.0f, 0.0f);
            m->forwardVel = 8.0f;
            m->faceAngle[1] = m->intendedYaw;
            break;
        case ACT_STEEP_JUMP:
            m->marioObj->header.gfx.animInfo.animID = -1;
            set_mario_y_vel_based_on_fspeed(m, 42.0f, 0.25f);
            m->faceAngle[0] = -0x2000;
            break;
        case ACT_LAVA_BOOST:
            m->vel[1] = 84.0f;
            if (actionArg == 0) m->forwardVel = 0.0f;
            break;
        case ACT_DIVE:
            if ((forwardVel = m->forwardVel + 15.0f) > 48.0f) forwardVel = 48.0f;
            mario_set_forward_vel(m, forwardVel);
            break;
        case ACT_LONG_JUMP:
            m->marioObj->header.gfx.animInfo.animID = -1;
            set_mario_y_vel_based_on_fspeed(m, 30.0f, 0.0f);
            m->marioObj->oMarioLongJumpIsSlow = m->forwardVel > 16.0f ? FALSE : TRUE;
            //! (BLJ's) This properly handles long jumps from getting forward speed with
            //  too much velocity, but misses backwards longs allowing high negative speeds.
            if ((m->forwardVel *= 1.5f) > 48.0f) m->forwardVel = 48.0f;
            break;
        case ACT_SLIDE_KICK:
            m->vel[1] = 12.0f;
            if (m->forwardVel < 32.0f) m->forwardVel = 32.0f;
            break;
        case ACT_JUMP_KICK:
            m->vel[1] = 20.0f;
            break;
#ifdef WALL_SLIDE
        case ACT_WALL_SLIDE:
            m->vel[1] = 0.0f;
            break;
#endif
    }
    m->peakHeight = m->pos[1];
    m->flags |= MARIO_JUMPING;
    return action;
}

/**
 * Transitions for a variety of moving actions.
 */
static u32 set_mario_action_moving(struct MarioState *m, u32 action, UNUSED u32 actionArg) {
    s16 floorClass = mario_get_floor_class(m);
    f32 forwardVel = m->forwardVel;
    f32 mag        = min(m->intendedMag, 8.0f);
    switch (action) {
        case ACT_WALKING:
            if (floorClass != SURFACE_CLASS_VERY_SLIPPERY && 0.0f <= forwardVel && forwardVel < mag) m->forwardVel = mag;
            m->marioObj->oMarioWalkingPitch = 0;
            break;
        case ACT_HOLD_WALKING:
            if (0.0f <= forwardVel && forwardVel < mag / 2.0f) m->forwardVel = mag / 2.0f;
            break;
        case ACT_BEGIN_SLIDING:
            action = mario_facing_downhill(m, FALSE) ? ACT_BUTT_SLIDE : ACT_STOMACH_SLIDE;
            break;
        case ACT_HOLD_BEGIN_SLIDING:
            action = mario_facing_downhill(m, FALSE) ? ACT_HOLD_BUTT_SLIDE : ACT_HOLD_STOMACH_SLIDE;
            break;
    }
    return action;
}

/**
 * Transition for certain submerged actions, which is actually just the metal jump actions.
 */
static u32 set_mario_action_submerged(struct MarioState *m, u32 action, UNUSED u32 actionArg) {
    if (action == ACT_METAL_WATER_JUMP || action == ACT_HOLD_METAL_WATER_JUMP) m->vel[1] = 32.0f;
    return action;
}

/**
 * Transitions for a variety of cutscene actions.
 */
static u32 set_mario_action_cutscene(struct MarioState *m, u32 action, UNUSED u32 actionArg) {
    switch (action) {
        case ACT_EMERGE_FROM_PIPE:      m->vel[1] = 52.0f;              break;
        case ACT_FALL_AFTER_STAR_GRAB:  mario_set_forward_vel(m, 0.0f); break;
        case ACT_SPAWN_SPIN_AIRBORNE:   mario_set_forward_vel(m, 2.0f); break;
        case ACT_SPECIAL_EXIT_AIRBORNE: // fall through
        case ACT_SPECIAL_DEATH_EXIT:    m->vel[1] = 64.0f;              break;
    }
    return action;
}

/**
 * Puts Mario into a given action, putting Mario through the appropriate
 * specific function if needed.
 */
u32 set_mario_action(struct MarioState *m, u32 action, u32 actionArg) {
    switch (action & ACT_GROUP_MASK) {
        case ACT_GROUP_MOVING:    action = set_mario_action_moving(   m, action, actionArg); break;
        case ACT_GROUP_AIRBORNE:  action = set_mario_action_airborne( m, action, actionArg); break;
        case ACT_GROUP_SUBMERGED: action = set_mario_action_submerged(m, action, actionArg); break;
        case ACT_GROUP_CUTSCENE:  action = set_mario_action_cutscene( m, action, actionArg); break;
    }
    // Resets the sound played flags, meaning Mario can play those sound types again.
    m->flags &= ~(MARIO_ACTION_SOUND_PLAYED | MARIO_MARIO_SOUND_PLAYED);
    if (!(m->action & ACT_FLAG_AIR)) m->flags &= ~MARIO_FALL_SOUND_PLAYED;
    // Initialize the action information.
    m->prevAction  = m->action;
    m->action      = action;
    m->actionArg   = actionArg;
    m->actionState = 0;
    m->actionTimer = 0;
    return TRUE;
}

/**
 * Puts Mario into a specific jumping action from a landing action.
 */
s32 set_jump_from_landing(struct MarioState *m) {
    if (m->quicksandDepth >= 11.0f) return set_mario_action(m, (m->heldObj == NULL) ? ACT_QUICKSAND_JUMP_LAND : ACT_HOLD_QUICKSAND_JUMP_LAND, 0);
    if (mario_floor_is_steep(m)) {
        set_steep_jump_action(m);
    } else {
        if ((m->doubleJumpTimer == 0) || (m->squishTimer != 0)) {
            set_mario_action(m, ACT_JUMP, 0);
        } else {
            switch (m->prevAction) {
                case ACT_JUMP_LAND:
                case ACT_FREEFALL_LAND:
                case ACT_SIDE_FLIP_LAND_STOP: set_mario_action(m, ACT_DOUBLE_JUMP, 0); break;

                case ACT_DOUBLE_JUMP_LAND:
                    // If Mario has a wing cap, he ignores the typical speed
                    // requirement for a triple jump.
                    if (m->flags & MARIO_WING_CAP) {
                        set_mario_action(m, ACT_FLYING_TRIPLE_JUMP, 0);
                    } else if (m->forwardVel > 20.0f) {
                        set_mario_action(m, ACT_TRIPLE_JUMP, 0);
                    } else {
                        set_mario_action(m, ACT_JUMP, 0);
                    }
                    break;
                default: set_mario_action(m, ACT_JUMP, 0); break;
            }
        }
    }
    m->doubleJumpTimer = 0;
    return TRUE;
}

/**
 * Puts Mario in a given action, as long as it is not overruled by
 * either a quicksand or steep jump.
 */
s32 set_jumping_action(struct MarioState *m, u32 action, u32 actionArg) {
    // Checks whether Mario is holding an object or not.
    if (m->quicksandDepth >= 11.0f) return set_mario_action(m, (m->heldObj == NULL) ? ACT_QUICKSAND_JUMP_LAND : ACT_HOLD_QUICKSAND_JUMP_LAND, 0);
    if (mario_floor_is_steep(m)) {
        set_steep_jump_action(m);
    } else {
        set_mario_action(m, action, actionArg);
    }
    return TRUE;
}

/**
 * Drop anything Mario is holding and set a new action.
 */
s32 drop_and_set_mario_action(struct MarioState *m, u32 action, u32 actionArg) {
    mario_stop_riding_and_holding(m);
    return set_mario_action(m, action, actionArg);
}

/**
 * Increment Mario's hurt counter and set a new action.
 */
s32 hurt_and_set_mario_action(struct MarioState *m, u32 action, u32 actionArg, s16 hurtCounter) {
    m->hurtCounter = hurtCounter;
    return set_mario_action(m, action, actionArg);
}

/**
 * Checks a variety of inputs for common transitions between many different
 * actions. A common variant of the below function.
 */
s32 check_common_action_exits(struct MarioState *m) {
    if (m->input & INPUT_A_PRESSED     ) return set_mario_action(m, ACT_JUMP         , 0);
    if (m->input & INPUT_OFF_FLOOR     ) return set_mario_action(m, ACT_FREEFALL     , 0);
    if (m->input & INPUT_NONZERO_ANALOG) return set_mario_action(m, ACT_WALKING      , 0);
    if (m->input & INPUT_ABOVE_SLIDE   ) return set_mario_action(m, ACT_BEGIN_SLIDING, 0);
    return FALSE;
}

/**
 * Checks a variety of inputs for common transitions between many different
 * object holding actions. A holding variant of the above function.
 */
s32 check_common_hold_action_exits(struct MarioState *m) {
    if (m->input & INPUT_A_PRESSED     ) return set_mario_action(m, ACT_HOLD_JUMP         , 0);
    if (m->input & INPUT_OFF_FLOOR     ) return set_mario_action(m, ACT_HOLD_FREEFALL     , 0);
    if (m->input & INPUT_NONZERO_ANALOG) return set_mario_action(m, ACT_HOLD_WALKING      , 0);
    if (m->input & INPUT_ABOVE_SLIDE   ) return set_mario_action(m, ACT_HOLD_BEGIN_SLIDING, 0);
    return FALSE;
}

/**
 * Transitions Mario from a submerged action to a walking action.
 */
s32 transition_submerged_to_walking(struct MarioState *m) {
    set_camera_mode(m->area->camera, m->area->camera->defMode, 1);
    vec3s_set(m->angleVel, 0x0, 0x0, 0x0);
    return set_mario_action(m, (m->heldObj == NULL) ? ACT_WALKING : ACT_HOLD_WALKING, 0);
}

/**
 * Transitions Mario from a submerged action to an airborne action.
 * You may want to change these actions to fit your hack
 */
s32 transition_submerged_to_airborne(struct MarioState *m) {
    set_camera_mode(m->area->camera, m->area->camera->defMode, 1);
    vec3s_set(m->angleVel, 0x0, 0x0, 0x0);
    if (m->heldObj == NULL) {
        return set_mario_action(m, (m->input & INPUT_A_DOWN) ? ACT_DIVE : ACT_FREEFALL, 0);
    } else {
        return set_mario_action(m, (m->input & INPUT_A_DOWN) ? ACT_HOLD_JUMP : ACT_HOLD_FREEFALL, 0);
    }
}

/**
 * This is the transition function typically for entering a submerged action for a
 * non-submerged action. This also applies the water surface camera preset.
 */
s32 set_water_plunge_action(struct MarioState *m) {
    m->forwardVel   = m->forwardVel / 4.0f;
    m->vel[1]       = m->vel[1]     / 2.0f;
    m->faceAngle[2] = 0x0;
    vec3s_set(m->angleVel, 0x0, 0x0, 0x0);
    if (!(m->action & ACT_FLAG_DIVING)) m->faceAngle[0] = 0x0;
    if (m->area->camera->mode != CAMERA_MODE_WATER_SURFACE) set_camera_mode(m->area->camera, CAMERA_MODE_WATER_SURFACE, 1);
#ifdef WATER_GROUND_POUND
    m->particleFlags |= PARTICLE_WATER_SPLASH;
    if (m->action == ACT_GROUND_POUND) {
        play_sound(SOUND_ACTION_WATER_PLUNGE, m->marioObj->header.gfx.cameraToObject);
        return set_mario_action(m, ACT_WATER_GROUND_POUND, 1);
    } else {
        return set_mario_action(m, ACT_WATER_PLUNGE, 0);
    }
#else
    return set_mario_action(m, ACT_WATER_PLUNGE, 0);
#endif
}

/**
 * These are the scaling values for the x and z axis for Mario
 * when he is close to unsquishing.
 */
u8 sSquishScaleOverTime[16] = { 0x46, 0x32, 0x32, 0x3C, 0x46, 0x50, 0x50, 0x3C,
                                0x28, 0x14, 0x14, 0x1E, 0x32, 0x3C, 0x3C, 0x28 };

/**
 * Applies the squish to Mario's model via scaling.
 */
void squish_mario_model(struct MarioState *m) {
    if (m->squishTimer != 0xFF) {
        // If no longer squished, scale back to default.
        if (m->squishTimer == 0) {
            vec3f_set(m->marioObj->header.gfx.scale, 1.0f, 1.0f, 1.0f);
        // If timer is less than 16, rubber-band Mario's size scale up and down.
        } else if (m->squishTimer <= 16) {
            m->squishTimer--;
            m->marioObj->header.gfx.scale[1] = 1.0f - ((sSquishScaleOverTime[15 - m->squishTimer] * 0.6f) / 100.0f);
            m->marioObj->header.gfx.scale[0] =        ((sSquishScaleOverTime[15 - m->squishTimer] * 0.4f) / 100.0f) + 1.0f;
            m->marioObj->header.gfx.scale[2] = m->marioObj->header.gfx.scale[0];
        } else {
            m->squishTimer--;
            vec3f_set(m->marioObj->header.gfx.scale, 1.4f, 0.4f, 1.4f);
        }
    }
}

#ifdef DEBUG_INFO
/**
 * Debug function that prints floor normal, velocity, and action information.
 */
void debug_print_speed_action_normal(struct MarioState *m) {
    f32 steepness;
    f32 surf_nY;
    if (gShowDebugText) {
        print_text_fmt_int(210, 184, "PX %d", m->pos[0]);
        print_text_fmt_int(210, 168, "PY %d", m->pos[1]);
        print_text_fmt_int(210, 152, "PZ %d", m->pos[2]);
        // print_text_fmt_int(210, 184, "SX %d", gMarioScreenX);
        // print_text_fmt_int(210, 168, "SY %d", gMarioScreenY);
        switch (sDebugMode) {
            case 0:
                print_text_fmt_int(210, 136,  "VX %d", m->vel[0]);
                print_text_fmt_int(210, 120,  "VY %d", m->vel[1]);
                print_text_fmt_int(210, 104,  "VZ %d", m->vel[2]);

                print_text_fmt_int(210,  88,  "RY %d", (m->faceAngle[1] * 45.0f) / 8192.0f);
                print_text_fmt_int(210,  72, "FWD %d",  m->forwardVel);
                print_text_fmt_int(210,  56,  "MY %d", (atan2s(m->marioObj->oVelZ, m->marioObj->oVelX) * 45.0f) / 8192.0f);
                // print_text_fmt_int(210,  56, "VEL", 0);
                // STA short for "status," the official action name via SMS map.
                print_text_fmt_int(210,  40, "STA %x", (m->action & ACT_ID_MASK));
                break;
            case 1:
                if (m->floor != NULL) {
                    steepness = sqrtf(((m->floor->normal.x * m->floor->normal.x) + (m->floor->normal.z * m->floor->normal.z)));
                    surf_nY = m->floor->normal.y;
                    print_text_fmt_int( 80, 136,   "F1 %d", m->floor->vertex1[0]);
                    print_text_fmt_int(184, 136,      "%d", m->floor->vertex1[1]);
                    print_text_fmt_int(248, 136,      "%d", m->floor->vertex1[2]);

                    print_text_fmt_int( 80, 120,   "F2 %d", m->floor->vertex2[0]);
                    print_text_fmt_int(184, 120,      "%d", m->floor->vertex2[1]);
                    print_text_fmt_int(248, 120,      "%d", m->floor->vertex2[2]);

                    print_text_fmt_int( 80, 104,   "F3 %d", m->floor->vertex3[0]);
                    print_text_fmt_int(184, 104,      "%d", m->floor->vertex3[1]);
                    print_text_fmt_int(248, 104,      "%d", m->floor->vertex3[2]);

                    print_text_fmt_int(210,  88,   "FH %d", m->floorHeight);

                    print_text_fmt_int(210,  72,  "ANG %d", (atan2s(surf_nY, steepness) * 45.0f) / 8192.0f);
                    print_text_fmt_int(128,  56, "SURF %x", m->floor->type);
                    print_text_fmt_int(226,  56,    "0*%x", m->floor->force);
                    print_text_fmt_int(210,  40,   "RM %d", m->floor->room);
                }
                // print_text_fmt_int(210, 56, "FLOOR", 0);
                break;
            case 2:
                if (m->ceil != NULL) {
                    steepness = sqrtf(((m->ceil->normal.x * m->ceil->normal.x) + (m->ceil->normal.z * m->ceil->normal.z)));
                    surf_nY = m->ceil->normal.y;
                    print_text_fmt_int( 80, 136,   "C1 %d", m->ceil->vertex1[0]);
                    print_text_fmt_int(184, 136,      "%d", m->ceil->vertex1[1]);
                    print_text_fmt_int(248, 136,      "%d", m->ceil->vertex1[2]);

                    print_text_fmt_int( 80, 120,   "C2 %d", m->ceil->vertex2[0]);
                    print_text_fmt_int(184, 120,      "%d", m->ceil->vertex2[1]);
                    print_text_fmt_int(248, 120,      "%d", m->ceil->vertex2[2]);

                    print_text_fmt_int( 80, 104,   "C3 %d", m->ceil->vertex3[0]);
                    print_text_fmt_int(184, 104,      "%d", m->ceil->vertex3[1]);
                    print_text_fmt_int(248, 104,      "%d", m->ceil->vertex3[2]);

                    print_text_fmt_int(210,  88,   "CH %d", m->ceilHeight);

                    print_text_fmt_int(210,  72,  "ANG %d", (atan2s(surf_nY, steepness) * 45.0f) / 8192.0f);
                    print_text_fmt_int(128,  56, "SURF %x", m->ceil->type);
                    print_text_fmt_int(226,  56,    "0*%x", m->ceil->force);
                }
                // print_text_fmt_int(210, 56, "CEIL", 0);
                break;
            case 3:
                if (m->wall != NULL) {
                    steepness = sqrtf(((m->wall->normal.x * m->wall->normal.x) + (m->wall->normal.z * m->wall->normal.z)));
                    surf_nY = m->wall->normal.y;
#ifdef UNDERWATER_STEEP_FLOORS_AS_WALLS
                    if (surf_nY > MIN_FLOOR_NORMAL_Y || surf_nY < MAX_CEIL_NORMAL_Y) break;
#endif
                    print_text_fmt_int( 80, 136,  "W1 %d", m->wall->vertex1[0]);
                    print_text_fmt_int(184, 136,     "%d", m->wall->vertex1[1]);
                    print_text_fmt_int(248, 136,     "%d", m->wall->vertex1[2]);

                    print_text_fmt_int( 80, 120,  "W2 %d", m->wall->vertex2[0]);
                    print_text_fmt_int(184, 120,     "%d", m->wall->vertex2[1]);
                    print_text_fmt_int(248, 120,     "%d", m->wall->vertex2[2]);

                    print_text_fmt_int( 80, 104,  "W3 %d", m->wall->vertex3[0]);
                    print_text_fmt_int(184, 104,     "%d", m->wall->vertex3[1]);
                    print_text_fmt_int(248, 104,     "%d", m->wall->vertex3[2]);
                    
                    print_text_fmt_int(210,  88,  "WRY %d", (atan2s(m->wall->normal.z, m->wall->normal.x) * 45.0f) / 8192.0f);

                    print_text_fmt_int(210,  72,  "ANG %d", (atan2s(surf_nY, steepness) * 45.0f) / 8192.0f);
                    print_text_fmt_int(128,  56, "SURF %x", m->wall->type);
                    print_text_fmt_int(226,  56,    "0*%x", m->wall->force);
                }
                // print_text_fmt_int(210, 56, "WALL", 0);
                break;
            case 4:
                print_text_fmt_int(210, 120, "C2 %d", (gGlobalTimer % 32767));
                print_text_fmt_int(210, 104, "AT %d", m->actionTimer);

                print_text_fmt_int(210,  88, "AY %d", (coss(m->intendedYaw) * m->intendedMag)); // far to near
                print_text_fmt_int(210,  72, "AX %d", (sins(m->intendedYaw) * m->intendedMag)); // left to right
                print_text_fmt_int(64,   56, "INP %016b", m->input);
                break;
        }
        print_text_fmt_int(16, 48, "F %d", gNumCalls.floor);
        print_text_fmt_int(16, 32, "C %d", gNumCalls.ceil );
        print_text_fmt_int(16, 16, "W %d", gNumCalls.wall );
        gNumCalls.floor = 0;
        gNumCalls.ceil  = 0;
        gNumCalls.wall  = 0;
        if (gPlayer1Controller->buttonPressed & L_TRIG) {
            sDebugMode++;
            if (sDebugMode > 4) sDebugMode = 0;
        }
    }
    if (gPlayer1Controller->buttonDown & Z_TRIG && gPlayer1Controller->buttonPressed & L_JPAD) {
        gShowDebugText ^= TRUE;
        gDebugInfoFlags = gShowDebugText ? DEBUG_INFO_FLAG_ALL : DEBUG_INFO_NOFLAGS;
    }
}
#endif

/**
 * Update the button inputs for Mario.
 */
void update_mario_button_inputs(struct MarioState *m) {
    if (m->controller->buttonPressed & A_BUTTON) m->input |= INPUT_A_PRESSED;
    if (m->controller->buttonDown    & A_BUTTON) m->input |= INPUT_A_DOWN;
#ifdef CUSTOM_DEBUG
    if (m->controller->buttonPressed & L_JPAD) gCustomDebugMode ^= TRUE;
    if (gCustomDebugMode) {
        if (m->controller->buttonPressed & R_JPAD) set_mario_action(gMarioState, (gMarioState->action == ACT_DEBUG_FREE_MOVE) ? ACT_IDLE : ACT_DEBUG_FREE_MOVE, 0);
    } else if (gMarioState->action == ACT_DEBUG_FREE_MOVE) {
        set_mario_action(gMarioState, ACT_IDLE, 0);
    }
#endif
    // Don't update for these buttons if squished.
    if (m->squishTimer == 0) {
        if (m->controller->buttonDown    & B_BUTTON) m->input |= INPUT_B_DOWN;
        if (m->controller->buttonPressed & B_BUTTON) m->input |= INPUT_B_PRESSED;
        if (m->controller->buttonDown    & Z_TRIG  ) m->input |= INPUT_Z_DOWN;
        if (m->controller->buttonPressed & Z_TRIG  ) m->input |= INPUT_Z_PRESSED;
    }
    if (m->input & INPUT_A_PRESSED) {
        m->framesSinceA = 0;
    } else if (m->framesSinceA < 0xFF) {
        m->framesSinceA++;
    }
    if (m->input & INPUT_B_PRESSED) {
        m->framesSinceB = 0;
    } else if (m->framesSinceB < 0xFF) {
        m->framesSinceB++;
    }
}

/**
 * Updates the joystick intended magnitude.
 */
void update_mario_joystick_inputs(struct MarioState *m) {
    struct Controller *controller = m->controller;
    f32 mag = ((controller->stickMag / 64.0f) * (controller->stickMag / 64.0f)) * 64.0f;
    m->intendedMag = mag / (m->squishTimer == 0 ? 2.0f : 8.0f);
    if (m->intendedMag > 0.0f) {
        m->intendedYaw = atan2s(-controller->stickY, controller->stickX) + m->area->camera->yaw;
        m->input |= INPUT_NONZERO_ANALOG;
    } else {
        m->intendedYaw = m->faceAngle[1];
    }
}

/**
 * Resolves wall collisions, and updates a variety of inputs.
 */
void update_mario_geometry_inputs(struct MarioState *m) {
    f32 gasLevel;
    f32 ceilToFloorDist;
    f32_find_wall_collision(&m->pos[0], &m->pos[1], &m->pos[2], 60.0f, 50.0f);
    f32_find_wall_collision(&m->pos[0], &m->pos[1], &m->pos[2], 30.0f, 24.0f);
    m->floorHeight = find_floor(m->pos[0], m->pos[1], m->pos[2], &m->floor);
    // If Mario is OOB, move his position to his graphical position (which was not updated)
    // and check for the floor there.
    // This can cause errant behavior when combined with astral projection,
    // since the graphical position was not Mario's previous location.
    if (m->floor == NULL) {
        vec3f_copy(m->pos, m->marioObj->header.gfx.pos);
        m->floorHeight = find_floor(m->pos[0], m->pos[1], m->pos[2], &m->floor);
    }
    m->ceilHeight = vec3f_find_ceil(m->pos, m->pos[1], &m->ceil);
    gasLevel      = find_poison_gas_level(m->pos[0], m->pos[2]);
    m->waterLevel = find_water_level(m->pos[0], m->pos[2]);
    if (m->floor != NULL) {
        m->floorAngle         = atan2s(m->floor->normal.z, m->floor->normal.x);
        m->terrainSoundAddend = mario_get_terrain_sound_addend(m);
        if ((m->pos[1] > m->waterLevel - 40) && mario_floor_is_slippery(m)) m->input |= INPUT_ABOVE_SLIDE;
        if ((m->floor->flags & SURFACE_FLAG_DYNAMIC) || (m->ceil && m->ceil->flags & SURFACE_FLAG_DYNAMIC)) {
            ceilToFloorDist = m->ceilHeight - m->floorHeight;
            if ((0.0f <= ceilToFloorDist) && (ceilToFloorDist <= gMarioObject->hitboxHeight-10.0f)) m->input |= INPUT_SQUISHED;
        }
        if (m->pos[1] > m->floorHeight + 80.0f)  m->input |= INPUT_OFF_FLOOR;
        if (m->pos[1] < (m->waterLevel - 10.0f)) m->input |= INPUT_IN_WATER;
        if (m->pos[1] <     (gasLevel - 100.0f)) m->input |= INPUT_IN_POISON_GAS;
    } else {
        level_trigger_warp(m, WARP_OP_DEATH);
    }
}

/**
 * Handles Mario's input flags as well as a couple timers.
 */
void update_mario_inputs(struct MarioState *m) {
    m->particleFlags            = 0;
    m->input                    = 0;
    m->collidedObjInteractTypes = m->marioObj->collidedObjInteractTypes;
    m->flags                   &= 0xFFFFFF;
    update_mario_button_inputs(m);
    update_mario_joystick_inputs(m);
    update_mario_geometry_inputs(m);
#ifdef DEBUG_INFO
    debug_print_speed_action_normal(m);
#endif
    if (gCameraMovementFlags & CAM_MOVE_C_UP_MODE) {
        if (m->action & ACT_FLAG_ALLOW_FIRST_PERSON ||
        (m->vel[0] < 8.0f && m->vel[1] < 8.0f && m->vel[2] < 8.0f && m->pos[1] <= m->floorHeight)) {
            m->input |= INPUT_FIRST_PERSON;
        } else {
            gCameraMovementFlags &= ~CAM_MOVE_C_UP_MODE;
        }
    }
    if (!(m->input & (INPUT_NONZERO_ANALOG | INPUT_A_PRESSED))) m->input |= INPUT_IDLE;
    // These 3 flags are defined by Bowser stomping attacks
    if (m->marioObj->oInteractStatus & (INT_STATUS_MARIO_STUNNED | INT_STATUS_MARIO_KNOCKBACK_DMG | INT_STATUS_MARIO_SHOCKWAVE)) m->input |= INPUT_STOMPED;
    // This function is located near other unused trampoline functions,
    // perhaps logically grouped here with the timers.
    stub_mario_step_1(m);
    if (m->wallKickTimer   > 0) m->wallKickTimer--;
    if (m->doubleJumpTimer > 0) m->doubleJumpTimer--;
}

/**
 * Set's the camera preset for submerged action behaviors.
 */
void set_submerged_cam_preset_and_spawn_bubbles(struct MarioState *m) {
    f32 heightBelowWater;
    s16 camPreset;
#ifdef REONU_CAM_3
    extern s16 s8DirModeBaseYaw;
    if (!gWaterCamOverride) {
        if ((m->action & ACT_GROUP_MASK) == ACT_GROUP_SUBMERGED) {
            heightBelowWater = (f32)(m->waterLevel - 80) - m->pos[1];
            camPreset = m->area->camera->mode;
            if (m->action & ACT_FLAG_METAL_WATER) {
                if (camPreset != CAMERA_MODE_CLOSE) set_camera_mode(m->area->camera, CAMERA_MODE_CLOSE, 1);
            } else {
                if ((heightBelowWater > 800.0f) && (camPreset != CAMERA_MODE_BEHIND_MARIO )) set_camera_mode(m->area->camera, CAMERA_MODE_BEHIND_MARIO , 1);
                if ((heightBelowWater < 400.0f) && (camPreset != CAMERA_MODE_WATER_SURFACE)) set_camera_mode(m->area->camera, CAMERA_MODE_WATER_SURFACE, 1);
                // As long as Mario isn't drowning or at the top
                // of the water with his head out, spawn bubbles.
                if (!(m->action & ACT_FLAG_INTANGIBLE) && ((m->pos[1] < (f32)(m->waterLevel - 160)) || (m->faceAngle[0] < -0x800))) m->particleFlags |= PARTICLE_BUBBLE;
            }
        }
    } else {
        set_camera_mode(m->area->camera, CAMERA_MODE_8_DIRECTIONS, 1);
    }
    if ((gPlayer1Controller->buttonPressed & R_TRIG) && (m->action & ACT_FLAG_SWIMMING)) {
        s8DirModeBaseYaw = ((gMarioState->faceAngle[1]-0x8000) + 0x1000) & 0xE000;
        gWaterCamOverride ^= TRUE;
    }
#else
    if ((m->action & ACT_GROUP_MASK) == ACT_GROUP_SUBMERGED) {
        heightBelowWater = (f32)(m->waterLevel - 80) - m->pos[1];
        camPreset = m->area->camera->mode;
        if (m->action & ACT_FLAG_METAL_WATER) {
            if (camPreset != CAMERA_MODE_CLOSE) set_camera_mode(m->area->camera, CAMERA_MODE_CLOSE, 1);
        } else {
            if ((heightBelowWater > 800.0f) && (camPreset != CAMERA_MODE_BEHIND_MARIO )) set_camera_mode(m->area->camera, CAMERA_MODE_BEHIND_MARIO , 1);
            if ((heightBelowWater < 400.0f) && (camPreset != CAMERA_MODE_WATER_SURFACE)) set_camera_mode(m->area->camera, CAMERA_MODE_WATER_SURFACE, 1);
            // As long as Mario isn't drowning or at the top
            // of the water with his head out, spawn bubbles.
            if (!(m->action & ACT_FLAG_INTANGIBLE) && ((m->pos[1] < (f32)(m->waterLevel - 160)) || (m->faceAngle[0] < -0x800))) m->particleFlags |= PARTICLE_BUBBLE;
        }
    }
#endif
}

/**
 * Both increments and decrements Mario's HP.
 */
void update_mario_health(struct MarioState *m) {
    s32 terrainIsSnow;
    if (m->health >= 0x100) {
        // When already healing or hurting Mario, Mario's HP is not changed any more here.
        if (((u32) m->healCounter | (u32) m->hurtCounter) == 0) {
            if ((m->input & INPUT_IN_POISON_GAS) && !(m->action & ACT_FLAG_INTANGIBLE)) {
                if (!(m->flags & MARIO_METAL_CAP) && !gDebugLevelSelect) m->health -= 4;
            } else {
                if ((m->action & ACT_FLAG_SWIMMING) && !(m->action & ACT_FLAG_INTANGIBLE)) {
                    terrainIsSnow = (m->area->terrainType & TERRAIN_MASK) == TERRAIN_SNOW;
#ifdef BREATH_METER
                    // when in snow terrains lose 3 health.
                    if ((m->pos[1] < (m->waterLevel - 140)) && terrainIsSnow) m->health -= 3;
#else
                    // When Mario is near the water surface, recover health (unless in snow),
                    // when in snow terrains lose 3 health.
                    // If using the debug level select, do not lose any HP to water.
                    if ((m->pos[1] >= (m->waterLevel - 140)) && !terrainIsSnow) {
                        m->health += 0x1A;
                    } else if (!gDebugLevelSelect) {
                        m->health -= (terrainIsSnow ? 3 : 1);
                    }
#endif
                }
            }
        }
        if (m->healCounter > 0) {
            m->health += 0x40;
            m->healCounter--;
        }
        if (m->hurtCounter > 0) {
            m->health -= 0x40;
            m->hurtCounter--;
#ifdef DAMAGE_SCREEN_TINT
            m->hurtShadeAlpha = 0x40;
#endif
        }
        if (m->health > 0x880) m->health = 0x880;
        if (m->health < 0x100) m->health = 0xFF;
#ifndef BREATH_METER
        // Play a noise to alert the player when Mario is close to drowning.
        if (((m->action & ACT_GROUP_MASK) == ACT_GROUP_SUBMERGED) && (m->health < 0x300) && !((m->flags & MARIO_METAL_CAP) > 0)) {
            play_sound(SOUND_MOVING_ALMOST_DROWNING, gGlobalSoundSource);
#if ENABLE_RUMBLE
            if (gRumblePakTimer == 0) {
                gRumblePakTimer = 36;
                if (is_rumble_finished_and_queue_empty()) queue_rumble_data(3, 30);
            }
        } else {
            gRumblePakTimer = 0;
#endif
        }
#endif
    }
}

#ifdef BREATH_METER
void update_mario_breath(struct MarioState *m) {
    if (m->breath >= 0x100 && m->health >= 0x100) {
        if (m->pos[1] < (m->waterLevel - 140.0f) && !(m->flags & MARIO_METAL_CAP) && !(m->action & ACT_FLAG_INTANGIBLE)) {
            m->breath--;
            if (m->breath < 0x300) {
                // Play a noise to alert the player when Mario is close to drowning.
                play_sound(SOUND_MOVING_ALMOST_DROWNING, gGlobalSoundSource);
#if ENABLE_RUMBLE
                if (gRumblePakTimer == 0) {
                    gRumblePakTimer = 36;
                    if (is_rumble_finished_and_queue_empty()) queue_rumble_data(3, 30);
                }
            } else {
                gRumblePakTimer = 0;
#endif
            }
        } else if (!(m->input & INPUT_IN_POISON_GAS)) {
            m->breath += 0x1A;
        }
        if (m->breathCounter > 0) {
            m->breath += 0x40;
            m->breathCounter--;
        }
        if (m->breath > 0x880) m->breath = 0x880;
        if (m->breath < 0x100) {
            m->breath =  0xFF;
            m->health =  0xFF;
        }
    }
}
#endif

/**
 * Updates some basic info for camera usage.
 */
void update_mario_info_for_cam(struct MarioState *m) {
    m->marioBodyState->action  = m->action;
    m->statusForCamera->action = m->action;
    vec3s_copy(m->statusForCamera->faceAngle, m->faceAngle);
    if (!(m->flags & MARIO_LEDGE_CLIMB_CAMERA)) vec3f_copy(m->statusForCamera->pos, m->pos);
}

/**
 * Resets Mario's model, done every time an action is executed.
 */
void mario_reset_bodystate(struct MarioState *m) {
    struct MarioBodyState *bodyState = m->marioBodyState;
    bodyState->capState    = MARIO_HAS_DEFAULT_CAP_OFF;
    bodyState->eyeState    = MARIO_EYES_BLINK;
    bodyState->handState   = MARIO_HAND_FISTS;
    bodyState->modelState  = 0;
    bodyState->wingFlutter = FALSE;
    m->flags              &= ~MARIO_METAL_SHOCK;
}

/**
 * Adjusts Mario's graphical height for quicksand.
 */
void sink_mario_in_quicksand(struct MarioState *m) {
    struct Object *o = m->marioObj;
    if (o->header.gfx.throwMatrix) (*o->header.gfx.throwMatrix)[3][1] -= m->quicksandDepth;
    o->header.gfx.pos[1] -= m->quicksandDepth;
}

/**
 * Is a binary representation of the frames to flicker Mario's cap when the timer
 * is running out.
 *
 * Equals [1000]^5 . [100]^8 . [10]^9 . [1] in binary, which is
 * 100010001000100010001001001001001001001001001010101010101010101.
 */
u64 sCapFlickerFrames = 0x4444449249255555;

/**
 * Updates the cap flags mainly based on the cap timer.
 */
u32 update_and_return_cap_flags(struct MarioState *m) {
    u32 flags = m->flags;
    u32 action;
    if (m->capTimer > 0) {
        action = m->action;
        if ((m->capTimer <= 60)
            || ((action != ACT_READING_AUTOMATIC_DIALOG)
             && (action != ACT_READING_NPC_DIALOG)
             && (action != ACT_READING_SIGN)
             && (action != ACT_IN_CANNON))) m->capTimer--;
        if (m->capTimer == 0) {
            stop_cap_music();
            m->flags &= ~MARIO_SPECIAL_CAPS;
            if (!(m->flags & MARIO_CAPS)) m->flags &= ~MARIO_CAP_ON_HEAD;
        }
        if (m->capTimer == 60) fadeout_cap_music();
        // This code flickers the cap through a long binary string, increasing in how
        // common it flickers near the end.
        if ((m->capTimer < 64) && ((1ULL << m->capTimer) & sCapFlickerFrames)) {
            flags &= ~MARIO_SPECIAL_CAPS;
            if (!(flags & MARIO_CAPS)) flags &= ~MARIO_CAP_ON_HEAD;
        }
    }
    return flags;
}

/**
 * Updates the Mario's cap, rendering, and hitbox.
 */
void mario_update_hitbox_and_cap_model(struct MarioState *m) {
    struct MarioBodyState *bodyState = m->marioBodyState;
    s32 flags = update_and_return_cap_flags(m);
    if (flags & MARIO_VANISH_CAP ) bodyState->modelState  = MODEL_STATE_NOISE_ALPHA;
    if (flags & MARIO_METAL_CAP  ) bodyState->modelState |= MODEL_STATE_METAL;
    if (flags & MARIO_METAL_SHOCK) bodyState->modelState |= MODEL_STATE_METAL;
    //! (Pause buffered hitstun) Since the global timer increments while paused,
    //  this can be paused through to give continual invisibility. This leads to
    //  no interaction with objects.
    if ((m->invincTimer >= 3) && (gGlobalTimer & 1)) gMarioState->marioObj->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
    if (flags & MARIO_CAP_IN_HAND) bodyState->handState = (flags & MARIO_WING_CAP) ? MARIO_HAND_HOLDING_WING_CAP : MARIO_HAND_HOLDING_CAP;
    if (flags & MARIO_CAP_ON_HEAD) bodyState->capState  = (flags & MARIO_WING_CAP) ? MARIO_HAS_WING_CAP_ON       : MARIO_HAS_DEFAULT_CAP_ON;
    // Short hitbox for crouching/crawling/etc.
    m->marioObj->hitboxHeight = (m->action & ACT_FLAG_SHORT_HITBOX) ? 100.0f : 160.0f;
    if ((m->flags & MARIO_TELEPORTING) && (m->fadeWarpOpacity != 0xFF)) {
        bodyState->modelState &= ~MODEL_STATE_MASK;
        bodyState->modelState |= (MODEL_STATE_ALPHA | m->fadeWarpOpacity);
    }
}

/**
 * An unused and possibly a debug function. Z + another button input
 * sets Mario with a different cap.
 */
UNUSED static void debug_update_mario_cap(u16 button, s32 flags, u16 capTimer, u16 capMusic) {
    // This checks for Z_TRIG instead of Z_DOWN flag
    // (which is also what other debug functions do),
    // so likely debug behavior rather than unused behavior.
    if ((gPlayer1Controller->buttonDown & Z_TRIG) && (gPlayer1Controller->buttonPressed & button)
        && !(gMarioState->flags & flags)) {
        gMarioState->flags |= (flags + MARIO_CAP_ON_HEAD);
        if (capTimer > gMarioState->capTimer) gMarioState->capTimer = capTimer;
        play_cap_music(capMusic);
    }
}

#if ENABLE_RUMBLE
void queue_rumble_particles(void) {
    if (gMarioState->particleFlags & PARTICLE_HORIZONTAL_STAR
     || gMarioState->particleFlags & PARTICLE_VERTICAL_STAR
     || gMarioState->particleFlags & PARTICLE_TRIANGLE) queue_rumble_data(5, 80);
    if (gMarioState->heldObj && gMarioState->heldObj->behavior == segmented_to_virtual(bhvBobomb)) reset_rumble_timers_slip();
}
#endif

/**
 * Main function for executing Mario's behavior.
 */
s32 execute_mario_action(UNUSED struct Object *o) {
    s32 inLoop = TRUE;
    if (gMarioState->action) {
        gMarioState->marioObj->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
        mario_reset_bodystate(      gMarioState);
        update_mario_inputs(        gMarioState);
        mario_handle_special_floors(gMarioState);
        mario_process_interactions( gMarioState);
        // If Mario is OOB, stop executing actions.
        if (gMarioState->floor == NULL) return FALSE;
        // The function can loop through many action shifts in one frame,
        // which can lead to unexpected sub-frame behavior. Could potentially hang
        // if a loop of actions were found, but there has not been a situation found.
        while (inLoop) {
            switch (gMarioState->action & ACT_GROUP_MASK) {
                case ACT_GROUP_STATIONARY: inLoop = mario_execute_stationary_action(gMarioState); break;
                case ACT_GROUP_MOVING:     inLoop = mario_execute_moving_action(    gMarioState); break;
                case ACT_GROUP_AIRBORNE:   inLoop = mario_execute_airborne_action(  gMarioState); break;
                case ACT_GROUP_SUBMERGED:  inLoop = mario_execute_submerged_action( gMarioState); break;
                case ACT_GROUP_CUTSCENE:   inLoop = mario_execute_cutscene_action(  gMarioState); break;
                case ACT_GROUP_AUTOMATIC:  inLoop = mario_execute_automatic_action( gMarioState); break;
                case ACT_GROUP_OBJECT:     inLoop = mario_execute_object_action(    gMarioState); break;
            }
        }
        sink_mario_in_quicksand(                   gMarioState);
        squish_mario_model(                        gMarioState);
        set_submerged_cam_preset_and_spawn_bubbles(gMarioState);
        update_mario_health(                       gMarioState);
#ifdef BREATH_METER
        update_mario_breath(                       gMarioState);
#endif
        update_mario_info_for_cam(                 gMarioState);
        mario_update_hitbox_and_cap_model(         gMarioState);
        // Both of the wind handling portions play wind audio only in
        // non-Japanese releases.
        if (gMarioState->floor->type == SURFACE_HORIZONTAL_WIND) {
            spawn_wind_particles(0, (gMarioState->floor->force << 8));
            play_sound(SOUND_ENV_WIND2, gMarioState->marioObj->header.gfx.cameraToObject);
        }
        if (gMarioState->floor->type == SURFACE_VERTICAL_WIND) {
            spawn_wind_particles(1, 0);
            play_sound(SOUND_ENV_WIND2, gMarioState->marioObj->header.gfx.cameraToObject);
        }
        play_infinite_stairs_music();
        gMarioState->marioObj->oInteractStatus = INT_STATUS_NONE;
#if ENABLE_RUMBLE
        queue_rumble_particles();
#endif
        return gMarioState->particleFlags;
    }
    return FALSE;
}

/**************************************************
 *                  INITIALIZATION                *
 **************************************************/

void init_mario(void) {
    Vec3s capPos;
    struct Object *capObject;
    sDebugMode                = 0;
    gMarioState->actionTimer  = 0;
    gMarioState->framesSinceA = 0xFF;
    gMarioState->framesSinceB = 0xFF;
    gMarioState->invincTimer  = 0;
    if (save_file_get_flags() & (SAVE_FLAG_CAP_ON_GROUND | SAVE_FLAG_CAP_ON_KLEPTO | SAVE_FLAG_CAP_ON_UKIKI | SAVE_FLAG_CAP_ON_MR_BLIZZARD)) {
        gMarioState->flags = 0;
    } else {
        gMarioState->flags = (MARIO_NORMAL_CAP | MARIO_CAP_ON_HEAD);
    }
    gMarioState->forwardVel                           = 0.0f;
    gMarioState->squishTimer                          = 0;
    gMarioState->hurtCounter                          = 0;
    gMarioState->healCounter                          = 0;
#ifdef DAMAGE_SCREEN_TINT
    gMarioState->hurtShadeAlpha                       = 0;
#endif
    gMarioState->capTimer                             = 0;
    gMarioState->quicksandDepth                       = 0.0f;
    gMarioState->heldObj                              = NULL;
    gMarioState->riddenObj                            = NULL;
    gMarioState->usedObj                              = NULL;
    gMarioState->waterLevel                           = find_water_level(gMarioSpawnInfo->startPos[0], gMarioSpawnInfo->startPos[2]);
    gMarioState->area                                 = gCurrentArea;
    gMarioState->marioObj                             = gMarioObject;
    gMarioState->marioObj->header.gfx.animInfo.animID = -1;
    vec3s_copy(    gMarioState->faceAngle, gMarioSpawnInfo->startAngle);
    vec3s_set(     gMarioState->angleVel , 0, 0, 0);
    vec3s_to_vec3f(gMarioState->pos      , gMarioSpawnInfo->startPos);
    vec3f_set(     gMarioState->vel      , 0, 0, 0);
    gMarioState->floorHeight = find_floor(gMarioState->pos[0], gMarioState->pos[1], gMarioState->pos[2], &gMarioState->floor);
    if (gMarioState->pos[1] < gMarioState->floorHeight) gMarioState->pos[1] = gMarioState->floorHeight;
    gMarioState->marioObj->header.gfx.pos[1]          = gMarioState->pos[1];
    gMarioState->action = (gMarioState->pos[1] <= (gMarioState->waterLevel - 100)) ? ACT_WATER_IDLE : ACT_IDLE;
    mario_reset_bodystate(    gMarioState);
    update_mario_info_for_cam(gMarioState);
    gMarioState->marioBodyState->punchState           = 0;
    gMarioState->marioObj->oPosX                      = gMarioState->pos[0];
    gMarioState->marioObj->oPosY                      = gMarioState->pos[1];
    gMarioState->marioObj->oPosZ                      = gMarioState->pos[2];
    gMarioState->marioObj->oMoveAnglePitch            = gMarioState->faceAngle[0];
    gMarioState->marioObj->oMoveAngleYaw              = gMarioState->faceAngle[1];
    gMarioState->marioObj->oMoveAngleRoll             = gMarioState->faceAngle[2];
    vec3f_copy(gMarioState->marioObj->header.gfx.pos,        gMarioState->pos);
    vec3s_set( gMarioState->marioObj->header.gfx.angle, 0x0, gMarioState->faceAngle[1], 0x0);
    if (save_file_get_cap_pos(capPos) && (count_objects_with_behavior(bhvNormalCap) > 1)) {
        capObject                                     = spawn_object(gMarioState->marioObj, MODEL_MARIOS_CAP, bhvNormalCap);
        capObject->oPosX                              = capPos[0];
        capObject->oPosY                              = capPos[1];
        capObject->oPosZ                              = capPos[2];
        capObject->oForwardVel                        = 0.0f;
        capObject->oMoveAngleYaw                      = 0x0;
    }
}

void init_mario_from_save_file(void) {
    gMarioState->floorAlignMatrixIndex = 0;
    gMarioState->flags                 = 0;
    gMarioState->action                = 0;
    gMarioState->spawnInfo             = &gPlayerSpawnInfos[0];
    gMarioState->statusForCamera       = &gPlayerCameraState[0];
    gMarioState->marioBodyState        = &gBodyStates[0];
    gMarioState->controller            = &gControllers[0];
    gMarioState->animList              = &gMarioAnimsBuf;
    gMarioState->numCoins              = 0;
    gMarioState->numStars              = save_file_get_total_star_count(gCurrSaveFileNum - 1, COURSE_MIN - 1, COURSE_MAX - 1);
    gMarioState->numKeys               = 0;
    if (save_file_get_flags() & SAVE_FLAG_HAVE_KEY_1) gMarioState->numKeys++;
    if (save_file_get_flags() & SAVE_FLAG_HAVE_KEY_2) gMarioState->numKeys++;
    gMarioState->numLives              = 4;
    gMarioState->health                = 0x880;
    gMarioState->prevNumStarsForDialog = gMarioState->numStars;
    gMarioState->animYTrans            = 0xBD;
#ifdef BREATH_METER
    gMarioState->breath                = 0x880;
    gHudDisplay.breath                 = 8;
#endif
    gHudDisplay.coins                  = 0;
    gHudDisplay.wedges                 = 8;
}
