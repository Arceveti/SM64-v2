#pragma once

#include <PR/ultratypes.h>

#include "macros.h"
#include "types.h"

// used for chain chomp and wiggler
struct ChainSegment
{
    Vec3f pos;
    Vec3a angle;
};

#define WATER_DROPLET_FLAG_RAND_ANGLE               (1 << 1) // 0x02
#define WATER_DROPLET_FLAG_RAND_OFFSET_XZ           (1 << 2) // 0x04 // Unused
#define WATER_DROPLET_FLAG_RAND_OFFSET_XYZ          (1 << 3) // 0x08 // Unused
#define WATER_DROPLET_FLAG_UNUSED                   (1 << 4) // 0x10 // Unused
#define WATER_DROPLET_FLAG_SET_Y_TO_WATER_LEVEL     (1 << 5) // 0x20
#define WATER_DROPLET_FLAG_RAND_ANGLE_INCR_BACKWARD (1 << 6) // 0x40
#define WATER_DROPLET_FLAG_RAND_ANGLE_INCR_FORWARD  (1 << 7) // 0x80 // Unused

// Call spawn_water_droplet with this struct to spawn an object.
struct WaterDropletParams
{
    s16 flags; // Droplet spawn flags, see defines above
    ModelID16 model;
    const BehaviorScript *behavior;
    Angle moveAngleRange; // Only used for RAND_ANGLE_INCR flags
    s16 moveRange;        // Only used for RAND_OFFSET flags
    f32 randForwardVelOffset;
    f32 randForwardVelScale;
    f32 randYVelOffset;
    f32 randYVelScale;
    f32 randSizeOffset;
    f32 randSizeScale;
};

// TODO: Field names
struct SpawnParticlesInfo
{
    /*0x00*/ s8        behParam;
    /*0x01*/ s8        count;
    /*0x02*/ ModelID16 model;
    /*0x03*/ s8        offsetY;
    /*0x04*/ s8        forwardVelBase;
    /*0x05*/ s8        forwardVelRange;
    /*0x06*/ s8        velYBase;
    /*0x07*/ s8        velYRange;
    /*0x08*/ s8        gravity;
    /*0x09*/ s8        dragStrength;
    /*0x0C*/ f32       sizeBase;
    /*0x10*/ f32       sizeRange;
};

// Mark an object to be unloaded at the end of the frame.
#define obj_mark_for_deletion(obj) ((obj)->activeFlags &= ~ACTIVE_FLAG_ACTIVE)

#define obj_copy_pos(  dstObj, srcObj) vec3_copy(&(dstObj)->oPosVec, &(srcObj)->oPosVec)
#define obj_copy_angle(dstObj, srcObj) {                            \
    vec3_copy(&(dstObj)->oMoveAngleVec, &(srcObj)->oMoveAngleVec);  \
    vec3_copy(&(dstObj)->oFaceAngleVec, &(srcObj)->oFaceAngleVec);  \
}
#define obj_copy_pos_and_angle(dstObj, srcObj) {    \
    obj_copy_pos(  (dstObj), (srcObj));             \
    obj_copy_angle((dstObj), (srcObj));             \
}

#define obj_set_gfx_pos_from_pos(obj)             vec3_copy(   (obj)->header.gfx.pos, &(obj)->oPosVec)
#define obj_copy_scale(dstObj, srcObj)            vec3_copy((dstObj)->header.gfx.scale, (srcObj)->header.gfx.scale)
#define obj_scale_xyz(obj, xScale, yScale, zScale) vec3_set(   (obj)->header.gfx.scale, (xScale), (yScale), (zScale))
// #define obj_scale(obj, scale) vec3_same(((obj)->header.gfx.scale), (scale)) //!
// #define cur_obj_scale(scale) vec3_same((o->header.gfx.scale), (scale)) //!

#define cur_obj_enable_rendering()  (o->header.gfx.node.flags |=  GRAPH_RENDER_ACTIVE   )
#define cur_obj_disable_rendering() (o->header.gfx.node.flags &= ~GRAPH_RENDER_ACTIVE   )
#define cur_obj_unhide()            (o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE)
#define cur_obj_hide()              (o->header.gfx.node.flags |=  GRAPH_RENDER_INVISIBLE)
#define obj_is_hidden(obj)      ((obj)->header.gfx.node.flags &   GRAPH_RENDER_INVISIBLE)

