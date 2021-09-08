// Functions for editing colors & textures

#include <PR/ultratypes.h>

#include "math_util.h"
#include "colors.h"

// ColorRGB

void rgba16_to_colorRGB(ColorRGB dst, RGBA16 src) {
    dst[0] = COMPOSITE_TO_COLOR(src, MSK_RGBA16_C, IDX_RGBA16_R);
    dst[1] = COMPOSITE_TO_COLOR(src, MSK_RGBA16_C, IDX_RGBA16_G);
    dst[2] = COMPOSITE_TO_COLOR(src, MSK_RGBA16_C, IDX_RGBA16_B);
}

void rgba16_to_colorRGBA(ColorRGBA dst, RGBA16 src) {
    rgba16_to_colorRGB(dst, src);
    dst[3] = COMPOSITE_TO_COLOR(src, MSK_RGBA16_A, IDX_RGBA16_A);
}

RGBA16 colorRGB_to_rgba16(ColorRGB src) {
    return (COLOR_TO_COMPOSITE(src[0], MSK_RGBA16_C, IDX_RGBA16_R)
          | COLOR_TO_COMPOSITE(src[1], MSK_RGBA16_C, IDX_RGBA16_G)
          | COLOR_TO_COMPOSITE(src[2], MSK_RGBA16_C, IDX_RGBA16_B)
          | MSK_RGBA16_A);
}

RGBA16 colorRGBA_to_rgba16(ColorRGBA src) {
    return (COLOR_TO_COMPOSITE(src[0], MSK_RGBA16_C, IDX_RGBA16_R)
          | COLOR_TO_COMPOSITE(src[1], MSK_RGBA16_C, IDX_RGBA16_G)
          | COLOR_TO_COMPOSITE(src[2], MSK_RGBA16_C, IDX_RGBA16_B)
          | COLOR_TO_COMPOSITE(src[2], MSK_RGBA16_A, IDX_RGBA16_A));
}

// ColorRGBf

void rgba16_to_colorRGBf(ColorRGBf dst, RGBA16 src) {
    dst[0] = COMPOSITE_TO_COLORF(src, MSK_RGBA16_C, IDX_RGBA16_R);
    dst[1] = COMPOSITE_TO_COLORF(src, MSK_RGBA16_C, IDX_RGBA16_G);
    dst[2] = COMPOSITE_TO_COLORF(src, MSK_RGBA16_C, IDX_RGBA16_B);
}

void rgba16_to_colorRGBAf(ColorRGBAf dst, RGBA16 src) {
    rgba16_to_colorRGBf(dst, src);
    dst[3] = COMPOSITE_TO_COLORF(src, MSK_RGBA16_A, IDX_RGBA16_A);
}

// CompositeColor colorf_to_composite(ColorF src, u32 bitmask, u32 index) {
//     return (((CompositeColor)(src * bitmask) & bitmask) << index);
// }

RGBA16 colorRGBf_to_rgba16(ColorRGBf src) {
    return (COLORF_TO_COMPOSITE(src[0], MSK_RGBA16_C, IDX_RGBA16_R)
          | COLORF_TO_COMPOSITE(src[1], MSK_RGBA16_C, IDX_RGBA16_G)
          | COLORF_TO_COMPOSITE(src[2], MSK_RGBA16_C, IDX_RGBA16_B)
          | MSK_RGBA16_A);
}

