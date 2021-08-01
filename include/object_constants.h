#ifndef OBJECT_CONSTANTS_H
#define OBJECT_CONSTANTS_H

// This file contains macros that provide descriptive names for
// field-specific and object-specific constants, e.g. actions.

/* activeFlags */
#define ACTIVE_FLAG_DEACTIVATED              0x0000  // 0x0000
#define ACTIVE_FLAG_ACTIVE                 (1 <<  0) // 0x0001
#define ACTIVE_FLAG_FAR_AWAY               (1 <<  1) // 0x0002
#define ACTIVE_FLAG_UNK2                   (1 <<  2) // 0x0004
#define ACTIVE_FLAG_IN_DIFFERENT_ROOM      (1 <<  3) // 0x0008
#define ACTIVE_FLAG_UNIMPORTANT            (1 <<  4) // 0x0010
#define ACTIVE_FLAG_INITIATED_TIME_STOP    (1 <<  5) // 0x0020
#define ACTIVE_FLAG_MOVE_THROUGH_GRATE     (1 <<  6) // 0x0040
#define ACTIVE_FLAG_DITHERED_ALPHA         (1 <<  7) // 0x0080
#define ACTIVE_FLAG_ALLOCATED              (1 <<  8) // 0x0100
#define ACTIVE_FLAG_SMALL_BOX_NOT_THROWN   (1 <<  9) // 0x0200
#define ACTIVE_FLAG_IGNORE_WATER_LEVEL     (1 << 10) // 0x0400


/* respawnInfoType */
#define RESPAWN_INFO_TYPE_NULL          0x00
#define RESPAWN_INFO_TYPE_32            0x01
#define RESPAWN_INFO_TYPE_16            0x02

/* respawnInfo */
#define RESPAWN_INFO_DONT_RESPAWN       0xFF

/* oFlags */
#define OBJ_FLAG_UPDATE_GFX_POS_AND_ANGLE           (1 <<  0) // 0x00000001
#define OBJ_FLAG_MOVE_XZ_USING_FVEL                 (1 <<  1) // 0x00000002
#define OBJ_FLAG_MOVE_Y_WITH_TERMINAL_VEL           (1 <<  2) // 0x00000004
#define OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW           (1 <<  3) // 0x00000008
#define OBJ_FLAG_SET_FACE_ANGLE_TO_MOVE_ANGLE       (1 <<  4) // 0x00000010
#define OBJ_FLAG_UPDATE_TRANSFORM_FOR_THROW_MATRIX  (1 <<  5) // 0x00000020
#define OBJ_FLAG_COMPUTE_DIST_TO_MARIO              (1 <<  6) // 0x00000040
#define OBJ_FLAG_ACTIVE_FROM_AFAR                   (1 <<  7) // 0x00000080
#define OBJ_FLAG_IS_MARIO                           (1 <<  8) // 0x00000100
#define OBJ_FLAG_TRANSFORM_RELATIVE_TO_PARENT       (1 <<  9) // 0x00000200
#define OBJ_FLAG_HOLDABLE                           (1 << 10) // 0x00000400
#define OBJ_FLAG_SET_THROW_MATRIX_FROM_TRANSFORM    (1 << 11) // 0x00000800
#define OBJ_FLAG_1000                               (1 << 12) // 0x00001000
#define OBJ_FLAG_COMPUTE_ANGLE_TO_MARIO             (1 << 13) // 0x00002000
#define OBJ_FLAG_PERSISTENT_RESPAWN                 (1 << 14) // 0x00004000
#define OBJ_FLAG_8000                               (1 << 15) // 0x00008000
#define OBJ_FLAG_HITBOX_WAS_SET                     (1 << 30) // 0x40000000

/* oHeldState */
#define HELD_FREE                       0x00
#define HELD_HELD                       0x01
#define HELD_THROWN                     0x02
#define HELD_DROPPED                    0x03

/* oDialogState */
#define DIALOG_STATUS_ENABLE_TIME_STOP  0x00
#define DIALOG_STATUS_INTERRUPT         0x01
#define DIALOG_STATUS_START_DIALOG      0x02
#define DIALOG_STATUS_STOP_DIALOG       0x03
#define DIALOG_STATUS_DISABLE_TIME_STOP 0x04

#define DIALOG_FLAG_NONE                0x00
#define DIALOG_FLAG_TURN_TO_MARIO      (1 <<  0) // 0x01 // cutscene only
#define DIALOG_FLAG_TEXT_DEFAULT       (1 <<  1) // 0x02
#define DIALOG_FLAG_TEXT_RESPONSE      (1 <<  2) // 0x04 // non-cutscene only
#define DIALOG_FLAG_UNK_CAPSWITCH      (1 <<  3) // 0x08 // not defined
#define DIALOG_FLAG_TIME_STOP_ENABLED  (1 <<  4) // 0x10

/* oMoveFlags */
#define OBJ_MOVE_LANDED                (1 <<  0) // 0x0001
#define OBJ_MOVE_ON_GROUND             (1 <<  1) // 0x0002  // mutually exclusive to OBJ_MOVE_LANDED
#define OBJ_MOVE_LEFT_GROUND           (1 <<  2) // 0x0004
#define OBJ_MOVE_ENTERED_WATER         (1 <<  3) // 0x0008
#define OBJ_MOVE_AT_WATER_SURFACE      (1 <<  4) // 0x0010
#define OBJ_MOVE_UNDERWATER_OFF_GROUND (1 <<  5) // 0x0020
#define OBJ_MOVE_UNDERWATER_ON_GROUND  (1 <<  6) // 0x0040
#define OBJ_MOVE_IN_AIR                (1 <<  7) // 0x0080
#define OBJ_MOVE_OUT_SCOPE             (1 <<  8) // 0x0100
#define OBJ_MOVE_HIT_WALL              (1 <<  9) // 0x0200
#define OBJ_MOVE_HIT_EDGE              (1 << 10) // 0x0400
#define OBJ_MOVE_ABOVE_LAVA            (1 << 11) // 0x0800
#define OBJ_MOVE_LEAVING_WATER         (1 << 12) // 0x1000
#define OBJ_MOVE_BOUNCE                (1 << 13) // 0x2000
#ifndef VERSION_JP
#define OBJ_MOVE_ABOVE_DEATH_BARRIER   (1 << 14) // 0x4000
#endif

#define OBJ_MOVE_MASK_ON_GROUND (OBJ_MOVE_LANDED | OBJ_MOVE_ON_GROUND)
#define OBJ_MOVE_MASK_IN_WATER (    \
    OBJ_MOVE_ENTERED_WATER         |\
    OBJ_MOVE_AT_WATER_SURFACE      |\
    OBJ_MOVE_UNDERWATER_OFF_GROUND |\
    OBJ_MOVE_UNDERWATER_ON_GROUND)

/* oActiveParticleFlags */
#define ACTIVE_PARTICLE_DUST                 (1 <<  0) // 0x00000001
#define ACTIVE_PARTICLE_UNUSED_1             (1 <<  1) // 0x00000002
#define ACTIVE_PARTICLE_UNUSED_2             (1 <<  2) // 0x00000004
#define ACTIVE_PARTICLE_SPARKLES             (1 <<  3) // 0x00000008
#define ACTIVE_PARTICLE_H_STAR               (1 <<  4) // 0x00000010
#define ACTIVE_PARTICLE_BUBBLE               (1 <<  5) // 0x00000020
#define ACTIVE_PARTICLE_WATER_SPLASH         (1 <<  6) // 0x00000040
#define ACTIVE_PARTICLE_IDLE_WATER_WAVE      (1 <<  7) // 0x00000080
#define ACTIVE_PARTICLE_SHALLOW_WATER_WAVE   (1 <<  8) // 0x00000100
#define ACTIVE_PARTICLE_PLUNGE_BUBBLE        (1 <<  9) // 0x00000200
#define ACTIVE_PARTICLE_WAVE_TRAIL           (1 << 10) // 0x00000400
#define ACTIVE_PARTICLE_FIRE                 (1 << 11) // 0x00000800
#define ACTIVE_PARTICLE_SHALLOW_WATER_SPLASH (1 << 12) // 0x00001000
#define ACTIVE_PARTICLE_LEAF                 (1 << 13) // 0x00002000
#define ACTIVE_PARTICLE_DIRT                 (1 << 14) // 0x00004000
#define ACTIVE_PARTICLE_MIST_CIRCLE          (1 << 15) // 0x00008000
#define ACTIVE_PARTICLE_SNOW                 (1 << 16) // 0x00010000
#define ACTIVE_PARTICLE_BREATH               (1 << 17) // 0x00020000
#define ACTIVE_PARTICLE_V_STAR               (1 << 18) // 0x00040000
#define ACTIVE_PARTICLE_TRIANGLE             (1 << 19) // 0x00080000

/* oAction */
#define OBJ_ACT_LAVA_DEATH                                  100
#define OBJ_ACT_DEATH_PLANE_DEATH                           101

#define OBJ_ACT_HORIZONTAL_KNOCKBACK                        100
#define OBJ_ACT_VERTICAL_KNOCKBACK                          101
#define OBJ_ACT_SQUISHED                                    102

/* gTTCSpeedSetting */
#define TTC_SPEED_SLOW                                      0x0
#define TTC_SPEED_FAST                                      0x1
#define TTC_SPEED_RANDOM                                    0x2
#define TTC_SPEED_STOPPED                                   0x3

/* Bob-omb */
    /* oBehParams2ndByte */
    #define BOBOMB_BP_STYPE_GENERIC                         0x0
    #define BOBOMB_BP_STYPE_STATIONARY                      0x1
    /* oAction */
    #define BOBOMB_ACT_PATROL                               0x0
    #define BOBOMB_ACT_LAUNCHED                             0x1
    #define BOBOMB_ACT_CHASE_MARIO                          0x2
    #define BOBOMB_ACT_EXPLODE                              0x3
    /* oAnimState */
    #define BOBOMB_ANIM_STATE_EYES_OPEN                     0x0
    #define BOBOMB_ANIM_STATE_EYES_CLOSED                   0x1
    /* Animations */
    #define BOBOMB_ANIM_WALKING                             0x0
    #define BOBOMB_ANIM_HELD                                0x1

