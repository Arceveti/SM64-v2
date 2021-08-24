#include <PR/ultratypes.h>

#include "draw_objects.h"
#include "dynlist_proc.h"
#include "gd_macros.h"
#include "gd_main.h"
#include "gd_math.h"
#include "joints.h"
#include "objects.h"
#include "sfx.h"
#include "skin.h"
#include "engine/math_util.h"

static s32 sJointCount;                   // @ 801BA974

// forward declarations
void set_joint_vecs(struct ObjJoint *j, f32 x, f32 y, f32 z);

/**
 * Controls movement of grabbable joints
 */
void grabbable_joint_update_func(struct ObjJoint *self) {
    Mat4 *attObjMtx;
    struct GdVec3f offset;  // difference between current position and initial position
    register struct ListNode *att;
    struct GdObj *attobj;
    // The joint acts somewhat like a spring in that the further it is moved
    // from its original position, the more resistance it has to moving further
    offset.x = (self->rotationMtx[3][0] - self->initPos.x);
    offset.y = (self->rotationMtx[3][1] - self->initPos.y);
    offset.z = (self->rotationMtx[3][2] - self->initPos.z);
    if (self->header.drawFlags & OBJ_PICKED) {
        self->velocity.x = (offset.x * -0.25f);
        self->velocity.y = (offset.y * -0.25f);
        self->velocity.z = (offset.z * -0.25f);
        self->flags |= JOINT_FLAG_GRABBED;
    } else {
        if (!gGdCtrl.trgR) { // R trigger is released
            // Set velocity so that the joint approaches its initial position
            self->velocity.x -= (offset.x * 0.5f);
            self->velocity.y -= (offset.y * 0.5f);
            self->velocity.z -= (offset.z * 0.5f);
            // Decay the velocity
            self->velocity.x *= 0.8f;
            self->velocity.y *= 0.8f;
            self->velocity.z *= 0.8f;
            // If the joint's velocity has decayed enough and it is very close
            // to its original position, stop its movement altogether
            if ((ABSF(self->velocity.x) + ABSF(self->velocity.y) + ABSF(self->velocity.z) < 1.0f)
             && (ABSF(offset.x) + ABSF(offset.y) + ABSF(offset.z) < 1.0f)) {
                self->velocity.x = self->velocity.y = self->velocity.z = 0.0f;
                self->rotationMtx[3][0] -= offset.x;
                self->rotationMtx[3][1] -= offset.y;
                self->rotationMtx[3][2] -= offset.z;
            }
            if (self->flags & JOINT_FLAG_GRABBED) gd_play_sfx(GD_SFX_LET_GO_FACE);
            self->flags &= ~JOINT_FLAG_GRABBED;
        } else {
            // freeze position of joint
            self->velocity.x = self->velocity.y = self->velocity.z = 0.0f;
        }
    }
    // update position
    self->rotationMtx[3][0] += self->velocity.x;
    self->rotationMtx[3][1] += self->velocity.y;
    self->rotationMtx[3][2] += self->velocity.z;
    if (self->header.drawFlags & OBJ_PICKED) {
        gGdCtrl.csrX -= ((gGdCtrl.csrX - gGdCtrl.dragStartX) * 0.2f);
        gGdCtrl.csrY -= ((gGdCtrl.csrY - gGdCtrl.dragStartY) * 0.2f);
    }
    // update position of attached objects
    offset.x = (self->rotationMtx[3][0] - self->initPos.x);
    offset.y = (self->rotationMtx[3][1] - self->initPos.y);
    offset.z = (self->rotationMtx[3][2] - self->initPos.z);
    for ((att = self->attachedObjsGrp->firstMember); (att != NULL); (att = att->next)) {
        attobj = att->obj;
        set_cur_dynobj(attobj);
        attObjMtx = d_get_matrix_ptr();
        gd_add_vec3f_to_mat4f_offset(attObjMtx, &offset);
    }
}

/**
 * Update function for Mario's eye joints, which makes them follow the cursor
 */
void eye_joint_update_func(struct ObjJoint *self) {
    Mat4 *sp5C;
    struct GdVec3f sp50;
    struct GdVec3f sp44;
    register struct ListNode *att;
    struct GdObj *attobj;
    if ((sCurrentMoveCamera == NULL) || ((self->rootAnimator != NULL) && (self->rootAnimator->state != 7))) return;
    set_cur_dynobj((struct GdObj *)self);
    sp5C = d_get_rot_mtx_ptr();
    vec3f_to_gdvec3f(&sp44, (*sp5C)[3]);
    world_pos_to_screen_coords(&sp44, sCurrentMoveCamera, sCurrentMoveView);
    sp50.x =  (gGdCtrl.csrX - sp44.x);
    sp50.y = -(gGdCtrl.csrY - sp44.y);
    sp50.z =  0.0f;
    sp50.x *= 2.0f;
    sp50.y *= 2.0f;
    sp50.z *= 2.0f;
    if (gd_vec3f_magnitude(&sp50) > 30.0f) {
        gd_normalize_vec3f(&sp50);
        sp50.x *= 30.0f;
        sp50.y *= 30.0f;
        sp50.z *= 30.0f;
    }
    for (att = self->attachedObjsGrp->firstMember; att != NULL; att = att->next) {
        attobj = att->obj;
        set_cur_dynobj(attobj);
        sp5C = d_get_rot_mtx_ptr();
        gd_add_vec3f_to_mat4f_offset(sp5C, &sp50);
    }
}

