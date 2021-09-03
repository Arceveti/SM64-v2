#include <PR/ultratypes.h>

#include "sm64.h"
#include "behavior_data.h"
#include "mario_actions_automatic.h"
#include "audio/external.h"
#include "area.h"
#include "mario.h"
#include "mario_step.h"
#include "engine/math_util.h"
#include "boot/memory.h"
#include "engine/graph_node.h"
#include "save_file.h"
#include "engine/surface_collision.h"
#include "interaction.h"
#include "camera.h"
#include "cutscene.h"
#include "level_table.h"
#include "rumble_init.h"

#include "config.h"

#define POLE_NONE               0x0
#define POLE_TOUCHED_FLOOR      0x1
#define POLE_FELL_OFF           0x2

#define HANG_NONE               0x0
#define HANG_HIT_CEIL_OR_OOB    0x1
#define HANG_LEFT_CEIL          0x2

void add_tree_leaf_particles(struct MarioState *m) {
    f32 leafHeight;
    if (m->usedObj->behavior == segmented_to_virtual(bhvTree)) {
        // make leaf effect spawn higher on the Shifting Sand Land palm tree
        leafHeight = ((m->usedObj->header.gfx.sharedChild == gLoadedGraphNodes[MODEL_SSL_PALM_TREE]) ? 250.0f : 100.0f);
        if ((m->pos[1] - m->floorHeight) > leafHeight) m->particleFlags |= PARTICLE_LEAF;
    }
}

void play_climbing_sounds(struct MarioState *m, s32 direction) {
    s32 isOnTree = (m->usedObj->behavior == segmented_to_virtual(bhvTree));
    if (direction) {
        if (is_anim_past_frame(m, 1)) play_sound(((isOnTree) ? SOUND_ACTION_CLIMB_UP_TREE : SOUND_ACTION_CLIMB_UP_POLE), m->marioObj->header.gfx.cameraToObject);
    } else {
        play_sound(((isOnTree) ? SOUND_MOVING_SLIDE_DOWN_TREE : SOUND_MOVING_SLIDE_DOWN_POLE), m->marioObj->header.gfx.cameraToObject);
    }
}

s32 set_pole_position(struct MarioState *m, f32 offsetY) {
    struct Surface *floor;
    struct Surface *ceil;
    f32 floorHeight;
    f32 ceilHeight;
    s32 collided;
    s32 result              = POLE_NONE;
    f32 poleTop             = ( m->usedObj->hitboxHeight     - 100.0f);
    f32 poleBottom          = (-m->usedObj->hitboxDownOffset - 100.0f);
    struct Object *marioObj =   m->marioObj;
    if (marioObj->oMarioPolePos > poleTop) marioObj->oMarioPolePos = poleTop;
    vec3f_copy_y_off(m->pos, &m->usedObj->oPosVec, (marioObj->oMarioPolePos + offsetY));
    collided   = f32_find_wall_collision(&m->pos[0], &m->pos[1], &m->pos[2], 60.0f, 50.0f);
    collided  |= f32_find_wall_collision(&m->pos[0], &m->pos[1], &m->pos[2], 30.0f, 24.0f);
    ceilHeight = find_ceil(m->pos[0], (m->pos[1] + m->midY), m->pos[2], &ceil);
    if (m->pos[1] > (ceilHeight - MARIO_HITBOX_HEIGHT)) {
        m->pos[1] = (ceilHeight - MARIO_HITBOX_HEIGHT);
        marioObj->oMarioPolePos = (m->pos[1] - m->usedObj->oPosY);
    }
    floorHeight = find_floor(m->pos[0], (m->pos[1] + MARIO_SHORT_HITBOX_HEIGHT), m->pos[2], &floor);
    if (m->pos[1] < floorHeight) {
        m->pos[1] = floorHeight;
        set_mario_action(m, ACT_IDLE, 0);
        result = POLE_TOUCHED_FLOOR;
    } else if (marioObj->oMarioPolePos < poleBottom) {
        m->pos[1] = (m->usedObj->oPosY + poleBottom);
        set_mario_action(m, ACT_FREEFALL, 0);
        result = POLE_FELL_OFF;
    } else if (collided) {
        if (m->pos[1] > (floorHeight + 20.0f)) {
            m->forwardVel = -8.0f;
            set_mario_action(m, ACT_FREEFALL, 0);
            result = POLE_FELL_OFF;
        } else {
            set_mario_action(m, ACT_IDLE, 0);
            result = POLE_TOUCHED_FLOOR;
        }
    }
    vec3f_copy(m->marioObj->header.gfx.pos, m->pos);
    vec3a_set(m->marioObj->header.gfx.angle, m->usedObj->oMoveAnglePitch, m->faceAngle[1], m->usedObj->oMoveAngleRoll);
    return result;
}

