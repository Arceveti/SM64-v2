#include <PR/ultratypes.h>

#include "string_utils.h"
#include "draw_objects.h"
#include "dynlist_proc.h"
#include "gd_math.h"
#include "joints.h"
#include "objects.h"
#include "renderer.h"
#include "shape_helper.h"
#include "skin.h"

/**
 * @file dynlist_proc.c
 *
 * Functions for parsing and processing Goddard's DynList object format.
 * It also has utility functions for abstracting at runtime over the various
 * flavors of `GdObj`s.
 */

// constants
/// Size of the dynamic object name buffer
#define DYNOBJ_NAME_SIZE 8
/// Total number of dynamic `GdObj`s that can be created
#define DYNOBJ_LIST_SIZE 3000
/// Maximum number of verticies supported when adding vertices node to an `ObjShape`
#define VTX_BUF_SIZE     3000

// types
/// Information about a dynamically created `GdObj`
struct DynObjInfo {
    char name[DYNOBJ_NAME_SIZE];
    struct GdObj *obj;
    s32 num;
    s32 unk;
};
/// @name DynList Accessors
/// Accessor marcos for easy interpretation of data in a `DynList` packet
///@{
#define Dyn1AsInt( dyn) ((dyn)->w1.word)
#define Dyn1AsPtr( dyn) ((dyn)->w1.ptr)
#define Dyn1AsStr( dyn) ((dyn)->w1.str)
#define Dyn1AsName(dyn) ((DynObjName)((dyn)->w1.ptr))

#define Dyn2AsInt( dyn) ((dyn)->w2.word)
#define Dyn2AsPtr( dyn) ((dyn)->w2.ptr)
#define Dyn2AsStr( dyn) ((dyn)->w2.str)
#define Dyn2AsName(dyn) ((DynObjName)((dyn)->w2.ptr))

#define DynVec( dyn) ((dyn)->vec)
#define DynVecX(dyn) ((dyn)->vec[0])
#define DynVecY(dyn) ((dyn)->vec[1])
#define DynVecZ(dyn) ((dyn)->vec[2])
///@}

// data
static struct DynObjInfo *sGdDynObjList  = NULL;  // @ 801A8250; info for all loaded/made dynobjs
static struct GdObj      *sDynListCurObj = NULL;  // @ 801A8254
static Bool32 sUseIntegerNames           = FALSE; // if TRUE, then all DynNames are specified as integers

// bss
static char sIntToStringBuf[DYNOBJ_NAME_SIZE];    ///< buffer for returning formated string from
                                                  ///< `integer_name_to_string()`
static struct DynObjInfo sNullDynObjInfo;         // @ 801B9F08
static char sDynNameSuffix[DYNOBJ_NAME_SIZE];     // @ 801B9F20; small buf for printing dynid to?
static s32 sUnnamedObjCount;                      // @ 801B9F28; used to print empty string ids (not NULL char *) to sDynNameSuffix
static s32 sLoadedDynObjs;                        // @ 801B9F2C; total loaded dynobjs
static struct DynObjInfo *sDynListCurInfo;        // @ 801B9F30; info for most recently added object
static struct DynObjInfo *sParentObjInfo;         ///< Information for `ObjNet` made by `d_add_net_with_subgroup()` or `ObjJoint` made by `d_attach_joint_to_net()`
static struct DynObjInfo *sStashedDynObjInfo;     // @ 801B9F38
static struct GdObj *sStashedDynObj;              // @ 801B9F3C
static s32 sDynNetCount;                          // @ 801B9F40
static char sDynNetNameSuffix[0x20];              // @ 801B9F48
static char sStashedDynNameSuffix[0x100];         // @ 801B9F68

// necessary foreward declarations
void d_add_net_with_subgroup(   DynObjName name);
void d_end_net_with_subgroup(   DynObjName name);
void d_attach_joint_to_net(     DynObjName name);
void d_link_with(               DynObjName name);
void d_link_with_ptr(void *ptr);
void d_set_rotation(f32 x, f32 y, f32 z);
void d_attach_to(     s32 flag, struct GdObj *obj);
void d_attachto_dynid(s32 flag, DynObjName name);
void d_set_att_offset(      Vec3f off);
void d_vec3f_set_att_offset(Vec3f off);
void d_set_nodegroup(           DynObjName name);
void d_set_matgroup(            DynObjName name);
void d_set_skinshape(           DynObjName name);
void d_set_planegroup(          DynObjName name);
void d_set_shapeptr(            DynObjName name);
void d_set_ambient(ColorF r, ColorF g, ColorF b);
void d_set_skin_weight(s32 vtxId, f32 percentWeight);
void d_set_id(s32 id);
void add_to_dynobj_list(struct GdObj *newObj, DynObjName name);

/**
 * Store the active dynamic `GdObj` into a one object stash.
 */
void d_stash_dynobj(void) {
    sStashedDynObjInfo = sDynListCurInfo;
    sStashedDynObj     = sDynListCurObj;
}

/**
 * Set the stashed `GdObj` as the active dynamic `GdObj`.
 */
void d_unstash_dynobj(void) {
    sDynListCurObj  = sStashedDynObj;
    sDynListCurInfo = sStashedDynObjInfo;
}

/**
 * Parse a `DynList` array into active `GdObj`s.
 *
 * @returns Pointer to current dynamically created dynamic `GdObj`.
 *          Normally the dynlist specifically sets an object for return.
 */
struct GdObj *proc_dynlist(struct DynList *dylist) {
    if (dylist++->cmd != 0xD1D4) gd_exit(); // not a valid dyn list
    while (dylist->cmd != 58) {
        switch (dylist->cmd) {
            case 15: d_makeobj(          Dyn2AsInt(dylist), Dyn1AsName(dylist)                               ); break;
            case 46: d_add_net_with_subgroup(               Dyn1AsName(dylist)                               ); break;
            case 48: d_end_net_with_subgroup(               Dyn1AsName(dylist)                               ); break;
            case 47: d_attach_joint_to_net(                 Dyn1AsName(dylist)                               ); break;
            case 16: d_start_group(                         Dyn1AsName(dylist)                               ); break;
            case 17: d_end_group(                           Dyn1AsName(dylist)                               ); break;
            case 30: d_use_obj(                             Dyn1AsName(dylist)                               ); break;
            case 28: d_link_with(                           Dyn1AsName(dylist)                               ); break;
            case 29: d_link_with_ptr(    Dyn1AsPtr(dylist)                                                   ); break;
            case 12: proc_dynlist(       Dyn1AsPtr(dylist)                                                   ); break;
            case  0: d_use_integer_names(Dyn2AsInt(dylist)                                                   ); break;
            case  5: d_set_scale(                           DynVecX(dylist), DynVecY(dylist), DynVecZ(dylist)); break;
            case  6: d_set_rotation(                        DynVecX(dylist), DynVecY(dylist), DynVecZ(dylist)); break;
            case  8: d_set_flags(        Dyn2AsInt(dylist)                                                   ); break;
            case 40: d_attachto_dynid(   Dyn2AsInt(dylist), Dyn1AsName(dylist)                               ); break;
            case 41: d_set_att_offset(      DynVec(dylist)                                                   ); break;
            case 21: d_set_nodegroup(                       Dyn1AsName(dylist)                               ); break;
            case 20: d_set_matgroup(                        Dyn1AsName(dylist)                               ); break;
            case 22: d_set_skinshape(                       Dyn1AsName(dylist)                               ); break;
            case 23: d_set_planegroup(                      Dyn1AsName(dylist)                               ); break;
            case 24: d_set_shapeptrptr(  Dyn1AsPtr(dylist)                                                   ); break;
            case 25: d_set_shapeptr(                        Dyn1AsName(dylist)                               ); break;
            case 19: d_set_type(         Dyn2AsInt(dylist)                                                   ); break;
            case 33: d_set_ambient(                         DynVecX(dylist), DynVecY(dylist), DynVecZ(dylist)); break;
            case 34: d_set_diffuse(                         DynVecX(dylist), DynVecY(dylist), DynVecZ(dylist)); break;
            case 32: d_set_skin_weight(  Dyn2AsInt(dylist), DynVecX(dylist)                                  ); break;
            case 35: d_set_id(           Dyn2AsInt(dylist)                                                   ); break;
            default: gd_exit(); // unkown command
        }
        dylist++;
    }
    return sDynListCurObj;
}

/**
 * Copy input `str` into a buffer that will be concatenated to a dynamic
 * `GdObj`'s name string when creating a new dynamic object. If input
 * is `NULL`, then a generic string is created based on the number of
 * unnamed objects.
 */
void d_set_name_suffix(char *str) {
    if (str != NULL) {
        if (str[0] == '\0') {
            sprintf(sDynNameSuffix, "__%d", ++sUnnamedObjCount);
        } else {
            gd_strcpy(sDynNameSuffix, str);
        }
    } else {
        sDynNameSuffix[0] = '\0';
    }
}

