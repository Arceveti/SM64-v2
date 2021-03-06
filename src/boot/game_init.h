#pragma once

#include <PR/ultratypes.h>
#include <PR/gbi.h>
#include <PR/os_cont.h>
#include <PR/os_message.h>

#include "types.h"
#include "memory.h"
#include "segments.h"

#ifdef USE_EXT_RAM
#define GFX_POOL_SIZE 12800 // Size of how large the master display list (gDisplayListHead) can be
#else
#define GFX_POOL_SIZE 10000 // Size of how large the master display list (gDisplayListHead) can be
#endif

#ifdef VARIABLE_FRAMERATE
extern void thread7_input_loop(   UNUSED void *arg);
extern void thread9_graphics_loop(UNUSED void *arg);
extern f32 gMoveSpeed;
#endif

struct GfxPool {
    Gfx buffer[GFX_POOL_SIZE];
    struct SPTask spTask;
};

struct DemoInput
{
    u8 timer; // time until next input. if this value is 0, it means the demo is over
    s8 rawStickX;
    s8 rawStickY;
    u8 buttonMask;
};

enum ZBmodes {
    KEEP_ZBUFFER  = FALSE,
    CLEAR_ZBUFFER = TRUE,
};

extern struct Controller    gControllers[3];
extern OSContStatus         gControllerStatuses[4];
extern OSContPad            gControllerPads[4];
extern OSMesgQueue          gGameVblankQueue;
extern OSMesgQueue          gGfxVblankQueue;
extern OSMesg               gGameMesgBuf[1];
extern OSMesg               gGfxMesgBuf[1];
extern struct VblankHandler gGameVblankHandler;
extern uintptr_t            gPhysicalFrameBuffers[3];
extern uintptr_t            gPhysicalZBuffer;
#ifdef VARIABLE_FRAMERATE
extern void                *gMarioAnimsMemAlloc[2];
#else
extern void                *gMarioAnimsMemAlloc;
#endif
extern void                *gDemoInputsMemAlloc;
extern struct SPTask       *gGfxSPTask;
extern Gfx                 *gDisplayListHead;
extern u8                  *gGfxPoolEnd;
extern struct GfxPool      *gGfxPool;
extern u8                   gControllerBits;
extern Bool8                gIsConsole;
#ifdef CUSTOM_FOV
extern s16                  gFieldOfView;
#endif
#if SILHOUETTE
extern s16                  gSilhouette;
#endif
// #ifndef DISABLE_AA
// extern s16                  gAntiAliasing;
// #endif
#ifdef REONU_CAM_3
extern s8                   gCameraSpeed;
extern u8                   gWaterCamOverride;
extern u8                   gFlyingCamOverride;
extern Bool8                gKeepCliffCam;
#endif
extern u8                   gBorderHeight;
#ifdef CUSTOM_DEBUG
extern u8                   gCustomDebugMode;
#endif
extern u8 *gAreaSkyboxStart[AREA_COUNT];
extern u8 *gAreaSkyboxEnd  [AREA_COUNT];
#ifdef EEP
extern s8                   gEepromProbe;
#endif
#ifdef SRAM
extern s8                   gSramProbe;
#endif

extern void (*gGoddardVblankCallback)(void);
extern struct Controller *gPlayer1Controller;
extern struct Controller *gPlayer2Controller;
extern struct Controller *gPlayer3Controller;
extern struct DemoInput  *gCurrDemoInput;
extern              u16   gDemoInputListID;
extern struct DemoInput   gRecordedDemoInput;

// this area is the demo input + the header. when the demo is loaded in, there is a header the size
// of a single word next to the input list. this word is the current ID count.
#ifdef VARIABLE_FRAMERATE
extern struct DmaHandlerList gMarioAnimsBuf[2];
#else
extern struct DmaHandlerList gMarioAnimsBuf;
#endif
extern struct DmaHandlerList gDemoInputsBuf;

extern u8  gMarioAnims[];
extern u8  gDemoInputs[];

extern u16 sRenderingFrameBuffer;
extern u32 gGlobalTimer;

void setup_game_memory(void);
void thread5_game_loop(UNUSED void *arg);
void clear_frame_buffer(                   RGBA16FILL color);
void clear_viewport(         Vp *viewport, RGBA16FILL color);
void make_viewport_clip_rect(Vp *viewport);
void init_rcp(Bool32 resetZB);
void end_master_display_list(void);
void render_init(            void);
void select_gfx_pool(        void);
void display_and_vsync(      void);
