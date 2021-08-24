#include <ultra64.h>
#include <stdarg.h>

#include "objects.h"

#include "draw_objects.h"
#include "dynlist_proc.h"
#include "gd_macros.h"
#include "gd_main.h"
#include "gd_math.h"
#include "joints.h"
#include "particles.h"
#include "renderer.h"
#include "sfx.h"
#include "skin.h"
#include "engine/math_util.h"

// bss
struct GdBoundingBox gSomeBoundingBox;
struct ObjCamera *sCurrentMoveCamera; // @ 801B9DB8
struct ObjView   *sCurrentMoveView;   // @ 801B9DBC
Mat4 D_801B9DC8;
struct ObjGroup  *sCurrentMoveGrp;    // @ 801B9E14
struct ObjCamera *gGdCameraList;      // @ 801B9E4C
struct ObjGroup  *gGdGroupList;       // @ 801B9E54
s32 gGdObjCount;                      // @ 801B9E58
s32 gGdGroupCount;                    // @ 801B9E5C
s32 gGdCameraCount;                   // @ 801B9E64
s32 sGdViewCount;                     // @ 801B9E68
struct ObjJoint *gGdJointList;        // @ 801B9E84
struct GdObj    *gGdObjectList;       // head of linked list containing every single GdObj that was created
struct ObjGroup *gGdViewsGroup;       // @ 801B9E90

/* @ 22A480 for 0x70 */
void reset_bounding_box(void) { /* Initialize Plane? */
    gSomeBoundingBox.minX =  10000000.0f;
    gSomeBoundingBox.minY =  10000000.0f;
    gSomeBoundingBox.minZ =  10000000.0f;

    gSomeBoundingBox.maxX = -10000000.0f;
    gSomeBoundingBox.maxY = -10000000.0f;
    gSomeBoundingBox.maxZ = -10000000.0f;
}

void add_obj_pos_to_bounding_box(struct GdObj *obj) {
    struct GdVec3f pos;
    set_cur_dynobj(obj);
    d_get_world_pos(&pos);
    if (pos.x < gSomeBoundingBox.minX) gSomeBoundingBox.minX = pos.x;
    if (pos.y < gSomeBoundingBox.minY) gSomeBoundingBox.minY = pos.y;
    if (pos.z < gSomeBoundingBox.minZ) gSomeBoundingBox.minZ = pos.z;
    if (pos.x > gSomeBoundingBox.maxX) gSomeBoundingBox.maxX = pos.x;
    if (pos.y > gSomeBoundingBox.maxY) gSomeBoundingBox.maxY = pos.y;
    if (pos.z > gSomeBoundingBox.maxZ) gSomeBoundingBox.maxZ = pos.z;
}

/**
 * Creates an object of the specified type
 */
struct GdObj *make_object(enum ObjTypeFlag objType) {
    struct GdObj *newObj;
    struct GdObj *objListOldHead;
    s32 objSize;
    s32 i;
    drawmethod_t objDrawFn;
    // const char *typeName;
    u8 *newObjBytes;
    s32 objPermanence = 0x10;
    switch (objType) {
        case OBJ_TYPE_JOINTS:    objSize = sizeof(struct ObjJoint   ); objDrawFn = (drawmethod_t) draw_nothing;                 break;
        case OBJ_TYPE_GROUPS:    objSize = sizeof(struct ObjGroup   ); objDrawFn = (drawmethod_t) draw_nothing;                 break;
        case OBJ_TYPE_PARTICLES: objSize = sizeof(struct ObjParticle); objDrawFn = (drawmethod_t) draw_particle;                break;
        case OBJ_TYPE_SHAPES:    objSize = sizeof(struct ObjShape   ); objDrawFn = (drawmethod_t) draw_nothing;                 break; // Shapes get drawn by their parent object instead of automatically.
        case OBJ_TYPE_NETS:      objSize = sizeof(struct ObjNet     ); objDrawFn = (drawmethod_t) draw_net;                     break;
        case OBJ_TYPE_VERTICES:  objSize = sizeof(struct ObjVertex  ); objDrawFn = (drawmethod_t) draw_nothing;                 break;
        case OBJ_TYPE_CAMERAS:   objSize = sizeof(struct ObjCamera  ); objDrawFn = (drawmethod_t) draw_nothing;                 break;
        case OBJ_TYPE_FACES:     objSize = sizeof(struct ObjFace    ); objDrawFn = (drawmethod_t) draw_face; objPermanence = 1; break;
        case OBJ_TYPE_MATERIALS: objSize = sizeof(struct ObjMaterial); objDrawFn = (drawmethod_t) draw_material;                break;
        case OBJ_TYPE_LIGHTS:    objSize = sizeof(struct ObjLight   ); objDrawFn = (drawmethod_t) draw_light;                   break;
        case OBJ_TYPE_WEIGHTS:   objSize = sizeof(struct ObjWeight  ); objDrawFn = (drawmethod_t) draw_nothing;                 break;
        case OBJ_TYPE_VIEWS:     objSize = sizeof(struct ObjView    ); objDrawFn = (drawmethod_t) draw_nothing;                 break;
        case OBJ_TYPE_ANIMATORS: objSize = sizeof(struct ObjAnimator); objDrawFn = (drawmethod_t) draw_nothing;                 break;
        default: gd_exit(); // Unkown object!
    }
    // typeName = get_obj_name_str(objType);
    // Allocate memory for the object
    // start_memtracker(typeName);
    newObj = gd_malloc(objSize, objPermanence);
    if (newObj == NULL) gd_exit(); // Cant allocate object [typeName] memory!
    // stop_memtracker(typeName);
    // Zero out the object
    newObjBytes = (u8 *) newObj;
    for (i = 0; i < objSize; i++) newObjBytes[i] = 0;
    // Add the new object to the beginning of gGdObjectList
    gGdObjCount++;
    objListOldHead = gGdObjectList;
    gGdObjectList = newObj;
    newObj->prev = NULL;
    if (objListOldHead != NULL) {
        newObj->next = objListOldHead;
        objListOldHead->prev = newObj;
    }
    // Fill in required fields
    newObj->index     = gGdObjCount;
    newObj->type      = objType;
    newObj->objDrawFn = objDrawFn;
    newObj->drawFlags = 0;
    return newObj;
}

