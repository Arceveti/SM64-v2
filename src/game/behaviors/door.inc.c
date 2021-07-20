// door.c.inc

struct DoorAction
{
    u32 flag;
    s32 action;
};

static struct DoorAction sDoorActions[] = { { INT_STATUS_WARP_DOOR_ANIM_3, 3 }, { INT_STATUS_WARP_DOOR_ANIM_4, 4 }, { INT_STATUS_DOOR_PULLED, 1 }, { INT_STATUS_DOOR_PUSHED, 2 }, { -1, 0 }, };

static s32 sDoorOpenSounds[] = { SOUND_GENERAL_OPEN_WOOD_DOOR, SOUND_GENERAL_OPEN_IRON_DOOR };

static s32 sDoorCloseSounds[] = { SOUND_GENERAL_CLOSE_WOOD_DOOR, SOUND_GENERAL_CLOSE_IRON_DOOR };

void door_animation_and_reset(s32 sp18) {
    cur_obj_init_animation_with_sound(sp18);
    if (cur_obj_check_if_near_animation_end()) {
        o->oAction = 0;
    }
}

void set_door_camera_event(void) {
    if (segmented_to_virtual(bhvDoor) == o->behavior) {
        gPlayerCameraState->cameraEvent = CAM_EVENT_DOOR;
    } else {
        gPlayerCameraState->cameraEvent = CAM_EVENT_DOOR_WARP;
    }
    gPlayerCameraState->usedObj = o;
}

void play_door_open_noise(void) {
    s32 sp1C = cur_obj_has_model(MODEL_HMC_METAL_DOOR);
    if (o->oTimer == 0) {
        cur_obj_play_sound_2(sDoorOpenSounds[sp1C]);
        gTimeStopState |= TIME_STOP_MARIO_OPENED_DOOR;
    }
    if (o->oTimer == 70) {
        cur_obj_play_sound_2(sDoorCloseSounds[sp1C]);
    }
}

void play_warp_door_open_noise(void) {
    s32 sp1C = cur_obj_has_model(MODEL_HMC_METAL_DOOR);
    if (o->oTimer == 30) {
        cur_obj_play_sound_2(sDoorCloseSounds[sp1C]);
    }
}

void bhv_door_loop(void) {
    s32 sp1C = 0;
    
    while (sDoorActions[sp1C].flag != (u32)~0) {
        if (cur_obj_clear_interact_status_flag(sDoorActions[sp1C].flag)) {
            set_door_camera_event();
            cur_obj_change_action(sDoorActions[sp1C].action);
        }
        sp1C++;
    }

    switch (o->oAction) {
        case 0:
            cur_obj_init_animation_with_sound(0);
            break;
        case 1: // INT_STATUS_DOOR_PULLED
            door_animation_and_reset(1);
            play_door_open_noise();
            break;
        case 2: // INT_STATUS_DOOR_PUSHED
            door_animation_and_reset(2);
            play_door_open_noise();
            break;
        case 3: // INT_STATUS_WARP_DOOR_ANIM_3
            door_animation_and_reset(3);
            play_warp_door_open_noise();
            break;
        case 4: // INT_STATUS_WARP_DOOR_ANIM_4
            door_animation_and_reset(4);
            play_warp_door_open_noise();
            break;
    }
    if (o->oAction == 0) {
        load_object_collision_model();
    }
    bhv_star_door_loop_2();
}

void bhv_door_init(void) {
    f32 x = o->oPosX;
    f32 z = o->oPosZ;
    struct Surface *floor;
    find_floor(x, o->oPosY, z, &floor);
    if (floor != NULL) {
        o->oDoorSelfRoom = floor->room;
    }

    x = o->oPosX + sins(o->oMoveAngleYaw) * 200.0f;
    z = o->oPosZ + coss(o->oMoveAngleYaw) * 200.0f;
    find_floor(x, o->oPosY, z, &floor);
    if (floor != NULL) {
        o->oDoorForwardRoom = floor->room;
    }

    x = o->oPosX + sins(o->oMoveAngleYaw) * -200.0f;
    z = o->oPosZ + coss(o->oMoveAngleYaw) * -200.0f;
    find_floor(x, o->oPosY, z, &floor);
    if (floor != NULL) {
        o->oDoorBackwardRoom = floor->room;
    }

    if (o->oDoorSelfRoom > 0 && o->oDoorSelfRoom < 60) {
        gDoorAdjacentRooms[o->oDoorSelfRoom][0] = o->oDoorForwardRoom;
        gDoorAdjacentRooms[o->oDoorSelfRoom][1] = o->oDoorBackwardRoom;
    }
}

void bhv_star_door_loop_2(void) {
    s32 doorIsRendering = FALSE;
    if (gMarioCurrentRoom != 0) {
        if (o->oDoorSelfRoom == gMarioCurrentRoom) {
            doorIsRendering = TRUE;
        } else if (gMarioCurrentRoom == o->oDoorForwardRoom) {
            doorIsRendering = TRUE;
        } else if (gMarioCurrentRoom == o->oDoorBackwardRoom) {
            doorIsRendering = TRUE;
        } else if (gDoorAdjacentRooms[gMarioCurrentRoom][0] == o->oDoorForwardRoom) {
            doorIsRendering = TRUE;
        } else if (gDoorAdjacentRooms[gMarioCurrentRoom][0] == o->oDoorBackwardRoom) {
            doorIsRendering = TRUE;
        } else if (gDoorAdjacentRooms[gMarioCurrentRoom][1] == o->oDoorForwardRoom) {
            doorIsRendering = TRUE;
        } else if (gDoorAdjacentRooms[gMarioCurrentRoom][1] == o->oDoorBackwardRoom) {
            doorIsRendering = TRUE;
        }
    } else {
        doorIsRendering = TRUE;
    }
    if (doorIsRendering) {
        o->header.gfx.node.flags |= GRAPH_RENDER_ACTIVE;
        D_8035FEE4++;
    }
    if (!doorIsRendering) {
        o->header.gfx.node.flags &= ~GRAPH_RENDER_ACTIVE;
    }
    o->oDoorIsRendering = doorIsRendering;
}
