// jrb_ship.c.inc

struct ObjectHitbox sSkullSlidingBoxHitbox = {
    /* interactType:      */ INTERACT_DAMAGE,
    /* downOffset:        */   0,
    /* damageOrCoinValue: */   1,
    /* health:            */   1,
    /* numLootCoins:      */   0,
    /* radius:            */ 130,
    /* height:            */ 100,
    /* hurtboxRadius:     */   0,
    /* hurtboxHeight:     */   0,
};

void bhv_ship_part_3_loop(void) {
    Angle initialPitch = o->oFaceAnglePitch;
    Angle initialRoll  = o->oFaceAngleRoll;
    cur_obj_set_pos_to_home_with_debug();
    o->oShipPart3LoopPitch += 0x100;
    o->oFaceAnglePitch = (sins(o->oShipPart3LoopPitch) * 1024.0f);
    o->oFaceAngleRoll  = 0x0; // (sins(o->oShipPart3LoopRoll) * 1024.0f);
    o->oAngleVelPitch  = (o->oFaceAnglePitch - initialPitch);
    o->oAngleVelRoll   = (o->oFaceAngleRoll  - initialRoll);
    if (gMarioObject->oPosY > 1000.0f) cur_obj_play_sound_1(SOUND_ENV_BOAT_ROCKING1);
}

void bhv_jrb_sliding_box_loop(void) {
    Mat4 mtx;
    Vec3f shipToBoxPos1, shipToBoxPos2;
    Vec3a shipRotation;
    struct Object *shipObj;
    if (o->oJrbSlidingBoxShipObj == NULL) {
        shipObj = cur_obj_nearest_object_with_behavior(bhvJrbFloatingShipCollision);
        if (shipObj != NULL) {
            o->oJrbSlidingBoxShipObj = shipObj;
            vec3_diff(&o->oParentRelativePosVec, &o->oPosVec, &shipObj->oPosVec);
        }
    } else {
        shipObj = o->oJrbSlidingBoxShipObj;
        vec3_copy(shipRotation, &shipObj->oFaceAngleVec);
        vec3_copy(shipToBoxPos1, &o->oParentRelativePosVec);
        mtxf_rotate_zxy_and_translate(mtx, shipToBoxPos1, shipRotation);
        linear_mtxf_mul_vec3f(mtx, shipToBoxPos2, shipToBoxPos1);
        vec3_sum(&o->oPosVec, &shipObj->oPosVec, shipToBoxPos2);
        o->oFaceAnglePitch = shipObj->oFaceAnglePitch;
    }
    o->oJrbSlidingBoxAdditiveZ = (sins(o->oJrbSlidingBoxAngle) * 20.0f);
    o->oJrbSlidingBoxAngle += 0x100;
    o->oParentRelativePosZ += o->oJrbSlidingBoxAdditiveZ;
    if ((gMarioObject->oPosY > 1000.0f) && (ABSF(o->oJrbSlidingBoxAdditiveZ) > 3.0f)) cur_obj_play_sound_1(SOUND_AIR_ROUGH_SLIDE);
    obj_set_hitbox(o, &sSkullSlidingBoxHitbox);
    if (!(o->oJrbSlidingBoxAngle & 0x7FFF)) cur_obj_become_tangible();
    if (obj_check_if_collided_with_object(o, gMarioObject)) {
        o->oInteractStatus = INT_STATUS_NONE;
        cur_obj_become_intangible();
    }
}
