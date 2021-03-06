// cap.c.inc

static struct ObjectHitbox sCapHitbox = {
    /* interactType:      */ INTERACT_CAP,
    /* downOffset:        */  0,
    /* damageOrCoinValue: */  0,
    /* health:            */  0,
    /* numLootCoins:      */  0,
    /* radius:            */ 80,
    /* height:            */ 80,
    /* hurtboxRadius:     */ 90,
    /* hurtboxHeight:     */ 90,
};

Bool32 cap_set_hitbox(void) {
    obj_set_hitbox(o, &sCapHitbox);
    if (o->oInteractStatus & INT_STATUS_INTERACTED) {
        obj_mark_for_deletion(o);
        o->oInteractStatus = INT_STATUS_NONE;
        return TRUE;
    }
    return FALSE;
}

void cap_despawn(void) {
    if (o->oTimer > 300) obj_flicker_and_disappear(o, 300);
}

void cap_check_quicksand(void) {
    if (sObjFloor == NULL) return;
    switch (sObjFloor->type) {
        case SURFACE_DEATH_PLANE:
            obj_mark_for_deletion(o);
            break;
        case SURFACE_SHALLOW_QUICKSAND:
        case SURFACE_DEEP_QUICKSAND:
        case SURFACE_QUICKSAND:
            o->oAction     = CAP_ACT_QUICKSAND;
            o->oForwardVel = 0.0f;
            break;
        case SURFACE_DEEP_MOVING_QUICKSAND:
        case SURFACE_SHALLOW_MOVING_QUICKSAND:
        case SURFACE_MOVING_QUICKSAND:
            o->oAction       = CAP_ACT_MOVING_QUICKSAND;
            o->oMoveAngleYaw = ((sObjFloor->force & 0xFF) << 8);
            o->oForwardVel   = (8.0f + (2.0f * -((sObjFloor->force & 0xFF00) >> 8)));
            break;
        case SURFACE_INSTANT_QUICKSAND:
            o->oAction     = CAP_ACT_INSTANT_QUICKSAND;
            o->oForwardVel = 0.0f;
            break;
        case SURFACE_INSTANT_MOVING_QUICKSAND:
            o->oAction       = CAP_ACT_INSTANT_MOVING_QUICKSAND;
            o->oMoveAngleYaw = ((sObjFloor->force & 0xFF) << 8);
            o->oForwardVel   = (8.0f + (2.0f * -((sObjFloor->force & 0xFF00) >> 8)));
            break;
    }
}

void cap_sink_quicksand(void) {
    switch (o->oAction) {
        case CAP_ACT_QUICKSAND:
            if (o->oTimer < 10) {
                o->oGraphYOffset -= 1.0f;
                o->oFaceAnglePitch = DEG(45);
            }
            break;
        case CAP_ACT_MOVING_QUICKSAND:
            if (o->oTimer < 10) o->oGraphYOffset -= 3.0f;
            o->oFaceAnglePitch = DEG(45);
            break;
        case CAP_ACT_INSTANT_QUICKSAND:
            o->oGraphYOffset -= 1.0f;
            if (o->oTimer >= 21) obj_mark_for_deletion(o);
            break;
        case CAP_ACT_INSTANT_MOVING_QUICKSAND:
            o->oGraphYOffset -= 6.0f;
            if (o->oTimer >= 21) obj_mark_for_deletion(o);
            o->oFaceAnglePitch = DEG(45);
            break;
    }
    cap_check_quicksand();
}

void bhv_wing_cap_init(void) {
    o->oGravity  = 1.2f;
    o->oFriction = 0.999f;
    o->oBuoyancy = 0.9f;
    o->oOpacity  = 255;
}

void cap_scale_vertically(void) {
    o->oCapScaleAngle += DEG(45);
    o->header.gfx.scale[1] = ((coss(o->oCapScaleAngle) * 0.3f) + 0.7f);
    if (o->oCapScaleAngle == 0x10000) {
        o->oCapScaleAngle        = 0x0;
        o->oCapDoScaleVertically = 2;
    }
}

