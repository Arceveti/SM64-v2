#include <PR/ultratypes.h>

#include "string_utils.h"
#include "dynlist_proc.h"
#include "gd_macros.h"
#include "gd_main.h"
#include "gd_math.h"
#include "objects.h"
#include "renderer.h"
#include "shape_helper.h"
#include "draw_objects.h"
#include "engine/math_util.h"

/**
 * @file draw_objects.c
 * This file contains the functions and helpers for rendering the various
 * GdObj primitives to the screen.
 */

// forward declarations
void update_shaders(  struct ObjShape *, struct GdVec3f *);
void draw_shape_faces(struct ObjShape *);
void register_light(  struct ObjLight *);

// types
/**
 * Modes for drawscene()
 */
enum SceneType {
    RENDER_SCENE = 26, ///< render the primitives to screen
    FIND_PICKS   = 27  ///< only check position of primitives relative to cursor click
};

// data
static struct GdColour sClrWhite        =   { 1.0f, 1.0f, 1.0f };   // @ 801A8070
static struct GdColour sClrRed          =   { 1.0f, 0.0f, 0.0f };   // @ 801A807C
static struct GdColour sClrGreen        =   { 0.0f, 1.0f, 0.0f };   // @ 801A8088
static struct GdColour sClrBlue         =   { 0.0f, 0.0f, 1.0f };   // @ 801A8094
static struct GdColour sClrErrDarkBlue  =   { 0.0f, 0.0f, 6.0f };   // @ 801A80A0
static struct GdColour sClrPink         =   { 1.0f, 0.0f, 1.0f };   // @ 801A80AC
static struct GdColour sClrBlack        =   { 0.0f, 0.0f, 0.0f };   // @ 801A80B8
static struct GdColour sClrGrey         =   { 0.6f, 0.6f, 0.6f };   // @ 801A80C4
static struct GdColour sClrDarkGrey     =   { 0.4f, 0.4f, 0.4f };   // @ 801A80D0
static struct GdColour sClrYellow       =   { 1.0f, 1.0f, 0.0f };   // @ 801A80DC
static struct GdColour sLightColours[1] = { { 1.0f, 1.0f, 0.0f } }; // @ 801A80E8
static struct GdColour *sSelectedColour = &sClrRed;                 // @ 801A80F4
struct ObjCamera *gViewUpdateCamera = NULL;                         // @ 801A80F8
static s32 sLightDlCounter = 1; // @ 801A81A0

// bss
struct ObjGroup *gGdLightGroup; // @ 801B9BB8; is this the main light group? only light group?

static enum SceneType sSceneProcessType; // @ 801B9C00
static s32 sUseSelectedColor;            // @ 801B9C04
static s16 sPickBuffer[100];             ///< buffer of objects near click
static s32 sPickDataTemp;                ///< now, only data is the object number of a selected joint
static f32 sPickObjDistance;             ///< distance between object position and cursor click location
static struct GdObj *sPickedObject;      ///< object selected with cursor
/// Various counters and pointers set in update_view() and used in various `draw_XXX` functions
static struct {
    struct ObjView *view; // @ 801B9CE4
    s32 mtlDlNum;         // @ 801B9CEC; name is a big guess
    s32 shapesDrawn;      // @ 801B9CF0
} sUpdateViewState;
static struct ObjLight *sPhongLight;          // material light? phong light?
static struct GdVec3f sPhongLightPosition;    //@ 801B9D00; guess; light source unit position for light
                                              // flagged 0x20 (sPhongLight)
static struct GdVec3f sLightPositionOffset;   // @ 801B9D10
static struct GdVec3f sLightPositionCache[8]; // @ 801B9D20; unit positions
static s32 sNumActiveLights;                  // @ 801B9D80; maybe?
static struct GdVec3f sGrabCords;             ///< x, y grabbable point near cursor

/**
 * Set the ambient light color and turn on G_CULL_BACK.
 */
void setup_lights(void) {
    set_light_num(NUMLIGHTS_2);
    gd_setproperty(GD_PROP_AMB_COLOUR, 0.5f, 0.5f, 0.5f);
    gd_setproperty(GD_PROP_CULLING, 1.0f, 0.0f, 0.0f); // set G_CULL_BACK
    return;
}

