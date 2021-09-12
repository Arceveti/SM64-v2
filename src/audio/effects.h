#ifndef AUDIO_EFFECTS_H
#define AUDIO_EFFECTS_H

#include <PR/ultratypes.h>

#include "internal.h"
#include "platform_info.h"

#define ADSR_STATE_DISABLED   0x0
#define ADSR_STATE_INITIAL    0x1
#define ADSR_STATE_START_LOOP 0x2
#define ADSR_STATE_LOOP       0x3
#define ADSR_STATE_FADE       0x4
#define ADSR_STATE_HANG       0x5
#define ADSR_STATE_DECAY      0x6
#define ADSR_STATE_RELEASE    0x7
#define ADSR_STATE_SUSTAIN    0x8

#define ADSR_ACTION_RELEASE (1 << 4) // 0x10
#define ADSR_ACTION_DECAY   (1 << 5) // 0x20
#define ADSR_ACTION_HANG    (1 << 6) // 0x40

#define ADSR_DISABLE  0
#define ADSR_HANG    -1
#define ADSR_GOTO    -2
#define ADSR_RESTART -3

// Envelopes are always stored as big endian, to match sequence files which are
// byte blobs and can embed envelopes. Hence this byteswapping macro.
#if IS_BIG_ENDIAN
#define BSWAP16(x) (x)
#else
#define BSWAP16(x) (((x) & 0xff) << 8 | (((x) >> 8) & 0xff))
#endif

void sequence_player_process_sound(struct SequencePlayer *seqPlayer);
void note_vibrato_update(struct Note *note);
void note_vibrato_init(  struct Note *note);
void adsr_init(struct AdsrState *adsr, struct AdsrEnvelope *envelope, s16 *volOut);
#if defined(VERSION_EU) || defined(VERSION_SH)
f32 adsr_update(struct AdsrState *adsr);
#else
s32 adsr_update(struct AdsrState *adsr);
#endif

#endif // AUDIO_EFFECTS_H
