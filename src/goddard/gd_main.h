#ifndef GD_MAIN_H
#define GD_MAIN_H

#include <PR/ultratypes.h>

#include "types.h"

// structs
struct GdControl { // gGdCtrl
    /* 0x00 */ s32 unk00;  // set but never used
    /* 0x04 */ u8  pad04[4];
    /* 0x08 */ s32 dleft; // Dpad-left (mask)
    /* 0x0C */ s32 dright; // Dpad-right (mask)
    /* 0x10 */ s32 dup; // Dpad-up (mask)
    /* 0x14 */ s32 ddown; // Dpad-down (mask)
    /* 0x18 */ s32 cleft; // bool C-left
    /* 0x1C */ s32 cright; // bool C-right
    /* 0x20 */ s32 cup; // bool C-up
    /* 0x24 */ s32 cdown; // bool C-down
    /* 0x28 */ void * unk28;     // null-checked ptr? symbol not deref-ed in extant code?
    /* 0x2C */ void * unk2C;     // some sort of old texture ptr? symbol not deref-ed in extant code?
    /* 0x30 */ void * unk30;     // null-checked ptr? symbol not deref-ed in extant code?
    /* 0x34 */ s32 btnA; // bool A button
    /* 0x38 */ s32 btnB; // bool B button
    /* 0x3C */ u8  pad3C[0x44-0x3C];
    /* 0x44 */ s32 trgL; // bool L trigger pressed
    /* 0x48 */ s32 trgR; // bool R trigger pressed
    /* 0x4C */ s32 unk4C;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 newStartPress; // toggle bit? start pressed?
    /* 0x58 */ u8  pad58[0x7C-0x58];
    /* 0x7C */ f32 stickXf;
    /* 0x80 */ f32 stickYf;
    /* 0x84 */ u8  pad84[0xB8-0x84];
    /* 0xB8 */ s32 dragStartX; // cursor x position when there was a new (A) press?
    /* 0xBC */ s32 dragStartY; // cursor y position when there was a new (A) press?
    /* 0xC0 */ s32 stickDeltaX;
    /* 0xC4 */ s32 stickDeltaY;
    /* 0xC8 */ s32 stickX;
    /* 0xCC */ s32 stickY;
    /* 0xD0 */ s32 csrX; // bounded by screen view
    /* 0xD4 */ s32 csrY; // bounded by screen view
    /* 0xD8 */ /* hand/cursor state bitfield? */
        /* b80 */ Bool8 dragging        : TRUE; // bool (A) pressed
        /* b40 */ Bool8 unkD8b40        : TRUE; // set to FALSE and unused
        /* b20 */ Bool8 unkD8b20        : TRUE; // set to FALSE and unused
        /* b10 */ Bool8 startedDragging : TRUE;  // bool new (A) press
        /* b08 */ Bool8 unkD8b08        : TRUE;
        /* b04 */ Bool8 unkD8b04        : TRUE;
        /* b02 */ Bool8 AbtnPressWait   : TRUE;  // bool 10 frames between (A) presses (cursor cool down?)
    /* 0xDC */ u32 dragStartFrame; // first frame of new a press
    /* 0xE0 */ u8  padE0[0xE8-0xE0];
    /* 0xE8 */ u32 currFrame; // frame count?
    /* 0xEC */ u8  padEC[0xF0-0xEC];
    /* 0xF0 */ struct GdControl *prevFrame; // previous frame data
};

// bss
extern struct GdControl gGdCtrl;
extern struct GdControl gGdCtrlPrev;

#endif // GD_MAIN_H
