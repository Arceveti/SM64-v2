// metal_box.c.inc

struct ObjectHitbox sMetalBoxHitbox = {
    /* interactType:      */   0,
    /* downOffset:        */   0,
    /* damageOrCoinValue: */   0,
    /* health:            */   1,
    /* numLootCoins:      */   0,
    /* radius:            */ 220,
    /* height:            */ 300,
    /* hurtboxRadius:     */ 220,
    /* hurtboxHeight:     */ 300,
};

//! move to object_helpers/behavior?
Bool32 check_if_moving_over_floor(f32 maxDist, f32 offset) {
    struct Surface *floor;
    f32 xPos        = (o->oPosX + (sins(o->oMoveAngleYaw) * offset));
    f32 zPos        = (o->oPosZ + (coss(o->oMoveAngleYaw) * offset));
    f32 floorHeight = (find_floor(xPos, (o->oPosY + (o->hitboxHeight / 2)), zPos, &floor) - o->oPosY);
    return (ABSF(floorHeight) < maxDist);
}

void bhv_pushable_loop(void) {
    Angle angleToMario;
    obj_set_hitbox(o, &sMetalBoxHitbox);
    o->oForwardVel = 0.0f;
    if (obj_check_if_collided_with_object(o, gMarioObject) && (gMarioStates[0].flags & MARIO_PUSHING)) {
        angleToMario = obj_angle_to_object(o, gMarioObject);
        if (abs_angle_diff(angleToMario, gMarioObject->oMoveAngleYaw) > DEG(90)) {
            o->oMoveAngleYaw = (Angle)((gMarioObject->oMoveAngleYaw + DEG(45)) & DEG(-90));
            if (check_if_moving_over_floor(8.0f, 150.0f)) {
                o->oForwardVel = 4.0f;
                cur_obj_play_sound_1(SOUND_ENV_METAL_BOX_PUSH);
            }
        }
    }
    cur_obj_move_using_fvel_and_gravity();
}
