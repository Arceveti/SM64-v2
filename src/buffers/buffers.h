#pragma once

#include <PR/ultratypes.h>
#ifdef HVQM
#include <hvqm2dec.h>
#endif

#include "game/save_file.h"
#include "boot/game_init.h"
#include "config.h"

extern u8 gDecompressionHeap[];

extern u8 gAudioHeap[];

extern u8 gIdleThreadStack[];
extern u8 gThread3Stack[];
extern u8 gThread4Stack[];
extern u8 gThread5Stack[];
#if ENABLE_RUMBLE
extern u8 gThread6Stack[];
#endif
#ifdef VARIABLE_FRAMERATE
extern u8 gThread7Stack[];
extern u8 gThread9Stack[];
#endif

extern u8 gGfxSPTaskYieldBuffer[];

extern struct SaveBuffer gSaveBuffer;

extern u8 gGfxSPTaskStack[];

extern struct GfxPool gGfxPools[2];

#ifdef HVQM
extern u8 adpcmbuf[];			/* Buffer for audio records ADPCM)  */

extern u64 hvq_yieldbuf[];		/* RSP task yield buffer            */
extern HVQM2Info hvq_spfifo[];	/* Data area for HVQM2 microcode    */
extern u16 hvqwork[];			/* Work buffer for HVQM2 decoder    */
extern u8 hvqbuf[];				/* Buffer for video records (HVQM2) */
#endif
