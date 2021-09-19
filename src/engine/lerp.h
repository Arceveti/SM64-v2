#pragma once

#ifdef VARIABLE_FRAMERATE
extern void approach_pos(           f32 *value[3], f32 orig, s32 index);
extern void approach_angle(         s16 *value[3], s16 orig           );
extern void approach_scale(         f32 *value[3], f32 orig, s32 index);

extern void approach_pos_vector(  Vec3f *value,  Vec3f orig, s32 index);
extern void approach_angle_vector(Vec3s *value,  Vec3s orig           );
extern void approach_scale_vector(Vec3f *value,  Vec3f orig, s32 index);
#endif
