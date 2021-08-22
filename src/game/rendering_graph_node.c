#include <PR/ultratypes.h>

#include "area.h"
#include "engine/math_util.h"
#include "game_init.h"
#include "gfx_dimensions.h"
#ifdef METAL_CAP_REFLECTION_LAKITU
#include "level_update.h"
#endif
#include "main.h"
#include "memory.h"
#include "print.h"
#include "rendering_graph_node.h"
#include "shadow.h"
#include "sm64.h"
#include "game_init.h"
#include "engine/extended_bounds.h"
#ifdef PUPPYPRINT
#include "puppyprint.h"
#endif
#include "debug_box.h"

#include "config.h"

#define static

/**
 * This file contains the code that processes the scene graph for rendering.
 * The scene graph is responsible for drawing everything except the HUD / text boxes.
 * First the root of the scene graph is processed when geo_process_root
 * is called from level_script.c. The rest of the tree is traversed recursively
 * using the function geo_process_node_and_siblings, which switches over all
 * geo node types and calls a specialized function accordingly.
 * The types are defined in engine/graph_node.h
 *
 * The scene graph typically looks like:
 * - Root (viewport)
 *  - Master list
 *   - Ortho projection
 *    - Background (skybox)
 *  - Master list
 *   - Perspective
 *    - Camera
 *     - <area-specific display lists>
 *     - Object parent
 *      - <group with 240 object nodes>
 *  - Master list
 *   - Script node (Cannon overlay)
 *
 */

s16  gMatStackIndex;
Mat4 gMatStack[32];
Mtx *gMatStackFixed[32];
f32  aspect;

/**
 * Animation nodes have state in global variables, so this struct captures
 * the animation state so a 'context switch' can be made when rendering the
 * held object.
 */
struct GeoAnimState {
    /*0x00*/ u8 type;
    /*0x01*/ u8 enabled;
    /*0x02*/ AnimFrame16 frame;
    /*0x04*/ f32 translationMultiplier;
    /*0x08*/ u16 *attribute;
    /*0x0C*/ s16 *data;
};

// For some reason, this is a GeoAnimState struct, but the current state consists
// of separate global variables. It won't match EU otherwise.
struct GeoAnimState gGeoTempState;

u8   gCurAnimType;
u8   gCurAnimEnabled;
s16  gCurrAnimFrame;
f32  gCurAnimTranslationMultiplier;
u16 *gCurrAnimAttribute;
s16 *gCurAnimData;

struct AllocOnlyPool *gDisplayListHeap;

struct RenderModeContainer {
    u32 modes[GFX_NUM_MASTER_LISTS];
};

#ifdef SILHOUETTE
/* Rendermode settings for cycle 1 for all 13 layers. */
struct RenderModeContainer renderModeTable_1Cycle[2] = { { {
    G_RM_OPA_SURF,                      // LAYER_FORCE
    G_RM_AA_OPA_SURF,                   // LAYER_OPAQUE
    G_RM_AA_OPA_SURF,                   // LAYER_OPAQUE_INTER
    G_RM_AA_OPA_SURF,                   // LAYER_OPAQUE_DECAL
    G_RM_AA_TEX_EDGE,                   // LAYER_ALPHA
    G_RM_AA_TEX_EDGE | ZMODE_DEC,       // LAYER_ALPHA_DECAL
    G_RM_AA_OPA_SURF,                   // LAYER_SILHOUETTE_OPAQUE
    G_RM_AA_TEX_EDGE,                   // LAYER_SILHOUETTE_ALPHA
    G_RM_AA_OPA_SURF,                   // LAYER_OCCLUDE_SILHOUETTE_OPAQUE
    G_RM_AA_TEX_EDGE,                   // LAYER_OCCLUDE_SILHOUETTE_ALPHA
    G_RM_AA_XLU_SURF,                   // LAYER_TRANSPARENT_DECAL
    G_RM_AA_XLU_SURF,                   // LAYER_TRANSPARENT
    G_RM_AA_XLU_SURF,                   // LAYER_TRANSPARENT_INTER
    } },
    { {
    /* z-buffered */
    G_RM_ZB_OPA_SURF,                   // LAYER_FORCE
    G_RM_AA_ZB_OPA_SURF,                // LAYER_OPAQUE
    G_RM_AA_ZB_OPA_INTER,               // LAYER_OPAQUE_INTER
    G_RM_AA_ZB_OPA_DECAL,               // LAYER_OPAQUE_DECAL
    G_RM_AA_ZB_TEX_EDGE,                // LAYER_ALPHA
    G_RM_AA_ZB_TEX_EDGE | ZMODE_DEC,    // LAYER_ALPHA_DECAL
    G_RM_AA_ZB_OPA_SURF,                // LAYER_SILHOUETTE_OPAQUE
    G_RM_AA_ZB_TEX_EDGE,                // LAYER_SILHOUETTE_ALPHA
    G_RM_AA_ZB_OPA_SURF,                // LAYER_OCCLUDE_SILHOUETTE_OPAQUE
    G_RM_AA_ZB_TEX_EDGE,                // LAYER_OCCLUDE_SILHOUETTE_ALPHA
    G_RM_AA_ZB_XLU_DECAL,               // LAYER_TRANSPARENT_DECAL
    G_RM_AA_ZB_XLU_SURF,                // LAYER_TRANSPARENT
    G_RM_AA_ZB_XLU_INTER,               // LAYER_TRANSPARENT_INTER
    } } };

/* Rendermode settings for cycle 2 for all 13 layers. */
struct RenderModeContainer renderModeTable_2Cycle[2] = { { {
    G_RM_OPA_SURF2,                     // LAYER_FORCE
    G_RM_AA_OPA_SURF2,                  // LAYER_OPAQUE
    G_RM_AA_OPA_SURF2,                  // LAYER_OPAQUE_INTER
    G_RM_AA_OPA_SURF2,                  // LAYER_OPAQUE_DECAL
    G_RM_AA_TEX_EDGE2,                  // LAYER_ALPHA
    G_RM_AA_TEX_EDGE2 | ZMODE_DEC,      // LAYER_ALPHA_DECAL
    G_RM_AA_OPA_SURF2,                  // LAYER_SILHOUETTE_OPAQUE
    G_RM_AA_TEX_EDGE2,                  // LAYER_SILHOUETTE_ALPHA
    G_RM_AA_OPA_SURF2,                  // LAYER_OCCLUDE_SILHOUETTE_OPAQUE
    G_RM_AA_TEX_EDGE2,                  // LAYER_OCCLUDE_SILHOUETTE_ALPHA
    G_RM_AA_XLU_SURF2,                  // LAYER_TRANSPARENT_DECAL
    G_RM_AA_XLU_SURF2,                  // LAYER_TRANSPARENT
    G_RM_AA_XLU_SURF2,                  // LAYER_TRANSPARENT_INTER
    } },
    { {
    /* z-buffered */
    G_RM_ZB_OPA_SURF2,                  // LAYER_FORCE
    G_RM_AA_ZB_OPA_SURF2,               // LAYER_OPAQUE
    G_RM_AA_ZB_OPA_INTER2,              // LAYER_OPAQUE_INTER
    G_RM_AA_ZB_OPA_DECAL2,              // LAYER_OPAQUE_DECAL
    G_RM_AA_ZB_TEX_EDGE2,               // LAYER_ALPHA
    G_RM_AA_ZB_TEX_EDGE2 | ZMODE_DEC,   // LAYER_ALPHA_DECAL
    G_RM_AA_ZB_OPA_SURF2,               // LAYER_SILHOUETTE_OPAQUE
    G_RM_AA_ZB_TEX_EDGE2,               // LAYER_SILHOUETTE_ALPHA
    G_RM_AA_ZB_OPA_SURF2,               // LAYER_OCCLUDE_SILHOUETTE_OPAQUE
    G_RM_AA_ZB_TEX_EDGE2,               // LAYER_OCCLUDE_SILHOUETTE_ALPHA
    G_RM_AA_ZB_XLU_DECAL2,              // LAYER_TRANSPARENT_DECAL
    G_RM_AA_ZB_XLU_SURF2,               // LAYER_TRANSPARENT
    G_RM_AA_ZB_XLU_INTER2,              // LAYER_TRANSPARENT_INTER
    } } };
