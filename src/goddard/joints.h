#pragma once

#include <PR/ultratypes.h>

// functions
void eye_joint_update_func(struct ObjJoint *self);
struct ObjJoint *make_joint(                                s32 flags, Vec3f pos);
struct ObjJoint *make_grabber_joint(struct ObjShape *shape, s32 flags, f32 x, f32 y, f32 z);
Bool32 set_skin_weight(struct ObjJoint *j, s32 id, struct ObjVertex *vtx, f32 weight);
void   reset_joint(   struct ObjJoint *j);
void   reset_joint_counts(void);
void   set_joint_vecs(struct ObjJoint *j, Vec3f pos);
