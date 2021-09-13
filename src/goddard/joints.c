#include <PR/ultratypes.h>

#include "draw_objects.h"
#include "dynlist_proc.h"
#include "gd_main.h"
#include "joints.h"
#include "objects.h"
#include "sfx.h"
#include "skin.h"
#include "engine/math_util.h"

static s32 sJointCount;                   // @ 801BA974

/**
 * Controls movement of grabbable joints
 */
void grabbable_joint_update_func(struct ObjJoint *self) {
    Mat4 *attObjMtx;
    Vec3f offset;  // difference between current position and initial position
    register struct ListNode *att;
    struct GdObj *attobj;
    // The joint acts somewhat like a spring in that the further it is moved
    // from its original position, the more resistance it has to moving further
    vec3_diff(offset, self->rotationMtx[3], self->initPos);
    if (self->header.drawFlags & OBJ_PICKED) {
        vec3_prod_val(self->velocity, offset, -0.25f);
        self->flags |= JOINT_FLAG_GRABBED;
    } else {
        if (!gGdCtrl.trgR) { // R trigger is released
            // Set velocity so that the joint approaches its initial position
            self->velocity[0] -= (offset[0] * 0.5f);
            self->velocity[1] -= (offset[1] * 0.5f);
            self->velocity[2] -= (offset[2] * 0.5f);
            // Decay the velocity
            vec3f_mul_val(self->velocity, 0.8f);
            // If the joint's velocity has decayed enough and it is very close
            // to its original position, stop its movement altogether
            if (((ABSF(self->velocity[0]) + ABSF(self->velocity[1]) + ABSF(self->velocity[2])) < 1.0f)
             && ((ABSF(offset[0]) + ABSF(offset[1]) + ABSF(offset[2])) < 1.0f)) {
                vec3_zero(self->velocity);
                vec3_sub(self->rotationMtx[3], offset);
            }
            if (self->flags & JOINT_FLAG_GRABBED) gd_play_sfx(GD_SFX_LET_GO_FACE);
            self->flags &= ~JOINT_FLAG_GRABBED;
        } else {
            // freeze position of joint
            vec3_zero(self->velocity);
        }
    }
    // update position
    vec3_add(self->rotationMtx[3], self->velocity);
    if (self->header.drawFlags & OBJ_PICKED) {
        gGdCtrl.csrX -= ((gGdCtrl.csrX - gGdCtrl.dragStartX) * 0.2f);
        gGdCtrl.csrY -= ((gGdCtrl.csrY - gGdCtrl.dragStartY) * 0.2f);
    }
    // update position of attached objects
    vec3_diff(offset, self->rotationMtx[3], self->initPos);
    for ((att = self->attachedObjsGrp->firstMember); (att != NULL); (att = att->next)) {
        attobj = att->obj;
        set_cur_dynobj(attobj);
        attObjMtx = d_get_matrix_ptr();
        vec3_add((*attObjMtx)[3], offset);
    }
}

/**
 * Update function for Mario's eye joints, which makes them follow the cursor
 */
void eye_joint_update_func(struct ObjJoint *self) {
    Mat4 *rotMtx;
    Vec3f offset;
    Vec3f pos;
    register struct ListNode *att;
    struct GdObj *attobj;
    if ((sCurrentMoveCamera == NULL) || ((self->rootAnimator != NULL) && (self->rootAnimator->state != 7))) return;
    set_cur_dynobj((struct GdObj *)self);
    rotMtx = d_get_rot_mtx_ptr();
    vec3_copy(pos, (*rotMtx)[3]);
    world_pos_to_screen_coords(pos, sCurrentMoveCamera, sCurrentMoveView);
    offset[0]  =  (gGdCtrl.csrX - pos[0]);
    offset[1]  = -(gGdCtrl.csrY - pos[1]);
    offset[2]  = 0.0f;
    vec3f_mul_val(offset, 2.0f);
    if (vec3_sumsq(offset) > sqr(30.0f)) {
        vec3f_normalize(offset);
        vec3f_mul_val(offset, 30.0f);
    }
    for ((att = self->attachedObjsGrp->firstMember); (att != NULL); (att = att->next)) {
        attobj = att->obj;
        set_cur_dynobj(attobj);
        rotMtx = d_get_rot_mtx_ptr();
        vec3f_add((*rotMtx)[3], offset);
    }
}

