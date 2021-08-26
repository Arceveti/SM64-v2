// sliding_platform.c.inc

void bhv_wf_sliding_platform_init(void) {
    o->oFaceAngleYaw -= DEGREES(90);
    o->oPosX         += 2.0f;
    o->oHomeX         = o->oPosX;
    switch (o->oBehParams2ndByte) {
        case WF_SLID_BRICK_PTFM_BP_MOV_VEL_10: o->oWFSlidBrickPtfmMovVel = 10.0f; break;
        case WF_SLID_BRICK_PTFM_BP_MOV_VEL_15: o->oWFSlidBrickPtfmMovVel = 15.0f; break;
        case WF_SLID_BRICK_PTFM_BP_MOV_VEL_20: o->oWFSlidBrickPtfmMovVel = 20.0f; break;
    }
    o->oTimer = (random_float() * 100.0f);
}

void bhv_wf_sliding_platform_loop(void) {
    switch (o->oAction) {
        case WF_SLID_BRICK_PTFM_ACT_WAIT:
            if (o->oTimer >= 101) {
                o->oAction     = WF_SLID_BRICK_PTFM_ACT_EXTEND;
                o->oForwardVel = o->oWFSlidBrickPtfmMovVel;
            }
            break;
        case WF_SLID_BRICK_PTFM_ACT_EXTEND:
            if (o->oTimer >= (500.0f / o->oWFSlidBrickPtfmMovVel)) {
                o->oForwardVel = 0.0f;
                o->oPosX       = (o->oHomeX + 512.0f);
            }
            if (o->oTimer == 60) {
                o->oAction        = WF_SLID_BRICK_PTFM_ACT_RETRACT;
                o->oForwardVel    = o->oWFSlidBrickPtfmMovVel;
                o->oMoveAngleYaw -= DEGREES(180);
            }
            break;
        case WF_SLID_BRICK_PTFM_ACT_RETRACT:
            if (o->oTimer >= (500.0f / o->oWFSlidBrickPtfmMovVel)) {
                o->oForwardVel = 0.0f;
                o->oPosX       = o->oHomeX;
            }
            if (o->oTimer == 90) {
                o->oAction        = WF_SLID_BRICK_PTFM_ACT_EXTEND;
                o->oForwardVel    = o->oWFSlidBrickPtfmMovVel;
                o->oMoveAngleYaw -= DEGREES(180);
            }
            break;
    }
}