/* Hidden Blue Coin */
    /* oAction */
    #define HIDDEN_BLUE_COIN_ACT_INACTIVE                   0x0
    #define HIDDEN_BLUE_COIN_ACT_WAITING                    0x1
    #define HIDDEN_BLUE_COIN_ACT_ACTIVE                     0x2

/* Blue Coin Switch */
    /* oAction */
    #define BLUE_COIN_SWITCH_ACT_IDLE                       0x0
    #define BLUE_COIN_SWITCH_ACT_RECEDING                   0x1
    #define BLUE_COIN_SWITCH_ACT_TICKING                    0x2
    #define BLUE_COIN_SWITCH_ACT_EXTENDING                  0x3

/* Moving Blue Coin */
    /* oAction */
    #define MOV_BCOIN_ACT_STILL                             0x0
    #define MOV_BCOIN_ACT_MOVING                            0x1
    #define MOV_BCOIN_ACT_SLOWING_DOWN                      0x2
    #define MOV_BCOIN_ACT_STOPPED                           0x3
    #define MOV_BCOIN_ACT_FLICKERING                        0x4

/* Moving Yellow Coin */
    /* oAction */
    #define MOV_YCOIN_ACT_IDLE                              0x0
    #define MOV_YCOIN_ACT_BLINKING                          0x1
    /* oSubAction */

/* Coin Formation */
    /* oAction */
    #define COIN_FORMATION_ACT_INACTIVE                     0x0
    #define COIN_FORMATION_ACT_ACTIVE                       0x1
    #define COIN_FORMATION_ACT_DEACTIVATE                   0x2

/* Coin Inside Boo */
    /* oAction */
    #define COIN_INSIDE_BOO_ACT_CARRIED                     0x0
    #define COIN_INSIDE_BOO_ACT_DROPPED                     0x1

/* 1-Up Mushroom */
    /* oBehParams2ndByte */
    #define MUSHROOM_BP_REQUIRES_BOWSER_1                   0x1
    #define MUSHROOM_BP_REQUIRES_BOWSER_2                   0x2
    /* oAction */

/* Bob-omb Buddy */
    /* oBehParams2ndByte */
    #define BOBOMB_BUDDY_BP_STYPE_GENERIC                   0x0
    #define BOBOMB_BUDDY_BP_STYPE_BOB_GRASS_KBB             0x1
    #define BOBOMB_BUDDY_BP_STYPE_BOB_CANNON_KBB            0x2
    #define BOBOMB_BUDDY_BP_STYPE_BOB_GRASS                 0x3
    /* oAction */
    #define BOBOMB_BUDDY_ACT_IDLE                           0x0
    #define BOBOMB_BUDDY_ACT_TURN_TO_TALK                   0x2
    #define BOBOMB_BUDDY_ACT_TALK                           0x3
    /* oBobombBuddyRole */
    #define BOBOMB_BUDDY_ROLE_ADVICE                        0x0
    #define BOBOMB_BUDDY_ROLE_CANNON                        0x1
    /* oBobombBuddyCannonStatus */
    #define BOBOMB_BUDDY_CANNON_UNOPENED                    0x0
    #define BOBOMB_BUDDY_CANNON_OPENING                     0x1
    #define BOBOMB_BUDDY_CANNON_OPENED                      0x2
    #define BOBOMB_BUDDY_CANNON_STOP_TALKING                0x3
    /* oBobombBuddyHasTalkedToMario */
    #define BOBOMB_BUDDY_HAS_NOT_TALKED                     0x0
    #define BOBOMB_BUDDY_HAS_TALKED                         0x2

/* Bowser */
    /* Tail oAction */
    #define BOWSER_ACT_TAIL_DEFAULT                         0x00
    #define BOWSER_ACT_TAIL_THROWN                          0x01
    #define BOWSER_ACT_TAIL_TOUCHED_MARIO                   0x02
    /* oAction */
    #define BOWSER_ACT_DEFAULT                              0x00
    #define BOWSER_ACT_THROWN                               0x01
    #define BOWSER_ACT_JUMP_ONTO_STAGE                      0x02
    #define BOWSER_ACT_DANCE                                0x03
    #define BOWSER_ACT_DEAD                                 0x04
    #define BOWSER_ACT_WAIT                                 0x05
    #define BOWSER_ACT_INTRO_WALK                           0x06
    #define BOWSER_ACT_CHARGE_MARIO                         0x07
    #define BOWSER_ACT_SPIT_FIRE_INTO_SKY                   0x08
    #define BOWSER_ACT_SPIT_FIRE_ONTO_FLOOR                 0x09
    #define BOWSER_ACT_HIT_EDGE                             0x0A
    #define BOWSER_ACT_TURN_FROM_EDGE                       0x0B
    #define BOWSER_ACT_HIT_MINE                             0x0C
    #define BOWSER_ACT_BIG_JUMP                             0x0D
    #define BOWSER_ACT_WALK_TO_MARIO                        0x0E
    #define BOWSER_ACT_BREATH_FIRE                          0x0F
    #define BOWSER_ACT_TELEPORT                             0x10
    #define BOWSER_ACT_QUICK_JUMP                           0x11
    #define BOWSER_ACT_UNUSED_SLOW_WALK                     0x12
    #define BOWSER_ACT_TILT_LAVA_PLATFORM                   0x13
    /* Animations */
    #define BOWSER_ANIM_STAND_UP                            0x00
    #define BOWSER_ANIM_STAND_UP_UNUSED                     0x01 // slightly different
    #define BOWSER_ANIM_SHAKING                             0x02
    #define BOWSER_ANIM_GRABBED                             0x03
    #define BOWSER_ANIM_BROKEN                              0x04 // broken animation
    #define BOWSER_ANIM_FALL_DOWN                           0x05 // unused
    #define BOWSER_ANIM_BREATH                              0x06
    #define BOWSER_ANIM_JUMP                                0x07 // unused, short jump, replaced by start/stop
    #define BOWSER_ANIM_JUMP_STOP                           0x08
    #define BOWSER_ANIM_JUMP_START                          0x09
    #define BOWSER_ANIM_DANCE                               0x0A
    #define BOWSER_ANIM_BREATH_UP                           0x0B
    #define BOWSER_ANIM_IDLE                                0x0C
    #define BOWSER_ANIM_SLOW_GAIT                           0x0D
    #define BOWSER_ANIM_LOOK_DOWN_STOP_WALK                 0x0E
    #define BOWSER_ANIM_LOOK_UP_START_WALK                  0x0F
    #define BOWSER_ANIM_FLIP_DOWN                           0x10
    #define BOWSER_ANIM_LAY_DOWN                            0x11
    #define BOWSER_ANIM_RUN_START                           0x12
    #define BOWSER_ANIM_RUN                                 0x13
    #define BOWSER_ANIM_RUN_STOP                            0x14
    #define BOWSER_ANIM_RUN_SLIP                            0x15
    #define BOWSER_ANIM_BREATH_QUICK                        0x16
    #define BOWSER_ANIM_EDGE_MOVE                           0x17
    #define BOWSER_ANIM_EDGE_STOP                           0x18
    #define BOWSER_ANIM_FLIP                                0x19
    #define BOWSER_ANIM_STAND_UP_FROM_FLIP                  0x1A
    /* oBehParams2ndByte */
    #define BOWSER_BP_BITDW                                 0x0
    #define BOWSER_BP_BITFS                                 0x1
    #define BOWSER_BP_BITS                                  0x2
    /* oBowserCamAct */
    #define BOWSER_CAM_ACT_IDLE                             0x0
    #define BOWSER_CAM_ACT_WALK                             0x1
    #define BOWSER_CAM_ACT_END                              0x2
    /* oBowserStatus */
    #define BOWSER_STATUS_ANGLE_MARIO                       (1 <<  1) // 0x00000002
    #define BOWSER_STATUS_ANGLE_CENTRE                      (1 <<  2) // 0x00000004
    #define BOWSER_STATUS_DIST_MARIO                        (1 <<  3) // 0x00000008
    #define BOWSER_STATUS_DIST_CENTRE                       (1 <<  4) // 0x00000010
    #define BOWSER_STATUS_BIG_JUMP                          (1 << 16) // 0x00010000
    #define BOWSER_STATUS_FIRE_SKY                          (1 << 17) // 0x00020000
    /* oBowserGrabbedStatus */
    #define BOWSER_GRAB_STATUS_NONE                         0x0
    #define BOWSER_GRAB_STATUS_GRABBED                      0x1
    #define BOWSER_GRAB_STATUS_HOLDING                      0x2
    /* oSubAction */
    #define BOWSER_SUB_ACT_DEAD_FLY_BACK                    0x0
    #define BOWSER_SUB_ACT_DEAD_BOUNCE                      0x1
    #define BOWSER_SUB_ACT_DEAD_WAIT                        0x2
    #define BOWSER_SUB_ACT_DEAD_DEFAULT_END                 0x3
    #define BOWSER_SUB_ACT_DEAD_DEFAULT_END_OVER            0x4
    #define BOWSER_SUB_ACT_DEAD_FINAL_END                   0xA
    #define BOWSER_SUB_ACT_DEAD_FINAL_END_OVER              0xB

    #define BOWSER_SUB_ACT_CHARGE_START                     0x0
    #define BOWSER_SUB_ACT_CHARGE_RUN                       0x1
    #define BOWSER_SUB_ACT_CHARGE_END                       0x2
    #define BOWSER_SUB_ACT_CHARGE_SLIP                      0x3

    #define BOWSER_SUB_ACT_TELEPORT_START                   0x0
    #define BOWSER_SUB_ACT_TELEPORT_MOVE                    0x1
    #define BOWSER_SUB_ACT_TELEPORT_STOP                    0x2

    #define BOWSER_SUB_ACT_HIT_MINE_START                   0x0
    #define BOWSER_SUB_ACT_HIT_MINE_FALL                    0x1
    #define BOWSER_SUB_ACT_HIT_MINE_STOP                    0x2
    
    #define BOWSER_SUB_ACT_JUMP_ON_STAGE_IDLE               0x0
    #define BOWSER_SUB_ACT_JUMP_ON_STAGE_START              0x1
    #define BOWSER_SUB_ACT_JUMP_ON_STAGE_LAND               0x2
    #define BOWSER_SUB_ACT_JUMP_ON_STAGE_STOP               0x3