#else
/* Rendermode settings for cycle 1 for all 8 layers. */
struct RenderModeContainer renderModeTable_1Cycle[2] = { { {
    G_RM_OPA_SURF,
    G_RM_AA_OPA_SURF,
    G_RM_AA_OPA_SURF,
    G_RM_AA_OPA_SURF,
    G_RM_AA_TEX_EDGE,
    G_RM_AA_XLU_SURF,
    G_RM_AA_XLU_SURF,
    G_RM_AA_XLU_SURF,
    } },
    { {
    /* z-buffered */
    G_RM_ZB_OPA_SURF,
    G_RM_AA_ZB_OPA_SURF,
    G_RM_AA_ZB_OPA_DECAL,
    G_RM_AA_ZB_OPA_INTER,
    G_RM_AA_ZB_TEX_EDGE,
    G_RM_AA_ZB_XLU_SURF,
    G_RM_AA_ZB_XLU_DECAL,
    G_RM_AA_ZB_XLU_INTER,
    } } };

/* Rendermode settings for cycle 2 for all 8 layers. */
struct RenderModeContainer renderModeTable_2Cycle[2] = { { {
    G_RM_OPA_SURF2,
    G_RM_AA_OPA_SURF2,
    G_RM_AA_OPA_SURF2,
    G_RM_AA_OPA_SURF2,
    G_RM_AA_TEX_EDGE2,
    G_RM_AA_XLU_SURF2,
    G_RM_AA_XLU_SURF2,
    G_RM_AA_XLU_SURF2,
    } },
    { {
    /* z-buffered */
    G_RM_ZB_OPA_SURF2,
    G_RM_AA_ZB_OPA_SURF2,
    G_RM_AA_ZB_OPA_DECAL2,
    G_RM_AA_ZB_OPA_INTER2,
    G_RM_AA_ZB_TEX_EDGE2,
    G_RM_AA_ZB_XLU_SURF2,
    G_RM_AA_ZB_XLU_DECAL2,
    G_RM_AA_ZB_XLU_INTER2,
    } } };
#endif

struct GraphNodeRoot        *gCurGraphNodeRoot       = NULL;
struct GraphNodeMasterList  *gCurGraphNodeMasterList = NULL;
struct GraphNodePerspective *gCurGraphNodeCamFrustum = NULL;
struct GraphNodeCamera      *gCurGraphNodeCamera     = NULL;
struct GraphNodeObject      *gCurGraphNodeObject     = NULL;
struct GraphNodeHeldObject  *gCurGraphNodeHeldObject = NULL;
u16 gAreaUpdateCounter = 0;
#ifdef METAL_CAP_REFLECTION_LAKITU
s16 gMarioScreenX, gMarioScreenY;
#endif

#ifdef F3DEX_GBI_2
LookAt lookAt;
#endif

#ifdef SILHOUETTE
#define SIL_ALPHA            0x7F
#define LAST_SIL_LAYER       LAYER_SILHOUETTE_ALPHA // Last silhouette layer
#define NUM_EXTRA_SIL_LAYERS 1                      // Number of silhouette layers - 1
#define SCHWA AA_EN | IM_RD | CLR_ON_CVG | CVG_DST_WRAP | CVG_X_ALPHA | FORCE_BL
#endif

/**
 * Process a master list node.
 */
static void geo_process_master_list_sub(struct GraphNodeMasterList *node) {
    struct DisplayListNode *currList;
    s32 i;
#ifdef SILHOUETTE
    s32 j;
#endif
    s32 enableZBuffer                     = ((node->node.flags & GRAPH_RENDER_Z_BUFFER) != 0);
    struct RenderModeContainer *mode1List = &renderModeTable_1Cycle[enableZBuffer];
    struct RenderModeContainer *mode2List = &renderModeTable_2Cycle[enableZBuffer];
#ifdef F3DEX_GBI_2
    Mtx lMtx;
#ifdef FIX_REFLECT_MTX
    guLookAtReflect(&lMtx, &lookAt, 0.0f, 0.0f, 0.0f, /* eye */ 0.0f, 0.0f, 1.0f, /* at */ 0.0f, 1.0f, 0.0f /* up */);
#else
    guLookAtReflect(&lMtx, &lookAt, 0.0f, 0.0f, 0.0f, /* eye */ 0.0f, 0.0f, 1.0f, /* at */ 1.0f, 0.0f, 0.0f /* up */);
#endif
#endif
    if (enableZBuffer) {
        gDPPipeSync(       gDisplayListHead++           );
        gSPSetGeometryMode(gDisplayListHead++, G_ZBUFFER);
    }
#ifdef SILHOUETTE
    for ((i = 0); (i < GFX_NUM_MASTER_LISTS); (i++)) {
        if ((currList = node->listHeads[i]) != NULL) {
            while (currList != NULL) {
                // check if the current layer is a silhouette layer
                if ((i == LAYER_SILHOUETTE_OPAQUE) || (i == LAYER_SILHOUETTE_ALPHA)) {
                    // Set render modes for the silhouette
                    gDPSetRenderMode(   gDisplayListHead++, SCHWA | GBL_c1(G_BL_CLR_FOG, G_BL_A_FOG, G_BL_CLR_MEM, G_BL_1MA),
                                                            SCHWA | GBL_c2(G_BL_CLR_FOG, G_BL_A_FOG, G_BL_CLR_MEM, G_BL_1MA));
                    // Enable fog for silhouette models
                    gSPSetGeometryMode( gDisplayListHead++, G_FOG);
                    gSPFogPosition(     gDisplayListHead++, 0, 1 );
                    gDPSetFogColor(     gDisplayListHead++, 0, 0, 0, SIL_ALPHA     ); // silhouette color & alpha
                    gDPSetEnvColor(     gDisplayListHead++, 0, 0, 0, SIL_ALPHA >> 1); // silhouette env transparency
                } else {
                    // use only the normal mode list for non-silhouette layers
                    gDPSetRenderMode(   gDisplayListHead++, mode1List->modes[i],
                                                            mode2List->modes[i]);
                }
                gSPMatrix(      gDisplayListHead++, VIRTUAL_TO_PHYSICAL(currList->transform),
                                                    (G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH));
                gSPDisplayList( gDisplayListHead++, currList->displayList);
                currList = currList->next;
            }
        }
         // When reaching the last silhouette layer, render the "normal" versions of the silhouette layers:
        if (i == LAST_SIL_LAYER) {
            for ((j = (i - NUM_EXTRA_SIL_LAYERS)); (j <= LAST_SIL_LAYER); (j++)) {
                // Disable fog for the non-silhouette versions
                gSPClearGeometryMode(   gDisplayListHead++, G_FOG);
                // reset the env color & alpha
                gDPSetEnvColor(         gDisplayListHead++, 255, 255, 255, 255);
                // use the normal mode list, but without anti-aliasing
                gDPSetRenderMode(       gDisplayListHead++, mode1List->modes[j] & ~IM_RD,
                                                            mode2List->modes[j] & ~IM_RD);
                currList = node->listHeads[j];
                while (currList != NULL) {
                    gSPMatrix(      gDisplayListHead++, VIRTUAL_TO_PHYSICAL(currList->transform),
                                                        (G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH));
                    gSPDisplayList( gDisplayListHead++, currList->displayList);
                    currList = currList->next;
                }
            }
        }
    }
#else
    for (i = 0; i < GFX_NUM_MASTER_LISTS; i++) {
        if ((currList = node->listHeads[i]) != NULL) {
            gDPSetRenderMode(gDisplayListHead++, mode1List->modes[i], mode2List->modes[i]);
            while (currList != NULL) {
                gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(currList->transform),
                          (G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH));
                gSPDisplayList(gDisplayListHead++, currList->displayList);
                currList = currList->next;
            }
        }
    }
