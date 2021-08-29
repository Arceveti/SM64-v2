// Not everything here works, probably -Arceveti

#include <PR/ultratypes.h>

#include "math_util.h"
// #include "gfx_dimensions.h"
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

#define BITMASK(size)   (u32)((1 << (size)) - 1)

#define IDX_RGBA16_R 0xB
#define IDX_RGBA16_G 0x6
#define IDX_RGBA16_B 0x1
#define SIZ_RGBA16_RGB 5
#define MSK_RGBA16_RGB BITMASK(SIZ_RGBA16_RGB)
#define IDX_RGBA16_A 0x0
#define SIZ_RGBA16_A   1
#define MSK_RGBA16_A BITMASK(SIZ_RGBA16_A)

u32 clamp_bits(u32 val, u32 size) {
    return MIN(val, BITMASK(size));
}

Color component_to_color(CompositeColor src, u32 bitmask, u32 index) {
    return ((((src >> index) & bitmask) * 255.0f) / bitmask);
}

CompositeColor color_to_component(Color src, u32 bitmask, u32 index) {
    return (((u32)((src * bitmask) / 255.0f) & bitmask) << index);
}

void rgba16_to_colorRGB(ColorRGB dst, RGBA16 src) {
    dst[0] = component_to_color(src, MSK_RGBA16_RGB, IDX_RGBA16_R);
    dst[1] = component_to_color(src, MSK_RGBA16_RGB, IDX_RGBA16_G);
    dst[2] = component_to_color(src, MSK_RGBA16_RGB, IDX_RGBA16_B);
}

void rgba16_to_colorRGBA(ColorRGBA dst, RGBA16 src) {
    dst[0] = component_to_color(src, MSK_RGBA16_RGB, IDX_RGBA16_R);
    dst[1] = component_to_color(src, MSK_RGBA16_RGB, IDX_RGBA16_G);
    dst[2] = component_to_color(src, MSK_RGBA16_RGB, IDX_RGBA16_B);
    dst[3] = component_to_color(src, MSK_RGBA16_A  , IDX_RGBA16_A);
}

RGBA16 colorRGB_to_rgba16(ColorRGB src) {
    return (color_to_component(src[0], MSK_RGBA16_RGB, IDX_RGBA16_R)
          | color_to_component(src[1], MSK_RGBA16_RGB, IDX_RGBA16_G)
          | color_to_component(src[2], MSK_RGBA16_RGB, IDX_RGBA16_B)
          | 0x1);
}

RGBA16 colorRGBA_to_rgba16(ColorRGBA src) {
    return (color_to_component(src[0], MSK_RGBA16_RGB, IDX_RGBA16_R)
          | color_to_component(src[1], MSK_RGBA16_RGB, IDX_RGBA16_G)
          | color_to_component(src[2], MSK_RGBA16_RGB, IDX_RGBA16_B)
          | color_to_component(src[2], MSK_RGBA16_A  , IDX_RGBA16_A));
}

// void colorRGB_to_colorHSV(ColorHSV dst, ColorRGB src) {
    
// }

// rgba16 value
u32 rgba16_set(u32 r, u32 g, u32 b, u32 a) {
    return ((clamp_bits(r, SIZ_RGBA16_RGB) << IDX_RGBA16_R) |
            (clamp_bits(g, SIZ_RGBA16_RGB) << IDX_RGBA16_G) |
            (clamp_bits(b, SIZ_RGBA16_RGB) << IDX_RGBA16_B) |
            (a & SIZ_RGBA16_A));
}

// rgba16 value
u32 rgba16_set_grayscale(u32 val, u32 alpha) {
    return rgba16_set(val, val, val, alpha);
}

// rgba16 value
u32 value_to_rgba16(u32 val) {
    return rgba16_set(val, val, val, 1);
}

// 0-31
u32 rgba16_get_red(u32 rgba) {
    return ((rgba >> 0xB) & 0x1F);
}

// 0-31
u32 rgba16_get_blue(u32 rgba) {
    return ((rgba >> 0x6) & 0x1F);
}

// 0-31
u32 rgba16_get_green(u32 rgba) {
    return ((rgba >> 0x1) & 0x1F);
}

// 0-1
u32 rgba16_get_alpha(u32 rgba) {
    return rgba & 0x1;
}



// 0-15
u32 ia8_get_color(u32 ia) {
    return ((ia >> 0x4) & 0xF);
}

// 0-15
u32 ia8_get_alpha(u32 ia) {
    return (ia & 0xF);
}

// 0-255
u32 ia16_get_color(u32 ia) {
    return ((ia >> 0x8) & 0xFF);
}

// 0-255
u32 ia16_get_alpha(u32 ia) {
    return (ia & 0xFF);
}

// ia8 value
u32 ia8_set(u32 i, u32 a) {
    return ((i & 0xF) << 0x4) | (a & 0xF);
}

// ia16 value
u32 ia16_set(u32 i, u32 a) {
    return ((i & 0xFF) << 0x8) | (a & 0xFF);
}

// 0-31
u32 rgba16_get_average_color(u32 rgba) {
    return (((rgba16_get_red(rgba) +
             rgba16_get_blue(rgba) +
             rgba16_get_green(rgba)) / 3) & 0x1F);
}

// rgba value
u32 rgba16_set_average_color(u32 rgba) {
    return rgba16_set_grayscale(rgba16_get_average_color(rgba), rgba16_get_alpha(rgba));
}

u32 i4_to_rgba16_color(u32 i) {
    return ((i << 1) & 0x1F);
}

u32 i8_to_rgba16_color(u32 i) {
    return ((i >> 3) & 0x1F);
}