// When the timer is negative, the object is intangible and the timer
// doesn't count down
#define cur_obj_become_intangible() (    o->oIntangibleTimer = -1)
#define obj_become_intangible( obj) ((obj)->oIntangibleTimer = -1)
#define cur_obj_become_tangible(  ) (    o->oIntangibleTimer =  0)
#define obj_become_tangible(   obj) ((obj)->oIntangibleTimer =  0)

#define cur_obj_disable() {         \
    cur_obj_disable_rendering();    \
    cur_obj_hide();                 \
    cur_obj_become_intangible();    \
}

#define mario_is_in_air_action() (gMarioStates[0].action &  ACT_FLAG_AIR  )
#define mario_is_dive_sliding()  (gMarioStates[0].action == ACT_DIVE_SLIDE)

#define cur_obj_set_model( modelID) (    o->header.gfx.sharedChild  = gLoadedGraphNodes[modelID])
#define obj_set_model(obj, modelID) ((obj)->header.gfx.sharedChild  = gLoadedGraphNodes[modelID])
#define cur_obj_has_model( modelID) (    o->header.gfx.sharedChild == gLoadedGraphNodes[modelID])
#define obj_has_model(obj, modelID) ((obj)->header.gfx.sharedChild == gLoadedGraphNodes[modelID])

#define cur_obj_set_behavior( bhv) (    o->behavior  = segmented_to_virtual(bhv))
#define obj_set_behavior(obj, bhv) ((obj)->behavior  = segmented_to_virtual(bhv))
#define cur_obj_has_behavior( bhv) (    o->behavior == segmented_to_virtual(bhv))
#define obj_has_behavior(obj, bhv) ((obj)->behavior == segmented_to_virtual(bhv))

#define cur_obj_check_if_at_animation_end(void)                     (o->header.gfx.animInfo.animFrame == (o->header.gfx.animInfo.curAnim->loopEnd - 1))
#define cur_obj_check_anim_frame(frame)                             ((frame) == o->header.gfx.animInfo.animFrame)
#define cur_obj_check_anim_frame_in_range(startFrame, rangeLength)  ((o->header.gfx.animInfo.animFrame >= (startFrame)) && (o->header.gfx.animInfo.animFrame < ((startFrame) + (rangeLength))))

#define enable_time_stop(      void) (gTimeStopState |= TIME_STOP_ENABLED)
#define disable_time_stop(     void) (gTimeStopState &= ~TIME_STOP_ENABLED)
#define set_time_stop_flags(  flags) (gTimeStopState |= (flags))
#define clear_time_stop_flags(flags) (gTimeStopState  = (gTimeStopState & ((flags) ^ 0xFFFFFFFF)))

#define cur_obj_set_pos_to_home() vec3_copy(&o->oPosVec, &o->oHomeVec)
#define cur_obj_set_pos_relative_to_parent(dleft, dy, dforward) cur_obj_set_pos_relative(o->parentObj, (dleft), (dy), (dforward))

#define cur_obj_set_face_angle_to_move_angle() vec3_copy(&o->oFaceAngleVec, &o->oMoveAngleVec)
#define cur_obj_rotate_move_angle_using_vel()  vec3_add( &o->oMoveAngleVec, &o->oAngleVelVec )
// #define cur_obj_rotate_face_angle_using_vel()  vec3_add( &o->oFaceAngleVec, &o->oAngleVelVec )

