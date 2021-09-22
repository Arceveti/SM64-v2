#pragma once

/**
 * @file config.h
 * A catch-all file for configuring various bugfixes and other settings (maybe eventually) in SM64
 */

/********************************************************************************************************************************
 *                                                                                                                              *
 * -- Version-Specific Bug Fixes --                                                                                             *
 *                                                                                                                              *
 ********************************************************************************************************************************/
// --| Post-JP Version Nintendo Bug Fixes
/// Fixes bug where obtaining over 999 coins sets the number of lives to 999 (or -25)
#define BUGFIX_MAX_LIVES (1 || VERSION_US || VERSION_EU || VERSION_SH)
/// Fixes bug where the Boss music won't fade out after defeating King Bob-omb
#define BUGFIX_KING_BOB_OMB_FADE_MUSIC (1 || VERSION_US || VERSION_EU || VERSION_SH)
/// Fixes bug in Bob-Omb Battlefield where entering a warp stops the Koopa race music
#define BUGFIX_KOOPA_RACE_MUSIC (1 || VERSION_US || VERSION_EU || VERSION_SH)
/// Fixes bug where Piranha Plants do not reset their action state when the
/// player exits their activation radius.
#define BUGFIX_PIRANHA_PLANT_STATE_RESET (1 || VERSION_US || VERSION_EU || VERSION_SH)
/// Fixes bug where sleeping Piranha Plants damage players that bump into them
#define BUGFIX_PIRANHA_PLANT_SLEEP_DAMAGE (1 || VERSION_US || VERSION_SH)
/// Fixes bug where it shows a star when you grab a key in bowser battle stages
#define BUGFIX_STAR_BOWSER_KEY (1 || VERSION_US || VERSION_EU || VERSION_SH)
/// Fixes bug that enables Mario in time stop even if is not ready to speak
#define BUGFIX_DIALOG_TIME_STOP (1 || VERSION_US || VERSION_EU || VERSION_SH)
/// Fixes bug that causes Mario to still collide with Bowser in BITS after his defeat
#define BUGFIX_BOWSER_COLLIDE_BITS_DEAD (1 || VERSION_US || VERSION_EU || VERSION_SH)
/// Fixes bug where Bowser wouldn't reset his speed when fallen off (and adds missing checks)
#define BUGFIX_BOWSER_FALLEN_OFF_STAGE (1 || VERSION_US || VERSION_EU || VERSION_SH)
/// Fixes bug where Bowser would look weird while fading out
#define BUGFIX_BOWSER_FADING_OUT (1 || VERSION_US || VERSION_EU || VERSION_SH)


/********************************************************************************************************************************
 *                                                                                                                              *
 * -- ROM/Build Settingss --                                                                                                    *
 *                                                                                                                              *
 ********************************************************************************************************************************/

// Internal ROM name. NEEDS TO BE **EXACTLY** 20 CHARACTERS. Can't be 19 characters, can't be 21 characters. You can fill it with spaces.
// The end quote should be here:               "
#define INTERNAL_ROM_NAME "SUPERMARIO64        "

// Use 8MB RAM instead of 4MB
#define USE_EXT_RAM

// Clear RAM on boot (UltraSM64)
#define CLEARRAM

// disables 'static' in many files. Useful for debugging purposes.
#define NONSTATIC

// Unlocks FPS (not recommended for normal gameplay)
// #define UNLOCK_FPS

/********************************************************************************************************************************
 *                                                                                                                              *
 * -- Misc. Settingss --                                                                                                        *
 *                                                                                                                              *
 ********************************************************************************************************************************/

// Set this to the extended bounds mode you want, then do "make clean".
// See engine/extended_bounds.h for info.
// (anonymous_moose)
#define EXTENDED_BOUNDS_MODE 1

// Adds multiple languages to the game. Just a placeholder for the most part,
// because it only works with EU, and must be enabled with EU.
// (HackerSM64)
#define MULTILANG (0 || VERSION_EU)

/// Removes multi-language cake screen (HackerSM64)
#define EU_CUSTOM_CAKE_FIX

// Support Rumble Pak (UltraSM64)
// Currently not recommended, as it may cause random crashes.
// #define ENABLE_RUMBLE (1 || VERSION_SH)

// Goddard easter egg from Shindou (Arceveti)
#define GODDARD_EASTER_EGG


/********************************************************************************************************************************
 *                                                                                                                              *
 * -- Graphics Settings --                                                                                                      *
 *                                                                                                                              *
 ********************************************************************************************************************************/

// Screen Size Defines (UltraSM64)
#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240

