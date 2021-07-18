#include "internal.h"
#include "data.h"

#ifdef VERSION_SH

struct ReverbSettingsEU sReverbSettings[] = {
    {0x01, 0x30, 0x2fff, 0x0000, 0x0000, -1, 0x3000, 0x0000, 0x0000},
    {0x01, 0x28, 0x47ff, 0x0000, 0x0000, -1, 0x3000, 0x0000, 0x0000},
    {0x01, 0x40, 0x2fff, 0x0000, 0x0000, -1, 0x3000, 0x0000, 0x0000},
    {0x01, 0x38, 0x3fff, 0x0000, 0x0000, -1, 0x3000, 0x0000, 0x0000},
    {0x01, 0x30, 0x4fff, 0x0000, 0x0000, -1, 0x3000, 0x0000, 0x0000},
    {0x01, 0x28, 0x37ff, 0x0000, 0x0000, -1, 0x3000, 0x0000, 0x0000},
};

struct AudioSessionSettingsEU gAudioSessionPresets[] = {
    { 0x00007d00, 0x01, 0x10, 0x01, 0x00, &sReverbSettings[0], 0x7fff, 0x0000, 0x00003a40, 0x00006d00,
      0x00000000, 0x00004400, 0x00002a00, 0x00000000, 0x00000000, 0x00000000 },
    { 0x00007d00, 0x01, 0x10, 0x01, 0x00, &sReverbSettings[1], 0x7fff, 0x0000, 0x00003a40, 0x00006d00,
      0x00000000, 0x00004400, 0x00002a00, 0x00000000, 0x00000000, 0x00000000 },
    { 0x00007d00, 0x01, 0x10, 0x01, 0x00, &sReverbSettings[2], 0x7fff, 0x0000, 0x00003a40, 0x00006d00,
      0x00000000, 0x00004400, 0x00002a00, 0x00000000, 0x00000000, 0x00000000 },
    { 0x00007d00, 0x01, 0x10, 0x01, 0x00, &sReverbSettings[3], 0x7fff, 0x0000, 0x00003a40, 0x00006d00,
      0x00000000, 0x00004400, 0x00002a00, 0x00000000, 0x00000000, 0x00000000 },
    { 0x00007d00, 0x01, 0x10, 0x01, 0x00, &sReverbSettings[4], 0x7fff, 0x0000, 0x00003a40, 0x00006d00,
      0x00000000, 0x00004400, 0x00002a00, 0x00000000, 0x00000000, 0x00000000 },
    { 0x00007d00, 0x01, 0x10, 0x01, 0x00, &sReverbSettings[0], 0x7fff, 0x0000, 0x00004000, 0x00006e00,
      0x00000000, 0x00003f00, 0x00002a00, 0x00000000, 0x00000000, 0x00000000 },
    { 0x00007d00, 0x01, 0x10, 0x01, 0x00, &sReverbSettings[1], 0x7fff, 0x0000, 0x00004100, 0x00006e00,
      0x00000000, 0x00004400, 0x00002a80, 0x00000000, 0x00000000, 0x00000000 },
    { 0x00007d00, 0x01, 0x14, 0x01, 0x00, &sReverbSettings[5], 0x7fff, 0x0000, 0x00003500, 0x00006280,
      0x00000000, 0x00004000, 0x00001b00, 0x00000000, 0x00000000, 0x00000000 }
};

// s8 gUnusedCount80333EE8 = UNUSED_COUNT_80333EE8;
s16 gTatumsPerBeat = TATUMS_PER_BEAT;
s32 gAudioHeapSize = DOUBLE_SIZE_ON_64_BIT(AUDIO_HEAP_SIZE);
s32 gAudioInitPoolSize = DOUBLE_SIZE_ON_64_BIT(AUDIO_INIT_POOL_SIZE);

// Used in audio_init:
u32 D_SH_80315EF0 = 0;
u16 D_SH_80315EF4 = 0;
u16 D_SH_80315EF8 = 0;
u16 D_SH_80315EFC = 0;

#endif
