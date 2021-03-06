#pragma once

#include <PR/ultratypes.h>

#include "types.h"
#include "area.h"
#include "engine/geo_layout.h"
#include "engine/graph_node.h"
#include "cutscene.h"
#ifdef PUPPYCAM
#include "puppycam2.h"
#endif

#include "level_table.h"

// X position of the mirror
// 0x875C3D = 8870973, 0x800 = 2048, 8870973 / 2048 = ~4331.52978515625
#define CASTLE_MIRROR_X ((f32)0x875C3D / 0x800)

/**
 * @file camera.h
 * Constants, defines, and structs used by the camera system.
 * @see camera.c
 */

#define LEVEL_AREA_INDEX(levelNum, areaNum) (((levelNum) << 4) + (areaNum))

/**
 * Helper macro for defining which areas of a level should zoom out the camera when the game is paused.
 * Because a mask is used by two levels, the pattern will repeat when more than 4 areas are used by a level.
 */
#define ZOOMOUT_AREA_MASK(level1Area1, level1Area2, level1Area3, level1Area4, \
                          level2Area1, level2Area2, level2Area3, level2Area4) \
    ((level2Area4) << 7 |                                                     \
     (level2Area3) << 6 |                                                     \
     (level2Area2) << 5 |                                                     \
     (level2Area1) << 4 |                                                     \
     (level1Area4) << 3 |                                                     \
     (level1Area3) << 2 |                                                     \
     (level1Area2) << 1 |                                                     \
     (level1Area1) << 0)


#define AREA_BBH                LEVEL_AREA_INDEX(LEVEL_BBH,              1)
#define AREA_CCM_OUTSIDE        LEVEL_AREA_INDEX(LEVEL_CCM,              1)
#define AREA_CCM_SLIDE          LEVEL_AREA_INDEX(LEVEL_CCM,              2)
#define AREA_CASTLE_LOBBY       LEVEL_AREA_INDEX(LEVEL_CASTLE,           1)
#define AREA_CASTLE_TIPPY       LEVEL_AREA_INDEX(LEVEL_CASTLE,           2)
#define AREA_CASTLE_BASEMENT    LEVEL_AREA_INDEX(LEVEL_CASTLE,           3)
#define AREA_HMC                LEVEL_AREA_INDEX(LEVEL_HMC,              1)
#define AREA_SSL_OUTSIDE        LEVEL_AREA_INDEX(LEVEL_SSL,              1)
#define AREA_SSL_PYRAMID        LEVEL_AREA_INDEX(LEVEL_SSL,              2)
#define AREA_SSL_EYEROK         LEVEL_AREA_INDEX(LEVEL_SSL,              3)
#define AREA_BOB                LEVEL_AREA_INDEX(LEVEL_BOB,              1)
#define AREA_SL_OUTSIDE         LEVEL_AREA_INDEX(LEVEL_SL,               1)
#define AREA_SL_IGLOO           LEVEL_AREA_INDEX(LEVEL_SL,               2)
#define AREA_WDW_MAIN           LEVEL_AREA_INDEX(LEVEL_WDW,              1)
#define AREA_WDW_TOWN           LEVEL_AREA_INDEX(LEVEL_WDW,              2)
#define AREA_JRB_MAIN           LEVEL_AREA_INDEX(LEVEL_JRB,              1)
#define AREA_JRB_SHIP           LEVEL_AREA_INDEX(LEVEL_JRB,              2)
#define AREA_THI_HUGE           LEVEL_AREA_INDEX(LEVEL_THI,              1)
#define AREA_THI_TINY           LEVEL_AREA_INDEX(LEVEL_THI,              2)
#define AREA_THI_WIGGLER        LEVEL_AREA_INDEX(LEVEL_THI,              3)
#define AREA_TTC                LEVEL_AREA_INDEX(LEVEL_TTC,              1)
#define AREA_RR                 LEVEL_AREA_INDEX(LEVEL_RR,               1)
#define AREA_CASTLE_GROUNDS     LEVEL_AREA_INDEX(LEVEL_CASTLE_GROUNDS,   1)
#define AREA_BITDW              LEVEL_AREA_INDEX(LEVEL_BITDW,            1)
#define AREA_VCUTM              LEVEL_AREA_INDEX(LEVEL_VCUTM,            1)
#define AREA_BITFS              LEVEL_AREA_INDEX(LEVEL_BITFS,            1)
#define AREA_SA                 LEVEL_AREA_INDEX(LEVEL_SA,               1)
#define AREA_BITS               LEVEL_AREA_INDEX(LEVEL_BITS,             1)
#define AREA_LLL_OUTSIDE        LEVEL_AREA_INDEX(LEVEL_LLL,              1)
#define AREA_LLL_VOLCANO        LEVEL_AREA_INDEX(LEVEL_LLL,              2)
#define AREA_DDD_WHIRLPOOL      LEVEL_AREA_INDEX(LEVEL_DDD,              1)
#define AREA_DDD_SUB            LEVEL_AREA_INDEX(LEVEL_DDD,              2)
#define AREA_WF                 LEVEL_AREA_INDEX(LEVEL_WF,               1)
#define AREA_ENDING             LEVEL_AREA_INDEX(LEVEL_ENDING,           1)
#define AREA_COURTYARD          LEVEL_AREA_INDEX(LEVEL_CASTLE_COURTYARD, 1)
#define AREA_PSS                LEVEL_AREA_INDEX(LEVEL_PSS,              1)
#define AREA_COTMC              LEVEL_AREA_INDEX(LEVEL_COTMC,            1)
#define AREA_TOTWC              LEVEL_AREA_INDEX(LEVEL_TOTWC,            1)
#define AREA_BOWSER_1           LEVEL_AREA_INDEX(LEVEL_BOWSER_1,         1)
#define AREA_WMOTR              LEVEL_AREA_INDEX(LEVEL_WMOTR,            1)
#define AREA_BOWSER_2           LEVEL_AREA_INDEX(LEVEL_BOWSER_2,         1)
#define AREA_BOWSER_3           LEVEL_AREA_INDEX(LEVEL_BOWSER_3,         1)
#define AREA_TTM_OUTSIDE        LEVEL_AREA_INDEX(LEVEL_TTM,              1)

