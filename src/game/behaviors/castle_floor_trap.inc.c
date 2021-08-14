// castle_floor_trap.c.inc

void bhv_floor_trap_in_castle_loop(void) {
    if (gMarioObject->platform == o) o->parentObj->oInteractStatus |= INT_STATUS_TRAP_TURN;
    o->oFaceAngleRoll = o->parentObj->oFaceAngleRoll;
}

void bhv_castle_floor_trap_init(void) {
    struct Object *floorTrapObj;
    floorTrapObj = spawn_object_relative(OBJ_BP_NONE, -358, 0, 0, o, MODEL_CASTLE_BOWSER_TRAP, bhvFloorTrapInCastle);
    floorTrapObj = spawn_object_relative(OBJ_BP_NONE,  358, 0, 0, o, MODEL_CASTLE_BOWSER_TRAP, bhvFloorTrapInCastle);
    floorTrapObj->oMoveAngleYaw += 0x8000;
}

void bhv_castle_floor_trap_open_detect(void) {
    if (gMarioStates[0].action == ACT_SPECIAL_EXIT_AIRBORNE
     || gMarioStates[0].action == ACT_SPECIAL_DEATH_EXIT) {
        o->oAction = CASTLE_FLOOR_TRAP_ACT_ROTATE; // rotates trapdoor so it looks always open
    } else {
        o->oAngleVelRoll = 0x400;
        if (o->oInteractStatus & INT_STATUS_TRAP_TURN) o->oAction = CASTLE_FLOOR_TRAP_ACT_OPEN; // detects interact then opens the trapdoor
    }
}

void bhv_castle_floor_trap_open(void) {
    if (o->oTimer == 0) play_sound(SOUND_GENERAL_CASTLE_TRAP_OPEN, gGlobalSoundSource);
    o->oAngleVelRoll  -= 0x100;
    o->oFaceAngleRoll += o->oAngleVelRoll;
    if (o->oFaceAngleRoll < -0x4000) {
        o->oFaceAngleRoll = -0x4000;
        o->oAction = CASTLE_FLOOR_TRAP_ACT_CLOSE_DETECT; // after opening is done, enable close detection
    }
}

void bhv_castle_floor_trap_close_detect(void) {
    if (o->oDistanceToMario > 1000.0f) o->oAction = CASTLE_FLOOR_TRAP_ACT_CLOSE; // close trapdoor
}

void bhv_castle_floor_trap_close(void) {
    o->oFaceAngleRoll += 0x400;
    if (o->oFaceAngleRoll   > 0x0) {
        o->oFaceAngleRoll   = 0x0;
        o->oAction          = CASTLE_FLOOR_TRAP_ACT_OPEN_DETECT; // after closing, reloads open detection
        o->oInteractStatus &= ~INT_STATUS_TRAP_TURN;
    }
}

void bhv_castle_floor_trap_rotate(void) {
    o->oFaceAngleRoll = -0x3C00;
}

void bhv_castle_floor_trap_loop(void) {
    switch (o->oAction) {
        case CASTLE_FLOOR_TRAP_ACT_OPEN_DETECT:  bhv_castle_floor_trap_open_detect();  break;
        case CASTLE_FLOOR_TRAP_ACT_OPEN:         bhv_castle_floor_trap_open();         break;
        case CASTLE_FLOOR_TRAP_ACT_CLOSE_DETECT: bhv_castle_floor_trap_close_detect(); break;
        case CASTLE_FLOOR_TRAP_ACT_CLOSE:        bhv_castle_floor_trap_close();        break;
        case CASTLE_FLOOR_TRAP_ACT_ROTATE:       bhv_castle_floor_trap_rotate();       break;
    }
}
