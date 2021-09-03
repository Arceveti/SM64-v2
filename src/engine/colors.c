// Functions for editing colors & textures

#include <PR/ultratypes.h>

#include "math_util.h"
#include "colors.h"

// i4
// A 0000 0000 0000 0000 0000 0000 0000 1111 >> 0x0  & 0xF  = 0-15 * (255/15 = 17)              = 0-255

// i8
// A 0000 0000 0000 0000 0000 0000 1111 1111 >> 0x0  & 0xFF                                     = 0-255

// ia4
// I 0000 0000 0000 0000 0000 0000 0000 1110 >> 0x1  & 0x7  = 0-7 * (255/7 = 36.4285714286)     = 0-255
// A 0000 0000 0000 0000 0000 0000 0000 0001 >> 0x0  & 0x1  = 0-255

// ia8
// I 0000 0000 0000 0000 0000 0000 1111 0000 >> 0x4  & 0xF  = 0-15 * (255/15 = 17)              = 0-255
// A 0000 0000 0000 0000 0000 0000 0000 1111 >> 0x0  & 0xF  = 0-15 * (255/15 = 17)              = 0-255

// ia16
// I 0000 0000 0000 0000 1111 1111 0000 0000 >> 0x8  & 0xFF                                     = 0-255
// A 0000 0000 0000 0000 0000 0000 1111 1111 >> 0x0  & 0xFF                                     = 0-255

// rgba16
//   0000 0000 0000 0000 0000 0000 0001 1111
// R 0000 0000 0000 0000 1111 1000 0000 0000 >> 0xB  & 0x1F = 0-31 * (255/31 = 8.22580645161)   = 0-255
// G 0000 0000 0000 0000 0000 0111 1100 0000 >> 0x6  & 0x1F = 0-31 * (255/31 = 8.22580645161)   = 0-255
// B 0000 0000 0000 0000 0000 0000 0011 1110 >> 0x1  & 0x1F = 0-31 * (255/31 = 8.22580645161)   = 0-255
// A 0000 0000 0000 0000 0000 0000 0000 0001 >> 0x0  & 0x1  = 0-1

// rgba32
// R 1111 1111 0000 0000 0000 0000 0000 0000 >> 0x20 & 0xFF                                     = 0-255
// G 0000 0000 1111 1111 0000 0000 0000 0000 >> 0x10 & 0xFF                                     = 0-255
// B 0000 0000 0000 0000 1111 1111 0000 0000 >> 0x8  & 0xFF                                     = 0-255
// A 0000 0000 0000 0000 0000 0000 1111 1111 >> 0x0  & 0xFF                                     = 0-255

// ci4
// P 0000 0000 0000 0000 0000 0000 0000 1111 >> 0x0  & 0xF  = 0-15 * (255/15 = 17)              = 0-255
// RGBA16

// ci8
// P 0000 0000 0000 0000 0000 0000 1111 1111 >> 0x0  & 0xFF                                     = 0-255
// RGBA16

// ColorRGB

Color composite_to_color(CompositeColor src, u32 bitmask, u32 index) {
    return ((((src >> index) & bitmask) * 255.0f) / bitmask);
}

void rgba16_to_colorRGB(ColorRGB dst, RGBA16 src) {
    dst[0] = composite_to_color(src, MSK_RGBA16_C, IDX_RGBA16_R);
    dst[1] = composite_to_color(src, MSK_RGBA16_C, IDX_RGBA16_G);
    dst[2] = composite_to_color(src, MSK_RGBA16_C, IDX_RGBA16_B);
}

void rgba16_to_colorRGBA(ColorRGBA dst, RGBA16 src) {
    rgba16_to_colorRGB(dst, src);
    dst[3] = composite_to_color(src, MSK_RGBA16_A, IDX_RGBA16_A);
}

CompositeColor color_to_composite(Color src, u32 bitmask, u32 index) {
    return (((CompositeColor)((src * bitmask) / 255.0f) & bitmask) << index);
}

RGBA16 colorRGB_to_rgba16(ColorRGB src) {
    return (color_to_composite(src[0], MSK_RGBA16_C, IDX_RGBA16_R)
          | color_to_composite(src[1], MSK_RGBA16_C, IDX_RGBA16_G)
          | color_to_composite(src[2], MSK_RGBA16_C, IDX_RGBA16_B)
          | MSK_RGBA16_A);
}