u32 i4_to_rgba16(u32 i) {
    return rgba16_set_grayscale(i4_to_rgba16_color(i), 1);
}

u32 i8_to_rgba16(u32 i) {
    return rgba16_set_grayscale(i8_to_rgba16_color(i), 1);
}



// rgba16 value
u32 ia8_to_rgba16_threshhold(u32 ia, u32 alphaThreshhold) {
    const u32 color = ((ia >> 3) & 0x1F);
    return rgba16_set_grayscale(color, ((ia8_get_alpha(ia) >= alphaThreshhold) ? 1 : 0));
}

// rgba16 value
u32 ia16_to_rgba16_thresshold(u32 ia, u32 alphaThreshhold) {
    const u32 color = ((ia >> 11) & 0x1F);
    return rgba16_set_grayscale(color, ((ia16_get_alpha(ia) >= alphaThreshhold) ? 1 : 0));
}



// rgba16 value
u32 ia8_to_rgba16(u32 ia) {
    const u32 color = (ia8_get_color(ia) << 0x1);//(ia >> 3) & 0x1F;
    const u32 alpha = ((ia >> 3) & 0x1); //!?
    return rgba16_set_grayscale(color, alpha);
}

// rgba16 value
u32 ia16_to_rgba16(u32 ia) {
    const u32 color = ((ia >> 11) & 0x1F);
    const u32 alpha = ((ia >>  7) & 0x1); //!?
    return rgba16_set_grayscale(color, alpha);
}



// ia8 value
u32 rgba16_to_ia8(u32 rgba) {
    return ((rgba16_get_average_color(rgba) << 4) | ((rgba & 0x1) < 3));
}

// ia8_value
u32 rgba16_to_ia16(u32 rgba) {
    return ((rgba16_get_average_color(rgba) << 12) | ((rgba & 0x1) < 7));
}

#define METALTEX_Y_MIN 76479 // (SCREEN_WIDTH * (SCREEN_HEIGHT - 1)) - 1
#define METALTEX_Y_MAX 76799 // (SCREEN_WIDTH * (SCREEN_HEIGHT)) - 1
#define METALTEX_DY       10 // SCREEN_WIDTH/TEXTURE_HEIGHT

#define METALTEX_X_MIN  2889 // 3 * trunc((SCREEN_HEIGHT - 1)/TEXTURE_WIDTH) * SCREEN_WIDTH | 3 * dx
#define METALTEX_X_MAX 64320 // (TEXTURE_WIDTH + 3) * trunc((SCREEN_HEIGHT - 1) / TEXTURE_WIDTH) * SCREEN_WIDTH | (TEXTURE_WIDTH + 3) * dx
#define METALTEX_DX      960 // trunc((SCREEN_HEIGHT - 1) / TEXTURE_WIDTH) * SCREEN_WIDTH

#ifdef METAL_CAP_REFLECTION_GRAYSCALE
void generate_metal_texture(u16 *dst, u16 *src) {
    u32 srcIndex = 0, dstIndex = 0;
    u32 y, x;
    for ((y = METALTEX_Y_MIN); (y < METALTEX_Y_MAX); (y += METALTEX_DY)) {
        for ((x = METALTEX_X_MIN); (x < METALTEX_X_MAX); (x += METALTEX_DX)) {
            dst[dstIndex] = rgba16_set_grayscale(rgba16_get_average_color(src[srcIndex]), 1);
            dstIndex++;
            srcIndex = (y - x);
        }
    }
}
#else
void generate_metal_texture(u16 *dst, u16 *src) {
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
void copy_partial_image(u16 *dst,  u16 *src,
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
        if ((dstY + y) > dstTH) break;          // bounds check
        ydy = (y*dy);
        if ((srcY + ydy) > srcTH) break;        // bounds check
        srcIndexY = (srcStartIndex + (ydy * srcTW));
        dstIndexY = (dstStartIndex + (y * dstTW));
        for ((x = 0); (x < dstW); (x++)) {      // loop columns
            if (dstX + x > dstTW) break;        // bounds check
            xdx = (x * dx);
            if ((srcX + xdx) > srcTW) break;    // bounds check
            srcIndex = (srcIndexY + xdx);
            dstIndex = (dstIndexY + x);
            dstV = dst[(s32)dstIndex];
            srcV = src[(s32)srcIndex];
            // 0001 11111
            dstAlpha = ((dstV & 0x1) ? 0x1F : 0x0);
            if (dstAlpha == 0x0) continue;
            srcAlpha = (ia8_get_alpha(srcV) << 0x1);
            if (srcAlpha == 0x0) continue;
            dstColor = rgba16_get_average_color(dstV);
            srcColor = (ia8_get_color(srcV) << 0x1);
            if (srcColor == dstColor) continue;
            resultColor        = ((srcColor * srcAlpha / 0x1F) + (dstColor * dstAlpha * (0x1F - srcAlpha) / (0x3C1)));
            dst[(s32)dstIndex] = rgba16_set_grayscale(resultColor, 1);
        }
    }
}

void overlay_i8_on_rgba16_additive(u16 *dst, u16 *src, u32 width, u32 height) {
    const u32 size = width*height;
    u32 i;
    u32 srcI;
    u32 srcVal, dstVal;
    for ((i = 0); (i < size); (i++)) {
        srcVal = src[i >> 1];
        dstVal = dst[i     ];
        srcI = i8_to_rgba16_color(srcVal);
        if (srcI > 0x0) {
            dst[i] = rgba16_set((rgba16_get_red(  dstVal) + srcI),
                                (rgba16_get_blue( dstVal) + srcI),
                                (rgba16_get_green(dstVal) + srcI), 0x1);
        }
    }
}
