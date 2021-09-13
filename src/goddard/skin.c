#include <PR/ultratypes.h>

#include "engine/math_util.h"
#include "draw_objects.h"
#include "joints.h"
#include "objects.h"
#include "renderer.h"
#include "skin.h"
#include "skin_movement.h"

// bss
struct ObjNet *gGdSkinNet; // @ 801BAAF0

static s32 sNetCount; // @ 801BAAF8

/* 2406E0 -> 240894 */
void compute_net_bounding_box(struct ObjNet *net) {
    reset_bounding_box();
    if (net->vertexGrp != NULL) apply_to_obj_types_in_group(OBJ_TYPE_ALL, (applyproc_t) add_obj_pos_to_bounding_box, net->vertexGrp);
    if (net->nodeGrp   != NULL) apply_to_obj_types_in_group(OBJ_TYPE_ALL, (applyproc_t) add_obj_pos_to_bounding_box, net->nodeGrp  );
    gSomeBoundingBox.minX *= net->scale[0];
    gSomeBoundingBox.maxX *= net->scale[0];
    gSomeBoundingBox.minY *= net->scale[1];
    gSomeBoundingBox.maxY *= net->scale[1];
    gSomeBoundingBox.minZ *= net->scale[2];
    gSomeBoundingBox.maxZ *= net->scale[2];
    net->boundingBox.minX  = gSomeBoundingBox.minX;
    net->boundingBox.minY  = gSomeBoundingBox.minY;
    net->boundingBox.minZ  = gSomeBoundingBox.minZ;
    net->boundingBox.maxX  = gSomeBoundingBox.maxX;
    net->boundingBox.maxY  = gSomeBoundingBox.maxY;
    net->boundingBox.maxZ  = gSomeBoundingBox.maxZ;
}

/* 240894 -> 240A64; orig name: func_801920C4 */
void reset_net(struct ObjNet *net) {
    struct ObjGroup *grp;
    vec3_copy(net->worldPos, net->initPos);
    vec3_zero(net->velocity);
    // vec3_zero(net->torque); // unused
    compute_net_bounding_box(net);
    gGdSkinNet = net;
    mtxf_identity(net->rotationMtx);
    mtxf_identity(net->idMtx);
    mtxf_rot_about_vec3f(net->idMtx,    net->initRotation); // set rot mtx to initial rotation?
    vec3_add(              net->idMtx[3], net->worldPos    ); // set to initial position?
    mtxf_copy(net->invMtx, net->idMtx);
    if ((grp = net->nodeGrp) != NULL) apply_to_obj_types_in_group(OBJ_TYPE_JOINTS, (applyproc_t) reset_joint, grp);
}

/* 240A64 -> 240ACC */
void func_80192294(struct ObjNet *net) {
    if (net->attachedToObj == NULL) transform_child_objects_recursive(&net->header, NULL);
}

/* 240ACC -> 240B84 */
void func_801922FC(struct ObjNet *net) {
    struct ObjGroup *group;
    gGdSkinNet = net;
    if (net->netType == NET_TYPE_DYNAMIC_BONES) {
        if (net->shapePtr         != NULL) scale_verts(net->shapePtr->vtxGroup);
        if ((group = net->nodeGrp) != NULL) apply_to_obj_types_in_group(OBJ_TYPE_JOINTS, (applyproc_t) reset_joint_weights, group);
    }
}

/* 240B84 -> 240CF8 */
struct ObjNet *make_net(struct ObjGroup *group) {
    struct ObjNet *net;
    net            = (struct ObjNet *) make_object(OBJ_TYPE_NETS);
    mtxf_identity(net->invMtx);
    vec3_zero(net->initPos);
    net->id        = ++sNetCount;
    vec3_zero(net->scale);
    net->shapePtr  = NULL;
    net->nodeGrp   = group;
    net->faceGroup = NULL;
    net->vertexGrp = NULL;
    net->netType   = NET_TYPE_DEFAULT;
    // net->unk3C     = 1;
    net->colourNum = COLOUR_BLACK;
    net->skinGrp   = NULL;
    reset_net(net);
    return net;
}

/* 24142C -> 24149C; orig name: func_80192C5C */
void move_bonesnet(struct ObjNet *net) {
    struct ObjGroup *group;
    if ((group = net->nodeGrp) != NULL) apply_to_obj_types_in_group(OBJ_TYPE_JOINTS, (applyproc_t) func_80181894, group);
}

