#ifndef GD_DYNLIST_PROCESSOR_H
#define GD_DYNLIST_PROCESSOR_H

#include <PR/ultratypes.h>

#include "gd_types.h"

// types
/// @name DynObjName Type
/// @{
/// A new type for identification of `GdObj`s in the dynamic object list.
typedef void *DynObjName;
/// Macros for casting between types of names,
/// as the name can be either a number or a string.
/// @{
#define DynNameAsStr(name) ((char *)(name))
#define DynNameAsInt(name) ((u32)(uintptr_t)(name))
#define AsDynName(unk)   ((DynObjName)(unk))
/// @}
/// @}


/// `d_makeobj()` object types
enum DObjTypes {
    D_CAR_DYNAMICS  = 0,
    D_NET           = 1,
    D_JOINT         = 2,
    D_ANOTHER_JOINT = 3,
    D_CAMERA        = 4,
    D_VERTEX        = 5,
    D_FACE          = 6,
    D_PLANE         = 7,
    D_BONE          = 8,
    D_MATERIAL      = 9,
    D_SHAPE         = 10,
    D_GADGET        = 11,
    D_LABEL         = 12,
    D_VIEW          = 13,
    D_ANIMATOR      = 14,
    D_DATA_GRP      = 15, ///< An `ObjGroup` that links to raw vertex or face data
    D_PARTICLE      = 16,
    D_LIGHT         = 17,
    D_GROUP         = 18
};

// functions
void d_stash_dynobj(void);
void d_unstash_dynobj(void);
struct GdObj *proc_dynlist(struct DynList *dylist);
void d_set_name_suffix(char *str);
struct GdObj *d_makeobj(enum DObjTypes type, DynObjName name);
void d_set_shapeptrptr(struct ObjShape **shpPtrptr);
struct GdObj *d_use_obj(DynObjName name);
void set_cur_dynobj(struct GdObj *obj);
void d_start_group(DynObjName name);
void d_end_group(DynObjName name);
void d_use_integer_names(s32 isIntBool);
void d_set_init_pos(f32 x, f32 y, f32 z);
void d_get_init_pos(struct GdVec3f *dst);
void d_get_init_rot(struct GdVec3f *dst);
void d_set_rel_pos(f32 x, f32 y, f32 z);
void d_get_rel_pos(struct GdVec3f *dst);
struct ObjGroup *d_get_att_objgroup(void);
void d_get_scale(struct GdVec3f *dst);
void d_set_world_pos(f32 x, f32 y, f32 z);
void d_get_world_pos(struct GdVec3f *dst);
void d_set_scale(f32 x, f32 y, f32 z);
void d_set_flags(s32 flags);
void d_set_obj_draw_flag(enum ObjDrawingFlags flag);
void d_set_type(s32 type);
void d_set_diffuse(f32 r, f32 g, f32 b);
void d_get_matrix(Mat4f *dst);
Mat4f *d_get_rot_mtx_ptr(void);
void d_set_i_matrix(Mat4f *src);
Mat4f *d_get_matrix_ptr(void);
Mat4f *d_get_i_mtx_ptr(void);
f32 d_calc_world_dist_btwn(struct GdObj *obj1, struct GdObj *obj2);

#endif // GD_DYNLIST_PROCESSOR_H
