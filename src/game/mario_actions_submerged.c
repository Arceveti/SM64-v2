#include <PR/ultratypes.h>

#include "sm64.h"
#include "mario_actions_submerged.h"
#include "level_update.h"
#include "boot/memory.h"
#include "engine/math_util.h"
#include "area.h"
#include "boot/game_init.h"
#include "save_file.h"
#include "sound_init.h"
#ifdef UNDERWATER_STEEP_FLOORS_AS_WALLS
#include "object_list_processor.h"
#endif
#include "engine/surface_collision.h"
#include "interaction.h"
#include "mario.h"
#include "mario_step.h"
#include "camera.h"
#include "audio/external.h"
#include "behavior_data.h"
#include "level_table.h"
#include "rumble_init.h"

#define MIN_SWIM_STRENGTH 160
#define MIN_SWIM_SPEED    16.0f

static Bool16 sWasAtSurface         = FALSE;
static s16    sSwimStrength         = MIN_SWIM_STRENGTH;
static s16    sWaterCurrentSpeeds[] = { 28, 12, 8, 4 };

static s16 sBobTimer;
static s16 sBobIncrement;
static f32 sBobHeight;

static void set_swimming_at_surface_particles(struct MarioState *m, u32 particleFlag) {
    Bool16 atSurface = (m->pos[1] >= (m->waterLevel - 130));
    if (atSurface) {
        m->particleFlags |= particleFlag;
        if (atSurface ^ sWasAtSurface) play_sound(SOUND_ACTION_SWIM_SURFACE, m->marioObj->header.gfx.cameraToObject);
    }
    sWasAtSurface = atSurface;
}

static s32 swimming_near_surface(struct MarioState *m) {
    if (m->flags & MARIO_METAL_CAP) return FALSE;
    return ((m->waterLevel - 80) - m->pos[1] < 400.0f);
}

static f32 get_buoyancy(struct MarioState *m) {
    f32 buoyancy = 0.0f;
    if (m->flags & MARIO_METAL_CAP) {
        buoyancy = ((m->action & ACT_FLAG_INVULNERABLE) ? -2.0f : -18.0f);
    } else if (swimming_near_surface(m)) {
        buoyancy = 1.25f;
    } else if (!(m->action & ACT_FLAG_MOVING)) {
        buoyancy = -2.0f;
    }
    return buoyancy;
}

#if WATER_NUM_STEPS > 1
static u32 perform_water_quarter_step(struct MarioState *m, Vec3f nextPos) {
    struct WallCollisionData wallData;
    struct Surface *ceil;
    struct Surface *floor;
    f32 ceilAmt;
    // f32 floorAmt;
    m->wall = NULL;
#ifdef UNDERWATER_STEEP_FLOORS_AS_WALLS
    gIncludeSteepFloorsInWallCollisionCheck = TRUE;
#endif
    resolve_and_return_wall_collision_data(nextPos, 10.0f, 110.0f, &wallData);
    f32 floorHeight = find_floor(nextPos[0], (nextPos[1] + m->midY), nextPos[2], &floor);
    f32 ceilHeight  = find_ceil( nextPos[0], (nextPos[1] + m->midY), nextPos[2], &ceil);
#ifndef ALLOW_OOB
    if (floor == NULL) return WATER_STEP_CANCELLED;
#endif
    if ((ceil != NULL) && (((nextPos[1] + MARIO_HITBOX_HEIGHT) >= ceilHeight) || ((ceilHeight - floorHeight) < MARIO_HITBOX_HEIGHT))) {
        ceilAmt = ((nextPos[1] + MARIO_HITBOX_HEIGHT) - ceilHeight);
        nextPos[0] += (ceil->normal.x * ceilAmt);
        nextPos[1] = (ceilHeight - MARIO_HITBOX_HEIGHT);
        nextPos[2] += (ceil->normal.z * ceilAmt);
        vec3_copy(m->pos, nextPos);
        set_mario_floor(m, floor, floorHeight);
        set_mario_wall(m, ((wallData.numWalls > 0) ? wallData.walls[0] : NULL)); //! only returns the first wall
        return WATER_STEP_HIT_CEILING;
    }
    if (nextPos[1] <= floorHeight) {
        nextPos[1]  = floorHeight;
        vec3_copy(m->pos, nextPos);
        set_mario_floor(m, floor, floorHeight);
        set_mario_wall(m, ((wallData.numWalls > 0) ? wallData.walls[0] : NULL)); //! only returns the first wall
        return WATER_STEP_HIT_FLOOR;
    }
    vec3_copy(m->pos, nextPos);
    set_mario_floor(m, floor, floorHeight);
    set_mario_ceil( m,  ceil,  ceilHeight);
    if (wallData.numWalls > 0) {
        set_mario_wall(m, wallData.walls[0]); //! only returns the first wall
        return WATER_STEP_HIT_WALL;
    } else {
        return WATER_STEP_NONE;
    }
}
#else
static u32 perform_water_full_step(struct MarioState *m, Vec3f nextPos) {
    struct WallCollisionData wallData;
    struct Surface *wall;
    struct Surface *ceil;
    struct Surface *floor;
    resolve_and_return_wall_collision_data(nextPos, 10.0f, 110.0f, &wallData);
    set_mario_wall(m, ((wallData.numWalls > 0) ? wallData.walls[0] : NULL)); //! only returns the first wall
    f32 floorHeight = find_floor(nextPos[0], (nextPos[1] + m->midY), nextPos[2], &floor);
    f32 ceilHeight  = find_ceil( nextPos[0], (nextPos[1] + m->midY), nextPos[2], &ceil);
#ifndef ALLOW_OOB
    if (floor == NULL) return WATER_STEP_CANCELLED;
#endif
    if (nextPos[1] >= floorHeight) {
        if ((ceilHeight - nextPos[1]) >= MARIO_HITBOX_HEIGHT) {
            vec3_copy(m->pos, nextPos);
            set_mario_floor(m, floor, floorHeight);
            return ((wall != NULL) ? WATER_STEP_HIT_WALL : WATER_STEP_NONE);
        }
        if ((ceilHeight - floorHeight) < MARIO_HITBOX_HEIGHT) return WATER_STEP_CANCELLED;
        //! Water ceiling downwarp
        vec3_set(m->pos, nextPos[0], (ceilHeight - MARIO_HITBOX_HEIGHT), nextPos[2]);
        set_mario_floor(m, floor, floorHeight);
        return WATER_STEP_HIT_CEILING;
    } else {
        if ((ceilHeight - floorHeight) < MARIO_HITBOX_HEIGHT) return WATER_STEP_CANCELLED;
        vec3_set(m->pos, nextPos[0], floorHeight, nextPos[2]);
        set_mario_floor(m, floor, floorHeight);
        return WATER_STEP_HIT_FLOOR;
    }
}
#endif

static void apply_water_current(struct MarioState *m, Vec3f step) {
    s32 i;
    f32 whirlpoolRadius = 2000.0f;
    if (m->floor && (m->floor->type == SURFACE_FLOWING_WATER)) {
        Angle currentAngle = (m->floor->force << 8);
        f32 currentSpeed = sWaterCurrentSpeeds[m->floor->force >> 8];
        step[0] += (currentSpeed * sins(currentAngle));
        step[2] += (currentSpeed * coss(currentAngle));
    }
    for ((i = 0); (i < 2); (i++)) {
        struct Whirlpool *whirlpool = gCurrentArea->whirlpools[i];
        if (whirlpool != NULL) {
            Vec3f d;
            vec3_diff(d, whirlpool->pos, m->pos);
            f32 strength           = 0.0f;
            f32 ld                 = (sqr(d[0]) + sqr(d[2]));
            f32 distance           = sqrtf(ld + sqr(d[1]));
            Angle pitchToWhirlpool = atan2s(sqrtf(ld), d[1]);
            Angle yawToWhirlpool   = atan2s(d[2], d[0]);
            yawToWhirlpool -= (Angle)(DEG(45) * (1000.0f / (distance + 1000.0f)));
            if (whirlpool->strength >= 0) {
                if ((gCurrLevelNum == LEVEL_DDD) && (gCurrAreaIndex == 2)) whirlpoolRadius = 4000.0f;
                if ((distance >= 26.0f) && (distance < whirlpoolRadius)) strength = (whirlpool->strength * (1.0f - (distance / whirlpoolRadius)));
            } else if (distance < 2000.0f) {
                strength = (whirlpool->strength * (1.0f - distance / 2000.0f));
            }
            step[0] += (strength * coss(pitchToWhirlpool) * sins(yawToWhirlpool));
            step[1] += (strength * sins(pitchToWhirlpool)                       );
            step[2] += (strength * coss(pitchToWhirlpool) * coss(yawToWhirlpool));
        }
    }
}

