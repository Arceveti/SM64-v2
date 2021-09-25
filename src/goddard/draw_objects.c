#include <PR/ultratypes.h>

#include "string_utils.h"
#include "dynlist_proc.h"
#include "gd_main.h"
#include "objects.h"
#include "renderer.h"
#include "shape_helper.h"
#include "draw_objects.h"
#include "engine/math_util.h"
#include "engine/colors.h"

/**
 * @file draw_objects.c
 * This file contains the functions and helpers for rendering the various
 * GdObj primitives to the screen.
 */

// types
/**
 * Modes for drawscene()
 */
enum SceneType {
    RENDER_SCENE = 26, ///< render the primitives to screen
    FIND_PICKS   = 27  ///< only check position of primitives relative to cursor click
};

// data
static ColorRGBf sClrWhite          = COLOR_RGBF_WHITE;
static ColorRGBf sClrRed            = COLOR_RGBF_RED;
static ColorRGBf sClrGreen          = COLOR_RGBF_GREEN;
static ColorRGBf sClrBlue           = COLOR_RGBF_BLUE;
static ColorRGBf sClrErrDarkBlue    = COLOR_RGBF_ERR_DARK_BLUE;
static ColorRGBf sClrPink           = COLOR_RGBF_PINK;
static ColorRGBf sClrBlack          = COLOR_RGBF_BLACK;
static ColorRGBf sClrGrey           = COLOR_RGBF_GREY;
static ColorRGBf sClrDarkGrey       = COLOR_RGBF_DARK_GREY;
static ColorRGBf sClrYellow         = COLOR_RGBF_YELLOW;
static ColorRGBf sLightColours      = COLOR_RGBF_YELLOW;
static ColorRGBf *sSelectedColour   = &sClrRed;
struct ObjCamera *gViewUpdateCamera = NULL;
static s32 sLightDlCounter = 1;

// bss
struct ObjGroup *gGdLightGroup; // @ 801B9BB8; is this the main light group? only light group?

static enum SceneType sSceneProcessType;
static Bool32 sUseSelectedColor;
static s16 sPickBuffer[100];             ///< buffer of objects near click
static s32 sPickDataTemp;                ///< now, only data is the object number of a selected joint
static f32 sPickObjDistance;             ///< distance between object position and cursor click location
static struct GdObj *sPickedObject;      ///< object selected with cursor
/// Various counters and pointers set in update_view() and used in various `draw_XXX` functions
static struct {
    struct ObjView *view;
    s32 mtlDlNum; // name is a big guess
    s32 shapesDrawn;
} sUpdateViewState;
static struct ObjLight *sPhongLight;    // material light? phong light?
static Vec3f sPhongLightPosition;       // guess; light source unit position for light
                                        // flagged 0x20 (sPhongLight)
static Vec3f sLightPositionOffset;
static Vec3f sLightPositionCache[8];    // unit positions
static s32 sNumActiveLights;            // maybe?
static Vec3f sGrabCords;                ///< x, y grabbable point near cursor

/**
 * Set the ambient light color and turn on G_CULL_BACK.
 */
void setup_lights(void) {
    set_light_num(NUMLIGHTS_2);
    gd_setproperty(GD_PROP_AMB_COLOUR, 0.5f, 0.5f, 0.5f);
    gd_setproperty(GD_PROP_CULLING,    1.0f, 0.0f, 0.0f); // set G_CULL_BACK
    return;
}

/* 226C6C -> 226FDC */
void draw_shape(struct ObjShape *shape, s32 flag, f32 c, f32 d, f32 e, // "sweep" indices 0-2 x, y, z
                f32 f, f32 g, f32 h, // translate shape + store offset (unused)
                f32 i, f32 j, f32 k, // translate shape
                f32 l, f32 m, f32 n, // rotate x, y, z
                s32 colorIdx, Mat4 *rotMtx) {
    Vec3f vec;
    sUpdateViewState.shapesDrawn++;
    if (shape == NULL) return;
    vec3_zero(vec);
    if (flag & 0x02) {
        gd_dl_load_trans_matrix(f, g, h);
        vec[0] += f;
        vec[1] += g;
        vec[2] += h;
    }
    if ((flag & 0x10) && rotMtx != NULL) {
        gd_dl_load_matrix(rotMtx);
        vec3_add(vec, (*rotMtx)[3]);
    }
    if (flag & 0x08) {
        if (m != 0.0f) gd_dl_rotate(m, 121);
        if (l != 0.0f) gd_dl_rotate(l, 120);
        if (n != 0.0f) gd_dl_rotate(n, 122);
    }
    if (colorIdx != 0) {
        sUseSelectedColor = TRUE;
        sSelectedColour = gd_get_colour(colorIdx);
        if (sSelectedColour != NULL) {
            gd_dl_material_lighting(-1, *sSelectedColour, GD_MTL_LIGHTS);
        } else {
            gd_exit(); // Bad colour
        }
    } else {
        sUseSelectedColor = FALSE;
        sSelectedColour   = NULL;
    }
    if ((sNumActiveLights != 0) && (shape->mtlGroup != NULL)) {
        if (rotMtx != NULL) {
            vec3_copy(vec, (*rotMtx)[3]);
        } else {
            vec3_zero(vec);
        }
        update_shaders(shape, vec);
    }
    if (flag & 0x04) gd_dl_mul_trans_matrix(i, j, k);
    if (flag & 0x01) gd_dl_scale(c, d, e);
    draw_shape_faces(shape);
    sUseSelectedColor = FALSE;
}

