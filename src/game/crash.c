
/* SM64 Crash Handler */
#include <sm64.h>
#include "crash.h"
#include "engine/colors.h"
extern u32 exceptionRegContext[];
extern char *pAssertFile;
extern int nAssertLine;
extern char *pAssertExpression;
extern int nAssertStopProgram;
RGBA16 fbFillColor    = 0xFFFF;
RGBA16 fbShadeColor   = 0x0000;
RGBA16 *fbAddress = NULL;
extern u8 crashFont[];
const char *szErrCodes[] = {
    "INTERRUPT",
    "TLB MOD",
    "UNMAPPED LOAD ADDR",
    "UNMAPPED STORE ADDR",
    "BAD LOAD ADDR",
    "BAD STORE ADDR",
    "BUS ERR ON INSTR FETCH",
    "BUS ERR ON LOADSTORE",
    "SYSCALL",
    "BREAKPOINT",
    "UNKNOWN INSTR",
    "COP UNUSABLE",
    "ARITHMETIC OVERFLOW",
    "TRAP EXC",
    "VIRTUAL COHERENCY INSTR",
    "FLOAT EXC",
};
const char *szGPRegisters1[] = { "R0", "AT", "V0", "V1", "A0", "A1", "A2", "A3",
                                 "T0", "T1", "T2", "T3", "T4", "T5", "T6", NULL };
const char *szGPRegisters2[] = { "T7", "S0", "S1", "S2", "S3", "S4",
                                 "S5", "S6", "S7", "T8", "T9", /*"K0", "K1",*/
                                 "GP", "SP", "FP", "RA", NULL };
int crash_strlen(char *str) {
    int len = 0;
    while (*str++) len++;
    return len;
}
void show_crash_screen_and_hang(void) {
    u32 cause;
    u32 epc;
    u8 errno;
    fb_set_address((void *) (*(u32 *) 0xA4400004 | 0x80000000)); // replace me
    cause = cop0_get_cause();
    epc   = cop0_get_epc();
    errno = ((cause >> 2) & 0x1F);
    if (nAssertStopProgram == 0) {
        fbFillColor = COLOR_RGBA16_CRASH_ERROR;
        fb_fill(10, 10, 300, 220);
        fb_print_str(80, 20, "AN ERROR HAS OCCURRED!");
        fb_print_int_hex(80, 30, errno, 8);
        fb_print_str(95, 30, szErrCodes[errno]);
        if ((errno >= 2) && (errno <= 5)) {
            /*
            2 UNMAPPED LOAD ADDR
            3 UNMAPPED STORE ADDR
            4 BAD LOAD ADDR
            5 BAD STORE ADDR
            */
            u32 badvaddr = cop0_get_badvaddr();
            fb_print_str(145, 50, "VA");
            fb_print_int_hex(160, 50, badvaddr, 32);
        }
    } else {
        int afterFileX;
        int exprBoxWidth;
        fbFillColor = COLOR_RGBA16_CRASH_ASSERT;
        fb_fill(10, 10, 300, 220);
        fb_print_str(80, 20, "ASSERTION FAILED!");
        afterFileX = fb_print_str(80, 30, pAssertFile);
        fb_print_str(afterFileX, 30, ":");
        fb_print_uint((afterFileX + 5), 30, nAssertLine);
        exprBoxWidth = ((crash_strlen(pAssertExpression) * 5) + 2);
        fbFillColor  = 0x0001;
        fb_fill((80 - 1), (40 - 1), exprBoxWidth, 10);
        fb_print_str(80, 40, pAssertExpression);
    }
    fb_print_str(80, 50, "PC");
    fb_print_int_hex(95, 50, epc, 32);
    fb_print_gpr_states( 80, 70, szGPRegisters1, &exceptionRegContext[6 + 0]);
    fb_print_gpr_states(145, 70, szGPRegisters2, &exceptionRegContext[6 + (15 * 2)]);
    fb_swap();
    osWritebackDCacheAll();
    while (TRUE) {// hang forever
        UNUSED volatile int t = 0; // keep pj64 happy
    }
}

u8 ascii_to_idx(char c) {
    return (c - 0x20);
}

void fb_set_address(void *address) {
    fbAddress = (RGBA16 *) address;
}

void fb_swap() {
    // update VI frame buffer register
    // todo other registers
    *(u32 *) (0xA4400004) = (u32) fbAddress & 0x00FFFFFF;
}

void fb_fill(int baseX, int baseY, int width, int height) {
    int y, x;
    for ((y = baseY); (y < (baseY + height)); (y++)) {
        for ((x = baseX); (x < (baseX + width)); (x++)) {
            fbAddress[(y * 320) + x] = fbFillColor;
        }
    }
}

void fb_draw_char(int x, int y, u8 idx) {
    RGBA16 *out = &fbAddress[(y * 320) + x];
    const u8 *in = &crashFont[idx * 3];
    int nbyte;
    int nrow;
    int ncol;
    for ((nbyte = 0); (nbyte < 3); (nbyte++)) {
        u8 curbyte = in[nbyte];
        for ((nrow = 0); (nrow < 2); (nrow++)) {
            for ((ncol = 0); (ncol < 4); (ncol++)) {
                u8 px = (curbyte & (1 << (7 - ((nrow * 4) + ncol))));
                if (px != 0) out[ncol] = fbFillColor;
            }
            out += 320;
        }
    }
}

void fb_draw_char_shaded(int x, int y, u8 idx) {
    fbFillColor = COLOR_RGBA16_CRASH_BLACK;
    fb_draw_char((x - 1), (y + 1), idx);
    fbFillColor = COLOR_RGBA16_CRASH_WHITE;
    fb_draw_char(x, y, idx);
}

int fb_print_str(int x, int y, const char *str) {
    while (1) {
        int yoffs = 0;
        u8 idx;
        char c = *str++;
        if (c == '\0')  break;
        if (c == ' ') {
            x += 5;
            continue;
        }
        switch (c) {
            case 'j':
            case 'g':
            case 'p':
            case 'q':
            case 'y':
            case 'Q':
                yoffs = 1;
                break;
            case ',':
                yoffs = 2;
                break;
        }
        idx = ascii_to_idx(c);
        fb_draw_char_shaded(x, (y + yoffs), idx);
        x += 5;
    }
    return x;
}

void fb_print_int_hex(int x, int y, u32 value, int nbits) {
    nbits -= 4;
    while (nbits >= 0) {
        int nib = ((value >> nbits) & 0xF);
        u8 idx;
        if (nib > 9) {
            idx = (('A' - 0x20) + (nib - 0xa));
        } else {
            idx = (('0' - 0x20) + nib);
        }
        fb_draw_char_shaded(x, y, idx);
        x     += 5;
        nbits -= 4;
    }
}

int fb_print_uint(int x, int y, u32 value) {
    int nchars = 0;
    int v      = value;
    int i;
    while (v /= 10) nchars++;
    x += (nchars * 5);
    for ((i = nchars); (i >= 0); (i--)) {
        fb_draw_char_shaded(x, y, (('0' - 0x20) + (value % 10)));
        value /= 10;
        x     -= 5;
    }
    return (x + (nchars * 5));
}

void fb_print_gpr_states(int x, int y, const char *regNames[], u32 *regContext) {
    int i;
    for ((i = 0); ; (i++)) {
        if (regNames[i] == NULL) break;
        fb_print_str(x, y, regNames[i]);
        fb_print_int_hex((x + 15), y, regContext[(i * 2) + 1], 32);
        y += 10;
    }
}