/**
 * Stash the current string that is appended to a created dynamic `GdObj` name.
 */
static void stash_name_suffix(void) {
    gd_strcpy(sStashedDynNameSuffix, sDynNameSuffix);
}

/**
 * Pop the stash for the string that is appended to a created dynamic `GdObj` name.
 */
static void unstash_name_suffix(void) {
    gd_strcpy(sDynNameSuffix, sStashedDynNameSuffix);
}

/**
 * Get the `DynObjInfo` struct for object `name`
 *
 * @param name Either a string or integer id for a dynamic `GdObj`
 * @returns pointer to that object's information
 */
static struct DynObjInfo *get_dynobj_info(DynObjName name) {
    struct DynObjInfo *foundDynobj;
    char buf[0x100];
    s32 i;
    if (sLoadedDynObjs == 0) return NULL;
    if (sUseIntegerNames) {
        sprintf(buf, "N%d", DynNameAsInt(name));
    } else {
        gd_strcpy(buf, DynNameAsStr(name));
    }
    gd_strcat(buf, sDynNameSuffix);
    foundDynobj = NULL;
    for ((i = 0); (i < sLoadedDynObjs); (i++)) {
        if (gd_str_not_equal(sGdDynObjList[i].name, buf) == 0) {
            foundDynobj = &sGdDynObjList[i];
            break;
        }
    }
    return foundDynobj;
}

/**
 * Create an `ObjNet` and an associated node `ObjGroup`. This function creates
 * its own naming string to append to later created dynamic objects.
 */
void d_add_net_with_subgroup(DynObjName name) {
    d_makeobj(D_NET, name);
    d_set_obj_draw_flag(OBJ_INVISIBLE);
    // this creates a string to append to the names of the objs created after this
    sprintf(sDynNetNameSuffix, "c%d", ++sDynNetCount);
    d_set_type(4);
    stash_name_suffix();
    d_set_name_suffix(sDynNetNameSuffix);
    d_start_group(name);
    unstash_name_suffix();
    d_use_obj(name);
    sParentObjInfo = sDynListCurInfo;
}

/**
 * End the `ObjNet`+`ObjGroup` set created by `d_add_net_with_subgroup()`.
 */
void d_end_net_with_subgroup(DynObjName name) {
    d_use_obj(name);
    stash_name_suffix();
    d_set_name_suffix(sDynNetNameSuffix);
    d_end_group(name);
    d_set_nodegroup(name);
    unstash_name_suffix();
    sParentObjInfo = NULL;
}

/**
 * Create an `ObjJoint` and attach that to the `ObjNet` created by
 * `d_add_net_with_subgroup()` or the most recent `ObjJoint` created
 * by `d_attach_joint_to_net()`.
 *
 * @param arg0 Not used
 * @param name   Name for created `ObjJoint`
 */
void d_attach_joint_to_net(DynObjName name) {
    d_makeobj(D_JOINT, name);
    d_set_type(3);
    d_set_shapeptrptr(NULL);
    d_attach_to(0xD, sParentObjInfo->obj);
    sParentObjInfo = sDynListCurInfo;
}

/**
 * Add `newobj` identified by `name` to the dynamic `GdObj` list. Once a `GdObj`
 * is in the dynamic list, it can referred to by its `name` when that object is
 * needed later.
 */
void add_to_dynobj_list(struct GdObj *newobj, DynObjName name) {
    char idbuf[0x100];
    if (sLoadedDynObjs < DYNOBJ_LIST_SIZE) {
        if (sGdDynObjList == NULL) {
            sGdDynObjList = gd_malloc_temp(DYNOBJ_LIST_SIZE * sizeof(struct DynObjInfo));
            if (sGdDynObjList == NULL) gd_exit(); // Cant allocate dynlist memory
        }
        if (sUseIntegerNames) {
            sprintf(idbuf, "N%d", DynNameAsInt(name));
            name = NULL;
        } else {
            sprintf(idbuf, "U%d", ((u32) sLoadedDynObjs) + 1);
        }
        if (DynNameAsStr(name) != NULL) {
            if (get_dynobj_info(name) != NULL) gd_exit(); // Object with same name already exists
            gd_strcpy(sGdDynObjList[sLoadedDynObjs].name, DynNameAsStr(name));
        } else {
            gd_strcpy(sGdDynObjList[sLoadedDynObjs].name, idbuf);
        }
        gd_strcat(sGdDynObjList[sLoadedDynObjs].name, sDynNameSuffix);
        if (gd_strlen(sGdDynObjList[sLoadedDynObjs].name) > (DYNOBJ_NAME_SIZE - 1)) gd_exit(); // dyn list obj name too long
        sGdDynObjList[sLoadedDynObjs].num   = sLoadedDynObjs;
        sDynListCurInfo                     = &sGdDynObjList[sLoadedDynObjs];
        sGdDynObjList[sLoadedDynObjs++].obj = newobj;
    } else {
        gd_exit(); // Too many dynlist objects
    }
    sDynListCurObj = newobj;
}

/**
 * Format `name` into string, if `DynObjName`s are currently being interpreted
 * as numbers.
 *
 * @returns pointer to global buffer for id
 * @retval NULL if `name` is `NULL` or if `DynObjName`s are interpreted as strings
 */
static char *integer_name_to_string(DynObjName name) {
    if ((DynNameAsInt(name) != 0) && sUseIntegerNames) {
        sprintf(sIntToStringBuf, "N%d", DynNameAsInt(name));
        return sIntToStringBuf;
    }
    return NULL;
}

/**
 * Create a new `GdObj` of `type` and add that object to the
 * dynamic object list with `name`. Created objects have default
 * parameters, which are usually 0 or NULL.
 *
 * @returns pointer to created object
 */
struct GdObj *d_makeobj(enum DObjTypes type, DynObjName name) {
    struct GdObj *dobj;
    switch (type) {
        case D_JOINT:    dobj = &make_joint(0, gVec3fZero)->header;                      break;
        case D_NET:      dobj = &make_net(NULL)->header;                                 break;
        case D_GROUP:    dobj = &make_group(0)->header;                                  break;
        case D_DATA_GRP: d_makeobj(D_GROUP, name); ((struct ObjGroup *) sDynListCurObj)->linkType = 1; return NULL;
        case D_CAMERA:   dobj = &make_camera()->header;                                  break;
        case D_MATERIAL: dobj = &make_material()->header;                                break;
        case D_SHAPE:    dobj = &make_shape(integer_name_to_string(name))->header;       break;
        case D_ANIMATOR: dobj = &make_animator()->header;                                break;
        case D_LIGHT:    dobj = &make_light()->header; addto_group(gGdLightGroup, dobj); break;
        default: gd_exit(); // Unkown object type
    }
    add_to_dynobj_list(dobj, name);
    return dobj;
}

/**
 * Attach the current dynamic `GdObj` into the proper subgroup of `obj` and set
 * the "attach flags" of the current dynamic object to `flag`
 */
void d_attach_to(s32 flag, struct GdObj *obj) {
    struct ObjGroup *attgrp;
    Vec3f currObjPos; // transformed into attach offset
    Vec3f objPos;
    d_stash_dynobj();
    if (sDynListCurObj == NULL) gd_exit();
    // find or generate attachment groups
    switch (obj->type) {
        case OBJ_TYPE_JOINTS:    if ((attgrp = ((struct ObjJoint    *) obj)->attachedObjsGrp) == NULL) attgrp = ((struct ObjJoint    *) obj)->attachedObjsGrp = make_group(0); break;
        case OBJ_TYPE_NETS:      if ((attgrp = ((struct ObjNet      *) obj)->attachedObjsGrp) == NULL) attgrp = ((struct ObjNet      *) obj)->attachedObjsGrp = make_group(0); break;
        case OBJ_TYPE_PARTICLES: if ((attgrp = ((struct ObjParticle *) obj)->attachedObjsGrp) == NULL) attgrp = ((struct ObjParticle *) obj)->attachedObjsGrp = make_group(0); break;
        case OBJ_TYPE_ANIMATORS: if ((attgrp = ((struct ObjAnimator *) obj)->attachedObjsGrp) == NULL) attgrp = ((struct ObjAnimator *) obj)->attachedObjsGrp = make_group(0); break;
        default: gd_exit(); // fatal_printf("%s: Object '%s'(%x) does not support this function.", "dAttachTo()", sDynListCurInfo->name, sDynListCurObj->type);
    }
    if (group_contains_obj(attgrp, sDynListCurObj)) return;
    addto_group(attgrp, sDynListCurObj);
    if (flag & 0x9) {
        d_vec3f_get_world_pos(currObjPos);
        set_cur_dynobj(obj);
        d_vec3f_get_world_pos(objPos);
        vec3f_sub(currObjPos, objPos);
    }
    d_unstash_dynobj();
    switch (sDynListCurObj->type) {
        case OBJ_TYPE_JOINTS:
            ((struct ObjJoint    *) sDynListCurObj)->attachFlags   = flag;
            ((struct ObjJoint    *) sDynListCurObj)->attachedToObj = obj;
            break;
        case OBJ_TYPE_NETS:
            ((struct ObjNet      *) sDynListCurObj)->attachFlags   = flag;
            ((struct ObjNet      *) sDynListCurObj)->attachedToObj = obj;
            break;
        case OBJ_TYPE_PARTICLES:
            ((struct ObjParticle *) sDynListCurObj)->attachFlags   = flag;
            ((struct ObjParticle *) sDynListCurObj)->attachedToObj = obj;
            break;
        case OBJ_TYPE_ANIMATORS:
            ((struct ObjAnimator *) sDynListCurObj)->attachFlags   = flag;
            ((struct ObjAnimator *) sDynListCurObj)->attachedToObj = obj;
            break;
        default: gd_exit(); // fatal_printf("%s: Object '%s'(%x) does not support this function.", "dAttachTo()", sDynListCurInfo->name, sDynListCurObj->type);
    }

    if (flag & 0x9) d_vec3f_set_att_offset(currObjPos);
}

