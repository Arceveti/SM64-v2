#include <ultra64.h>

#ifdef VISUAL_DEBUG

/**
 * @file debug_box.c
 * Draws 3D boxes for debugging purposes
 * Originally written by Synray, modified by Fazana.
 *
 * How to use:
 *
 * Just call debug_box() whenever you want to draw one!
 *
 * debug_box by default takes two arguments: a center and bounds vec3f.
 * This will draw a box starting from the point (center - bounds) to (center + bounds).
 *
 * Use debug_box_rot to draw a box rotated in the xz-plane.
 *
 * If you want to draw a box by specifying min and max points, use debug_box_pos() instead.
 */

#include "sm64.h"
#include "boot/game_init.h"
#include "game/geo_misc.h"
#include "engine/math_util.h"
#include "engine/colors.h"
#include "area.h"
#include "level_update.h"
#include "print.h"
#include "engine/surface_collision.h"
#include "engine/surface_load.h"
#include "object_list_processor.h"

#include "debug_box.h"

Bool8  hitboxView = FALSE;
Bool8 surfaceView = FALSE;

/**
 * Internal struct containing box info
 */
struct DebugBox {
    RGBA32 color;
    Vec3s center;
    Vec3s bounds;
    Angle yaw;
    u8 type;
};

struct DebugVert
{
    Vec3t pos;
    Vec3n normal;
};

struct DebugBox sBoxes[MAX_DEBUG_BOXES];
s16 sNumBoxes = 0;

extern Mat4 gMatStack[32]; //XXX: Hack

/**
 * The debug boxes' default transparency
 */
#define DBG_BOX_ALPHA     COLOR_RGBA32_DEBUG_ALPHA
/**
 * The debug boxes' default color. sCurBoxColor is reset to this every frame.
 */
#define DBG_BOX_DEF_COLOR COLOR_RGBA32_DEBUG_DEFAULT

/**
 * The color that new boxes will be drawn with.
 */
RGBA32 sCurBoxColor = ((DBG_BOX_ALPHA << 24) | DBG_BOX_DEF_COLOR);

/**
 * The allocated size of a rotated box's dl
 */
#define DBG_BOX_DLSIZE ((s32)((6 * sizeof(Gfx)) + (8 * sizeof(Vtx))))

/**
 * Sets up the RCP for drawing the boxes
 */
static const Gfx dl_debug_box_begin[] = {
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_ZB_XLU_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH),
    gsSPTexture(0, 0, 0, 0, G_OFF),
    gsDPSetCombineMode(G_CC_FADE, G_CC_FADE),
    gsSPEndDisplayList(),
};

static const Gfx dl_debug_box_begin_water[] = {
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_ZB_XLU_SURF, G_RM_NOOP2),
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH),
    gsSPTexture(0, 0, 0, 0, G_OFF),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

static const Gfx dl_debug_box_end[] = {
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsSPClearGeometryMode(G_LIGHTING | G_CULL_BACK),
    gsSPTexture(0, 0, 0, 0, G_OFF),
    gsDPSetCombineMode(G_CC_FADE, G_CC_FADE),
    gsDPSetEnvColor(0xFF, 0xFF, 0xFF, 0xFF),
    gsSPEndDisplayList(),
};

static const Gfx dl_visual_surface[] = {
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_ZB_XLU_DECAL, G_RM_NOOP2),
    gsSPClearGeometryMode(G_LIGHTING),
    gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH),
    gsSPTexture(0, 0, 0, 0, G_OFF),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPEndDisplayList(),
};

u8 viewCycle = 0;

// Puppyprint will call this from elsewhere.
void debug_box_input(void) {
    if (gPlayer1Controller->buttonPressed & R_JPAD) {
        viewCycle++;
        if (viewCycle > 3) viewCycle = 0;
        hitboxView  = ((viewCycle == 1) || (viewCycle == 3));
        surfaceView = ((viewCycle == 2) || (viewCycle == 3));
    }
}

s16 gVisualSurfaceCount;
s32 gVisualOffset;
extern s32 gSurfaceNodesAllocated;
extern s32 gSurfacesAllocated;

