#ifndef GD_TYPES_H
#define GD_TYPES_H

#include <PR/ultratypes.h>
#include <ultra64.h>
#include "types.h"

struct GdBoundingBox {
    f32 minX, minY, minZ;
    f32 maxX, maxY, maxZ;
};

struct GdTriangleF {
    Vec3f p0, p1, p2;
};

struct GdAnimTransform {
    Vec3f scale;
    Vec3f rotate;  // each component specifies the degrees to rotate about that axis
    Vec3f pos;
};

/* dynlist entries and types */
union DynUnion {
    void *ptr;
    char *str;
    s32 word;
};

struct DynList {
    s32 cmd;
    union DynUnion w1;
    union DynUnion w2;
    Vec3f vec;
};

/* Goddard Code Object Structs */
/* Object Type Flags */
enum ObjTypeFlag {
    OBJ_TYPE_GROUPS    = (1 <<  0), // 0x00000001,
    OBJ_TYPE_BONES     = (1 <<  1), // 0x00000002, // unused
    OBJ_TYPE_JOINTS    = (1 <<  2), // 0x00000004,
    OBJ_TYPE_PARTICLES = (1 <<  3), // 0x00000008,
    OBJ_TYPE_SHAPES    = (1 <<  4), // 0x00000010,
    OBJ_TYPE_NETS      = (1 <<  5), // 0x00000020,
    OBJ_TYPE_PLANES    = (1 <<  6), // 0x00000040, // unused
    OBJ_TYPE_FACES     = (1 <<  7), // 0x00000080,
    OBJ_TYPE_VERTICES  = (1 <<  8), // 0x00000100,
    OBJ_TYPE_CAMERAS   = (1 <<  9), // 0x00000200,
    OBJ_TYPE_UNUSED_10 = (1 << 10), // 0x00000400, // unused
    OBJ_TYPE_MATERIALS = (1 << 11), // 0x00000800,
    OBJ_TYPE_WEIGHTS   = (1 << 12), // 0x00001000,
    OBJ_TYPE_GADGETS   = (1 << 13), // 0x00002000, // unused
    OBJ_TYPE_VIEWS     = (1 << 14), // 0x00004000,
    OBJ_TYPE_LABELS    = (1 << 15), // 0x00008000,
    OBJ_TYPE_ANIMATORS = (1 << 16), // 0x00010000,
    OBJ_TYPE_VALPTRS   = (1 << 17), // 0x00020000,
    OBJ_TYPE_UNUSED_18 = (1 << 18), // 0x00040000, // unused
    OBJ_TYPE_LIGHTS    = (1 << 19), // 0x00080000,
    OBJ_TYPE_ZONES     = (1 << 20), // 0x00100000, // unused
    OBJ_TYPE_UNUSED_21 = (1 << 21), // 0x00200000  // unused
};
/* This constant seems to be used to indicate the type of any or all objects */
#define OBJ_TYPE_ALL 0x00FFFFFF


/// Function pointer for a `GdObj`'s drawing routine
typedef void (*drawmethod_t)(void *);
/// Flags for the drawFlags field of an GdObj
enum ObjDrawingFlags {
    OBJ_DRAW_UNK01  = (1 << 0), // 0x01,
    OBJ_INVISIBLE   = (1 << 1), // 0x02, ///< This `GdObj` shouldn't be drawn when updating a scene
    OBJ_PICKED      = (1 << 2), // 0x04, ///< This `GdObj` is held by the cursor
    OBJ_IS_GRABBALE = (1 << 3), // 0x08, ///< This `GdObj` can be grabbed/picked by the cursor
    OBJ_HIGHLIGHTED = (1 << 4)  // 0x10
};

/**
 * The base of structure of all of Goddard's objects. It is present as a "header"
 * at the beginning of all `ObjX` structures, and as such, this type is used
 * when we need to generalize code to take different `ObjX`es.
 * Every GdObj created is connected together in a linked list with `prev` and `next` pointers.
 */