Bool32 act_holding_pole(struct MarioState *m) {
    struct Object *marioObj = m->marioObj;
    if ((m->input & (INPUT_B_PRESSED | INPUT_Z_PRESSED)) || (m->health < 0x100)) {
        add_tree_leaf_particles(m);
        m->forwardVel = -8.0f;
        return set_mario_action(m, ACT_FREEFALL, 0);
    }
    if (m->input & INPUT_A_PRESSED) {
        add_tree_leaf_particles(m);
#ifdef ACTION_CANCELS
        if (analog_stick_held_back(m, DEG(90))) {
            m->faceAngle[1]  = m->intendedYaw;
        } else {
            m->faceAngle[1] += DEG(180);
        }
#else
        m->faceAngle[1] += DEG(180);
#endif
        return set_mario_action(m, ACT_WALL_KICK_AIR, 0);
    }
    if (m->controller->stickY > 16.0f) {
        f32 poleTop = (m->usedObj->hitboxHeight - MARIO_SHORT_HITBOX_HEIGHT);
        const BehaviorScript *poleBehavior = virtual_to_segmented(0x13, m->usedObj->behavior);
        if (marioObj->oMarioPolePos < (poleTop - 0.4f)                       ) return set_mario_action(m, ACT_CLIMBING_POLE         , 0);
        if ((poleBehavior != bhvGiantPole) && (m->controller->stickY > 50.0f)) return set_mario_action(m, ACT_TOP_OF_POLE_TRANSITION, 0);
    }
    if (m->controller->stickY < -16.0f) {
        m->angleVel[1] -= (m->controller->stickY * 2);
        if (m->angleVel[1] > 0x1000) m->angleVel[1] = 0x1000;
        m->faceAngle[1] += m->angleVel[1];
        marioObj->oMarioPolePos -= (m->angleVel[1] / 0x100);
        if (m->usedObj->behavior == segmented_to_virtual(bhvTree)) {
            f32 leafHeight = ((m->usedObj->header.gfx.sharedChild == gLoadedGraphNodes[MODEL_SSL_PALM_TREE]) ? 250.0f : 100.0f);
            if ((m->pos[1] - m->floorHeight) > leafHeight) m->particleFlags |= PARTICLE_LEAF;
        }
        play_climbing_sounds(m, FALSE);
#if ENABLE_RUMBLE
        reset_rumble_timers_slip();
#endif
        set_sound_moving_speed(SOUND_BANK_MOVING, ((m->angleVel[1] / 0x100) * 2));
    } else {
        m->angleVel[1] = 0x0;
        m->faceAngle[1] -= (m->controller->stickX * 16.0f);
    }
    if (set_pole_position(m, 0.0f) == POLE_NONE) set_mario_animation(m, MARIO_ANIM_IDLE_ON_POLE);
    return FALSE;
}

Bool32 act_climbing_pole(struct MarioState *m) {
    AnimAccel animSpeed;
    struct Object *marioObj = m->marioObj;
    Angle cameraAngle       = m->area->camera->yaw;
    if ((m->input & (INPUT_B_PRESSED | INPUT_Z_PRESSED)) || (m->health < 0x100)) {
        add_tree_leaf_particles(m);
        m->forwardVel = -8.0f;
        return set_mario_action(m, ACT_FREEFALL, 0);
    }
    if (m->input & INPUT_A_PRESSED) {
        add_tree_leaf_particles(m);
        if (analog_stick_held_back(m, DEG(90))) {
            m->faceAngle[1]  = m->intendedYaw;
        } else {
            m->faceAngle[1] += DEG(180);
        }
        return set_mario_action(m, ACT_WALL_KICK_AIR, 0);
    }
    if (m->controller->stickY < 8.0f) return set_mario_action(m, ACT_HOLDING_POLE, 0);
    marioObj->oMarioPolePos   += (m->controller->stickY / 8.0f);
    m->angleVel[1] = 0x0;
    approach_s16_symmetric_bool(&m->faceAngle[1], cameraAngle, 0x400);
    if (set_pole_position(m, 0.0f) == POLE_NONE) {
        animSpeed = ((m->controller->stickY / 4.0f) * 0x10000);
        set_mario_anim_with_accel(m, MARIO_ANIM_CLIMB_UP_POLE, animSpeed);
        add_tree_leaf_particles(m);
        play_climbing_sounds(m, TRUE);
    }
    return FALSE;
}

Bool32 act_grab_pole_slow(struct MarioState *m) {
    play_sound_if_no_flag(m, SOUND_MARIO_WHOA, MARIO_MARIO_SOUND_PLAYED);
#if defined(ACTION_CANCELS) || defined(POLE_SWING)
    if ((m->input & (INPUT_B_PRESSED | INPUT_Z_PRESSED)) || (m->health < 0x100)) {
        add_tree_leaf_particles(m);
        m->forwardVel = -8.0f;
        return set_mario_action(m, ACT_FREEFALL, 0);
    }
    if (m->input & INPUT_A_PRESSED) {
        add_tree_leaf_particles(m);
        if (analog_stick_held_back(m, DEG(90))) {
            m->faceAngle[1]  = m->intendedYaw;
        } else {
            m->faceAngle[1] += DEG(180);
        }
        return set_mario_action(m, ACT_WALL_KICK_AIR, 0);
    }
#endif
    if (set_pole_position(m, 0.0f) == POLE_NONE) {
        set_mario_animation(m, MARIO_ANIM_GRAB_POLE_SHORT);
        if (is_anim_at_end(m)) set_mario_action(m, ACT_HOLDING_POLE, 0);
        add_tree_leaf_particles(m);
    }
    return FALSE;
}