void iterate_surfaces_visual(s32 x, s32 z, Vtx *verts) {
    struct SurfaceNode *node;
    struct Surface *surf;
    s32 i = 0;
    ColorRGB col = ARR(COLOR_RGB_RED);
    if ((x <= -LEVEL_BOUNDARY_MAX)
     || (x >=  LEVEL_BOUNDARY_MAX)
     || (z <= -LEVEL_BOUNDARY_MAX)
     || (z >=  LEVEL_BOUNDARY_MAX)) return;
    register const CellIndex cellX = (((x + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX);
    register const CellIndex cellZ = (((z + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX);
    for ((i = 0); (i < 8); (i++)) {
        switch (i) {
            case 0: node = gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_WALLS ].next; vec3_copy(col, (ColorRGB)ARR(COLOR_RGB_GREEN )); break;
            case 1: node =  gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_WALLS ].next; vec3_copy(col, (ColorRGB)ARR(COLOR_RGB_GREEN )); break;
            case 2: node = gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_FLOORS].next; vec3_copy(col, (ColorRGB)ARR(COLOR_RGB_BLUE  )); break;
            case 3: node =  gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_FLOORS].next; vec3_copy(col, (ColorRGB)ARR(COLOR_RGB_BLUE  )); break;
            case 4: node = gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_CEILS ].next; vec3_copy(col, (ColorRGB)ARR(COLOR_RGB_RED   )); break;
            case 5: node =  gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_CEILS ].next; vec3_copy(col, (ColorRGB)ARR(COLOR_RGB_RED   )); break;
            case 6: node = gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_WATER ].next; vec3_copy(col, (ColorRGB)ARR(COLOR_RGB_YELLOW)); break;
            case 7: node =  gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_WATER ].next; vec3_copy(col, (ColorRGB)ARR(COLOR_RGB_YELLOW)); break;
        }
        while (node != NULL) {
            surf = node->surface; 
            node = node->next;
            make_vertex(verts, (gVisualSurfaceCount + 0), surf->vertex1[0], surf->vertex1[1], surf->vertex1[2], 0, 0, col[0], col[1], col[2], DBG_BOX_ALPHA);
            make_vertex(verts, (gVisualSurfaceCount + 1), surf->vertex2[0], surf->vertex2[1], surf->vertex2[2], 0, 0, col[0], col[1], col[2], DBG_BOX_ALPHA);
            make_vertex(verts, (gVisualSurfaceCount + 2), surf->vertex3[0], surf->vertex3[1], surf->vertex3[2], 0, 0, col[0], col[1], col[2], DBG_BOX_ALPHA);
            gVisualSurfaceCount+=3;
        }
    }
}

void iterate_surfaces_envbox(Vtx *verts) {
    Collision *p = gEnvironmentRegions;
    s32 i = 0;
    ColorRGB col = ARR(COLOR_RGB_YELLOW);
    if (p != NULL) {
        s32 numRegions = *p++;
        for ((i = 0); (i < numRegions); (i++)) {
            make_vertex(verts, (gVisualSurfaceCount + 0), p[1], p[5], p[2], 0, 0, col[0], col[1], col[2], DBG_BOX_ALPHA);
            make_vertex(verts, (gVisualSurfaceCount + 1), p[1], p[5], p[4], 0, 0, col[0], col[1], col[2], DBG_BOX_ALPHA);
            make_vertex(verts, (gVisualSurfaceCount + 2), p[3], p[5], p[2], 0, 0, col[0], col[1], col[2], DBG_BOX_ALPHA);
            make_vertex(verts, (gVisualSurfaceCount + 3), p[3], p[5], p[2], 0, 0, col[0], col[1], col[2], DBG_BOX_ALPHA);
            make_vertex(verts, (gVisualSurfaceCount + 4), p[1], p[5], p[4], 0, 0, col[0], col[1], col[2], DBG_BOX_ALPHA);
            make_vertex(verts, (gVisualSurfaceCount + 5), p[3], p[5], p[4], 0, 0, col[0], col[1], col[2], DBG_BOX_ALPHA);
            gVisualSurfaceCount += 6;
            gVisualOffset       += 6;
            p                   += 6;
        }
    }
}

#if defined(F3DEX_GBI_2) || defined(F3DEX_GBI)
#define VERTCOUNT 30
#else
#define VERTCOUNT 12
#endif // F3DEX_GBI_2

void visual_surface_display(Vtx *verts, s32 iteration) {
    s32 vts;
    s32 vtl = 0;
    s32 count = VERTCOUNT;
    s32 ntx = 0;
    if (!iteration) {
        vts = gVisualSurfaceCount;
    } else {
        vts = gVisualOffset;
    }
    while (vts > 0) {
        if (count == VERTCOUNT) {
            ntx = MIN(VERTCOUNT, vts);
            gSPVertex(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(verts + ((gVisualSurfaceCount)-vts)), ntx, 0);
            count = 0;
            vtl   = VERTCOUNT;
        }
        if (vtl >= 6) {
            gSP2Triangles(gDisplayListHead++, (count + 0), (count + 1), (count + 2), 0, (count + 3), (count + 4), (count + 5), 0);
            vts   -= 6;
            vtl   -= 6;
            count += 6;
        } else if (vtl >= 3) {
            gSP1Triangle(gDisplayListHead++, (count + 0), (count + 1), (count + 2), 0);
            vts   -= 3;
            vtl   -= 6;
            count += 3;
        }
    }
}

