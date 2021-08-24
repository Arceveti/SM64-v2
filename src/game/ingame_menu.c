#include <ultra64.h>

#include "actors/common1.h"
#include "area.h"
#include "audio/external.h"
#include "camera.h"
#include "course_table.h"
#include "dialog_ids.h"
#include "engine/math_util.h"
#include "eu_translation.h"
#include "segment_symbols.h"
#include "game_init.h"
#include "gfx_dimensions.h"
#include "ingame_menu.h"
#include "level_update.h"
#include "levels/castle_grounds/header.h"
#include "memory.h"
#include "print.h"
#include "save_file.h"
#include "segment2.h"
#include "segment7.h"
#include "seq_ids.h"
#include "sm64.h"
#include "text_strings.h"
#include "types.h"
#include "config.h"
#ifdef PUPPYCAM
#include "puppycam2.h"
#endif

u16 gDialogColorFadeTimer;
s8  gLastDialogLineNum;
s32 gDialogVariable;
u16 gDialogTextAlpha;
ScreenPos gCutsceneMsgXOffset;
ScreenPos gCutsceneMsgYOffset;
s8  gRedCoinsCollected;
#ifdef HUD_SECRETS
s8  gSecretsCollected;
#endif

#if MULTILANG
#define seg2_course_name_table course_name_table_eu_en
#define seg2_act_name_table act_name_table_eu_en
#define seg2_dialog_table dialog_table_eu_en
#endif

s16 gInGameLanguage = 0;
s16 gLoadedLanguage = 0;

void *languageTable[][3] =
{
    {&seg2_dialog_table, &seg2_course_name_table, &seg2_act_name_table}, //In EU, this is just mirroring English.
    #if MULTILANG
    {&dialog_table_eu_en, &course_name_table_eu_en, &act_name_table_eu_en},
    {&dialog_table_eu_fr, &course_name_table_eu_fr, &act_name_table_eu_fr},
    {&dialog_table_eu_de, &course_name_table_eu_de, &act_name_table_eu_de},
    #endif
};

extern u8 gLastCompletedCourseNum;
extern u8 gLastCompletedStarNum;

enum DialogBoxState {
    DIALOG_STATE_OPENING,
    DIALOG_STATE_VERTICAL,
    DIALOG_STATE_HORIZONTAL,
    DIALOG_STATE_CLOSING
};

enum DialogBoxPageState {
    DIALOG_PAGE_STATE_NONE,
    DIALOG_PAGE_STATE_SCROLL,
    DIALOG_PAGE_STATE_END
};

enum DialogBoxType {
    DIALOG_TYPE_ROTATE, // used in NPCs and level messages
    DIALOG_TYPE_ZOOM    // used in signposts and wall signs and etc
};

enum DialogMark { DIALOG_MARK_NONE = 0, DIALOG_MARK_DAKUTEN = 1, DIALOG_MARK_HANDAKUTEN = 2 };

#define DEFAULT_DIALOG_BOX_ANGLE 90.0f
#define DEFAULT_DIALOG_BOX_SCALE 19.0f

#if defined(VERSION_US) || defined(VERSION_EU)
u8 gDialogCharWidths[256] = { // TODO: Is there a way to auto generate this?
    7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  6,  6,  6,  6,  6,  6,
    6,  6,  5,  6,  6,  5,  8,  8,  6,  6,  6,  6,  6,  5,  6,  6,
    8,  7,  6,  6,  6,  5,  5,  6,  5,  5,  6,  5,  4,  5,  5,  3,
    7,  5,  5,  5,  6,  5,  5,  5,  5,  5,  7,  7,  5,  5,  4,  4,
    8,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    8,  8,  8,  8,  7,  7,  6,  7,  7,  0,  0,  0,  0,  0,  0,  0,
#ifdef VERSION_EU
    6,  6,  6,  0,  6,  6,  6,  0,  0,  0,  0,  0,  0,  0,  0,  4,
    5,  5,  5,  5,  6,  6,  6,  6,  0,  0,  0,  0,  0,  0,  0,  0,
    5,  5,  5,  0,  6,  6,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  5,  5,  0,  0,  6,  6,  0,  0,  0,  0,  0,  0,  0,  5,  6,
    0,  4,  4,  0,  0,  5,  5,  0,  0,  0,  0,  0,  0,  0,  0,  0,
#else
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  5,  6,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
#endif
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
#ifdef VERSION_EU
    7,  5, 10,  5,  9,  8,  4,  0,  0,  0,  0,  5,  5,  6,  5,  0,
#else
    7,  5, 10,  5,  9,  8,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,
#endif
    0,  0,  5,  7,  7,  6,  6,  8,  0,  8, 10,  6,  4, 10,  0,  0
};
#endif

s8  gDialogBoxState       = DIALOG_STATE_OPENING;
f32 gDialogBoxOpenTimer   = DEFAULT_DIALOG_BOX_ANGLE;
f32 gDialogBoxScale       = DEFAULT_DIALOG_BOX_SCALE;
s16 gDialogScrollOffsetY  = 0;
s8  gDialogBoxType        = DIALOG_TYPE_ROTATE;
s16 gDialogID             = DIALOG_NONE;
s16 gLastDialogPageStrPos = 0;
s16 gDialogTextPos        = 0;
s8  gDialogLineNum        = 1;
s8  gLastDialogResponse   = 0;
u8  gMenuHoldKeyIndex     = 0;
u8  gMenuHoldKeyTimer     = 0;
s32 gDialogResponse       = DIALOG_RESPONSE_NONE;


void create_dl_identity_matrix(void) {
    Mtx *matrix = (Mtx *) alloc_display_list(sizeof(Mtx));
    if (matrix == NULL) return;
#ifndef GBI_FLOATS
    matrix->m[0][0] = 0x00010000;    matrix->m[1][0] = 0x00000000;    matrix->m[2][0] = 0x00000000;    matrix->m[3][0] = 0x00000000;
    matrix->m[0][1] = 0x00000000;    matrix->m[1][1] = 0x00010000;    matrix->m[2][1] = 0x00000000;    matrix->m[3][1] = 0x00000000;
    matrix->m[0][2] = 0x00000001;    matrix->m[1][2] = 0x00000000;    matrix->m[2][2] = 0x00000000;    matrix->m[3][2] = 0x00000000;
    matrix->m[0][3] = 0x00000000;    matrix->m[1][3] = 0x00000001;    matrix->m[2][3] = 0x00000000;    matrix->m[3][3] = 0x00000000;
#else
    guMtxIdent(matrix);
#endif
    gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(matrix), (G_MTX_MODELVIEW  | G_MTX_LOAD | G_MTX_NOPUSH));
    gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(matrix), (G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH));
}

void create_dl_translation_matrix(s8 pushOp, f32 x, f32 y, f32 z) {
    Mtx *matrix = (Mtx *) alloc_display_list(sizeof(Mtx));
    if (matrix == NULL) return;
    guTranslate(matrix, x, y, z);
    gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(matrix), (G_MTX_MODELVIEW | G_MTX_MUL | pushOp));
}

void create_dl_rotation_matrix(s8 pushOp, f32 a, f32 x, f32 y, f32 z) {
    Mtx *matrix = (Mtx *) alloc_display_list(sizeof(Mtx));
    if (matrix == NULL) return;
    guRotate(matrix, a, x, y, z);
    gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(matrix), (G_MTX_MODELVIEW | G_MTX_MUL | pushOp));
}

void create_dl_scale_matrix(s8 pushOp, f32 x, f32 y, f32 z) {
    Mtx *matrix = (Mtx *) alloc_display_list(sizeof(Mtx));
    if (matrix == NULL) return;
    guScale(matrix, x, y, z);
    gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(matrix), (G_MTX_MODELVIEW | G_MTX_MUL | pushOp));
}

void create_dl_ortho_matrix(void) {
    Mtx *matrix = (Mtx *) alloc_display_list(sizeof(Mtx));
    if (matrix == NULL) return;
    create_dl_identity_matrix();
    guOrtho(matrix, 0.0f, SCREEN_WIDTH, 0.0f, SCREEN_HEIGHT, -10.0f, 10.0f, 1.0f);
    // Should produce G_RDPHALF_1 in Fast3D
    gSPPerspNormalize(gDisplayListHead++, 0xFFFF);
    gSPMatrix(        gDisplayListHead++, VIRTUAL_TO_PHYSICAL(matrix), (G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH))
}

#if !defined(VERSION_JP) && !defined(VERSION_SH)
UNUSED
#endif
static u8 *alloc_ia8_text_from_i1(u16 *in, s16 width, s16 height) { //! uchar or Texture?
    s32 inPos;
    u16 bitMask;
    u8 *out;
    s16 outPos = 0;
    out = alloc_display_list((u32) width * (u32) height);
    if (out == NULL) return NULL;
    for (inPos = 0; inPos < ((width * height) / 16); inPos++) {
        bitMask = 0x8000;
        while (bitMask != 0) {
            out[outPos] = ((in[inPos] & bitMask) ? 0xFF : 0x00);
            bitMask >>= 1;
            // bitMask /= 2; //? bitMask >> 1;
            outPos++;
        }
    }
    return out;
}

u8 *alloc_ia4_tex_from_i1(u8 *in, s16 width, s16 height) {
    u32 size = (u32) width * (u32) height;
    u8 *out;
    s32 inPos;
    s16 outPos;
    u8 bitMask;
    outPos = 0;
    out = (u8 *) alloc_display_list(size);
    if (out == NULL) return NULL;
    for (inPos = 0; inPos < (width * height) / 4; inPos++) {
        bitMask = 0x80;
        while (bitMask != 0) {
            out[outPos] = ((in[inPos] & bitMask) ? 0xF0 : 0x00);
            bitMask /= 2;
            out[outPos] = ((in[inPos] & bitMask) ? out[outPos] + 0x0F : out[outPos]);
            bitMask /= 2;
            outPos++;
        }
    }
    return out;
}

void render_generic_char(uchar c) {
    void **fontLUT;
    void *packedTexture;
#ifdef VERSION_EU
    void *unpackedTexture;
#endif
    fontLUT         = segmented_to_virtual(main_font_lut);
    packedTexture   = segmented_to_virtual(fontLUT[c]);
#ifdef VERSION_EU
    unpackedTexture = alloc_ia4_tex_from_i1(packedTexture, 8, 8);
    gDPPipeSync(       gDisplayListHead++);
    gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_IA, G_IM_SIZ_16b, 1, VIRTUAL_TO_PHYSICAL(unpackedTexture));
#else
    gDPPipeSync(       gDisplayListHead++);
    gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_IA, G_IM_SIZ_16b, 1, VIRTUAL_TO_PHYSICAL(packedTexture));
#endif
    gSPDisplayList(    gDisplayListHead++, dl_ia_text_tex_settings);
}


struct MultiTextEntry {
    u8 length;
    uchar str[4];
};

#define TEXT_THE_RAW ASCII_TO_DIALOG('t'), ASCII_TO_DIALOG('h'), ASCII_TO_DIALOG('e'), 0x00
#define TEXT_YOU_RAW ASCII_TO_DIALOG('y'), ASCII_TO_DIALOG('o'), ASCII_TO_DIALOG('u'), 0x00

enum MultiStringIDs { STRING_THE, STRING_YOU };

/*
 * Place the multi-text string according to the ID passed. (US, EU)
 * 0: 'the'
 * 1: 'you'
 */
void render_multi_text_string(s8 multiTextID) {
    s8 i;
    struct MultiTextEntry textLengths[2] = {
        { 3, { TEXT_THE_RAW } },
        { 3, { TEXT_YOU_RAW } },
    };
    for (i = 0; i < textLengths[multiTextID].length; i++) {
        render_generic_char(textLengths[multiTextID].str[i]);
        create_dl_translation_matrix(G_MTX_NOPUSH, (f32)(gDialogCharWidths[textLengths[multiTextID].str[i]]), 0.0f, 0.0f);
    }
}

