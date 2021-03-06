#include <PR/ultratypes.h>

#include "audio/external.h"
#include "behavior_data.h"
#include "engine/behavior_script.h"
#include "engine/graph_node.h"
#include "engine/math_util.h"
#include "eu_translation.h"
#include "game/area.h"
#include "boot/game_init.h"
#include "game/ingame_menu.h"
#include "game/level_update.h"
#include "boot/memory.h"
#include "game/object_helpers.h"
#include "game/object_list_processor.h"
#include "game/save_file.h"
#include "game/segment2.h"
#include "game/segment7.h"
#include "game/rumble_init.h"
#include "sm64.h"
#include "star_select.h"
#include "text_strings.h"
// #include "prevent_bss_reordering.h"
#include "boot/main.h"

/**
 * @file star_select.c
 * This file implements how the star select screen (act selector) function.
 * That includes handles what stars can be selected, star selector types,
 * strings, act values, and star selector model rendering if a star is collected or not.
 */

// Star Selector count models printed in the act selector menu.
static struct Object *sStarSelectorModels[8];

// The act the course is loaded as, affects whether some objects spawn.
static s8 sLoadedActNum;

// Number of obtained stars, excluding the coin star.
static u8 sObtainedStars;

// Total number of stars that appear in the act selector menu.
static s8 sVisibleStars;

// Act selected when the act menu is first opened.
static u8 sInitSelectedActNum;

// Index value of the act selected in the act menu.
static s8 sSelectedActIndex = 0;

// Index value of the star that is selectable in the act menu.
// Excluding the next star, it doesn't count other transparent stars.
static s8 sSelectableStarIndex = 0;

// Act Selector menu timer that keeps counting until you choose an act.
static s32 sActSelectorMenuTimer = 0;

/**
 * Act Selector Star Type Loop Action
 * Defines a select type for a star in the act selector.
 */
void bhv_act_selector_star_type_loop(void) {
    switch (o->oStarSelectorType) {
        // If a star is not selected, don't rotate or change size
        case STAR_SELECTOR_NOT_SELECTED:
            o->oStarSelectorSize -= 0.1f;
            if (o->oStarSelectorSize < 1.0f) o->oStarSelectorSize = 1.0f;
            o->oFaceAngleYaw  =   0x0;
            break;
        // If a star is selected, rotate and slightly increase size
        case STAR_SELECTOR_SELECTED:
            o->oStarSelectorSize += 0.1f;
            if (o->oStarSelectorSize > 1.3f) o->oStarSelectorSize = 1.3f;
            o->oFaceAngleYaw += DEG(11.25);
            break;
        // If the 100 coin star is selected, rotate
        case STAR_SELECTOR_100_COINS:
            o->oFaceAngleYaw += DEG(11.25);
            break;
    }
    // Scale act selector stars depending of the type selected
    cur_obj_scale(o->oStarSelectorSize);
    // Unused timer, only referenced here. Probably replaced by sActSelectorMenuTimer
    o->oStarSelectorTimer++;
}

/**
 * Renders the 100 coin star with an special star selector type.
 */
void render_100_coin_star(u8 stars) {
    if (stars & STAR_FLAG_ACT_100_COINS) {
        // If the 100 coin star has been collected, create a new star selector next to the coin score.
#ifdef WIDE
        sStarSelectorModels[6] = spawn_object_abs_with_rot(o, 0, MODEL_STAR, bhvActSelectorStarType, (gConfig.widescreen ? ((370 * 4.0f) / 3.0f) : 370), 24, -300, 0x0, 0x0, 0x0);
#else
        sStarSelectorModels[6] = spawn_object_abs_with_rot(o, 0, MODEL_STAR, bhvActSelectorStarType,                                                370, 24, -300, 0x0, 0x0, 0x0);
#endif
        sStarSelectorModels[6]->oStarSelectorSize = 0.8f;
        sStarSelectorModels[6]->oStarSelectorType = STAR_SELECTOR_100_COINS;
    }
}

/**
 * Act Selector Init Action
 * Checks how many stars has been obtained in a course, to render
 * the correct star models, the 100 coin star and also handles
 * checks of what star should be next in sInitSelectedActNum.
 */