struct GdObj {
    /* 0x00 */ struct GdObj *prev;      // previous node in gGdObjectList linked list
    /* 0x04 */ struct GdObj *next;      // next node in gGdObjectList linked list
    /* 0x08 */ drawmethod_t objDrawFn;
    /* 0x0C */ enum ObjTypeFlag type;
    /* 0x10 */ s16 index;               ///< the index of this `GdObj` in the linked list
    /* 0x12 */ u16 drawFlags;           ///< enumerated in `::ObjDrawingFlags`
    /* 0x14 Specific object data starts here  */
};

/* Used to create a linked list of objects (or data)
** within an ObjGroup */
struct ListNode {
    /* 0x00 */ struct ListNode *prev;
    /* 0x04 */ struct ListNode *next;
    /* 0x08 */ struct GdObj    *obj;
};

// I think this is actually the same type as ListNode, and data is just a generic "void *" pointer.
struct VtxLink {
    struct VtxLink *prev;
    struct VtxLink *next;
    Vtx *data;
};

/* These are the compressed versions of ObjFace or ObjVertex that are
** pointed to by ListNode in the faceGroup and vtxGroup, if Group.linkType
** is set to 0x01. See `chk_shapegen` */
struct GdFaceData {
    u32 count;
    s32 type;
    u16 (*data)[4]; ///< (mtl id, vtx ids[3])
};

struct GdVtxData {
    u32 count;
    s32 type;
    s16 (*data)[3]; ///< [x, y, z]
};


/**
 * Used to group related objects together. Seems to mainly be used for `apply_to_obj_types_in_group`.
 */
struct ObjGroup {
    /* 0x00 */ struct GdObj header;
    /* 0x14 */ struct ObjGroup *prev;
    /* 0x18 */ struct ObjGroup *next;
    /* 0x1C */ struct ListNode *firstMember;            ///< Head of a linked list for objects contained in this group
    /* 0x20 */ struct ListNode *lastMember;             ///< Tail of a linked list for objects contained in this group
    /* 0x24 */ s32 memberTypes;                         ///< OR'd collection of type flags for all objects in this group
    /* 0x28 */ s32 memberCount;                         // number of objects in this group
    /* 0x2C */ s32 debugPrint;                          // might also be a type?
    /* 0x30 */ s32 linkType;
    /* 0x34 */ char name[0x40];                         ///< possibly, only referenced in old code
    /* 0x74 */ s32 id;
}; /* sizeof = 0x78 */

#define JOINT_FLAG_GRABBED (1 << 13) // 0x2000

