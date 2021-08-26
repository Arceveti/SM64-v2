// warp.c.inc

void bhv_warp_loop(void) {
    u16 params;
    if (o->oTimer == 0) {
        params = ((o->oBehParams >> 24) & 0xFF);
        if (params == 0) {
            o->hitboxRadius = 50.0f;
        } else if (params == 0xFF) {
            o->hitboxRadius = 10000.0f;
        } else {
            o->hitboxRadius = (params * 10.0f);
        }
        o->hitboxHeight = 50.0f;
    }
    o->oInteractStatus = INT_STATUS_NONE;
}

void bhv_fading_warp_loop() { // identical to the above function except for o->hitboxRadius
#ifdef VISIBLE_FADE_WARPS
    spawn_sparkle_particles(1, 85, 50, 120);
#endif
    u16 params;
    if (o->oTimer == 0) {
        params = ((o->oBehParams >> 24) & 0xFF);
        if (params == 0) {
            o->hitboxRadius = 85.0f;
        } else if (params == 0xFF) {
            o->hitboxRadius = 10000.0f;
        } else {
            o->hitboxRadius = (params * 10.0f);
        }
        o->hitboxHeight = 50.0f;
    }
    o->oInteractStatus = INT_STATUS_NONE;
}