#define CAM_MODE_MARIO_ACTIVE               (1 << 0) // 0x01
#define CAM_MODE_LAKITU_WAS_ZOOMED_OUT      (1 << 1) // 0x02
#define CAM_MODE_MARIO_SELECTED             (1 << 2) // 0x04

#define CAM_SELECTION_MARIO                 (1 << 0) // 0x01
#define CAM_SELECTION_FIXED                 (1 << 1) // 0x02

#define CAM_ANGLE_MARIO                     (1 << 0) // 0x01
#define CAM_ANGLE_LAKITU                    (1 << 1) // 0x02

#define CAMERA_MODE_NONE                    0x00
#define CAMERA_MODE_RADIAL                  0x01
#define CAMERA_MODE_OUTWARD_RADIAL          0x02
#define CAMERA_MODE_BEHIND_MARIO            0x03
#define CAMERA_MODE_CLOSE                   0x04 // Inside Castle / Big Boo's Haunt
#define CAMERA_MODE_C_UP                    0x06
#define CAMERA_MODE_WATER_SURFACE           0x08
#define CAMERA_MODE_SLIDE_HOOT              0x09
#define CAMERA_MODE_INSIDE_CANNON           0x0A
#define CAMERA_MODE_BOSS_FIGHT              0x0B
#define CAMERA_MODE_PARALLEL_TRACKING       0x0C
#define CAMERA_MODE_FIXED                   0x0D
#define CAMERA_MODE_8_DIRECTIONS            0x0E // AKA Parallel Camera, Bowser Courses & Rainbow Ride
#define CAMERA_MODE_FREE_ROAM               0x10
#define CAMERA_MODE_SPIRAL_STAIRS           0x11