Bool32 act_grab_pole_fast(struct MarioState *m) {
    play_sound_if_no_flag(m, SOUND_MARIO_WHOA, MARIO_MARIO_SOUND_PLAYED);
    m->faceAngle[1] += m->angleVel[1];
    if (ABSI(m->angleVel[1]) > 0x1) {
        m->angleVel[1] *= 0.8f;
    } else {
        m->angleVel[1] = 0x0;
    }
#if defined(ACTION_CANCELS) || defined(POLE_SWING)
    if ((m->input & (INPUT_B_PRESSED | INPUT_Z_PRESSED)) || (m->health < 0x100)) {
        add_tree_leaf_particles(m);
        m->forwardVel = -8.0f;
        return set_mario_action(m, ACT_FREEFALL, 0);
    }
    if (m->input & INPUT_A_PRESSED) {
        add_tree_leaf_particles(m);
        if (m->input & INPUT_NONZERO_ANALOG) {
            m->faceAngle[1]  = m->intendedYaw;
        } else {
            m->faceAngle[1] += DEG(180);
        }
        return set_mario_action(m, ACT_WALL_KICK_AIR, 0);
    }
#endif
    if (set_pole_position(m, 0.0f) == POLE_NONE) {
        if (ABSI(m->angleVel[1]) > 0x800) {
            set_mario_animation(m, MARIO_ANIM_GRAB_POLE_SWING_PART1);
        } else {
            set_mario_animation(m, MARIO_ANIM_GRAB_POLE_SWING_PART2);
            if (is_anim_at_end(m) || (m->angleVel[1] == 0x0)) set_mario_action(m, ACT_HOLDING_POLE, 0);
        }
        add_tree_leaf_particles(m);
    }
    return FALSE;
}

Bool32 act_top_of_pole_transition(struct MarioState *m) {
    m->angleVel[1] = 0x0;
    if (m->actionArg == 0) {
        set_mario_animation(m, MARIO_ANIM_START_HANDSTAND);
        if (is_anim_at_end(m)) return set_mario_action(m, ACT_TOP_OF_POLE, 0);
    } else {
        set_mario_animation(m, MARIO_ANIM_RETURN_FROM_HANDSTAND);
        if (m->marioObj->header.gfx.animInfo.animFrame == 0) return set_mario_action(m, ACT_HOLDING_POLE, 0);
    }
    set_pole_position(m, return_mario_anim_y_translation(m));
    return FALSE;
}

Bool32 act_top_of_pole(struct MarioState *m) {
    if (m->input & INPUT_A_PRESSED    ) return set_mario_action(m, ACT_TOP_OF_POLE_JUMP      , 0);
    if (m->controller->stickY < -16.0f) return set_mario_action(m, ACT_TOP_OF_POLE_TRANSITION, 1);
    m->faceAngle[1] -= (m->controller->stickX * 16.0f);
    set_mario_animation(m, MARIO_ANIM_HANDSTAND_IDLE);
    set_pole_position(m, return_mario_anim_y_translation(m));
    return FALSE;
}

s32 perform_hanging_step(struct MarioState *m, Vec3f nextPos) {
    struct WallCollisionData wallData;
    struct Surface *ceil;
    struct Surface *floor;
    f32 ceilHeight;
    f32 floorHeight;
    f32 ceilOffset;
    resolve_and_return_wall_collisions(nextPos, 50.0f, 50.0f, &wallData);
    m->wall     = wallData.walls[0];
    floorHeight = find_floor(nextPos[0], (nextPos[1] + m->midY), nextPos[2], &floor);
    ceilHeight  = find_ceil( nextPos[0], (nextPos[1] + m->midY), nextPos[2], &ceil);
    if (floor == NULL                                          ) return HANG_HIT_CEIL_OR_OOB;
    if (ceil  == NULL                                          ) return HANG_LEFT_CEIL;
    if (ceilHeight - floorHeight <= MARIO_HANGING_HITBOX_HEIGHT) return HANG_HIT_CEIL_OR_OOB;
    if (ceil->type != SURFACE_HANGABLE                         ) return HANG_LEFT_CEIL;
    ceilOffset = (ceilHeight - (nextPos[1] + MARIO_HANGING_HITBOX_HEIGHT));
    if (ceilOffset < -30.0f                                    ) return HANG_HIT_CEIL_OR_OOB;
    if (ceilOffset >  30.0f                                    ) return HANG_LEFT_CEIL;
    nextPos[1] = (m->ceilHeight - MARIO_HANGING_HITBOX_HEIGHT);
    vec3f_copy(m->pos, nextPos);
    if (m->floor != floor) m->floorYaw = atan2s(floor->normal.z, floor->normal.x);
    m->floor       = floor;
    m->floorHeight = floorHeight;
    m->ceil        = ceil;
    m->ceilHeight  = ceilHeight;
    return HANG_NONE;
}

MarioStep update_hang_moving(struct MarioState *m) {
    MarioStep stepResult;
    Vec3f nextPos;
#ifdef EASIER_HANGING
    f32 maxSpeed = (m->intendedMag / 2.0f);
#else
    f32 maxSpeed = HANGING_SPEED;
#endif
    m->forwardVel += 1.0f;
    if (m->forwardVel > maxSpeed) m->forwardVel = maxSpeed;
#ifdef TIGHTER_HANGING_CONTROLS
    m->faceAngle[1] = m->intendedYaw;
#else
    approach_s16_symmetric_bool(&m->faceAngle[1], m->intendedYaw, 0x800);
#endif
    m->slideYaw  =                       m->faceAngle[1];
    m->slideVelX = (m->forwardVel * sins(m->faceAngle[1]));
    m->slideVelZ = (m->forwardVel * coss(m->faceAngle[1]));
    m->vel[0]    = m->slideVelX;
    m->vel[1]    = 0.0f;
    m->vel[2]    = m->slideVelZ;
    nextPos[0]   = (m->pos[0] - (m->ceil->normal.y * m->vel[0]));
    nextPos[2]   = (m->pos[2] - (m->ceil->normal.y * m->vel[2]));
    nextPos[1]   =  m->pos[1];
    stepResult   = perform_hanging_step(m, nextPos);
    vec3f_copy(m->marioObj->header.gfx.pos, m->pos);
    vec3a_set( m->marioObj->header.gfx.angle, 0x0, m->faceAngle[1], 0x0);
    return stepResult;
}

