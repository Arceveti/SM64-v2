// cannon.c.inc

void opened_cannon_act_idle(void) {
    if (o->oTimer == 0) {
        o->oInteractStatus = INT_STATUS_NONE;
        vec3f_copy(&o->oPosVec, &o->oHomeVec);
        o->oMoveAnglePitch = 0x0;
        o->oMoveAngleYaw   = (Angle)(o->oBehParams2ndByte << 8);
        o->oCannonAngle    = 0x0;
        o->oCannonIsActive = FALSE;
        cur_obj_enable_rendering();
        cur_obj_become_tangible();
    }
    if (o->oDistanceToMario < 500.0f) {
        cur_obj_become_tangible();
        cur_obj_enable_rendering();
        if (o->oInteractStatus & INT_STATUS_INTERACTED && (!(o->oInteractStatus & INT_STATUS_TOUCHED_BOB_OMB))) { // bob-omb explodes when it gets into a cannon
            o->oAction                   = OPENED_CANNON_ACT_RISING;
            o->oCannonIsActive           = TRUE;
            o->oCannonTimeSinceActivated = 1;
        } else {
            o->oInteractStatus = INT_STATUS_NONE;
        }
    } else {
        cur_obj_become_intangible();
        cur_obj_disable_rendering();
        o->oCannonIsActive = FALSE;
    }
}

void opened_cannon_act_rising(void) {
    if (o->oTimer == 0) cur_obj_play_sound_2(SOUND_OBJ_CANNON_RISE);
    o->oPosY += 5.0f;
    o->oPosX += ((f32)(((o->oTimer / 2) & 0x1) - 0.5f) * 2.0f);
    o->oPosZ += ((f32)(((o->oTimer / 2) & 0x1) - 0.5f) * 2.0f);
    if (o->oTimer > 67) {
        o->oPosX += ((f32)(((o->oTimer / 2) & 0x1) - 0.5f) * 4.0f);
        o->oPosZ += ((f32)(((o->oTimer / 2) & 0x1) - 0.5f) * 4.0f);
        o->oAction = OPENED_CANNON_ACT_TURNING_YAW;
    }
}

void opened_cannon_act_turning_yaw(void) {
    if (o->oTimer == 0) cur_obj_play_sound_2(SOUND_OBJ_CANNON_TURN);
    if (o->oTimer < 4) {
        o->oPosX += ((f32)(((o->oTimer / 2) & 0x1) - 0.5f) * 4.0f);
        o->oPosZ += ((f32)(((o->oTimer / 2) & 0x1) - 0.5f) * 4.0f);
    } else {
        if (o->oTimer >= 6) {
            if (o->oTimer < 22) {
                o->oMoveAngleYaw = ((sins(o->oCannonAngle) * DEG(90)) + (Angle)(o->oBehParams2ndByte << 8));
                o->oCannonAngle += 0x400;
            } else if (o->oTimer >= 26) {
                o->oCannonAngle = 0x0;
                o->oAction      = OPENED_CANNON_ACT_RAISE_BARREL;
            }
        }
    }
}

void opened_cannon_act_raise_barrel(void) {
    if (o->oTimer == 0) cur_obj_play_sound_2(SOUND_OBJ_CANNON_BARREL_PITCH);
    if (o->oTimer >= 4) {
        if (o->oTimer < 20) {
            o->oCannonAngle += 0x400;
            o->oMoveAnglePitch = (sins(o->oCannonAngle) * DEG(45));
        } else if (o->oTimer >= 25) {
            o->oAction = OPENED_CANNON_ACT_READY;
        }
    }
}

void opened_cannon_act_ready(void) {
    cur_obj_become_intangible();
    cur_obj_disable_rendering();
    o->oCannonIsActive = FALSE;
    gMarioShotFromCannon = TRUE;
}

void opened_cannon_act_shoot(void) {
    o->oAction = OPENED_CANNON_ACT_RESETTING;
}

void opened_cannon_act_resetting(void) {
    if (o->oTimer > 3) o->oAction = OPENED_CANNON_ACT_IDLE;
}

void (*sOpenedCannonActions[])(void) = { opened_cannon_act_idle,
                                         opened_cannon_act_ready,
                                         opened_cannon_act_shoot,
                                         opened_cannon_act_resetting,
                                         opened_cannon_act_rising,
                                         opened_cannon_act_raise_barrel,
                                         opened_cannon_act_turning_yaw };

void bhv_cannon_base_loop(void) {
    cur_obj_call_action_function(sOpenedCannonActions);
    if (o->oCannonTimeSinceActivated) o->oCannonTimeSinceActivated++;
    o->oInteractStatus = INT_STATUS_NONE;
}

void bhv_cannon_barrel_loop(void) {
    struct Object *parent = o->parentObj;
    if (parent->header.gfx.node.flags & GRAPH_RENDER_ACTIVE) {
        cur_obj_enable_rendering();
        obj_copy_pos(o, o->parentObj);
        o->oMoveAngleYaw   = o->parentObj->oMoveAngleYaw;
        o->oFaceAnglePitch = o->parentObj->oMoveAnglePitch;
    } else {
        cur_obj_disable_rendering();
    }
}
