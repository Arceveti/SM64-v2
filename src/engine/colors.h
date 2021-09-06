#ifndef COLORS_H
#define COLORS_H

#include <PR/ultratypes.h>
#include <PR/gbi.h>

#include "types.h"
#include "math_util.h"

#define COLOR_RGBA_WHITE            { 0xFF, 0xFF, 0xFF, 0xFF }
// Grayscale color presets
#define COLOR_RGB_WHITE             { 0xFF, 0xFF, 0xFF } // 255 255 255
#define COLOR_RGB_LIGHT             { 0xBF, 0xBF, 0xBF } // 191 191 191
#define COLOR_RGB_GRAY              { 0x7F, 0x7F, 0x7F } // 127 127 127
#define COLOR_RGB_DARK              { 0x3F, 0x3F, 0x3F } //  63  63  63
#define COLOR_RGB_BLACK             { 0x00, 0x00, 0x00 } //   0   0   0
// Primary/secondary/tertiary color presets
#define COLOR_RGB_RED               { 0xFF, 0x00, 0x00 } // 255   0   0
#define COLOR_RGB_ORANGE            { 0xFF, 0x7F, 0x00 } // 255 127   0
#define COLOR_RGB_YELLOW            { 0xFF, 0xFF, 0x00 } // 255 255   0
#define COLOR_RGB_LIME              { 0x7F, 0xFF, 0x00 } // 127 255   0
#define COLOR_RGB_GREEN             { 0x00, 0xFF, 0x00 } //   0 255   0
#define COLOR_RGB_SPRING            { 0x00, 0xFF, 0x7F } //   0 255 127
#define COLOR_RGB_CYAN              { 0x00, 0xFF, 0xFF } //   0 255 255
#define COLOR_RGB_SKY               { 0x00, 0x7F, 0xFF } //   0 127 255
#define COLOR_RGB_BLUE              { 0x00, 0x00, 0xFF } //   0   0 255
#define COLOR_RGB_PURPLE            { 0x7F, 0x00, 0xFF } // 127   0 255
#define COLOR_RGB_MAGENTA           { 0xFF, 0x00, 0xFF } // 255   0 255
#define COLOR_RGB_PINK              { 0xFF, 0x00, 0x7F } // 255   0 127
// Elemental color presets
#define COLOR_RGB_JRB_SKY           { 0x50, 0x64, 0x5A } //  80 100  90
#define COLOR_RGB_WATER             { 0x05, 0x50, 0x96 } //   5  80 150
#define COLOR_RGB_LAVA              { 0x8F, 0x06, 0x00 } // 143   6   0
#define COLOR_RGB_SAND              { 0xDC, 0xA9, 0x73 } // 220 169 115
#define COLOR_RGB_ELECTRIC          { 0xFF, 0xEE, 0x00 } // 255 238   0
// Goddard-specific
#define COLOR_RGBF_WHITE            { 1.0f, 1.0f, 1.0f }
#define COLOR_RGBF_RED              { 1.0f, 0.0f, 0.0f }
#define COLOR_RGBF_GREEN            { 0.0f, 1.0f, 0.0f }
#define COLOR_RGBF_BLUE             { 0.0f, 0.0f, 1.0f }
#define COLOR_RGBF_ERR_DARK_BLUE    { 0.0f, 0.0f, 6.0f }
#define COLOR_RGBF_PINK             { 1.0f, 0.0f, 1.0f }
#define COLOR_RGBF_BLACK            { 0.0f, 0.0f, 0.0f }
#define COLOR_RGBF_GREY             { 0.6f, 0.6f, 0.6f }
#define COLOR_RGBF_DARK_GREY        { 0.4f, 0.4f, 0.4f }
#define COLOR_RGBF_YELLOW           { 1.0f, 1.0f, 1.0f }

// I4
#define SIZ_I4      0x4
#define MSK_I4      BITMASK(SIZ_I4)

// I8
#define SIZ_I8      0x8
#define MSK_I8      BITMASK(SIZ_I8)

// IA4
#define SIZ_IA4_I   0x3
#define MSK_IA4_I   BITMASK(SIZ_IA4_I)
#define IDX_IA4_I   ((SIZ_IA4_I * 0) + 1)
#define IA4_I(c)    (((c) >> IDX_IA4_I) & MSK_IA4_I)
#define I_IA4(c)    (((c) & MSK_IA4_I) << IDX_IA4_I)
#define SIZ_IA4_A   0x1
#define MSK_IA4_A   BITMASK(SIZ_IA4_A)
#define IDX_IA4_A   ((SIZ_IA4_A * 0) + 0)
#define IA4_A(c)    (((c) >> IDX_IA4_A) & MSK_IA4_A)
#define A_IA4(c)    (((c) & MSK_IA4_A) << IDX_IA4_A)

// IA8
#define SIZ_IA8_C   0x4
#define MSK_IA8_C   BITMASK(SIZ_IA8_C)
#define IDX_IA8_I   ((SIZ_IA8_C * 1) + 0)
#define IDX_IA8_A   ((SIZ_IA8_C * 0) + 0)
#define IA8_I(c)    (((c) >> IDX_IA8_I) & MSK_IA8_C)
#define IA8_A(c)    (((c) >> IDX_IA8_A) & MSK_IA8_C)
#define I_IA8(c)    (((c) & MSK_IA8_C) << IDX_IA8_I)
#define A_IA8(c)    (((c) & MSK_IA8_C) << IDX_IA8_A)