void update_hang_stationary(struct MarioState *m) {
    m->forwardVel = 0.0f;
    m->slideVelX  = 0.0f;
    m->slideVelZ  = 0.0f;
    m->pos[1]     = (m->ceilHeight - MARIO_HANGING_HITBOX_HEIGHT);
    vec3f_zero(m->vel);
    vec3f_copy(m->marioObj->header.gfx.pos, m->pos);
#ifdef EASIER_HANGING
    vec3a_set(m->marioObj->header.gfx.angle, 0x0, m->faceAngle[1], 0x0);
#endif
}

Bool32 act_start_hanging(struct MarioState *m) {
#if ENABLE_RUMBLE
    if (m->actionTimer++ == 0) queue_rumble_data(5, 80);
#else
    m->actionTimer++;
#endif
#ifdef EASIER_HANGING
    if ((m->input & INPUT_NONZERO_ANALOG) && (m->intendedMag > 16.0f) && (m->actionTimer > 1)) return set_mario_action(m, ACT_HANGING     , 0);
    if ( m->input & (INPUT_A_PRESSED | INPUT_B_PRESSED)                                      ) return set_mario_action(m, ACT_FREEFALL    , 0);
#else
    if ((m->input & INPUT_NONZERO_ANALOG) && (m->actionTimer >= 31)                          ) return set_mario_action(m, ACT_HANGING     , 0);
    if (!(m->input & INPUT_A_DOWN)                                                           ) return set_mario_action(m, ACT_FREEFALL    , 0);
#endif
    if (m->input & INPUT_Z_PRESSED                                                           ) return set_mario_action(m, ACT_GROUND_POUND, 0);
    if ((m->ceil == NULL) || (m->ceil->type != SURFACE_HANGABLE)                             ) return set_mario_action(m, ACT_FREEFALL    , 0);
    set_mario_animation(m, MARIO_ANIM_HANG_ON_CEILING);
    play_sound_if_no_flag(m, SOUND_ACTION_HANGING_STEP, MARIO_ACTION_SOUND_PLAYED);
    update_hang_stationary(m);
    if (is_anim_at_end(m)) set_mario_action(m, ACT_HANGING, 0);
    return FALSE;
}

Bool32 act_hanging(struct MarioState *m) {
    if (m->input & INPUT_NONZERO_ANALOG                         ) return set_mario_action(m, ACT_HANG_MOVING , m->actionArg);
#ifdef EASIER_HANGING
    if (m->input & (INPUT_A_PRESSED | INPUT_B_PRESSED)          ) return set_mario_action(m, ACT_FREEFALL    , 0);
#else
    if (!(m->input & INPUT_A_DOWN)                              ) return set_mario_action(m, ACT_FREEFALL    , 0);
#endif
    if (m->input & INPUT_Z_PRESSED                              ) return set_mario_action(m, ACT_GROUND_POUND, 0);
    if ((m->ceil == NULL) || (m->ceil->type != SURFACE_HANGABLE)) return set_mario_action(m, ACT_FREEFALL    , 0);

    set_mario_animation(m, (m->actionArg & 1) ? MARIO_ANIM_HANDSTAND_LEFT : MARIO_ANIM_HANDSTAND_RIGHT);
    update_hang_stationary(m);
    return FALSE;
}

Bool32 act_hang_moving(struct MarioState *m) {
#ifdef EASIER_HANGING
    if (m->input & (INPUT_A_PRESSED | INPUT_B_PRESSED)          ) return set_mario_action(m, ACT_FREEFALL    , 0);
#else
    if (!(m->input & INPUT_A_DOWN)                              ) return set_mario_action(m, ACT_FREEFALL    , 0);
#endif
    if (m->input & INPUT_Z_PRESSED                              ) return set_mario_action(m, ACT_GROUND_POUND, 0);
    if ((m->ceil == NULL) || (m->ceil->type != SURFACE_HANGABLE)) return set_mario_action(m, ACT_FREEFALL    , 0);
#ifdef EASIER_HANGING
    set_mario_anim_with_accel(m, ((m->actionArg & 1) ? MARIO_ANIM_MOVE_ON_WIRE_NET_RIGHT : MARIO_ANIM_MOVE_ON_WIRE_NET_LEFT), ((m->forwardVel + 1.0f) * 0x2000));
#else
    set_mario_animation(m, ((m->actionArg & 1) ? MARIO_ANIM_MOVE_ON_WIRE_NET_RIGHT : MARIO_ANIM_MOVE_ON_WIRE_NET_LEFT));
#endif
    if (m->marioObj->header.gfx.animInfo.animFrame == 12) {
        play_sound(SOUND_ACTION_HANGING_STEP, m->marioObj->header.gfx.cameraToObject);
#if ENABLE_RUMBLE
        queue_rumble_data(1, 30);
#endif
    }
    if (is_anim_past_end(m)) m->actionArg ^= 1;
    if (m->input & INPUT_IDLE                  ) return set_mario_action(m, ACT_HANGING , m->actionArg);
    if (update_hang_moving(m) == HANG_LEFT_CEIL)        set_mario_action(m, ACT_FREEFALL, 0);
    return FALSE;
}

