// explosion.c.inc

void bhv_explosion_init(void) {
#ifdef PUPPYLIGHTS
    cur_obj_set_light_properties_default(PUPPYLIGHTS_SMALL_EXPLOSION_LIGHT, COLOR_RGBA32_EXPLOSION_LIGHT);
    cur_obj_enable_light();
#endif
    create_sound_spawner(SOUND_GENERAL2_BOBOMB_EXPLOSION);
    set_environmental_camera_shake(SHAKE_ENV_EXPLOSION);
    o->oOpacity = 255;
}

void bhv_explosion_loop(void) {
    s32 i;
    if (o->oTimer == 9) {
        if (find_water_level(o->oPosX, o->oPosZ) > o->oPosY) {
            for ((i = 0); (i < 40); (i++)) spawn_object(o, MODEL_WHITE_PARTICLE_SMALL, bhvBobombExplosionBubble);
        } else {
            spawn_object(o, MODEL_SMOKE, bhvBobombBullyDeathSmoke);
        }
        obj_mark_for_deletion(o);
    }
    o->oOpacity -= 14;
    cur_obj_scale(((f32) o->oTimer / 9.0f) + 1.0f);
}

void bhv_bobomb_bully_death_smoke_init(void) {
    o->oPosY -= 300.0f;
    cur_obj_scale(10.0f);
}

void bhv_bobomb_explosion_bubble_init(void) {
    obj_scale_xyz(o, 2.0f, 2.0f, 1.0f);
    o->oBobombExpBubGfxExpRateX = ((s32)(random_float() * 2048.0f) + 0x800);
    o->oBobombExpBubGfxExpRateY = ((s32)(random_float() * 2048.0f) + 0x800);
    o->oTimer                   =       (random_float() * 10.0f);
    o->oVelY                    = ((s32)(random_float() *  4.0f) + 4.0f);
}

void bhv_bobomb_explosion_bubble_loop(void) {
    f32 waterY = gMarioStates[0].waterLevel;
    o->header.gfx.scale[0] = ((sins(o->oBobombExpBubGfxScaleFacX) * 0.5f) + 2.0f);
    o->oBobombExpBubGfxScaleFacX += o->oBobombExpBubGfxExpRateX;
    o->header.gfx.scale[1] = ((sins(o->oBobombExpBubGfxScaleFacY) * 0.5f) + 2.0f);
    o->oBobombExpBubGfxScaleFacY += o->oBobombExpBubGfxExpRateY;
    if (o->oPosY > waterY) {
        obj_mark_for_deletion(o);
        o->oPosY += 5.0f;
        spawn_object(o, MODEL_SMALL_WATER_SPLASH, bhvObjectWaterSplash);
    }
    if (o->oTimer >= 61) obj_mark_for_deletion(o);
    o->oPosY += o->oVelY;
    o->oTimer++;
}
