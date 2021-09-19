#pragma once

#include <PR/ultratypes.h>

#include "farcall.h"

#define ATTACK_HANDLER_NOP                                  0x0
#define ATTACK_HANDLER_DIE_IF_HEALTH_NON_POSITIVE           0x1
#define ATTACK_HANDLER_KNOCKBACK                            0x2
#define ATTACK_HANDLER_SQUISHED                             0x3
#define ATTACK_HANDLER_SPECIAL_KOOPA_LOSE_SHELL             0x4
#define ATTACK_HANDLER_SET_SPEED_TO_ZERO                    0x5
#define ATTACK_HANDLER_SPECIAL_WIGGLER_JUMPED_ON            0x6
#define ATTACK_HANDLER_SPECIAL_HUGE_GOOMBA_WEAKLY_ATTACKED  0x7
#define ATTACK_HANDLER_SQUISHED_WITH_BLUE_COIN              0x8

#define cur_obj_forward_vel_approach(target, delta) approach_f32_ptr(&o->oForwardVel, (target), (delta))
#define cur_obj_y_vel_approach(      target, delta) approach_f32_ptr(&o->oVelY,       (target), (delta))

Bool32 cur_obj_is_rendering_enabled(void);
Angle  cur_obj_get_pitch_from_vel(void);
s32    cur_obj_update_race_proposition_dialog(DialogID dialogID);
void   cur_obj_set_dist_from_home(f32 distFromHome);
Bool32 cur_obj_is_near_to_and_facing_mario(f32 maxDist, Angle maxAngleDiff);
void   cur_obj_perform_position_op(s32 op);
void   cur_obj_spin_all_dimensions(f32 pitchSpeed, f32 rollSpeed);
Angle  cur_obj_get_pitch_to_home(f32 latDistToHome);
void   cur_obj_compute_vel_from_move_pitch(f32 speed);
void   cur_obj_init_anim_extend(          s32 animIndex);
Bool32 cur_obj_init_anim_and_check_if_end(s32 animIndex);
Bool32 cur_obj_init_anim_check_frame(     s32 animIndex, AnimFrame32 frame);
Bool32 cur_obj_set_anim_if_at_end(        s32 animIndex);
Bool32 cur_obj_play_sound_at_anim_range(AnimFrame32 startFrame1, AnimFrame32 startFrame2, u32 sound);
Angle  cur_obj_turn_pitch_toward_mario(f32 targetOffsetY, Angle turnAmount);
Bool32 cur_obj_move_pitch_approach(Angle target,      Angle delta     );
Bool32 cur_obj_face_pitch_approach(Angle targetPitch, Angle deltaPitch);
Bool32 cur_obj_face_yaw_approach(  Angle targetYaw,   Angle deltaYaw  );
Bool32 cur_obj_face_roll_approach( Angle targetRoll,  Angle deltaRoll );
Bool32 cur_obj_smooth_turn(Angle *angleVel, s32 *angle, Angle targetAngle, f32 targetSpeedProportion, s16 accel, s16 minSpeed, s16 maxSpeed);
void   cur_obj_roll_to_match_yaw_turn(Angle targetYaw, Angle maxRoll, Angle rollSpeed);
Angle  cur_obj_random_fixed_turn(Angle delta);
s32    cur_obj_grow_then_shrink(f32 *scaleVel, f32 shootFireScale, f32 endScale);
Bool32 oscillate_toward(s32 *value, f32 *vel, s32 target, f32 velCloseToZero, f32 accel, f32 slowdown);
void   cur_obj_update_blinking(s32 *blinkTimer, s16 baseCycleLength, s16 cycleLengthRange, s16 blinkLength);
void   cur_obj_die_if_health_non_positive(void);
void   obj_unused_die(void);
void   cur_obj_set_knockback_action(s32 attackType);
void   cur_obj_set_squished_action(void);
Bool32 cur_obj_die_if_above_lava_and_health_non_positive(void);
s32    cur_obj_handle_attacks(struct ObjectHitbox *hitbox, s32 attackedMarioAction, u8 *attackHandlers);
void   cur_obj_act_knockback(UNUSED f32 baseScale);
void   cur_obj_act_squished(f32 baseScale);
Bool32 cur_obj_update_standard_actions(f32 scale);
s32    cur_obj_check_attacks(struct ObjectHitbox *hitbox, s32 attackedMarioAction);
Bool32 cur_obj_move_for_one_second(s32 endAction);
void   cur_obj_treat_far_home_as_mario(f32 threshold);

void   shelled_koopa_attack_handler(s32 attackType);
void   cur_obj_spit_fire(s16 relativePosX, s16 relativePosY, s16 relativePosZ, f32 scale, ModelID32 model, f32 startSpeed, f32 endSpeed, Angle movePitch);
void   obj_set_speed_to_zero(void);
