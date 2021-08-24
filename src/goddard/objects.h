#ifndef GD_OBJECTS_H
#define GD_OBJECTS_H

#include <PR/ultratypes.h>

#include "gd_types.h"

// types
// Type to erase for func arg to `apply_to_obj_types_in_group`. Maybe one day this
// can be the proper type of 'void (*)(struct GdObj *)...
typedef void (*applyproc_t)(void *);

// bss
extern struct GdBoundingBox gSomeBoundingBox;
extern struct ObjCamera *sCurrentMoveCamera;
extern struct ObjView *sCurrentMoveView;
extern Mat4 D_801B9DC8;
extern struct ObjGroup* sCurrentMoveGrp;
extern struct ObjCamera* gGdCameraList;
extern struct ObjGroup* gGdGroupList;
extern s32 gGdObjCount;
extern s32 gGdGroupCount;
extern s32 gGdCameraCount;
extern s32 sGdViewCount;
extern struct ObjJoint* gGdJointList;
extern struct GdObj* gGdObjectList;
extern struct ObjGroup* gGdViewsGroup;

// functions
void reset_bounding_box(void);
void add_obj_pos_to_bounding_box(struct GdObj *obbj);
struct GdObj       *make_object(enum ObjTypeFlag objFlag);
struct ListNode    *make_link_to_obj(struct ListNode *head, struct GdObj *a1);
struct VtxLink     *make_vtx_link(struct VtxLink *prevLink, Vtx *data);
struct ObjCamera   *make_camera(  void);
struct ObjMaterial *make_material(void);
struct ObjLight    *make_light(   void);
struct ObjView     *make_view(const char *name, s32 flags, s32 projectionType, s32 ulx, s32 uly, s32 lrx, s32 lry, struct ObjGroup *parts);
struct ObjAnimator *make_animator(void);
struct ObjWeight   *make_weight(s32 id, struct ObjVertex *vtx, f32 weight);
struct ObjGroup    *make_group_of_type(enum ObjTypeFlag type, struct GdObj *fromObj);
struct ObjGroup    *make_group(s32 count, ...);
void addto_group(                                           struct ObjGroup *group, struct GdObj *obj);
void addto_groupfirst(                                      struct ObjGroup *group, struct GdObj *obj);
Bool32 group_contains_obj(                                  struct ObjGroup *group, struct GdObj *obj);
s32  apply_to_obj_types_in_group(s32 types, applyproc_t fn, struct ObjGroup *group);
s32  transform_child_objects_recursive(struct GdObj *obj,                           struct GdObj *parentObj);
void interpolate_animation_transform(struct GdAnimTransform *t1, struct GdAnimTransform *t2, f32 dt);
void move_animator(              struct ObjAnimator *animObj);
void drag_picked_object(         struct GdObj       *inputObj);
void move_animators(             struct ObjGroup    *group);
void find_and_drag_picked_object(struct ObjGroup    *group);
void move_camera(                struct ObjCamera   *cam);
void move_cameras_in_grp(        struct ObjGroup    *group);
void proc_view_movement(         struct ObjView     *view);
void reset_nets_and_gadgets(     struct ObjGroup    *group);
void null_obj_lists(void);

#endif // GD_OBJECTS_H
