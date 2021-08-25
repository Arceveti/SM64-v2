#ifndef GD_DRAW_OBJECTS_H
#define GD_DRAW_OBJECTS_H

#include <PR/ultratypes.h>

#include "gd_types.h"
#include "macros.h"

enum ColourNum {
    COLOUR_BLACK     = 0x0,
    COLOUR_WHITE     = 0x1,
    COLOUR_RED       = 0x2,
    COLOUR_GREEN     = 0x3,
    COLOUR_BLUE      = 0x4,
    COLOUR_GRAY      = 0x5,
    COLOUR_DARK_GRAY = 0x6,
    COLOUR_DARK_BLUE = 0x7,
    COLOUR_YELLOW    = 0x8,
    COLOUR_PINK      = 0x9,
    COLOUR_BLACK2    = 0xA
};

// data
extern struct ObjCamera *gViewUpdateCamera;

// bss
extern struct ObjGroup *gGdLightGroup;  // ObjGroup* of ObjLights

// functions
void draw_light(   struct ObjLight  *light);
void draw_material(struct ObjMaterial *mtl);
GdColour *gd_get_colour(s32 idx);
void draw_face(                 struct ObjFace  *face);
void draw_net(                  struct ObjNet   *self);
void draw_camera(               struct ObjCamera *cam);
void world_pos_to_screen_coords(       Vec3f      pos, struct ObjCamera *cam, struct ObjView *view);
void draw_nothing(       UNUSED struct GdObj     *nop);
void draw_particle(             struct GdObj     *obj);
void draw_group(                struct ObjGroup  *grp);
void apply_obj_draw_fn(         struct GdObj     *obj);
void create_gddl_for_shapes(    struct ObjGroup  *grp);
void map_face_materials(        struct ObjGroup  *faces, struct ObjGroup *mtls);
void update_view(               struct ObjView  *view);

#endif // GD_DRAW_OBJECTS_H