// Border Height Define for NTSC Versions (UltraSM64)
#ifdef TARGET_N64
// Size of the black border at the top and bottom of the screen. You can set it to different values for console and emulator.
// There is generally no reason to have a value other than 0 for emulator. As for console, it provides a (small) performance boost.
#define BORDER_HEIGHT_CONSOLE  0
#define BORDER_HEIGHT_EMULATOR 0
#endif

// Enable widescreen (16:9) support (HackerSM64)
#define WIDE

// Skybox size modifier, changing this will add support for larger skybox images. NOTE: Vanilla skyboxes may break if you change this option. Be sure to rescale them accordingly.
// Whenever you change this, make sure to run "make -C tools clean" to rebuild the skybox tool (alternatively go into skyconv.c and change the file in any way (like adding/deleting a space) to specifically rebuild that tool).
// When increasing this, you should probably also increase the GFX pool size. (the GFX_POOL_SIZE define in src/boot/game_init.h)
// (HackerSM64)
#define SKYBOX_SIZE 1

// When this option is enabled, LODs will ONLY work on console.
// When this option is disabled, LODs will work regardless of whether console or emulator is used.
// Regardless of whether this setting is enabled or not, you can use gIsConsole to wrap your own code in a console check.
// (HackerSM64)
#define AUTO_LOD

// Disable AA (Recommended: it changes nothing on emulator, and it makes console run better)
// (HackerSM64)
// #define DISABLE_AA

// Makes the coins ia8 64x64 instead of ia16 32x32.
// Uses new ia8 textures so that vanilla coins look better.
// (HackerSM64)
#define IA8_COINS

// Higher resolution coins rotating at 30 FPS
// Overwrites IA8_COINS
// (Arceveti)
#define IA8_30FPS_COINS

// Allows Mario's shadow to be transparent on top of transparent surfaces, such as water, lava, and ice
#define FIX_SHADOW_TRANSPARENCY

// Fixes the game reading the ia8 burn smoke texture as an rgba16
#define BURN_SMOKE_FIX

// Lightweight directional lighting engine by Fazana. Intended for giving proximity and positional pointlights to small objects.
#define PUPPYLIGHTS

// Intensities for puppylights light sources:
#define PUPPYLIGHTS_GRAND_STAR_LIGHT       1600
#define PUPPYLIGHTS_STAR_LIGHT              800
#define PUPPYLIGHTS_FLAME_LIGHT             800
#define PUPPYLIGHTS_AMP_LIGHT               400
#define PUPPYLIGHTS_SMALL_EXPLOSION_LIGHT   800
#define PUPPYLIGHTS_LARGE_EXPLOSION_LIGHT  3200

// Glowing effect for Power Stars and Flames.
// The number is the size of the glow. Set to 0 to disable.
// (Arceveti)
#define STAR_GLOW 144
#define FLAME_GLOW 32

// Mario's silhouette when behind solid objects/surfaces
// Also enables new render layers, such as LAYER_ALPHA_DECAL.
// The number is the intensity of the silhouette, from 0-255.
// NOTE: The overlap between Mario's model parts is visible on certain HLE plugins.
// Also, this also disables anti-aliasing on Mario, and the outermost pixel edges of the silhouette are slightly visible on Mario's normal model at lower resolutions.
// (Frame#5375, Axollyon, AloXado320, Wiseguy, Arceveti)
#define SILHOUETTE 127

// Use 64x64 quarter shadow textures instead of 16x16 (Arceveti)
#define HD_SHADOW

// Animate Bowser 3's rainbow effect (Arceveti)
#define RAINBOW_BOWSER

// Allows for the in-game FoV to be changed
// If Puppycam is enabled, it will be an option in the menu.
// (Arceveti)
#define CUSTOM_FOV
// Default FoV percentage
#define DEFAULT_FOV_PERCENT 100

// Overlay effects (Arceveti)
// - Red flash when damaged
// - Yellow flash when shocked
#define DAMAGE_SCREEN_TINT
// - Blueish tint when underwater
// - Greenish tint when in toxic gas
// - Sand color fills the screen when under quicksand
#define ENVIRONMENT_SCREEN_TINT
// - Lava color tint specifically for inside the LLL volcano (requires ENVIRONMENT_SCREEN_TINT)
#define LLL_VOLCANO_TINT

// Read the framebuffer to the metal cap texture to make it look reflective (mks#2512, Rovert, Arceveti)
#define METAL_CAP_REFLECTION
// - Overlay a shine texture over the metal cap texture (Arceveti)
#define METAL_CAP_REFLECTION_SHINE
// - Make the metal cap reflection grayscale so it looks like metal instead of glass (Arceveti)
#define METAL_CAP_REFLECTION_GRAYSCALE
// - Draw a lakitu sprite in the metal cap reflection when in first person mode to cover up the duplicate Mario
// - METAL_CAP_REFLECTION_GRAYSCALE is recommended because
// - the lakitu sprite is an ia8 for the cloud's transparency
// - (Arceveti)
#define METAL_CAP_REFLECTION_LAKITU

