// ground_particles.c.inc

static struct SpawnParticlesInfo sGlobalMistParticles = { 3, 20, MODEL_MIST             , 20, 10,  5,  0, 0,   0, 30, 30.0f, 1.5f };
static struct SpawnParticlesInfo sSandParticles       = { 0,  5, MODEL_SAND_DUST        ,  0,  0, 20, 20, 0, 252, 30,  5.0f, 2.0f };
static struct SpawnParticlesInfo sSnowParticles       = { 0,  5, MODEL_WHITE_PARTICLE_DL,  0,  0, 20, 20, 0, 252, 30,  2.0f, 2.0f };

void bhv_pound_white_puffs_init(void) {
    clear_particle_flags(ACTIVE_PARTICLE_MIST_CIRCLE);
    spawn_mist_from_global();
}

void spawn_mist_from_global(void) {
    cur_obj_spawn_particles(&sGlobalMistParticles);
}

void bhv_ground_sand_init(void) {
    clear_particle_flags(ACTIVE_PARTICLE_DIRT);
    cur_obj_spawn_particles(&sSandParticles);
}

void spawn_smoke_with_velocity(void) {
    struct Object *smoke = spawn_object_with_scale(o, MODEL_SMOKE, bhvWhitePuffSmoke2, 1.0f);
    smoke->oForwardVel =  2.0f;
    smoke->oVelY       = -8.0f;
    smoke->oGravity    =  1.0f;
    obj_translate_xyz_random(smoke, 4.0f);
}

// TODO Fix name
void clear_particle_flags(u32 flags) {
    o->parentObj->oActiveParticleFlags &= ~flags; // Clear the flags given
}

void bhv_ground_snow_init(void) {
    clear_particle_flags(ACTIVE_PARTICLE_SNOW);
    cur_obj_spawn_particles(&sSnowParticles);
}