Gfx            *geo_update_projectile_pos_from_parent(s32 callContext, UNUSED struct GraphNode *node, Mat4 mtx);
Gfx            *geo_update_layer_transparency(        s32 callContext,        struct GraphNode *node, UNUSED void *context);
Gfx            *geo_switch_anim_state(                s32 callContext,        struct GraphNode *node, UNUSED void *context);
Gfx            *geo_switch_room(                      s32 callContext,        struct GraphNode *node, UNUSED void *context);
void            obj_update_pos_from_parent_transformation(Mat4 mtx, struct Object *obj);
void            obj_apply_scale_to_matrix(   struct Object *obj, Mat4 dst, Mat4 src);
void            obj_set_held_state(          struct Object *obj,  const BehaviorScript *heldBehavior);
f32             lateral_dist_between_objects(struct Object *obj1, struct Object *obj2);
f32             dist_between_objects(        struct Object *obj1, struct Object *obj2);
f32             lateral_dist_between_objects_squared(struct Object *obj1, struct Object *obj2);
f32             dist_between_objects_squared(        struct Object *obj1, struct Object *obj2);
void            cur_obj_forward_vel_approach_upward(f32 target,   f32 increment);
Bool32          cur_obj_rotate_yaw_toward(        Angle target, Angle increment);
Angle           obj_angle_to_object(        struct Object *obj1, struct Object *obj2);
Angle           obj_turn_toward_object(     struct Object *obj, struct Object *target, s16 angleIndex, Angle turnAmount);
void            obj_set_parent_relative_pos(struct Object *obj, s16 relX, s16 relY, s16 relZ);
void            obj_set_pos(                struct Object *obj, s16 x,    s16 y,    s16 z);
void            obj_set_angle(              struct Object *obj, Angle pitch, Angle yaw, Angle roll);
struct Object  *spawn_object_abs_with_rot(                  struct Object *parent,       s16 uselessArg, ModelID32 model, const BehaviorScript *behavior, s16 x,    s16 y,    s16 z,    Angle rx, Angle ry,        Angle rz);
struct Object  *spawn_object_rel_with_rot(                  struct Object *parent,                       ModelID32 model, const BehaviorScript *behavior, s16 xOff, s16 yOff, s16 zOff, Angle rx, Angle ry, UNUSED Angle rz);
struct Object  *spawn_obj_with_transform_flags(             struct Object *parent,                       ModelID32 model, const BehaviorScript *behavior);
struct Object  *spawn_water_droplet(                        struct Object *parent, struct WaterDropletParams *params);
struct Object  *spawn_object_at_origin(                     struct Object *parent, UNUSED s32 unusedArg, ModelID32 model, const BehaviorScript *behavior);
struct Object  *spawn_object(                               struct Object *parent,                       ModelID32 model, const BehaviorScript *behavior);
struct Object  *try_to_spawn_object(s16 offsetY, f32 scale, struct Object *parent,                       ModelID32 model, const BehaviorScript *behavior);
struct Object  *spawn_object_with_scale(                    struct Object *parent,                       ModelID32 model, const BehaviorScript *behavior, f32 scale);
struct Object  *spawn_object_relative(           s16 behaviorParam, s16 relativePosX, s16 relativePosY, s16 relativePosZ,            struct Object *parent, ModelID32 model, const BehaviorScript *behavior);
struct Object  *spawn_object_relative_with_scale(s16 behaviorParam, s16 relativePosX, s16 relativePosY, s16 relativePosZ, f32 scale, struct Object *parent, ModelID32 model, const BehaviorScript *behavior);
ModelID32       obj_get_model_id(              struct Object *obj);
void            obj_apply_scale_to_transform(  struct Object *obj);
void            obj_scale(                     struct Object *obj, f32 scale); //!
void            cur_obj_scale(f32 scale); //!
void            cur_obj_init_animation_with_sound(s32 animIndex);
void            cur_obj_init_animation_with_accel_and_sound(s32 animIndex, f32 accel);
void            cur_obj_init_animation(s32 animIndex);
void            obj_init_animation_with_sound(struct Object *obj, const struct Animation * const *animations, s32 animIndex);
void            cur_obj_set_pos_relative(struct Object *other, f32 dleft, f32 dy, f32 dforward);
u32             get_object_list_from_behavior(               const BehaviorScript *behavior);
struct Object  *cur_obj_nearest_object_with_behavior(        const BehaviorScript *behavior);
f32             cur_obj_dist_to_nearest_object_with_behavior(const BehaviorScript *behavior);
struct Object  *cur_obj_find_nearest_object_with_behavior(   const BehaviorScript *behavior,            f32 *dist);
struct Object  *find_nearest_obj_with_behavior_from_point(   const BehaviorScript *behavior, Vec3f pos, f32 *dist);
struct Object  *find_nearest_obj_with_behavior_from_yaw(     const BehaviorScript *behavior, Vec3f pos, const Angle lookAngle, Angle *yawToObj);
struct Object  *find_unimportant_object(  void);
s32             count_unimportant_objects(void);
s32             count_objects_with_behavior(   const BehaviorScript *behavior);
struct Object  *cur_obj_find_nearby_held_actor(const BehaviorScript *behavior, f32 maxDist);
void            cur_obj_change_action(ObjAction action);
void            cur_obj_set_vel_from_mario_vel(f32 min, f32 mul);
void            cur_obj_reverse_animation(          void);
void            cur_obj_extend_animation_if_at_end( void);
Bool32          cur_obj_check_if_near_animation_end(void);
Bool32          cur_obj_check_frame_prior_current_frame(AnimFrame16 *frame);
void            cur_obj_set_y_vel_and_animation(f32 yVel, s32 animIndex);
void            cur_obj_unrender_set_action_and_anim(     s32 animIndex, ObjAction action);
void            cur_obj_get_thrown_or_placed(f32 forwardVel, f32 velY, ObjAction thrownAction);
void            cur_obj_get_dropped(void);
Bool32          cur_obj_clear_interact_status_flag(s32 flag);
void            cur_obj_update_floor_height(void);
struct Surface *cur_obj_update_floor_height_and_get_floor(void);
void            cur_obj_apply_drag_xz(f32 dragStrength);
void            cur_obj_move_y(f32 gravity, f32 bounciness, f32 buoyancy);
void            cur_obj_unused_resolve_wall_collisions(f32 offsetY, f32 radius);
void            cur_obj_move_xz_using_fvel_and_yaw(void);
void            cur_obj_move_y_with_terminal_vel(  void);
void            cur_obj_compute_vel_xz(            void);
f32             increment_velocity_toward_range(f32 value, f32 center, f32 zeroThreshold, f32 increment);
Bool32          obj_check_if_collided_with_object(struct Object *obj1, struct Object *obj2);
f32             cur_obj_lateral_dist_from_mario_to_home(void);
f32             cur_obj_lateral_dist_from_mario_to_home_squared(void);
f32             cur_obj_lateral_dist_to_home(           void);
f32             cur_obj_lateral_dist_to_home_squared(   void);
void            cur_obj_set_pos_to_home_and_stop(       void);
void            cur_obj_shake_y(f32 amount);
void            cur_obj_start_cam_event(UNUSED struct Object *obj, s32 cameraEvent);
void            obj_set_billboard(          struct Object *obj);
void            cur_obj_set_hitbox_radius_and_height( f32 radius, f32 height);
void            cur_obj_set_hurtbox_radius_and_height(f32 radius, f32 height);
void            obj_spawn_loot_blue_coins(  struct Object *obj, s32 numCoins, f32 baseYVel, s16 posJitter);
void            obj_spawn_loot_yellow_coins(struct Object *obj, s32 numCoins, f32 baseYVel);
void            cur_obj_spawn_loot_coin_at_mario_pos(    void);
UNUSED AnimFrame32 cur_obj_advance_looping_anim(void);
s32             cur_obj_resolve_wall_collisions(         void);
void            cur_obj_update_floor_and_walls(          void);
void            cur_obj_move_standard(Angle steepSlopeAngleDegrees);
void            cur_obj_move_using_vel_and_gravity(      void);
void            cur_obj_move_using_fvel_and_gravity(     void);
Angle           cur_obj_angle_to_home(                   void);
void            obj_set_gfx_pos_at_obj_pos(            struct Object *obj1, struct Object *obj2);
void            obj_translate_local(                   struct Object *obj, s16 posIndex, s16 localTranslateIndex);
void            obj_build_transform_from_pos_and_angle(struct Object *obj, s16 posIndex, s16 angleIndex);
void            obj_set_throw_matrix_from_transform(   struct Object *obj);
void            obj_build_transform_relative_to_parent(struct Object *obj);
void            obj_create_transform_from_self(        struct Object *obj);
void            cur_obj_rotate_face_angle_using_vel(void);
s32             cur_obj_follow_path(void);
void            chain_segment_init(struct ChainSegment *segment);
void            obj_scale_random(        struct Object *obj, f32 rangeLength, f32 minScale);
void            obj_translate_xyz_random(struct Object *obj, f32 rangeLength);
void            obj_translate_xz_random( struct Object *obj, f32 rangeLength);
void            cur_obj_set_pos_via_transform(void);
void            cur_obj_spawn_particles(struct SpawnParticlesInfo *info);
Angle           cur_obj_reflect_move_angle_off_wall(void);

