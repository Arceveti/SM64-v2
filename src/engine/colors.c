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
    dst[0] = composite_to_color(src, MSK_RGBA16_C, IDX_RGBA16_R);
    dst[1] = composite_to_color(src, MSK_RGBA16_C, IDX_RGBA16_G);
    dst[2] = composite_to_color(src, MSK_RGBA16_C, IDX_RGBA16_B);
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
    dst[0] = composite_to_colorf(src, MSK_RGBA16_C, IDX_RGBA16_R);
    dst[1] = composite_to_colorf(src, MSK_RGBA16_C, IDX_RGBA16_G);
    dst[2] = composite_to_colorf(src, MSK_RGBA16_C, IDX_RGBA16_B);
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

// void colorRGB_to_colorHSV(ColorHSV dst, ColorRGB src) {

// }

// void colorHSV_to_colorRGB(ColorRGB dst, ColorHSV src) {

// }

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
                        u32 dstW,  u32 dstH,  // 32, 32,
                        u32 dstTW, u32 dstTH, // 64, 32,
                        UNUSED u32 dstFormat, UNUSED u32 dstPixelSize,
                        s32 srcX,  s32 srcY,  //  0,  0,
                        u32 srcW,  u32 srcH,  // 64, 64,
                        u32 srcTW, u32 srcTH, // 64, 64,
                        UNUSED u32 srcFormat, UNUSED u32 srcPixelSize) {
    if (dstX > (s32)dstTW) return;
    if (dstY > (s32)dstTH) return;
    if (srcX > (s32)srcTW) return;
    if (srcY > (s32)srcTH) return;
    if ((dst == NULL) || (src == NULL)) return;
    u32 x, y;
    f32 srcIndex = 0, dstIndex = 0;
    const u32 srcStartIndex = ((srcY * srcTW) + srcX);
    const u32 dstStartIndex = ((dstY * dstTW) + dstX);
    const f32 dx = ((f32)srcW) / ((f32)dstW * 2.0f);
    const f32 dy = ((f32)srcH) / ((f32)dstH * 2.0f);
    u32 xdx, ydy;
    u32 dstIndexY, srcIndexY;
    u32 srcV, dstV;
    u32 dstColor, dstAlpha;
    u32 srcColor, srcAlpha;
    u32 resultColor;
    for ((y = 0); (y < dstH); (y++)) {          // loop rows
        if ((dstY + y  ) > dstTH) break;        // bounds check
        ydy = (y*dy);
        if ((srcY + ydy) > srcTH) break;        // bounds check
        srcIndexY = (srcStartIndex + (ydy * srcTW));
        dstIndexY = (dstStartIndex + (y   * dstTW));
        for ((x = 0); (x < dstW); (x++)) {      // loop columns
            if (dstX + x > dstTW) break;        // bounds check
            xdx = (x * dx);
            if ((srcX + xdx) > srcTW) break;    // bounds check
            srcIndex = (srcIndexY + xdx);
            dstIndex = (dstIndexY + x  );
            dstV = dst[(s32)dstIndex];
            srcV = src[(s32)srcIndex];
            // 0001 11111
            dstAlpha = ((dstV & 0x1) ? 0x1F : 0x0);
            if (dstAlpha == 0x0) continue;
            srcAlpha = (IA8_A(srcV) << 0x1);
            if (srcAlpha == 0x0) continue;
            dstColor = rgba16_get_average_color(dstV);
            srcColor = (IA8_I(srcV) << 0x1);
            if (srcColor == dstColor) continue;
            resultColor        = ((srcColor * srcAlpha / 0x1F) + (dstColor * dstAlpha * (0x1F - srcAlpha) / (0x3C1)));
            dst[(s32)dstIndex] = rgba16_set_grayscale(resultColor, 1);
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