s32 iterate_surface_count(s32 x, s32 z) {
    struct SurfaceNode *node;
    s32 i = 0, j = 0;
    Collision *p = gEnvironmentRegions;
    s32 numRegions;
    if ((x <= -LEVEL_BOUNDARY_MAX)
     || (x >=  LEVEL_BOUNDARY_MAX)
     || (z <= -LEVEL_BOUNDARY_MAX)
     || (z >=  LEVEL_BOUNDARY_MAX)) return 0;
    register const CellIndex cellX = (((x + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX);
    register const CellIndex cellZ = (((z + LEVEL_BOUNDARY_MAX) / CELL_SIZE) & NUM_CELLS_INDEX);
    for ((i = 0); (i < 8); (i++)) {
        switch (i) {
            case 0: node = gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_WALLS ].next; break;
            case 1: node =  gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_WALLS ].next; break;
            case 2: node = gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_FLOORS].next; break;
            case 3: node =  gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_FLOORS].next; break;
            case 4: node = gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_CEILS ].next; break;
            case 5: node =  gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_CEILS ].next; break;
            case 6: node = gDynamicSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_WATER ].next; break;
            case 7: node =  gStaticSurfacePartition[cellZ][cellX][SPATIAL_PARTITION_WATER ].next; break;
        }
        while (node != NULL) {
            node = node->next;
            j++;
        }
    }
    if (p != NULL) {
        numRegions = *p++;
        j += (numRegions * 6);
    }
    return j;
}

void visual_surface_loop(void) {
    Vtx *verts;
    Mtx *mtx;
    if (!gSurfaceNodesAllocated || !gSurfacesAllocated || !gMarioState->marioObj) return;
    mtx =           alloc_display_list(sizeof(Mtx));
    verts = alloc_display_list((iterate_surface_count(gMarioState->pos[0], gMarioState->pos[2]) * 3) * sizeof(Vtx));
    gVisualSurfaceCount = 0;
    gVisualOffset       = 0;
    if ((mtx == NULL) || (verts == NULL)) return;
    mtxf_to_mtx(mtx, gMatStack[1]);
    gSPDisplayList(gDisplayListHead++, dl_visual_surface);
    gSPMatrix(     gDisplayListHead++, mtx, (G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH));
    iterate_surfaces_visual(gMarioState->pos[0], gMarioState->pos[2], verts);
    visual_surface_display(verts, 0);
    iterate_surfaces_envbox(verts);
    gSPDisplayList(gDisplayListHead++, dl_debug_box_begin_water);
    visual_surface_display(verts, 1);
    gSPPopMatrix(  gDisplayListHead++, G_MTX_MODELVIEW);
    gSPDisplayList(gDisplayListHead++, dl_debug_box_end);
}

/**
 * Adds a box to the list to be rendered this frame.
 *
 * If there are already MAX_DEBUG_BOXES boxes, does nothing.
 */
static void append_debug_box(Vec3f center, Vec3f bounds, Angle yaw, s32 type) {
    if (hitboxView) {
        if (sNumBoxes >= MAX_DEBUG_BOXES) return;
        vec3f_to_vec3s(sBoxes[sNumBoxes].center, center);
        vec3f_to_vec3s(sBoxes[sNumBoxes].bounds, bounds);
        sBoxes[sNumBoxes].yaw   = yaw;
        sBoxes[sNumBoxes].color = sCurBoxColor;
        sBoxes[sNumBoxes].type  = type;
        ++sNumBoxes;
    }
}

/**
 * Draw new boxes with the given color.
 * Color format is 32-bit ARGB.
 * If the alpha component is zero, DBG_BOX_ALPHA (0x7f) will be used instead.
 * Ex: 0xFF0000 becomes 0x7FFF0000
 */
void debug_box_color(RGBA32 color) {
    if ((color >> 24) == 0) color |= (DBG_BOX_ALPHA << 24);
    sCurBoxColor = color;
}

/**
 * Draws a debug box from (center - bounds) to (center + bounds)
 * To draw a rotated box, use debug_box_rot()
 *
 * @see debug_box_rot()
 */
void debug_box(Vec3f center, Vec3f bounds, s32 type) {
    append_debug_box(center, bounds, 0, type);
}

/**
 * Draws a debug box from (center - bounds) to (center + bounds), rotating it by `yaw`
 */