/* 226C6C -> 226FDC */
void draw_shape(struct ObjShape *shape, s32 flag, f32 c, f32 d, f32 e, // "sweep" indices 0-2 x, y, z
                f32 f, f32 g, f32 h, // translate shape + store offset (unused)
                f32 i, f32 j, f32 k, // translate shape
                f32 l, f32 m, f32 n, // rotate x, y, z
                s32 colorIdx, Mat4f *rotMtx) {
    struct GdVec3f vec;
    sUpdateViewState.shapesDrawn++;
    if (shape == NULL) return;
    vec.x = vec.y = vec.z = 0.0f;
    if (flag & 0x02) {
        gd_dl_load_trans_matrix(f, g, h);
        vec.x += f;
        vec.y += g;
        vec.z += h;
    }
    if ((flag & 0x10) && rotMtx != NULL) {
        gd_dl_load_matrix(rotMtx);
        vec.x += (*rotMtx)[3][0];
        vec.y += (*rotMtx)[3][1];
        vec.z += (*rotMtx)[3][2];
    }
    if (flag & 0x08) {
        if (m != 0.0f) func_8019F2C4(m, 121);
        if (l != 0.0f) func_8019F2C4(l, 120);
        if (n != 0.0f) func_8019F2C4(n, 122);
    }
    if (colorIdx != 0) {
        sUseSelectedColor = TRUE;
        sSelectedColour = gd_get_colour(colorIdx);
        if (sSelectedColour != NULL) {
            gd_dl_material_lighting(-1, sSelectedColour, GD_MTL_LIGHTS);
        } else {
            gd_exit(); // Bad colour
        }
    } else {
        sUseSelectedColor = FALSE;
        sSelectedColour   = NULL;
    }

    if (sNumActiveLights != 0 && shape->mtlGroup != NULL) {
        if (rotMtx != NULL) {
            vec.x = (*rotMtx)[3][0];
            vec.y = (*rotMtx)[3][1];
            vec.z = (*rotMtx)[3][2];
        } else {
            vec.x = vec.y = vec.z = 0.0f;
        }
        update_shaders(shape, &vec);
    }
    if (flag & 0x04) gd_dl_mul_trans_matrix(i, j, k);
    if (flag & 0x01) gd_dl_scale(c, d, e);
    draw_shape_faces(shape);
    sUseSelectedColor = FALSE;
}

void draw_shape_2d(struct ObjShape *shape, s32 flag, f32 posX, f32 posY, f32 posZ) {
    struct GdVec3f pos;
    sUpdateViewState.shapesDrawn++;
    if (shape == NULL) return;
    if (flag & 0x02) {
        pos.x = posX;
        pos.y = posY;
        pos.z = posZ;
        if (gViewUpdateCamera != NULL) gd_rotate_and_translate_vec3f(&pos, &gViewUpdateCamera->unkE8);
        gd_dl_load_trans_matrix(pos.x, pos.y, pos.z);
    }
    draw_shape_faces(shape);
}

void draw_light(struct ObjLight *light) {
    struct GdVec3f sp94;
    Mat4f sp54;
    struct ObjShape *shape;
    if (sSceneProcessType == FIND_PICKS) return;
    sLightColours[0].r = light->colour.r;
    sLightColours[0].g = light->colour.g;
    sLightColours[0].b = light->colour.b;
    if (light->flags & LIGHT_UNK02) {
        gd_set_identity_mat4(&sp54);
        sp94.x = -light->unk80.x;
        sp94.y = -light->unk80.y;
        sp94.z = -light->unk80.z;
        gd_create_origin_lookat(&sp54, &sp94, 0.0f);
        shape = gSpotShape;
    } else {
        shape = light->unk9C;
        if (++sLightDlCounter >= 17) sLightDlCounter = 1;
        shape->unk50 = sLightDlCounter;
    }
    draw_shape_2d(shape, 2, light->position.x, light->position.y, light->position.z);
}

