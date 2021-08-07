#include <PR/ultratypes.h>

#include "config.h"
#include "prevent_bss_reordering.h"
#include "area.h"
#include "sm64.h"
#include "gfx_dimensions.h"
#include "behavior_data.h"
#include "game_init.h"
#include "object_list_processor.h"
#include "engine/math_util.h"
#include "engine/surface_load.h"
#include "ingame_menu.h"
#include "screen_transition.h"
#include "mario.h"
#include "mario_actions_cutscene.h"
#include "print.h"
#include "hud.h"
#include "audio/external.h"
#include "area.h"
#include "rendering_graph_node.h"
#include "level_update.h"
#include "engine/geo_layout.h"
#include "save_file.h"
#include "level_table.h"
#include "dialog_ids.h"

struct SpawnInfo gPlayerSpawnInfos[1];
struct GraphNode *gGraphNodePointers[MODEL_ID_COUNT];
struct Area gAreaData[8];

struct WarpTransition gWarpTransition;

s16 gCurrCourseNum;
s16 gCurrActNum;
s16 gCurrAreaIndex;
s16 gSavedCourseNum;
s16 gMenuOptSelectIndex;
s16 gSaveOptSelectIndex;

struct SpawnInfo    *gMarioSpawnInfo   = &gPlayerSpawnInfos[0];
struct GraphNode   **gLoadedGraphNodes =  gGraphNodePointers;
struct Area         *gAreas            =  gAreaData;
struct Area         *gCurrentArea      = NULL;
struct CreditsEntry *gCurrCreditsEntry = NULL;
Vp *gViewportOverride    = NULL;
Vp *gViewportClip        = NULL;
s16 gWarpTransDelay      = 0;
u32 gFBSetColor          = 0;
u32 gWarpTransFBSetColor = 0;
u8  gWarpTransRed        = 0;
u8  gWarpTransGreen      = 0;
u8  gWarpTransBlue       = 0;
s16 gCurrSaveFileNum     = 1;
s16 gCurrLevelNum        = LEVEL_MIN;

/*
 * The following two tables are used in get_mario_spawn_type() to determine spawn type
 * from warp behavior.
 * When looping through sWarpBhvSpawnTable, if the behavior function in the table matches
 * the spawn behavior executed, the index of that behavior is used with sSpawnTypeFromWarpBhv
*/

const BehaviorScript *sWarpBhvSpawnTable[] = {
    bhvDoorWarp,                bhvStar,                   bhvExitPodiumWarp,          bhvWarp,
    bhvWarpPipe,                bhvFadingWarp,             bhvInstantActiveWarp,       bhvAirborneWarp,
    bhvHardAirKnockBackWarp,    bhvSpinAirborneCircleWarp, bhvDeathWarp,               bhvSpinAirborneWarp,
    bhvFlyingWarp,              bhvSwimmingWarp,           bhvPaintingStarCollectWarp, bhvPaintingDeathWarp,
    bhvAirborneStarCollectWarp, bhvAirborneDeathWarp,      bhvLaunchStarCollectWarp,   bhvLaunchDeathWarp,
};

u8 sSpawnTypeFromWarpBhv[] = {
    MARIO_SPAWN_DOOR_WARP,             MARIO_SPAWN_IDLE,                 MARIO_SPAWN_PIPE,                  MARIO_SPAWN_PIPE,
    MARIO_SPAWN_PIPE,                  MARIO_SPAWN_TELEPORT,             MARIO_SPAWN_INSTANT_ACTIVE,        MARIO_SPAWN_AIRBORNE,
    MARIO_SPAWN_HARD_AIR_KNOCKBACK,    MARIO_SPAWN_SPIN_AIRBORNE_CIRCLE, MARIO_SPAWN_DEATH,                 MARIO_SPAWN_SPIN_AIRBORNE,
    MARIO_SPAWN_FLYING,                MARIO_SPAWN_SWIMMING,             MARIO_SPAWN_PAINTING_STAR_COLLECT, MARIO_SPAWN_PAINTING_DEATH,
    MARIO_SPAWN_AIRBORNE_STAR_COLLECT, MARIO_SPAWN_AIRBORNE_DEATH,       MARIO_SPAWN_LAUNCH_STAR_COLLECT,   MARIO_SPAWN_LAUNCH_DEATH,
};

