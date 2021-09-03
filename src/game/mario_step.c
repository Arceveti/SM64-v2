#include <ultra64.h>

#include "sm64.h"
#include "engine/math_util.h"
#include "engine/surface_collision.h"
#include "mario.h"
#include "audio/external.h"
#include "boot/game_init.h"
#include "interaction.h"
#include "mario_step.h"

#include "config.h"

static s16 sMovingSandSpeeds[] = { 12, 8, 4, 0 };

struct Surface gWaterSurfacePseudoFloor = {
    SURFACE_VERY_SLIPPERY, // type
    0,                     // force
    0,                     // flags
    0,                     // room
    -5, 5,                 // lowerY, upperY
    { 0, 0, 0 },           // vertex1
    { 0, 0, 0 },           // vertex2
    { 0, 0, 0 },           // vertex3
    { 0.0f, 1.0f, 0.0f },  // normal
    0.0f,                  // originOffset
    NULL,                  // object
};

// static struct Object *sTrampoline;

/**
 * Always returns zero. This may have been intended
 * to be used for the beta trampoline. Its return value
 * is used by set_mario_y_vel_based_on_fspeed as a constant
 * addition to Mario's Y velocity. Given the closeness of
 * this function to stub_mario_step_2, it is probable that this
 * was intended to check whether a trampoline had made itself
 * known through stub_mario_step_2 and whether Mario was on it,
 * and if so return a higher value than 0.
 */
f32 get_additive_y_vel_for_jumps(void) {
    // return (sTrampoline != NULL) ? sTrampoline->oBetaTrampolineAdditiveYVel : 0.0f;
    return 0.0f;
}

/**
 * Does nothing, but takes in a MarioState. This is only ever
 * called by update_mario_inputs, which is called as part of Mario's
 * update routine. Due to its proximity to stub_mario_step_2, an
 * incomplete trampoline function, and get_additive_y_vel_for_jumps,
 * a potentially trampoline-related function, it is plausible that
 * this could be used for checking if Mario was on the trampoline.
 * It could, for example, make him bounce.
 */
void stub_mario_step_1(UNUSED struct MarioState *m) {
}

/**
 * Does nothing. This is only called by the beta trampoline.
 * Due to its proximity to get_additive_y_vel_for_jumps, another
 * currently-pointless function, it is probable that this was used
 * by the trampoline to make itself known to get_additive_y_vel_for_jumps,
 * or to set a variable with its intended additive Y vel.
 */
void stub_mario_step_2(void) {
    // sTrampoline = gCurrentObject;
}

void transfer_bully_speed(struct BullyCollisionData *obj1, struct BullyCollisionData *obj2) {
    f32 rx = (obj2->posX - obj1->posX);
    f32 rz = (obj2->posZ - obj1->posZ);
    //! Bully NaN crash
    f32 projectedV1 = ((( rx * obj1->velX) + (rz * obj1->velZ)) / ((rx * rx) + (rz * rz)));
    f32 projectedV2 = (((-rx * obj2->velX) - (rz * obj2->velZ)) / ((rx * rx) + (rz * rz)));
    // Kill speed along r. Convert one object's speed along r and transfer it to
    // the other object.
    obj2->velX += ((obj2->conversionRatio * projectedV1 * rx) - ( projectedV2 * -rx));
    obj2->velZ += ((obj2->conversionRatio * projectedV1 * rz) - ( projectedV2 * -rz));
    obj1->velX += ((-projectedV1 * rx) + (obj1->conversionRatio * projectedV2 * -rx));
    obj1->velZ += ((-projectedV1 * rz) + (obj1->conversionRatio * projectedV2 * -rz));

    //! Bully battery
}

void init_bully_collision_data(struct BullyCollisionData *data, f32 posX, f32 posZ, f32 forwardVel, Angle yaw, f32 conversionRatio, f32 radius) {
    if (forwardVel < 0.0f) {
        forwardVel *= -1.0f;
        yaw        += DEG(180);
    }
    data->radius          = radius;
    data->conversionRatio = conversionRatio;
    data->posX            = posX;
    data->posZ            = posZ;
    data->velX            = (forwardVel * sins(yaw));
    data->velZ            = (forwardVel * coss(yaw));
}

void mario_bonk_reflection(struct MarioState *m, u32 negateSpeed) {
    if (m->wall != NULL) {
        m->faceAngle[1] = (m->wallYaw - (Angle)(m->faceAngle[1] - m->wallYaw));
        play_sound((m->flags & MARIO_METAL_CAP) ? SOUND_ACTION_METAL_BONK : SOUND_ACTION_BONK, m->marioObj->header.gfx.cameraToObject);
    } else {
        play_sound(SOUND_ACTION_HIT, m->marioObj->header.gfx.cameraToObject);
    }
    if (negateSpeed) {
        mario_set_forward_vel(m, -m->forwardVel);
    } else {
        m->faceAngle[1] += DEG(180);
    }
}

