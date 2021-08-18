#include <ultra64.h>

#include "sm64.h"
#include "engine/math_util.h"
#include "engine/surface_collision.h"
#include "mario.h"
#include "audio/external.h"
#include "game_init.h"
#include "interaction.h"
#include "mario_step.h"

#include "config.h"

static s16 sMovingSandSpeeds[] = { 12, 8, 4, 0 };

struct Surface gWaterSurfacePseudoFloor = {
    SURFACE_VERY_SLIPPERY, // type
    0,                     // force
    0,                     // flags
    0,                     // room
    0, 0,                  // lowerY, upperY
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
void stub_mario_step_1(UNUSED struct MarioState *x) {
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

void init_bully_collision_data(struct BullyCollisionData *data, f32 posX, f32 posZ, f32 forwardVel, s16 yaw, f32 conversionRatio, f32 radius) {
    if (forwardVel < 0.0f) {
        forwardVel *= -1.0f;
        yaw        += 0x8000;
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
        s16 wallAngle   = atan2s(m->wall->normal.z, m->wall->normal.x);
        m->faceAngle[1] = (wallAngle - (s16)(m->faceAngle[1] - wallAngle));
        play_sound((m->flags & MARIO_METAL_CAP) ? SOUND_ACTION_METAL_BONK : SOUND_ACTION_BONK, m->marioObj->header.gfx.cameraToObject);
    } else {
        play_sound(SOUND_ACTION_HIT, m->marioObj->header.gfx.cameraToObject);
    }
    if (negateSpeed) {
        mario_set_forward_vel(m, -m->forwardVel);
    } else {
        m->faceAngle[1] += 0x8000;
    }
}

u32 mario_update_quicksand(struct MarioState *m, f32 sinkingSpeed) {
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
                if ((m->quicksandDepth += sinkingSpeed) >= 160.0f) {
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

u32 mario_push_off_steep_floor(struct MarioState *m, u32 action, u32 actionArg) {
    if (abs_angle_diff(m->floorAngle, m->faceAngle[1]) < 0x4000) {
        m->forwardVel   =  16.0f;// * (1.0f-m->floor->normal.y);;
        m->faceAngle[1] = m->floorAngle;
    } else {
        m->forwardVel   = -16.0f;// * (1.0f-m->floor->normal.y);
        m->faceAngle[1] = (m->floorAngle + 0x8000);
    }
    return set_mario_action(m, action, actionArg);
}

u32 mario_update_moving_sand(struct MarioState *m) {
    struct Surface *floor = m->floor;
    s32 floorType         = floor->type;
    if ((floorType == SURFACE_DEEP_MOVING_QUICKSAND)
     || (floorType == SURFACE_SHALLOW_MOVING_QUICKSAND)
     || (floorType == SURFACE_MOVING_QUICKSAND)
     || (floorType == SURFACE_INSTANT_MOVING_QUICKSAND)) {
        s16 pushAngle = (floor->force << 8);
        f32 pushSpeed = sMovingSandSpeeds[floor->force >> 8];
        m->vel[0] += (pushSpeed * sins(pushAngle));
        m->vel[2] += (pushSpeed * coss(pushAngle));
        return TRUE;
    }
    return FALSE;
}

u32 mario_update_windy_ground(struct MarioState *m) {
    struct Surface *floor = m->floor;
    if (floor->type == SURFACE_HORIZONTAL_WIND) {
        f32 pushSpeed;
        s16 pushAngle = (floor->force << 8);
        if (m->action & ACT_FLAG_MOVING) {
            s16 pushDYaw = (m->faceAngle[1] - pushAngle);
            pushSpeed = ((m->forwardVel > 0.0f) ? (-m->forwardVel * 0.5f) : -8.0f);
            if ((pushDYaw > -0x4000) && (pushDYaw < 0x4000)) pushSpeed *= -1.0f;
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
    if (m->pos[1] < (m->floorHeight + 80.0f)) m->pos[1] = m->floorHeight;
    vec3f_copy(marioObj->header.gfx.pos, m->pos);
    vec3s_set( marioObj->header.gfx.angle, 0x0, m->faceAngle[1], 0x0);
}

s32 stationary_ground_step(struct MarioState *m) {
    u32 takeStep;
    struct Object *marioObj = m->marioObj;
    u32 stepResult = GROUND_STEP_NONE;
    mario_set_forward_vel(m, 0.0f);
    takeStep  = mario_update_moving_sand(m);
    takeStep |= mario_update_windy_ground(m);
    if (takeStep) {
        stepResult = perform_ground_step(m);
    } else {
        //? This is responsible for several stationary downwarps.
        if (m->pos[1] < (m->floorHeight + 80.0f)) m->pos[1] = m->floorHeight;
        vec3f_copy(marioObj->header.gfx.pos, m->pos);
        vec3s_set( marioObj->header.gfx.angle, 0x0, m->faceAngle[1], 0x0);
    }
    return stepResult;
}

static s32 perform_ground_quarter_step(struct MarioState *m, Vec3f nextPos) {
#ifdef BETTER_WALL_COLLISION
    struct WallCollisionData lowerWall, upperWall;
    s16 i;
    s16 wallDYaw;
    // s16 oldWallDYaw, absWallDYaw;
#else
 #ifndef SKIP_GROUND_LOWER_WALL
    UNUSED struct Surface *lowerWall;
 #endif
    struct Surface *upperWall;
#endif
    struct Surface *ceil, *floor;
    f32 ceilHeight, floorHeight, waterLevel;
#if NULL_FLOOR_STEPS > 0
    u32 missedFloors = 0;
    Vec3f startPos;
#endif
#ifdef BETTER_WALL_COLLISION
    resolve_and_return_wall_collisions(nextPos, 30.0f, 24.0f, &lowerWall);
    resolve_and_return_wall_collisions(nextPos, 60.0f, 50.0f, &upperWall);
#else
 #ifndef SKIP_GROUND_LOWER_WALL
    lowerWall = resolve_and_return_wall_collisions(nextPos, 30.0f, 24.0f);
 #endif
    upperWall = resolve_and_return_wall_collisions(nextPos, 60.0f, 50.0f);
#endif
    floorHeight = find_floor(nextPos[0], nextPos[1], nextPos[2], &floor);

#if NULL_FLOOR_STEPS > 0
    vec3f_copy(startPos, nextPos);
    while ((floor == NULL) && (missedFloors < NULL_FLOOR_STEPS)) {
        nextPos[0] += (m->floor->normal.y * (m->vel[0] / AIR_NUM_STEPS));
        nextPos[2] += (m->floor->normal.y * (m->vel[2] / AIR_NUM_STEPS));
 #ifdef BETTER_WALL_COLLISION
        resolve_and_return_wall_collisions(nextPos, 30.0f, 24.0f, &lowerWall);
        resolve_and_return_wall_collisions(nextPos, 60.0f, 50.0f, &upperWall);
 #else
  #ifndef SKIP_GROUND_LOWER_WALL
        lowerWall = resolve_and_return_wall_collisions(nextPos, 30.0f, 24.0f);
  #endif
        upperWall = resolve_and_return_wall_collisions(nextPos, 60.0f, 50.0f);
 #endif
        floorHeight = find_floor(nextPos[0], nextPos[1], nextPos[2], &floor);
        missedFloors++;
    }
#endif
    ceilHeight = vec3f_find_ceil(nextPos, nextPos[1], &ceil);
    waterLevel = find_water_level(nextPos[0], nextPos[2]);
#ifndef BETTER_WALL_COLLISION
    m->wall = upperWall;
#endif
    if (floor == NULL) {
#if NULL_FLOOR_STEPS > 0
        vec3f_copy(nextPos, startPos);
#endif
        return GROUND_STEP_HIT_WALL_STOP_QSTEPS;
    }
    if ((m->action & ACT_FLAG_RIDING_SHELL) && (floorHeight < waterLevel)) {
        floorHeight         = waterLevel;
        floor               = &gWaterSurfacePseudoFloor;
        floor->originOffset = -floorHeight;
    }
    if (nextPos[1] > (floorHeight + 100.0f)) {
#ifdef LEDGE_PROTECTION
        if ((m->input & INPUT_NONZERO_ANALOG)
            && (m->forwardVel <= 32.0f)
            && !(m->action & ACT_FLAG_SHORT_HITBOX)
            && !(m->action & ACT_FLAG_BUTT_OR_STOMACH_SLIDE)
            && (mario_get_floor_class(m) != SURFACE_CLASS_VERY_SLIPPERY)
            && analog_stick_held_back(m, 0x471C)) {
            return GROUND_STEP_NONE;
        }
#endif
        if ((nextPos[1] + m->marioObj->hitboxHeight) >= ceilHeight) return GROUND_STEP_HIT_WALL_STOP_QSTEPS;
        vec3f_copy(m->pos, nextPos);
        m->floor       = floor;
        m->floorHeight = floorHeight;
#if COYOTE_TIME > 0
        if (m->coyoteTimer++ < COYOTE_TIME) {
            return GROUND_STEP_NONE;
        } else {
            m->coyoteTimer = 0;
            return GROUND_STEP_LEFT_GROUND;
        }
    }
    m->coyoteTimer = 0;
#else
        return GROUND_STEP_LEFT_GROUND;
    }
#endif
#ifdef BETTER_CEILING_HANDLING
    if (((nextPos[1] + m->marioObj->hitboxHeight) > ceilHeight) && (floorHeight < ceilHeight)) {
        // softlock fix
        s16 surfAngle;
        s32 underSteepSurf = FALSE;
        if ((floor != NULL) && (ceil != NULL)) {
            // steep floor
            if (floor->normal.y < COS25) {
                surfAngle = atan2s(floor->normal.z, floor->normal.x);
                underSteepSurf = TRUE;
            }
            // steep ceiling
            if (-COS25 < ceil->normal.y) {
                surfAngle = atan2s(ceil->normal.z, ceil->normal.x);
                underSteepSurf = TRUE;
            }
        }
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
    if ((floorHeight + 160.0f) >= ceilHeight) return GROUND_STEP_HIT_WALL_STOP_QSTEPS;
#endif
    vec3f_set(m->pos, nextPos[0], floorHeight, nextPos[2]);
    m->floor       = floor;
    m->floorHeight = floorHeight;
#ifdef BETTER_WALL_COLLISION
    // if (m->wall != NULL) {
    //     oldWallDYaw = (atan2s(m->wall->normal.z, m->wall->normal.x) - m->faceAngle[1]);
    //     oldWallDYaw = ((oldWallDYaw < 0) ? -oldWallDYaw : oldWallDYaw);
    // } else {
    //     oldWallDYaw = 0;
    // }
    for (i = 0; i < upperWall.numWalls; i++) {
        wallDYaw = (atan2s(upperWall.walls[i]->normal.z, upperWall.walls[i]->normal.x) - m->faceAngle[1]);
        // absWallDYaw = ((wallDYaw < 0) ? -wallDYaw : wallDYaw);
        // if (absWallDYaw > oldWallDYaw) {
        //     oldWallDYaw = absWallDYaw;
        //     m->wall = upperWall.walls[i];
        // }
        m->wall = upperWall.walls[i];
        if ((wallDYaw >=  0x2AAA) && (wallDYaw <=  0x5555)) continue;
        if ((wallDYaw <= -0x2AAA) && (wallDYaw >= -0x5555)) continue;
#else
    if (upperWall != NULL) {
        s16 wallDYaw = atan2s(upperWall->normal.z, upperWall->normal.x) - m->faceAngle[1];
        if ((wallDYaw >=  0x2AAA) && (wallDYaw <=  0x5555)) return GROUND_STEP_NONE;
        if ((wallDYaw <= -0x2AAA) && (wallDYaw >= -0x5555)) return GROUND_STEP_NONE;
#endif
        return GROUND_STEP_HIT_WALL_CONTINUE_QSTEPS;
    }
    return GROUND_STEP_NONE;
}

s32 perform_ground_step(struct MarioState *m) {
    Vec3f intendedPos;
    u32 stepResult;
#ifdef BETTER_WALL_COLLISION
    m->wall = NULL;
#endif
#if GROUND_NUM_STEPS > 1
    const f32 numSteps = GROUND_NUM_STEPS;
    s32 i;
    for (i = 0; i < numSteps; i++) {
        intendedPos[0] = (m->pos[0] + (m->floor->normal.y * (m->vel[0] / numSteps)));
        intendedPos[2] = (m->pos[2] + (m->floor->normal.y * (m->vel[2] / numSteps)));
        intendedPos[1] =  m->pos[1];
        stepResult = perform_ground_quarter_step(m, intendedPos);
        if ((stepResult == GROUND_STEP_LEFT_GROUND) || (stepResult == GROUND_STEP_HIT_WALL_STOP_QSTEPS)) break;
    }
#else
    // Step once
    intendedPos[0] = (m->pos[0] + (m->floor->normal.y * m->vel[0]));
    intendedPos[2] = (m->pos[2] + (m->floor->normal.y * m->vel[2]));
    intendedPos[1] =  m->pos[1];
    stepResult = perform_ground_quarter_step(m, intendedPos);
#endif
    m->terrainSoundAddend = mario_get_terrain_sound_addend(m);
    vec3f_copy(m->marioObj->header.gfx.pos, m->pos);
    vec3s_set( m->marioObj->header.gfx.angle, 0x0, m->faceAngle[1], 0x0);
    if (stepResult == GROUND_STEP_HIT_WALL_CONTINUE_QSTEPS) stepResult = GROUND_STEP_HIT_WALL;
#ifdef WALL_QUICKSAND
    if ((stepResult == GROUND_STEP_HIT_WALL) && m->wall && (m->wall->type == SURFACE_INSTANT_QUICKSAND)) {
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

#ifdef BETTER_WALL_COLLISION
struct Surface *check_ledge_grab(struct MarioState *m, struct Surface *grabbedWall, struct Surface *wall, Vec3f intendedPos, Vec3f nextPos, Vec3f ledgePos, struct Surface **ledgeFloor) {
    struct Surface *returnedWall = wall;
    if (m->vel[1] > 0.0f || wall == NULL) return FALSE;
    if (grabbedWall == NULL) grabbedWall = wall;
    if ((m->action == ACT_WALL_SLIDE)
     || (m->action == ACT_FORWARD_ROLLOUT)
     || (m->action == ACT_BACKWARD_ROLLOUT)
     || analog_stick_held_back(m, 0x4000)) return FALSE;
    // Return the already grabbed wall if Mario is moving into it more than the newly tested wall
    if (((grabbedWall->normal.x * m->vel[0]) + (grabbedWall->normal.z * m->vel[2])) < ((wall->normal.x * m->vel[0]) + (wall->normal.z * m->vel[2]))) returnedWall = grabbedWall;
    f32 displacementX = (nextPos[0] - intendedPos[0]);
    f32 displacementZ = (nextPos[2] - intendedPos[2]);
    // Only ledge grab if the wall displaced Mario in the opposite direction of
    // his velocity.
    if (((displacementX * m->vel[0]) + (displacementZ * m->vel[2])) > 0.0f) returnedWall = grabbedWall;
    ledgePos[0] = (nextPos[0] - (wall->normal.x * 60.0f));
    ledgePos[2] = (nextPos[2] - (wall->normal.z * 60.0f));
    ledgePos[1] = find_floor(ledgePos[0], (nextPos[1] + 100.0f), ledgePos[2], ledgeFloor);
    if ((ledgeFloor == NULL)
     || (ledgePos[1] < (nextPos[1] + 80.0f))
     || ((*ledgeFloor)->normal.y < COS25)
     || ((*ledgeFloor)->type == SURFACE_BURNING)
     || SURFACE_IS_QUICKSAND((*ledgeFloor)->type)) return FALSE;
    // if (ledgePos[1] <= (nextPos[1] + 100.0f)) returnedWall = grabbedWall;
    return returnedWall;
}
#else
u32 check_ledge_grab(struct MarioState *m, struct Surface *wall, Vec3f intendedPos, Vec3f nextPos) {
    struct Surface *ledgeFloor;
    Vec3f ledgePos;
    if (m->vel[1] > 0) return FALSE;
#ifdef LEDGE_GRAB_FIX
    if ((m->action == ACT_WALL_SLIDE) || (m->action == ACT_FORWARD_ROLLOUT) || (m->action == ACT_BACKWARD_ROLLOUT) || analog_stick_held_back(m, 0x4000)) return FALSE;
#endif
    f32 displacementX = (nextPos[0] - intendedPos[0]);
    f32 displacementZ = (nextPos[2] - intendedPos[2]);
    // Only ledge grab if the wall displaced Mario in the opposite direction of
    // his velocity.
    if ((displacementX * m->vel[0]) + (displacementZ * m->vel[2]) > 0.0f) return FALSE;
    ledgePos[0] = (nextPos[0] - (wall->normal.x * 60.0f));
    ledgePos[2] = (nextPos[2] - (wall->normal.z * 60.0f));
#ifdef LEDGE_GRAB_FIX
    ledgePos[1] = find_floor(ledgePos[0], (nextPos[1] + 80.0f), ledgePos[2], &ledgeFloor);
    if ((ledgeFloor == NULL) || (ledgeFloor->normal.y < COS25) || (ledgeFloor->type == SURFACE_BURNING) || SURFACE_IS_QUICKSAND(ledgeFloor->type)) return FALSE;
#else
    //! Since the search for floors starts at y + 160, we will sometimes grab
    // a higher ledge than expected (glitchy ledge grab)
    ledgePos[1] = find_floor(ledgePos[0], (nextPos[1] + 160.0f), ledgePos[2], &ledgeFloor);
#endif
    if ((ledgePos[1] - nextPos[1]) <= 100.0f) return FALSE;
    vec3f_copy(m->pos, ledgePos);
    m->floor        = ledgeFloor;
    m->floorHeight  = ledgePos[1];
    m->floorAngle   = atan2s(ledgeFloor->normal.z, ledgeFloor->normal.x);
    m->faceAngle[0] = 0x0;
    m->faceAngle[1] = atan2s(wall->normal.z, wall->normal.x) + 0x8000;
    return TRUE;
}
#endif

#ifdef BETTER_WALL_COLLISION
s32 bonk_or_hit_lava_wall(struct MarioState *m, struct WallCollisionData *wallData) {
    s16 i;
    s32 result = AIR_STEP_NONE;
    s16 wallDYaw;
#ifndef WALL_SLIDE
    s16 absWallDYaw;
    s16 oldWallDYaw = ((m->wall != NULL) ? abs_angle_diff(atan2s(m->wall->normal.z, m->wall->normal.x), m->faceAngle[1]) : 0x0);
#endif
    for (i = 0; i < wallData->numWalls; i++) {
        if (wallData->walls[i] != NULL) {
            wallDYaw = (atan2s(wallData->walls[i]->normal.z, wallData->walls[i]->normal.x) - m->faceAngle[1]);
#ifdef WALL_SLIDE
            m->wall = wallData->walls[i];
            if (wallData->walls[i]->type == SURFACE_BURNING) return AIR_STEP_HIT_LAVA_WALL;
            if (((wallDYaw < -0x5000) || (wallDYaw > 0x5000)) && (m->vel[1] <= 0)) {
                m->flags |= MARIO_AIR_HIT_WALL;
                result = AIR_STEP_HIT_WALL;
            }
#else
            if (wallData->walls[i]->type == SURFACE_BURNING) {
                m->wall = wallData->walls[i];
                return AIR_STEP_HIT_LAVA_WALL;
            }
            // Update wall reference (bonked wall) only if the new wall has a better facing angle
            absWallDYaw = ((wallDYaw < 0) ? -wallDYaw : wallDYaw);
            if (absWallDYaw > oldWallDYaw) {
                oldWallDYaw = absWallDYaw;
                m->wall = wallData->walls[i];
                if ((wallDYaw < -0x6000) || (wallDYaw > 0x6000)) {
                    m->flags |= MARIO_AIR_HIT_WALL;
                    result = AIR_STEP_HIT_WALL;
                }
            }
#endif
        }
    }
    return result;
}
#endif

s32 perform_air_quarter_step(struct MarioState *m, Vec3f intendedPos, u32 stepArg) {
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
#ifdef BETTER_WALL_COLLISION
    s16 i;
    s32 stepResult = AIR_STEP_NONE;
    struct WallCollisionData upperWall, lowerWall;
    Vec3f ledgePos;
    struct Surface *grabbedWall = NULL;
    struct Surface *ledgeFloor;
    resolve_and_return_wall_collisions(nextPos, 150.0f, 50.0f, &upperWall);
    resolve_and_return_wall_collisions(nextPos,  30.0f, 50.0f, &lowerWall);
#else
    struct Surface *upperWall, *lowerWall;
    s16 wallDYaw;
    upperWall   = resolve_and_return_wall_collisions(nextPos, 150.0f, 50.0f);
    lowerWall   = resolve_and_return_wall_collisions(nextPos,  30.0f, 50.0f);
#endif
    floorHeight = find_floor(nextPos[0], nextPos[1], nextPos[2], &floor);
#if NULL_FLOOR_STEPS > 0
    // vec3f_copy(startPos, nextPos); // why does this crash the game when ledge grabbing?
    while ((floor == NULL) && (missedFloors < NULL_FLOOR_STEPS)) {
        nextPos[0] += (m->vel[0] / GROUND_NUM_STEPS);
        nextPos[2] += (m->vel[2] / GROUND_NUM_STEPS);
 #ifdef BETTER_WALL_COLLISION
        resolve_and_return_wall_collisions(nextPos, 150.0f, 50.0f, &upperWall);
        resolve_and_return_wall_collisions(nextPos,  30.0f, 50.0f, &lowerWall);
 #else
        upperWall   = resolve_and_return_wall_collisions(nextPos, 150.0f, 50.0f);
        lowerWall   = resolve_and_return_wall_collisions(nextPos,  30.0f, 50.0f);
 #endif
        floorHeight = find_floor(nextPos[0], nextPos[1], nextPos[2], &floor);
        missedFloors++;
    }
#endif
    ceilHeight = vec3f_find_ceil(nextPos, nextPos[1], &ceil);
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
    if ((m->action & ACT_FLAG_RIDING_SHELL) && floorHeight < waterLevel) {
        floorHeight         = waterLevel;
        floor               = &gWaterSurfacePseudoFloor;
        floor->originOffset = -floorHeight;
    }
    //! This check uses f32, but findFloor uses short (overflow jumps)
    if (nextPos[1] <= floorHeight) {
        if ((ceilHeight - floorHeight) > m->marioObj->hitboxHeight) {
            m->pos[0]      = nextPos[0];
            m->pos[2]      = nextPos[2];
            m->floor       = floor;
            m->floorHeight = floorHeight;
        }
        //! When ceilHeight - floorHeight <= 160, the step result says that
        // Mario landed, but his movement is cancelled and his referenced floor
        // isn't updated (pedro spots)
        m->pos[1]      = floorHeight;
        m->floor       = floor;
        m->floorHeight = floorHeight;
        return AIR_STEP_LANDED;
    }
#ifdef BETTER_CEILING_HANDLING
    if ((ceil != NULL) && ((nextPos[1] + 160.0f) > ceilHeight)) {
        if (floorHeight > nextPos[1]) return AIR_STEP_HIT_WALL;
        if ((m->vel[1] >= 0.0f) && !(m->prevAction & ACT_FLAG_HANGING) && (ceil->type == SURFACE_HANGABLE)) {
            m->vel[1] = 0.0f;
            return AIR_STEP_GRABBED_CEILING;
        }
        if (-COS25 >= ceil->normal.y) {
            if (m->vel[1] > 0.0f) m->vel[1] = 0.0f;
        } else {
            ceilSteepness = sqrtf(sqr(ceil->normal.x) + sqr(ceil->normal.z));
            if (abs_angle_diff(atan2s(ceil->normal.z,  ceil->normal.x), m->marioObj->oMoveAngleYaw) <= 0x4000) {
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
        nextPos[1] = (ceilHeight - 160.0f);
        vec3f_copy(m->pos, nextPos);
        m->floor       = floor;
        m->floorHeight = floorHeight;
 #ifdef BETTER_WALL_COLLISION
        return AIR_STEP_HIT_CEILING;
 #else
        return AIR_STEP_NONE;
 #endif
    }
#else
    if ((nextPos[1] + 160.0f) > ceilHeight) {
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
 #ifdef BETTER_WALL_COLLISION
        return AIR_STEP_HIT_CEILING;
 #else
        return AIR_STEP_HIT_WALL;
 #endif
    }
#endif
    //! When the wall is not completely vertical or there is a slight wall
    // misalignment, you can activate these conditions in unexpected situations
#ifdef BETTER_WALL_COLLISION
    if ((stepArg & AIR_STEP_CHECK_LEDGE_GRAB) && (upperWall.numWalls == 0) && (lowerWall.numWalls != 0)) {
        for (i = 0; i < lowerWall.numWalls; i++) {
            if ((grabbedWall = check_ledge_grab(m, grabbedWall, lowerWall.walls[i], intendedPos, nextPos, ledgePos, &ledgeFloor))) {
                stepResult = AIR_STEP_GRABBED_LEDGE;
            }
        }
        if (stepResult == AIR_STEP_GRABBED_LEDGE) {// && ledgeFloor != NULL && grabbedWall != NULL) {
            vec3f_copy(m->pos, ledgePos);
            m->floor        = ledgeFloor;
            m->floorHeight  = ledgePos[1];
            m->floorAngle   = atan2s(ledgeFloor->normal.z, ledgeFloor->normal.x);
            m->faceAngle[0] = 0x0;
            m->faceAngle[1] = (atan2s(grabbedWall->normal.z, grabbedWall->normal.x) + 0x8000);
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
    stepResult      = bonk_or_hit_lava_wall(m, &upperWall);
    if (stepResult != AIR_STEP_NONE) return stepResult;
    return bonk_or_hit_lava_wall(m, &lowerWall);
#else
    if ((stepArg & AIR_STEP_CHECK_LEDGE_GRAB) && (upperWall == NULL) && (lowerWall != NULL)) {
        if (check_ledge_grab(m, lowerWall, intendedPos, nextPos)) return AIR_STEP_GRABBED_LEDGE;
        vec3f_copy(m->pos, nextPos);
        m->floor       = floor;
        m->floorHeight = floorHeight;
        return AIR_STEP_NONE;
    }
    vec3f_copy(m->pos, nextPos);
    m->floor        = floor;
    m->floorHeight  = floorHeight;
    if ((upperWall != NULL) || (lowerWall != NULL)) {
        m->wall = ((upperWall != NULL) ? upperWall : lowerWall);
        wallDYaw = abs_angle_diff(atan2s(m->wall->normal.z, m->wall->normal.x), m->faceAngle[1]);
        if (m->wall->type == SURFACE_BURNING) return AIR_STEP_HIT_LAVA_WALL;
 #ifdef WALL_SLIDE
        if ((wallDYaw > 0x5000) && (m->vel[1] <= 0)) {
 #elif WALLKICKS_46_DEGREES
        if (wallDYaw > 0x5B00) { // 0x5F4A?
 #else
        if (wallDYaw > 0x6000) {
 #endif
            m->flags |= MARIO_AIR_HIT_WALL;
            return AIR_STEP_HIT_WALL;
        }
    }
    return AIR_STEP_NONE;
#endif
}

void apply_twirl_gravity(struct MarioState *m) {
    f32 terminalVelocity;
    f32 heaviness = 1.0f;
#ifdef Z_TWIRL
    f32 Zmodifier = ((m->input & INPUT_Z_DOWN) ? 4.0f : 1.0f);
#endif
    if (m->angleVel[1] > 1024) heaviness = (1024.0f / m->angleVel[1]);
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

u32 should_strengthen_gravity_for_jump_ascent(struct MarioState *m) {
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
        if (m->vel[1] < (-TERMINAL_GRAVITY_VELOCITY * 0.5f)) m->vel[1] = -TERMINAL_GRAVITY_VELOCITY*0.5f;
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
    f32 offsetY;
    if (m->action != ACT_GROUND_POUND) {
        offsetY = (m->pos[1] + 1500.0f);
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

s32 perform_air_step(struct MarioState *m, u32 stepArg) {
    // s16 wallDYaw;
    Vec3f intendedPos;
    s32 stepResult = AIR_STEP_NONE;
    m->wall = NULL;
#if AIR_NUM_STEPS > 1
    const f32 numSteps = AIR_NUM_STEPS; /* max(4.0f, (s32)(sqrtf(sqr(m->vel[0]) + sqr(m->vel[1]) + sqr(m->vel[2])) / 50.0f));*/
    s32 i;
    s32 quarterStepResult;
    for (i = 0; i < numSteps; i++) {
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
        if ((quarterStepResult == AIR_STEP_HIT_WALL) && m->wall && (m->wall->type == SURFACE_INSTANT_QUICKSAND)) {
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
    if ((quarterStepResult == AIR_STEP_HIT_WALL) && m->wall && (m->wall->type == SURFACE_INSTANT_QUICKSAND)) {
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
    vec3s_set( m->marioObj->header.gfx.angle, 0x0, m->faceAngle[1], 0x0);
    /*if (stepResult == AIR_STEP_HIT_WALL && m->wall != NULL) {
        wallDYaw = atan2s(m->wall->normal.z, m->wall->normal.x) - m->faceAngle[1];
        if ((stepArg & AIR_STEP_CHECK_BONK) && (wallDYaw < -0x6000 || wallDYaw > 0x6000)) {
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