/* Bowser Bits Platform*/
    /* oAction */
    #define BOWSER_BITS_PLAT_ACT_START                      0x0
    #define BOWSER_BITS_PLAT_ACT_CHECK                      0x1
    #define BOWSER_BITS_PLAT_ACT_FALL                       0x2

/* Bowser Key Cutscene */
    /* Animations */
    #define BOWSER_KEY_CUTSCENE_ANIM_UNLOCK_DOOR            0x0
    #define BOWSER_KEY_CUTSCENE_ANIM_COURSE_EXIT            0x1

/* Fish Spawer */
    /* oAction */
    #define FISH_SPAWNER_ACT_SPAWN                          0x0
    #define FISH_SPAWNER_ACT_IDLE                           0x1
    #define FISH_SPAWNER_ACT_RESPAWN                        0x2
    /* oBehParams2ndByte */
    #define FISH_SPAWNER_BP_MANY_BLUE                       0x0
    #define FISH_SPAWNER_BP_FEW_BLUE                        0x1
    #define FISH_SPAWNER_BP_MANY_CYAN                       0x2
    #define FISH_SPAWNER_BP_FEW_CYAN                        0x3

/* Fish */
    /* oAction */
    #define FISH_ACT_INIT                                   0x0
    #define FISH_ACT_ROAM                                   0x1
    #define FISH_ACT_FLEE                                   0x2

/* Blue Fish Spawner */
    /* oAction: bhv_blue_fish_spawn_loop */
    #define BLUE_FISH_ACT_SPAWN                             0x0
    #define BLUE_FISH_ACT_ROOM                              0x1
    #define BLUE_FISH_ACT_DUPLICATE                         0x2

/* Blue_Fish */
    /* oAction */
    #define BLUE_FISH_ACT_DIVE                              0x0
    #define BLUE_FISH_ACT_TURN                              0x1
    #define BLUE_FISH_ACT_ASCEND                            0x2
    #define BLUE_FISH_ACT_TURN_BACK                         0x3

    /* Animations */
    #define BLUE_FISH_ANIM_DEFAULT                          0x0

/* Cheep Cheep Spawner */
    /* oAction */
    #define BUB_SPAWNER_ACT_SPAWN_BUBS                      0x0
    #define BUB_SPAWNER_ACT_IDLE                            0x1
    #define BUB_SPAWNER_ACT_REMOVE_BUBS                     0x2
    #define BUB_SPAWNER_ACT_RESET                           0x3

/* Cheep Cheep */
    /* oAction */
    #define BUB_ACT_INIT                                    0x0
    #define BUB_ACT_SWIMMING_TOWARDS_MARIO                  0x1
    #define BUB_ACT_SWIMMING_AWAY_FROM_MARIO                0x2

/* Bubba */
    /* oAction */
    #define BUBBA_ACT_IDLE                                  0x0
    #define BUBBA_ACT_ATTACK                                0x1
    /* oAnimState */
    #define BUBBA_ANIM_STATE_CLOSED_MOUTH                   0x0
    #define BUBBA_ANIM_STATE_OPEN_MOUTH                     0x1

/* Clam */
    /* oAction */
    #define CLAM_ACT_CLOSING                                0x0
    #define CLAM_ACT_OPENING                                0x1

    /* Animations */
    #define CLAM_ANIM_CLOSING                               0x0
    #define CLAM_ANIM_OPENING                               0x1

/* Breakable Box */
    /* oAnimState */
    #define BREAKABLE_BOX_ANIM_STATE_CRAZY_BOX              0x0
    #define BREAKABLE_BOX_ANIM_STATE_CORK_BOX               0x1

/* Small Breakable Box */
    /* oAction */
    #define BREAKABLE_BOX_SMALL_ACT_MOVE                    0x0

/* Exclamation Box */
    /* oAction */
    #define EXCLAMATION_BOX_ACT_INIT                        0x0
    #define EXCLAMATION_BOX_ACT_OUTLINE                     0x1
    #define EXCLAMATION_BOX_ACT_ACTIVE                      0x2
    #define EXCLAMATION_BOX_ACT_SCALING                     0x3
    #define EXCLAMATION_BOX_ACT_EXPLODE                     0x4
    #define EXCLAMATION_BOX_ACT_WAIT_FOR_RESPAWN            0x5

/* Cap Switch */
    /* oAction */
    #define CAP_SWITCH_ACT_INIT                             0x0
    #define CAP_SWITCH_ACT_IDLE                             0x1
    #define CAP_SWITCH_ACT_BEING_PRESSED                    0x2
    #define CAP_SWITCH_ACT_DONE                             0x3

/* Mario Cap */
    /* oAction */
    #define CAP_ACT_MOVE                                    0x0
    #define CAP_ACT_QUICKSAND                               0xA
    #define CAP_ACT_MOVING_QUICKSAND                        0xB
    #define CAP_ACT_INSTANT_QUICKSAND                       0xC
    #define CAP_ACT_INSTANT_MOVING_QUICKSAND                0xD

/* Cannon Trap Door */
    /* oAction */
    #define CANNON_TRAP_DOOR_ACT_CLOSED                     0x0
    #define CANNON_TRAP_DOOR_ACT_CAM_ZOOM                   0x1
    #define CANNON_TRAP_DOOR_ACT_OPENING                    0x2
    #define CANNON_TRAP_DOOR_ACT_OPEN                       0x3

/* Opened Cannon */
    /* oAction */
    #define OPENED_CANNON_ACT_IDLE                          0x0
    #define OPENED_CANNON_ACT_READY                         0x1
    #define OPENED_CANNON_ACT_SHOOT                         0x2
    #define OPENED_CANNON_ACT_RESETTING                     0x3
    #define OPENED_CANNON_ACT_RISING                        0x4
    #define OPENED_CANNON_ACT_RAISE_BARREL                  0x5
    #define OPENED_CANNON_ACT_TURNING_YAW                   0x6

/* Door */
    /* oAction */
    #define DOOR_ACT_CLOSED                                 0x0
    #define DOOR_ACT_PULLED                                 0x1
    #define DOOR_ACT_PUSHED                                 0x2
    #define DOOR_ACT_WARP_PULLED                            0x3
    #define DOOR_ACT_WARP_PUSHED                            0x4

/* Star Door */
    /* oAction */
    #define STAR_DOOR_ACT_CLOSED                            0x0
    #define STAR_DOOR_ACT_OPENING                           0x1
    #define STAR_DOOR_ACT_OPEN                              0x2
    #define STAR_DOOR_ACT_CLOSING                           0x3
    #define STAR_DOOR_ACT_RESET                             0x4

/* Castle Trap Door */
    /* oAction */
    #define CASTLE_FLOOR_TRAP_ACT_OPEN_DETECT               0x0
    #define CASTLE_FLOOR_TRAP_ACT_OPEN                      0x1
    #define CASTLE_FLOOR_TRAP_ACT_CLOSE_DETECT              0x2
    #define CASTLE_FLOOR_TRAP_ACT_CLOSE                     0x3
    #define CASTLE_FLOOR_TRAP_ACT_ROTATE                    0x4

/* Homing Amp */
    /* oAction */
    #define HOMING_AMP_ACT_INACTIVE                         0x0
    #define HOMING_AMP_ACT_APPEAR                           0x1
    #define HOMING_AMP_ACT_CHASE                            0x2
    #define HOMING_AMP_ACT_GIVE_UP                          0x3
    #define HOMING_AMP_ACT_ATTACK_COOLDOWN                  0x4

/* Amp */
    /* oBehParams2ndByte */
    #define AMP_BP_ROT_RADIUS_200                           0x0
    #define AMP_BP_ROT_RADIUS_300                           0x1
    #define AMP_BP_ROT_RADIUS_400                           0x2
    #define AMP_BP_ROT_RADIUS_0                             0x3

    /* oAction */
    #define AMP_ACT_IDLE                                    0x2
    #define AMP_ACT_ATTACK_COOLDOWN                         0x4

    /* oAnimState */
    #define AMP_ANIM_STATE_OFF                              0x0
    #define AMP_ANIM_STATE_ON                               0x1

/* Butterfly */
    /* oAction */
    #define BUTTERFLY_ACT_RESTING                           0x0
    #define BUTTERFLY_ACT_FOLLOW_MARIO                      0x1
    #define BUTTERFLY_ACT_RETURN_HOME                       0x2
    /* Animations */
    #define BUTTERFLY_ANIM_FLYING                           0x0
    #define BUTTERFLY_ANIM_RESTING                          0x1

/* Hoot */
    /* oHootAvailability */
    #define HOOT_AVAIL_ASLEEP_IN_TREE                       0x0
    #define HOOT_AVAIL_WANTS_TO_TALK                        0x1
    #define HOOT_AVAIL_READY_TO_FLY                         0x2
    /* oAction */
    #define HOOT_ACT_ASCENT                                 0x0
    #define HOOT_ACT_CARRY                                  0x1
    #define HOOT_ACT_TIRED                                  0x2

/* Bully (all variants) */
    /* oBehParams2ndByte */
    #define BULLY_BP_SIZE_SMALL                             0x0
    #define BULLY_BP_SIZE_BIG                               0x1
    /* oAction */
    #define BULLY_ACT_PATROL                                0x0
    #define BULLY_ACT_CHASE_MARIO                           0x1
    #define BULLY_ACT_KNOCKBACK                             0x2
    #define BULLY_ACT_BACK_UP                               0x3
    #define BULLY_ACT_INACTIVE                              0x4
    #define BULLY_ACT_ACTIVATE_AND_FALL                     0x5
    /* oBullySubtype */
    #define BULLY_STYPE_GENERIC                             0x00
    #define BULLY_STYPE_MINION                              0x01
    #define BULLY_STYPE_CHILL                               0x10
    /* Animations */
    #define BULLY_ANIM_WALKING                              0x0
    #define BULLY_ANIM_RUNNING                              0x1
    #define BULLY_ANIM_UNUSED                               0x2
    #define BULLY_ANIM_BOAST                                0x3