// Default texture filtering method:
// - G_TF_POINT     Point sampling mode, basically Minecraft textures.
// - G_TF_AVERAGE   Averages the surrounding texels.
// - G_TF_BILERP    Bilinear interpolation on the surrounding texels, default.
#define G_TF_DEFAULT    G_TF_BILERP

/********************************************************************************************************************************
 *                                                                                                                              *
 * -- Audio Settings --                                                                                                         *
 *                                                                                                                              *
 ********************************************************************************************************************************/

// Increase audio heap size to allow for more concurrent notes to be played and for more custom sequences/banks to be imported.
// Does nothing with EU and SH versions
// (HackerSM64)
#define EXPAND_AUDIO_HEAP

// Use a much better implementation of reverb over vanilla's fake echo reverb. Great for caves or eerie levels, as well as just a better audio experience in general.
// Reverb parameters can be configured in audio/synthesis.c to meet desired aesthetic/performance needs. Currently US/JP only.
// (HackerSM64)
// #define BETTER_REVERB


/********************************************************************************************************************************
 *                                                                                                                              *
 * -- Vanilla Level/Cutscene Settings --                                                                                        *
 *                                                                                                                              *
 ********************************************************************************************************************************/

// Uncomment this if you want to skip the title screen (Super Mario 64 logo)
// (HackerSM64)
// #define SKIP_TITLE_SCREEN

// Skip peach letter cutscene (HackerSM64)
// #define SKIP_PEACH_LETTER_CUTSCENE

// Uncomment this if you want to keep the Mario head and not skip it (HackerSM64)
#define KEEP_MARIO_HEAD

// Disables the demo that plays when idle on the start screen (Arceveti)
#define DISABLE_DEMO

// Fixes the castle music sometimes triggering after getting a dialog (HackerSM64)
#define FIX_CASTLE_MUSIC

// Fixes various "impossible" coin locations throughout the gane (Arceveti)
#define FIX_IMPOSSIBLE_COINS

// Fixes the 1ups in the CCM slide shortcut (Arceveti)
#define FIX_CCM_SLIDE_1UPS

// Fixes Lakitu cutscene detection bounds
#define FIX_LAKITU_SKIP

// Makes the WF star spawn from the wall instead of existing already (AdyaGD)
#define FIX_CANNONLESS

// Re-implements and fixes unused SSL pillars cutscene
// (SunlitSpace542, AloXado320/AloYuisabelle, Arceveti)
#define SSL_PILLARS_CUTSCENE

// Re-implements cracked ice in SL (SunlitSpace542, Arceveti)
#define DEEP_FREEZE_CRACKED_ICE

// Adds a visual moving water current to the warp behind the Bowser's Sub door in DDD (Arceveti)
#define DDD_WARP_CURRENT_TEXTURE

// Disables the ambient rising/lowering water level in WDW and areas with a variable water level,
// since it can cause subtle nausea.
// (Arceveti)
#define WDW_DISABLE_AMBIENT_WAVES

// Use painting data for the PSS painting instead of a static texture (Arceveti)
// TODO: Painting Wobble
#define PSS_PAINTING

// Adds a few extra objects to some levels
// Mainly Recovery Hearts, 1-Ups, & Cap Boxes
// (Arceveti)
#define BONUS_OBJECTS

// Min/max pairs for fog
#define HMC_FOG_MIN          980 // vanilla is 960
#define HMC_FOG_MAX         1000
#define BOB_FOG_MIN          980
#define BOB_FOG_MAX         1000
#define JRB_FOG_MIN          900
#define JRB_FOG_MAX         1000
#define TTC_FOG_MIN          970 // vanilla is 900
#define TTC_FOG_MAX         1000
#define INF_STAIRS_FOG_MIN   950
#define INF_STAIRS_FOG_MAX  1000
#define PSS_FOG_MIN          980
#define PSS_FOG_MAX         1000
#define COTMC_FOG_MIN        980
#define COTMC_FOG_MAX       1000
#define TTM_SLIDE_FOG_MIN    980
#define TTM_SLIDE_FOG_MAX   1000
#define BOWSER_2_FOG_MIN     960
#define BOWSER_2_FOG_MAX    1000
// This isn't gsSPFogPosition since there is no valid min/max pair that corresponds to 0x0E49F2B7
#define SSL_PYRAMID_FOG_FM  0x0E49
#define SSL_PYRAMID_FOG_FO  0xF2B7
 //! This isn't gsSPFogPosition since there is no valid min/max pair that corresponds to 0x0855F8AB
