#include <PR/ultratypes.h>

#include "draw_objects.h"
#include "dynlist_proc.h"
#include "dynlists/dynlists.h"
#include "gd_main.h"
#include "engine/math_util.h"
#include "joints.h"
#include "objects.h"
#include "particles.h"
#include "renderer.h"
#include "shape_helper.h"
#include "skin.h"

// data
struct        ObjGroup *gMarioFaceGrp       = NULL; // @ 801A82E0; returned by load_dynlist
struct        ObjShape *gSpotShape          = NULL;  // Shape used for drawing lights?
static struct ObjShape *sGrabJointTestShape = NULL; // Test shape for showing grab joints. This isn't rendered due to make_grabber_joint setting the drawFlags to OBJ_INVISIBLE.
struct        ObjShape *gShapeRedSpark      = NULL; // @ 801A82EC
struct        ObjShape *gShapeSilverSpark   = NULL; // @ 801A82F0
struct        ObjShape *gShapeRedStar       = NULL; // @ 801A82F4
struct        ObjShape *gShapeSilverStar    = NULL; // @ 801A82F8
static struct ObjShape *sGdShapeListHead;           // @ 801BAC50
static             u32  sGdShapeCount;              // @ 801BAC54

/**
 * Computes the normal vector for a face based on three of its vertices.
 */
void calc_face_normal(struct ObjFace *face) {
    Vec3f p1, p2, p3;
    Vec3n normal;
    struct ObjVertex *vtx1;
    struct ObjVertex *vtx2;
    struct ObjVertex *vtx3;
    // f32 mul = 1000.0f;
    if (face->vtxCount >= 3) {  // need at least three points to compute a normal
        vtx1  = face->vertices[0];
        vec3_copy(p1, vtx1->pos);
        vtx2  = face->vertices[1];
        vec3_copy(p2, vtx2->pos);
        vtx3  = face->vertices[2];
        vec3_copy(p3, vtx3->pos);
        // calculate the cross product of edges (p2 - p1) and (p3 - p2)
        find_vector_perpendicular_to_plane(normal, p1, p2, p3);
        // not sure why each component is multiplied by 1000. maybe to avoid loss of precision when normalizing?
        vec3_mul_val(normal, 1000.0f);
        vec3f_normalize(normal);
        vec3_copy(face->normal, normal);
    }
}

/* @ 245CDC for 0x118 */
struct ObjVertex *gd_make_vertex(Vec3s pos) {
    struct ObjVertex *vtx = (struct ObjVertex *) make_object(OBJ_TYPE_VERTICES);
    vtx->id          = 0xD1D4; //?
    vec3_copy(vtx->pos,     pos);
    vec3_copy(vtx->initPos, pos);
    vtx->scaleFactor = 1.0f;
    vtx->gbiVerts    = NULL;
    vtx->alpha       = 1.0f;
    vec3_copy(vtx->normal, gVec3fY);
    return vtx;
}

/* @ 245DF4 for 0xAC */
struct ObjFace *make_face_with_colour(ColorRGBf color) {
    struct ObjFace *newFace = (struct ObjFace *) make_object(OBJ_TYPE_FACES);
    vec3_copy(newFace->colour, color);
    newFace->vtxCount =  0;
    newFace->mtlId    = -1;
    newFace->mtl      = NULL;
    return newFace;
}

/* @ 245F94 for 0x78; orig name: func_801977C4 */
void add_3_vtx_to_face(struct ObjFace *face, struct ObjVertex *vtx1, struct ObjVertex *vtx2, struct ObjVertex *vtx3) {
    face->vertices[0] = vtx1;
    face->vertices[1] = vtx2;
    face->vertices[2] = vtx3;
    face->vtxCount    = 3;
    calc_face_normal(face);
}

/**
 * Creates an `ObjShape` object
 */