/* Water Ring (all variants) */
    /* oAction */
    #define WATER_RING_ACT_NOT_COLLECTED                    0x0
    #define WATER_RING_ACT_COLLECTED                        0x1

/* Jet Stream Water Ring Spawner */
    /* oAction */
    #define JS_RING_SPAWNER_ACT_ACTIVE                      0x0
    #define JS_RING_SPAWNER_ACT_INACTIVE                    0x1

/* Celebration Star */
    /* oAction */
    #define CELEB_STAR_ACT_SPIN_AROUND_MARIO                0x0
    #define CELEB_STAR_ACT_FACE_CAMERA                      0x1

/* LLL Drawbridge */
    /* oAction */
    #define LLL_DRAWBRIDGE_ACT_LOWER                        0x0
    #define LLL_DRAWBRIDGE_ACT_RAISE                        0x1

/* Bomp (both variants) */
    /* oAction */
    #define BOMP_ACT_WAIT                                   0x0
    #define BOMP_ACT_POKE_OUT                               0x1
    #define BOMP_ACT_EXTEND                                 0x2
    #define BOMP_ACT_RETRACT                                0x3

/* WF Sliding Brick Platform */
    /* oBehParams2ndByte */
    #define WF_SLID_BRICK_PTFM_BP_MOV_VEL_10                0x1
    #define WF_SLID_BRICK_PTFM_BP_MOV_VEL_15                0x2
    #define WF_SLID_BRICK_PTFM_BP_MOV_VEL_20                0x3
    /* oAction */
    #define WF_SLID_BRICK_PTFM_ACT_WAIT                     0x0
    #define WF_SLID_BRICK_PTFM_ACT_EXTEND                   0x1
    #define WF_SLID_BRICK_PTFM_ACT_RETRACT                  0x2

/* Fake Moneybag Coin */
    /* oAction */
    #define FAKE_MONEYBAG_COIN_ACT_IDLE                     0x0
    #define FAKE_MONEYBAG_COIN_ACT_TRANSFORM                0x1

/* Moneybag */
    /* oAction */
    #define MONEYBAG_ACT_APPEAR                             0x0
    #define MONEYBAG_ACT_UNUSED_APPEAR                      0x1
    #define MONEYBAG_ACT_MOVE_AROUND                        0x2
    #define MONEYBAG_ACT_RETURN_HOME                        0x3
    #define MONEYBAG_ACT_DISAPPEAR                          0x4
    #define MONEYBAG_ACT_DEATH                              0x5
    /* oMoneybagJumpState */
    #define MONEYBAG_JUMP_LANDING                           0x0
    #define MONEYBAG_JUMP_PREPARE                           0x1
    #define MONEYBAG_JUMP_JUMP                              0x2
    #define MONEYBAG_JUMP_JUMP_AND_BOUNCE                   0x3
    #define MONEYBAG_JUMP_WALK_AROUND                       0x4
    #define MONEYBAG_JUMP_WALK_HOME                         0x5

/* Bowling Ball */
    /* oAction */
    #define BBALL_ACT_INITIALIZE                            0x0
    #define BBALL_ACT_ROLL                                  0x1

/* Bowling Ball + Bowling Ball Spawner (all variants) */
    /* oBehParams2ndByte */
    #define BBALL_BP_STYPE_BOB_UPPER                        0x0
    #define BBALL_BP_STYPE_TTM                              0x1
    #define BBALL_BP_STYPE_BOB_LOWER                        0x2
    #define BBALL_BP_STYPE_THI_LARGE                        0x3
    #define BBALL_BP_STYPE_THI_SMALL                        0x4

/* Bowling Ball (Free) */
    /* oAction */
    #define FREE_BBALL_ACT_IDLE                             0x0
    #define FREE_BBALL_ACT_ROLL                             0x1
    #define FREE_BBALL_ACT_RESET                            0x2

/* Beta Chest Lid */
    /* oAction */
    #define BETA_CHEST_ACT_IDLE_CLOSED                      0x0
    #define BETA_CHEST_ACT_OPENING                          0x1
    #define BETA_CHEST_ACT_IDLE_OPEN                        0x2

/* BBH Tilting Trap Platform */
    /* oAction */
    #define BBH_TILTING_TRAP_PLATFORM_ACT_MARIO_ON          0x0
    #define BBH_TILTING_TRAP_PLATFORM_ACT_MARIO_OFF         0x1

/* Boo */
    /* oAction */
    #define BOO_ACT_STOPPED                                 0x0
    #define BOO_ACT_CHASING_MARIO                           0x1
    #define BOO_ACT_BOUNCED_ON                              0x2
    #define BOO_ACT_ATTACKED                                0x3
    #define BOO_ACT_DEATH                                   0x4
    #define BOO_ACT_5                                       0x5

    /* oBehParams2ndByte */
    #define BOO_BP_GHOST_HUNT                               0x0
    #define BOO_BP_NORMAL                                   0x1
    #define BOO_BP_MERRY_GO_ROUND                           0x2

    /* oBooDeathStatus */
    #define BOO_DEATH_STATUS_ALIVE                          0x0
    #define BOO_DEATH_STATUS_DYING                          0x1
    #define BOO_DEATH_STATUS_DEAD                           0x2

    /* attackStatus */
    #define BOO_NOT_ATTACKED                                0x0
    #define BOO_ATTACKED                                    0x1
    #define BOO_BOUNCED_ON                                 -0x1

/* Big Boo */
    /* oBehParams2ndByte */
    #define BIG_BOO_BP_GHOST_HUNT                           0x0
    #define BIG_BOO_BP_MERRY_GO_ROUND                       0x1
    #define BIG_BOO_BP_BALCONY                              0x2

/* Beta Boo Key */
    /* oAction */
    #define BETA_BOO_KEY_ACT_IN_BOO                         0x0
    #define BETA_BOO_KEY_ACT_DROPPING                       0x1
    #define BETA_BOO_KEY_ACT_DROPPED                        0x2

/* Boo Cage */
    /* oAction */
    #define BOO_CAGE_ACT_IN_BOO                             0x0
    #define BOO_CAGE_ACT_FALLING                            0x1
    #define BOO_CAGE_ACT_ON_GROUND                          0x2
    #define BOO_CAGE_ACT_MARIO_JUMPING_IN                   0x3
    #define BOO_CAGE_ACT_USELESS                            0x4

/* BBH Staircase */
    /* oBehParams2ndByte */
    #define BOO_STAIRCASE_BP_0                              0x0
    #define BOO_STAIRCASE_BP_1                              0x1
    #define BOO_STAIRCASE_BP_2                              0x2

/* BBH Haunted Bookshelf */
    /* oAction */
    #define HAUNTED_BOOKSHELF_ACT_IDLE                      0x0
    #define HAUNTED_BOOKSHELF_ACT_RECEDE                    0x1

/* BBH Merry-Go-Round */
    /* gMarioCurrentRoom */
    #define BBH_NEAR_MERRY_GO_ROUND_ROOM                    10
    #define BBH_DYNAMIC_SURFACE_ROOM                        0
    #define BBH_OUTSIDE_ROOM                                13

/* Coffin Spawner */
    /* oAction */
    #define COFFIN_SPAWNER_ACT_COFFINS_UNLOADED             0x0

/* Coffin */
    /* oAction */
    #define COFFIN_ACT_IDLE                                 0x0
    #define COFFIN_ACT_STAND_UP                             0x1

    /* oBehParams2ndByte */
    #define COFFIN_BP_STATIC                                0x0

/* WDW Arrow Lift */
    /* oAction */
    #define ARROW_LIFT_ACT_IDLE                             0x0
    #define ARROW_LIFT_ACT_MOVING_AWAY                      0x1
    #define ARROW_LIFT_ACT_MOVING_BACK                      0x2

    /* status */
    #define ARROW_LIFT_NOT_DONE_MOVING                      0x0
    #define ARROW_LIFT_DONE_MOVING                          0x1

/* Yoshi */
    /* oAction */
    #define YOSHI_ACT_IDLE                                  0x0
    #define YOSHI_ACT_WALK                                  0x1
    #define YOSHI_ACT_TALK                                  0x2
    #define YOSHI_ACT_WALK_JUMP_OFF_ROOF                    0x3
    #define YOSHI_ACT_FINISH_JUMPING_AND_DESPAWN            0x4
    #define YOSHI_ACT_GIVE_PRESENT                          0x5
    #define YOSHI_ACT_CREDITS                               0xA

