// animated_floor_switch.inc.c

struct FloorSwitchTriggeredAnimationFrame {
    const void *collisionData;
    s16 model;
};

struct FloorSwitchTriggeredAnimationFrame sFloorSwitchTriggeredAnimationFrames[][5] = {
    {
        { bits_seg7_collision_staircase_frame_4,      MODEL_BITS_STAIRCASE_FRAME4      },
        { bits_seg7_collision_staircase_frame_3,      MODEL_BITS_STAIRCASE_FRAME3      },
        { bits_seg7_collision_staircase_frame_2,      MODEL_BITS_STAIRCASE_FRAME2      },
        { bits_seg7_collision_staircase_frame_1,      MODEL_BITS_STAIRCASE_FRAME1      },
        { bits_seg7_collision_staircase,              MODEL_BITS_STAIRCASE             },
    },
    {
        { bitdw_seg7_collision_staircase,             MODEL_BITDW_STAIRCASE            },
        { bitdw_seg7_collision_staircase_frame_1,     MODEL_BITDW_STAIRCASE_FRAME1     },
        { bitdw_seg7_collision_staircase_frame_2,     MODEL_BITDW_STAIRCASE_FRAME2     },
        { bitdw_seg7_collision_staircase_frame_3,     MODEL_BITDW_STAIRCASE_FRAME3     },
        { bitdw_seg7_collision_staircase_frame_4,     MODEL_BITDW_STAIRCASE_FRAME4     },
    },
    {
        { rr_seg7_collision_tricky_triangles_frame_4, MODEL_RR_TRICKY_TRIANGLES_FRAME4 },
        { rr_seg7_collision_tricky_triangles_frame_3, MODEL_RR_TRICKY_TRIANGLES_FRAME3 },
        { rr_seg7_collision_tricky_triangles_frame_2, MODEL_RR_TRICKY_TRIANGLES_FRAME2 },
        { rr_seg7_collision_tricky_triangles_frame_1, MODEL_RR_TRICKY_TRIANGLES_FRAME1 },
        { rr_seg7_collision_tricky_triangles,         MODEL_RR_TRICKY_TRIANGLES        },
    },
};

void bhv_animates_on_floor_switch_press_init(void) {
    o->parentObj = cur_obj_nearest_object_with_behavior(bhvFloorSwitchAnimatesObject);
}

void bhv_animates_on_floor_switch_press_loop(void) {
    if (o->oFloorSwitchPressAnimationSwitchNotTicking) {
        if (o->parentObj->oAction != PURPLE_SWITCH_TICKING) o->oFloorSwitchPressAnimationSwitchNotTicking = FALSE;

        if (o->oFloorSwitchPressAnimationDoResetTime != 0) {
            o->oFloorSwitchPressAnimationTickTimer = o->parentObj->oTimer;
        } else {
            o->oFloorSwitchPressAnimationTickTimer = 0;
        }
    } else if (o->parentObj->oAction == PURPLE_SWITCH_TICKING) {
        o->oFloorSwitchPressAnimationDoResetTime ^= TRUE;
        o->oFloorSwitchPressAnimationSwitchNotTicking = TRUE;
    }

    if (o->oFloorSwitchPressAnimationTickTimer != 0) {
        if (o->oFloorSwitchPressAnimationTickTimer < 60) {
            cur_obj_play_sound_1(SOUND_GENERAL2_SWITCH_TICK_SLOW);
        } else {
            cur_obj_play_sound_1(SOUND_GENERAL2_SWITCH_TICK_FAST);
        }

        if (--o->oFloorSwitchPressAnimationTickTimer == 0) o->oFloorSwitchPressAnimationDoResetTime = FALSE;
        if (o->oFloorSwitchPressAnimationDoubleFrame < 9) o->oFloorSwitchPressAnimationDoubleFrame++;
    } else if ((o->oFloorSwitchPressAnimationDoubleFrame -= 2) < 0) {
        o->oFloorSwitchPressAnimationDoubleFrame = 0;
        o->oFloorSwitchPressAnimationDoResetTime = TRUE;
    }

    o->collisionData = segmented_to_virtual(
        sFloorSwitchTriggeredAnimationFrames[o->oBehParams2ndByte][o->oFloorSwitchPressAnimationDoubleFrame / 2].collisionData);

    cur_obj_set_model(sFloorSwitchTriggeredAnimationFrames[o->oBehParams2ndByte][o->oFloorSwitchPressAnimationDoubleFrame / 2].model);
}
