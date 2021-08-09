#ifndef GD_DRAW_OBJECTS_H
#define GD_DRAW_OBJECTS_H

#include <PR/ultratypes.h>

#include "gd_types.h"
#include "macros.h"

enum ColourNum {
    COLOUR_BLACK     =  0,
    COLOUR_WHITE     =  1,
    COLOUR_RED       =  2,
    COLOUR_GREEN     =  3,
    COLOUR_BLUE      =  4,
    COLOUR_GRAY      =  5,
    COLOUR_DARK_GRAY =  6,
    COLOUR_DARK_BLUE =  7,
    COLOUR_YELLOW    =  8,
    COLOUR_PINK      =  9,
    COLOUR_BLACK2    = 10
};

// data
extern struct ObjCamera *gViewUpdateCamera;

// bss
extern struct ObjGroup *gGdLightGroup;  // ObjGroup* of ObjLights

// functions
void draw_light(   struct ObjLight  *light);
void draw_material(struct ObjMaterial *mtl);
struct GdColour *gd_get_colour(s32 idx);
void draw_face(                 struct ObjFace  *face);
void draw_net(                  struct ObjNet   *self);
void draw_camera(               struct ObjCamera *cam);
void world_pos_to_screen_coords(struct GdVec3f   *pos, struct ObjCamera *cam, struct ObjView *view);
void draw_nothing(       UNUSED struct GdObj     *nop);
void draw_particle(             struct GdObj     *obj);
void draw_group(                struct ObjGroup  *grp);
void apply_obj_draw_fn(         struct GdObj     *obj);
void create_gddl_for_shapes(    struct ObjGroup  *grp);
void map_face_materials(        struct ObjGroup  *faces, struct ObjGroup *mtls);
void update_view(               struct ObjView  *view);

#endif // GD_DRAW_OBJECTS_H
