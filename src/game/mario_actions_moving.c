#include <PR/ultratypes.h>

#include "sm64.h"
#include "mario.h"
#include "audio/external.h"
#include "engine/math_util.h"
#include "engine/surface_collision.h"
#include "mario_step.h"
#include "area.h"
#include "interaction.h"
#include "mario_actions_moving.h"
#include "mario_actions_object.h"
#include "boot/memory.h"
#include "behavior_data.h"
#include "rumble_init.h"

#include "config.h"
#ifdef ENABLE_DEBUG_FREE_MOVE
#include "boot/game_init.h"
#endif

struct LandingAction {
    s16 numFrames;
    s16 doubleJumpTimer;
    MarioAction verySteepAction;
    MarioAction endAction;
    MarioAction aPressedAction;
    MarioAction offFloorAction;
    MarioAction slideAction;
};

/*                                               numFrames, doubleJumpTimer,   verySteepAction,                   endAction,    aPressedAction,    offFloorAction,            slideAction, */
struct LandingAction sJumpLandAction         = {         4,               5,      ACT_FREEFALL,          ACT_JUMP_LAND_STOP,   ACT_DOUBLE_JUMP,      ACT_FREEFALL,      ACT_BEGIN_SLIDING, };
struct LandingAction sFreefallLandAction     = {         4,               5,      ACT_FREEFALL,      ACT_FREEFALL_LAND_STOP,   ACT_DOUBLE_JUMP,      ACT_FREEFALL,      ACT_BEGIN_SLIDING, };
struct LandingAction sSideFlipLandAction     = {         4,               5,      ACT_FREEFALL,     ACT_SIDE_FLIP_LAND_STOP,   ACT_DOUBLE_JUMP,      ACT_FREEFALL,      ACT_BEGIN_SLIDING, };
struct LandingAction sHoldJumpLandAction     = {         4,               5, ACT_HOLD_FREEFALL,     ACT_HOLD_JUMP_LAND_STOP,     ACT_HOLD_JUMP, ACT_HOLD_FREEFALL, ACT_HOLD_BEGIN_SLIDING, };
struct LandingAction sHoldFreefallLandAction = {         4,               5, ACT_HOLD_FREEFALL, ACT_HOLD_FREEFALL_LAND_STOP,     ACT_HOLD_JUMP, ACT_HOLD_FREEFALL, ACT_HOLD_BEGIN_SLIDING, };
struct LandingAction sLongJumpLandAction     = {         6,               5,      ACT_FREEFALL,     ACT_LONG_JUMP_LAND_STOP,     ACT_LONG_JUMP,      ACT_FREEFALL,      ACT_BEGIN_SLIDING, };
struct LandingAction sDoubleJumpLandAction   = {         4,               5,      ACT_FREEFALL,   ACT_DOUBLE_JUMP_LAND_STOP,          ACT_JUMP,      ACT_FREEFALL,      ACT_BEGIN_SLIDING, };
struct LandingAction sTripleJumpLandAction   = {         4,               0,      ACT_FREEFALL,   ACT_TRIPLE_JUMP_LAND_STOP, ACT_UNINITIALIZED,      ACT_FREEFALL,      ACT_BEGIN_SLIDING, };
struct LandingAction sBackflipLandAction     = {         4,               0,      ACT_FREEFALL,      ACT_BACKFLIP_LAND_STOP,      ACT_BACKFLIP,      ACT_FREEFALL,      ACT_BEGIN_SLIDING, };

Mat4 sFloorAlignMatrix[2];

Angle tilt_body_running(struct MarioState *m) {
    Angle pitch = 0x0;
#ifdef FIX_RELATIVE_SLOPE_ANGLE_MOVEMENT
    if ((m->pos[1] <= m->floorHeight) && (m->steepness < COS1)) pitch = m->movePitch;
#else
    if ((m->pos[1] <= m->floorHeight) && (m->floor->normal.y < COS1)) pitch = find_floor_slope(m, 0x0, 5.0f);
#endif
    return ((-pitch * m->forwardVel) / 40.0f);
}

void play_step_sound(struct MarioState *m, AnimFrame16 frame1, AnimFrame16 frame2) {
    if (is_anim_past_frame(m, frame1) || is_anim_past_frame(m, frame2)) {
        if (m->flags & MARIO_METAL_CAP) {
            play_sound_and_spawn_particles(m, ((m->marioObj->header.gfx.animInfo.animID == MARIO_ANIM_TIPTOE) ? SOUND_ACTION_METAL_STEP_TIPTOE : SOUND_ACTION_METAL_STEP), 0);
        } else if (m->quicksandDepth > 50.0f) {
            play_sound(SOUND_ACTION_QUICKSAND_STEP, m->marioObj->header.gfx.cameraToObject);
        } else if (m->marioObj->header.gfx.animInfo.animID == MARIO_ANIM_TIPTOE) {
            play_sound_and_spawn_particles(m, SOUND_ACTION_TERRAIN_STEP_TIPTOE, 0);
        } else {
            play_sound_and_spawn_particles(m, SOUND_ACTION_TERRAIN_STEP, 0);
        }
    }
}