// IA16
#define SIZ_IA16_C  0x8
#define MSK_IA16_C  BITMASK(SIZ_IA16_C)
#define IDX_IA16_I  ((SIZ_IA16_C * 1) + 0)
#define IDX_IA16_A  ((SIZ_IA16_C * 0) + 0)
#define IA16_I(c)   (((c) >> IDX_IA16_I) & MSK_IA16_C)
#define IA16_A(c)   (((c) >> IDX_IA16_A) & MSK_IA16_C)
#define I_IA16(c)   (((c) & MSK_IA16_C) << IDX_IA16_I)
#define A_IA16(c)   (((c) & MSK_IA16_C) << IDX_IA16_A)

// RGBA16
#define SIZ_RGBA16_C 0x5
#define MSK_RGBA16_C BITMASK(SIZ_RGBA16_C)
#define IDX_RGBA16_R ((SIZ_RGBA16_C * 2) + 1)
#define IDX_RGBA16_G ((SIZ_RGBA16_C * 1) + 1)
#define IDX_RGBA16_B ((SIZ_RGBA16_C * 0) + 1)
#define RGBA16_R(c)  (((c) >> IDX_RGBA16_R) & MSK_RGBA16_C)
#define RGBA16_G(c)  (((c) >> IDX_RGBA16_G) & MSK_RGBA16_C)
#define RGBA16_B(c)  (((c) >> IDX_RGBA16_B) & MSK_RGBA16_C)
#define R_RGBA16(c)  (((c) & MSK_RGBA16_C) << IDX_RGBA16_R)
#define G_RGBA16(c)  (((c) & MSK_RGBA16_C) << IDX_RGBA16_G)
#define B_RGBA16(c)  (((c) & MSK_RGBA16_C) << IDX_RGBA16_B)
#define SIZ_RGBA16_A 0x1
#define MSK_RGBA16_A BITMASK(SIZ_RGBA16_A)
#define IDX_RGBA16_A ((SIZ_RGBA16_A * 0) + 0)
#define RGBA16_A(c)  (((c) >> IDX_RGBA16_A) & MSK_RGBA16_A)
#define A_RGBA16(c)  (((c) & MSK_RGBA16_A) << IDX_RGBA16_A)

// RGBA32
#define SIZ_RGBA32_C 0x08
#define MSK_RGBA32_C BITMASK(SIZ_RGBA32_C)
#define IDX_RGBA32_R ((SIZ_RGBA32_C * 3) + 0)
#define IDX_RGBA32_G ((SIZ_RGBA32_C * 2) + 0)
#define IDX_RGBA32_B ((SIZ_RGBA32_C * 1) + 0)
#define IDX_RGBA32_A ((SIZ_RGBA32_C * 0) + 0)
#define RGBA32_R(c)  (((c) >> IDX_RGBA32_R) & MSK_RGBA32_C)
#define RGBA32_G(c)  (((c) >> IDX_RGBA32_G) & MSK_RGBA32_C)
#define RGBA32_B(c)  (((c) >> IDX_RGBA32_B) & MSK_RGBA32_C)
#define RGBA32_A(c)  (((c) >> IDX_RGBA32_A) & MSK_RGBA32_C)
#define R_RGBA32(c)  (((c) & MSK_RGBA32_C) << IDX_RGBA32_R)
#define G_RGBA32(c)  (((c) & MSK_RGBA32_C) << IDX_RGBA32_G)
#define B_RGBA32(c)  (((c) & MSK_RGBA32_C) << IDX_RGBA32_B)
#define A_RGBA32(c)  (((c) & MSK_RGBA32_A) << IDX_RGBA32_A)

// CI4
#define SIZ_CI4 0x4
#define MSK_CI4 BITMASK(SIZ_CI4)

// CI8
#define SIZ_CI8 0x8
#define MSK_CI8 BITMASK(SIZ_CI8)

// Direct format conversions:
#define I4_TO_RGBA16_C(c)   (((c) << (SIZ_RGBA16_C - SIZ_I4)) & MSK_RGBA16_C)
#define I8_TO_RGBA16_C(c)   (((c) >> (SIZ_I8 - SIZ_RGBA16_C)) & MSK_RGBA16_C)

#define colorRGB_set(    dst, r, g, b) vec3_set( (dst), (r), (g), (b))
#define colorRGB_copy(   dst, src    ) vec3_copy((dst), (src)        )
#define colorRGB_to_vec3(dst, src    ) vec3_copy((dst), (src)        )
#define vec3_to_colorRGB(dst, src    ) vec3_copy((dst), (src)        )

Bool32 colorRGBA_average_2(ColorRGBA dst, ColorRGBA c1, ColorRGBA c2);
Bool32 colorRGBA_average_3(ColorRGBA dst, ColorRGBA c1, ColorRGBA c2, ColorRGBA c3);

void generate_metal_texture(u16 *dst,      u16 *src);
void copy_partial_image(    u16 *dst,      u16 *src,
                            s32 dstX,      s32 dstY,
                            s32 dstW,      s32 dstH,
                            s32 dstTW,     s32 dstTH,
                            u32 dstFormat, u32 dstPixelSize,
                            s32 srcX,      s32 srcY,
                            s32 srcW,      s32 srcH,
                            s32 srcTW,     s32 srcTH,
                            u32 srcFormat, u32 srcPixelSize);
void overlay_i8_on_rgba16_additive(u16 *dst, u16 *src, u32 width, u32 height);
void colorRGB_add_hue(ColorRGB color, Color hueAdd, Color s);

#endif // SHADOW_H