/* Koopa */
    /* oAction */
    #define KOOPA_UNSHELLED_ACT_RUN                         0x0
    #define KOOPA_UNSHELLED_ACT_DIVE                        0x1
    #define KOOPA_UNSHELLED_ACT_LYING                       0x2
    #define KOOPA_UNSHELLED_ACT_UNUSED3                     0x3

    #define KOOPA_SHELLED_ACT_STOPPED                       0x0
    #define KOOPA_SHELLED_ACT_WALK                          0x1
    #define KOOPA_SHELLED_ACT_RUN_FROM_MARIO                0x2
    #define KOOPA_SHELLED_ACT_LYING                         0x3
    #define KOOPA_SHELLED_ACT_DIE                           0x4

    #define KOOPA_THE_QUICK_ACT_WAIT_BEFORE_RACE            0x0
    #define KOOPA_THE_QUICK_ACT_UNUSED1                     0x1
    #define KOOPA_THE_QUICK_ACT_SHOW_INIT_TEXT              0x2
    #define KOOPA_THE_QUICK_ACT_RACE                        0x3
    #define KOOPA_THE_QUICK_ACT_DECELERATE                  0x4
    #define KOOPA_THE_QUICK_ACT_STOP                        0x5
    #define KOOPA_THE_QUICK_ACT_AFTER_RACE                  0x6

    /* oSubAction */
    #define KOOPA_SHELLED_SUB_ACT_START_WALK                0x0
    #define KOOPA_SHELLED_SUB_ACT_WALK                      0x1
    #define KOOPA_SHELLED_SUB_ACT_STOP_WALK                 0x2

    #define KOOPA_THE_QUICK_SUB_ACT_START_RUN               0x0
    #define KOOPA_THE_QUICK_SUB_ACT_RUN                     0x1
    #define KOOPA_THE_QUICK_SUB_ACT_JUMP                    0x2

    /* oKoopaTheQuickRaceIndex */
    #define KOOPA_THE_QUICK_BOB_INDEX                       0x0
    #define KOOPA_THE_QUICK_THI_INDEX                       0x1

    /* oBehParams2ndByte */
    #define KOOPA_BP_UNSHELLED                              0x0
    #define KOOPA_BP_NORMAL                                 0x1
    #define KOOPA_BP_KOOPA_THE_QUICK_BASE                   0x2
    #define KOOPA_BP_KOOPA_THE_QUICK_BOB                    (KOOPA_BP_KOOPA_THE_QUICK_BASE + KOOPA_THE_QUICK_BOB_INDEX)
    #define KOOPA_BP_KOOPA_THE_QUICK_THI                    (KOOPA_BP_KOOPA_THE_QUICK_BASE + KOOPA_THE_QUICK_THI_INDEX)
    #define KOOPA_BP_TINY                                   0x4

/* Pokey */
    /* oAction */
    #define POKEY_ACT_UNINITIALIZED                         0x0
    #define POKEY_ACT_WANDER                                0x1
    #define POKEY_ACT_UNLOAD_PARTS                          0x2

/* Swoop */
    /* oAction */
    #define SWOOP_ACT_IDLE                                  0x0
    #define SWOOP_ACT_MOVE                                  0x1

/* Fly guy */
    /* oAction */
    #define FLY_GUY_ACT_IDLE                                0x0
    #define FLY_GUY_ACT_APPROACH_MARIO                      0x1
    #define FLY_GUY_ACT_LUNGE                               0x2
    #define FLY_GUY_ACT_SHOOT_FIRE                          0x3

/* Goomba triplet spawner */
    /* oBehParams2ndByte */
    #define GOOMBA_TRIPLET_SPAWNER_BP_SIZE_MASK             0x00000003
    #define GOOMBA_TRIPLET_SPAWNER_BP_EXTRA_GOOMBAS_MASK    0x000000FC
    /* oAction */
    #define GOOMBA_TRIPLET_SPAWNER_ACT_UNLOADED             0x0
    #define GOOMBA_TRIPLET_SPAWNER_ACT_LOADED               0x1

/* Goomba */
    /* oBehParams2ndByte */
    #define GOOMBA_BP_SIZE_MASK                             0x00000003
    #define GOOMBA_SIZE_REGULAR                             0x00000000
    #define GOOMBA_SIZE_HUGE                                0x00000001
    #define GOOMBA_SIZE_TINY                                0x00000002
    #define GOOMBA_BP_TRIPLET_FLAG_MASK                     0x000000FC
    /* oAction */
    #define GOOMBA_ACT_WALK                                 0x0
    #define GOOMBA_ACT_ATTACKED_MARIO                       0x1
    #define GOOMBA_ACT_JUMP                                 0x2

/* Chain chomp */
    /* oAction */
    #define CHAIN_CHOMP_ACT_UNINITIALIZED                   0x0
    #define CHAIN_CHOMP_ACT_MOVE                            0x1
    #define CHAIN_CHOMP_ACT_UNLOAD_CHAIN                    0x2

    /* oSubAction */
    #define CHAIN_CHOMP_SUB_ACT_TURN                        0x0
    #define CHAIN_CHOMP_SUB_ACT_LUNGE                       0x1

    /* oChainChompReleaseStatus */
    #define CHAIN_CHOMP_NOT_RELEASED                        0x0
    #define CHAIN_CHOMP_RELEASED_TRIGGER_CUTSCENE           0x1
    #define CHAIN_CHOMP_RELEASED_LUNGE_AROUND               0x2
    #define CHAIN_CHOMP_RELEASED_BREAK_GATE                 0x3
    #define CHAIN_CHOMP_RELEASED_JUMP_AWAY                  0x4
    #define CHAIN_CHOMP_RELEASED_END_CUTSCENE               0x5

/* Chain chomp chain part */
    /* oBehParams2ndByte */
    #define CHAIN_CHOMP_CHAIN_PART_BP_PIVOT                 0x0

/* Wooden post */
    /* oBehParams */
    #define WOODEN_POST_BP_NO_COINS_MASK                    0x0000FF00

/* Wiggler */
    /* oAction */
    #define WIGGLER_ACT_UNINITIALIZED                       0x0
    #define WIGGLER_ACT_WALK                                0x1
    #define WIGGLER_ACT_KNOCKBACK                           0x2
    #define WIGGLER_ACT_JUMPED_ON                           0x3
    #define WIGGLER_ACT_SHRINK                              0x4
    #define WIGGLER_ACT_FALL_THROUGH_FLOOR                  0x5

    /* oWigglerTextStatus */
    #define WIGGLER_TEXT_STATUS_AWAIT_DIALOG                0x0
    #define WIGGLER_TEXT_STATUS_SHOWING_DIALOG              0x1
    #define WIGGLER_TEXT_STATUS_COMPLETED_DIALOG            0x2

/* Spiny */
    /* oAction */
    #define SPINY_ACT_WALK                                  0x0
    #define SPINY_ACT_HELD_BY_LAKITU                        0x1
    #define SPINY_ACT_THROWN_BY_LAKITU                      0x2
    #define SPINY_ACT_ATTACKED_MARIO                        0x3

/* Evil Lakitu */
    /* oAction */
    #define ENEMY_LAKITU_ACT_UNINITIALIZED                  0x0
    #define ENEMY_LAKITU_ACT_MAIN                           0x1

    /* oSubAction */
    #define ENEMY_LAKITU_SUB_ACT_NO_SPINY                   0x0
    #define ENEMY_LAKITU_SUB_ACT_HOLD_SPINY                 0x1
    #define ENEMY_LAKITU_SUB_ACT_THROW_SPINY                0x2

/* Cloud */
    /* oAction */
    #define CLOUD_ACT_SPAWN_PARTS                           0x0
    #define CLOUD_ACT_MAIN                                  0x1
    #define CLOUD_ACT_UNLOAD                                0x2
    #define CLOUD_ACT_FWOOSH_HIDDEN                         0x3

    /* oBehParams2ndByte */
    #define CLOUD_BP_FWOOSH                                 0x0
    #define CLOUD_BP_LAKITU_CLOUD                           0x1

//! names
/* Intro Lakitu */
    /* oAction */
    #define INTRO_LAKITU_ACT_0                              0x00
    #define INTRO_LAKITU_ACT_1                              0x01
    #define INTRO_LAKITU_ACT_2                              0x02
    #define INTRO_LAKITU_ACT_3                              0x03
    #define INTRO_LAKITU_ACT_100                            0x64
    #define INTRO_LAKITU_ACT_101                            0x65
    #define INTRO_LAKITU_ACT_102                            0x66

/* Camera Lakitu */
    /* oAction */
    #define CAMERA_LAKITU_INTRO_ACT_TRIGGER_CUTSCENE        0x0
    #define CAMERA_LAKITU_INTRO_ACT_SPAWN_CLOUD             0x1
    #define CAMERA_LAKITU_INTRO_ACT_SHOW_DIALOG             0x2

    /* oBehParams2ndByte */
    #define CAMERA_LAKITU_BP_FOLLOW_CAMERA                  0x0
    #define CAMERA_LAKITU_BP_INTRO                          0x1

/* Manta Ray */
    /* oAction */
    #define MANTA_ACT_SPAWN_RINGS                           0x0
    #define MANTA_ACT_NO_RINGS                              0x1

/* Monty mole */
    /* oAction */
    #define MONTY_MOLE_ACT_SELECT_HOLE                      0x0
    #define MONTY_MOLE_ACT_RISE_FROM_HOLE                   0x1
    #define MONTY_MOLE_ACT_SPAWN_ROCK                       0x2
    #define MONTY_MOLE_ACT_BEGIN_JUMP_INTO_HOLE             0x3
    #define MONTY_MOLE_ACT_THROW_ROCK                       0x4
    #define MONTY_MOLE_ACT_JUMP_INTO_HOLE                   0x5
    #define MONTY_MOLE_ACT_HIDE                             0x6
    #define MONTY_MOLE_ACT_JUMP_OUT_OF_HOLE                 0x7

    /* oBehParams2ndByte */
    #define MONTY_MOLE_BP_NO_ROCK                           0x0

/* Monty mole rock */
    /* oAction */
    #define MONTY_MOLE_ROCK_ACT_HELD                        0x0
    #define MONTY_MOLE_ROCK_ACT_MOVE                        0x1

