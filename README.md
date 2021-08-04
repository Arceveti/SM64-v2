# SM64v2
**AFTER CLONING THE REPO, CHECK OUT THE `include/config.h` FILE BEFORE ANYTHING ELSE! IT THERE'S A LOT OF STUFF IN THIS REPO THAT CAN BE TOGGLED THERE.**

NOTE: HMC crashes when entering via debug level select unless there is input on the first frame (?). This seems to be caused by Swoops as the crash does not occur when they are removed. This crash is also present on the upstream repositories.

This repo needs gcc in order to be able to build it. To install it, run `sudo apt install gcc-mips-linux-gnu`

This is a fork of HackerSM64 by Reonu, with the following additional features, fixes, and optimizations (patches marked with `*` are toggleable in `config.h`):

**Graphics:**
- Power stars now have a glowing effect. (Arceveti) *
- 30 FPS ia8 (64x64) coins. (Arceveti) *
- Screen tint effects based on damage & environment, which can be enabled separately (Arceveti) *
- Mario's silhouette is shown when behind most surfaces (Frame#5375, Axollyon, AloXado320, Wiseguy, Arceveti) *
- Bowser 3's rainbow effect is animated (Arceveti) *
- Use 64x64 quarter shadow textures instead of 16x16 (Arceveti) *
- King Bob-omb blinks
- Reflective metal cap texture using the framebuffer (mks#2512, Rovert, Arceveti) *

**Vanilla level changes:**
- Fixed various models which had misaligned vertices/UVs (Arceveti)
- The Blast Away The Wall star spawns from the wall instead of existing in the world already *
- Re-implementation of the unused SSL pillars cutscene (SunlitSpace542, AloXado320/AloYuisabelle, Arceveti) *
- Re-implementation of the unused cracked ice in SL (SunlitSpace542, Arceveti) *
- Bowser's puzzle in LLL is now seamless (Arceveti)
- Fix for Lakitu cutscene detection bounds *
- A visual moving water current to the warp behind the Bowser door in DDD (Arceveti) *

**Bugfixes:**
- `obj_resolve_object_collisions()` now works consistently (Arceveti) *
- Fixed DDD water rings by using interaction checking (Arceveti) *
- Bomb clip fix (Arceveti) *
- Mario's collision with lava is detected regardless of his action *
- Unagi and Klepto's stars become transparent stars after they are collected (SunlitSpace542) *
- Many smaller bugs patched

**Optimizations:**
- Most doubles are now floats where the extra percision isn't needed
- Improved slope fix and exposed ceilings fix (Arceveti)
- Almost all unused code/data from the Goddard folder is removed (Arceveti)
- Some unecessary find_floor (collision) checks are removed (Arceveti)
- Optimized DDD Bowser's Submarine collision model (Arceveti)
- Many stubbed/unused/duplicate functions/variables are removed (Arceveti)
- Many smaller optimizations (Arceveti)
- [Fast inverse square root for normalizing float vectors :)](https://en.wikipedia.org/wiki/Fast_inverse_square_root) *

**Hacker QoL:**
- Many unnamed variables have been named/documented (Arceveti, AloXado320, iProgramMC)
- Many unnamed display lists and geolayouts have been named (Arceveti)
- Almost all textures have been named (Arceveti)
- Hardcoded render layers are replaced with their defines (Arceveti)
- Many object constants have been defined (Arceveti)
- New render layer (LAYER_ALPHA_DECAL) when Silhouette is enabled (Arceveti) *
- Extended debug info, with more info for velocity and info for floors/ceilings/walls (Arceveti) *
- Configurable terminal velocity for gravity (Arceveti) *
- Z Offset for billboards, used for the star glow effect (Arceveti)
- Defines for specific cos() values used through out the game, specifically for checking the Y normal of surfaces (Arceveti)
- Vertical quicksand support (Wiseguy) *
- Include the English characters that were missing from US segment2 `J, Q, V, X, Z, ¨, !, !!, ?, &, %, ., and the beta key` [MAKE SURE TO ALSO BUILD FROM JP/SH AND EU TO OBTAIN THE ASSETS] (Arceveti)*
- Extra segment2 characters/glyphs: `Red Coin, Blue Coin, Silver Coin, Minus Symbol` (Arceveti) *

**HUD/Gameplay QoL:**
- Slightly modified version of Reonu Cam 3 (Reonu, Arceveti) *
- Signs and NPCs are easier to talk to (Arceveti) *
- An "A" is shown above an object or NPC when Mario is able to talk to it (Arceveti) *
- Number of Red Coins collected is displayed on the HUD (Arceveti) *
- Number of Secrets collected is displayed on the HUD (Arceveti) *
- Leading zeroes on HUD counters like in modern Mario games (Arceveti) *

**Object Behaviors:**
- Collecting a 1-Up Mushroom will fully heal Mario (Arceveti) *
- The speed of a platform on a track can be controlled by standing near the front or back of it (Arceveti) *
- Respawning Koopa shell boxes (Arceveti) *
- Allow for retries on collecting the remaining blue coins from a blue coin switch (Arceveti) *
- Clams don't hurt mario unless they are moving (opening/closing) (Arceveti) *
- Moving Coins flicker and disappear when they hit lava instead of being instantly deleted (Arceveti) *
- Tiny Goombas (from THI) always drop their coin (Arceveti) *
- Leaf particles fall from trees which contain Hoot (Arceveti) *
- Reimplemented the unused "sad" eye texture for the mother penguin in CCM *
- Configurable amount of segments for Chain Chomp, Pokey & Wiggler (Arceveti) *

**Collision/Movement:**
- Don't fall after a star grab if the floor is too far below Mario (Arceveti) *
- Hold A when bouncing on an enemy to jump higher (Arceveti) *
- Hold Z while twirling to descend faster (Arceveti) *
- Ground pound jump similar to SMO *
- Underwater Ground pound similar to SMO *
- Platform Displacement 2 is modified to work with static objects, such as TTC Treadmills (Arceveti)
- Check past null floors for a safe floor on the other side, preventing most cases of invisible walls caused by small gaps in level geometry (Arceveti) *
- General movement improvements, including turn circle fix, midair turn, faster transitions between actions, better ceiling collision handling, less softlocks, etc. (Arceveti) *
- Water steps are split into quarter steps just like ground and air steps (Arceveti) *
- Unique wall slide which takes horizontal momentum into account (Arceveti) *
- Ground pound dive similar to SMO, but can also be used to cancel out of a ground pound if the analog stick is held back (Arceveti) *
- Coyote time, allowing Mario to walk over small gaps [or make a jump for a few frames late after walking off a ledge](https://developer.amazon.com/blogs/appstore/post/9d2094ed-53cb-4a3a-a5cf-c7f34bca6cd3/coding-imprecise-controls-to-make-them-feel-more-precise), while also preventing most cases of ledge jittering (Arceveti) *

**Misc:**
- Goddard easter egg from Shindou *

**Experimental:**
- Platform Displacement 2 for objects other than Mario & Bowser (Arceveti) *
- PSS Painting uses painting data instead of being part of the level model (Arceveti) *

# HackerSM64:

This is a fork of the ultrasm64 repo by CrashOveride which includes the following commonly used patches (patches marked with `*` are toggleable in `config.h`): 

**About Puppycam**
- Puppycam is available **on a dedicated branch**. If you want puppycam in your hack, clone the `puppycamera2` branch instead of `master`.

**Collision:**
- Slope fix and exposed ceilings fix
- No false ledgegrabs fix * 
- Jump kick fix * 
- 46 degree wallkicks * 
- Pole fix
- Possibility of disabling BLJs *
- Hanging fix (mario can grab hangable ceilings from any state, instead of only jump or double jump) *
- Increased maximum pole length (The game will read bparam1 and bparam2 together as a single value, so you can have a very long pole) *
- Platform Displacement 2 by Arthurtilly *
- Water Surface Type patch by thecozies
- Rounded corners by FramePerfection, merged by Cheezepin

**Common Hack Changes:**
- Better extended boundaries by anonymous_moose
- Mario head skip *
- Peach letter cutscene skip *
- Exit course while moving *
- Toggle to disable fall damage and the fall damage sound *
- Nonstop stars *
- Removed course-specific camera processing *
- You can increase the number of frames that you have to perform a firsty *
- Ability to set Mario's movement speed when hanging from a ceiling *
- Tighter hanging controls (mario will face the direction of the analog stick directly while hanging from a ceiling) *
- reonucam3: custom camera by me. This is included as a .patch file in the enhancements folder, you need to apply it if you want this camera.
  This video shows a rundown of the features: https://youtu.be/TQNkznX9Z3k

**Hacker QOL:**
- Global, non-level based, star IDs (off by default) *
- FPS counter (use the function `print_fps(x,y)` anywhere that runs code every frame)
- Automatic console/emulator detection. If emulator is detected, LODs are disabled. *
- Ability to configure whether there's a 100 coin star at all and how many coins are required to spawn it *
- Ability to easily change the warp that EXIT COURSE takes you to via config.h, or disable it entirely. *
- 16 bit model IDs by someone2639. This means you can have up to 65536 models (lol). You can set the maximum number of model IDs in `config.h`. 
- Apply_patch.sh improved
- Removed the ifdef hell in `file_select.c` and `ingame_menu.c`
- Added Blake's custom function for object model stuff: `obj_set_model` and `obj_has_model`
- The "far" variable is now u16, allowing you to increase the farclip (the max distance at which geometry is rendered). However, when increasing the farclip, make sure to increase the nearclip by the same ratio, or rendering will break on console and LLE plugins. 
- Many general use defines for object struct members, meant for use in custom object behaviors. Check `object_fields.h` for more info on this. (By MrComit)
- Included `actors/group0.c` in `behavior_data.c`
- The internal ROM name is now set with a define in `config.h` to make it simpler
- There is a `gIsConsole` variable that is 1 when running on console and 0 when running on emulator. This way you can wrap your code in a console check.
- Expanded audio heap allows for a larger concurrent note count and the importing of more m64 sequences and sound banks (By ArcticJaguar725) *
- You can set a test level in config.h in order to boot straight into it, so you can quickly test the level you're working on. *
- Allows all surfaces in the game to have a `force` parameter. Activating this doesn't REQUIRE you to set `force` for every surface: If you don't set, it will default to 0x0000 rather than crashing. Increases RAM usage of collision. *
- Colored ia4 text support. Format: `"@XXXXXXXX[YOUR TEXT]@--------"` (By ArcticJaguar725)
  - Example Text: `"@FF0000FFRED @00FF00FFGREEN @0000FFFFBLUE @FFFFFF00INVISIBLE @--------NORMAL"`
  - NOTE: It is not mandatory to reset the text color with `"@--------"`, but text will need to be recolored each time it scrolls in a dialog box, or the custom color will reset.

**Other Bugfixes:**
- Castle music fix (Fixes the castle music sometimes triggering after getting a dialog) *
- bparam4 fix (the game no longer uses bparam4 to check if an object is mario and therefore you can safely use it)
- Instant warp offset fix (makes the instant warp offset work even when warping to a different area) *
- haveyourcake, also known as cake screen fix. Made by Wiseguy and ported/PR'd by Cheezepin
- Tree particle fix (Whether a tree uses snow particles or not is decided via the model IDs instead of the course number) *
- Coordinate overflow fix by falcobuster. Your levels will render correctly on console and LLE emulators even when using 2x or 4x bounds, while not hurting anything on HLE plugins. *This is automatic now, you don't have to set WORLD_SCALE manually.*
- A couple vanilla texture fixes
- Smoke fix (the smoke texture uses the correct texture format)

**Neat Misc. Changes:**
- Instant Input patch by Wiseguy (Removes all input lag caused by plugins supporting framebuffer)
  - This means that you'll have to do your framebuffer effects on buffer 0 for emulator, but NOT for console. You can use the `gIsConsole` variable to check for console when doing your framebuffer effects.
- Widescreen (16:9) support toggleable by pressing `L` in the pause menu. *
- S2DEX engine by someone2639! To use it, compile with `make TEXT_ENGINE=s2dex_text_engine` or just set `TEXT_ENGINE` to `s2dex_text_engine` in the makefile.
- ia8 coins (64x64), the vanilla coin texture is upgraded to accomodate. *
- Skybox size modifier. You can have 2x, 3x and 4x size skyboxes (you can select the skybox size in `config.h`.) Please note that this might affect console performance, especially 4x mode. 2x or 3x mode is recommended if aiming for console. By CowQuack *
- You can set the black border size to different values for console and emulator. It's set to 0 by default for both. *

# UltraSM64

- This repo contains a full decompilation of Super Mario 64 (J), (U), (E), and (SH).
- Naming and documentation of the source code and data structures are in progress.
- It has been edited to allow for the usage of the final "N64 OS" library, version ``2.0L``
- Shindou Rumble Pak code is on for all regions.
- Targeting the iQue Player is supported.
- Saving to 32kbyte/256kbit SRAM is supported.
- Newer compression options are supported.
- UNFLoader (flashcart USB library) is supported, allowing for debugging on EverDrive/64Drive.
- It has been patched with someone2639's shiftable segments patch
- Wiseguy's instant input patch has been added to allow for less input lag on emulation (Does not affect console)
  This does mean that any framebuffer effects will have to be done on buffer 0 if targeting emulators
- Automatic console and emulator detection: Use the `gIsConsole` variable to wrap your code in an emulator check.
- Separate defines for emulator and console black border height.
- Getting HVQM FMV support to work with the game is WIP.

Requirements are the same as regular SM64, however a GCC MIPS cross compiler is also required. If you're on Debian-like Linux, you can use the ``gcc-mips-linux-gnu`` package. The toolchain that comes with my SDK is also supported.

## UNFLoader support

The repository supports UNFLoader for debugging.
To build with UNF, run make with ``UNF=1``.

Further instructions can be found at the [official repository](https://github.com/buu342/N64-UNFLoader)

## Multi-Save support
The repository supports SRAM in addition to EEPROM. The standard save data functions are #ifdef'd to accommedate this.
To build with SRAM support, run make with ``SAVETYPE=sram``.

I may attempt FlashRAM in the future.

## Multi-Console support
The repository supports targeting the iQue Player in addition to the N64. The iQue libultra is ***NOT*** compatible with N64 in many ways, so it is currently NOT possible to have one build for both consoles.
To target iQue, run make with the ``CONSOLE=bb`` argument.

## Compression

The repo also supports RNC (Rob Northen Compression). RNC has two methods. 

Method 1 is designed to compress as small as possible, while method 2 is designed so that decompression is as fast as possible.

Method 1 is the current default, and is the best all-rounder in terms of speed and ratio.

Both methods are fast. Method 1 has better compression than 2, so I suggest using method 1 if using RNC.

To switch to RNC, run make with either ``COMPRESS=rnc1`` or ``COMPRESS=rnc2``, depending on preferred method.

The repository also supports using DEFLATE compression. This boasts a better compression ratio, but at a slight cost to load times.

On average I'd estimate that the bottleneck on decompression is about 1-2 seconds.

To switch to gzip, run make with the ``COMPRESS=gzip`` argument.

The repo also supports gziping with ``libdeflate-gzip``. This compresses at a slightly better ratio than standard ``gzip``, with no real downside from a decompression standpoint.

To use ``libdeflate-gzip``, first clone the [repo](https://github.com/ebiggers/libdeflate), then `make` and `make install` it.

Then run make for sm64 with ``GZIPVER=libdef`` in addition to ``COMPRESS=gzip``

The repo also supports building a ROM with no compression.
This is not recommended as it increases ROM size significantly, with little point other than load times decreased to almost nothing.
To switch to no compression, run make with the ``COMPRESS=uncomp`` argument.

## FAQ

Q: Why in the hell are you bundling your own build of ``ld``?

A: Newer binutils (Like the one bundled with Ubuntu, 2.34) break linking with libultra builds due to local asm symbols.
This puts me at a crossroads of either touching leaked code and requiring GCC, or just using an older linker that works just fine.
I went with the latter.
Thanks to "someone2639" for this hacky-ass idea

Q: Will this allow me to use FlashRAM/Transfer Pak/microcode swapping/Other Cool N64 Features?

A: Theoretically, all yes.

## Installation help

Go read the original SM64 repo README.md