void draw_material(struct ObjMaterial *mtl) {
    s32 mtlType = mtl->type;
    if (mtlType == GD_MTL_SHINE_DL) {
        if (sPhongLight != NULL && sPhongLight->unk30 > 0.0f) {
            if (gViewUpdateCamera != NULL) {
                gd_dl_hilite(mtl->gddlNumber, gViewUpdateCamera, &sPhongLightPosition, &sPhongLight->colour);
            } else {
                gd_exit(); // no active camera for phong
            }
        } else {
            mtlType = GD_MTL_BREAK;
        }
    }
    if (!sUseSelectedColor) {
        gd_dl_material_lighting(mtl->gddlNumber, &mtl->Kd, mtlType);
    } else {
        gd_dl_material_lighting(mtl->gddlNumber, sSelectedColour, GD_MTL_LIGHTS);
    }
}

/**
 * Create a `GdDisplayList` and store its number in the input `ObjMaterial`
 * if this material doesn't have one
 */
void create_mtl_gddl_if_empty(struct ObjMaterial *mtl) {
    if (mtl->gddlNumber == 0) mtl->gddlNumber = create_mtl_gddl();
}

/**
 * @brief Convert a numeric index into pointer to a struct GdColour
 *
 * A simple switch case to convert from index @p idx to a pointer to the
 * three f32 GdColour structure. Goddard stored the index in a structure,
 * and uses this function to get the colour RGB values if needed.
 * -1 uses the environment colour.
 * A possible enhancement for this is to ennumerate all colours, and then
 * use those enumerations and/or enum type where ever a colour is requested
 *
 * @param idx Index of colour
 * @return Pointer to a GdColour struct
 */
struct GdColour *gd_get_colour(s32 idx) {
    switch (idx) {
        case COLOUR_BLACK:     return &sClrBlack;        break;
        case COLOUR_WHITE:     return &sClrWhite;        break;
        case COLOUR_RED:       return &sClrRed;          break;
        case COLOUR_GREEN:     return &sClrGreen;        break;
        case COLOUR_BLUE:      return &sClrBlue;         break;
        case COLOUR_GRAY:      return &sClrGrey;         break;
        case COLOUR_DARK_GRAY: return &sClrDarkGrey;     break;
        case COLOUR_DARK_BLUE: return &sClrErrDarkBlue;  break;
        case COLOUR_BLACK2:    return &sClrBlack;        break;
        case COLOUR_YELLOW:    return &sClrYellow;       break;
        case COLOUR_PINK:      return &sClrPink;         break;
        case -1:               return &sLightColours[0]; break;
        default:               return NULL;
    }
}

/**
 * Rendering function for `ObjFace` structures. It has a fair amount
 * of stub code
 */
void draw_face(struct ObjFace *face) {
    struct ObjVertex *vtx;
    f32 z, y, x;
    s32 i; // also used to store mtl's gddl number
    Vtx *gbiVtx;
    if (!sUseSelectedColor
     && face->mtlId >= 0 // -1 == colored face
     && face->mtl != NULL
     && (i = face->mtl->gddlNumber) != 0
     && (i != sUpdateViewState.mtlDlNum)) {
        gd_dl_flush_vertices();
        branch_to_gddl(i);
        sUpdateViewState.mtlDlNum = i;
    }
    check_tri_display(face->vtxCount);
    for (i = 0; i < face->vtxCount; i++) {
        vtx = face->vertices[i];
        x = vtx->pos.x;
        y = vtx->pos.y;
        z = vtx->pos.z;
        set_Vtx_norm_buf_2(&vtx->normal);
        gbiVtx = gd_dl_make_vertex(x, y, z, vtx->alpha);
        if (gbiVtx != NULL) vtx->gbiVerts = make_vtx_link(vtx->gbiVerts, gbiVtx);
    }
    func_8019FEF0();
}

/* 227DF8 -> 227F3C; orig name: Proc80179628 */
void draw_net(struct ObjNet *self) {
    struct ObjNet *net = self;
    s32 netColor;
    if (sSceneProcessType == FIND_PICKS) return;
    netColor = (net->header.drawFlags & OBJ_HIGHLIGHTED) ? COLOUR_YELLOW : net->colourNum;
    if (net->shapePtr != NULL) draw_shape(net->shapePtr, 0x10, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, netColor, &net->mat168);
    if (net->unk1C8   != NULL) draw_group(net->unk1C8);
}

