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

// fn declarations
void   move_particle(  struct ObjParticle *ptc);
void   func_80182A08(  struct ObjParticle *ptc, Vec3f b);

/* 230CC0 -> 230DCC */
struct ObjParticle *make_particle(u32 flags, s32 colourNum, f32 x, f32 y, f32 z) {
    struct ObjParticle *particle = (struct ObjParticle *) make_object(OBJ_TYPE_PARTICLES);
    vec3f_set(particle->pos, x, y, z);
    vec3f_zero(particle->vel);
    particle->colourNum = colourNum;
    particle->flags     = flags | GD_PARTICLE_FLAG_8;
    particle->timeout   = -1;
    particle->shapePtr  = NULL;
    particle->unkB0     =  1;
    return particle;
}

/* 2311D8 -> 231454 */
void func_80182A08(struct ObjParticle *ptc, Vec3f b) {
    register struct ListNode *link;
    struct ObjParticle *linkedPtc;
    if (ptc->subParticlesGrp != NULL) {
        link = ptc->subParticlesGrp->firstMember;
        while (link != NULL) {
            // FIXME: types
            linkedPtc = (struct ObjParticle *) link->obj;
            if (linkedPtc->timeout <= 0) {
                vec3f_copy(linkedPtc->pos, ptc->pos);
                linkedPtc->timeout = (12.0f - (gd_rand_float() * 5.0f));
                do {
                    linkedPtc->vel[0] = ((gd_rand_float() * 50.0f) - 25.0f);
                    linkedPtc->vel[1] = ((gd_rand_float() * 50.0f) - 25.0f);
                    linkedPtc->vel[2] = ((gd_rand_float() * 50.0f) - 25.0f);
                } while (vec3f_mag(linkedPtc->vel) > 30.0f);
                vec3f_add(linkedPtc->vel, b);
                linkedPtc->header.drawFlags &= ~OBJ_INVISIBLE;
                linkedPtc->flags |= GD_PARTICLE_FLAG_8;
            }
            link = link->next;
        }
    }
}

/* 231454 -> 231D40; orig name: Unknown80182C84 */
void move_particle(struct ObjParticle *ptc) {
    Vec3f worldPos;
    struct ObjParticle *particle;
    s32 i;
    struct ObjCamera *camera;
    Vec3f vec1, vec2;
    if (  ptc->flags & GD_PARTICLE_FLAG_2)  return;
    if (!(ptc->flags & GD_PARTICLE_FLAG_8)) return;
    if (ptc->particleType == 3) {
        vec1[0] = (-gViewUpdateCamera->lookatMtx[2][0] *  50.0f);
        vec1[1] = (-gViewUpdateCamera->lookatMtx[2][1] *  50.0f);
        vec1[2] = ( gViewUpdateCamera->lookatMtx[2][2] *  50.0f);
        vec2[0] = ( gViewUpdateCamera->lookatMtx[2][0] * -20.0f);
        vec2[1] = ( gViewUpdateCamera->lookatMtx[2][1] * -20.0f);
        vec2[2] = ( gViewUpdateCamera->lookatMtx[2][2] * -20.0f);
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
        vec3f_copy(ptc->pos, worldPos);
    }
    vec3f_add(ptc->pos, ptc->vel);
    if (ptc->flags & GD_PARTICLE_FLAG_1) ptc->vel[1] -= 0.4f;
    if (ptc->unkB0 == 1) {
        ptc->unkB0 = 2;
        if (ptc->particleType == 3) {
            switch (ptc->unk64) {
                case 1:
                    ptc->subParticlesGrp = make_group(0);
                    for ((i = 0); (i < 50); (i++)) {
                        particle = make_particle(GD_PARTICLE_FLAG_1, -1, ptc->pos[0], ptc->pos[1], ptc->pos[2]);
                        particle->shapePtr = ptc->shapePtr;
                        addto_group(ptc->subParticlesGrp, &particle->header);
                        particle->flags &= ~GD_PARTICLE_FLAG_8;
                    }
                    break;
                case 2:
                case 3:
                    ptc->subParticlesGrp = make_group(0);
                    for ((i = 0); (i < 30); (i++)) {
                        particle = make_particle(GD_PARTICLE_FLAG_1, -1, ptc->pos[0], ptc->pos[1], ptc->pos[2]);
                        particle->shapePtr = ptc->shapePtr;
                        addto_group(ptc->subParticlesGrp, &particle->header);
                        particle->flags &= ~GD_PARTICLE_FLAG_8;
                    }
                    break;
            }
        }
    }
    vec3f_mul_f32(ptc->vel, 0.9f);
    if (ptc->particleType == 3) {
        switch (ptc->unk64) {
            case 1:
                break;
            case 3:
                if ((ptc->flags & GD_PARTICLE_FLAG_B) && !(ptc->flags & GD_PARTICLE_FLAG_A)) {
                    func_80182A08(ptc, vec1);
                    ptc->flags |= GD_PARTICLE_FLAG_A;
                }
                break;
            case 2: func_80182A08(ptc, vec2); break;
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