Vp gViewport = { {
    { 640, 480, 511, 0 },
    { 640, 480, 511, 0 },
} };

#ifdef VERSION_EU
const char *gNoControllerMsg[] = {
    "NO CONTROLLER",
    "MANETTE DEBRANCHEE",
    "CONTROLLER FEHLT",
};
#endif

void override_viewport_and_clip(Vp *a, Vp *b, u8 c, u8 d, u8 e) {
    u16 sp6 = ((c >> 3) << 11) | ((d >> 3) << 6) | ((e >> 3) << 1) | 1;

    gFBSetColor = (sp6 << 16) | sp6;
    gViewportOverride = a;
    gViewportClip = b;
}

void set_warp_transition_rgb(u8 red, u8 green, u8 blue) {
    u16 warpTransitionRGBA16 = ((red >> 3) << 11) | ((green >> 3) << 6) | ((blue >> 3) << 1) | 1;

    gWarpTransFBSetColor = (warpTransitionRGBA16 << 16) | warpTransitionRGBA16;
    gWarpTransRed = red;
    gWarpTransGreen = green;
    gWarpTransBlue = blue;
}

void print_intro_text(void) {
#ifdef VERSION_EU
    s32 language = eu_get_language();
#endif
    if ((gGlobalTimer & 0x1F) < 20) {
        if (gControllerBits == 0) {
#ifdef VERSION_EU
            print_text_centered(SCREEN_WIDTH / 2, 20, gNoControllerMsg[language]);
#else
            print_text_centered(SCREEN_WIDTH / 2, 20, "NO CONTROLLER");
#endif
        } else {
#ifdef VERSION_EU
            print_text(GFX_DIMENSIONS_FROM_LEFT_EDGE(20), 20, "START");
#else
            print_text_centered(GFX_DIMENSIONS_FROM_LEFT_EDGE(60), 38, "PRESS");
            print_text_centered(GFX_DIMENSIONS_FROM_LEFT_EDGE(60), 20, "START");
#endif
        }
    }
}

u32 get_mario_spawn_type(struct Object *o) {
    s32 i;
    const BehaviorScript *behavior = virtual_to_segmented(0x13, o->behavior);
    for (i = 0; i < 20; i++) if (sWarpBhvSpawnTable[i] == behavior) return sSpawnTypeFromWarpBhv[i];
    return MARIO_SPAWN_NONE;
}

struct ObjectWarpNode *area_get_warp_node(u8 id) {
    struct ObjectWarpNode *node = NULL;
    for (node = gCurrentArea->warpNodes; node != NULL; node = node->next) if (node->node.id == id) break;
    return node;
}

struct ObjectWarpNode *area_get_warp_node_from_params(struct Object *o) {
    u8 id = (o->oBehParams & 0x00FF0000) >> 16;
    return area_get_warp_node(id);
}

void load_obj_warp_nodes(void) {
    struct ObjectWarpNode *warpNode;
    struct Object         *children = (struct Object *) gObjParentGraphNode.children;
    do {
        struct Object *obj = children;
        if (obj->activeFlags != ACTIVE_FLAG_DEACTIVATED && get_mario_spawn_type(obj) != 0) {
            warpNode = area_get_warp_node_from_params(obj);
            if (warpNode != NULL) warpNode->object = obj;
        }
    } while ((children = (struct Object *) children->header.gfx.node.next) != (struct Object *) gObjParentGraphNode.children);
}

void clear_areas(void) {
    s32 i;
    gCurrentArea                   = NULL;
    gWarpTransition.isActive       = FALSE;
    gWarpTransition.pauseRendering = FALSE;
    gMarioSpawnInfo->areaIndex     = -1;
    for (i = 0; i < 8; i++) {
        gAreaData[i].index             = i;
        gAreaData[i].flags             = 0;
        gAreaData[i].terrainType       = 0;
        gAreaData[i].graphNode         = NULL;
        gAreaData[i].terrainData       = NULL;
        gAreaData[i].surfaceRooms      = NULL;
        gAreaData[i].macroObjects      = NULL;
        gAreaData[i].warpNodes         = NULL;
        gAreaData[i].paintingWarpNodes = NULL;
        gAreaData[i].instantWarps      = NULL;
        gAreaData[i].objectSpawnInfos  = NULL;
        gAreaData[i].camera            = NULL;
        gAreaData[i].unused28          = NULL;
        gAreaData[i].whirlpools[0]     = NULL;
        gAreaData[i].whirlpools[1]     = NULL;
        gAreaData[i].dialog[0]         = DIALOG_NONE;
        gAreaData[i].dialog[1]         = DIALOG_NONE;
        gAreaData[i].musicParam        = 0;
        gAreaData[i].musicParam2       = 0;
    }
}

