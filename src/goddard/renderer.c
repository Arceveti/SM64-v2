#include <ultra64.h>

#include "draw_objects.h"
#include "dynlist_proc.h"
#include "gd_main.h"
#include "gd_memory.h"
#include "objects.h"
#include "renderer.h"
#include "sfx.h"
#include "shape_helper.h"
#include "skin.h"
#include "engine/math_util.h"
#include "engine/colors.h"

#define MAX_GD_DLS 1000
#define OS_MESG_SI_COMPLETE 0x33333333

#ifndef NO_SEGMENTED_MEMORY
#define GD_VIRTUAL_TO_PHYSICAL(addr) ((uintptr_t)(addr)  & 0x0FFFFFFF)
#define GD_LOWER_24(addr)            ((uintptr_t)(addr)  & 0x00FFFFFF)
#define GD_LOWER_29(addr)           (((uintptr_t)(addr)) & 0x1FFFFFFF)
#else
#define GD_VIRTUAL_TO_PHYSICAL(addr)   (addr)
#define GD_LOWER_24(addr)  ((uintptr_t)(addr))
#define GD_LOWER_29(addr) (((uintptr_t)(addr)))
#endif

#define LOOKAT_PACK(c) ((s32) MIN(((c) * (128.0f)), 127.0f) & 0xff)

// structs
struct GdDisplayList {
    /* Vertices */
    /*0x00*/ s32 curVtxIdx;
    /*0x04*/ s32 totalVtx;
    /*0x08*/ Vtx *vtx;
    /* Matrices */
    /*0x0C*/ s32 curMtxIdx;
    /*0x10*/ s32 totalMtx;
    /*0x14*/ Mtx *mtx;
    /* Lights */
    /*0x18*/ s32 curLightIdx;
    /*0x1C*/ s32 totalLights;
    /*0x20*/ Lights4 *light;
    /* Gfx-es */
    /*0x24*/ s32 curGfxIdx;
    /*0x28*/ s32 totalGfx;
    /*0x2C*/ Gfx *gfx;    // active position in DL
    /*0x30*/ Gfx **dlptr; // pointer to list/array of display lists for each frame?
                          /* Viewports */
    /*0x34*/ s32 curVpIdx;
    /*0x38*/ s32 totalVp;
    /*0x3C*/ Vp *vp;
    /* GD DL Info */
    /*0x40*/ u32 id;     // user specified
    /*0x44*/ u32 number; // count
    /*0x48*/ u8 pad48[4];
    /*0x4C*/ struct GdDisplayList *parent; // not quite sure?
};                                         /* sizeof = 0x50 */
// accessor macros for gd dl
#define DL_CURRENT_VTX(dl)   ((dl)->vtx[(dl)->curVtxIdx])
#define DL_CURRENT_MTX(dl)   ((dl)->mtx[(dl)->curMtxIdx])
#define DL_CURRENT_LIGHT(dl) ((dl)->light[(dl)->curLightIdx])
#define DL_CURRENT_GFX(dl)   ((dl)->gfx[(dl)->curGfxIdx])
#define DL_CURRENT_VP(dl)    ((dl)->vp[(dl)->curVpIdx])

// bss
static OSMesgQueue sGdControllerMsgQ; // controller msg queue
static OSMesg D_801BE848[10];
static OSMesgQueue sGdDMAQueue;
static OSMesg sGdMesgBuf[1];
static OSMesg sGdDMACompleteMsg; // msg buf for D_801BE8B0 queue
static OSIoMesg sGdDMAReqMesg;
static OSContStatus D_801BAE60[4];
static OSContPad sGdContPads[4];
static OSContPad sPrevFrameCont[4];
static u8  D_801BAEA0;
static u32 D_801BAF28; // RAM addr offset?
static s16 sTriangleBuf[13][8]; // [[s16; 8]; 13]? vert indices?
static u8 *sMemBlockPoolBase;
static u32 sAllocMemory; // malloc-ed bytes
static s16 sVtxCvrtTCBuf[2];
static struct ObjGroup *sMarioSceneGrp;
static s32 D_801BB0B4;                  // second offset into sTriangleBuf
static s32 sVertexBufCount;             // vtx's to load into RPD? Vtx len in GD Dl and in the lower bank (AF30)
static s32 sTriangleBufCount;           // number of triangles in sTriangleBuf
static struct ObjView *sMSceneView;     // Mario scene view
static s32 sVertexBufStartIndex;        // Vtx start in GD Dl
static s32 sUpdateMarioScene;           // update dl Vtx from ObjVertex?
static Mtx sIdnMtx;
static Mat4 sInitIdnMat4;
static s8 sVtxCvrtNormBuf[3];
static s16 sAlpha;
static s32 sNumLights;
static ColorRGBf sAmbScaleColour;
static ColorRGBf sLightScaleColours[2];
static Vec3i sLightDirections[2];
static s32 sLightId;
static Hilite sHilites[600];
static struct GdDisplayList *sStaticDl;
static struct GdDisplayList *sDynamicMainDls[2];
static struct GdDisplayList *sGdDlStash;
static struct GdDisplayList *sMHeadMainDls[2];       // two DLs, double buffered one per frame - seem to be basic dls that branch to actual lists?
static struct GdDisplayList *sViewDls[3][2];         // I guess? 801BD7C8 -> 801BD7E0?
static struct GdDisplayList *sGdDLArray[MAX_GD_DLS]; // indexed by dl number (gddl+0x44)
static s32 sPickBufLen;
static s32 sPickBufPosition;
static s16 *sPickBuf;
static LookAt gGdLookAts[3];
static u32 sMemBlockPoolSize = 1;
static s32 sMemBlockPoolUsed = 0;
s32 gGdFrameBufNum           = 0;
static struct ObjShape      *sHandShape   = NULL;
static s32 sMtxParamType = G_MTX_PROJECTION;
static struct ObjView       *sActiveView  = NULL; // current view? used when drawing dl
static struct ObjView       *sScreenView  = NULL;
static struct ObjView       *sHandView    = NULL;
static struct GdDisplayList *sCurrentGdDl = NULL;
static u32 sGdDlCount = 0;

// textures and display list data
UNUSED static Gfx gd_texture1_dummy_aligner1[] = {
    gsSPEndDisplayList(),
};

ALIGNED8 static Texture gd_texture_hand_open[] = {
#include "textures/intro_raw/hand_open.rgba16.inc.c"
};

UNUSED static Gfx gd_texture2_dummy_aligner1[] = {
    gsSPEndDisplayList()
};

ALIGNED8 static Texture gd_texture_hand_closed[] = {
#include "textures/intro_raw/hand_closed.rgba16.inc.c"
};

ALIGNED8 static Texture gd_texture_red_star_0[] = {
#include "textures/intro_raw/red_star_0.rgba16.inc.c"
};

ALIGNED8 static Texture gd_texture_red_star_1[] = {
#include "textures/intro_raw/red_star_1.rgba16.inc.c"
};

ALIGNED8 static Texture gd_texture_red_star_2[] = {
#include "textures/intro_raw/red_star_2.rgba16.inc.c"
};

ALIGNED8 static Texture gd_texture_red_star_3[] = {
#include "textures/intro_raw/red_star_3.rgba16.inc.c"
};

ALIGNED8 static Texture gd_texture_red_star_4[] = {
#include "textures/intro_raw/red_star_4.rgba16.inc.c"
};

ALIGNED8 static Texture gd_texture_red_star_5[] = {
#include "textures/intro_raw/red_star_5.rgba16.inc.c"
};

ALIGNED8 static Texture gd_texture_red_star_6[] = {
#include "textures/intro_raw/red_star_6.rgba16.inc.c"
};

ALIGNED8 static Texture gd_texture_red_star_7[] = {
#include "textures/intro_raw/red_star_7.rgba16.inc.c"
};

ALIGNED8 static Texture gd_texture_white_star_0[] = {
#include "textures/intro_raw/white_star_0.rgba16.inc.c"
};

ALIGNED8 static Texture gd_texture_white_star_1[] = {
#include "textures/intro_raw/white_star_1.rgba16.inc.c"
};

ALIGNED8 static Texture gd_texture_white_star_2[] = {
#include "textures/intro_raw/white_star_2.rgba16.inc.c"
};

ALIGNED8 static Texture gd_texture_white_star_3[] = {
#include "textures/intro_raw/white_star_3.rgba16.inc.c"
};

ALIGNED8 static Texture gd_texture_white_star_4[] = {
#include "textures/intro_raw/white_star_4.rgba16.inc.c"
};

ALIGNED8 static Texture gd_texture_white_star_5[] = {
#include "textures/intro_raw/white_star_5.rgba16.inc.c"
};

ALIGNED8 static Texture gd_texture_white_star_6[] = {
#include "textures/intro_raw/white_star_6.rgba16.inc.c"
};

ALIGNED8 static Texture gd_texture_white_star_7[] = {
#include "textures/intro_raw/white_star_7.rgba16.inc.c"
};

static Vtx_t gd_vertex_star[] = {
    {{   -64,     0,     0}, 0, ST_P(     0,    32), {0x00, 0x00, 0x7F}},
    {{    64,     0,     0}, 0, ST_P(    32,    32), {0x00, 0x00, 0x7F}},
    {{    64,   128,     0}, 0, ST_P(    32,     0), {0x00, 0x00, 0x7F}},
    {{   -64,   128,     0}, 0, ST_P(     0,     0), {0x00, 0x00, 0x7F}},
};

static Gfx gd_dl_star_common[] = {
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsSPClearGeometryMode(G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_NOOP2),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, G_TX_CLAMP, 5, G_TX_NOLOD, G_TX_CLAMP, 5, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, ((32 - 1) << G_TEXTURE_IMAGE_FRAC), ((32 - 1) << G_TEXTURE_IMAGE_FRAC)),
    gsSPVertex(gd_vertex_star, 4, 0),
    gsSP2Triangles( 0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_INTER, G_RM_NOOP2),
    gsSPEndDisplayList(),
};

static Gfx gd_dl_red_star_0[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, gd_texture_red_star_0),
    gsSPBranchList(gd_dl_star_common),
};

static Gfx gd_dl_red_star_1[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, gd_texture_red_star_1),
    gsSPBranchList(gd_dl_star_common),
};

static Gfx gd_dl_red_star_2[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, gd_texture_red_star_2),
    gsSPBranchList(gd_dl_star_common),
};

static Gfx gd_dl_red_star_3[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, gd_texture_red_star_3),
    gsSPBranchList(gd_dl_star_common),
};

static Gfx gd_dl_red_star_4[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, gd_texture_red_star_4),
    gsSPBranchList(gd_dl_star_common),
};

