// controllable_platform.c.inc

static s8 sControllablePlatformDirectionState = DIRECTION_STATE_STOPPED;

void controllable_platform_button_act_pressed(void) {
    o->oParentRelativePosY -= 4.0f;
    if (o->oParentRelativePosY < 41.0f) {
        o->oParentRelativePosY = 41.0f;
        o->oAction = CONTROLLABLE_PLATFORM_BUTTON_ACT_CHECK_UNPRESS;
    }
}

void controllable_platform_act_check_unpress(void) {
    if (o->oBehParams2ndByte == sControllablePlatformDirectionState) return;

    o->oParentRelativePosY += 4.0f;
    if (o->oParentRelativePosY > 51.0f) {
        o->oParentRelativePosY = 51.0f;
        o->oAction = CONTROLLABLE_PLATFORM_ACT_UNPRESSED;
    }
}

void bhv_controllable_platform_sub_loop(void) {
    switch (o->oAction) {
        case CONTROLLABLE_PLATFORM_ACT_UNPRESSED:
            if (o->oTimer < 30) break;

            if (gMarioObject->platform == o) {
                sControllablePlatformDirectionState = o->oBehParams2ndByte;
                o->parentObj->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
                o->oAction = CONTROLLABLE_PLATFORM_BUTTON_ACT_PRESSED;
                cur_obj_play_sound_2(SOUND_GENERAL_MOVING_PLATFORM_SWITCH);
            }
            break;

        case CONTROLLABLE_PLATFORM_BUTTON_ACT_PRESSED:
            controllable_platform_button_act_pressed();
            break;

        case CONTROLLABLE_PLATFORM_BUTTON_ACT_CHECK_UNPRESS:
            controllable_platform_act_check_unpress();
            break;
    }

    o->oVelX = o->parentObj->oVelX;
    o->oVelZ = o->parentObj->oVelZ;

    if (o->parentObj->activeFlags == ACTIVE_FLAG_DEACTIVATED) o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
}

void bhv_controllable_platform_init(void) {
    struct Object *buttonObj;
    buttonObj = spawn_object_rel_with_rot(o, MODEL_HMC_METAL_ARROW_PLATFORM, bhvControllablePlatformButton,    0, 51,  205, 0,       0, 0);
    buttonObj->oBehParams2ndByte = DIRECTION_STATE_SOUTH;
    buttonObj = spawn_object_rel_with_rot(o, MODEL_HMC_METAL_ARROW_PLATFORM, bhvControllablePlatformButton,    0, 51, -205, 0, -0x8000, 0);
    buttonObj->oBehParams2ndByte = DIRECTION_STATE_NORTH;
    buttonObj = spawn_object_rel_with_rot(o, MODEL_HMC_METAL_ARROW_PLATFORM, bhvControllablePlatformButton,  205, 51,    0, 0,  0x4000, 0);
    buttonObj->oBehParams2ndByte = DIRECTION_STATE_EAST;
    buttonObj = spawn_object_rel_with_rot(o, MODEL_HMC_METAL_ARROW_PLATFORM, bhvControllablePlatformButton, -205, 51,    0, 0, -0x4000, 0);
    buttonObj->oBehParams2ndByte = DIRECTION_STATE_WEST;

    sControllablePlatformDirectionState = DIRECTION_STATE_STOPPED;

    o->oControllablePlatformInitPosY = o->oPosY;
}

void controllable_platform_hit_wall(s8 nextDirection) {
    o->oControllablePlatformWallHitDirection = nextDirection;
    o->oTimer = 0;
    sControllablePlatformDirectionState = DIRECTION_STATE_HIT_WALL;

    cur_obj_play_sound_2(SOUND_GENERAL_QUIET_POUND1);
#if ENABLE_RUMBLE
    queue_rumble_data(50, 80);
#endif
}

