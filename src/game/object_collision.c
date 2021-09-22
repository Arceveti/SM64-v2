#include <PR/ultratypes.h>

#include "sm64.h"
#include "debug.h"
#include "interaction.h"
#include "mario.h"
#include "object_list_processor.h"
#include "spawn_object.h"
#include "engine/math_util.h"
#include "object_helpers.h"

struct Object *debug_print_obj_collision(struct Object *a) {
    struct Object *currCollidedObj;
    s32 i;
    for ((i = 0); (i < a->numCollidedObjs); (i++)) {
        print_debug_top_down_objectinfo("ON", 0);
        currCollidedObj = a->collidedObjs[i];
        if (currCollidedObj != gMarioObject) return currCollidedObj;
    }
    return NULL;
}

void cur_obj_rotate_yaw_and_bounce_off_walls(Angle targetYaw, Angle turnAmount) {
    if (o->oMoveFlags & OBJ_MOVE_HIT_WALL) targetYaw = cur_obj_reflect_move_angle_off_wall();
    cur_obj_rotate_yaw_toward(targetYaw, turnAmount);
}

Bool32 cur_obj_resolve_object_collisions(Angle32 *targetYaw) {
    struct Object *otherObject;
    f32 dx, dz;
    Angle angle;
    f32 radius, otherRadius, relativeRadius;
    s32 i;
    if (o->numCollidedObjs != 0) {
        for ((i = 0); (i < o->numCollidedObjs); (i++)) {
            otherObject = o->collidedObjs[i];
            if (otherObject == gMarioObject) continue;
            if (otherObject->oInteractType & INTERACT_MASK_NO_OBJ_COLLISIONS) continue;
            dx             = (o->oPosX - otherObject->oPosX);
            dz             = (o->oPosZ - otherObject->oPosZ);
            radius         = ((          o->hurtboxRadius > 0) ?           o->hurtboxRadius :           o->hitboxRadius);
            otherRadius    = ((otherObject->hurtboxRadius > 0) ? otherObject->hurtboxRadius : otherObject->hitboxRadius);
            relativeRadius = (radius + otherRadius);
            if ((sqr(dx) + sqr(dz)) > sqr(relativeRadius)) continue;
            angle    = atan2s(dz, dx);
            o->oPosX = (otherObject->oPosX + (relativeRadius * sins(angle)));
            o->oPosZ = (otherObject->oPosZ + (relativeRadius * coss(angle)));
            if ((targetYaw != NULL) && (abs_angle_diff(o->oMoveAngleYaw, angle) < DEG(90))) {
                *targetYaw = (Angle)((angle - o->oMoveAngleYaw) + angle + DEG(180));
                return TRUE;
            }
        }
    }
    return FALSE;
}

Bool32 cur_obj_bounce_off_walls_edges_objects(Angle32 *targetYaw) {
    if (o->oMoveFlags & OBJ_MOVE_HIT_WALL) {
        *targetYaw = cur_obj_reflect_move_angle_off_wall();
    } else if (o->oMoveFlags & OBJ_MOVE_HIT_EDGE) {
        *targetYaw = (Angle)(o->oMoveAngleYaw + DEG(180));
    } else if (!cur_obj_resolve_object_collisions(targetYaw)) {
        return FALSE;
    }
    return TRUE;
}

Bool32 cur_obj_resolve_collisions_and_turn(Angle targetYaw, Angle turnSpeed) {
    cur_obj_resolve_object_collisions(NULL);
    return (!cur_obj_rotate_yaw_toward(targetYaw, turnSpeed));
}

Bool32 detect_object_hitbox_overlap(struct Object *a, struct Object *b) {
    f32 dya_bottom      = (a->oPosY - a->hitboxDownOffset);
    f32 dyb_bottom      = (b->oPosY - b->hitboxDownOffset);
    f32 dx              = (a->oPosX - b->oPosX);
    f32 dz              = (a->oPosZ - b->oPosZ);
    f32 collisionRadius = (a->hitboxRadius + b->hitboxRadius);
    if (sqr(collisionRadius) > (sqr(dx) + sqr(dz))) {
        f32 dya_top = (a->hitboxHeight + dya_bottom);
        f32 dyb_top = (b->hitboxHeight + dyb_bottom);
        if (dya_bottom > dyb_top   ) return FALSE;
        if (dya_top    < dyb_bottom) return FALSE;
        if (a->numCollidedObjs >= 4) return FALSE;
        if (b->numCollidedObjs >= 4) return FALSE;
        a->collidedObjs[a->numCollidedObjs] = b;
        b->collidedObjs[b->numCollidedObjs] = a;
        a->collidedObjInteractTypes        |= b->oInteractType;
        b->collidedObjInteractTypes        |= a->oInteractType;
        a->numCollidedObjs++;
        b->numCollidedObjs++;
        return TRUE;
    }
    return FALSE;
}

Bool32 detect_object_hurtbox_overlap(struct Object *a, struct Object *b) {
    f32 dya_bottom      = (a->oPosY - a->hitboxDownOffset);
    f32 dyb_bottom      = (b->oPosY - b->hitboxDownOffset);
    f32 dx              = (a->oPosX - b->oPosX);
    f32 dz              = (a->oPosZ - b->oPosZ);
    f32 collisionRadius = (a->hurtboxRadius + b->hurtboxRadius);
    if (a == gMarioObject) b->oInteractionSubtype |= INT_SUBTYPE_DELAY_INVINCIBILITY;
    if (sqr(collisionRadius) > (sqr(dx) + sqr(dz))) {
        f32 dya_top = (a->hitboxHeight  + dya_bottom);
        f32 dyb_top = (b->hurtboxHeight + dyb_bottom);
        if (dya_bottom > dyb_top   ) return FALSE;
        if (dya_top    < dyb_bottom) return FALSE;
        if (a == gMarioObject) b->oInteractionSubtype &= ~INT_SUBTYPE_DELAY_INVINCIBILITY;
        return TRUE;
    }
    return FALSE;
}