struct ObjJoint {
    /* 0x000 */ struct GdObj header;
    /* 0x014 */ Vec3f worldPos;                         // position in world space
    /* 0x020 */ struct ObjShape *shapePtr;
    /* 0x024 */ struct ObjJoint *prevjoint;             // prev joint? linked joint?
    /* 0x028 */ struct ObjJoint *nextjoint;
    /* 0x02C */ void (*updateFunc)(struct ObjJoint*);   // seems to update attached objects? see grabbable_joint_update_func
    /* 0x030 */ Vec3f pos;                              // huge array of vecs? another matrix?
    /* 0x03C */ Vec3f relPos;                           // relative position?
    /* 0x048 */ Vec3f nextPos;
    /* 0x054 */ Vec3f initPos;                          // attached offset? (with +200 as well)
    /* 0x060 */ u8    pad60[0x6C-0x60];
    /* 0x06C */ Vec3f initRotation;                     // initial rotation vec
    /* 0x078 */ Vec3f velocity;
    /* 0x084 */ Vec3f unk84;                            // Set to 0 and unused?
    /* 0x090 */ Vec3f unk90;                            // Set to 0 and unused?
    /* 0x09C */ Vec3f scale;
    /* 0x0A8 */ Vec3f unkA8;                            // unused
    /* 0x0B4 */ Vec3f unkB4;                            // unused
    /* 0x0C0 */ Vec3f shapeOffset;
    /* 0x0CC */ Vec3f unkCC;                            // unused
    /* 0x0D8 */ u8    padD8[4];
    /* 0x0DC */ Vec3f friction;
    /* 0x0E8 */ Mat4 invMtx;                            // matrix4x4
    /* 0x128 */ Mat4 rotationMtx;                       // "rot matrix"
    /* 0x168 */ Mat4 idMtx;                             // "id matrix"
    /* 0x1A8 */ Vec3f unk1A8;                           // set to 0 and unused
    /* 0x1B4 */ s32  id;
    /* 0x1B8 */ u8   pad1B8[4];
    /* 0x1BC */ s32  flags;                             // "flags" - 0x2000 = grabbed
    /* 0x1C0 */ s32  unk1C0;                            // unused
    /* 0x1C4 */ struct ObjGroup *unk1C4;                // bone group? unused
    /* 0x1C8 */ s32 colourNum;
    /* 0x1CC */ s32 type;                               // 0 = normal joint, 5 = grabbable joint. seems to be set, but never used
    /* 0x1D0 */ struct ObjAnimator *rootAnimator;       // root animator? used by eye_joint_update_func
    /* 0x1D4 */ u8  pad1D4[0x1f4-0x1d4];
    /* 0x1F4 */ struct ObjGroup *weightGrp;             // Group of ObjWeights, only? skin weights?
    /* 0x1F8 */ struct ObjGroup *attachedObjsGrp;       // attach object group
    /* 0x1FC */ s32 attachFlags;                        // d_attach_to arg 0; "AttFlag"
    /* 0x200 */ Vec3f attachOffset;
    /* 0x20C */ struct GdObj *attachedToObj;            // object that this object is attached to
    /* 0x210 */ u8  pad210[0x228-0x210];
    /* 0x228 */ f32 unk228;                             // unused
}; /* sizeof = 0x22C */

/* Particle Types (+60)
   3 = Has groups of other particles in 6C?
*/

#define GD_PARTICLE_FLAGS_NONE  (0 << 0)
#define GD_PARTICLE_FLAG_1      (1 << 0)
#define GD_PARTICLE_FLAG_2      (1 << 1)
#define GD_PARTICLE_FLAG_4      (1 << 2)
#define GD_PARTICLE_FLAG_8      (1 << 3)
#define GD_PARTICLE_FLAG_A      (1 << 4)
#define GD_PARTICLE_FLAG_B      (1 << 5)

struct ObjParticle {
    /* 0x00 */ struct GdObj header;
    /* 0x14 */ u8 pad14[0x1C-0x14];
    /* 0x1C */ struct ObjShape *shapePtr;           // looks like a shape...
    /* 0x20 */ Vec3f pos;                           // some kind of position - relative? world?
    /* 0x2C */ u8  pad2C[0x30-0x2C];
    /* 0x30 */ f32 unk30;                           // unused
    /* 0x34 */ u8  pad34[0x38-0x34];
    /* 0x38 */ Vec3f vel;                           // velocity?
    /* 0x44 */ f32 unk44;                           // not vec? unused
    /* 0x48 */ f32 unk48;                           // not vec? unused
    /* 0x4C */ u8  pad4C[0x50-0x4C];
    /* 0x50 */ s32 id;
    /* 0x54 */ u32 flags;                           // "dflags"?
    /* 0x58 */ s32 colourNum;
    /* 0x5C */ s32 timeout;                         // when this reaches zero, the particle disappears
    /* 0x60 */ s32 particleType;
    /* 0x64 */ s32 type;                            // type? (1 = has 50 sub-particles, 2,3 = has 30 sub-particles
    /* 0x68 */ u8  pad68[0x6C-0x68];
    /* 0x6C */ struct ObjGroup *subParticlesGrp;    // group of other Particles ?
    /* 0x70 */ u8  pad70[4];
    /* 0x74 */ s32 unk74;                           // unused
    /* 0x78 */ u8  unk78[4];
    /* 0x7C */ struct ObjAnimator *unk7C;           // unused. guessing on type; doesn't seem to be used in final code
    /* 0x80 */ struct ObjLight *objLight;           // could be a Net or Light; not seen as non-null in running code
    /* 0x84 */ u8 pad84[0xB0-0x84];
    /* 0xB0 */ s32 state;                           // state?
    /* 0xB4 */ struct ObjGroup *attachedObjsGrp;    // attach group? unused group of particles
    /* 0xB8 */ s32 attachFlags;                     // attached arg0; "AttFlag"
    /* 0xBC */ struct GdObj *attachedToObj;         // object that this object is attached to. looks like can be a Light or Camera
}; /* sizeof = 0xC0 */