#define LLL_VOLCANO_FOG_FM  0x0855
#define LLL_VOLCANO_FOG_FO  0xF8AB

/********************************************************************************************************************************
 *                                                                                                                              *
 * -- Optimizations --                                                                                                          *
 *                                                                                                                              *
 ********************************************************************************************************************************/

// Set more object types to use "OBJ_LIST_UNIMPORTANT" so they can be unloaded when needed (Arceveti)
#define UNIMPORTANT_OBJECTS

// geo_switch_room always uses Mario's floor instead of looking for intangible floors.
// when this is disabled, the game will still only try to find a new floor if there is
// an intangible floor in the current cell
// #define SWITCH_ROOM_ALWAYS_USES_MARIO_FLOOR

// Use the floor's normal instead of a triangle of find_floor if the floor isn't steep (Arceveti)
#define FAST_FLOOR_ALIGN


/********************************************************************************************************************************
 *                                                                                                                              *
 * -- Hacker QoL --                                                                                                             *
 *                                                                                                                              *
 ********************************************************************************************************************************/

// TEST LEVEL (HackerSM64)
// Uncomment this define and set a test level in order to boot straight into said level.
// This allows you to quickly test the level you're working on.
// If you want the game to boot normally, just comment out the define again.
// #define TEST_LEVEL LEVEL_CASTLE

// Number of possible unique model ID's (keep it higher than 256)
#define MODEL_ID_COUNT 256

// Number of supported areas per level.
#define AREA_COUNT 8

// Custom debug mode. Press DPAD left to show the debug UI. Press DPAD right to enter the noclip mode. (HackerSM64)
// #define CUSTOM_DEBUG

// Include Puppyprint, a display library for text and large images.
// Also includes a custom, enhanced performance profiler.
// (FazanaJ, HackerSM64)
#define PUPPYPRINT
#define PUPPYPRINT_DEBUG 1

// Visual debug enables some collision visuals.
// Tapping Right on the dpad will cycle between visual hitboxes, visual surfaces, both, and neither.
// If puppyprint is enabled, then this can be cycled only while the screen is active. (HackerSM64)
#define VISUAL_DEBUG

// Enable debug level select (doesn't work if Goddard is skipped)
#define DEBUG_LEVEL_SELECT

// Open all courses and doors. Used for debugging purposes to unlock all content.
#define UNLOCK_ALL

// Enable debug info with info for velocity and info for floors/ceilings/walls
// [COMPLETE_EN_US_SEGMENT2 is recommended]
// (Arceveti)
// #define DEBUG_INFO

// Debug Free Move by pressind Dpad up (Arceveti)
#define ENABLE_DEBUG_FREE_MOVE

// Enables sSegmentROMTable (Arthurtilly?)
#define SEGMENT_ROM_TABLE


/********************************************************************************************************************************
 *                                                                                                                              *
 * -- HUD Settingss --                                                                                                          *
 *                                                                                                                              *
 ********************************************************************************************************************************/

// Disable exit course (HackerSM64)
// #define DISABLE_EXIT_COURSE

// Decides which level "exit course" takes you to (has no effect if you disable exit course)
#define EXIT_COURSE_LEVEL LEVEL_CASTLE
// Decides the area node "exit course" takes you to (has no effect if you disable exit course)
#define EXIT_COURSE_AREA 0x01
// Decides the warp node "exit course" takes you to (has no effect if you disable exit course)
#define EXIT_COURSE_NODE 0x1F

// Disable lives and hide the lives counter (HackerSM64)
// #define DISABLE_LIVES

// Save number of lives to the save file (Arceveti)
#define SAVE_NUM_LIVES
// The number of lives Mario starts with after a game over or starting the game for the first time.
#define DEFAULT_NUM_LIVES 4
// This can be 0..127
#define MAX_NUM_LIVES   100
// This can be 0..32767
#define MAX_NUM_COINS   999

// Include the English characters that were missing from US segment2 (J, Q, V, X, Z, ¨, !, !!, ?, &, %, ., and the beta key) [MAKE SURE TO ALSO BUILD FROM JP/SH AND EU TO OBTAIN THE ASSETS]
// #define COMPLETE_EN_US_SEGMENT2

// Include the backup missing segment2 characters.
// This does not require building from the other ROM versions
// (Arcevet)
#define BACKUP_SEGMENT2

// Air/Breath meter is separate from health meter when underwater (Arceveti)
#define BREATH_METER

// Display number of Red Coins collected on the HUD (Arceveti)
#define HUD_RED_COINS

// Display number of Secrets collected on the HUD [COMPLETE_EN_US_SEGMENT2 is recommended] (Arceveti)
#define HUD_SECRETS

// Adds leading zeroes to the counters on the HUD (Arceveti)
#define HUD_LEADING_ZEROES