#define CAM_MOVE_RETURN_TO_MIDDLE           (1 <<  0) // 0x0001
#define CAM_MOVE_ZOOMED_OUT                 (1 <<  1) // 0x0002
#define CAM_MOVE_ROTATE_RIGHT               (1 <<  2) // 0x0004
#define CAM_MOVE_ROTATE_LEFT                (1 <<  3) // 0x0008
#define CAM_MOVE_ENTERED_ROTATE_SURFACE     (1 <<  4) // 0x0010
#define CAM_MOVE_METAL_BELOW_WATER          (1 <<  5) // 0x0020
#define CAM_MOVE_FIX_IN_PLACE               (1 <<  6) // 0x0040
#define CAM_MOVE_UNKNOWN_8                  (1 <<  7) // 0x0080
#define CAM_MOVING_INTO_MODE                (1 <<  8) // 0x0100
#define CAM_MOVE_STARTED_EXITING_C_UP       (1 <<  9) // 0x0200
#define CAM_MOVE_UNKNOWN_11                 (1 << 10) // 0x0400
#define CAM_MOVE_INIT_CAMERA                (1 << 11) // 0x0800
#define CAM_MOVE_ALREADY_ZOOMED_OUT         (1 << 12) // 0x1000
#define CAM_MOVE_C_UP_MODE                  (1 << 13) // 0x2000
#define CAM_MOVE_SUBMERGED                  (1 << 14) // 0x4000
#define CAM_MOVE_PAUSE_SCREEN               (1 << 15) // 0x8000

#define CAM_MOVE_ROTATE /**/ (CAM_MOVE_ROTATE_RIGHT | CAM_MOVE_ROTATE_LEFT | CAM_MOVE_RETURN_TO_MIDDLE)
/// These flags force the camera to move a certain way
#define CAM_MOVE_RESTRICT /**/ (CAM_MOVE_ENTERED_ROTATE_SURFACE | CAM_MOVE_METAL_BELOW_WATER | CAM_MOVE_FIX_IN_PLACE | CAM_MOVE_UNKNOWN_8)

#define CAM_SOUND_C_UP_PLAYED               (1 <<  0) // 0x0001
#define CAM_SOUND_MARIO_ACTIVE              (1 <<  1) // 0x0002
#define CAM_SOUND_NORMAL_ACTIVE             (1 <<  2) // 0x0004
#define CAM_SOUND_UNUSED_SELECT_MARIO       (1 <<  3) // 0x0008
#define CAM_SOUND_UNUSED_SELECT_FIXED       (1 <<  4) // 0x0010
#define CAM_SOUND_FIXED_ACTIVE              (1 <<  5) // 0x0020

#define CAM_FLAG_SMOOTH_MOVEMENT            (1 <<  0) // 0x0001
#define CAM_FLAG_BLOCK_SMOOTH_MOVEMENT      (1 <<  1) // 0x0002
#define CAM_FLAG_FRAME_AFTER_CAM_INIT       (1 <<  2) // 0x0004
#define CAM_FLAG_CHANGED_PARTRACK_INDEX     (1 <<  3) // 0x0008
#define CAM_FLAG_CCM_SLIDE_SHORTCUT         (1 <<  4) // 0x0010
#define CAM_FLAG_CAM_NEAR_WALL              (1 <<  5) // 0x0020
#define CAM_FLAG_SLEEPING                   (1 <<  6) // 0x0040
#define CAM_FLAG_UNUSED_7                   (1 <<  7) // 0x0080
#define CAM_FLAG_UNUSED_8                   (1 <<  8) // 0x0100
#define CAM_FLAG_COLLIDED_WITH_WALL         (1 <<  9) // 0x0200
#define CAM_FLAG_START_TRANSITION           (1 << 10) // 0x0400
#define CAM_FLAG_TRANSITION_OUT_OF_C_UP     (1 << 11) // 0x0800
#define CAM_FLAG_BLOCK_AREA_PROCESSING      (1 << 12) // 0x1000
#define CAM_FLAG_UNUSED_13                  (1 << 13) // 0x2000
#define CAM_FLAG_UNUSED_CUTSCENE_ACTIVE     (1 << 14) // 0x4000
#define CAM_FLAG_BEHIND_MARIO_POST_DOOR     (1 << 15) // 0x8000