/**
 * An object that represents the visual portion of a 3D model.
 */
struct ObjShape {
    /* 0x00 */ struct GdObj header;
    /* 0x14 */ struct ObjShape *prevShape;
    /* 0x18 */ struct ObjShape *nextShape;
    /* 0x1C */ struct ObjGroup *faceGroup;          /* face group; based on get_3DG1_shape */
    /* 0x20 */ struct ObjGroup *vtxGroup;           /* vtx group; based on get_3DG1_shape */
    /* 0x24 */ struct ObjGroup *scaledVtxGroup;     /* group for type 2 shapenets only ? vertices whose scaleFactor is not 1 get put into this group. */
    /* 0x28 */ u8  pad28[4];
    /* 0x2C */ struct ObjGroup *mtlGroup;           /* what does this group do? materials? */
    /* 0x30 */ Bool32 connectVerts;
    /* 0x34 */ s32 faceCount;                       /* face count? based on get_3DG1_shape */
    /* 0x38 */ s32 vtxCount;                        /* vtx count? based on get_3DG1_shape */
    /* 0x3C */ Bool32 cullFaces;                    // bool? if FALSE, then draw_shape_faces(shape)
    /* 0x40 */ u32 id;
    /* 0x44 */ s32 flag;                            // what are the flag values? only from dynlists?
    /* 0x48 */ s32 dlNums[2];                       // gd dl number for each frame buffer (??) [0, 1]
               s32 frameIndex;                      // frame number (index into dlNums)?
    /* 0x54 */ u8  pad54[0x58-0x54];                // part of above array??
    /* 0x58 */ AlphaF alpha;                        // paramF? opacitiy? something with rendertype
    /* 0x5C */ char name[0x40];
}; /* sizeof = 0x9C */

/* 0x44 Flag Values
 * 0x01 -
 * 0x10 - Use vtx position as vtx normal? (`chk_shapegen`)
 */

/* netTypes
 * 0 - default?
 * 1 - shape net
 * 2 - something about the shape unk24 group having vertices too?
 * 3 - joints?
 * 4 - dynamic net? bone net?
 * 5 - particle net?
 * 6 - stub
 * 7 -
 */
#define NET_TYPE_DEFAULT            0x0
#define NET_TYPE_SHAPE              0x1
#define NET_TYPE_SCALED_VERTICES    0x2
#define NET_TYPE_JOINTS             0x3
#define NET_TYPE_DYNAMIC_BONES      0x4
#define NET_TYPE_PARTICLES          0x5