#define MAX_STRING_WIDTH 16

/**
 * Prints a generic white string.
 * In JP/EU a IA1 texture is used but in US a IA4 texture is used.
 */
void print_generic_string(ScreenPos x, ScreenPos y, const uchar *str) {
    UNUSED s8 mark    = DIALOG_MARK_NONE; // unused in EU
    s32 strPos        = 0;
    u8  lineNum       = 1;
    s16 colorLoop;
    ColorRGBA rgbaColors = {0, 0, 0, 0};
    u8  customColor   = FALSE;
    u8  diffTmp       = 0;
    create_dl_translation_matrix(G_MTX_PUSH, x, y, 0.0f);
    while (str[strPos] != DIALOG_CHAR_TERMINATOR) {
        if (customColor) {
            gDPSetEnvColor(gDisplayListHead++, rgbaColors[0], rgbaColors[1], rgbaColors[2], rgbaColors[3]);
        } else {
            if (customColor == 2) {
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255); // TODO: Is it possible to retrieve the original color that was set before print_generic_string was called?
                customColor = FALSE;
            }
        }
        switch (str[strPos]) {
            case DIALOG_CHAR_COLOR:
                customColor = TRUE;
                strPos++;
                for ((colorLoop = (strPos + 8)); (strPos < colorLoop); (++strPos)) {
                    diffTmp = 0;
                    if ((str[strPos] >= 0x24) && (str[strPos] <= 0x29)) {
                        diffTmp = 0x1A;
                    } else if (str[strPos] >= 0x10) {
                        customColor = 2;
                        strPos      = (colorLoop - 8);
                        for (diffTmp = 0; diffTmp < 8; ++diffTmp) if (str[strPos + diffTmp] != 0x9F) break;
                        if (diffTmp == 8) strPos += diffTmp;
                        break;
                    }
                    if (!((8 - (colorLoop - strPos)) & 0x1)) {
                        rgbaColors[(8 - (colorLoop - strPos)) / 2]  = (((str[strPos] - diffTmp) & 0x0F) << 4);
                    } else {
                        rgbaColors[(8 - (colorLoop - strPos)) / 2] +=  ((str[strPos] - diffTmp) & 0x0F);
                    }
                }
                strPos--;
                break;
            case DIALOG_CHAR_DAKUTEN:
                mark = DIALOG_MARK_DAKUTEN;
                break;
            case DIALOG_CHAR_PERIOD_OR_HANDAKUTEN:
                mark = DIALOG_MARK_HANDAKUTEN;
                break;
            case DIALOG_CHAR_NEWLINE:
                gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
                create_dl_translation_matrix(G_MTX_PUSH, x, (y - (lineNum * MAX_STRING_WIDTH)), 0.0f);
                lineNum++;
                break;
            case DIALOG_CHAR_PERIOD:
                create_dl_translation_matrix(G_MTX_PUSH, -2.0f, -5.0f, 0.0f);
                render_generic_char(DIALOG_CHAR_PERIOD_OR_HANDAKUTEN);
                gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
                break;
            case DIALOG_CHAR_SLASH:
                create_dl_translation_matrix(G_MTX_NOPUSH, (f32)(gDialogCharWidths[DIALOG_CHAR_SPACE] * 2), 0.0f, 0.0f);
                break;
            case DIALOG_CHAR_MULTI_THE:
                render_multi_text_string(STRING_THE);
                break;
            case DIALOG_CHAR_MULTI_YOU:
                render_multi_text_string(STRING_YOU);
                break;
            case DIALOG_CHAR_SPACE:
                create_dl_translation_matrix(G_MTX_NOPUSH, (f32)(gDialogCharWidths[DIALOG_CHAR_SPACE]), 0.0f, 0.0f);
                break; // ? needed to match
            default:
                render_generic_char(str[strPos]);
                if (mark != DIALOG_MARK_NONE) {
                    create_dl_translation_matrix(G_MTX_PUSH, 5.0f, 5.0f, 0.0f);
                    render_generic_char(mark + 0xEF);
                    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
                    mark = DIALOG_MARK_NONE;
                }
                create_dl_translation_matrix(G_MTX_NOPUSH, (f32)(gDialogCharWidths[str[strPos]]), 0.0f, 0.0f);
                break; // what an odd difference. US added a useless break here.
        }
        strPos++;
    }
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
}

/**
 * Prints a char depending on the index of the hud table list defined.
 */
u32 print_hud_lut_char(s8 hudLUT, ScreenPos x, ScreenPos y, const uchar c) {
    void **hudLUT1 = segmented_to_virtual(menu_hud_lut); // Japanese Menu HUD Color font
    void **hudLUT2 = segmented_to_virtual(main_hud_lut); // 0-9 A-Z HUD Color Font
    gDPPipeSync(gDisplayListHead++);
    if (hudLUT == HUD_LUT_JPMENU) gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, hudLUT1[c]);
    if (hudLUT == HUD_LUT_GLOBAL) gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, hudLUT2[c]);
    gSPDisplayList(     gDisplayListHead++, dl_rgba16_load_tex_block);
    gSPTextureRectangle(gDisplayListHead++, (x << 2), (y << 2), ((x + 16) << 2),
                        ((y + 16) << 2), G_TX_RENDERTILE, 0, 0, (1 << 10), (1 << 10));
    return ((hudLUT == HUD_LUT_JPMENU) ? 16 : 12);
}

/**
 * Prints a hud string depending on the hud table list defined.
 */
void print_hud_lut_string(s8 hudLUT, ScreenPos x, ScreenPos y, const uchar *str) {
    s32 strPos     = 0;
    while (str[strPos] != GLOBAR_CHAR_TERMINATOR) {
        x += print_hud_lut_char(hudLUT, x, y, str[strPos]);
        strPos++;
    }
}

/**
 * Prints a centered hud string depending on the hud table list defined.
 */
void print_hud_lut_string_centered(s8 hudLUT, ScreenPos x, ScreenPos y, const uchar *str) {
    s32 strPos, strLength = 0;
    while (str[strLength] != GLOBAR_CHAR_TERMINATOR) strLength++;
    x -= (strLength * ((hudLUT == HUD_LUT_JPMENU) ? 8 : 6));
    for ((strPos = 0); (strPos < strLength); (strPos++)) x += print_hud_lut_char(hudLUT, x, y, str[strPos]);
}


void print_menu_generic_string(ScreenPos x, ScreenPos y, const uchar *str) {
    UNUSED s8 mark = DIALOG_MARK_NONE; // unused in EU
    s32 strPos = 0;
    u32 curX   = x;
    u32 curY   = y;
    void **fontLUT = segmented_to_virtual(menu_font_lut);
    while (str[strPos] != DIALOG_CHAR_TERMINATOR) {
        switch (str[strPos]) {
            case DIALOG_CHAR_DAKUTEN:
                mark = DIALOG_MARK_DAKUTEN;
                break;
            case DIALOG_CHAR_PERIOD_OR_HANDAKUTEN:
                mark = DIALOG_MARK_HANDAKUTEN;
                break;
            case DIALOG_CHAR_SPACE:
                curX += 4;
                break;
            default:
                gDPSetTextureImage( gDisplayListHead++, G_IM_FMT_IA, G_IM_SIZ_8b, 1, fontLUT[str[strPos]]);
                gDPLoadSync(        gDisplayListHead++);
                gDPLoadBlock(       gDisplayListHead++, G_TX_LOADTILE, 0, 0, ((8 * 8) - 1), CALC_DXT(8, G_IM_SIZ_8b_BYTES));
                gSPTextureRectangle(gDisplayListHead++, (curX << 2), (curY << 2), ((curX + 8) << 2),
                                    ((curY + 8) << 2), G_TX_RENDERTILE, 0, 0, (1 << 10), (1 << 10));
                if (mark != DIALOG_MARK_NONE) {
                    gDPSetTextureImage( gDisplayListHead++, G_IM_FMT_IA, G_IM_SIZ_8b, 1, fontLUT[mark + 0xEF]);
                    gDPLoadSync(        gDisplayListHead++);
                    gDPLoadBlock(       gDisplayListHead++, G_TX_LOADTILE, 0, 0, ((8 * 8) - 1), CALC_DXT(8, G_IM_SIZ_8b_BYTES));
                    gSPTextureRectangle(gDisplayListHead++, ((curX + 6) << 2), ((curY - 7) << 2),
                                        (((curX + 6) + 8) << 2), (((curY - 7) + 8) << 2), G_TX_RENDERTILE, 0, 0, (1 << 10), (1 << 10));
                    mark = DIALOG_MARK_NONE;
                }
                curX += gDialogCharWidths[str[strPos]];
        }
        strPos++;
    }
}

void print_credits_string(ScreenPos x, ScreenPos y, const uchar *str) {
    s32 strPos = 0;
    void **fontLUT = segmented_to_virtual(main_credits_font_lut);
    //! ScreenPos type?
    u32 curX = x;
    u32 curY = y;
    gDPSetTile(    gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0,
                   (G_TX_WRAP | G_TX_NOMIRROR), G_TX_NOMASK, G_TX_NOLOD, (G_TX_WRAP | G_TX_NOMIRROR), G_TX_NOMASK, G_TX_NOLOD);
    gDPTileSync(   gDisplayListHead++);
    gDPSetTile(    gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 2, 0, G_TX_RENDERTILE, 0,
                   G_TX_CLAMP, 3, G_TX_NOLOD, G_TX_CLAMP, 3, G_TX_NOLOD);
    gDPSetTileSize(gDisplayListHead++, G_TX_RENDERTILE, 0, 0, ((8 - 1) << G_TEXTURE_IMAGE_FRAC), ((8 - 1) << G_TEXTURE_IMAGE_FRAC));
    while (str[strPos] != GLOBAR_CHAR_TERMINATOR) {
        switch (str[strPos]) {
            case GLOBAL_CHAR_SPACE:
                curX += 4;
                break;
            default:
                gDPPipeSync(        gDisplayListHead++);
                gDPSetTextureImage( gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, fontLUT[str[strPos]]);
                gDPLoadSync(        gDisplayListHead++);
                gDPLoadBlock(       gDisplayListHead++, G_TX_LOADTILE, 0, 0, ((8 * 8) - 1), CALC_DXT(8, G_IM_SIZ_16b_BYTES));
                gSPTextureRectangle(gDisplayListHead++, (curX << 2), (curY << 2), ((curX + 8) << 2),
                                    ((curY + 8) << 2), G_TX_RENDERTILE, 0, 0, (1 << 10), (1 << 10));
                curX += 7;
                break;
        }
        strPos++;
    }
}

void handle_menu_scrolling(s8 scrollDirection, s8 *currentIndex, s8 minIndex, s8 maxIndex) {
    u8 index = 0;
    if (scrollDirection == MENU_SCROLL_VERTICAL) {
        if ((gPlayer3Controller->rawStickY >  60) || (gPlayer3Controller->buttonDown & U_CBUTTONS) || (gPlayer3Controller->buttonDown & U_JPAD)) index++;
        if ((gPlayer3Controller->rawStickY < -60) || (gPlayer3Controller->buttonDown & D_CBUTTONS) || (gPlayer3Controller->buttonDown & D_JPAD)) index += 2;
    } else if (scrollDirection == MENU_SCROLL_HORIZONTAL) {
        if ((gPlayer3Controller->rawStickX >  60) || (gPlayer3Controller->buttonDown & R_CBUTTONS) || (gPlayer3Controller->buttonDown & R_JPAD)) index += 2;
        if ((gPlayer3Controller->rawStickX < -60) || (gPlayer3Controller->buttonDown & L_CBUTTONS) || (gPlayer3Controller->buttonDown & L_JPAD)) index++;
    }
    if ((((index ^ gMenuHoldKeyIndex) & index) == 2) && (currentIndex[0] < maxIndex)) {
        play_sound(SOUND_MENU_CHANGE_SELECT, gGlobalSoundSource);
        currentIndex[0]++;
    }
    if ((((index ^ gMenuHoldKeyIndex) & index) == 1) && (currentIndex[0] > minIndex)) {
        play_sound(SOUND_MENU_CHANGE_SELECT, gGlobalSoundSource);
        currentIndex[0]--;
    }
    if (gMenuHoldKeyTimer == 10) {
        gMenuHoldKeyTimer = 8;
        gMenuHoldKeyIndex = 0;
    } else {
        gMenuHoldKeyTimer++;
        gMenuHoldKeyIndex = index;
    }
    if (!(index & 3)) gMenuHoldKeyTimer = 0;
}