void bhv_act_selector_init(void) {
    s16 i = 0;
    ModelID16 selectorModelIDs[10];
    u8 stars = save_file_get_star_flags((gCurrSaveFileNum - 1), (gCurrCourseNum - 1));
    sVisibleStars = 0;
    while (i != sObtainedStars) {
        if (stars & (1 << sVisibleStars)) { // Star has been collected
            selectorModelIDs[sVisibleStars] = MODEL_STAR;
            i++;
        } else { // Star has not been collected
            selectorModelIDs[sVisibleStars] = MODEL_TRANSPARENT_STAR;
            // If this is the first star that has not been collected, set
            // the default selection to this star.
            if (sInitSelectedActNum == 0) {
                sInitSelectedActNum  = (sVisibleStars + 1);
                sSelectableStarIndex =  sVisibleStars;
            }
        }
        sVisibleStars++;
    }
    // If the stars have been collected in order so far, show the next star.
    if ((sVisibleStars == sObtainedStars) && (sVisibleStars != 6)) {
        selectorModelIDs[sVisibleStars] = MODEL_TRANSPARENT_STAR;
        sInitSelectedActNum             = (sVisibleStars + 1);
        sSelectableStarIndex            =  sVisibleStars;
        sVisibleStars++;
    }
    // If all stars have been collected, set the default selection to the last star.
    if (sObtainedStars == 6) sInitSelectedActNum = sVisibleStars;
    // Render star selector objects
#ifdef WIDE
    if (gConfig.widescreen) {
        for ((i = 0); (i < sVisibleStars); (i++)) {
            sStarSelectorModels[i] = spawn_object_abs_with_rot(o, 0, selectorModelIDs[i], bhvActSelectorStarType, (((75 + sVisibleStars * -75 + i * 152)*4.0f)/3), 248, -300, 0x0, 0x0, 0x0);
            sStarSelectorModels[i]->oStarSelectorSize = 1.0f;
        }
    } else {
        for ((i = 0); (i < sVisibleStars); (i++)) {
            sStarSelectorModels[i] = spawn_object_abs_with_rot(o, 0, selectorModelIDs[i], bhvActSelectorStarType, 75 + sVisibleStars * -75 + i * 152, 248, -300, 0x0, 0x0, 0x0);
            sStarSelectorModels[i]->oStarSelectorSize = 1.0f;
        }
    }
#else
    for ((i = 0); (i < sVisibleStars); (i++)) {
        sStarSelectorModels[i] = spawn_object_abs_with_rot(o, 0, selectorModelIDs[i], bhvActSelectorStarType, 75 + sVisibleStars * -75 + i * 152, 248, -300, 0x0, 0x0, 0x0);
        sStarSelectorModels[i]->oStarSelectorSize = 1.0f;
    }
#endif
    render_100_coin_star(stars);
}

/**
 * Act Selector Loop Action
 * Handles star selector scrolling depending of what stars are
 * selectable, whenever all 6 stars are obtained or not.
 * Also handles 2 star selector types whenever the star is selected
 * or not, the types are defined in bhv_act_selector_star_type_loop.
 */
void bhv_act_selector_loop(void) {
    s8 i;
    u8 starIndexCounter;
    u8 stars = save_file_get_star_flags((gCurrSaveFileNum - 1), (gCurrCourseNum - 1));
    if (sObtainedStars != 6) {
        // Sometimes, stars are not selectable even if they appear on the screen.
        // This code filters selectable and non-selectable stars.
        sSelectedActIndex = 0;
        handle_menu_scrolling(MENU_SCROLL_HORIZONTAL, &sSelectableStarIndex, 0, sObtainedStars);
        starIndexCounter = sSelectableStarIndex;
        for ((i = 0); (i < sVisibleStars); (i++)) {
            // Can the star be selected (is it either already completed or the first non-completed mission)
            if ((stars & (1 << i)) || ((i + 1) == sInitSelectedActNum)) {
                if (starIndexCounter == 0) { // We have reached the sSelectableStarIndex-th selectable star.
                    sSelectedActIndex = i;
                    break;
                }
                starIndexCounter--;
            }
        }
    } else {
        // If all stars are collected then they are all selectable.
        handle_menu_scrolling(MENU_SCROLL_HORIZONTAL, &sSelectableStarIndex, 0, sVisibleStars - 1);
        sSelectedActIndex = sSelectableStarIndex;
    }
    // Star selector type handler
    for ((i = 0); (i < sVisibleStars); (i++)) sStarSelectorModels[i]->oStarSelectorType = ((sSelectedActIndex == i) ? STAR_SELECTOR_SELECTED : STAR_SELECTOR_NOT_SELECTED);
}