static Gfx gd_dl_red_star_5[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, gd_texture_red_star_5),
    gsSPBranchList(gd_dl_star_common),
};

static Gfx gd_dl_red_star_6[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, gd_texture_red_star_6),
    gsSPBranchList(gd_dl_star_common),
};

static Gfx gd_dl_red_star_7[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, gd_texture_red_star_7),
    gsSPBranchList(gd_dl_star_common),
};

static Gfx gd_dl_silver_star_0[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, gd_texture_white_star_0),
    gsSPBranchList(gd_dl_star_common),
};

static Gfx gd_dl_silver_star_1[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, gd_texture_white_star_1),
    gsSPBranchList(gd_dl_star_common),
};

static Gfx gd_dl_silver_star_2[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, gd_texture_white_star_2),
    gsSPBranchList(gd_dl_star_common),
};

static Gfx gd_dl_silver_star_3[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, gd_texture_white_star_3),
    gsSPBranchList(gd_dl_star_common),
};

static Gfx gd_dl_silver_star_4[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, gd_texture_white_star_4),
    gsSPBranchList(gd_dl_star_common),
};

static Gfx gd_dl_silver_star_5[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, gd_texture_white_star_5),
    gsSPBranchList(gd_dl_star_common),
};

static Gfx gd_dl_silver_star_6[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, gd_texture_white_star_6),
    gsSPBranchList(gd_dl_star_common),
};

static Gfx gd_dl_silver_star_7[] = {
    gsDPPipeSync(),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, gd_texture_white_star_7),
    gsSPBranchList(gd_dl_star_common),
};

static Gfx *gd_red_star_dl_array[] = {
    gd_dl_red_star_0,
    gd_dl_red_star_0,
    gd_dl_red_star_1,
    gd_dl_red_star_1,
    gd_dl_red_star_2,
    gd_dl_red_star_2,
    gd_dl_red_star_3,
    gd_dl_red_star_3,
    gd_dl_red_star_4,
    gd_dl_red_star_4,
    gd_dl_red_star_5,
    gd_dl_red_star_5,
    gd_dl_red_star_6,
    gd_dl_red_star_6,
    gd_dl_red_star_7,
    gd_dl_red_star_7,
};

static Gfx *gd_silver_star_dl_array[] = {
    gd_dl_silver_star_0,
    gd_dl_silver_star_0,
    gd_dl_silver_star_1,
    gd_dl_silver_star_1,
    gd_dl_silver_star_2,
    gd_dl_silver_star_2,
    gd_dl_silver_star_3,
    gd_dl_silver_star_3,
    gd_dl_silver_star_4,
    gd_dl_silver_star_4,
    gd_dl_silver_star_5,
    gd_dl_silver_star_5,
    gd_dl_silver_star_6,
    gd_dl_silver_star_6,
    gd_dl_silver_star_7,
    gd_dl_silver_star_7,
};

ALIGNED8 static Texture gd_texture_sparkle_0[] = {
#include "textures/intro_raw/sparkle_0.rgba16.inc.c"
};

ALIGNED8 static Texture gd_texture_sparkle_1[] = {
#include "textures/intro_raw/sparkle_1.rgba16.inc.c"
};

ALIGNED8 static Texture gd_texture_sparkle_2[] = {
#include "textures/intro_raw/sparkle_2.rgba16.inc.c"
};

ALIGNED8 static Texture gd_texture_sparkle_3[] = {
#include "textures/intro_raw/sparkle_3.rgba16.inc.c"
};

ALIGNED8 static Texture gd_texture_sparkle_4[] = {
#include "textures/intro_raw/sparkle_4.rgba16.inc.c"
};

ALIGNED8 static Texture gd_texture_sparkle_5[] = {
#include "textures/intro_raw/sparkle_5.rgba16.inc.c"
};

static Vtx_t gd_vertex_sparkle[] = {
    {{   -32,      0,      0}, 0, ST_P(      0,     64), {  0x00, 0x00, 0x7F, 0x00}},
    {{    32,      0,      0}, 0, ST_P(     64,     64), {  0x00, 0x00, 0x7F, 0x00}},
    {{    32,     64,      0}, 0, ST_P(     64,      0), {  0x00, 0x00, 0x7F, 0x00}},
    {{   -32,     64,      0}, 0, ST_P(      0,      0), {  0x00, 0x00, 0x7F, 0x00}},
};

static Gfx gd_dl_sparkle[] = {
    gsDPSetCombineMode(G_CC_MODULATERGBA_PRIM, G_CC_MODULATERGBA_PRIM),
    gsSPClearGeometryMode(G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_NOOP2),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, (G_TX_WRAP | G_TX_NOMIRROR), G_TX_NOMASK, G_TX_NOLOD, (G_TX_WRAP | G_TX_NOMIRROR), G_TX_NOMASK, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, CALC_LRS(32, 32), CALC_DXT(32, G_IM_SIZ_16b_BYTES)),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, G_TX_RENDERTILE, 0, (G_TX_WRAP | G_TX_NOMIRROR), G_TX_NOMASK, G_TX_NOLOD,  (G_TX_WRAP | G_TX_NOMIRROR), G_TX_NOMASK, G_TX_NOLOD),
    gsDPSetTileSize(0, 0, 0, ((32 - 1) << G_TEXTURE_IMAGE_FRAC), ((32 - 1) << G_TEXTURE_IMAGE_FRAC)),
    gsSPVertex(gd_vertex_sparkle, 4, 0),
    gsSP2Triangles(0,  1,  2, 0x0,  0,  2,  3, 0x0),
    gsSPTexture(0x0001, 0x0001, 0, G_TX_RENDERTILE, G_OFF),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_INTER, G_RM_NOOP2),
    gsSPEndDisplayList(),
};

static Gfx gd_dl_sparkle_red_color[] = {
    gsDPSetPrimColor(0, 0, 255, 0, 0, 255),
    gsSPEndDisplayList(),
};

static Gfx gd_dl_sparkle_white_color[] = {
    gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
    gsSPEndDisplayList(),
};

static Gfx gd_dl_red_sparkle_0[] = {
    gsDPPipeSync(),
    gsSPDisplayList(gd_dl_sparkle_red_color),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, gd_texture_sparkle_0),
    gsSPBranchList(gd_dl_sparkle),
};

static Gfx gd_dl_red_sparkle_1[] = {
    gsDPPipeSync(),
    gsSPDisplayList(gd_dl_sparkle_red_color),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, gd_texture_sparkle_1),
    gsSPBranchList(gd_dl_sparkle),
};

static Gfx gd_dl_red_sparkle_2[] = {
    gsDPPipeSync(),
    gsSPDisplayList(gd_dl_sparkle_red_color),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, gd_texture_sparkle_2),
    gsSPBranchList(gd_dl_sparkle),
};

static Gfx gd_dl_red_sparkle_3[] = {
    gsDPPipeSync(),
    gsSPDisplayList(gd_dl_sparkle_red_color),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, gd_texture_sparkle_3),
    gsSPBranchList(gd_dl_sparkle),
};

static Gfx gd_dl_red_sparkle_4[] = {
    gsDPPipeSync(),
    gsSPDisplayList(gd_dl_sparkle_red_color),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, gd_texture_sparkle_4),
    gsSPBranchList(gd_dl_sparkle),
};

static Gfx gd_dl_red_sparkle_5[] ={
    gsDPPipeSync(),
    gsSPDisplayList(gd_dl_sparkle_red_color),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, gd_texture_sparkle_5),
    gsSPBranchList(gd_dl_sparkle),
};

static Gfx gd_dl_silver_sparkle_0[] = {
    gsDPPipeSync(),
    gsSPDisplayList(gd_dl_sparkle_white_color),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, gd_texture_sparkle_0),
    gsSPBranchList(gd_dl_sparkle),
};

static Gfx gd_dl_silver_sparkle_1[] = {
    gsDPPipeSync(),
    gsSPDisplayList(gd_dl_sparkle_white_color),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, gd_texture_sparkle_1),
    gsSPBranchList(gd_dl_sparkle),
};

static Gfx gd_dl_silver_sparkle_2[] = {
    gsDPPipeSync(),
    gsSPDisplayList(gd_dl_sparkle_white_color),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, gd_texture_sparkle_2),
    gsSPBranchList(gd_dl_sparkle),
};

static Gfx gd_dl_silver_sparkle_3[] = {
    gsDPPipeSync(),
    gsSPDisplayList(gd_dl_sparkle_white_color),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, gd_texture_sparkle_3),
    gsSPBranchList(gd_dl_sparkle),
};

static Gfx gd_dl_silver_sparkle_4[] = {
    gsDPPipeSync(),
    gsSPDisplayList(gd_dl_sparkle_white_color),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, gd_texture_sparkle_4),
    gsSPBranchList(gd_dl_sparkle),
};

static Gfx gd_dl_silver_sparkle_5[] = {
    gsDPPipeSync(),
    gsSPDisplayList(gd_dl_sparkle_white_color),
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, gd_texture_sparkle_5),
    gsSPBranchList(gd_dl_sparkle),
};

static Gfx *gd_red_sparkle_dl_array[] = {
    gd_dl_red_sparkle_4,
    gd_dl_red_sparkle_4,
    gd_dl_red_sparkle_3,
    gd_dl_red_sparkle_3,
    gd_dl_red_sparkle_2,
    gd_dl_red_sparkle_2,
    gd_dl_red_sparkle_1,
    gd_dl_red_sparkle_1,
    gd_dl_red_sparkle_0,
    gd_dl_red_sparkle_0,
    gd_dl_red_sparkle_5,
    gd_dl_red_sparkle_5,
};

static Gfx *gd_silver_sparkle_dl_array[] = {
    gd_dl_silver_sparkle_4,
    gd_dl_silver_sparkle_4,
    gd_dl_silver_sparkle_3,
    gd_dl_silver_sparkle_3,
    gd_dl_silver_sparkle_2,
    gd_dl_silver_sparkle_2,
    gd_dl_silver_sparkle_1,
    gd_dl_silver_sparkle_1,
    gd_dl_silver_sparkle_0,
    gd_dl_silver_sparkle_0,
    gd_dl_silver_sparkle_5,
    gd_dl_silver_sparkle_5,
};

UNUSED static Gfx gd_texture3_dummy_aligner1[] = {
    gsSPEndDisplayList(),
};

ALIGNED8 static Texture gd_texture_mario_face_shine[] = {
#include "textures/intro_raw/mario_face_shine.ia8.inc.c"
};

