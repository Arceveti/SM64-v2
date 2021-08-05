#include <PR/ultratypes.h>

#include "debug_utils.h"
#include "draw_objects.h"
#include "dynlist_proc.h"
#include "gd_math.h"
#include "gd_types.h"
#include "macros.h"
#include "objects.h"
#include "particles.h"
#include "renderer.h"
#include "skin.h"

// static types
typedef union {
    struct ObjVertex *vtx;
    struct ObjParticle *ptc;
} VtxPtc;

struct Connection {
    struct GdObj header;  // this header is never used
    u8 filler14[8];
    VtxPtc node1;  // first connected vertex or particle
    VtxPtc node2;  // second connected vertex or particle
    f32 unk24;
    u32 unk28; // union tag? 0 = vertex; 1 = particle?
};

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

// static bss
static struct ObjFace *D_801B9EF0;

// fn declarations
void Unknown80181D14(struct ObjFace     *);
void func_80181EB0(  struct Connection  *);
void func_80182088(  struct Connection  *);
void move_particle(  struct ObjParticle *);
int  func_80182778(  struct ObjParticle *);
void func_80182A08(  struct ObjParticle *, struct GdVec3f *b);

static void connect_vertices(struct ObjVertex *vtx1, struct ObjVertex *vtx2) {
    register struct ListNode *link;
    if (vtx1 == vtx2) return;
    link = gGdSkinNet->unk1C0->firstMember;
    while (link != NULL) {
        // FIXME: types
        struct Connection *conn = (struct Connection *) link->obj;
        if ((conn->node1.vtx == vtx1 || conn->node1.vtx == vtx2)
         && (conn->node2.vtx == vtx1 || conn->node2.vtx == vtx2)) break;
        link = link->next;
    }
}

/* 2304E4 -> 230680 */
void Unknown80181D14(struct ObjFace *face) {
    s32 i;
    s32 j;
    struct ObjVertex *vtx1;
    struct ObjVertex *vtx2;
    for (i = 0; i < face->vtxCount - 1; i++) {
        vtx1 = face->vertices[i];
        vtx2 = face->vertices[i + 1];
        connect_vertices(vtx1, vtx2);
    }
    if (D_801B9EF0 != NULL) {
        for (i = 0; i < face->vtxCount; i++) {
            vtx1 = face->vertices[i];
            for (j = 0; j < D_801B9EF0->vtxCount; j++) {
                vtx2 = D_801B9EF0->vertices[j];
                connect_vertices(vtx1, vtx2);
            }
        }
    }
    D_801B9EF0 = face;
}

/* 230680 -> 230858 */
void func_80181EB0(struct Connection *cxn) {
    struct GdVec3f sp34;
    struct ObjParticle *sp4 = cxn->node1.ptc;
    struct ObjParticle *sp0 = cxn->node2.ptc;
    sp34.x        = 0.0f;
    sp34.y        = sp4->pos.y - sp0->pos.y;
    sp34.z        = 0.0f;
    sp34.y       *= 0.01f;
    sp4->unk38.x -= sp34.x;
    sp4->unk38.y -= sp34.y;
    sp4->unk38.z -= sp34.z;
    sp0->unk38.x += sp34.x;
    sp0->unk38.y += sp34.y;
    sp0->unk38.z += sp34.z;
    if (!(sp4->flags & 0x2)) {
        sp4->pos.x -= sp34.x;
        sp4->pos.y -= sp34.y;
        sp4->pos.z -= sp34.z;
    }
    if (!(sp0->flags & 0x2)) {
        sp0->pos.x += sp34.x;
        sp0->pos.y += sp34.y;
        sp0->pos.z += sp34.z;
    }
}

/* @ 230858 -> 230B70 */
void func_80182088(struct Connection *cxn) {
    struct GdVec3f vec;
    f32 mul;
    f32 div;
    struct ObjParticle *particle1;
    struct ObjParticle *particle2;
    if (cxn->unk28 & 0x1) {
        func_80181EB0(cxn);
        return;
    }
    particle1 = cxn->node1.ptc;
    particle2 = cxn->node2.ptc;
    vec.x = particle1->pos.x - particle2->pos.x;
    vec.y = particle1->pos.y - particle2->pos.y;
    vec.z = particle1->pos.z - particle2->pos.z;
    div = gd_vec3f_magnitude(&vec); //? fast invsqrt
    mul = div - cxn->unk24;
    vec.x /= div;
    vec.y /= div;
    vec.z /= div;
    vec.x *= mul * 0.1f;
    vec.y *= mul * 0.1f;
    vec.z *= mul * 0.1f;
    particle1->unk38.x -= vec.x;
    particle1->unk38.y -= vec.y;
    particle1->unk38.z -= vec.z;
    particle2->unk38.x += vec.x;
    particle2->unk38.y += vec.y;
    particle2->unk38.z += vec.z;
    if (!(particle1->flags & 0x2)) {
        particle1->pos.x -= vec.x;
        particle1->pos.y -= vec.y;
        particle1->pos.z -= vec.z;
    }
    if (!(particle2->flags & 0x2)) {
        particle2->pos.x += vec.x;
        particle2->pos.y += vec.y;
        particle2->pos.z += vec.z;
    }
}