static MarioStep perform_water_step(struct MarioState *m) {
    MarioStep stepResult = WATER_STEP_NONE;
    Vec3f nextPos;
    Vec3f step;
    struct Object *marioObj = m->marioObj;
    vec3_copy(step, m->vel);
    if (m->action & ACT_FLAG_SWIMMING) apply_water_current(m, step);
#if WATER_NUM_STEPS > 1
 #ifdef VARIABLE_STEPS
    const f32 speed = (m->moveSpeed / 8.0f);
    const f32 numSteps = MAX(WATER_NUM_STEPS, speed);
 #else
    const f32 numSteps = WATER_NUM_STEPS;
 #endif
    u32 i;
    for ((i = 0); (i < numSteps); (i++)) {
        nextPos[0] = (m->pos[0] + (step[0] / numSteps));
        nextPos[1] = (m->pos[1] + (step[1] / numSteps));
        nextPos[2] = (m->pos[2] + (step[2] / numSteps));
        // If Mario is at the surface, keep him there?
        if (nextPos[1] > (m->waterLevel - 80)) {
            nextPos[1] = (m->waterLevel - 80);
            m->vel[1]  = 0.0f;
        }
        stepResult = perform_water_quarter_step(m, nextPos);
        if (stepResult == WATER_STEP_CANCELLED) break;
    }
#else
    vec3_sum(nextPos, m->pos, step);
    if (nextPos[1] > (m->waterLevel - 80)) {
        nextPos[1] = (m->waterLevel - 80);
        m->vel[1]  = 0.0f;
    }
    stepResult = perform_water_full_step(m, nextPos);
#endif
    vec3_copy(marioObj->header.gfx.pos, m->pos);
    vec3_set( marioObj->header.gfx.angle, -m->faceAngle[0], m->faceAngle[1], m->faceAngle[2]);
    return stepResult;
}

static void update_water_pitch(struct MarioState *m) {
    struct Object *marioObj = m->marioObj;
    if (marioObj->header.gfx.angle[0] > 0x0) marioObj->header.gfx.pos[1]  += (60.0f * sins(marioObj->header.gfx.angle[0]) * sins(marioObj->header.gfx.angle[0])); // GRAVITY
    if (marioObj->header.gfx.angle[0] < 0x0) marioObj->header.gfx.angle[0] =              (marioObj->header.gfx.angle[0]  * 0.6f);  // 3 / 5; //  6 / 10;
    if (marioObj->header.gfx.angle[0] > 0x0) marioObj->header.gfx.angle[0] =              (marioObj->header.gfx.angle[0]  * 1.25f); // 5 / 4; // 10 /  8;
}

static void stationary_slow_down(struct MarioState *m) {
    f32 buoyancy    = get_buoyancy(m);
    m->angleVel[0]  = 0x0;
    m->angleVel[1]  = 0x0;
    approach_f32_bool(&m->forwardVel, 0.0f, 1.0f, 1.0f);
    approach_f32_bool(&m->vel[1], buoyancy, 2.0f, 1.0f);
    approach_s16_bool(&m->faceAngle[0], 0x0, 0x200, 0x200);
    approach_s16_bool(&m->faceAngle[2], 0x0, 0x100, 0x100);
    m->vel[0]       = (m->forwardVel * coss(m->faceAngle[0]) * sins(m->faceAngle[1]));
    m->vel[2]       = (m->forwardVel * coss(m->faceAngle[0]) * coss(m->faceAngle[1]));
}

static void update_swimming_speed(struct MarioState *m, f32 decelThreshold) {
    f32 buoyancy = get_buoyancy(m);
    f32 maxSpeed = MAX_SWIMMING_SPEED;
    if (m->action & ACT_FLAG_STATIONARY) m->forwardVel -= 2.0f;
    if (m->forwardVel < 0.0f           ) m->forwardVel  = 0.0f;
    if (m->forwardVel > maxSpeed       ) m->forwardVel  = maxSpeed;
    if (m->forwardVel > decelThreshold ) m->forwardVel -= 0.5f;
    m->vel[0] =  (m->forwardVel * coss(m->faceAngle[0]) * sins(m->faceAngle[1]));
    m->vel[1] = ((m->forwardVel * sins(m->faceAngle[0])) + buoyancy);
    m->vel[2] =  (m->forwardVel * coss(m->faceAngle[0]) * coss(m->faceAngle[1]));
}

static void update_swimming_yaw(struct MarioState *m) {
    Angle targetYawVel = -(Angle)(10.0f * m->controller->stickX);
    if (targetYawVel > 0x0) {
        if (m->angleVel[1] < 0x0) {
            m->angleVel[1] += 0x40;
            if (m->angleVel[1] > 0x10) m->angleVel[1] = 0x10;
        } else {
            approach_s16_bool(&m->angleVel[1], targetYawVel, 0x10, 0x20);
        }
    } else if (targetYawVel < 0x0) {
        if (m->angleVel[1] > 0x0) {
            m->angleVel[1] -= 0x40;
            if (m->angleVel[1] < -0x10) m->angleVel[1] = -0x10;
        } else {
            approach_s16_bool(&m->angleVel[1], targetYawVel, 0x20, 0x10);
        }
    } else {
        approach_s16_symmetric_bool(&m->angleVel[1], 0x0, 0x40);
    }
    m->faceAngle[1] += m->angleVel[1];
    m->faceAngle[2] = (-m->angleVel[1] * 0x8);
}

static void update_swimming_pitch(struct MarioState *m) {
    Angle targetPitch = -(Angle)(256.0f * m->controller->stickY);
    Angle pitchVel    = ((m->faceAngle[0] < 0x0) ? 0x100 : 0x200);
    approach_angle_bool(&m->faceAngle[0], targetPitch, pitchVel);
}

static void common_idle_step(struct MarioState *m, AnimID32 animation, AnimAccel animSpeed) {
#ifdef ENABLE_DEBUG_FREE_MOVE
    if (gPlayer1Controller->buttonDown & U_JPAD) {
        set_camera_mode(m->area->camera, CAMERA_MODE_8_DIRECTIONS, 1);
        set_mario_action(m, ACT_DEBUG_FREE_MOVE, 0);
        return;
    }
#endif
    update_swimming_yaw(m);
    update_swimming_pitch(m);
    update_swimming_speed(m, MIN_SWIM_SPEED);
    perform_water_step(m);
    update_water_pitch(m);
    //? What does this do with the head angle?
    if (m->faceAngle[0] > 0x0) {
        // approach_angle_asymmetric_bool?
        approach_s16_bool(&m->marioBodyState->headAngle[0], (m->faceAngle[0] / 0x2), 0x80, 0x200);
    } else {
        approach_angle_bool(&m->marioBodyState->headAngle[0], 0x0, 0x200);
    }
    if (animSpeed == 0x0) {
        set_mario_animation(m, animation);
    } else {
        set_mario_anim_with_accel(m, animation, animSpeed);
    }
    set_swimming_at_surface_particles(m, PARTICLE_IDLE_WATER_WAVE);
}

static Bool32 act_water_idle(struct MarioState *m) {
    AnimAccel animSpeed = 0x10000;
#ifdef ENABLE_DEBUG_FREE_MOVE
    if (gPlayer1Controller->buttonDown & U_JPAD) {
        set_camera_mode(m->area->camera, CAMERA_MODE_8_DIRECTIONS, 1);
        return set_mario_action(m, ACT_DEBUG_FREE_MOVE, 0);
    }
#endif
    if (m->flags & MARIO_METAL_CAP) return set_mario_action(         m, ACT_METAL_WATER_FALLING, 1);
    if (m->input & INPUT_B_PRESSED) return set_mario_action(         m, ACT_WATER_PUNCH        , 0);
    if (m->input & INPUT_A_PRESSED) return set_mario_action(         m, ACT_BREASTSTROKE       , 0);
#ifdef WATER_GROUND_POUND
    if (m->input & INPUT_Z_PRESSED) return drop_and_set_mario_action(m, ACT_WATER_GROUND_POUND , 0);
#endif
    if (m->faceAngle[0] < -DEG(22.5)) animSpeed = 0x30000;
    common_idle_step(m, MARIO_ANIM_WATER_IDLE, animSpeed);
    return FALSE;
}

static Bool32 act_hold_water_idle(struct MarioState *m) {
    if (m->flags & MARIO_METAL_CAP                                 ) return set_mario_action         (m, ACT_HOLD_METAL_WATER_FALLING, 0);
    if (m->marioObj->oInteractStatus & INT_STATUS_MARIO_DROP_OBJECT) return drop_and_set_mario_action(m, ACT_WATER_IDLE              , 0);
    if (m->input & INPUT_B_PRESSED                                 ) return set_mario_action(         m, ACT_WATER_THROW             , 0);
    if (m->input & INPUT_A_PRESSED                                 ) return set_mario_action(         m, ACT_HOLD_BREASTSTROKE       , 0);
    common_idle_step(m, MARIO_ANIM_WATER_IDLE_WITH_OBJ, 0);
    return FALSE;
}

static Bool32 act_water_action_end(struct MarioState *m) {
    if (m->flags & MARIO_METAL_CAP) return set_mario_action(         m, ACT_METAL_WATER_FALLING, 1);
    if (m->input & INPUT_B_PRESSED) return set_mario_action(         m, ACT_WATER_PUNCH        , 0);
    if (m->input & INPUT_A_PRESSED) return set_mario_action(         m, ACT_BREASTSTROKE       , 0);
#ifdef WATER_GROUND_POUND
    if (m->input & INPUT_Z_PRESSED) return drop_and_set_mario_action(m, ACT_WATER_GROUND_POUND , 0);
#endif
    common_idle_step(m, MARIO_ANIM_WATER_ACTION_END, 0);
    if (is_anim_at_end(m)) set_mario_action(m, ACT_WATER_IDLE, 0);
    return FALSE;
}

