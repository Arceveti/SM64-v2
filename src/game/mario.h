#pragma once

#include <PR/ultratypes.h>

#include "macros.h"
#include "types.h"
#include "engine/surface_collision.h"

Bool32 is_anim_at_end(                       struct MarioState *m);
Bool32 is_anim_past_end(                     struct MarioState *m);
AnimFrame16 set_mario_animation(             struct MarioState *m, AnimID32 targetAnimID);
AnimFrame16 set_mario_anim_with_accel(       struct MarioState *m, AnimID32 targetAnimID, AnimAccel accel);
void   set_anim_to_frame(                    struct MarioState *m, AnimFrame16 animFrame);
Bool32 is_anim_past_frame(                   struct MarioState *m, AnimFrame16 animFrame);
s32    find_mario_anim_flags_and_translation(struct Object *marioObj, Angle32 yaw, Vec3s translation);
void   update_mario_pos_for_anim(            struct MarioState *m);
s32    return_mario_anim_y_translation(      struct MarioState *m);
void   play_sound_if_no_flag(                struct MarioState *m, u32 soundBits, u32 flags);
void   play_mario_jump_sound(                struct MarioState *m);
void   adjust_sound_for_speed(               struct MarioState *m);
void   play_sound_and_spawn_particles(       struct MarioState *m, u32 soundBits, u32 waveParticleType);
void   play_mario_action_sound(              struct MarioState *m, u32 soundBits, u32 waveParticleType);
void   play_mario_landing_sound(             struct MarioState *m, u32 soundBits);
void   play_mario_landing_sound_once(        struct MarioState *m, u32 soundBits);
void   play_mario_heavy_landing_sound(       struct MarioState *m, u32 soundBits);
void   play_mario_heavy_landing_sound_once(  struct MarioState *m, u32 soundBits);
void   play_mario_sound(                     struct MarioState *m, s32 primarySoundBits, s32 scondarySoundBits);
Bool32 mario_is_shocked(                     struct MarioState *m);
Bool32 mario_is_burning(                     struct MarioState *m);
void   mario_set_forward_vel(                struct MarioState *m, f32 speed);
s32    mario_get_floor_class(                struct MarioState *m);
u32    mario_get_terrain_sound_addend(       struct MarioState *m);
Bool32 mario_facing_downhill(                struct MarioState *m, Bool32 turnYaw);
Bool32 mario_floor_is_slippery(              struct MarioState *m);
Bool32 mario_floor_is_slope(                 struct MarioState *m);
Bool32 mario_floor_is_steep(                 struct MarioState *m);
f32    find_floor_height_relative_polar(     struct MarioState *m, Angle angleFromMario, f32 distFromMario);
#if !defined(FIX_RELATIVE_SLOPE_ANGLE_MOVEMENT) || !defined (SMOOTH_WATER_FLOOR_PITCH) || !defined(FIX_WALL_SIDLE_SLOPE)
Angle  find_floor_slope(                     struct MarioState *m, Angle yawOffset,      f32 distFromMario);
#endif
Bool32 set_mario_wall( struct MarioState *m, struct Surface *wall);
Bool32 set_mario_ceil( struct MarioState *m, struct Surface *ceil,  f32 ceilHeight);
Bool32 set_mario_floor(struct MarioState *m, struct Surface *floor, f32 floorHeight);
Bool32 analog_stick_held_back(               struct MarioState *m, Angle range);
void   update_mario_sound_and_camera(        struct MarioState *m);
void   set_steep_jump_action(                struct MarioState *m);
Bool32 set_mario_action(                     struct MarioState *m, MarioAction action, u32 actionArg);
Bool32 set_jump_from_landing(                struct MarioState *m);
Bool32 set_jumping_action(                   struct MarioState *m, MarioAction action, u32 actionArg);
Bool32 drop_and_set_mario_action(            struct MarioState *m, MarioAction action, u32 actionArg);
Bool32 hurt_and_set_mario_action(            struct MarioState *m, MarioAction action, u32 actionArg, s16 hurtCounter);
Bool32 check_common_action_exits(            struct MarioState *m);
Bool32 check_common_hold_action_exits(       struct MarioState *m);
Bool32 transition_submerged_to_walking(      struct MarioState *m);
Bool32 transition_submerged_to_airborne(     struct MarioState *m);
Bool32 set_water_plunge_action(              struct MarioState *m);
Bool32 execute_mario_action(                 struct MarioState *m);
#ifdef VARIABLE_FRAMERATE
void   debug_print_speed_action_normal(      struct MarioState *m);
#endif
void   init_mario(void);
void   init_mario_from_save_file(void);