/**
 * Print the course number selected with the wood rgba16 course texture.
 */
#ifdef VERSION_EU
void print_course_number(s16 language) {
#else
void print_course_number(void) {
#endif
    u8 courseNum[4];
    create_dl_translation_matrix(G_MTX_PUSH, 158.0f, 81.0f, 0.0f);
    // Full wood texture in JP & US, lower part of it on EU
    gSPDisplayList(gDisplayListHead++, dl_menu_rgba16_wood_course);
#ifdef VERSION_EU
    // Change upper part of the wood texture depending of the language defined
    switch (language) {
        case LANGUAGE_ENGLISH: gSPDisplayList(gDisplayListHead++, dl_menu_texture_course_upper); break;
        case LANGUAGE_FRENCH:  gSPDisplayList(gDisplayListHead++, dl_menu_texture_niveau_upper); break;
        case LANGUAGE_GERMAN:  gSPDisplayList(gDisplayListHead++, dl_menu_texture_kurs_upper  ); break;
    }
    gSPDisplayList(gDisplayListHead++, dl_menu_rgba16_wood_course_end);
#endif
    gSPPopMatrix(  gDisplayListHead++, G_MTX_MODELVIEW);
    gSPDisplayList(gDisplayListHead++, dl_rgba16_text_begin);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
    int_to_str(gCurrCourseNum, courseNum);
    print_hud_lut_string_centered(HUD_LUT_GLOBAL, (SCREEN_CENTER_X - 4), 158, courseNum); // was ((gCurrCourseNum < 10) ? 152 : 143), 1 or 2 digit number
    gSPDisplayList(gDisplayListHead++, dl_rgba16_text_end);
}

#ifdef VERSION_JP
#define ACT_NAME_X 158
#else
#define ACT_NAME_X 163
#endif

/**
 * Print act selector strings, some with special checks.
 */
void print_act_selector_strings(void) {
#ifdef VERSION_EU
    uchar myScore[][10] = { {TEXT_MYSCORE}, {TEXT_MY_SCORE_FR}, {TEXT_MY_SCORE_DE} };
#else
    uchar myScore[]     = { TEXT_MYSCORE };
#endif
    uchar starNumbers[] = { TEXT_ZERO };
#ifdef VERSION_EU
    uchar **levelNameTbl;
    uchar *currLevelName;
    uchar **actNameTbl;
#else
    uchar **levelNameTbl = segmented_to_virtual(seg2_course_name_table);
    uchar *currLevelName = segmented_to_virtual(levelNameTbl[gCurrCourseNum - 1]);
    uchar **actNameTbl   = segmented_to_virtual(seg2_act_name_table);
#endif
    uchar *selectedActName;
#ifndef VERSION_EU
    s16 lvlNameX, actNameX;
#endif
    s8 i;
#ifdef VERSION_EU
    s16 language = eu_get_language();
#endif
    create_dl_ortho_matrix();
#ifdef VERSION_EU
    switch (language) {
        case LANGUAGE_ENGLISH:
            actNameTbl   = segmented_to_virtual(act_name_table_eu_en);
            levelNameTbl = segmented_to_virtual(course_name_table_eu_en);
            break;
        case LANGUAGE_FRENCH:
            actNameTbl   = segmented_to_virtual(act_name_table_eu_fr);
            levelNameTbl = segmented_to_virtual(course_name_table_eu_fr);
            break;
        case LANGUAGE_GERMAN:
            actNameTbl   = segmented_to_virtual(act_name_table_eu_de);
            levelNameTbl = segmented_to_virtual(course_name_table_eu_de);
            break;
    }
    currLevelName = segmented_to_virtual(levelNameTbl[gCurrCourseNum - 1]);
#endif
    // Print the coin highscore.
    gSPDisplayList(gDisplayListHead++, dl_rgba16_text_begin);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
    print_hud_my_score_coins(TRUE, (gCurrSaveFileNum - 1), (gCurrCourseNum - 1), 155, 106);
    gSPDisplayList(gDisplayListHead++, dl_rgba16_text_end);
    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);
    // Print the "MY SCORE" text if the coin score is more than 0
    if (save_file_get_course_coin_score((gCurrSaveFileNum - 1), (gCurrCourseNum - 1)) != 0) {
#ifdef VERSION_EU
        print_generic_string(95, 118, myScore[language]);
#else
        print_generic_string(102, 118, myScore);
#endif
    }
#ifdef VERSION_EU
    print_generic_string(get_str_x_pos_from_center(160, (currLevelName + 3), 10.0f), 33, currLevelName + 3);
#else
    lvlNameX = get_str_x_pos_from_center(160, (currLevelName + 3), 10.0f);
    print_generic_string(lvlNameX, 33, (currLevelName + 3));
#endif
    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);