struct ObjNet {
    /* 0x000 */ struct GdObj header;
    /* 0x014 */ Vec3f worldPos;                     // position? d_set_initpos + d_set_world_pos; print_net says world
    /* 0x020 */ Vec3f initPos;                      // position? d_set_initpos? attached offset? dynamic? scratch?
    /* 0x02C */ u8    pad2c[0x34-0x2C];
    /* 0x034 */ s32   flags;                        // "dflags"?
    /* 0x038 */ u32   id;                           // some sort of id? from move_net
    /* 0x03C */ s32   unk3C;                        // state flags? vertex info flags? unused
    /* 0x040 */ s32   colourNum;
    /* 0x044 */ Vec3f unusedForce;                  // "force" (unused)
    /* 0x050 */ Vec3f velocity;
    /* 0x05C */ Vec3f rotation;                     // unused
    /* 0x068 */ Vec3f initRotation;                 // initial rotation?
    /* 0x074 */ Vec3f collDisp;                     // what is this?
    /* 0x080 */ Vec3f collTorque;                   // what is this?
    /* 0x08C */ Vec3f unusedCollTorqueL;            // unused
    /* 0x098 */ Vec3f unusedCollTorqueD;            // unused
    /* 0x0A4 */ Vec3f torque;                       // torque, unused
    /* 0x0B0 */ Vec3f centerOfGravity;              // "CofG" center of gravity?
    /* 0x0BC */ struct GdBoundingBox boundingBox;
    /* 0x0D4 */ Vec3f unusedCollDispOff;            // unused
    /* 0x0E0 */ f32   unusedCollMaxD;               // unused
    /* 0x0E4 */ f32   maxRadius;
    /* 0x0E8 */ Mat4  idMtx;
    /* 0x128 */ Mat4  invMtx;
    /* 0x168 */ Mat4  rotationMtx;                  // "rotation matrix"
    /* 0x1A8 */ struct ObjShape *shapePtr;
    /* 0x1AC */ Vec3f scale;
    /* 0x1B8 */ f32   unusedMass;                   // unused
    /* 0x1BC */ s32   numModes;                     // unused
    /* 0x1C0 */ struct ObjGroup *unk1C0;            // group of `ObjVertex` or `ObjParticle`. unused
    /* 0x1C4 */ struct ObjGroup *skinGrp;           // SkinGroup (from reset_weight) (joints and bones)
    /* 0x1C8 */ struct ObjGroup *nodeGrp;           // "node group" (joints, weights?)
    /* 0x1CC */ struct ObjGroup *faceGroup;         // plane group (only type 1?)
    /* 0x1D0 */ struct ObjGroup *vertexGrp;         // vertex group
    /* 0x1D4 */ struct ObjGroup *attachedObjsGrp;
    /* 0x1D8 */ Vec3f attachOffset;
    /* 0x1E4 */ s32   attachFlags;                  // d_attach_to arg 0; "AttFlag"
    /* 0x1E8 */ struct GdObj *attachedToObj;        // object that this object is attached to
    /* 0x1EC */ s32   netType;                      // from move_net
    /* 0x1F0 */ struct ObjNet *unk1F0;              // or joint. guess from Unknown80192AD0. unused
    /* 0x1F4 */ Vec3f unk1F4;                       // unused
    /* 0x200 */ Vec3f unk200;                       // unused
    /* 0x20C */ struct ObjGroup *unk20C;            // unused
    /* 0x210 */ s32 ctrlType;                       // has no purpose
}; /* sizeof = 0x220 */

struct ObjVertex {
    /* 0x00 */ struct GdObj header;
    /* 0x14 */ Vec3f initPos;
    /* 0x20 */ Vec3f pos;                           // new position after being moved by joints?
    /* 0x2C */ Vec3n normal;                        // normal? also color (like gbi?)
    /* 0x38 */ s16 id;
    /* 0x3C */ f32 scaleFactor;
    /* 0x40 */ f32 alpha;
    /* 0x44 */ struct VtxLink *gbiVerts;
}; /* sizeof = 0x48 */

/**
 * An object that represents a face in an `ObjShape`. It connects 3 or 4 vertices.
 */
struct ObjFace {
    /* 0x00 */ struct GdObj header;
    /* 0x14 */ ColorRGBf colour;
    /* 0x20 */ s32 colourNum;                       // "colour" index
    /* 0x24 */ Vec3n normal;
    /* 0x30 */ s32 vtxCount;
    /* 0x34 */ struct ObjVertex *vertices[4];       // these can also be s32 indices? which are then replaced by `find_thisface_verts`
    /* 0x44 */ s32 mtlId;                           // from compressed GdFaceData; -1 == coloured face?
    /* 0x48 */ struct ObjMaterial *mtl;             // initialize to NULL; set by `map_face_materials` from mtlId
}; /* sizeof = 0x4C */