#define CAM_STATUS_NONE                     (0 <<  0) // 0x0000
#define CAM_STATUS_MARIO                    (1 <<  0) // 0x0001
#define CAM_STATUS_LAKITU                   (1 <<  1) // 0x0002
#define CAM_STATUS_FIXED                    (1 <<  2) // 0x0004
#define CAM_STATUS_C_DOWN                   (1 <<  3) // 0x0008
#define CAM_STATUS_C_UP                     (1 <<  4) // 0x0010

#define CAM_STATUS_MODE_GROUP   (CAM_STATUS_MARIO | CAM_STATUS_LAKITU | CAM_STATUS_FIXED)
#define CAM_STATUS_C_MODE_GROUP (CAM_STATUS_C_DOWN | CAM_STATUS_C_UP)

#define SHAKE_ATTACK                        0x01
#define SHAKE_GROUND_POUND                  0x02
#define SHAKE_SMALL_DAMAGE                  0x03
#define SHAKE_MED_DAMAGE                    0x04
#define SHAKE_LARGE_DAMAGE                  0x05
#define SHAKE_HIT_FROM_BELOW                0x08
#define SHAKE_FALL_DAMAGE                   0x09
#define SHAKE_SHOCK                         0x0A

#define SHAKE_ENV_EXPLOSION                 0x01
#define SHAKE_ENV_BOWSER_THROW_BOUNCE       0x02
#define SHAKE_ENV_BOWSER_JUMP               0x03
#define SHAKE_ENV_UNUSED_5                  0x05
#define SHAKE_ENV_UNUSED_6                  0x06
#define SHAKE_ENV_UNUSED_7                  0x07
#define SHAKE_ENV_PYRAMID_EXPLODE           0x08
#define SHAKE_ENV_JRB_SHIP_DRAIN            0x09
#define SHAKE_ENV_FALLING_BITS_PLAT         0x0A

#define SHAKE_FOV_SMALL                     0x01
#define SHAKE_FOV_UNUSED                    0x02
#define SHAKE_FOV_MEDIUM                    0x03
#define SHAKE_FOV_LARGE                     0x04

#define SHAKE_POS_SMALL                     0x01
#define SHAKE_POS_MEDIUM                    0x02
#define SHAKE_POS_LARGE                     0x03
#define SHAKE_POS_BOWLING_BALL              0x04

// cutscene stuff was here.

/**
 * A copy of player information that is relevant to the camera.
 */
struct PlayerCameraState
{
    /**
     * Mario's action on this frame.
     */
    /*0x00*/ MarioAction action;
    /*0x04*/ Vec3f pos;
    /*0x10*/ Vec3a faceAngle;
    /*0x16*/ Vec3a headRotation;
    /*0x1C*/ s16 unused;
    /**
     * Set to nonzero when an event, such as entering a door, starting the credits, or throwing bowser,
     * has happened on this frame.
     */
    /*0x1E*/ s16 cameraEvent;
    /*0x20*/ struct Object *usedObj;
};

/**
 * Struct containing info that is used when transition_next_state() is called. Stores the intermediate
 * distances and angular displacements from lakitu's goal position and focus.
 */
struct TransitionInfo
{
    /*0x00*/ Angle posPitch;
    /*0x02*/ Angle posYaw;
    /*0x04*/ f32   posDist;
    /*0x08*/ Angle focPitch;
    /*0x0A*/ Angle focYaw;
    /*0x0C*/ f32   focDist;
    /*0x10*/ s32   framesLeft;
    /*0x14*/ Vec3f marioPos;
    /*0x20*/ u8    pad; // for the structs to align, there has to be an extra unused variable here. type is unknown.
};

