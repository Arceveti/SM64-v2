// lll_octagonal_rotating_mesh.c.inc

enum {
	LLL_OCTMESH_CHANGE_DIR = 1, // 1
	LLL_OCTMESH_LINEAR_MOVE,    // 2
	LLL_OCTMESH_RESET,          // 3
	LLL_OCTMESH_WAIT_FOR_MARIO  // 4
};

//! Note: useless zero at the reset instruction, there's no accesses beyond that anyway

// Path for big bullies platforms
s16 gLllOctagonalMeshAction0[] = { 
    // instruction            time moveAngle  forwardVel
	LLL_OCTMESH_LINEAR_MOVE,    30,   0x4000,         0, 
	LLL_OCTMESH_CHANGE_DIR,    220,      900,        30, 
	LLL_OCTMESH_CHANGE_DIR,     30,        0,       -30, 
	LLL_OCTMESH_LINEAR_MOVE,    30,  -0x4000,         0,
	LLL_OCTMESH_CHANGE_DIR,    220,      900,        30,  
	LLL_OCTMESH_CHANGE_DIR,     30,        0,       -30, 
	LLL_OCTMESH_RESET,           0 
};

// Path for rolling log
s16 gLllOctagonalMeshAction1[] = { 
    // instruction              time moveAngle  forwardVel
	LLL_OCTMESH_WAIT_FOR_MARIO,    0,        0,         0, 
	LLL_OCTMESH_CHANGE_DIR,      475,      900,        30, 
	LLL_OCTMESH_CHANGE_DIR,       30,        0,       -30, 
	LLL_OCTMESH_LINEAR_MOVE,      30,   0x8000,         0, 
	LLL_OCTMESH_CHANGE_DIR,      475,      900,        30,  
	LLL_OCTMESH_CHANGE_DIR,       30,        0,       -30, 
	LLL_OCTMESH_RESET,             0 
};

// picked by oBehParams2ndByte
s16 *gLllOctagonalMeshActionList[] = { gLllOctagonalMeshAction0, gLllOctagonalMeshAction1 };


s32 lll_octagonal_mesh_move(s16 *actionTable, s32 actionOffset) {
    switch (actionTable[actionOffset]) {
        case LLL_OCTMESH_WAIT_FOR_MARIO:
            o->oMoveAngleYaw = actionTable[actionOffset + 2];
            o->oForwardVel   = actionTable[actionOffset + 3] / 100.0f;
            if (cur_obj_is_mario_on_platform()) {
                actionOffset += 4;
                o->oTimer     = 0;
            }
            break;
        case LLL_OCTMESH_LINEAR_MOVE:
            o->oMoveAngleYaw = actionTable[actionOffset + 2];
            o->oForwardVel   = actionTable[actionOffset + 3] / 100.0f;
            if (o->oTimer    > actionTable[actionOffset + 1]) {
                actionOffset += 4;
                o->oTimer     = 0;
            }
            break;
        case LLL_OCTMESH_CHANGE_DIR:
            approach_f32_signed(&o->oForwardVel, actionTable[actionOffset + 2] / 100.0f, actionTable[actionOffset + 3] / 100.0f);
            if (o->oTimer > actionTable[actionOffset + 1]) {
                actionOffset += 4;
                o->oTimer     = 0;
            }
            break;
        case LLL_OCTMESH_RESET:
            o->oForwardVel = 0.0f;
            actionOffset   = 0;
            break;
    }
    return actionOffset;
}

s32 lll_octagonal_mesh_find_y_offset(s32 *standTimer, f32 *posOffset, s32 standTimerInc, s32 moveDownAmount) {
	// if Mario is on the platform...
    if (cur_obj_is_mario_on_platform()) {
        if (standTimer[0] < 0x4000) {
            standTimer[0] += standTimerInc;
        } else {
            standTimer[0] = 0x4000;
        }
    } else {
        if (standTimer[0] > 0) {
            standTimer[0] -= standTimerInc;
        } else {
            standTimer[0] = 0;
        }
    }
    posOffset[0] = sins(standTimer[0]) * moveDownAmount;
    return (standTimer[0] == 0 || standTimer[0] == 0x4000);
}

void bhv_lll_moving_octagonal_mesh_platform_loop(void) {
    if (o->oAction == LLL_OCTAGONAL_ROTATING_MESH_ACT_RESET) {
        // reset the platform (when initting?)
        o->oLllOctmeshActionOffset = 0;
        o->oAction = LLL_OCTAGONAL_ROTATING_MESH_ACT_MOVE;
    } else {
        o->oLllOctmeshActionOffset = lll_octagonal_mesh_move(gLllOctagonalMeshActionList[o->oBehParams2ndByte], o->oLllOctmeshActionOffset);
    }
	// prints the current actionOffset to the screen
    print_debug_top_down_objectinfo("number %d\n", o->oLllOctmeshActionOffset);
    cur_obj_move_using_fvel_and_gravity();
    // are we transitioning between Mario standing and not standing?
    if (lll_octagonal_mesh_find_y_offset(&o->oLllOctmeshStandTimer, &o->oLllOctmeshWaveOffset2, 0x400, -80)) {
		// nope, wave as usual
        o->oLllOctmeshWaveTimer   += 0x800;
        o->oLllOctmeshWaveOffset1 -= sins(o->oLllOctmeshWaveTimer) * 2;
    }
    o->oPosY = o->oLllOctmeshWaveOffset1 + o->oLllOctmeshWaveOffset2;
}
