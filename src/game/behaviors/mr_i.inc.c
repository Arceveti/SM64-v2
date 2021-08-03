// mr_i.c.inc

// this is actually the MrI particle loop function. piranha
// plant code later on reuses this function.
void bhv_piranha_particle_loop(void) {
    if (o->oTimer == 0) {
        o->oVelY       = 20.0f + 20.0f * random_float();
        o->oForwardVel = 20.0f + 20.0f * random_float();
        o->oMoveAngleYaw = random_u16();
    }
    cur_obj_move_using_fvel_and_gravity();
}

void mr_i_piranha_particle_act_move(void) {
    cur_obj_scale(3.0f);
    o->oForwardVel = 20.0f;
    cur_obj_update_floor_and_walls();
    if (o->oInteractStatus & INT_STATUS_INTERACTED) {
        o->oAction = MR_I_PIRANHA_PARTICLE_ACT_INTERACTED;
    } else if ((o->oTimer >= 101) || (o->oMoveFlags & OBJ_MOVE_HIT_WALL) || o->activeFlags & ACTIVE_FLAG_IN_DIFFERENT_ROOM) {
        obj_mark_for_deletion(o);
        spawn_mist_particles();
    }
}

void mr_i_piranha_particle_act_interacted(void) {
    s32 i;
    obj_mark_for_deletion(o);
    for (i = 0; i < 10; i++) spawn_object(o, MODEL_PURPLE_MARBLE, bhvPurpleParticle);
}

void (*sMrIParticleActions[])(void) = { mr_i_piranha_particle_act_move, mr_i_piranha_particle_act_interacted };

void bhv_mr_i_particle_loop(void) {
    cur_obj_call_action_function(sMrIParticleActions);
}

void spawn_mr_i_particle(void) {
    struct Object *particle;
    f32 scaleY = o->header.gfx.scale[1];
    particle = spawn_object(o, MODEL_PURPLE_MARBLE, bhvMrIParticle);
    particle->oPosY += 50.0f * scaleY;
    particle->oPosX += sins(o->oMoveAngleYaw) * 90.0f * scaleY;
    particle->oPosZ += coss(o->oMoveAngleYaw) * 90.0f * scaleY;
    cur_obj_play_sound_2(SOUND_OBJ_MRI_SHOOT);
}

void bhv_mr_i_body_loop(void) {
    obj_copy_pos_and_angle(o, o->parentObj);
    if (!(o->activeFlags & ACTIVE_FLAG_IN_DIFFERENT_ROOM)) {
        obj_copy_scale(o, o->parentObj);
        obj_set_parent_relative_pos(o, 0, 0, o->header.gfx.scale[1] * 100.0f);
        obj_build_transform_from_pos_and_angle(o, 44, 15);
        obj_translate_local(o, 6, 44);
        o->oFaceAnglePitch = o->oMoveAnglePitch;
        o->oGraphYOffset = o->header.gfx.scale[1] * 100.0f;
    }
    if (!o->parentObj->oMrIBlinking) {
        o->oAnimState = -1;
    } else {
        o->oAnimState++;
        if (o->oAnimState == 15) o->parentObj->oMrIBlinking = FALSE;
    }
    if (o->parentObj->activeFlags == ACTIVE_FLAG_DEACTIVATED) {
        obj_mark_for_deletion(o);
    }
}

void mr_i_act_spin_death(void) {
    s16 startYaw;
    f32 shakeY;
    f32 baseScale;
    f32 BBHScaleModifier = o->oBehParams2ndByte ? 2.0f : 1.0f;
    s16 direction = (o->oMrISpinDirection < 0) ? 0x1000 : -0x1000;
    f32 spinAmount = (o->oTimer + 1) / 96.0f;
    if (o->oTimer < 64) {
        startYaw = o->oMoveAngleYaw;
        o->oMoveAngleYaw += direction * coss(0x4000 * spinAmount);
        if (startYaw < 0 && o->oMoveAngleYaw >= 0) cur_obj_play_sound_2(SOUND_OBJ2_MRI_SPINNING);
        o->oMoveAnglePitch = (1.0f - coss(0x4000 * spinAmount)) * -0x4000;
        cur_obj_shake_y(4.0f);
    } else if (o->oTimer < 96) {
        if (o->oTimer == 64) cur_obj_play_sound_2(SOUND_OBJ_MRI_DEATH);
        shakeY = (f32)(o->oTimer - 63) / 32;
        o->oMoveAngleYaw += direction * coss(0x4000 * spinAmount);
        o->oMoveAnglePitch = (1.0f - coss(0x4000 * spinAmount)) * -0x4000;
        cur_obj_shake_y((s32)((1.0f - shakeY) * 4)); // trucating the f32?
        baseScale = coss(0x4000 * shakeY) * 0.4f + 0.6f;
        cur_obj_scale(baseScale * BBHScaleModifier);
    } else if (o->oTimer < 104) {
        // do nothing
    } else if (o->oTimer < 168) {
        if (o->oTimer == 104) {
            cur_obj_become_intangible();
            spawn_mist_particles();
            o->oMrISize = BBHScaleModifier * 0.6f;
            if (o->oBehParams2ndByte) {
                o->oPosY += 100.0f;
                spawn_default_star(1370, 2000.0f, -320.0f);
                obj_mark_for_deletion(o);
            } else {
                cur_obj_spawn_loot_blue_coin();
            }
        }
        o->oMrISize -= 0.2f * BBHScaleModifier;
        if (o->oMrISize < 0) o->oMrISize = 0; // Prevent negative scale
        cur_obj_scale(o->oMrISize);
    } else {
        obj_mark_for_deletion(o);
    }
}