#endif
    if (enableZBuffer) {
        gDPPipeSync(         gDisplayListHead++);
        gSPClearGeometryMode(gDisplayListHead++, G_ZBUFFER);
    }
}

/**
 * Appends the display list to one of the master lists based on the layer
 * parameter. Look at the RenderModeContainer struct to see the corresponding
 * render modes of layers.
 */
static void geo_append_display_list(void *displayList, DrawingLayer layer) {
#ifdef F3DEX_GBI_2
    gSPLookAt(gDisplayListHead++, &lookAt);
#endif
    if (gCurGraphNodeMasterList != 0) {
        struct DisplayListNode *listNode = alloc_only_pool_alloc(gDisplayListHeap, sizeof(struct DisplayListNode));
        listNode->transform   = gMatStackFixed[gMatStackIndex];
        listNode->displayList = displayList;
        listNode->next        = 0;
        if (gCurGraphNodeMasterList->listHeads[layer] == LAYER_FORCE) {
            gCurGraphNodeMasterList->listHeads[layer]       = listNode;
        } else {
            gCurGraphNodeMasterList->listTails[layer]->next = listNode;
        }
        gCurGraphNodeMasterList->listTails[layer] = listNode;
    }
}

/**
 * Process the master list node.
 */
static void geo_process_master_list(struct GraphNodeMasterList *node) {
    s32 i;
    if (gCurGraphNodeMasterList == NULL && node->node.children != NULL) {
        gCurGraphNodeMasterList = node;
        for (i = 0; i < GFX_NUM_MASTER_LISTS; i++) node->listHeads[i] = NULL;
        geo_process_node_and_siblings(node->node.children);
        geo_process_master_list_sub(  node               );
        gCurGraphNodeMasterList = NULL;
    }
}

/**
 * Process an orthographic projection node.
 */
static void geo_process_ortho_projection(struct GraphNodeOrthoProjection *node) {
    if (node->node.children != NULL) {
        Mtx *mtx = alloc_display_list(sizeof(*mtx));
        f32 left   = (gCurGraphNodeRoot->x - gCurGraphNodeRoot->width ) / 2.0f * node->scale;
        f32 right  = (gCurGraphNodeRoot->x + gCurGraphNodeRoot->width ) / 2.0f * node->scale;
        f32 top    = (gCurGraphNodeRoot->y - gCurGraphNodeRoot->height) / 2.0f * node->scale;
        f32 bottom = (gCurGraphNodeRoot->y + gCurGraphNodeRoot->height) / 2.0f * node->scale;
        guOrtho(mtx, left, right, bottom, top, -2.0f, 2.0f, 1.0f);
        gSPPerspNormalize(gDisplayListHead++, 0xFFFF);
        gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(mtx), G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
        geo_process_node_and_siblings(node->node.children);
    }
}

/**
 * Process a perspective projection node.
 */
static void geo_process_perspective(struct GraphNodePerspective *node) {
    if (node->fnNode.func != NULL) node->fnNode.func(GEO_CONTEXT_RENDER, &node->fnNode.node, gMatStack[gMatStackIndex]);
    if (node->fnNode.node.children != NULL) {
        u16 perspNorm;
        Mtx *mtx = alloc_display_list(sizeof(*mtx));
#ifdef WIDE
        aspect = (gWidescreen && (gCurrLevelNum != 0x01)) ? (16.0f/9.0f) : (4.0f/3.0f); // 1.775f, 1.33333f
#else
        aspect = (4.0f/3.0f); // 1.33333f
#endif
        guPerspective(mtx, &perspNorm, node->fov, aspect, node->near / WORLD_SCALE, node->far / WORLD_SCALE, 1.0f);
        gSPPerspNormalize(gDisplayListHead++, perspNorm);
        gSPMatrix(        gDisplayListHead++, VIRTUAL_TO_PHYSICAL(mtx), G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
        gCurGraphNodeCamFrustum = node;
        geo_process_node_and_siblings(node->fnNode.node.children);
        gCurGraphNodeCamFrustum = NULL;
    }
}

/**
 * Process a level of detail node. From the current transformation matrix,
 * the perpendicular distance to the camera is extracted and the children
 * of this node are only processed if that distance is within the render
 * range of this node.
 */
static void geo_process_level_of_detail(struct GraphNodeLevelOfDetail *node) {
#ifdef AUTO_LOD
    f32 distanceFromCam = gIsConsole ? -gMatStack[gMatStackIndex][3][2] : 50;
#else
    f32 distanceFromCam = -gMatStack[gMatStackIndex][3][2];
#endif
    if ((f32)node->minDistance <= distanceFromCam && distanceFromCam < (f32)node->maxDistance && node->node.children != 0) geo_process_node_and_siblings(node->node.children);
}

/**
 * Process a switch case node. The node's selection function is called
 * if it is 0, and among the node's children, only the selected child is
 * processed next.
 */
static void geo_process_switch(struct GraphNodeSwitchCase *node) {
    struct GraphNode *selectedChild = node->fnNode.node.children;
    s32 i;
    if (node->fnNode.func != NULL) node->fnNode.func(GEO_CONTEXT_RENDER, &node->fnNode.node, gMatStack[gMatStackIndex]);
    for (i = 0; selectedChild != NULL && node->selectedCase > i; i++) selectedChild = selectedChild->next;
    if (selectedChild != NULL) geo_process_node_and_siblings(selectedChild);
}

//! move to math_util?
static void make_roll_matrix(Mtx *mtx, Angle angle) {
    Mat4 temp;
    mtxf_identity(temp);
    temp[0][0] = coss(angle);
    temp[0][1] = sins(angle);
    temp[1][0] = -temp[0][1];
    temp[1][1] =  temp[0][0];
    guMtxF2L(temp, mtx);
}

/**
 * Process a camera node.
 */
static void geo_process_camera(struct GraphNodeCamera *node) {
    Mat4 cameraTransform;
#ifdef METAL_CAP_REFLECTION_LAKITU
    Vec3s marioPos3s;
#endif
    Mtx *rollMtx = alloc_display_list(sizeof(*rollMtx));
    Mtx *mtx     = alloc_display_list(sizeof(*mtx));
    if (node->fnNode.func != NULL) node->fnNode.func(GEO_CONTEXT_RENDER, &node->fnNode.node, gMatStack[gMatStackIndex]);
    make_roll_matrix(rollMtx, node->rollScreen);
    gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(rollMtx), (G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH));
#ifdef CUSTOM_FOV
    mtxf_lookat(cameraTransform, node->pos, node->focus, node->roll, (gFieldOfView / 100.0f));
#else
    mtxf_lookat(cameraTransform, node->pos, node->focus, node->roll);
#endif
    mtxf_mul(gMatStack[gMatStackIndex + 1], cameraTransform, gMatStack[gMatStackIndex]);
    gMatStackIndex++;
    mtxf_to_mtx(mtx, gMatStack[gMatStackIndex]);
    gMatStackFixed[gMatStackIndex] = mtx;
    if (node->fnNode.node.children != 0) {
        gCurGraphNodeCamera = node;
        node->matrixPtr = &gMatStack[gMatStackIndex];
        geo_process_node_and_siblings(node->fnNode.node.children);
        gCurGraphNodeCamera = NULL;
    }
#ifdef METAL_CAP_REFLECTION_LAKITU
    // Convert Mario's coordinates into vec3s so they can be used in mtxf_mul_vec3s
    vec3f_to_vec3s(marioPos3s, gMarioState->pos);
    // Transform Mario's coordinates into view frustrum
    mtxf_mul_vec3s(gMatStack[gMatStackIndex], marioPos3s);
    // Perspective divide
    gMarioScreenX = max(2 * (0.5f - marioPos3s[0] / (f32)marioPos3s[2]) * (gCurGraphNodeRoot->width ), 0);
    gMarioScreenY = max(2 * (0.5f - marioPos3s[1] / (f32)marioPos3s[2]) * (gCurGraphNodeRoot->height), 0);
#endif
    gMatStackIndex--;
}

