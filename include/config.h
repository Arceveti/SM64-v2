#ifndef CONFIG_H
#define CONFIG_H
// HACKERSM64 CONFIG DEFINES NEAR BOTTOM
/**
 * @file config.h
 * A catch-all file for configuring various bugfixes and other settings (maybe eventually) in SM64
 */

// Bug Fixes
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
/// Removes multi-language cake screen
#define EU_CUSTOM_CAKE_FIX 1

// Support Rumble Pak
// Currently not recommended, as it may cause random crashes.
// #define ENABLE_RUMBLE (1 || VERSION_SH)

// Clear RAM on boot
#define CLEARRAM 1

// Screen Size Defines
#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240

// Border Height Define for NTSC Versions
#ifdef TARGET_N64
// Size of the black border at the top and bottom of the screen. You can set it to different values for console and emulator.
// There is generally no reason to have a value other than 0 for emulator. As for console, it provides a (small) performance boost.
#define BORDER_HEIGHT_CONSOLE  0
#define BORDER_HEIGHT_EMULATOR 0

#endif

// -- HackerSM64 specific settings --

// TEST LEVEL
// Uncomment this define and set a test level in order to boot straight into said level.
// This allows you to quickly test the level you're working on.
// If you want the game to boot normally, just comment out the define again.
// #define TEST_LEVEL LEVEL_CASTLE

// COMMON HACK CHANGES
// Internal ROM name. NEEDS TO BE **EXACTLY** 20 CHARACTERS. Can't be 19 characters, can't be 21 characters. You can fill it with spaces.
// The end quote should be here:               "
#define INTERNAL_ROM_NAME "SUPERMARIO64        "
// Disable lives and hide the lives counter
// #define DISABLE_LIVES
// Skip peach letter cutscene
#define PEACH_SKIP
// Fixes the castle music sometimes triggering after getting a dialog
#define CASTLE_MUSIC_FIX
// Remove course specific camera processing
#define CAMERA_FIX
// Change the movement speed when hanging from a ceiling (the vanilla value is 4.0f)
#define HANGING_SPEED 12.0f
// Makes Mario face the direction of the analog stick directly while hanging from a ceiling, without doing "semicircles"
// #define TIGHTER_HANGING_CONTROLS
// Disables fall damage
#define NO_FALL_DAMAGE
// Disables the scream that Mario makes when falling off a great height (this is separate from actual fall damage)
// #define NO_FALL_DAMAGE_SOUND
// Number of coins to spawn the "100 coin" star. If you remove the define altogether, then there won't be a 100 coin star at all.
#define X_COIN_STAR 100
// Platform displacement 2 also known as momentum patch. Makes Mario keep the momemtum from moving platforms. Doesn't break treadmills anymore!
#define PLATFORM_DISPLACEMENT_2
// Stars don't kick you out of the level
// #define NON_STOP_STARS
// Uncomment this if you want global star IDs (useful for creating an open world hack ala MVC)
// #define GLOBAL_STAR_IDS
// Uncomment this if you want to skip the title screen (Super Mario 64 logo)
// #define SKIP_TITLE_SCREEN
// Uncomment this if you want to keep the Mario head and not skip it
#define KEEP_MARIO_HEAD
// Enables "parallel lakitu camera" or "aglab cam" which lets you move the camera smoothly with the dpad
#define PARALLEL_LAKITU_CAM
// Allows Mario to ledgegrab sloped floors
// #define NO_FALSE_LEDGEGRABS
// Adds multiple languages to the game. Just a placeholder for the most part, because it only works with EU, and must be enabled with EU.
#define MULTILANG (0 || VERSION_EU)
// Enables Puppy Camera 2, a rewritten camera that can be freely configured and modified.
#define PUPPYCAM


// HACKER QOL
// Increase the maximum pole length (it will treat bparam1 and bparam2 as a single value)
#define LONGER_POLES
// Number of possible unique model ID's (keep it higher than 256)
#define MODEL_ID_COUNT 256
// Increase audio heap size to allow for more concurrent notes to be played and for more custom sequences/banks to be imported (does nothing with EU and SH versions)
#define EXPAND_AUDIO_HEAP
// Allow all surfaces types to have force, (doesn't require setting force, just allows it to be optional).
#define ALL_SURFACES_HAVE_FORCE
// Custom debug mode. Press DPAD left to show the debug UI. Press DPAD right to enter the noclip mode.
// #define CUSTOM_DEBUG
// Include Puppyprint, a display library for text and large images. Also includes a custom, enhanced performance profiler.
// #define PUPPYPRINT
// #define PUPPYPRINT_DEBUG 0