RGBA16 colorRGBA_to_rgba16(ColorRGBA src) {
    return (color_to_composite(src[0], MSK_RGBA16_C, IDX_RGBA16_R)
          | color_to_composite(src[1], MSK_RGBA16_C, IDX_RGBA16_G)
          | color_to_composite(src[2], MSK_RGBA16_C, IDX_RGBA16_B)
          | color_to_composite(src[2], MSK_RGBA16_A, IDX_RGBA16_A));
}

// ColorRGBf

ColorF composite_to_colorf(CompositeColor src, u32 bitmask, u32 index) {
    return ((ColorF)((src >> index) & bitmask) / bitmask);
}

void rgba16_to_colorRGBf(ColorRGBf dst, RGBA16 src) {
    dst[0] = composite_to_colorf(src, MSK_RGBA16_C, IDX_RGBA16_R);
    dst[1] = composite_to_colorf(src, MSK_RGBA16_C, IDX_RGBA16_G);
    dst[2] = composite_to_colorf(src, MSK_RGBA16_C, IDX_RGBA16_B);
}

void rgba16_to_colorRGBAf(ColorRGBAf dst, RGBA16 src) {
    rgba16_to_colorRGBf(dst, src);
    dst[3] = composite_to_colorf(src, MSK_RGBA16_A, IDX_RGBA16_A);
}

CompositeColor colorf_to_composite(ColorF src, u32 bitmask, u32 index) {
    return (((CompositeColor)(src * bitmask) & bitmask) << index);
}

RGBA16 colorRGBf_to_rgba16(ColorRGBf src) {
    return (colorf_to_composite(src[0], MSK_RGBA16_C, IDX_RGBA16_R)
          | colorf_to_composite(src[1], MSK_RGBA16_C, IDX_RGBA16_G)
          | colorf_to_composite(src[2], MSK_RGBA16_C, IDX_RGBA16_B)
          | MSK_RGBA16_A);
}

RGBA16 colorRGBAf_to_rgba16(ColorRGBAf src) {
    return (colorf_to_composite(src[0], MSK_RGBA16_C, IDX_RGBA16_R)
          | colorf_to_composite(src[1], MSK_RGBA16_C, IDX_RGBA16_G)
          | colorf_to_composite(src[2], MSK_RGBA16_C, IDX_RGBA16_B)
          | colorf_to_composite(src[2], MSK_RGBA16_A, IDX_RGBA16_A));
}

void colorRGB_to_colorRGBf(ColorRGBf dst, ColorRGB src) {
    dst[0] = (src[0] / 255.0f);
    dst[1] = (src[1] / 255.0f);
    dst[2] = (src[2] / 255.0f);
}

void colorRGBA_to_colorRGBAf(ColorRGBf dst, ColorRGB src) {
    colorRGB_to_colorRGBf(dst, src);
    dst[3] = (src[3] / 255.0f);
}

void colorRGBf_to_colorRGB(ColorRGB dst, ColorRGBf src) {
    dst[0] = (src[0] * 255.0f);
    dst[1] = (src[1] * 255.0f);
    dst[2] = (src[2] * 255.0f);
}

void colorRGBAf_to_colorRGBA(ColorRGBA dst, ColorRGBAf src) {
    colorRGBf_to_colorRGB(dst, src);
    dst[3] = (src[3] * 255.0f);
}

//! TODO:
// void colorRGB_to_colorHSV(ColorHSV dst, ColorRGB src) {
// }

// void colorHSV_to_colorRGB(ColorRGB dst, ColorHSV src) {
// }

// void colorRGBf_to_colorHSVf(ColorHSVf dst, ColorRGBf src) {
// }

// void colorHSVf_to_colorRGBf(ColorRGBf dst, ColorHSVf src) {
// }

/// Copy ColorRGB vector src to dest
void colorRGB_set(ColorRGB dest, Color r, Color g, Color b) {
    dest[0] = r;
    dest[1] = g;
    dest[2] = b;
}

/// Copy ColorRGB vector src to dest
void colorRGB_copy(ColorRGB dest, const ColorRGB src) {
    vec3_copy(dest, src);
}

void vec3s_to_colorRGB(ColorRGB dest, Vec3s src) {
    vec3_copy(dest, src);
}

// rgba16 value
RGBA16 rgba16_set(RGBA16Component r, RGBA16Component g, RGBA16Component b, RGBA16Component a) {
    return ((clamp_bits(r, SIZ_RGBA16_C) << IDX_RGBA16_R) |
            (clamp_bits(g, SIZ_RGBA16_C) << IDX_RGBA16_G) |
            (clamp_bits(b, SIZ_RGBA16_C) << IDX_RGBA16_B) |
            (a & SIZ_RGBA16_A));
}