/**
 * Process a translation / rotation node. A transformation matrix based
 * on the node's translation and rotation is created and pushed on both
 * the float and fixed point matrix stacks.
 * For the rest it acts as a normal display list node.
 */
static void geo_process_translation_rotation(struct GraphNodeTranslationRotation *node) {
    Mat4 mtxf;
    Vec3f translation;
    Mtx *mtx = alloc_display_list(sizeof(*mtx));
    vec3s_to_vec3f(translation, node->translation);
    mtxf_rotate_zxy_and_translate(mtxf, translation, node->rotation);
    mtxf_mul(gMatStack[gMatStackIndex + 1], mtxf, gMatStack[gMatStackIndex]);
    gMatStackIndex++;
    mtxf_to_mtx(mtx, gMatStack[gMatStackIndex]);
    gMatStackFixed[gMatStackIndex] = mtx;
    if (node->displayList   != NULL) geo_append_display_list(node->displayList, node->node.flags >> 8);
    if (node->node.children != NULL) geo_process_node_and_siblings(node->node.children);
    gMatStackIndex--;
}

/**
 * Process a translation node. A transformation matrix based on the node's
 * translation is created and pushed on both the float and fixed point matrix stacks.
 * For the rest it acts as a normal display list node.
 */
static void geo_process_translation(struct GraphNodeTranslation *node) {
    Mat4 mtxf;
    Vec3f translation;
    Mtx *mtx = alloc_display_list(sizeof(*mtx));
    vec3s_to_vec3f(translation, node->translation);
    mtxf_rotate_zxy_and_translate(mtxf, translation, gVec3sZero);
    mtxf_mul(gMatStack[gMatStackIndex + 1], mtxf, gMatStack[gMatStackIndex]);
    gMatStackIndex++;
    mtxf_to_mtx(mtx, gMatStack[gMatStackIndex]);
    gMatStackFixed[gMatStackIndex] = mtx;
    if (node->displayList   != NULL) geo_append_display_list(node->displayList, node->node.flags >> 8);
    if (node->node.children != NULL) geo_process_node_and_siblings(node->node.children);
    gMatStackIndex--;
}

/**
 * Process a rotation node. A transformation matrix based on the node's
 * rotation is created and pushed on both the float and fixed point matrix stacks.
 * For the rest it acts as a normal display list node.
 */
static void geo_process_rotation(struct GraphNodeRotation *node) {
    Mat4 mtxf;
    Mtx *mtx = alloc_display_list(sizeof(*mtx));
    mtxf_rotate_zxy_and_translate(mtxf, gVec3fZero, node->rotation);
    mtxf_mul(gMatStack[gMatStackIndex + 1], mtxf, gMatStack[gMatStackIndex]);
    gMatStackIndex++;
    mtxf_to_mtx(mtx, gMatStack[gMatStackIndex]);
    gMatStackFixed[gMatStackIndex] = mtx;
    if (node->displayList   != NULL) geo_append_display_list(node->displayList, node->node.flags >> 8);
    if (node->node.children != NULL) geo_process_node_and_siblings(node->node.children);
    gMatStackIndex--;
}

/**
 * Process a scaling node. A transformation matrix based on the node's
 * scale is created and pushed on both the float and fixed point matrix stacks.
 * For the rest it acts as a normal display list node.
 */
static void geo_process_scale(struct GraphNodeScale *node) {
    Vec3f scaleVec;
    Mtx *mtx = alloc_display_list(sizeof(*mtx));
    vec3f_set(scaleVec, node->scale, node->scale, node->scale);
    mtxf_scale_vec3f(gMatStack[gMatStackIndex + 1], gMatStack[gMatStackIndex], scaleVec);
    gMatStackIndex++;
    mtxf_to_mtx(mtx, gMatStack[gMatStackIndex]);
    gMatStackFixed[gMatStackIndex] = mtx;
    if (node->displayList   != NULL) geo_append_display_list(node->displayList, node->node.flags >> 8);
    if (node->node.children != NULL) geo_process_node_and_siblings(node->node.children);
    gMatStackIndex--;
}

/**
 * Process a billboard node. A transformation matrix is created that makes its
 * children face the camera, and it is pushed on the floating point and fixed
 * point matrix stacks.
 * For the rest it acts as a normal display list node.
 */
static void geo_process_billboard(struct GraphNodeBillboard *node) {
    Vec3f translation;
    Mtx *mtx = alloc_display_list(sizeof(*mtx));
    gMatStackIndex++;
    vec3s_to_vec3f(translation, node->translation);\
    if (node->zOffset < 0) {
        mtxf_align_facing_view(gMatStack[gMatStackIndex], gMatStack[gMatStackIndex - 1], translation, gCurGraphNodeCamera->roll, node->zOffset);
    } else {
        mtxf_billboard(        gMatStack[gMatStackIndex], gMatStack[gMatStackIndex - 1], translation, gCurGraphNodeCamera->roll, node->zOffset);
    }
    if (gCurGraphNodeHeldObject != NULL) {
        mtxf_scale_vec3f(gMatStack[gMatStackIndex], gMatStack[gMatStackIndex], gCurGraphNodeHeldObject->objNode->header.gfx.scale);
    } else if (gCurGraphNodeObject != NULL) {
        mtxf_scale_vec3f(gMatStack[gMatStackIndex], gMatStack[gMatStackIndex], gCurGraphNodeObject->scale);
    }
    mtxf_to_mtx(mtx, gMatStack[gMatStackIndex]);
    gMatStackFixed[gMatStackIndex] = mtx;
    if (node->displayList   != NULL) geo_append_display_list(node->displayList, node->node.flags >> 8);
    if (node->node.children != NULL) geo_process_node_and_siblings(node->node.children);
    gMatStackIndex--;
}