// EU has both get_str_x_pos_from_center and get_str_x_pos_from_center_scale
// US and JP only implement one or the other
s16 get_str_x_pos_from_center(s16 centerPos, uchar *str, UNUSED f32 scale) {
    s16 strPos      = 0;
    f32 spacesWidth = 0.0f;
    while (str[strPos] != DIALOG_CHAR_TERMINATOR) {
        spacesWidth += gDialogCharWidths[str[strPos]];
        strPos++;
    }
    // return the x position of where the string starts as half the string's
    // length from the position of the provided center.
    return (s16)(centerPos - (s16)(spacesWidth / 2.0f));
}


s16 get_string_width(uchar *str) {
    s16 strPos = 0;
    s16 width  = 0;
    while (str[strPos] != DIALOG_CHAR_TERMINATOR) {
        width += gDialogCharWidths[str[strPos]];
        strPos++;
    }
    return width;
}

uchar gHudSymCoin[] = { GLYPH_COIN    , GLYPH_SPACE };
uchar gHudSymX[]    = { GLYPH_MULTIPLY, GLYPH_SPACE };

void print_hud_my_score_coins(s32 useCourseCoinScore, s8 fileNum, s8 courseNum, ScreenPos x, ScreenPos y) {
    uchar strNumCoins[4];
    s16 numCoins;
    if (!useCourseCoinScore) {
        numCoins = (u16)(save_file_get_max_coin_score(courseNum) & 0xFFFF);
    } else {
        numCoins = save_file_get_course_coin_score(fileNum, courseNum);
    }
    if (numCoins != 0) {
        print_hud_lut_string(HUD_LUT_GLOBAL,  x,       y, gHudSymCoin);
        print_hud_lut_string(HUD_LUT_GLOBAL, (x + 16), y, gHudSymX   );
        int_to_str(numCoins, strNumCoins);
        print_hud_lut_string(HUD_LUT_GLOBAL, (x + 32), y, strNumCoins);
    }
}

void print_hud_my_score_stars(s8 fileNum, s8 courseNum, ScreenPos x, ScreenPos y) {
    uchar strStarCount[4];
    s16 starCount;
    uchar textSymStar[] = { GLYPH_STAR    , GLYPH_SPACE };
    uchar textSymX[]    = { GLYPH_MULTIPLY, GLYPH_SPACE };
    starCount = save_file_get_course_star_count(fileNum, courseNum);
    if (starCount != 0) {
        print_hud_lut_string(HUD_LUT_GLOBAL,  x,       y, textSymStar );
        print_hud_lut_string(HUD_LUT_GLOBAL, (x + 16), y, textSymX    );
        int_to_str(starCount, strStarCount);
        print_hud_lut_string(HUD_LUT_GLOBAL, (x + 32), y, strStarCount);
    }
}

void int_to_str(s32 num, uchar *dst) {
    s32 digit1, digit2, digit3;
    s8  pos = 0;
    if (num > 999) {
        dst[0] = 0x00; dst[1] = DIALOG_CHAR_TERMINATOR;
        return;
    }
    digit1 =  (num / 100);
    digit2 = ((num - (digit1 * 100)) / 10);
    digit3 = ((num - (digit1 * 100)) - (digit2 * 10));
    if (digit1 != 0) dst[pos++] = digit1;
    if (digit2 != 0 || digit1 != 0) dst[pos++] = digit2;
    dst[pos++] = digit3;
    dst[pos  ] = DIALOG_CHAR_TERMINATOR;
}

DialogID get_dialog_id(void) {
    return gDialogID;
}

void create_dialog_box(s16 dialog) {
    if (gDialogID == DIALOG_NONE) {
        gDialogID      = dialog;
        gDialogBoxType = DIALOG_TYPE_ROTATE;
    }
}

void create_dialog_box_with_var(s16 dialog, s32 dialogVar) {
    if (gDialogID == DIALOG_NONE) {
        gDialogID       = dialog;
        gDialogVariable = dialogVar;
        gDialogBoxType  = DIALOG_TYPE_ROTATE;
    }
}

void create_dialog_inverted_box(s16 dialog) {
    if (gDialogID == DIALOG_NONE) {
        gDialogID      = dialog;
        gDialogBoxType = DIALOG_TYPE_ZOOM;
    }
}

void create_dialog_box_with_response(s16 dialog) {
    if (gDialogID == DIALOG_NONE) {
        gDialogID           = dialog;
        gDialogBoxType      = DIALOG_TYPE_ROTATE;
        gLastDialogResponse = 1;
    }
}

void reset_dialog_render_state(void) {
    level_set_transition(0, NULL);

    gDialogBoxScale       = 19.0f;
    gDialogBoxOpenTimer   = 90.0f;
    gDialogBoxState       = DIALOG_STATE_OPENING;
    gDialogID             = DIALOG_NONE;
    gDialogTextPos        = 0;
    gLastDialogResponse   = 0;
    gLastDialogPageStrPos = 0;
    gDialogResponse       = DIALOG_RESPONSE_NONE;
}

#define X_VAL1 -7.0f
#define Y_VAL1  5.0f
#define Y_VAL2  5.0f

void render_dialog_box_type(struct DialogEntry *dialog, s8 linesPerBox) {
    create_dl_translation_matrix(G_MTX_NOPUSH, dialog->leftOffset, dialog->width, 0);
    switch (gDialogBoxType) {
        case DIALOG_TYPE_ROTATE: // Renders a dialog black box with zoom and rotation
            if ((gDialogBoxState == DIALOG_STATE_OPENING) || (gDialogBoxState == DIALOG_STATE_CLOSING)) {
                create_dl_scale_matrix(G_MTX_NOPUSH, (1.0f / gDialogBoxScale), (1.0f / gDialogBoxScale), 1.0f);
                // convert the speed into angle
                create_dl_rotation_matrix(G_MTX_NOPUSH, (gDialogBoxOpenTimer * 4.0f), 0, 0, 1.0f);
            }
            gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 150);
            break;
        case DIALOG_TYPE_ZOOM: // Renders a dialog white box with zoom
            if ((gDialogBoxState == DIALOG_STATE_OPENING) || (gDialogBoxState == DIALOG_STATE_CLOSING)) {
                create_dl_translation_matrix(G_MTX_NOPUSH, (65.0f - (65.0f / gDialogBoxScale)), ((40.0f / gDialogBoxScale) - 40), 0);
                create_dl_scale_matrix(G_MTX_NOPUSH, (1.0f / gDialogBoxScale), (1.0f / gDialogBoxScale), 1.0f);
            }
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 150);
            break;
    }
    create_dl_translation_matrix(G_MTX_PUSH, X_VAL1, Y_VAL1, 0);
    create_dl_scale_matrix(      G_MTX_NOPUSH, 1.1f, (((f32) linesPerBox / Y_VAL2) + 0.1f), 1.0f);
    gSPDisplayList(gDisplayListHead++, dl_draw_text_bg_box);
    gSPPopMatrix(  gDisplayListHead++, G_MTX_MODELVIEW);
}

void change_and_flash_dialog_text_color_lines(s8 colorMode, s8 lineNum, u8 *customColor) {
    u8 colorFade;
    if (colorMode == 1) {
        if (lineNum == 1) {
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
        } else {
            if (lineNum == gDialogLineNum) {
                colorFade = ((gSineTable[gDialogColorFadeTimer >> 4] * 50.0f) + 200.0f);
                gDPSetEnvColor(gDisplayListHead++, colorFade, colorFade, colorFade, 255);
            } else {
                gDPSetEnvColor(gDisplayListHead++, 200, 200, 200, 255);
            }
        }
    } else {
        switch (gDialogBoxType) {
            case DIALOG_TYPE_ROTATE:
                if (*customColor == 2) {
                    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
                    *customColor = FALSE;
                }
                break;
            case DIALOG_TYPE_ZOOM:
                gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);
                break;
        }
    }
}

#define X_VAL3 0.0f
#define Y_VAL3 16

void handle_dialog_scroll_page_state(s8 lineNum, s8 totalLines, s8 *pageState, s8 *xMatrix, s16 *linePos) {
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
    if (lineNum == totalLines) {
        pageState[0] = DIALOG_PAGE_STATE_SCROLL;
        return;
    }
    create_dl_translation_matrix(G_MTX_PUSH, X_VAL3, (2 - (lineNum * Y_VAL3)), 0);
    linePos[0] = 0;
    xMatrix[0] = 1;
}


void render_star_count_dialog_text(s8 *xMatrix, s16 *linePos) {
    s8 tensDigit = (gDialogVariable / 10);
    s8 onesDigit = (gDialogVariable - (tensDigit * 10)); // remainder
    if (tensDigit != 0) {
        if (xMatrix[0] != 1) create_dl_translation_matrix(G_MTX_NOPUSH, (f32)(gDialogCharWidths[DIALOG_CHAR_SPACE] * xMatrix[0]), 0, 0);
        render_generic_char(tensDigit);
        create_dl_translation_matrix(G_MTX_NOPUSH, (f32) gDialogCharWidths[tensDigit], 0, 0);
        xMatrix[0] = 1;
        linePos[0]++;
    }
    if (xMatrix[0] != 1) create_dl_translation_matrix(G_MTX_NOPUSH, (f32)(gDialogCharWidths[DIALOG_CHAR_SPACE] * (xMatrix[0] - 1)), 0, 0);
    render_generic_char(onesDigit);
    create_dl_translation_matrix(G_MTX_NOPUSH, (f32) gDialogCharWidths[onesDigit], 0, 0);
    linePos[0]++;
    xMatrix[0] = 1;
}

void render_multi_text_string_lines(s8 multiTextId, s8 lineNum, s16 *linePos, s8 linesPerBox, s8 xMatrix, s8 lowerBound) {
    s8 i;
    struct MultiTextEntry textLengths[2] = {
        { 3, { TEXT_THE_RAW } },
        { 3, { TEXT_YOU_RAW } },
    };
    if (lineNum >= lowerBound && lineNum <= (lowerBound + linesPerBox)) {
        if ((linePos[0] != 0) || (xMatrix != 1)) create_dl_translation_matrix(G_MTX_NOPUSH, (gDialogCharWidths[DIALOG_CHAR_SPACE] * (xMatrix - 1)), 0, 0);
        for (i = 0; i < textLengths[multiTextId].length; i++) {
            render_generic_char(textLengths[multiTextId].str[i]);
            create_dl_translation_matrix(G_MTX_NOPUSH, (gDialogCharWidths[textLengths[multiTextId].str[i]]), 0, 0);
        }
    }
    linePos += textLengths[multiTextId].length;
}


u32 ensure_nonnegative(s16 value) {
    if (value < 0) value = 0;
    return value;
}