void mr_i_act_looking_at_mario(void) {
    s16 dYaw;
    s16 startYaw = o->oMoveAngleYaw;
    if (o->oTimer == 0) {
        o->oMrISpinAngle     = (o->oBehParams2ndByte) ? 200 : 120;
        o->oMrISpinAmount    = 0;
        o->oMrISpinDirection = 0;
        o->oMrIParticleTimer = 0;
    }
    obj_turn_toward_object(o, gMarioObject, 0x10, 0x800);
    obj_turn_toward_object(o, gMarioObject, 0x0F, 0x400);
    dYaw = startYaw - (s16)(o->oMoveAngleYaw);
    if (!dYaw) {
        o->oMrISpinAmount = 0;
        o->oMrISpinDirection = 0;
    } else if (dYaw > 0) {
        if (o->oMrISpinDirection > 0) {
            o->oMrISpinAmount += dYaw;
        } else {
            o->oMrISpinAmount = 0;
        }
        o->oMrISpinDirection = 1;
    } else {
        if (o->oMrISpinDirection < 0) {
            o->oMrISpinAmount -= dYaw;
        } else {
            o->oMrISpinAmount = 0;
        }
        o->oMrISpinDirection = -1;
    }
    if (!o->oMrISpinAmount) o->oMrISpinAngle = 120;
    if (o->oMrISpinAmount > (1 << 16)) o->oAction = MR_I_ACT_SPIN_DEATH;
    o->oMrISpinAngle--;
    if (!o->oMrISpinAngle) {
        o->oMrISpinAngle = 120;
        o->oMrISpinAmount = 0;
    }
    if (o->oMrISpinAmount < 5000) {
        if (o->oMrIParticleTimer == o->oMrIParticleTimerTarget) o->oMrIBlinking = TRUE;
        if (o->oMrIParticleTimer == o->oMrIParticleTimerTarget + 20) {
            spawn_mr_i_particle();
            o->oMrIParticleTimer = 0;
            o->oMrIParticleTimerTarget = (s32)(random_float() * 50.0f + 50.0f);
        }
        o->oMrIParticleTimer++;
    } else {
        o->oMrIParticleTimer = 0;
        o->oMrIParticleTimerTarget = (s32)(random_float() * 50.0f + 50.0f);
    }
    if (o->oDistanceToMario > 800.0f) o->oAction = MR_I_ACT_IDLE;
}

void mr_i_act_idle(void) {
    s16 angleToMario = obj_angle_to_object(o, gMarioObject);
    s16 angleDiffMoveYawToMario = abs_angle_diff(o->oMoveAngleYaw, angleToMario);
    s16 angleDiffMoveYawToMarioFaceYaw = abs_angle_diff(o->oMoveAngleYaw, gMarioObject->oFaceAngleYaw);
    if (o->oTimer == 0) {
        cur_obj_become_tangible();
        o->oMoveAnglePitch         = 0;
        o->oMrIParticleTimer       = 30;
        o->oMrIParticleTimerTarget = random_float() * 20.0f;
        o->oAngleVelYaw            = (o->oMrIParticleTimerTarget & 1) ? -256 : 256;
    }
    if (angleDiffMoveYawToMario < 1024 && angleDiffMoveYawToMarioFaceYaw > 0x4000) {
        if (o->oDistanceToMario < 700.0f) {
            o->oAction = MR_I_ACT_LOOKING_AT_MARIO;
        } else {
            o->oMrIParticleTimer++;
        }
    } else {
        o->oMoveAngleYaw += o->oAngleVelYaw;
        o->oMrIParticleTimer = 30;
    }
    if (o->oMrIParticleTimer == o->oMrIParticleTimerTarget + 60) o->oMrIBlinking = TRUE;
    if (o->oMrIParticleTimerTarget + 80 < o->oMrIParticleTimer) {
        o->oMrIParticleTimer       = 0;
        o->oMrIParticleTimerTarget = random_float() * 80.0f;
        spawn_mr_i_particle();
    }
}

void mr_i_act_far_away(void) {
    obj_set_angle(o, 0, 0, 0);
    cur_obj_scale(o->oBehParams2ndByte + 1);
    if (o->oTimer == 0) cur_obj_set_pos_to_home();
    if (o->oDistanceToMario < 1500.0f) o->oAction = MR_I_ACT_IDLE;
}

void (*sMrIActions[])(void) = { mr_i_act_far_away, mr_i_act_idle, mr_i_act_looking_at_mario, mr_i_act_spin_death };

struct ObjectHitbox sMrIHitbox = {
    /* interactType:      */ INTERACT_DAMAGE,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 2,
    /* health:            */ 2,
    /* numLootCoins:      */ 5,
    /* radius:            */ 80,
    /* height:            */ 150,
    /* hurtboxRadius:     */ 0,
    /* hurtboxHeight:     */ 0,
};

void bhv_mr_i_loop(void) {
    obj_set_hitbox(o, &sMrIHitbox);
    cur_obj_call_action_function(sMrIActions);
    if (o->oAction != MR_I_ACT_SPIN_DEATH && (o->oDistanceToMario > 3000.0f || o->activeFlags & ACTIVE_FLAG_IN_DIFFERENT_ROOM)) o->oAction = MR_I_ACT_FAR_AWAY;
    o->oInteractStatus = INT_STATUS_NONE;
}
