#ifndef CONFIG_H
#define CONFIG_H
// ULTRASM64-EXTBOUNDS CONFIG FLAGS NEAR BOTTOM
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
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

// Border Height Define for NTSC Versions
#ifdef TARGET_N64
// Size of the black border at the top and bottom of the screen. You can set it to different values for console and emulator.
// There is generally no reason to have a value other than 0 for emulator. As for console, it provides a (small) performance boost.
#define BORDER_HEIGHT_CONSOLE 0
#define BORDER_HEIGHT_EMULATOR 0

#endif

// -- ultrasm64-extbounds specific settings --

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
// Change the movement speed when hanging from a ceiling (the vanilla value is 4.f)
#define HANGING_SPEED 12.0f
// Makes Mario face the direction of the analog stick directly while hanging from a ceiling, without doing "semicircles"
// #define TIGHTER_HANGING_CONTROLS
// Disables fall damage
#define NO_FALL_DAMAGE
// Disables the scream that mario makes when falling off a great height (this is separate from actual fall damage)
// #define NO_FALL_DAMAGE_SOUND
// Number of coins to spawn the "100 coin" star. If you remove the define altogether, then there won't be a 100 coin star at all.
#define X_COIN_STAR 100
// Platform displacement 2 also known as momentum patch. Makes Mario keep the momemtum from moving platforms. Breaks treadmills.
#define PLATFORM_DISPLACEMENT_2
// Stars don't kick you out of the level
// #define NON_STOP_STARS
// Uncomment this if you want global star IDs (useful for creating an open world hack ala MVC)
// #define GLOBAL_STAR_IDS
// Uncomment this if you want to skip the title screen (Super Mario 64 logo)
// #define SKIP_TITLE_SCREEN
// Uncomment this if you want to keep the mario head and not skip it
#define KEEP_MARIO_HEAD
// Makes the coins ia8 64x64 instead of ia16 32x32. Uses new ia8 textures so that vanilla coins look better.
#define IA8_COINS
// Enables "parallel lakitu camera" or "aglab cam" which lets you move the camera smoothly with the dpad
#define PARALLEL_LAKITU_CAM

// HACKER QOL 
// Enable widescreen (16:9) support
#define WIDE
// When this option is enabled, LODs will ONLY work on console.
// When this option is disabled, LODs will work regardless of whether console or emulator is used.
// Regardless of whether this setting is enabled or not, you can use gIsConsole to wrap your own code in a console check.
#define AUTO_LOD
// Increase the maximum pole length (it will treat bparam1 and bparam2 as a single value)
#define LONGER_POLES
// Disable AA (Recommended: it changes nothing on emulator, and it makes console run better)
#define DISABLE_AA
// Allows Mario to ledgegrab sloped floors
#define NO_FALSE_LEDGEGRABS
// Number of possible unique model ID's (keep it higher than 256)
#define MODEL_ID_COUNT 256
// Increase audio heap size to allow for more concurrent notes to be played and for more custom sequences/banks to be imported (does nothing with EU and SH versions)
#define EXPAND_AUDIO_HEAP

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
// Skybox size modifier, changing this will add support for larger skybox images. NOTE: Vanilla skyboxes may break if you change this option. Be sure to rescale them accordingly.
// Whenever you change this, make sure to run "make -C tools clean" to rebuild the skybox tool (alternatively go into skyconv.c and change the file in any way (like adding/deleting a space) to specifically rebuild that tool).
// When increasing this, you should probably also increase the GFX pool size. (the GFX_POOL_SIZE define in src/game/game_init.h)
#define SKYBOX_SIZE 1

// If you want to change the extended boundaries mode, go to engine/extended_bounds.h and change EXTENDED_BOUNDS_MODE

// -- Graphics --

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
#define ENABLE_SCREEN_TINT_EFFECTS

// -- The following require ENABLE_SCREEN_TINT_EFFECTS -- 
#ifdef ENABLE_SCREEN_TINT_EFFECTS

// - Red flash when damaged
// - Yellow flashed when shocked
#define DAMAGE_SCREEN_TINT
// - Blueish tint when underwater
// - Greenish tint when in toxic gas
#define ENVIRONMENT_SCREEN_TINT

#endif

// -- Vanilla Level Changes --

// Fixes Lakitu cutscene detection bounds
#define FIX_LAKITU_SKIP
// Makes the WF star spawn from the wall instead of existing already (Unknown)
#define FIX_CANNONLESS
// Re-implements and fixes unused SSL pillars cutscene
// (SunlitSpace542, AloXado320/AloYuisabelle, Arceveti)
#define SSL_PILLARS_CUTSCENE
// Re-implements cracked ice in SL (SunlitSpace542, Arceveti)
#define DEEP_FREEZE_CRACKED_ICE
// Adds a visual moving water current to the warp behind the Bowser's Sub door in DDD (Arceveti)
#define DDD_WARP_CURRENT_TEXTURE

// -- Bugfixes --

// Makes obj_resolve_object_collisions work consistently (Arceveti)
#define OBJ_COLLISIONS_FIX
// Fix DDD water rings (Arceveti)
#define WATER_RING_FIX
// Fix bomb clip
#define FIX_BOMB_CLIP
// Detect Mario's collision with lava regardless of action (Arceveti)
#define LAVA_FIX
// Unagi's and Klepto's star becomes transparent after it's collected like other stars (SunlitSpace542)
#define HELD_TRANSPARENT_STAR