/* Ukiki */
    /* oAction */
    #define UKIKI_ACT_IDLE                                  0x0
    #define UKIKI_ACT_RUN                                   0x1
    #define UKIKI_ACT_TURN_TO_MARIO                         0x2
    #define UKIKI_ACT_JUMP                                  0x3
    #define UKIKI_ACT_GO_TO_CAGE                            0x4
    #define UKIKI_ACT_WAIT_TO_RESPAWN                       0x5
    #define UKIKI_ACT_UNUSED_TURN                           0x6
    #define UKIKI_ACT_RETURN_HOME                           0x7

    /* oSubAction */
    #define UKIKI_SUB_ACT_TAUNT_NONE                        0x0
    #define UKIKI_SUB_ACT_TAUNT_ITCH                        0x1
    #define UKIKI_SUB_ACT_TAUNT_SCREECH                     0x2
    #define UKIKI_SUB_ACT_TAUNT_JUMP_CLAP                   0x3
    #define UKIKI_SUB_ACT_TAUNT_HANDSTAND                   0x4

    #define UKIKI_SUB_ACT_CAGE_RUN_TO_CAGE                  0x0
    #define UKIKI_SUB_ACT_CAGE_WAIT_FOR_MARIO               0x1
    #define UKIKI_SUB_ACT_CAGE_TALK_TO_MARIO                0x2
    #define UKIKI_SUB_ACT_CAGE_TURN_TO_CAGE                 0x3
    #define UKIKI_SUB_ACT_CAGE_JUMP_TO_CAGE                 0x4
    #define UKIKI_SUB_ACT_CAGE_LAND_ON_CAGE                 0x5
    #define UKIKI_SUB_ACT_CAGE_SPIN_ON_CAGE                 0x6
    #define UKIKI_SUB_ACT_CAGE_DESPAWN                      0x7

    /* oUkikiTextState */
    #define UKIKI_TEXT_DEFAULT                              0x0
    #define UKIKI_TEXT_CAGE_TEXTBOX                         0x1
    #define UKIKI_TEXT_GO_TO_CAGE                           0x2
    #define UKIKI_TEXT_STOLE_CAP                            0x3
    #define UKIKI_TEXT_HAS_CAP                              0x4
    #define UKIKI_TEXT_GAVE_CAP_BACK                        0x5
    #define UKIKI_TEXT_DO_NOT_LET_GO                        0x6
    #define UKIKI_TEXT_STEAL_CAP                            0x7

    /* oBehParams2ndByte */
    #define UKIKI_CAGE                                      0x0
    #define UKIKI_CAP                                       0x1

    /* Animations */
    #define UKIKI_ANIM_RUN                                  0x0
    #define UKIKI_ANIM_UNUSED_WALK                          0x1
    #define UKIKI_ANIM_UNUSED_APOSE                         0x2
    #define UKIKI_ANIM_UNUSED_DEATH                         0x3
    #define UKIKI_ANIM_SCREECH                              0x4
    #define UKIKI_ANIM_JUMP_CLAP                            0x5
    #define UKIKI_ANIM_UNUSED_HOP                           0x6
    #define UKIKI_ANIM_LAND                                 0x7
    #define UKIKI_ANIM_JUMP                                 0x8
    #define UKIKI_ANIM_ITCH                                 0x9
    #define UKIKI_ANIM_HANDSTAND                            0xA
    #define UKIKI_ANIM_TURN                                 0xB
    #define UKIKI_ANIM_HELD                                 0xC

    /* oAnimState */
    #define UKIKI_ANIM_STATE_DEFAULT                        0x0
    #define UKIKI_ANIM_STATE_EYE_CLOSED                     0x1
    #define UKIKI_ANIM_STATE_CAP_ON                         0x2

    /* oUkikiHasCap */
    #define UKIKI_CAP_ON                                    0x1

/* Ukiki Cage Star */
    /* oAction */
    #define UKIKI_CAGE_STAR_ACT_IN_CAGE                     0x0
    #define UKIKI_CAGE_STAR_ACT_SPAWN_STAR                  0x1

/* Ukiki Cage */
    /* oAction */
    #define UKIKI_CAGE_ACT_WAIT_FOR_UKIKI                   0x0
    #define UKIKI_CAGE_ACT_SPIN                             0x1
    #define UKIKI_CAGE_ACT_FALL                             0x2
    #define UKIKI_CAGE_ACT_HIDE                             0x3

/* Piranha Plant */
    /* oAction */
    #define PIRANHA_PLANT_ACT_IDLE                          0x0
    #define PIRANHA_PLANT_ACT_SLEEPING                      0x1
    #define PIRANHA_PLANT_ACT_BITING                        0x2
    #define PIRANHA_PLANT_ACT_WOKEN_UP                      0x3
    #define PIRANHA_PLANT_ACT_STOPPED_BITING                0x4
    #define PIRANHA_PLANT_ACT_ATTACKED                      0x5
    #define PIRANHA_PLANT_ACT_SHRINK_AND_DIE                0x6
    #define PIRANHA_PLANT_ACT_WAIT_TO_RESPAWN               0x7
    #define PIRANHA_PLANT_ACT_RESPAWN                       0x8

/* Piranha Plant bubble */
    /* oAction */
    #define PIRANHA_PLANT_BUBBLE_ACT_IDLE                   0x0
    #define PIRANHA_PLANT_BUBBLE_ACT_GROW_SHRINK_LOOP       0x1
    #define PIRANHA_PLANT_BUBBLE_ACT_BURST                  0x2

/* Checkerboard Platform */
    /* oAction */
    #define CHECKERBOARD_PLATFORM_ACT_MOVE_VERTICALLY       0x0
    #define CHECKERBOARD_PLATFORM_ACT_MOVE_UP               0x1
    #define CHECKERBOARD_PLATFORM_ACT_ROTATE_UP             0x2
    #define CHECKERBOARD_PLATFORM_ACT_MOVE_DOWN             0x3
    #define CHECKERBOARD_PLATFORM_ACT_ROTATE_DOWN           0x4

/* Platform on track */
    /* oAction */
    #define PLATFORM_ON_TRACK_ACT_INIT                      0x0
    #define PLATFORM_ON_TRACK_ACT_WAIT_FOR_MARIO            0x1
    #define PLATFORM_ON_TRACK_ACT_MOVE_ALONG_TRACK          0x2
    #define PLATFORM_ON_TRACK_ACT_PAUSE_BRIEFLY             0x3
    #define PLATFORM_ON_TRACK_ACT_FALL                      0x4

    /* oBehParams >> 16 */
    #define PLATFORM_ON_TRACK_BP_MASK_PATH                  0xF
    #define PLATFORM_ON_TRACK_BP_MASK_TYPE                  (0x7 << 4)
    #define PLATFORM_ON_TRACK_BP_RETURN_TO_START            (1 <<  8)
    #define PLATFORM_ON_TRACK_BP_DONT_DISAPPEAR             (1 <<  9)
    #define PLATFORM_ON_TRACK_BP_DONT_TURN_YAW              (1 << 10)
    #define PLATFORM_ON_TRACK_BP_DONT_TURN_ROLL             (1 << 11)

    #define PLATFORM_ON_TRACK_TYPE_CARPET                   0x0
    #define PLATFORM_ON_TRACK_TYPE_SKI_LIFT                 0x1
    #define PLATFORM_ON_TRACK_TYPE_CHECKERED                0x2
    #define PLATFORM_ON_TRACK_TYPE_GRATE                    0x3

/* HMC Controllable Platform */
    /* oAction */

    /* oBehParams2ndByte / sControllablePlatformDirectionState */
    #define DIRECTION_STATE_STOPPED                         0x0
    #define DIRECTION_STATE_SOUTH                           0x1
    #define DIRECTION_STATE_NORTH                           0x2
    #define DIRECTION_STATE_EAST                            0x3
    #define DIRECTION_STATE_WEST                            0x4
    #define DIRECTION_STATE_HIT_WALL                        0x5
    #define DIRECTION_STATE_DISAPPEARING                    0x6

    #define MOVE_DIRECTION_NORTH                            0x1
    #define MOVE_DIRECTION_SOUTH                            0x2
    #define MOVE_DIRECTION_WEST                             0x3
    #define MOVE_DIRECTION_EAST                             0x4

/* Purple switch */
    #define PURPLE_SWITCH_IDLE                              0x0
    #define PURPLE_SWITCH_PRESSED                           0x1
    #define PURPLE_SWITCH_TICKING                           0x2
    #define PURPLE_SWITCH_UNPRESSED                         0x3
    #define PURPLE_SWITCH_WAIT_FOR_MARIO_TO_GET_OFF         0x4

/* Openable Grill Door */
    /* oAction */
    #define OEPNABLE_GRILL_SPAWN                            0x0
    #define OEPNABLE_GRILL_IDLE_CLOSED                      0x1
    #define OEPNABLE_GRILL_OPENING                          0x2
    #define OEPNABLE_GRILL_IDLE_OPEN                        0x3

/* Pyramid elevator */
    #define PYRAMID_ELEVATOR_IDLE                           0x0
    #define PYRAMID_ELEVATOR_START_MOVING                   0x1
    #define PYRAMID_ELEVATOR_CONSTANT_VELOCITY              0x2
    #define PYRAMID_ELEVATOR_AT_BOTTOM                      0x3

/* Pyramid top */
    #define PYRAMID_TOP_ACT_CHECK_IF_SOLVED                 0x0
    #define PYRAMID_TOP_ACT_SPINNING                        0x1
    #define PYRAMID_TOP_ACT_EXPLODE                         0x2

/* Pyramid wall */
    /* oAction */
    #define PYRAMID_WALL_ACT_MOVING_DOWN                    0x0
    #define PYRAMID_WALL_ACT_MOVING_UP                      0x1

    /* oBehParams2ndByte */
    #define PYRAMID_WALL_BP_POSITION_HIGH                   0x0
    #define PYRAMID_WALL_BP_POSITION_MIDDLE                 0x1
    #define PYRAMID_WALL_BP_POSITION_LOW                    0x2

/* Penguins (general) */
    /* Walking sounds */
    #define PENGUIN_WALK_BABY                               0x0
    #define PENGUIN_WALK_BIG                                0x1

    /* Animations */
    #define PENGUIN_ANIM_WALK                               0x0
    #define PENGUIN_ANIM_IDLE                               0x3

/* Racing Penguin */
    /* oAction */
    #define RACING_PENGUIN_ACT_WAIT_FOR_MARIO               0x0
    #define RACING_PENGUIN_ACT_SHOW_INIT_TEXT               0x1
    #define RACING_PENGUIN_ACT_PREPARE_FOR_RACE             0x2
    #define RACING_PENGUIN_ACT_RACE                         0x3
    #define RACING_PENGUIN_ACT_FINISH_RACE                  0x4
    #define RACING_PENGUIN_ACT_SHOW_FINAL_TEXT              0x5