/* 230B70 -> 230CC0 */
void func_801823A0(struct ObjNet *net) {
    register struct ListNode *link;
    struct Connection *cxn;
    gGdSkinNet = net;
    switch (net->unk3C) {
        case 1: // Shape; Are these flags the same as net->netType (+0x1EC)?
            net->unk1C8 = net->shapePtr->vtxGroup;
            net->unk1C0 = make_group(0);
            D_801B9EF0 = NULL;
            apply_to_obj_types_in_group(OBJ_TYPE_FACES, (applyproc_t) Unknown80181D14, net->shapePtr->faceGroup);
            net->unk3C = 2;
            break;
        case 2:
            link = net->unk1C0->firstMember;
            while (link != NULL) {
                // FIXME: types
                cxn = (struct Connection *) link->obj;
                func_80182088(cxn);
                link = link->next;
            }
            apply_to_obj_types_in_group(OBJ_TYPE_PARTICLES, (applyproc_t) move_particle, net->unk1C8);
            apply_to_obj_types_in_group(OBJ_TYPE_PLANES   , (applyproc_t) reset_plane  , net->unk1CC);
            break;
    }
}

/* 230CC0 -> 230DCC */
struct ObjParticle *make_particle(u32 flags, s32 colourNum, f32 x, f32 y, f32 z) {
    struct ObjParticle *particle = (struct ObjParticle *) make_object(OBJ_TYPE_PARTICLES);
    particle->pos.x     = x;
    particle->pos.y     = y;
    particle->pos.z     = z;
    particle->unk38.x   = particle->unk38.y = particle->unk38.z = 0.0f;
    particle->colourNum = colourNum;
    particle->flags     = flags | 8;
    particle->timeout   = -1;
    particle->shapePtr  = NULL;
    particle->unkB0     =  1;
    return particle;
}