// BUG/GAME QOL FIXES
// Fix instant warp offset not working when warping across different areas
#define INSTANT_WARP_OFFSET_FIX
// Whether a tree uses snow particles or not is decided via the model IDs instead of the course number
#define TREE_PARTICLE_FIX
// Allows Mario to jump kick on steep surfaces that are set to be non slippery, instead of being forced to dive
#define JUMP_KICK_FIX
// Allow Mario to grab hangable ceilings from any state
#define HANGING_FIX
// The last frame that will be considered a firsty when wallkicking
#define FIRSTY_LAST_FRAME 1
// 46 degree wallkicks
#define WALLKICKS_46_DEGREES
// Disable BLJs and crush SimpleFlips's dreams
// #define DISABLE_BLJ

// RELATING TO EXIT COURSE
// Disable exit course
// #define DISABLE_EXIT_COURSE
// Decides whether you can exit course while moving (has no effect if you disable exit course)
#define EXIT_COURSE_WHILE_MOVING
// Decides which level "exit course" takes you to (has no effect if you disable exit course)
#define EXIT_COURSE_LEVEL LEVEL_CASTLE
// Decides the area node "exit course" takes you to (has no effect if you disable exit course)
#define EXIT_COURSE_AREA 0x01
// Decides the warp node "exit course" takes you to (has no effect if you disable exit course)
#define EXIT_COURSE_NODE 0x1F

// OTHER ENHANCEMENTS
// Enable widescreen (16:9) support
#define WIDE
// Skybox size modifier, changing this will add support for larger skybox images. NOTE: Vanilla skyboxes may break if you change this option. Be sure to rescale them accordingly.
// Whenever you change this, make sure to run "make -C tools clean" to rebuild the skybox tool (alternatively go into skyconv.c and change the file in any way (like adding/deleting a space) to specifically rebuild that tool).
// When increasing this, you should probably also increase the GFX pool size. (the GFX_POOL_SIZE define in src/game/game_init.h)
#define SKYBOX_SIZE 1
// When this option is enabled, LODs will ONLY work on console.
// When this option is disabled, LODs will work regardless of whether console or emulator is used.
// Regardless of whether this setting is enabled or not, you can use gIsConsole to wrap your own code in a console check.
#define AUTO_LOD
// Disable AA (Recommended: it changes nothing on emulator, and it makes console run better)
#define DISABLE_AA
// Makes the coins ia8 64x64 instead of ia16 32x32. Uses new ia8 textures so that vanilla coins look better.
#define IA8_COINS
// Use a much better implementation of reverb over vanilla's fake echo reverb. Great for caves or eerie levels, as well as just a better audio experience in general.
// Reverb parameters can be configured in audio/synthesis.c to meet desired aesthetic/performance needs.
// #define BETTER_REVERB

// If you want to change the extended boundaries mode, go to engine/extended_bounds.h and change EXTENDED_BOUNDS_MODE



/********************************************************************************************************************************
 *                                                                                                                              *
 * -- SM64v2 specific settings --                                                                                               *
 *                                                                                                                              *
 ********************************************************************************************************************************/


/****************************************************************
 * Graphics                                                     *
 ****************************************************************/

// Fixes the game reading the ia8 burn smoke texture as an rgba16
#define BURN_SMOKE_FIX

// Glowing effect on power stars (Arceveti)
#define STAR_GLOW

// Higher resolution coins rotating at 30 FPS (Arceveti)
#define IA8_30FPS_COINS

// Mario's silhouette when behind solid objects/surfaces
// Also enables new render layers
// (Frame#5375, Axollyon, AloXado320, Wiseguy, Arceveti)
#define SILHOUETTE

// Use 64x64 quarter shadow textures instead of 16x16 (Arceveti)
#define HD_SHADOW

// Animate Bowser 3's rainbow effect (Arceveti)
#define RAINBOW_BOWSER

// Overlay effects (Arceveti)
// - Red flash when damaged
// - Yellow flashed when shocked
#define DAMAGE_SCREEN_TINT
// - Blueish tint when underwater
// - Greenish tint when in toxic gas
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


/****************************************************************
 * Vanilla level changes                                        *
 ****************************************************************/

// Adds a few extra objects to some levels
// Mainly recovery hearts, 1-ups, & cap boxes
// (Arceveti)
#define BONUS_OBJECTS

// Fixes various "impossible" coin locations throughout the gane (Arceveti)
#define FIX_IMPOSSIBLE_COINS

// Fixes the 1ups in the CCM slide shortcut (Arceveti)
#define FIX_CCM_SLIDE_1UPS

