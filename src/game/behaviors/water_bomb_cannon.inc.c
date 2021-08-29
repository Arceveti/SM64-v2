// water_bomb_cannon.inc.c

void bhv_bubble_cannon_barrel_loop(void) {
    struct Object *waterBombObj;
    if (o->parentObj->oAction == WATER_BOMB_CANNON_ACT_HIDE) {
        obj_mark_for_deletion(o);
    } else {
        o->oMoveAngleYaw   =  o->parentObj->oFaceAngleYaw;
        o->oMoveAnglePitch = (o->parentObj->oMoveAnglePitch + DEG(90));
        o->oFaceAnglePitch =  o->parentObj->oMoveAnglePitch;
        if ((o->oCannonBarrelBubblesForwardVelCheck += o->oForwardVel) > 0.0f) {
            cur_obj_set_pos_via_transform();
            cur_obj_forward_vel_approach(-5.0f, 18.0f);
        } else {
            o->oCannonBarrelBubblesForwardVelCheck = 0.0f;
            obj_copy_pos(o, o->parentObj);
            // check this
            if (o->parentObj->oWaterCannonIdleTimer != 0) {
                if (o->oForwardVel == 0.0f) {
                    o->oForwardVel = 35.0f;
                    waterBombObj = spawn_object(o, MODEL_WATER_BOMB, bhvWaterBomb);
                    if (waterBombObj != NULL) {
                        waterBombObj->oForwardVel         = -100.0f;
                        waterBombObj->header.gfx.scale[1] =    1.7f;
                    }
                    set_camera_shake_from_point(SHAKE_POS_MEDIUM, o->oPosX, o->oPosY, o->oPosZ);
                }
            } else {
                o->oForwardVel = 0.0f;
            }
        }
    }
}

void water_bomb_cannon_act_hidden_inactive(void) { // act 0
    if (o->oDistanceToMario < 2000.0f) {
        spawn_object(o, MODEL_CANNON_BARREL, bhvCannonBarrelBubbles);
        cur_obj_unhide();
        o->oAction = WATER_BOMB_CANNON_ACT_ACTIVE;
        o->oMoveAnglePitch = o->oWaterCannonTargetMovePitch = 0x1C00;
    }
}

void water_bomb_cannon_act_active(void) { // act 1
    if (o->oDistanceToMario > 2500.0f) {
        o->oAction = WATER_BOMB_CANNON_ACT_HIDE;
    } else if (o->oBehParams2ndByte == WATER_BOMB_CANNON_BP_ACTIVE) {
        if (o->oWaterCannonIdleTimer != 0) {
            o->oWaterCannonIdleTimer--;
        } else {
            cur_obj_move_pitch_approach(o->oWaterCannonTargetMovePitch, 0x80);
            cur_obj_face_yaw_approach(  o->oWaterCannonTargetFaceYaw,  0x100);
            if ((Angle) o->oFaceAngleYaw == (Angle) o->oWaterCannonTargetFaceYaw) {
                if (o->oWaterCannonRotationTimer != 0) {
                    o->oWaterCannonRotationTimer--;
                } else {
                    cur_obj_play_sound_2(SOUND_OBJ_WATER_BOMB_CANNON);
                    o->oWaterCannonIdleTimer = 70;
                    o->oWaterCannonTargetMovePitch = (0x1000 + (0x400 * (random_u16() & 0x3)));
                    o->oWaterCannonTargetFaceYaw   = (-DEG(45) + o->oMoveAngleYaw + (0x1000 * (random_u16() % 5)));
                    o->oWaterCannonRotationTimer   = 60;
                }
            }
        }
    }
}

void water_bomb_cannon_act_hide(void) { // act 2
    cur_obj_hide();
    o->oAction = WATER_BOMB_CANNON_ACT_HIDDEN;
}

void bhv_water_bomb_cannon_loop(void) {
    cur_obj_push_mario_away_from_cylinder(220.0f, 300.0f);
    switch (o->oAction) {
        case WATER_BOMB_CANNON_ACT_HIDDEN: water_bomb_cannon_act_hidden_inactive(); break;
        case WATER_BOMB_CANNON_ACT_ACTIVE: water_bomb_cannon_act_active();          break;
        case WATER_BOMB_CANNON_ACT_HIDE:   water_bomb_cannon_act_hide();            break;
    }
}