// Show Bowser Key on the castle pause menu
#define PAUSE_BOWSER_KEYS


/********************************************************************************************************************************
 *                                                                                                                              *
 * -- Camera Settingss --                                                                                                       *
 *                                                                                                                              *
 ********************************************************************************************************************************/

// Mario's eye height for the camera
// Vanilla is 125.0f
#define CAMERA_Y_OFFSET 125.0f

// Enables "parallel lakitu camera" or "aglab cam" which lets you move the camera smoothly with the dpad (HackerSM64)
// #define PARALLEL_LAKITU_CAM

// Remove course specific camera processing (HackerSM64)
#define CAMERA_FIX

// Enables Puppy Camera 2, a rewritten camera that can be freely configured and modified. (FazanaJ, HackerSM64)
#define PUPPYCAM

// The camera will center on the bomb you're looking at while spinning Bowser
// Requires PUPPYCAM
// (Arceveti)
#define BOWSER_BOMB_FOCUS

// The camera noclips through surfaces
// Requires PUPPYCAM
// (Arceveti)
// #define CAMERA_NOCLIP

// Slightly modified version of Reonu Cam 3 (Reonu)
// #define REONU_CAM_3

// Camera approaches Mario's height much more quickly (Reonu)
// #define FAST_VERTICAL_CAMERA_MOVEMENT


/********************************************************************************************************************************
 *                                                                                                                              *
 * -- Object Behavior Settingss --                                                                                              *
 *                                                                                                                              *
 ********************************************************************************************************************************/

// Stars don't kick you out of the level (HackerSM64)
// #define NON_STOP_STARS

// Uncomment this if you want global star IDs
// Useful for creating an open world hack ala MVC
// (HackerSM64)
// #define GLOBAL_STAR_IDS

// Number of coins to spawn the "100 coin" star.
// If you remove the define altogether, then there won't be a 100 coin star at all.
// (HackerSM64)
#define X_COIN_STAR 100

// Fix instant warp offset not working when warping across different areas (HackerSM64)
#define INSTANT_WARP_OFFSET_FIX

// Whether a tree uses snow particles or not is decided via the model IDs instead of the course number (HackerSM64)
#define TREE_PARTICLE_FIX

// Increase the maximum pole length (it will treat bparam1 and bparam2 as a single value) (HackerSM64)
#define LONGER_POLES

// Makes signs and NPCs easier to talk to (Arceveti)
#define EASIER_DIALOG_TRIGGER

// Show an "A" when Mario is able to talk [requires EASIER_DIALOG_TRIGGER] (Arceveti)
#define DIALOG_INDICATOR

// Fade warps have a particle effect to show where they are (Arceveti)
#define VISIBLE_FADE_WARPS

// Step height for objects. (Arceveti)
#define OBJ_STEP_HEIGHT 40.0f

// Fix DDD water rings (Arceveti)
#define FIX_WATER_RINGS

// Fix bomb clip
#define FIX_BOMB_CLIP

// Collecting a 1-Up Mushroom will fully heal Mario (Arceveti)
#define MUSHROOMS_HEAL

// Collecting a Power Star will fully heal Mario (Arceveti)
#define POWER_STARS_HEAL

// Koopa Shell boxes respawn (Arceveti)
#define KOOPA_SHELL_BOXES_RESPAWN

// The speed of a platform on a track can be controlled by standing near the front or back of it (Arceveti)
#define CONTROLLABLE_PLATFORM_SPEED

// Allows for retries on collecting the remaining blue coins from a blue coin switch (Arceveti)
#define BLUE_COIN_SWITCH_RETRY

// Unagi's and Klepto's star becomes transparent after it's collected like other stars (SunlitSpace542)
#define HELD_TRANSPARENT_STAR

// Clams don't hurt Mario unless they are moving (opening/closing) (Arceveti)
#define CLAMS_ONLY_HURT_WHEN_MOVING

// Moving Coins flicker and disappear when they hit lava instead of being instantly deleted (Arceveti)
#define COIN_LAVA_FLICKER

// Tiny Goombas (from THI) always drop their coin (Arceveti)
#define TINY_GOOMBA_ALWAYS_DROPS_COIN

// Leaf particles occasionally fall from trees which contain Hoot (Arceveti)
#define HOOT_TREE_PARTICLES

// Reimplement the unused sad eye texture for the mother penguin
#define PENGUIN_MOTHER_SAD_EYES

// Makes bowser throws more lenient
// (Arceveti)
#define LENIENT_BOWSER_THROWS

// The number of chain balls the Chain Chomp has
// Vanilla is 5
// Arceveti
#define CHAIN_CHOMP_NUM_PARTS 5

