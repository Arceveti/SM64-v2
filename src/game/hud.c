#include <PR/ultratypes.h>

#include "sm64.h"
#include "actors/common1.h"
#include "gfx_dimensions.h"
#include "game_init.h"
#include "level_update.h"
#include "camera.h"
#include "print.h"
#include "ingame_menu.h"
#include "hud.h"
#include "segment2.h"
#include "area.h"
#include "save_file.h"
#include "print.h"
#include "engine/surface_load.h"

/* @file hud.c
 * This file implements HUD rendering and power meter animations.
 * That includes stars, lives, coins, camera status, power meter, timer
 * cannon reticle, and the unused keys.
 **/

#define HUD_TOP_Y 209
#define HUD_BOTTOM_Y 31
#define HUD_TIMER_X 150 // from right edge
#define HUD_COINS_X 152 // from right edge
#define HUD_STARS_X 78
#define HUD_CAMERA_X 54
#define HUD_CAMERA_Y (SCREEN_HEIGHT - HUD_BOTTOM_Y) - 4;
#define HUD_POWER_METER_Y 166

#ifdef NEW_HUD
#define HUD_LIVES_X 8
#define HUD_POWER_METER_X 142
#define HUD_RED_COINS_X 70
#define HUD_SECRETS_X 8
#else
#define HUD_LIVES_X 22
#define HUD_POWER_METER_X 140
#define HUD_RED_COINS_X 8
#define HUD_SECRETS_X 8
#endif

// ------------- FPS COUNTER ---------------
// To use it, call print_fps(x,y); every frame.
#define FRAMETIME_COUNT 30

OSTime frameTimes[FRAMETIME_COUNT];
u8 curFrameTimeIndex = 0;

#include "PR/os_convert.h"

// Call once per frame
f32 calculate_and_update_fps() {
    OSTime newTime = osGetTime();
    OSTime oldTime = frameTimes[curFrameTimeIndex];
    frameTimes[curFrameTimeIndex] = newTime;

    curFrameTimeIndex++;
    if (curFrameTimeIndex >= FRAMETIME_COUNT) {
        curFrameTimeIndex = 0;
    }

    return ((f32)FRAMETIME_COUNT * 1000000.0f) / (s32)OS_CYCLES_TO_USEC(newTime - oldTime);
}

void print_fps(s32 x, s32 y) {
    f32 fps = calculate_and_update_fps();
    char text[10];

    sprintf(text, "%2.2f", fps);

    print_text(x, y, text);
}

// ------------ END OF FPS COUNER -----------------

struct PowerMeterHUD {
    s8 animation;
    s16 x;
    s16 y;
};

struct CameraHUD {
    s16 status;
};

// Stores health segmented value defined by numHealthWedges
// When the HUD is rendered this value is 8, full health.
static s16 sPowerMeterStoredHealth;

static struct PowerMeterHUD sPowerMeterHUD = {
    POWER_METER_HIDDEN,
    HUD_POWER_METER_X,
    HUD_POWER_METER_Y,
};

// Power Meter timer that keeps counting when it's visible.
// Gets reset when the health is filled and stops counting
// when the power meter is hidden.
s32 sPowerMeterVisibleTimer = 0;

static struct CameraHUD sCameraHUD = { CAM_STATUS_NONE };

/**
 * Renders a rgba16 16x16 glyph texture from a table list.
 */
void render_hud_tex_lut(s32 x, s32 y, u8 *texture) {
    gDPPipeSync(gDisplayListHead++);
    gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, texture);
    gSPDisplayList(gDisplayListHead++, &dl_hud_img_load_tex_block);
    gSPTextureRectangle(gDisplayListHead++, x << 2, y << 2, (x + 15) << 2, (y + 15) << 2,
                        G_TX_RENDERTILE, 0, 0, 4 << 10, 1 << 10);
}

/**
 * Renders a rgba16 8x8 glyph texture from a table list.
 */
