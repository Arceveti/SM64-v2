// grill_door.c.inc

struct OpenableGrill {
    s16 halfWidth;
    ModelID modelID;
    const Collision *collision;
};

struct OpenableGrill gOpenableGrills[] = { { 320, MODEL_BOB_BARS_GRILLS, bob_seg7_collision_gate       },
                                           { 410, MODEL_HMC_RED_GRILLS,  hmc_seg7_collision_grill_door } };

void bhv_openable_grill_door_loop(void) {
    if (o->oAction == OPENABLE_GRILL_DOOR_ACT_CLOSED) {
        if (o->parentObj->oOpenableGrillIsOpen) o->oAction = OPENABLE_GRILL_DOOR_ACT_OPENING;
    } else if (o->oAction == OPENABLE_GRILL_DOOR_ACT_OPENING) {
        if (o->oTimer < 64) {
            o->oMoveAngleYaw -= (o->oBehParams2ndByte * 0x100);
        } else {
            o->oAction = OPENABLE_GRILL_DOOR_ACT_OPEN;
        }
    }
}

void bhv_openable_grill_loop(void) {
    struct Object *grillObj;
    s32 grillIdx;
    switch (o->oAction) {
        case OEPNABLE_GRILL_ACT_SPAWN:
            grillIdx = o->oBehParams2ndByte;
            grillObj = spawn_object_relative(OPENABLE_GRILL_DOOR_BP_SIDE_FLIPPED,    gOpenableGrills[grillIdx].halfWidth, 0, 0, o, gOpenableGrills[grillIdx].modelID, bhvOpenableGrillDoor);
            grillObj->oMoveAngleYaw += DEG(180);
            obj_set_collision_data(grillObj, gOpenableGrills[grillIdx].collision);
            grillObj = spawn_object_relative(OPENABLE_GRILL_DOOR_BP_SIDE_UNFLIPPED, -gOpenableGrills[grillIdx].halfWidth, 0, 0, o, gOpenableGrills[grillIdx].modelID, bhvOpenableGrillDoor);
            obj_set_collision_data(grillObj, gOpenableGrills[grillIdx].collision);
            o->oAction = OEPNABLE_GRILL_IDLE_CLOSED;
            break;
        case OEPNABLE_GRILL_IDLE_CLOSED:
            if ((o->oOpenableGrillFloorSwitchObj = cur_obj_nearest_object_with_behavior(bhvFloorSwitchGrills)) != NULL) o->oAction = OEPNABLE_GRILL_OPENING;
            break;
        case OEPNABLE_GRILL_OPENING:
            grillObj = o->oOpenableGrillFloorSwitchObj;
            if (grillObj->oAction == OPENABLE_GRILL_DOOR_ACT_OPEN) {
                o->oOpenableGrillIsOpen = TRUE;
                cur_obj_play_sound_2(SOUND_GENERAL_CAGE_OPEN);
                o->oAction = OEPNABLE_GRILL_IDLE_OPEN;
                if (o->oBehParams2ndByte != OPENABLE_GRILL_BP_BOB) play_puzzle_jingle();
            }
            break;
        case OEPNABLE_GRILL_IDLE_OPEN:
            break;
    }
}