/**
 * Process a display list node. It draws a display list without first pushing
 * a transformation on the stack, so all transformations are inherited from the
 * parent node. It processes its children if it has them.
 */
static void geo_process_display_list(struct GraphNodeDisplayList *node) {
    if (node->displayList   != NULL) geo_append_display_list(node->displayList, node->node.flags >> 8);
    if (node->node.children != NULL) geo_process_node_and_siblings(node->node.children);
}

/**
 * Process a generated list. Instead of storing a pointer to a display list,
 * the list is generated on the fly by a function.
 */
static void geo_process_generated_list(struct GraphNodeGenerated *node) {
    if (node->fnNode.func != NULL) {
        Gfx *list = node->fnNode.func(GEO_CONTEXT_RENDER, &node->fnNode.node, (struct AllocOnlyPool *) gMatStack[gMatStackIndex]);
        if (list != NULL) geo_append_display_list((void *) VIRTUAL_TO_PHYSICAL(list), node->fnNode.node.flags >> 8);
    }
    if (node->fnNode.node.children != NULL) geo_process_node_and_siblings(node->fnNode.node.children);
}

/**
 * Process a background node. Tries to retrieve a background display list from
 * the function of the node. If that function is null or returns null, a black
 * rectangle is drawn instead.
 */
static void geo_process_background(struct GraphNodeBackground *node) {
    Gfx *list = NULL;
    if (node->fnNode.func != NULL) list = node->fnNode.func(GEO_CONTEXT_RENDER, &node->fnNode.node, (struct AllocOnlyPool *) gMatStack[gMatStackIndex]);
    if (list != NULL) {
        geo_append_display_list((void *) VIRTUAL_TO_PHYSICAL(list), node->fnNode.node.flags >> 8);
    } else if (gCurGraphNodeMasterList != NULL) {
#ifndef F3DEX_GBI_2E
        Gfx *gfxStart = alloc_display_list(sizeof(Gfx) * 7);
#else
        Gfx *gfxStart = alloc_display_list(sizeof(Gfx) * 8);
#endif
        Gfx *gfx = gfxStart;
        gDPPipeSync(      gfx++);
        gDPSetCycleType(  gfx++, G_CYC_FILL);
        gDPSetFillColor(  gfx++, node->background);
        gDPFillRectangle( gfx++, GFX_DIMENSIONS_RECT_FROM_LEFT_EDGE(0), gBorderHeight,
                                GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(0) - 1, SCREEN_HEIGHT - gBorderHeight - 1);
        gDPPipeSync(      gfx++);
        gDPSetCycleType(  gfx++, G_CYC_1CYCLE);
        gSPEndDisplayList(gfx++);
        geo_append_display_list((void *) VIRTUAL_TO_PHYSICAL(gfxStart), LAYER_FORCE);
    }
    if (node->fnNode.node.children != NULL) geo_process_node_and_siblings(node->fnNode.node.children);
}

/**
 * Render an animated part. The current animation state is not part of the node
 * but set in global variables. If an animated part is skipped, everything afterwards desyncs.
 */
static void geo_process_animated_part(struct GraphNodeAnimatedPart *node) {
    Mat4  matrix;
    Vec3a rotation;
    Vec3f translation;
    Mtx   *matrixPtr = alloc_display_list(sizeof(*matrixPtr));

    vec3s_copy(rotation, gVec3sZero);
    vec3f_set(translation, node->translation[0], node->translation[1], node->translation[2]);
    if (gCurAnimType == ANIM_TYPE_TRANSLATION) {
        translation[0] += gCurAnimData[retrieve_animation_index(gCurrAnimFrame, &gCurrAnimAttribute)] * gCurAnimTranslationMultiplier;
        translation[1] += gCurAnimData[retrieve_animation_index(gCurrAnimFrame, &gCurrAnimAttribute)] * gCurAnimTranslationMultiplier;
        translation[2] += gCurAnimData[retrieve_animation_index(gCurrAnimFrame, &gCurrAnimAttribute)] * gCurAnimTranslationMultiplier;
        gCurAnimType = ANIM_TYPE_ROTATION;
    } else {
        if (gCurAnimType == ANIM_TYPE_LATERAL_TRANSLATION) {
            translation[0] += gCurAnimData[retrieve_animation_index(gCurrAnimFrame, &gCurrAnimAttribute)] * gCurAnimTranslationMultiplier;
            gCurrAnimAttribute += 2;
            translation[2] += gCurAnimData[retrieve_animation_index(gCurrAnimFrame, &gCurrAnimAttribute)] * gCurAnimTranslationMultiplier;
            gCurAnimType = ANIM_TYPE_ROTATION;
        } else {
            if (gCurAnimType == ANIM_TYPE_VERTICAL_TRANSLATION) {
                gCurrAnimAttribute += 2;
                translation[1] += gCurAnimData[retrieve_animation_index(gCurrAnimFrame, &gCurrAnimAttribute)] * gCurAnimTranslationMultiplier;
                gCurrAnimAttribute += 2;
                gCurAnimType = ANIM_TYPE_ROTATION;
            } else if (gCurAnimType == ANIM_TYPE_NO_TRANSLATION) {
                gCurrAnimAttribute += 6;
                gCurAnimType = ANIM_TYPE_ROTATION;
            }
        }
    }
    if (gCurAnimType == ANIM_TYPE_ROTATION) {
        rotation[0] = gCurAnimData[retrieve_animation_index(gCurrAnimFrame, &gCurrAnimAttribute)];
        rotation[1] = gCurAnimData[retrieve_animation_index(gCurrAnimFrame, &gCurrAnimAttribute)];
        rotation[2] = gCurAnimData[retrieve_animation_index(gCurrAnimFrame, &gCurrAnimAttribute)];
    }
    mtxf_rotate_xyz_and_translate(matrix, translation, rotation);
    mtxf_mul(gMatStack[gMatStackIndex + 1], matrix, gMatStack[gMatStackIndex]);
    gMatStackIndex++;
    mtxf_to_mtx(matrixPtr, gMatStack[gMatStackIndex]);
    gMatStackFixed[gMatStackIndex] = matrixPtr;
    if (node->displayList   != NULL) geo_append_display_list(node->displayList, node->node.flags >> 8);
    if (node->node.children != NULL) geo_process_node_and_siblings(node->node.children);
    gMatStackIndex--;
}

/**
 * Initialize the animation-related global variables for the currently drawn
 * object's animation.
 */
void geo_set_animation_globals(struct AnimInfo *node, s32 hasAnimation) {
    struct Animation *anim            = node->curAnim;
    if (hasAnimation) node->animFrame = geo_update_animation_frame(node, &node->animFrameAccelAssist);
    node->animTimer = gAreaUpdateCounter;
    if (anim->flags & ANIM_FLAG_HOR_TRANS) {
        gCurAnimType = ANIM_TYPE_VERTICAL_TRANSLATION;
    } else if (anim->flags & ANIM_FLAG_VERT_TRANS) {
        gCurAnimType = ANIM_TYPE_LATERAL_TRANSLATION;
    } else if (anim->flags & ANIM_FLAG_6) {
        gCurAnimType = ANIM_TYPE_NO_TRANSLATION;
    } else {
        gCurAnimType = ANIM_TYPE_TRANSLATION;
    }
    gCurrAnimFrame                = node->animFrame;
    gCurAnimEnabled               = (anim->flags & ANIM_FLAG_5) == 0;
    gCurrAnimAttribute            = segmented_to_virtual((void *) anim->index);
    gCurAnimData                  = segmented_to_virtual((void *) anim->values);
    gCurAnimTranslationMultiplier = (anim->animYTransDivisor == 0) ? 1.0f : ((f32) node->animYTrans / (f32) anim->animYTransDivisor);
}