/* 23D748 -> 23D818; orig name: func_8018EF78 */
void set_joint_vecs(struct ObjJoint *j, f32 x, f32 y, f32 z) {
    j->worldPos.x   = x;
    j->worldPos.y   = y;
    j->worldPos.z   = z;
    j->unk30.x      = x;
    j->unk30.y      = y;
    j->unk30.z      = z;
    j->unk3C.x      = x;
    j->unk3C.y      = y;
    j->unk3C.z      = z;
    j->initPos.x    = x;
    j->initPos.y    = y;
    j->initPos.z    = z;
    vec3f_set(j->rotationMtx[3], x, y, z);
}

/* 23D818 -> 23DA18 */
struct ObjJoint *make_joint(s32 flags, f32 x, f32 y, f32 z) {
    struct ObjJoint *j; // sp24
    struct ObjJoint *oldhead;
    j = (struct ObjJoint *) make_object(OBJ_TYPE_JOINTS);
    sJointCount++;
    oldhead = gGdJointList;
    gGdJointList = j;
    if (oldhead != NULL) {
        j->nextjoint = oldhead;
        oldhead->prevjoint = j;
    }
    gd_set_identity_mat4(&j->matE8 );
    gd_set_identity_mat4(&j->rotationMtx);
    set_joint_vecs(j, x, y, z);
    j->type       = 0;
    j->id         = sJointCount;
    j->flags      = flags;
    j->colourNum  = ((j->flags & 0x1) ? COLOUR_RED : COLOUR_PINK);
    j->unk1C4     = NULL;
    j->shapePtr   = NULL;
    // vec3f_to_gdvec3f(&j->scale, gVec3fOne);
    j->scale.x    = 1.0f;
    j->scale.y    = 1.0f;
    j->scale.z    = 1.0f;
    // vec3f_to_gdvec3f(&j->friction, gVec3fZero);
    j->friction.x = 0.0f;
    j->friction.y = 0.0f;
    j->friction.z = 0.0f;
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
    j                    = make_joint(0, x, y, z);
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

/* 23F9F0 -> 23FB90 */
void func_80191220(struct ObjJoint *j) {
    gd_vec3f_copy(&j->unk48, &j->initPos); // storing "attached offset"?
    gd_mat4f_mult_vec3f(&j->unk48, &gGdSkinNet->mat128);
    gd_vec3f_copy(&j->unk3C, &j->unk48);
    gd_vec3f_copy(&j->worldPos, &gGdSkinNet->worldPos);
    j->worldPos.x += j->unk3C.x;
    j->worldPos.y += j->unk3C.y;
    j->worldPos.z += j->unk3C.z;
    // vec3f_to_gdvec3f(&j->unk1A8, gVec3fZero);
    j->unk1A8.x = j->unk1A8.y = j->unk1A8.z = 0.0f;
}

/* 23FDD4 -> 23FFF4 */
void reset_joint(struct ObjJoint *j) {
    gd_vec3f_copy(&j->worldPos, &j->initPos);
    gd_vec3f_copy(&j->unk30, &j->initPos);
    gd_vec3f_copy(&j->unk3C, &j->initPos);
    j->velocity.x = j->velocity.y = j->velocity.z = 0.0f;
    j->unk84.x    = j->unk84.y    = j->unk84.z    = 0.0f;
    j->unk90.x    = j->unk90.y    = j->unk90.z    = 0.0f;
    j->unk1A8.x   = j->unk1A8.y   = j->unk1A8.z   = 0.0f;
    gd_set_identity_mat4(        &j->idMtx);
    gd_scale_mat4f_by_vec3f(     &j->idMtx, (struct GdVec3f *) &j->scale);
    gd_rot_mat_about_vec(        &j->idMtx, (struct GdVec3f *) &j->unk6C);
    gd_add_vec3f_to_mat4f_offset(&j->idMtx, &j->attachOffset);
    gd_copy_mat4f(               &j->idMtx, &j->matE8);
    gd_set_identity_mat4(        &j->rotationMtx);
    gd_add_vec3f_to_mat4f_offset(&j->rotationMtx, &j->initPos);
}

/* 2406B8 -> 2406E0; orig name: func_80191EE8 */
void reset_joint_counts(void) {
    sJointCount = 0;
}