// rgba16 value
RGBA16 rgba16_set_grayscale(RGBA16Component val, RGBA16Component alpha) {
    return rgba16_set(val, val, val, alpha);
}

// 0-31
RGBA16Component rgba16_get_average_color(RGBA16 rgba) {
    ColorRGBf color;
    ColorF avg;
    rgba16_to_colorRGBf(color, rgba);
    avg = vec3f_average(color);
    return colorf_to_composite(avg, MSK_RGBA16_C, 0);
}

RGBA16 rgba16_make_grayscale(RGBA16 rgba) {
    ColorRGBf color;
    ColorF avg;
    rgba16_to_colorRGBf(color, rgba);
    avg = vec3f_average(color);
    vec3f_set(color, avg, avg, avg);
    return colorRGBf_to_rgba16(color);
}

#define METALTEX_Y_MIN 76479 // ((SCREEN_WIDTH * (SCREEN_HEIGHT - 1)) - 1)
#define METALTEX_Y_MAX 76799 // ((SCREEN_WIDTH * (SCREEN_HEIGHT)) - 1)
#define METALTEX_DY       10 // (SCREEN_WIDTH / TEXTURE_HEIGHT)

#define METALTEX_X_MIN  2889 // (3 * trunc((SCREEN_HEIGHT - 1) / TEXTURE_WIDTH) * SCREEN_WIDTH) | (3 * dx)
#define METALTEX_X_MAX 64320 // ((TEXTURE_WIDTH + 3) * trunc((SCREEN_HEIGHT - 1) / TEXTURE_WIDTH) * SCREEN_WIDTH) | ((TEXTURE_WIDTH + 3) * dx)
#define METALTEX_DX      960 // (trunc((SCREEN_HEIGHT - 1) / TEXTURE_WIDTH) * SCREEN_WIDTH)

#ifdef METAL_CAP_REFLECTION_GRAYSCALE
void generate_metal_texture(ImageTexture *dst, ImageTexture *src) {
    u32 srcIndex = 0, dstIndex = 0;
    u32 y, x;
    for ((y = METALTEX_Y_MIN); (y < METALTEX_Y_MAX); (y += METALTEX_DY)) {
        for ((x = METALTEX_X_MIN); (x < METALTEX_X_MAX); (x += METALTEX_DX)) {
            dst[dstIndex] = rgba16_make_grayscale(src[srcIndex]);
            dstIndex++;
            srcIndex = (y - x);
        }
    }
}
#else
void generate_metal_texture(ImageTexture *dst, ImageTexture *src) {
    u32 srcIndex = 0, dstIndex = 0;
    u32 y, x;
    for ((y = METALTEX_Y_MIN); (y < METALTEX_Y_MAX); (y += METALTEX_DY)) {
        for ((x = METALTEX_X_MIN); (x < METALTEX_X_MAX); (x += METALTEX_DX)) {
            dst[dstIndex] = src[srcIndex];
            dstIndex++;
            srcIndex = (y - x);
        }
    }
}
#endif