/**
 * Creates a ListNode for the object. Adds the new node after `prevNode` if `prevNode` is not NULL.
 */
struct ListNode *make_link_to_obj(struct ListNode *prevNode, struct GdObj *obj) {
    struct ListNode *newNode;
    // Allocate link node
    newNode = gd_malloc_perm(sizeof(struct ListNode));
    if (newNode == NULL) gd_exit(); // Cant allocate link memory!
    // Append to `prevNode` if not NULL
    if (prevNode != NULL) prevNode->next = newNode;
    newNode->prev = prevNode;
    newNode->next = NULL;
    newNode->obj  = obj;
    return newNode;
}

/*
 * Creates a VtxLink for the vertex. Adds the new node after `prevNode` if `prevNode` is not NULL.
 */
struct VtxLink *make_vtx_link(struct VtxLink *prevNode, Vtx *data) {
    struct VtxLink *newNode;
    newNode = gd_malloc_perm(sizeof(struct VtxLink));
    if (newNode == NULL) gd_exit(); // Cant allocate link memory!
    // Append to `prevNode` if not NULL
    if (prevNode != NULL) prevNode->next = newNode;
    newNode->prev = prevNode;
    newNode->next = NULL;
    newNode->data = data;
    //! WTF? Not sure what this is supposed to check
    if (((uintptr_t)(newNode)) == 0x3F800000) gd_exit(); // fatal_printf("bad3\n");
    return newNode;
}

/* @ 22B6A0 for 0x21C; orig name: func_8017CED0 */
struct ObjCamera *make_camera(void) {
    struct ObjCamera *newCam;
    struct ObjCamera *oldCameraHead;
    newCam = (struct ObjCamera *) make_object(OBJ_TYPE_CAMERAS);
    gGdCameraCount++;
    newCam->id    = gGdCameraCount;
    oldCameraHead = gGdCameraList;
    gGdCameraList = newCam;
    if (oldCameraHead != NULL) {
        newCam->next        = oldCameraHead;
        oldCameraHead->prev = newCam;
    }
    newCam->flags = CAMERA_FLAG_16;
    newCam->unk30 = NULL;
    gd_set_identity_mat4(&newCam->unk64);
    gd_set_identity_mat4(&newCam->unkA8);
    newCam->unk180.x     = 1.0f;
    newCam->unk180.y     = 0.1f;
    newCam->unk180.z     = 1.0f;
    newCam->unk134.x     = 4.0f;
    newCam->unk134.y     = 4.0f;
    newCam->unk134.z     = 4.0f;
    newCam->unk178       = 0.0f;
    newCam->unk17C       = 0.25f;
    newCam->zoomLevel    = 0;
    newCam->maxZoomLevel = -1;
    newCam->unkA4        = 0.0f;
    newCam->lookAt.x     = newCam->lookAt.y   = newCam->lookAt.z   = 0.0f;
    newCam->worldPos.x   = newCam->worldPos.y = newCam->worldPos.z = 0.0f;

    return newCam;
}

/* @ 22B8BC for 0xA8; orig. name: func_8017D0EC */
struct ObjMaterial *make_material(void) {
    struct ObjMaterial *newMtl;
    newMtl = (struct ObjMaterial *) make_object(OBJ_TYPE_MATERIALS);
    // gd_strcpy(newMtl->name, "x");
    newMtl->id         = 0;
    newMtl->gddlNumber = 0;
    newMtl->type       = 16;
    return newMtl;
}

/* @ 22B964 for 0x114; orig name: func_8017D194 */
struct ObjLight *make_light(void) {
    struct ObjLight *newLight;
    newLight = (struct ObjLight *) make_object(OBJ_TYPE_LIGHTS);
    // gd_strcpy(newLight->name, "x");
    newLight->id      = 0;
    newLight->unk30   = 1.0f;
    newLight->unk4C   = 0;
    newLight->flags   = LIGHT_NEW_UNCOUNTED;
    newLight->unk98   = 0;
    newLight->unk40   = 0;
    newLight->unk68.x = newLight->unk68.y = newLight->unk68.z = 0;
    return newLight;
}

