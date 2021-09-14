// whirlpool.c.inc

static struct ObjectHitbox sWhirlpoolHitbox = {
    /* interactType:      */ INTERACT_WHIRLPOOL,
    /* downOffset:        */   0,
    /* damageOrCoinValue: */   0,
    /* health:            */   0,
    /* numLootCoins:      */   0,
    /* radius:            */ 200,
    /* height:            */ 500,
    /* hurtboxRadius:     */   0,
    /* hurtboxHeight:     */   0,
};

void bhv_whirlpool_init(void) {
    o->oWhirlpoolInitFacePitch = o->oFaceAnglePitch;
    o->oWhirlpoolInitFaceRoll  = o->oFaceAngleRoll;
    o->oFaceAnglePitch         = 0x0;
    o->oFaceAngleRoll          = 0x0;
}

void whirlpool_set_hitbox(void) {
    obj_set_hitbox(o, &sWhirlpoolHitbox);
}

void whirpool_orient_graph(void) {
    Vec3n normal;
    f32 cosPitch =             coss(o->oFaceAnglePitch);
    normal[0]    = (cosPitch * sins(o->oFaceAngleRoll));
    normal[1]    = (cosPitch * coss(o->oFaceAngleRoll));
    normal[2]    =             sins(o->oFaceAnglePitch);
    obj_orient_graph(o, normal);
}

void bhv_whirlpool_loop(void) {
    if (o->oDistanceToMario < 5000.0f) {
        o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
        // not sure if actually an array
        gEnvFxBubbleConfig[ENVFX_STATE_PARTICLECOUNT] = 60;
        gEnvFxBubbleConfig[ENVFX_STATE_SRC_X        ] =  o->oPosX;
        gEnvFxBubbleConfig[ENVFX_STATE_SRC_Z        ] =  o->oPosZ;
        gEnvFxBubbleConfig[ENVFX_STATE_DEST_X       ] =  o->oPosX;
        gEnvFxBubbleConfig[ENVFX_STATE_DEST_Y       ] =  o->oPosY;
        gEnvFxBubbleConfig[ENVFX_STATE_DEST_Z       ] =  o->oPosZ;
        gEnvFxBubbleConfig[ENVFX_STATE_SRC_Y        ] = (o->oPosY + 800.0f);
        gEnvFxBubbleConfig[ENVFX_STATE_PITCH        ] = o->oWhirlpoolInitFacePitch;
        gEnvFxBubbleConfig[ENVFX_STATE_YAW          ] = o->oWhirlpoolInitFaceRoll;
        whirpool_orient_graph();
        o->oFaceAngleYaw += 0x1F40;
    } else {
        o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
        gEnvFxBubbleConfig[ENVFX_STATE_PARTICLECOUNT] = 0;
    }
    cur_obj_play_sound_1(SOUND_ENV_WATER);
    whirlpool_set_hitbox();
}

void bhv_jet_stream_loop(void) {
    if (o->oDistanceToMario < 5000.0f) {
        gEnvFxBubbleConfig[ENVFX_STATE_PARTICLECOUNT] = 60;
        gEnvFxBubbleConfig[ENVFX_STATE_SRC_X        ] = o->oPosX;
        gEnvFxBubbleConfig[ENVFX_STATE_SRC_Y        ] = o->oPosY;
        gEnvFxBubbleConfig[ENVFX_STATE_SRC_Z        ] = o->oPosZ;
    } else {
        gEnvFxBubbleConfig[ENVFX_STATE_PARTICLECOUNT] = 0;
    }
    cur_obj_play_sound_1(SOUND_ENV_WATER);
}