/**
 * Process a shadow node. Renders a shadow under an object offset by the
 * translation of the first animated component and rotated according to
 * the floor below it.
 */
static void geo_process_shadow(struct GraphNodeShadow *node) {
    Gfx *shadowList;
    Mat4 mtxf;
    Vec3f shadowPos;
    Vec3f animOffset;
    f32 objScale;
    f32 shadowScale;
    f32 sinAng, cosAng;
    struct GraphNode *geo;
    Mtx *mtx;
    if (gCurGraphNodeCamera != NULL && gCurGraphNodeObject != NULL) {
        if (gCurGraphNodeHeldObject != NULL) {
            get_pos_from_transform_mtx(shadowPos, gMatStack[gMatStackIndex], *gCurGraphNodeCamera->matrixPtr);
            shadowScale = node->shadowScale;
        } else {
            vec3f_copy(shadowPos, gCurGraphNodeObject->pos);
            shadowScale = node->shadowScale * gCurGraphNodeObject->scale[0];
        }
        objScale = 1.0f;
        if (gCurAnimEnabled) {
            if (gCurAnimType == ANIM_TYPE_TRANSLATION
             || gCurAnimType == ANIM_TYPE_LATERAL_TRANSLATION) {
                geo = node->node.children;
                if (geo != NULL && geo->type == GRAPH_NODE_TYPE_SCALE) objScale = ((struct GraphNodeScale *) geo)->scale;
                animOffset[0]       = gCurAnimData[retrieve_animation_index(gCurrAnimFrame, &gCurrAnimAttribute)] * gCurAnimTranslationMultiplier * objScale;
                animOffset[1]       = 0.0f;
                gCurrAnimAttribute += 2;
                animOffset[2]       = gCurAnimData[retrieve_animation_index(gCurrAnimFrame, &gCurrAnimAttribute)] * gCurAnimTranslationMultiplier * objScale;
                gCurrAnimAttribute -= 6;
                // simple matrix rotation so the shadow offset rotates along with the object
                sinAng              = sins(gCurGraphNodeObject->angle[1]);
                cosAng              = coss(gCurGraphNodeObject->angle[1]);
                shadowPos[0]       += ( animOffset[0] * cosAng + animOffset[2] * sinAng);
                shadowPos[2]       += (-animOffset[0] * sinAng + animOffset[2] * cosAng);
            }
        }
        shadowList = create_shadow_below_xyz(shadowPos[0], shadowPos[1], shadowPos[2], shadowScale, node->shadowSolidity, node->shadowType);
        if (shadowList != NULL) {
            mtx = alloc_display_list(sizeof(*mtx));
            gMatStackIndex++;
            mtxf_translate(mtxf, shadowPos);
            mtxf_mul(gMatStack[gMatStackIndex], mtxf, *gCurGraphNodeCamera->matrixPtr);
            mtxf_to_mtx(mtx, gMatStack[gMatStackIndex]);
            gMatStackFixed[gMatStackIndex] = mtx;
            geo_append_display_list((void *) VIRTUAL_TO_PHYSICAL(shadowList), (gShadowAboveWaterOrLava || gShadowAboveCustomWater || gMarioOnIceOrCarpet) ? LAYER_TRANSPARENT : LAYER_TRANSPARENT_DECAL);
            gMatStackIndex--;
        }
    }
    if (node->node.children != NULL) geo_process_node_and_siblings(node->node.children);
}

/**
 * Check whether an object is in view to determine whether it should be drawn.
 * This is known as frustum culling.
 * It checks whether the object is far away, very close / behind the camera,
 * or horizontally out of view. It does not check whether it is vertically
 * out of view. It assumes a sphere of 300 units around the object's position
 * unless the object has a culling radius node that specifies otherwise.
 *
 * The matrix parameter should be the top of the matrix stack, which is the
 * object's transformation matrix times the camera 'look-at' matrix. The math
 * is counter-intuitive, but it checks column 3 (translation vector) of this
 * matrix to determine where the origin (0,0,0) in object space will be once
 * transformed to camera space (x+ = right, y+ = up, z = 'coming out the screen').
 * In 3D graphics, you typically model the world as being moved in front of a
 * static camera instead of a moving camera through a static world, which in
 * this case simplifies calculations. Note that the perspective matrix is not
 * on the matrix stack, so there are still calculations with the fov to compute
 * the slope of the lines of the frustum.
 *
 *        z-
 *
 *  \     |     /
 *   \    |    /
 *    \   |   /
 *     \  |  /
 *      \ | /
 *       \|/
 *        C       x+
 *
 * Since (0,0,0) is unaffected by rotation, columns 0, 1 and 2 are ignored.
 */
static s32 obj_is_in_view(struct GraphNodeObject *node, Mat4 matrix) {
    s16 cullingRadius;
    s16 halfFov; // half of the fov in in-game angle units instead of degrees
    struct GraphNode *geo;
    f32 hScreenEdge;
    if (node->node.flags & GRAPH_RENDER_INVISIBLE) return FALSE;
    geo         = node->sharedChild;
    halfFov     = ((gCurGraphNodeCamFrustum->fov*aspect) / 2.0f + 1.0f) * 32768.0f / 180.0f + 0.5f;
    hScreenEdge = -matrix[3][2] * sins(halfFov) / coss(halfFov);
    // -matrix[3][2] is the depth, which gets multiplied by tan(halfFov) to get
    // the amount of units between the center of the screen and the horizontal edge
    // given the distance from the object to the camera.

    // This multiplication should really be performed on 4:3 as well,
    // but the issue will be more apparent on widescreen.
    // HackerSM64: This multiplication is done regardless of aspect ratio to fix object pop-in on the edges of the screen (which happens at 4:3 too)
    hScreenEdge *= GFX_DIMENSIONS_ASPECT_RATIO;
    if (geo != NULL && geo->type == GRAPH_NODE_TYPE_CULLING_RADIUS) {
        cullingRadius = ((struct GraphNodeCullingRadius *) geo)->cullingRadius;
    } else {
        cullingRadius = 300;
    }
    // Don't render if the object is close to or behind the camera
    if (matrix[3][2] >   -100.0f + cullingRadius) return FALSE;
    //! This makes the HOLP not update when the camera is far away, and it
    //  makes PU travel safe when the camera is locked on the main map.
    //  If Mario were rendered with a depth over 65536 it would cause overflow
    //  when converting the transformation matrix to a fixed point matrix.
    if (matrix[3][2] < -20000.0f - cullingRadius) return FALSE;
    // Check whether the object is horizontally in view
    return !((matrix[3][0] > hScreenEdge + cullingRadius) || (matrix[3][0] < -hScreenEdge - cullingRadius));
}

/**
 * Process an object node.
 */