void handle_dialog_text_and_pages(s8 colorMode, struct DialogEntry *dialog, s8 lowerBound) {
    uchar strChar;
    s16 colorLoop;
    ColorRGBA rgbaColors = {0, 0, 0, 0};
    u8 customColor   = FALSE;
    u8 diffTmp       = 0;
    uchar *str          = segmented_to_virtual(dialog->str);
    s8 lineNum       = 1;
    s8 totalLines;
    s8 pageState     = DIALOG_PAGE_STATE_NONE;
    UNUSED s8 mark   = DIALOG_MARK_NONE; // unused in US, EU
    s8 xMatrix       = 1;
    s8 linesPerBox   = dialog->linesPerBox;
    s16 strIdx;
    s16 linePos      = 0;
    if (gDialogBoxState == DIALOG_STATE_HORIZONTAL) {
        // If scrolling, consider the number of lines for both
        // the current page and the page being scrolled to.
        totalLines = ((linesPerBox * 2) + 1);
    } else {
        totalLines = ( linesPerBox      + 1);
    }
    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
    strIdx = gDialogTextPos;
    if (gDialogBoxState == DIALOG_STATE_HORIZONTAL) create_dl_translation_matrix(G_MTX_NOPUSH, 0, (f32) gDialogScrollOffsetY, 0);
    create_dl_translation_matrix(G_MTX_PUSH, X_VAL3, (2 - (lineNum * Y_VAL3)), 0);
    while (pageState == DIALOG_PAGE_STATE_NONE) {
        if (customColor) {
            gDPSetEnvColor(gDisplayListHead++, rgbaColors[0], rgbaColors[1], rgbaColors[2], rgbaColors[3]);
        } else {
            change_and_flash_dialog_text_color_lines(colorMode, lineNum, &customColor);
        }
        strChar = str[strIdx];
        switch (strChar) {
            case DIALOG_CHAR_TERMINATOR:
                pageState = DIALOG_PAGE_STATE_END;
                gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
                break;
            case DIALOG_CHAR_COLOR:
                customColor = TRUE;
                strIdx++;
                for ((colorLoop = (strIdx + 8)); (strIdx < colorLoop); (++strIdx)) {
                    diffTmp = 0;
                    if ((str[strIdx] >= 0x24) && (str[strIdx] <= 0x29)) {
                        diffTmp = 0x1A;
                    } else if (str[strIdx] >= 0x10) {
                        customColor = 2;
                        strIdx = (colorLoop - 8);
                        for ((diffTmp = 0); (diffTmp < 8); (++diffTmp)) {
                            if (str[strIdx + diffTmp] != 0x9F) break;
                        }
                        if (diffTmp == 8) strIdx += diffTmp;
                        break;
                    }
                    if (!((8 - (colorLoop - strIdx)) & 0x1)) {
                        rgbaColors[(8 - (colorLoop - strIdx)) / 2]  = (((str[strIdx] - diffTmp) & 0x0F) << 4);
                    } else {
                        rgbaColors[(8 - (colorLoop - strIdx)) / 2] +=  ((str[strIdx] - diffTmp) & 0x0F);
                    }
                }
                strIdx--;
                break;
            case DIALOG_CHAR_NEWLINE:
                lineNum++;
                handle_dialog_scroll_page_state(lineNum, totalLines, &pageState, &xMatrix, &linePos);
                break;
            case DIALOG_CHAR_DAKUTEN:
                mark = DIALOG_MARK_DAKUTEN;
                break;
            case DIALOG_CHAR_PERIOD_OR_HANDAKUTEN:
                mark = DIALOG_MARK_HANDAKUTEN;
                break;
            case DIALOG_CHAR_SPACE:
                xMatrix++;
                linePos++;
                break;
            case DIALOG_CHAR_SLASH:
                xMatrix += 2;
                linePos += 2;
                break;
            case DIALOG_CHAR_MULTI_THE:
                render_multi_text_string_lines(STRING_THE, lineNum, &linePos, linesPerBox, xMatrix, lowerBound);
                xMatrix = 1;
                break;
            case DIALOG_CHAR_MULTI_YOU:
                render_multi_text_string_lines(STRING_YOU, lineNum, &linePos, linesPerBox, xMatrix, lowerBound);
                xMatrix = 1;
                break;
            case DIALOG_CHAR_STAR_COUNT:
                render_star_count_dialog_text(&xMatrix, &linePos);
                break;
            default: // any other character
                if ((lineNum >= lowerBound) && (lineNum <= (lowerBound + linesPerBox))) {
                    if (linePos || (xMatrix != 1)) create_dl_translation_matrix(G_MTX_NOPUSH, (f32)(gDialogCharWidths[DIALOG_CHAR_SPACE] * (xMatrix - 1)), 0, 0);
                    render_generic_char(strChar);
                    create_dl_translation_matrix(G_MTX_NOPUSH, (f32)(gDialogCharWidths[strChar]), 0, 0);
                    xMatrix = 1;
                    linePos++;
                }
        }
        strIdx++;
    }
    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
    if (gDialogBoxState == DIALOG_STATE_VERTICAL) gLastDialogPageStrPos = ((pageState == DIALOG_PAGE_STATE_END) ? -1 : strIdx);
    gLastDialogLineNum = lineNum;
}

#define X_VAL4_1 56
#define X_VAL4_2 47
#define Y_VAL4_1 2
#define Y_VAL4_2 16

void render_dialog_triangle_choice(void) {
    if (gDialogBoxState == DIALOG_STATE_VERTICAL) handle_menu_scrolling(MENU_SCROLL_HORIZONTAL, &gDialogLineNum, 1, 2);
    create_dl_translation_matrix(G_MTX_NOPUSH, ((gDialogLineNum * X_VAL4_1) - X_VAL4_2), (Y_VAL4_1 - (gLastDialogLineNum * Y_VAL4_2)), 0);
    if (gDialogBoxType == DIALOG_TYPE_ROTATE) {
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
    } else {
        gDPSetEnvColor(gDisplayListHead++,    0,  0,   0, 255);
    }
    gSPDisplayList(gDisplayListHead++, dl_draw_triangle);
}

#define X_VAL5   118.0f
#define Y_VAL5_1 -16
#define Y_VAL5_2  5
#define X_Y_VAL6 0.8f

void render_dialog_string_color(s8 linesPerBox) {
    if (gGlobalTimer & 0x08) return;
    create_dl_translation_matrix(G_MTX_PUSH, X_VAL5, ((linesPerBox * Y_VAL5_1) + Y_VAL5_2), 0);
    create_dl_scale_matrix(      G_MTX_NOPUSH, X_Y_VAL6, X_Y_VAL6, 1.0f);
    create_dl_rotation_matrix(   G_MTX_NOPUSH, -DEFAULT_DIALOG_BOX_ANGLE, 0, 0, 1.0f);
    if (gDialogBoxType == DIALOG_TYPE_ROTATE) { // White Text
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
    } else { // Black Text
        gDPSetEnvColor(gDisplayListHead++,   0,   0,   0, 255);
    }
    gSPDisplayList(gDisplayListHead++, dl_draw_triangle);
    gSPPopMatrix(  gDisplayListHead++, G_MTX_MODELVIEW);
}

void handle_special_dialog_text(DialogID dialogID) { // dialog ID tables, in order
    // King Bob-omb (Start), Whomp (Start), King Bob-omb (throw him out), Eyerock (Start), Wiggler (Start)
    DialogID dialogBossStart[] = { DIALOG_017, DIALOG_114, DIALOG_128, DIALOG_117, DIALOG_150 };
    // Koopa the Quick (BOB), Koopa the Quick (THI), Penguin Race, Fat Penguin Race (120 stars)
    DialogID dialogRaceSound[] = { DIALOG_005, DIALOG_009, DIALOG_055, DIALOG_164             };
    // Red Switch, Green Switch, Blue Switch, 100 coins star, Bowser Red Coin Star
    DialogID dialogStarSound[] = { DIALOG_010, DIALOG_011, DIALOG_012, DIALOG_013, DIALOG_014 };
    // King Bob-omb (Start), Whomp (Defeated), King Bob-omb (Defeated, missing in JP), Eyerock (Defeated), Wiggler (Defeated)
#if BUGFIX_KING_BOB_OMB_FADE_MUSIC
    DialogID dialogBossStop[]  = { DIALOG_017, DIALOG_115, DIALOG_116, DIALOG_118, DIALOG_152 };
#else
    //! @bug JP misses King Bob-omb defeated DIALOG_116, meaning that the boss music will still
    //! play after King Bob-omb is defeated until BOB loads it's music after the star cutscene
    DialogID dialogBossStop[] = { DIALOG_017, DIALOG_115, DIALOG_118, DIALOG_152 };
#endif
    DialogID i;
    for ((i = 0); (i < ARRAY_COUNT(dialogBossStart)); (i++)) {
        if (dialogBossStart[i] == dialogID) {
            seq_player_unlower_volume(SEQ_PLAYER_LEVEL, 60);
            play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_EVENT_BOSS), 0);
            return;
        }
    }
    for ((i = 0); (i < ARRAY_COUNT(dialogRaceSound)); (i++)) {
        if ((dialogRaceSound[i] == dialogID) && (gDialogLineNum == 1)) {
            play_race_fanfare();
            return;
        }
    }
    for ((i = 0); (i < ARRAY_COUNT(dialogStarSound)); (i++)) {
        if ((dialogStarSound[i] == dialogID) && (gDialogLineNum == 1)) {
            play_sound(SOUND_MENU_STAR_SOUND, gGlobalSoundSource);
            return;
        }
    }
    for ((i = 0); (i < ARRAY_COUNT(dialogBossStop)); (i++)) {
        if (dialogBossStop[i] == dialogID) {
            seq_player_fade_out(SEQ_PLAYER_LEVEL, 1);
            return;
        }
    }
}

s16 gMenuMode = MENU_MODE_NONE;

uchar gEndCutsceneStrEn0[] = { TEXT_FILE_MARIO_EXCLAMATION };
uchar gEndCutsceneStrEn1[] = { TEXT_POWER_STARS_RESTORED   };
uchar gEndCutsceneStrEn2[] = { TEXT_THANKS_TO_YOU          };
uchar gEndCutsceneStrEn3[] = { TEXT_THANK_YOU_MARIO        };
uchar gEndCutsceneStrEn4[] = { TEXT_SOMETHING_SPECIAL      };
uchar gEndCutsceneStrEn5[] = { TEXT_LISTEN_EVERYBODY       };
uchar gEndCutsceneStrEn6[] = { TEXT_LETS_HAVE_CAKE         };
uchar gEndCutsceneStrEn7[] = { TEXT_FOR_MARIO              };
uchar gEndCutsceneStrEn8[] = { TEXT_FILE_MARIO_QUESTION    };

uchar *gEndCutsceneStringsEn[] = {
    gEndCutsceneStrEn0,
    gEndCutsceneStrEn1,
    gEndCutsceneStrEn2,
    gEndCutsceneStrEn3,
    gEndCutsceneStrEn4,
    gEndCutsceneStrEn5,
    gEndCutsceneStrEn6,
    gEndCutsceneStrEn7,
    // This [8] string is actually unused. In the cutscene handler, the developers do not
    // set the 8th one, but use the first string again at the very end, so Peach ends up
    // saying "Mario!" twice. It is likely that she was originally meant to say "Mario?" at
    // the end but the developers changed their mind, possibly because the line recorded
    // sounded more like an exclamation than a question.
    gEndCutsceneStrEn8,
    NULL
};


u16 gCutsceneMsgFade        =  0;
s16 gCutsceneMsgIndex       = -1;
s16 gCutsceneMsgDuration    = -1;
s16 gCutsceneMsgTimer       =  0;
s8  gDialogCameraAngleIndex = CAM_SELECTION_MARIO;
s8  gDialogCourseActNum     =  1;

#define DIAG_VAL1 16
#define DIAG_VAL3 132 // US & EU
#define DIAG_VAL4 5
#define DIAG_VAL2 240 // JP & US