#ifdef FAST_FLOOR_ALIGN
void align_with_floor(struct MarioState *m, Bool32 smooth) {
    struct Surface *floor = m->floor;
    if ((floor != NULL) && (m->pos[1] < (m->floorHeight + MAX(MARIO_STEP_HEIGHT, 80.0f)))) {
// #ifdef FIX_RELATIVE_SLOPE_ANGLE_MOVEMENT
//         if ((m->steepness > COS45) && (mario_get_floor_class(m) == SURFACE_CLASS_NOT_SLIPPERY) && (m->forwardVel < GROUND_SPEED_THRESHOLD_2)) {
// #else
//         if ((floor->normal.y > COS45) && (mario_get_floor_class(m) == SURFACE_CLASS_NOT_SLIPPERY) && (m->forwardVel < GROUND_SPEED_THRESHOLD_2)) {
// #endif
        m->pos[1] = m->floorHeight;
// #ifdef FAST_FLOOR_ALIGN
        if (!smooth || ABSF(m->forwardVel) > FAST_FLOOR_ALIGN) {
            Vec3f floorNormal = { floor->normal.x, floor->normal.y, floor->normal.z };
            mtxf_align_terrain_normal(sFloorAlignMatrix[m->playerID], floorNormal, m->pos, m->faceAngle[1]);
        } else {
            mtxf_align_terrain_triangle(sFloorAlignMatrix[m->playerID], m->pos, m->faceAngle[1], 40.0f);
        }
// #else
//         mtxf_align_terrain_triangle(sFloorAlignMatrix[m->playerID], m->pos, m->faceAngle[1], 40.0f);
// #endif
        m->marioObj->header.gfx.throwMatrix = &sFloorAlignMatrix[m->playerID];
    }
#else
void align_with_floor(struct MarioState *m) {
    m->pos[1] = m->floorHeight;
    mtxf_align_terrain_triangle(sFloorAlignMatrix[m->playerID], m->pos, m->faceAngle[1], 40.0f);
    m->marioObj->header.gfx.throwMatrix = &sFloorAlignMatrix[m->playerID];
#endif
}

Bool32 begin_walking_action(struct MarioState *m, f32 forwardVel, MarioAction action, u32 actionArg) {
    m->faceAngle[1] = m->intendedYaw;
    mario_set_forward_vel(m, forwardVel);
    return set_mario_action(m, action, actionArg);
}

void check_ledge_climb_down(struct MarioState *m) {
    struct WallCollisionData wallCols;
    struct Surface *floor;
    struct Surface *wall;
    if (m->forwardVel < GROUND_SPEED_THRESHOLD_2) {
        //! Why doesn't this work: if ((m->floor == NULL) || (m->floor->normal.y < COS25)) return;
        vec3_copy(wallCols.pos, m->pos);
        wallCols.radius  =  10.0f;
        wallCols.offsetY = -10.0f;
        if (find_wall_collisions(&wallCols) != 0) {
            f32 floorHeight = find_floor(wallCols.pos[0], (wallCols.pos[1] + m->midY), wallCols.pos[2], &floor);
            if ((floor != NULL) && (((wallCols.pos[1] - floorHeight) > MARIO_SHORT_HITBOX_HEIGHT))) {
                wall = wallCols.walls[wallCols.numWalls - 1];
                Angle wallAngle = SURFACE_YAW(wall);
                if (abs_angle_diff(wallAngle, m->faceAngle[1]) < DEG(90)) {
                    m->pos[0]       = (wallCols.pos[0] - (20.0f * wall->normal.x));
                    m->pos[2]       = (wallCols.pos[2] - (20.0f * wall->normal.z));
                    m->faceAngle[0] = 0x0;
                    m->faceAngle[1] = (wallAngle + DEG(180));
                    set_mario_wall(m, wall);
                    set_mario_action(m, ACT_LEDGE_CLIMB_DOWN, 0);
                    set_mario_animation(m, MARIO_ANIM_CLIMB_DOWN_LEDGE);
                }
            }
        }
    }
}

void slide_bonk(struct MarioState *m, MarioAction fastAction, MarioAction slowAction) {
    if (m->forwardVel > 16.0f) {
        mario_bonk_reflection(m, TRUE);
        drop_and_set_mario_action(m, fastAction, 0);
    } else {
        mario_set_forward_vel(m, 0.0f);
        set_mario_action(m, slowAction, 0);
    }
}

Bool32 set_triple_jump_action(struct MarioState *m, UNUSED MarioAction action, UNUSED u32 actionArg) {
    if (m->flags & MARIO_WING_CAP) {
        return set_mario_action(m, ACT_FLYING_TRIPLE_JUMP, 0);
    } else if (m->forwardVel > 20.0f) {
        return set_mario_action(m, ACT_TRIPLE_JUMP,        0);
    } else {
        return set_mario_action(m, ACT_JUMP,               0);
    }
    return FALSE;
}

void update_sliding_angle(struct MarioState *m, f32 accel, f32 lossFactor) {
    struct Surface *floor = m->floor;
    Angle slopeAngle      = m->floorYaw;
    f32 accelSteepness = ((m->floor) ? (accel * sqrtf(sqr(floor->normal.x) + sqr(floor->normal.z))) : 0.0f);
    m->slideVelX += (accelSteepness * sins(slopeAngle));
    m->slideVelZ += (accelSteepness * coss(slopeAngle));
    m->slideVelX *= lossFactor;
    m->slideVelZ *= lossFactor;
    m->slideYaw   = atan2s(m->slideVelZ, m->slideVelX);
    Angle facingDYaw  = (m->faceAngle[1] - m->slideYaw);
    s32 newFacingDYaw = facingDYaw; //! cast to s32 for some reason
    if (newFacingDYaw > 0x0 && newFacingDYaw <= DEG(90)) { // (0..0x4000]
        if ((newFacingDYaw -= 0x200) <      0x0 ) newFacingDYaw =      0x0;
    } else if (newFacingDYaw >= -DEG( 90) && newFacingDYaw <  0x0) { // [-0x4000..0)
        if ((newFacingDYaw += 0x200) >      0x0 ) newFacingDYaw =      0x0;
    } else if (newFacingDYaw >   DEG( 90) && newFacingDYaw <  DEG(180)) { // (0x4000..0x8000)
        if ((newFacingDYaw += 0x200) >  DEG(180)) newFacingDYaw =  DEG(180);
    } else if (newFacingDYaw >  -DEG(180) && newFacingDYaw < -DEG( 90)) { // (-0x8000..-0x4000)
        if ((newFacingDYaw -= 0x200) < -DEG(180)) newFacingDYaw = -DEG(180);
    }
    m->faceAngle[1] = (m->slideYaw + newFacingDYaw);
    vec3_set(m->vel, m->slideVelX, 0.0f, m->slideVelZ);
    mario_update_moving_sand(m);
    mario_update_windy_ground(m);
    //! Speed is capped a frame late (butt slide HSG)
    m->forwardVel = sqrtf(sqr(m->slideVelX) + sqr(m->slideVelZ));
    if (m->forwardVel > 100.0f) {
        m->slideVelX = ((m->slideVelX * 100.0f) / m->forwardVel);
        m->slideVelZ = ((m->slideVelZ * 100.0f) / m->forwardVel);
    }
    if ((newFacingDYaw < -DEG(90)) || (newFacingDYaw >  DEG(90))) m->forwardVel *= -1.0f;
}

Bool32 update_sliding(struct MarioState *m, f32 stopSpeed) {
    f32 accel, lossFactor;
    Angle intendedDYaw = (m->intendedYaw - m->slideYaw);
    f32 forward        = coss(intendedDYaw);
    //! 10k glitch
    if ((forward < 0.0f) && (m->forwardVel >= 0.0f)) forward *= (0.5f + (0.5f * m->forwardVel / 100.0f));
    switch (mario_get_floor_class(m)) {
        case SURFACE_CLASS_VERY_SLIPPERY: accel = 10.0f; lossFactor = (((m->intendedMag / 32.0f) * forward * 0.02f) + 0.98f); break;
        case SURFACE_CLASS_SLIPPERY:      accel =  8.0f; lossFactor = (((m->intendedMag / 32.0f) * forward * 0.02f) + 0.96f); break;
        default:                          accel =  7.0f; lossFactor = (((m->intendedMag / 32.0f) * forward * 0.02f) + 0.92f); break;
        case SURFACE_CLASS_NOT_SLIPPERY:  accel =  5.0f; lossFactor = (((m->intendedMag / 32.0f) * forward * 0.02f) + 0.92f); break;
    }
    f32 oldSpeed          = sqrtf(sqr(m->slideVelX) + sqr(m->slideVelZ));
    f32 sideward          = ((m->intendedMag / 32.0f) * sins(intendedDYaw) * 0.05f);
    f32 slideVelXModifier = (m->slideVelZ * sideward);
    f32 slideVelZModifier = (m->slideVelX * sideward);
    m->slideVelX         += slideVelXModifier;
    m->slideVelZ         -= slideVelZModifier;
    f32 newSpeed          = sqrtf(sqr(m->slideVelX) + sqr(m->slideVelZ));
    if ((oldSpeed > 0.0f) && (newSpeed > 0.0f)) {
        m->slideVelX = ((m->slideVelX * oldSpeed) / newSpeed);
        m->slideVelZ = ((m->slideVelZ * oldSpeed) / newSpeed);
    }
    update_sliding_angle(m, accel, lossFactor);
    if (!mario_floor_is_slope(m) && (sqr(m->forwardVel) < sqr(stopSpeed))) {
        mario_set_forward_vel(m, 0.0f);
        return TRUE;
    }
    return FALSE;
}

void apply_slope_accel(struct MarioState *m) {
    f32 slopeAccel;
#ifdef FIX_RELATIVE_SLOPE_ANGLE_MOVEMENT
    f32 steepness = (1.0f - m->steepness);
#else
    struct Surface *floor = m->floor;
    f32 steepness = sqrtf(sqr(floor->normal.x) + sqr(floor->normal.z));
#endif
    if (mario_floor_is_slope(m)) {
        s16 slopeClass = 0;
        if ((m->action != ACT_SOFT_BACKWARD_GROUND_KB) && (m->action != ACT_SOFT_FORWARD_GROUND_KB)) slopeClass = mario_get_floor_class(m);
        switch (slopeClass) {
            case SURFACE_CLASS_VERY_SLIPPERY: slopeAccel = 5.3f; break;
            case SURFACE_CLASS_SLIPPERY:      slopeAccel = 2.7f; break;
            default:                          slopeAccel = 1.7f; break;
            case SURFACE_CLASS_NOT_SLIPPERY:  slopeAccel = 0.0f; break;
        }
        if (abs_angle_diff(m->floorYaw, m->faceAngle[1]) < DEG(90)) {
            m->forwardVel += (slopeAccel * steepness);
        } else {
            m->forwardVel -= (slopeAccel * steepness);
        }
    }
    m->slideYaw  =                       m->faceAngle[1];
    m->slideVelX = (m->forwardVel * sins(m->faceAngle[1]));
    m->slideVelZ = (m->forwardVel * coss(m->faceAngle[1]));
    m->vel[0]    = m->slideVelX;
    m->vel[1]    = 0.0f;
    m->vel[2]    = m->slideVelZ;
    mario_update_moving_sand(m);
    mario_update_windy_ground(m);
}

Bool32 apply_landing_accel(struct MarioState *m, f32 frictionFactor) {
    apply_slope_accel(m);
    if (!mario_floor_is_slope(m)) {
        m->forwardVel *= frictionFactor;
        if (sqr(m->forwardVel) < 1.0f) {
            mario_set_forward_vel(m, 0.0f);
            return TRUE;
        }
    }
    return FALSE;
}

void update_shell_speed(struct MarioState *m) {
    if (m->floorHeight < m->waterLevel) {
        set_mario_floor(m, &gWaterSurfacePseudoFloor, m->waterLevel);
        m->floor->originOffset = -m->waterLevel;
    }
    f32 maxTargetSpeed = (((m->floor != NULL) && (m->floor->type == SURFACE_SLOW)) ? 48.0f : 64.0f);
    f32 targetSpeed    = (m->intendedMag * 2.0f);
    if (targetSpeed > maxTargetSpeed) targetSpeed = maxTargetSpeed;
    if (targetSpeed < 24.0f) targetSpeed = 24.0f;
    if (m->forwardVel <= 0.0f) {
        m->forwardVel += 1.1f;
    } else if (m->forwardVel <= targetSpeed) {
        m->forwardVel += (1.1f - (m->forwardVel / 58.0f));
#ifdef FIX_RELATIVE_SLOPE_ANGLE_MOVEMENT
    } else if (m->steepness >= 0.95f) {
#else
    } else if (m->floor->normal.y >= 0.95f) {
#endif
        m->forwardVel -= 1.0f;
    }
    if (m->forwardVel >  64.0f) m->forwardVel =  64.0f;
    if (m->forwardVel < -64.0f) m->forwardVel = -64.0f;
    approach_angle_bool(&m->faceAngle[1], m->intendedYaw, DEG(11.25));
    apply_slope_accel(m);
}

Bool32 apply_slope_decel(struct MarioState *m, f32 decelCoef) {
    f32 decel;
    Bool32 stopped = FALSE;
    switch (mario_get_floor_class(m)) {
        case SURFACE_CLASS_VERY_SLIPPERY: decel = (decelCoef * 0.2f); break;
        case SURFACE_CLASS_SLIPPERY:      decel = (decelCoef * 0.7f); break;
        default:                          decel = (decelCoef * 2.0f); break;
        case SURFACE_CLASS_NOT_SLIPPERY:  decel = (decelCoef * 3.0f); break;
    }
    approach_f32_ptr(&m->forwardVel, 0.0f, decel);
    if (m->forwardVel == 0.0f) stopped = TRUE;
    apply_slope_accel(m);
    return stopped;
}

Bool32 update_decelerating_speed(struct MarioState *m) {
    Bool32 stopped = FALSE;
    approach_f32_ptr(&m->forwardVel, 0.0f, 1.0f);
    if (m->forwardVel == 0.0f) stopped = TRUE;
    mario_set_forward_vel(m, m->forwardVel);
    mario_update_moving_sand(m);
    mario_update_windy_ground(m);
    return stopped;
}

void update_walking_speed(struct MarioState *m) {
    f32 maxTargetSpeed = (((m->floor != NULL) && (m->floor->type == SURFACE_SLOW)) ? 24.0f : 32.0f);
    f32 targetSpeed    = ((m->intendedMag < maxTargetSpeed) ? m->intendedMag : maxTargetSpeed);
    if (m->quicksandDepth > 10.0f) targetSpeed *= (6.25f / m->quicksandDepth);
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
    if (m->forwardVel > 48.0f) m->forwardVel = 48.0f;
#if GROUND_TURN_MODE == 0 // Vanilla behavior.
    approach_angle_bool(&m->faceAngle[1], m->intendedYaw, DEG(11.25));
#elif GROUND_TURN_MODE == 1 // Similar to vanilla, but prevents Mario from moving in the wrong direction when turning around, and allows finer control with the analog stick.
    s16 turnRange = DEG(11.25);
    s16 dYaw = abs_angle_diff(m->faceAngle[1], m->intendedYaw); // 0x0 is turning forwards, 0x8000 is turning backwards
    if (m->forwardVel < 0.0f) { // Don't modify Mario's speed and turn radius if Mario is moving backwards
        // Flip controls when moving backwards so Mario still moves towards intendedYaw
        m->intendedYaw += DEG(180);
    } else if (dYaw > DEG(90)) { // Only modify Mario's speed and turn radius if Mario is turning around
        // Reduce Mario's forward speed by the turn amount, so Mario won't move off sideward from the intended angle when turning around.
        m->forwardVel *= ((coss(dYaw) + 1.0f) / 2.0f); // 1.0f is turning forwards, 0.0f is turning backwards
        // Increase turn speed if forwardVel is lower and intendedMag is higher
        turnRange     *= (2.0f - (ABSF(m->forwardVel) / MAX(m->intendedMag, __FLT_EPSILON__))); // 1.0f front, 2.0f back
    }
    approach_angle_bool(&m->faceAngle[1], m->intendedYaw, turnRange);
#elif GROUND_TURN_MODE == 2 // similar to mode 1, but a bit further from vanilla, and allows instant turnaround if Mario is moving slower than a certain threshold.
    if ((m->forwardVel < 0.0f) && (m->heldObj == NULL) && !(m->action & ACT_FLAG_SHORT_HITBOX)) {
        // Flip Mario if he is moving backwards
        m->faceAngle[1] += DEG(180);
        m->forwardVel   *= -1.0f;
    }
    if (analog_stick_held_back(m, DEG(100)) && (m->heldObj == NULL) && !(m->action & ACT_FLAG_SHORT_HITBOX)) {
        // Turn around instantly
        set_mario_action(m, ACT_TURNING_AROUND, 0);
        if (m->forwardVel < GROUND_SPEED_THRESHOLD) m->faceAngle[1] = m->intendedYaw;
    } else {
        // Scale the turn radius by forwardVel
        Angle turnRange = (DEG(22.5) - (m->forwardVel * 0x20));
        if (turnRange < DEG(11.25)) {
            turnRange = DEG(11.25); // Clamp the minimum radius (vanilla radius, 0x800)
            set_mario_action(m, ACT_TURNING_AROUND, 0);
        } else if (turnRange > DEG(22.5)) {
            turnRange = DEG(22.5); // Clamp the maximum radius (0x1000)
        }
        approach_angle_bool(&m->faceAngle[1], m->intendedYaw, turnRange);
    }
#elif GROUND_TURN_MODE == 3 // Instant turn.
    m->faceAngle[1] = m->intendedYaw;
#endif
    apply_slope_accel(m);
}

Bool32 should_begin_sliding(struct MarioState *m) {
    return ((m->input & INPUT_ABOVE_SLIDE)
    && (((m->area->terrainType & TERRAIN_MASK) == TERRAIN_SLIDE)
     || (m->forwardVel <= -1.0f)
     || mario_facing_downhill(m, FALSE)));
}

Bool32 check_ground_dive_or_punch(struct MarioState *m) {
    if (m->input & INPUT_B_PRESSED) {
        //! Speed kick (shoutouts to SimpleFlips)
#ifdef SUPER_RESPONSIVE_GROUND_DIVE
        if (!(m->input & INPUT_A_DOWN)
         && (m->forwardVel  >= GROUND_SPEED_THRESHOLD)
         && (m->intendedMag >= GROUND_DIVE_THRESHOLD)
         && (m->controller->stickMag > 48.0f)
         && ((m->wall == NULL) || (m->wall->object == NULL))
        //  && !(m->input & INPUT_INTERACT_OBJ_GRABBABLE)) {
         && !(m->marioObj->collidedObjInteractTypes & INTERACT_GRABBABLE)) {
#else
        if ((m->forwardVel >= GROUND_DIVE_THRESHOLD) && (m->controller->stickMag > 48.0f)) {
#endif
            m->vel[1] = 20.0f;
            return set_mario_action(m, ACT_DIVE, 1);
        }
        return set_mario_action(m, ACT_MOVE_PUNCHING, 0);
    }
    return FALSE;
}

Bool32 begin_braking_action(struct MarioState *m) {
    mario_drop_held_object(m);
    if (m->actionState == ACT_WALKING_STATE_REACH_WALL) {
        m->faceAngle[1] = m->actionArg;
        return set_mario_action(m, ACT_STANDING_AGAINST_WALL, 0);
    }
    if ((m->forwardVel >= GROUND_SPEED_THRESHOLD) && m->floor && (m->floor->normal.y >= COS80)) return set_mario_action(m, ACT_BRAKING, 0);
    return set_mario_action(m, ACT_DECELERATING, 0);
}

void anim_and_audio_for_walk(struct MarioState *m) {
    AnimAccel animSpeed;
    struct Object *marioObj = m->marioObj;
    Bool32 inLoop = TRUE;
    Angle targetPitch       = 0x0;
    f32 intendedSpeed       = ((m->intendedMag > m->forwardVel) ? m->intendedMag : m->forwardVel);
    if (intendedSpeed < 4.0f) intendedSpeed = 4.0f;
    if (m->quicksandDepth > 50.0f) {
        animSpeed = (AnimAccel)((intendedSpeed / 4.0f) * 0x10000);
        set_mario_anim_with_accel(m, MARIO_ANIM_MOVE_IN_QUICKSAND, animSpeed);
        play_step_sound(m, 19, 93);
        m->actionTimer = 0;
    } else {
        while (inLoop) {
            switch (m->actionTimer) {
                case 0:
                    if (intendedSpeed > 8.0f) {
                        m->actionTimer = 2;
                    } else {
                        //! (Speed Crash) If Mario's speed is more than 2^17.
                        if ((animSpeed = (AnimAccel)((intendedSpeed / 4.0f) * 0x10000)) < 0x1000) animSpeed = 0x1000;
                        set_mario_anim_with_accel(m, MARIO_ANIM_START_TIPTOE, animSpeed);
                        play_step_sound(m, 7, 22);
                        if (is_anim_past_frame(m, 23)) m->actionTimer = 2;
                        inLoop = FALSE;
                    }
                    break;
                case 1:
                    if (intendedSpeed > 8.0f) {
                        m->actionTimer = 2;
                    } else {
                        //! (Speed Crash) If Mario's speed is more than 2^17.
                        if ((animSpeed = (AnimAccel)(intendedSpeed * 0x10000)) < 0x1000) animSpeed = 0x1000;
                        set_mario_anim_with_accel(m, MARIO_ANIM_TIPTOE, animSpeed);
                        play_step_sound(m, 14, 72);
                        inLoop = FALSE;
                    }
                    break;
                case 2:
                    if (intendedSpeed < 5.0f) {
                        m->actionTimer = 1;
                    } else if (intendedSpeed > 22.0f) {
                        m->actionTimer = 3;
                    } else {
                        //! (Speed Crash) If Mario's speed is more than 2^17.
                        animSpeed = (AnimAccel)((intendedSpeed / 4.0f) * 0x10000);
                        set_mario_anim_with_accel(m, MARIO_ANIM_WALKING, animSpeed);
                        play_step_sound(m, 10, 49);
                        inLoop = FALSE;
                    }
                    break;
                case 3:
                    if (intendedSpeed < 18.0f) {
                        m->actionTimer = 2;
                    } else {
                        //! (Speed Crash) If Mario's speed is more than 2^17.
                        animSpeed = (AnimAccel)((intendedSpeed / 4.0f) * 0x10000);
                        set_mario_anim_with_accel(m, MARIO_ANIM_RUNNING, animSpeed);
                        play_step_sound(m, 9, 45);
                        targetPitch = tilt_body_running(m);
                        inLoop = FALSE;
                    }
                    break;
            }
        }
    }
    approach_s32_symmetric_bool(&marioObj->oMarioWalkingPitch, targetPitch, DEG(11.25));
    marioObj->header.gfx.angle[0] = marioObj->oMarioWalkingPitch;
}

void anim_and_audio_for_hold_walk(struct MarioState *m) {
    Bool32 inLoop = TRUE;
    f32 intendedSpeed = ((m->intendedMag > m->forwardVel) ? m->intendedMag : m->forwardVel);
    if (intendedSpeed < 2.0f) intendedSpeed = 2.0f;
    while (inLoop) {
        switch (m->actionTimer) {
            case 0:
                if (intendedSpeed > 6.0f) {
                    m->actionTimer = 1;
                } else {
                    //! (Speed Crash) Crashes if Mario's speed exceeds or equals 2^15.
                    set_mario_anim_with_accel(m, MARIO_ANIM_SLOW_WALK_WITH_LIGHT_OBJ, (intendedSpeed * 0x10000));
                    play_step_sound(m, 12, 62);
                    inLoop = FALSE;
                }
                break;
            case 1:
                if (intendedSpeed < 3.0f) {
                    m->actionTimer = 0;
                } else if (intendedSpeed > 11.0f) {
                    m->actionTimer = 2;
                } else {
                    //! (Speed Crash) Crashes if Mario's speed exceeds or equals 2^15.
                    set_mario_anim_with_accel(m, MARIO_ANIM_WALK_WITH_LIGHT_OBJ, (intendedSpeed * 0x10000));
                    play_step_sound(m, 12, 62);
                    inLoop = FALSE;
                }
                break;
            case 2:
                if (intendedSpeed < 8.0f) {
                    m->actionTimer = 1;
                } else {
                    //! (Speed Crash) Crashes if Mario's speed exceeds or equals 2^16.
                    set_mario_anim_with_accel(m, MARIO_ANIM_RUN_WITH_LIGHT_OBJ, ((intendedSpeed / 2.0f) * 0x10000));
                    play_step_sound(m, 10, 49);
                    inLoop = FALSE;
                }
                break;
        }
    }
}

void anim_and_audio_for_heavy_walk(struct MarioState *m) {
    AnimAccel animSpeed = (AnimAccel)(m->intendedMag * 0x10000);
    set_mario_anim_with_accel(m, MARIO_ANIM_WALK_WITH_HEAVY_OBJ, animSpeed);
    play_step_sound(m, 26, 79);
}

void push_or_sidle_wall(struct MarioState *m, Vec3f startPos) {
    Angle dWallAngle;
    f32 speed;
    vec3f_get_lateral_dist(startPos, m->pos, &speed);
    //! (Speed Crash) If a wall is after moving 16384 distance, this crashes.
    AnimAccel animSpeed = (AnimAccel)((speed * 2.0f) * 0x10000);
    if (m->forwardVel > 6.0f) mario_set_forward_vel(m, 6.0f);
    if (m->wall != NULL) dWallAngle = abs_angle_diff(m->wallYaw, m->faceAngle[1]);
    if ((m->wall == NULL) || (dWallAngle > DEG(160))) {
        m->flags |= MARIO_PUSHING;
        set_mario_animation(m, MARIO_ANIM_PUSHING);
        play_step_sound(m, 6, 18);
#ifdef FIX_WALL_SIDLE_SLOPE
        if (m->wall != NULL) {
            m->marioObj->header.gfx.angle[1] = (m->wallYaw + DEG(180));
            if ((m->floor != NULL) && (m->floor->normal.y < NEAR_ONE)) m->marioObj->header.gfx.angle[2] = ((atan2s(sqrtf(sqr(m->floor->normal.z) + sqr(m->floor->normal.x)), m->floor->normal.y) - DEG(90)) * sins(m->wallYaw - m->floorYaw));
        }
#endif
    } else {
        set_mario_anim_with_accel(m, ((dWallAngle < 0) ? MARIO_ANIM_SIDESTEP_RIGHT : MARIO_ANIM_SIDESTEP_LEFT), animSpeed);
        if (m->marioObj->header.gfx.animInfo.animFrame < 20) {
            play_sound((SOUND_MOVING_TERRAIN_SLIDE + m->terrainSoundAddend), m->marioObj->header.gfx.cameraToObject);
            m->particleFlags |= PARTICLE_DUST;
        }
        m->actionState                   = PUSH_OR_SIDLE_WALL_STATE_SIDLING;
        m->actionArg                     = (m->wallYaw + DEG(180));
        //! TODO: Make these smooth somehow:
        m->marioObj->header.gfx.angle[1] = (m->wallYaw + DEG(180));
#ifdef FIX_WALL_SIDLE_SLOPE
        if ((m->floor != NULL) && (m->floor->normal.y < NEAR_ONE)) m->marioObj->header.gfx.angle[2] = ((atan2s(sqrtf(sqr(m->floor->normal.z) + sqr(m->floor->normal.x)), m->floor->normal.y) - DEG(90)) * sins(m->wallYaw - m->floorYaw));
#else
        m->marioObj->header.gfx.angle[2] = find_floor_slope(m, DEG(90), 5.0f);
#endif
    }
}

void tilt_body_walking(struct MarioState *m, Angle startYaw) {
    struct MarioBodyState *marioBodyState = m->marioBodyState;
    AnimID16 animID = m->marioObj->header.gfx.animInfo.animID;
    if ((animID == MARIO_ANIM_WALKING) || (animID == MARIO_ANIM_RUNNING)) {
        Angle dYaw = (m->faceAngle[1] - startYaw);
        //! (Speed Crash) These casts can cause a crash if (dYaw * forwardVel / 12) or
        //! (forwardVel * 170) exceed or equal 2^31.
        Angle nextBodyRoll = -(Angle)(dYaw * m->forwardVel /  12.0f);
        Angle nextBodyPitch = (Angle)(       m->forwardVel * 170.0f);
        if (nextBodyRoll  >  DEG(30)) nextBodyRoll  =  DEG(30);
        if (nextBodyRoll  < -DEG(30)) nextBodyRoll  = -DEG(30);
        if (nextBodyPitch >  DEG(30)) nextBodyPitch =  DEG(30);
        if (nextBodyPitch <     0x0) nextBodyPitch =     0x0;
        approach_angle_bool(&marioBodyState->torsoAngle[2], nextBodyRoll,  DEG(5.625));
        approach_angle_bool(&marioBodyState->torsoAngle[0], nextBodyPitch, DEG(5.625));
    } else {
        marioBodyState->torsoAngle[2] = 0x0;
        marioBodyState->torsoAngle[0] = 0x0;
    }
}

void tilt_body_ground_shell(struct MarioState *m, Angle startYaw) {
    struct MarioBodyState *marioBodyState = m->marioBodyState;
    struct Object *marioObj = m->marioObj;
    Angle dYaw = m->faceAngle[1] - startYaw;
    //! (Speed Crash) These casts can cause a crash if (dYaw * forwardVel / 12) or
    //! (forwardVel * 170) exceed or equal 2^31. Harder (if not impossible to do)
    //! while on a Koopa Shell making this less of an issue.
    Angle nextBodyRoll = -(Angle)(dYaw * m->forwardVel /  12.0f);
    Angle nextBodyPitch = (Angle)(       m->forwardVel * 170.0f);
    if (nextBodyRoll  >  DEG(33.75)) nextBodyRoll  =  DEG(33.75);
    if (nextBodyRoll  < -DEG(33.75)) nextBodyRoll  = -DEG(33.75);
    if (nextBodyPitch >  DEG(22.5 )) nextBodyPitch =  DEG(22.5 );
    if (nextBodyPitch <         0x0) nextBodyPitch =         0x0;
    approach_angle_bool(&marioBodyState->torsoAngle[2], nextBodyRoll,  0x200);
    approach_angle_bool(&marioBodyState->torsoAngle[0], nextBodyPitch, 0x200);
    marioBodyState->headAngle[2]  = -marioBodyState->torsoAngle[2];
    marioObj->header.gfx.angle[2] =  marioBodyState->torsoAngle[2];
    marioObj->header.gfx.pos[1]  += 45.0f;
}

Bool32 act_walking(struct MarioState *m) {
    Angle startYaw = m->faceAngle[1];
    mario_drop_held_object(m);
    if (should_begin_sliding(m)                                                         ) return set_mario_action(m, ACT_BEGIN_SLIDING, 0);
    if (m->input & INPUT_FIRST_PERSON                                                   ) return begin_braking_action(m);
    if (m->input & INPUT_A_PRESSED                                                      ) return set_jump_from_landing(m);
    if (check_ground_dive_or_punch(m)                                                   ) return TRUE;
    if (m->input & INPUT_IDLE                                                           ) return begin_braking_action(m);
    if (analog_stick_held_back(m, DEG(100)) && (m->forwardVel >= GROUND_SPEED_THRESHOLD)) return set_mario_action(m, ACT_TURNING_AROUND, 0);
    if (m->input & INPUT_Z_PRESSED                                                      ) return set_mario_action(m, ACT_CROUCH_SLIDE  , 0);
    m->actionState = ACT_WALKING_STATE_NO_WALL;
    Vec3f startPos;
    vec3_copy(startPos, m->pos);
    update_walking_speed(m);
    switch (perform_ground_step(m)) {
        case GROUND_STEP_LEFT_GROUND:
            set_mario_action(m, ACT_FREEFALL, 0);
            set_mario_animation(m, MARIO_ANIM_GENERAL_FALL);
            break;
        case GROUND_STEP_NONE:
            anim_and_audio_for_walk(m);
            if ((m->intendedMag - m->forwardVel) > GROUND_SPEED_THRESHOLD) m->particleFlags |= PARTICLE_DUST;
            break;
        case GROUND_STEP_HIT_WALL:
            push_or_sidle_wall(m, startPos);
            m->actionTimer = 0;
            break;
    }
    check_ledge_climb_down(m);
    tilt_body_walking(m, startYaw);
#ifdef FIX_WALL_SIDLE_SLOPE
    if ((m->wall != NULL) && (abs_angle_diff(m->wallYaw, m->faceAngle[1]) > DEG(135))) {
        m->marioObj->header.gfx.angle[1] = (m->wallYaw + DEG(180));
        if ((m->floor != NULL) && (m->floor->normal.y < NEAR_ONE)) m->marioObj->header.gfx.angle[2] = ((atan2s(sqrtf(sqr(m->floor->normal.z) + sqr(m->floor->normal.x)), m->floor->normal.y) - DEG(90)) * sins(m->wallYaw - m->floorYaw));
    }
#endif
    return FALSE;
}

Bool32 act_move_punching(struct MarioState *m) {
    if (should_begin_sliding(m)                                                               ) return set_mario_action(m, ACT_BEGIN_SLIDING, 0);
    if ((m->actionState == ACT_MOVE_PUNCHING_STATE_CAN_JUMP_KICK) && (m->input & INPUT_A_DOWN)) return set_mario_action(m, ACT_JUMP_KICK    , 0);
    m->actionState = ACT_MOVE_PUNCHING_STATE_NO_JUMP_KICK;
    mario_update_punch_sequence(m);
    if (m->forwardVel >= 0.0f) {
        apply_slope_decel(m, 0.5f);
    } else {
        if ((m->forwardVel += 8.0f) >= 0.0f) m->forwardVel = 0.0f;
        apply_slope_accel(m);
    }
    switch (perform_ground_step(m)) {
        case GROUND_STEP_LEFT_GROUND: set_mario_action(m, ACT_FREEFALL, 0); break;
        case GROUND_STEP_NONE:        m->particleFlags |= PARTICLE_DUST;    break;
    }
    return FALSE;
}

Bool32 act_hold_walking(struct MarioState *m) {
    if (m->heldObj->behavior == segmented_to_virtual(bhvJumpingBox)) return set_mario_action(         m, ACT_CRAZY_BOX_BOUNCE  , 0);
    if (m->marioObj->oInteractStatus & INT_STATUS_MARIO_DROP_OBJECT) return drop_and_set_mario_action(m, ACT_WALKING           , 0);
    if (should_begin_sliding(m)                                    ) return set_mario_action(         m, ACT_HOLD_BEGIN_SLIDING, 0);
    if (m->input & INPUT_B_PRESSED                                 ) return set_mario_action(         m, ACT_THROWING          , 0);
    if (m->input & INPUT_A_PRESSED                                 ) return set_jumping_action(       m, ACT_HOLD_JUMP         , 0);
    if (m->input & INPUT_IDLE                                      ) return set_mario_action(         m, ACT_HOLD_DECELERATING , 0);
    if (m->input & INPUT_Z_PRESSED                                 ) return drop_and_set_mario_action(m, ACT_CROUCH_SLIDE      , 0);
    m->intendedMag *= 0.4f;
    update_walking_speed(m);
    switch (perform_ground_step(m)) {
        case GROUND_STEP_LEFT_GROUND: set_mario_action(m, ACT_HOLD_FREEFALL, 0);                  break;
        case GROUND_STEP_HIT_WALL:    if (m->forwardVel > 16.0f) mario_set_forward_vel(m, 16.0f); break;
    }
    anim_and_audio_for_hold_walk(m);
    if (((0.4f * m->intendedMag) - m->forwardVel) > GROUND_SPEED_THRESHOLD_2) m->particleFlags |= PARTICLE_DUST;
    return FALSE;
}

Bool32 act_hold_heavy_walking(struct MarioState *m) {
    if (m->input & INPUT_B_PRESSED) return set_mario_action(         m, ACT_HEAVY_THROW    , 0);
    if (should_begin_sliding(m)   ) return drop_and_set_mario_action(m, ACT_BEGIN_SLIDING  , 0);
    if (m->input & INPUT_IDLE     ) return set_mario_action(         m, ACT_HOLD_HEAVY_IDLE, 0);
    m->intendedMag *= 0.1f;
    update_walking_speed(m);
    switch (perform_ground_step(m)) {
        case GROUND_STEP_LEFT_GROUND: drop_and_set_mario_action(m, ACT_FREEFALL, 0);              break;
        case GROUND_STEP_HIT_WALL:    if (m->forwardVel > 10.0f) mario_set_forward_vel(m, 10.0f); break;
    }
    anim_and_audio_for_heavy_walk(m);
    return FALSE;
}

Bool32 act_turning_around(struct MarioState *m) {
    if (m->input & INPUT_ABOVE_SLIDE        ) return set_mario_action(    m, ACT_BEGIN_SLIDING, 0);
    if (m->input & INPUT_A_PRESSED          ) return set_jumping_action(  m, ACT_SIDE_FLIP    , 0);
#ifdef ACTION_CANCELS
    if (m->input & INPUT_B_PRESSED          ) return set_mario_action(    m, ACT_MOVE_PUNCHING, 0);
#endif
    if (m->input & INPUT_IDLE               ) return set_mario_action(    m, ACT_BRAKING      , 0);
    if (!analog_stick_held_back(m, DEG(100))) return set_mario_action(    m, ACT_WALKING      , 0);
    if (apply_slope_decel(m, 2.0f)          ) return begin_walking_action(m, 8.0f, ACT_FINISH_TURNING_AROUND, 0);
    play_sound((SOUND_MOVING_TERRAIN_SLIDE + m->terrainSoundAddend), m->marioObj->header.gfx.cameraToObject);
    adjust_sound_for_speed(m);
    switch (perform_ground_step(m)) {
        case GROUND_STEP_LEFT_GROUND: set_mario_action(m, ACT_FREEFALL, 0); break;
        case GROUND_STEP_NONE:        m->particleFlags |= PARTICLE_DUST;    break;
    }
    if (m->forwardVel >= 18.0f) {
        set_mario_animation(m, MARIO_ANIM_TURNING_PART1);
    } else {
        set_mario_animation(m, MARIO_ANIM_TURNING_PART2);
        if (is_anim_at_end(m)) begin_walking_action(m, ((m->forwardVel > 0.0f) ? -m->forwardVel : 8.0f), ACT_WALKING, 0);
    }
    return FALSE;
}

Bool32 act_finish_turning_around(struct MarioState *m) {
    if (m->input & INPUT_ABOVE_SLIDE) return set_mario_action(         m, ACT_BEGIN_SLIDING, 0);
    if (m->input & INPUT_A_PRESSED  ) return set_jumping_action(       m, ACT_SIDE_FLIP    , 0);
#ifdef ACTION_CANCELS
    if (m->input & INPUT_B_PRESSED  ) return set_mario_action(         m, ACT_MOVE_PUNCHING, 0);
    if (m->input & INPUT_Z_PRESSED  ) return drop_and_set_mario_action(m, ACT_CROUCH_SLIDE , 0);
#endif
    update_walking_speed(m);
    set_mario_animation(m, MARIO_ANIM_TURNING_PART2);
    if (perform_ground_step(m) == GROUND_STEP_LEFT_GROUND) set_mario_action(m, ACT_FREEFALL, 0);
    if (is_anim_at_end(m)) set_mario_action(m, ACT_WALKING, 0);
    //! TODO: fix this for FLOOR_ALIGNMENT
    m->marioObj->header.gfx.angle[1] += DEG(180);
    return FALSE;
}

Bool32 act_braking(struct MarioState *m) {
#ifdef LESS_GROUND_BONKS
    Vec3f startPos;
    vec3_copy(startPos, m->pos);
#endif
    if (!(m->input & INPUT_FIRST_PERSON) && (m->input & (INPUT_NONZERO_ANALOG | INPUT_A_PRESSED | INPUT_OFF_FLOOR | INPUT_ABOVE_SLIDE))) return check_common_action_exits(m);
    if (apply_slope_decel(m, 2.0f)) return set_mario_action(m, ACT_BRAKING_STOP , 0);
    if (m->input & INPUT_B_PRESSED) return set_mario_action(m, ACT_MOVE_PUNCHING, 0);
#ifdef ACTION_CANCELS
    if (m->input & INPUT_Z_PRESSED) return set_mario_action(m, ACT_CROUCH_SLIDE , 0);
#endif
#ifdef FIX_WALL_SIDLE_SLOPE
    if ((m->wall != NULL) && (abs_angle_diff(m->wallYaw, m->faceAngle[1]) > DEG(135))) return set_mario_action(m, ACT_STANDING_AGAINST_WALL, 0);
#endif
    switch (perform_ground_step(m)) {
        case GROUND_STEP_LEFT_GROUND: set_mario_action(m, ACT_FREEFALL, 0); break;
        case GROUND_STEP_NONE:        m->particleFlags |= PARTICLE_DUST;    break;
        case GROUND_STEP_HIT_WALL:
#ifdef LESS_GROUND_BONKS
            push_or_sidle_wall(m, startPos);
#else
            slide_bonk(m, ACT_BACKWARD_GROUND_KB, ACT_BRAKING_STOP);
#endif
            break;
    }
#ifdef LESS_GROUND_BONKS
    if (m->wall != NULL) {
        push_or_sidle_wall(m, startPos);
        m->actionTimer = 0;
    }
#endif
    play_sound(SOUND_MOVING_TERRAIN_SLIDE + m->terrainSoundAddend, m->marioObj->header.gfx.cameraToObject);
    adjust_sound_for_speed(m);
    set_mario_animation(m, MARIO_ANIM_SKID_ON_GROUND);
    return FALSE;
}

Bool32 act_decelerating(struct MarioState *m) {
    AnimAccel animSpeed;
    s16 slopeClass = mario_get_floor_class(m);
    if (!(m->input & INPUT_FIRST_PERSON)) {
        if (should_begin_sliding(m)        ) return set_mario_action(m, ACT_BEGIN_SLIDING, 0);
        if (m->input & INPUT_A_PRESSED     ) return set_jump_from_landing(m);
        if (check_ground_dive_or_punch(m)  ) return TRUE;
        if (m->input & INPUT_NONZERO_ANALOG) return set_mario_action(m, ACT_WALKING     , 0);
        if (m->input & INPUT_Z_PRESSED     ) return set_mario_action(m, ACT_CROUCH_SLIDE, 0);
    }
    if (update_decelerating_speed(m)) return set_mario_action(m, ACT_IDLE, 0);
    switch (perform_ground_step(m)) {
        case GROUND_STEP_LEFT_GROUND: set_mario_action(m, ACT_FREEFALL, 0); break;
        case GROUND_STEP_HIT_WALL:
            if (slopeClass == SURFACE_CLASS_VERY_SLIPPERY) {
                mario_bonk_reflection(m, TRUE);
            } else {
                mario_set_forward_vel(m, 0.0f);
            }
            break;
    }
    if (slopeClass == SURFACE_CLASS_VERY_SLIPPERY) {
        set_mario_animation(m, MARIO_ANIM_IDLE_HEAD_LEFT);
        play_sound(SOUND_MOVING_TERRAIN_SLIDE + m->terrainSoundAddend, m->marioObj->header.gfx.cameraToObject);
        adjust_sound_for_speed(m);
        m->particleFlags |= PARTICLE_DUST;
    } else {
        // (Speed Crash) Crashes if speed exceeds 2^17.
        if ((animSpeed = (AnimAccel)((m->forwardVel / 4.0f) * 0x10000)) < 0x1000) animSpeed = 0x1000;
        set_mario_anim_with_accel(m, MARIO_ANIM_WALKING, animSpeed);
        play_step_sound(m, 10, 49);
    }
#ifdef LEDGE_PROTECTION
    check_ledge_climb_down(m);
#endif
    return FALSE;
}

Bool32 act_hold_decelerating(struct MarioState *m) {
    AnimAccel animSpeed;
    s16 slopeClass = mario_get_floor_class(m);
    if (m->marioObj->oInteractStatus & INT_STATUS_MARIO_DROP_OBJECT) return drop_and_set_mario_action(m, ACT_WALKING, 0);
    if (should_begin_sliding(m)        ) return set_mario_action(         m, ACT_HOLD_BEGIN_SLIDING, 0);
    if (m->input & INPUT_B_PRESSED     ) return set_mario_action(         m, ACT_THROWING          , 0);
    if (m->input & INPUT_A_PRESSED     ) return set_jumping_action(       m, ACT_HOLD_JUMP         , 0);
    if (m->input & INPUT_Z_PRESSED     ) return drop_and_set_mario_action(m, ACT_CROUCH_SLIDE      , 0);
    if (m->input & INPUT_NONZERO_ANALOG) return set_mario_action(         m, ACT_HOLD_WALKING      , 0);
    if (update_decelerating_speed(m)   ) return set_mario_action(         m, ACT_HOLD_IDLE         , 0);
    m->intendedMag *= 0.4f;
    switch (perform_ground_step(m)) {
        case GROUND_STEP_LEFT_GROUND: set_mario_action(m, ACT_HOLD_FREEFALL, 0); break;
        case GROUND_STEP_HIT_WALL:
            if (slopeClass == SURFACE_CLASS_VERY_SLIPPERY) {
                mario_bonk_reflection(m, TRUE);
            } else {
                mario_set_forward_vel(m, 0.0f);
            }
            break;
    }
    if (slopeClass == SURFACE_CLASS_VERY_SLIPPERY) {
        set_mario_animation(m, MARIO_ANIM_IDLE_WITH_LIGHT_OBJ);
        play_sound(SOUND_MOVING_TERRAIN_SLIDE + m->terrainSoundAddend, m->marioObj->header.gfx.cameraToObject);
        adjust_sound_for_speed(m);
        m->particleFlags |= PARTICLE_DUST;
    } else {
        //! (Speed Crash) This crashes if Mario has more speed than 2^15 speed.
        if ((animSpeed = (AnimAccel)(m->forwardVel * 0x10000)) < 0x1000) animSpeed = 0x1000;
        set_mario_anim_with_accel(m, MARIO_ANIM_WALK_WITH_LIGHT_OBJ, animSpeed);
        play_step_sound(m, 12, 62);
    }
    return FALSE;
}

Bool32 act_riding_shell_ground(struct MarioState *m) {
    Angle startYaw = m->faceAngle[1];
    if (m->input & INPUT_A_PRESSED) return set_mario_action(m, ACT_RIDING_SHELL_JUMP, 0);
    if (m->input & INPUT_Z_PRESSED) {
        mario_stop_riding_object(m);
        if (m->forwardVel < 24.0f) mario_set_forward_vel(m, 24.0f);
        return set_mario_action(m, ACT_CROUCH_SLIDE, 0);
    }
    update_shell_speed(m);
    set_mario_animation(m, ((m->actionArg == 0) ? MARIO_ANIM_START_RIDING_SHELL : MARIO_ANIM_RIDING_SHELL));
    switch (perform_ground_step(m)) {
        case GROUND_STEP_LEFT_GROUND:
            set_mario_action(m, ACT_RIDING_SHELL_FALL, 0);
            break;
        case GROUND_STEP_HIT_WALL:
// #ifdef LESS_GROUND_BONKS
//             if (m->wall == NULL) {
//                 m->faceAngle[1] += DEG(180);
//             } else {
// #endif
                mario_stop_riding_object(m);
                play_sound(((m->flags & MARIO_METAL_CAP) ? SOUND_ACTION_METAL_BONK : SOUND_ACTION_BONK), m->marioObj->header.gfx.cameraToObject);
                m->particleFlags |= PARTICLE_VERTICAL_STAR;
                set_mario_action(m, ACT_BACKWARD_GROUND_KB, 0);
// #ifdef LESS_GROUND_BONKS
//             }
// #endif
            break;
    }
    tilt_body_ground_shell(m, startYaw);
    play_sound(((m->floor->type == SURFACE_BURNING) ? SOUND_MOVING_RIDING_SHELL_LAVA : (SOUND_MOVING_TERRAIN_RIDING_SHELL + m->terrainSoundAddend)), m->marioObj->header.gfx.cameraToObject);
    adjust_sound_for_speed(m);
#if ENABLE_RUMBLE
    reset_rumble_timers_slip();
#endif
    return FALSE;
}

Bool32 act_crawling(struct MarioState *m) {
    if (should_begin_sliding(m)      ) return set_mario_action(  m, ACT_BEGIN_SLIDING, 0);
    if (m->input & INPUT_FIRST_PERSON) return set_mario_action(  m, ACT_STOP_CRAWLING, 0);
    if (m->input & INPUT_A_PRESSED   ) return set_jumping_action(m, ACT_JUMP         , 0);
    if (check_ground_dive_or_punch(m)) return TRUE;
    if (m->input & INPUT_IDLE        ) return set_mario_action(  m, ACT_STOP_CRAWLING, 0);
    if (!(m->input & INPUT_Z_DOWN)   ) return set_mario_action(  m, ACT_STOP_CRAWLING, 0);
    m->intendedMag *= 0.1f;
    update_walking_speed(m);
    switch (perform_ground_step(m)) {
        case GROUND_STEP_LEFT_GROUND: set_mario_action(m, ACT_FREEFALL, 0); break;
        case GROUND_STEP_HIT_WALL:
            if (m->forwardVel > GROUND_SPEED_THRESHOLD_2) mario_set_forward_vel(m, GROUND_SPEED_THRESHOLD_2);
            //! Possibly unintended missing break
#ifdef FAST_FLOOR_ALIGN
        // fall through
        case GROUND_STEP_NONE: align_with_floor(m, TRUE); break;
#else
        // fall through
        case GROUND_STEP_NONE: align_with_floor(m); break;
#endif
    }
    AnimAccel animSpeed = (AnimAccel)((m->intendedMag * 2.0f) * 0x10000);
    set_mario_anim_with_accel(m, MARIO_ANIM_CRAWLING, animSpeed);
    play_step_sound(m, 26, 79);
    return FALSE;
}

Bool32 act_burning_ground(struct MarioState *m) {
    if (m->input & INPUT_A_PRESSED) return set_mario_action(m, ACT_BURNING_JUMP, 0);
    m->marioObj->oMarioBurnTimer += 2;
    if (m->marioObj->oMarioBurnTimer > 160) return set_mario_action(m, ACT_WALKING, 0);
    if ((m->waterLevel - m->floorHeight) > 50.0f) {
        play_sound(SOUND_GENERAL_FLAME_OUT, m->marioObj->header.gfx.cameraToObject);
        return set_mario_action(m, ACT_WALKING, 0);
    }
    if (m->forwardVel <  8.0f) m->forwardVel =  8.0f;
    if (m->forwardVel > 48.0f) m->forwardVel = 48.0f;
    approach_f32_bool(&m->forwardVel, 32.0f, 4.0f, 1.0f);
    if (m->input & INPUT_NONZERO_ANALOG) approach_angle_bool(&m->faceAngle[1], m->intendedYaw, 0x600);
    apply_slope_accel(m);
    if (perform_ground_step(m) == GROUND_STEP_LEFT_GROUND) set_mario_action(m, ACT_BURNING_FALL, 0);
    set_mario_anim_with_accel(m, MARIO_ANIM_RUNNING, (s32)((m->forwardVel / 2.0f) * 0x10000));
    play_step_sound(m, 9, 45);
    m->particleFlags |= PARTICLE_FIRE;
    play_sound(SOUND_MOVING_LAVA_BURN, m->marioObj->header.gfx.cameraToObject);
    m->health -= 10;
#ifdef DAMAGE_SCREEN_TINT
    m->hurtShadeAlpha = 0x40;
#endif
    if (m->health < 0x100) set_mario_action(m, ACT_STANDING_DEATH, 0);
    m->marioBodyState->eyeState = MARIO_EYES_DEAD;
#if ENABLE_RUMBLE
    reset_rumble_timers_slip();
#endif
    return FALSE;
}

void tilt_body_butt_slide(struct MarioState *m) {
    Angle intendedDYaw = (m->intendedYaw - m->faceAngle[1]);
    m->marioBodyState->torsoAngle[0] = (Angle32)( (5461.3335f * (m->intendedMag / 32.0f) * coss(intendedDYaw)));
    m->marioBodyState->torsoAngle[2] = (Angle32)(-(5461.3335f * (m->intendedMag / 32.0f) * sins(intendedDYaw)));
}

void common_slide_action(struct MarioState *m, MarioAction endAction, MarioAction airAction, AnimID32 animation) {
    play_sound((SOUND_MOVING_TERRAIN_SLIDE + m->terrainSoundAddend), m->marioObj->header.gfx.cameraToObject);
#if ENABLE_RUMBLE
    reset_rumble_timers_slip();
#endif
    adjust_sound_for_speed(m);
    switch (perform_ground_step(m)) {
        case GROUND_STEP_LEFT_GROUND:
#ifdef LEDGE_PROTECTION
            mario_set_forward_vel(m, m->forwardVel + 8.0f);
#endif
            set_mario_action(m, airAction, 0);
            if ((m->forwardVel < -50.0f) || (50.0f < m->forwardVel)) play_sound(SOUND_MARIO_HOOHOO, m->marioObj->header.gfx.cameraToObject);
            break;
        case GROUND_STEP_NONE:
#ifdef FAST_CROUCHING
            set_mario_anim_with_accel(m, animation, 0x30000);
#else
            set_mario_animation(m, animation);
#endif
#ifdef FAST_FLOOR_ALIGN
            align_with_floor(m, FALSE);
#else
            align_with_floor(m);
#endif
            m->particleFlags |= PARTICLE_DUST;
            break;
        case GROUND_STEP_HIT_WALL:
            if (!mario_floor_is_slippery(m)) {
                if (m->forwardVel > 16.0f) m->particleFlags |= PARTICLE_VERTICAL_STAR;
                slide_bonk(m, ACT_GROUND_BONK, endAction);
            } else if (m->wall != NULL) {
                Angle wallAngle  = m->wallYaw;
                f32 slideSpeed   = sqrtf(sqr(m->slideVelX) + sqr(m->slideVelZ));
                if ((slideSpeed *= 0.9f) < 4.0f) slideSpeed = 4.0f;
                m->slideYaw = (wallAngle - ((Angle)(m->slideYaw - wallAngle) + DEG(180)));
                m->vel[0] = m->slideVelX = (slideSpeed * sins(m->slideYaw));
                m->vel[2] = m->slideVelZ = (slideSpeed * coss(m->slideYaw));
            }
#ifdef FAST_FLOOR_ALIGN
            align_with_floor(m, FALSE);
#else
            align_with_floor(m);
#endif
            break;
    }
}

Bool32 common_slide_action_with_jump(struct MarioState *m, MarioAction stopAction, MarioAction jumpAction, MarioAction airAction, AnimID32 animation) {
    if (m->actionTimer == 5) {
        if (m->input & INPUT_A_PRESSED) return set_jumping_action(m, jumpAction, 0);
    } else {
        m->actionTimer++;
    }
    if (update_sliding(m, 4.0f)) return set_mario_action(m, stopAction, 0);
    common_slide_action(m, stopAction, airAction, animation);
    return FALSE;
}

Bool32 act_butt_slide(struct MarioState *m) {
    Bool32 cancel = common_slide_action_with_jump(m, ACT_BUTT_SLIDE_STOP, ACT_JUMP, ACT_BUTT_SLIDE_AIR, MARIO_ANIM_SLIDE);
    tilt_body_butt_slide(m);
    return cancel;
}

Bool32 act_hold_butt_slide(struct MarioState *m) {
    if (m->marioObj->oInteractStatus & INT_STATUS_MARIO_DROP_OBJECT) return drop_and_set_mario_action(m, ACT_BUTT_SLIDE, 0);
    Bool32 cancel = common_slide_action_with_jump(m, ACT_HOLD_BUTT_SLIDE_STOP, ACT_HOLD_JUMP, ACT_HOLD_BUTT_SLIDE_AIR, MARIO_ANIM_SLIDING_ON_BOTTOM_WITH_LIGHT_OBJ);
    tilt_body_butt_slide(m);
    return cancel;
}

Bool32 act_crouch_slide(struct MarioState *m) {
    Bool32 cancel;
    if (m->input & INPUT_ABOVE_SLIDE) return set_mario_action(m, ACT_BUTT_SLIDE, 0);
#ifdef ACTION_CANCELS
    if (m->marioObj->header.gfx.animInfo.animID == MARIO_ANIM_STOP_CROUCHING && is_anim_past_end(m)) set_mario_action(m, ACT_WALKING, 0);
#endif
    if (m->actionTimer < 30) {
        m->actionTimer++;
        if (m->input & INPUT_A_PRESSED) {
#ifdef ACTION_CANCELS
            return set_jumping_action(m, ((m->forwardVel > 8.0f) && !analog_stick_held_back(m, DEG(100))) ? ACT_LONG_JUMP : ACT_BACKFLIP, 0);
        }
    } else if (m->input & INPUT_A_PRESSED) {
        return set_jumping_action(m, ACT_JUMP, 0);
    } else if ((m->input & INPUT_NONZERO_ANALOG) && (m->intendedMag > 16.0f)) {
        return set_mario_action(m, ACT_START_CRAWLING, 0);
#else
            if (m->forwardVel > GROUND_SPEED_THRESHOLD_2) return set_jumping_action(m, ACT_LONG_JUMP, 0);
        }
#endif
    }
    if (m->input & INPUT_B_PRESSED) {
        if (m->forwardVel >= GROUND_SPEED_THRESHOLD_2) {
            return set_mario_action(m, ACT_SLIDE_KICK, 0);
        } else {
            return set_mario_action(m, ACT_MOVE_PUNCHING, 0x9);
        }
    }
#ifdef ACTION_CANCELS
    if (m->input & INPUT_OFF_FLOOR   ) return set_mario_action(  m, ACT_FREEFALL     , 0);
    if (m->input & INPUT_ABOVE_SLIDE ) return set_mario_action(  m, ACT_BEGIN_SLIDING, 0);
#else
    if (m->input & INPUT_A_PRESSED   ) return set_jumping_action(m, ACT_JUMP         , 0);
#endif
    if (m->input & INPUT_FIRST_PERSON) return set_mario_action(  m, ACT_BRAKING      , 0);
    cancel = common_slide_action_with_jump(m, ACT_CROUCHING, ACT_JUMP, ACT_FREEFALL,
#ifdef ACTION_CANCELS
                                           (m->input & INPUT_Z_DOWN) ? MARIO_ANIM_START_CROUCHING : MARIO_ANIM_STOP_CROUCHING);
#else
                                           MARIO_ANIM_START_CROUCHING);
#endif
    return cancel;
}

