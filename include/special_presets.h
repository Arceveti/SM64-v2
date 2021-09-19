#pragma once

#include "special_preset_names.h"
#include "behavior_data.h"
#include "model_ids.h"

// Special Preset types
#define SPTYPE_NO_YROT_OR_PARAMS  0x0 // object is  8-bytes long,  no y-rotation or any behavior params
#define SPTYPE_YROT_NO_PARAMS     0x1 // object is 10-bytes long, has y-rotation but no params
#define SPTYPE_PARAMS_AND_YROT    0x2 // object is 12-bytes long, has y-rotation and params
#define SPTYPE_UNKNOWN            0x3 // object is 14-bytes long, has 3 extra shorts that get converted to floats.
#define SPTYPE_DEF_PARAM_AND_YROT 0x4 // object is 10-bytes long, has y-rotation and uses the default param

struct SpecialPreset
{
    /*00*/ u8       preset_id;
    /*01*/ u8       type;      // Determines whether object is 8, 10, 12 or 14 bytes long.
    /*02*/ u8       defParam;  // Default parameter, only used when type is SPTYPE_DEF_PARAM_AND_YROT
    /*03*/ ModelID  model;
    /*04*/ const BehaviorScript *behavior;
};

// Some Models ID's are missing their names because they are probably unused