void render_dialog_entries(void) {
    void **dialogTable;
    struct DialogEntry *dialog;
    s8 lowerBound = 0;
    dialogTable   = segmented_to_virtual(languageTable[gInGameLanguage][0]);
    dialog        = segmented_to_virtual(dialogTable[gDialogID]);
    // if the dialog entry is invalid, set the ID to -1.
    if (segmented_to_virtual(NULL) == dialog) {
        gDialogID = DIALOG_NONE;
        return;
    }
    switch (gDialogBoxState) {
        case DIALOG_STATE_OPENING:
            if (gDialogBoxOpenTimer == DEFAULT_DIALOG_BOX_ANGLE) {
                play_dialog_sound(gDialogID);
                play_sound(SOUND_MENU_MESSAGE_APPEAR, gGlobalSoundSource);
            }
            if (gDialogBoxType == DIALOG_TYPE_ROTATE) {
                gDialogBoxOpenTimer -= 7.5f;
                gDialogBoxScale     -= 1.5f;
            } else {
                gDialogBoxOpenTimer -= 10.0f;
                gDialogBoxScale     -=  2.0f;
            }
            if (gDialogBoxOpenTimer == 0.0f) {
                gDialogBoxState = DIALOG_STATE_VERTICAL;
                gDialogLineNum  = 1;
            }
            lowerBound = 1;
            break;
        case DIALOG_STATE_VERTICAL:
            gDialogBoxOpenTimer = 0.0f;
            if (gPlayer3Controller->buttonPressed & (A_BUTTON | B_BUTTON)) {
                if (gLastDialogPageStrPos == -1) {
                    handle_special_dialog_text(gDialogID);
                    gDialogBoxState = DIALOG_STATE_CLOSING;
                } else {
                    gDialogBoxState = DIALOG_STATE_HORIZONTAL;
                    play_sound(SOUND_MENU_MESSAGE_NEXT_PAGE, gGlobalSoundSource);
                }
            }
            lowerBound = 1;
            break;
        case DIALOG_STATE_HORIZONTAL:
            gDialogScrollOffsetY += (dialog->linesPerBox * 2);

            if (gDialogScrollOffsetY >= (dialog->linesPerBox * DIAG_VAL1)) {
                gDialogTextPos       = gLastDialogPageStrPos;
                gDialogBoxState      = DIALOG_STATE_VERTICAL;
                gDialogScrollOffsetY = 0;
            }
            lowerBound = ((gDialogScrollOffsetY / DIAG_VAL1) + 1);
            break;
        case DIALOG_STATE_CLOSING:
            if (gDialogBoxOpenTimer == 20.0f) {
                level_set_transition(0, NULL);
                play_sound(SOUND_MENU_MESSAGE_DISAPPEAR, gGlobalSoundSource);
                gDialogResponse = gDialogLineNum;
            }
            gDialogBoxOpenTimer = (gDialogBoxOpenTimer + 10.0f);
            gDialogBoxScale     = (gDialogBoxScale     +  2.0f);
            if (gDialogBoxOpenTimer == DEFAULT_DIALOG_BOX_ANGLE) {
                gDialogBoxState       = DIALOG_STATE_OPENING;
                gDialogID             = DIALOG_NONE;
                gDialogTextPos        = 0;
                gLastDialogResponse   = 0;
                gLastDialogPageStrPos = 0;
                gDialogResponse       = DIALOG_RESPONSE_NONE;
            }
            lowerBound = 1;
            break;
    }
    render_dialog_box_type(dialog, dialog->linesPerBox);

    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE,
                  // Horizontal scissoring isn't really required and can potentially mess up widescreen enhancements.
#ifdef WIDESCREEN
                  0,
#else
                  ensure_nonnegative(dialog->leftOffset),
#endif
                  ensure_nonnegative(DIAG_VAL2 - dialog->width),
#ifdef WIDESCREEN
                  SCREEN_WIDTH,
#else
                  ensure_nonnegative(DIAG_VAL3 + dialog->leftOffset),
#endif
                  ensure_nonnegative(240 + ((dialog->linesPerBox * 80) / DIAG_VAL4) - dialog->width));
    handle_dialog_text_and_pages(0, dialog, lowerBound);
    if ((gLastDialogPageStrPos == -1) && (gLastDialogResponse == 1)) render_dialog_triangle_choice();
    gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 2, 2, (SCREEN_WIDTH - (gBorderHeight/2)), (SCREEN_HEIGHT - (gBorderHeight/2)));
    if ((gLastDialogPageStrPos != -1) && (gDialogBoxState == DIALOG_STATE_VERTICAL)) render_dialog_string_color(dialog->linesPerBox);
}

// Calls a gMenuMode value defined by render_menus_and_dialogs cases
void set_menu_mode(s16 mode) {
    if (gMenuMode == MENU_MODE_NONE) gMenuMode = mode;
}

void reset_cutscene_msg_fade(void) {
    gCutsceneMsgFade = 0;
}

void dl_rgba16_begin_cutscene_msg_fade(void) {
    gSPDisplayList(gDisplayListHead++, dl_rgba16_text_begin);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gCutsceneMsgFade);
}

void dl_rgba16_stop_cutscene_msg_fade(void) {
    gSPDisplayList(gDisplayListHead++, dl_rgba16_text_end);
    if (gCutsceneMsgFade < 250) {
        gCutsceneMsgFade += 25;
    } else {
        gCutsceneMsgFade = 255;
    }
}

uchar ascii_to_credits_char(uchar c) {
    if ((c >= 'A') && (c <= 'Z')) return (c - ('A' - 0xA));
    if ((c >= 'a') && (c <= 'z')) return (c - ('a' - 0xA)); // remap lower to upper case
    if ( c == ' ') return GLOBAL_CHAR_SPACE;
    if ( c == '.') return 0x24;
    if ( c == '3') return ASCII_TO_DIALOG('3');
    if ( c == '4') return ASCII_TO_DIALOG('4');
    if ( c == '6') return ASCII_TO_DIALOG('6');
    return GLOBAL_CHAR_SPACE;
}

void print_credits_str_ascii(ScreenPos x, ScreenPos y, const char *str) {
    s32 pos = 0;
    uchar  c   = str[pos];
    uchar  creditStr[100];
    while (c != 0) {
        creditStr[pos++] = ascii_to_credits_char(c);
        c                = str[pos];
    }
    creditStr[pos] = GLOBAR_CHAR_TERMINATOR;
    print_credits_string(x, y, creditStr);
}

void set_cutscene_message(ScreenPos xOffset, ScreenPos yOffset, s16 msgIndex, s16 msgDuration) {
    // is message done printing?
    if (gCutsceneMsgIndex == -1) {
        gCutsceneMsgIndex    = msgIndex;
        gCutsceneMsgDuration = msgDuration;
        gCutsceneMsgTimer    = 0;
        gCutsceneMsgXOffset  = xOffset;
        gCutsceneMsgYOffset  = yOffset;
        gCutsceneMsgFade     = 0;
    }
}

void do_cutscene_handler(void) {
    ScreenPos x;
    // is a cutscene playing? do not perform this handler's actions if so.
    if (gCutsceneMsgIndex == -1) return;
    create_dl_ortho_matrix();
    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gCutsceneMsgFade);
    // get the x coordinate of where the cutscene string starts.
    x = get_str_x_pos_from_center(gCutsceneMsgXOffset  , gEndCutsceneStringsEn[gCutsceneMsgIndex], 10.0f);
    print_generic_string(x, (240 - gCutsceneMsgYOffset), gEndCutsceneStringsEn[gCutsceneMsgIndex]       );
    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
    // if the timing variable is less than 5, increment
    // the fade until we are at full opacity.
    if (gCutsceneMsgTimer < 5) gCutsceneMsgFade += 50;
    // if the cutscene frame length + the fade-in counter is
    // less than the timer, it means we have exceeded the
    // time that the message is supposed to remain on
    // screen. if (message_duration = 50) and (msg_timer = 55)
    // then after the first 5 frames, the message will remain
    // on screen for another 50 frames until it starts fading.
    if ((gCutsceneMsgDuration +  5) < gCutsceneMsgTimer) gCutsceneMsgFade -= 50;
    // like the first check, it takes 5 frames to fade out, so
    // perform a + 10 to account for the earlier check (10-5=5).
    if ((gCutsceneMsgDuration + 10) < gCutsceneMsgTimer) {
        gCutsceneMsgIndex = -1;
        gCutsceneMsgFade  =  0;
        gCutsceneMsgTimer =  0;
        return;
    }
    gCutsceneMsgTimer++;
}

#define PEACH_MESSAGE_TIMER 250

#define STR_X  38
#define STR_Y 142

// "Dear Mario" message handler
void print_peach_letter_message(void) {
    void **dialogTable;
    struct DialogEntry *dialog;
    uchar *str;
    dialogTable = segmented_to_virtual(languageTable[gInGameLanguage][0]);
    dialog      = segmented_to_virtual(dialogTable[gDialogID]);
    str         = segmented_to_virtual(dialog->str);
    create_dl_translation_matrix(MENU_MTX_PUSH, 97.0f, 118.0f, 0);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gCutsceneMsgFade);
    gSPDisplayList(gDisplayListHead++, castle_grounds_seg7_dl_peach_letter);
    gSPPopMatrix(  gDisplayListHead++, G_MTX_MODELVIEW);
    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
    gDPSetEnvColor(gDisplayListHead++, 20, 20, 20, gCutsceneMsgFade);
    print_generic_string(STR_X, STR_Y, str);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
    gDPSetEnvColor(gDisplayListHead++, 200, 80, 120, gCutsceneMsgFade);
    gSPDisplayList(gDisplayListHead++, castle_grounds_seg7_us_dl_peach_signature);
    // at the start/end of message, reset the fade.
    if (gCutsceneMsgTimer == 0) gCutsceneMsgFade = 0;
    // we're less than 20 increments, so increase the fade.
    if (gCutsceneMsgTimer < 20) gCutsceneMsgFade += 10;
    // we're after PEACH_MESSAGE_TIMER increments, so decrease the fade.
    if (gCutsceneMsgTimer > PEACH_MESSAGE_TIMER) gCutsceneMsgFade -= 10;
    // 20 increments after the start of the decrease, we're
    // back where we are, so reset everything at the end.
    if (gCutsceneMsgTimer > (PEACH_MESSAGE_TIMER + 20)) {
        gCutsceneMsgIndex = -1;
        gCutsceneMsgFade  =  0; //! uselessly reset since the next execution will just set it to 0 again.
        gDialogID         = DIALOG_NONE;
        gCutsceneMsgTimer =  0;
        return; // return to avoid incrementing the timer
    }
    gCutsceneMsgTimer++;
}

/**
 * Renders the cannon reticle when Mario is inside a cannon.
 * Formed by four triangles.
 */
void render_hud_cannon_reticle(void) {
    create_dl_translation_matrix(G_MTX_PUSH, 160.0f, 120.0f, 0.0f);
    gDPSetEnvColor(gDisplayListHead++, 50, 50, 50, 180);
    create_dl_translation_matrix(G_MTX_PUSH, -20.0f, -8.0f, 0.0f);
    gSPDisplayList(gDisplayListHead++, dl_draw_triangle);
    gSPPopMatrix(  gDisplayListHead++, G_MTX_MODELVIEW);
    create_dl_translation_matrix(G_MTX_PUSH, 20.0f, 8.0f, 0.0f);
    create_dl_rotation_matrix(G_MTX_NOPUSH, 180.0f, 0.0f, 0.0f, 1.0f);
    gSPDisplayList(gDisplayListHead++, dl_draw_triangle);
    gSPPopMatrix(  gDisplayListHead++, G_MTX_MODELVIEW);
    create_dl_translation_matrix(G_MTX_PUSH, 8.0f, -20.0f, 0.0f);
    create_dl_rotation_matrix(G_MTX_NOPUSH, DEFAULT_DIALOG_BOX_ANGLE, 0.0f, 0.0f, 1.0f);
    gSPDisplayList(gDisplayListHead++, dl_draw_triangle);
    gSPPopMatrix(  gDisplayListHead++, G_MTX_MODELVIEW);
    create_dl_translation_matrix(G_MTX_PUSH, -8.0f, 20.0f, 0.0f);
    create_dl_rotation_matrix(G_MTX_NOPUSH, -DEFAULT_DIALOG_BOX_ANGLE, 0.0f, 0.0f, 1.0f);
    gSPDisplayList(gDisplayListHead++, dl_draw_triangle);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
}

