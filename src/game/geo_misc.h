#pragma once

#include <PR/ultratypes.h>
#include <PR/gbi.h>

enum FlyingCarpetState
{
    FLYING_CARPET_IDLE                 = 0,
    FLYING_CARPET_MOVING_WITHOUT_MARIO = 1,
    FLYING_CARPET_MOVING_WITH_MARIO    = 2
};

extern s8 gFlyingCarpetState;

#ifndef GBI_FLOATS
extern void make_vertex(
    Vtx *vtx, s32 n, VtxPosS x, VtxPosS y, VtxPosS z, TextureCoord tx, TextureCoord ty, Color r, Color g, Color b, Alpha a
);
#else
extern void make_vertex(
    Vtx *vtx, s32 n, VtxPosF x, VtxPosF y, VtxPosF z, TextureCoord tx, TextureCoord ty, Color r, Color g, Color b, Alpha a
);
#endif
extern Gfx *geo_exec_inside_castle_light       (s32 callContext, struct GraphNode *node, UNUSED Mat4 mtx);
extern Gfx *geo_exec_flying_carpet_timer_update(s32 callContext, struct GraphNode *node, UNUSED Mat4 mtx);
extern Gfx *geo_exec_flying_carpet_create      (s32 callContext, struct GraphNode *node, UNUSED Mat4 mtx);
extern Gfx *geo_exec_cake_end_screen           (s32 callContext, struct GraphNode *node, UNUSED Mat4 mtx);

#define gLoadBlockTexture(dl, width, height, format, image)                                                     \
{                                                                                                               \
    gDPSetTextureImage((dl), (format), G_IM_SIZ_16b, 1, (image));                                               \
    gDPTileSync((dl));                                                                                          \
    gDPSetTile((dl), (format), G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD,    \
               G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD);                                                         \
    gDPLoadSync((dl));                                                                                          \
    gDPLoadBlock((dl), G_TX_LOADTILE, 0, 0, CALC_LRS((width), (height)), CALC_DXT((width), G_IM_SIZ_16b_BYTES)) \
}