Bool32 act_slide_kick_slide(struct MarioState *m) {
#ifdef ACTION_CANCELS
    if (m->input & (INPUT_A_PRESSED | INPUT_B_PRESSED)) {
#if ENABLE_RUMBLE
        queue_rumble_data(5, 80);
#endif
        return set_jumping_action(m, analog_stick_held_back(m, DEG(90)) ? ACT_BACKWARD_ROLLOUT : ((m->forwardVel >= 0.0f) ? ACT_FORWARD_ROLLOUT : ACT_BACKWARD_ROLLOUT), 0);
    }
#else
    if (m->input & INPUT_A_PRESSED) {
#if ENABLE_RUMBLE
        queue_rumble_data(5, 80);
#endif
        return set_jumping_action(m, ACT_FORWARD_ROLLOUT, 0);
    }
#endif
    set_mario_animation(m, MARIO_ANIM_SLIDE_KICK);
#ifdef ACTION_CANCELS
    if ((is_anim_at_end(m) && (m->forwardVel < 1.0f)) || !(m->input & INPUT_NONZERO_ANALOG)) return set_mario_action(m, ACT_SLIDE_KICK_SLIDE_STOP, 0);
#else
    if ( is_anim_at_end(m) && (m->forwardVel < 1.0f)) return set_mario_action(m, ACT_SLIDE_KICK_SLIDE_STOP, 0);
#endif
    update_sliding(m, 1.0f);
    switch (perform_ground_step(m)) {
        case GROUND_STEP_LEFT_GROUND: set_mario_action(m, ACT_FREEFALL, 2); break;
        case GROUND_STEP_HIT_WALL:
            mario_bonk_reflection(m, TRUE);
            m->particleFlags |= PARTICLE_VERTICAL_STAR;
            set_mario_action(m, ACT_BACKWARD_GROUND_KB, 0);
            break;
    }
    play_sound(SOUND_MOVING_TERRAIN_SLIDE + m->terrainSoundAddend, m->marioObj->header.gfx.cameraToObject);
    m->particleFlags |= PARTICLE_DUST;
    return FALSE;
}