static Bool32 act_hold_water_action_end(struct MarioState *m) {
    if (m->flags & MARIO_METAL_CAP                                 ) return set_mario_action(         m, ACT_HOLD_METAL_WATER_FALLING, 0);
    if (m->marioObj->oInteractStatus & INT_STATUS_MARIO_DROP_OBJECT) return drop_and_set_mario_action(m, ACT_WATER_IDLE              , 0);
    if (m->input & INPUT_B_PRESSED                                 ) return set_mario_action(         m, ACT_WATER_THROW             , 0);
    if (m->input & INPUT_A_PRESSED                                 ) return set_mario_action(         m, ACT_HOLD_BREASTSTROKE       , 0);
#ifdef WATER_GROUND_POUND
    if (m->input & INPUT_Z_PRESSED                                 ) return drop_and_set_mario_action(m, ACT_WATER_GROUND_POUND      , 0);
#endif
    common_idle_step(m, ((m->actionArg == 0) ? MARIO_ANIM_WATER_ACTION_END_WITH_OBJ : MARIO_ANIM_STOP_GRAB_OBJ_WATER), 0);
    if (is_anim_at_end(m)) set_mario_action(m, ACT_HOLD_WATER_IDLE, 0);
    return FALSE;
}

static void reset_bob_variables(struct MarioState *m) {
    sBobTimer     = 0;
    sBobIncrement = 0x800;
    sBobHeight    = ((m->faceAngle[0] / 256.0f) + 20.0f);
}

/**
 * Controls the bobbing that happens when you swim near the surface.
 */
static void surface_swim_bob(struct MarioState *m) {
    if ((sBobIncrement != 0)
     && (m->pos[1] > (m->waterLevel - 85))
     && (m->faceAngle[0] >= 0x0)
     && ((sBobTimer += sBobIncrement) >= 0x0)) {
        m->marioObj->header.gfx.pos[1] += (sBobHeight * sins(sBobTimer)); // GRAVITY
        return;
    }
    sBobIncrement = 0x0;
}

static void common_swimming_step(struct MarioState *m, s16 swimStrength) {
#ifdef ENABLE_DEBUG_FREE_MOVE
    if (gPlayer1Controller->buttonDown & U_JPAD) {
        set_camera_mode(m->area->camera, CAMERA_MODE_8_DIRECTIONS, 1);
        set_mario_action(m, ACT_DEBUG_FREE_MOVE, 0);
        return;
    }
#endif
    update_swimming_yaw(m);
    update_swimming_pitch(m);
    update_swimming_speed(m, (swimStrength / 10.0f));
    switch (perform_water_step(m)) {
        case WATER_STEP_HIT_FLOOR:
            if (m->floor) {
#ifdef SMOOTH_WATER_FLOOR_PITCH
                // Angle floorPitch = atan2s(sqrtf(sqr(m->floor->normal.x) + sqr(m->floor->normal.z)), m->floor->normal.y);
                Angle floorPitch = atan2s(1.0f, m->floor->normal.y);
                if (m->faceAngle[0] < floorPitch) approach_angle_bool(&m->faceAngle[0], floorPitch, DEG(11.25));
#else
                Angle floorPitch = -find_floor_slope(m, -DEG(180), 5.0f);
                if (m->faceAngle[0] < floorPitch) m->faceAngle[0] = floorPitch;
#endif
            }
            break;
        case WATER_STEP_HIT_CEILING:
            if (m->faceAngle[0] > -DEG(67.5)) m->faceAngle[0] -= 0x100;
            break;
        case WATER_STEP_HIT_WALL:
            if (m->controller->stickY == 0.0f) {
                if (m->faceAngle[0] > 0.0f) {
                    m->faceAngle[0] += 0x200;
                    if (m->faceAngle[0] >  0x3F00) m->faceAngle[0] =  0x3F00;
                } else {
                    m->faceAngle[0] -= 0x200;
                    if (m->faceAngle[0] < -0x3F00) m->faceAngle[0] = -0x3F00;
                }
            }
            break;
    }
    update_water_pitch(m);
    approach_angle_bool(&m->marioBodyState->headAngle[0], 0x0, 0x200);
    surface_swim_bob(m);
    set_swimming_at_surface_particles(m, PARTICLE_WAVE_TRAIL);
}

static void play_swimming_noise(struct MarioState *m) {
    AnimFrame16 animFrame = m->marioObj->header.gfx.animInfo.animFrame;
    if ((animFrame == 0) || (animFrame == 12)) play_sound(SOUND_ACTION_FLUTTER_KICK, m->marioObj->header.gfx.cameraToObject);
}