void reset_red_coins_collected(void) {
    gRedCoinsCollected = 0;
#ifdef HUD_SECRETS
    gSecretsCollected  = 0;
#endif
}

#ifdef REONU_CAM_3
void render_camera_speed_setting(ScreenPos x, ScreenPos y) {
    uchar textCamInfoSpeeds[][17] = { { TEXT_CAM_INFO_SPEED_0 },
                                      { TEXT_CAM_INFO_SPEED_1 },
                                      { TEXT_CAM_INFO_SPEED_2 },
                                      { TEXT_CAM_INFO_SPEED_3 },
                                      { TEXT_CAM_INFO_SPEED_4 } };
    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);
    print_generic_string(x, y, textCamInfoSpeeds[gCameraSpeed]);
    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
    if ((gPlayer1Controller->rawStickX > 60) || (gPlayer1Controller->buttonPressed & (R_JPAD | R_CBUTTONS))) {
        if (gCameraSpeed < 4) {
            gCameraSpeed++;
        } else {
            gCameraSpeed = 0;
        }
        save_file_set_camera_speed(gCameraSpeed);
    } else if ((gPlayer1Controller->rawStickX < -60) || (gPlayer1Controller->buttonPressed & (L_JPAD | L_CBUTTONS))) {
        if (gCameraSpeed > 0) {
            gCameraSpeed--;
        } else {
            gCameraSpeed = 4;
        }
        save_file_set_camera_speed(gCameraSpeed);
    }
}
#endif

void change_dialog_camera_angle(void) {
    gDialogCameraAngleIndex = (cam_select_alt_mode(0) == CAM_SELECTION_MARIO) ? CAM_SELECTION_MARIO : CAM_SELECTION_FIXED;
}

void shade_screen(void) {
    create_dl_translation_matrix(G_MTX_PUSH, GFX_DIMENSIONS_FROM_LEFT_EDGE(0), SCREEN_HEIGHT, 0);
    // This is a bit weird. It reuses the dialog text box (width 130, height -80),
    // so scale to at least fit the screen.
#ifdef WIDESCREEN
    create_dl_scale_matrix(G_MTX_NOPUSH, (GFX_DIMENSIONS_ASPECT_RATIO * SCREEN_HEIGHT / 130.0f), 3.0f, 1.0f);
#else
    create_dl_scale_matrix(G_MTX_NOPUSH, 2.6f, 3.4f, 1.0f);
#endif
    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 110);
    gSPDisplayList(gDisplayListHead++, dl_draw_text_bg_box);
    gSPPopMatrix(  gDisplayListHead++, G_MTX_MODELVIEW);
}

#ifdef PAUSE_BOWSER_KEYS
void print_bowser_key(s32 x, s32 y, Angle rotation) { // bowser key
    create_dl_translation_matrix(G_MTX_PUSH,             (x +  4), (y + 18),     0.0f);
    create_dl_rotation_matrix(   G_MTX_NOPUSH,      -90,     0.0f,     0.0f,     1.0f);
    create_dl_rotation_matrix(   G_MTX_NOPUSH, rotation,     1.0f,     0.0f,     0.0f);
    create_dl_scale_matrix(      G_MTX_NOPUSH,            0.0625f,  0.0625f,  0.0625f);
    gSPSetGeometryMode(  gDisplayListHead++, G_ZBUFFER);
    gSPDisplayList(      gDisplayListHead++, bowser_key_dl);
    gSPPopMatrix(        gDisplayListHead++, G_MTX_MODELVIEW);
    gSPClearGeometryMode(gDisplayListHead++, G_ZBUFFER);
}

void render_pause_bowser_keys(void) {
    const s32 speed = 12;
    Angle rotation;
    if (gHudDisplay.keys > 0) {
        rotation = ((gGlobalTimer % (360 / speed)) * -speed);
        print_bowser_key(GFX_DIMENSIONS_FROM_RIGHT_EDGE(30), 16, rotation);
    }
}
#endif

void print_animated_red_coin(ScreenPos x, ScreenPos y) {
    s32 timer = gGlobalTimer;
    create_dl_translation_matrix(G_MTX_PUSH, x, y, 0);
    create_dl_scale_matrix(G_MTX_NOPUSH, 0.25f, 0.25f, 1.0f);
    gDPSetRenderMode(gDisplayListHead++, G_RM_TEX_EDGE, G_RM_TEX_EDGE2);
#ifdef IA8_30FPS_COINS
    switch (timer & 7) {
        case 0: gSPDisplayList(gDisplayListHead++, coin_seg3_dl_red_0     ); break;
        case 1: gSPDisplayList(gDisplayListHead++, coin_seg3_dl_red_22_5  ); break;
        case 2: gSPDisplayList(gDisplayListHead++, coin_seg3_dl_red_45    ); break;
        case 3: gSPDisplayList(gDisplayListHead++, coin_seg3_dl_red_67_5  ); break;
        case 4: gSPDisplayList(gDisplayListHead++, coin_seg3_dl_red_90    ); break;
        case 5: gSPDisplayList(gDisplayListHead++, coin_seg3_dl_red_67_5_r); break;
        case 6: gSPDisplayList(gDisplayListHead++, coin_seg3_dl_red_45_r  ); break;
        case 7: gSPDisplayList(gDisplayListHead++, coin_seg3_dl_red_22_5_r); break;
    }
#else
    switch (timer & 6) {
        case 0: gSPDisplayList(gDisplayListHead++, coin_seg3_dl_red_front_0     ); break;
        case 2: gSPDisplayList(gDisplayListHead++, coin_seg3_dl_red_tilt_right_0); break;
        case 4: gSPDisplayList(gDisplayListHead++, coin_seg3_dl_red_side_0      ); break;
        case 6: gSPDisplayList(gDisplayListHead++, coin_seg3_dl_red_tilt_left_0 ); break;
    }
#endif
    gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
    gSPPopMatrix(    gDisplayListHead++, G_MTX_MODELVIEW);
}

void render_pause_red_coins(void) {
    s8 x;
    for (x = 0; x < gRedCoinsCollected; x++) print_animated_red_coin((GFX_DIMENSIONS_FROM_RIGHT_EDGE(30) - (x * 20)), 16);
}

/// By default, not needed as puppycamera has an option, but should you wish to revert that, you are legally allowed.

#if defined(WIDE) && !defined(PUPPYCAM)
void render_widescreen_setting(void) {
    uchar textCurrRatio43[]  = { TEXT_HUD_CURRENT_RATIO_43  };
    uchar textCurrRatio169[] = { TEXT_HUD_CURRENT_RATIO_169 };
    uchar textPressL[]       = { TEXT_HUD_PRESS_L           };
    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);
    print_generic_string(10, 20, (gWidescreen ? textCurrRatio169 : textCurrRatio43));
    print_generic_string(10,  7, textPressL);
    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
    if (gPlayer1Controller->buttonPressed & L_TRIG){
        gWidescreen ^= TRUE;
        save_file_set_widescreen_mode(gWidescreen);
    }
}
#endif

#define CRS_NUM_X1 100
#define TXT_STAR_X  98
#define ACT_NAME_X 116
#define LVL_NAME_X 117
#define MYSCORE_X   62

void render_pause_my_score_coins(void) {
    uchar textCourse[]       = { TEXT_COURSE        };
    uchar textMyScore[]      = { TEXT_MY_SCORE      };
    uchar textStar[]         = { TEXT_STAR          };
    uchar textUnfilledStar[] = { TEXT_UNFILLED_STAR };
    uchar strCourseNum[4];
    void **courseNameTbl;
    uchar *courseName;
    void **actNameTbl;
    uchar *actName;
    u8 courseIndex;
    u8 starFlags;
    courseNameTbl = segmented_to_virtual(languageTable[gInGameLanguage][1]);
    actNameTbl    = segmented_to_virtual(languageTable[gInGameLanguage][2]);
    courseIndex   = (gCurrCourseNum - 1);
    starFlags     = save_file_get_star_flags((gCurrSaveFileNum - 1), (gCurrCourseNum - 1));
    gSPDisplayList(gDisplayListHead++, dl_rgba16_text_begin);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);
    if (courseIndex < COURSE_STAGES_COUNT) {
        print_hud_my_score_coins(TRUE, (gCurrSaveFileNum - 1), courseIndex, 178, 103);
        print_hud_my_score_stars(      (gCurrSaveFileNum - 1), courseIndex, 118, 103);
    }
    gSPDisplayList(gDisplayListHead++, dl_rgba16_text_end);
    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);
    if ((courseIndex < COURSE_STAGES_COUNT) && (save_file_get_course_star_count((gCurrSaveFileNum - 1), courseIndex) != 0)) print_generic_string(MYSCORE_X, 121, textMyScore);
    courseName = segmented_to_virtual(courseNameTbl[courseIndex]);
    if (courseIndex < COURSE_STAGES_COUNT) {
        print_generic_string(63, 157, textCourse);
        int_to_str(gCurrCourseNum, strCourseNum);
        print_generic_string(CRS_NUM_X1, 157, strCourseNum);
        actName = segmented_to_virtual(actNameTbl[((gCurrCourseNum - 1) * 6) + gDialogCourseActNum - 1]);
        print_generic_string(TXT_STAR_X, 140, ((starFlags & (1 << (gDialogCourseActNum - 1))) ? textStar : textUnfilledStar));
        print_generic_string(ACT_NAME_X, 140, actName);
        print_generic_string(LVL_NAME_X, 157, &courseName[3]);
    } else {
        print_generic_string(94, 157, &courseName[3]);
    }
    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
}

#define TXT1_X 3
#define TXT2_X 119
#define Y_VAL7 2

void render_pause_camera_options(ScreenPos x, ScreenPos y, s8 *index, s16 xIndex) {
    uchar textLakituMario[]   = { TEXT_LAKITU_MARIO   };
    uchar textLakituStop[]    = { TEXT_LAKITU_STOP    };
    uchar textNormalUpClose[] = { TEXT_NORMAL_UPCLOSE };
    uchar textNormalFixed[]   = { TEXT_NORMAL_FIXED   };
    handle_menu_scrolling(MENU_SCROLL_HORIZONTAL, index, 1, 2);
    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);
    print_generic_string((x + 14    ), (y +  2), textLakituMario);
    print_generic_string((x + TXT1_X), (y - 13), textNormalUpClose);
    print_generic_string((x + 124   ), (y +  2), textLakituStop);
    print_generic_string((x + TXT2_X), (y - 13), textNormalFixed);
    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
    create_dl_translation_matrix(G_MTX_PUSH, (((*index - 1) * xIndex) + x), (y + Y_VAL7), 0);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);
    gSPDisplayList(gDisplayListHead++, dl_draw_triangle);
    gSPPopMatrix(  gDisplayListHead++, G_MTX_MODELVIEW);
    switch (*index) {
        case CAM_SELECTION_MARIO: cam_select_alt_mode(CAM_SELECTION_MARIO); break;
        case CAM_SELECTION_FIXED: cam_select_alt_mode(CAM_SELECTION_FIXED); break;
    }
}

#define X_VAL8 4
#define Y_VAL8 2