/* 22803C -> 22829C */
void draw_camera(struct ObjCamera *cam) {
    struct GdVec3f sp44;
    sp44.x = 0.0f;
    sp44.y = 0.0f;
    sp44.z = 0.0f;
    if (cam->unk30 != NULL) {
        set_cur_dynobj(cam->unk30);
        d_get_world_pos(&sp44);
        sp44.x += cam->lookAt.x;
        sp44.y += cam->lookAt.y;
        sp44.z += cam->lookAt.z;
    } else {
        sp44.x  = cam->lookAt.x;
        sp44.y  = cam->lookAt.y;
        sp44.z  = cam->lookAt.z;
    }
    if (absf(cam->worldPos.x - sp44.x) + absf(cam->worldPos.z - sp44.z) == 0.0f) return; // Zero view distance
    gd_dl_lookat(cam, cam->worldPos.x, cam->worldPos.y, cam->worldPos.z, sp44.x, sp44.y, sp44.z, cam->unkA4);
}

/* 22836C -> 228498 */
void world_pos_to_screen_coords(struct GdVec3f *pos, struct ObjCamera *cam, struct ObjView *view) {
    gd_rotate_and_translate_vec3f(pos, &cam->unkE8);
    if (pos->z > -256.0f) return;
    pos->x *= (256.0f / -pos->z);
    pos->y *= (256.0f /  pos->z);
    pos->x += (view->lowerRight.x / 2.0f);
    pos->y += (view->lowerRight.y / 2.0f);
}

/**
 * Check if the current cursor position is near enough to @p input to
 * grab that `GdObj`. The range is +/- 20 units for being close to a
 * grab point.
 *
 * If the object can be grabbed, its information is stored in a buffer by
 * `store_in_pickbuf()`.
 *
 * @param input `GdObj` to check position of
 * @return void
 */
void check_grabable_click(struct GdObj *input) {
    struct GdVec3f objPos;
    struct GdObj  *obj;
    Mat4f *mtx;
    if (gViewUpdateCamera == NULL) return;
    obj = input;
    if (!(obj->drawFlags & OBJ_IS_GRABBALE)) return;
    set_cur_dynobj(obj);
    mtx = d_get_rot_mtx_ptr();
    objPos.x = (*mtx)[3][0];
    objPos.y = (*mtx)[3][1];
    objPos.z = (*mtx)[3][2];
    world_pos_to_screen_coords(&objPos, gViewUpdateCamera, sUpdateViewState.view);
    if (absf(gGdCtrl.csrX - objPos.x) < 20.0f
     && absf(gGdCtrl.csrY - objPos.y) < 20.0f) {
        // store (size, Obj Type, Obj Index) in s16 pick buffer array
        store_in_pickbuf(2);
        store_in_pickbuf(obj->type);
        store_in_pickbuf(obj->index);
        sGrabCords.x = objPos.x;
        sGrabCords.y = objPos.y;
    }
}

/**
 * The main function for rendering the components of an `ObjView`. It called
 * both for drawing the various `GdObj` primatives as well as when checking
 * the location of a cursor click.
 * @note This has to be called from update_view() due to that function setting
 *       state variables on which this function relies
 *
 * @param process determines if this is rendering the scene
 *                or just checking click location
 * @param interactables components of `ObjView`
 * @param lightgrp lights of `ObjView
 */