Bool32 mario_update_quicksand(struct MarioState *m, f32 sinkingSpeed) {
    if ((m->action & ACT_FLAG_RIDING_SHELL) || (m->pos[1] > m->floorHeight)) {
        m->quicksandDepth = 0.0f;
    } else {
        if (m->quicksandDepth < 1.1f) m->quicksandDepth = 1.1f;
        switch (m->floor->type) {
            case SURFACE_SHALLOW_QUICKSAND:         if ((m->quicksandDepth += sinkingSpeed) >= 10.0f) m->quicksandDepth = 10.0f; break;
            case SURFACE_SHALLOW_MOVING_QUICKSAND:  if ((m->quicksandDepth += sinkingSpeed) >= 25.0f) m->quicksandDepth = 25.0f; break;
            case SURFACE_QUICKSAND:                 // fall through
            case SURFACE_MOVING_QUICKSAND:          if ((m->quicksandDepth += sinkingSpeed) >= 60.0f) m->quicksandDepth = 60.0f; break;
            case SURFACE_DEEP_QUICKSAND:            // fall through
            case SURFACE_DEEP_MOVING_QUICKSAND:
                if ((m->quicksandDepth += sinkingSpeed) >= MARIO_HITBOX_HEIGHT) {
                    update_mario_sound_and_camera(m);
                    return drop_and_set_mario_action(m, ACT_QUICKSAND_DEATH, 0);
                }
                break;
            case SURFACE_INSTANT_QUICKSAND: // fall through
            case SURFACE_INSTANT_MOVING_QUICKSAND:
                update_mario_sound_and_camera(m);
                return drop_and_set_mario_action(m, ACT_QUICKSAND_DEATH, 0);
                break;
            default: m->quicksandDepth = 0.0f; break;
        }
    }
    return FALSE;
}

Bool32 mario_push_off_steep_floor(struct MarioState *m, MarioAction action, u32 actionArg) {
    if (abs_angle_diff(m->floorYaw, m->faceAngle[1]) < DEG(90)) {
        m->forwardVel   =  16.0f; // * (1.0f-m->floor->normal.y);
        m->faceAngle[1] = m->floorYaw;
    } else {
        m->forwardVel   = -16.0f; // * (1.0f-m->floor->normal.y);
        m->faceAngle[1] = (m->floorYaw + DEG(180));
    }
    return set_mario_action(m, action, actionArg);
}

Bool32 mario_update_moving_sand(struct MarioState *m) {
    struct Surface *floor = m->floor;
    SurfaceType floorType = floor->type;
    if ((floorType == SURFACE_DEEP_MOVING_QUICKSAND)
     || (floorType == SURFACE_SHALLOW_MOVING_QUICKSAND)
     || (floorType == SURFACE_MOVING_QUICKSAND)
     || (floorType == SURFACE_INSTANT_MOVING_QUICKSAND)) {
        Angle pushAngle = (floor->force << 8);
        f32 pushSpeed = sMovingSandSpeeds[floor->force >> 8];
        m->vel[0] += (pushSpeed * sins(pushAngle));
        m->vel[2] += (pushSpeed * coss(pushAngle));
        return TRUE;
    }
    return FALSE;
}

Bool32 mario_update_windy_ground(struct MarioState *m) {
    struct Surface *floor = m->floor;
    if (floor->type == SURFACE_HORIZONTAL_WIND) {
        f32 pushSpeed;
        Angle pushAngle = (floor->force << 8);
        if (m->action & ACT_FLAG_MOVING) {
            Angle pushDYaw = (m->faceAngle[1] - pushAngle);
            pushSpeed = ((m->forwardVel > 0.0f) ? (-m->forwardVel * 0.5f) : -8.0f);
            if ((pushDYaw > -DEG(90)) && (pushDYaw < DEG(90))) pushSpeed *= -1.0f;
            pushSpeed *= coss(pushDYaw);
        } else {
            pushSpeed = (3.2f + (gGlobalTimer & 0x3));
        }
        m->vel[0] += (pushSpeed * sins(pushAngle));
        m->vel[2] += (pushSpeed * coss(pushAngle));
#ifdef VERSION_JP
        play_sound(SOUND_ENV_WIND2, m->marioObj->header.gfx.cameraToObject);
#endif
        return TRUE;
    }
    return FALSE;
}

void stop_and_set_height_to_floor(struct MarioState *m) {
    struct Object *marioObj = m->marioObj;
    mario_set_forward_vel(m, 0.0f);
    m->vel[1] = 0.0f;
    //? This is responsible for some downwarps.
    if (m->pos[1] < (m->floorHeight + MARIO_STEP_HEIGHT)) m->pos[1] = m->floorHeight;
    vec3f_copy(marioObj->header.gfx.pos, m->pos);
    vec3a_set( marioObj->header.gfx.angle, 0x0, m->faceAngle[1], 0x0);
}

MarioStep stationary_ground_step(struct MarioState *m) {
    mario_set_forward_vel(m, 0.0f);
#ifdef STATIONARY_GROUND_STEPS
    mario_update_moving_sand(m);
    mario_update_windy_ground(m);
    return perform_ground_step(m);
#else
    struct Object *marioObj = m->marioObj;
    MarioStep stepResult = GROUND_STEP_NONE;
    Bool32 takeStep;
    takeStep  = mario_update_moving_sand(m);
    takeStep |= mario_update_windy_ground(m);
    if (takeStep) {
        stepResult = perform_ground_step(m);
    } else {
        if (m->pos[1] < (m->floorHeight + MARIO_STEP_HEIGHT)) m->pos[1] = m->floorHeight;
        vec3f_copy(marioObj->header.gfx.pos, m->pos);
        vec3a_set( marioObj->header.gfx.angle, 0x0, m->faceAngle[1], 0x0);
    }
    return stepResult;
#endif
}

