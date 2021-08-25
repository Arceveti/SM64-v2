#include <PR/ultratypes.h>

#include "draw_objects.h"
#include "dynlist_proc.h"
#include "gd_math.h"
#include "objects.h"
#include "particles.h"
#include "skin.h"

// static types
typedef union {
    struct ObjVertex   *vtx;
    struct ObjParticle *ptc;
} VtxPtc;

// data
static s32 D_801A81D4[25] = {
    /*  ID?    X    Y    Z */
    9,  3,  12,  -14, 25, 5,  16,  -25, 42, 4,  15, -39, 55,
    -6, 20, -23, 70,  -2, 20, -23, 135, 0,  16, 0,  0 /* Terminator */
};
static s32 D_801A8238[5] = {
    /*  ID? X   Y  Z */
    15, 0, 22, 0, 0 /* Terminator */
};

// fn declarations
void   move_particle(  struct ObjParticle *ptc);
Bool32 func_80182778(  struct ObjParticle *ptc);
void   func_80182A08(  struct ObjParticle *ptc, struct GdVec3f *b);

/* 230CC0 -> 230DCC */
struct ObjParticle *make_particle(u32 flags, s32 colourNum, f32 x, f32 y, f32 z) {
    struct ObjParticle *particle = (struct ObjParticle *) make_object(OBJ_TYPE_PARTICLES);
    particle->pos.x     = x;
    particle->pos.y     = y;
    particle->pos.z     = z;
    particle->unk38.x   = particle->unk38.y = particle->unk38.z = 0.0f;
    particle->colourNum = colourNum;
    particle->flags     = flags | GD_PARTICLE_FLAG_8;
    particle->timeout   = -1;
    particle->shapePtr  = NULL;
    particle->unkB0     =  1;
    return particle;
}

/* 230F48 -> 2311D8 */
Bool32 func_80182778(struct ObjParticle *ptc) {
    s32 sp4 = 0;
    if ((ptc->unk7C->animSeqNum == 2) && (ptc->unk74 == 1)) {
        while (D_801A81D4[sp4] != 0) {
            if (D_801A81D4[sp4] == ptc->unk7C->frame) {
                ptc->pos.x = (D_801A81D4[sp4 + 1] * 10.0f);
                ptc->pos.y = (D_801A81D4[sp4 + 2] * 10.0f);
                ptc->pos.z = (D_801A81D4[sp4 + 3] * 10.0f);
                return TRUE;
            }
            sp4 += 4;
        }
    }
    if (ptc->unk7C->animSeqNum == 1 && ptc->unk74 == 1) {
        while (D_801A8238[sp4] != 0) {
            if (D_801A8238[sp4] == ptc->unk7C->frame) {
                ptc->pos.x = (D_801A8238[sp4 + 1] * 10.0f);
                ptc->pos.y = (D_801A8238[sp4 + 2] * 10.0f);
                ptc->pos.z = (D_801A8238[sp4 + 3] * 10.0f);
                return TRUE;
            }
            sp4 += 4;
        }
    }
    return FALSE;
}

/* 2311D8 -> 231454 */
void func_80182A08(struct ObjParticle *ptc, struct GdVec3f *b) {
    register struct ListNode *link;
    struct ObjParticle *linkedPtc;
    if (ptc->subParticlesGrp != NULL) {
        link = ptc->subParticlesGrp->firstMember;
        while (link != NULL) {
            // FIXME: types
            linkedPtc = (struct ObjParticle *) link->obj;
            if (linkedPtc->timeout <= 0) {
                linkedPtc->pos.x = ptc->pos.x;
                linkedPtc->pos.y = ptc->pos.y;
                linkedPtc->pos.z = ptc->pos.z;
                linkedPtc->timeout = (12.0f - (gd_rand_float() * 5.0f));
                do {
                    linkedPtc->unk38.x = ((gd_rand_float() * 50.0f) - 25.0f);
                    linkedPtc->unk38.y = ((gd_rand_float() * 50.0f) - 25.0f);
                    linkedPtc->unk38.z = ((gd_rand_float() * 50.0f) - 25.0f);
                } while (gd_vec3f_magnitude(&linkedPtc->unk38) > 30.0f);
                linkedPtc->unk38.x += b->x;
                linkedPtc->unk38.y += b->y;
                linkedPtc->unk38.z += b->z;
                linkedPtc->header.drawFlags &= ~OBJ_INVISIBLE;
                linkedPtc->flags |= GD_PARTICLE_FLAG_8;
            }
            link = link->next;
        }
    }
}

