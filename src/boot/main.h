#pragma once

#include "config.h"

#ifdef VARIABLE_FRAMERATE
extern OSThread gInputLoopThread;
extern OSThread gGraphicsLoopThread;
extern OSMesg gInputReceivedMesg;
extern OSMesg gVideoReceivedMesg;
#endif

struct RumbleData {
    u8  comm;
    u8  level;
    s16 time;
    s16 decay;
};

struct RumbleSettings {
    s16 event;
    s16 level;
    s16 timer;
    s16 count;
    s16 start;
    s16 slip;
    s16 vibrate;
    s16 decay;
};
extern struct Config gConfig;

// extern OSThread gUnkThread;
extern OSThread gIdleThread;
extern OSThread gMainThread;
extern OSThread gGameLoopThread;
extern OSThread gSoundThread;
#ifdef HVQM
extern OSThread hvqmThread;
#endif
#if ENABLE_RUMBLE
extern OSThread gRumblePakThread;

extern OSPfs gRumblePakPfs;
#endif

extern OSMesgQueue gPIMesgQueue;
extern OSMesgQueue gIntrMesgQueue;
extern OSMesgQueue gSPTaskMesgQueue;
#if ENABLE_RUMBLE
extern OSMesgQueue gRumblePakSchedulerMesgQueue;
extern OSMesgQueue gRumbleThreadVIMesgQueue;
#endif
extern OSMesg      gDmaMesgBuf[1];
extern OSMesg      gPIMesgBuf[32];
extern OSMesg      gSIEventMesgBuf[1];
extern OSMesg      gIntrMesgBuf[16];
extern OSMesg      gUnknownMesgBuf[16];
extern OSIoMesg    gDmaIoMesg;
extern OSMesg      gMainReceivedMesg;
extern OSMesgQueue gDmaMesgQueue;
extern OSMesgQueue gSIEventMesgQueue;
#if ENABLE_RUMBLE
extern OSMesg gRumblePakSchedulerMesgBuf[1];
extern OSMesg gRumbleThreadVIMesgBuf[1];

extern struct RumbleData gRumbleDataQueue[3];
extern struct RumbleSettings gCurrRumbleSettings;
#endif

extern struct VblankHandler *gVblankHandler1;
extern struct VblankHandler *gVblankHandler2;
extern struct SPTask *gActiveSPTask;
extern u32 gNumVblanks;
extern s8  gResetTimer;
extern s8  gNmiResetBarsTimer;
extern Bool8 gDebugLevelSelect;
extern Bool8 gShowProfiler;
extern Bool8 gShowDebugText;

void set_vblank_handler(s32 index, struct VblankHandler *handler, OSMesgQueue *queue, OSMesg *msg);
void dispatch_audio_sptask(struct SPTask *spTask);
void exec_display_list(    struct SPTask *spTask);