static void geo_process_object(struct Object *node) {
    Mat4 mtxf;
    s32 hasAnimation = ((node->header.gfx.node.flags & GRAPH_RENDER_HAS_ANIMATION) != 0);
    if (node->header.gfx.areaIndex == gCurGraphNodeRoot->areaIndex) {
        if (node->header.gfx.throwMatrix != NULL) {
            mtxf_mul(gMatStack[gMatStackIndex + 1], *node->header.gfx.throwMatrix, gMatStack[gMatStackIndex]);
        } else if (node->header.gfx.node.flags & GRAPH_RENDER_BILLBOARD) {
            mtxf_billboard(gMatStack[gMatStackIndex + 1], gMatStack[gMatStackIndex], node->header.gfx.pos, gCurGraphNodeCamera->roll, 0.0f);
        } else {
            mtxf_rotate_zxy_and_translate(mtxf, node->header.gfx.pos, node->header.gfx.angle);
            mtxf_mul(gMatStack[gMatStackIndex + 1], mtxf, gMatStack[gMatStackIndex]);
        }
        mtxf_scale_vec3f(gMatStack[gMatStackIndex + 1], gMatStack[gMatStackIndex + 1], node->header.gfx.scale);
        node->header.gfx.throwMatrix       = &gMatStack[++gMatStackIndex];
        node->header.gfx.cameraToObject[0] =  gMatStack[  gMatStackIndex][3][0];
        node->header.gfx.cameraToObject[1] =  gMatStack[  gMatStackIndex][3][1];
        node->header.gfx.cameraToObject[2] =  gMatStack[  gMatStackIndex][3][2];
        // FIXME: correct types
        if (node->header.gfx.animInfo.curAnim != NULL) geo_set_animation_globals(&node->header.gfx.animInfo, hasAnimation);
        if (obj_is_in_view(&node->header.gfx, gMatStack[gMatStackIndex])) {
            Mtx *mtx = alloc_display_list(sizeof(*mtx));
            mtxf_to_mtx(mtx, gMatStack[gMatStackIndex]);
            gMatStackFixed[gMatStackIndex] = mtx;
            if (node->header.gfx.sharedChild != NULL) {
#ifdef VISUAL_DEBUG
                if (hitboxView) {
                    Vec3f bnds1;
                    Vec3f bnds2;
                    // This will create a cylinder that visualises their hitbox.
                    // If they do not have a hitbox, it will be a small white cube instead.
                    if (node->oIntangibleTimer != -1) {
                        vec3f_set(bnds1, node->oPosX, (node->oPosY - node->hitboxDownOffset), node->oPosZ);
                        vec3f_set(bnds2, node->hitboxRadius, node->hitboxHeight-node->hitboxDownOffset, node->hitboxRadius);
                        debug_box_color(0x800000FF);
                        debug_box(bnds1, bnds2, DEBUG_SHAPE_CYLINDER);
                        vec3f_set(bnds1, node->oPosX, (node->oPosY - node->hitboxDownOffset), node->oPosZ);
                        vec3f_set(bnds2, node->hurtboxRadius, node->hurtboxHeight, node->hurtboxRadius);
                        debug_box_color(0x8FF00000);
                        debug_box(bnds1, bnds2, DEBUG_SHAPE_CYLINDER);
                    } else {
                        vec3f_set(bnds1, node->oPosX, (node->oPosY - 15), node->oPosZ);
                        vec3f_set(bnds2, 30, 30, 30);
                        debug_box_color(0x80FFFFFF);
                        debug_box(bnds1, bnds2, DEBUG_SHAPE_BOX);
                    }
                }
#endif
                gCurGraphNodeObject = (struct GraphNodeObject *) node;
                node->header.gfx.sharedChild->parent = &node->header.gfx.node;
                geo_process_node_and_siblings(node->header.gfx.sharedChild);
                node->header.gfx.sharedChild->parent = NULL;
                gCurGraphNodeObject                  = NULL;
            }
            if (node->header.gfx.node.children != NULL) geo_process_node_and_siblings(node->header.gfx.node.children);
        }
        gMatStackIndex--;
        gCurAnimType                 = ANIM_TYPE_NONE;
        node->header.gfx.throwMatrix = NULL;
    }
}

/**
 * Process an object parent node. Temporarily assigns itself as the parent of
 * the subtree rooted at 'sharedChild' and processes the subtree, after which the
 * actual children are be processed. (in practice they are null though)
 */
static void geo_process_object_parent(struct GraphNodeObjectParent *node) {
    if (node->sharedChild != NULL) {
        node->sharedChild->parent = (struct GraphNode *) node;
        geo_process_node_and_siblings(node->sharedChild);
        node->sharedChild->parent = NULL;
    }
    if (node->node.children != NULL) geo_process_node_and_siblings(node->node.children);
}

/**
 * Process a held object node.
 */
void geo_process_held_object(struct GraphNodeHeldObject *node) {
    Mat4 mat;
    Vec3f translation;
    Mtx *mtx = alloc_display_list(sizeof(*mtx));
#ifdef F3DEX_GBI_2
    gSPLookAt(gDisplayListHead++, &lookAt);
#endif
    if (node->fnNode.func != NULL)   node->fnNode.func(GEO_CONTEXT_RENDER, &node->fnNode.node, gMatStack[gMatStackIndex]);
    if (node->objNode     != NULL && node->objNode->header.gfx.sharedChild != NULL) {
        s32 hasAnimation = (node->objNode->header.gfx.node.flags & GRAPH_RENDER_HAS_ANIMATION) != 0;
        translation[0] = (node->translation[0] / 4.0f);
        translation[1] = (node->translation[1] / 4.0f);
        translation[2] = (node->translation[2] / 4.0f);
        mtxf_translate(mat, translation);
        mtxf_copy(       gMatStack[gMatStackIndex + 1], *gCurGraphNodeObject->throwMatrix);
        vec3f_copy(gMatStack[gMatStackIndex + 1][3], gMatStack[gMatStackIndex][3]);
        // gMatStack[                 gMatStackIndex + 1][3][0] = gMatStack[gMatStackIndex][3][0];
        // gMatStack[                 gMatStackIndex + 1][3][1] = gMatStack[gMatStackIndex][3][1];
        // gMatStack[                 gMatStackIndex + 1][3][2] = gMatStack[gMatStackIndex][3][2];
        mtxf_mul(        gMatStack[gMatStackIndex + 1], mat,   gMatStack[gMatStackIndex + 1]);
        mtxf_scale_vec3f(gMatStack[gMatStackIndex + 1],        gMatStack[gMatStackIndex + 1], node->objNode->header.gfx.scale);
        if (node->fnNode.func != NULL) node->fnNode.func(GEO_CONTEXT_HELD_OBJ, &node->fnNode.node, (struct AllocOnlyPool *) gMatStack[gMatStackIndex + 1]);
        gMatStackIndex++;
        mtxf_to_mtx(mtx, gMatStack[gMatStackIndex]);
        gMatStackFixed[gMatStackIndex]      = mtx;
        gGeoTempState.type                  = gCurAnimType;
        gGeoTempState.enabled               = gCurAnimEnabled;
        gGeoTempState.frame                 = gCurrAnimFrame;
        gGeoTempState.translationMultiplier = gCurAnimTranslationMultiplier;
        gGeoTempState.attribute             = gCurrAnimAttribute;
        gGeoTempState.data                  = gCurAnimData;
        gCurAnimType                        = ANIM_TYPE_NONE;
        gCurGraphNodeHeldObject             = (void *) node;
        if (node->objNode->header.gfx.animInfo.curAnim != NULL) geo_set_animation_globals(&node->objNode->header.gfx.animInfo, hasAnimation);
        geo_process_node_and_siblings(node->objNode->header.gfx.sharedChild);
        gCurGraphNodeHeldObject             = NULL;
        gCurAnimType                        = gGeoTempState.type;
        gCurAnimEnabled                     = gGeoTempState.enabled;
        gCurrAnimFrame                      = gGeoTempState.frame;
        gCurAnimTranslationMultiplier       = gGeoTempState.translationMultiplier;
        gCurrAnimAttribute                  = gGeoTempState.attribute;
        gCurAnimData                        = gGeoTempState.data;
        gMatStackIndex--;
    }
    if (node->fnNode.node.children != NULL) geo_process_node_and_siblings(node->fnNode.node.children);
}