void render_hud_small_tex_lut(s32 x, s32 y, u8 *texture) {
    gDPSetTile(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0,
                G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD, G_TX_WRAP | G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOLOD);
    gDPTileSync(gDisplayListHead++);
    gDPSetTile(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 2, 0, G_TX_RENDERTILE, 0,
                G_TX_CLAMP, 3, G_TX_NOLOD, G_TX_CLAMP, 3, G_TX_NOLOD);
    gDPSetTileSize(gDisplayListHead++, G_TX_RENDERTILE, 0, 0, (8 - 1) << G_TEXTURE_IMAGE_FRAC, (8 - 1) << G_TEXTURE_IMAGE_FRAC);
    gDPPipeSync(gDisplayListHead++);
    gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, texture);
    gDPLoadSync(gDisplayListHead++);
    gDPLoadBlock(gDisplayListHead++, G_TX_LOADTILE, 0, 0, 8 * 8 - 1, CALC_DXT(8, G_IM_SIZ_16b_BYTES));
    gSPTextureRectangle(gDisplayListHead++, x << 2, y << 2, (x + 7) << 2, (y + 7) << 2, G_TX_RENDERTILE,
                        0, 0, 4 << 10, 1 << 10);
}

/**
 * Renders power meter health segment texture using a table list.
 */
void render_power_meter_health_segment(s16 numHealthWedges) {
    u8 *(*healthLUT)[];

    healthLUT = segmented_to_virtual(&power_meter_health_segments_lut);

    gDPPipeSync(gDisplayListHead++);
    gDPSetTextureImage(gDisplayListHead++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1,
                       (*healthLUT)[numHealthWedges - 1]);
    gDPLoadSync(gDisplayListHead++);
    gDPLoadBlock(gDisplayListHead++, G_TX_LOADTILE, 0, 0, 32 * 32 - 1, CALC_DXT(32, G_IM_SIZ_16b_BYTES));
    gSP1Triangle(gDisplayListHead++, 0, 1, 2, 0);
    gSP1Triangle(gDisplayListHead++, 0, 2, 3, 0);
}

/**
 * Renders power meter display lists.
 * That includes the "POWER" base and the colored health segment textures.
 */
void render_dl_power_meter(s16 numHealthWedges) {
    Mtx *mtx;

    mtx = alloc_display_list(sizeof(Mtx));

    if (mtx == NULL) return;

    guTranslate(mtx, (f32) sPowerMeterHUD.x, (f32) sPowerMeterHUD.y, 0);

    gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(mtx++),
              G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gSPDisplayList(gDisplayListHead++, &dl_power_meter_base);

    if (numHealthWedges != 0) {
        gSPDisplayList(gDisplayListHead++, &dl_power_meter_health_segments_begin);
        render_power_meter_health_segment(numHealthWedges);
        gSPDisplayList(gDisplayListHead++, &dl_power_meter_health_segments_end);
    }

    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);
}

/**
 * Power meter animation called when there's less than 8 health segments
 * Checks its timer to later change into deemphasizing mode.
 */
void animate_power_meter_emphasized(void) {
    s16 hudDisplayFlags;
    hudDisplayFlags = gHudDisplay.flags;

    if (!(hudDisplayFlags & HUD_DISPLAY_FLAG_EMPHASIZE_POWER)) {
        if (sPowerMeterVisibleTimer == 45) {
            sPowerMeterHUD.animation = POWER_METER_DEEMPHASIZING;
        }
    } else {
        sPowerMeterVisibleTimer = 0;
    }
}

/**
 * Power meter animation called after emphasized mode.
 * Moves power meter y pos speed until it's at 200 to be visible.
 */
static void animate_power_meter_deemphasizing(void) {
    s16 speed = 5;

    if (sPowerMeterHUD.y >= 181) {
        speed = 3;
    }

    if (sPowerMeterHUD.y >= 191) {
        speed = 2;
    }

    if (sPowerMeterHUD.y >= 196) {
        speed = 1;
    }

    sPowerMeterHUD.y += speed;

    if (sPowerMeterHUD.y >= 201) {
        sPowerMeterHUD.y = 200;
        sPowerMeterHUD.animation = POWER_METER_VISIBLE;
    }
}

/**
 * Power meter animation called when there's 8 health segments.
 * Moves power meter y pos quickly until it's at 301 to be hidden.
 */
static void animate_power_meter_hiding(void) {
    sPowerMeterHUD.y += 20;
    if (sPowerMeterHUD.y >= 301) {
        sPowerMeterHUD.animation = POWER_METER_HIDDEN;
        sPowerMeterVisibleTimer = 0;
    }
}

/**
 * Handles power meter actions depending of the health segments values.
 */
