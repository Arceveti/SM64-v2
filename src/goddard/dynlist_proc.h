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
#define DynNameAsStr(name)         ((char *)(name))
#define DynNameAsInt(name) ((u32)(uintptr_t)(name))
#define AsDynName(unk)         ((DynObjName)(unk))
/// @}
/// @}

/// `d_makeobj()` object types
enum DObjTypes {
    D_CAR_DYNAMICS  = 0x00, // unused
    D_NET           = 0x01,
    D_JOINT         = 0x02,
    D_ANOTHER_JOINT = 0x03, // unused
    D_CAMERA        = 0x04,
    D_VERTEX        = 0x05, // unused
    D_FACE          = 0x06, // unused
    D_PLANE         = 0x07, // unused
    D_BONE          = 0x08, // unused
    D_MATERIAL      = 0x09,
    D_SHAPE         = 0x0A,
    D_GADGET        = 0x0B, // unused
    D_LABEL         = 0x0C, // unused
    D_VIEW          = 0x0D,
    D_ANIMATOR      = 0x0E,
    D_DATA_GRP      = 0x0F, ///< An `ObjGroup` that links to raw vertex or face data
    D_PARTICLE      = 0x10,
    D_LIGHT         = 0x11,
    D_GROUP         = 0x12
};

// functions
void d_stash_dynobj(void);
void d_unstash_dynobj(void);
struct GdObj *proc_dynlist(struct DynList *dylist);
void d_set_name_suffix(char *str);
struct GdObj *d_makeobj(enum DObjTypes type, DynObjName name);
void d_set_shapeptrptr(struct ObjShape **shpPtrptr);
struct GdObj *d_use_obj(                     DynObjName name);
void set_cur_dynobj( struct GdObj *obj);
void d_start_group(                          DynObjName name);
void d_end_group(                            DynObjName name);
void d_use_integer_names(s32 isIntBool);
void d_set_init_pos( f32 x, f32 y, f32 z);
void d_get_init_pos(Vec3f dst);
void d_get_init_rot(Vec3f dst);
void d_set_rel_pos(  f32 x, f32 y, f32 z);
void d_get_rel_pos(Vec3f dst);
struct ObjGroup *d_get_att_objgroup(void);
void d_get_scale(    Vec3f dst);
void d_set_world_pos(f32 x, f32 y, f32 z);
UNUSED void d_get_world_pos(Vec3f dst);
void d_vec3f_get_world_pos(Vec3f dst);
void d_set_scale(    f32 x, f32 y, f32 z);
void d_set_flags(s32 flags);
void d_set_obj_draw_flag(enum ObjDrawingFlags flag);
void d_set_type(s32 type);
void d_set_diffuse(ColorF r, ColorF g, ColorF b);
void d_get_matrix(Mat4 dst);
Mat4 *d_get_rot_mtx_ptr(void);
void d_set_i_matrix(Mat4 *src);
Mat4 *d_get_matrix_ptr(void);
Mat4 *d_get_i_mtx_ptr( void);
f32 d_calc_world_dist_btwn(struct GdObj *obj1, struct GdObj *obj2);

#endif // GD_DYNLIST_PROCESSOR_H
