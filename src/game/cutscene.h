#ifndef CUTSCENE_H
#define CUTSCENE_H

#include <PR/ultratypes.h>

#define CUTSCENE_NONE                   0x0

#define CUTSCENE_DOOR_PULL              0x82
#define CUTSCENE_DOOR_PUSH              0x83
#define CUTSCENE_ENTER_CANNON           0x85
#define CUTSCENE_ENTER_PAINTING         0x86
#define CUTSCENE_DEATH_EXIT             0x87
#define CUTSCENE_DOOR_WARP              0x8B
#define CUTSCENE_DOOR_PULL_MODE         0x8C
#define CUTSCENE_DOOR_PUSH_MODE         0x8D
#define CUTSCENE_INTRO_PEACH            0x8E
#define CUTSCENE_DANCE_ROTATE           0x8F
#define CUTSCENE_ENTER_BOWSER_ARENA     0x90
#define CUTSCENE_0F_UNUSED              0x91 // Never activated, stub cutscene functions
#define CUTSCENE_UNUSED_EXIT            0x93 // Never activated
#define CUTSCENE_SLIDING_DOORS_OPEN     0x95
#define CUTSCENE_PREPARE_CANNON         0x96
#define CUTSCENE_UNLOCK_KEY_DOOR        0x97
#define CUTSCENE_STANDING_DEATH         0x98
#define CUTSCENE_DEATH_ON_STOMACH       0x99
#define CUTSCENE_DEATH_ON_BACK          0x9A
#define CUTSCENE_QUICKSAND_DEATH        0x9B
#define CUTSCENE_SUFFOCATION_DEATH      0x9C
#define CUTSCENE_EXIT_BOWSER_SUCC       0x9D
#define CUTSCENE_EXIT_BOWSER_DEATH      0x9E // Never activated
#define CUTSCENE_WATER_DEATH            0x9F // Not in cutscene switch
#define CUTSCENE_EXIT_PAINTING_SUCC     0xA0
#define CUTSCENE_CAP_SWITCH_PRESS       0xA1
#define CUTSCENE_DIALOG                 0xA2
#define CUTSCENE_RACE_DIALOG            0xA3
#define CUTSCENE_ENTER_PYRAMID_TOP      0xA4
#define CUTSCENE_DANCE_FLY_AWAY         0xA5
#define CUTSCENE_DANCE_CLOSEUP          0xA6
#define CUTSCENE_KEY_DANCE              0xA7
#define CUTSCENE_SSL_PYRAMID_EXPLODE    0xA8 // Never activated
#define CUTSCENE_EXIT_SPECIAL_SUCC      0xA9
#define CUTSCENE_NONPAINTING_DEATH      0xAA
#define CUTSCENE_READ_MESSAGE           0xAB
#define CUTSCENE_ENDING                 0xAC
#define CUTSCENE_STAR_SPAWN             0xAD
#define CUTSCENE_GRAND_STAR             0xAE
#define CUTSCENE_DANCE_DEFAULT          0xAF
#define CUTSCENE_RED_COIN_STAR_SPAWN    0xB0
#define CUTSCENE_END_WAVING             0xB1
#define CUTSCENE_CREDITS                0xB2
#define CUTSCENE_EXIT_WATERFALL         0xB3
#define CUTSCENE_EXIT_FALL_WMOTR        0xB4
#define CUTSCENE_ENTER_POOL             0xB5

/**
 * Stop the cutscene.
 */
#define CUTSCENE_STOP                   0x8000
/**
 * Play the current cutscene shot indefinitely (until canceled).
 */
#define CUTSCENE_LOOP                   0x7FFF

#define HAND_CAM_SHAKE_OFF              0x00
#define HAND_CAM_SHAKE_CUTSCENE         0x01
#define HAND_CAM_SHAKE_UNUSED           0x02
#define HAND_CAM_SHAKE_HANG_OWL         0x03
#define HAND_CAM_SHAKE_HIGH             0x04
#define HAND_CAM_SHAKE_STAR_DANCE       0x05
#define HAND_CAM_SHAKE_LOW              0x06

#define DOOR_DEFAULT                    0x00
#define DOOR_LEAVING_SPECIAL            0x01
#define DOOR_ENTER_LOBBY                0x02

// Might rename these to reflect what they are used for instead "SET_45" etc.
#define CAM_FOV_SET_45                  0x01
#define CAM_FOV_DEFAULT                 0x02
#define CAM_FOV_APP_45                  0x04
#define CAM_FOV_SET_30                  0x05
#define CAM_FOV_APP_20                  0x06
#define CAM_FOV_BBH                     0x07
#define CAM_FOV_APP_80                  0x09
#define CAM_FOV_APP_30                  0x0A
#define CAM_FOV_APP_60                  0x0B
#define CAM_FOV_ZOOM_30                 0x0C
#define CAM_FOV_SET_29                  0x0D

#define CAM_EVENT_CANNON                0x01
#define CAM_EVENT_SHOT_FROM_CANNON      0x02
#define CAM_EVENT_UNUSED_3              0x03
#define CAM_EVENT_BOWSER_INIT           0x04
#define CAM_EVENT_DOOR_WARP             0x05
#define CAM_EVENT_DOOR                  0x06
#define CAM_EVENT_BOWSER_JUMP           0x07
#define CAM_EVENT_BOWSER_THROW_BOUNCE   0x08
#define CAM_EVENT_START_INTRO           0x09
#define CAM_EVENT_START_GRAND_STAR      0x0A
#define CAM_EVENT_START_ENDING          0x0B
#define CAM_EVENT_START_END_WAVING      0x0C
#define CAM_EVENT_START_CREDITS         0x0D

#endif