Bool32 stomach_slide_action(struct MarioState *m, MarioAction stopAction, MarioAction airAction, AnimID32 animation) {
#ifdef ACTION_CANCELS
    if (m->input & (INPUT_A_PRESSED | INPUT_B_PRESSED)) {
#else
    if (m->actionTimer == 5) {
        if (!(m->input & INPUT_ABOVE_SLIDE) && (m->input & (INPUT_A_PRESSED | INPUT_B_PRESSED))) {
#endif
#if ENABLE_RUMBLE
            queue_rumble_data(5, 80);
#endif
#ifdef ACTION_CANCELS
        return drop_and_set_mario_action(m, (analog_stick_held_back(m, DEG(90)) ? ACT_BACKWARD_ROLLOUT : ((m->forwardVel >= 0.0f) ? ACT_FORWARD_ROLLOUT : ACT_BACKWARD_ROLLOUT)), 0);
    }
#else
            return drop_and_set_mario_action(m, ((m->forwardVel >= 0.0f) ? ACT_FORWARD_ROLLOUT : ACT_BACKWARD_ROLLOUT), 0);
        }
    } else {
        m->actionTimer++;
    }
#endif
    if (update_sliding(m, 4.0f)) return set_mario_action(m, stopAction, 0);
    common_slide_action(m, stopAction, airAction, animation);
    return FALSE;
}