// The number of parts Pokey has, including the head
// Vanilla is 5, max is 30
// (Arceveti)
#define POKEY_NUM_PARTS       5

// The number of segments Wiggler has, not including the head
// Vanilla is 4. Visual bugs start appearing in the pause menu at about 20ish,
// in-game at about 24ish, and crashes at about 28ish or higher.
// (Arceveti)
#define WIGGLER_NUM_SEGMENTS  4


/********************************************************************************************************************************
 *                                                                                                                              *
 * -- Collision Settingss --                                                                                                    *
 *                                                                                                                              *
 ********************************************************************************************************************************/

// Collision data is the type that the collision system uses. All data by default is stored as an s16, but you may change it to s32.
// Naturally, that would double the size of all collision data, but would allow you to use 32 bit values instead of 16.
// Rooms are s8 in vanilla, but if you somehow have more than 255 rooms, you may raise this number.
// Currently, they *must* say as u8/s8, because the room tables generated by literally anything are explicitly u8 and don't use a macro, making this currently infeasable.
#define COLLISION_DATA_TYPE s16
#define ROOM_DATA_TYPE      s8

// Automatically calculate the optimal collision distance for an object based on its vertices.
#define AUTO_COLLISION_DISTANCE

// Platform displacement 2 also known as momentum patch.
// Makes Mario keep the momemtum from moving platforms.
// Doesn't break treadmills anymore!
// (Arthurtilly, HackerSM64)
#define PLATFORM_DISPLACEMENT_2

// Allow all surfaces types to have force.
// Doesn't require setting force, just allows it to be optional.
// (HackerSM64)
#define ALL_SURFACES_HAVE_FORCE

// Water surfaces (Thecozies)
#define NEW_WATER_SURFACES

// Vertical quicksand support (Wiseguy)
#define WALL_QUICKSAND

// Detect Mario's collision with lava regardless of action (Arceveti)
#define FIX_LAVA_INTERACTION

// Number of walls that can push Mario at once. (vanilla is 4, higher is recommended)
#define MAX_REFEREMCED_WALLS 16

// Push Mario out of sloped ceilings instead of stopping or bonking
// helps prevent unwanted bonks and softlocks
// (Arceveti)
#define BETTER_CEILING_HANDLING

// Include steep floors when checking for walls when underwater
// This fixes the weirdness caused by swimming into such slopes (as seen with the JRB pillars in vanilla)
// May cause performance issues when underwater due to also iterating through the floors partition
// in addition to the regular walls partition when checking wall collisions.
// (Arceveti)
#define UNDERWATER_STEEP_FLOORS_AS_WALLS
#define MIN_UNDERWATER_FLOOR_NORMAL_Y 0.1f

// Minimum Y normal for floors (vanilla is 0.01f)
#define MIN_FLOOR_NORMAL_Y 0.02f

// Minimum Y normal for ceilings (vanilla is -0.01f, -0.2f is recommended)
#define MAX_CEIL_NORMAL_Y -0.2f


/********************************************************************************************************************************
 *                                                                                                                              *
 * -- Movement Settingss --                                                                                                     *
 *                                                                                                                              *
 ********************************************************************************************************************************/


/****************************************************************
 * Movement: General                                            *
 ****************************************************************/

// Increasses the subframe step count the faster Mario is moving
// (Arceveti)
#define VARIABLE_STEPS

// Decides whether you can exit course while moving
// Has no effect if you disable exit course)
// (HackerSM64)
#define EXIT_COURSE_WHILE_MOVING

// Lets Mario transition from more actions to more other actions (Arceveti)
#define ACTION_CANCELS

// Enables the shindou pole fix and allows Mario to
// swing around poles when grabbing them (Arceveti)
#define POLE_SWING

// Mario can move sideways on ledges (Arceveti)
#define LEDGE_SIDLE

// Mario's squish scale is smooth rather than being instantly set (Arceveti)
#define SMOOTH_SQUISH

// Change the movement speed when hanging from a ceiling (the vanilla value is 4.0f)
// (HackerSM64)
#define HANGING_SPEED 12.0f

// Makes Mario face the direction of the analog stick directly while hanging from a ceiling, without doing "semicircles" (HackerSM64)
// #define TIGHTER_HANGING_CONTROLS

// Improved hanging which doesn't require holding down the A button (Arceveti)
#define EASIER_HANGING

// Number of steps before Mario falls off a ledge.
// This allows Mario to walk over small gaps,
// and also helps prevent ledge jittering
// (Arceveti)
#define COYOTE_TIME      16

// Number of null floors to check ahead through during a qstep.
// Fixes many instances of invisible walls but may cause minor
// issues on actual level boundaries, such as extra knockback
// (Arceveti)
#define NULL_FLOOR_STEPS 4

