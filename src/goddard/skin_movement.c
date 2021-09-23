#include <PR/ultratypes.h>

#include "engine/math_util.h"
#include "objects.h"
#include "renderer.h"
#include "skin.h"
#include "skin_movement.h"

//! combine with skin.c?

/* bss */
struct ObjWeight *sResetCurWeight;
static Mat4 sHead2Mtx; // TODO: rename to sHead2Mtx?

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
            vec3_prod_val(vtx->pos, vtx->initPos, scaleFac);
        } else {
            vec3_zero(vtx->pos);
        }
    }
}

/* @ 230064 for 0x13C*/
void func_80181894(struct ObjJoint *joint) {
    Vec3f stackVec;
    register struct ObjWeight *curWeight;
    register struct ObjVertex *connectedVtx;
    register struct ListNode *link;
    register f32 scaleFactor;
    struct GdObj *linkedObj;
    register struct ObjGroup *weightGroup = joint->weightGrp; // baseGroup? weights Only?
    if (weightGroup != NULL) {
        for ((link = weightGroup->firstMember); (link != NULL); (link = link->next)) {
            linkedObj                = link->obj;
            curWeight                = (struct ObjWeight *) linkedObj;
            if (curWeight->weightVal > 0.0f) {
                linear_mtxf_mul_vec3f_and_translate(joint->invMtx, stackVec, curWeight->vec20);
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
    // Vec3f localVec;
    if (sResetWeightVtxNum++ == sResetCurWeight->vtxId) {  // found matching vertex
        sResetCurWeight->vtx = vtx;
        linear_mtxf_mul_vec3f_and_translate(sHead2Mtx, sResetCurWeight->vec20, vtx->pos);
        vtx->scaleFactor    -= sResetCurWeight->weightVal;
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
    mtxf_inverse(&sHead2Mtx, &joint->invMtx);
    if ((group = joint->weightGrp) != NULL) apply_to_obj_types_in_group(OBJ_TYPE_WEIGHTS, (applyproc_t) reset_weight, group);
}
