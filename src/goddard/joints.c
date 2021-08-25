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
    Vec3f offset;  // difference between current position and initial position
    register struct ListNode *att;
    struct GdObj *attobj;
    // The joint acts somewhat like a spring in that the further it is moved
    // from its original position, the more resistance it has to moving further
    vec3f_diff(offset, self->rotationMtx[3], self->initPos);
    if (self->header.drawFlags & OBJ_PICKED) {
        self->velocity[0] = (offset[0] * -0.25f);
        self->velocity[1] = (offset[1] * -0.25f);
        self->velocity[2] = (offset[2] * -0.25f);
        self->flags |= JOINT_FLAG_GRABBED;
    } else {
        if (!gGdCtrl.trgR) { // R trigger is released
            // Set velocity so that the joint approaches its initial position
            self->velocity[0] -= (offset[0] * 0.5f);
            self->velocity[1] -= (offset[1] * 0.5f);
            self->velocity[2] -= (offset[2] * 0.5f);
            // Decay the velocity
            vec3f_mul_f32(self->velocity, 0.8f);
            // If the joint's velocity has decayed enough and it is very close
            // to its original position, stop its movement altogether
            if (((ABSF(self->velocity[0]) + ABSF(self->velocity[1]) + ABSF(self->velocity[2])) < 1.0f)
             && ((ABSF(offset[0]) + ABSF(offset[1]) + ABSF(offset[2])) < 1.0f)) {
                vec3f_zero(self->velocity);
                vec3f_sub(self->rotationMtx[3], offset);
            }
            if (self->flags & JOINT_FLAG_GRABBED) gd_play_sfx(GD_SFX_LET_GO_FACE);
            self->flags &= ~JOINT_FLAG_GRABBED;
        } else {
            // freeze position of joint
            vec3f_zero(self->velocity);
        }
    }
    // update position
    vec3f_add(self->rotationMtx[3], self->velocity);
    if (self->header.drawFlags & OBJ_PICKED) {
        gGdCtrl.csrX -= ((gGdCtrl.csrX - gGdCtrl.dragStartX) * 0.2f);
        gGdCtrl.csrY -= ((gGdCtrl.csrY - gGdCtrl.dragStartY) * 0.2f);
    }
    // update position of attached objects
    vec3f_diff(offset, self->rotationMtx[3], self->initPos);
    for ((att = self->attachedObjsGrp->firstMember); (att != NULL); (att = att->next)) {
        attobj = att->obj;
        set_cur_dynobj(attobj);
        attObjMtx = d_get_matrix_ptr();
        vec3f_add((*attObjMtx)[3], offset);
    }
}

/**
 * Update function for Mario's eye joints, which makes them follow the cursor
 */
void eye_joint_update_func(struct ObjJoint *self) {
    Mat4 *rotMtx;
    Vec3f offset;
    Vec3f sp44;
    register struct ListNode *att;
    struct GdObj *attobj;
    if ((sCurrentMoveCamera == NULL) || ((self->rootAnimator != NULL) && (self->rootAnimator->state != 7))) return;
    set_cur_dynobj((struct GdObj *)self);
    rotMtx = d_get_rot_mtx_ptr();
    vec3f_copy(sp44, (*rotMtx)[3]);
    world_pos_to_screen_coords(sp44, sCurrentMoveCamera, sCurrentMoveView);
    offset[0]  =  (gGdCtrl.csrX - sp44[0]);
    offset[1]  = -(gGdCtrl.csrY - sp44[1]);
    offset[2]  = 0.0f;
    vec3f_mul_f32(offset, 2.0f);
    if (vec3f_mag(offset) > 30.0f) {
        vec3f_normalize(offset);
        vec3f_mul_f32(offset, 30.0f);
    }
    for (att = self->attachedObjsGrp->firstMember; att != NULL; att = att->next) {
        attobj = att->obj;
        set_cur_dynobj(attobj);
        rotMtx = d_get_rot_mtx_ptr();
        vec3f_add((*rotMtx)[3], offset);
    }
}

/* 23D748 -> 23D818; orig name: func_8018EF78 */
void set_joint_vecs(struct ObjJoint *j, f32 x, f32 y, f32 z) {
    vec3f_set(j->worldPos, x, y, z);
    vec3f_set(j->unk30, x, y, z);
    vec3f_set(j->unk3C, x, y, z);
    vec3f_set(j->initPos, x, y, z);
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
    vec3f_copy(j->scale, gVec3fOne);
    vec3f_zero(j->friction);
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
    vec3f_copy(j->unk48, j->initPos); // storing "attached offset"?
    gd_mat4f_mult_vec3f(j->unk48, &gGdSkinNet->mat128);
    vec3f_copy(j->unk3C, j->unk48);
    vec3f_copy(j->worldPos, gGdSkinNet->worldPos);
    vec3f_add(j->worldPos, j->unk3C);
    // vec3f_zero(j->unk1A8); // unused
}

/* 23FDD4 -> 23FFF4 */
void reset_joint(struct ObjJoint *j) {
    vec3f_copy(j->worldPos, j->initPos);
    vec3f_copy(j->unk30, j->initPos);
    vec3f_copy(j->unk3C, j->initPos);
    vec3f_zero(j->velocity);
    // vec3f_zero(j->unk84);  // unused
    // vec3f_zero(j->unk90);  // unused
    // vec3f_zero(j->unk1A8); // unused
    gd_set_identity_mat4(        &j->idMtx);
    gd_scale_mat4f_by_vec3f(   &j->idMtx, j->scale);
    gd_rot_mat_about_vec3f(      &j->idMtx, j->initRotation);
    vec3f_add(j->idMtx[3], j->attachOffset);
    gd_copy_mat4f(               &j->idMtx, &j->matE8);
    gd_set_identity_mat4(        &j->rotationMtx);
    vec3f_add(j->rotationMtx[3], j->initPos);
}

/* 2406B8 -> 2406E0; orig name: func_80191EE8 */
void reset_joint_counts(void) {
    sJointCount = 0;
}