#define WAYPOINT_FLAGS_END                    -1
#define WAYPOINT_FLAGS_INITIALIZED        0x8000
#define WAYPOINT_MASK_00FF                0x00FF
#define WAYPOINT_FLAGS_PLATFORM_ON_TRACK_PAUSE 3

#define PATH_NONE              0
#define PATH_REACHED_END      -1
#define PATH_REACHED_WAYPOINT  1

#define SCALE_AXIS_X    (1 << 0) // 0x01
#define SCALE_AXIS_Y    (1 << 1) // 0x02
#define SCALE_AXIS_Z    (1 << 2) // 0x04

void   obj_set_hitbox(struct Object *obj, struct ObjectHitbox *hitbox);
Bool32 cur_obj_wait_then_blink(s32 timeUntilBlinking, s32 numBlinks);
Bool32 cur_obj_is_mario_ground_pounding_platform(void);
void   spawn_mist_particles(void);
void   spawn_mist_particles_with_sound(u32 soundMagic);
void   cur_obj_push_mario_away(f32 radius);
void   cur_obj_push_mario_away_from_cylinder(f32 radius, f32 extentY);
s32    cur_obj_set_direction_table(s8 *pattern);
s32    cur_obj_progress_direction_table(void);
void   cur_obj_scale_over_time(s32 axis, s32 times, f32 start, f32 end);
void   cur_obj_set_pos_to_home_with_debug(void);
Bool32 cur_obj_is_mario_on_platform(void);
void   cur_obj_call_action_function(void (*actionFunctions[])(void));
Bool32 cur_obj_mario_far_away(void);
Bool32 is_mario_moving_fast_or_in_air(s32 speedThreshold);
Bool32 is_item_in_array(s8 item, s8 *array);
void   cur_obj_enable_rendering_if_mario_in_room(void);
Bool32 cur_obj_set_hitbox_and_die_if_attacked(struct ObjectHitbox *hitbox, s32 deathSound, s32 noLootCoins);
void   obj_explode_and_spawn_coins(f32 mistSize, s32 coinType);
void   obj_set_collision_data(struct Object *obj, const void *segAddr);
void   cur_obj_if_hit_wall_bounce_away(void);
Bool32 cur_obj_hide_if_mario_far_away_y(f32 distY);
Gfx   *geo_offset_klepto_held_object(s32 callContext, struct GraphNode *node, UNUSED Mat4 mtx);
s32    cur_obj_can_mario_activate_textbox(  f32 radius, f32 height, UNUSED s32 unused);
s32    cur_obj_can_mario_activate_textbox_2(f32 radius, f32 height);
s32    cur_obj_update_dialog(              s32 actionArg, s32 dialogFlags,                    DialogID dialogID, UNUSED s32 unused);
s32    cur_obj_update_dialog_with_cutscene(s32 actionArg, s32 dialogFlags, s32 cutsceneTable, DialogID dialogID);
void   cur_obj_align_gfx_with_floor(void);
Bool32 mario_is_within_rectangle(s16 minX, s16 maxX, s16 minZ, s16 maxZ);
void   cur_obj_shake_screen(s32 shake);
Bool32 obj_attack_collided_from_other_object(struct Object *obj);
Bool32 cur_obj_was_attacked_or_ground_pounded(void);
void   obj_copy_behavior_params(struct Object *dst, struct Object *src);
void   cur_obj_init_animation_and_anim_frame(       s32 animIndex, AnimFrame32 animFrame);
s32    cur_obj_init_animation_and_check_if_near_end(s32 animIndex);
void   cur_obj_init_animation_and_extend_if_at_end( s32 animIndex);
Bool32 cur_obj_check_grabbed_mario(        void);
Bool32 player_performed_grab_escape_action(void);
void   cur_obj_unused_play_footstep_sound(AnimFrame32 animFrame1, AnimFrame32 animFrame2, s32 sound);
void   enable_time_stop_including_mario(   void);
void   disable_time_stop_including_mario(  void);
Bool32 cur_obj_check_interacted(           void);
void   cur_obj_spawn_loot_blue_coin(       void);
void   cur_obj_spawn_star_at_y_offset(f32 targetX, f32 targetY, f32 targetZ, f32 offsetY);