#define CAMERA_FLAG_CONTROLLABLE (1 << 2) // 0x04
#define CAMERA_FLAG_16           (1 << 4) // 0x10

struct ObjCamera {
    /* 0x000 */ struct GdObj header;
    /* 0x014 */ Vec3f worldPos;                     // position vec? from d_set_initpos
    /* 0x020 */ struct ObjCamera* prev;
    /* 0x024 */ struct ObjCamera* next;
    /* 0x028 */ s32 id;
    /* 0x02C */ s32 flags;                          // flag of some sort
    /* 0x030 */ struct GdObj* dynObj;               // pointer to some type of object
    /* 0x034 */ Vec3f lookAt;                       // point that the camera faces
    /* 0x040 */ Vec3f relPos;                       // relative position related?
    /* 0x04C */ Vec3f curZoomPosition;
    /* 0x058 */ Vec3f unk58;
    /* 0x064 */ Mat4 idMtx;                         // matrix4x4
    /* 0x0A4 */ f32  colXY;
    /* 0x0A8 */ Mat4 transformMtx;                  // matrix4x4, multiplied to nextPos in move_camera
    /* 0x0E8 */ Mat4 lookatMtx;
    /* 0x128 */ Vec3f rotationAngle;
    /* 0x134 */ Vec3f rotationSpeeds;
    /* 0x140 */ Vec3f zoomPositions[4];             // zoom positions (*1, *1.5, *2, empty fourth)
    /* 0x170 */ s32 maxZoomLevel;                   // max number of zoom positions
    /* 0x174 */ s32 zoomLevel;                      // index into zoomPositions array
    /* 0x178 */ f32 unk178;                         // set to 0 and unused
    /* 0x17C */ f32 multiplier;                     // always 0.25
    /* 0x180 */ Vec3f unk180;                       // unused. only [1] wass used, 1.0f, 0.1f, 1.0f
    /* 0x18C */ struct ObjView *unk18C;             // view that has/is using this camera?
}; /* sizeof = 0x190 */

enum GdMtlTypes {
    GD_MTL_STUB_DL  = (1 << 0), // 0x01,
    GD_MTL_BREAK    = (1 << 2), // 0x04,
    GD_MTL_SHINE_DL = (1 << 4), // 0x10,
    GD_MTL_TEX_OFF  = (1 << 5), // 0x20,
    GD_MTL_LIGHTS   = (1 << 6)  // 0x40 // uses default case
};

struct ObjMaterial {
    /* 0x00 */ struct GdObj header;
    /* 0x14 */ u8  pad14[0x1c-0x14];
    /* 0x1C */ s32 id;
    /* 0x20 */ char name[8];
    /* 0x28 */ s32 type;
    /* 0x2C */ u8  pad2C[4];
    /* 0x30 */ ColorRGBf Ka;  // ambient color
    /* 0x3C */ ColorRGBf Kd;  // diffuse color
    /* 0x48 */ u8  pad48[0x58-0x48];
    /* 0x58 */ void *texture;       // set by d_usetexture; never seems to be non-null though.
    /* 0x5C */ s32 gddlNumber;
}; /* sizeof = 0x60 */

struct ObjWeight {
    /* 0x00 */ struct GdObj header;
    /* 0x14 */ u8  pad14[0x8];
    /* 0x1C */ s32 vtxId;               // ID of vertex that this weight applies to
    /* 0x20 */ Vec3f vec20;             // based on func_80181894? maybe a GdBoundingBox?
    /* 0x2C */ u8  pad2C[0x38-0x2c];
    /* 0x38 */ f32 weightVal;           // weight (unit?)
    /* 0x3C */ struct ObjVertex* vtx;
}; /* sizeof = 0x40 */