static MarioStep perform_ground_quarter_step(struct MarioState *m, Vec3f nextPos) {
    struct WallCollisionData lowerWall, upperWall;
    s16 i;
    Angle wallDYaw, oldWallDYaw;
    struct Surface *ceil, *floor;
    f32 ceilHeight, floorHeight, waterLevel;
#if NULL_FLOOR_STEPS > 0
    u32 missedFloors = 0;
    Vec3f startPos;
#endif
    // Check for walls
    resolve_and_return_wall_collisions(nextPos, 30.0f, 24.0f, &lowerWall);
    resolve_and_return_wall_collisions(nextPos, 60.0f, 50.0f, &upperWall);
    // Check for a floor
    floorHeight = find_floor(nextPos[0], (nextPos[1] + m->midY), nextPos[2], &floor);
    // m->wall     = NULL;
#if NULL_FLOOR_STEPS > 0
    // Save the current position in case the next position is a null floor
    vec3f_copy(startPos, nextPos);
    // Check for null floors
    while ((floor == NULL) && (missedFloors < NULL_FLOOR_STEPS)) {
#ifdef FIX_RELATIVE_SLOPE_ANGLE_MOVEMENT
        nextPos[0] += (m->steepness * (m->vel[0] / AIR_NUM_STEPS));
        nextPos[2] += (m->steepness * (m->vel[2] / AIR_NUM_STEPS));
#else
        nextPos[0] += (m->floor->normal.y * (m->vel[0] / AIR_NUM_STEPS));
        nextPos[2] += (m->floor->normal.y * (m->vel[2] / AIR_NUM_STEPS));
#endif
        resolve_and_return_wall_collisions(nextPos, 30.0f, 24.0f, &lowerWall);
        resolve_and_return_wall_collisions(nextPos, 60.0f, 50.0f, &upperWall);
        floorHeight = find_floor(nextPos[0], (nextPos[1] + m->midY), nextPos[2], &floor);
        missedFloors++;
    }
#endif
    // Check for ceilings in the new position
    ceilHeight = find_ceil(nextPos[0], (nextPos[1] + m->midY), nextPos[2], &ceil);
    waterLevel = find_water_level(nextPos[0], nextPos[2]);
    // If the next floor is null, return to the first position
    if (floor == NULL) {
#if NULL_FLOOR_STEPS > 0
        vec3f_copy(nextPos, startPos);
        ceilHeight = find_ceil(nextPos[0], (nextPos[1] + m->midY), nextPos[2], &ceil);
        waterLevel = find_water_level(nextPos[0], nextPos[2]);
#endif
        return GROUND_STEP_HIT_WALL_STOP_QSTEPS;
    }
    // When riding a shell on water, make a fake floor on the surface
    if ((m->action & ACT_FLAG_RIDING_SHELL) && (floorHeight < waterLevel)) {
        floorHeight         = waterLevel;
        floor               = &gWaterSurfacePseudoFloor;
        floor->originOffset = -floorHeight;
    }
    // Walking off a ledge
    if (nextPos[1] > (floorHeight + MARIO_STEP_HEIGHT)) {
#ifdef LEDGE_PROTECTION
        // Prevent some cases of slipping off ledges
        if ((m->input & INPUT_NONZERO_ANALOG)
         && (m->forwardVel < 32.0f)
         && !(m->action & ACT_FLAG_SHORT_HITBOX)
         && !(m->action & ACT_FLAG_BUTT_OR_STOMACH_SLIDE)
         && (mario_get_floor_class(m) != SURFACE_CLASS_VERY_SLIPPERY)
         && analog_stick_held_back(m, DEG(100))) return GROUND_STEP_NONE;
#endif
        // If Mario walks into a ceiling, fall down or stop moving
        if ((nextPos[1] + m->marioObj->hitboxHeight) >= ceilHeight) {
            if (nextPos[1] > floorHeight) {
#if COYOTE_TIME > 0
                m->coyoteTimer = 0;
#endif
                return GROUND_STEP_LEFT_GROUND;
            } else {
                return GROUND_STEP_HIT_WALL_STOP_QSTEPS;
            }
        }
        // Set Mario's position and floor
        vec3f_copy(m->pos, nextPos);
        if (m->floor != floor) m->floorYaw = atan2s(floor->normal.z, floor->normal.x);
        m->floor       = floor;
        m->floorHeight = floorHeight;
#if COYOTE_TIME > 0
        // Coyote Time - Consider Mario as still being on the ground for a few frames after walking off a ledge
        if (m->coyoteTimer++ < COYOTE_TIME) {
            return GROUND_STEP_NONE;
        } else {
            m->coyoteTimer = 0;
            return GROUND_STEP_LEFT_GROUND;
        }
    }
    // If Mario has not left the ground, reset the coyote timer
    m->coyoteTimer = 0;
#else
        return GROUND_STEP_LEFT_GROUND;
    }
#endif
#ifdef FIX_RELATIVE_SLOPE_ANGLE_MOVEMENT
    if ((m->pos[1] <= (m->floorHeight + MARIO_STEP_HEIGHT)) && (nextPos[1] <= (floorHeight + MARIO_STEP_HEIGHT))) {
        f32 dist;
        vec3f_get_lateral_dist(m->pos, nextPos, &dist);
        // if not moving, use the floor's y normal like in vanilla
        m->steepness = ((dist == 0.0f) ? (floor->normal.y) : coss(atan2s(dist, (floorHeight - m->floorHeight)))); //! normalize instead?
    } else {
        // If doing ground steps in air (Coyote Time), assume a flat floor
        m->steepness  = 1.0f;
    }