void render_pause_course_options(ScreenPos x, ScreenPos y, s8 *index, s16 yIndex) {
    uchar textContinue[]     = { TEXT_CONTINUE       };
    uchar textExitCourse[]   = { TEXT_EXIT_COURSE    };
#ifndef PUPPYCAM
    uchar textCameraAngleR[] = { TEXT_CAMERA_ANGLE_R };
#endif
#ifdef REONU_CAM_3
    u8 cameraMode = gCurrentArea->camera->mode;
#endif
#ifdef PUPPYCAM
    handle_menu_scrolling(MENU_SCROLL_VERTICAL, index, 1, 2);
#else
    handle_menu_scrolling(MENU_SCROLL_VERTICAL, index, 1, 3);
#endif
    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);
    print_generic_string((x + 10), (y -  2), textContinue);
    print_generic_string((x + 10), (y - 17), textExitCourse);
#ifndef PUPPYCAM
#ifdef REONU_CAM_3
    if ((*index != MENU_OPT_CAMERA_ANGLE_R) && (cameraMode != CAMERA_MODE_8_DIRECTIONS)) print_generic_string((x + 10), (y - 33), textCameraAngleR);
    if ((*index != MENU_OPT_CAMERA_ANGLE_R) || (cameraMode == CAMERA_MODE_8_DIRECTIONS)) {
#else
    if (*index != MENU_OPT_CAMERA_ANGLE_R) {
        print_generic_string((x + 10), (y - 33), textCameraAngleR);
#endif
#endif
        gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
        create_dl_translation_matrix(G_MTX_PUSH, (x - X_VAL8), ((y - ((*index - 1) * yIndex)) - Y_VAL8), 0);
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);
        gSPDisplayList(gDisplayListHead++, dl_draw_triangle);
        gSPPopMatrix(  gDisplayListHead++, G_MTX_MODELVIEW);
#ifndef PUPPYCAM
    }
#ifdef REONU_CAM_3
    if (*index == MENU_OPT_CAMERA_ANGLE_R && cameraMode != CAMERA_MODE_8_DIRECTIONS) {
#else
    if (*index == MENU_OPT_CAMERA_ANGLE_R) {
#endif
        render_pause_camera_options((x - 42), (y - 42), &gDialogCameraAngleIndex, 110);
    }
#endif
}

void render_pause_castle_menu_box(ScreenPos x, ScreenPos y) {
    create_dl_translation_matrix(G_MTX_PUSH, (x - 78), (y - 32), 0);
    create_dl_scale_matrix(G_MTX_NOPUSH, 1.2f, 0.8f, 1.0f);
    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 105);
    gSPDisplayList(gDisplayListHead++, dl_draw_text_bg_box);
    gSPPopMatrix(  gDisplayListHead++, G_MTX_MODELVIEW);
    create_dl_translation_matrix(G_MTX_PUSH, (x + 6), (y - 28), 0);
    create_dl_rotation_matrix(G_MTX_NOPUSH, DEFAULT_DIALOG_BOX_ANGLE, 0, 0, 1.0f);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);
    gSPDisplayList(gDisplayListHead++, dl_draw_triangle);
    gSPPopMatrix(  gDisplayListHead++, G_MTX_MODELVIEW);
    create_dl_translation_matrix(G_MTX_PUSH, (x - 9), (y - 101), 0);
    create_dl_rotation_matrix(G_MTX_NOPUSH, 270.0f, 0, 0, 1.0f);
    gSPDisplayList(gDisplayListHead++, dl_draw_triangle);
    gSPPopMatrix(  gDisplayListHead++, G_MTX_MODELVIEW);
}

void highlight_last_course_complete_stars(void) {
    u8 courseDone;
    if (gLastCompletedCourseNum == COURSE_NONE) {
        courseDone = 0;
    } else {
        courseDone = (gLastCompletedCourseNum - 1);
        if (courseDone >= COURSE_STAGES_COUNT) courseDone = COURSE_STAGES_COUNT;
    }
    gDialogLineNum = courseDone;
}

void print_hud_pause_colorful_str(void) {
    uchar textPause[] = { TEXT_PAUSE };
    gSPDisplayList(gDisplayListHead++, dl_rgba16_text_begin);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);
    print_hud_lut_string(HUD_LUT_GLOBAL, 123, 81, textPause);
    gSPDisplayList(gDisplayListHead++, dl_rgba16_text_end);
}

void render_pause_castle_course_stars(ScreenPos x, ScreenPos y, s16 fileNum, s16 courseNum) {
    s16 hasStar      = 0;
    uchar str[COURSE_STAGES_COUNT * 2];
    uchar textStar[] = { TEXT_STAR };
    u8  starFlags    = save_file_get_star_flags(fileNum, courseNum);
    u16 starCount    = save_file_get_course_star_count(fileNum, courseNum);
    u16 nextStar     = 0;
    if (starFlags & 0x40) {
        starCount--;
        print_generic_string((x + 89), (y - 5), textStar);
    }
    while (hasStar != starCount) {
        if (starFlags & (1 << nextStar)) {
            str[nextStar * 2] = DIALOG_CHAR_STAR_FILLED;
            hasStar++;
        } else {
            str[nextStar * 2] = DIALOG_CHAR_STAR_OPEN;
        }
        str[(nextStar * 2) + 1] = DIALOG_CHAR_SPACE;
        nextStar++;
    }
    if ((starCount == nextStar) && (starCount != 6)) {
        str[(nextStar * 2)    ] = DIALOG_CHAR_STAR_OPEN;
        str[(nextStar * 2) + 1] = DIALOG_CHAR_SPACE;
        nextStar++;
    }
    str[nextStar * 2] = DIALOG_CHAR_TERMINATOR;
    print_generic_string((x + 14), (y + 13), str);
}