/**
 * Attach the current dynamic object to dynamic object `name`. This function
 * is a wrapper around `d_attach_to()`
 */
void d_attachto_dynid(s32 flag, DynObjName name) {
    struct DynObjInfo *info;
    if (name == NULL) return;
    if (sDynListCurObj == NULL) gd_exit();
    info = get_dynobj_info(name);
    if (info == NULL) gd_exit(); // fatal_printf("dAttachTo(\"%s\"): Undefined object", DynNameAsStr(name));
    d_attach_to(flag, info->obj);
}

/**
 * Helper function to copy bytes. Where's memcpy when you need it?
 */
void copy_bytes(u8 *src, u8 *dst, s32 num) {
    if (num == 0) return;
    while (num--) *dst++ = *src++;
}

/**
 * Allocate the animation data for `animator` onto the goddard heap.
 * Animation data of type `::GD_ANIM_SCALE3S_POS3S_ROT3S` is converted to a `AnimMtxVec` struct,
 * rather than solely byted copied like the other types.
 */
void alloc_animdata(struct ObjAnimator *animator) {
    // probably should be three GdVec3fs, not triangle...
    // vec0 = position; vec1 = scale? rotation?; vec2 = translation
    struct GdTriangleF tri;           //+58; temp float for converting half to f32?
    s16(*halfarr)[9];                 //+54; data to convert into a AnimMtxVec
    struct AnimDataInfo *curAnimSrc;  //+50; source animation data...
    struct AnimDataInfo *animDst;     //+4c; destination anim data II
    struct AnimDataInfo *animDataArr; //+48; start of allocated anim data memory
    struct ObjGroup     *animgrp;     //+44
    s32 datasize;                     //+40; anim data allocation size?
    s32 dataIdx;                      //+3C; byte count?
    s32 animCnt;                      //+38; count of animdata "info" structs
    s32 i;                            //+34
    void *allocSpace;                 //+30; allocated animdata space
    f32 allocMtxScale = 0.1f;         //+2C; scale postion/rotation of GD_ANIM_SCALE3S_POS3S_ROT3S data
    struct AnimMtxVec *curMtxVec;     //+28
    if ((animgrp    = animator->animdataGrp) == NULL) gd_exit(); // no anim group
    if ((curAnimSrc = (struct AnimDataInfo *) animgrp->firstMember->obj) == NULL) gd_exit(); // no animation data
    // count number of array-ed animation data structs
    animDst = curAnimSrc;
    animCnt = 0;
    while ((animDst++)->count >= 0) animCnt++;
    animDst = gd_malloc_perm(animCnt * sizeof(struct AnimDataInfo)); // gd_alloc_perm
    if ((animDataArr = animDst) == NULL) gd_exit(); // cant allocate animation data
    for ((i = 0); (i < animCnt); (i++)) {
        allocSpace = NULL;
        if (curAnimSrc->type != 0) {
            switch (curAnimSrc->type) {
                case GD_ANIM_CAMERA_EYE3S_LOOKAT3S: datasize = sizeof(s16[6]);            break;
                case GD_ANIM_ROT3S:                 datasize = sizeof(s16[3]);            break;
                case GD_ANIM_POS3S:                 datasize = sizeof(s16[3]);            break;
                case GD_ANIM_ROT3S_POS3S:           datasize = sizeof(s16[6]);            break;
                case GD_ANIM_SCALE3F_ROT3F_POS3F:   datasize = sizeof(f32[3][3]);         break;
                case GD_ANIM_SCALE3S_POS3S_ROT3S:   datasize = sizeof(struct AnimMtxVec); break; // This function will convert the s16[9] array into a struct AnimMtxVec
                case GD_ANIM_MTX4x4:                datasize = sizeof(Mat4);              break;
                default:                            gd_exit();                            break; // unknown anim type for allocation       
            }
            allocSpace = gd_malloc_perm(curAnimSrc->count * datasize); // gd_alloc_perm
            if (allocSpace == NULL) gd_exit(); // can't allocate animation data
            if (curAnimSrc->type == GD_ANIM_SCALE3S_POS3S_ROT3S) {
                for ((dataIdx = 0); (dataIdx < curAnimSrc->count); (dataIdx++)) {
                    halfarr = &((s16(*)[9]) curAnimSrc->data)[dataIdx];
                    curMtxVec = &((struct AnimMtxVec *) allocSpace)[dataIdx];
                    vec3s_to_vec3f(tri.p0, halfarr[0]);
                    vec3f_mul_val(tri.p0, allocMtxScale);
                    vec3s_to_vec3f(tri.p1, halfarr[3]);
                    vec3f_mul_val(tri.p1, allocMtxScale);
                    vec3s_to_vec3f(tri.p2, halfarr[6]);
                    mtxf_identity(curMtxVec->matrix);
                    gd_rot_mat_about_vec3f(&curMtxVec->matrix, tri.p1);
                    vec3f_add(curMtxVec->matrix[3], tri.p2);
                    vec3f_copy(((struct AnimMtxVec *) allocSpace)[dataIdx].vec, tri.p0);
                }
                curAnimSrc->type = GD_ANIM_MTX4x4F_SCALE3F;
            } else {
                copy_bytes(curAnimSrc->data, allocSpace, curAnimSrc->count * datasize);
            }
        }
        animDst[i].type  = curAnimSrc->type;
        animDst[i].count = curAnimSrc->count;
        animDst[i].data  = allocSpace;
        curAnimSrc++; // next anim data struct
    }
    animgrp->firstMember->obj = (void *) animDataArr;
}

/**
 * Generate or create the various `ObjVertex`, `ObjFace`, and/or
 * `ObjMaterial` when groups of those structures are attached to
 * `shape`. This function is called when `d_set_nodegroup()`,
 * `d_set_planegroup()`, or `d_set_matgroup()` are called
 * when an `ObjShape` is the active dynamic object.
 *
 * @note Face/vertices need to be set before materials
 */
void chk_shapegen(struct ObjShape *shape) {
    struct ObjFace    *face;   // made face
    struct ObjVertex  *vtx;    // made gdvtx
    struct ObjVertex **vtxbuf; // heap storage for made gd vtx
    struct ObjGroup *shapeMtls;
    struct ObjGroup *shapeFaces;
    struct ObjGroup *shapeVtx;
    struct ObjGroup *madeFaces;
    struct ObjGroup *madeVtx;
    u32 i;
    struct GdVtxData *vtxdata;
    struct GdFaceData *facedata;
    struct GdObj *oldObjHead;
    shapeMtls  = shape->mtlGroup;
    shapeFaces = shape->faceGroup;
    shapeVtx   = shape->vtxGroup;
    if ((shapeVtx != NULL) && (shapeFaces != NULL)) {
        if (shapeVtx->linkType & 0x1) {
            // These ListNodes point to special, compressed data structures
            vtxdata  = (struct GdVtxData  *) shapeVtx->firstMember->obj;
            facedata = (struct GdFaceData *) shapeFaces->firstMember->obj;
            if (facedata->type != 1) gd_exit(); // unsupported poly type
            if (vtxdata->type  != 1) gd_exit(); // unsupported vertex type
            if (vtxdata->count >= VTX_BUF_SIZE) gd_exit(); // too many vertices
            vtxbuf     = gd_malloc_temp(VTX_BUF_SIZE * sizeof(struct ObjVertex *));
            oldObjHead = gGdObjectList;
            for ((i = 0); (i < vtxdata->count); (i++)) {
                vtx = gd_make_vertex(vtxdata->data[i]);
                vec3f_zero(vtx->normal);
                vtxbuf[i] = vtx;
            }
            madeVtx = make_group_of_type(OBJ_TYPE_VERTICES, oldObjHead);
            oldObjHead = gGdObjectList;
            for ((i = 0); (i < facedata->count); (i++)) {
                face = make_face_with_colour(gVec3fOne);
                face->mtlId = (s32) facedata->data[i][0];
                add_3_vtx_to_face(face, vtxbuf[facedata->data[i][1]],
                                        vtxbuf[facedata->data[i][2]],
                                        vtxbuf[facedata->data[i][3]]);
                vec3f_add(vtxbuf[facedata->data[i][1]]->normal, face->normal);
                vec3f_add(vtxbuf[facedata->data[i][2]]->normal, face->normal);
                vec3f_add(vtxbuf[facedata->data[i][3]]->normal, face->normal);
            }
            if (shape->flag & 0x10) { //! flag name
                for ((i = 0); (i < vtxdata->count); (i++)) {
                    vec3f_copy(vtxbuf[i]->normal, vtxbuf[i]->pos);
                    vec3f_normalize(vtxbuf[i]->normal);
                }
            } else {
                for ((i = 0); (i < vtxdata->count); (i++)) vec3f_normalize(vtxbuf[i]->normal);
            }
            gd_free(vtxbuf);
            madeFaces = make_group_of_type(OBJ_TYPE_FACES, oldObjHead);
            shape->faceGroup = madeFaces;
            shape->vtxGroup = madeVtx;
        }
    }
    if (shapeMtls != NULL) {
        if (shape->faceGroup) {
            map_face_materials(shape->faceGroup, shapeMtls);
        } else {
            gd_exit(); // please set face group before mats
        }
    }
}