void debug_box_rot(Vec3f center, Vec3f bounds, Angle yaw, s32 type) {
    append_debug_box(center, bounds, yaw, type);
}

/**
 * Draws a debug box from pMin to pMax
 * To draw a rotated box this way, use debug_box_pos_rot()
 *
 * @see debug_box_pos_rot()
 */
void debug_box_pos(Vec3f pMin, Vec3f pMax, s32 type) {
    debug_box_pos_rot(pMin, pMax, 0, type);
}

/**
 * Draws a debug box from pMin to pMax, rotating it in the xz-plane by `yaw`
 */
void debug_box_pos_rot(Vec3f pMin, Vec3f pMax, Angle yaw, s32 type) {
    Vec3f center, bounds;
    bounds[0] = ((pMax[0] - pMin[0]) / 2.0f);
    bounds[1] = ((pMax[1] - pMin[1]) / 2.0f);
    bounds[2] = ((pMax[2] - pMin[2]) / 2.0f);
    vec3f_sum(center, pMin, bounds);
    append_debug_box(center, bounds, yaw, type);
}

#define DBG_BOX_VTX_BOX(i, x, y, z) make_vertex(debugBoxVtx,      i, x, y, z, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF)
#define DBG_BOX_VTX_CYL(i, x, y, z) make_vertex(debugCylinderVtx, i, x, y, z, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF)
#define CYLINDER_VERTS 24

static void render_box(int index, Vtx *vbox, Vtx *vcylinder) {
    Mtx *translate;
    Mtx *rotate;
    Mtx *scale;
    Mtx *mtx;
    struct DebugBox *box = &sBoxes[index];
    s32 color            = box->color;
    // Translate to the origin, rotate, then translate back, effectively rotating the box about
    // its center
    mtx       = alloc_display_list(sizeof(Mtx));
    translate = alloc_display_list(sizeof(Mtx));
    rotate    = alloc_display_list(sizeof(Mtx));
    scale     = alloc_display_list(sizeof(Mtx));
    if ((mtx == NULL) || (translate == NULL) || (rotate == NULL) || (scale == NULL)) return;
    mtxf_to_mtx(mtx, gMatStack[1]);
    guTranslate(translate, box->center[0],  box->center[1],  box->center[2]);
    guRotate(rotate, (box->yaw / (float)0x10000 * 360.0f), 0, 1.0f, 0);
    guScale(scale, ((f32) box->bounds[0] * 0.01f), ((f32) box->bounds[1] * 0.01f), ((f32) box->bounds[2] * 0.01f));
    gSPMatrix(     gDisplayListHead++, mtx,          (G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH));
    gSPMatrix(     gDisplayListHead++, translate,    (G_MTX_MODELVIEW | G_MTX_MUL  | G_MTX_NOPUSH));
    gSPMatrix(     gDisplayListHead++, rotate,       (G_MTX_MODELVIEW | G_MTX_MUL  | G_MTX_NOPUSH));
    gSPMatrix(     gDisplayListHead++, scale,        (G_MTX_MODELVIEW | G_MTX_MUL  | G_MTX_NOPUSH));
    gDPSetEnvColor(gDisplayListHead++, ((color >> 16) & 0xFF), ((color >> 8) & 0xFF), ((color) & 0xFF), ((color >> 24) & 0xFF));
    if (box->type == DEBUG_SHAPE_BOX) {
        gSPVertex(    gDisplayListHead++, VIRTUAL_TO_PHYSICAL(vbox), 8, 0);
        gSP2Triangles(gDisplayListHead++, 5, 4, 6, 0x0, 5, 6, 7, 0x0); // front
        gSP2Triangles(gDisplayListHead++, 0, 1, 2, 0x0, 2, 1, 3, 0x0); // back
        gSP2Triangles(gDisplayListHead++, 4, 0, 2, 0x0, 2, 6, 4, 0x0); // left
        gSP2Triangles(gDisplayListHead++, 1, 5, 3, 0x0, 3, 5, 7, 0x0); // right
        gSP2Triangles(gDisplayListHead++, 1, 0, 4, 0x0, 1, 4, 5, 0x0); // top
        gSP2Triangles(gDisplayListHead++, 2, 3, 6, 0x0, 6, 3, 7, 0x0); // bottom
    } else {
        gSPVertex(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(vcylinder), 26, 0);
        // Bottom
        /*
        gSP2Triangles(gDisplayListHead++,  0,  1,  3,  0,  0,  3,  5,  0);
        gSP2Triangles(gDisplayListHead++,  0,  5,  7,  0,  0,  7,  9,  0);
        gSP2Triangles(gDisplayListHead++,  0,  9, 11,  0,  0, 11, 13,  0);
        gSP2Triangles(gDisplayListHead++,  0, 13, 15,  0,  0, 15, 17,  0);
        gSP2Triangles(gDisplayListHead++,  0, 17, 19,  0,  0, 19, 21,  0);
        gSP2Triangles(gDisplayListHead++,  0, 21, 23,  0,  0, 23,  1,  0);
        */
        // Side
        gSP2Triangles(gDisplayListHead++,  1,  2,  3,  0,  2,  3,  4,  0);
        gSP2Triangles(gDisplayListHead++,  3,  4,  5,  0,  4,  5,  6,  0);
        gSP2Triangles(gDisplayListHead++,  5,  6,  7,  0,  6,  7,  8,  0);
        gSP2Triangles(gDisplayListHead++,  7,  8,  9,  0,  8,  9, 10,  0);
        gSP2Triangles(gDisplayListHead++,  9, 10, 11,  0, 10, 11, 12,  0);
        gSP2Triangles(gDisplayListHead++, 11, 12, 13,  0, 12, 13, 14,  0);
        gSP2Triangles(gDisplayListHead++, 13, 14, 15,  0, 14, 15, 16,  0);
        gSP2Triangles(gDisplayListHead++, 15, 16, 17,  0, 16, 17, 18,  0);
        gSP2Triangles(gDisplayListHead++, 17, 18, 19,  0, 18, 19, 20,  0);
        gSP2Triangles(gDisplayListHead++, 19, 20, 21,  0, 20, 21, 22,  0);
        gSP2Triangles(gDisplayListHead++, 21, 22, 23,  0, 22, 23, 24,  0);
        gSP2Triangles(gDisplayListHead++, 23, 24,  1,  0, 24,  1,  2,  0);
        // Top
        gSP2Triangles(gDisplayListHead++, 25,  2,  4,  0, 25,  4,  6,  0);
        gSP2Triangles(gDisplayListHead++, 25,  6,  8,  0, 25,  8, 10,  0);
        gSP2Triangles(gDisplayListHead++, 25, 10, 12,  0, 25, 12, 14,  0);
        gSP2Triangles(gDisplayListHead++, 25, 14, 16,  0, 25, 16, 18,  0);
        gSP2Triangles(gDisplayListHead++, 25, 18, 20,  0, 25, 20, 22,  0);
        gSP2Triangles(gDisplayListHead++, 25, 22, 24,  0, 25, 24,  2,  0);
    }
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
}