void controllable_platform_check_walls(s8 nextDirection, s8 wallDisplacement[3], Vec3f dist1, UNUSED Vec3f dist2, Vec3f dist3) {
    if (wallDisplacement[1] == 1 || (wallDisplacement[0] == 1 && wallDisplacement[2] == 1)) {
        controllable_platform_hit_wall(nextDirection);
    } else {
        if (wallDisplacement[0] == 1) {
            if (((nextDirection == MOVE_DIRECTION_SOUTH || nextDirection == MOVE_DIRECTION_NORTH) && (s32) dist1[2] != 0)
             || ((nextDirection == MOVE_DIRECTION_WEST  || nextDirection == MOVE_DIRECTION_EAST ) && (s32) dist1[0] != 0)) {
                controllable_platform_hit_wall(nextDirection);
            } else {
                o->oPosX += dist1[0];
                o->oPosZ += dist1[2];
            }
        }

        if (wallDisplacement[2] == 1) {
            if (((nextDirection == MOVE_DIRECTION_SOUTH || nextDirection == MOVE_DIRECTION_NORTH) && (s32) dist3[2] != 0)
             || ((nextDirection == MOVE_DIRECTION_WEST  || nextDirection == MOVE_DIRECTION_EAST ) && (s32) dist3[0] != 0)) {
                controllable_platform_hit_wall(nextDirection);
            } else {
                o->oPosX += dist3[0];
                o->oPosZ += dist3[2];
            }
        }
    }

    if (!is_point_within_radius_of_mario(o->oPosX, o->oPosY, o->oPosZ, 400)) {
        sControllablePlatformDirectionState = DIRECTION_STATE_DISAPPEARING;
        o->oControllablePlatformIsFarFromMario = TRUE;
        o->oTimer = 0;
    }
}

void controllable_platform_shake_on_wall_hit(void) {
    if (o->oControllablePlatformWallHitDirection == 1 || o->oControllablePlatformWallHitDirection == 2) {
        o->oFaceAnglePitch = sins(o->oTimer * 0x1000) * 182.04444f * 10.0f;
        o->oPosY = o->oControllablePlatformInitPosY + sins(o->oTimer * 0x2000) * 20.0f;
    } else {
        o->oFaceAngleRoll  = sins(o->oTimer * 0x1000) * 182.04444f * 10.0f;
        o->oPosY = o->oControllablePlatformInitPosY + sins(o->oTimer * 0x2000) * 20.0f;
    }

    if (o->oTimer == 32) {
        sControllablePlatformDirectionState = o->oControllablePlatformWallHitDirection;
        o->oFaceAnglePitch = 0x0;
        o->oFaceAngleRoll  = 0x0;
        o->oPosY = o->oControllablePlatformInitPosY;
    }
}

void controllable_platform_tilt_from_mario(void) {
    s16 dx = gMarioObject->header.gfx.pos[0] - o->oPosX;
    s16 dz = gMarioObject->header.gfx.pos[2] - o->oPosZ;

    if (gMarioObject->platform == o || gMarioObject->platform == cur_obj_nearest_object_with_behavior(bhvControllablePlatformButton)) {
        o->oFaceAnglePitch = dz * 4;
        o->oFaceAngleRoll = -dx * 4;
        if (sControllablePlatformDirectionState == DIRECTION_STATE_DISAPPEARING) {
            sControllablePlatformDirectionState = DIRECTION_STATE_STOPPED;
            o->oTimer = 0;
            o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
        }
    }
}

