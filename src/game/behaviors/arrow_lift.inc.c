/**
 * Behavior for WDW arrow lifts.
 * When a player stands on an arrow lift, it starts moving between
 * two positions 384 units apart.
 * Arrow lifts move either along the X axis or the Z axis.
 * Their facing angle is always perpendicular to the axis they move on.
 * The angle the arrow lifts move initially is 90º clockwise of the face angle.
 * This means an arrow lift at (0, 0, 0) with face angle 0 (positive Z) will
 * move between (0, 0, 0) and (-384, 0, 0).
 */

/**
 * Move the arrow lift away from its original position.
 */
static s32 arrow_lift_move_away(void) {
    Bool8 doneMoving = FALSE;
    o->oMoveAngleYaw = (o->oFaceAngleYaw - DEG(90));
    o->oVelY         =  0.0f;
    o->oForwardVel   = 12.0f;
    // Cumulative displacement is used to keep track of how far the platform
    // has travelled, so that it can stop.
    o->oArrowLiftDisplacement += o->oForwardVel;
    // Stop the platform after moving 384 units.
    if (o->oArrowLiftDisplacement > 384.0f) {
        o->oForwardVel            =   0.0f;
        o->oArrowLiftDisplacement = 384.0f;
        doneMoving                = TRUE;
    }
    obj_move_xyz_using_fvel_and_yaw(o);
    return doneMoving;
}

/**
 * Move the arrow lift back to its original position.
 */
static Bool32 arrow_lift_move_back(void) {
    Bool8 doneMoving           = FALSE;
    o->oMoveAngleYaw           = (o->oFaceAngleYaw + DEG(90));
    o->oVelY                   =  0.0f;
    o->oForwardVel             = 12.0f;
    o->oArrowLiftDisplacement -= o->oForwardVel;
    // Stop the platform after returning back to its original position.
    if (o->oArrowLiftDisplacement < 0.0f) {
        o->oForwardVel            = 0.0f;
        o->oArrowLiftDisplacement = 0.0f;
        doneMoving = TRUE;
    }
    obj_move_xyz_using_fvel_and_yaw(o);
    return doneMoving;
}

/**
 * Arrow lift update function.
 */
void bhv_arrow_lift_loop(void) {
    switch (o->oAction) {
        case ARROW_LIFT_ACT_IDLE:
            // Wait 61 frames before moving.
            if ((o->oTimer > 60) && (gMarioObject->platform == o)) o->oAction = ARROW_LIFT_ACT_MOVING_AWAY;
            break;
        case ARROW_LIFT_ACT_MOVING_AWAY:
            if (arrow_lift_move_away()) o->oAction = ARROW_LIFT_ACT_MOVING_BACK;
            break;
        case ARROW_LIFT_ACT_MOVING_BACK:
            // Wait 61 frames before moving (after stopping after moving forwards).
            if ((o->oTimer > 60) && arrow_lift_move_back()) o->oAction = ARROW_LIFT_ACT_IDLE;
            break;
    }
}
