// sound_spawner.c.inc

void bhv_sound_spawner_init(void) {
    s32 soundBits = o->oSoundEffectBits;
    play_sound(soundBits, o->header.gfx.cameraToObject);
}