void drawscene(enum SceneType process, struct ObjGroup *interactables, struct ObjGroup *lightgrp) {
    set_gd_mtx_parameters(G_MTX_PROJECTION | G_MTX_MUL | G_MTX_PUSH);
    if (sUpdateViewState.view->projectionType == 1) {
        gd_create_perspective_matrix(sUpdateViewState.view->clipping.z,
                      sUpdateViewState.view->lowerRight.x / sUpdateViewState.view->lowerRight.y,
                      sUpdateViewState.view->clipping.x,    sUpdateViewState.view->clipping.y);
    } else {
        gd_create_ortho_matrix(
            -sUpdateViewState.view->lowerRight.x / 2.0f, sUpdateViewState.view->lowerRight.x / 2.0f,
            -sUpdateViewState.view->lowerRight.y / 2.0f, sUpdateViewState.view->lowerRight.y / 2.0f,
             sUpdateViewState.view->clipping.x,          sUpdateViewState.view->clipping.y);
    }
    if (lightgrp != NULL) {
        set_gd_mtx_parameters(G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_PUSH);
        apply_to_obj_types_in_group(OBJ_TYPE_LIGHTS | OBJ_TYPE_PARTICLES, (applyproc_t) apply_obj_draw_fn, lightgrp);
        set_gd_mtx_parameters(G_MTX_PROJECTION | G_MTX_MUL | G_MTX_PUSH);
    }
    if (gViewUpdateCamera != NULL) {
        draw_camera(gViewUpdateCamera);
    } else {
        gd_dl_mul_trans_matrix(0.0f, 0.0f, -1000.0f);
    }
    setup_lights();
    set_gd_mtx_parameters(G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_PUSH);
    gd_dl_push_matrix();
    sSceneProcessType = process;
    if ((sNumActiveLights = sUpdateViewState.view->flags & VIEW_LIGHT)) sUpdateViewState.view->flags &= ~VIEW_LIGHT;
    sNumActiveLights = 1;
    apply_to_obj_types_in_group(OBJ_TYPE_LIGHTS, (applyproc_t) register_light, gGdLightGroup);
    if (sSceneProcessType == FIND_PICKS) {
        apply_to_obj_types_in_group(OBJ_TYPE_ALL, (applyproc_t) check_grabable_click, interactables);
    } else {
        apply_to_obj_types_in_group(OBJ_TYPE_LIGHTS | OBJ_TYPE_NETS | OBJ_TYPE_PARTICLES, (applyproc_t) apply_obj_draw_fn, interactables);
    }
    gd_setproperty(GD_PROP_LIGHTING, 1.0f, 0.0f, 0.0f);
    gd_dl_pop_matrix();
    return;
}

/**
 * A drawing function that does nothing. This function is used for
 * `GdObj`s that don't need to be rendered
 */
void draw_nothing(UNUSED struct GdObj *nop) {
}

/**
 * Render the `faceGroup` of an `ObjShape`. This is called from
 * draw_shape() and draw_shape_2d(), or when creating the shape
 * `GdDisplayList` when calling create_shape_gddl()
 */
void draw_shape_faces(struct ObjShape *shape) {
    sUpdateViewState.mtlDlNum = 0;
    set_render_alpha(shape->alpha);
    if (shape->dlNums[gGdFrameBufNum] != 0) {
        draw_indexed_dl(shape->dlNums[gGdFrameBufNum], shape->unk50);
    } else if (shape->faceGroup != NULL) {
        func_801A0038();
        draw_group(shape->faceGroup);
        gd_dl_flush_vertices();
    }
}

/**
 * Rendering function for `ObjParticle`.
 */
void draw_particle(struct GdObj *obj) {
    struct ObjParticle *ptc = (struct ObjParticle *) obj;
    struct GdColour *white;
    struct GdColour *black;
    f32 brightness;
    if (ptc->timeout > 0) {
        white = &sClrWhite;
        black = &sClrBlack;
        brightness = ptc->timeout / 10.0f;
        sLightColours[0].r = (white->r - black->r) * brightness + black->r;
        sLightColours[0].g = (white->g - black->g) * brightness + black->g;
        sLightColours[0].b = (white->b - black->b) * brightness + black->b;
    } else {
        sLightColours[0].r = 0.0f;
        sLightColours[0].g = 0.0f;
        sLightColours[0].b = 0.0f;
    }
    if (ptc->timeout > 0) {
        ptc->shapePtr->unk50 = ptc->timeout;
        draw_shape_2d(ptc->shapePtr, 2, ptc->pos.x, ptc->pos.y, ptc->pos.z);
    }
    if (ptc->particleType == 3 && ptc->subParticlesGrp != NULL) draw_group(ptc->subParticlesGrp);
}

/**
 * Call `apply_obj_draw_fn()` to all `GdObj` in input `ObjGroup`
 *
 * @param grp `ObjGroup` of objects to draw
 * @return void
 */
void draw_group(struct ObjGroup *grp) {
    if (grp == NULL) gd_exit(); // Bad group definition!
    apply_to_obj_types_in_group(OBJ_TYPE_ALL, (applyproc_t) apply_obj_draw_fn, grp);
}