Bool32 let_go_of_ledge(struct MarioState *m) {
    struct Surface *floor;
    m->vel[1]     =  0.0f;
    m->forwardVel = -8.0f;
    m->pos[0]    -= 60.0f * sins(m->faceAngle[1]);
    m->pos[2]    -= 60.0f * coss(m->faceAngle[1]);
    f32 floorHeight = find_floor(m->pos[0], m->pos[1], m->pos[2], &floor);
    if (floorHeight < (m->pos[1] - 100.0f)) {
        m->pos[1] -= 100.0f;
    } else {
        m->pos[1] = floorHeight;
    }
    return set_mario_action(m, ACT_SOFT_BONK, 0);
}

void climb_up_ledge(struct MarioState *m) {
    set_mario_animation(m, MARIO_ANIM_IDLE_HEAD_LEFT);
    m->pos[0] += (14.0f * sins(m->faceAngle[1]));
    m->pos[2] += (14.0f * coss(m->faceAngle[1]));
    vec3f_copy(m->marioObj->header.gfx.pos, m->pos);
}

void update_ledge_climb_camera(struct MarioState *m) {
    f32 dist = ((m->actionTimer < 14) ? m->actionTimer : 14.0f);
    m->statusForCamera->pos[0] = (m->pos[0] + (dist * sins(m->faceAngle[1])));
    m->statusForCamera->pos[2] = (m->pos[2] + (dist * coss(m->faceAngle[1])));
    m->statusForCamera->pos[1] =  m->pos[1];
    m->actionTimer++;
    m->flags |= MARIO_LEDGE_CLIMB_CAMERA;
}

void update_ledge_climb(struct MarioState *m, AnimID32 animation, MarioAction endAction) {
    stop_and_set_height_to_floor(m);
    set_mario_animation(m, animation);
    if (is_anim_at_end(m)) {
        set_mario_action(m, endAction, 0);
        if (endAction == ACT_IDLE) climb_up_ledge(m);
    }
#ifdef LEDGE_SIDLE
    if ((m->floor != NULL) && (m->floor->normal.y < NEAR_ONE)) m->marioObj->header.gfx.angle[2] = ((atan2s(sqrtf(sqr(m->floor->normal.z) + sqr(m->floor->normal.x)), m->floor->normal.y) - DEG(90)) * sins(m->wallYaw - m->floorYaw));
#endif
}