void draw_shape_2d(struct ObjShape *shape, s32 flag, Vec3f in) {
    Vec3f pos = { 0.0f, 0.0f, 0.0f };
    sUpdateViewState.shapesDrawn++;
    if (shape == NULL) return;
    if (flag & 0x02) {
        if (gViewUpdateCamera != NULL) linear_mtxf_mul_vec3f_and_translate(gViewUpdateCamera->lookatMtx, pos, in);
        gd_dl_load_trans_matrix(pos[0], pos[1], pos[2]);
    }
    draw_shape_faces(shape);
}

void draw_light(struct ObjLight *light) {
    struct ObjShape *shape;
    if (sSceneProcessType == FIND_PICKS) return;
    vec3_copy(sLightColours, light->colour);
    if (light->flags & LIGHT_UNK02) {
        shape = gSpotShape;
    } else {
        shape = light->shapePtr;
        if (++sLightDlCounter >= 17) sLightDlCounter = 1;
        shape->frameIndex = sLightDlCounter;
    }
    draw_shape_2d(shape, 2, light->position);
}

void draw_material(struct ObjMaterial *mtl) {
    s32 mtlType = mtl->type;
    if (mtlType == GD_MTL_SHINE_DL) {
        if ((sPhongLight != NULL) && (sPhongLight->diffuseFac > 0.0f)) {
            if (gViewUpdateCamera != NULL) {
                gd_dl_hilite(mtl->gddlNumber, gViewUpdateCamera, sPhongLightPosition, sPhongLight->colour);
            } else {
                gd_exit(); // no active camera for phong
            }
        } else {
            mtlType = GD_MTL_BREAK;
        }
    }
    if (!sUseSelectedColor) {
        gd_dl_material_lighting(mtl->gddlNumber, mtl->Kd, mtlType);
    } else {
        gd_dl_material_lighting(mtl->gddlNumber, *sSelectedColour, GD_MTL_LIGHTS);
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
 * @brief Convert a numeric index into pointer to a struct ColorRGBf
 *
 * A simple switch case to convert from index @p idx to a pointer to the
 * three f32 ColorRGBf structure. Goddard stored the index in a structure,
 * and uses this function to get the colour RGB values if needed.
 * -1 uses the environment colour.
 * A possible enhancement for this is to ennumerate all colours, and then
 * use those enumerations and/or enum type where ever a colour is requested
 *
 * @param idx Index of colour
 * @return Pointer to a ColorRGBf struct
 */
ColorRGBf *gd_get_colour(s32 idx) {
    switch (idx) {
        case COLOUR_BLACK:     return &sClrBlack;       break;
        case COLOUR_WHITE:     return &sClrWhite;       break;
        case COLOUR_RED:       return &sClrRed;         break;
        case COLOUR_GREEN:     return &sClrGreen;       break;
        case COLOUR_BLUE:      return &sClrBlue;        break;
        case COLOUR_GRAY:      return &sClrGrey;        break;
        case COLOUR_DARK_GRAY: return &sClrDarkGrey;    break;
        case COLOUR_DARK_BLUE: return &sClrErrDarkBlue; break;
        case COLOUR_BLACK2:    return &sClrBlack;       break;
        case COLOUR_YELLOW:    return &sClrYellow;      break;
        case COLOUR_PINK:      return &sClrPink;        break;
        case -1:               return &sLightColours;   break;
        default:               return NULL;
    }
}

/**
 * Rendering function for `ObjFace` structures. It has a fair amount
 * of stub code
 */
void draw_face(struct ObjFace *face) {
    struct ObjVertex *vtx;
    // f32 z, y, x;
    Vec3f pos;
    s32 i; // also used to store mtl's gddl number
    Vtx *gbiVtx;
    if (!sUseSelectedColor
     && (face->mtlId >= 0) // -1 == colored face
     && (face->mtl != NULL)
     && ((i = face->mtl->gddlNumber) != 0)
     && (i != sUpdateViewState.mtlDlNum)) {
        gd_dl_flush_vertices();
        branch_to_gddl(i);
        sUpdateViewState.mtlDlNum = i;
    }
    check_tri_display(face->vtxCount);
    for ((i = 0); (i < face->vtxCount); (i++)) {
        vtx = face->vertices[i];
        vec3_copy(pos, vtx->pos);
        set_Vtx_norm_buf_2(vtx->normal);
        gbiVtx = gd_dl_make_vertex(pos[0], pos[1], pos[2], vtx->alpha);
        if (gbiVtx != NULL) vtx->gbiVerts = make_vtx_link(vtx->gbiVerts, gbiVtx);
    }
    flush_current_triangle_buffer();
}

/* 227DF8 -> 227F3C; orig name: Proc80179628 */
void draw_net(struct ObjNet *self) {
    struct ObjNet *net = self;
    s32 netColor;
    if (sSceneProcessType == FIND_PICKS) return;
    netColor = ((net->header.drawFlags & OBJ_HIGHLIGHTED) ? COLOUR_YELLOW : net->colourNum);
    if (net->shapePtr != NULL) draw_shape(net->shapePtr, 0x10, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, netColor, &net->rotationMtx);
    if (net->nodeGrp  != NULL) draw_group(net->nodeGrp);
}

/* 22803C -> 22829C */
void draw_camera(struct ObjCamera *cam) {
    Vec3f pos = { 0.0f, 0.0f, 0.0f };
    if (cam->dynObj != NULL) {
        set_cur_dynobj(cam->dynObj);
        d_vec3f_get_world_pos(pos);
        vec3_add(pos, cam->lookAt);
    } else {
        vec3_copy(pos, cam->lookAt);
    }
    if (absf(cam->worldPos[0] - pos[0]) + absf(cam->worldPos[2] - pos[2]) == 0.0f) return; // Zero view distance
    gd_dl_lookat(cam, cam->worldPos, pos, cam->colXY);
}

/* 22836C -> 228498 */
void world_pos_to_screen_coords(Vec3f pos, struct ObjCamera *cam, struct ObjView *view) {
    linear_mtxf_mul_vec3f_self_and_translate(cam->lookatMtx, pos);
    if (pos[2] > -256.0f) return;
    pos[0] *= (256.0f / -pos[2]);
    pos[1] *= (256.0f /  pos[2]);
    pos[0] += (view->lowerRight[0] / 2.0f);
    pos[1] += (view->lowerRight[1] / 2.0f);
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
    if (gViewUpdateCamera == NULL) return;
    struct GdObj  *obj = input;
    if (!(obj->drawFlags & OBJ_IS_GRABBALE)) return;
    set_cur_dynobj(obj);
    Mat4 *mtx = d_get_rot_mtx_ptr();
    Vec3f objPos;
    vec3_copy(objPos, (*mtx)[3]);
    world_pos_to_screen_coords(objPos, gViewUpdateCamera, sUpdateViewState.view);
    if ((absf(gGdCtrl.csrX - objPos[0]) < 20.0f)
     && (absf(gGdCtrl.csrY - objPos[1]) < 20.0f)) {
        // store (size, Obj Type, Obj Index) in s16 pick buffer array
        store_in_pickbuf(2);
        store_in_pickbuf(obj->type);
        store_in_pickbuf(obj->index);
        sGrabCords[0] = objPos[0];
        sGrabCords[1] = objPos[1];
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
        gd_create_perspective_matrix(sUpdateViewState.view->clipping[2],
                      (sUpdateViewState.view->lowerRight[0] / sUpdateViewState.view->lowerRight[1]),
                       sUpdateViewState.view->clipping[0],    sUpdateViewState.view->clipping[1]);
    } else {
        gd_create_ortho_matrix(
            (-sUpdateViewState.view->lowerRight[0] / 2.0f), (sUpdateViewState.view->lowerRight[0] / 2.0f),
            (-sUpdateViewState.view->lowerRight[1] / 2.0f), (sUpdateViewState.view->lowerRight[1] / 2.0f),
              sUpdateViewState.view->clipping[0],            sUpdateViewState.view->clipping[1]);
    }
    if (lightgrp != NULL) {
        set_gd_mtx_parameters(G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_PUSH);
        apply_to_obj_types_in_group((OBJ_TYPE_LIGHTS | OBJ_TYPE_PARTICLES), (applyproc_t) apply_obj_draw_fn, lightgrp);
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
        apply_to_obj_types_in_group((OBJ_TYPE_LIGHTS | OBJ_TYPE_NETS | OBJ_TYPE_PARTICLES), (applyproc_t) apply_obj_draw_fn, interactables);
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
        draw_indexed_dl(shape->dlNums[gGdFrameBufNum], shape->frameIndex);
    } else if (shape->faceGroup != NULL) {
        gd_dl_reset_buffers();
        draw_group(shape->faceGroup);
        gd_dl_flush_vertices();
    }
}

/**
 * Rendering function for `ObjParticle`.
 */
void draw_particle(struct GdObj *obj) {
    struct ObjParticle *ptc = (struct ObjParticle *) obj;
    if (ptc->timeout > 0) {
        ColorRGBf white;
        vec3_copy(white, sClrWhite);
        ColorRGBf black;
        vec3_copy(black, sClrBlack);
        f32 brightness = (ptc->timeout / 10.0f);
        sLightColours[0] = (((white[0] - black[0]) * brightness) + black[0]);
        sLightColours[1] = (((white[1] - black[1]) * brightness) + black[1]);
        sLightColours[2] = (((white[2] - black[2]) * brightness) + black[2]);
    } else {
        vec3_zero(sLightColours);
    }
    if (ptc->timeout > 0) {
        ptc->shapePtr->frameIndex = ptc->timeout;
        draw_shape_2d(ptc->shapePtr, 2, ptc->pos);
    }
    if ((ptc->particleType == 3) && (ptc->subParticlesGrp != NULL)) draw_group(ptc->subParticlesGrp);
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
    vec3_prod_val(light->colour, light->diffuse, light->diffuseFac);
    Vec3f lightPos;
    vec3_diff(lightPos, light->position, sLightPositionOffset);
    vec3_normalize(lightPos);
    vec3_copy(sLightPositionCache[light->id], lightPos);
    if (light->flags & LIGHT_UNK20) {
        vec3_copy(sPhongLightPosition, sLightPositionCache[light->id]);
        sPhongLight = light;
    }
    f32 diffuseFac = light->diffuseFac;
    if (light->flags & LIGHT_UNK02) {
        f32 facMul;
        f32 diffuseThreshold = (1.0f - (light->diffuseTheta / 90.0f));
        if (diffuseThreshold < 0.0f) {
            facMul = (-diffuseThreshold * (1.0f / (1.0f - diffuseThreshold)));
            facMul = CLAMP(facMul, 0.0f, 1.0f);
        } else {
            facMul = 0.0f;
        }
        diffuseFac *= facMul;
    }
    set_light_id(light->id);
    gd_setproperty(GD_PROP_DIFUSE_COLOUR, (light->diffuse[0] * diffuseFac), (light->diffuse[1] * diffuseFac), (light->diffuse[2] * diffuseFac));
    gd_setproperty(GD_PROP_LIGHT_DIR, sLightPositionCache[light->id][0], sLightPositionCache[light->id][1], sLightPositionCache[light->id][2]);
    gd_setproperty(GD_PROP_LIGHTING, 2.0f, 0.0f, 0.0f);
}

/* 229568 -> 229658; orig name: func_8017AD98 */
void update_shaders(struct ObjShape *shape, Vec3f offset) {
    stash_current_gddl();
    vec3_copy(sLightPositionOffset, offset);
    sPhongLight = NULL;
    if (gGdLightGroup   != NULL) apply_to_obj_types_in_group(OBJ_TYPE_LIGHTS,    (applyproc_t) update_lighting,   gGdLightGroup  );
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
 */
void create_shape_gddl(struct ObjShape *s) {
    struct ObjShape *shape = s;
    create_shape_mtl_gddls(shape);
    s32 shapedl = gd_startdisplist(7);
    if (shapedl == 0) return;
    setup_lights();
    sUseSelectedColor = FALSE;
    if (!shape->cullFaces) draw_shape_faces(shape);
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
 */
void create_gddl_for_shapes(struct ObjGroup *grp) {
    apply_to_obj_types_in_group(OBJ_TYPE_SHAPES, (applyproc_t) create_shape_gddl, grp); // made [shapedls] display lists
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
    struct GdObj *temp;
    struct ObjMaterial *mtl;
    register struct ListNode *linkMtls;
    register struct ListNode *linkFaces = faces->firstMember;
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
            sPickedObject    = obj;
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
    s32 i, j;
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
                s32 pickOffset   = get_cur_pickbuf_offset();
                sPickDataTemp    = 0;
                sPickedObject    = NULL;
                sPickObjDistance = 10000000.0f;
                if (pickOffset < 0) {
                    gd_exit(); // Pick buffer too small
                } else if (pickOffset > 0) {
                    s32 pickDataIdx = 0;
                    s32 pickDataSize;
                    s32 pickedObjType;
                    for ((i = 0); (i < pickOffset); (i++)) {
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
                            for ((j = 0); (j < (pickDataSize - 1)); (j++)) {
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
                    gGdCtrl.dragStartX = gGdCtrl.csrX = sGrabCords[0];
                    gGdCtrl.dragStartY = gGdCtrl.csrY = sGrabCords[1];
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