void clear_object_collision(struct Object *a) {
    struct Object *nextObj = (struct Object *) a->header.next;
    while (nextObj != a) {
        nextObj->numCollidedObjs          = 0;
        nextObj->collidedObjInteractTypes = 0;
        if (nextObj->oIntangibleTimer > 0) nextObj->oIntangibleTimer--;
        nextObj = (struct Object *) nextObj->header.next;
    }
}

void check_collision_in_list(struct Object *a, struct Object *b, struct Object *c) {
    if (a->oIntangibleTimer == 0) {
        while (b != c) {
            if ((b->oIntangibleTimer == 0) && detect_object_hitbox_overlap(a, b) && (b->hurtboxRadius != 0.0f)) detect_object_hurtbox_overlap(a, b);
            b = (struct Object *) b->header.next;
        }
    }
}

void check_player_object_collision(void) {
    struct Object *playerObj = (struct Object *) &gObjectLists[OBJ_LIST_PLAYER];
    struct Object   *nextObj = (struct Object *) playerObj->header.next;
    while (nextObj != playerObj) {
        check_collision_in_list(nextObj, (struct Object *) nextObj->header.next, playerObj);
        check_collision_in_list(nextObj, (struct Object *) gObjectLists[OBJ_LIST_POLELIKE   ].next, (struct Object *) &gObjectLists[OBJ_LIST_POLELIKE   ]);
        check_collision_in_list(nextObj, (struct Object *) gObjectLists[OBJ_LIST_LEVEL      ].next, (struct Object *) &gObjectLists[OBJ_LIST_LEVEL      ]);
        check_collision_in_list(nextObj, (struct Object *) gObjectLists[OBJ_LIST_GENACTOR   ].next, (struct Object *) &gObjectLists[OBJ_LIST_GENACTOR   ]);
        check_collision_in_list(nextObj, (struct Object *) gObjectLists[OBJ_LIST_PUSHABLE   ].next, (struct Object *) &gObjectLists[OBJ_LIST_PUSHABLE   ]);
        check_collision_in_list(nextObj, (struct Object *) gObjectLists[OBJ_LIST_SURFACE    ].next, (struct Object *) &gObjectLists[OBJ_LIST_SURFACE    ]);
        check_collision_in_list(nextObj, (struct Object *) gObjectLists[OBJ_LIST_DESTRUCTIVE].next, (struct Object *) &gObjectLists[OBJ_LIST_DESTRUCTIVE]);
        nextObj = (struct Object *) nextObj->header.next;
    }
}

void check_pushable_object_collision(void) {
    struct Object *pushableObj = (struct Object *) &gObjectLists[OBJ_LIST_PUSHABLE];
    struct Object     *nextObj = (struct Object *) pushableObj->header.next;
    while (nextObj != pushableObj) {
        check_collision_in_list(nextObj, (struct Object *) nextObj->header.next, pushableObj);
        nextObj = (struct Object *) nextObj->header.next;
    }
}

void check_destructive_object_collision(void) {
    struct Object *destructiveObj = (struct Object *) &gObjectLists[OBJ_LIST_DESTRUCTIVE];
    struct Object        *nextObj = (struct Object *) destructiveObj->header.next;
    while (nextObj != destructiveObj) {
        if ((nextObj->oDistanceToMario < 2000.0f) && !(nextObj->activeFlags & ACTIVE_FLAG_SMALL_BOX_NOT_THROWN)) {
            check_collision_in_list(nextObj, (struct Object *) nextObj->header.next, destructiveObj);
            check_collision_in_list(nextObj, (struct Object *) gObjectLists[OBJ_LIST_GENACTOR].next, (struct Object *) &gObjectLists[OBJ_LIST_GENACTOR]);
            check_collision_in_list(nextObj, (struct Object *) gObjectLists[OBJ_LIST_PUSHABLE].next, (struct Object *) &gObjectLists[OBJ_LIST_PUSHABLE]);
            check_collision_in_list(nextObj, (struct Object *) gObjectLists[OBJ_LIST_SURFACE ].next, (struct Object *) &gObjectLists[OBJ_LIST_SURFACE]);
        }
        nextObj = (struct Object *) nextObj->header.next;
    }
}

void detect_object_collisions(void) {
    clear_object_collision((struct Object *) &gObjectLists[OBJ_LIST_POLELIKE   ]);
    clear_object_collision((struct Object *) &gObjectLists[OBJ_LIST_PLAYER     ]);
    clear_object_collision((struct Object *) &gObjectLists[OBJ_LIST_PUSHABLE   ]);
    clear_object_collision((struct Object *) &gObjectLists[OBJ_LIST_GENACTOR   ]);
    clear_object_collision((struct Object *) &gObjectLists[OBJ_LIST_LEVEL      ]);
    clear_object_collision((struct Object *) &gObjectLists[OBJ_LIST_SURFACE    ]);
    clear_object_collision((struct Object *) &gObjectLists[OBJ_LIST_DESTRUCTIVE]);
    check_player_object_collision();
    check_destructive_object_collision();
    check_pushable_object_collision();
}