/**
 * A point that's used in a spline, controls the direction to move the camera in
 * during the shake effect.
 */
struct HandheldShakePoint
{
    /*0x00*/ s8 index; // only set to -1
    /*0x04 (aligned)*/ u32 pad;
    /*0x08*/ Vec3s point;
}; // size = 0x10

/**
 * Defines a bounding box which activates an event while Mario is inside
 */
struct CameraTrigger
{
    /**
     * The area this should be checked in, or -1 if it should run in every area of the level.
     *
     * Triggers with area set to -1 are run by default, they don't care if Mario is inside their bounds.
     * However, they are only active if Mario is not already inside an area-specific trigger's
     * boundaries.
     */
    s8 area;
    /// A function that gets called while Mario is in the trigger bounds
    CameraEvent event;
    // The (x,y,z) position of the center of the bounding box
    Vec3s center;
    // The max displacement in x, y, and z from the center for a point to be considered inside the
    // bounding box
    Vec3s bounds;
    /// This angle rotates Mario's offset from the box's origin, before it is checked for being inside.
    Angle boundsYaw;
};

/**
 * Info for the camera's field of view and the FOV shake effect.
 */
struct CameraFOVStatus
{
    /// The current function being used to set the camera's field of view (before any fov shake is applied).
    /*0x00*/ u8 fovFunc;
    /// The current field of view in degrees
    /*0x04*/ f32 fov;

    // Fields used by shake_camera_fov()

    /// The amount to change the current fov by in the fov shake effect.
    /*0x08*/ f32 fovOffset;
    /// A bool set in fov_default() but unused otherwise
    /*0x0C*/ u32 unusedIsSleeping;
    /// The range in degrees to shake fov
    /*0x10*/ f32 shakeAmplitude;
    /// Used to calculate fovOffset, the phase through the shake's period.
    /*0x14*/ s16 shakePhase;
    /// How much to progress through the shake period
    /*0x16*/ s16 shakeSpeed;
    /// How much to decrease shakeAmplitude each frame.
    /*0x18*/ s16 decay;
};

/**
 * Struct containing the nearest floor and ceiling to the player, as well as the previous floor and
 * ceiling. It also stores their distances from the player's position.
 */
struct PlayerGeometry
{
    /*0x00*/ struct Surface *currFloor;
    /*0x04*/ f32 currFloorHeight;
    /*0x08*/ SurfaceType currFloorType;
    /*0x0C*/ struct Surface *currCeil;
    /*0x10*/ SurfaceType currCeilType;
    /*0x14*/ f32 currCeilHeight;
    /*0x18*/ struct Surface *prevFloor;
    /*0x1C*/ f32 prevFloorHeight;
    /*0x20*/ SurfaceType prevFloorType;
    /*0x24*/ struct Surface *prevCeil;
    /*0x28*/ f32 prevCeilHeight;
    /*0x2C*/ SurfaceType prevCeilType;
    /// Unused, but recalculated every frame
    /*0x30*/ f32 waterHeight;
};

/**
 * Point used in transitioning between camera modes and C-Up.
 */
struct LinearTransitionPoint
{
    Vec3f focus;
    Vec3f pos;
    f32   dist;
    Angle pitch;
    Angle yaw;
};

/**
 * Info about transitioning between camera modes.
 */
struct ModeTransitionInfo
{
    s16 newMode;
    s16 lastMode;
    s16 max;
    s16 frame;
    struct LinearTransitionPoint transitionStart;
    struct LinearTransitionPoint transitionEnd;
};

/**
 * A point in a path used by update_parallel_tracking_camera
 */
