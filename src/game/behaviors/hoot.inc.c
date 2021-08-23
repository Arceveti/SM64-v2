// hoot.c.inc

void bhv_hoot_init(void) {
    cur_obj_init_animation(HOOT_ANIM_DEFAULT);
    o->oHomeX = (o->oPosX + 800.0f);
    o->oHomeY = (o->oPosY - 150.0f);
    o->oHomeZ = (o->oPosZ + 300.0f);
    o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
    cur_obj_become_intangible();
}

f32 hoot_find_next_floor(struct FloorGeometry **floorGeo, f32 dist) {
    f32 nextX = ((dist * sins(o->oMoveAngleYaw)) + o->oPosX);
    f32 nextZ = ((dist * coss(o->oMoveAngleYaw)) + o->oPosZ);
    return find_floor_height_and_data(nextX, 10000.0f, nextZ, floorGeo);;
}

void hoot_floor_bounce(void) {
    struct FloorGeometry *floorGeo;
    f32 floorY  = hoot_find_next_floor(&floorGeo, 375.0f);
    if ((floorY +  75.0f) > o->oPosY) o->oMoveAnglePitch -= 3640.8888f;
    floorY      = hoot_find_next_floor(&floorGeo, 200.0f);
    if ((floorY + 125.0f) > o->oPosY) o->oMoveAnglePitch -= 7281.7776f;
    floorY      = hoot_find_next_floor(&floorGeo,   0.0f);
    if ((floorY + 125.0f) > o->oPosY) o->oPosY = (floorY + 125.0f);
    if (o->oMoveAnglePitch < -21845.3328f) o->oMoveAnglePitch = -21845;
}

void hoot_free_step(s16 fastOscY, s32 speed) {
    struct FloorGeometry *floorGeo;
    Angle yaw             = o->oMoveAngleYaw;
    Angle pitch           = o->oMoveAnglePitch;
    AnimFrame16 animFrame = o->header.gfx.animInfo.animFrame;
    f32 xPrev             = o->oPosX;
    f32 zPrev             = o->oPosZ;
    o->oVelY              = (sins(pitch) *  speed);
    f32 hSpeed            = (coss(pitch) *  speed);
    o->oVelX              = (sins(yaw)   * hSpeed);
    o->oVelZ              = (coss(yaw)   * hSpeed);
    o->oPosX             += o->oVelX;
    o->oPosY             -= (o->oVelY + (coss((s32)(animFrame * ((fastOscY == 0) ? 3276.8f : 6553.6f))) * 50.0f / 4));
    o->oPosZ             += o->oVelZ;
    find_floor_height_and_data(o->oPosX, o->oPosY, o->oPosZ, &floorGeo);
    if (floorGeo == NULL) {
        o->oPosX = xPrev;
        o->oPosZ = zPrev;
    }
    if (animFrame == 0) cur_obj_play_sound_2(SOUND_GENERAL_WING_FLAP);
}

void hoot_player_set_yaw(void) {
#ifdef HOOT_YAW_FIX
    Angle turnSpeed  = (gMarioState->intendedMag * 0x20);
    // o->oMoveAngleYaw = (gMarioState->intendedYaw - approach_s32((Angle)(gMarioState->intendedYaw - o->oMoveAngleYaw), 0x0, turnSpeed, turnSpeed));
    o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, gMarioState->intendedYaw, turnSpeed);
#else
    s16 stickX = gPlayer3Controller->rawStickX;
    s16 stickY = gPlayer3Controller->rawStickY;
    if ((stickX < 10) && (stickX > -10)) stickX = 0;
    if ((stickY < 10) && (stickY > -10)) stickY = 0;
    o->oMoveAngleYaw -= (5 * stickX);
#endif
}

void hoot_carry_step(s32 speed) {
    Angle yaw             = o->oMoveAngleYaw;
    Angle pitch           = o->oMoveAnglePitch;
    AnimFrame16 animFrame = o->header.gfx.animInfo.animFrame;
    o->oVelY              = (sins(pitch) *  speed);
    f32 hSpeed            = (coss(pitch) *  speed);
    o->oVelX              = (sins(yaw)   * hSpeed);
    o->oVelZ              = (coss(yaw)   * hSpeed);
    o->oPosX             +=  o->oVelX;
    o->oPosY             -= (o->oVelY + (coss((s32)(animFrame * 6553.6f)) * 50.0f / 4));
    o->oPosZ             +=  o->oVelZ;
    if (animFrame == 0) cur_obj_play_sound_2(SOUND_GENERAL_WING_FLAP);
}

void hoot_surface_collision(f32 xPrev, f32 zPrev) {
    struct FloorGeometry *floorGeo;
    struct WallCollisionData hitbox;
    hitbox.x       = o->oPosX;
    hitbox.y       = o->oPosY;
    hitbox.z       = o->oPosZ;
    hitbox.offsetY = 10.0f;
    hitbox.radius  = 50.0f;
    if (find_wall_collisions(&hitbox) != 0) {
        o->oPosX = hitbox.x;
        o->oPosY = hitbox.y;
        o->oPosZ = hitbox.z;
        gMarioObject->oInteractStatus |= INT_STATUS_MARIO_DROP_FROM_HOOT; /* bit 7 */
    }
    f32 floorY = find_floor_height_and_data(o->oPosX, o->oPosY, o->oPosZ, &floorGeo);
    if (floorGeo == NULL) {
        o->oPosX = xPrev;
        o->oPosZ = zPrev;
        return;
    }
    if (absf(o->oPosX) > 8000.0f) o->oPosX = xPrev;
    if (absf(o->oPosZ) > 8000.0f) o->oPosZ = zPrev;
    if (floorY + 125.0f > o->oPosY) o->oPosY = floorY + 125.0f;
}