// Mario hitbox values
// Vanilla is 160.0f
#define MARIO_HITBOX_HEIGHT         160.0f
#define MARIO_HALF_HITBOX_HEIGHT    (MARIO_HITBOX_HEIGHT / 2.0f)

// Mario's hitbox height when in certain actions, such as crouching
#define MARIO_SHORT_HITBOX_HEIGHT   100.0f

#define MARIO_HANGING_HITBOX_HEIGHT (MARIO_HITBOX_HEIGHT - 16.0f)

// The amount Mario will be able to be warped up/down onto a floor when walking onto it
#define MARIO_STEP_HEIGHT           (MARIO_HITBOX_HEIGHT / 4.0f)

// Terminal velovity for gravity (75.0f is default) (Arceveti)
#define TERMINAL_GRAVITY_VELOCITY   75.0f


/****************************************************************
 * Movement: Ground                                             *
 ****************************************************************/

// Number of ground steps per frame (Vanilla is 4)
#define GROUND_NUM_STEPS 4

// Disable BLJs and crush SimpleFlips's dreams (HackerSM64)
// #define DISABLE_BLJ

// Allows Mario to jump kick on steep surfaces that are set to be non slippery, instead of being forced to dive (HackerSM64)
#define JUMP_KICK_FIX

// Fixes Mario's turn radius by making it dependent on forward speed. (Arceveti)
#define FIX_GROUND_TURN_RADIUS

// Prevent bonks when walking into a wall (Arceveti)
#define LESS_GROUND_BONKS

// Threshold for whether Mario is walking "fast" (Arceveti)
// Vanilla is 16.0f
#define GROUND_SPEED_THRESHOLD   10.0f
// Vanilla is 10.0f
#define GROUND_SPEED_THRESHOLD_2 10.0f

// The minimum forward speed Mario should be moving to dive instead of punch
// Vanilla is 29.0f
#define GROUND_DIVE_THRESHOLD  24.0f

// Diving is based on the analog stick magnitude instead of Mario's speed (Arceveti)
// #define SUPER_RESPONSIVE_GROUND_DIVE

// Perform ground steps while standing still. This fixes several bugs. (Arceveti)
#define STATIONARY_GROUND_STEPS

// Uses the relative angles of Mario's slope rather than surface normals
// This allows Mario to properly walk laterally across floor surfaces.
// STATIONARY_GROUND_STEPS is recommended
// (Arceveti)
#define FIX_RELATIVE_SLOPE_ANGLE_MOVEMENT

// Optimizes sidling a wall while on a slope (Arceveti)
#define FIX_WALL_SIDLE_SLOPE

// Faster Crouching animation (Arceveti)
#define FAST_CROUCHING

// Makes it slightly easier to stay on narrow platforms (Arceveti)
#define LEDGE_PROTECTION


/****************************************************************
 * Movement: Airborne                                           *
 ****************************************************************/

// Number of air steps per frame (Vanilla is 4)
#define AIR_NUM_STEPS    4

// Disables the scream that Mario makes when falling off a great height.
// This is separate from actual fall damage
// (HackerSM64)
// #define NO_FALL_DAMAGE_SOUND

// Vanilla is 1150.0f
#define FALL_DAMAGE_HEIGHT_SMALL 1200.0f
// Vanilla is 3000.0f
#define FALL_DAMAGE_HEIGHT_LARGE 3000.0f

// Disables fall damage
// Overwrites the above values
// (HackerSM64)
#define NO_FALL_DAMAGE

// Disables Mario getting stuck in snow and sand when falling
// #define NO_GETTING_BURIED

// Allows for turning in midair (Arceveti)
// #define AIR_TURN

// The minimum forward speed Mario should be moving to dive instead of kick in midair
// Vanilla is 28.0f
#define AIR_DIVE_THRESHOLD 24.0f

// Diving is based on the analog stick magnitude instead of Mario's speed (Arceveti)
// #define SUPER_RESPONSIVE_AIR_DIVE

// Mario's falling speed affects his horizontal movement speed.
// This makes Mario's falling feel more realistic, but might occasionally feel restrictive.
// This only has an effect if AIR_TURN is enabled.
// (Arceveti)
// #define GRAVITY_DRAG
// Use intendedYaw to control Hoot instead of raw left and right inputs (Arceveti)
#define HOOT_YAW_FIX

// The last frame that will be considered a firsty when wallkicking (HackerSM64)
#define FIRSTY_LAST_FRAME 1

// Wallkick/wallslide angle in degrees
// Vanilla is 45
// (Arceveti)
#define WALL_KICK_DEGREES 67.5