void handle_power_meter_actions(s16 numHealthWedges) {
    // Show power meter if health is not full, less than 8
    if (numHealthWedges < 8 && sPowerMeterStoredHealth == 8 && sPowerMeterHUD.animation == POWER_METER_HIDDEN) {
        sPowerMeterHUD.animation = POWER_METER_EMPHASIZED;
        sPowerMeterHUD.y = 166;
    }

    // Show power meter if health is full, has 8
    if (numHealthWedges == 8 && sPowerMeterStoredHealth == 7) {
        sPowerMeterVisibleTimer = 0;
    }

    // After health is full, hide power meter
    if (numHealthWedges == 8 && sPowerMeterVisibleTimer > 45) {
        sPowerMeterHUD.animation = POWER_METER_HIDING;
    }

    // Update to match health value
    sPowerMeterStoredHealth = numHealthWedges;

    // If Mario is swimming, keep power meter visible
    if (gPlayerCameraState->action & ACT_FLAG_SWIMMING) {
        if (sPowerMeterHUD.animation == POWER_METER_HIDDEN
            || sPowerMeterHUD.animation == POWER_METER_EMPHASIZED) {
            sPowerMeterHUD.animation = POWER_METER_DEEMPHASIZING;
            sPowerMeterHUD.y = 166;
        }
        sPowerMeterVisibleTimer = 0;
    }
}

/**
 * Renders the power meter that shows when Mario is in underwater
 * or has taken damage and has less than 8 health segments.
 * And calls a power meter animation function depending of the value defined.
 */
void render_hud_power_meter(void) {
    s16 shownHealthWedges = gHudDisplay.wedges;

    if (sPowerMeterHUD.animation != POWER_METER_HIDING) {
        handle_power_meter_actions(shownHealthWedges);
    }

    if (sPowerMeterHUD.animation == POWER_METER_HIDDEN) return;

    switch (sPowerMeterHUD.animation) {
        case POWER_METER_EMPHASIZED:
            animate_power_meter_emphasized();
            break;
        case POWER_METER_DEEMPHASIZING:
            animate_power_meter_deemphasizing();
            break;
        case POWER_METER_HIDING:
            animate_power_meter_hiding();
            break;
        default:
            break;
    }

    render_dl_power_meter(shownHealthWedges);

    sPowerMeterVisibleTimer++;
}

#ifdef VERSION_JP
#define HUD_TOP_Y 210
#else
#define HUD_TOP_Y 209
#endif

/**
 * Renders the amount of lives Mario has.
 */
void render_hud_mario_lives(void) {
    print_text(GFX_DIMENSIONS_RECT_FROM_LEFT_EDGE(HUD_LIVES_X), HUD_TOP_Y, ","); // 'Mario Head' glyph
    print_text(GFX_DIMENSIONS_RECT_FROM_LEFT_EDGE(HUD_LIVES_X) + 18, HUD_TOP_Y, "*"); // 'X' glyph
#ifdef HUD_LEADING_ZEROES
    print_text_fmt_int(GFX_DIMENSIONS_RECT_FROM_LEFT_EDGE(HUD_LIVES_X) + 32, HUD_TOP_Y, "%02d", gHudDisplay.lives);
#else
    print_text_fmt_int(GFX_DIMENSIONS_RECT_FROM_LEFT_EDGE(HUD_LIVES_X) + 32, HUD_TOP_Y, "%d", gHudDisplay.lives);
#endif
}

/**
 * Renders the amount of coins collected.
 */
void render_hud_coins(void) {
    print_text(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(HUD_COINS_X), HUD_TOP_Y, "$"); // 'Coin' glyph
    print_text(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(HUD_COINS_X) + 16, HUD_TOP_Y, "*"); // 'X' glyph

#ifdef HUD_LEADING_ZEROES
    print_text_fmt_int(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(HUD_COINS_X) + 30, HUD_TOP_Y, "%03d", gHudDisplay.coins);
#else
    print_text_fmt_int(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(HUD_COINS_X) + 30, HUD_TOP_Y, "%d", gHudDisplay.coins);
#endif
#ifdef NEW_HUD
    if (gRedCoinsCollected > 0) {
        print_text(         GFX_DIMENSIONS_RECT_FROM_LEFT_EDGE(HUD_RED_COINS_X), HUD_TOP_Y, "@"); // 'Red Coin' glyph
        print_text(         GFX_DIMENSIONS_RECT_FROM_LEFT_EDGE(HUD_RED_COINS_X) + 16, HUD_TOP_Y, "*"); // 'X' glyph
        print_text_fmt_int( GFX_DIMENSIONS_RECT_FROM_LEFT_EDGE(HUD_RED_COINS_X) + 30, HUD_TOP_Y, "%d", gRedCoinsCollected);
    }
#endif
}

