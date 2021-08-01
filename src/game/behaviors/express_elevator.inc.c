// express_elevator.c.inc

void bhv_wdw_express_elevator_loop(void) {
    o->oVelY = 0.0f;
    if (o->oAction == EXPRESS_ELEVATOR_ACT_IDLE) {
        if (cur_obj_is_mario_on_platform()) o->oAction = EXPRESS_ELEVATOR_ACT_MOVING_DOWN;
    } else if (o->oAction == EXPRESS_ELEVATOR_ACT_MOVING_DOWN) {
        o->oVelY = -20.0f;
        o->oPosY += o->oVelY;
        cur_obj_play_sound_1(SOUND_ENV_ELEVATOR4);
        if (o->oTimer > 132) o->oAction = EXPRESS_ELEVATOR_ACT_PAUSING_AT_BOTTOM;
    } else if (o->oAction == EXPRESS_ELEVATOR_ACT_PAUSING_AT_BOTTOM) {
        if (o->oTimer > 110) o->oAction = EXPRESS_ELEVATOR_ACT_MOVING_UP;
    } else if (o->oAction == EXPRESS_ELEVATOR_ACT_MOVING_UP) {
        o->oVelY = 10.0f;
        o->oPosY += o->oVelY;
        cur_obj_play_sound_1(SOUND_ENV_ELEVATOR4);
        if (o->oPosY >= o->oHomeY) {
            o->oPosY = o->oHomeY;
            o->oAction = EXPRESS_ELEVATOR_ACT_DONE;
        }
    } else if (!cur_obj_is_mario_on_platform()) {
        o->oAction = EXPRESS_ELEVATOR_ACT_IDLE;
    }
}
