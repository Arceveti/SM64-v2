#ifndef GD_JOINTS_H
#define GD_JOINTS_H

#include <PR/ultratypes.h>

#include "gd_types.h"

// functions
void eye_joint_update_func(struct ObjJoint *self);
struct ObjJoint *make_joint(s32 flags, f32 x, f32 y, f32 z);
struct ObjJoint *make_grabber_joint(struct ObjShape *shape, s32 flags, f32 x, f32 y, f32 z);
s32 set_skin_weight(struct ObjJoint *j, s32 id, struct ObjVertex *vtx, f32 weight);
void func_801911A8(struct ObjJoint *j);
void func_80191220(struct ObjJoint *j);
void func_801913F0(struct ObjJoint *j);
void reset_joint(struct ObjJoint *j);
void func_80191824(struct ObjJoint *j);
void reset_joint_counts(void);

#endif // GD_JOINTS_H