/**
 * Apply `GdObj.objDrawFn` to the input `GdObj` if that object is draw-able.
 *
 * @param obj `GdObj` to draw
 * @return void
 */
void apply_obj_draw_fn(struct GdObj *obj) {
    if (obj == NULL) gd_exit(); // Bad object!
    if (obj->drawFlags & OBJ_INVISIBLE) return;
    obj->objDrawFn(obj);
}

/**
 * Count input `ObjLight` as an active light, if it wasn't already counted.
 */
void register_light(struct ObjLight *light) {
    set_light_id(light->id);
    gd_setproperty(GD_PROP_LIGHTING, 2.0f, 0.0f, 0.0f);
    if (light->flags & LIGHT_NEW_UNCOUNTED) sNumActiveLights++;
    light->flags &= ~LIGHT_NEW_UNCOUNTED;
}

/* 229180 -> 229564 */
void update_lighting(struct ObjLight *light) {
    f32 sp24; // diffuse factor?
    f32 sp20;
    f32 sp1C;
    light->colour.r = light->diffuse.r * light->unk30;
    light->colour.g = light->diffuse.g * light->unk30;
    light->colour.b = light->diffuse.b * light->unk30;
    sLightPositionCache[light->id].x = light->position.x - sLightPositionOffset.x;
    sLightPositionCache[light->id].y = light->position.y - sLightPositionOffset.y;
    sLightPositionCache[light->id].z = light->position.z - sLightPositionOffset.z;
    gd_normalize_vec3f(&sLightPositionCache[light->id]);
    if (light->flags & LIGHT_UNK20) {
        sPhongLightPosition.x = sLightPositionCache[light->id].x;
        sPhongLightPosition.y = sLightPositionCache[light->id].y;
        sPhongLightPosition.z = sLightPositionCache[light->id].z;
        sPhongLight = light;
    }
    sp24 = light->unk30;
    if (light->flags & LIGHT_UNK02) {
        sp20 = -gd_dot_vec3f(&sLightPositionCache[light->id], &light->unk80);
        sp1C = 1.0f - light->unk38 / 90.0f;
        if (sp20 > sp1C) {
            sp20 = (sp20 - sp1C) * (1.0f / (1.0f - sp1C));
            if (sp20 > 1.0f) {
                sp20 = 1.0f;
            } else if (sp20 < 0.0f) {
                sp20 = 0.0f;
            }
        } else {
            sp20 = 0.0f;
        }
        sp24 *= sp20;
    }
    set_light_id(light->id);
    gd_setproperty(GD_PROP_DIFUSE_COLOUR, light->diffuse.r * sp24, light->diffuse.g * sp24, light->diffuse.b * sp24);
    gd_setproperty(GD_PROP_LIGHT_DIR, sLightPositionCache[light->id].x, sLightPositionCache[light->id].y, sLightPositionCache[light->id].z);
    gd_setproperty(GD_PROP_LIGHTING, 2.0f, 0.0f, 0.0f);
}

/* 229568 -> 229658; orig name: func_8017AD98 */
void update_shaders(struct ObjShape *shape, struct GdVec3f *offset) {
    stash_current_gddl();
    sLightPositionOffset.x = offset->x;
    sLightPositionOffset.y = offset->y;
    sLightPositionOffset.z = offset->z;
    sPhongLight = NULL;
    if (gGdLightGroup   != NULL) apply_to_obj_types_in_group(OBJ_TYPE_LIGHTS   , (applyproc_t) update_lighting     , gGdLightGroup );
    if (shape->mtlGroup != NULL) apply_to_obj_types_in_group(OBJ_TYPE_MATERIALS, (applyproc_t) apply_obj_draw_fn, shape->mtlGroup);
    pop_gddl_stash();
}

/**
 * Create `GdDisplayList`s for any `ObjMaterial`s in `shape` that don't already
 * have a GdDL. Doesn't do anything if `shape`'s `mtlGroup` is NULL
 *
 * @param shape Input `ObjShape` to create material GdDLs for
 * @return void
 */
void create_shape_mtl_gddls(struct ObjShape *shape) {
    if (shape->mtlGroup != NULL) apply_to_obj_types_in_group(OBJ_TYPE_MATERIALS, (applyproc_t) create_mtl_gddl_if_empty, shape->mtlGroup);
}