/**
 * Set the "node group" of the current dynamic object to dynamic object `name`.
 * The node group depends on the type of the current dynamic object:
 * * the vertex group is set for `ObjShape`
 * * the joints/weight group is set for `ObjNet`
 * * data is set for `ObjAnimator`
 * * something is set for `ObjGadget`
 */
void d_set_nodegroup(DynObjName name) {
    struct DynObjInfo *info;
    if (sDynListCurObj == NULL) gd_exit();
    info = get_dynobj_info(name);
    if (info == NULL) gd_exit(); // fatal_printf("dSetNodeGroup(\"%s\"): Undefined group", DynNameAsStr(name));
    switch (sDynListCurObj->type) {
        case OBJ_TYPE_NETS:
            ((struct ObjNet *) sDynListCurObj)->nodeGrp   = (struct ObjGroup *) info->obj;
            ((struct ObjNet *) sDynListCurObj)->vertexGrp = (struct ObjGroup *) info->obj;
            break;
        case OBJ_TYPE_SHAPES:
            ((struct ObjShape *) sDynListCurObj)->vtxGroup = (struct ObjGroup *) info->obj;
            chk_shapegen((struct ObjShape *) sDynListCurObj);
            break;
        case OBJ_TYPE_ANIMATORS:
            ((struct ObjAnimator *) sDynListCurObj)->animdataGrp = (struct ObjGroup *) info->obj;
            alloc_animdata((struct ObjAnimator *) sDynListCurObj);
            break;
        default: gd_exit(); // fatal_printf("%s: Object '%s'(%x) does not support this function.", "dSetNodeGroup()", sDynListCurInfo->name, sDynListCurObj->type);
    }
}

/**
 * Set the material group of the current dynamic `ObjShape` to `name`.
 */
void d_set_matgroup(DynObjName name) {
    struct DynObjInfo *info;
    if (sDynListCurObj == NULL) gd_exit();
    info = get_dynobj_info(name);
    if (info == NULL) gd_exit(); // fatal_printf("dSetMatGroup(\"%s\"): Undefined group", DynNameAsStr(name));
    switch (sDynListCurObj->type) {
        case OBJ_TYPE_SHAPES:
            ((struct ObjShape *) sDynListCurObj)->mtlGroup = (struct ObjGroup *) info->obj;
            chk_shapegen((struct ObjShape *) sDynListCurObj);
            break;
        default: gd_exit(); // fatal_printf("%s: Object '%s'(%x) does not support this function.", "dSetMatGroup()", sDynListCurInfo->name, sDynListCurObj->type);
    }
}

/**
 * Set the current dynamic `ObjNet`'s skin group with the vertex group from
 * the dynamic `ObjShape` with `name`.
 */
void d_set_skinshape(DynObjName name) {
    struct DynObjInfo *info;
    if (sDynListCurObj == NULL) gd_exit();
    info = get_dynobj_info(name);
    if (info == NULL) gd_exit(); // fatal_printf("dSetSkinShape(\"%s\"): Undefined object", DynNameAsStr(name));
    if (sDynListCurObj->type == OBJ_TYPE_NETS) {
        ((struct ObjNet *) sDynListCurObj)->skinGrp = ((struct ObjShape *) info->obj)->vtxGroup;
    } else {
        gd_exit(); // fatal_printf("%s: Object '%s'(%x) does not support this function.", "dSetSkinShape()", sDynListCurInfo->name, sDynListCurObj->type);
    }
}

/**
 * In practice, this is used to set the faces of the current
 * active dynamic `ObjShape` to the dynamic group `name` of `ObjFace`s.
 * It also has interactions with `ObjNet`s, but there are no examples
 * of that usage in existing code.
 */
void d_set_planegroup(DynObjName name) {
    struct DynObjInfo *info;
    if (sDynListCurObj == NULL) gd_exit();
    info = get_dynobj_info(name);
    if (info == NULL) gd_exit(); // fatal_printf("dSetPlaneGroup(\"%s\"): Undefined group", DynNameAsStr(name));
    switch (sDynListCurObj->type) {
        case OBJ_TYPE_NETS:
            ((struct ObjNet   *) sDynListCurObj)->faceGroup = (struct ObjGroup *) info->obj;
            break;
        case OBJ_TYPE_SHAPES:
            ((struct ObjShape *) sDynListCurObj)->faceGroup = (struct ObjGroup *) info->obj;
            chk_shapegen((struct ObjShape *) sDynListCurObj);
            break;
        default: gd_exit(); // fatal_printf("%s: Object '%s'(%x) does not support this function.", "dSetPlaneGroup()", sDynListCurInfo->name, sDynListCurObj->type);
    }
}

/**
 * Set the shape pointer of the current active dynamic object to the
 * pointer pointed to by `shpPtrptr`.
 */
void d_set_shapeptrptr(struct ObjShape **shpPtrptr) {
    struct ObjShape *defaultptr = NULL;
    if (sDynListCurObj == NULL) gd_exit();
    if (shpPtrptr == NULL) shpPtrptr = &defaultptr;
    switch (sDynListCurObj->type) {
        case OBJ_TYPE_JOINTS:
            ((struct ObjJoint *) sDynListCurObj)->shapePtr  = *shpPtrptr;
            ((struct ObjJoint *) sDynListCurObj)->colourNum = COLOUR_BLACK;
            break;
        case OBJ_TYPE_NETS:      ((struct ObjNet      *) sDynListCurObj)->shapePtr = *shpPtrptr; break;
        case OBJ_TYPE_PARTICLES: ((struct ObjParticle *) sDynListCurObj)->shapePtr = *shpPtrptr; break;
        case OBJ_TYPE_LIGHTS:    ((struct ObjLight    *) sDynListCurObj)->shapePtr = *shpPtrptr; break;
        default: gd_exit(); // fatal_printf("%s: Object '%s'(%x) does not support this function.", "dSetShapePtrPtr()", sDynListCurInfo->name, sDynListCurObj->type);
    }
}

/**
 * Set the shape pointer of the current active dynamic object to dynamic
 * `ObjShape` `name`.
 */
void d_set_shapeptr(DynObjName name) {
    struct DynObjInfo *info;
    if (name == NULL) return;
    info = get_dynobj_info(name);
    if (info == NULL) gd_exit(); // fatal_printf("dSetShapePtr(\"%s\"): Undefined object", DynNameAsStr(name));
    switch (sDynListCurObj->type) {
        case OBJ_TYPE_JOINTS:
            ((struct ObjJoint *) sDynListCurObj)->shapePtr  = (struct ObjShape *) info->obj;
            ((struct ObjJoint *) sDynListCurObj)->colourNum = COLOUR_BLACK;
            break;
        case OBJ_TYPE_NETS:      ((struct ObjNet      *) sDynListCurObj)->shapePtr = (struct ObjShape *) info->obj; break;
        case OBJ_TYPE_PARTICLES: ((struct ObjParticle *) sDynListCurObj)->shapePtr = (struct ObjShape *) info->obj; break;
        default: gd_exit(); // fatal_printf("%s: Object '%s'(%x) does not support this function.", "dSetShapePtr()", sDynListCurInfo->name, sDynListCurObj->type);
    }
}

/**
 * Set the current active dynamic object to object `name`.
 */