/* Mother Penguin */
    /* oAction */
    #define MOTHER_PENGUIN_ACT_IDLE                         0x0
    #define MOTHER_PENGUIN_ACT_RECEIVE_BABY                 0x1
    #define MOTHER_PENGUIN_ACT_RECEIVED_BABY                0x2
    /* oSubAction */
    /* Act 0 */
    #define MOTHER_PENGUIN_SUB_ACT_READY_TO_ASK             0x0
    #define MOTHER_PENGUIN_SUB_ACT_ASK_FOR_BABY             0x1
    #define MOTHER_PENGUIN_SUB_ACT_ALREADY_ASKED            0x2
    /* Act 1 */
    #define MOTHER_PENGUIN_SUB_ACT_RECEIVE_BABY             0x0
    #define MOTHER_PENGUIN_SUB_ACT_CORRECT_BABY             0x1
    #define MOTHER_PENGUIN_SUB_ACT_WRONG_BABY               0x2
    /* Act 2 */
    #define MOTHER_PENGUIN_SUB_ACT_CHASE_MARIO              0x0
    #define MOTHER_PENGUIN_SUB_ACT_STOP_CHASING_MARIO       0x1

/* Small Penguin */
    /* oAction */
    #define SMALL_PENGUIN_ACT_WALKING                       0x0
    #define SMALL_PENGUIN_ACT_WALKING_TOWARD_MARIO          0x1
    #define SMALL_PENGUIN_ACT_WALKING_AWAY_FROM_MARIO       0x2
    #define SMALL_PENGUIN_ACT_DIVE_SLIDING                  0x3
    #define SMALL_PENGUIN_ACT_DIVE_SLIDING_STOP             0x4
    #define SMALL_PENGUIN_ACT_NEAR_MOTHER                   0x5

/* SL walking Penguin */
    /* oAction */
    #define SL_WALKING_PENGUIN_ACT_MOVING_FORWARDS          0x0
    #define SL_WALKING_PENGUIN_ACT_TURNING_BACK             0x1
    #define SL_WALKING_PENGUIN_ACT_RETURNING                0x2
    #define SL_WALKING_PENGUIN_ACT_TURNING_FORWARDS         0x3

/* Snowman wind */
    /* oSubAction */
    #define SL_SNOWMAN_WIND_ACT_IDLE                        0x0
    #define SL_SNOWMAN_WIND_ACT_TALKING                     0x1
    #define SL_SNOWMAN_WIND_ACT_BLOWING                     0x2

/* Water Bomb Cannon */
    /* oAction */
    #define WATER_BOMB_CANNON_ACT_HIDDEN                    0x0
    #define WATER_BOMB_CANNON_ACT_ACTIVE                    0x1
    #define WATER_BOMB_CANNON_ACT_HIDE                      0x2

/* Water bomb */
    /* oAction */
    #define WATER_BOMB_ACT_SHOT_FROM_CANNON                 0x0
    #define WATER_BOMB_ACT_INIT                             0x1
    #define WATER_BOMB_ACT_DROP                             0x2
    #define WATER_BOMB_ACT_EXPLODE                          0x3

/* TTC rotating solid */
    /* oBehParams2ndByte */
    #define TTC_ROTATING_SOLID_BP_CUBE                      0x0
    #define TTC_ROTATING_SOLID_BP_TRIANGULAR_PRISM          0x1

/* TTC moving bar */
    /* oAction */
    #define TTC_MOVING_BAR_ACT_WAIT                         0x0
    #define TTC_MOVING_BAR_ACT_PULL_BACK                    0x1
    #define TTC_MOVING_BAR_ACT_EXTEND                       0x2
    #define TTC_MOVING_BAR_ACT_RETRACT                      0x3

/* TTC cog */
    /* oBehParams2ndByte */
    #define TTC_COG_BP_SHAPE_MASK                           0x00000002
    #define TTC_COG_BP_SHAPE_HEXAGON                        (0 << 1)
    #define TTC_COG_BP_SHAPE_TRIANGLE                       (1 << 1)
    #define TTC_COG_BP_DIR_MASK                             0x00000001
    #define TTC_COG_BP_DIR_CCW                              (0 << 0) // TODO: Check these
    #define TTC_COG_BP_DIR_CW                               (1 << 0)

/* TTC 2D Rotator */
    /* oBehParams2ndByte */
    #define TTC_2D_ROTATOR_BP_HAND                          0x0
    #define TTC_2D_ROTATOR_BP_2D_COG                        0x1

/* Activated Back-and-Forth Platform */
    /* ((u16)(o->oBehParams >> 16) &         0x0300) >> 8 aka platform type */
    #define ACTIVATED_BF_PLAT_TYPE_BITS_ARROW_PLAT          0x0
    #define ACTIVATED_BF_PLAT_TYPE_BITFS_MESH_PLAT          0x1
    #define ACTIVATED_BF_PLAT_TYPE_BITFS_ELEVATOR           0x2

/* Unagi */
    /* oAction */
    #define UNAGI_SHIP_RESET_PATH                           0x0
    #define UNAGI_SHIP_PATH                                 0x1
    #define UNAGI_RETURN_TO_CAVE                            0x2
    #define UNAGI_IN_CAVE                                   0x3
    #define UNAGI_CAVE_PATH                                 0x4

    /* oAnimState */
    #define UNAGI_ANIM_STATE_NO_STAR                        0x0
    #define UNAGI_ANIM_STATE_HAS_STAR                       0x1
    #define UNAGI_ANIM_STATE_HAS_TRANSPARENT_STAR           0x2

/* Dorrie */
    /* oAction */
    #define DORRIE_ACT_MOVE                                 0x0
    #define DORRIE_ACT_LOWER_HEAD                           0x1
    #define DORRIE_ACT_RAISE_HEAD                           0x2

/* Mad piano */
    /* oAction */
    #define MAD_PIANO_ACT_WAIT                              0x0
    #define MAD_PIANO_ACT_ATTACK                            0x1

/* Haunted Chair */
    /* oAction */
    #define HAUNTED_CHAIR_ACT_0                             0x0
    #define HAUNTED_CHAIR_ACT_1                             0x1

/* Fire piranha plant */
    /* oAction */
    #define FIRE_PIRANHA_PLANT_ACT_HIDE                     0x0
    #define FIRE_PIRANHA_PLANT_ACT_GROW                     0x1

/* Fire spitter */
    /* oAction */
    #define FIRE_SPITTER_ACT_IDLE                           0x0
    #define FIRE_SPITTER_ACT_SPIT_FIRE                      0x1

/* Bouncing Fireball Flame */
    /* oAction */
    #define BOUNCING_FLAME_ACT_SPAWNED                      0x0
    #define BOUNCING_FLAME_ACT_LANDED                       0x1

/* Bouncing Fireball */
    /* oAction */
    #define BOUNCING_FIREBALL_SPAWNER_ACT_IDLE              0x0
    #define BOUNCING_FIREBALL_SPAWNER_ACT_SPAWN_FLAME       0x1
    #define BOUNCING_FIREBALL_SPAWNER_ACT_COOLDOWN          0x2

/* Eyerok boss */
    /* oAction */
    #define EYEROK_BOSS_ACT_SLEEP                           0x0
    #define EYEROK_BOSS_ACT_WAKE_UP                         0x1
    #define EYEROK_BOSS_ACT_SHOW_INTRO_TEXT                 0x2
    #define EYEROK_BOSS_ACT_FIGHT                           0x3
    #define EYEROK_BOSS_ACT_DIE                             0x4

/* Eyerok hand */
    /* oAction */
    #define EYEROK_HAND_ACT_SLEEP                           0x0
    #define EYEROK_HAND_ACT_IDLE                            0x1
    #define EYEROK_HAND_ACT_OPEN                            0x2
    #define EYEROK_HAND_ACT_SHOW_EYE                        0x3
    #define EYEROK_HAND_ACT_CLOSE                           0x4
    #define EYEROK_HAND_ACT_RETREAT                         0x5
    #define EYEROK_HAND_ACT_TARGET_MARIO                    0x6
    #define EYEROK_HAND_ACT_SMASH                           0x7
    #define EYEROK_HAND_ACT_FIST_PUSH                       0x8
    #define EYEROK_HAND_ACT_FIST_SWEEP                      0x9
    #define EYEROK_HAND_ACT_BEGIN_DOUBLE_POUND              0xA // raising for double smash
    #define EYEROK_HAND_ACT_DOUBLE_POUND                    0xB // double smashing
    #define EYEROK_HAND_ACT_ATTACKED                        0xC
    #define EYEROK_HAND_ACT_RECOVER                         0xD
    #define EYEROK_HAND_ACT_BECOME_ACTIVE                   0xE
    #define EYEROK_HAND_ACT_DIE                             0xF

/* King Bobomb */
    /* oAction */
    #define KING_BOBOMB_ACT_INACTIVE                        0x0
    #define KING_BOBOMB_ACT_ACTIVATE                        0x1
    #define KING_BOBOMB_ACT_ACTIVE                          0x2
    #define KING_BOBOMB_ACT_GRABBED_MARIO                   0x3
    #define KING_BOBOMB_ACT_BEEN_THROWN                     0x4
    #define KING_BOBOMB_ACT_RETURN_HOME                     0x5
    #define KING_BOBOMB_ACT_HIT_GROUND                      0x6
    #define KING_BOBOMB_ACT_DEATH                           0x7
    #define KING_BOBOMB_ACT_STOP_MUSIC                      0x8

    /* oSubAction */
    #define KING_BOBOMB_SUB_ACT_RETURN_HOME_0               0x0
    #define KING_BOBOMB_SUB_ACT_RETURN_HOME_1               0x1
    #define KING_BOBOMB_SUB_ACT_RETURN_HOME_2               0x2
    #define KING_BOBOMB_SUB_ACT_RETURN_HOME_3               0x3
    #define KING_BOBOMB_SUB_ACT_RETURN_HOME_DIALOG          0x4

    /* Animations */
    #define KING_BOBOMB_ANIM_GRAB_MARIO                     0x0
    #define KING_BOBOMB_ANIM_HOLDING_MARIO                  0x1
    #define KING_BOBOMB_ANIM_HIT_GROUND                     0x2
    #define KING_BOBOMB_ANIM_UNUSED_3                       0x3
    #define KING_BOBOMB_ANIM_STOMP                          0x4
    #define KING_BOBOMB_ANIM_IDLE                           0x5
    #define KING_BOBOMB_ANIM_HELD                           0x6
    #define KING_BOBOMB_ANIM_T_POSE                         0x7
    #define KING_BOBOMB_ANIM_JUMP                           0x8
    #define KING_BOBOMB_ANIM_THROW_MARIO                    0x9
    #define KING_BOBOMB_ANIM_STAND_UP                       0xA
    #define KING_BOBOMB_ANIM_WALKING                        0xB