/* @ 22BA78 for 0x294; orig name: func_8017D2A8*/
struct ObjView *make_view(const char *name, s32 flags, s32 projectionType, s32 ulx, s32 uly, s32 lrx, s32 lry, struct ObjGroup *parts) {
    struct ObjView *newView = (struct ObjView *) make_object(OBJ_TYPE_VIEWS);
    if (gGdViewsGroup == NULL) gGdViewsGroup = make_group(0);
    addto_group(gGdViewsGroup, &newView->header);
    newView->flags = flags | VIEW_UPDATE | VIEW_LIGHT;
    newView->id = sGdViewCount++;
    if ((newView->components = parts) != NULL) reset_nets_and_gadgets(parts);
    newView->unk78           = 0;
    newView->projectionType  = projectionType;
    newView->clipping.x      =   30.0f;
    newView->clipping.y      = 5000.0f;
    newView->clipping.z      =   45.0f;
    newView->upperLeft.x     = (f32) ulx;
    newView->upperLeft.y     = (f32) uly;
    newView->lowerRight.x    = (f32) lrx;
    newView->lowerRight.y    = (f32) lry;
    newView->unk48           = 1.0f;
    newView->unk4C           = 1.0f;
    newView->colour.r        = newView->id * 0.1f;
    newView->colour.g        = 0.06f;
    newView->colour.b        = 1.0f;
    newView->proc            = NULL;
    newView->unk9C           = 0;
    if (name != NULL) newView->unk1C = setup_view_buffers(name, newView);
    newView->namePtr         = name;
    newView->lights          = NULL;
    return newView;
}

/* @ 22BD0C for 0x78; orig name: func_8017D53C */
struct ObjAnimator *make_animator(void) {
    struct ObjAnimator *newAnim = (struct ObjAnimator *) make_object(OBJ_TYPE_ANIMATORS);
    newAnim->unk24       = 1.0f;
    newAnim->frame       = 1.0f;
    newAnim->controlFunc = NULL;
    newAnim->state       = 0;
    return newAnim;
}

/* @ 22BD84 for 0x78; orig name: func_8017D5B4 */
struct ObjWeight *make_weight(s32 vtxId, struct ObjVertex *vtx /* always NULL */, f32 weight) {
    struct ObjWeight *newWeight = (struct ObjWeight *) make_object(OBJ_TYPE_WEIGHTS);
    newWeight->vtxId     = vtxId;
    newWeight->weightVal = weight;
    newWeight->vtx       = vtx;  // is always NULL here. This vtx field actually gets set in reset_weight_vtx.
    return newWeight;
}

/**
 * Makes a group, adding all objects from `fromObj` to `toObj` with type `type`
 * as members.
 */
struct ObjGroup *make_group_of_type(enum ObjTypeFlag type, struct GdObj *fromObj) {
    struct ObjGroup *newGroup;
    struct GdObj *curObj;
    newGroup = make_group(0);
    curObj   = fromObj;
    while (curObj != NULL) {
        if (curObj->type & type) addto_group(newGroup, curObj);
        if (curObj == NULL) break;
        curObj = curObj->prev;
    }
    return newGroup;
}

/* @ 22C094 for 0x210 */
struct ObjGroup *make_group(s32 count, ...) {
    va_list args;
    s32 i;
    struct GdObj *curObj;
    struct ObjGroup *newGroup;
    struct ObjGroup *oldGroupListHead;
    struct GdObj *vargObj;
    struct ListNode *curLink;
    newGroup              = (struct ObjGroup *) make_object(OBJ_TYPE_GROUPS);
    newGroup->id          = ++gGdGroupCount;
    newGroup->memberCount = 0;
    newGroup->firstMember = newGroup->lastMember = NULL;
    oldGroupListHead = gGdGroupList;
    gGdGroupList = newGroup;
    if (oldGroupListHead != NULL) {
        newGroup->next = oldGroupListHead;
        oldGroupListHead->prev = newGroup;
    }
    if (count == 0) return newGroup;
    va_start(args, count);
    curLink = NULL;
    for (i = 0; i < count; i++) {
        // get the next pointer in the struct.
        vargObj = va_arg(args, struct GdObj *);
        // one of our pointers was NULL. raise an error.
        if (vargObj == NULL) gd_exit(); // NULL group ptr
        curObj = vargObj;
        newGroup->memberTypes |= curObj->type;
        addto_group(newGroup, vargObj);
    }
    va_end(args);
    curLink = newGroup->firstMember;
    while (curLink != NULL) {
        curObj = curLink->obj;
        curLink = curLink->next;
    }
    return newGroup;
}

/**
 * Adds the object as a member of the group, placing it at the end of the group's list.
 */
void addto_group(struct ObjGroup *group, struct GdObj *obj) {
    // Add object to the end of group's member list
    if (group->firstMember == NULL) {
        group->firstMember = make_link_to_obj(NULL, obj);
        group->lastMember = group->firstMember;
    } else {
        group->lastMember = make_link_to_obj(group->lastMember, obj);
    }
    group->memberTypes |= obj->type;
    group->memberCount++;
}

/**
 * Adds the object as a member of the group, placing it at the beginning of the group's list.
 */