struct GdObj *d_use_obj(DynObjName name) {
    struct DynObjInfo *info = get_dynobj_info(name);
    if (info == NULL) gd_exit(); // fatal_printf("dUseObj(\"%s\"): Undefined object", DynNameAsStr(name));
    sDynListCurObj  = info->obj;
    sDynListCurInfo = info;
    return info->obj;
}

/**
 * Set the current active dynamic object to `obj`. This object can
 * any type of `GdObj`, not just an object created through the
 * dynmaic object system.
 */
void set_cur_dynobj(struct GdObj *obj) {
    sDynListCurObj = obj;
    sDynListCurInfo = &sNullDynObjInfo;
}

/**
 * Start a dynamic `ObjGroup` identified with `name`.
 */
void d_start_group(DynObjName name) {
    d_makeobj(D_GROUP, name);
}

/**
 * Add all dynamic objects created between the start of dynamic `ObjGroup` `name`
 * and this call.
 */
void d_end_group(DynObjName name) {
    struct DynObjInfo *info = get_dynobj_info(name);
    struct ObjGroup *dynGrp;
    s32 i;
    if (info == NULL) gd_exit(); // fatal_printf("dEndGroup(\"%s\"): Undefined group", DynNameAsStr(name));
    dynGrp = (struct ObjGroup *) info->obj;
    for ((i = (info->num + 1)); (i < sLoadedDynObjs); (i++)) if (sGdDynObjList[i].obj->type != OBJ_TYPE_GROUPS) addto_group(dynGrp, sGdDynObjList[i].obj);
}

/**
 * Set if `DynObjName` should be treated as integer values,
 * or as `char *` string pointers.
 *
 * @param isIntBool `TRUE` to interpret ids as integers
 */
void d_use_integer_names(Bool32 isIntBool) {
    sUseIntegerNames = isIntBool;
}

/**
 * Set the initial position of the current dynamic object
 * to `(x, y, z)`.
 */
void d_set_init_pos(Vec3f pos) {
    struct GdObj *dynobj = sDynListCurObj;
    if (sDynListCurObj == NULL) gd_exit();
    switch (sDynListCurObj->type) {
        case OBJ_TYPE_JOINTS:
            vec3f_copy(((struct ObjJoint *) dynobj)->worldPos, pos);
            vec3f_copy(((struct ObjJoint *) dynobj)->relPos,   pos);
            vec3f_copy(((struct ObjJoint *) dynobj)->initPos,  pos);
            break;
        case OBJ_TYPE_NETS:
            vec3f_copy(((struct ObjNet *) dynobj)->worldPos, pos);
            vec3f_copy(((struct ObjNet *) dynobj)->initPos,  pos);
            break;
        case OBJ_TYPE_PARTICLES: vec3f_copy(((struct ObjParticle *) dynobj)->pos,      pos); break;
        case OBJ_TYPE_CAMERAS:   vec3f_copy(((struct ObjCamera   *) dynobj)->worldPos, pos); break;
        case OBJ_TYPE_VERTICES:
            d_set_rel_pos(pos[0], pos[1], pos[2]);
            vec3f_copy(((struct ObjVertex *) dynobj)->initPos, pos);
            break;
        default: gd_exit(); // fatal_printf("%s: Object '%s'(%x) does not support this function.", "dSetInitPos()", sDynListCurInfo->name, sDynListCurObj->type);
    }
}

/**
 * Set the velocity of the current active dynamic object. The
 * values of the input `Vec3f` are copied into the object.
 */
UNUSED void d_set_velocity(Vec3f vel) {
    struct GdObj *dynobj = sDynListCurObj;
    if (sDynListCurObj == NULL) gd_exit();
    switch (sDynListCurObj->type) {
        case OBJ_TYPE_JOINTS: vec3f_copy(((struct ObjJoint *) dynobj)->velocity, vel); break;
        case OBJ_TYPE_NETS:   vec3f_copy(((struct ObjNet   *) dynobj)->velocity, vel); break;
        default: gd_exit(); // fatal_printf("%s: Object '%s'(%x) does not support this function.", "dSetVelocity()", sDynListCurInfo->name, sDynListCurObj->type);
    }
}

/**
 * Read the velocity value of the current dynamic object into `dst`
 *
 * @param[out] dst values are copied to this `Vec3f`
 */
UNUSED void d_get_velocity(Vec3f dst) {
    struct GdObj *dynobj = sDynListCurObj;
    if (sDynListCurObj == NULL) gd_exit();
    switch (sDynListCurObj->type) {
        case OBJ_TYPE_JOINTS: vec3f_copy(dst, ((struct ObjJoint *) dynobj)->velocity); break;
        case OBJ_TYPE_NETS:   vec3f_copy(dst, ((struct ObjNet   *) dynobj)->velocity); break;
        default: vec3f_zero(dst); break;
    }
}

/**
 * Get the initial position of the current dynamic object and
 * store in `dst`.
 */
void d_get_init_pos(Vec3f dst) {
    struct GdObj *dynobj = sDynListCurObj;
    if (sDynListCurObj == NULL) gd_exit();
    switch (sDynListCurObj->type) {
        case OBJ_TYPE_JOINTS:   vec3f_copy(dst, ((struct ObjJoint  *) dynobj)->initPos); break;
        case OBJ_TYPE_NETS:     vec3f_copy(dst, ((struct ObjNet    *) dynobj)->initPos); break;
        case OBJ_TYPE_VERTICES: vec3f_copy(dst, ((struct ObjVertex *) dynobj)->initPos); break;
        default: gd_exit(); // fatal_printf("%s: Object '%s'(%x) does not support this function.", "dGetInitPos()", sDynListCurInfo->name, sDynListCurObj->type);
    }
}

/**
 * Get the initial rotation of the current dynamic object and
 * store in `dst`.
 */
void d_get_init_rot(Vec3f dst) {
    struct GdObj *dynobj = sDynListCurObj;
    if (sDynListCurObj == NULL) gd_exit();
    switch (sDynListCurObj->type) {
        case OBJ_TYPE_JOINTS: vec3f_copy(dst, ((struct ObjJoint *) dynobj)->initRotation); break;
        case OBJ_TYPE_NETS:   vec3f_copy(dst, ((struct ObjNet   *) dynobj)->initRotation); break;
        case OBJ_TYPE_LIGHTS: vec3f_zero(dst                                            ); break;
        default: gd_exit(); // fatal_printf("%s: Object '%s'(%x) does not support this function.", "dGetInitRot()", sDynListCurInfo->name, sDynListCurObj->type);
    }
}

/**
 * Set the position of the current dynamic object.
 *
 * @note This function automatically adjusts the three zoom levels
 *       for an `ObjCamera`.
 */
//! Vec3f pos
void d_set_rel_pos(f32 x, f32 y, f32 z) {
    struct GdObj *dynobj = sDynListCurObj;
    if (sDynListCurObj == NULL) gd_exit();
    switch (sDynListCurObj->type) {
        case OBJ_TYPE_JOINTS:  vec3f_set(((struct ObjJoint  *) dynobj)->relPos, x, y, z); break;
        case OBJ_TYPE_CAMERAS:
            vec3f_set(((struct ObjCamera *) dynobj)->relPos,            x,          y,          z        );
            vec3f_set(((struct ObjCamera *) dynobj)->zoomPositions[0], (x       ), (y       ), (z       ));
            vec3f_set(((struct ObjCamera *) dynobj)->zoomPositions[1], (x * 1.5f), (y * 1.5f), (z * 1.5f));
            vec3f_set(((struct ObjCamera *) dynobj)->zoomPositions[2], (x * 2.0f), (y * 2.0f), (z * 2.0f));
            ((struct ObjCamera *) dynobj)->maxZoomLevel = 2;
            break;
        case OBJ_TYPE_VERTICES:  vec3f_set(((struct ObjVertex   *) dynobj)->pos, x, y, z); break;
        case OBJ_TYPE_PARTICLES: vec3f_set(((struct ObjParticle *) dynobj)->pos, x, y, z); break;
        case OBJ_TYPE_NETS:                                                                break;
        default: gd_exit(); // fatal_printf("%s: Object '%s'(%x) does not support this function.", "dSetRelPos()", sDynListCurInfo->name, sDynListCurObj->type);
    }
}

/**
 * Offset the current position of the current dynamic object.
 */
UNUSED void d_addto_rel_pos(Vec3f src) {
    struct GdObj *dynobj = sDynListCurObj;
    if (sDynListCurObj == NULL) gd_exit();
    switch (sDynListCurObj->type) {
        case OBJ_TYPE_VERTICES:  vec3f_add(((struct ObjVertex   *) dynobj)->pos,    src); break;
        case OBJ_TYPE_JOINTS:    vec3f_add(((struct ObjJoint    *) dynobj)->relPos, src); break;
        case OBJ_TYPE_PARTICLES: vec3f_add(((struct ObjParticle *) dynobj)->pos,    src); break;
        default: gd_exit(); // fatal_printf("%s: Object '%s'(%x) does not support this function.", "dAddToRelPos()", sDynListCurInfo->name, sDynListCurObj->type);
    }
}