#endif
#ifdef BETTER_CEILING_HANDLING
    // Handle getting stuck between a sloped floor/ceiling
    if (((nextPos[1] + m->marioObj->hitboxHeight) > ceilHeight) && (floorHeight < ceilHeight)) {
        // softlock fix
        Angle surfAngle;
        Bool32 underSteepSurf = FALSE;
        if ((floor != NULL) && (ceil != NULL)) {
            if (floor->normal.y < COS25) { surfAngle = atan2s(floor->normal.z, floor->normal.x); underSteepSurf = TRUE; } // steep floor
            if (-COS25 < ceil->normal.y) { surfAngle = atan2s( ceil->normal.z,  ceil->normal.x); underSteepSurf = TRUE; } // steep ceiling
        }
        // Push mario away from the surfaces
        if (underSteepSurf) {
            m->vel[0]  = (sins(surfAngle) * 10.0f);
            m->vel[2]  = (coss(surfAngle) * 10.0f);
            m->pos[0] += m->vel[0];
            m->pos[2] += m->vel[2];
            if ((m->pos[1] > m->floorHeight) && (m->pos[1] < (m->floorHeight + m->marioObj->hitboxHeight))) m->pos[1] = m->floorHeight;
        }
        return GROUND_STEP_HIT_WALL_STOP_QSTEPS;
    }
#else
    if ((floorHeight + MARIO_HITBOX_HEIGHT) >= ceilHeight) return GROUND_STEP_HIT_WALL_STOP_QSTEPS;
#endif
    // Set mario's height to the floor
    vec3f_set(m->pos, nextPos[0], floorHeight, nextPos[2]);
    if (!SURFACE_IS_QUICKSAND(floor->type) && (floor->type != SURFACE_BURNING)) vec3f_copy(m->lastSafePos, m->pos);
    if (m->floor != floor) m->floorYaw = atan2s(floor->normal.z, floor->normal.x);
    m->floor       = floor;
    m->floorHeight = floorHeight;
    if (m->wall != NULL) {
        oldWallDYaw = abs_angle_diff(atan2s(m->wall->normal.z, m->wall->normal.x), m->faceAngle[1]);
    } else {
        oldWallDYaw = 0x0;
    }
    if (upperWall.numWalls == 0) {
        m->wall = NULL;
    } else {
        for ((i = 0); (i < upperWall.numWalls); (i++)) {
            wallDYaw = abs_angle_diff(atan2s(upperWall.walls[i]->normal.z, upperWall.walls[i]->normal.x), m->faceAngle[1]);
            if (wallDYaw >= oldWallDYaw) {
                oldWallDYaw = wallDYaw;
                m->wall     = upperWall.walls[i];
            }
            if ((wallDYaw >= DEG(60)) && (wallDYaw <= DEG(120))) continue; //! what's the first 60 degrees check for?
            return GROUND_STEP_HIT_WALL_CONTINUE_QSTEPS;
        }
    }
    return GROUND_STEP_NONE;
}

MarioStep perform_ground_step(struct MarioState *m) {
    Vec3f intendedPos;
    MarioStep stepResult = GROUND_STEP_NONE;
//     m->wall = NULL;
#ifdef FIX_RELATIVE_SLOPE_ANGLE_MOVEMENT
    f32 steepness = m->steepness;
#else
    f32 steepness = m->floor->normal.y;
#endif
#if GROUND_NUM_STEPS > 1
 #ifdef VARIABLE_STEPS
    const f32 speed    = (m->moveSpeed / 8.0f);
    const f32 numSteps = MAX(GROUND_NUM_STEPS, speed);
 #else
    const f32 numSteps = GROUND_NUM_STEPS;
 #endif
    s32 i;
    for ((i = 0); (i < numSteps); (i++)) {
        intendedPos[0] = (m->pos[0] + (steepness * (m->vel[0] / numSteps)));
        intendedPos[2] = (m->pos[2] + (steepness * (m->vel[2] / numSteps)));
        intendedPos[1] =  m->pos[1];
        stepResult = perform_ground_quarter_step(m, intendedPos);
        if ((stepResult == GROUND_STEP_LEFT_GROUND) || (stepResult == GROUND_STEP_HIT_WALL_STOP_QSTEPS)) break;
    }
#else
    // Step once
    intendedPos[0] = (m->pos[0] + (steepness * m->vel[0]));
    intendedPos[2] = (m->pos[2] + (steepness * m->vel[2]));
    intendedPos[1] =  m->pos[1];
    stepResult     = perform_ground_quarter_step(m, intendedPos);
#endif
    m->terrainSoundAddend = mario_get_terrain_sound_addend(m);
    vec3f_copy(m->marioObj->header.gfx.pos, m->pos);
    vec3a_set( m->marioObj->header.gfx.angle, 0x0, m->faceAngle[1], 0x0);
    if (stepResult == GROUND_STEP_HIT_WALL_CONTINUE_QSTEPS) stepResult = GROUND_STEP_HIT_WALL;
#ifdef WALL_QUICKSAND
    // Handle wall quicksand
    if ((stepResult == GROUND_STEP_HIT_WALL) && (m->wall) && (m->wall->type == SURFACE_INSTANT_QUICKSAND)) {
        stepResult = GROUND_STEP_DEATH;
        m->vel[0] = (-2.0f * m->wall->normal.x);
        m->vel[1] = (-2.0f * m->wall->normal.y);
        m->vel[2] = (-2.0f * m->wall->normal.z);
        drop_and_set_mario_action(m, ACT_QUICKSAND_DEATH, 1);
        return stepResult;
    }
#endif
    return stepResult;
}