void addto_groupfirst(struct ObjGroup *group, struct GdObj *obj) {
    // Add object to the beginning of group's member list
    if (group->firstMember == NULL) {
        group->firstMember = make_link_to_obj(NULL, obj);
        group->lastMember = group->firstMember;
    } else {
        struct ListNode *newNode = make_link_to_obj(NULL, obj);
        group->firstMember->prev = newNode;
        newNode->next = group->firstMember;
        group->firstMember = newNode;
    }
    group->memberTypes |= obj->type;
    group->memberCount++;
}

/**
 * Returns TRUE if `obj` is a member of `group`, or FALSE otherwise
 */
Bool32 group_contains_obj(struct ObjGroup *group, struct GdObj *obj) { //! Bool32?
    struct ListNode *node = group->firstMember;
    while (node != NULL) {
        if (node->obj->index == obj->index) return TRUE;
        node = node->next;
    }
    return FALSE;
}

/**
 * Recursively calls `func` on all members of `group` whose type is in the
 * `types` bitmask.
 * Returns the number of objects this function was called on.
 */
s32 apply_to_obj_types_in_group(s32 types, applyproc_t func, struct ObjGroup *group) {
    struct ListNode *curLink;
    struct ListNode *nextLink;
    struct GdObj    *linkedObj;
    enum ObjTypeFlag linkedObjType;
    applyproc_t objFn;
    s32 fnAppliedCount;
    fnAppliedCount = 0;
    if (group == NULL) return fnAppliedCount;
    if (group->linkType & 0x1) return fnAppliedCount; // compressed data, not an Obj
    if (!((group->memberTypes & OBJ_TYPE_GROUPS) | (group->memberTypes & types))) return fnAppliedCount;
    objFn   = func;
    curLink = group->firstMember;
    while (curLink != NULL) {
        linkedObj     = curLink->obj;
        linkedObjType = linkedObj->type;
        nextLink      = curLink->next;
        if (linkedObjType == OBJ_TYPE_GROUPS) fnAppliedCount += apply_to_obj_types_in_group(types, func, (struct ObjGroup *) linkedObj);
        if (linkedObjType & types) {
            (*objFn)(linkedObj);
            fnAppliedCount++;
        }
        curLink = nextLink;
    }
    return fnAppliedCount;
}

/* @ 22D824 for 0x1BC */
s32 transform_child_objects_recursive(struct GdObj *obj, struct GdObj *parentObj) {
    struct ListNode *curLink;
    struct ObjGroup *curGroup;
    Mat4 *parentUnkMtx;
    Mat4 *iMtx;
    Mat4 *unkMtx;
    Mat4 *rotMtx;
    Mat4 *rotMtx2;
    struct GdVec3f scale;
    if (parentObj != NULL) {
        set_cur_dynobj(parentObj);
        parentUnkMtx =          d_get_matrix_ptr();
        rotMtx       = (Mat4 *) d_get_rot_mtx_ptr();
        set_cur_dynobj(obj);
        iMtx    =          d_get_i_mtx_ptr();
        rotMtx2 = (Mat4 *) d_get_rot_mtx_ptr();
        d_get_scale(&scale);
        unkMtx = d_get_matrix_ptr();
        gd_mult_mat4f(iMtx, parentUnkMtx, unkMtx);
        gd_mult_mat4f(iMtx, rotMtx, rotMtx2);
        gd_scale_mat4f_by_vec3f(rotMtx2, &scale);
    } else {
        set_cur_dynobj(obj);
        unkMtx =          d_get_matrix_ptr();
        iMtx   =          d_get_i_mtx_ptr();
        rotMtx = (Mat4 *) d_get_rot_mtx_ptr();
        d_get_scale(&scale);
        gd_set_identity_mat4(unkMtx);
        gd_copy_mat4f(iMtx, rotMtx);
        gd_scale_mat4f_by_vec3f(rotMtx, &scale);
    }
    // Recursively call this function on attached children
    set_cur_dynobj(obj);
    curGroup = d_get_att_objgroup();
    if (curGroup != NULL) {
        curLink = curGroup->firstMember;
        while (curLink != NULL) {
            transform_child_objects_recursive(curLink->obj, obj);
            curLink = curLink->next;
        }
    }
    return 0;
}

/**
 * Interpolates between animation transformations `t1` and `t2`, with `dt` as
 * the interpolation factor (between 0 and 1). Sets the current dynobj's matrix
 * as the result of the transformation.
 */