/**
 * Store the current dynamic object's position into `dst`.
 */
UNUSED void d_get_rel_pos(Vec3f dst) {
    if (sDynListCurObj == NULL) gd_exit();
    switch (sDynListCurObj->type) {
        case OBJ_TYPE_VERTICES:  vec3f_copy(dst, ((struct ObjVertex   *) sDynListCurObj)->pos   ); break;
        case OBJ_TYPE_JOINTS:    vec3f_copy(dst, ((struct ObjJoint    *) sDynListCurObj)->relPos); break;
        case OBJ_TYPE_CAMERAS:   vec3f_copy(dst, ((struct ObjCamera   *) sDynListCurObj)->relPos); break;
        case OBJ_TYPE_PARTICLES: vec3f_copy(dst, ((struct ObjParticle *) sDynListCurObj)->pos   ); break;
        default: gd_exit(); // fatal_printf("%s: Object '%s'(%x) does not support this function.", "dGetRelPos()", sDynListCurInfo->name, sDynListCurObj->type);
    }
}

/**
 * Return a pointer to the attached object group of the current
 * dynamic object.
 */
struct ObjGroup *d_get_att_objgroup(void) {
    if (sDynListCurObj == NULL) gd_exit();
    switch (sDynListCurObj->type) {
        case OBJ_TYPE_JOINTS: return ((struct ObjJoint *) sDynListCurObj)->attachedObjsGrp;
        case OBJ_TYPE_NETS:   return ((struct ObjNet   *) sDynListCurObj)->attachedObjsGrp;
        default: gd_exit(); // fatal_printf("%s: Object '%s'(%x) does not support this function.", "dGetAttObjGroup()", sDynListCurInfo->name, sDynListCurObj->type);
    } // No null return due to `fatal_printf()` being a non-returning function?
}

/**
 * Return a pointer to the object that the current dynamic object is attached to.
 */
struct GdObj *d_get_att_to_obj(void) {
    if (sDynListCurObj == NULL) gd_exit();
    switch (sDynListCurObj->type) {
        case OBJ_TYPE_JOINTS: return ((struct ObjJoint *) sDynListCurObj)->attachedToObj;
        case OBJ_TYPE_NETS:   return ((struct ObjNet   *) sDynListCurObj)->attachedToObj;
        default: gd_exit(); // fatal_printf("%s: Object '%s'(%x) does not support this function.", "dGetAttToObj()", sDynListCurInfo->name, sDynListCurObj->type);
    } // No null return due to `fatal_printf()` being a non-returning function?
}

/**
 * Store the current dynamic object's scale into `dst`.
 */
void d_get_scale(Vec3f dst) {
    struct GdObj *dynobj;
    if (sDynListCurObj == NULL) gd_exit();
    dynobj = sDynListCurObj;
    switch (sDynListCurObj->type) {
        case OBJ_TYPE_JOINTS: vec3f_copy(dst, ((struct ObjJoint *) dynobj)->scale); break;
        case OBJ_TYPE_NETS:   vec3f_copy(dst, ((struct ObjNet   *) dynobj)->scale); break;
        case OBJ_TYPE_LIGHTS: vec3f_copy(dst, gVec3fOne                          ); break;
        default: gd_exit(); // fatal_printf("%s: Object '%s'(%x) does not support this function.", "dGetScale()", sDynListCurInfo->name, sDynListCurObj->type);
    }
}

/**
 * Set the offset of the attached object on the current dynamic object.
 */
void d_set_att_offset(Vec3f off) {
    struct GdObj *dynobj;
    if (sDynListCurObj == NULL) gd_exit();
    dynobj = sDynListCurObj;
    switch (sDynListCurObj->type) {
        case OBJ_TYPE_JOINTS:
            vec3f_copy(((struct ObjJoint *) dynobj)->attachOffset, off);
            vec3f_copy(((struct ObjJoint *) dynobj)->initPos,      off);
            break;
        case OBJ_TYPE_NETS:
            vec3f_copy(((struct ObjNet   *) dynobj)->attachOffset, off);
            vec3f_copy(((struct ObjNet   *) dynobj)->initPos,      off);
            break;
        case OBJ_TYPE_PARTICLES: break;
        default: gd_exit(); // fatal_printf("%s: Object '%s'(%x) does not support this function.", "dSetAttOffset()", sDynListCurInfo->name, sDynListCurObj->type);
    }
}

/**
 * Set the offset of the attached object on the current dynamic object.
 */
void d_vec3f_set_att_offset(Vec3f off) {
    struct GdObj *dynobj;
    if (sDynListCurObj == NULL) gd_exit();
    dynobj = sDynListCurObj;
    switch (sDynListCurObj->type) {
        case OBJ_TYPE_JOINTS:
            vec3f_copy(((struct ObjJoint *) dynobj)->attachOffset, off);
            vec3f_copy(((struct ObjJoint *) dynobj)->initPos,      off);
            break;
        case OBJ_TYPE_NETS:
            vec3f_copy(((struct ObjNet   *) dynobj)->attachOffset, off);
            vec3f_copy(((struct ObjNet   *) dynobj)->initPos,      off);
            break;
        case OBJ_TYPE_PARTICLES: break;
        default: gd_exit(); // fatal_printf("%s: Object '%s'(%x) does not support this function.", "dSetAttOffset()", sDynListCurInfo->name, sDynListCurObj->type);
    }
}


/**
 * Set the world position of the current dynamic object.
 *
 * @note Sets the upper left coordinates of an `ObjView`
 */
//! Vec3f pos
void d_set_world_pos(f32 x, f32 y, f32 z) {
    if (sDynListCurObj == NULL) gd_exit();
    switch (sDynListCurObj->type) {
        case OBJ_TYPE_CAMERAS:  vec3f_set(((struct ObjCamera *) sDynListCurObj)->worldPos,  x, y, z); break;
        case OBJ_TYPE_JOINTS:   vec3f_set(((struct ObjJoint  *) sDynListCurObj)->worldPos,  x, y, z); break;
        case OBJ_TYPE_NETS:     vec3f_set(((struct ObjNet    *) sDynListCurObj)->worldPos,  x, y, z); break;
        case OBJ_TYPE_VIEWS:    vec3f_set(((struct ObjView   *) sDynListCurObj)->upperLeft, x, y, z); break;
        case OBJ_TYPE_VERTICES: vec3f_set(((struct ObjVertex *) sDynListCurObj)->pos,       x, y, z); break;
        default: gd_exit(); // fatal_printf("%s: Object '%s'(%x) does not support this function.", "dSetWorldPos()", sDynListCurInfo->name, sDynListCurObj->type);
    }
}

/**
 * Copy the world position of the current dynamic object into `dst`.
 */
UNUSED void d_get_world_pos(Vec3f dst) {
    if (sDynListCurObj == NULL) gd_exit();
    switch (sDynListCurObj->type) {
        case OBJ_TYPE_VERTICES:  vec3f_copy(dst, ((struct ObjVertex   *) sDynListCurObj)->pos     ); break;
        case OBJ_TYPE_JOINTS:    vec3f_copy(dst, ((struct ObjJoint    *) sDynListCurObj)->worldPos); break;
        case OBJ_TYPE_NETS:      vec3f_copy(dst, ((struct ObjNet      *) sDynListCurObj)->worldPos); break;
        case OBJ_TYPE_PARTICLES: vec3f_copy(dst, ((struct ObjParticle *) sDynListCurObj)->pos     ); break;
        case OBJ_TYPE_CAMERAS:   vec3f_copy(dst, ((struct ObjCamera   *) sDynListCurObj)->worldPos); break;
        case OBJ_TYPE_SHAPES:    vec3f_zero(dst                                                   ); break;
        case OBJ_TYPE_LIGHTS:    vec3f_copy(dst, ((struct ObjLight    *) sDynListCurObj)->position); break;
        default: gd_exit(); // fatal_printf("%s: Object '%s'(%x) does not support this function.", "dGetWorldPos()", sDynListCurInfo->name, sDynListCurObj->type);
    }
}

/**
 * Copy the world position of the current dynamic object into `dst`.
 */