#ifdef VERSION_EU
    print_course_number(language);
#else
    print_course_number();
#endif
    gSPDisplayList(gDisplayListHead++, dl_menu_ia8_text_begin);
    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);
    // Print the name of the selected act.
    if (sVisibleStars != 0) {
        selectedActName = segmented_to_virtual(actNameTbl[((gCurrCourseNum - 1) * 6) + sSelectedActIndex]);
#ifdef VERSION_EU
        print_menu_generic_string(get_str_x_pos_from_center(ACT_NAME_X, selectedActName, 8.0f), 81, selectedActName);
#else
        actNameX = get_str_x_pos_from_center(ACT_NAME_X, selectedActName, 8.0f);
        print_menu_generic_string(actNameX, 81, selectedActName);
#endif
    }

    // Print the numbers above each star.
    for ((i = 1); (i <= sVisibleStars); (i++)) {
        starNumbers[0] = i;
#ifdef VERSION_EU
        print_menu_generic_string(((143 - (sVisibleStars * 15)) + (i * 30)), 38, starNumbers);
#else
        print_menu_generic_string(((139 - (sVisibleStars * 17)) + (i * 34)), 38, starNumbers);
#endif
    }

    gSPDisplayList(gDisplayListHead++, dl_menu_ia8_text_end);
 }

/**
 * Geo function that Print act selector strings.
 */
Gfx *geo_act_selector_strings(s16 callContext, UNUSED struct GraphNode *node, UNUSED void *context) {
    if (callContext == GEO_CONTEXT_RENDER) print_act_selector_strings();
    return NULL;
}

/**
 * Initiates act selector values before entering a main course.
 * Also load how much stars a course has, without counting the 100 coin star.
 */
s32 lvl_init_act_selector_values_and_stars(UNUSED s32 arg, UNUSED s32 unused) {
    u8 stars              = save_file_get_star_flags((gCurrSaveFileNum - 1), (gCurrCourseNum - 1));
    sLoadedActNum         = 0;
    sInitSelectedActNum   = 0;
    sVisibleStars         = 0;
    sActSelectorMenuTimer = 0;
    sObtainedStars        = save_file_get_course_star_count((gCurrSaveFileNum - 1), (gCurrCourseNum - 1));
    // Don't count 100 coin star
    if (stars & STAR_FLAG_ACT_100_COINS) sObtainedStars--;
    return 0;
}

/**
 * Loads act selector button actions with selected act value checks.
 * Also updates objects and returns act number selected after is chosen.
 */
s32 lvl_update_obj_and_load_act_button_actions(UNUSED s32 arg, UNUSED s32 unused) {
    if (sActSelectorMenuTimer >= 11) {
        // If any of these buttons are pressed, play sound and go to course act
#ifndef VERSION_EU
        if ((gPlayer3Controller->buttonPressed & A_BUTTON)
         || (gPlayer3Controller->buttonPressed & START_BUTTON)
         || (gPlayer3Controller->buttonPressed & B_BUTTON)) {
#else
        if ((gPlayer3Controller->buttonPressed & (A_BUTTON | START_BUTTON | B_BUTTON | Z_TRIG))) {
#endif
#if defined(VERSION_JP)
            play_sound(SOUND_MENU_STAR_SOUND, gGlobalSoundSource);
#else
            play_sound(SOUND_MENU_STAR_SOUND_LETS_A_GO, gGlobalSoundSource);
#endif
#if ENABLE_RUMBLE
            queue_rumble_data(60, 70);
            queue_rumble_decay(1);
#endif
            sLoadedActNum       = ((sInitSelectedActNum >= (sSelectedActIndex + 1)) ? (sSelectedActIndex + 1) : sInitSelectedActNum);
            gDialogCourseActNum = (sSelectedActIndex + 1);
        }
    }
    area_update_objects();
    sActSelectorMenuTimer++;
    return sLoadedActNum;
}