void wing_vanish_cap_act_move(void) {
    o->oFaceAngleYaw += o->oForwardVel * 128.0f;
    if (object_step() & OBJ_COL_FLAG_GROUNDED) {
        cap_check_quicksand();
        if (o->oVelY != 0.0f) {
            o->oCapDoScaleVertically = 1;
            o->oVelY = 0.0f;
        }
    }
    if (o->oCapDoScaleVertically) cap_scale_vertically();
}

void bhv_wing_vanish_cap_loop(void) {
    if (o->oAction == CAP_ACT_MOVE) {
        wing_vanish_cap_act_move();
    } else {
        object_step();
        cap_sink_quicksand();
    }
    if (o->oTimer > 20) cur_obj_become_tangible();
    cap_despawn();
    cap_set_hitbox();
}

void bhv_metal_cap_init(void) {
    o->oGravity  = 2.4f;
    o->oFriction = 0.999f;
    o->oBuoyancy = 1.5f;
    o->oOpacity  = 0xFF;
}

void metal_cap_act_move(void) {
    o->oFaceAngleYaw += o->oForwardVel * 128.0f;
    if (object_step() & OBJ_COL_FLAG_GROUNDED) cap_check_quicksand();
}

void bhv_metal_cap_loop(void) {
    if (o->oAction == CAP_ACT_MOVE) {
        metal_cap_act_move();
    } else {
        object_step();
        cap_sink_quicksand();
    }
    if (o->oTimer > 20) cur_obj_become_tangible();
    cap_set_hitbox();
    cap_despawn();
}

void bhv_normal_cap_init(void) {
    o->oGravity  = 0.7f;
    o->oFriction = 0.89f;
    o->oBuoyancy = 0.9f;
    o->oOpacity  = 0xFF;
    save_file_set_cap_pos(o->oPosX, o->oPosY, o->oPosZ);
}

void normal_cap_set_save_flags(void) {
    save_file_clear_flags(SAVE_FLAG_CAP_ON_GROUND);
    switch (gCurrCourseNum) {
        case COURSE_SSL: save_file_set_flags(SAVE_FLAG_CAP_ON_KLEPTO     ); break;
        case COURSE_SL:  save_file_set_flags(SAVE_FLAG_CAP_ON_MR_BLIZZARD); break;
        case COURSE_TTM: save_file_set_flags(SAVE_FLAG_CAP_ON_UKIKI      ); break;
        default:         save_file_set_flags(SAVE_FLAG_CAP_ON_KLEPTO     ); break;
    }
}

void normal_cap_act_move(void) {
    o->oFaceAngleYaw   += o->oForwardVel * 128.0f;
    o->oFaceAnglePitch += o->oForwardVel *  80.0f;
    if (object_step() & OBJ_COL_FLAG_GROUNDED) {
        cap_check_quicksand();
        if (o->oVelY != 0.0f) {
            o->oCapDoScaleVertically = 1;
            o->oVelY                 = 0.0f;
            o->oFaceAnglePitch       = 0x0;
        }
    }
    if (o->oCapDoScaleVertically == 1) cap_scale_vertically();
}

void bhv_normal_cap_loop(void) {
    if (o->oAction == CAP_ACT_MOVE) {
        normal_cap_act_move();
    } else {
        object_step();
        cap_sink_quicksand();
    }
    if ((s32) o->oForwardVel != 0) save_file_set_cap_pos(o->oPosX, o->oPosY, o->oPosZ);
    if (!(o->activeFlags & ACTIVE_FLAG_ACTIVE)) normal_cap_set_save_flags();
    if (cap_set_hitbox()) save_file_clear_flags(SAVE_FLAG_CAP_ON_GROUND);
}

void bhv_vanish_cap_init(void) {
    o->oGravity  = 1.2f;
    o->oFriction = 0.999f;
    o->oBuoyancy = 0.9f;
    o->oOpacity  = 150;
}