struct ObjShape *make_shape(UNUSED const char *name) {
    struct ObjShape *newShape;
    struct ObjShape *curShapeHead;
    newShape = (struct ObjShape *) make_object(OBJ_TYPE_SHAPES);
    // gd_strcpy(newShape->name, (name != NULL) ? name : "x");
    sGdShapeCount++;
    curShapeHead     = sGdShapeListHead;
    sGdShapeListHead = newShape;
    if (curShapeHead != NULL) {
        newShape->nextShape     = curShapeHead;
        curShapeHead->prevShape = newShape;
    }
    newShape->id         = sGdShapeCount;
    newShape->flag       = 0;
    newShape->vtxCount   = 0;
    newShape->faceCount  = 0;
    newShape->dlNums[0]  = 0;
    newShape->dlNums[1]  = 0;
    newShape->cullFaces  = FALSE;
    newShape->faceGroup  = NULL; /* whoops, NULL-ed twice */
    newShape->alpha      = 1.0f;
    newShape->vtxGroup   = NULL;
    newShape->faceGroup  = NULL;
    newShape->mtlGroup   = NULL;
    // newShape->connectVerts = FALSE; // unused
    newShape->frameIndex = 0;
    return newShape;
}

/**
 * Controls the dizzy (game over) animation of Mario's head.
 */
void animate_mario_head_gameover(struct ObjAnimator *self) {
    switch (self->state) {
        case 0:
            self->frame = 1.0f;
            self->animSeqNum = 1;  // game over anim sequence
            self->state = 1;
            break;
        case 1:
            self->frame += 1.0f;
            // After the gameover animation ends, switch to the normal animation
            if (self->frame == 166.0f) {
                self->frame = 69.0f;
                self->state = 4;
                self->controlFunc = animate_mario_head_normal;
                self->animSeqNum = 0;  // normal anim sequence
            }
            break;
    }
}

/**
 * Controls the normal animation of Mario's head. This functions like a state machine.
 */
void animate_mario_head_normal(struct ObjAnimator *self) {
    s32 state = 0; // TODO: label these states
    Bool32 aBtnPressed = gGdCtrl.dragging;
    switch (self->state) {
        case 0:
            // initialize?
            self->frame      = 1.0f;
            self->animSeqNum = 0;  // normal anim sequence
            state            = 2;
            self->nods       = 5;
            break;
        case 2:
            if (aBtnPressed) state = 5;
            self->frame += 1.0f;
            if (self->frame == 810.0f) {
                self->frame = 750.0f;
                self->nods--;
                if (self->nods == 0) state = 3;
            }
            break;
        case 3:
            self->frame += 1.0f;
            if (self->frame == 820.0f) {
                self->frame = 69.0f;
                state       = 4;
            }
            break;
        case 4:
            self->frame += 1.0f;
            if (self->frame == 660.0f) {
                self->frame = 661.0f;
                state       = 2;
                self->nods  = 5;
            }
            break;
        case 5:
            if (self->frame == 660.0f) {
                state = 7;
            } else if (self->frame > 660.0f) {
                self->frame -= 1.0f;
            } else if (self->frame < 660.0f) {
                self->frame += 1.0f;
            }
            self->stillTimer = 150;
            break;
        case 7:  // Mario is staying still while his eyes follow the cursor
            if (aBtnPressed) {
                self->stillTimer = 300;
            } else {
                self->stillTimer--;
                if (self->stillTimer == 0) state = 6;
            }
            self->frame = 660.0f;
            break;
        case 6:
            state      = 2;
            self->nods = 5;
            break;
    }
    if (state != 0) self->state = state;
}

/**
 * Loads the Mario head from `dynlist_mario_master`, sets up grabbers, and makes
 * sparkle particles
 */