void clear_area_graph_nodes(void) {
    s32 i;
    if (gCurrentArea != NULL) {
        geo_call_global_function_nodes(&gCurrentArea->graphNode->node, GEO_CONTEXT_AREA_UNLOAD);
        gCurrentArea = NULL;
        gWarpTransition.isActive = FALSE;
    }
    for (i = 0; i < 8; i++) {
        if (gAreaData[i].graphNode != NULL) {
            geo_call_global_function_nodes(&gAreaData[i].graphNode->node, GEO_CONTEXT_AREA_INIT);
            gAreaData[i].graphNode = NULL;
        }
    }
}

void load_area(s32 index) {
    if (gCurrentArea == NULL && gAreaData[index].graphNode != NULL) {
        gCurrentArea   = &gAreaData[index];
        gCurrAreaIndex = gCurrentArea->index;
        if (gCurrentArea->terrainData != NULL) load_area_terrain(index, gCurrentArea->terrainData,
                                                                        gCurrentArea->surfaceRooms,
                                                                        gCurrentArea->macroObjects);
        if (gCurrentArea->objectSpawnInfos != NULL) spawn_objects_from_info(gCurrentArea->objectSpawnInfos);
        load_obj_warp_nodes();
        geo_call_global_function_nodes(&gCurrentArea->graphNode->node, GEO_CONTEXT_AREA_LOAD);
    }
}

void unload_area(void) {
    if (gCurrentArea != NULL) {
        unload_objects_from_area(gCurrentArea->index);
        geo_call_global_function_nodes(&gCurrentArea->graphNode->node, GEO_CONTEXT_AREA_UNLOAD);
        gCurrentArea->flags      = 0x0;
        gCurrentArea             = NULL;
        gWarpTransition.isActive = FALSE;
    }
}

void load_mario_area(void) {
    stop_sounds_in_continuous_banks();
    load_area(gMarioSpawnInfo->areaIndex);
    if (gCurrentArea->index == gMarioSpawnInfo->areaIndex) {
        gCurrentArea->flags |= 0x01;
        spawn_objects_from_info(gMarioSpawnInfo);
    }
}

void unload_mario_area(void) {
    if (gCurrentArea != NULL && (gCurrentArea->flags & 0x01)) {
        unload_objects_from_area(gMarioSpawnInfo->activeAreaIndex);
        gCurrentArea->flags &= ~0x01;
        if (gCurrentArea->flags == 0x0) unload_area();
    }
}

void change_area(s32 index) {
    s32 areaFlags = gCurrentArea->flags;
    if (gCurrAreaIndex != index) {
        unload_area();
        load_area(index);
        gCurrentArea->flags = areaFlags;
        gMarioObject->oActiveParticleFlags = 0;
    }
    if (areaFlags & 0x01) gMarioObject->header.gfx.areaIndex = index, gMarioSpawnInfo->areaIndex = index;
}

void area_update_objects(void) {
    gAreaUpdateCounter++;
    update_objects();
}

/*
 * Sets up the information needed to play a warp transition, including the
 * transition type, time in frames, and the RGB color that will fill the screen.
 */