/* 23D748 -> 23D818; orig name: func_8018EF78 */
void set_joint_vecs(struct ObjJoint *j, Vec3f pos) {
    vec3_copy(j->worldPos,       pos);
    vec3_copy(j->pos,            pos);
    vec3_copy(j->relPos,         pos);
    vec3_copy(j->initPos,        pos);
    vec3_copy(j->rotationMtx[3], pos);
}

/* 23D818 -> 23DA18 */
struct ObjJoint *make_joint(s32 flags, Vec3f pos) {
    struct ObjJoint *j; // sp24
    struct ObjJoint *oldhead;
    j = (struct ObjJoint *) make_object(OBJ_TYPE_JOINTS);
    sJointCount++;
    oldhead      = gGdJointList;
    gGdJointList = j;
    if (oldhead != NULL) {
        j->nextjoint       = oldhead;
        oldhead->prevjoint = j;
    }
    mtxf_identity(j->invMtx);
    mtxf_identity(j->rotationMtx);
    set_joint_vecs(j, pos);
    j->type       = 0;
    j->id         = sJointCount;
    j->flags      = flags;
    j->colourNum  = ((j->flags & 0x1) ? COLOUR_RED : COLOUR_PINK);
    j->unk1C4     = NULL;
    j->shapePtr   = NULL;
    vec3_same(j->scale, 1.0f);
    vec3_zero(j->friction);
    j->updateFunc = NULL;
    return j;
}

/**
 * Creates a joint that can be grabbed by the cursor. When moved, this joint
 * drags the joints in its unk1F8 group along with it. The `shape` does not
 * actually get rendered due to the joint's OBJ_INVISIBLE flag being set.
 */
struct ObjJoint *make_grabber_joint(struct ObjShape *shape, s32 flags, f32 x, f32 y, f32 z) {
    struct ObjJoint *j;
    Vec3f pos = {x, y, z};
    j                    = make_joint(0, pos);
    j->shapePtr          = shape;
    j->type              = 5; //! type name
    j->flags            |= flags;
    j->colourNum         = COLOUR_PINK;
    j->header.drawFlags |= OBJ_IS_GRABBALE;
    j->header.drawFlags |= OBJ_INVISIBLE;
    j->updateFunc        = grabbable_joint_update_func;
    j->rootAnimator      = NULL;
    return j;
}

/* 23E298 -> 23E328; orig name: func_8018FAC8 */
Bool32 set_skin_weight(struct ObjJoint *j, s32 id, struct ObjVertex *vtx /* always NULL */, f32 weight) {
    struct ObjWeight *w;
    if (j->weightGrp == NULL) j->weightGrp = make_group(0);
    w = make_weight(id, vtx, weight);
    addto_group(j->weightGrp, &w->header);
    return TRUE;
}

/* 23FDD4 -> 23FFF4 */
void reset_joint(struct ObjJoint *j) {
    vec3_copy(j->worldPos, j->initPos);
    vec3_copy(j->pos,      j->initPos);
    vec3_copy(j->relPos,   j->initPos);
    vec3_zero(j->velocity);
    // vec3_zero(j->unk84);  // unused
    // vec3_zero(j->unk90);  // unused
    // vec3_zero(j->unk1A8); // unused
    mtxf_identity(j->idMtx);
    mtxf_scale_self_vec3f( j->idMtx, j->scale);
    mtxf_rot_about_vec3f(j->idMtx, j->initRotation);
    vec3_add(j->idMtx[3], j->attachOffset);
    mtxf_copy(j->invMtx, j->idMtx);
    mtxf_identity(j->rotationMtx);
    vec3_add(j->rotationMtx[3], j->initPos);
    vec3_copy(j->nextPos, j->initPos); // storing "attached offset"?
    linear_mtxf_self_mul_vec3f_self(gGdSkinNet->invMtx, j->nextPos);
    vec3_copy(j->relPos, j->nextPos);
    vec3_copy(j->worldPos, gGdSkinNet->worldPos);
    vec3_add(j->worldPos, j->relPos);
    // vec3_zero(j->unk1A8); // unused
}

/* 2406B8 -> 2406E0; orig name: func_80191EE8 */
void reset_joint_counts(void) {
    sJointCount = 0;
}