/* 231454 -> 231D40; orig name: Unknown80182C84 */
void move_particle(struct ObjParticle *ptc) {
    f32 sp7C;
    Vec3f worldPos;
    struct ObjParticle *particle;
    s32 i;
    struct ObjCamera *camera;
    struct GdVec3f sp40;
    struct GdVec3f sp34;
    if (  ptc->flags & GD_PARTICLE_FLAG_2)  return;
    if (!(ptc->flags & GD_PARTICLE_FLAG_8)) return;
    if (ptc->particleType == 3) {
        sp40.x = (-gViewUpdateCamera->unkE8[2][0] *  50.0f);
        sp40.y = (-gViewUpdateCamera->unkE8[2][1] *  50.0f);
        sp40.z = ( gViewUpdateCamera->unkE8[2][2] *  50.0f);
        sp34.x = ( gViewUpdateCamera->unkE8[2][0] * -20.0f);
        sp34.y = ( gViewUpdateCamera->unkE8[2][1] * -20.0f);
        sp34.z = ( gViewUpdateCamera->unkE8[2][2] * -20.0f);
    }
    if (ptc->attachedToObj != NULL) {
        set_cur_dynobj(ptc->attachedToObj);
        if ((ptc->particleType == 3) && (ptc->unk64 == 3)) {
            camera = (struct ObjCamera *) ptc->attachedToObj;
            // Camera->unk18C = ObjView here
            if (camera->unk18C->pickedObj != NULL) {
                set_cur_dynobj(camera->unk18C->pickedObj);
                ptc->flags |=  GD_PARTICLE_FLAG_B;
            } else {
                ptc->flags &= ~GD_PARTICLE_FLAG_A;
                ptc->flags &= ~GD_PARTICLE_FLAG_B;
            }
        }
        d_vec3f_get_world_pos(worldPos);
        vec3f_to_gdvec3f(&ptc->pos, worldPos);
    }
    sp7C = -0.4f;
    ptc->pos.x += ptc->unk38.x;
    ptc->pos.y += ptc->unk38.y;
    ptc->pos.z += ptc->unk38.z;
    if (ptc->flags & GD_PARTICLE_FLAG_1) ptc->unk38.y += sp7C;
    if (ptc->unkB0 == 1) {
        ptc->unkB0 = 2;
        if (ptc->particleType == 3) {
            switch (ptc->unk64) {
                case 1:
                    ptc->subParticlesGrp = make_group(0);
                    for ((i = 0); (i < 50); (i++)) {
                        particle = make_particle(GD_PARTICLE_FLAG_1, -1, ptc->pos.x, ptc->pos.y, ptc->pos.z);
                        particle->shapePtr = ptc->shapePtr;
                        addto_group(ptc->subParticlesGrp, &particle->header);
                        particle->flags &= ~GD_PARTICLE_FLAG_8;
                    }
                    break;
                case 2:
                case 3:
                    ptc->subParticlesGrp = make_group(0);
                    for ((i = 0); (i < 30); (i++)) {
                        particle = make_particle(GD_PARTICLE_FLAG_1, -1, ptc->pos.x, ptc->pos.y, ptc->pos.z);
                        particle->shapePtr = ptc->shapePtr;
                        addto_group(ptc->subParticlesGrp, &particle->header);
                        particle->flags &= ~GD_PARTICLE_FLAG_8;
                    }
                    break;
            }
        }
    }
    ptc->unk38.x *= 0.9f;
    ptc->unk38.y *= 0.9f;
    ptc->unk38.z *= 0.9f;
    if (ptc->particleType == 3) {
        switch (ptc->unk64) {
            case 1:
                if (func_80182778(ptc) && (ptc->subParticlesGrp != NULL)) {
                    register struct ListNode *link;
                    if (ptc->unk80 != NULL) {
                        ptc->unk80->unk3C     |= 0x1;
                        gd_vec3f_copy(&ptc->unk80->position, &ptc->pos);
                    }
                    link = ptc->subParticlesGrp->firstMember;
                    while (link != NULL) {
                        struct ObjParticle *linkedPtc = (struct ObjParticle *) link->obj;
                        gd_vec3f_copy(&linkedPtc->pos, &ptc->pos);
                        linkedPtc->timeout = 20;
                        do {
                            linkedPtc->unk38.x = ((gd_rand_float() * 64.0f) - 32.0f);
                            linkedPtc->unk38.y = ((gd_rand_float() * 64.0f) - 32.0f);
                            linkedPtc->unk38.z = ((gd_rand_float() * 64.0f) - 32.0f);
                        } while (gd_vec3f_magnitude(&linkedPtc->unk38) > 32.0f);
                        linkedPtc->unk30             = (gd_rand_float() * 180.0f);
                        linkedPtc->header.drawFlags &= ~OBJ_INVISIBLE;
                        linkedPtc->flags            |= GD_PARTICLE_FLAG_8;
                        link = link->next;
                    }
                }
                break;
            case 3:
                if ((ptc->flags & GD_PARTICLE_FLAG_B) && !(ptc->flags & GD_PARTICLE_FLAG_A)) {
                    func_80182A08(ptc, &sp40);
                    ptc->flags |= GD_PARTICLE_FLAG_A;
                }
                break;
            case 2: func_80182A08(ptc, &sp34); break;
        }
        apply_to_obj_types_in_group(OBJ_TYPE_PARTICLES, (applyproc_t) move_particle, ptc->subParticlesGrp);
    }
    if (ptc->timeout >= 0) {
        if (ptc->timeout-- <= 0) {
            ptc->header.drawFlags |= OBJ_INVISIBLE;
            ptc->flags            &= ~GD_PARTICLE_FLAG_8;
        }
    }
}

/* 231D40 -> 231D98; orig name: func_80183570 */
void move_particles_in_grp(struct ObjGroup *group) {
    gGdSkinNet = NULL;
    apply_to_obj_types_in_group(OBJ_TYPE_PARTICLES, (applyproc_t) move_particle, group);
}