// Unique wall slide which takes horizontal momentum into account
// Overwrites FIRSTY_LAST_FRAME
// WALL_KICK_DEGREES 67.5 is recommended
// (Arceveti)
#define WALL_SLIDE

// Hold A when bouncing on an enemy to go higher (Arceveti)
#define BOUNCE_BOOST

// Hold Z while twirling to descend faster (Arceveti)
#define Z_TWIRL

// Don't fall after star grab if the floor is too far below (Arceveti)
#define AIR_STAR_DANCE

// Ground pound dive similar to SMO, can also be used to cancel
// a ground pound if the analog stick is held back (Arceveti)
#define GROUND_POUND_JUMP

// Ground pound jump similar to SMO (Unknown)
#define GROUND_POUND_DIVE

// Do air steps while ground pounding
// This preventing stuff like clipping through whomps,
// but still isn't enough in some cases
// (Arceveti)
#define GROUND_POUND_AIR_STEP

// Prevents bonks when ground pounding next to a wall (Arceveti)
#define GROUND_POUND_WALL_FIX

// Allow Mario to grab hangable ceilings from any state (HackerSM64)
#define HANGING_FIX


/****************************************************************
 * Movement: Submerged                                          *
 ****************************************************************/

// Number of swimming steps per frame (Vanilla is 1)
#define WATER_NUM_STEPS  4

// Maximum swimming speed (vanilla is 28.0f, 32.0f is recommended)
#define MAX_SWIMMING_SPEED 32.0f

// Underwater Ground pound similar to SMO (Unknown)
#define WATER_GROUND_POUND

// Makes jumping out of water easier (Arceveti)
#define BETTER_WATER_JUMP

// Makes the underwater koopa shell action last forever until the player cancels it (Arceveti)
#define INFINITE_WATER_SHELL

// Makes the pitch change when hitting the floor underwater smooth instead of instant (Arceveti)
#define SMOOTH_WATER_FLOOR_PITCH


/********************************************************************************************************************************
 *                                                                                                                              *
 * -- Experimental/Unfinished Settingss --                                                                                      *
 *                                                                                                                              *
 ********************************************************************************************************************************/

// Don't prevent Mario from going out of bounds
// #define ALLOW_OOB

// Variable Framerate (Fazana)
//! Not compatible with KEEP_MARIO_HEAD
//! Completely broken now, lol
// #define VARIABLE_FRAMERATE

// Align mario to the floor
// Requires FAST_FLOOR_ALIGN
// #define FLOOR_ALIGNMENT

// Platform Displacement 2 for objects other than Mario & Bowser
//! Moves or doesn't move certain objects at the wrong times, such as amps, boos, and coins
// #define PLATFORM_DISPLACEMENT_2_OBJECTS

// Fixes the guLookAtReflect call in geo_process_master_list_sub
//! Since vanilla's environment mapped textures are sideways, they will appear as sideways in-game if this is enabled.
// #define FIX_REFLECT_MTX

// Fixes the inverse Z values in offset_rotated and other functions in camera.c
//! Need to check every cutscene in the game for this lol
// #define FIX_CAMERA_OFFSET_ROTATED

// In vanilla, the skybox FOV is always 90 degrees.
//! FoV seems to control skybox rotation due to how skyboxes are set up
// #define UNLOCK_SKYBOX_FOV

// Not yet implemented
// #define RAYCAST_COLLISION

// Not yet implemented
// #define DYNAMIC_GRAVITY


/********************************************************************************************************************************
 *                                                                                                                              *
 * -- Compatibility safeguards. Don't mess with these unless you know what you're doing.--                                      *
 *                                                                                                                              *
 ********************************************************************************************************************************/

#ifdef IA8_30FPS_COINS
#undef IA8_COINS
#endif

#ifndef ENVIRONMENT_SCREEN_TINT
#undef LLL_VOLCANO_TINT
#endif

#ifndef METAL_CAP_REFLECTION
#undef METAL_CAP_REFLECTION_SHINE
#undef METAL_CAP_REFLECTION_GRAYSCALE
#undef METAL_CAP_REFLECTION_LAKITU
#endif

#ifdef PUPPYCAM
#undef REONU_CAM_3
#undef FAST_VERTICAL_CAMERA_MOVEMENT
#else
#undef BOWSER_BOMB_FOCUS
#undef CAMERA_NOCLIP
#endif

#ifndef EASIER_DIALOG_TRIGGER
#undef DIALOG_INDICATOR
#endif

#ifdef ALLOW_OOB
#undef NULL_FLOOR_STEPS
#define NULL_FLOOR_STEPS 0
#endif

#ifdef VARIABLE_FRAMERATE
#undef KEEP_MARIO_HEAD
#endif

#ifndef FAST_FLOOR_ALIGN
#undef FLOOR_ALIGNMENT
#endif
