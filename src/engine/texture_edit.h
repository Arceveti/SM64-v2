#ifndef TEXTURE_EDIT_H
#define TEXTURE_EDIT_H

#include <PR/ultratypes.h>
#include <PR/gbi.h>

#include "types.h"

void generate_metal_texture(u16 *dst,      u16 *src);
void copy_partial_image(    u16 *dst,      u16 *src,
                            s32 dstX,      s32 dstY,
                            u32 dstW,      u32 dstH,
                            u32 dstTW,     u32 dstTH,
                            u32 dstFormat, u32 dstPixelSize,
                            s32 srcX,      s32 srcY,
                            u32 srcW,      u32 srcH,
                            u32 srcTW,     u32 srcTH,
                            u32 srcFormat, u32 srcPixelSize);
void overlay_i8_on_rgba16_additive(u16 *dst, u16 *src, u32 width, u32 height);

#endif // SHADOW_H