enum GdViewFlags {
    VIEW_2_COL_BUF      = (1 <<  3), // 0x000008,
    VIEW_ALLOC_ZBUF     = (1 <<  4), // 0x000010,
    VIEW_SAVE_TO_GLOBAL = (1 <<  6), // 0x000040,
    VIEW_DEFAULT_PARENT = (1 <<  8), // 0x000100,
    VIEW_BORDERED       = (1 << 10), // 0x000400,
    VIEW_UPDATE         = (1 << 11), // 0x000800,
    VIEW_UNK_1000       = (1 << 12), // 0x001000, // used in setup_view_buffers
    VIEW_UNK_2000       = (1 << 13), // 0x002000, // only see together with 0x4000
    VIEW_UNK_4000       = (1 << 14), // 0x004000,
    VIEW_COLOUR_BUF     = (1 << 15), // 0x008000,
    VIEW_Z_BUF          = (1 << 16), // 0x010000,
    VIEW_1_CYCLE        = (1 << 17), // 0x020000,
    VIEW_MOVEMENT       = (1 << 18), // 0x040000,
    VIEW_DRAW           = (1 << 19), // 0x080000,
    VIEW_WAS_UPDATED    = (1 << 20), // 0x100000,
    VIEW_LIGHT          = (1 << 21)  // 0x200000
};

struct ObjView {
    /* 0x00 */ struct GdObj header;
    /* 0x14 */ u8  pad14[0x8];
    /* 0x1C */ s32 unk1C;                       // set as nonexistent return of `setup_view_buffers`
    /* 0x20 */ s32 id;
    /* 0x24 */ struct ObjCamera *activeCam;     // is this really active?
    /* 0x28 */ struct ObjGroup *components;     // camera + joints + nets, etc..?
    /* 0x2C */ struct ObjGroup *lights;         // only lights?
    /* 0x30 */ struct GdObj *pickedObj;         // selected with cursor (`update_view`)
    /* 0x34 */ enum GdViewFlags flags;
    /* 0x38 */ s32 projectionType;              // enum? if 1 use guPerspective, if 0 (or 2?) use guOrtho (see `drawscene`)
    /* 0x3C */ Vec3f upperLeft;                 // position vec?
    /* 0x48 */ f32 unk48;                       // what are these? are they another vec?
    /* 0x4C */ f32 unk4C;                       // set to 1 and unused?
    /* 0x50 */ u8  pad50[0x4];
    /* 0x54 */ Vec3f lowerRight;
    /* 0x60 */ Vec3f clipping;                  // z-coordinate of (x: near, y: far) clipping plane?
    /* 0x6C */ const char *namePtr;
    /* 0x70 */ s32 gdDlNum;
    /* 0x74 */ s32 unk74;                       // unused
    /* 0x78 */ s32 unk78;
    /* 0x7C */ ColorRGBf colour;
    /* 0x88 */ struct ObjView *parent;          // maybe not a true parent, but link to buffers in parent?
    /* 0x8C */ void *zbuf;
    /* 0x90 */ void *colourBufs[2];             // frame buffers?
    /* 0x98 */ void (*proc)(struct ObjView *);  // Never non-null in game...?
    /* 0x9C */ s32 unk9C;                       // unused
}; /* sizeof = 0xA0 */

struct ObjAnimator {
    /* 0x00 */ struct GdObj header;
    /* 0x14 */ struct ObjGroup* animatedPartsGrp;           // group containing objects animated by this animator. I think all of them are joints.
    /* 0x18 */ struct ObjGroup* animdataGrp;                // animation data? a group, but the link points to something weird..
    /* 0x1C */ u8  pad1C[0x4];
    /* 0x20 */ s32 animSeqNum;                              // which entry in the AnimDataInfo array to use
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 frame;                                   // key frame number. This is a float so that it can interpolate between key frames, though I think in practice, it's always a whole number.
    /* 0x2C */ u8  pad2C[4];
    /* 0x30 */ struct ObjGroup *attachedObjsGrp;
    /* 0x34 */ s32 attachFlags;                             // attach arg0, not used
    /* 0x38 */ u8  pad38[0x44-0x38];
    /* 0x44 */ struct GdObj* attachedToObj;                 // object that this object is attached to. Normally another Objanimator?
    /* 0x48 */ void (*controlFunc) (struct ObjAnimator *);  // function that "controls" the animation sequence by choosing the frame number
    /* 0x4C */ s32 state;                                   // state enum?
    /* 0x50 */ s32 nods;                                    // Counts the number of nods when Mario is dozing off. When this reaches zero, he wakes up again
    /* 0x54 */ s32 stillTimer;                              // number of frames to remain in the part where Mario's head stays still with his eyes following the cursor
}; /* sizeof = 0x58 */