/* 241768 -> 241AB4; orig name: func_80192F98 */
void convert_gd_verts_to_Vn(struct ObjGroup *grp) {
    Vtx *vn;
    Vec3uc n;
    Vec3vs pos;
    register struct VtxLink *vtxlink;
#ifndef GBI_FLOATS
    register RawVertexData *vnPos;
#endif
    register struct ObjVertex *vtx;
    register struct ListNode *link;
    struct GdObj *obj;
    for (link = grp->firstMember; link != NULL; link = link->next) {
        obj = link->obj;
        vtx = (struct ObjVertex *) obj;
        vec3f_to_vec3s(pos, vtx->pos);
        vec3_prod_val(n, vtx->normal, 255.0f);
        for (vtxlink = vtx->gbiVerts; vtxlink != NULL; vtxlink = vtxlink->prev) {
#ifndef GBI_FLOATS
            vnPos    = vtxlink->data->n.ob;
            vn       = vtxlink->data;
            *vnPos++ = pos[0];
            *vnPos++ = pos[1];
            *vnPos++ = pos[2];
#else
            vn = vtxlink->data;
            vec3_copy(vn->n.ob, pos);
#endif
            vec3_copy(vn->n.n, n);
        }
    }
}

/* 241AB4 -> 241BCC; orig name: func_801932E4 */
void convert_gd_verts_to_Vtx(struct ObjGroup *grp) {
    register struct VtxLink *vtxlink;
#ifndef GBI_FLOATS
    register RawVertexData *vtxcoords;
#endif
    Vec3vs pos;
    register struct ObjVertex *vtx;
    register struct ListNode *link;
    struct GdObj *obj;
    for (link = grp->firstMember; link != NULL; link = link->next) {
        obj = link->obj;
        vtx = (struct ObjVertex *) obj;
        vec3f_to_vec3s(pos, vtx->pos);
        for (vtxlink = vtx->gbiVerts; vtxlink != NULL; vtxlink = vtxlink->prev) {
#ifndef GBI_FLOATS
            vtxcoords = vtxlink->data->v.ob;
            vec3_copy(vtxcoords, pos);
#else
            vec3_copy(vtxlink->data->v.ob, pos);
#endif
        }
    }
}

/* 241BCC -> 241CA0; orig name: Proc801933FC */
void convert_net_verts(struct ObjNet *net) {
    if (net->netType  == NET_TYPE_SCALED_VERTICES && net->shapePtr != NULL) convert_gd_verts_to_Vtx(net->shapePtr->scaledVtxGroup);
}

/* 241CA0 -> 241D6C */
static void move_joints_in_net(struct ObjNet *net) {
    struct ObjGroup *grp;
    register struct ListNode *link;
    struct GdObj *obj;
    if ((grp = net->nodeGrp) != NULL) {
        for ((link = grp->firstMember); (link != NULL); (link = link->next)) {
            obj = link->obj;
            if ((obj->type == OBJ_TYPE_JOINTS) && ((struct ObjJoint *) obj)->updateFunc != NULL) (*((struct ObjJoint *) obj)->updateFunc)((struct ObjJoint *) obj);
        }
    }
}

/* 241D6C -> 241E94; orig name: func_8019359C */
void move_net(struct ObjNet *net) {
    gGdSkinNet = net;
    switch (net->netType) {
        case NET_TYPE_SHAPE:                                                                                  break;
        case NET_TYPE_DYNAMIC_BONES:                              move_bonesnet(     net);                    break;
        case NET_TYPE_SCALED_VERTICES: if (net->shapePtr != NULL) scale_verts(net->shapePtr->scaledVtxGroup); break;
        case NET_TYPE_JOINTS:                                     move_joints_in_net(net);                    break;
        default: gd_exit(); // Undefined net type
    }
}

/* 241E94 -> 241F0C; orig name: func_801936C4 */
void move_nets(struct ObjGroup *group) {
    apply_to_obj_types_in_group(OBJ_TYPE_NETS, (applyproc_t) func_80192294, group);
    apply_to_obj_types_in_group(OBJ_TYPE_NETS, (applyproc_t) move_net     , group);
}

/* 241F0C -> 242018 */
void func_8019373C(struct ObjNet *net) {
    register struct ListNode *link;
    struct ObjVertex *vtx;
    if ((net->netType == NET_TYPE_SCALED_VERTICES) && (net->shapePtr != NULL)) {
        net->shapePtr->scaledVtxGroup = make_group(0);
        for ((link = net->shapePtr->vtxGroup->firstMember); (link != NULL); (link = link->next)) {
            vtx = (struct ObjVertex *) link->obj;
            if (vtx->scaleFactor != 1.0f) addto_group(net->shapePtr->scaledVtxGroup, &vtx->header);
        }
    }
}

/* 242018 -> 24208C */
void func_80193848(struct ObjGroup *group) {
    apply_to_obj_types_in_group(OBJ_TYPE_NETS, (applyproc_t) reset_net    , group);
    apply_to_obj_types_in_group(OBJ_TYPE_NETS, (applyproc_t) func_80192294, group);
    apply_to_obj_types_in_group(OBJ_TYPE_NETS, (applyproc_t) func_801922FC, group);
    apply_to_obj_types_in_group(OBJ_TYPE_NETS, (applyproc_t) func_8019373C, group);
}

/* 2422E0 -> 2422F8; orig name: func_80193B10 */
void reset_net_count(void) {
    sNetCount = 0;
}