void d_vec3f_get_world_pos(Vec3f dst) {
    if (sDynListCurObj == NULL) gd_exit();
    switch (sDynListCurObj->type) {
        case OBJ_TYPE_VERTICES:  vec3f_copy(dst, ((struct ObjVertex   *) sDynListCurObj)->pos     ); break;
        case OBJ_TYPE_JOINTS:    vec3f_copy(dst, ((struct ObjJoint    *) sDynListCurObj)->worldPos); break;
        case OBJ_TYPE_NETS:      vec3f_copy(dst, ((struct ObjNet      *) sDynListCurObj)->worldPos); break;
        case OBJ_TYPE_PARTICLES: vec3f_copy(dst, ((struct ObjParticle *) sDynListCurObj)->pos     ); break;
        case OBJ_TYPE_CAMERAS:   vec3f_copy(dst, ((struct ObjCamera   *) sDynListCurObj)->worldPos); break;
        case OBJ_TYPE_SHAPES:    vec3f_zero(dst                                                   ); break;
        case OBJ_TYPE_LIGHTS:    vec3f_copy(dst, ((struct ObjLight    *) sDynListCurObj)->position); break;
        default: gd_exit(); // fatal_printf("%s: Object '%s'(%x) does not support this function.", "dGetWorldPos()", sDynListCurInfo->name, sDynListCurObj->type);
    }
}

/**
 * Scale the current dynamic object by factor `(x, y, z)`.
 *
 * @note Sets the lower right coordinates of an `ObjView`
 */
//! Vec3f scale
void d_set_scale(f32 x, f32 y, f32 z) {
    struct GdObj *initDynobj;
    if (sDynListCurObj == NULL) gd_exit();
    initDynobj = sDynListCurObj;
    d_stash_dynobj();
    switch (sDynListCurObj->type) {
        case OBJ_TYPE_JOINTS: vec3f_set(((struct ObjJoint *) initDynobj)->scale,      x, y, z); break;
        case OBJ_TYPE_NETS:   vec3f_set(((struct ObjNet   *) initDynobj)->scale,      x, y, z); break;
        case OBJ_TYPE_VIEWS:  vec3f_set(((struct ObjView  *) initDynobj)->lowerRight, x, y, z); break;
        case OBJ_TYPE_PARTICLES: break;
        case OBJ_TYPE_LIGHTS:    break;
        default: gd_exit(); // fatal_printf("%s: Object '%s'(%x) does not support this function.", "dSetScale()", sDynListCurInfo->name, sDynListCurObj->type);
    }
    d_unstash_dynobj();
}

/**
 * Set the rotation value of the current active dynamic object.
 */
//! Vec3f rotation
void d_set_rotation(f32 x, f32 y, f32 z) {
    struct GdObj *dynobj;
    if (sDynListCurObj == NULL) gd_exit();
    dynobj = sDynListCurObj;
    switch (sDynListCurObj->type) {
        case OBJ_TYPE_JOINTS: vec3f_set(((struct ObjJoint *) dynobj)->initRotation, x, y, z); break;
        case OBJ_TYPE_NETS:   vec3f_set(((struct ObjNet   *) dynobj)->initRotation, x, y, z); break;
        default: gd_exit(); // fatal_printf("%s: Object '%s'(%x) does not support this function.", "dSetRotation()", sDynListCurInfo->name, sDynListCurObj->type);
    }
}

/**
 * Link a variable pointer to the current active dynamic object.
 * In the final game, this is used to link arrays of raw vertex, face,
 * or animation data to `ObjGroup`s, or to link joints to `ObjAnimator`s.
 */
void d_link_with_ptr(void *ptr) {
    struct GdObj *dynobj;
    struct ListNode *link;
    if (sDynListCurObj == NULL) gd_exit();
    dynobj = sDynListCurObj;
    switch (sDynListCurObj->type) {
        case OBJ_TYPE_CAMERAS:
            ((struct ObjCamera *) dynobj)->dynObj = ptr;
            break;
        case OBJ_TYPE_GROUPS:
            link = make_link_to_obj(NULL, ptr);
            ((struct ObjGroup *) dynobj)->firstMember = link;
            break;
        case OBJ_TYPE_VIEWS:
            ((struct ObjView *) dynobj)->components = ptr;
            ((struct ObjView *) dynobj)->unk1C = setup_view_buffers(((struct ObjView *) dynobj)->namePtr, (struct ObjView *) dynobj);
            reset_nets_and_gadgets(((struct ObjView *) dynobj)->components);
            break;
        case OBJ_TYPE_FACES:
            if (((struct ObjFace *) dynobj)->vtxCount >= 4) gd_exit(); // too many points
            ((struct ObjFace *) dynobj)->vertices[((struct ObjFace *) dynobj)->vtxCount] = ptr;
            ((struct ObjFace *) dynobj)->vtxCount++;
            if (((struct ObjFace *) dynobj)->vtxCount >= 3) calc_face_normal((struct ObjFace *) dynobj);
            break;
        case OBJ_TYPE_ANIMATORS:
            if (((struct ObjAnimator *) dynobj)->animatedPartsGrp == NULL) ((struct ObjAnimator *) dynobj)->animatedPartsGrp = make_group(0);
            addto_group(((struct ObjAnimator *) dynobj)->animatedPartsGrp, ptr);
            break;
        default: gd_exit(); // fatal_printf("%s: Object '%s'(%x) does not support this function.", "dLinkWithPtr()", sDynListCurInfo->name, sDynListCurObj->type);
    }
}

/**
 * Link the dynamic object `name` to the current dynamic object by wrapping
 * `d_link_with_ptr()`.
 */
void d_link_with(DynObjName name) {
    struct DynObjInfo *info;
    struct DynObjInfo *origInfo = sDynListCurInfo;
    if (sDynListCurObj == NULL) gd_exit();
    if (name == NULL) return;
    info = get_dynobj_info(name);
    if (info == NULL) gd_exit(); // fatal_printf("dLinkWith(\"%s\"): Undefined object", DynNameAsStr(name));
    d_link_with_ptr(info->obj);
    set_cur_dynobj(origInfo->obj);
    sDynListCurInfo = origInfo;
}

/**
 * Set the object specific flags of the current dynamic object.
 */
void d_set_flags(s32 flags) {
    struct GdObj *dynobj;
    if (sDynListCurObj == NULL) gd_exit();
    dynobj = sDynListCurObj;
    switch (sDynListCurObj->type) {
        case OBJ_TYPE_JOINTS:    ((struct ObjJoint    *) dynobj)->flags |= flags; break;
        case OBJ_TYPE_NETS:      ((struct ObjNet      *) dynobj)->flags |= flags; break;
        case OBJ_TYPE_CAMERAS:   ((struct ObjCamera   *) dynobj)->flags |= flags; break;
        case OBJ_TYPE_VIEWS:     ((struct ObjView     *) dynobj)->flags |= flags; break;
        case OBJ_TYPE_SHAPES:    ((struct ObjShape    *) dynobj)->flag  |= flags; break; //? ->flags?
        case OBJ_TYPE_PARTICLES: ((struct ObjParticle *) dynobj)->flags |= flags; break;
        case OBJ_TYPE_LIGHTS:    ((struct ObjLight    *) dynobj)->flags |= flags; break;
        default: gd_exit(); // fatal_printf("%s: Object '%s'(%x) does not support this function.", "dSetFlags()", sDynListCurInfo->name, sDynListCurObj->type);
    }
}

/**
 * Set the generic drawing flags for the current dynamic object.
 */
void d_set_obj_draw_flag(enum ObjDrawingFlags flag) {
    if (sDynListCurObj == NULL) gd_exit();
    sDynListCurObj->drawFlags |= flag;
}

/**
 * Set an object specific type field for the current dynamic object.
 */
void d_set_type(s32 type) {
    struct GdObj *dynobj = sDynListCurObj;
    if (sDynListCurObj == NULL) gd_exit();
    switch (sDynListCurObj->type) {
        case OBJ_TYPE_NETS:      ((struct ObjNet      *) dynobj)->netType      = type; break;
        case OBJ_TYPE_GROUPS:    ((struct ObjGroup    *) dynobj)->debugPrint   = type; break;
        case OBJ_TYPE_JOINTS:    ((struct ObjJoint    *) dynobj)->type         = type; break;
        case OBJ_TYPE_PARTICLES: ((struct ObjParticle *) dynobj)->particleType = type; break;
        case OBJ_TYPE_MATERIALS: ((struct ObjMaterial *) dynobj)->type         = type; break;
        default: gd_exit(); // fatal_printf("%s: Object '%s'(%x) does not support this function.", "dSetType()", sDynListCurInfo->name, sDynListCurObj->type);
    }
}

/**
 * Set the specific object ID field for the current dynamic object.
 */
void d_set_id(s32 id) {
    struct GdObj *dynobj = sDynListCurObj;
    if (sDynListCurObj == NULL) gd_exit();
    switch (sDynListCurObj->type) {
        case OBJ_TYPE_MATERIALS: ((struct ObjMaterial *) dynobj)->id = id; break;
        case OBJ_TYPE_JOINTS:    ((struct ObjJoint    *) dynobj)->id = id; break;
        case OBJ_TYPE_VERTICES:  ((struct ObjVertex   *) dynobj)->id = id; break;
        case OBJ_TYPE_LIGHTS:    ((struct ObjLight    *) dynobj)->id = id; break;
        default: gd_exit(); // fatal_printf("%s: Object '%s'(%x) does not support this function.", "dSetID()", sDynListCurInfo->name, sDynListCurObj->type);
    }
}

