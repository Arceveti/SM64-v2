#include <PR/ultratypes.h>

#include "gd_math.h"
#include "objects.h"
#include "renderer.h"
#include "skin.h"
#include "skin_movement.h"

//! combine with skin.c?

/* bss */
struct ObjWeight *sResetCurWeight;
static Mat4 D_801B9EA8; // TODO: rename to sHead2Mtx?

s32 sResetWeightVtxNum;

/* @ 22FF30 for 0xDC */
/* called with ObjNext->unk1A8 (variable obj ptr?) ->unk20 or ->unk24 ptr*/
// TODO: figure out the proper object type for a0
void scale_verts(struct ObjGroup *group) {
    register f32 scaleFac;
    register struct ListNode *link;
    struct ObjVertex *vtx;
    for ((link = group->firstMember); (link != NULL); (link = link->next)) {
        vtx = (struct ObjVertex *) link->obj;
        if ((scaleFac = vtx->scaleFactor) != 0.0f) {
            vtx->pos[0] = (vtx->initPos[0] * scaleFac);
            vtx->pos[1] = (vtx->initPos[1] * scaleFac);
            vtx->pos[2] = (vtx->initPos[2] * scaleFac);
        } else {
            vec3f_zero(vtx->pos);
        }
    }
}

/* @ 230064 for 0x13C*/
void func_80181894(struct ObjJoint *joint) {
    register struct ObjGroup *weightGroup; // baseGroup? weights Only?
    Vec3f stackVec;
    register struct ObjWeight *curWeight;
    register struct ObjVertex *connectedVtx;
    register struct ListNode *link;
    register f32 scaleFactor;
    struct GdObj *linkedObj;
    weightGroup = joint->weightGrp;
    if (weightGroup != NULL) {
        for ((link = weightGroup->firstMember); (link != NULL); (link = link->next)) {
            linkedObj                = link->obj;
            curWeight                = (struct ObjWeight *) linkedObj;
            if (curWeight->weightVal > 0.0f) {
                vec3f_copy(stackVec, curWeight->vec20);
                gd_rotate_and_translate_vec3f(stackVec, &joint->invMtx);
                connectedVtx         = curWeight->vtx;
                scaleFactor          = curWeight->weightVal;
                connectedVtx->pos[0] += (stackVec[0] * scaleFactor);
                connectedVtx->pos[1] += (stackVec[1] * scaleFactor);
                connectedVtx->pos[2] += (stackVec[2] * scaleFactor);
            }
        }
    }
}

/* @ 2301A0 for 0x110 */
void reset_weight_vtx(struct ObjVertex *vtx) {
    Vec3f localVec;
    if (sResetWeightVtxNum++ == sResetCurWeight->vtxId) {  // found matching vertex
        sResetCurWeight->vtx     = vtx;
        vec3f_copy(localVec, vtx->pos);
        gd_rotate_and_translate_vec3f(localVec, &D_801B9EA8);
        vec3f_copy(sResetCurWeight->vec20, localVec);
        vtx->scaleFactor        -= sResetCurWeight->weightVal;
    }
}

void reset_weight(struct ObjWeight *weight) {
    struct ObjGroup *skinGroup;
    sResetCurWeight = weight;
    sResetWeightVtxNum = 0;
    if ((skinGroup = gGdSkinNet->skinGrp) != NULL) {
        // Go through every vertex in the skin group, and reset the weight if the vertex is managed by the weight
        apply_to_obj_types_in_group(OBJ_TYPE_VERTICES, (applyproc_t) reset_weight_vtx, skinGroup);
    } else {
        gd_exit(); // Skin net has no SkinGroup
    }
    if (weight->vtx == NULL) gd_exit(); // fatal_printf("reset_weight(): Skin vertex ID %d not found", weight->vtxId);
}

void reset_joint_weights(struct ObjJoint *joint) {
    struct ObjGroup *group;
    mtxf_inverse(&D_801B9EA8, &joint->invMtx);
    if ((group = joint->weightGrp) != NULL) apply_to_obj_types_in_group(OBJ_TYPE_WEIGHTS, (applyproc_t) reset_weight, group);
}