void render_debug_boxes(void) {
    s32 i;
    Vtx *debugBoxVtx;
    Vtx *debugCylinderVtx;
    debug_box_color(DBG_BOX_DEF_COLOR);
    if (sNumBoxes == 0) return;
    // Create the vertices for the box.
    debugBoxVtx      = alloc_display_list( 8 * sizeof(Vtx));
    debugCylinderVtx = alloc_display_list(26 * sizeof(Vtx));
    if ((debugBoxVtx == NULL) || (debugCylinderVtx == NULL)) return;
    DBG_BOX_VTX_BOX(0, -100,  100, -100);
    DBG_BOX_VTX_BOX(1,  100,  100, -100);
    DBG_BOX_VTX_BOX(2, -100, -100, -100);
    DBG_BOX_VTX_BOX(3,  100, -100, -100);
    DBG_BOX_VTX_BOX(4, -100,  100,  100);
    DBG_BOX_VTX_BOX(5,  100,  100,  100);
    DBG_BOX_VTX_BOX(6, -100, -100,  100);
    DBG_BOX_VTX_BOX(7,  100, -100,  100);
    DBG_BOX_VTX_CYL(0,    0,    0,    0);
    for ((i = 0); (i < (CYLINDER_VERTS)); (i++)) {
        DBG_BOX_VTX_CYL((1 + i),
        0 + (100 * coss((0xFFFF / ((CYLINDER_VERTS) / 2)) * (i / 2))),
        0 + (100 * (i & 0x1)),
        0 + (100 * sins((0xFFFF / ((CYLINDER_VERTS) / 2)) * (i / 2))));
    }
    DBG_BOX_VTX_CYL((CYLINDER_VERTS + 1), 0, 100, 0);
    gSPDisplayList(gDisplayListHead++, dl_debug_box_begin);
    for ((i = 0); (i < sNumBoxes); (++i)) render_box(i, debugBoxVtx, debugCylinderVtx);
    sNumBoxes = 0;
    gSPDisplayList(gDisplayListHead++, dl_debug_box_end);
}

#endif
