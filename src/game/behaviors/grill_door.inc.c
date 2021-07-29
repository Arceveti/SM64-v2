// grill_door.c.inc

struct OpenableGrill gOpenableGrills[] = { { 320, MODEL_BOB_BARS_GRILLS, bob_seg7_collision_gate       },
                                           { 410, MODEL_HMC_RED_GRILLS,  hmc_seg7_collision_grill_door } };

void bhv_openable_cage_door_loop(void) {
    if (gCurrentObject->oAction == 0) {
        if (gCurrentObject->parentObj->oOpenableGrillIsOpen) gCurrentObject->oAction++;
    } else if (gCurrentObject->oAction == 1) {
        if (gCurrentObject->oTimer < 64) {
            gCurrentObject->oMoveAngleYaw -= gCurrentObject->oBehParams2ndByte * 0x100;
        } else {
            gCurrentObject->oAction++;
        }
    }
}

void bhv_openable_grill_loop(void) {
    struct Object *grillObj;
    s32 grillIdx;
    switch (o->oAction) {
        case OEPNABLE_GRILL_SPAWN:
            grillIdx = o->oBehParams2ndByte;
            grillObj = spawn_object_relative(-1, gOpenableGrills[grillIdx].halfWidth, 0, 0, o, gOpenableGrills[grillIdx].modelID, bhvOpenableCageDoor);
            grillObj->oMoveAngleYaw += 0x8000;
            obj_set_collision_data(grillObj, gOpenableGrills[grillIdx].collision);
            grillObj = spawn_object_relative(1, -gOpenableGrills[grillIdx].halfWidth, 0, 0, o, gOpenableGrills[grillIdx].modelID, bhvOpenableCageDoor);
            obj_set_collision_data(grillObj, gOpenableGrills[grillIdx].collision);
            o->oAction = OEPNABLE_GRILL_IDLE_CLOSED;
            break;
        case OEPNABLE_GRILL_IDLE_CLOSED:
            if ((o->oOpenableGrillFloorSwitchObj = cur_obj_nearest_object_with_behavior(bhvFloorSwitchGrills)) != NULL) o->oAction = OEPNABLE_GRILL_OPENING;
            break;
        case OEPNABLE_GRILL_OPENING:
            grillObj = o->oOpenableGrillFloorSwitchObj;
            if (grillObj->oAction == 2) {
                o->oOpenableGrillIsOpen = TRUE;
                cur_obj_play_sound_2(SOUND_GENERAL_CAGE_OPEN);
                o->oAction++;
                if (o->oBehParams2ndByte != 0) play_puzzle_jingle();
            }
            break;
        case OEPNABLE_GRILL_IDLE_OPEN:
            break;
    }
}