s32 load_mario_head(void (*aniFn)(struct ObjAnimator *)) {
    struct ObjNet      *net;          // net made with jointGrp group
    struct ObjGroup    *jointGrp;     // Joint group
    struct ObjGroup    *mainShapesGrp;
    struct GdObj       *objList;      // object list head before making a bunch of joints
    struct GdObj       *faceJoint;    // joint on the face that `grabberJoint` pulls
    struct ObjJoint    *grabberJoint; // joint that's dragged by the cursor
    struct ObjCamera   *camera;
    struct ObjAnimator *animator;
    struct ObjParticle *particle;
    // Load Mario head from the dynlist
    d_set_name_suffix("l");  // add "l" to the end of all dynobj names generated by the dynlist, for some reason
    d_use_integer_names(TRUE);
    animator = (struct ObjAnimator *) d_makeobj(D_ANIMATOR, AsDynName(DYNOBJ_MARIO_MAIN_ANIMATOR));
    animator->controlFunc = aniFn;
    d_use_integer_names(FALSE);
    // FIXME: make segment address work once seg4 is disassembled
    gMarioFaceGrp = (struct ObjGroup *) load_dynlist(dynlist_mario_master);
    // Make camera
    camera = (struct ObjCamera *) d_makeobj(D_CAMERA, NULL);
    d_set_rel_pos(  0.0f, 200.0f, 2000.0f);
    d_set_world_pos(0.0f, 200.0f, 2000.0f);
    d_set_flags(4);
    vec3_set(camera->lookAt, 0.0f, 200.0f, 0.0f);
    addto_group(gMarioFaceGrp, &camera->header);
    addto_group(gMarioFaceGrp, &animator->header);
    d_set_name_suffix(NULL); // stop adding "l" to generated dynobj names
    // Make sparkle particles
    particle = make_particle(GD_PARTICLE_FLAGS_NONE, COLOUR_WHITE, gVec3fZero);
    particle->particleType          = 3;
    particle->type                  = 3;
    particle->attachedToObj         = &camera->header;
    particle->shapePtr              = gShapeSilverSpark;
    addto_group(gGdLightGroup, &particle->header);
    particle = make_particle(GD_PARTICLE_FLAGS_NONE, COLOUR_WHITE, gVec3fZero);
    particle->particleType          = 3;
    particle->type                  = 2;
    particle->attachedToObj         = d_use_obj("N228l"); // DYNOBJ_SILVER_STAR_LIGHT
    particle->shapePtr              = gShapeSilverSpark;
    addto_group(gGdLightGroup, &particle->header);
    particle = make_particle(GD_PARTICLE_FLAGS_NONE, COLOUR_RED,   gVec3fZero);
    particle->particleType          = 3;
    particle->type                  = 2;
    particle->attachedToObj         = d_use_obj("N231l"); // DYNOBJ_RED_STAR_LIGHT
    particle->shapePtr              = gShapeRedSpark;
    addto_group(gGdLightGroup, &particle->header);
    mainShapesGrp                   = (struct ObjGroup *) d_use_obj("N1000l"); // DYNOBJ_MARIO_MAIN_SHAPES_GROUP
    create_gddl_for_shapes(mainShapesGrp);
    objList                         = gGdObjectList;
    // Make grabbers to move the face with the cursor
    grabberJoint                    = make_grabber_joint(sGrabJointTestShape, 0, -500.0f,   0.0f, -150.0f);
    faceJoint                       = d_use_obj("N167l"); // DYNOBJ_MARIO_LEFT_EAR_JOINT_1
    grabberJoint->attachedObjsGrp   = make_group(1, faceJoint);
    grabberJoint                    = make_grabber_joint(sGrabJointTestShape, 0, 500.0f,    0.0f, -150.0f);
    faceJoint                       = d_use_obj("N176l"); // DYNOBJ_MARIO_RIGHT_EAR_JOINT_1
    grabberJoint->attachedObjsGrp   = make_group(1, faceJoint);
    grabberJoint                    = make_grabber_joint(sGrabJointTestShape, 0,    0.0f, 700.0f,  300.0f);
    faceJoint                       = d_use_obj("N131l"); // DYNOBJ_MARIO_CAP_JOINT_1
    grabberJoint->attachedObjsGrp   = make_group(1, faceJoint);
    // drag eyelids and eyebrows along with cap?
    faceJoint                       = d_use_obj("N206l"); // DYNOBJ_LEFT_EYELID_JOINT_1
    addto_group(grabberJoint->attachedObjsGrp, faceJoint);
    faceJoint                       = d_use_obj("N215l"); // DYNOBJ_RIGHT_EYELID_JOINT_1
    addto_group(grabberJoint->attachedObjsGrp, faceJoint);
    faceJoint                       = d_use_obj("N31l");  // DYNOBJ_MARIO_LEFT_EYEBROW_MPART_JOINT_1
    addto_group(grabberJoint->attachedObjsGrp, faceJoint);
    faceJoint                       = d_use_obj("N65l");  // DYNOBJ_MARIO_RIGHT_EYEBROW_MPART_JOINT_1
    addto_group(grabberJoint->attachedObjsGrp, faceJoint);
    grabberJoint                    = make_grabber_joint(sGrabJointTestShape, 0,    0.0f,    0.0f, 600.0f);
    faceJoint                       = d_use_obj("N185l"); // DYNOBJ_MARIO_NOSE_JOINT_1
    grabberJoint->attachedObjsGrp   = make_group(1, faceJoint);
    grabberJoint                    = make_grabber_joint(sGrabJointTestShape, 0,    0.0f, -300.0f, 300.0f);
    faceJoint                       = d_use_obj("N194l");  // DYNOBJ_MARIO_LEFT_JAW_JOINT
    grabberJoint->attachedObjsGrp   = make_group(1, faceJoint);
    grabberJoint                    = make_grabber_joint(sGrabJointTestShape, 0,  250.0f, -150.0f, 300.0f);
    faceJoint                       = d_use_obj("N158l"); // DYNOBJ_MARIO_RIGHT_LIP_CORNER_JOINT_1
    grabberJoint->attachedObjsGrp   = make_group(1, faceJoint);
    faceJoint                       = d_use_obj("N15l");  // DYNOBJ_MARIO_LEFT_MUSTACHE_JOINT_1
    addto_group(grabberJoint->attachedObjsGrp, faceJoint);
    grabberJoint                    = make_grabber_joint(sGrabJointTestShape, 0, -250.0f, -150.0f, 300.0f);
    faceJoint                       = d_use_obj("N149l"); // DYNOBJ_MARIO_LEFT_LIP_CORNER_JOINT_1
    grabberJoint->attachedObjsGrp   = make_group(1, faceJoint);
    faceJoint                       = d_use_obj("N6l"  ); // DYNOBJ_MARIO_RIGHT_MUSTACHE_JOINT_1
    addto_group(grabberJoint->attachedObjsGrp, faceJoint);
    // make the left eye follow cursor
    grabberJoint                    = make_grabber_joint(sGrabJointTestShape, 0,  100.0f,  200.0f, 400.0f);
    faceJoint                       = d_use_obj("N112l"); // DYNOBJ_MARIO_RIGHT_EYE_UNKNOWN_NET
    grabberJoint->attachedObjsGrp   = make_group(1, faceJoint);
    grabberJoint->updateFunc        = eye_joint_update_func;
    grabberJoint->rootAnimator      = animator;
    grabberJoint->header.drawFlags &= ~OBJ_IS_GRABBALE;
    // make the right eye follow cursor
    grabberJoint                    = make_grabber_joint(sGrabJointTestShape, 0, -100.0f,  200.0f, 400.0f);
    faceJoint                       = d_use_obj("N96l" ); // DYNOBJ_MARIO_LEFT_EYE_UNKNOWN_NET
    grabberJoint->attachedObjsGrp   = make_group(1, faceJoint);
    grabberJoint->updateFunc        = eye_joint_update_func;
    grabberJoint->rootAnimator      = animator;
    grabberJoint->header.drawFlags &= ~OBJ_IS_GRABBALE;
    jointGrp                        = make_group_of_type(OBJ_TYPE_JOINTS, objList);
    net                             = make_net(jointGrp);
    net->netType                    = NET_TYPE_JOINTS;
    addto_group(gMarioFaceGrp, &jointGrp->header);
    addto_groupfirst(gMarioFaceGrp, &net->header);
    return 0;
}

/* @ 249288 for 0xe0 */
void load_shapes2(void) {
    sGdShapeCount    = 0;
    sGdShapeListHead = NULL;
    gGdLightGroup    = make_group(0);
}