// dstX, dstY   destination position to print to
// dstW, dstH   destination size
// dstTW, dstTH destination texture size
// srcX, srcY   source position to start reading from
// srcW, srcH   source sample size
// srcTW, srcTH source texture size
// 1 px dst x = dx px src x
// 1 px dst y = dy px src y
void copy_partial_image(ImageTexture *dst, ImageTexture *src,
                        s32 dstX,  s32 dstY,  // 16,  0,
                        s32 dstW,  s32 dstH,  // 32, 32,
                        s32 dstTW, s32 dstTH, // 64, 32,
                        UNUSED u32 dstFormat, UNUSED u32 dstPixelSize,
                        s32 srcX,  s32 srcY,  //  0,  0,
                        s32 srcW,  s32 srcH,  // 64, 64,
                        s32 srcTW, s32 srcTH, // 64, 64,
                        UNUSED u32 srcFormat, UNUSED u32 srcPixelSize) {
    if (dstX > dstTW) return;
    if (dstY > dstTH) return;
    if (srcX > srcTW) return;
    if (srcY > srcTH) return;
    if ((dst == NULL) || (src == NULL)) return;
    s32 x, y;
    s32 srcIndex = 0, dstIndex = 0;
    const u32 srcStartIndex = ((srcY * srcTW) + srcX);
    const u32 dstStartIndex = ((dstY * dstTW) + dstX);
    const f32 dx = ((srcW) / (dstW * 2.0f));
    const f32 dy = ((srcH) / (dstH * 2.0f));
    s32 xdx, ydy;
    s32 dstIndexY, srcIndexY;
    ColorF dstColor, srcColor;
    AlphaF srcAlpha;
    for ((y = 0); (y < dstH); (y++)) {          // loop rows
        if ((dstY + y  ) > dstTH) break;        // bounds check
        ydy = (y * dy);
        if ((srcY + ydy) > srcTH) break;        // bounds check
        srcIndexY = (srcStartIndex + (ydy * srcTW));
        dstIndexY = (dstStartIndex + (y   * dstTW));
        for ((x = 0); (x < dstW); (x++)) {      // loop columns
            if ((dstX + x) > dstTW) break;        // bounds check
            xdx = (x * dx);
            if ((srcX + xdx) > srcTW) break;    // bounds check
            srcIndex = (srcIndexY + xdx);
            dstIndex = (dstIndexY + x  );
            srcAlpha = composite_to_colorf(src[srcIndex], MSK_IA8_C, IDX_IA8_A);
            if (srcAlpha == 0.0f) continue;
            srcColor = composite_to_colorf(src[srcIndex], MSK_IA8_C, IDX_IA8_I);
            dstColor = composite_to_colorf(dst[dstIndex], MSK_RGBA16_C, IDX_RGBA16_B);
            if (srcColor == dstColor) continue;
            dst[dstIndex] = rgba16_set_grayscale(colorf_to_composite(((srcColor * srcAlpha) + (dstColor * (1.0f - srcAlpha))), MSK_RGBA16_C, 0), 1);
        }
    }
}

void overlay_i8_on_rgba16_additive(ImageTexture *dst, ImageTexture *src, u32 width, u32 height) {
    const u32 size = (width * height);
    u32 i;
    u32 srcI;
    u32 srcVal, dstVal;
    for ((i = 0); (i < size); (i++)) {
        srcVal = src[i >> 1];
        dstVal = dst[i     ];
        srcI = I8_TO_RGBA16_C(srcVal);
        if (srcI > 0x0) {
            dst[i] = rgba16_set((RGBA16_R(dstVal) + srcI),
                                (RGBA16_G(dstVal) + srcI),
                                (RGBA16_B(dstVal) + srcI), 0x1);
        }
    }
}

void colorRGB_add_hue(ColorRGB color, Color hueAdd, Color s) {
    Color min = min_3uc(color[0], color[1], color[2]);
    Color max = max_3uc(color[0], color[1], color[2]);
    if (min == max) return;
    f32 hue = 0.0f;
    if (       max == color[0]) { // red
        hue = (       (color[1] - color[2]) / (f32)(max - min));
    } else if (max == color[1]) { // green
        hue = (2.0f + (color[2] - color[0]) / (f32)(max - min));
    } else {                      // blue
        hue = (4.0f + (color[0] - color[1]) / (f32)(max - min));
    }
    if (hue < 0.0f) hue += 6.0f;
    // this is the algorithm to convert from RGB to HSV:
    Color h  = (((u8)((hue * (128.0f/3.0f)) + hueAdd) >> 2) * 3); // needs to u8 cycle before multiplying. 0..191
    Color i  =  (h >> 5);                                         // 0..5
    Color f  = ((h & 0x1F) << 3);                                 // 'fractional' part of 'i' 0..248 in jumps
    Color pv = (0xFF -   s                    );                  // pv will be in range 0..255
    Color qv = (0xFF - ((s *         f ) >> 8));
    Color tv = (0xFF - ((s * (0xFF - f)) >> 8));
    switch (i) {
        case 0: color[0] = 0xFF; color[1] =   tv; color[2] =   pv; break;
        case 1: color[0] =   qv; color[1] = 0xFF; color[2] =   pv; break;
        case 2: color[0] =   pv; color[1] = 0xFF; color[2] =   tv; break;
        case 3: color[0] =   pv; color[1] =   qv; color[2] = 0xFF; break;
        case 4: color[0] =   tv; color[1] =   pv; color[2] = 0xFF; break;
        case 5: color[0] = 0xFF; color[1] =   pv; color[2] =   qv; break;
    }
}
