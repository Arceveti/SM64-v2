#ifndef OBJ_BEHAVIORS_2_NONSTATIC_H
#define OBJ_BEHAVIORS_2_NONSTATIC_H

#include "object_fields.h"
#include "object_constants.h"
#include "object_helpers.h"
#include "object_collision.h"
#include "obj_behaviors.h"
#include "object_list_processor.h"
#include "interaction.h"
#include "behavior_data.h"
#include "engine/behavior_script.h"
#include "engine/math_util.h"
#include "engine/surface_load.h"
#include "engine/surface_collision.h"
#include "sound_init.h"
#include "spawn_sound.h"
#include "farcall.h"
#include "audio/external.h"
#include "level_update.h"
#include "mario.h"
#include "save_file.h"

#define o gCurrentObject

s32  obj_is_rendering_enabled(void);
s16  obj_get_pitch_from_vel(void);
s32  obj_update_race_proposition_dialog(s16 dialogID);
void obj_set_dist_from_home(f32 distFromHome);
s32  obj_is_near_to_and_facing_mario(f32 maxDist, s16 maxAngleDiff);
void obj_perform_position_op(s32 op);
void cur_obj_spin_all_dimensions(f32 arg0, f32 arg1);
s16  obj_get_pitch_to_home(f32 latDistToHome);
void obj_compute_vel_from_move_pitch(f32 speed);
void cur_obj_init_anim_extend(s32 arg0);
s32  cur_obj_init_anim_and_check_if_end(s32 arg0);
s32  cur_obj_init_anim_check_frame(s32 arg0, s32 arg1);
s32  cur_obj_set_anim_if_at_end(s32 arg0);
s32  cur_obj_play_sound_at_anim_range(s8 arg0, s8 arg1, u32 sound);
s16  obj_turn_pitch_toward_mario(f32 targetOffsetY, Angle turnAmount);
s32  obj_forward_vel_approach(f32 target, f32 delta);
s32  obj_y_vel_approach(f32 target, f32 delta);
s32  obj_move_pitch_approach(Angle target, Angle delta);
s32  obj_face_pitch_approach(Angle targetPitch, Angle deltaPitch);
s32  obj_face_yaw_approach(Angle targetYaw, Angle deltaYaw);
s32  obj_face_roll_approach(Angle targetRoll, Angle deltaRoll);
s32  obj_smooth_turn(Angle *angleVel, s32 *angle, Angle targetAngle, f32 targetSpeedProportion, s16 accel, s16 minSpeed, s16 maxSpeed);
void obj_roll_to_match_yaw_turn(Angle targetYaw, Angle maxRoll, Angle rollSpeed);
s16  obj_random_fixed_turn(Angle delta);
s32  obj_grow_then_shrink(f32 *scaleVel, f32 shootFireScale, f32 endScale);
s32  oscillate_toward(s32 *value, f32 *vel, s32 target, f32 velCloseToZero, f32 accel,  f32 slowdown);
void obj_update_blinking(s32 *blinkTimer, s16 baseCycleLength, s16 cycleLengthRange, s16 blinkLength);
void obj_die_if_health_non_positive(void);
void obj_unused_die(void);
void obj_set_knockback_action(s32 attackType);
void obj_set_squished_action(void);
s32  obj_die_if_above_lava_and_health_non_positive(void);
s32  obj_handle_attacks(struct ObjectHitbox *hitbox, s32 attackedMarioAction, u8 *attackHandlers);
void obj_act_knockback(UNUSED f32 baseScale);
void obj_act_squished(f32 baseScale);
s32  obj_update_standard_actions(f32 scale);
s32  obj_check_attacks(struct ObjectHitbox *hitbox, s32 attackedMarioAction);
s32  obj_move_for_one_second(s32 endAction);
void treat_far_home_as_mario(f32 threshold);

#endif