// Fixes Lakitu cutscene detection bounds
#define FIX_LAKITU_SKIP

// Use painting data for the PSS painting instead of a static texture (Arceveti)
// TODO: Painting Wobble
#define PSS_PAINTING

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


/****************************************************************
 * Optimizations                                                *
 ****************************************************************/

// Set more object types to use "OBJ_LIST_UNIMPORTANT" so they can be unloaded when needed (Arceveti)
#define UNIMPORTANT_OBJECTS

// geo_switch_area always uses Mario's floor instead of looking for intangible floors.
// when this is disabled, the game will still only try to find a new floor if there is
// an intangible floor in the current cell
// #define SWITCH_AREA_ALWAYS_USES_MARIO_FLOOR
// Use fast inverse square root from Quake III
#define FAST_INVSQRT

// Use fast inverse square root for surface normals (casues some noticable issues, especially in slide levels)
// TODO: check implementation?
// #define FAST_INVSQRT_SURFACES
// Use fast inverse square root for mtxf_lookat
#define FAST_INVSQRT_MTXF_LOOKAT

// Use the floor's normal instead of a triangle of find_floor if the floor isn't steep (Arceveti)
#define FAST_FLOOR_ALIGN


/****************************************************************
 * Hacker QoL                                                   *
 ****************************************************************/

// Enable debug level select (doesn't work if Goddard is skipped)
#define DEBUG_LEVEL_SELECT

// Enable debug info with info for velocity and info for floors/ceilings/walls
// [COMPLETE_EN_US_SEGMENT2 is recommended]
// (Arceveti)
#define DEBUG_INFO

// Debug Free Move by pressind Dpad up (Arceveti)
#define ENABLE_DEBUG_FREE_MOVE

// Enables sSegmentROMTable (Arthurtilly?)
#define SEGMENT_ROM_TABLE


/****************************************************************
 * HUD                                                          *
 ****************************************************************/

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


/****************************************************************
 * Camera                                                       *
 ****************************************************************/

// Slightly modified version of Reonu Cam 3 (Reonu)
#define REONU_CAM_3

// Camera approaches Mario's height much more quickly (Reonu)
#define FAST_VERTICAL_CAMERA_MOVEMENT


/****************************************************************
 * Object behaviors                                             *
 ****************************************************************/

// Makes obj_resolve_object_collisions work consistently (Arceveti)
#define FIX_OBJ_COLLISIONS

// Makes signs and NPCs easier to talk to (Arceveti)
#define EASIER_DIALOG_TRIGGER

// Show an "A" when Mario is able to talk [requires EASIER_DIALOG_TRIGGER] (Arceveti)
#define DIALOG_INDICATOR

// Fade warps have a particle effect to show where they are (Arceveti)
#define VISIBLE_FADE_WARPS

// Step height for objects. Comment out the define to use vanilla behavior. (Arceveti)
#define OBJ_STEP_HEIGHT 32.0f

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

// Makes bowser throws more lenient (Arceveti)
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


/****************************************************************
 * Collision                                                    *
 ****************************************************************/

// Water surfaces (Thecozies)
// #define NEW_WATER_SURFACES

// Vertical quicksand support (Wiseguy)
#define WALL_QUICKSAND

// Detect Mario's collision with lava regardless of action (Arceveti)
#define FIX_LAVA_INTERACTION

// The lower wall check in ground quarter steps is unused, so this skips it (Arceveti)
// #define SKIP_GROUND_LOWER_WALL
// Improves ceiling handling, helps prevent unwanted bonks and softlocks (Arceveti)
#define BETTER_CEILING_HANDLING

// Maximum number of walls to check (vanilla is 4, higher is recommended)
#define MAX_REFEREMCED_WALLS 16

// Improved wall collision detection, with rounded corners
// Fixes Mario jittering when walking into multiple walls at once
// (frameperfection/Frame#5375)
#define BETTER_WALL_COLLISION

// Include steep floors when checking for walls when underwater
// This fixes the weirdness caused by swimming into such slopes (as seen with the JRB pillars in vanilla)
// May cause performance issues when underwater due to also iterating through the floors partition
// in addition to the regular walls partition when checking wall collisions.
// (Arceveti)
#define UNDERWATER_STEEP_FLOORS_AS_WALLS
#define MIN_UNDERWATER_FLOOR_NORMAL_Y 0.1f

// Minimum Y normal for floors (vanilla is 0.01f)
#define MIN_FLOOR_NORMAL_Y 0.01f

// Minimum Y normal for ceilings (vanilla is -0.01f, -0.2f is recommended)
#define MAX_CEIL_NORMAL_Y -0.2f