/* 230F48 -> 2311D8 */
int func_80182778(struct ObjParticle *ptc) {
    s32 sp4 = 0;
    if (ptc->unk7C->animSeqNum == 2 && ptc->unk74 == 1) {
        while (D_801A81D4[sp4] != 0) {
            if (D_801A81D4[sp4] == ptc->unk7C->frame) {
                ptc->pos.x = D_801A81D4[sp4 + 1] * 10.0f;
                ptc->pos.y = D_801A81D4[sp4 + 2] * 10.0f;
                ptc->pos.z = D_801A81D4[sp4 + 3] * 10.0f;
                return TRUE;
            }
            sp4 += 4;
        }
    }
    if (ptc->unk7C->animSeqNum == 1 && ptc->unk74 == 1) {
        while (D_801A8238[sp4] != 0) {
            if (D_801A8238[sp4] == ptc->unk7C->frame) {
                ptc->pos.x = D_801A8238[sp4 + 1] * 10.0f;
                ptc->pos.y = D_801A8238[sp4 + 2] * 10.0f;
                ptc->pos.z = D_801A8238[sp4 + 3] * 10.0f;
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
    struct ObjParticle *sp20;
    if (ptc->subParticlesGrp != NULL) {
        link = ptc->subParticlesGrp->firstMember;
        while (link != NULL) {
            // FIXME: types
            sp20 = (struct ObjParticle *) link->obj;
            if (sp20->timeout <= 0) {
                sp20->pos.x = ptc->pos.x;
                sp20->pos.y = ptc->pos.y;
                sp20->pos.z = ptc->pos.z;
                sp20->timeout = 12.0f - gd_rand_float() * 5.0f;
                do {
                    sp20->unk38.x = gd_rand_float() * 50.0f - 25.0f;
                    sp20->unk38.y = gd_rand_float() * 50.0f - 25.0f;
                    sp20->unk38.z = gd_rand_float() * 50.0f - 25.0f;
                } while (gd_vec3f_magnitude(&sp20->unk38) > 30.0f);
                sp20->unk38.x += b->x;
                sp20->unk38.y += b->y;
                sp20->unk38.z += b->z;
                sp20->header.drawFlags &= ~OBJ_INVISIBLE;
                sp20->flags |= 8;
            }
            link = link->next;
        }
    }
}

/* 231454 -> 231D40; orig name: Unknown80182C84 */
void move_particle(struct ObjParticle *ptc) {
    f32 sp7C;
    struct GdVec3f sp64;
    struct ObjParticle *particle;
    s32 i;
    struct ObjCamera *camera;
    struct GdVec3f sp40;
    struct GdVec3f sp34;
    if (  ptc->flags & 0x2)  return;
    if (!(ptc->flags & 0x8)) return;
    if (ptc->unk60 == 3) {
        sp40.x = -gViewUpdateCamera->unkE8[2][0] *  50.0f;
        sp40.y = -gViewUpdateCamera->unkE8[2][1] *  50.0f;
        sp40.z =  gViewUpdateCamera->unkE8[2][2] *  50.0f;
        sp34.x =  gViewUpdateCamera->unkE8[2][0] * -20.0f;
        sp34.y =  gViewUpdateCamera->unkE8[2][1] * -20.0f;
        sp34.z =  gViewUpdateCamera->unkE8[2][2] * -20.0f;
    }
    if (ptc->attachedToObj != NULL) {
        set_cur_dynobj(ptc->attachedToObj);
        if (ptc->unk60 == 3 && ptc->unk64 == 3) {
            camera = (struct ObjCamera *) ptc->attachedToObj;
            // Camera->unk18C = ObjView here
            if (camera->unk18C->pickedObj != NULL) {
                set_cur_dynobj(camera->unk18C->pickedObj);
                ptc->flags |= 0x20;
            } else {
                ptc->flags &= ~0x10;
                ptc->flags &= ~0x20;
            }
        }
        d_get_world_pos(&sp64);
        ptc->pos.x = sp64.x;
        ptc->pos.y = sp64.y;
        ptc->pos.z = sp64.z;
    }
    sp7C = -0.4f;
    ptc->pos.x += ptc->unk38.x;
    ptc->pos.y += ptc->unk38.y;
    ptc->pos.z += ptc->unk38.z;
    if (ptc->flags & 0x1) ptc->unk38.y += sp7C;
    if (ptc->unkB0 == 1) {
        ptc->unkB0 = 2;
        if (ptc->unk60 == 3) {
            switch (ptc->unk64) {
                case 1:
                    ptc->subParticlesGrp = make_group(0);
                    for (i = 0; i < 50; i++) {
                        particle = make_particle(1, -1, ptc->pos.x, ptc->pos.y, ptc->pos.z);
                        particle->shapePtr = ptc->shapePtr;
                        addto_group(ptc->subParticlesGrp, &particle->header);
                        particle->flags &= ~8;
                    }
                    break;
                case 2:
                case 3:
                    ptc->subParticlesGrp = make_group(0);
                    for (i = 0; i < 30; i++) {
                        particle = make_particle(1, -1, ptc->pos.x, ptc->pos.y, ptc->pos.z);
                        particle->shapePtr = ptc->shapePtr;
                        addto_group(ptc->subParticlesGrp, &particle->header);
                        particle->flags &= ~8;
                    }
                    break;
            }
        }
    }
    ptc->unk38.x *= 0.9f;
    ptc->unk38.y *= 0.9f;
    ptc->unk38.z *= 0.9f;
    if (ptc->unk60 == 3) {
        switch (ptc->unk64) {
            case 1:
                if (func_80182778(ptc) && ptc->subParticlesGrp != NULL) {
                    register struct ListNode *link;
                    if (ptc->unk80 != NULL) {
                        ptc->unk80->unk3C |= 1;
                        ptc->unk80->position.x = ptc->pos.x;
                        ptc->unk80->position.y = ptc->pos.y;
                        ptc->unk80->position.z = ptc->pos.z;
                    }
                    link = ptc->subParticlesGrp->firstMember;
                    while (link != NULL) {
                        struct ObjParticle *sp2C = (struct ObjParticle *) link->obj;
                        sp2C->pos.x = ptc->pos.x;
                        sp2C->pos.y = ptc->pos.y;
                        sp2C->pos.z = ptc->pos.z;
                        sp2C->timeout = 20;
                        do {
                            sp2C->unk38.x = gd_rand_float() * 64.0f - 32.0f;
                            sp2C->unk38.y = gd_rand_float() * 64.0f - 32.0f;
                            sp2C->unk38.z = gd_rand_float() * 64.0f - 32.0f;
                        } while (gd_vec3f_magnitude(&sp2C->unk38) > 32.0f);
                        sp2C->unk30 = gd_rand_float() * 180.0f;
                        sp2C->header.drawFlags &= ~OBJ_INVISIBLE;
                        sp2C->flags |= 8;
                        link = link->next;
                    }
                }
                break;
            case 3:
                if ((ptc->flags & 0x20) && !(ptc->flags & 0x10)) {
                    func_80182A08(ptc, &sp40);
                    ptc->flags |= 0x10;
                }
                break;
            case 2: func_80182A08(ptc, &sp34); break;
        }
        apply_to_obj_types_in_group(OBJ_TYPE_PARTICLES, (applyproc_t) move_particle, ptc->subParticlesGrp);
    }
    if (ptc->timeout >= 0) {
        if (ptc->timeout-- <= 0) {
            ptc->header.drawFlags |= OBJ_INVISIBLE;
            ptc->flags &= ~0x8;
        }
    }
}

/* 231D40 -> 231D98; orig name: func_80183570 */
void move_particles_in_grp(struct ObjGroup *group) {
    gGdSkinNet = NULL;
    apply_to_obj_types_in_group(OBJ_TYPE_PARTICLES, (applyproc_t) move_particle, group);
}
