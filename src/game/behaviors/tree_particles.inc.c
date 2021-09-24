#include "config.h"
// tree_particles.c.inc

void bhv_tree_snow_or_leaf_loop(void) {
    cur_obj_update_floor_height();
    if (o->oTimer == 0) {
        o->oAngleVelPitch                  = ((random_float() - 0.5f) * DEG(22.5));
        o->oAngleVelRoll                   = ((random_float() - 0.5f) * DEG(22.5));
        o->oTreeSnowOrLeafSidewardVel      = 4;
        o->oTreeSnowOrLeafSidewardAngleVel = ((random_float() * 0x400) + 0x600);
    }
    if ((o->oPosY < o->oFloorHeight) || (o->oFloorHeight < FLOOR_LOWER_LIMIT) || (o->oTimer > 100) || (gPrevFrameObjectCount > (OBJECT_POOL_CAPACITY - 28))) obj_mark_for_deletion(o);
    o->oFaceAnglePitch += o->oAngleVelPitch;
    o->oFaceAngleRoll  += o->oAngleVelRoll;
    o->oVelY -= 3.0f;
    if (o->oVelY < -8.0f) o->oVelY = -8.0f;
    if (o->oForwardVel >  0.0f) {
        o->oForwardVel -= 0.3f;
    } else {
        o->oForwardVel  = 0.0f;
    }
    o->oPosX                        += (sins(o->oMoveAngleYaw) * sins(o->oTreeSnowOrLeafSidewardAngle) * o->oTreeSnowOrLeafSidewardVel);
    o->oPosZ                        += (coss(o->oMoveAngleYaw) * sins(o->oTreeSnowOrLeafSidewardAngle) * o->oTreeSnowOrLeafSidewardVel);
    o->oTreeSnowOrLeafSidewardAngle += o->oTreeSnowOrLeafSidewardAngleVel;
    o->oPosY                        += o->oVelY;
}

void bhv_snow_leaf_particle_spawn_init(void) {
    struct Object *obj; // Either snow or leaf
    f32 scale;
    gMarioObject->oActiveParticleFlags &= ~ACTIVE_PARTICLE_LEAF;
    struct Object *nearestTree = cur_obj_nearest_object_with_behavior(bhvTree);
    if (nearestTree == NULL) return;
    if (obj_has_model(nearestTree, MODEL_CCM_SNOW_TREE) || obj_has_model(nearestTree, MODEL_SL_SNOW_TREE)) {
        if (random_float() < 0.5f) {
            obj                  = spawn_object(o, MODEL_WHITE_PARTICLE_DL, bhvTreeSnow);
            scale                = random_float();
            obj_scale(obj, scale);
            obj->oMoveAngleYaw   = random_u16();
            obj->oForwardVel     = (random_float() *  5.0f);
            obj->oVelY           = (random_float() * 15.0f);
        }
    } else {
        if (random_float() < 0.3f) {
            obj                  = spawn_object(o, MODEL_LEAVES, bhvTreeLeaf);
            scale                = (random_float() *  3.0f);
            obj_scale(obj, scale);
            obj->oMoveAngleYaw   = random_u16();
            obj->oForwardVel     = ((random_float() *  5.0f) + 5.0f);
            obj->oVelY           =  (random_float() * 15.0f);
            obj->oFaceAnglePitch = random_u16();
            obj->oFaceAngleRoll  = random_u16();
            obj->oFaceAngleYaw   = random_u16();
        }
    }
}