/* Animation Data Types */
enum GdAnimations {
    GD_ANIM_EMPTY                 = 0x0,  // Listed types are how the data are arranged in memory; maybe not be exact type
    GD_ANIM_MTX4x4                = 0x1,  // f32[4][4]
    GD_ANIM_SCALE3F_ROT3F_POS3F   = 0x2,  // f32[3][3]
    GD_ANIM_SCALE3S_POS3S_ROT3S   = 0x3,  // s16[9]
    GD_ANIM_SCALE3F_ROT3F_POS3F_2 = 0x4,  // f32[3][3]
    GD_ANIM_STUB                  = 0x5,
    GD_ANIM_ROT3S                 = 0x6,  // s16[3]
    GD_ANIM_POS3S                 = 0x7,  // s16[3]
    GD_ANIM_ROT3S_POS3S           = 0x8,  // s16[6]
    GD_ANIM_MTX4x4F_SCALE3F       = 0x9,  // {f32 mtx[4][4]; f32 vec[3];}
    GD_ANIM_CAMERA_EYE3S_LOOKAT3S = 0xB   // s16[6]
};
/* This struct is pointed to by the `obj` field in ListNode struct in the `animdata` ObjGroup */
struct AnimDataInfo {
    s32 count;              // count or -1 for end of array of AnimDataInfo structures
    enum GdAnimations type; // types are used in "move_animator"
    void* data;             // points to an array of `type` data
};
/* GD_ANIM_MTX4x4F_SCALE3F (9) type */
struct AnimMtxVec {
    /* 0x00 */ Mat4 matrix;
    /* 0x40 */ Vec3f vec;  // seems to be a scale vec
};

enum GdLightFlags {
    LIGHT_UNK02         = (1 << 1), // 0x02, // old type of light?
    LIGHT_NEW_UNCOUNTED = (1 << 4), // 0x10,
    LIGHT_UNK20         = (1 << 5)  // 0x20 // new, actually used type of light? used for phong shading?
};

struct ObjLight {
    /* 0x00 */ struct GdObj header;
    /* 0x14 */ u8  pad0[0x8];
    /* 0x1C */ s32 id;
    /* 0x20 */ char name[8];
    /* 0x28 */ u8  pad28[4];
    /* 0x2C */ s32 flags;
    /* 0x30 */ f32 diffuseFac;      // color (5C) = Kd (50) * 30
    /* 0x34 */ u8  pad34[4];
    /* 0x38 */ f32 diffuseTheta;    // calculated diffuse theta (in degrees?)
    /* 0x3C */ s32 unk3C;           // unused
    /* 0x40 */ s32 unk40;           // unused
    /* 0x44 */ u8  pad3[0x8];
    /* 0x4C */ s32 unk4C;           // set to 0 and unused
    /* 0x50 */ ColorRGBf diffuse;
    /* 0x5C */ ColorRGBf colour;
    /* 0x68 */ Vec3f unk68;         // unused
    /* 0x74 */ Vec3f position;
    /* 0x80 */ Vec3f unk80;         // unused
    /* 0x8C */ Vec3f unk8C;         // unused
    /* 0x98 */ s32   unk98;         // unused
    /* 0x9C */ struct ObjShape *shapePtr;
}; /* sizeof = 0xA0 */

#endif // GD_TYPES_H