void interpolate_animation_transform(struct GdAnimTransform *t1, struct GdAnimTransform *t2, f32 dt) {
    Mat4 mtx;
    gd_set_identity_mat4(&mtx);
    if (dt != 0.0f) {
        struct GdAnimTransform transform;
        // interpolate rotation between t1 and t2
        transform.rotate.x = (t1->rotate.x + ((t2->rotate.x - t1->rotate.x) * dt));
        transform.rotate.y = (t1->rotate.y + ((t2->rotate.y - t1->rotate.y) * dt));
        transform.rotate.z = (t1->rotate.z + ((t2->rotate.z - t1->rotate.z) * dt));
        // interpolate position between t1 and t2
        transform.pos.x    = (t1->pos.x + ((t2->pos.x - t1->pos.x) * dt));
        transform.pos.y    = (t1->pos.y + ((t2->pos.y - t1->pos.y) * dt));
        transform.pos.z    = (t1->pos.z + ((t2->pos.z - t1->pos.z) * dt));
        // not going to interpolate scale?
        gd_scale_mat4f_by_vec3f(     &mtx, &t1->scale);
        gd_rot_mat_about_vec(        &mtx, &transform.rotate);
        gd_add_vec3f_to_mat4f_offset(&mtx, &transform.pos);
    } else {
        d_set_scale(t1->scale.x, t1->scale.y, t1->scale.z);
        gd_rot_mat_about_vec(        &mtx, &t1->rotate);
        gd_add_vec3f_to_mat4f_offset(&mtx, &t1->pos);
    }
    d_set_i_matrix(&mtx);
}