struct ParallelTrackingPoint
{
    /// Whether this point is the start of a path
    s16 startOfPath;
    /// Point used to define a line segment to follow
    Vec3f pos;
    /// The distance Mario can move along the line before the camera should move
    f32 distThresh;
    /// The percentage that the camera should move from the line to Mario
    f32 zoom;
};

/**
 * Stores the camera's info
 */
struct CameraStoredInfo
{
    /*0x00*/ Vec3f pos;
    /*0x0C*/ Vec3f focus;
    /*0x18*/ f32 panDist;
    /*0x1C*/ f32 cannonYOffset;
};

/**
 * The main camera struct. Gets updated by the active camera mode and the current level/area. In
 * update_lakitu, its pos and focus are used to calculate lakitu's next position and focus, which are
 * then used to render the game.
 */
//? can areaCen be Vec3f?
struct Camera
{
    /*0x00*/ u8 mode; // What type of mode the camera uses (see defines above)
    /*0x01*/ u8 defMode;
    /**
     * Determines what direction Mario moves in when the analog stick is moved.
     *
     * @warning This is NOT the camera's xz-rotation in world space. This is the angle calculated from the
     *          camera's focus TO the camera's position, instead of the other way around like it should
     *          be. It's effectively the opposite of the camera's actual yaw. Use
     *          vec3f_get_dist_and_angle() if you need the camera's yaw.
     */
    /*0x02*/ Angle yaw;
    /*0x04*/ Vec3f focus;
    /*0x10*/ Vec3f pos;
    /*0x1C*/ Vec3f unusedVec1;
    /// The x and z coordinates of the "center" of the area. The camera will rotate around this point.
    /// For example, this is what makes the camera rotate around the hill in BoB
    /// The y coordinate of the "center" of the area. Unlike x and z, this is only used
    /// when paused. See zoom_out_if_paused_and_outside
             Vec3f areaCen;
    /*0x30*/ u8 cutscene;
    /*0x31*/ u8 filler31[0x8];
    /*0x3A*/ Angle nextYaw;
    /*0x3C*/ u8 filler3C[0x28];
    /*0x64*/ u8 doorStatus;
};

/**
 * A struct containing info pertaining to lakitu, such as his position and focus, and what
 * camera-related effects are happening to him, like camera shakes.
 *
 * This struct's pos and focus are what is actually used to render the game.
 *
 * @see update_lakitu()
 */
struct LakituState
{
    /**
     * Lakitu's position, which (when CAM_FLAG_SMOOTH_MOVEMENT is set), approaches his goalPos every frame.
     */
    /*0x00*/ Vec3f curFocus;
    /**
     * Lakitu's focus, which (when CAM_FLAG_SMOOTH_MOVEMENT is set), approaches his goalFocus every frame.
     */
    /*0x0C*/ Vec3f curPos;
    /**
     * The focus point that lakitu turns towards every frame.
     * If CAM_FLAG_SMOOTH_MOVEMENT is unset, this is the same as curFocus.
     */
    /*0x18*/ Vec3f goalFocus;
    /**
     * The point that lakitu flies towards every frame.
     * If CAM_FLAG_SMOOTH_MOVEMENT is unset, this is the same as curPos.
     */
    /*0x24*/ Vec3f goalPos;

    /*0x30*/ u8 filler30[12]; // extra unused Vec3f?

    /// Copy of the active camera mode
    /*0x3C*/ u8 mode;
    /// Copy of the default camera mode
    /*0x3D*/ u8 defMode;

    /*0x3E*/ u8 filler3E[10];

    /*0x48*/ f32 focusDistance; // unused

    /*0x4C*/ Vec3a oldAngle;

    /// The angular offsets added to lakitu's pitch, yaw, and roll
    /*0x52*/ Vec3s shakeMagnitude;

    // shake pitch, yaw, and roll phase: The progression through the camera shake (a cosine wave).
    // shake pitch, yaw, and roll vel: The speed of the camera shake.
    // shake pitch, yaw, and roll decay: The shake's deceleration.
    /*0x58*/ Angle shakePitchPhase;
    /*0x5A*/ Angle shakePitchVel;
    /*0x5C*/ Angle shakePitchDecay;