struct Surface *check_ledge_grab(struct MarioState *m, struct Surface *grabbedWall, struct Surface *wall, Vec3f intendedPos, Vec3f nextPos, Vec3f ledgePos, struct Surface **ledgeFloor) {
    struct Surface *returnedWall = wall;
    if ((m->vel[1] > 0.0f) || (wall == NULL)) return FALSE;
    if ((m->action == ACT_WALL_SLIDE)
     || (m->action == ACT_FORWARD_ROLLOUT)
     || (m->action == ACT_BACKWARD_ROLLOUT)
     || analog_stick_held_back(m, DEG(90))) return FALSE;
    if (grabbedWall == NULL) grabbedWall = wall;
    //! find better wall angle?
    // Return the already grabbed wall if Mario is moving into it more than the newly tested wall
    if (((grabbedWall->normal.x * m->vel[0]) + (grabbedWall->normal.z * m->vel[2])) < ((wall->normal.x * m->vel[0]) + (wall->normal.z * m->vel[2]))) returnedWall = grabbedWall;
    f32 displacementX = (nextPos[0] - intendedPos[0]);
    f32 displacementZ = (nextPos[2] - intendedPos[2]);
    // Only ledge grab if the wall displaced Mario in the opposite direction of
    // his velocity.
    if (((displacementX * m->vel[0]) + (displacementZ * m->vel[2])) > 0.0f) returnedWall = grabbedWall;
    ledgePos[0] = (nextPos[0] - (wall->normal.x * 60.0f));
    ledgePos[2] = (nextPos[2] - (wall->normal.z * 60.0f));
    ledgePos[1] = find_floor(ledgePos[0], (nextPos[1] + m->midY + MARIO_SHORT_HITBOX_HEIGHT), ledgePos[2], ledgeFloor);
    if ((ledgeFloor == NULL)
     || (ledgePos[1] < (nextPos[1] + 80.0f))
     || ((*ledgeFloor)->normal.y < COS25)
     || ((*ledgeFloor)->type == SURFACE_BURNING)
     || SURFACE_IS_QUICKSAND((*ledgeFloor)->type)) return FALSE;
    // if (ledgePos[1] <= (nextPos[1] + MARIO_SHORT_HITBOX_HEIGHT)) returnedWall = grabbedWall;
    return returnedWall;
}