void hoot_act_ascent(void) {
    o->oMoveAngleYaw   = approach_s16_symmetric(o->oMoveAngleYaw, atan2s(-o->oPosZ, -o->oPosX), 0x500);
    o->oMoveAnglePitch = 0xCE38;
    if (o->oTimer >= 29) {
        cur_obj_play_sound_1(SOUND_ENV_WIND2);
        o->header.gfx.animInfo.animFrame = 1;
    }
    if (o->oPosY > 6500.0f) o->oAction = HOOT_ACT_CARRY;
    hoot_carry_step(60);
}

void hoot_action_loop(void) {
    f32 xPrev = o->oPosX;
    // f32 yPrev = o->oPosY;
    f32 zPrev = o->oPosZ;
    switch (o->oAction) {
        case HOOT_ACT_ASCENT:
            hoot_act_ascent();
            break;
        case HOOT_ACT_CARRY:
            hoot_player_set_yaw();
            o->oMoveAnglePitch = 0x71C;
            if (o->oPosY < 2700.0f) {
                set_time_stop_flags(TIME_STOP_ENABLED | TIME_STOP_MARIO_AND_DOORS);
                if (cutscene_object_with_dialog(CUTSCENE_DIALOG, o, DIALOG_045)) {
                    clear_time_stop_flags(TIME_STOP_ENABLED | TIME_STOP_MARIO_AND_DOORS);
                    o->oAction = HOOT_ACT_TIRED;
                }
            }
            hoot_carry_step(20);
            break;
        case HOOT_ACT_TIRED:
            hoot_player_set_yaw();
            o->oMoveAnglePitch = 0x0;
            hoot_carry_step(20);
            if (o->oTimer >= 61) gMarioObject->oInteractStatus |= INT_STATUS_MARIO_DROP_FROM_HOOT; /* bit 7 */
            break;
    }
    hoot_surface_collision(xPrev, zPrev);
}

void hoot_turn_to_home(void) {
    Vec3f homeDist;
    vec3f_diff(homeDist, &o->oHomeVec, &o->oPosVec);
    s16 hAngleToHome   = atan2s(homeDist[2], homeDist[1]);
    s16 vAngleToHome   = atan2s(sqrtf(sqr(homeDist[1]) + sqr(homeDist[2])), -homeDist[1]);
    o->oMoveAngleYaw   = approach_s16_symmetric(o->oMoveAngleYaw  , hAngleToHome, 0x140);
    o->oMoveAnglePitch = approach_s16_symmetric(o->oMoveAnglePitch, vAngleToHome, 0x140);
}

void hoot_awake_loop(void) {
    if (o->oInteractStatus == TRUE) { //! Note: Not a flag, treated as a TRUE/FALSE statement
        hoot_action_loop();
        cur_obj_init_animation(HOOT_ANIM_HOLDING_MARIO);
    } else {
        cur_obj_init_animation(HOOT_ANIM_DEFAULT);
        hoot_turn_to_home();
        hoot_floor_bounce();
        hoot_free_step(0, 10);
        o->oAction = HOOT_ACT_ASCENT;
        o->oTimer  = 0;
    }
    set_object_visibility(o, 2000);
}

void bhv_hoot_loop(void) {
#ifdef HOOT_TREE_PARTICLES
    struct Object *obj;
    f32 scale;
#endif
    switch (o->oHootAvailability) {
        case HOOT_AVAIL_ASLEEP_IN_TREE:
            if (is_point_within_radius_of_mario(o->oPosX, o->oPosY, o->oPosZ, 50)) {
                o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
                o->oHootAvailability      =  HOOT_AVAIL_WANTS_TO_TALK;
            }
#ifdef HOOT_TREE_PARTICLES
            if (random_float() < 0.05f) {
                obj                  = spawn_object(o, MODEL_LEAVES, bhvTreeLeaf);
                scale                = (random_float() * 3.0f);
                obj_scale(obj, scale);
                obj->oMoveAngleYaw   = random_u16();
                obj->oForwardVel     = ((random_float() *  5.0f) + 5.0f);
                obj->oVelY           =  (random_float() * 15.0f);
                obj->oFaceAnglePitch = random_u16();
                obj->oFaceAngleRoll  = random_u16();
                obj->oFaceAngleYaw   = random_u16();
            }
#endif
            break;
        case HOOT_AVAIL_WANTS_TO_TALK:
            hoot_awake_loop();
            if (set_mario_npc_dialog(MARIO_DIALOG_LOOK_UP) == MARIO_DIALOG_STATUS_SPEAK 
                && cutscene_object_with_dialog(CUTSCENE_DIALOG, o, DIALOG_044)) {
                set_mario_npc_dialog(MARIO_DIALOG_STOP);
                cur_obj_become_tangible();
                o->oHootAvailability = HOOT_AVAIL_READY_TO_FLY;
            }
            break;
        case HOOT_AVAIL_READY_TO_FLY:
            hoot_awake_loop();
            break;
    }
}