/* @ 22DD94 for 0x1060; orig name: func_8017F5C4 */
void move_animator(struct ObjAnimator *animObj) {
    struct AnimDataInfo *animData; // array?
    Mat4 *mtxArr;
    Mat4 localMtx;
    struct GdAnimTransform *triPtr;
    struct GdAnimTransform currTransform; // transformation for the current keyframe
    struct GdAnimTransform nextTransform; // transformation for the next keyframe
    s16(*animData9s16)[9];                // GdTriangleH[]?
    s16(*animData3s16)[3];                // MyVec3h[]?
    s16(*animData6s16)[6];                // GdPlaneH[]?
    s16(*animDataCam)[6];                 // camera GdPlaneH[]?
    s32 currKeyFrame;
    s32 nextKeyFrame;
    f32 dt;
    f32 scale = 0.1f;
    struct AnimMtxVec *sp28;
    register struct ListNode *link;
    struct GdObj *linkedObj;
    if (animObj->controlFunc != NULL) animObj->controlFunc(animObj);
    if (animObj->animatedPartsGrp == NULL) return;  // nothing to animate
    animData = (struct AnimDataInfo *) animObj->animdataGrp->firstMember->obj;
    if (animObj->attachedToObj != NULL) {
        animObj->frame = ((struct ObjAnimator *) animObj->attachedToObj)->frame / ((struct ObjAnimator *) animObj->attachedToObj)->unk24;
        animData += ((struct ObjAnimator *) animObj->attachedToObj)->animSeqNum;
    }
    if (animData->type == 0) return;
    if (animObj->frame > (f32) animData->count) {
        animObj->frame = 1.0f;
    } else if (animObj->frame < 0.0f) {
        animObj->frame = (f32) animData->count;
    }
    currKeyFrame = (s32) animObj->frame;
    dt           = animObj->frame - (f32) currKeyFrame;
    nextKeyFrame = currKeyFrame + 1;
    if (nextKeyFrame > animData->count) nextKeyFrame = 1;
    // convert frame numbers to zero-indexed
    currKeyFrame--;
    nextKeyFrame--;
    link = animObj->animatedPartsGrp->firstMember;
    while (link != NULL) {
        linkedObj = link->obj;
        set_cur_dynobj(linkedObj);
        switch (animData->type) {
            case GD_ANIM_MTX4x4: // data = Mat4* (f32[4][4])
                mtxArr = (Mat4 *) animData->data;
                /* This needs be be un-dereferenced pointer addition to make the registers match */
                d_set_i_matrix(mtxArr + (s32) animObj->frame);
                break;
            case GD_ANIM_ROT3S: // data = s16(*)[3] - rotation only
                animData3s16 = (s16(*)[3]) animData->data;
                // keep current object scale
                d_get_scale(&currTransform.scale);
                gd_vec3f_copy(&nextTransform.scale, &currTransform.scale);
                // keep current object position
                d_get_init_pos(&currTransform.pos);
                gd_vec3f_copy(&nextTransform.pos, &currTransform.pos);
                // use animation rotation
                currTransform.rotate.x = ((f32) animData3s16[currKeyFrame][0] * scale);
                currTransform.rotate.y = ((f32) animData3s16[currKeyFrame][1] * scale);
                currTransform.rotate.z = ((f32) animData3s16[currKeyFrame][2] * scale);
                nextTransform.rotate.x = ((f32) animData3s16[nextKeyFrame][0] * scale);
                nextTransform.rotate.y = ((f32) animData3s16[nextKeyFrame][1] * scale);
                nextTransform.rotate.z = ((f32) animData3s16[nextKeyFrame][2] * scale);
                interpolate_animation_transform(&currTransform, &nextTransform, dt);
                break;
            case GD_ANIM_POS3S: // data = s16(*)[3] - position only
                animData3s16 = (s16(*)[3]) animData->data;
                // keep current object scale
                d_get_scale(&currTransform.scale);
                gd_vec3f_copy(&nextTransform.scale, &currTransform.scale);
                // keep current object rotation
                d_get_init_rot(&currTransform.rotate);
                gd_vec3f_copy(&nextTransform.rotate, &currTransform.rotate);
                // use animation position
                currTransform.pos.x = (f32) animData3s16[currKeyFrame][0];
                currTransform.pos.y = (f32) animData3s16[currKeyFrame][1];
                currTransform.pos.z = (f32) animData3s16[currKeyFrame][2];
                nextTransform.pos.x = (f32) animData3s16[nextKeyFrame][0];
                nextTransform.pos.y = (f32) animData3s16[nextKeyFrame][1];
                nextTransform.pos.z = (f32) animData3s16[nextKeyFrame][2];
                interpolate_animation_transform(&currTransform, &nextTransform, dt);
                break;
            case GD_ANIM_ROT3S_POS3S: // data = s16(*)[6] - rotation and position
                animData6s16 = (s16(*)[6]) animData->data;
                // keep current object scale
                d_get_scale(&currTransform.scale);
                gd_vec3f_copy(&nextTransform.scale, &currTransform.scale);
                // use animation rotation
                currTransform.rotate.x = ((f32) animData6s16[currKeyFrame][0] * scale);
                currTransform.rotate.y = ((f32) animData6s16[currKeyFrame][1] * scale);
                currTransform.rotate.z = ((f32) animData6s16[currKeyFrame][2] * scale);
                nextTransform.rotate.x = ((f32) animData6s16[nextKeyFrame][0] * scale);
                nextTransform.rotate.y = ((f32) animData6s16[nextKeyFrame][1] * scale);
                nextTransform.rotate.z = ((f32) animData6s16[nextKeyFrame][2] * scale);
                // use animation position
                currTransform.pos.x    =  (f32) animData6s16[currKeyFrame][3];
                currTransform.pos.y    =  (f32) animData6s16[currKeyFrame][4];
                currTransform.pos.z    =  (f32) animData6s16[currKeyFrame][5];
                nextTransform.pos.x    =  (f32) animData6s16[nextKeyFrame][3];
                nextTransform.pos.y    =  (f32) animData6s16[nextKeyFrame][4];
                nextTransform.pos.z    =  (f32) animData6s16[nextKeyFrame][5];
                interpolate_animation_transform(&currTransform, &nextTransform, dt);
                break;
            case GD_ANIM_SCALE3S_POS3S_ROT3S: // data = s16(*)[9] - scale, position, and rotation
                animData9s16 = (s16(*)[9]) animData->data;
                currTransform.scale.x  = ((f32) animData9s16[currKeyFrame][0] * scale);
                currTransform.scale.y  = ((f32) animData9s16[currKeyFrame][1] * scale);
                currTransform.scale.z  = ((f32) animData9s16[currKeyFrame][2] * scale);
                currTransform.rotate.x = ((f32) animData9s16[currKeyFrame][3] * scale);
                currTransform.rotate.y = ((f32) animData9s16[currKeyFrame][4] * scale);
                currTransform.rotate.z = ((f32) animData9s16[currKeyFrame][5] * scale);
                currTransform.pos.x    =  (f32) animData9s16[currKeyFrame][6];
                currTransform.pos.y    =  (f32) animData9s16[currKeyFrame][7];
                currTransform.pos.z    =  (f32) animData9s16[currKeyFrame][8];
                nextTransform.scale.x  = ((f32) animData9s16[nextKeyFrame][0] * scale);
                nextTransform.scale.y  = ((f32) animData9s16[nextKeyFrame][1] * scale);
                nextTransform.scale.z  = ((f32) animData9s16[nextKeyFrame][2] * scale);
                nextTransform.rotate.x = ((f32) animData9s16[nextKeyFrame][3] * scale);
                nextTransform.rotate.y = ((f32) animData9s16[nextKeyFrame][4] * scale);
                nextTransform.rotate.z = ((f32) animData9s16[nextKeyFrame][5] * scale);
                nextTransform.pos.x    =  (f32) animData9s16[nextKeyFrame][6];
                nextTransform.pos.y    =  (f32) animData9s16[nextKeyFrame][7];
                nextTransform.pos.z    =  (f32) animData9s16[nextKeyFrame][8];
                interpolate_animation_transform(&currTransform, &nextTransform, dt);
                break;
            case GD_ANIM_CAMERA_EYE3S_LOOKAT3S: // s16(*)[6]?
                if (linkedObj->type == OBJ_TYPE_CAMERAS) {
                    animDataCam = animData->data;
                    // eye position
                    currTransform.pos.x = (f32) animDataCam[currKeyFrame][0];
                    currTransform.pos.y = (f32) animDataCam[currKeyFrame][1];
                    currTransform.pos.z = (f32) animDataCam[currKeyFrame][2];
                    // lookat position
                    nextTransform.pos.x = (f32) animDataCam[currKeyFrame][3];
                    nextTransform.pos.y = (f32) animDataCam[currKeyFrame][4];
                    nextTransform.pos.z = (f32) animDataCam[currKeyFrame][5];

                    ((struct ObjCamera *) linkedObj)->worldPos.x = currTransform.pos.x;
                    ((struct ObjCamera *) linkedObj)->worldPos.y = currTransform.pos.y;
                    ((struct ObjCamera *) linkedObj)->worldPos.z = currTransform.pos.z;
                    ((struct ObjCamera *) linkedObj)->lookAt.x   = nextTransform.pos.x;
                    ((struct ObjCamera *) linkedObj)->lookAt.y   = nextTransform.pos.y;
                    ((struct ObjCamera *) linkedObj)->lookAt.z   = nextTransform.pos.z;
                }
                break;
            case GD_ANIM_SCALE3F_ROT3F_POS3F: // scale, rotation, and position (as floats)
                triPtr = (struct GdAnimTransform *) animData->data;
                interpolate_animation_transform(&triPtr[currKeyFrame], &triPtr[nextKeyFrame], dt);
                break;
            case GD_ANIM_MTX4x4F_SCALE3F: // AnimMtxVec[]
                sp28 = &((struct AnimMtxVec *) animData->data)[currKeyFrame];
                d_set_i_matrix(&sp28->matrix);
                d_set_scale(sp28->vec.x, sp28->vec.y, sp28->vec.z);
                break;
            case GD_ANIM_SCALE3F_ROT3F_POS3F_2:  // similar to GD_ANIM_SCALE3F_ROT3F_POS3F, but no interpolation? what matrix does d_set_i_matrix set?
                triPtr = (struct GdAnimTransform *) animData->data;
                gd_set_identity_mat4(&localMtx);
                gd_scale_mat4f_by_vec3f(&localMtx, &triPtr->scale);
                gd_rot_mat_about_vec(&localMtx, &triPtr->rotate);
                gd_add_vec3f_to_mat4f_offset(&localMtx, &triPtr->pos);
                d_set_i_matrix(&localMtx);
                break;
            case GD_ANIM_STUB: //!?
                break;
            default:
                gd_exit(); // Unkown animation data type
        }
        link = link->next;
    }
}

