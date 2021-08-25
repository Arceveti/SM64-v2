#ifndef GD_RENDERER_H
#define GD_RENDERER_H

#include <PR/ultratypes.h>

#include "gd_types.h"
#include "macros.h"

// types
/// Properties types used in [gd_setproperty](@ref gd_setproperty); most are stubbed out.
enum GdProperty {
    GD_PROP_LIGHTING      = 11,
    GD_PROP_AMB_COLOUR    = 12,
    GD_PROP_DIFUSE_COLOUR = 13,
    GD_PROP_LIGHT_DIR     = 15,
    GD_PROP_CULLING       = 16
};

enum GdSceneId {
    GD_SCENE_YOSHI,  // create yoshi?
    GD_SCENE_YOSHI1,  // destroy yoshi?
    GD_SCENE_REGULAR_MARIO,
    GD_SCENE_DIZZY_MARIO
};

// data
extern s32 gGdFrameBufNum;

// functions
u32 get_alloc_mem_amt(void);

#if defined(ISVPRINT) || defined(UNF)
#define gd_printf osSyncPrintf
#endif
void  gd_exit(void) NORETURN;
void  gd_free(void *ptr);
void *gd_allocblock(             u32 size);
void *gd_malloc(                 u32 size, u8 perm);
void *gd_malloc_perm(            u32 size);
void *gd_malloc_temp(            u32 size);
void  draw_indexed_dl(s32 dlNum, s32 gfxIdx);
void  gd_add_to_heap(void *addr, u32 size);
void  gdm_init(void *blockpool,  u32 size);
void  gdm_setup(void);
void  gdm_maketestdl(s32 id);
void  gd_vblank(void);
void  gd_copy_p1_contpad(OSContPad *p1cont);
s32   gd_sfx_to_play(void);
Gfx  *gdm_gettestdl(s32 id);
void  stash_current_gddl(void);
void  pop_gddl_stash(void);
s32   gd_startdisplist(s32 memarea);
s32   gd_enddlsplist_parent(void);
void  gd_dl_load_matrix(Mat4 *mtx);
void  gd_dl_push_matrix(void);
void  gd_dl_pop_matrix(void);
void  gd_dl_mul_trans_matrix( f32 x, f32 y, f32 z);
void  gd_dl_load_trans_matrix(f32 x, f32 y, f32 z);
void  gd_dl_scale(            f32 x, f32 y, f32 z);
void  func_8019F2C4(f32 angle, s8 axis);
void  gd_dl_lookat(struct ObjCamera *cam, f32 xFrom, f32 yFrom, f32 zFrom, f32 xTo, f32 yTo, f32 zTo, f32 colXY);
void  check_tri_display(s32 vtxcount);
Vtx  *gd_dl_make_vertex(f32 x, f32 y, f32 z, f32 alpha);
void  func_8019FEF0(void);
void  gd_dl_make_triangle(f32 x1, f32 y1, f32 z1, f32 x2, f32 y2, f32 z2, f32 x3, f32 y3, f32 z3);
void  func_801A0038(void);
void  gd_dl_flush_vertices(void);
void  set_render_alpha(f32 alpha);
void  set_light_id(s32 index);
void  set_light_num(s32 n);
s32   create_mtl_gddl(void);
void  branch_to_gddl(s32 dlNum);
void  gd_dl_hilite(s32 idx, struct ObjCamera *cam, Vec3f phongLightPosition, GdColour colour);
s32   gd_dl_material_lighting(s32 id, GdColour colour, s32 material);
void  set_Vtx_norm_buf_2(Vec3f norm);
void  set_gd_mtx_parameters(s32 params);
void  gd_set_one_cycle(void);
void  start_view_dl(struct ObjView *view);
void  gd_setproperty(enum GdProperty prop, f32 f1, f32 f2, f32 f3);
void  gd_create_ortho_matrix(f32 l, f32 r, f32 b, f32 t, f32 n, f32 f);
void  gd_create_perspective_matrix(f32 fovy, f32 aspect, f32 near, f32 far);
s32   setup_view_buffers(UNUSED const char *name, struct ObjView *view);
void  gd_init_controllers(void);
void  set_active_view(struct ObjView *v);
void  gd_init(void);
void  init_pick_buf(s16 *buf, s32 len);
void  store_in_pickbuf(s16 data);
s32   get_cur_pickbuf_offset(void);
struct GdObj *load_dynlist(struct DynList *dynlist);

#endif // GD_RENDERER_H
