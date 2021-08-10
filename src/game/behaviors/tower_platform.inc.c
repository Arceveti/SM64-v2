// tower_platform.c.inc

void bhv_wf_solid_tower_platform_loop(void) {
    if (o->parentObj->oAction == WF_TOWER_PLATFORM_GROUP_ACT_REMOVE_PLATFORMS) obj_mark_for_deletion(o);
}

void bhv_wf_elevator_tower_platform_loop(void) {
    switch (o->oAction) {
        case WF_TOWER_ELEVATOR_PLATFORM_ACT_BOTTOM:
            if (gMarioObject->platform == o) o->oAction = WF_TOWER_ELEVATOR_PLATFORM_ACT_MOVING_UP;
            break;
        case WF_TOWER_ELEVATOR_PLATFORM_ACT_MOVING_UP:
            cur_obj_play_sound_1(SOUND_ENV_ELEVATOR1);
            if (o->oTimer > 140) {
                o->oAction = WF_TOWER_ELEVATOR_PLATFORM_ACT_TOP;
            } else {
                o->oPosY += 5.0f;
            }
            break;
        case WF_TOWER_ELEVATOR_PLATFORM_ACT_TOP:
            if (o->oTimer > 60) o->oAction = WF_TOWER_ELEVATOR_PLATFORM_ACT_MOVING_DOWN;
            break;
        case WF_TOWER_ELEVATOR_PLATFORM_ACT_MOVING_DOWN:
            cur_obj_play_sound_1(SOUND_ENV_ELEVATOR1);
            if (o->oTimer > 140) {
                o->oAction = WF_TOWER_ELEVATOR_PLATFORM_ACT_BOTTOM;
            } else {
                o->oPosY -= 5.0f;
            }
            break;
    }
    if (o->parentObj->oAction == WF_TOWER_PLATFORM_GROUP_ACT_REMOVE_PLATFORMS) obj_mark_for_deletion(o);
}

void bhv_wf_sliding_tower_platform_loop(void) {
    s32 moveTimer = o->oPlatformWFTowerMoveDistance / o->oPlatformWFTowerForwardVel;
    switch (o->oAction) {
        case WF_TOWER_SLIDING_PLATFORM_ACT_BACKWARD:
            if (o->oTimer > moveTimer) o->oAction = WF_TOWER_SLIDING_PLATFORM_ACT_FORWARD;
            o->oForwardVel = -o->oPlatformWFTowerForwardVel;
            break;
        case WF_TOWER_SLIDING_PLATFORM_ACT_FORWARD:
            if (o->oTimer > moveTimer) o->oAction = WF_TOWER_SLIDING_PLATFORM_ACT_BACKWARD;
            o->oForwardVel = o->oPlatformWFTowerForwardVel;
            break;
    }
    cur_obj_compute_vel_xz();
    o->oPosX += o->oVelX;
    o->oPosZ += o->oVelZ;
    if (o->parentObj->oAction == WF_TOWER_PLATFORM_GROUP_ACT_REMOVE_PLATFORMS) obj_mark_for_deletion(o);
}

void spawn_and_init_wf_platforms(s16 model, const BehaviorScript *bhv) {
    struct Object *platform = spawn_object(o, model, bhv);
    s16 yaw = o->oPlatformSpawnerWFTowerPlatformNum * o->oPlatformSpawnerWFTowerDYaw + o->oPlatformSpawnerWFTowerYawOffset;
    platform->oMoveAngleYaw                = yaw;
    platform->oPosX                       += o->oPlatformSpawnerWFTowerRadius * sins(yaw);
    platform->oPosY                       += 100 * o->oPlatformSpawnerWFTowerPlatformNum;
    platform->oPosZ                       += o->oPlatformSpawnerWFTowerRadius * coss(yaw);
    platform->oPlatformWFTowerMoveDistance = o->oPlatformSpawnerWFTowerMoveDistance;
    platform->oPlatformWFTowerForwardVel   = o->oPlatformSpawnerWFTowerForwardVel;
    o->oPlatformSpawnerWFTowerPlatformNum++;
}

void spawn_wf_platform_group(void) {
    o->oPlatformSpawnerWFTowerPlatformNum  = 0;
    o->oPlatformSpawnerWFTowerYawOffset    = 0;
    o->oPlatformSpawnerWFTowerDYaw         = 0x2000;
    o->oPlatformSpawnerWFTowerRadius       = 704.0f;
    o->oPlatformSpawnerWFTowerMoveDistance = 380.0f;
    o->oPlatformSpawnerWFTowerForwardVel   = 3.0f;
    spawn_and_init_wf_platforms(MODEL_WF_TOWER_SQUARE_PLATORM,          bhvWfSolidTowerPlatform);
    spawn_and_init_wf_platforms(MODEL_WF_TOWER_SQUARE_PLATORM,          bhvWfSlidingTowerPlatform);
    spawn_and_init_wf_platforms(MODEL_WF_TOWER_SQUARE_PLATORM,          bhvWfSolidTowerPlatform);
    spawn_and_init_wf_platforms(MODEL_WF_TOWER_SQUARE_PLATORM,          bhvWfSlidingTowerPlatform);
    spawn_and_init_wf_platforms(MODEL_WF_TOWER_SQUARE_PLATORM,          bhvWfSolidTowerPlatform);
    spawn_and_init_wf_platforms(MODEL_WF_TOWER_SQUARE_PLATORM,          bhvWfSlidingTowerPlatform);
    spawn_and_init_wf_platforms(MODEL_WF_TOWER_SQUARE_PLATORM,          bhvWfSolidTowerPlatform);
    spawn_and_init_wf_platforms(MODEL_WF_TOWER_SQUARE_PLATORM_ELEVATOR, bhvWfElevatorTowerPlatform);
}

void bhv_tower_platform_group_loop(void) {
    f32 marioY = gMarioObject->oPosY;
    o->oDistanceToMario = dist_between_objects(o, gMarioObject);
    switch (o->oAction) {
        case WF_TOWER_PLATFORM_GROUP_ACT_INACTIVE:
            if (marioY > o->oHomeY - 1000.0f) o->oAction = WF_TOWER_PLATFORM_GROUP_ACT_SPAWN_PLATFORMS;
            break;
        case WF_TOWER_PLATFORM_GROUP_ACT_SPAWN_PLATFORMS:
            spawn_wf_platform_group();
            o->oAction = WF_TOWER_PLATFORM_GROUP_ACT_ACTIVE;
            break;
        case WF_TOWER_PLATFORM_GROUP_ACT_ACTIVE:
            if (marioY < o->oHomeY - 1000.0f) o->oAction = WF_TOWER_PLATFORM_GROUP_ACT_REMOVE_PLATFORMS;
            break;
        case WF_TOWER_PLATFORM_GROUP_ACT_REMOVE_PLATFORMS:
            o->oAction = WF_TOWER_PLATFORM_GROUP_ACT_INACTIVE;
            break;
    }
}