void play_transition(s16 transType, s16 time, u8 red, u8 green, u8 blue) {
    gWarpTransition.isActive       = TRUE;
    gWarpTransition.type           = transType;
    gWarpTransition.time           = time;
    gWarpTransition.pauseRendering = FALSE;
    // The lowest bit of transType determines if the transition is fading in or out.
    if (transType & 1) {
        set_warp_transition_rgb(red, green, blue);
    } else {
        red = gWarpTransRed, green = gWarpTransGreen, blue = gWarpTransBlue;
    }
    if (transType < 8) { // if transition is RGB
        gWarpTransition.data.red   = red;
        gWarpTransition.data.green = green;
        gWarpTransition.data.blue  = blue;
    } else { // if transition is textured
        gWarpTransition.data.red   = red;
        gWarpTransition.data.green = green;
        gWarpTransition.data.blue  = blue;
        // Both the start and end textured transition are always located in the middle of the screen.
        // If you really wanted to, you could place the start at one corner and the end at
        // the opposite corner. This will make the transition image look like it is moving
        // across the screen.
        gWarpTransition.data.startTexX = SCREEN_WIDTH  / 2;
        gWarpTransition.data.startTexY = SCREEN_HEIGHT / 2;
        gWarpTransition.data.endTexX   = SCREEN_WIDTH  / 2;
        gWarpTransition.data.endTexY   = SCREEN_HEIGHT / 2;
        gWarpTransition.data.texTimer  = 0;
        if (transType & 1) { // Is the image fading in?
            gWarpTransition.data.startTexRadius = GFX_DIMENSIONS_FULL_RADIUS;
            gWarpTransition.data.endTexRadius   = (transType >= 0x0F ? 16 : 0);
        } else { // The image is fading out. (Reverses start & end circles)
            gWarpTransition.data.startTexRadius = (transType >= 0x0E ? 16 : 0);
            gWarpTransition.data.endTexRadius   = GFX_DIMENSIONS_FULL_RADIUS;
        }
    }
}

/*
 * Sets up the information needed to play a warp transition, including the
 * transition type, time in frames, and the RGB color that will fill the screen.
 * The transition will play only after a number of frames specified by 'delay'
 */
void play_transition_after_delay(s16 transType, s16 time, u8 red, u8 green, u8 blue, s16 delay) {
    gWarpTransDelay = delay; // Number of frames to delay playing the transition.
    play_transition(transType, time, red, green, blue);
}

#ifdef ENABLE_SCREEN_TINT_EFFECTS
// 0x0200EDA8 - 0x0200EDE8
static const Vtx vertex_screen_shade_box[] = {
    {{{     0,    -80,      0}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   130,    -80,      0}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{   130,      0,      0}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}},
    {{{     0,      0,      0}, 0, {     0,      0}, {0xff, 0xff, 0xff, 0xff}}},
};