static Bool32 check_water_jump(struct MarioState *m) {
    s32 probe = (s32)(m->pos[1] + 1.5f);
    if (m->input & INPUT_A_PRESSED) {
#ifdef BETTER_WATER_JUMP
        if ((probe >= (m->waterLevel - 80)) && (((m->faceAngle[0] >= 0x0) && (m->controller->stickY < -32.0f)) || (m->wall != NULL))) {
#else
        if ((probe >= (m->waterLevel - 80)) && (  m->faceAngle[0] >= 0x0) &&  m->controller->stickY < -60.0f) {
#endif
            vec3_zero(m->angleVel);
            m->vel[1] = 62.0f;
            return set_mario_action(m, ((m->heldObj == NULL) ? ACT_WATER_JUMP : ACT_HOLD_WATER_JUMP), 0);
        }
    }
    return FALSE;
}

#ifdef WATER_GROUND_POUND
static Bool32 act_water_ground_pound(struct MarioState *m) {
    MarioStep stepResult;
    f32 yOffset;
    s32 stateFlags = (m->heldObj != NULL);
    if (m->flags & MARIO_METAL_CAP) return set_mario_action(m, ACT_METAL_WATER_FALLING, 1);
    if (m->input & INPUT_B_PRESSED) return set_mario_action(m, ACT_WATER_ACTION_END   , 0);
    if (m->flags & MARIO_METAL_CAP) {
        stateFlags |= PLUNGE_FLAG_METAL_CAP;
    } else if ((m->prevAction & ACT_FLAG_DIVING) || (m->input & INPUT_A_DOWN)) {
        stateFlags |= PLUNGE_FLAG_DIVING;
    }
    if (m->actionArg == 1) m->actionState = ACT_WATER_GROUND_POUND_STATE_FALL;
    if (m->actionState == ACT_WATER_GROUND_POUND_STATE_SPIN) {
        play_sound(SOUND_GENERAL_WING_FLAP, m->marioObj->header.gfx.cameraToObject);
        if (m->actionTimer < 10) {
            yOffset = (20 - (2 * m->actionTimer));
            if (((m->pos[1] + yOffset + MARIO_HITBOX_HEIGHT) < m->ceilHeight) && ((m->pos[1] + yOffset + MARIO_HITBOX_HEIGHT) < m->waterLevel)) {
                m->pos[1] += yOffset;
                vec3_copy(m->marioObj->header.gfx.pos, m->pos);
            }
        }
        m->vel[1] = -32.0f;
        mario_set_forward_vel(m, -0.1f);
        set_mario_animation(m, MARIO_ANIM_START_GROUND_POUND);
        if (m->actionTimer == 0) play_sound(SOUND_ACTION_SWIM_FAST, m->marioObj->header.gfx.cameraToObject);
        m->actionTimer++;
        if (m->actionTimer >= (m->marioObj->header.gfx.animInfo.curAnim->loopEnd + 4)) {
            if (m->input & INPUT_A_DOWN) {
                play_sound(((sSwimStrength == MIN_SWIM_STRENGTH) ? SOUND_ACTION_SWIM : SOUND_ACTION_SWIM_FAST), m->marioObj->header.gfx.cameraToObject);
                m->vel[1] = 25.0f;
                mario_set_forward_vel(m, 20.0f);
                return set_mario_action(m, ACT_BREASTSTROKE, 0);
            } else {
                play_sound(SOUND_ACTION_SWIM, m->marioObj->header.gfx.cameraToObject);
                m->faceAngle[0] = 0x0;
                m->actionState  = ACT_WATER_GROUND_POUND_STATE_FALL;
            }
        }
#if ENABLE_RUMBLE
        if (m->prevAction & ACT_FLAG_AIR) queue_rumble_data(5, 80);
#endif
    } else {
        if (m->input & INPUT_A_PRESSED) {
            m->vel[1] = 25.0f;
            mario_set_forward_vel(m, 20.0f);
            return set_mario_action(m, ACT_WATER_ACTION_END, 0);
        }
#if ENABLE_RUMBLE
        reset_rumble_timers_slip();
#endif
        set_mario_animation(m, MARIO_ANIM_GROUND_POUND);
        m->particleFlags |= PARTICLE_PLUNGE_BUBBLE;
        m->actionTimer++;
        yOffset = ((m->input & INPUT_Z_DOWN) ? 1.0f : 2.0f); // Reuse yOffset var for y speed
        approach_f32_symmetric_bool(&m->vel[1], 0.0f, yOffset);
        stepResult = perform_water_step(m);
        if ((m->vel[1] >= 0.0f) || (m->actionTimer > 120)) {
            switch (stateFlags) {
                case 0: set_mario_action(m, ACT_WATER_ACTION_END        , 0); break;
                case 1: set_mario_action(m, ACT_HOLD_WATER_ACTION_END   , 0); break;
                case 2: set_mario_action(m, ACT_FLUTTER_KICK            , 0); break;
                case 3: set_mario_action(m, ACT_HOLD_FLUTTER_KICK       , 0); break;
                case 4: set_mario_action(m, ACT_METAL_WATER_FALLING     , 0); break;
                case 5: set_mario_action(m, ACT_HOLD_METAL_WATER_FALLING, 0); break;
            }
        }
        sBobIncrement = 0;
        if (stepResult == WATER_STEP_HIT_FLOOR) {
            play_mario_heavy_landing_sound(m, SOUND_ACTION_TERRAIN_HEAVY_LANDING);
            m->particleFlags |= ACTIVE_PARTICLE_DUST;
            set_mario_action(m, ACT_WATER_GROUND_POUND_LAND, 0);
            set_camera_shake_from_hit(SHAKE_GROUND_POUND);
        } else if (stepResult == WATER_STEP_HIT_WALL) {
            if (m->wall == NULL) {
                mario_set_forward_vel(m, -16.0f);
                if (m->vel[1] > 0.0f) m->vel[1] = 0.0f;
                m->particleFlags |= PARTICLE_VERTICAL_STAR;
                set_mario_action(m, ACT_WATER_ACTION_END, 0);
            }
        }
    }
    return FALSE;
}

static Bool32 act_water_ground_pound_land(struct MarioState *m) { //! actionState name?
    m->actionState = 1;
    if (m->input & INPUT_STOMPED  ) return drop_and_set_mario_action(m, ACT_SHOCKWAVE_BOUNCE, 0);
    if (m->input & INPUT_OFF_FLOOR) return set_mario_action(         m, ACT_WATER_ACTION_END, 0);
    if (m->input & INPUT_A_PRESSED) return set_mario_action(         m, ACT_BREASTSTROKE    , 0);
    // return set_mario_action(m, ACT_WATER_ACTION_END, 0);
    set_mario_animation(m, MARIO_ANIM_GROUND_POUND_LANDING);
    if (is_anim_at_end(m)) return set_mario_action(m, ACT_WATER_ACTION_END, 0);
    return FALSE;
}
#endif

static Bool32 act_breaststroke(struct MarioState *m) {
    if (m->actionArg == 0) sSwimStrength = MIN_SWIM_STRENGTH;
    if (m->flags & MARIO_METAL_CAP) return set_mario_action(         m, ACT_METAL_WATER_FALLING, 1);
    if (m->input & INPUT_B_PRESSED) return set_mario_action(         m, ACT_WATER_PUNCH        , 0);
#ifdef WATER_GROUND_POUND
    if (m->input & INPUT_Z_PRESSED) return drop_and_set_mario_action(m, ACT_WATER_GROUND_POUND , 0);
#endif
    if (++m->actionTimer == 14    ) return set_mario_action(         m, ACT_FLUTTER_KICK       , 0);
    if (check_water_jump(m)) return TRUE;
    if (m->actionTimer <  6) m->forwardVel += 0.5f;
    if (m->actionTimer >= 9) m->forwardVel += 1.5f;
    if (m->actionTimer >= 2) {
        if ((m->actionTimer <  6) && (m->input & INPUT_A_PRESSED)) m->actionState = ACT_BREASTSTROKE_STATE_CONTINUE;
        if ((m->actionTimer == 9) && (m->actionState == ACT_BREASTSTROKE_STATE_CONTINUE)) {
            set_anim_to_frame(m, 0);
            m->actionState = ACT_BREASTSTROKE_STATE_START;
            m->actionTimer = 1;
            sSwimStrength  = MIN_SWIM_STRENGTH;
        }
    }
    if (m->actionTimer == 1) {
        play_sound(((sSwimStrength == MIN_SWIM_STRENGTH) ? SOUND_ACTION_SWIM : SOUND_ACTION_SWIM_FAST), m->marioObj->header.gfx.cameraToObject);
        reset_bob_variables(m);
    }
#if ENABLE_RUMBLE
    if (m->actionTimer < 6) queue_rumble_submerged();
#endif
    set_mario_animation(m, MARIO_ANIM_SWIM_PART1);
    common_swimming_step(m, sSwimStrength);
    return FALSE;
}

static Bool32 act_swimming_end(struct MarioState *m) {
    if (m->flags & MARIO_METAL_CAP) return set_mario_action(m, ACT_METAL_WATER_FALLING, 1);
    if (m->input & INPUT_B_PRESSED) return set_mario_action(m, ACT_WATER_PUNCH        , 0);
    if (m->actionTimer >= 15      ) return set_mario_action(m, ACT_WATER_ACTION_END   , 0);
    if (check_water_jump(m)) return TRUE;
    if ((m->input & INPUT_A_DOWN) && (m->actionTimer >= 7)) {
        if ((m->actionTimer == 7) && (sSwimStrength < 280)) sSwimStrength += 10;
        return set_mario_action(m, ACT_BREASTSTROKE, 1);
    }
    if (m->actionTimer >= 7) sSwimStrength = MIN_SWIM_STRENGTH;
    m->actionTimer++;
    m->forwardVel -= 0.25f;
    set_mario_animation(m, MARIO_ANIM_SWIM_PART2);
    common_swimming_step(m, sSwimStrength);
    return FALSE;
}

static Bool32 act_flutter_kick(struct MarioState *m) {
    if (m->flags & MARIO_METAL_CAP) return set_mario_action(m, ACT_METAL_WATER_FALLING, 1);
    if (m->input & INPUT_B_PRESSED) return set_mario_action(m, ACT_WATER_PUNCH        , 0);
    if (!(m->input & INPUT_A_DOWN)) {
        if ((m->actionTimer == 0) && (sSwimStrength < 280)) sSwimStrength += 10;
        return set_mario_action(m, ACT_SWIMMING_END, 0);
    }
#ifdef WATER_GROUND_POUND
    if (m->input & INPUT_Z_PRESSED) return drop_and_set_mario_action(m, ACT_WATER_GROUND_POUND, 0);
#endif
    approach_f32_bool(&m->forwardVel, 12.0f, 0.1f, 0.15f);
    m->actionTimer = 1;
    sSwimStrength = MIN_SWIM_STRENGTH;
    if (m->forwardVel < 14.0f) {
        play_swimming_noise(m);
        set_mario_animation(m, MARIO_ANIM_FLUTTERKICK);
    }
    common_swimming_step(m, sSwimStrength);
    return FALSE;
}

static Bool32 act_hold_breaststroke(struct MarioState *m) {
    if (m->flags & MARIO_METAL_CAP                                 ) return set_mario_action(         m, ACT_HOLD_METAL_WATER_FALLING, 0);
    if (m->marioObj->oInteractStatus & INT_STATUS_MARIO_DROP_OBJECT) return drop_and_set_mario_action(m, ACT_WATER_IDLE              , 0);
    if (++m->actionTimer == 17                                     ) return set_mario_action(         m, ACT_HOLD_FLUTTER_KICK       , 0);
    if (m->input & INPUT_B_PRESSED                                 ) return set_mario_action(         m, ACT_WATER_THROW             , 0);
#ifdef WATER_GROUND_POUND
    if (m->input & INPUT_Z_PRESSED                                 ) return drop_and_set_mario_action(m, ACT_WATER_GROUND_POUND      , 0);
#endif
    if (check_water_jump(m)) return TRUE;
    if (m->actionTimer <  6) m->forwardVel += 0.5f;
    if (m->actionTimer >= 9) m->forwardVel += 1.5f;
    if (m->actionTimer >= 2) {
        if ((m->actionTimer <  6) && (m->input & INPUT_A_PRESSED)) m->actionState = ACT_HOLD_BREASTSTROKE_STATE_CONTINUE;
        if ((m->actionTimer == 9) && (m->actionState == ACT_HOLD_BREASTSTROKE_STATE_CONTINUE)) {
            set_anim_to_frame(m, 0);
            m->actionState = ACT_HOLD_BREASTSTROKE_STATE_START;
            m->actionTimer = 1;
        }
    }
    if (m->actionTimer == 1) {
        play_sound(SOUND_ACTION_SWIM, m->marioObj->header.gfx.cameraToObject);
        reset_bob_variables(m);
    }
    set_mario_animation(m, MARIO_ANIM_SWIM_WITH_OBJ_PART1);
    common_swimming_step(m, 0x00A0);
    return FALSE;
}

static Bool32 act_hold_swimming_end(struct MarioState *m) {
    if (m->flags & MARIO_METAL_CAP                                 ) return set_mario_action(         m, ACT_HOLD_METAL_WATER_FALLING, 0);
    if (m->marioObj->oInteractStatus & INT_STATUS_MARIO_DROP_OBJECT) return drop_and_set_mario_action(m, ACT_WATER_IDLE              , 0);
    if (m->actionTimer >= 15                                       ) return set_mario_action(         m, ACT_HOLD_WATER_ACTION_END   , 0);
    if (m->input & INPUT_B_PRESSED                                 ) return set_mario_action(         m, ACT_WATER_THROW             , 0);
#ifdef WATER_GROUND_POUND
    if (m->input & INPUT_Z_PRESSED                                 ) return drop_and_set_mario_action(m, ACT_WATER_GROUND_POUND      , 0);
#endif
    if (check_water_jump(m)) return TRUE;
    if ((m->input & INPUT_A_DOWN) && (m->actionTimer >= 7)         ) return set_mario_action(         m, ACT_HOLD_BREASTSTROKE       , 0);
    m->actionTimer++;
    m->forwardVel -= 0.25f;
    set_mario_animation(m, MARIO_ANIM_SWIM_WITH_OBJ_PART2);
    common_swimming_step(m, 0x00A0);
    return FALSE;
}

static Bool32 act_hold_flutter_kick(struct MarioState *m) {
    if (m->flags & MARIO_METAL_CAP                                 ) return set_mario_action(         m, ACT_HOLD_METAL_WATER_FALLING, 0);
    if (m->marioObj->oInteractStatus & INT_STATUS_MARIO_DROP_OBJECT) return drop_and_set_mario_action(m, ACT_WATER_IDLE              , 0);
    if (m->input & INPUT_B_PRESSED                                 ) return set_mario_action(         m, ACT_WATER_THROW             , 0);
    if (!(m->input & INPUT_A_DOWN)                                 ) return set_mario_action(         m, ACT_HOLD_SWIMMING_END       , 0);
#ifdef WATER_GROUND_POUND
    if (m->input & INPUT_Z_PRESSED                                 ) return drop_and_set_mario_action(m, ACT_WATER_GROUND_POUND      , 0);
#endif
    approach_f32_bool(&m->forwardVel, 12.0f, 0.1f, 0.15f);
    if (m->forwardVel < 14.0f) {
        play_swimming_noise(m);
        set_mario_animation(m, MARIO_ANIM_FLUTTERKICK_WITH_OBJ);
    }
    common_swimming_step(m, 0x00A0);
    return FALSE;
}

static Bool32 act_water_shell_swimming(struct MarioState *m) {
    if (m->marioObj->oInteractStatus & INT_STATUS_MARIO_DROP_OBJECT) return drop_and_set_mario_action(m, ACT_WATER_IDLE        , 0);
    if (m->input & INPUT_B_PRESSED                                 ) return set_mario_action(         m, ACT_WATER_THROW       , 0);
#ifdef WATER_GROUND_POUND
    if (m->input & INPUT_Z_PRESSED                                 ) return drop_and_set_mario_action(m, ACT_WATER_GROUND_POUND, 0);
#endif
#ifndef INFINITE_WATER_SHELL
    if (m->actionTimer++ == 240) {
        m->heldObj->oInteractStatus = INT_STATUS_STOP_RIDING;
        m->heldObj = NULL;
        stop_shell_music();
        set_mario_action(m, ACT_FLUTTER_KICK, 0);
    }
#endif
    approach_f32_bool(&m->forwardVel, MAX(MAX_SWIMMING_SPEED, 30.0f), 2.0f, 1.0f);
    play_swimming_noise(m);
    set_mario_animation(m, MARIO_ANIM_FLUTTERKICK_WITH_OBJ);
    common_swimming_step(m, 0x012C);
    return FALSE;
}

static Bool32 check_water_grab(struct MarioState *m) {
    if (m->marioObj->collidedObjInteractTypes & INTERACT_GRABBABLE) {
        struct Object *object = mario_get_collided_object(m, INTERACT_GRABBABLE);
        if (object->oInteractionSubtype & INT_SUBTYPE_NOT_GRABBABLE) return FALSE;
        f32 dx = (object->oPosX - m->pos[0]);
        f32 dz = (object->oPosZ - m->pos[2]);
        Angle dAngleToObject = abs_angle_diff(atan2s(dz, dx), m->faceAngle[1]);
        if (dAngleToObject <= DEG(60)) {
            m->usedObj = object;
            mario_grab_used_object(m);
            m->marioBodyState->grabPos = GRAB_POS_LIGHT_OBJ;
            return TRUE;
        }
    }
    return FALSE;
}

static Bool32 act_water_throw(struct MarioState *m) {
    update_swimming_yaw(m);
    update_swimming_pitch(m);
    update_swimming_speed(m, MIN_SWIM_SPEED);
    perform_water_step(m);
    update_water_pitch(m);
    set_mario_animation(m, MARIO_ANIM_WATER_THROW_OBJ);
    play_sound_if_no_flag(m, SOUND_ACTION_SWIM, MARIO_ACTION_SOUND_PLAYED);
    approach_angle_bool(&m->marioBodyState->headAngle[0], 0x0, 0x200);
    if (m->actionTimer++ == 5) {
        mario_throw_held_object(m);
#if ENABLE_RUMBLE
        queue_rumble_data(3, 50);
#endif
    }
    if (is_anim_at_end(m)) set_mario_action(m, ACT_WATER_IDLE, 0);
    return FALSE;
}

static Bool32 act_water_punch(struct MarioState *m) {
    if (m->flags & MARIO_METAL_CAP) return set_mario_action(m, ACT_METAL_WATER_FALLING, 1);
#ifdef ACTION_CANCELS
    if (m->actionTimer++ >= 2) {
        if (m->input & INPUT_B_PRESSED) return set_mario_action(         m, ACT_WATER_PUNCH       , 0);
        if (m->input & INPUT_A_PRESSED) return set_mario_action(         m, ACT_BREASTSTROKE      , 0);
#ifdef WATER_GROUND_POUND
        if (m->input & INPUT_Z_PRESSED) return drop_and_set_mario_action(m, ACT_WATER_GROUND_POUND, 0);
#endif
    }
#endif
    if (m->forwardVel < 7.0f) m->forwardVel += 1.0f;
    update_swimming_yaw(m);
    update_swimming_pitch(m);
    update_swimming_speed(m, MIN_SWIM_SPEED);
    perform_water_step(m);
    update_water_pitch(m);
    approach_angle_bool(&m->marioBodyState->headAngle[0], 0x0, 0x200);
    play_sound_if_no_flag(m, SOUND_ACTION_SWIM, MARIO_ACTION_SOUND_PLAYED);
    switch (m->actionState) {
        case ACT_WATER_PUNCH_STATE_START:
            set_mario_animation(m, MARIO_ANIM_WATER_GRAB_OBJ_PART1);
            if (is_anim_at_end(m)) m->actionState = (check_water_grab(m) + 1);
            break;
        case ACT_WATER_PUNCH_STATE_MISSED:
            set_mario_animation(m, MARIO_ANIM_WATER_GRAB_OBJ_PART2);
            if (is_anim_at_end(m)) set_mario_action(m, ACT_WATER_ACTION_END, 0);
            break;
        case ACT_WATER_PUNCH_STATE_PICK_UP:
            set_mario_animation(m, MARIO_ANIM_WATER_PICK_UP_OBJ);
            if (is_anim_at_end(m)) {
                if (m->heldObj->behavior == segmented_to_virtual(bhvKoopaShellUnderwater)) {
                    play_shell_music();
                    set_mario_action(m, ACT_WATER_SHELL_SWIMMING,  0);
                } else {
                    set_mario_action(m, ACT_HOLD_WATER_ACTION_END, 1);
                }
            }
            break;
    }
    return FALSE;
}

static void common_water_knockback_step(struct MarioState *m, AnimID32 animation, MarioAction endAction, s32 arg3) {
#ifdef ENABLE_DEBUG_FREE_MOVE
    if (gPlayer1Controller->buttonDown & U_JPAD) {
        set_camera_mode(m->area->camera, CAMERA_MODE_8_DIRECTIONS, 1);
        set_mario_action(m, ACT_DEBUG_FREE_MOVE, 0);
        return;
    }
#endif
    stationary_slow_down(m);
    perform_water_step(m);
    set_mario_animation(m, animation);
    m->marioBodyState->headAngle[0] = 0x0;
    if (is_anim_at_end(m)) {
        if (arg3 > 0) m->invincTimer = 30;
        set_mario_action(m, ((m->health >= 0x100) ? endAction : ACT_WATER_DEATH), 0);
    }
}

static Bool32 act_backward_water_kb(struct MarioState *m) {
    common_water_knockback_step(m, MARIO_ANIM_BACKWARDS_WATER_KB, ACT_WATER_IDLE, m->actionArg);
    return FALSE;
}

static Bool32 act_forward_water_kb(struct MarioState *m) {
    common_water_knockback_step(m, MARIO_ANIM_WATER_FORWARD_KB, ACT_WATER_IDLE, m->actionArg);
    return FALSE;
}

static Bool32 act_water_shocked(struct MarioState *m) {
    play_sound_if_no_flag(m, SOUND_MARIO_WAAAOOOW, MARIO_ACTION_SOUND_PLAYED);
    play_sound(SOUND_MOVING_SHOCKED, m->marioObj->header.gfx.cameraToObject);
    set_camera_shake_from_hit(SHAKE_SHOCK);
    if (set_mario_animation(m, MARIO_ANIM_SHOCKED) == 0) {
        m->actionTimer++;
        m->flags |= MARIO_METAL_SHOCK;
    }
    if (m->actionTimer >= 6) {
        m->invincTimer = 30;
        set_mario_action(m, ((m->health < 0x100) ? ACT_WATER_DEATH : ACT_WATER_IDLE), 0);
    }
    stationary_slow_down(m);
    perform_water_step(m);
    m->marioBodyState->headAngle[0] = 0x0;
    return FALSE;
}

static Bool32 act_drowning(struct MarioState *m) {
    switch (m->actionState) {
        case ACT_DROWNING_STATE_EYES_HALF_CLOSED:
            set_mario_animation(m, MARIO_ANIM_DROWNING_PART1);
            m->marioBodyState->eyeState = MARIO_EYES_HALF_CLOSED;
            if (is_anim_at_end(m)) m->actionState = ACT_DROWNING_STATE_EYES_DEAD;
            break;
        case ACT_DROWNING_STATE_EYES_DEAD:
            set_mario_animation(m, MARIO_ANIM_DROWNING_PART2);
            m->marioBodyState->eyeState = MARIO_EYES_DEAD;
            if (m->marioObj->header.gfx.animInfo.animFrame == 30) level_trigger_warp(m, WARP_OP_DEATH);
            break;
    }
    play_sound_if_no_flag(m, SOUND_MARIO_DROWNING, MARIO_ACTION_SOUND_PLAYED);
    stationary_slow_down(m);
    perform_water_step(m);
    return FALSE;
}

static Bool32 act_water_death(struct MarioState *m) {
    stationary_slow_down(m);
    perform_water_step(m);
    m->marioBodyState->eyeState = MARIO_EYES_DEAD;
    set_mario_animation(m, MARIO_ANIM_WATER_DYING);
    if (set_mario_animation(m, MARIO_ANIM_WATER_DYING) == 35) level_trigger_warp(m, WARP_OP_DEATH);
    return FALSE;
}

static Bool32 act_water_plunge(struct MarioState *m) {
    s32 stateFlags = (m->heldObj != NULL);
    f32 endVSpeed  = (swimming_near_surface(m) ? 0.0f : -5.0f);
    if (m->flags & MARIO_METAL_CAP) return set_mario_action(         m, ACT_METAL_WATER_FALLING, 1);
#ifdef ACTION_CANCELS
    if (m->input & INPUT_B_PRESSED) return set_mario_action(         m, ACT_WATER_PUNCH        , 0);
#ifdef WATER_GROUND_POUND
    if (m->input & INPUT_Z_PRESSED) return drop_and_set_mario_action(m, ACT_WATER_GROUND_POUND , 0);
#endif
#endif
    if (m->flags & MARIO_METAL_CAP) {
        stateFlags |= PLUNGE_FLAG_METAL_CAP;
    } else if ((m->prevAction & ACT_FLAG_DIVING) || (m->input & INPUT_A_DOWN)) {
        stateFlags |= PLUNGE_FLAG_DIVING;
    }
    m->actionTimer++;
    stationary_slow_down(m);
    MarioStep stepResult = perform_water_step(m);
    if (m->actionState == ACT_WATER_PLUNGE_STATE_FALL) {
        play_sound(SOUND_ACTION_WATER_PLUNGE, m->marioObj->header.gfx.cameraToObject);
        if ((m->peakHeight - m->pos[1]) > FALL_DAMAGE_HEIGHT_SMALL) play_sound(SOUND_MARIO_HAHA_WATER, m->marioObj->header.gfx.cameraToObject);
        m->particleFlags |= PARTICLE_WATER_SPLASH;
        m->actionState    = ACT_WATER_PLUNGE_STATE_SINK;
#if ENABLE_RUMBLE
        if (m->prevAction & ACT_FLAG_AIR) queue_rumble_data(5, 80);
#endif
    }
    if ((stepResult == WATER_STEP_HIT_FLOOR) || (m->vel[1] >= endVSpeed) || (m->actionTimer > 20)) {
        switch (stateFlags) {
            case 0: set_mario_action(m, ACT_WATER_ACTION_END        , 0); break;
            case 1: set_mario_action(m, ACT_HOLD_WATER_ACTION_END   , 0); break;
            case 2: set_mario_action(m, ACT_FLUTTER_KICK            , 0); break;
            case 3: set_mario_action(m, ACT_HOLD_FLUTTER_KICK       , 0); break;
            case 4: set_mario_action(m, ACT_METAL_WATER_FALLING     , 0); break;
            case 5: set_mario_action(m, ACT_HOLD_METAL_WATER_FALLING, 0); break;
        }
        sBobIncrement = 0;
    }
    switch (stateFlags) {
        case 0: set_mario_animation(m, MARIO_ANIM_WATER_ACTION_END         ); break;
        case 1: set_mario_animation(m, MARIO_ANIM_WATER_ACTION_END_WITH_OBJ); break;
        case 2: set_mario_animation(m, MARIO_ANIM_FLUTTERKICK              ); break;
        case 3: set_mario_animation(m, MARIO_ANIM_FLUTTERKICK_WITH_OBJ     ); break;
        case 4: set_mario_animation(m, MARIO_ANIM_GENERAL_FALL             ); break;
        case 5: set_mario_animation(m, MARIO_ANIM_FALL_WITH_LIGHT_OBJ      ); break;
    }
    m->particleFlags |= PARTICLE_PLUNGE_BUBBLE;
    return FALSE;
}

static Bool32 act_caught_in_whirlpool(struct MarioState *m) {
    f32 sinAngleChange, cosAngleChange;
    f32 newDistance;
    Angle angleChange;
    struct Object *marioObj  = m->marioObj;
    struct Object *whirlpool = m->usedObj;
    f32 dx = (m->pos[0] - whirlpool->oPosX);
    f32 dz = (m->pos[2] - whirlpool->oPosZ);
    f32 distance = sqrtf(sqr(dx) + sqr(dz));
    if ((marioObj->oMarioWhirlpoolPosY += m->vel[1]) < 0.0f) {
        marioObj->oMarioWhirlpoolPosY = 0.0f;
        if ((distance < 16.1f) && (m->actionTimer++ == 16)) level_trigger_warp(m, WARP_OP_DEATH);
    }
    if (distance <= 28.0f) {
        newDistance = 16.0f;
        angleChange = DEG(33.75);
    } else if (distance < 256.0f) {
        newDistance = (distance - (12.0f - (distance / 32.0f)));
        angleChange = (Angle)(0x1C00 - (distance * 20.0f));
    } else {
        newDistance = (distance - 4.0f);
        angleChange = DEG(11.25);
    }
    m->vel[1] = (-640.0f / (newDistance + 16.0f));
    sinAngleChange = sins(angleChange);
    cosAngleChange = coss(angleChange);
    if (distance < 1.0f) {
        dx = (newDistance * sins(m->faceAngle[1]));
        dz = (newDistance * coss(m->faceAngle[1]));
    } else {
        dx *= (newDistance / distance);
        dz *= (newDistance / distance);
    }
    m->pos[0]       = (whirlpool->oPosX + (dx * cosAngleChange) + (dz * sinAngleChange));
    m->pos[2]       = (whirlpool->oPosZ - (dx * sinAngleChange) + (dz * cosAngleChange));
    m->pos[1]       = (whirlpool->oPosY + marioObj->oMarioWhirlpoolPosY);
    m->faceAngle[1] = (atan2s(dz, dx) + DEG(180));
    set_mario_animation(m, MARIO_ANIM_GENERAL_FALL);
    vec3_copy(m->marioObj->header.gfx.pos, m->pos);
    vec3_set( m->marioObj->header.gfx.angle, 0x0, m->faceAngle[1], 0x0);
#if ENABLE_RUMBLE
    reset_rumble_timers_slip();
#endif
    return FALSE;
}

static void play_metal_water_jumping_sound(struct MarioState *m, u32 landing) {
    if (!(m->flags & MARIO_ACTION_SOUND_PLAYED)) m->particleFlags |= PARTICLE_MIST_CIRCLE;
    play_sound_if_no_flag(m, landing ? SOUND_ACTION_METAL_LAND_WATER : SOUND_ACTION_METAL_JUMP_WATER, MARIO_ACTION_SOUND_PLAYED);
}

static void play_metal_water_walking_sound(struct MarioState *m) {
    if (is_anim_past_frame(m, 10) || is_anim_past_frame(m, 49)) {
        play_sound(SOUND_ACTION_METAL_STEP_WATER, m->marioObj->header.gfx.cameraToObject);
        m->particleFlags |= PARTICLE_DUST;
    }
}

static void update_metal_water_walking_speed(struct MarioState *m) {
    f32 targetSpeed = (m->intendedMag / 1.5f);
    if (m->forwardVel <= 0.0f) {
        m->forwardVel += 1.1f;
    } else if (m->forwardVel <= targetSpeed) {
        m->forwardVel += (1.1f - (m->forwardVel / 43.0f));
#ifdef FIX_RELATIVE_SLOPE_ANGLE_MOVEMENT
    } else if (m->steepness >= 0.95f) {
#else
    } else if (m->floor->normal.y >= 0.95f) {
#endif
        m->forwardVel -= 1.0f;
    }
    if (m->forwardVel > 32.0f) m->forwardVel = 32.0f;
    approach_angle_bool(&m->faceAngle[1], m->intendedYaw, DEG(11.25));
    m->slideVelX    = (m->forwardVel * sins(m->faceAngle[1]));
    m->slideVelZ    = (m->forwardVel * coss(m->faceAngle[1]));
    m->vel[0]       =  m->slideVelX;
    m->vel[1]       = 0.0f;
    m->vel[2]       =  m->slideVelZ;
}

static Bool32 update_metal_water_jump_speed(struct MarioState *m) {
    f32 waterSurface = (m->waterLevel - 100);
    if ((m->vel[1] > 0.0f) && (m->pos[1] > waterSurface)) return TRUE;
    if (m->input & INPUT_NONZERO_ANALOG) {
        Angle intendedDYaw = (m->intendedYaw - m->faceAngle[1]);
        m->forwardVel     += (0.8f  * coss(intendedDYaw));
        m->faceAngle[1]   += (0x200 * sins(intendedDYaw));
    } else {
        approach_f32_symmetric_bool(&m->forwardVel, 0.0f, 0.25f);
    }
    if (m->forwardVel > 16.0f) m->forwardVel -= 1.0f;
    if (m->forwardVel <  0.0f) m->forwardVel += 2.0f;
    m->vel[0] = m->slideVelX = (m->forwardVel * sins(m->faceAngle[1]));
    m->vel[2] = m->slideVelZ = (m->forwardVel * coss(m->faceAngle[1]));
    return FALSE;
}

static Bool32 act_metal_water_standing(struct MarioState *m) { //! actionState names
    if (!(m->flags & MARIO_METAL_CAP)  ) return set_mario_action(m, ACT_WATER_IDLE         , 0);
    if (m->input & INPUT_A_PRESSED     ) return set_mario_action(m, ACT_METAL_WATER_JUMP   , 0);
    if (m->input & INPUT_NONZERO_ANALOG) return set_mario_action(m, ACT_METAL_WATER_WALKING, 0);
    switch (m->actionState) {
        case 0: set_mario_animation(m, MARIO_ANIM_IDLE_HEAD_LEFT  ); break;
        case 1: set_mario_animation(m, MARIO_ANIM_IDLE_HEAD_RIGHT ); break;
        case 2: set_mario_animation(m, MARIO_ANIM_IDLE_HEAD_CENTER); break;
    }
    if (is_anim_at_end(m) && (++m->actionState == 3)) m->actionState = 0;
    stop_and_set_height_to_floor(m);
    if (m->pos[1] >= (m->waterLevel - 150)) m->particleFlags |= PARTICLE_IDLE_WATER_WAVE;
    return FALSE;
}

static Bool32 act_hold_metal_water_standing(struct MarioState *m) {
    if (m->marioObj->oInteractStatus & INT_STATUS_MARIO_DROP_OBJECT) return drop_and_set_mario_action(m, ACT_METAL_WATER_STANDING    , 0);
    if (!(m->flags & MARIO_METAL_CAP)                              ) return set_mario_action(         m, ACT_HOLD_WATER_IDLE         , 0);
    if (m->input & INPUT_A_PRESSED                                 ) return set_mario_action(         m, ACT_HOLD_METAL_WATER_JUMP   , 0);
    if (m->input & INPUT_NONZERO_ANALOG                            ) return set_mario_action(         m, ACT_HOLD_METAL_WATER_WALKING, 0);
    stop_and_set_height_to_floor(m);
    set_mario_animation(m, MARIO_ANIM_IDLE_WITH_LIGHT_OBJ);
    return FALSE;
}

static Bool32 act_metal_water_walking(struct MarioState *m) {
    AnimAccel animSpeed;
    if (!(m->flags & MARIO_METAL_CAP)) return set_mario_action(m, ACT_WATER_IDLE          , 0);
    if (m->input & INPUT_FIRST_PERSON) return set_mario_action(m, ACT_METAL_WATER_STANDING, 0);
    if (m->input & INPUT_A_PRESSED   ) return set_mario_action(m, ACT_METAL_WATER_JUMP    , 0);
    if (m->input & INPUT_IDLE        ) return set_mario_action(m, ACT_METAL_WATER_STANDING, 0);
    if ((animSpeed = (AnimAccel)((m->forwardVel / 4.0f) * 0x10000)) < 0x1000) animSpeed = 0x1000;
    set_mario_anim_with_accel(m, MARIO_ANIM_WALKING, animSpeed);
    play_metal_water_walking_sound(m);
    update_metal_water_walking_speed(m);
    switch (perform_ground_step(m)) {
        case GROUND_STEP_LEFT_GROUND: set_mario_action(m, ACT_METAL_WATER_FALLING, 1); break;
        case GROUND_STEP_HIT_WALL:    m->forwardVel = 0.0f;                            break;
    }
    return FALSE;
}

static Bool32 act_hold_metal_water_walking(struct MarioState *m) {
    AnimAccel animSpeed;
    if (m->marioObj->oInteractStatus & INT_STATUS_MARIO_DROP_OBJECT) return drop_and_set_mario_action(m, ACT_METAL_WATER_WALKING      , 0);
    if (!(m->flags & MARIO_METAL_CAP)                              ) return set_mario_action(         m, ACT_HOLD_WATER_IDLE          , 0);
    if (m->input & INPUT_A_PRESSED                                 ) return set_mario_action(         m, ACT_HOLD_METAL_WATER_JUMP    , 0);
    if (m->input & INPUT_IDLE                                      ) return set_mario_action(         m, ACT_HOLD_METAL_WATER_STANDING, 0);
    m->intendedMag *= 0.4f;
    if ((animSpeed = (AnimAccel)((m->forwardVel / 2.0f) * 0x10000)) < 0x1000) animSpeed = 0x1000;
    set_mario_anim_with_accel(m, MARIO_ANIM_RUN_WITH_LIGHT_OBJ, animSpeed);
    play_metal_water_walking_sound(m);
    update_metal_water_walking_speed(m);
    switch (perform_ground_step(m)) {
        case GROUND_STEP_LEFT_GROUND: set_mario_action(m, ACT_HOLD_METAL_WATER_FALLING, 1); break;
        case GROUND_STEP_HIT_WALL:    m->forwardVel = 0.0f;                                 break;
    }
    return FALSE;
}

static Bool32 act_metal_water_jump(struct MarioState *m) {
    if (!(m->flags & MARIO_METAL_CAP)   ) return set_mario_action(m, ACT_WATER_IDLE, 0);
    if (update_metal_water_jump_speed(m)) return set_mario_action(m, ACT_WATER_JUMP, 1);
    play_metal_water_jumping_sound(m, FALSE);
    set_mario_animation(m, MARIO_ANIM_SINGLE_JUMP);
    switch (perform_air_step(m, 0)) {
        case AIR_STEP_LANDED:   set_mario_action(m, ACT_METAL_WATER_JUMP_LAND, 0); break;
        case AIR_STEP_HIT_WALL: m->forwardVel = 0.0f;                              break;
    }
    return FALSE;
}

static Bool32 act_hold_metal_water_jump(struct MarioState *m) {
    if (m->marioObj->oInteractStatus & INT_STATUS_MARIO_DROP_OBJECT) return drop_and_set_mario_action(m, ACT_METAL_WATER_FALLING, 0);
    if (!(m->flags & MARIO_METAL_CAP)                              ) return set_mario_action(         m, ACT_HOLD_WATER_IDLE    , 0);
    if (update_metal_water_jump_speed(m)                           ) return set_mario_action(         m, ACT_HOLD_WATER_JUMP    , 1);
    play_metal_water_jumping_sound(m, FALSE);
    set_mario_animation(m, MARIO_ANIM_JUMP_WITH_LIGHT_OBJ);
    switch (perform_air_step(m, 0)) {
        case AIR_STEP_LANDED:   set_mario_action(m, ACT_HOLD_METAL_WATER_JUMP_LAND, 0); break;
        case AIR_STEP_HIT_WALL: m->forwardVel = 0.0f;                                   break;
    }
    return FALSE;
}

static Bool32 act_metal_water_falling(struct MarioState *m) {
    if (!(m->flags & MARIO_METAL_CAP)) return set_mario_action(m, ACT_WATER_IDLE, 0);
    if (m->input & INPUT_NONZERO_ANALOG) m->faceAngle[1] += (DEG(5.625) * sins(m->intendedYaw - m->faceAngle[1]));
    set_mario_animation(m, ((m->actionArg == 0) ? MARIO_ANIM_GENERAL_FALL : MARIO_ANIM_FALL_FROM_WATER));
    stationary_slow_down(m);
    if (perform_water_step(m) & WATER_STEP_HIT_FLOOR) set_mario_action(m, ACT_METAL_WATER_FALL_LAND, 0); // hit floor or cancelled
    return FALSE;
}

static Bool32 act_hold_metal_water_falling(struct MarioState *m) {
    if (m->marioObj->oInteractStatus & INT_STATUS_MARIO_DROP_OBJECT) return drop_and_set_mario_action(m, ACT_METAL_WATER_FALLING, 0);
    if (!(m->flags & MARIO_METAL_CAP)                              ) return set_mario_action(         m, ACT_HOLD_WATER_IDLE    , 0);
    if (m->input & INPUT_NONZERO_ANALOG) m->faceAngle[1] += (DEG(5.625) * sins(m->intendedYaw - m->faceAngle[1]));
    set_mario_animation(m, MARIO_ANIM_FALL_WITH_LIGHT_OBJ);
    stationary_slow_down(m);
    if (perform_water_step(m) & WATER_STEP_HIT_FLOOR) set_mario_action(m, ACT_HOLD_METAL_WATER_FALL_LAND, 0); // hit floor or cancelled
    return FALSE;
}

static Bool32 act_metal_water_jump_land(struct MarioState *m) {
    play_metal_water_jumping_sound(m, TRUE);
    if (!(m->flags & MARIO_METAL_CAP)  ) return set_mario_action(m, ACT_WATER_IDLE         , 0);
    if (m->input & INPUT_NONZERO_ANALOG) return set_mario_action(m, ACT_METAL_WATER_WALKING, 0);
    stop_and_set_height_to_floor(m);
    set_mario_animation(m, MARIO_ANIM_LAND_FROM_SINGLE_JUMP);
    if (is_anim_at_end(m)) return set_mario_action(m, ACT_METAL_WATER_STANDING, 0);
    return FALSE;
}

static Bool32 act_hold_metal_water_jump_land(struct MarioState *m) {
    play_metal_water_jumping_sound(m, TRUE);
    if (m->marioObj->oInteractStatus & INT_STATUS_MARIO_DROP_OBJECT) return drop_and_set_mario_action(m, ACT_METAL_WATER_STANDING    , 0);
    if (!(m->flags & MARIO_METAL_CAP)                              ) return set_mario_action(         m, ACT_HOLD_WATER_IDLE         , 0);
    if (m->input & INPUT_NONZERO_ANALOG                            ) return set_mario_action(         m, ACT_HOLD_METAL_WATER_WALKING, 0);
    stop_and_set_height_to_floor(m);
    set_mario_animation(m, MARIO_ANIM_JUMP_LAND_WITH_LIGHT_OBJ);
    if (is_anim_at_end(m)) return set_mario_action(m, ACT_HOLD_METAL_WATER_STANDING, 0);
    return FALSE;
}

static Bool32 act_metal_water_fall_land(struct MarioState *m) {
    play_metal_water_jumping_sound(m, TRUE);
    if (!(m->flags & MARIO_METAL_CAP)  ) return set_mario_action(m, ACT_WATER_IDLE         , 0);
    if (m->input & INPUT_NONZERO_ANALOG) return set_mario_action(m, ACT_METAL_WATER_WALKING, 0);
    stop_and_set_height_to_floor(m);
    set_mario_animation(m, MARIO_ANIM_GENERAL_LAND);
    if (is_anim_at_end(m)) return set_mario_action(m, ACT_METAL_WATER_STANDING, 0);
    return FALSE;
}

static Bool32 act_hold_metal_water_fall_land(struct MarioState *m) {
    play_metal_water_jumping_sound(m, TRUE);
    if (m->marioObj->oInteractStatus & INT_STATUS_MARIO_DROP_OBJECT) return drop_and_set_mario_action(m, ACT_METAL_WATER_STANDING    , 0);
    if (!(m->flags & MARIO_METAL_CAP)                              ) return set_mario_action(         m, ACT_HOLD_WATER_IDLE         , 0);
    if (m->input & INPUT_NONZERO_ANALOG                            ) return set_mario_action(         m, ACT_HOLD_METAL_WATER_WALKING, 0);
    stop_and_set_height_to_floor(m);
    set_mario_animation(m, MARIO_ANIM_FALL_LAND_WITH_LIGHT_OBJ);
    if (is_anim_at_end(m)) return set_mario_action(m, ACT_HOLD_METAL_WATER_STANDING, 0);
    return FALSE;
}

static Bool32 check_common_submerged_cancels(struct MarioState *m) {
    if (m->pos[1] > (m->waterLevel - 80)) {
        if ((m->waterLevel - 80) > m->floorHeight) {
            if ((m->pos[1] - (m->waterLevel - 80)) < 50.0f) {
                m->pos[1]  = (m->waterLevel - 80); // lock mario to top if the falloff isn't big enough
            } else {
                return transition_submerged_to_airborne(m);
            }
        } else {
            //! If you press B to throw the shell, there is a ~5 frame window
            // where your held object is the shell, but you are not in the
            // water shell swimming action. This allows you to hold the water
            // shell on land (used for cloning in DDD).
            if ((m->action == ACT_WATER_SHELL_SWIMMING) && (m->heldObj != NULL)) {
                m->heldObj->oInteractStatus = INT_STATUS_STOP_RIDING;
                m->heldObj                  = NULL;
                stop_shell_music();
            }
            return transition_submerged_to_walking(m);
        }
    }
    if ((m->health < 0x100) && !(m->action & (ACT_FLAG_INTANGIBLE | ACT_FLAG_INVULNERABLE))) set_mario_action(m, ACT_DROWNING, 0);
    return FALSE;
}

Bool32 mario_execute_submerged_action(struct MarioState *m) {
    Bool32 cancel;
    if (check_common_submerged_cancels(m)) return TRUE;
    m->quicksandDepth               = 0.0f;
    m->marioBodyState->headAngle[1] = 0x0;
    m->marioBodyState->headAngle[2] = 0x0;
    /* clang-format off */
    switch (m->action) {
        case ACT_WATER_IDLE:                 cancel = act_water_idle(m);                 break;
        case ACT_HOLD_WATER_IDLE:            cancel = act_hold_water_idle(m);            break;
        case ACT_WATER_ACTION_END:           cancel = act_water_action_end(m);           break;
        case ACT_HOLD_WATER_ACTION_END:      cancel = act_hold_water_action_end(m);      break;
        case ACT_DROWNING:                   cancel = act_drowning(m);                   break;
        case ACT_BACKWARD_WATER_KB:          cancel = act_backward_water_kb(m);          break;
        case ACT_FORWARD_WATER_KB:           cancel = act_forward_water_kb(m);           break;
        case ACT_WATER_DEATH:                cancel = act_water_death(m);                break;
        case ACT_WATER_SHOCKED:              cancel = act_water_shocked(m);              break;
#ifdef WATER_GROUND_POUND
        case ACT_WATER_GROUND_POUND:         cancel = act_water_ground_pound(m);         break;
        case ACT_WATER_GROUND_POUND_LAND:    cancel = act_water_ground_pound_land(m);    break;
#endif
        case ACT_BREASTSTROKE:               cancel = act_breaststroke(m);               break;
        case ACT_SWIMMING_END:               cancel = act_swimming_end(m);               break;
        case ACT_FLUTTER_KICK:               cancel = act_flutter_kick(m);               break;
        case ACT_HOLD_BREASTSTROKE:          cancel = act_hold_breaststroke(m);          break;
        case ACT_HOLD_SWIMMING_END:          cancel = act_hold_swimming_end(m);          break;
        case ACT_HOLD_FLUTTER_KICK:          cancel = act_hold_flutter_kick(m);          break;
        case ACT_WATER_SHELL_SWIMMING:       cancel = act_water_shell_swimming(m);       break;
        case ACT_WATER_THROW:                cancel = act_water_throw(m);                break;
        case ACT_WATER_PUNCH:                cancel = act_water_punch(m);                break;
        case ACT_WATER_PLUNGE:               cancel = act_water_plunge(m);               break;
        case ACT_CAUGHT_IN_WHIRLPOOL:        cancel = act_caught_in_whirlpool(m);        break;
        case ACT_METAL_WATER_STANDING:       cancel = act_metal_water_standing(m);       break;
        case ACT_METAL_WATER_WALKING:        cancel = act_metal_water_walking(m);        break;
        case ACT_METAL_WATER_FALLING:        cancel = act_metal_water_falling(m);        break;
        case ACT_METAL_WATER_FALL_LAND:      cancel = act_metal_water_fall_land(m);      break;
        case ACT_METAL_WATER_JUMP:           cancel = act_metal_water_jump(m);           break;
        case ACT_METAL_WATER_JUMP_LAND:      cancel = act_metal_water_jump_land(m);      break;
        case ACT_HOLD_METAL_WATER_STANDING:  cancel = act_hold_metal_water_standing(m);  break;
        case ACT_HOLD_METAL_WATER_WALKING:   cancel = act_hold_metal_water_walking(m);   break;
        case ACT_HOLD_METAL_WATER_FALLING:   cancel = act_hold_metal_water_falling(m);   break;
        case ACT_HOLD_METAL_WATER_FALL_LAND: cancel = act_hold_metal_water_fall_land(m); break;
        case ACT_HOLD_METAL_WATER_JUMP:      cancel = act_hold_metal_water_jump(m);      break;
        case ACT_HOLD_METAL_WATER_JUMP_LAND: cancel = act_hold_metal_water_jump_land(m); break;
        default:                             cancel = act_water_idle(m);                 break;
    }
    /* clang-format on */
    return cancel;
}