static Gfx gd_dl_mario_face_shine[] = {
    gsSPSetGeometryMode(G_TEXTURE_GEN),
    gsSPTexture(0x07C0, 0x07C0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureFilter(G_TF_DEFAULT),
    gsDPSetCombineMode(G_CC_HILITERGBA, G_CC_HILITERGBA),
    gsDPLoadTextureBlock(gd_texture_mario_face_shine, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, 0,
                        (G_TX_WRAP | G_TX_NOMIRROR), (G_TX_WRAP | G_TX_NOMIRROR), 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

f32 sGdPerspTimer = 1.0f;

static Gfx gd_dl_sprite_start_tex_block[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsDPSetBlendColor(0, 0, 0, 1),
    gsDPSetRenderMode(G_RM_AA_ZB_TEX_EDGE, G_RM_NOOP2),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetTextureFilter(G_TF_DEFAULT),
    gsDPSetTexturePersp(G_TP_NONE),
    gsSPEndDisplayList(),
};

// linker (ROM addresses)
extern u8 _gd_dynlistsSegmentRomStart[];
extern u8 _gd_dynlistsSegmentRomEnd[];

// forward declarations
u32  new_gddl_from(Gfx *dl);
void gd_setup_cursor(struct ObjGroup *parentgrp);
void parse_p1_controller(void);
void update_cursor(void);
void update_view_and_dl(struct ObjView *view);
static void update_render_mode(void);
void gddl_is_loading_shine_dl(Bool32 dlLoad);
void gd_put_sprite(TexturePtr *sprite, s32 x, s32 y, s32 wx, s32 wy);
void reset_cur_dl_indices(void);

// TODO: make a gddl_num_t?

u32 get_alloc_mem_amt(void) {
    return sAllocMemory;
}

/**
 * Increments the current display list's Gfx index list and returns a pointer to the next Gfx element
 */
static Gfx *next_gfx(void) {
    if (sCurrentGdDl->curGfxIdx >= sCurrentGdDl->totalGfx) gd_exit(); // Gfx list overflow
    return &sCurrentGdDl->gfx[sCurrentGdDl->curGfxIdx++];
}

/**
 * Increments the current display list's Light index list and returns a pointer to the next Light element
 */
static Lights4 *next_light(void) {
    if (sCurrentGdDl->curLightIdx >= sCurrentGdDl->totalLights) gd_exit(); // Light list overflow
    return &sCurrentGdDl->light[sCurrentGdDl->curLightIdx++];
}

/**
 * Increments the current display list's matrix index list and returns a pointer to the next matrix element
 */
static Mtx *next_mtx(void) {
    if (sCurrentGdDl->curMtxIdx >= sCurrentGdDl->totalMtx) gd_exit(); // Mtx list overflow
    return &sCurrentGdDl->mtx[sCurrentGdDl->curMtxIdx++];
}

/**
 * Increments the current display list's vertex index list and returns a pointer to the next vertex element
 */
static Vtx *next_vtx(void) {
    if (sCurrentGdDl->curVtxIdx >= sCurrentGdDl->totalVtx) gd_exit(); // Vtx list overflow
    return &sCurrentGdDl->vtx[sCurrentGdDl->curVtxIdx++];
}

/**
 * Increments the current display list's viewport list and returns a pointer to the next viewport element
 */
static Vp *next_vp(void) {
    if (sCurrentGdDl->curVpIdx >= sCurrentGdDl->totalVp) gd_exit(); // Vp list overflow
    return &sCurrentGdDl->vp[sCurrentGdDl->curVpIdx++];
}

#if defined(ISVPRINT) || defined(UNF)
#define stubbed_printf osSyncPrintf
#endif

/* 24A19C -> 24A1D4 */
void gd_exit(void) {
    while (TRUE) {} // exit
}

/* 24A1D4 -> 24A220; orig name: func_8019BA04 */
void gd_free(void *ptr) {
    sAllocMemory -= gd_free_mem(ptr);
}

/* 24A220 -> 24A318 */
void *gd_allocblock(u32 size) {
    void *block;
    size = ALIGN(size, 8);
    if ((sMemBlockPoolUsed + size) > sMemBlockPoolSize) gd_exit();
    block = sMemBlockPoolBase + sMemBlockPoolUsed;
    sMemBlockPoolUsed += size;
    return block;
}

/* 24A318 -> 24A3E8 */
void *gd_malloc(u32 size, u8 perm) {
    void *ptr; // 1c
    size = ALIGN(size, 8);
    ptr = gd_request_mem(size, perm);
    if (ptr == NULL) return NULL;
    sAllocMemory += size;
    return ptr;
}

/* 24A3E8 -> 24A420; orig name: func_8019BC18 */
void *gd_malloc_perm(u32 size) {
    return gd_malloc(size, PERM_G_MEM_BLOCK);
}

/* 24A420 -> 24A458; orig name: func_8019BC50 */
void *gd_malloc_temp(u32 size) {
    return gd_malloc(size, TEMP_G_MEM_BLOCK);
}

/* 24A4DC -> 24A598 */
void draw_indexed_dl(s32 dlNum, s32 gfxIdx) {
    Gfx *dl;
    if (gfxIdx != 0) {
        dl = sGdDLArray[dlNum]->dlptr[gfxIdx - 1];  // multiple display lists (determined by frame)
    } else {
        dl = sGdDLArray[dlNum]->gfx;  // only one display list
    }
    gSPDisplayList(next_gfx(), GD_VIRTUAL_TO_PHYSICAL(dl));
}

/* 24A598 -> 24A610; orig name: func_8019BDC8 */
void branch_cur_dl_to_num(s32 dlNum) {
    Gfx *dl;
    dl = sGdDLArray[dlNum]->gfx;
    gSPDisplayList(next_gfx(), GD_VIRTUAL_TO_PHYSICAL(dl));
}

/**
 * Creates `ObjShape`s for the stars and sparkles
 */
void setup_stars(void) {
    gShapeRedStar                                   = make_shape("redstar");
    gShapeRedStar->dlNums[0]                        = new_gddl_from(NULL);
    gShapeRedStar->dlNums[1]                        = gShapeRedStar->dlNums[0];
    sGdDLArray[gShapeRedStar->dlNums[0]]->dlptr     = gd_red_star_dl_array;
    sGdDLArray[gShapeRedStar->dlNums[1]]->dlptr     = gd_red_star_dl_array;
    gShapeSilverStar                                = make_shape("silverstar");
    gShapeSilverStar->dlNums[0]                     = new_gddl_from(NULL);
    gShapeSilverStar->dlNums[1]                     = gShapeSilverStar->dlNums[0];
    sGdDLArray[gShapeSilverStar->dlNums[0]]->dlptr  = gd_silver_star_dl_array;
    sGdDLArray[gShapeSilverStar->dlNums[1]]->dlptr  = gd_silver_star_dl_array;
    // make_shape names of the dl array they call are misnamed (swapped)
    // "sspark" calls red sparkles and "rspark" calls silver sparkles
    gShapeRedSpark                                  = make_shape("sspark");
    gShapeRedSpark->dlNums[0]                       = new_gddl_from(NULL);
    gShapeRedSpark->dlNums[1]                       = gShapeRedSpark->dlNums[0];
    sGdDLArray[gShapeRedSpark->dlNums[0]]->dlptr    = gd_red_sparkle_dl_array;
    sGdDLArray[gShapeRedSpark->dlNums[1]]->dlptr    = gd_red_sparkle_dl_array;
    gShapeSilverSpark                               = make_shape("rspark");
    gShapeSilverSpark->dlNums[0]                    = new_gddl_from(NULL);
    gShapeSilverSpark->dlNums[1]                    = gShapeSilverSpark->dlNums[0];
    sGdDLArray[gShapeSilverSpark->dlNums[0]]->dlptr = gd_silver_sparkle_dl_array;
    sGdDLArray[gShapeSilverSpark->dlNums[1]]->dlptr = gd_silver_sparkle_dl_array;
}

/* 24AAA8 -> 24AAE0; orig name: func_8019C2D8 */
void gd_add_to_heap(void *addr, u32 size) {
    // TODO: is this `1` for permanence special?
    gd_add_mem_to_heap(size, addr, 1);
}

/* 24AAE0 -> 24AB7C */
void gdm_init(void *blockpool, u32 size) {
    // Align downwards?
    size = ((size - 8) & ~0x7);
    // Align to next double word boundry?
    blockpool = (void *) (((uintptr_t) blockpool + 8) & ~7);
    sMemBlockPoolBase = blockpool;
    sMemBlockPoolSize = size;
    sMemBlockPoolUsed = 0;
    sAllocMemory      = 0;
    init_mem_block_lists();
    gd_reset_sfx();
}

/**
 * Initializes the Mario head demo
 */
void gdm_setup(void) {
    sMarioSceneGrp    = NULL;
    sUpdateMarioScene = FALSE;
    osViSetSpecialFeatures(OS_VI_GAMMA_OFF);
    osCreateMesgQueue(&sGdDMAQueue, sGdMesgBuf, ARRAY_COUNT(sGdMesgBuf));
    gd_init();
    load_shapes2();
    reset_cur_dl_indices();
    setup_stars();
}

/* 24AC80 -> 24AD14; orig name: func_8019C4B0 */
struct ObjView *make_view_withgrp(char *name, struct ObjGroup *grp) {
    struct ObjView *view = make_view(name, (VIEW_DRAW | VIEW_ALLOC_ZBUF | VIEW_MOVEMENT), 1, 0, 0, 320, 240, grp);
    UNUSED struct ObjGroup *viewgrp = make_group(2, grp, view);
    view->lights = gGdLightGroup;
    return view;
}

/* 24AD14 -> 24AEB8 */
void gdm_maketestdl(s32 isIntro) {
    // normal or game over Mario head
    if (sMarioSceneGrp == NULL) {
        load_mario_head(isIntro ? animate_mario_head_normal : animate_mario_head_gameover);
        sMarioSceneGrp = gMarioFaceGrp; // gMarioFaceGrp set by load_mario_head
        gd_setup_cursor(NULL);
    }
    sMSceneView = make_view_withgrp("mscene", sMarioSceneGrp);
}

/**
 * Runs every frame at V-blank. Handles input and updates state.
 */
void gd_vblank(void) {
    gd_sfx_update();
    if (sUpdateMarioScene) apply_to_obj_types_in_group(OBJ_TYPE_NETS, (applyproc_t) convert_net_verts, sMarioSceneGrp);
    sUpdateMarioScene = FALSE;
    gGdFrameBufNum   ^= 1;
    reset_cur_dl_indices();
    parse_p1_controller();
    update_cursor();
}

/**
 * Copies the player1 controller data from p1cont to sGdContPads[0].
 */
void gd_copy_p1_contpad(OSContPad *p1cont) {
    u32 i;
    u8 *src  = (u8 *) p1cont;
    u8 *dest = (u8 *) &sGdContPads[0];
    for ((i = 0); (i < sizeof(OSContPad)); (i++)) dest[i] = src[i];
}

/* 24B058 -> 24B088; orig name: gd_sfx_to_play */
s32 gd_sfx_to_play(void) {
    return gd_new_sfx_to_play();
}

/* 24B088 -> 24B418 */
Gfx *gdm_gettestdl(UNUSED s32 id) {
    struct GdDisplayList *gddl = NULL;
    update_view_and_dl(sMSceneView);
    if (sHandView != NULL) update_view_and_dl(sHandView);
    sCurrentGdDl = sMHeadMainDls[gGdFrameBufNum];
    gSPEndDisplayList(next_gfx());
    gddl              = sCurrentGdDl;
    sUpdateMarioScene = TRUE;
    if (gddl == NULL) gd_exit(); // no display list
    return (void *) osVirtualToPhysical(gddl->gfx);
}

/* 24B5D4 -> 24B6AC */
struct GdDisplayList *alloc_displaylist(u32 id) {
    struct GdDisplayList *gdDl = gd_malloc_perm(sizeof(struct GdDisplayList));
    if (gdDl == NULL) gd_exit(); // Out of DL mem
    gdDl->number = sGdDlCount++;
    if (sGdDlCount >= MAX_GD_DLS) gd_exit(); // fatal_printf("alloc_displaylist() too many display lists %d (MAX %d)", sGdDlCount + 1, MAX_GD_DLS);
    sGdDLArray[gdDl->number] = gdDl;
    gdDl->id = id;
    return gdDl;
}

/* 24B6AC -> 24B7A0; orig name: func_8019CEDC */
void cpy_remaining_gddl(struct GdDisplayList *dst, struct GdDisplayList *src) {
    dst->vtx         = &DL_CURRENT_VTX(   src);
    dst->mtx         = &DL_CURRENT_MTX(   src);
    dst->light       = &DL_CURRENT_LIGHT( src);
    dst->gfx         = &DL_CURRENT_GFX(   src);
    dst->vp          = &DL_CURRENT_VP(    src);
    dst->totalVtx    = src->totalVtx    - src->curVtxIdx;
    dst->totalMtx    = src->totalMtx    - src->curMtxIdx;
    dst->totalLights = src->totalLights - src->curLightIdx;
    dst->totalGfx    = src->totalGfx    - src->curGfxIdx;
    dst->totalVp     = src->totalVp     - src->curVpIdx;
    dst->curVtxIdx   = 0;
    dst->curMtxIdx   = 0;
    dst->curLightIdx = 0;
    dst->curGfxIdx   = 0;
    dst->curVpIdx    = 0;
}

/* 24B7A0 -> 24B7F8; orig name: func_8019CFD0 */
struct GdDisplayList *create_child_gdl(s32 id, struct GdDisplayList *srcDl) {
    struct GdDisplayList *newDl;
    newDl = alloc_displaylist(id);
    newDl->parent = srcDl;
    cpy_remaining_gddl(newDl, srcDl);
    return newDl;
}

/* 24B7F8 -> 24BA48; orig name: func_8019D028 */
struct GdDisplayList *new_gd_dl(s32 id, s32 gfxs, s32 verts, s32 mtxs, s32 lights, s32 vps) {
    struct GdDisplayList *dl;
    dl = alloc_displaylist(id);
    dl->parent              = NULL;
    if (verts == 0) verts   = 1;
    dl->curVtxIdx           = 0;
    dl->totalVtx            = verts;
    if ((dl->vtx            = gd_malloc_perm(verts * sizeof(Vtx))) == NULL) gd_exit(); // Out of DL mem
    if (mtxs == 0) mtxs     = 1;
    dl->curMtxIdx           = 0;
    dl->totalMtx            = mtxs;
    if ((dl->mtx            = gd_malloc_perm(mtxs * sizeof(Mtx))) == NULL) gd_exit(); // Out of DL mem
    if (lights == 0) lights = 1;
    dl->curLightIdx         = 0;
    dl->totalLights         = lights;
    if ((dl->light          = gd_malloc_perm(lights * sizeof(Lights4))) == NULL) gd_exit(); // Out of DL mem
    if (gfxs   == 0)   gfxs = 1;
    dl->curGfxIdx           = 0;
    dl->totalGfx            = gfxs;
    if ((dl->gfx            = gd_malloc_perm(gfxs * sizeof(Gfx))) == NULL) gd_exit(); // Out of DL mem
    if (vps    == 0)    vps = 1;
    dl->curVpIdx            = 0;
    dl->totalVp             = vps;
    if ((dl->vp             = gd_malloc_perm(vps * sizeof(Vp))) == NULL) gd_exit(); // Out of DL mem
    dl->dlptr               = NULL;
    return dl;
}

/* 24CF2C -> 24CFCC; orig name: func_8019E75C */
void reset_cur_dl_indices(void) {
    sMHeadMainDls[gGdFrameBufNum]->curGfxIdx = 0;
    sCurrentGdDl = sDynamicMainDls[gGdFrameBufNum];
    sCurrentGdDl->curVtxIdx   = 0;
    sCurrentGdDl->curMtxIdx   = 0;
    sCurrentGdDl->curLightIdx = 0;
    sCurrentGdDl->curGfxIdx   = 0;
    sCurrentGdDl->curVpIdx    = 0;
}

/* 24CFCC -> 24D044; orig name: func_8019E7FC */
void begin_gddl(s32 num) {
    sCurrentGdDl = sGdDLArray[num];
    sCurrentGdDl->curVtxIdx   = 0;
    sCurrentGdDl->curMtxIdx   = 0;
    sCurrentGdDl->curLightIdx = 0;
    sCurrentGdDl->curGfxIdx   = 0;
    sCurrentGdDl->curVpIdx    = 0;
}

/* 24D044 -> 24D064; orig name: func_8019E874 */
void stash_current_gddl(void) {
    sGdDlStash = sCurrentGdDl;
}

/* 24D064 -> 24D084; orig name: func_8019E894 */
void pop_gddl_stash(void) {
    sCurrentGdDl = sGdDlStash;
}

/* 24D084 -> 24D1D4 */
s32 gd_startdisplist(s32 memarea) {
    switch (memarea) {
        case 7:  // Create new display list as a child of sStaticDl
            sCurrentGdDl = create_child_gdl(0, sStaticDl);
            break;
        case 8:  // Use the active view's display list
            if (sActiveView->id > 2) gd_exit(); // Too many views to display
            sCurrentGdDl = sViewDls[sActiveView->id][gGdFrameBufNum];
            cpy_remaining_gddl(sCurrentGdDl, sCurrentGdDl->parent);
            break;
        default: gd_exit(); break; // Unknown memory area
    }
    gDPPipeSync(next_gfx());
    return sCurrentGdDl->number;
}

/* 24D1D4 -> 24D23C */
void gd_enddlsplist(void) {
    gDPPipeSync(next_gfx());
    gSPEndDisplayList(next_gfx());
}

/* 24D23C -> 24D39C; orig name: func_8019EA6C */
s32 gd_enddlsplist_parent(void) {
    s32 curDlIdx = 0;
    gDPPipeSync(next_gfx());
    gSPEndDisplayList(next_gfx());
    if (sCurrentGdDl->parent != NULL) {
        sCurrentGdDl->parent->curVtxIdx   = (sCurrentGdDl->parent->curVtxIdx   + sCurrentGdDl->curVtxIdx  );
        sCurrentGdDl->parent->curMtxIdx   = (sCurrentGdDl->parent->curMtxIdx   + sCurrentGdDl->curMtxIdx  );
        sCurrentGdDl->parent->curLightIdx = (sCurrentGdDl->parent->curLightIdx + sCurrentGdDl->curLightIdx);
        sCurrentGdDl->parent->curGfxIdx   = (sCurrentGdDl->parent->curGfxIdx   + sCurrentGdDl->curGfxIdx  );
        sCurrentGdDl->parent->curVpIdx    = (sCurrentGdDl->parent->curVpIdx    + sCurrentGdDl->curVpIdx   );
    }
    curDlIdx = sCurrentGdDl->curGfxIdx;
    return curDlIdx;
}

/* 24D3D8 -> 24D458; orig name: func_8019EC08 */
u32 new_gddl_from(Gfx *dl) {
    struct GdDisplayList *gddl;
    gddl = new_gd_dl(0, 0, 0, 0, 0, 0);
    gddl->gfx = (Gfx *) (GD_LOWER_24((uintptr_t) dl) + D_801BAF28);
    return gddl->number;
}

/**
 * Adds a display list operation that multiplies the current matrix with `mtx`.
 */
void gd_dl_mul_matrix(Mat4 *mtx) {
    mtxf_to_mtx(&DL_CURRENT_MTX(sCurrentGdDl), (*mtx));
    gSPMatrix(next_gfx(), osVirtualToPhysical(&DL_CURRENT_MTX(sCurrentGdDl)), sMtxParamType | G_MTX_MUL | G_MTX_NOPUSH);
    next_mtx();
}

/**
 * Adds a display list operation that replaces the current matrix with `mtx`.
 */
void gd_dl_load_matrix(Mat4 *mtx) {
    mtxf_to_mtx(&DL_CURRENT_MTX(sCurrentGdDl), (*mtx));
    gSPMatrix(next_gfx(), osVirtualToPhysical(&DL_CURRENT_MTX(sCurrentGdDl)), sMtxParamType | G_MTX_LOAD | G_MTX_NOPUSH);
    next_mtx();
}

/**
 * Adds a display list operation that replaces the current matrix with the
 * identity matrix.
 */
void gd_dl_load_identity_matrix(void) {
    gSPMatrix(next_gfx(), osVirtualToPhysical(&sIdnMtx), sMtxParamType | G_MTX_LOAD | G_MTX_NOPUSH);
}

/**
 * Adds a display list operation that pushes the current matrix onto the matrix
 * stack.
 */
void gd_dl_push_matrix(void) {
    gSPMatrix(next_gfx(), osVirtualToPhysical(&sIdnMtx), sMtxParamType | G_MTX_MUL | G_MTX_PUSH);
}

/**
 * Adds a display list operation that pops a matrix from the matrix stack.
 */
void gd_dl_pop_matrix(void) {
    gSPPopMatrix(next_gfx(), sMtxParamType);
}

/**
 * Adds a display list operation that translates the current matrix by `x`, `y`, and `z`.
 */
void gd_dl_mul_trans_matrix(f32 x, f32 y, f32 z) {
    guTranslate(&DL_CURRENT_MTX(sCurrentGdDl), x, y, z);
    gSPMatrix(next_gfx(), osVirtualToPhysical(&DL_CURRENT_MTX(sCurrentGdDl)), sMtxParamType | G_MTX_MUL | G_MTX_NOPUSH);
    next_mtx();
}

/**
 * Adds a display list operation that loads a translation matrix.
 */
void gd_dl_load_trans_matrix(f32 x, f32 y, f32 z) {
    guTranslate(&DL_CURRENT_MTX(sCurrentGdDl), x, y, z);
    gSPMatrix(next_gfx(), osVirtualToPhysical(&DL_CURRENT_MTX(sCurrentGdDl)), sMtxParamType | G_MTX_LOAD | G_MTX_NOPUSH);
    next_mtx();
}

/**
 * Adds a display list operation that scales the current matrix by `x`, `y`, and `z`.
 */
void gd_dl_scale(f32 x, f32 y, f32 z) {
    Mat4 mtx;
    Vec3f scaleVec = {x, y, z};
    mtxf_identity(mtx);
    mtxf_scale_self_vec3f(mtx, scaleVec);
    gd_dl_mul_matrix(&mtx);
}

/* 24DA94 -> 24DAE8 */
void gd_dl_rotate(f32 angle, s8 axis) {
    Mat4 mtx;
    mtxf_identity(mtx);
    mtxf_absrot(      mtx, (axis - 120), -angle);
    gd_dl_mul_matrix(    &mtx);
}

/* 24DAE8 -> 24E1A8 */
void gd_dl_lookat(struct ObjCamera *cam, Vec3f from, Vec3f to, f32 colXY) {
    LookAt *lookat;
    colXY *= RAD_PER_DEG;
    mtxf_lookat(cam->lookatMtx, from, to, colXY);
    mtxf_to_mtx(&DL_CURRENT_MTX(sCurrentGdDl), cam->lookatMtx);
    gSPMatrix(next_gfx(), osVirtualToPhysical(&DL_CURRENT_MTX(sCurrentGdDl)),  G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
    /*  col           colc          dir
        0  1  2   3   4  5  6   7   8  9  10  11
    { { 0, 0, 0}, _, {0, 0, 0}, _, {0, 0, 0}, _}
       16 17 18  19  20 21  22 23  24 25  26  27
    { { 0, 0, 0}, _, {0, 0, 0}, _, {0, 0, 0}, _}
    */
    lookat                 = &gGdLookAts[gGdFrameBufNum];
    lookat->l[0].l.dir[0]  = LOOKAT_PACK(cam->lookatMtx[0][0]);
    lookat->l[0].l.dir[1]  = LOOKAT_PACK(cam->lookatMtx[1][0]);
    lookat->l[0].l.dir[2]  = LOOKAT_PACK(cam->lookatMtx[2][0]);
    lookat->l[1].l.dir[0]  = LOOKAT_PACK(cam->lookatMtx[0][1]);
    lookat->l[1].l.dir[1]  = LOOKAT_PACK(cam->lookatMtx[1][1]);
    lookat->l[1].l.dir[2]  = LOOKAT_PACK(cam->lookatMtx[2][1]);
    vec3_zero(lookat->l[0].l.col );
    lookat->l[0].l.pad1    = 0;
    vec3_zero(lookat->l[0].l.colc);
    lookat->l[0].l.pad2    = 0;
    vec3_set(lookat->l[1].l.col,  0x0, 0x80, 0x0);
    lookat->l[1].l.pad1    = 0;
    vec3_set(lookat->l[1].l.colc, 0x0, 0x80, 0x0);
    lookat->l[1].l.pad2    = 0;
    gSPLookAt(next_gfx(), osVirtualToPhysical(&gGdLookAts[gGdFrameBufNum]));
    next_mtx();
}

/* 24E1A8 -> 24E230; orig name: func_8019F9D8 */
void check_tri_display(s32 vtxcount) {
    D_801BB0B4 = 0;
    if (vtxcount != 3) gd_exit(); // cant display no tris
}

/**
 * Adds a vertex to the current display list. Returns a pointer to the vertex if
 * it is new, or NULL if the vertex already exists.
 */
Vtx *gd_dl_make_vertex(f32 x, f32 y, f32 z, f32 alpha) {
    Vtx *vtx = NULL;
    s32 i;
    // Add the vertex index to the buffer if it doesn't already exist
    for ((i = sVertexBufStartIndex); (i < (sVertexBufStartIndex + sVertexBufCount)); (i++)) {
        if ((sCurrentGdDl->vtx[i].n.ob[0] == (RawVertexData) x)
         && (sCurrentGdDl->vtx[i].n.ob[1] == (RawVertexData) y)
         && (sCurrentGdDl->vtx[i].n.ob[2] == (RawVertexData) z)) {
            sTriangleBuf[sTriangleBufCount][D_801BB0B4++] = (s16) i;
            return NULL;
        }
    }
    sVertexBufCount++;
    sTriangleBuf[sTriangleBufCount][D_801BB0B4++] = (s16) sCurrentGdDl->curVtxIdx;
    vec3_set(DL_CURRENT_VTX(sCurrentGdDl).n.ob, x, y, z);
    DL_CURRENT_VTX(sCurrentGdDl).n.flag  = 0;
    DL_CURRENT_VTX(sCurrentGdDl).n.tc[0] = sVtxCvrtTCBuf[0];
    DL_CURRENT_VTX(sCurrentGdDl).n.tc[1] = sVtxCvrtTCBuf[1];
    vec3_copy(DL_CURRENT_VTX(sCurrentGdDl).n.n, sVtxCvrtNormBuf);
    DL_CURRENT_VTX(sCurrentGdDl).n.a     = (Alpha)(alpha * 255.0f);
    vtx = &DL_CURRENT_VTX(sCurrentGdDl);
    next_vtx();
    return vtx;
}

/* 24E6C0 -> 24E724 */
void flush_current_triangle_buffer(void) {
    sTriangleBufCount++;
    if (sVertexBufCount >= 12) {
        gd_dl_flush_vertices();
        gd_dl_reset_buffers();
    }
}

/* 24E808 -> 24E840 */
void gd_dl_reset_buffers(void) {
    sVertexBufCount      = 0;
    sTriangleBufCount    = 0;
    sVertexBufStartIndex = sCurrentGdDl->curVtxIdx;
}

/* 24E840 -> 24E9BC */
void gd_dl_flush_vertices(void) {
    s32 i;
    if (sVertexBufCount != 0) {
        // load vertex data
        gSPVertex(next_gfx(), osVirtualToPhysical(&sCurrentGdDl->vtx[sVertexBufStartIndex]), sVertexBufCount, 0);
        // load triangle data
        for ((i = 0); (i < sTriangleBufCount); (i++)) {
            gSP1Triangle(next_gfx(), (sTriangleBuf[i][0] - sVertexBufStartIndex),
                                     (sTriangleBuf[i][1] - sVertexBufStartIndex),
                                     (sTriangleBuf[i][2] - sVertexBufStartIndex), 0);
        }
    }
    gd_dl_reset_buffers();
}

/* 24EA88 -> 24EAF4 */
void set_render_alpha(f32 alpha) {
    sAlpha = (alpha * 255.0f);
    update_render_mode();
}

/* 24EAF4 -> 24EB0C */
// light id?
void set_light_id(s32 index) {
    sLightId = index;
}

/* 24EB0C -> 24EB24; orig name: func_801A033C */
void set_light_num(s32 n) {
    sNumLights = n;
}

/* 24EB24 -> 24EC18 */
s32 create_mtl_gddl(void) {
    ColorRGBf blue = {0.0f, 0.0f, 1.0f};
    s32 dlnum      = gd_startdisplist(7);
    gd_dl_material_lighting(dlnum, blue, GD_MTL_TEX_OFF);
    gd_enddlsplist_parent();
    sCurrentGdDl->totalVtx    = sCurrentGdDl->curVtxIdx;
    sCurrentGdDl->totalMtx    = sCurrentGdDl->curMtxIdx;
    sCurrentGdDl->totalLights = sCurrentGdDl->curLightIdx;
    sCurrentGdDl->totalGfx    = sCurrentGdDl->curGfxIdx;
    sCurrentGdDl->totalVp     = sCurrentGdDl->curVpIdx;
    return dlnum;
}

/* 24EC18 -> 24EC48; orig name: func_801A0448 */
void branch_to_gddl(s32 dlNum) {
    branch_cur_dl_to_num(dlNum);
}

/* 24EC48 -> 24F03C */
// phong shading function?
void gd_dl_hilite(s32 idx, // material GdDl number; offsets into hilite array
                   struct ObjCamera *cam,
                   Vec3f phongLightPosition, // vector to light source?
                   ColorRGBf colour) {       // light color
    Hilite *hilite;
    Vec3f vec;
    f32 mag; // magnitude of vec
    const f32 xMul = 32.0f; // x scale factor?
    const f32 yMul = 32.0f; // y scale factor?
    if (idx >= 0xc8) gd_exit(); // too many hilites
    hilite = &sHilites[idx];
    gDPSetPrimColor(next_gfx(), 0, 0, (s32)(colour[0] * 255.0f), (s32)(colour[1] * 255.0f), (s32)(colour[2] * 255.0f), 255);
    vec[2] = (cam->lookatMtx[0][2] + phongLightPosition[0]);
    vec[1] = (cam->lookatMtx[1][2] + phongLightPosition[1]);
    vec[0] = (cam->lookatMtx[2][2] + phongLightPosition[2]);
    mag = vec3_mag(vec);
    if (mag > 0.1f) {
        mag = 1.0f / mag;
        vec3f_mul_val(vec, mag);
        hilite->h.x1 = (((vec[2] * cam->lookatMtx[0][0]) + (vec[1] * cam->lookatMtx[1][0]) + (vec[0] * cam->lookatMtx[2][0])) * xMul * 2.0f) + (xMul * 4.0f);
        hilite->h.y1 = (((vec[2] * cam->lookatMtx[0][1]) + (vec[1] * cam->lookatMtx[1][1]) + (vec[0] * cam->lookatMtx[2][1])) * yMul * 2.0f) + (yMul * 4.0f);
    } else {
        hilite->h.x1 = (xMul * 2.0f);
        hilite->h.y1 = (yMul * 2.0f);
    }
}

/**
 * Adds some display list commands that perform lighting for a material
 */
s32 gd_dl_material_lighting(s32 id, ColorRGBf colour, s32 material) {
    s32 i;
    s32 numLights = sNumLights;
    Vec3i scaledColours;
    Vec3i lightDir;
    if (id > 0) begin_gddl(id);
    switch (material) {
        case GD_MTL_TEX_OFF:
            gddl_is_loading_shine_dl(FALSE);
            gddl_is_loading_shine_dl(FALSE);
            gddl_is_loading_shine_dl(FALSE);
            gddl_is_loading_shine_dl(FALSE);
            numLights = NUMLIGHTS_2;
            break;
        case GD_MTL_SHINE_DL:
            gddl_is_loading_shine_dl(TRUE);
            if (id >= 200) gd_exit(); // too many hilites
            gDPSetHilite1Tile(next_gfx(), G_TX_RENDERTILE, &sHilites[id], 32, 32);
            break;
        case GD_MTL_BREAK:
            break;
        default:
            gddl_is_loading_shine_dl(FALSE);
            DL_CURRENT_LIGHT(sCurrentGdDl).a.l.col[0]  = (colour[0] * 255.0f);
            DL_CURRENT_LIGHT(sCurrentGdDl).a.l.col[1]  = (colour[1] * 255.0f);
            DL_CURRENT_LIGHT(sCurrentGdDl).a.l.col[2]  = (colour[2] * 255.0f);
            vec3_copy(DL_CURRENT_LIGHT(sCurrentGdDl).a.l.colc, DL_CURRENT_LIGHT(sCurrentGdDl).a.l.col);
            vec3_zero(DL_CURRENT_LIGHT(sCurrentGdDl).l[0].l.col );
            vec3_zero(DL_CURRENT_LIGHT(sCurrentGdDl).l[0].l.colc);
            gSPNumLights(next_gfx(), NUMLIGHTS_1);
            gSPLight(next_gfx(), osVirtualToPhysical(&DL_CURRENT_LIGHT(sCurrentGdDl).l), LIGHT_1);
            gSPLight(next_gfx(), osVirtualToPhysical(&DL_CURRENT_LIGHT(sCurrentGdDl).a), LIGHT_2);
            next_light();
            if (id > 0) gd_enddlsplist();
            return 0;
            break;
    }
    scaledColours[0] = (s32)(colour[0] * sAmbScaleColour[0] * 255.0f);
    scaledColours[1] = (s32)(colour[1] * sAmbScaleColour[1] * 255.0f);
    scaledColours[2] = (s32)(colour[2] * sAmbScaleColour[2] * 255.0f);
    vec3_copy(DL_CURRENT_LIGHT(sCurrentGdDl).a.l.col,  scaledColours);
    vec3_copy(DL_CURRENT_LIGHT(sCurrentGdDl).a.l.colc, scaledColours);
    gSPNumLights(next_gfx(), numLights);
    for ((i = 0); (i < numLights); (i++)) {
        scaledColours[0] = (colour[0] * sLightScaleColours[i][0] * 255.0f);
        scaledColours[1] = (colour[1] * sLightScaleColours[i][1] * 255.0f);
        scaledColours[2] = (colour[2] * sLightScaleColours[i][2] * 255.0f);
        vec3_copy(DL_CURRENT_LIGHT(sCurrentGdDl).l[i].l.col,  scaledColours);
        vec3_copy(DL_CURRENT_LIGHT(sCurrentGdDl).l[i].l.colc, scaledColours);
        lightDir[0] = (s8)sLightDirections[i][0];
        lightDir[1] = (s8)sLightDirections[i][1];
        lightDir[2] = (s8)sLightDirections[i][2];
        vec3_copy(DL_CURRENT_LIGHT(sCurrentGdDl).l[i].l.dir, lightDir);
        gSPLight(next_gfx(), osVirtualToPhysical(&DL_CURRENT_LIGHT(sCurrentGdDl).l[i]), (i + 1));
    }
    gSPLight(next_gfx(), osVirtualToPhysical(&DL_CURRENT_LIGHT(sCurrentGdDl)), (i + 1));
    next_light();
    gd_enddlsplist();
    return 0;
}

/* 24FE94 -> 24FF80; orig name: func_801A16C4; only from verts? */
void set_Vtx_norm_buf_2(Vec3n norm) {
    vec3_prod_val(sVtxCvrtNormBuf, norm, 127.0f);
}

/* 24FF80 -> 24FFDC; orig name: func_801A17B0 */
void set_gd_mtx_parameters(s32 params) {
    switch (params) {
        case (G_MTX_PROJECTION | G_MTX_MUL | G_MTX_PUSH): sMtxParamType = G_MTX_PROJECTION; break;
        case (G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_PUSH): sMtxParamType = G_MTX_MODELVIEW;  break;
    }
}

/**
 * Adds a viewport to the current display list based on the current active view
 */
static void gd_dl_viewport(void) {
    Vp *vp;
    vp = &DL_CURRENT_VP(sCurrentGdDl);
    vp->vp.vscale[0] = (s16)(sActiveView->lowerRight[0] * 2.0f);  // x scale
    vp->vp.vscale[1] = (s16)(sActiveView->lowerRight[1] * 2.0f);  // y scale
    vp->vp.vscale[2] = 0x1FF;  // z scale
    vp->vp.vscale[3] = 0x000;
    vp->vp.vtrans[0] = (s16)((sActiveView->upperLeft[0] * 4.0f) + (sActiveView->lowerRight[0] * 2.0f));  // x offset
    vp->vp.vtrans[1] = (s16)((sActiveView->upperLeft[1] * 4.0f) + (sActiveView->lowerRight[1] * 2.0f));  // y offset
    vp->vp.vtrans[2] = 0x1FF;  // z offset
    vp->vp.vtrans[3] = 0x000;
    gSPViewport(next_gfx(), osVirtualToPhysical(vp));
    next_vp();
}

/* 2501D0 -> 250300 */
static void update_render_mode(void) {
    if ((sActiveView->flags & VIEW_ALLOC_ZBUF) != 0) {
        if (sAlpha != 0xff) {
            gDPSetRenderMode(next_gfx(), G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2);
        } else {
            gDPSetRenderMode(next_gfx(), G_RM_AA_ZB_OPA_INTER, G_RM_NOOP2);
        }
    } else {
        if (sAlpha != 0xff) {
            gDPSetRenderMode(next_gfx(), G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
        } else {
            gDPSetRenderMode(next_gfx(), G_RM_AA_ZB_OPA_INTER, G_RM_NOOP2);
        }
    }
}

/* 250AE0 -> 250B30; orig name: func_801A2310 */
void gd_set_one_cycle(void) {
    gDPSetCycleType(next_gfx(), G_CYC_1CYCLE);
    update_render_mode();
}

/* 250B58 -> 250C18 */
void gddl_is_loading_shine_dl(Bool32 dlLoad) {
    if (dlLoad) {
        gSPDisplayList(next_gfx(), osVirtualToPhysical(&gd_dl_mario_face_shine));
    } else {
        gSPTexture(next_gfx(), 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_OFF);
        gDPSetCombineMode(next_gfx(), G_CC_SHADE, G_CC_SHADE);
    }
}

/* 250C18 -> 251014; orig name: func_801A2448 */
void start_view_dl(struct ObjView *view) {
    f32 ulx, uly, lrx, lry;
    if (view->upperLeft[0] < view->parent->upperLeft[0]) {
        ulx = view->parent->upperLeft[0];
    } else {
        ulx = view->upperLeft[0];
    }
    if ((view->upperLeft[0] + view->lowerRight[0]) > (view->parent->upperLeft[0] + view->parent->lowerRight[0])) {
        lrx = view->parent->upperLeft[0] + view->parent->lowerRight[0];
    } else {
        lrx = (view->upperLeft[0] + view->lowerRight[0]);
    }
    if (view->upperLeft[1] < view->parent->upperLeft[1]) {
        uly = view->parent->upperLeft[1];
    } else {
        uly = view->upperLeft[1];
    }
    if ((view->upperLeft[1] + view->lowerRight[1]) > (view->parent->upperLeft[1] + view->parent->lowerRight[1])) {
        lry = (view->parent->upperLeft[1] + view->parent->lowerRight[1]);
    } else {
        lry = (view->upperLeft[1] + view->lowerRight[1]);
    }
    if (ulx >= lrx) ulx = (lrx - 1.0f);
    if (uly >= lry) uly = (lry - 1.0f);
    gDPSetScissor(       next_gfx(), G_SC_NON_INTERLACE, ulx, uly, lrx, lry);
    gSPClearGeometryMode(next_gfx(), 0xFFFFFFFF);
    gSPSetGeometryMode(  next_gfx(), (G_LIGHTING | G_CULL_BACK | G_SHADING_SMOOTH | G_SHADE));
    if (view->flags & VIEW_ALLOC_ZBUF) gSPSetGeometryMode(next_gfx(), G_ZBUFFER);
    gd_dl_viewport();
    update_render_mode();
    gDPPipeSync(next_gfx());
}

/* 251014 -> 251A1C; orig name: func_801A2844 */
void parse_p1_controller(void) {
    u32 i;
    struct GdControl *gdctrl = &gGdCtrl;
    OSContPad *currInputs;
    OSContPad *prevInputs;
    // Copy current inputs to previous
    u8 *src  = (u8 *) gdctrl;
    u8 *dest = (u8 *) gdctrl->prevFrame;
    for ((i = 0); (i < sizeof(struct GdControl)); (i++)) *dest++ = *src++;
    gdctrl->unk50 = gdctrl->unk4C = gdctrl->dup = gdctrl->ddown = 0;
    currInputs = &sGdContPads[0];
    prevInputs = &sPrevFrameCont[0];
    // stick values
    gdctrl->stickXf      = currInputs->stick_x;
    gdctrl->stickYf      = currInputs->stick_y;
    gdctrl->stickDeltaX  =     gdctrl->stickX;
    gdctrl->stickDeltaY  =     gdctrl->stickY;
    gdctrl->stickX       = currInputs->stick_x;
    gdctrl->stickY       = currInputs->stick_y;
    gdctrl->stickDeltaX -=     gdctrl->stickX;
    gdctrl->stickDeltaY -=     gdctrl->stickY;
    // button values (as bools)
    gdctrl->trgL   = ((currInputs->button & L_TRIG    ) != 0);
    gdctrl->trgR   = ((currInputs->button & R_TRIG    ) != 0);
    gdctrl->btnA   = ((currInputs->button & A_BUTTON  ) != 0);
    gdctrl->btnB   = ((currInputs->button & B_BUTTON  ) != 0);
    gdctrl->cleft  = ((currInputs->button & L_CBUTTONS) != 0);
    gdctrl->cright = ((currInputs->button & R_CBUTTONS) != 0);
    gdctrl->cup    = ((currInputs->button & U_CBUTTONS) != 0);
    gdctrl->cdown  = ((currInputs->button & D_CBUTTONS) != 0);
    // but not these buttons??
    gdctrl->dleft  = (currInputs->button & L_JPAD);
    gdctrl->dright = (currInputs->button & R_JPAD);
    gdctrl->dup    = (currInputs->button & U_JPAD);
    gdctrl->ddown  = (currInputs->button & D_JPAD);
    gdctrl->startedDragging = (gdctrl->btnA && !gdctrl->dragging);
    // toggle if A is pressed? or is this just some seed for an rng?
    gdctrl->dragging      = gdctrl->btnA;
    gdctrl->AbtnPressWait = FALSE;
    if (gdctrl->startedDragging) {
        gdctrl->dragStartX = gdctrl->csrX;
        gdctrl->dragStartY = gdctrl->csrY;
        if ((gdctrl->currFrame - gdctrl->dragStartFrame) < 10) gdctrl->AbtnPressWait = TRUE;
    }
    if (gdctrl->dragging) gdctrl->dragStartFrame = gdctrl->currFrame;
    gdctrl->currFrame++;
    if ((currInputs->button & START_BUTTON) && !(prevInputs->button & START_BUTTON)) gdctrl->newStartPress ^= 1;
    // deadzone checks
    if (ABSI(gdctrl->stickX) >= 6) gdctrl->csrX += (gdctrl->stickX * 0.1f);
    if (ABSI(gdctrl->stickY) >= 6) gdctrl->csrY -= (gdctrl->stickY * 0.1f);
    // clamp cursor position within screen view bounds
    if (gdctrl->csrX < ( sScreenView->parent->upperLeft[0]                                       + 16.0f)) gdctrl->csrX = ( sScreenView->parent->upperLeft[0]                                       + 16.0f);
    if (gdctrl->csrX > ((sScreenView->parent->upperLeft[0] + sScreenView->parent->lowerRight[0]) - 48.0f)) gdctrl->csrX = ((sScreenView->parent->upperLeft[0] + sScreenView->parent->lowerRight[0]) - 48.0f);
    if (gdctrl->csrY < ( sScreenView->parent->upperLeft[1]                                       + 16.0f)) gdctrl->csrY = ( sScreenView->parent->upperLeft[1]                                       + 16.0f);
    if (gdctrl->csrY > ((sScreenView->parent->upperLeft[1] + sScreenView->parent->lowerRight[1]) - 32.0f)) gdctrl->csrY = ((sScreenView->parent->upperLeft[1] + sScreenView->parent->lowerRight[1]) - 32.0f);
    for ((i = 0); (i < sizeof(OSContPad)); (i++)) ((u8 *) prevInputs)[i] = ((u8 *) currInputs)[i];
}

/* 251E18 -> 2522B0 */
void gd_setproperty(enum GdProperty prop, f32 f1, f32 f2, f32 f3) {
    s32 parm;
    switch (prop) {
        case GD_PROP_LIGHTING:
            parm = (s32) f1;
            switch (parm) {
                case 1: gSPSetGeometryMode(  next_gfx(), G_LIGHTING); break;
                case 0: gSPClearGeometryMode(next_gfx(), G_LIGHTING); break;
            }
            break;
        case GD_PROP_AMB_COLOUR: vec3_set(sAmbScaleColour, f1, f2, f3); break;
        case GD_PROP_LIGHT_DIR:  vec3_set(sLightDirections[sLightId], (s32)(f1 * 120.0f),
                                                                      (s32)(f2 * 120.0f),
                                                                      (s32)(f3 * 120.0f)); break;
        case GD_PROP_DIFUSE_COLOUR: vec3_set(sLightScaleColours[sLightId], f1, f2, f3); break;
        case GD_PROP_CULLING:
            parm = (s32) f1;
            switch (parm) {
                case 1: gSPSetGeometryMode(  next_gfx(), G_CULL_BACK); break;
                case 0: gSPClearGeometryMode(next_gfx(), G_CULL_BACK); break;
            }
            break;
        default: gd_exit(); // Unkown property
    }
}

/* 2522C0 -> 25245C */
void gd_create_ortho_matrix(f32 l, f32 r, f32 b, f32 t, f32 n, f32 f) {
    uintptr_t orthoMtx;
    uintptr_t rotMtx;
    // Should produce G_RDPHALF_1 in Fast3D
    gSPPerspNormalize(next_gfx(), 0xFFFF);
    guOrtho(&DL_CURRENT_MTX(sCurrentGdDl), l, r, b, t, n, f, 1.0f);
    orthoMtx = GD_LOWER_29(&DL_CURRENT_MTX(sCurrentGdDl));
    gSPMatrix(next_gfx(), orthoMtx, (G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH));
    next_mtx();
    guRotate(&DL_CURRENT_MTX(sCurrentGdDl), 0.0f, 0.0f, 0.0f, 1.0f);
    rotMtx = GD_LOWER_29(&DL_CURRENT_MTX(sCurrentGdDl));
    gSPMatrix(next_gfx(), rotMtx, (G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH));
    next_mtx();
}

/* 25245C -> 25262C */
void gd_create_perspective_matrix(f32 fovy, f32 aspect, f32 near, f32 far) {
    u16 perspNorm;
    uintptr_t perspecMtx;
    uintptr_t rotMtx;
    sGdPerspTimer += 0.1f;
    guPerspective(&DL_CURRENT_MTX(sCurrentGdDl), &perspNorm, fovy, aspect, near, far, 1.0f);
    gSPPerspNormalize(next_gfx(), perspNorm);
    perspecMtx = GD_LOWER_29(&DL_CURRENT_MTX(sCurrentGdDl));
    gSPMatrix(next_gfx(), perspecMtx, (G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH));
    next_mtx();
    guRotate(&DL_CURRENT_MTX(sCurrentGdDl), 0.0f, 0.0f, 0.0f, 1.0f);
    rotMtx = GD_LOWER_29(&DL_CURRENT_MTX(sCurrentGdDl));
    gSPMatrix(next_gfx(), rotMtx, (G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH));
    next_mtx();
}

/* 25262C -> 252AF8 */
s32 setup_view_buffers(UNUSED const char *name, struct ObjView *view) {
    // char memtrackerName[0x100];
    if (view->flags & (VIEW_Z_BUF | VIEW_COLOUR_BUF) && !(view->flags & VIEW_UNK_1000)) {
        if (view->flags & VIEW_COLOUR_BUF) {
            // sprintf(memtrackerName, "%s CBuf", name);
            // start_memtracker(memtrackerName);
            view->colourBufs[0] = gd_malloc((u32)((2.0f * view->lowerRight[0] * view->lowerRight[1]) + 64.0f), 0x20);
            if (view->flags & VIEW_2_COL_BUF) {
                view->colourBufs[1] = gd_malloc((u32)((2.0f * view->lowerRight[0] * view->lowerRight[1]) + 64.0f), 0x20);
            } else {
                view->colourBufs[1] = view->colourBufs[0];
            }
            view->colourBufs[0] = (void *) ALIGN((uintptr_t) view->colourBufs[0], 64);
            view->colourBufs[1] = (void *) ALIGN((uintptr_t) view->colourBufs[1], 64);
            // stop_memtracker(memtrackerName);
            if ((view->colourBufs[0] == NULL) || (view->colourBufs[1] == NULL)) gd_exit(); // Not enough DRAM for colour buffers
            view->parent = view;
        } else {
            view->parent = sScreenView;
        }
        if (view->flags & VIEW_Z_BUF) {
            // sprintf(memtrackerName, "%s ZBuf", name);
            // start_memtracker(memtrackerName);
            if (view->flags & VIEW_ALLOC_ZBUF) {
                view->zbuf = gd_malloc((u32)((2.0f * view->lowerRight[0] * view->lowerRight[1]) + 64.0f), 0x40);
                if (view->zbuf == NULL) gd_exit(); // Not enough DRAM for Z buffer
                view->zbuf = (void *) ALIGN((uintptr_t) view->zbuf, 64);
            }
            // stop_memtracker(memtrackerName);
        } else {
            view->zbuf = sScreenView->zbuf;
        }
    } else {
        view->parent = sScreenView;
    }
    view->gdDlNum = 0;
    // view->unk74   = 0; // unused
    if (view->flags & VIEW_DEFAULT_PARENT) view->parent = NULL;
    return 0;
}

/* 252AF8 -> 252BAC; orig name: _InitControllers */
void gd_init_controllers(void) {
    OSContPad *p1cont = &sPrevFrameCont[0];
    u32 i;
    osCreateMesgQueue(          &sGdControllerMsgQ, D_801BE848, ARRAY_COUNT(D_801BE848));
    osSetEventMesg(OS_EVENT_SI, &sGdControllerMsgQ, (OSMesg) OS_MESG_SI_COMPLETE);
    osContInit(                 &sGdControllerMsgQ, &D_801BAEA0, D_801BAE60);
    osContStartReadData(        &sGdControllerMsgQ);
    for ((i = 0); (i < sizeof(OSContPad)); (i++)) ((u8 *) p1cont)[i] = 0;
}

/* 253018 -> 253084 */
void func_801A4848(s32 linkDl) {
    struct GdDisplayList *curDl;
    curDl        = sCurrentGdDl;
    sCurrentGdDl = sMHeadMainDls[gGdFrameBufNum];
    branch_cur_dl_to_num(linkDl);
    sCurrentGdDl = curDl;
}

/* 2530C0 -> 2530D8; orig name: func_801A48F0 */
void set_active_view(struct ObjView *v) {
    sActiveView = v;
}

/* 2533DC -> 253728; orig name: func_801A4C0C */
void update_cursor(void) {
    if (sHandView == NULL) return;
    if ((gGdCtrl.currFrame - gGdCtrl.dragStartFrame) < 300) {
        sHandView->flags |= VIEW_UPDATE;
        // by playing the sfx every frame, it will only play once as it
        // never leaves the "sfx played last frame" buffer
        gd_play_sfx(GD_SFX_HAND_APPEAR);
    } else {
        sHandView->flags &= ~VIEW_UPDATE;
        gd_play_sfx(GD_SFX_HAND_DISAPPEAR);
    }
    sHandView->upperLeft[0] = (f32) gGdCtrl.csrX;
    sHandView->upperLeft[1] = (f32) gGdCtrl.csrY;
    // Make hand display list
    begin_gddl(sHandShape->dlNums[gGdFrameBufNum]);
    gd_put_sprite((TexturePtr *) (gGdCtrl.dragging ? gd_texture_hand_closed : gd_texture_hand_open), sHandView->upperLeft[0], sHandView->upperLeft[1], 0x20, 0x20);
    gd_enddlsplist_parent();
    if (sHandView->upperLeft[0] <  sHandView->parent->upperLeft[0]                                    ) sHandView->upperLeft[0] =  sHandView->parent->upperLeft[0];
    if (sHandView->upperLeft[0] > (sHandView->parent->upperLeft[0] + sHandView->parent->lowerRight[0])) sHandView->upperLeft[0] = (sHandView->parent->upperLeft[0] + sHandView->parent->lowerRight[0]);
    if (sHandView->upperLeft[1] <  sHandView->parent->upperLeft[1]                                    ) sHandView->upperLeft[1] =  sHandView->parent->upperLeft[1];
    if (sHandView->upperLeft[1] > (sHandView->parent->upperLeft[1] + sHandView->parent->lowerRight[1])) sHandView->upperLeft[1] = (sHandView->parent->upperLeft[1] + sHandView->parent->lowerRight[1]);
}

/* 253938 -> 2539DC; orig name: func_801A5168 */
void update_view_and_dl(struct ObjView *view) {
    s32 prevFlags;
    prevFlags = view->flags;
    update_view(view);
    if (prevFlags & VIEW_UPDATE) {
        sCurrentGdDl = sMHeadMainDls[gGdFrameBufNum];
        if (view->gdDlNum != 0) func_801A4848(view->gdDlNum);
    }
}

/* 253BC8 -> 2540E0 */
void gd_init(void) {
    s32 i = (u32)(sMemBlockPoolSize - DOUBLE_SIZE_ON_64_BIT(0x3E800));
    s8 *data = gd_allocblock(i);
    gd_add_mem_to_heap(i, data, 0x10);
    sAlpha            = (u16) 0xff;
    gGdFrameBufNum    = 0;
    sGdDlCount        = 0;
    sLightId          = 0;
    vec3_zero(sAmbScaleColour);
    const ColorRGBf redVec = ARR(COLOR_RGBF_RED);
    for ((i = 0); (i < ARRAY_COUNT(sLightScaleColours)); (i++)) {
        vec3_copy(sLightScaleColours[i], redVec);
        vec3_set(sLightDirections[i], 0, 120, 0);
    }
    sNumLights = NUMLIGHTS_2;
    mtxf_identity(sInitIdnMat4);
    mtxf_to_mtx(&sIdnMtx, sInitIdnMat4);
    // remove_all_memtrackers();
    null_obj_lists();
    // start_memtracker("total");
    sStaticDl          = new_gd_dl(0, 1900, 4000,   1, 300, 8);
    sDynamicMainDls[0] = new_gd_dl(1,  600,   10, 200,  10, 3);
    sDynamicMainDls[1] = new_gd_dl(1,  600,   10, 200,  10, 3);
    sMHeadMainDls[0]   = new_gd_dl(1,  100,    0,   0,   0, 0);
    sMHeadMainDls[1]   = new_gd_dl(1,  100,    0,   0,   0, 0);
    for ((i = 0); (i < ARRAY_COUNT(sViewDls)); (i++)) {
        sViewDls[i][0] = create_child_gdl(1, sDynamicMainDls[0]);
        sViewDls[i][1] = create_child_gdl(1, sDynamicMainDls[1]);
    }
    sScreenView           = make_view("screenview2", (VIEW_2_COL_BUF | VIEW_UNK_1000 | VIEW_COLOUR_BUF | VIEW_Z_BUF), 0, 0, 0, 320, 240, NULL);
    vec3_zero(sScreenView->colour);
    sScreenView->parent   = sScreenView;
    sScreenView->flags   &= ~VIEW_UPDATE;
    sActiveView           = sScreenView;
    // Zero out controller inputs
    data = (s8 *) &gGdCtrl;
    for ((i = 0); ((u32) i < sizeof(struct GdControl)); (i++)) *data++ = 0;
    // 801A5868
    gGdCtrl.newStartPress  = FALSE;
    gGdCtrl.prevFrame      = &gGdCtrlPrev;
    gGdCtrl.csrX           =   160;
    gGdCtrl.csrY           =   120;
    gGdCtrl.dragStartFrame = -1000;
}

/**
 * Initializes the pick buffer. This functions like the `pick` or `gselect`
 * functions from IRIS GL.
 * @param buf  pointer to an array of 16-bit values
 * @param len  maximum number of values to store
 */
void init_pick_buf(s16 *buf, s32 len) {
    buf[0]           = 0;
    buf[1]           = 0;
    sPickBufLen      = len;
    sPickBuf         = buf;
    sPickBufPosition = 0;
}

/**
 * Stores a 16-bit value into the pick buffer. This functions like the
 * `pushname` function from IRIS GL.
 */
void store_in_pickbuf(s16 data) {
    sPickBuf[sPickBufPosition++] = data;
}

/* 25421C -> 254250; orig name: func_801A5A4C
** Divides by 3, since in the final game, only thing stored
** in the pick buf is a tupple of three halves: (datasize, objtype, objnumber)
** (datasize is always 2) */
s32 get_cur_pickbuf_offset(void) {
    return (sPickBufPosition / 3);
}

/* 254AC0 -> 254DFC; orig name: PutSprite */
void gd_put_sprite(TexturePtr *sprite, s32 x, s32 y, s32 wx, s32 wy) {
    s32 c, r;
    gSPDisplayList(next_gfx(), osVirtualToPhysical(gd_dl_sprite_start_tex_block));
    for ((r = 0); (r < wy); (r += 32)) {
        for ((c = 0); (c < wx); (c += 32)) {
             gDPLoadTextureBlock(next_gfx(), ((r * 32) + sprite + c), G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
                (G_TX_WRAP | G_TX_NOMIRROR), (G_TX_WRAP | G_TX_NOMIRROR), G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD)
             gSPTextureRectangle(next_gfx(), (x << 2), ((y + r) << 2), ((x + 32) << 2), ((y + r + 32) << 2),
                G_TX_RENDERTILE, 0, 0, (1 << 10), (1 << 10));
        }
    }
    gDPPipeSync(     next_gfx());
    gDPSetCycleType( next_gfx(), G_CYC_1CYCLE);
    gDPSetRenderMode(next_gfx(), G_RM_AA_ZB_OPA_INTER, G_RM_NOOP2);
    gSPTexture(      next_gfx(), 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_OFF);
}

/* 254DFC -> 254F94; orig name: proc_dyn_list */
void gd_setup_cursor(struct ObjGroup *parentgrp) {
    struct ObjView *mouseview;
    struct ObjGroup *mousegrp;
    UNUSED struct ObjNet *net;
    sHandShape = make_shape("mouse");
    sHandShape->dlNums[0] = gd_startdisplist(7);
    gd_put_sprite((TexturePtr *) gd_texture_hand_open, 100, 100, 32, 32);
    gd_enddlsplist_parent();
    sHandShape->dlNums[1] = gd_startdisplist(7);
    gd_put_sprite((TexturePtr *) gd_texture_hand_open, 100, 100, 32, 32);
    gd_enddlsplist_parent();
    d_start_group("mouseg");
    net = (struct ObjNet *) d_makeobj(D_NET, AsDynName(0));
    d_set_init_pos(gVec3fZero);
    d_set_type(3);
    d_set_shapeptrptr(&sHandShape);
    d_end_group("mouseg");
    mousegrp = (struct ObjGroup *) d_use_obj("mouseg");
    mouseview = make_view("mouseview", (VIEW_2_COL_BUF | VIEW_ALLOC_ZBUF | VIEW_1_CYCLE | VIEW_MOVEMENT | VIEW_DRAW), 2, 0, 0, 32, 32, mousegrp);
    mouseview->flags &= ~VIEW_UPDATE;
    sHandView = mouseview;
    if (parentgrp != NULL) addto_group(parentgrp, &mousegrp->header);
}

#ifndef NO_SEGMENTED_MEMORY
/**
 * Copies `size` bytes of data from ROM address `romAddr` to RAM address `vAddr`.
 */
static void gd_block_dma(u32 romAddr, void *vAddr, s32 size) {
    s32 blockSize;
    do {
        if ((blockSize = size) > 0x1000) blockSize = 0x1000;
        osPiStartDma(&sGdDMAReqMesg, OS_MESG_PRI_NORMAL, OS_READ, romAddr, vAddr, blockSize, &sGdDMAQueue);
        osRecvMesg(&sGdDMAQueue, &sGdDMACompleteMsg, OS_MESG_BLOCK);
        romAddr += blockSize;
        vAddr = (void *) ((uintptr_t) vAddr + blockSize);
        size -= 0x1000;
    } while (size > 0);
}

/**
 * Loads the specified DynList from ROM and processes it.
 */
struct GdObj *load_dynlist(struct DynList *dynlist) {
    void *allocPtr;
    s32 tlbEntries;
    struct GdObj *loadedList;
    s32 i = -1;
    uintptr_t dynlistSegStart = (uintptr_t) _gd_dynlistsSegmentRomStart;
    uintptr_t dynlistSegEnd   = (uintptr_t) _gd_dynlistsSegmentRomEnd;
#define PAGE_SIZE 65536  // size of a 64K TLB page
    u32 segSize   = (dynlistSegEnd - dynlistSegStart);
    u8 *allocSegSpace = gd_malloc_temp(segSize + PAGE_SIZE);
    if ((allocPtr = (void *) allocSegSpace) == NULL) gd_exit(); // Not enough DRAM for DATA segment
    allocSegSpace = (u8 *) (((uintptr_t) allocSegSpace + PAGE_SIZE) & 0xFFFF0000);
    // Copy the dynlist data from ROM
    gd_block_dma(dynlistSegStart, (void *) allocSegSpace, segSize);
    osUnmapTLBAll();
    tlbEntries = (((segSize / PAGE_SIZE) / 2) + 1);
    if (tlbEntries >= 31) gd_exit(); // too many TLBs
    // Map virtual address 0x04000000 to `allocSegSpace`
    for ((i = 0); (i < tlbEntries); (i++)) {
        osMapTLB(i, OS_PM_64K,
            (void *) (uintptr_t) (0x04000000 + (i * 2 * PAGE_SIZE)),  // virtual address to map
            GD_LOWER_24(((uintptr_t) allocSegSpace) + (i * 2 * PAGE_SIZE) +         0),  // even page address
            GD_LOWER_24(((uintptr_t) allocSegSpace) + (i * 2 * PAGE_SIZE) + PAGE_SIZE),  // odd page address
            -1);
    }
#undef PAGE_SIZE
    // process the dynlist
    loadedList = proc_dynlist(dynlist);
    gd_free(allocPtr);
    osUnmapTLBAll();
    return loadedList;
}
#else
struct GdObj *load_dynlist(struct DynList *dynlist) {
    return proc_dynlist(dynlist);
}
#endif