Bool32 act_stomach_slide(struct MarioState *m) {
    return stomach_slide_action(m, ACT_STOMACH_SLIDE_STOP, ACT_FREEFALL, MARIO_ANIM_SLIDE_DIVE);
}

Bool32 act_hold_stomach_slide(struct MarioState *m) {
    if (m->marioObj->oInteractStatus & INT_STATUS_MARIO_DROP_OBJECT) return drop_and_set_mario_action(m, ACT_STOMACH_SLIDE, 0);
    return stomach_slide_action(m, ACT_DIVE_PICKING_UP, ACT_HOLD_FREEFALL, MARIO_ANIM_SLIDE_DIVE);
}

Bool32 act_dive_slide(struct MarioState *m) {
#ifdef ACTION_CANCELS
    if (m->input & (INPUT_A_PRESSED | INPUT_B_PRESSED)) {
#else
    if (!(m->input & INPUT_ABOVE_SLIDE) && (m->input & (INPUT_A_PRESSED | INPUT_B_PRESSED))) {
#endif
#if ENABLE_RUMBLE
        queue_rumble_data(5, 80);
#endif
#ifdef ACTION_CANCELS
        return set_mario_action(m, (analog_stick_held_back(m, DEG(90)) ? ACT_BACKWARD_ROLLOUT : ((m->forwardVel > 0.0f) ? ACT_FORWARD_ROLLOUT : ACT_BACKWARD_ROLLOUT)), 0);
#else
        return set_mario_action(m, ((m->forwardVel > 0.0f) ? ACT_FORWARD_ROLLOUT : ACT_BACKWARD_ROLLOUT), 0);
#endif
    }
    play_mario_landing_sound_once(m, SOUND_ACTION_TERRAIN_BODY_HIT_GROUND);
    //! If the dive slide ends on the same frame that we pick up on object,
    // Mario will not be in the dive slide action for the call to
    // mario_check_object_grab, and so will end up in the regular picking action,
    // rather than the picking up after dive action.
    if (update_sliding(m, 8.0f) && is_anim_at_end(m)) {
        mario_set_forward_vel(m, 0.0f);
        set_mario_action(m, ACT_STOMACH_SLIDE_STOP, 0);
    }
    if (mario_check_object_grab(m)) {
        mario_grab_used_object(m);
        m->marioBodyState->grabPos = GRAB_POS_LIGHT_OBJ;
        return TRUE;
    }
    common_slide_action(m, ACT_STOMACH_SLIDE_STOP, ACT_FREEFALL, MARIO_ANIM_DIVE);
    return FALSE;
}

AnimFrame32 common_ground_knockback_action(struct MarioState *m, AnimID32 animation, AnimFrame32 checkFrame, Bool32 playLandingSound, s32 actionArg) {
    if (playLandingSound) play_mario_heavy_landing_sound_once(m, SOUND_ACTION_TERRAIN_BODY_HIT_GROUND);
    if (actionArg > 0) {
        play_sound_if_no_flag(m, SOUND_MARIO_ATTACKED, MARIO_MARIO_SOUND_PLAYED);
    } else {
#ifdef VERSION_JP
        play_sound_if_no_flag(m, SOUND_MARIO_OOOF, MARIO_MARIO_SOUND_PLAYED);
#else
        play_sound_if_no_flag(m, SOUND_MARIO_OOOF2, MARIO_MARIO_SOUND_PLAYED);
#endif
    }
    if (m->forwardVel >  32.0f) m->forwardVel =  32.0f;
    if (m->forwardVel < -32.0f) m->forwardVel = -32.0f;
    AnimFrame32 animFrame = set_mario_animation(m, animation);
    if (animFrame < checkFrame) {
        apply_landing_accel(m, 0.9f);
    } else if (m->forwardVel >= 0.0f) {
        mario_set_forward_vel(m,  0.1f);
    } else {
        mario_set_forward_vel(m, -0.1f);
    }
    if (perform_ground_step(m) == GROUND_STEP_LEFT_GROUND) {
        set_mario_action(m, ((m->forwardVel >= 0.0f) ? ACT_FORWARD_AIR_KB : ACT_BACKWARD_AIR_KB), actionArg);
    } else if (is_anim_at_end(m)) {
        if (m->health < 0x100) {
            set_mario_action(m, ACT_STANDING_DEATH, 0);
        } else {
            if (actionArg > 0) m->invincTimer = 30;
            set_mario_action(m, ACT_IDLE, 0);
        }
    }
    return animFrame;
}

Bool32 act_hard_backward_ground_kb(struct MarioState *m) {
    AnimFrame32 animFrame = common_ground_knockback_action(m, MARIO_ANIM_FALL_OVER_BACKWARDS, 43, TRUE, m->actionArg);
    if ((animFrame == 43) && (m->health < 0x100)) set_mario_action(m, ACT_DEATH_ON_BACK, 0);
#ifndef VERSION_JP
    if ((animFrame == 54) && (m->prevAction == ACT_SPECIAL_DEATH_EXIT)) play_sound(SOUND_MARIO_MAMA_MIA, m->marioObj->header.gfx.cameraToObject);
#endif
    if (animFrame == 69) play_mario_landing_sound_once(m, SOUND_ACTION_TERRAIN_LANDING);
    return FALSE;
}

Bool32 act_hard_forward_ground_kb(struct MarioState *m) {
    AnimFrame32 animFrame = common_ground_knockback_action(m, MARIO_ANIM_LAND_ON_STOMACH, 21, TRUE, m->actionArg);
    if ((animFrame == 23) && (m->health < 0x100)) set_mario_action(m, ACT_DEATH_ON_STOMACH, 0);
    return FALSE;
}

Bool32 act_backward_ground_kb(struct MarioState *m) {
    common_ground_knockback_action(m, MARIO_ANIM_BACKWARD_KB, 22, TRUE, m->actionArg);
    return FALSE;
}

Bool32 act_forward_ground_kb(struct MarioState *m) {
    common_ground_knockback_action(m, MARIO_ANIM_FORWARD_KB, 20, TRUE, m->actionArg);
    return FALSE;
}

Bool32 act_soft_backward_ground_kb(struct MarioState *m) {
    common_ground_knockback_action(m, MARIO_ANIM_SOFT_BACK_KB, 100, FALSE, m->actionArg);
    return FALSE;
}

Bool32 act_soft_forward_ground_kb(struct MarioState *m) {
    common_ground_knockback_action(m, MARIO_ANIM_SOFT_FRONT_KB, 100, FALSE, m->actionArg);
    return FALSE;
}

Bool32 act_ground_bonk(struct MarioState *m) {
    AnimFrame32 animFrame = common_ground_knockback_action(m, MARIO_ANIM_GROUND_BONK, 32, TRUE, m->actionArg);
    if (animFrame == 32) play_mario_landing_sound(m, SOUND_ACTION_TERRAIN_LANDING);
    return FALSE;
}

Bool32 act_death_exit_land(struct MarioState *m) {
    apply_landing_accel(m, 0.9f);
    play_mario_heavy_landing_sound_once(m, SOUND_ACTION_TERRAIN_BODY_HIT_GROUND);
    AnimFrame32 animFrame = set_mario_animation(m, MARIO_ANIM_FALL_OVER_BACKWARDS);
    if (animFrame == 54) play_sound(SOUND_MARIO_MAMA_MIA, m->marioObj->header.gfx.cameraToObject);
    if (animFrame == 68) play_mario_landing_sound(m, SOUND_ACTION_TERRAIN_LANDING);
    if (is_anim_at_end(m)) set_mario_action(m, ACT_IDLE, 0);
    return FALSE;
}

MarioStep common_landing_action(struct MarioState *m, AnimID16 animation, MarioAction airAction) {
    MarioStep stepResult;
    if (m->input & INPUT_NONZERO_ANALOG) {
        apply_landing_accel(m, 0.98f);
    } else if (m->forwardVel >= GROUND_SPEED_THRESHOLD) {
        apply_slope_decel(m, 2.0f);
    } else {
        m->vel[1] = 0.0f;
    }
#ifdef AIR_TURN
    if (m->forwardVel < 0.0f) m->forwardVel = 0.0f;
#endif
    stepResult = perform_ground_step(m);
    switch (stepResult) {
        case GROUND_STEP_LEFT_GROUND: set_mario_action(   m, airAction, 0);       break;
        case GROUND_STEP_HIT_WALL:    set_mario_animation(m, MARIO_ANIM_PUSHING); break;
    }
    if (m->forwardVel > GROUND_SPEED_THRESHOLD) m->particleFlags |= PARTICLE_DUST;
    set_mario_animation(m, animation);
    play_mario_landing_sound_once(m, SOUND_ACTION_TERRAIN_LANDING);
    if (m->floor && (m->floor->type >= SURFACE_SHALLOW_QUICKSAND) && (m->floor->type <= SURFACE_MOVING_QUICKSAND)) m->quicksandDepth += (((4 - m->actionTimer) * 3.5f) - 0.5f);
    return stepResult;
}

Bool32 common_landing_cancels(struct MarioState *m, struct LandingAction *landingAction, Bool32 (*setAPressAction)(struct MarioState *m, MarioAction action, u32 actionArg)) {
#ifdef ENABLE_DEBUG_FREE_MOVE
    if (gPlayer1Controller->buttonDown & U_JPAD) {
        set_camera_mode(m->area->camera, CAMERA_MODE_8_DIRECTIONS, 1);
        return set_mario_action(m, ACT_DEBUG_FREE_MOVE, 0);
    }
#endif
#ifdef ACTION_CANCELS
    if (m->input & INPUT_Z_PRESSED                  ) return set_mario_action(          m, ACT_CROUCH_SLIDE              , 0);
#endif
    if (m->input & INPUT_OFF_FLOOR                  ) return set_mario_action(          m, landingAction->offFloorAction , 0);
#ifdef FIX_RELATIVE_SLOPE_ANGLE_MOVEMENT
    if (m->steepness < COS73                        ) return mario_push_off_steep_floor(m, landingAction->verySteepAction, 0);
#else
    if (m->floor->normal.y < COS73                  ) return mario_push_off_steep_floor(m, landingAction->verySteepAction, 0);
#endif
    m->doubleJumpTimer = landingAction->doubleJumpTimer;
    if (should_begin_sliding(m)                     ) return set_mario_action(          m, landingAction->slideAction    , 0);
    if (m->input & INPUT_FIRST_PERSON               ) return set_mario_action(          m, landingAction->endAction      , 0);
    if (++m->actionTimer >= landingAction->numFrames) return set_mario_action(          m, landingAction->endAction      , 0);
    if (m->input & INPUT_A_PRESSED                  ) return setAPressAction(           m, landingAction->aPressedAction , 0);
#ifdef ACTION_CANCELS
    if (m->input & INPUT_B_PRESSED                  ) return set_mario_action(          m, ACT_MOVE_PUNCHING             , 0);
#endif
    return FALSE;
}

Bool32 act_jump_land(struct MarioState *m) {
    common_landing_action(m, MARIO_ANIM_LAND_FROM_SINGLE_JUMP, ACT_FREEFALL);
    return (common_landing_cancels(m, &sJumpLandAction, set_jumping_action));
}

Bool32 act_freefall_land(struct MarioState *m) {
    common_landing_action(m, MARIO_ANIM_GENERAL_LAND, ACT_FREEFALL);
    return (common_landing_cancels(m, &sFreefallLandAction, set_jumping_action));
}

Bool32 act_side_flip_land(struct MarioState *m) {
    if (common_landing_action(m, MARIO_ANIM_SLIDEFLIP_LAND, ACT_FREEFALL) != GROUND_STEP_HIT_WALL) m->marioObj->header.gfx.angle[1] += DEG(180);
    return (common_landing_cancels(m, &sSideFlipLandAction, set_jumping_action));
}

Bool32 act_hold_jump_land(struct MarioState *m) {
    if (m->marioObj->oInteractStatus & INT_STATUS_MARIO_DROP_OBJECT) return drop_and_set_mario_action(m, ACT_JUMP_LAND_STOP, 0);
    common_landing_action(m, MARIO_ANIM_JUMP_LAND_WITH_LIGHT_OBJ, ACT_HOLD_FREEFALL);
    return (common_landing_cancels(m, &sHoldJumpLandAction, set_jumping_action));
}

Bool32 act_hold_freefall_land(struct MarioState *m) {
    if (m->marioObj->oInteractStatus & INT_STATUS_MARIO_DROP_OBJECT) return drop_and_set_mario_action(m, ACT_FREEFALL_LAND_STOP, 0);
    common_landing_action(m, MARIO_ANIM_FALL_LAND_WITH_LIGHT_OBJ, ACT_HOLD_FREEFALL);
    return (common_landing_cancels(m, &sHoldFreefallLandAction, set_jumping_action));
}

Bool32 act_long_jump_land(struct MarioState *m) {
#if defined (VERSION_SH) || defined(DISABLE_BLJ)
    // BLJ (Backwards Long Jump) speed build up fix, crushing SimpleFlips's dreams since July 1997
    if (m->forwardVel < 0.0f) m->forwardVel = 0.0f;
#endif
#ifdef ACTION_CANCELS
    sLongJumpLandAction.aPressedAction = ((m->input & INPUT_Z_DOWN) ? ACT_LONG_JUMP : ACT_JUMP);
#else
    if (!(m->input & INPUT_Z_DOWN)) m->input &= ~INPUT_A_PRESSED;
#endif
    common_landing_action(m, !m->marioObj->oMarioLongJumpIsSlow ? MARIO_ANIM_CROUCH_FROM_FAST_LONGJUMP : MARIO_ANIM_CROUCH_FROM_SLOW_LONGJUMP, ACT_FREEFALL);
    if (common_landing_cancels(m, &sLongJumpLandAction, set_jumping_action)) return TRUE;
    if (!(m->input & INPUT_NONZERO_ANALOG)) play_sound_if_no_flag(m, SOUND_MARIO_UH_LONG_JUMP_LAND, MARIO_MARIO_SOUND_PLAYED);
    return FALSE;
}

Bool32 act_double_jump_land(struct MarioState *m) {
    common_landing_action(m, MARIO_ANIM_LAND_FROM_DOUBLE_JUMP, ACT_FREEFALL);
    return (common_landing_cancels(m, &sDoubleJumpLandAction, set_triple_jump_action));
}

Bool32 act_triple_jump_land(struct MarioState *m) {
    m->input &= ~INPUT_A_PRESSED;
    common_landing_action(m, MARIO_ANIM_TRIPLE_JUMP_LAND, ACT_FREEFALL);
    if (common_landing_cancels(m, &sTripleJumpLandAction, set_jumping_action)) return TRUE;
    if (!(m->input & INPUT_NONZERO_ANALOG)) play_sound_if_no_flag(m, SOUND_MARIO_HAHA, MARIO_MARIO_SOUND_PLAYED);
    return FALSE;
}

Bool32 act_backflip_land(struct MarioState *m) {
#ifdef ACTION_CANCELS
    sBackflipLandAction.aPressedAction = ((m->input & INPUT_Z_DOWN) ? ACT_BACKFLIP : ACT_JUMP);
#else
    if (!(m->input & INPUT_Z_DOWN)) m->input &= ~INPUT_A_PRESSED;
#endif
    common_landing_action(m, MARIO_ANIM_TRIPLE_JUMP_LAND, ACT_FREEFALL);
    if (common_landing_cancels(m, &sBackflipLandAction, set_jumping_action)) return TRUE;
    if (!(m->input & INPUT_NONZERO_ANALOG)) play_sound_if_no_flag(m, SOUND_MARIO_HAHA, MARIO_MARIO_SOUND_PLAYED);
    return FALSE;
}

Bool32 quicksand_jump_land_action(struct MarioState *m, AnimID32 animation1, AnimID32 animation2, MarioAction endAction, MarioAction airAction) {
    if (m->actionTimer++ < 6) {
        m->quicksandDepth -= ((7 - m->actionTimer) * 0.8f);
        if (m->quicksandDepth < 1.0f) m->quicksandDepth = 1.1f;
        play_mario_jump_sound(m);
        set_mario_animation(m, animation1);
    } else {
        if (m->actionTimer >= 13) return set_mario_action(m, endAction, 0);
        set_mario_animation(m, animation2);
    }
    apply_landing_accel(m, 0.95f);
    if (perform_ground_step(m) == GROUND_STEP_LEFT_GROUND) set_mario_action(m, airAction, 0);
    return FALSE;
}

Bool32 act_quicksand_jump_land(struct MarioState *m) {
    return quicksand_jump_land_action(m, MARIO_ANIM_SINGLE_JUMP,         MARIO_ANIM_LAND_FROM_SINGLE_JUMP,    ACT_JUMP_LAND_STOP,      ACT_FREEFALL);
}

Bool32 act_hold_quicksand_jump_land(struct MarioState *m) {
    return quicksand_jump_land_action(m, MARIO_ANIM_JUMP_WITH_LIGHT_OBJ, MARIO_ANIM_JUMP_LAND_WITH_LIGHT_OBJ, ACT_HOLD_JUMP_LAND_STOP, ACT_HOLD_FREEFALL);
}

Bool32 check_common_moving_cancels(struct MarioState *m) {
    if (m->pos[1] < (m->waterLevel - 100)                                 ) return set_water_plunge_action(  m);
    if (!(m->action & ACT_FLAG_INVULNERABLE) && (m->input & INPUT_STOMPED)) return drop_and_set_mario_action(m, ACT_SHOCKWAVE_BOUNCE, 0);
    if (m->input & INPUT_SQUISHED                                         ) return drop_and_set_mario_action(m, ACT_SQUISHED        , 0);
    if (!(m->action & ACT_FLAG_INVULNERABLE) && (m->health < 0x100)       ) return drop_and_set_mario_action(m, ACT_STANDING_DEATH  , 0);
    return FALSE;
}

Bool32 mario_execute_moving_action(struct MarioState *m) {
    Bool32 cancel;
    if (check_common_moving_cancels(m)  ) return TRUE;
    if (mario_update_quicksand(m, 0.25f)) return TRUE;
    /* clang-format off */
    switch (m->action) {
        case ACT_WALKING:                  cancel = act_walking(m);                  break;
        case ACT_HOLD_WALKING:             cancel = act_hold_walking(m);             break;
        case ACT_HOLD_HEAVY_WALKING:       cancel = act_hold_heavy_walking(m);       break;
        case ACT_TURNING_AROUND:           cancel = act_turning_around(m);           break;
        case ACT_FINISH_TURNING_AROUND:    cancel = act_finish_turning_around(m);    break;
        case ACT_BRAKING:                  cancel = act_braking(m);                  break;
        case ACT_RIDING_SHELL_GROUND:      cancel = act_riding_shell_ground(m);      break;
        case ACT_CRAWLING:                 cancel = act_crawling(m);                 break;
        case ACT_BURNING_GROUND:           cancel = act_burning_ground(m);           break;
        case ACT_DECELERATING:             cancel = act_decelerating(m);             break;
        case ACT_HOLD_DECELERATING:        cancel = act_hold_decelerating(m);        break;
        case ACT_BUTT_SLIDE:               cancel = act_butt_slide(m);               break;
        case ACT_STOMACH_SLIDE:            cancel = act_stomach_slide(m);            break;
        case ACT_HOLD_BUTT_SLIDE:          cancel = act_hold_butt_slide(m);          break;
        case ACT_HOLD_STOMACH_SLIDE:       cancel = act_hold_stomach_slide(m);       break;
        case ACT_DIVE_SLIDE:               cancel = act_dive_slide(m);               break;
        case ACT_MOVE_PUNCHING:            cancel = act_move_punching(m);            break;
        case ACT_CROUCH_SLIDE:             cancel = act_crouch_slide(m);             break;
        case ACT_SLIDE_KICK_SLIDE:         cancel = act_slide_kick_slide(m);         break;
        case ACT_HARD_BACKWARD_GROUND_KB:  cancel = act_hard_backward_ground_kb(m);  break;
        case ACT_HARD_FORWARD_GROUND_KB:   cancel = act_hard_forward_ground_kb(m);   break;
        case ACT_BACKWARD_GROUND_KB:       cancel = act_backward_ground_kb(m);       break;
        case ACT_FORWARD_GROUND_KB:        cancel = act_forward_ground_kb(m);        break;
        case ACT_SOFT_BACKWARD_GROUND_KB:  cancel = act_soft_backward_ground_kb(m);  break;
        case ACT_SOFT_FORWARD_GROUND_KB:   cancel = act_soft_forward_ground_kb(m);   break;
        case ACT_GROUND_BONK:              cancel = act_ground_bonk(m);              break;
        case ACT_DEATH_EXIT_LAND:          cancel = act_death_exit_land(m);          break;
        case ACT_JUMP_LAND:                cancel = act_jump_land(m);                break;
        case ACT_FREEFALL_LAND:            cancel = act_freefall_land(m);            break;
        case ACT_DOUBLE_JUMP_LAND:         cancel = act_double_jump_land(m);         break;
        case ACT_SIDE_FLIP_LAND:           cancel = act_side_flip_land(m);           break;
        case ACT_HOLD_JUMP_LAND:           cancel = act_hold_jump_land(m);           break;
        case ACT_HOLD_FREEFALL_LAND:       cancel = act_hold_freefall_land(m);       break;
        case ACT_TRIPLE_JUMP_LAND:         cancel = act_triple_jump_land(m);         break;
        case ACT_BACKFLIP_LAND:            cancel = act_backflip_land(m);            break;
        case ACT_QUICKSAND_JUMP_LAND:      cancel = act_quicksand_jump_land(m);      break;
        case ACT_HOLD_QUICKSAND_JUMP_LAND: cancel = act_hold_quicksand_jump_land(m); break;
        case ACT_LONG_JUMP_LAND:           cancel = act_long_jump_land(m);           break;
        default:                           cancel = act_walking(m);                  break;
    }
    /* clang-format on */
    if (!cancel && (m->input & INPUT_IN_WATER)) {
        m->particleFlags |=  PARTICLE_WAVE_TRAIL;
        m->particleFlags &= ~PARTICLE_DUST;
    }
    return cancel;
}