/**
 * Start a new `GdDisplayList` struct and store its reference index
 * in the input `ObjShape`.
 *
 * @param s `ObjShape` to create GdDL for
 * @return Either `-1` if the DL couldn't be created,
 *         or the created DL's reference index
 * @bug Nothing is returned if the DL is created
 * @note Contains string literals that suggest a removed `printf` call
 */
void create_shape_gddl(struct ObjShape *s) {
    struct ObjShape *shape = s;
    s32 shapedl;
    create_shape_mtl_gddls(shape);
    shapedl = gd_startdisplist(7);
    if (shapedl == 0) return;
    setup_lights();
    sUseSelectedColor = FALSE;
    if (shape->unk3C == 0) draw_shape_faces(shape);
    gd_enddlsplist_parent();
    shape->dlNums[0] = shapedl;
    shape->dlNums[1] = shapedl;
}

/**
 * Create `GdDisplayList` structs for all `ObjShapes` in `grp` by calling
 * `create_shape_gddl()`.
 *
 * @param grp `ObjGroup` containing `ObjShape` to create GdDLs for
 * @return void
 * @note Contains string literals that suggest a removed `printf` call
 */
void create_gddl_for_shapes(struct ObjGroup *grp) {
    apply_to_obj_types_in_group(OBJ_TYPE_SHAPES, (applyproc_t) create_shape_gddl, grp); // printf("made %d display lists\n", shapedls);
}

/**
 * Map material id's to `ObjMaterial` pointers for an `ObjGroup` of `ObjFace` structs.
 * This is the final function used in dynlist processing (see `chk_shapegen()`)
 *
 * @param[in,out] faces `ObjGroup` of `ObjFace` structs to map over
 * @param[in]     mtls  `ObjGroup` of `ObjMaterial` structs to map ids to pointers
 * @return void
 */
void map_face_materials(struct ObjGroup *faces, struct ObjGroup *mtls) {
    struct ObjFace *face;
    register struct ListNode *linkFaces;
    struct GdObj *temp;
    register struct ListNode *linkMtls;
    struct ObjMaterial *mtl;
    linkFaces = faces->firstMember;
    while (linkFaces != NULL) {
        temp = linkFaces->obj;
        face = (struct ObjFace *) temp;
        linkMtls = mtls->firstMember;
        while (linkMtls != NULL) {
            mtl = (struct ObjMaterial *) linkMtls->obj;
            if (mtl->id == face->mtlId) break;
            linkMtls = linkMtls->next;
        }
        if (linkMtls != NULL) face->mtl = mtl;
        linkFaces = linkFaces->next;
    }
}

/**
 * @brief Find the closest object to the cursor on an A-button press
 *
 * This function is applied to all objects in an `ObjView.components` group
 * to find the object closest to the cursor when there's an A press
 *
 * @param input `GdObj` to check
 * @return void
 */
void find_closest_pickable_obj(struct GdObj *input) {
    struct GdObj *obj = input;
    f32 distance;
    if ((obj->drawFlags & OBJ_IS_GRABBALE) && (obj->index == sPickDataTemp)) {
        if (gViewUpdateCamera != NULL) {
            distance = d_calc_world_dist_btwn(&gViewUpdateCamera->header, obj);
        } else {
            distance = 0.0f;
        }
        if (distance < sPickObjDistance) {
            sPickObjDistance = distance;
            sPickedObject = obj;
        }
    }
}

/**
 * @brief Set the global view camera if not already set.
 *
 * This function is used to find the first `ObjCamera` when running `update_view()`.
 *
 * @param cam `ObjCamera` to set to the update camera, if possible
 * @return void
 */
void set_view_update_camera(struct ObjCamera *cam) {
    if (gViewUpdateCamera != NULL) return;
    gViewUpdateCamera = cam;
}

/**
 * @brief The main per-frame function for handling a view
 *
 * This function handles updating and rendering a given `ObjView` structure.
 * It also handles the A button input for grabbing an area of an `ObjShape`
 * that is contained in the `ObjView.components` group
 *
 * @param view The `ObjView` to update
 * @return void
 */