void bhv_controllable_platform_loop(void) {
    s8 wallDisplacement[3];
    Vec3f dist1;
    Vec3f dist2;
    Vec3f dist3;

    o->oAngleVelRoll  = 0x0;
    o->oAngleVelPitch = 0x0;
    o->oVelX          = 0.0f;
    o->oVelZ          = 0.0f;

    switch (sControllablePlatformDirectionState) {
        case DIRECTION_STATE_STOPPED:
            o->oFaceAnglePitch /= 2;
            o->oFaceAngleRoll  /= 2;
            if (o->oControllablePlatformIsFarFromMario == 1 && o->oTimer > 30) {
                sControllablePlatformDirectionState = 6;
                o->oTimer = 0;
            }
            break;

        case DIRECTION_STATE_SOUTH:
            o->oVelZ = 10.0f;
            wallDisplacement[0] = obj_find_wall_displacement(dist1, o->oPosX + 250.0f, o->oPosY, o->oPosZ + 300.0f, 50.0f);
            // wallDisplacement[1] = obj_find_wall_displacement(dist2, o->oPosX         , o->oPosY, o->oPosZ + 300.0f, 50.0f);
            wallDisplacement[2] = obj_find_wall_displacement(dist3, o->oPosX - 250.0f, o->oPosY, o->oPosZ + 300.0f, 50.0f);
            controllable_platform_check_walls(MOVE_DIRECTION_SOUTH, wallDisplacement, dist1, dist2, dist3);
            break;

        case DIRECTION_STATE_NORTH:
            o->oVelZ = -10.0f;
            wallDisplacement[0] = obj_find_wall_displacement(dist1, o->oPosX + 250.0f, o->oPosY, o->oPosZ - 300.0f, 50.0f);
            // wallDisplacement[1] = obj_find_wall_displacement(dist2, o->oPosX         , o->oPosY, o->oPosZ - 300.0f, 50.0f);
            wallDisplacement[2] = obj_find_wall_displacement(dist3, o->oPosX - 250.0f, o->oPosY, o->oPosZ - 300.0f, 50.0f);
            controllable_platform_check_walls(MOVE_DIRECTION_NORTH, wallDisplacement, dist1, dist2, dist3);
            break;

        case DIRECTION_STATE_EAST:
            o->oVelX = 10.0f;
            wallDisplacement[0] = obj_find_wall_displacement(dist1, o->oPosX + 300.0f, o->oPosY, o->oPosZ + 250.0f, 50.0f);
            // wallDisplacement[1] = obj_find_wall_displacement(dist2, o->oPosX + 300.0f, o->oPosY, o->oPosZ         , 50.0f);
            wallDisplacement[2] = obj_find_wall_displacement(dist3, o->oPosX + 300.0f, o->oPosY, o->oPosZ - 250.0f, 50.0f);
            controllable_platform_check_walls(MOVE_DIRECTION_EAST, wallDisplacement, dist1, dist2, dist3);
            break;

        case DIRECTION_STATE_WEST:
            o->oVelX = -10.0f;
            wallDisplacement[0] = obj_find_wall_displacement(dist1, o->oPosX - 300.0f, o->oPosY, o->oPosZ + 250.0f, 50.0f);
            // wallDisplacement[1] = obj_find_wall_displacement(dist2, o->oPosX - 300.0f, o->oPosY, o->oPosZ         , 50.0f);
            wallDisplacement[2] = obj_find_wall_displacement(dist3, o->oPosX - 300.0f, o->oPosY, o->oPosZ - 250.0f, 50.0f);
            controllable_platform_check_walls(MOVE_DIRECTION_WEST, wallDisplacement, dist1, dist2, dist3);
            break;

        case DIRECTION_STATE_HIT_WALL:
            controllable_platform_shake_on_wall_hit();
            return;
            break;

        case DIRECTION_STATE_DISAPPEARING:
            if (obj_flicker_and_disappear(o, 150)) spawn_object_abs_with_rot(o, 0, MODEL_HMC_METAL_PLATFORM, bhvControllablePlatform, o->oHomeX, o->oHomeY, o->oHomeZ, 0x0, 0x0, 0x0);
            break;
    }

    controllable_platform_tilt_from_mario();
    o->oPosX += o->oVelX;
    o->oPosZ += o->oVelZ;
    if (sControllablePlatformDirectionState != DIRECTION_STATE_STOPPED
     && sControllablePlatformDirectionState != DIRECTION_STATE_DISAPPEARING) cur_obj_play_sound_1(SOUND_ENV_ELEVATOR2);
}