void render_pause_castle_main_strings(ScreenPos x, ScreenPos y) {
    void **courseNameTbl = segmented_to_virtual(languageTable[gInGameLanguage][1]);
    uchar textCoin[]     = { TEXT_COIN_X };
    void *courseName;
    uchar strVal[8];
    s16 starNum = gDialogLineNum;
    handle_menu_scrolling(MENU_SCROLL_VERTICAL, &gDialogLineNum, -1, (COURSE_STAGES_COUNT + 1));
    if (gDialogLineNum == (COURSE_STAGES_COUNT + 1)) gDialogLineNum = 0;
    if (gDialogLineNum == -1) gDialogLineNum = COURSE_STAGES_COUNT;
    if (gDialogLineNum != COURSE_STAGES_COUNT) {
        while (save_file_get_course_star_count((gCurrSaveFileNum - 1), gDialogLineNum) == 0) {
            if (gDialogLineNum >= starNum) {
                gDialogLineNum++;
            } else {
                gDialogLineNum--;
            }
            if ((gDialogLineNum == COURSE_STAGES_COUNT) || (gDialogLineNum == -1)) {
                gDialogLineNum = COURSE_STAGES_COUNT;
                break;
            }
        }
    }
    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);
    if (gDialogLineNum < COURSE_STAGES_COUNT) {
        courseName = segmented_to_virtual(courseNameTbl[gDialogLineNum]);
        render_pause_castle_course_stars(x, y, (gCurrSaveFileNum - 1), gDialogLineNum);
        print_generic_string((x + 34), (y - 5), textCoin);
        int_to_str(save_file_get_course_coin_score((gCurrSaveFileNum - 1), gDialogLineNum), strVal);
        print_generic_string((x + 54), (y - 5), strVal);
    } else {
        uchar textStarX[] = { TEXT_STAR_X };
        courseName = segmented_to_virtual(courseNameTbl[COURSE_MAX]);
        print_generic_string((x + 40), (y + 13), textStarX);
        int_to_str(save_file_get_total_star_count((gCurrSaveFileNum - 1), (COURSE_BONUS_STAGES - 1), (COURSE_MAX - 1)), strVal);
        print_generic_string((x + 60), (y + 13), strVal);
    }
    print_generic_string((x - 9), (y + 30), courseName);
    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
}
s8  gCourseCompleteCoinsEqual = 0;
s32 gCourseDoneMenuTimer      = 0;
s32 gCourseCompleteCoins      = 0;
s8  gHudFlash                 = FALSE;
s16 render_pause_courses_and_castle(void) {
#ifdef PUPPYCAM
    puppycam_check_pause_buttons();
    if (!gPCOptionOpen) {
#endif
        switch (gDialogBoxState) {
            case DIALOG_STATE_OPENING:
                gDialogLineNum   = MENU_OPT_DEFAULT;
                gDialogTextAlpha = 0;
                level_set_transition(-1, NULL);
                play_sound(SOUND_MENU_PAUSE_OPEN, gGlobalSoundSource);
                if ((gCurrCourseNum >= COURSE_MIN) && (gCurrCourseNum <= COURSE_MAX)) {
                    change_dialog_camera_angle();
                    gDialogBoxState = DIALOG_STATE_VERTICAL;
                } else {
                    highlight_last_course_complete_stars();
                    gDialogBoxState = DIALOG_STATE_HORIZONTAL;
                }
                break;
            case DIALOG_STATE_VERTICAL:
                shade_screen();
                render_pause_my_score_coins();
                render_pause_red_coins();
#ifndef EXIT_COURSE_WHILE_MOVING
                s32 exitCheck = gMarioStates[0].action & ACT_FLAG_PAUSE_EXIT;
#else
                s32 exitCheck = ((gMarioStates[0].pos[1] <= gMarioStates[0].floorHeight)
                    || (gMarioStates[0].action & (ACT_FLAG_SWIMMING | ACT_FLAG_METAL_WATER | ACT_FLAG_PAUSE_EXIT)));
#endif
#ifndef DISABLE_EXIT_COURSE
                if (exitCheck) render_pause_course_options(99, 93, &gDialogLineNum, 15);
#endif
#ifdef REONU_CAM_3
                if (gCurrentArea->camera->mode == CAMERA_MODE_8_DIRECTIONS) render_camera_speed_setting(109, 60);
                if (gPlayer3Controller->buttonPressed & (START_BUTTON)
                || (gPlayer3Controller->buttonPressed & (A_BUTTON | B_BUTTON) && !((gDialogLineNum == MENU_OPT_CAMERA_ANGLE_R) && (gCurrentArea->camera->mode == CAMERA_MODE_8_DIRECTIONS)))) {
#else
                if (gPlayer3Controller->buttonPressed & (A_BUTTON | B_BUTTON | START_BUTTON)) {
#endif
                    level_set_transition(0, NULL);
                    play_sound(SOUND_MENU_PAUSE_CLOSE, gGlobalSoundSource);
                    gDialogBoxState = DIALOG_STATE_OPENING;
                    gMenuMode = MENU_MODE_NONE;
                    return ((gDialogLineNum == MENU_OPT_EXIT_COURSE) ? gDialogLineNum : MENU_OPT_DEFAULT); // MENU_OPT_CONTINUE or MENU_OPT_CAMERA_ANGLE_R
#ifdef REONU_CAM_3
                } else if ((gDialogLineNum == MENU_OPT_CAMERA_ANGLE_R) && (gCurrentArea->camera->mode == CAMERA_MODE_8_DIRECTIONS)) {
                    if (gPlayer3Controller->buttonPressed & A_BUTTON) {
                        if (gCameraSpeed < 4) {
                            gCameraSpeed++;
                        } else {
                            gCameraSpeed = 0;
                        }
                        save_file_set_camera_speed(gCameraSpeed);
                    } else if (gPlayer3Controller->buttonPressed & B_BUTTON) {
                        if (gCameraSpeed > 0) {
                            gCameraSpeed--;
                        } else {
                            gCameraSpeed = 4;
                        }
                        save_file_set_camera_speed(gCameraSpeed);
                    }
#endif
                }
                break;
            case DIALOG_STATE_HORIZONTAL:
                shade_screen();
                print_hud_pause_colorful_str();
                render_pause_castle_menu_box(    160, 143);
                render_pause_castle_main_strings(104,  60);
#ifdef PAUSE_BOWSER_KEYS
                render_pause_bowser_keys();
#endif
#ifdef REONU_CAM_3
                if (gCurrentArea->camera->mode == CAMERA_MODE_8_DIRECTIONS) render_camera_speed_setting(190, 7);
#endif
                if (gPlayer3Controller->buttonPressed & (A_BUTTON | B_BUTTON | START_BUTTON)) {
                    level_set_transition(0, NULL);
                    play_sound(SOUND_MENU_PAUSE_CLOSE, gGlobalSoundSource);
                    gMenuMode       = MENU_MODE_NONE;
                    gDialogBoxState = DIALOG_STATE_OPENING;
                    return MENU_OPT_DEFAULT;
                }
                break;
        }
#if defined(WIDE) && !defined(PUPPYCAM)
        render_widescreen_setting();
#endif
        if (gDialogTextAlpha < 250) gDialogTextAlpha += 25;
#ifdef PUPPYCAM
    } else {
        shade_screen();
        puppycam_display_options();
    }
    puppycam_render_option_text();
#endif
    return MENU_OPT_NONE;
}

#define TXT_HISCORE_X 109
#define TXT_HISCORE_Y  36
#define TXT_CONGRATS_X 70

#define HUD_PRINT_HISCORE         0x0
#define HUD_PRINT_CONGRATULATIONS 0x1

void print_hud_course_complete_string(s8 str) {
    uchar textHiScore[]         = { TEXT_HUD_HI_SCORE        };
    uchar textCongratulations[] = { TEXT_HUD_CONGRATULATIONS };
    uchar colorFade             = ((sins(gDialogColorFadeTimer) * 50.0f) + 200.0f);
    gSPDisplayList(gDisplayListHead++, dl_rgba16_text_begin);
    gDPSetEnvColor(gDisplayListHead++, colorFade, colorFade, colorFade, 255);
    if (str == HUD_PRINT_HISCORE) {
        print_hud_lut_string(HUD_LUT_GLOBAL, TXT_HISCORE_X, TXT_HISCORE_Y, textHiScore);
    } else { // HUD_PRINT_CONGRATULATIONS
        print_hud_lut_string(HUD_LUT_GLOBAL, TXT_CONGRATS_X, 67, textCongratulations);
    }
    gSPDisplayList(gDisplayListHead++, dl_rgba16_text_end);
}

void print_hud_course_complete_coins(ScreenPos x, ScreenPos y) {
    uchar courseCompleteCoinsStr[4];
    uchar hudTextSymCoin[] = { GLYPH_COIN,     GLYPH_SPACE };
    uchar hudTextSymX[]    = { GLYPH_MULTIPLY, GLYPH_SPACE };
    gSPDisplayList(gDisplayListHead++, dl_rgba16_text_begin);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
    print_hud_lut_string(HUD_LUT_GLOBAL,  x,       y, hudTextSymCoin);
    print_hud_lut_string(HUD_LUT_GLOBAL, (x + 16), y, hudTextSymX);
    int_to_str(gCourseCompleteCoins, courseCompleteCoinsStr);
    print_hud_lut_string(HUD_LUT_GLOBAL, (x + 32), y, courseCompleteCoinsStr);
    gSPDisplayList(gDisplayListHead++, dl_rgba16_text_end);
    if (gCourseCompleteCoins >= gHudDisplay.coins) {
        gCourseCompleteCoinsEqual = 1;
        gCourseCompleteCoins      = gHudDisplay.coins;
        if (gGotFileCoinHiScore) print_hud_course_complete_string(HUD_PRINT_HISCORE);
    } else {
        if ((gCourseDoneMenuTimer & 0x1) || (gHudDisplay.coins > 70)) {
            gCourseCompleteCoins++;
            play_sound(SOUND_MENU_YOSHI_GAIN_LIVES, gGlobalSoundSource);
            if ((gCourseCompleteCoins % 50) == 0) {
                play_sound(SOUND_GENERAL_COLLECT_1UP, gGlobalSoundSource);
                gMarioState->numLives++;
            }
        }
        if ((gHudDisplay.coins == gCourseCompleteCoins) && gGotFileCoinHiScore) play_sound(SOUND_MENU_HIGH_SCORE, gGlobalSoundSource);
    }
}

void play_star_fanfare_and_flash_hud(s32 arg, u8 starNum) {
    if ((gHudDisplay.coins == gCourseCompleteCoins) && ((gCurrCourseStarFlags & starNum) == 0) && !gHudFlash) {
        play_star_fanfare();
        gHudFlash = arg;
    }
}

#define TXT_NAME_X1   71
#define TXT_NAME_X2   69
#define CRS_NUM_X2   104
#define CRS_NUM_X3   102
#define TXT_CLEAR_X1 (get_string_width(name) + 81)
#define TXT_CLEAR_X2 (get_string_width(name) + 79)

void render_course_complete_lvl_info_and_hud_str(void) {
    uchar textCourse[]       = { TEXT_COURSE             };
    UNUSED uchar textClear[] = { TEXT_CLEAR              };
    uchar textSymStar[]      = { GLYPH_STAR, GLYPH_SPACE };
    void **actNameTbl;
    void **courseNameTbl;
    uchar *name;
    uchar strCourseNum[4];
    actNameTbl    = segmented_to_virtual(languageTable[gInGameLanguage][2]);
    courseNameTbl = segmented_to_virtual(languageTable[gInGameLanguage][1]);
    if (gLastCompletedCourseNum <= COURSE_STAGES_MAX) {
        print_hud_course_complete_coins(118, 103);
        play_star_fanfare_and_flash_hud(TRUE, (1 << (gLastCompletedStarNum - 1)));
        name = segmented_to_virtual(actNameTbl[((gLastCompletedStarNum == 7) ? ((COURSE_STAGES_MAX * 6) + 1) : (((gLastCompletedCourseNum - 1) * 6) + gLastCompletedStarNum - 1))]);
        gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
        int_to_str(gLastCompletedCourseNum, strCourseNum);
        gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, gDialogTextAlpha);
        print_generic_string(65, 165, textCourse);
        print_generic_string(CRS_NUM_X2, 165, strCourseNum);
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);
        print_generic_string(63, 167, textCourse);
        print_generic_string(CRS_NUM_X3, 167, strCourseNum);
        gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
    } else if ((gLastCompletedCourseNum == COURSE_BITDW) || (gLastCompletedCourseNum == COURSE_BITFS)) {
        name = segmented_to_virtual(courseNameTbl[gLastCompletedCourseNum - 1]);
        gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
        gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, gDialogTextAlpha);
        print_generic_string(TXT_NAME_X1,  130, name);
        print_generic_string(TXT_CLEAR_X1, 130, textClear);
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);
        print_generic_string(TXT_NAME_X2,  132, name);
        print_generic_string(TXT_CLEAR_X2, 132, textClear);
        gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
        print_hud_course_complete_string(HUD_PRINT_CONGRATULATIONS);
        print_hud_course_complete_coins(118, 111);
        play_star_fanfare_and_flash_hud(FALSE, 0); // 2 isn't defined, originally for key hud?
        return;
    } else {
        name = segmented_to_virtual(actNameTbl[COURSE_STAGES_MAX * 6]);
        print_hud_course_complete_coins(118, 103);
        play_star_fanfare_and_flash_hud(TRUE, (1 << (gLastCompletedStarNum - 1)));
    }
    gSPDisplayList(gDisplayListHead++, dl_rgba16_text_begin);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);
    print_hud_lut_string(HUD_LUT_GLOBAL, 55, 77, textSymStar);
    gSPDisplayList(gDisplayListHead++, dl_rgba16_text_end);
    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, gDialogTextAlpha);
    print_generic_string(76, 145, name);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);
    print_generic_string(74, 147, name);
    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
}

#define TXT_SAVEOPTIONS_X (x + 12)
#define TXT_SAVECONT_Y          0
#define TXT_SAVEQUIT_Y         20
#define TXT_CONTNOSAVE_Y       40

#define X_VAL9 x
void render_save_confirmation(ScreenPos x, ScreenPos y, s8 *index, ScreenPos yPos) { // last arg is always 20
    uchar textSaveAndContinue[]     = { TEXT_SAVE_AND_CONTINUE       };
    uchar textSaveAndQuit[]         = { TEXT_SAVE_AND_QUIT           };
    uchar textContinueWithoutSave[] = { TEXT_CONTINUE_WITHOUT_SAVING };
    handle_menu_scrolling(MENU_SCROLL_VERTICAL, index, 1, 3);
    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);
    print_generic_string(TXT_SAVEOPTIONS_X, y + TXT_SAVECONT_Y,   textSaveAndContinue    );
    print_generic_string(TXT_SAVEOPTIONS_X, y - TXT_SAVEQUIT_Y,   textSaveAndQuit        );
    print_generic_string(TXT_SAVEOPTIONS_X, y - TXT_CONTNOSAVE_Y, textContinueWithoutSave);
    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
    create_dl_translation_matrix(G_MTX_PUSH, X_VAL9, (y - (((*index - 1) * yPos))), 0);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, gDialogTextAlpha);
    gSPDisplayList(gDisplayListHead++, dl_draw_triangle);
    gSPPopMatrix(  gDisplayListHead++, G_MTX_MODELVIEW);
}

s16 render_course_complete_screen(void) {
    s16 index;
    switch (gDialogBoxState) {
        case DIALOG_STATE_OPENING:
            render_course_complete_lvl_info_and_hud_str();
            if ((gCourseDoneMenuTimer > 100) && (gCourseCompleteCoinsEqual == 1)) {
                gDialogBoxState = DIALOG_STATE_VERTICAL;
                level_set_transition(-1, NULL);
                gDialogTextAlpha = 0;
                gDialogLineNum = MENU_OPT_DEFAULT;
            }
            break;
        case DIALOG_STATE_VERTICAL:
            shade_screen();
            render_course_complete_lvl_info_and_hud_str();
            render_save_confirmation(100, 86, &gDialogLineNum, 20);
            if ((gCourseDoneMenuTimer > 110) && (gPlayer3Controller->buttonPressed & (A_BUTTON | START_BUTTON))) {
                level_set_transition(0, NULL);
                play_sound(SOUND_MENU_STAR_SOUND, gGlobalSoundSource);
                gDialogBoxState           = DIALOG_STATE_OPENING;
                gMenuMode                 = MENU_MODE_NONE;
                index                     = gDialogLineNum;
                gCourseDoneMenuTimer      = 0;
                gCourseCompleteCoins      = 0;
                gCourseCompleteCoinsEqual = 0;
                gHudFlash                 = FALSE;
                return index;
            }
            break;
    }
    if (gDialogTextAlpha < 250) gDialogTextAlpha += 25;
    gCourseDoneMenuTimer++;
    return MENU_OPT_NONE;
}

s16 render_menus_and_dialogs(void) {
    s16 index = MENU_OPT_NONE;
    create_dl_ortho_matrix();
    if (gMenuMode != MENU_MODE_NONE) {
        switch (gMenuMode) {
            case MENU_MODE_UNUSED_0:                      index = render_pause_courses_and_castle(); break;
            case MENU_MODE_RENDER_PAUSE_SCREEN:           index = render_pause_courses_and_castle(); break;
            case MENU_MODE_RENDER_COURSE_COMPLETE_SCREEN: index = render_course_complete_screen();   break;
            case MENU_MODE_UNUSED_3:                      index = render_course_complete_screen();   break;
        }
        gDialogColorFadeTimer = (s16) gDialogColorFadeTimer + 0x1000;
    } else if (gDialogID != DIALOG_NONE) {
        // The Peach "Dear Mario" message needs to be repositioned separately
        if (gDialogID == DIALOG_020) {
            print_peach_letter_message();
            return index;
        }
        render_dialog_entries();
        gDialogColorFadeTimer = (s16) gDialogColorFadeTimer + 0x1000;
    }
    return index;
}