RGBA16 colorRGBAf_to_rgba16(ColorRGBAf src) {
    return (COLORF_TO_COMPOSITE(src[0], MSK_RGBA16_C, IDX_RGBA16_R)
          | COLORF_TO_COMPOSITE(src[1], MSK_RGBA16_C, IDX_RGBA16_G)
          | COLORF_TO_COMPOSITE(src[2], MSK_RGBA16_C, IDX_RGBA16_B)
          | COLORF_TO_COMPOSITE(src[2], MSK_RGBA16_A, IDX_RGBA16_A));
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

Bool32 colorRGBA_average_2(ColorRGBA dst, ColorRGBA c1, ColorRGBA c2) {
    if ((dst[3] = (c1[3] + c2[3])) > 0) {
        dst[0] = (((c1[0] * c1[3]) + (c2[0] * c2[3])) / dst[3]);
        dst[1] = (((c1[1] * c1[3]) + (c2[1] * c2[3])) / dst[3]);
        dst[2] = (((c1[2] * c1[3]) + (c2[2] * c2[3])) / dst[3]);
        return TRUE;
    }
    return FALSE;
}

Bool32 colorRGBA_average_3(ColorRGBA dst, ColorRGBA c1, ColorRGBA c2, ColorRGBA c3) {
    if ((dst[3] = (c1[3] + c2[3] + c3[3])) > 0) {
        dst[0] = (((c1[0] * c1[3]) + (c2[0] * c2[3]) + (c3[0] * c3[3])) / dst[3]);
        dst[1] = (((c1[1] * c1[3]) + (c2[1] * c2[3]) + (c3[1] * c3[3])) / dst[3]);
        dst[2] = (((c1[2] * c1[3]) + (c2[2] * c2[3]) + (c3[2] * c3[3])) / dst[3]);
        return TRUE;
    }
    return FALSE;
}

// 0-31
UNUSED RGBA16Component rgba16_get_average_component(RGBA16 rgba) {
    ColorRGBf color;
    ColorF avg;
    rgba16_to_colorRGBf(color, rgba);
    avg = vec3_average(color);
    return COLORF_TO_COMPOSITE(avg, MSK_RGBA16_C, 0);
}

RGBA16 rgba16_make_grayscale(RGBA16 rgba) {
    ColorRGBf color;
    ColorF avg;
    rgba16_to_colorRGBf(color, rgba);
    avg = vec3_average(color);
    vec3_set(color, avg, avg, avg);
    return colorRGBf_to_rgba16(color);
}

#define METALTEX_Y_MIN 76479 // ((SCREEN_WIDTH * (SCREEN_HEIGHT - 1)) - 1)
#define METALTEX_Y_MAX 76799 // ((SCREEN_WIDTH * (SCREEN_HEIGHT)) - 1)
#define METALTEX_DY       10 // (SCREEN_WIDTH / TEXTURE_HEIGHT)

#define METALTEX_X_MIN  2889 // (3 * trunc((SCREEN_HEIGHT - 1) / TEXTURE_WIDTH) * SCREEN_WIDTH) | (3 * dx)
#define METALTEX_X_MAX 64320 // ((TEXTURE_WIDTH + 3) * trunc((SCREEN_HEIGHT - 1) / TEXTURE_WIDTH) * SCREEN_WIDTH) | ((TEXTURE_WIDTH + 3) * dx)
#define METALTEX_DX      960 // (trunc((SCREEN_HEIGHT - 1) / TEXTURE_WIDTH) * SCREEN_WIDTH)

#ifdef METAL_CAP_REFLECTION_GRAYSCALE
void generate_metal_texture(TexturePtr *dst, TexturePtr *src) {
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
void generate_metal_texture(TexturePtr *dst, TexturePtr *src) {
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
void copy_partial_image(TexturePtr *dst, TexturePtr *src,
                        s32 dstX,  s32 dstY,  // 16,  0,
                        s32 dstW,  s32 dstH,  // 32, 32,
                        s32 dstTW, s32 dstTH, // 64, 32,
                        s32 srcX,  s32 srcY,  //  0,  0,
                        s32 srcW,  s32 srcH,  // 64, 64,
                        s32 srcTW, s32 srcTH  // 64, 64,
                        ) {
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
            if ((dstX + x) > dstTW) break;      // bounds check
            xdx = (x * dx);
            if ((srcX + xdx) > srcTW) break;    // bounds check
            srcIndex = (srcIndexY + xdx);
            dstIndex = (dstIndexY + x  );
            srcAlpha = COMPOSITE_TO_COLORF(src[srcIndex], MSK_IA8_C,    IDX_IA8_A);
            if (srcAlpha == 0.0f) continue;
            srcColor = COMPOSITE_TO_COLORF(src[srcIndex], MSK_IA8_C,    IDX_IA8_I);
            dstColor = COMPOSITE_TO_COLORF(dst[dstIndex], MSK_RGBA16_C, IDX_RGBA16_B);
            if (srcColor == dstColor) continue;
            dst[dstIndex] = RGBA16_COMPOSITE_GRAYSCALE(COLORF_TO_COMPOSITE(((srcColor * srcAlpha) + (dstColor * (1.0f - srcAlpha))), MSK_RGBA16_C, 0), MSK_RGBA16_A);
        }
    }
}

//! src should be I8 type
void overlay_i8_on_rgba16_additive(TexturePtr *dst, TexturePtr *src, u32 width, u32 height) {
    const u32 size = (width * height);
    u32 i;
    I8 srcVal;
    RGBA16 dstVal;
    RGBA16Component srcI;
    RGBA16Component rgb[3];
    for ((i = 0); (i < size); (i++)) {
        srcVal = src[i >> 1];
        srcI = I8_TO_RGBA16_C(srcVal);
        if (srcI > 0x0) {
            dstVal = dst[i];
            rgb[0] = (RGBA16_R(dstVal) + srcI);
            rgb[1] = (RGBA16_G(dstVal) + srcI);
            rgb[2] = (RGBA16_B(dstVal) + srcI);
            rgb[0] = MIN(rgb[0], MSK_RGBA16_C);
            rgb[1] = MIN(rgb[1], MSK_RGBA16_C);
            rgb[2] = MIN(rgb[2], MSK_RGBA16_C);
            dst[i] = RGBA16_COMPOSITE(rgb[0], rgb[1], rgb[2], MSK_RGBA16_A);
        }
    }
}

void colorRGB_add_hue(ColorRGB color, Color hueAdd, Color s) {
    Color min = min_3(color[0], color[1], color[2]);
    Color max = max_3(color[0], color[1], color[2]);
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