/* @ 22EDF4 for 0x300; orig name: func_80180624 */
void drag_picked_object(struct GdObj *inputObj) {
    struct GdVec3f displacement;
    struct GdVec3f spC4;
    struct GdControl *ctrl;
    Mat4 sp80;
    Mat4 sp40;
    struct GdObj *obj;
    f32 dispMag;
    ctrl = &gGdCtrl;
    if (gViewUpdateCamera == NULL) return;
    dispMag = gd_vec3f_magnitude(&gViewUpdateCamera->unk40);
    dispMag /= 1000.0f; //! fast invsqrt?
    displacement.x = (((f32)   (ctrl->csrX - ctrl->dragStartX)) * dispMag);
    displacement.y = (((f32) - (ctrl->csrY - ctrl->dragStartY)) * dispMag);
    displacement.z = 0.0f;
    gd_inverse_mat4f(&gViewUpdateCamera->unkE8, &sp40);
    gd_mat4f_mult_vec3f(&displacement, &sp40);
    obj = inputObj;
    if ((inputObj->drawFlags & OBJ_PICKED) && gGdCtrl.dragging) {
        gd_play_sfx(GD_SFX_PINCH_FACE);
        // Note: this second sfx won't play, as it is "overwritten" by the first
        if (ABSI(ctrl->stickDeltaX) + ABSI(ctrl->stickDeltaY) >= 11) gd_play_sfx(GD_SFX_PINCH_FACE_2);
        switch (inputObj->type) {
            case OBJ_TYPE_JOINTS:
                ((struct ObjJoint *) obj)->mat128[3][0] += displacement.x;
                ((struct ObjJoint *) obj)->mat128[3][1] += displacement.y;
                ((struct ObjJoint *) obj)->mat128[3][2] += displacement.z;
                break;
            case OBJ_TYPE_NETS:
                gd_inverse_mat4f(&((struct ObjNet *) obj)->mat128, &sp80);
                spC4.x = displacement.x;
                spC4.y = displacement.y;
                spC4.z = displacement.z;
                gd_mat4f_mult_vec3f(&spC4, &sp80);
                ((struct ObjNet *) obj)->matE8[3][0] += displacement.x;
                ((struct ObjNet *) obj)->matE8[3][1] += displacement.y;
                ((struct ObjNet *) obj)->matE8[3][2] += displacement.z;
                break;
            case OBJ_TYPE_PARTICLES:
            default: break;
        }
    }
}

/* @ 22F0F4 for 0x50; orig name: func_80180924*/
void move_animators(struct ObjGroup *group) {
    apply_to_obj_types_in_group(OBJ_TYPE_ANIMATORS, (applyproc_t) move_animator, group);
}

/* @ 22F144 for 0x3C; orig name: func_80180974 */
void find_and_drag_picked_object(struct ObjGroup *group) {
    apply_to_obj_types_in_group(OBJ_TYPE_ALL, (applyproc_t) drag_picked_object, group);
}