    /*0x60*/ Vec3f unusedVec1;
    /*0x6C*/ Vec3s unusedVec2;
    /*0x72*/ u8 filler72[8];

    /// Used to rotate the screen when rendering.
    /*0x7A*/ Angle roll;
    /// Copy of the camera's yaw.
    /*0x7C*/ Angle yaw;
    /// Copy of the camera's next yaw.
    /*0x7E*/ Angle nextYaw;
    /// The actual focus point the game uses to render.
    /*0x80*/ Vec3f focus;
    /// The actual position the game is rendered from.
    /*0x8C*/ Vec3f pos;

    // Shake variables: See above description
    /*0x98*/ Angle shakeRollPhase;
    /*0x9A*/ Angle shakeRollVel;
    /*0x9C*/ Angle shakeRollDecay;
    /*0x9E*/ Angle shakeYawPhase;
    /*0xA0*/ Angle shakeYawVel;
    /*0xA2*/ Angle shakeYawDecay;

    // focH,Vspeed: how fast lakitu turns towards his goalFocus.
    /// By default HSpeed is 0.8, so lakitu turns 80% of the horz distance to his goal each frame.
    /*0xA4*/ f32 focHSpeed;
    /// By default VSpeed is 0.3, so lakitu turns 30% of the vert distance to his goal each frame.
    /*0xA8*/ f32 focVSpeed;

    // posH,Vspeed: How fast lakitu flies towards his goalPos.
    /// By default they are 0.3, so lakitu will fly 30% of the way towards his goal each frame.
    /*0xAC*/ f32 posHSpeed;
    /*0xB0*/ f32 posVSpeed;

    /// The roll offset applied during part of the key dance cutscene
    /*0xB4*/ Angle keyDanceRoll;
    /// Mario's action from the previous frame. Only used to determine if Mario just finished a dive.
    /*0xB8*/ u32 lastFrameAction;
    /*0xBC*/ s16 unused;
};

// BSS
extern s16 sSelectionFlags;
extern s16 sCameraSoundFlags;
extern u16 sCButtonsPressed;
extern struct PlayerCameraState gPlayerCameraState[2];
extern struct LakituState gLakituState;
extern s16 gCameraMovementFlags;
extern s32 gObjCutsceneDone;
extern struct Camera *gCamera;

extern struct Object *gCutsceneFocus;
extern struct Object *gSecondCameraFocus;
extern u8 gRecentCutscene;

// TODO: sort all of this extremely messy shit out after the split