/* Chuckya */
    /* oAction */
    #define CHUCKYA_ACT_MOVING                              0x0
    #define CHUCKYA_ACT_GRABBED_MARIO                       0x1
    #define CHUCKYA_ACT_THROWN                              0x2
    #define CHUCKYA_ACT_RELEASE_MARIO                       0x3

    /* oSubAction */
    #define CHUCKYA_SUB_ACT_TURN_TOWARD_MARIO               0x0
    #define CHUCKYA_SUB_ACT_ACCELERATE                      0x1
    #define CHUCKYA_SUB_ACT_STOP                            0x2
    #define CHUCKYA_SUB_ACT_TURN_TOWARD_HOME                0x3

    #define CHUCKYA_SUB_ACT_GRAB_MARIO                      0x0
    #define CHUCKYA_SUB_ACT_HOLD_MARIO                      0x1
    #define CHUCKYA_SUB_ACT_THROW_MARIO                     0x2

    /* oCommonAnchorAction */
    #define COMMON_ANCHOR_ACT_INACTIVE                      0x0
    #define COMMON_ANCHOR_ACT_SET_MARIO_GFX_TO_POS          0x1
    #define COMMON_ANCHOR_ACT_THROW_MARIO                   0x2
    #define COMMON_ANCHOR_ACT_DROP_MARIO                    0x3

    /* Animations */
    #define CHUCKYA_ANIM_GRAB_MARIO                         0x0
    #define CHUCKYA_ANIM_THROW_1                            0x1
    #define CHUCKYA_ANIM_HELD                               0x2
    #define CHUCKYA_ANIM_THROW_2                            0x3
    #define CHUCKYA_ANIM_IDLE                               0x4

/* Klepto */
    /* oAction */
    #define KLEPTO_ACT_CIRCLE_TARGET_HOLDING                0x0
    #define KLEPTO_ACT_APPROACH_TARGET_HOLDING              0x1
    #define KLEPTO_ACT_WAIT_FOR_MARIO                       0x2
    #define KLEPTO_ACT_TURN_TOWARD_MARIO                    0x3
    #define KLEPTO_ACT_DIVE_AT_MARIO                        0x4
    #define KLEPTO_ACT_RESET_POSITION                       0x5
    #define KLEPTO_ACT_STRUCK_BY_MARIO                      0x6
    #define KLEPTO_ACT_RETREAT                              0x7

    /* oAnimState */
    #define KLEPTO_ANIM_STATE_HOLDING_NOTHING               0x0
    #define KLEPTO_ANIM_STATE_HOLDING_CAP                   0x1
    #define KLEPTO_ANIM_STATE_HOLDING_STAR                  0x2
    #define KLEPTO_ANIM_STATE_HOLDING_TRANSPARENT_STAR      0x3

/* Bird */
    /* oAction */
    #define BIRD_ACT_INACTIVE                               0x0
    #define BIRD_ACT_FLY                                    0x1

    /* oBehParams2ndByte */
    #define BIRD_BP_SPAWNED                                 0x0
    #define BIRD_BP_SPAWNER                                 0x1

/* Skeeter */
    /* oAction */
    #define SKEETER_ACT_IDLE                                0x0
    #define SKEETER_ACT_LUNGE                               0x1
    #define SKEETER_ACT_WALK                                0x2

/* Snufit */
    /* oAction */
    #define SNUFIT_ACT_IDLE                                 0x0
    #define SNUFIT_ACT_SHOOT                                0x1

/* Tweester */
    /* oAction */
    #define TWEESTER_ACT_IDLE                               0x0
    #define TWEESTER_ACT_CHASE                              0x1
    #define TWEESTER_ACT_HIDE                               0x2

    /* oSubAction */
    #define TWEESTER_SUB_ACT_WAIT                           0x0

    #define TWEESTER_SUB_ACT_CHASE                          0x0

/* Triplet butterfly */
    /* oAction */
    #define TRIPLET_BUTTERFLY_ACT_INIT                      0x0
    #define TRIPLET_BUTTERFLY_ACT_WANDER                    0x1
    #define TRIPLET_BUTTERFLY_ACT_ACTIVATE                  0x2
    #define TRIPLET_BUTTERFLY_ACT_EXPLODE                   0x3

    /* oBehParams2ndByte */
    #define TRIPLET_BUTTERFLY_BP_BUTTERFLY_NUM              0x3
    #define TRIPLET_BUTTERFLY_BP_NO_BOMBS                   0x4

    /* oTripletButterflyType */
    #define TRIPLET_BUTTERFLY_TYPE_NORMAL                  -0x1
    #define TRIPLET_BUTTERFLY_TYPE_EXPLODES                 0x0
    #define TRIPLET_BUTTERFLY_TYPE_SPAWN_1UP                0x1

/* Water level diamond */
    /* oAction */
    // Loading
    #define WATER_LEVEL_DIAMOND_ACT_INIT                    0x0
    // Idling when Mario isn't inside its hitbox
    #define WATER_LEVEL_DIAMOND_ACT_IDLE                    0x1
    // While the water level is changing
    #define WATER_LEVEL_DIAMOND_ACT_CHANGE_WATER_LEVEL      0x2
    // After the water level has changed but Mario hasn't left its hitbox yet
    #define WATER_LEVEL_DIAMOND_ACT_IDLE_SPINNING           0x3

/* Mips */
    /* oAction */
    #define MIPS_ACT_WAIT_FOR_NEARBY_MARIO                  0x0
    #define MIPS_ACT_FOLLOW_PATH                            0x1
    #define MIPS_ACT_WAIT_FOR_ANIMATION_DONE                0x2
    #define MIPS_ACT_FALL_DOWN                              0x3
    #define MIPS_ACT_IDLE                                   0x4

    /* oMipsStarStatus */
    #define MIPS_STAR_STATUS_HAVENT_SPAWNED_STAR            0x0
    #define MIPS_STAR_STATUS_SHOULD_SPAWN_STAR              0x1
    #define MIPS_STAR_STATUS_ALREADY_SPAWNED_STAR           0x2

/* Falling Pillar */
    /* oAction */
    #define FALLING_PILLAR_ACT_IDLE                         0x0
    #define FALLING_PILLAR_ACT_TURNING                      0x1
    #define FALLING_PILLAR_ACT_FALLING                      0x2

/* Bowser Puzzle */
    /* oAction */
    #define BOWSER_PUZZLE_ACT_SPAWN_PIECES                  0x0
    #define BOWSER_PUZZLE_ACT_WAIT_FOR_COMPLETE             0x1
    #define BOWSER_PUZZLE_ACT_DONE                          0x2

/* Bowser Puzzle Piece */
    /* oAction */
    #define BOWSER_PUZZLE_PIECE_ACT_IDLE                    0x0
    #define BOWSER_PUZZLE_PIECE_ACT_LEFT                    0x1
    #define BOWSER_PUZZLE_PIECE_ACT_RIGHT                   0x2
    #define BOWSER_PUZZLE_PIECE_ACT_UP                      0x3
    #define BOWSER_PUZZLE_PIECE_ACT_DOWN                    0x4

/* Mr Blizzard */
    /* oAction */
    #define MR_BLIZZARD_ACT_SPAWN_SNOWBALL                  0x0
    #define MR_BLIZZARD_ACT_HIDE_UNHIDE                     0x1
    #define MR_BLIZZARD_ACT_RISE_FROM_GROUND                0x2
    #define MR_BLIZZARD_ACT_ROTATE                          0x3
    #define MR_BLIZZARD_ACT_THROW_SNOWBALL                  0x4
    #define MR_BLIZZARD_ACT_BURROW                          0x5
    #define MR_BLIZZARD_ACT_DEATH                           0x6
    #define MR_BLIZZARD_ACT_JUMP                            0x7
    /* oBehParams2ndByte */
    #define MR_BLIZZARD_STYPE_NO_CAP                        0x0
    #define MR_BLIZZARD_STYPE_JUMPING                       0x1

/* Mr I */
    /* oAction */
    #define MR_I_ACT_FAR_AWAY                               0x0
    #define MR_I_ACT_IDLE                                   0x1
    #define MR_I_ACT_LOOKING_AT_MARIO                       0x2
    #define MR_I_ACT_SPIN_DEATH                             0x3

/* Bullet Bill */
    /* oAction */
    #define BULLET_BILL_ACT_RESET                           0x0
    #define BULLET_BILL_ACT_IDLE                            0x1
    #define BULLET_BILL_ACT_CHASING_MARIO                   0x2
    #define BULLET_BILL_ACT_HIT                             0x3

/* WF Kickable Board */
    /* oAction */
    #define KICKABLE_BOARD_ACT_IDLE_VERTICAL                0x0
    #define KICKABLE_BOARD_ACT_ROCKING                      0x1
    #define KICKABLE_BOARD_ACT_FALLING                      0x2
    #define KICKABLE_BOARD_ACT_IDLE_HORIZONTAL              0x3
    /* check_mario_attacking */
    #define WF_ATTACK_NONE                                  0x0
    #define WF_ATTACK_GROUND                                0x1
    #define WF_ATTACK_AIR                                   0x2

#endif // OBJECT_CONSTANTS_H