Bool32 act_ledge_grab(struct MarioState *m) {
    f32 heightAboveFloor;
    Angle intendedDYaw   = (m->intendedYaw - m->faceAngle[1]);
    s32 hasSpaceForMario = ((m->ceilHeight - m->floorHeight) >= MARIO_HITBOX_HEIGHT);
#ifdef LEDGE_SIDLE
    AnimAccel accel   = 0x10000;
    f32 sidewaysSpeed = 0.0f;
    f32 nextX         = m->pos[0];
    f32 nextZ         = m->pos[2];
    UNUSED f32 nextFloorHeight = FLOOR_LOWER_LIMIT;
    struct Surface *nextFloor;
    struct WallCollisionData wallCols;
    struct Surface *floor;
    f32 floorHeight;
    struct Surface *oldWwall;
    struct Surface *wall;
    Angle oldWallAngle, oldWallDYaw;
    Angle newWallAngle, newWallDYaw;
    s32 i;
#endif
    if (m->floor->normal.y < COS25                                      ) return let_go_of_ledge(m);
#ifdef FIX_LEDGE_GRABS
    if ((m->wall != NULL) && ((m->wall->normal.y > MIN_FLOOR_NORMAL_Y) || (m->wall->normal.y < MAX_CEIL_NORMAL_Y))) return let_go_of_ledge(m);
#endif
#ifdef ACTION_CANCELS
    if (m->input & (INPUT_B_PRESSED | INPUT_Z_PRESSED | INPUT_OFF_FLOOR)) return let_go_of_ledge(m);
#else
    if (m->input & (INPUT_Z_PRESSED | INPUT_OFF_FLOOR)                  ) return let_go_of_ledge(m);
#endif
    if ((m->input & INPUT_A_PRESSED) && hasSpaceForMario                ) return set_mario_action(m, ACT_LEDGE_CLIMB_FAST, 0);
    if (m->input & INPUT_STOMPED) {
        if ((m->marioObj->oInteractStatus) & INT_STATUS_MARIO_KNOCKBACK_DMG) m->hurtCounter += ((m->flags & MARIO_CAP_ON_HEAD) ? 12 : 18);
        return let_go_of_ledge(m);
    }
    m->actionTimer++;
#ifdef ACTION_CANCELS
    if ((m->actionTimer >=  5) && (m->input & INPUT_NONZERO_ANALOG)) {
        if (m->actionTimer >= 0xFFFF) m->actionTimer = 5;
#else
    if ((m->actionTimer >= 10) && (m->input & INPUT_NONZERO_ANALOG)) {
        if (m->actionTimer >= 0xFFFF) m->actionTimer = 10;
#endif
#ifdef LEDGE_SIDLE
        if (intendedDYaw >= -DEG(45) && intendedDYaw <= DEG(45)) {
            if (hasSpaceForMario) return set_mario_action(m, ACT_LEDGE_CLIMB_SLOW_1, 0);
        } else if (intendedDYaw <= -DEG(135) || intendedDYaw >= DEG(135)) {
            return let_go_of_ledge(m);
        }
        sidewaysSpeed = ((m->intendedMag / 4.0f) * sins(intendedDYaw));
        nextX += (sidewaysSpeed * sins(m->faceAngle[1] + DEG(90)));
        nextZ += (sidewaysSpeed * coss(m->faceAngle[1] + DEG(90)));
        //! TODO: Fix this for concave wall angles
        // Check for wall collisions, if new wall is closer to m->intendedYaw, switch to that one.
        vec3f_copy(wallCols.pos, m->pos);
        wallCols.pos[0]  = nextX;
        wallCols.pos[2]  = nextZ;
        wallCols.radius  =  10.0f;
        wallCols.offsetY = -10.0f;
        if (find_wall_collisions(&wallCols) != 0) {
            floorHeight = find_floor(wallCols.pos[0], (wallCols.pos[1] + m->midY), wallCols.pos[2], &floor);
            if ((floor != NULL) && ((wallCols.pos[1] - floorHeight) > MARIO_HITBOX_HEIGHT)) {
                oldWwall = m->wall;
                oldWallAngle = atan2s(oldWwall->normal.z, oldWwall->normal.x);
                oldWallDYaw  = abs_angle_diff(oldWallAngle, m->intendedYaw);
                for ((i = 0); (i < wallCols.numWalls); (i++)) {
                    wall         = wallCols.walls[i];
                    newWallAngle = atan2s(wall->normal.z, wall->normal.x);
                    newWallDYaw  = abs_angle_diff(newWallAngle, m->intendedYaw);
                    if (newWallDYaw < oldWallDYaw) {
                        oldWwall     = wall;
                        oldWallAngle = newWallAngle;
                        oldWallDYaw  = newWallDYaw;
                    }
                }
                nextX           = (wallCols.pos[0] - (20.0f * oldWwall->normal.x));
                nextZ           = (wallCols.pos[2] - (20.0f * oldWwall->normal.z));
                m->faceAngle[0] = 0x0;
                m->faceAngle[1] = (oldWallAngle + DEG(180));
                m->wall         = oldWwall;
            }
        }
        // Prevent moving OOB
        nextFloorHeight = find_floor(nextX, (m->pos[1] + 80.0f), nextZ, &nextFloor);
        if (nextFloor != NULL) {
            m->pos[0] = nextX;
            m->pos[2] = nextZ;
            accel *= ABSF(sidewaysSpeed);
            if ((m->actionTimer % (u32)absf(sidewaysSpeed * 2.0f)) == 0) {
                play_sound((SOUND_MOVING_TERRAIN_SLIDE + m->terrainSoundAddend), m->marioObj->header.gfx.cameraToObject);
                m->particleFlags |= PARTICLE_DUST;
            }
        }
#else
        if (intendedDYaw >= -DEG(90) && intendedDYaw <= DEG(90)) {
            if (hasSpaceForMario) return set_mario_action(m, ACT_LEDGE_CLIMB_SLOW_1, 0);
        } else {
            return let_go_of_ledge(m);
        }
#endif
    }
    heightAboveFloor = (m->pos[1] - find_floor_height_relative_polar(m, -DEG(180), 30.0f));
    if (hasSpaceForMario && (heightAboveFloor < 100.0f)) return set_mario_action(m, ACT_LEDGE_CLIMB_FAST, 0);
    if (m->actionArg == 0) play_sound_if_no_flag(m, SOUND_MARIO_WHOA, MARIO_MARIO_SOUND_PLAYED);
    stop_and_set_height_to_floor(m);
#ifdef LEDGE_SIDLE
    set_mario_anim_with_accel(m, MARIO_ANIM_IDLE_ON_LEDGE, accel);
    if ((m->floor != NULL) && (m->floor->normal.y < NEAR_ONE)) m->marioObj->header.gfx.angle[2] = ((atan2s(sqrtf(sqr(m->floor->normal.z) + sqr(m->floor->normal.x)), m->floor->normal.y) - DEG(90)) * sins(m->wallYaw - m->floorYaw));
#else
    set_mario_animation(m, MARIO_ANIM_IDLE_ON_LEDGE);
#endif
    return FALSE;
}

Bool32 act_ledge_climb_slow(struct MarioState *m) {
    if (m->input & INPUT_OFF_FLOOR) return let_go_of_ledge(m);
    if ((m->actionTimer >= 28) && (m->input & (INPUT_NONZERO_ANALOG | INPUT_A_PRESSED | INPUT_OFF_FLOOR | INPUT_ABOVE_SLIDE))) {
        climb_up_ledge(m);
        return check_common_action_exits(m);
    }
    if (m->actionTimer == 10) play_sound_if_no_flag(m, SOUND_MARIO_EEUH, MARIO_MARIO_SOUND_PLAYED);
    update_ledge_climb(m, MARIO_ANIM_SLOW_LEDGE_CLIMB, ACT_IDLE);
    update_ledge_climb_camera(m);
    if (m->marioObj->header.gfx.animInfo.animFrame == 17) m->action = ACT_LEDGE_CLIMB_SLOW_2;
    return FALSE;
}

Bool32 act_ledge_climb_down(struct MarioState *m) {
    if (m->input & INPUT_OFF_FLOOR) return let_go_of_ledge(m);
    play_sound_if_no_flag(m, SOUND_MARIO_WHOA, MARIO_MARIO_SOUND_PLAYED);
    update_ledge_climb(m, MARIO_ANIM_CLIMB_DOWN_LEDGE, ACT_LEDGE_GRAB);
    m->actionArg = 1;
    return FALSE;
}

Bool32 act_ledge_climb_fast(struct MarioState *m) {
    if (m->input & INPUT_OFF_FLOOR) return let_go_of_ledge(m);
    play_sound_if_no_flag(m, SOUND_MARIO_UH_LEDGE_CLIMB_FAST, MARIO_MARIO_SOUND_PLAYED);
    update_ledge_climb(m, MARIO_ANIM_FAST_LEDGE_CLIMB, ACT_IDLE);
    if (m->marioObj->header.gfx.animInfo.animFrame == 8) play_mario_landing_sound(m, SOUND_ACTION_TERRAIN_LANDING);
    update_ledge_climb_camera(m);
    return FALSE;
}

Bool32 act_grabbed(struct MarioState *m) {
    if (m->marioObj->oInteractStatus & INT_STATUS_MARIO_UNK2) {
        s32 thrown = ((m->marioObj->oInteractStatus & INT_STATUS_MARIO_UNK6) == 0);
        m->faceAngle[1] = m->usedObj->oMoveAngleYaw;
        vec3f_copy(m->pos, m->marioObj->header.gfx.pos);
#if ENABLE_RUMBLE
        queue_rumble_data(5, 60);
#endif
        return set_mario_action(m, (m->forwardVel >= 0.0f) ? ACT_THROWN_FORWARD : ACT_THROWN_BACKWARD, thrown);
    }
    set_mario_animation(m, MARIO_ANIM_BEING_GRABBED);
    return FALSE;
}

Bool32 act_in_cannon(struct MarioState *m) {
    struct Object *marioObj = m->marioObj;
    Angle startFacePitch    = m->faceAngle[0];
    Angle startFaceYaw      = m->faceAngle[1];
    switch (m->actionState) {
        case ACT_IN_CANNON_STATE_INIT:
            m->marioObj->header.gfx.node.flags &= ~GRAPH_RENDER_ACTIVE;
            m->usedObj->oInteractStatus         = INT_STATUS_INTERACTED;
            m->statusForCamera->cameraEvent     = CAM_EVENT_CANNON;
            m->statusForCamera->usedObj         = m->usedObj;
            vec3f_zero(m->vel);
            m->pos[0]      =  m->usedObj->oPosX;
            m->pos[1]      = (m->usedObj->oPosY + 350.0f);
            m->pos[2]      =  m->usedObj->oPosZ;
            m->forwardVel  = 0.0f;
            m->actionState = ACT_IN_CANNON_STATE_WAIT_FOR_CANNON;
            break;
        case ACT_IN_CANNON_STATE_WAIT_FOR_CANNON:
            if (m->usedObj->oAction == OPENED_CANNON_ACT_READY) {
                m->faceAngle[0]                 = m->usedObj->oMoveAnglePitch;
                m->faceAngle[1]                 = m->usedObj->oMoveAngleYaw;
                marioObj->oMarioCannonObjectYaw = m->usedObj->oMoveAngleYaw;
                marioObj->oMarioCannonInputYaw  = 0x0;
                m->actionState                  = ACT_IN_CANNON_STATE_READY;
            }
            break;
        case ACT_IN_CANNON_STATE_READY:
            m->faceAngle[0]                -= (Angle)(m->controller->stickY * 10.0f);
            marioObj->oMarioCannonInputYaw -= (Angle)(m->controller->stickX * 10.0f);
            if (m->faceAngle[0] > DEG(80)) m->faceAngle[0] = DEG(80);
            if (m->faceAngle[0] <     0x0) m->faceAngle[0] =     0x0;
            if (marioObj->oMarioCannonInputYaw >  DEG(45)) marioObj->oMarioCannonInputYaw =  DEG(45);
            if (marioObj->oMarioCannonInputYaw < -DEG(45)) marioObj->oMarioCannonInputYaw = -DEG(45);
            m->faceAngle[1] = (marioObj->oMarioCannonObjectYaw + marioObj->oMarioCannonInputYaw);
            if (m->input & INPUT_A_PRESSED) {
                m->forwardVel = (100.0f * coss(m->faceAngle[0])                        );
                m->vel[1]     = (100.0f * sins(m->faceAngle[0])                        );
                m->pos[0]    += (120.0f * coss(m->faceAngle[0]) * sins(m->faceAngle[1]));
                m->pos[1]    += (120.0f * sins(m->faceAngle[0])                        );
                m->pos[2]    += (120.0f * coss(m->faceAngle[0]) * coss(m->faceAngle[1]));
                play_sound(SOUND_ACTION_FLYING_FAST,  m->marioObj->header.gfx.cameraToObject);
                play_sound(SOUND_OBJ_POUNDING_CANNON, m->marioObj->header.gfx.cameraToObject);
                m->marioObj->header.gfx.node.flags |= GRAPH_RENDER_ACTIVE;
                set_mario_action(m, ACT_SHOT_FROM_CANNON, 0);
#if ENABLE_RUMBLE
                queue_rumble_data(60, 70);
#endif
                m->usedObj->oAction = OPENED_CANNON_ACT_SHOOT;
                return FALSE;
            } else if ((m->faceAngle[0] != startFacePitch) || (m->faceAngle[1] != startFaceYaw)) {
                play_sound(SOUND_MOVING_AIM_CANNON, m->marioObj->header.gfx.cameraToObject);
#if ENABLE_RUMBLE
                reset_rumble_timers_vibrate(0);
#endif
            }
    }
    vec3f_copy(m->marioObj->header.gfx.pos, m->pos);
    vec3a_set( m->marioObj->header.gfx.angle, 0x0, m->faceAngle[1], 0x0);
    set_mario_animation(m, MARIO_ANIM_DIVE);
    return FALSE;
}

Bool32 act_tornado_twirling(struct MarioState *m) {
    struct Surface *floor;
    Vec3f nextPos;
    f32 sinAngleVel, cosAngleVel;
    f32 floorHeight;
    struct Object *marioObj = m->marioObj;
    struct Object *usedObj  = m->usedObj;
    Angle prevTwirlYaw        = m->twirlYaw;
    f32 dx = ((m->pos[0] - usedObj->oPosX) * 0.95f);
    f32 dz = ((m->pos[2] - usedObj->oPosZ) * 0.95f);
    if (m->vel[1] < 60.0f) m->vel[1] += 1.0f;
    if ((marioObj->oMarioTornadoPosY += m->vel[1]) < 0.0f) marioObj->oMarioTornadoPosY = 0.0f;
    if (marioObj->oMarioTornadoPosY > usedObj->hitboxHeight) {
        if (m->vel[1] < 20.0f) m->vel[1] = 20.0f;
        return set_mario_action(m, ACT_TWIRLING, 1);
    }
    if (m->angleVel[1] < DEG(67.5)) m->angleVel[1] += 0x100;
    if (marioObj->oMarioTornadoYawVel < 0x1000) marioObj->oMarioTornadoYawVel += 0x100;
    m->twirlYaw += m->angleVel[1];
    sinAngleVel  = sins(marioObj->oMarioTornadoYawVel);
    cosAngleVel  = coss(marioObj->oMarioTornadoYawVel);
    nextPos[0]   = (usedObj->oPosX + (dx * cosAngleVel) + (dz * sinAngleVel));
    nextPos[2]   = (usedObj->oPosZ - (dx * sinAngleVel) + (dz * cosAngleVel));
    nextPos[1]   = (usedObj->oPosY + marioObj->oMarioTornadoPosY);
    f32_find_wall_collision(&nextPos[0], &nextPos[1], &nextPos[2], 60.0f, 50.0f);
    floorHeight = find_floor(nextPos[0],  nextPos[1],  nextPos[2], &floor);
    if (floor != NULL) {
        if (m->floor != floor) m->floorYaw = atan2s(floor->normal.z, floor->normal.x);
        m->floor       = floor;
        m->floorHeight = floorHeight;
        vec3f_copy(m->pos, nextPos);
    } else {
        if (nextPos[1] >= m->floorHeight) {
            m->pos[1] = nextPos[1];
        } else {
            m->pos[1] = m->floorHeight;
        }
    }
    m->actionTimer++;
    set_mario_animation(m, (m->actionArg == 0) ? MARIO_ANIM_START_TWIRL : MARIO_ANIM_TWIRL);
    if (is_anim_past_end(m)) m->actionArg = 1;
    // Play sound on angle overflow
    if (prevTwirlYaw > m->twirlYaw) play_sound(SOUND_ACTION_TWIRL, m->marioObj->header.gfx.cameraToObject);
    vec3f_copy(m->marioObj->header.gfx.pos, m->pos);
    vec3a_set( m->marioObj->header.gfx.angle, 0x0, (m->faceAngle[1] + m->twirlYaw), 0x0);
#if ENABLE_RUMBLE
    reset_rumble_timers_slip();
#endif
    return FALSE;
}

Bool32 check_common_automatic_cancels(struct MarioState *m) {
    if (m->pos[1] < m->waterLevel - 100) return set_water_plunge_action(m);
    return FALSE;
}

Bool32 mario_execute_automatic_action(struct MarioState *m) {
    Bool32 cancel = FALSE;
    if (check_common_automatic_cancels(m)) return TRUE;
    m->quicksandDepth = 0.0f;
    /* clang-format off */
    switch (m->action) {
        case ACT_HOLDING_POLE:           cancel = act_holding_pole(m);           break;
        case ACT_GRAB_POLE_SLOW:         cancel = act_grab_pole_slow(m);         break;
        case ACT_GRAB_POLE_FAST:         cancel = act_grab_pole_fast(m);         break;
        case ACT_CLIMBING_POLE:          cancel = act_climbing_pole(m);          break;
        case ACT_TOP_OF_POLE_TRANSITION: cancel = act_top_of_pole_transition(m); break;
        case ACT_TOP_OF_POLE:            cancel = act_top_of_pole(m);            break;
        case ACT_START_HANGING:          cancel = act_start_hanging(m);          break;
        case ACT_HANGING:                cancel = act_hanging(m);                break;
        case ACT_HANG_MOVING:            cancel = act_hang_moving(m);            break;
        case ACT_LEDGE_GRAB:             cancel = act_ledge_grab(m);             break;
        case ACT_LEDGE_CLIMB_SLOW_1:     cancel = act_ledge_climb_slow(m);       break;
        case ACT_LEDGE_CLIMB_SLOW_2:     cancel = act_ledge_climb_slow(m);       break;
        case ACT_LEDGE_CLIMB_DOWN:       cancel = act_ledge_climb_down(m);       break;
        case ACT_LEDGE_CLIMB_FAST:       cancel = act_ledge_climb_fast(m);       break;
        case ACT_GRABBED:                cancel = act_grabbed(m);                break;
        case ACT_IN_CANNON:              cancel = act_in_cannon(m);              break;
        case ACT_TORNADO_TWIRLING:       cancel = act_tornado_twirling(m);       break;
        default:                         cancel = act_ledge_grab(m);             break;
    }
    /* clang-format on */
    return cancel;
}
