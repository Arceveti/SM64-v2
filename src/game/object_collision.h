#pragma once

void   cur_obj_rotate_yaw_and_bounce_off_walls( Angle  targetYaw, Angle turnAmount);
Bool32 cur_obj_resolve_object_collisions(     Angle32 *targetYaw);
Bool32 cur_obj_bounce_off_walls_edges_objects(Angle32 *targetYaw);
Bool32 cur_obj_resolve_collisions_and_turn(     Angle  targetYaw, Angle turnSpeed);

void detect_object_collisions(void);
