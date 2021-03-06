#pragma once

#include <types.h>
#define CRASH_SCREEN_INCLUDED 1
extern u32 cop0_get_cause(   void);
extern u32 cop0_get_epc(     void);
extern u32 cop0_get_badvaddr(void);
extern void _n64_assert(const char* pFile, int nLine, const char *pExpression, int nStopProgram);
extern u8 __crash_handler_entry[];
void show_crash_screen_and_hang(void);
u8   ascii_to_idx(char c);
void fb_set_address(void *address);
void fb_swap(void);
void fb_fill(int baseX, int baseY, int width, int height);
void fb_draw_char(       int x, int y, u8 idx);
void fb_draw_char_shaded(int x, int y, u8 idx);
int  fb_print_str(       int x, int y, const char *str);
int  fb_print_uint(      int x, int y, u32 value);
void fb_print_int_hex(   int x, int y, u32 value, int nbits);
void fb_print_gpr_states(int x, int y, const char* regStrs[], u32 *regContext);
