#ifndef GD_PARTICLES_H
#define GD_PARTICLES_H

#include <PR/ultratypes.h>

// functions
struct ObjParticle *make_particle(u32 a, s32 b, Vec3f pos);
void move_particles_in_grp(struct ObjGroup *group);

#endif // GD_PARTICLES_H
