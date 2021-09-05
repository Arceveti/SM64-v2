#ifndef OBJECT_COLLISION_H
#define OBJECT_COLLISION_H

void   cur_obj_rotate_yaw_and_bounce_off_walls(Angle targetYaw, Angle turnAmount);
Bool32 cur_obj_resolve_object_collisions(       s32 *targetYaw);
Bool32 cur_obj_bounce_off_walls_edges_objects(  s32 *targetYaw);
Bool32 cur_obj_resolve_collisions_and_turn(    Angle targetYaw, Angle turnSpeed);

void detect_object_collisions(void);

#endif // OBJECT_COLLISION_H
