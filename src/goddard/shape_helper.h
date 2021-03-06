#pragma once

#include <PR/ultratypes.h>

// data
extern struct ObjGroup *gMarioFaceGrp;
extern struct ObjShape *gSpotShape;
extern struct ObjShape *gShapeRedSpark;
extern struct ObjShape *gShapeSilverSpark;
extern struct ObjShape *gShapeRedStar;
extern struct ObjShape *gShapeSilverStar;

// functions
void calc_face_normal( struct ObjFace *face);
struct ObjVertex *gd_make_vertex(Vec3s pos);
void add_3_vtx_to_face(struct ObjFace *face, struct ObjVertex *vtx1, struct ObjVertex *vtx2, struct ObjVertex *vtx3);
struct ObjShape *make_shape(const char *name);
void animate_mario_head_gameover(  struct ObjAnimator *self);
void animate_mario_head_normal(    struct ObjAnimator *self);
s32  load_mario_head(void (*aniFn)(struct ObjAnimator *));
void load_shapes2(  void);

struct ObjFace* make_face_with_colour(ColorRGBf color);