/**
 * Set the ambient color of the current dynamic `ObjMaterial`.
 */
void d_set_ambient(ColorF r, ColorF g, ColorF b) {
    if (sDynListCurObj == NULL) gd_exit();
    switch (sDynListCurObj->type) {
        case OBJ_TYPE_MATERIALS: vec3f_set(((struct ObjMaterial *) sDynListCurObj)->Ka, r, g, b); break;
        default: gd_exit(); // fatal_printf("%s: Object '%s'(%x) does not support this function.", "dSetAmbient()", sDynListCurInfo->name, sDynListCurObj->type);
    }
}

/**
 * Set the diffuse color of the current dynamic `ObjMaterial` or `ObjLight`.
 */
//! ColorRGBf
void d_set_diffuse(ColorF r, ColorF g, ColorF b) {
    if (sDynListCurObj == NULL) gd_exit();
    switch (sDynListCurObj->type) {
        case OBJ_TYPE_MATERIALS: vec3f_set(((struct ObjMaterial *) sDynListCurObj)->Kd,      r, g, b); break;
        case OBJ_TYPE_LIGHTS:    vec3f_set(((struct ObjLight    *) sDynListCurObj)->diffuse, r, g, b); break;
        default: gd_exit(); // fatal_printf("%s: Object '%s'(%x) does not support this function.", "dSetDiffuse()", sDynListCurInfo->name, sDynListCurObj->type);
    }
}

/**
 * Copy the matrix from the current dynamic object into `dst`.
 */
void d_get_matrix(Mat4 dst) {
    struct GdObj *dynobj;
    if (sDynListCurObj == NULL) gd_exit();
    dynobj = sDynListCurObj;
    switch (sDynListCurObj->type) {
        case OBJ_TYPE_NETS:      mtxf_copy(dst, ((struct ObjNet    *) dynobj)->invMtx   ); break;
        case OBJ_TYPE_JOINTS:    mtxf_copy(dst, ((struct ObjJoint  *) dynobj)->invMtx   ); break;
        case OBJ_TYPE_CAMERAS:   mtxf_copy(dst, ((struct ObjCamera *) dynobj)->lookatMtx); break;
        case OBJ_TYPE_PARTICLES: mtxf_identity(                                      dst); break;
        case OBJ_TYPE_SHAPES:    mtxf_identity(                                      dst); break;
        default: gd_exit(); // fatal_printf("%s: Object '%s'(%x) does not support this function.", "dGetMatrix()", sDynListCurInfo->name, sDynListCurObj->type);
    }
}

/**
 * Set the matrix of the current dynamic object by copying `src` into the object.
 */
UNUSED void d_set_matrix(Mat4 src) {
    if (sDynListCurObj == NULL) gd_exit();
    switch (sDynListCurObj->type) {
        case OBJ_TYPE_NETS:    mtxf_copy(((struct ObjNet    *) sDynListCurObj)->invMtx, src); break;
        case OBJ_TYPE_JOINTS:  mtxf_copy(((struct ObjJoint  *) sDynListCurObj)->invMtx, src); break;
        case OBJ_TYPE_CAMERAS: mtxf_copy(((struct ObjCamera *) sDynListCurObj)->idMtx,  src); break;
        default: gd_exit(); // fatal_printf("%s: Object '%s'(%x) does not support this function.", "dSetMatrix()", sDynListCurInfo->name, sDynListCurObj->type);
    }
}

/**
 * Set the rotation matrix of the current dynamic object by copying
 * the input matrix `src`.
 */
UNUSED void d_set_rot_mtx(Mat4 src) {
    if (sDynListCurObj == NULL) gd_exit();
    switch (sDynListCurObj->type) {
        case OBJ_TYPE_JOINTS: mtxf_copy(((struct ObjJoint *) sDynListCurObj)->rotationMtx, src); break;
        case OBJ_TYPE_NETS:   mtxf_copy(((struct ObjNet   *) sDynListCurObj)->rotationMtx, src); break;
        default: gd_exit(); // fatal_printf("%s: Object '%s'(%x) does not support this function.", "dSetRMatrix()", sDynListCurInfo->name, sDynListCurObj->type);
    }
}

/**
 * Get a pointer to the current dynamic object's rotation matrix.
 */
Mat4 *d_get_rot_mtx_ptr(void) {
    if (sDynListCurObj == NULL) gd_exit();
    switch (sDynListCurObj->type) {
        case OBJ_TYPE_JOINTS: return &((struct ObjJoint *) sDynListCurObj)->rotationMtx;
        case OBJ_TYPE_NETS:   return &((struct ObjNet   *) sDynListCurObj)->rotationMtx;
        default: gd_exit(); // fatal_printf("%s: Object '%s'(%x) does not support this function.", "dGetRMatrixPtr()", sDynListCurInfo->name, sDynListCurObj->type);
    } // No null return due to `fatal_printf()` being a non-returning function?
}

/**
 * Copy `src` into the matrix of the current dynamic object.
 * TODO: What is an IMatrix?
 * Maybe Identity Matrix?
 */
void d_set_i_matrix(Mat4 *src) {
    struct GdObj *dynobj;
    if (sDynListCurObj == NULL) gd_exit();
    dynobj = sDynListCurObj;
    switch (sDynListCurObj->type) {
        case OBJ_TYPE_NETS:   mtxf_copy( ((struct ObjNet   *) dynobj)->idMtx,    (*src)   ); break;
        case OBJ_TYPE_JOINTS: mtxf_copy( ((struct ObjJoint *) dynobj)->idMtx,    (*src)   ); break;
        case OBJ_TYPE_LIGHTS: vec3f_copy(((struct ObjLight *) dynobj)->position, (*src)[3]); break;
        default: gd_exit(); // fatal_printf("%s: Object '%s'(%x) does not support this function.", "dSetIMatrix()", sDynListCurInfo->name, sDynListCurObj->type);
    }
}

/**
 * Get a pointer to the current dynamic object's matrix.
 */
Mat4 *d_get_matrix_ptr(void) {
    if (sDynListCurObj == NULL) gd_exit();
    switch (sDynListCurObj->type) {
        case OBJ_TYPE_NETS:    return &((struct ObjNet    *) sDynListCurObj)->invMtx; break;
        case OBJ_TYPE_CAMERAS: return &((struct ObjCamera *) sDynListCurObj)->idMtx;  break;
        case OBJ_TYPE_JOINTS:  return &((struct ObjJoint  *) sDynListCurObj)->invMtx; break;
        default: gd_exit(); // fatal_printf("%s: Object '%s'(%x) does not support this function.", "dGetMatrixPtr()", sDynListCurInfo->name, sDynListCurObj->type);
    } // No null return due to `fatal_printf()` being a non-returning function?
}

/**
 * Get a pointer to the current dynamic object's matrix.
 * TODO: What is an IMatrix?
 */
Mat4 *d_get_i_mtx_ptr(void) {
    struct GdObj *dynobj;
    if (sDynListCurObj == NULL) gd_exit();
    dynobj = sDynListCurObj;
    switch (sDynListCurObj->type) {
        case OBJ_TYPE_NETS:   return &((struct ObjNet   *) dynobj)->idMtx;  break;
        case OBJ_TYPE_JOINTS: return &((struct ObjJoint *) dynobj)->idMtx; break;
        default: gd_exit(); // fatal_printf("%s: Object '%s'(%x) does not support this function.", "dGetIMatrixPtr()", sDynListCurInfo->name, sDynListCurObj->type);
    } // No null return due to `fatal_printf()` being a non-returning function?
}

/**
 * Use the dynamic object system to calculate the distance between
 * two `GdObj`s. The objects don't have to be dynamic objects.
 */
f32 d_calc_world_dist_btwn(struct GdObj *obj1, struct GdObj *obj2) {
    Vec3f obj1pos, obj2pos, posdiff;
    set_cur_dynobj(obj1);
    d_vec3f_get_world_pos(obj1pos);
    set_cur_dynobj(obj2);
    d_vec3f_get_world_pos(obj2pos);
    vec3f_diff(posdiff, obj2pos, obj1pos);
    return vec3_mag(posdiff);
}

/**
 * Create a new weight for the vertex `vtxId` in the current dynamic `ObjJoint`.
 * The input weight value is out of 100.
 */
void d_set_skin_weight(s32 vtxId, f32 percentWeight) {
    if (sDynListCurObj == NULL) gd_exit();
    if (sDynListCurObj->type == OBJ_TYPE_JOINTS) {
        set_skin_weight((struct ObjJoint *) sDynListCurObj, vtxId, NULL, (percentWeight / 100.0f));
    } else {
        gd_exit(); // fatal_printf("%s: Object '%s'(%x) does not support this function.", "dSetSkinWeight()", sDynListCurInfo->name, sDynListCurObj->type);
    }
}