#ifdef VERSION_JP
#define HUD_STARS_X 73
#else
#define HUD_STARS_X 78
#endif

/**
 * Renders the amount of stars collected.
 * Disables "X" glyph when Mario has 100 stars or more.
 */
void render_hud_stars(void) {
    s8 showX = 0;

    if (gHudFlash == 1 && gGlobalTimer & 0x08) return;

    if (gHudDisplay.stars < 100) {
        showX = 1;
    }

    print_text(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(HUD_STARS_X), HUD_TOP_Y, "^"); // 'Star' glyph
    if (showX == 1) {
        print_text(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(HUD_STARS_X) + 16, HUD_TOP_Y, "*"); // 'X' glyph
    }
    print_text_fmt_int((showX * 14) + GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(HUD_STARS_X) + 16,
#ifdef HUD_LEADING_ZEROES
                       HUD_TOP_Y, "%03d", gHudDisplay.stars);
#else
                       HUD_TOP_Y, "%d", gHudDisplay.stars);
#endif
}

/**
 * Unused function that renders the amount of keys collected.
 * Leftover function from the beta version of the game.
 */
void render_hud_keys(void) {
    s16 i;

    for (i = 0; i < gHudDisplay.keys; i++) {
        print_text((i * 16) + 220, 142, "/"); // unused glyph - beta key
    }
}

/**
 * Function that renders the amount of secrets collected.
 */
void render_hud_secrets(void) {
    if (gSecretsCollected > 0) {
        print_text(         GFX_DIMENSIONS_RECT_FROM_LEFT_EDGE(HUD_SECRETS_X   ), HUD_TOP_Y-24, "?"); // 'question mark' glyph
        print_text(         GFX_DIMENSIONS_RECT_FROM_LEFT_EDGE(HUD_SECRETS_X+18), HUD_TOP_Y-24, "*"); // 'X' glyph
        print_text_fmt_int( GFX_DIMENSIONS_RECT_FROM_LEFT_EDGE(HUD_SECRETS_X+32), HUD_TOP_Y-24, "%d", gSecretsCollected);
    }
}

/**
 * Renders the timer when Mario start sliding in PSS.
 */
void render_hud_timer(void) {
    u8 *(*hudLUT)[58];
    u16 timerValFrames;
    u16 timerMins;
    u16 timerSecs;
    u16 timerFracSecs;

    hudLUT = segmented_to_virtual(&main_hud_lut);
    timerValFrames = gHudDisplay.timer;
#ifdef VERSION_EU
    switch (eu_get_language()) {
        case LANGUAGE_ENGLISH:
            print_text(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(HUD_TIMER_X), HUD_TOP_Y-24, "TIME");
            break;
        case LANGUAGE_FRENCH:
            print_text(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(HUD_TIMER_X), HUD_TOP_Y-24, "TEMPS");
            break;
        case LANGUAGE_GERMAN:
            print_text(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(HUD_TIMER_X), HUD_TOP_Y-24, "ZEIT");
            break;
    }
#endif
    timerMins = timerValFrames / (30 * 60);
    timerSecs = (timerValFrames - (timerMins * 1800)) / 30;

    timerFracSecs = ((timerValFrames - (timerMins * 1800) - (timerSecs * 30)) & 0xFFFF) / 3;
#ifndef VERSION_EU
    print_text(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(HUD_TIMER_X), HUD_TOP_Y-24, "TIME");
#endif
    print_text_fmt_int(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(HUD_TIMER_X) + 59, HUD_TOP_Y-24, "%0d", timerMins);
    print_text_fmt_int(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(HUD_TIMER_X) + 79, HUD_TOP_Y-24, "%02d", timerSecs);
    print_text_fmt_int(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(HUD_TIMER_X) + 115, HUD_TOP_Y-24, "%d", timerFracSecs);
    gSPDisplayList(gDisplayListHead++, dl_hud_img_begin);
    render_hud_tex_lut(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(HUD_TIMER_X) + 69, HUD_TOP_Y-177, (*hudLUT)[GLYPH_APOSTROPHE]);
    render_hud_tex_lut(GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(HUD_TIMER_X) + 104, HUD_TOP_Y-177, (*hudLUT)[GLYPH_DOUBLE_QUOTE]);
    gSPDisplayList(gDisplayListHead++, dl_hud_img_end);
}

/**
 * Sets HUD status camera value depending of the actions
 * defined in update_camera_status.
 */
void set_hud_camera_status(s16 status) {
    sCameraHUD.status = status;
}