void set_camera_shake_from_hit(     s16 shake);
void set_environmental_camera_shake(s16 shake);
void set_camera_shake_from_point(   s16 shake, Vec3f pos);
void move_mario_head_c_up( UNUSED struct Camera *c);
void transition_next_state(UNUSED struct Camera *c,           s16 frames);
void set_camera_mode(             struct Camera *c, s16 mode, s16 frames);
void update_camera(               struct Camera *c);
void reset_camera(                struct Camera *c);
void init_camera(                 struct Camera *c);
void select_mario_cam_mode(void);
Gfx *geo_camera_main(s32 callContext, struct GraphNode *g, void *context);
Bool32 move_point_along_spline(Vec3f p, struct CutsceneSplinePoint spline[], s16 *splineSegment, f32 *progress);
s32    cam_select_alt_mode(Angle32 angle);
s32    set_cam_angle(      s32 mode);
void   set_handheld_shake(  u8 mode);
void   shake_camera_handheld(Vec3f pos, Vec3f focus);
s32    find_c_buttons_pressed(u16 currentState, u16 buttonsPressed, u16 buttonsDown);
s32    update_camera_hud_status(struct Camera *c);
Bool32 is_point_within_radius_of_mario_cam_state(f32     posX,   f32   posY, f32 posZ, f32 maxDist);
Bool32 set_or_approach_f32_asymptotic(    f32     *dst,   f32   goal, f32 scale);
void   set_or_approach_vec3f_asymptotic(Vec3f      dst, Vec3f   goal, f32 xMul, f32 yMul, f32 zMul);
Bool32 set_or_approach_s16_symmetric(     s16 *current,   s16 target, s16 increment);
s32  clamp_positions_and_find_yaw(Vec3f pos,  Vec3f origin, f32 xMax, f32 xMin, f32 zMax, f32 zMin);
void rotate_in_xz(Vec3f dst, Vec3f src, Angle yaw);
void rotate_in_yz(Vec3f dst, Vec3f src, Angle pitch);
void set_camera_pitch_shake(s16 mag, s16 decay, s16 inc);
void set_camera_yaw_shake(  s16 mag, s16 decay, s16 inc);
void set_camera_roll_shake( s16 mag, s16 decay, s16 inc);
void set_pitch_shake_from_point(s16 mag, s16 decay, s16 inc, f32 maxDist, Vec3f pos);
void shake_camera_pitch(Vec3f pos, Vec3f focus);
void shake_camera_yaw(  Vec3f pos, Vec3f focus);
void shake_camera_roll(Angle *roll);
s32  offset_yaw_outward_radial(struct Camera *c, Angle areaYaw);
void play_camera_buzz_if_cdown(                    void);
void play_camera_buzz_if_cbutton(                  void);
void play_camera_buzz_if_c_sideways(               void);
void play_sound_cbutton_up(                        void);
void play_sound_cbutton_down(                      void);
void play_sound_cbutton_side(                      void);
void play_sound_button_change_blocked(             void);
void play_sound_rbutton_changed(                   void);
void play_sound_if_cam_switched_to_lakitu_or_mario(void);
void radial_camera_input(           struct Camera *c);
void handle_c_button_movement(      struct Camera *c);
void start_cutscene(                struct Camera *c, u8 cutscene);
s32  get_cutscene_from_mario_status(struct Camera *c);
void warp_camera(Vec3f displacement);
void approach_camera_height(        struct Camera *c, f32 goal, f32 inc);
void offset_rotated(Vec3f dst, Vec3f from, Vec3f to, Vec3a rotation);
Angle next_lakitu_state(Vec3f newPos, Vec3f newFoc, Vec3f curPos, Vec3f curFoc, Vec3f oldPos, Vec3f oldFoc, Angle yaw);
void set_fixed_cam_axis_sa_lobby(UNUSED s16 preset);
s32  camera_course_processing(    struct Camera *c);
s32  rotate_camera_around_walls(  struct Camera *c, Vec3f cPos, Angle *avoidYaw, Angle yawRange);
void find_mario_floor_and_ceil(struct PlayerGeometry *pg);
void start_object_cutscene_without_focus(u8 cutscene);
s32  cutscene_object_with_dialog(        u8 cutscene, struct Object *obj, DialogID dialogID);
s32  cutscene_object_without_dialog(     u8 cutscene, struct Object *obj);
s32  cutscene_object(                    u8 cutscene, struct Object *obj);
void play_cutscene(struct Camera *c);
void cutscene_event(CameraEvent event, struct Camera * c, s16 start, s16 end);
void cutscene_spawn_obj(u32 obj, s16 frame);
void set_fov_shake(s16 amplitude, s16 decay, s16 shakeSpeed);

void set_fov_function(u8 func);
void cutscene_set_fov_shake_preset(  u8 preset);
void set_fov_shake_from_point_preset(u8 preset, Vec3f pos);
void obj_rotate_towards_point(struct Object *obj, Vec3f point, Angle pitchOff, Angle yawOff, Angle pitchDiv, Angle yawDiv);

Gfx *geo_camera_fov(s32 callContext, struct GraphNode *g, UNUSED void *context);