// 0x0200EDE8 - 0x0200EE28
const Gfx dl_draw_screen_shade_box[] = {
    gsDPPipeSync(),
    gsSPClearGeometryMode(G_LIGHTING),
    gsDPSetCombineMode(G_CC_FADE, G_CC_FADE),
    gsDPSetRenderMode(G_RM_XLU_SURF, G_RM_XLU_SURF2),
    gsSPVertex(vertex_screen_shade_box, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPEndDisplayList(),
};

void shade_screen_color(u32 r, u32 g, u32 b, u32 a) {
    create_dl_translation_matrix(G_MTX_PUSH, GFX_DIMENSIONS_FROM_LEFT_EDGE(0), SCREEN_HEIGHT, 0);

    // This is a bit weird. It reuses the dialog text box (width 130, height -80),
    // so scale to at least fit the screen.
#ifndef WIDESCREEN
    create_dl_scale_matrix(G_MTX_NOPUSH, 2.6f, 3.4f, 1.0f);
#else
    create_dl_scale_matrix(G_MTX_NOPUSH, GFX_DIMENSIONS_ASPECT_RATIO * SCREEN_HEIGHT / 130.0f, 3.0f, 1.0f);
#endif

    gDPSetEnvColor(gDisplayListHead++, r, g, b, a);
    gSPDisplayList(gDisplayListHead++, dl_draw_screen_shade_box);
    gSPPopMatrix(  gDisplayListHead++, G_MTX_MODELVIEW);
}

void render_screen_overlay(void) {
    struct MarioState *m = gMarioState;
    Vec3s rgbWater       = {   5,  80, 150};
    Vec3s rgbHurt        = { 255,   0,   0};
    Vec3s rgb            = {   0,   0,   0};
    u32 aWater           = 0;
    u32 aHurt            = 0;
    u32 a                = 0;
#ifdef ENVIRONMENT_SCREEN_TINT
    f32 surfaceHeight    = -(gLakituState.oldPitch / 90.0f);
    f32 waterLevel       = find_water_level(     gLakituState.pos[0], gLakituState.pos[2]) + surfaceHeight + 40.0f;
    f32 gasLevel         = find_poison_gas_level(gLakituState.pos[0], gLakituState.pos[2]) + surfaceHeight + 40.0f;
    if (gLakituState.pos[1] < waterLevel) {
        aWater = (waterLevel - gLakituState.pos[1]);
    } else if (gLakituState.pos[1] < gasLevel) {
        aWater = (  gasLevel - gLakituState.pos[1]);
        vec3s_set(rgbWater, 255, 255, 0);
    }
    if (aWater > 63) aWater = 63;
#endif
#ifdef DAMAGE_SCREEN_TINT
    if (m->health < 0x100 && m->hurtShadeAlpha > 0) {
        m->hurtShadeAlpha--;
    } else if (m->hurtShadeAlpha >= 4) {
        m->hurtShadeAlpha -= 4;
    }
    aHurt = m->hurtShadeAlpha;
#endif
    a = aWater + aHurt;
    if (a > 0) {
#ifdef DAMAGE_SCREEN_TINT
        if (m->action == ACT_SHOCKED
         || m->action == ACT_WATER_SHOCKED
         || m->action == ACT_SHOCKWAVE_BOUNCE) vec3s_set(rgbHurt, 255, 238, 0);
#endif
        rgb[0] = ((rgbWater[0] * aWater) + (rgbHurt[0] * aHurt))/a;
        rgb[1] = ((rgbWater[1] * aWater) + (rgbHurt[1] * aHurt))/a;
        rgb[2] = ((rgbWater[2] * aWater) + (rgbHurt[2] * aHurt))/a;
        if (rgb[0] <   0) rgb[0] =   0;
        if (rgb[1] <   0) rgb[1] =   0;
        if (rgb[2] <   0) rgb[2] =   0;
        if (rgb[0] > 255) rgb[0] = 255;
        if (rgb[1] > 255) rgb[1] = 255;
        if (rgb[2] > 255) rgb[2] = 255;
        if (    a  > 255)     a  = 255;
        shade_screen_color(rgb[0], rgb[1], rgb[2], a);
    }
}
#endif

void render_game(void) {
    if (gCurrentArea != NULL && !gWarpTransition.pauseRendering) {
        geo_process_root(gCurrentArea->graphNode, gViewportOverride, gViewportClip, gFBSetColor);

        gSPViewport(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(&gViewport));

        gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, gBorderHeight, SCREEN_WIDTH, SCREEN_HEIGHT - gBorderHeight);
        render_hud();
#ifdef ENABLE_SCREEN_TINT_EFFECTS
        render_screen_overlay();
#endif
        gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        render_text_labels();
        do_cutscene_handler();
        print_displaying_credits_entry();
        gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, gBorderHeight, SCREEN_WIDTH, SCREEN_HEIGHT - gBorderHeight);
        gMenuOptSelectIndex = render_menus_and_dialogs();

        if (gMenuOptSelectIndex != 0) gSaveOptSelectIndex = gMenuOptSelectIndex;

        if (gViewportClip != NULL) {
            make_viewport_clip_rect(gViewportClip);
        } else {
            gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, gBorderHeight, SCREEN_WIDTH, SCREEN_HEIGHT - gBorderHeight);
        }
        if (gWarpTransition.isActive) {
            if (gWarpTransDelay == 0) {
                gWarpTransition.isActive = !render_screen_transition(0, gWarpTransition.type, gWarpTransition.time, &gWarpTransition.data);
                if (!gWarpTransition.isActive) {
                    if (gWarpTransition.type & 1) {
                        gWarpTransition.pauseRendering = TRUE;
                    } else {
                        set_warp_transition_rgb(0, 0, 0);
                    }
                }
            } else {
                gWarpTransDelay--;
            }
        }
    } else {
        render_text_labels();
        if (gViewportClip != NULL) {
            clear_viewport(gViewportClip, gWarpTransFBSetColor);
        } else {
            clear_frame_buffer(gWarpTransFBSetColor);
        }
    }
    gViewportOverride = NULL;
    gViewportClip     = NULL;
}