static struct SpecialPreset SpecialObjectPresets[] =
{
    {0x00, SPTYPE_YROT_NO_PARAMS    , 0x00, MODEL_NONE                              , NULL                              }, // special_null_start
    {0x01, SPTYPE_NO_YROT_OR_PARAMS , 0x00, MODEL_YELLOW_COIN                       , bhvYellowCoin                     }, // special_yellow_coin
    {0x02, SPTYPE_NO_YROT_OR_PARAMS , 0x00, MODEL_YELLOW_COIN                       , bhvYellowCoin                     }, // special_yellow_coin_2
    {0x03, SPTYPE_NO_YROT_OR_PARAMS , 0x00, MODEL_UNKNOWN_B8                        , bhvStaticObject                   }, // special_unknown_3
    {0x04, SPTYPE_NO_YROT_OR_PARAMS , 0x00, MODEL_BOO                               , bhvCourtyardBooTriplet            }, // special_boo
    {0x05, SPTYPE_NO_YROT_OR_PARAMS , 0x00, MODEL_UNKNOWN_AC                        , bhvCastleFloorTrap                }, // special_unknown_5
    {0x06, SPTYPE_NO_YROT_OR_PARAMS , 0x00, MODEL_LLL_MOVING_OCTAGONAL_MESH_PLATFORM, bhvLllMovingOctagonalMeshPlatform }, // special_lll_moving_octagonal_mesh_platform
    {0x07, SPTYPE_NO_YROT_OR_PARAMS , 0x00, MODEL_CCM_SNOWMAN_HEAD                  , bhvSnowBall                       }, // special_snow_ball
    {0x08, SPTYPE_YROT_NO_PARAMS    , 0x00, MODEL_LLL_DRAWBRIDGE_PART               , bhvLllDrawbridgeSpawner           }, // special_lll_drawbridge_spawner
    {0x09, SPTYPE_NO_YROT_OR_PARAMS , 0x00, MODEL_NONE                              , bhvStaticObject                   }, // special_empty_9
    {0x0A, SPTYPE_NO_YROT_OR_PARAMS , 0x00, MODEL_LLL_ROTATING_BLOCK_FIRE_BARS      , bhvLllRotatingBlockWithFireBars   }, // special_lll_rotating_block_with_fire_bars
    {0x0B, SPTYPE_NO_YROT_OR_PARAMS , 0x00, MODEL_NONE                              , bhvLllFloatingWoodBridge          }, // special_lll_floating_wood_bridge
    {0x0C, SPTYPE_NO_YROT_OR_PARAMS , 0x00, MODEL_NONE                              , bhvLllTumblingBridge              }, // special_tumbling_platform
    {0x0D, SPTYPE_NO_YROT_OR_PARAMS , 0x00, MODEL_LLL_ROTATING_HEXAGONAL_RING       , bhvLllRotatingHexagonalRing       }, // special_lll_rotating_hexagonal_ring
    {0x0E, SPTYPE_YROT_NO_PARAMS    , 0x00, MODEL_LLL_SINKING_RECTANGULAR_PLATFORM  , bhvLllSinkingRectangularPlatform  }, // special_lll_sinking_rectangular_platform
    {0x0F, SPTYPE_NO_YROT_OR_PARAMS , 0x00, MODEL_LLL_SINKING_SQUARE_PLATFORMS      , bhvLllSinkingSquarePlatforms      }, // special_lll_sinking_square_platforms
    {0x10, SPTYPE_NO_YROT_OR_PARAMS , 0x00, MODEL_LLL_TILTING_SQUARE_PLATFORM       , bhvLllTiltingInvertedPyramid      }, // special_lll_tilting_square_platform
    {0x11, SPTYPE_NO_YROT_OR_PARAMS , 0x00, MODEL_NONE                              , bhvLllBowserPuzzle                }, // special_lll_bowser_puzzle
    {0x12, SPTYPE_NO_YROT_OR_PARAMS , 0x00, MODEL_NONE                              , bhvMrI                            }, // special_mr_i
    {0x13, SPTYPE_NO_YROT_OR_PARAMS , 0x00, MODEL_BULLY                             , bhvSmallBully                     }, // special_small_bully
    {0x14, SPTYPE_NO_YROT_OR_PARAMS , 0x00, MODEL_BULLY_BOSS                        , bhvBigBully                       }, // special_big_bully
    {0x15, SPTYPE_NO_YROT_OR_PARAMS , 0x00, MODEL_NONE                              , bhvStaticObject                   }, // special_empty_21
    {0x16, SPTYPE_NO_YROT_OR_PARAMS , 0x00, MODEL_NONE                              , bhvStaticObject                   }, // special_empty_22
    {0x17, SPTYPE_NO_YROT_OR_PARAMS , 0x00, MODEL_NONE                              , bhvStaticObject                   }, // special_empty_23
    {0x18, SPTYPE_NO_YROT_OR_PARAMS , 0x00, MODEL_NONE                              , bhvStaticObject                   }, // special_empty_24
    {0x19, SPTYPE_NO_YROT_OR_PARAMS , 0x00, MODEL_NONE                              , bhvStaticObject                   }, // special_empty_25
    {0x1A, SPTYPE_NO_YROT_OR_PARAMS , 0x00, MODEL_YELLOW_COIN                       , bhvMovingBlueCoin                 }, // special_moving_blue_coin
    {0x1B, SPTYPE_NO_YROT_OR_PARAMS , 0x00, MODEL_TREASURE_CHEST_BASE               , bhvBetaChestBottom                }, // special_jrb_chest
    {0x1C, SPTYPE_NO_YROT_OR_PARAMS , 0x00, MODEL_WATER_RING                        , bhvJetStreamRingSpawner           }, // special_water_ring
    {0x1D, SPTYPE_NO_YROT_OR_PARAMS , 0x00, MODEL_WATER_MINE                        , bhvBowserBomb                     }, // special_mine
    {0x1E, SPTYPE_UNKNOWN           , 0x00, MODEL_NONE                              , bhvStaticObject                   }, // special_empty_30, SPTYPE_UNKNOWN
    {0x1F, SPTYPE_NO_YROT_OR_PARAMS , 0x00, MODEL_NONE                              , bhvStaticObject                   }, // special_empty_31
    {0x20, SPTYPE_NO_YROT_OR_PARAMS , 0x00, MODEL_BUTTERFLY                         , bhvButterfly                      }, // special_butterfly
    {0x21, SPTYPE_NO_YROT_OR_PARAMS , 0x00, MODEL_BOWSER                            , bhvBowser                         }, // special_bowser
    {0x22, SPTYPE_NO_YROT_OR_PARAMS , 0x00, MODEL_WF_ROTATING_WOODEN_PLATFORM       , bhvWfRotatingWoodenPlatform       }, // special_wf_rotating_wooden_platform
    {0x23, SPTYPE_YROT_NO_PARAMS    , 0x00, MODEL_WF_SMALL_BOMP                     , bhvSmallBomp                      }, // special_small_bomp
    {0x24, SPTYPE_YROT_NO_PARAMS    , 0x00, MODEL_WF_SLIDING_PLATFORM               , bhvWfSlidingPlatform              }, // special_wf_sliding_platform
    {0x25, SPTYPE_NO_YROT_OR_PARAMS , 0x00, MODEL_NONE                              , bhvTowerPlatformGroup             }, // special_tower_platform_group
    {0x26, SPTYPE_NO_YROT_OR_PARAMS , 0x00, MODEL_NONE                              , bhvRotatingCounterClockwise       }, // special_rotating_counter_clockwise
    {0x27, SPTYPE_NO_YROT_OR_PARAMS , 0x00, MODEL_WF_TUMBLING_BRIDGE                , bhvWfTumblingBridge               }, // special_wf_tumbling_bridge
    {0x28, SPTYPE_NO_YROT_OR_PARAMS , 0x00, MODEL_WF_LARGE_BOMP                     , bhvLargeBomp                      }, // special_large_bomp
    {0x65, SPTYPE_YROT_NO_PARAMS    , 0x00, MODEL_LEVEL_GEOMETRY_03                 , bhvStaticObject                   }, // special_level_geo_03 = 0x65
    {0x66, SPTYPE_YROT_NO_PARAMS    , 0x00, MODEL_LEVEL_GEOMETRY_04                 , bhvStaticObject                   }, // special_level_geo_04
    {0x67, SPTYPE_YROT_NO_PARAMS    , 0x00, MODEL_LEVEL_GEOMETRY_05                 , bhvStaticObject                   }, // special_level_geo_05
    {0x68, SPTYPE_YROT_NO_PARAMS    , 0x00, MODEL_LEVEL_GEOMETRY_06                 , bhvStaticObject                   }, // special_level_geo_06
    {0x69, SPTYPE_YROT_NO_PARAMS    , 0x00, MODEL_LEVEL_GEOMETRY_07                 , bhvStaticObject                   }, // special_level_geo_07
    {0x6A, SPTYPE_YROT_NO_PARAMS    , 0x00, MODEL_LEVEL_GEOMETRY_08                 , bhvStaticObject                   }, // special_level_geo_08
    {0x6B, SPTYPE_YROT_NO_PARAMS    , 0x00, MODEL_LEVEL_GEOMETRY_09                 , bhvStaticObject                   }, // special_level_geo_09
    {0x6C, SPTYPE_YROT_NO_PARAMS    , 0x00, MODEL_LEVEL_GEOMETRY_0A                 , bhvStaticObject                   }, // special_level_geo_0A
    {0x6D, SPTYPE_YROT_NO_PARAMS    , 0x00, MODEL_LEVEL_GEOMETRY_0B                 , bhvStaticObject                   }, // special_level_geo_0B
    {0x6E, SPTYPE_YROT_NO_PARAMS    , 0x00, MODEL_LEVEL_GEOMETRY_0C                 , bhvStaticObject                   }, // special_level_geo_0C
    {0x6F, SPTYPE_YROT_NO_PARAMS    , 0x00, MODEL_LEVEL_GEOMETRY_0D                 , bhvStaticObject                   }, // special_level_geo_0D
    {0x70, SPTYPE_YROT_NO_PARAMS    , 0x00, MODEL_LEVEL_GEOMETRY_0E                 , bhvStaticObject                   }, // special_level_geo_0E
    {0x71, SPTYPE_YROT_NO_PARAMS    , 0x00, MODEL_LEVEL_GEOMETRY_0F                 , bhvStaticObject                   }, // special_level_geo_0F
    {0x72, SPTYPE_YROT_NO_PARAMS    , 0x00, MODEL_LEVEL_GEOMETRY_10                 , bhvStaticObject                   }, // special_level_geo_10
    {0x73, SPTYPE_YROT_NO_PARAMS    , 0x00, MODEL_LEVEL_GEOMETRY_11                 , bhvStaticObject                   }, // special_level_geo_11
    {0x74, SPTYPE_YROT_NO_PARAMS    , 0x00, MODEL_LEVEL_GEOMETRY_12                 , bhvStaticObject                   }, // special_level_geo_12
    {0x75, SPTYPE_YROT_NO_PARAMS    , 0x00, MODEL_LEVEL_GEOMETRY_13                 , bhvStaticObject                   }, // special_level_geo_13
    {0x76, SPTYPE_YROT_NO_PARAMS    , 0x00, MODEL_LEVEL_GEOMETRY_14                 , bhvStaticObject                   }, // special_level_geo_14
    {0x77, SPTYPE_YROT_NO_PARAMS    , 0x00, MODEL_LEVEL_GEOMETRY_15                 , bhvStaticObject                   }, // special_level_geo_15
    {0x78, SPTYPE_YROT_NO_PARAMS    , 0x00, MODEL_LEVEL_GEOMETRY_16                 , bhvStaticObject                   }, // special_level_geo_16
    {0x79, SPTYPE_NO_YROT_OR_PARAMS , 0x00, MODEL_BOB_BUBBLY_TREE                   , bhvTree                           }, // special_bubble_tree
    {0x7A, SPTYPE_NO_YROT_OR_PARAMS , 0x00, MODEL_COURTYARD_SPIKY_TREE              , bhvTree                           }, // special_spiky_tree
    {0x7B, SPTYPE_NO_YROT_OR_PARAMS , 0x00, MODEL_CCM_SNOW_TREE                     , bhvTree                           }, // special_snow_tree
    {0x7C, SPTYPE_NO_YROT_OR_PARAMS , 0x00, MODEL_UNKNOWN_TREE_1A                   , bhvTree                           }, // special_unknown_tree
    {0x7D, SPTYPE_NO_YROT_OR_PARAMS , 0x00, MODEL_SSL_PALM_TREE                     , bhvTree                           }, // special_palm_tree
    {0x89, SPTYPE_YROT_NO_PARAMS    , 0x00, MODEL_CASTLE_CASTLE_DOOR_UNUSED         , bhvDoor                           }, // special_wooden_door
    {0x7E, SPTYPE_YROT_NO_PARAMS    , 0x00, MODEL_CASTLE_WOODEN_DOOR_UNUSED         , bhvDoor                           }, // special_haunted_door = special_wooden_door
    {0x7F, SPTYPE_YROT_NO_PARAMS    , 0x00, MODEL_UNKNOWN_DOOR_1E                   , bhvDoor                           }, // special_unknown_door
    {0x80, SPTYPE_YROT_NO_PARAMS    , 0x00, MODEL_HMC_METAL_DOOR                    , bhvDoor                           }, // special_metal_door
    {0x81, SPTYPE_YROT_NO_PARAMS    , 0x00, MODEL_HMC_HAZY_MAZE_DOOR                , bhvDoor                           }, // special_hmc_door
    {0x82, SPTYPE_YROT_NO_PARAMS    , 0x00, MODEL_UNKNOWN_DOOR_21                   , bhvDoor                           }, // special_unknown2_door
    {0x8A, SPTYPE_DEF_PARAM_AND_YROT, 0x00, MODEL_CASTLE_DOOR_0_STARS               , bhvDoor                           }, // special_wooden_door_warp
    {0x8B, SPTYPE_DEF_PARAM_AND_YROT, 0x01, MODEL_CASTLE_DOOR_1_STAR                , bhvDoor                           }, // special_unknown1_door_warp
    {0x8C, SPTYPE_DEF_PARAM_AND_YROT, 0x03, MODEL_CASTLE_DOOR_3_STARS               , bhvDoor                           }, // special_metal_door_warp
    {0x8D, SPTYPE_DEF_PARAM_AND_YROT, 0x00, MODEL_CASTLE_KEY_DOOR                   , bhvDoor                           }, // special_unknown2_door_warp
    {0x88, SPTYPE_PARAMS_AND_YROT   , 0x00, MODEL_CASTLE_CASTLE_DOOR                , bhvDoorWarp                       }, // special_unknown3_door_warp
    {0x83, SPTYPE_PARAMS_AND_YROT   , 0x00, MODEL_CASTLE_WOODEN_DOOR                , bhvDoorWarp                       }, // special_castle_door_warp
    {0x84, SPTYPE_PARAMS_AND_YROT   , 0x00, MODEL_UNKNOWN_DOOR_28                   , bhvDoorWarp                       }, // special_0stars_door
    {0x85, SPTYPE_PARAMS_AND_YROT   , 0x00, MODEL_CASTLE_METAL_DOOR                 , bhvDoorWarp                       }, // special_1star_door
    {0x86, SPTYPE_PARAMS_AND_YROT   , 0x00, MODEL_UNKNOWN_DOOR_2A                   , bhvDoorWarp                       }, // special_3star_door
    {0x87, SPTYPE_PARAMS_AND_YROT   , 0x00, MODEL_UNKNOWN_DOOR_2B                   , bhvDoorWarp                       }, // special_key_door
    {0xFF, SPTYPE_NO_YROT_OR_PARAMS , 0x00, MODEL_NONE                              , NULL                              }  // special_null_end = 0xFF
};