/**
 * Renders camera HUD glyphs using a table list, depending of
 * the camera status called, a defined glyph is rendered.
 */
void render_hud_camera_status(void) {
    u8 *(*cameraLUT)[6];
    s32 x;
    s32 y;

    cameraLUT = segmented_to_virtual(&main_hud_camera_lut);
    x = GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(HUD_CAMERA_X);
    y = HUD_CAMERA_Y;

    if (sCameraHUD.status == CAM_STATUS_NONE) return;

    gSPDisplayList(gDisplayListHead++, dl_hud_img_begin);
    render_hud_tex_lut(x, y, (*cameraLUT)[GLYPH_CAM_CAMERA]);

    switch (sCameraHUD.status & CAM_STATUS_MODE_GROUP) {
        case CAM_STATUS_MARIO:
            render_hud_tex_lut(x + 16, y, (*cameraLUT)[GLYPH_CAM_MARIO_HEAD]);
            break;
        case CAM_STATUS_LAKITU:
            render_hud_tex_lut(x + 16, y, (*cameraLUT)[GLYPH_CAM_LAKITU_HEAD]);
            break;
        case CAM_STATUS_FIXED:
            render_hud_tex_lut(x + 16, y, (*cameraLUT)[GLYPH_CAM_FIXED]);
            break;
    }

    switch (sCameraHUD.status & CAM_STATUS_C_MODE_GROUP) {
        case CAM_STATUS_C_DOWN:
            render_hud_small_tex_lut(x + 4, y + 16, (*cameraLUT)[GLYPH_CAM_ARROW_DOWN]);
            break;
        case CAM_STATUS_C_UP:
            render_hud_small_tex_lut(x + 4, y - 8, (*cameraLUT)[GLYPH_CAM_ARROW_UP]);
            break;
    }

    gSPDisplayList(gDisplayListHead++, dl_hud_img_end);
}

/**
 * Render HUD strings using hudDisplayFlags with it's render functions,
 * excluding the cannon reticle which detects a camera preset for it.
 */
void render_hud(void) {
    s16 hudDisplayFlags;
#ifdef VERSION_EU
    Mtx *mtx;
#endif

    hudDisplayFlags = gHudDisplay.flags;

    if (hudDisplayFlags == HUD_DISPLAY_NONE) {
        sPowerMeterHUD.animation = POWER_METER_HIDDEN;
        sPowerMeterStoredHealth = 8;
        sPowerMeterVisibleTimer = 0;
    } else {
#ifdef VERSION_EU
        // basically create_dl_ortho_matrix but guOrtho screen width is different

        mtx = alloc_display_list(sizeof(*mtx));
        if (mtx == NULL) return;
        create_dl_identity_matrix();
        guOrtho(mtx, -16.0f, SCREEN_WIDTH + 16, 0, SCREEN_HEIGHT, -10.0f, 10.0f, 1.0f);
        gSPPerspNormalize(gDisplayListHead++, 0xFFFF);
        gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(mtx),
                G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);
#else
        create_dl_ortho_matrix();
#endif

        if (gCurrentArea != NULL && gCurrentArea->camera->mode == CAMERA_MODE_INSIDE_CANNON) {
            render_hud_cannon_reticle();
        }
#ifndef DISABLE_LIVES
        if (hudDisplayFlags & HUD_DISPLAY_FLAG_LIVES) {
            render_hud_mario_lives();
        }
#endif
        if (hudDisplayFlags & HUD_DISPLAY_FLAG_COIN_COUNT) {
            render_hud_coins();
        }

        if (hudDisplayFlags & HUD_DISPLAY_FLAG_STAR_COUNT) {
            render_hud_stars();
        }
#ifdef NEW_HUD
        if (hudDisplayFlags & HUD_DISPLAY_FLAG_SECRETS) {
            render_hud_secrets();
        }
#endif
        if (hudDisplayFlags & HUD_DISPLAY_FLAG_CAMERA_AND_POWER) {
            render_hud_power_meter();
            render_hud_camera_status();
        }

        if (hudDisplayFlags & HUD_DISPLAY_FLAG_TIMER) {
            render_hud_timer();
        }

        if (gSurfacePoolError & NOT_ENOUGH_ROOM_FOR_SURFACES) {
            print_text(10, 40, "SURFACE POOL FULL");
        }
        if (gSurfacePoolError & NOT_ENOUGH_ROOM_FOR_NODES) {
            print_text(10, 60, "SURFACE NODE POOL FULL");
        }
    }
}