/* @ 22F180 for 0x624; orig name: func_801809B0 */
void move_camera(struct ObjCamera *cam) {
    struct GdObj *spEC;
    struct GdVec3f spE0;
    struct GdVec3f spD4;
    struct GdVec3f spC8;
    struct GdVec3f spB0;
    Mat4 sp70;
    Mat4 *sp2C;
    struct GdControl *ctrl;
    ctrl = &gGdCtrl;
    if (!(cam->flags & CAMERA_FLAG_16)) return;
    spE0.x = spE0.y = spE0.z = 0.0f;
    spB0.x = spB0.y = spB0.z = 0.0f;
    if ((spEC = cam->unk30) != NULL) {
        set_cur_dynobj(spEC);
        d_get_world_pos(&spE0);
        d_get_matrix(&sp70);
        spC8.x = (sp70[2][0] - cam->unk58);
        spC8.z = (sp70[2][2] - cam->unk60);
        cam->unk58 += (spC8.x * cam->unk180.y);
        cam->unk60 += (spC8.z * cam->unk180.y);
        cam->unkA8[2][0] =  cam->unk58;
        cam->unkA8[2][1] = 0.0f;
        cam->unkA8[2][2] =  cam->unk60;
        cam->unkA8[0][0] =  cam->unkA8[2][2];
        cam->unkA8[0][1] = 0.0f;
        cam->unkA8[0][2] = -cam->unkA8[2][0];
        cam->unkA8[1][0] = 0.0f;
        cam->unkA8[1][1] = 1.0f;
        cam->unkA8[1][2] = 0.0f;
        //! setting the unkA8 matrix above is pointless, if we're just going to overwrite it with the identity matrix.
        gd_set_identity_mat4(&cam->unkA8);
    } else {
        gd_set_identity_mat4(&cam->unkA8);
    }
    sp2C = &cam->unk64;
    if ((cam->flags & CAMERA_FLAG_CONTROLLABLE) != 0) {
        if (ctrl->btnB && !ctrl->prevFrame->btnB) {  // new B press
            cam->zoomLevel++;
            if (cam->zoomLevel > cam->maxZoomLevel) cam->zoomLevel = 0;
            switch (cam->zoomLevel) {
                case 0: gd_play_sfx(GD_SFX_CAM_ZOOM_IN);  break;
                case 1: // fall through
                case 2: gd_play_sfx(GD_SFX_CAM_ZOOM_OUT); break;
            }
        }
        if (ctrl->cleft ) cam->unk128.y += cam->unk134.y;
        if (ctrl->cright) cam->unk128.y -= cam->unk134.y;
        if (ctrl->cup   ) cam->unk128.x += cam->unk134.x;
        if (ctrl->cdown ) cam->unk128.x -= cam->unk134.x;
        clamp_f32(&cam->unk128.x, -80.0f, 80.0f);
        gd_vec3f_copy(&cam->unk4C, &cam->zoomPositions[cam->zoomLevel]);
        gd_rot_2d_vec(  cam->unk128.x, &cam->unk4C.y, &cam->unk4C.z);
        gd_rot_2d_vec( -cam->unk128.y, &cam->unk4C.x, &cam->unk4C.z);
        cam->unk40.x += ((cam->unk4C.x - cam->unk40.x) * cam->unk17C);
        cam->unk40.y += ((cam->unk4C.y - cam->unk40.y) * cam->unk17C);
        cam->unk40.z += ((cam->unk4C.z - cam->unk40.z) * cam->unk17C);
    } else {
        gd_set_identity_mat4(sp2C);
    }
    gd_vec3f_copy(&spD4, &cam->unk40);
    spD4.x += spB0.x; // offset1
    spD4.y += spB0.y;
    spD4.z += spB0.z;
    gd_mult_mat4f(sp2C, &cam->unkA8, &cam->unkA8);
    gd_mat4f_mult_vec3f(&spD4, &cam->unkA8);
    gd_vec3f_copy(&cam->worldPos, &spD4);
    cam->worldPos.x += spE0.x; // offset2
    cam->worldPos.y += spE0.y;
    cam->worldPos.z += spE0.z;
}

/* @ 22F7A4 for 0x38; orig name: func_80180FD4 */
void move_cameras_in_grp(struct ObjGroup *group) {
    apply_to_obj_types_in_group(OBJ_TYPE_CAMERAS, (applyproc_t) move_camera, group);
}

/* @ 22FB80 for 0xAC; orig name: func_801813B0 */
void move_group_members(void) {
    s32 i;
    // move_lights_in_grp(sCurrentMoveGrp);
    move_particles_in_grp(sCurrentMoveGrp);
    move_animators(sCurrentMoveGrp);
    for ((i = 0); (i <= 0); (i++)) move_nets(sCurrentMoveGrp);
    move_cameras_in_grp(sCurrentMoveGrp);
}

/* @ 22FC2C for 0x98; orig name: func_8018145C */
void proc_view_movement(struct ObjView *view) {
    sCurrentMoveCamera   = view->activeCam;
    sCurrentMoveView     = view;
    if ((sCurrentMoveGrp = view->components) != NULL) move_group_members();
    if ((sCurrentMoveGrp = view->lights    ) != NULL) move_group_members();
}

/* @ 22FCC4 for 0x44; orig name: func_801814F4 */
void reset_nets_and_gadgets(struct ObjGroup *group) {
    func_80193848(group);
}

/* @ 22FD08 for 0x9C; orig name: func_80181538*/
void null_obj_lists(void) {
    gGdObjCount    = 0;
    gGdGroupCount  = 0;
    gGdCameraCount = 0;
    sGdViewCount   = 0;
    gGdCameraList  = NULL;
    gGdJointList   = NULL;
    gGdGroupList   = NULL;
    gGdObjectList  = NULL;
    gGdViewsGroup  = NULL;
    reset_net_count();
    reset_joint_counts();
}