// -- Hacker QoL --

// Enable debug level select (doesn't work if Goddard is skipped)
#define DEBUG_LEVEL_SELECT
// Enable debug info [COMPLETE_EN_US_SEGMENT2 is recommended] (Arceveti)
#define DEBUG_INFO
// Extended debug info, with more info for velocity and info for floors/ceilings/walls (Arceveti)
#define EXTENDED_DEBUG_INFO
// Debug Free Move by pressind Dpad up (Arceveti)
#define ENABLE_DEBUG_FREE_MOVE
// Vertical quicksand support (Wiseguy)
#define WALL_QUICKSAND
// Include the English characters that were missing from US segment2 (J, Q, V, X, Z, ¨, !, !!, ?, &, %, ., and the beta key) [MAKE SURE TO ALSO BUILD FROM JP/SH AND EU TO OBTAIN THE ASSETS]
#define COMPLETE_EN_US_SEGMENT2
// Terminal velovity for gravity (Arceveti)
#define TERMINAL_GRAVITY_VELOCITY 75.0f

// -- HUD/Gameplay QoL --

// Makes signs and NPCs easier to talk to (Arceveti)
#define EASIER_DIALOG_TRIGGER
// Show an "A" when Mario is able to talk [requires EASIER_DIALOG_TRIGGER] (Arceveti)
#define DIALOG_INDICATOR
// Display number of Red Coins collected on the HUD (Arceveti)
#define HUD_RED_COINS
// Display number of Secrets collected on the HUD [COMPLETE_EN_US_SEGMENT2 is recommended] (Arceveti)
#define HUD_SECRETS
// Adds leading zeroes to the counters on the HUD (Arceveti)
#define HUD_LEADING_ZEROES

// -- Object Behaviors --

// Collecting a 1-Up Mushroom will fully heal Mario (Arceveti)
#define MUSHROOMS_HEAL
// Koopa Shell boxes respawn (Arceveti)
#define KOOPA_SHELL_BOXES_RESPAWN
// The speed of a platform on a track can be controlled by standing near the front or back of it (Arceveti)
#define CONTROLLABLE_PLATFORM_SPEED
// Allows for retries on collecting the remaining blue coins from a blue coin switch (Arceveti)
#define BLUE_COIN_SWITCH_RETRY
// Clams don't hurt mario unless they are moving (opening/closing) (Arceveti)
#define CLAMS_ONLY_HURT_WHEN_MOVING
// Moving Coins flicker and disappear when they hit lava instead of being instantly deleted (Arceveti)
#define COIN_LAVA_FLICKER
// Tiny Goombas (from THI) always drop their coin (Arceveti)
#define TINY_GOOMBA_COIN
// Leaf particles fall from trees which contain Hoot (Arceveti)
#define HOOT_TREE_PARTICLES

// -- Movement --

// Hold A when bouncing on an enemy to go higher (Arceveti)
#define BOUNCE_BOOST
// Hold Z while twirling to descend faster (Arceveti)
#define Z_TWIRL
// Enables the shindou pole fix and allows Mario to swing around poles when grabbing them (Arceveti)
#define POLE_SWING
// Don't fall after star grab if the floor is too far below (Arceveti)
#define AIR_STAR_DANCE
// Number of null floors to check ahead through during a qstep.
// Fixes many instances of invisible walls but may cause minor issues on actual level boundaries
// (Arceveti)
#define NULL_FLOOR_STEPS 3
// General movement improvements, including turn circle fix,
// midair turn, better ceiling handling, less softlocks, etc.
// (Arceveti)
#define IMPROVED_MOVEMENT

// -- The following require IMPROVED_MOVEMENT --
#ifdef IMPROVED_MOVEMENT

// Lets Mario transition to more other actions (Arceveti)
#define ACTION_CANCELS
// Fixes turning around on the ground (Arceveti)
#define GROUND_TURN_FIX
// Allows for turning in midair (Arceveti)
#define AIR_TURN
// Unique wall slide which takes horizontal momentum into account (Arceveti)
#define WALL_SLIDE
// Ground pound dive similar to SMO, can also be used to cancel
// a ground pound if the analog stick is held back (Arceveti)
#define GROUND_POUND_DIVE
// Ground pound jump similar to SMO (Unknown)
#define GROUND_POUND_JUMP
// Underwater Ground pound similar to SMO (Unknown)
#define WATER_GROUND_POUND
// Number of frames before Mario falls off a ledge.
// This allows Mario to walk over small gaps
// and also helps prevent ledge jittering
// (Arceveti)
#define COYOTE_TIME 8
// Split water steps into quarter frames just like ground and air steps (Arceveti)
#define WATER_QSTEPS
// Improved hanging which doesn't require holding down the A button (Arceveti)
#define EASIER_HANGING

#endif

// -- Misc --

// Goddard easter egg from Shindou (Nintendo, Arceveti)
#define GODDARD_EASTER_EGG

// -- Experimental --

// Platform Displacement 2 for objects other than Mario & Bowser
// #define PLATFORM_DISPLACEMENT_2_OBJECTS

#endif // CONFIG_H
