// tumbling_bridge.c.inc

#include "levels/wf/header.h"
#include "levels/bbh/header.h"
#include "levels/lll/header.h"
#include "levels/bitfs/header.h"

struct TumblingBridgeType {
    s16 numBridgeSections;
    s16 bridgeRelativeStartingXorZ;
    s16 platformWidth;
    ModelID model;
    const void *segAddr;
};

struct TumblingBridgeType sTumblingBridgeParams[] = {
    { 9, -512, 0x80, MODEL_WF_TUMBLING_BRIDGE_PART,         wf_seg7_collision_tumbling_bridge },
    { 9, -412, 0x67, MODEL_BBH_TUMBLING_PLATFORM_PART,     bbh_seg7_collision_tumbling_bridge },
    { 9, -512, 0x80, MODEL_LLL_FALLING_PLATFORM,           lll_seg7_collision_tumbling_bridge },
    { 9, -512, 0x80, MODEL_BITFS_TUMBLING_PLATFORM_PART, bitfs_seg7_collision_tumbling_bridge }
};

void bhv_tumbling_bridge_platform_loop(void) {
    switch (o->oAction) {
        case TUMBLING_BRIDGE_PLATFORM_ACT_IDLE:
            if (gMarioObject->platform == o) {
                o->oAction = TUMBLING_BRIDGE_PLATFORM_ACT_UNSTABLE;
                o->oTumblingBridgeRollAccel = random_sign() * 0x80;
            }
            break;
        case TUMBLING_BRIDGE_PLATFORM_ACT_UNSTABLE:
            cur_obj_update_floor_height();
            if (o->oTimer > 5) {
                o->oAction = TUMBLING_BRIDGE_PLATFORM_ACT_FALL;
                cur_obj_play_sound_2(SOUND_GENERAL_PLATFORM);
            }
            break;
        case TUMBLING_BRIDGE_PLATFORM_ACT_FALL:
            if (o->oAngleVelPitch <  0x400) o->oAngleVelPitch += 0x80;
            if (o->oAngleVelRoll  > -0x400 && o->oAngleVelRoll < 0x400) o->oAngleVelRoll += o->oTumblingBridgeRollAccel; // acceleration?
            o->oGravity = -3.0f;
            cur_obj_rotate_face_angle_using_vel();
            cur_obj_move_using_fvel_and_gravity();
            if (o->oPosY < o->oFloorHeight - 300.0f) o->oAction = TUMBLING_BRIDGE_PLATFORM_ACT_END;
            break;
        case TUMBLING_BRIDGE_PLATFORM_ACT_END:
            break;
    }
    if (o->parentObj->oAction == TUMBLING_BRIDGE_ACT_RESET) obj_mark_for_deletion(o);
}

void tumbling_bridge_act_spawn_sections(void) { // act 1
    struct Object *platformObj;
    s32 i;
    s32 bridgeID = o->oBehParams2ndByte;
    s32 relativePlatformX;
    s32 relativePlatformZ;
    s32 relativePlatformY        = 0;
    s32 relativeInitialPlatformY = 0;

    for (i = 0; i < sTumblingBridgeParams[bridgeID].numBridgeSections; i++) {
        relativePlatformX = 0;
        relativePlatformZ = 0;

        if (bridgeID == TUMBLING_BRIDGE_BP_BITFS) { // Spawn sideways in BITFS
            relativePlatformX = sTumblingBridgeParams[bridgeID].bridgeRelativeStartingXorZ + sTumblingBridgeParams[bridgeID].platformWidth * i;
        } else {
            relativePlatformZ = sTumblingBridgeParams[bridgeID].bridgeRelativeStartingXorZ + sTumblingBridgeParams[bridgeID].platformWidth * i;
        }

        if (cur_obj_has_behavior(bhvLllTumblingBridge)) {
            if (i % 3 == 0) relativePlatformY -= 150;
            relativeInitialPlatformY = 450;
        }

        platformObj = spawn_object_relative(
            OBJ_BP_NONE, relativePlatformX, relativePlatformY + relativeInitialPlatformY, relativePlatformZ, o,
            sTumblingBridgeParams[bridgeID].model, bhvTumblingBridgePlatform);

        obj_set_collision_data(platformObj, sTumblingBridgeParams[bridgeID].segAddr);
    }

    o->oAction = TUMBLING_BRIDGE_ACT_NEAR;
}

void tumbling_bridge_act_near(void) { // act 2
    cur_obj_hide();
    if (cur_obj_has_behavior(bhvLllTumblingBridge)) {
        cur_obj_unhide();
    } else if (o->oDistanceToMario > 1200.0f) {
        o->oAction = TUMBLING_BRIDGE_ACT_RESET;
        cur_obj_unhide();
    }
}

void tumbling_bridge_act_reset(void) { // act 3
    cur_obj_unhide();
    o->oAction = TUMBLING_BRIDGE_ACT_FAR;
}

void tumbling_bridge_act_far(void) { // act 0
    if (cur_obj_has_behavior(bhvLllTumblingBridge) || o->oDistanceToMario < 1000.0f) o->oAction = TUMBLING_BRIDGE_ACT_SPAWN_SECTIONS;
}

void (*sTumblingBridgeActions[])(void) = { tumbling_bridge_act_far,
                                           tumbling_bridge_act_spawn_sections,
                                           tumbling_bridge_act_near,
                                           tumbling_bridge_act_reset };

void bhv_tumbling_bridge_loop(void) {
    cur_obj_call_action_function(sTumblingBridgeActions);
}