s32 bonk_or_hit_lava_wall(struct MarioState *m, struct WallCollisionData *wallData) {
    s16 i;
    s32 result = AIR_STEP_NONE;
    Angle wallDYaw;
    Angle oldWallDYaw = ((m->wall != NULL) ? abs_angle_diff(atan2s(m->wall->normal.z, m->wall->normal.x), m->faceAngle[1]) : 0x0);
    if (wallData->numWalls == 0) {
        m->wall = NULL;
    } else {
        for ((i = 0); (i < wallData->numWalls); (i++)) {
            if (wallData->walls[i] != NULL) {
                if (wallData->walls[i]->type == SURFACE_BURNING) {
                    m->wall = wallData->walls[i];
                    return AIR_STEP_HIT_LAVA_WALL;
                }
                wallDYaw = abs_angle_diff(atan2s(wallData->walls[i]->normal.z, wallData->walls[i]->normal.x), m->faceAngle[1]);
                // Update wall reference (bonked wall) only if the new wall has a better facing angle
                if (wallDYaw >= oldWallDYaw) {
                    oldWallDYaw = wallDYaw;
                    m->wall     = wallData->walls[i];
#ifdef WALL_SLIDE
                    if ((wallDYaw > DEG(180 - WALL_KICK_DEGREES)) && (m->vel[1] <= 0.0f)) {
#else
                    if (wallDYaw > DEG(180 - WALL_KICK_DEGREES)) {
#endif
                        m->flags |= MARIO_AIR_HIT_WALL;
                        result = AIR_STEP_HIT_WALL;
                    }
                }
            }
        }
    }
    return result;
}

MarioStep perform_air_quarter_step(struct MarioState *m, Vec3f intendedPos, u32 stepArg) {
#ifdef BETTER_CEILING_HANDLING
    f32 ceilSteepness;
#endif
#if NULL_FLOOR_STEPS > 0
    u32 missedFloors = 0;
    // Vec3f startPos;
#endif
    Vec3f nextPos;
    struct Surface *ceil, *floor;
    f32 ceilHeight, floorHeight, waterLevel;
    vec3f_copy(nextPos, intendedPos);
    s16 i;
    MarioStep stepResult = AIR_STEP_NONE;
    struct WallCollisionData upperWall, lowerWall;
    Vec3f ledgePos;
    struct Surface *grabbedWall = NULL;
    struct Surface *ledgeFloor;
    m->wall = NULL;
    resolve_and_return_wall_collisions(nextPos, 150.0f, 50.0f, &upperWall);
    resolve_and_return_wall_collisions(nextPos,  30.0f, 50.0f, &lowerWall);
    floorHeight = find_floor(nextPos[0], (nextPos[1] + m->midY), nextPos[2], &floor);
#if NULL_FLOOR_STEPS > 0
    // vec3f_copy(startPos, nextPos); // why does this crash the game when ledge grabbing?
    while ((floor == NULL) && (missedFloors < NULL_FLOOR_STEPS)) {
        nextPos[0] += (m->vel[0] / GROUND_NUM_STEPS);
        nextPos[2] += (m->vel[2] / GROUND_NUM_STEPS);
        resolve_and_return_wall_collisions(nextPos, 150.0f, 50.0f, &upperWall);
        resolve_and_return_wall_collisions(nextPos,  30.0f, 50.0f, &lowerWall);
        floorHeight = find_floor(nextPos[0], (nextPos[1] + m->midY), nextPos[2], &floor);
        missedFloors++;
    }
#endif
    ceilHeight = find_ceil(nextPos[0], (nextPos[1] + m->midY), nextPos[2], &ceil);
    waterLevel = find_water_level(nextPos[0], nextPos[2]);
    //! The water pseudo floor is not referenced when your intended qstep is
    // out of bounds, so it won't detect you as landing.
    if (floor == NULL) {
        if (nextPos[1] <= m->floorHeight) {
            m->pos[1] = m->floorHeight;
            return AIR_STEP_LANDED;
        }
        m->pos[1] = nextPos[1];
        return AIR_STEP_HIT_WALL;
    }
    if ((m->action & ACT_FLAG_RIDING_SHELL) && (floorHeight < waterLevel)) {
        floorHeight         = waterLevel;
        floor               = &gWaterSurfacePseudoFloor;
        floor->originOffset = -floorHeight;
    }
    //! This check uses f32, but findFloor uses short (overflow jumps)
    if (nextPos[1] <= floorHeight) {
        if ((ceilHeight - floorHeight) > m->marioObj->hitboxHeight) {
            m->pos[0]      = nextPos[0];
            m->pos[2]      = nextPos[2];
            if (m->floor != floor) m->floorYaw = atan2s(floor->normal.z, floor->normal.x);
            m->floor       = floor;
            m->floorHeight = floorHeight;
        }
        //! When ceilHeight - floorHeight <= 160, the step result says that
        // Mario landed, but his movement is cancelled and his referenced floor
        // isn't updated (pedro spots)
        m->pos[1]      = floorHeight;
        if (m->floor != floor) m->floorYaw = atan2s(floor->normal.z, floor->normal.x);
        m->floor       = floor;
        m->floorHeight = floorHeight;
#ifdef FIX_RELATIVE_SLOPE_ANGLE_MOVEMENT
        m->steepness  = floor->normal.y;
#endif
        return AIR_STEP_LANDED;
    }
#ifdef BETTER_CEILING_HANDLING
    if ((ceil != NULL) && ((nextPos[1] + MARIO_HITBOX_HEIGHT) > ceilHeight)) {
        if (floorHeight > nextPos[1]) return AIR_STEP_HIT_WALL;
        if ((m->vel[1] >= 0.0f) && !(m->prevAction & ACT_FLAG_HANGING) && (ceil->type == SURFACE_HANGABLE)) {
            m->vel[1]   = 0.0f;
            return AIR_STEP_GRABBED_CEILING;
        }
        if (-COS25 >= ceil->normal.y) {
            if (m->vel[1] > 0.0f) m->vel[1] = 0.0f;
        } else {
            ceilSteepness = sqrtf(sqr(ceil->normal.x) + sqr(ceil->normal.z));
            if (abs_angle_diff(atan2s(ceil->normal.z,  ceil->normal.x), m->marioObj->oMoveAngleYaw) <= DEG(90)) {
                if (m->vel[1] > 0.0f) {
                    m->slideVelX += (ceil->normal.x * m->vel[1] * ceilSteepness);
                    m->slideVelZ += (ceil->normal.z * m->vel[1] * ceilSteepness);
                    m->vel[0]    += m->slideVelX;
                    m->vel[2]    += m->slideVelZ;
                    m->vel[1]    *= (1.0f + ceil->normal.y);
                }
            } else if (m->vel[1] > 0.0f) {
                m->vel[1] = 0.0f;
            }
        }
        nextPos[1] = (ceilHeight - MARIO_HITBOX_HEIGHT);
        vec3f_copy(m->pos, nextPos);
        if (m->floor != floor) m->floorYaw = atan2s(floor->normal.z, floor->normal.x);
        m->floor       = floor;
        m->floorHeight = floorHeight;
        return AIR_STEP_HIT_CEILING; // or AIR_STEP_NONE?
    }
#else
    if ((nextPos[1] + MARIO_HITBOX_HEIGHT) > ceilHeight) {
        if (m->vel[1] >= 0.0f) {
            m->vel[1]  = 0.0f;
            //! Uses referenced ceiling instead of ceil (ceiling hang upwarp)
 #ifdef HANGING_FIX
            if ((m->ceil != NULL) && (m->ceil->type == SURFACE_HANGABLE)) {
 #else
            if ((stepArg & AIR_STEP_CHECK_HANG) && (m->ceil != NULL) && (m->ceil->type == SURFACE_HANGABLE)) {
 #endif
                return AIR_STEP_GRABBED_CEILING;
            }
            return AIR_STEP_NONE;
        }
        //! Potential subframe downwarp->upwarp?
        if (nextPos[1] <= m->floorHeight) {
            m->pos[1] = m->floorHeight;
            return AIR_STEP_LANDED;
        }
        m->pos[1] = nextPos[1];
        return AIR_STEP_HIT_CEILING;
    }
#endif
    //! When the wall is not completely vertical or there is a slight wall
    // misalignment, you can activate these conditions in unexpected situations
    if ((stepArg & AIR_STEP_CHECK_LEDGE_GRAB) && (upperWall.numWalls == 0) && (lowerWall.numWalls != 0)) {
        for ((i = 0); (i < lowerWall.numWalls); (i++)) if ((grabbedWall = check_ledge_grab(m, grabbedWall, lowerWall.walls[i], intendedPos, nextPos, ledgePos, &ledgeFloor)) != NULL) stepResult = AIR_STEP_GRABBED_LEDGE;
        if ((stepResult == AIR_STEP_GRABBED_LEDGE) && (grabbedWall != NULL) && (ledgeFloor != NULL) && (ledgePos != NULL)) {
            vec3f_copy(m->pos, ledgePos);
            m->floor        = ledgeFloor;
            m->floorHeight  = ledgePos[1];
            m->floorYaw     = atan2s(ledgeFloor->normal.z, ledgeFloor->normal.x);
            m->faceAngle[0] = 0x0;
            m->faceAngle[1] = (atan2s(grabbedWall->normal.z, grabbedWall->normal.x) + DEG(180));
            m->wall         = grabbedWall;
        } else {
            vec3f_copy(m->pos, nextPos);
            m->floor        = floor;
            m->floorHeight  = floorHeight;
        }
        return stepResult;
    }
    vec3f_copy(m->pos, nextPos);
    m->floor        = floor;
    m->floorHeight  = floorHeight;
    if (upperWall.numWalls > 0) {
        stepResult  = bonk_or_hit_lava_wall(m, &upperWall);
        if (stepResult != AIR_STEP_NONE) return stepResult;
    }
    return ((lowerWall.numWalls > 0) ? bonk_or_hit_lava_wall(m, &lowerWall) : AIR_STEP_NONE);
}

void apply_twirl_gravity(struct MarioState *m) {
    f32 terminalVelocity;
    f32 heaviness = 1.0f;
#ifdef Z_TWIRL
    f32 Zmodifier = ((m->input & INPUT_Z_DOWN) ? 4.0f : 1.0f);
#endif
    if (m->angleVel[1] > 0x400) heaviness = (1024.0f / m->angleVel[1]);
#ifdef Z_TWIRL
    terminalVelocity = (-TERMINAL_GRAVITY_VELOCITY * heaviness * Zmodifier);
#else
    terminalVelocity = (-TERMINAL_GRAVITY_VELOCITY * heaviness);
#endif
#ifdef Z_TWIRL
    m->vel[1] -= (4.0f * heaviness * Zmodifier);
#else
    m->vel[1] -= (4.0f * heaviness);
#endif
    if (m->vel[1] < terminalVelocity) m->vel[1] = terminalVelocity;
}

Bool32 should_strengthen_gravity_for_jump_ascent(struct MarioState *m) {
    if (!(m->flags & MARIO_JUMPING)) return FALSE;
    if (m->action & (ACT_FLAG_INTANGIBLE | ACT_FLAG_INVULNERABLE)) return FALSE;
    if (!(m->input & INPUT_A_DOWN) && (m->vel[1] > 20.0f)) return (m->action & ACT_FLAG_CONTROL_JUMP_HEIGHT) != 0;
    return FALSE;
}

void apply_gravity(struct MarioState *m) {
    if ((m->action == ACT_TWIRLING) && (m->vel[1] < 0.0f)) {
        apply_twirl_gravity(m);
    } else if (m->action == ACT_SHOT_FROM_CANNON) {
        m->vel[1] -= 1.0f;
        if (m->vel[1] < -TERMINAL_GRAVITY_VELOCITY) m->vel[1] = -TERMINAL_GRAVITY_VELOCITY;
    } else if ((m->action == ACT_LONG_JUMP) || (m->action == ACT_SLIDE_KICK) || (m->action == ACT_BBH_ENTER_SPIN)) {
        m->vel[1] -= 2.0f;
        if (m->vel[1] < -TERMINAL_GRAVITY_VELOCITY) m->vel[1] = -TERMINAL_GRAVITY_VELOCITY;
#ifdef WALL_SLIDE
    } else if (m->action == ACT_WALL_SLIDE) {
        m->vel[1] -= 3.2f;
        if (m->vel[1] < (-TERMINAL_GRAVITY_VELOCITY * 0.5f)) m->vel[1] = (-TERMINAL_GRAVITY_VELOCITY * 0.5f);
#endif
    } else if ((m->action == ACT_LAVA_BOOST) || (m->action == ACT_FALL_AFTER_STAR_GRAB)) {
        m->vel[1] -= 3.2f;
        if (m->vel[1] < -65.0f) m->vel[1] = -65.0f;
    } else if (m->action == ACT_GETTING_BLOWN) {
        m->vel[1] -= m->windGravity;
        if (m->vel[1] < -TERMINAL_GRAVITY_VELOCITY) m->vel[1] = -TERMINAL_GRAVITY_VELOCITY;
    } else if (should_strengthen_gravity_for_jump_ascent(m)) {
        m->vel[1] /= 4.0f;
    } else if (m->action & ACT_FLAG_METAL_WATER) {
        m->vel[1] -= 1.6f;
        if (m->vel[1] < -16.0f) m->vel[1] = -16.0f;
    } else if ((m->flags & MARIO_WING_CAP) && (m->vel[1] < 0.0f) && (m->input & INPUT_A_DOWN)) {
        m->marioBodyState->wingFlutter = TRUE;
        m->vel[1] -= 2.0f;
        if ((m->vel[1] < -37.5f) && (m->vel[1] += 4.0f) > -37.5f) m->vel[1] = -37.5f;
    } else {
        m->vel[1] -= 4.0f;
        if (m->vel[1] < -TERMINAL_GRAVITY_VELOCITY) m->vel[1] = -TERMINAL_GRAVITY_VELOCITY;
    }
}

void apply_vertical_wind(struct MarioState *m) {
    f32 maxVelY;
    if (m->action != ACT_GROUND_POUND) {
        f32 offsetY = (m->pos[1] + 1500.0f);
        if ((m->floor->type == SURFACE_VERTICAL_WIND) && (-3000.0f < offsetY) && (offsetY < 2000.0f)) {
            if (offsetY >= 0.0f) {
                maxVelY = (10000.0f / (offsetY + 200.0f));
            } else {
                maxVelY = 50.0f;
            }
            if (m->vel[1] < maxVelY) if ((m->vel[1] += maxVelY / 8.0f) > maxVelY) m->vel[1] = maxVelY;
#ifdef VERSION_JP
            play_sound(SOUND_ENV_WIND2, m->marioObj->header.gfx.cameraToObject);
#endif
        }
    }
}

MarioStep perform_air_step(struct MarioState *m, u32 stepArg) {
    // Angle wallDYaw;
    Vec3f intendedPos;
    MarioStep stepResult = AIR_STEP_NONE;
    // m->wall = NULL;
#if AIR_NUM_STEPS > 1
 #ifdef VARIABLE_STEPS
    const f32 speed    = (m->moveSpeed / 8.0f);
    const f32 numSteps = MAX(AIR_NUM_STEPS, speed);
 #else
    const f32 numSteps = AIR_NUM_STEPS; /* MAX(4.0f, (s32)(sqrtf(sqr(m->vel[0]) + sqr(m->vel[1]) + sqr(m->vel[2])) / 50.0f));*/
 #endif
    s32 i;
    MarioStep quarterStepResult;
    for ((i = 0); (i < numSteps); (i++)) {
        intendedPos[0] = (m->pos[0] + (m->vel[0] / numSteps));
        intendedPos[1] = (m->pos[1] + (m->vel[1] / numSteps));
        intendedPos[2] = (m->pos[2] + (m->vel[2] / numSteps));
        quarterStepResult = perform_air_quarter_step(m, intendedPos, stepArg);
        //! On one qf, hit OOB/ceil/wall to store the 2 return value, and continue
        // getting 0s until your last qf. Graze a wall on your last qf, and it will
        // return the stored 2 with a sharply angled reference wall. (some gwks)
        if (quarterStepResult != AIR_STEP_NONE) stepResult = quarterStepResult;
        if ((quarterStepResult == AIR_STEP_LANDED)
         || (quarterStepResult == AIR_STEP_GRABBED_LEDGE)
         || (quarterStepResult == AIR_STEP_GRABBED_CEILING)
         || (quarterStepResult == AIR_STEP_HIT_LAVA_WALL)) break;
 #ifdef WALL_QUICKSAND
        if ((quarterStepResult == AIR_STEP_HIT_WALL) && (m->wall) && (m->wall->type == SURFACE_INSTANT_QUICKSAND)) {
            stepResult = AIR_STEP_DEATH;
            m->vel[0] = (-2.0f * m->wall->normal.x);
            m->vel[1] = (-2.0f * m->wall->normal.y);
            m->vel[2] = (-2.0f * m->wall->normal.z);
            drop_and_set_mario_action(m, ACT_QUICKSAND_DEATH, 1);
            return stepResult;
        }
 #endif
    }
#else
    // Step once
    vec3f_sum(intendedPos, m->pos, m->vel);
    stepResult = perform_air_quarter_step(m, intendedPos, stepArg);
 #ifdef WALL_QUICKSAND
    if ((quarterStepResult == AIR_STEP_HIT_WALL) && (m->wall) && (m->wall->type == SURFACE_INSTANT_QUICKSAND)) {
        stepResult = AIR_STEP_DEATH;
        m->vel[0] = (-2.0f * m->wall->normal.x);
        m->vel[1] = (-2.0f * m->wall->normal.y);
        m->vel[2] = (-2.0f * m->wall->normal.z);
        drop_and_set_mario_action(m, ACT_QUICKSAND_DEATH, 1);
        return stepResult;
    }
 #endif
#endif
    if (m->vel[1] >= 0.0f) m->peakHeight = m->pos[1];
    m->terrainSoundAddend = mario_get_terrain_sound_addend(m);
    if (m->action != ACT_FLYING) apply_gravity(m);
    apply_vertical_wind(m);
    vec3f_copy(m->marioObj->header.gfx.pos, m->pos);
    vec3a_set( m->marioObj->header.gfx.angle, 0x0, m->faceAngle[1], 0x0);
    /*if (stepResult == AIR_STEP_HIT_WALL && m->wall != NULL) {
        wallDYaw = atan2s(m->wall->normal.z, m->wall->normal.x) - m->faceAngle[1];
        if ((stepArg & AIR_STEP_CHECK_BONK) && (wallDYaw < -DEG(135) || wallDYaw > DEG(135))) {
            if (m->forwardVel > 16.0f) mario_bonk_reflection(m, (stepArg & AIR_STEP_BONK_NEGATE_SPEED), m->wall);
        }
    }*/
    return stepResult;
}

// They had these functions the whole time and never used them? Lol

void set_vel_from_pitch_and_yaw(struct MarioState *m) {
    m->vel[0] = (m->forwardVel * coss(m->faceAngle[0]) * sins(m->faceAngle[1]));
    m->vel[1] = (m->forwardVel * sins(m->faceAngle[0])                        );
    m->vel[2] = (m->forwardVel * coss(m->faceAngle[0]) * coss(m->faceAngle[1]));
}

void set_vel_from_yaw(struct MarioState *m) {
    m->vel[0] = m->slideVelX = (m->forwardVel * sins(m->faceAngle[1]));
    m->vel[1] = 0.0f;
    m->vel[2] = m->slideVelZ = (m->forwardVel * coss(m->faceAngle[1]));
}