void update_view(struct ObjView *view) {
    s32 i;
    s32 pickOffset;
    s32 pickDataSize;
    s32 j;
    s32 pickDataIdx;
    s32 pickedObjType;
    char objTypeAbbr[0x100];
    sUpdateViewState.shapesDrawn = 0;
    if (!(view->flags & VIEW_UPDATE)) {
        view->flags &= ~VIEW_WAS_UPDATED;
        return;
    }
    if (view->proc != NULL) view->proc(view);
    if (!(view->flags & VIEW_WAS_UPDATED)) view->flags |= VIEW_WAS_UPDATED;
    gViewUpdateCamera = NULL;
    if (view->components != NULL) {
        apply_to_obj_types_in_group(OBJ_TYPE_CAMERAS, (applyproc_t) set_view_update_camera, view->components);
        view->activeCam = gViewUpdateCamera;
        if (view->activeCam != NULL) gViewUpdateCamera->unk18C = view;
    }
    if (view->flags & VIEW_MOVEMENT) {
        proc_view_movement(view);
        gViewUpdateCamera = view->activeCam;
    }
    if (!(view->flags & VIEW_DRAW)) return;
    sUpdateViewState.view = view;
    set_active_view(view);
    view->gdDlNum = gd_startdisplist(8);
    start_view_dl(sUpdateViewState.view);
    if (view->flags & (VIEW_UNK_2000 | VIEW_UNK_4000)) gd_set_one_cycle();
    if (view->components != NULL) {
        if (gGdCtrl.dragging) {
            if (gGdCtrl.startedDragging) {
                init_pick_buf(sPickBuffer, ARRAY_COUNT(sPickBuffer));
                drawscene(FIND_PICKS, sUpdateViewState.view->components, NULL);
                pickOffset = get_cur_pickbuf_offset();
                sPickDataTemp = 0;
                sPickedObject = NULL;
                sPickObjDistance = 10000000.0f;
                if (pickOffset < 0) {
                    gd_exit(); // Pick buffer too small
                } else if (pickOffset > 0) {
                    pickDataIdx = 0;
                    for (i = 0; i < pickOffset; i++) {
                        pickDataSize = sPickBuffer[pickDataIdx++];
                        if (pickDataSize != 0) {
                            switch ((pickedObjType = sPickBuffer[pickDataIdx++])) {
                                case OBJ_TYPE_JOINTS:    gd_strcpy(objTypeAbbr, "J"); break;
                                case OBJ_TYPE_NETS:      gd_strcpy(objTypeAbbr, "N"); break;
                                case OBJ_TYPE_PARTICLES: gd_strcpy(objTypeAbbr, "P"); break;
                                default:                 gd_strcpy(objTypeAbbr, "?"); break;
                            }
                        }
                        if (pickDataSize >= 2) {
                            for (j = 0; j < pickDataSize - 1; j++) {
                                sPickDataTemp = sPickBuffer[pickDataIdx++];
                                apply_to_obj_types_in_group(pickedObjType, (applyproc_t) find_closest_pickable_obj, sUpdateViewState.view->components);
                            }
                        }
                    }
                }
                if (sPickedObject != NULL) {
                    sPickedObject->drawFlags |= OBJ_PICKED;
                    sPickedObject->drawFlags |= OBJ_HIGHLIGHTED;
                    sUpdateViewState.view->pickedObj = sPickedObject;
                    gGdCtrl.dragStartX = gGdCtrl.csrX = sGrabCords.x;
                    gGdCtrl.dragStartY = gGdCtrl.csrY = sGrabCords.y;
                }
            }
            find_and_drag_picked_object(sUpdateViewState.view->components);
        } else { // check for any previously picked objects, and turn off?
            if (sUpdateViewState.view->pickedObj != NULL) {
                sUpdateViewState.view->pickedObj->drawFlags &= ~OBJ_PICKED;
                sUpdateViewState.view->pickedObj->drawFlags &= ~OBJ_HIGHLIGHTED;
                sUpdateViewState.view->pickedObj = NULL;
            }
        }
        drawscene(RENDER_SCENE, sUpdateViewState.view->components, sUpdateViewState.view->lights);
    }
    // border_active_view();
    gd_enddlsplist_parent();
    return;
}