/**
 * Processes the children of the given GraphNode if it has any
 */
void geo_try_process_children(struct GraphNode *node) {
    if (node->children != NULL) geo_process_node_and_siblings(node->children);
}

/**
 * Process a generic geo node and its siblings.
 * The first argument is the start node, and all its siblings will
 * be iterated over.
 */
void geo_process_node_and_siblings(struct GraphNode *firstNode) {
    s16 iterateChildren            = TRUE;
    struct GraphNode *curGraphNode = firstNode;
    struct GraphNode *parent       = curGraphNode->parent;
    // In the case of a switch node, exactly one of the children of the node is
    // processed instead of all children like usual
    if (parent != NULL) iterateChildren = (parent->type != GRAPH_NODE_TYPE_SWITCH_CASE);
    do {
        if (curGraphNode->flags & GRAPH_RENDER_ACTIVE) {
            if (curGraphNode->flags & GRAPH_RENDER_CHILDREN_FIRST) {
                geo_try_process_children(curGraphNode);
            } else {
                switch (curGraphNode->type) {
                    case GRAPH_NODE_TYPE_ORTHO_PROJECTION:     geo_process_ortho_projection(    (struct GraphNodeOrthoProjection     *) curGraphNode); break;
                    case GRAPH_NODE_TYPE_PERSPECTIVE:          geo_process_perspective(         (struct GraphNodePerspective         *) curGraphNode); break;
                    case GRAPH_NODE_TYPE_MASTER_LIST:          geo_process_master_list(         (struct GraphNodeMasterList          *) curGraphNode); break;
                    case GRAPH_NODE_TYPE_LEVEL_OF_DETAIL:      geo_process_level_of_detail(     (struct GraphNodeLevelOfDetail       *) curGraphNode); break;
                    case GRAPH_NODE_TYPE_SWITCH_CASE:          geo_process_switch(              (struct GraphNodeSwitchCase          *) curGraphNode); break;
                    case GRAPH_NODE_TYPE_CAMERA:               geo_process_camera(              (struct GraphNodeCamera              *) curGraphNode); break;
                    case GRAPH_NODE_TYPE_TRANSLATION_ROTATION: geo_process_translation_rotation((struct GraphNodeTranslationRotation *) curGraphNode); break;
                    case GRAPH_NODE_TYPE_TRANSLATION:          geo_process_translation(         (struct GraphNodeTranslation         *) curGraphNode); break;
                    case GRAPH_NODE_TYPE_ROTATION:             geo_process_rotation(            (struct GraphNodeRotation            *) curGraphNode); break;
                    case GRAPH_NODE_TYPE_OBJECT:               geo_process_object(              (struct Object                       *) curGraphNode); break;
                    case GRAPH_NODE_TYPE_ANIMATED_PART:        geo_process_animated_part(       (struct GraphNodeAnimatedPart        *) curGraphNode); break;
                    case GRAPH_NODE_TYPE_BILLBOARD:            geo_process_billboard(           (struct GraphNodeBillboard           *) curGraphNode); break;
                    case GRAPH_NODE_TYPE_DISPLAY_LIST:         geo_process_display_list(        (struct GraphNodeDisplayList         *) curGraphNode); break;
                    case GRAPH_NODE_TYPE_SCALE:                geo_process_scale(               (struct GraphNodeScale               *) curGraphNode); break;
                    case GRAPH_NODE_TYPE_SHADOW:               geo_process_shadow(              (struct GraphNodeShadow              *) curGraphNode); break;
                    case GRAPH_NODE_TYPE_OBJECT_PARENT:        geo_process_object_parent(       (struct GraphNodeObjectParent        *) curGraphNode); break;
                    case GRAPH_NODE_TYPE_GENERATED_LIST:       geo_process_generated_list(      (struct GraphNodeGenerated           *) curGraphNode); break;
                    case GRAPH_NODE_TYPE_BACKGROUND:           geo_process_background(          (struct GraphNodeBackground          *) curGraphNode); break;
                    case GRAPH_NODE_TYPE_HELD_OBJ:             geo_process_held_object(         (struct GraphNodeHeldObject          *) curGraphNode); break;
                    default:                                   geo_try_process_children(        (struct GraphNode                    *) curGraphNode); break;
                }
            }
        } else if (curGraphNode->type == GRAPH_NODE_TYPE_OBJECT) {
            ((struct GraphNodeObject *) curGraphNode)->throwMatrix = NULL;
        }
    } while (iterateChildren && (curGraphNode = curGraphNode->next) != firstNode);
}

/**
 * Process a root node. This is the entry point for processing the scene graph.
 * The root node itself sets up the viewport, then all its children are processed
 * to set up the projection and draw display lists.
 */
void geo_process_root(struct GraphNodeRoot *node, Vp *b, Vp *c, s32 clearColor) {
#ifdef PUPPYPRINT
    OSTime first = osGetTime();
#endif
    if (node->node.flags & GRAPH_RENDER_ACTIVE) {
        Mtx *initialMatrix;
        Vp *viewport     = alloc_display_list(sizeof(*viewport));
        gDisplayListHeap = alloc_only_pool_init(main_pool_available() - sizeof(struct AllocOnlyPool), MEMORY_POOL_LEFT);
        initialMatrix    = alloc_display_list(sizeof(*initialMatrix));
        gMatStackIndex   = 0;
        gCurAnimType     = ANIM_TYPE_NONE;
        vec3s_set(viewport->vp.vtrans, (node->x     * 4), (node->y      * 4), 511);
        vec3s_set(viewport->vp.vscale, (node->width * 4), (node->height * 4), 511);
        if (b != NULL) {
            clear_frame_buffer(clearColor);
            make_viewport_clip_rect(b);
            *viewport = *b;
        } else if (c != NULL) {
            clear_frame_buffer(clearColor);
            make_viewport_clip_rect(c);
        }
        mtxf_identity(gMatStack[gMatStackIndex]);
        mtxf_to_mtx(initialMatrix, gMatStack[gMatStackIndex]);
        gMatStackFixed[gMatStackIndex] = initialMatrix;
        gSPViewport(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(viewport));
        gSPMatrix(  gDisplayListHead++, VIRTUAL_TO_PHYSICAL(gMatStackFixed[gMatStackIndex]), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        gCurGraphNodeRoot = node;
        if (node->node.children != NULL) geo_process_node_and_siblings(node->node.children);
        gCurGraphNodeRoot = NULL;
        if (gShowDebugText) {
#ifdef HUD_LEADING_ZEROES
            print_text_fmt_int(180, 24, "MEM %07d", gDisplayListHeap->totalSpace - gDisplayListHeap->usedSpace);
#else
            print_text_fmt_int(180, 36, "MEM %d",   gDisplayListHeap->totalSpace - gDisplayListHeap->usedSpace);
#endif
        }
        main_pool_free(gDisplayListHeap);
    }
#ifdef PUPPYPRINT
    profiler_update(graphTime, first);
#endif
}