/****************************************************************
 * Movement                                                     *
 ****************************************************************/


/********************************
 * Movement - Ground            *
 ********************************/

// Fixes turning around on the ground (Arceveti)
#define GROUND_TURN_FIX

// Faster Crouching animation (Arceveti)
#define FAST_CROUCHING

// Makes it slightly easier to stay on narrow platforms (Arceveti)
#define LEDGE_PROTECTION


/********************************
 * Movement - Airborne          *
 ********************************/

// Allows for turning in midair (Arceveti)
#define AIR_TURN

// Mario's falling speed affects his horizontal movement speed.
// This makes Mario's falling feel more realistic, but might 
// occasionally feel restrictive.
// This only has an effect if AIR_TURN is enabled.
// (Arceveti)
// #define GRAVITY_DRAG
// Use intendedYaw to control Hoot instead of raw left and right inputs (Arceveti)
#define HOOT_YAW_FIX

// Unique wall slide which takes horizontal momentum into account (Arceveti)
#define WALL_SLIDE

// Hold A when bouncing on an enemy to go higher (Arceveti)
#define BOUNCE_BOOST

// Hold Z while twirling to descend faster (Arceveti)
#define Z_TWIRL

// Don't fall after star grab if the floor is too far below (Arceveti)
#define AIR_STAR_DANCE

// Fixes false ledge grabs
// Does nothing if BETTER_WALL_COLLISION is enabled.
// (Arceveti)
#define LEDGE_GRAB_FIX

// Ground pound dive similar to SMO, can also be used to cancel
// a ground pound if the analog stick is held back (Arceveti)
#define GROUND_POUND_JUMP

// Ground pound jump similar to SMO (Unknown)
#define GROUND_POUND_DIVE

// Do air steps while ground pounding, preventing stuff like clipping through whomps (Arceveti)
#define GROUND_POUND_AIR_STEP

// Prevents bonks when ground pounding next to a wall (Arceveti)
#define GROUND_POUND_WALL_FIX


/********************************
 * Movement - Submerged         *
 ********************************/

// Underwater Ground pound similar to SMO (Unknown)
#define WATER_GROUND_POUND

// Makes jumping out of water easier (Arceveti)
#define BETTER_WATER_JUMP

// Makes the underwater koopa shell action last forever until the player cancels it (Arceveti)
#define INFINITE_WATER_SHELL

// Makes the pitch change when hitting the floor underwater smooth instead of instant (Arceveti)
#define SMOOTH_WATER_FLOOR_PITCH


/********************************
 * Movement - Misc.             *
 ********************************/

// Lets Mario transition from more actions to more other actions (Arceveti)
#define ACTION_CANCELS

// Enables the shindou pole fix and allows Mario to
// swing around poles when grabbing them (Arceveti)
#define POLE_SWING

// Mario can move sideways on ledges (Arceveti)
#define LEDGE_SIDLE

// Mario's squish scale is smooth rather than being instantly set (Arceveti)
#define SMOOTH_SQUISH

// Improved hanging which doesn't require holding down the A button (Arceveti)
#define EASIER_HANGING

// Number of ground steps per frame (Vanilla is 4)
#define GROUND_NUM_STEPS 4

// Number of air steps per frame (Vanilla is 4)
#define AIR_NUM_STEPS    4

// Number of swimming steps per frame (Vanilla is 1)
#define WATER_NUM_STEPS  4

// Number of steps before Mario falls off a ledge.
// This allows Mario to walk over small gaps
// and also helps prevent ledge jittering
// (Arceveti)
#define COYOTE_TIME      16

// Number of null floors to check ahead through during a qstep.
// Fixes many instances of invisible walls but may cause minor
// issues on actual level boundaries, such as extra knockback
// (Arceveti)
#define NULL_FLOOR_STEPS 4

// Maximum swimming speed (vanilla is 28.0f, 32.0f is recommended)
#define MAX_SWIMMING_SPEED 32.0f

// Terminal velovity for gravity (75.0f is default) (Arceveti)
#define TERMINAL_GRAVITY_VELOCITY 75.0f


/****************************************************************
 * Misc.                                                        *
 ****************************************************************/

// Goddard easter egg from Shindou (Nintendo, Arceveti)
#define GODDARD_EASTER_EGG


/****************************************************************
 * Experimental/Unfinished                                       *
 ****************************************************************/

// Platform Displacement 2 for objects other than Mario & Bowser
// #define PLATFORM_DISPLACEMENT_2_OBJECTS

#endif // CONFIG_H
