/**
 * Behavior for bhvBooCage.
 * This is the cage inside the big boo in the castle courtyard
 * that lets Mario enter BBH. It has its own special interaction type,
 * INTERACT_BBH_ENTRANCE.
 */

/**
 * Boo cage hitbox. It's not tangible; this is the hitbox
 * Mario has to enter to enter BBH.
 */
static struct ObjectHitbox sBooCageHitbox = {
    /* interactType: */ INTERACT_BBH_ENTRANCE,
    /* downOffset: */ 0,
    /* damageOrCoinValue: */ 0,
    /* health: */ 0,
    /* numLootCoins: */ 0,
    /* radius: */ 120,
    /* height: */ 300,
    /* hurtboxRadius: */ 0,
    /* hurtboxHeight: */ 0,
};

/**
 * Update function for bhvBooCage.
 */
void bhv_boo_cage_loop(void) {
    obj_set_hitbox(o, &sBooCageHitbox);

    switch (o->oAction) {
        case BOO_CAGE_ACT_IN_BOO:
            // Don't let Mario enter BBH until the boo is killed
            cur_obj_become_intangible();

            // If the cage's parent boo is killed, set the action to BOO_CAGE_ACT_FALLING,
            // give the cage an initial Y velocity of 60 units/frame, and play the puzzle jingle.
            // Otherwise, stay inside the boo.
            if (o->parentObj->oBooDeathStatus != BOO_DEATH_STATUS_ALIVE) {
                o->oAction++;
                o->oVelY = 60.0f;
                play_puzzle_jingle();
            } else {
                obj_copy_pos_and_angle(o, o->parentObj);
            }

            break;
        case BOO_CAGE_ACT_FALLING:

            // Apply standard physics to the cage.
            cur_obj_update_floor_and_walls();
            cur_obj_move_standard(-78);

            // Spawn sparkles while the cage falls.
            spawn_object(o, MODEL_NONE, bhvSparkleSpawn);

            // When the cage lands/bounces, play a landing/bouncing sound.
            if (o->oMoveFlags & OBJ_MOVE_LANDED) {
                cur_obj_play_sound_2(SOUND_GENERAL_SOFT_LANDING);
            }

            // Once the cage stops bouncing and settles on the ground,
            // set the action to BOO_CAGE_ACT_ON_GROUND.
            // This is the only use of the OBJ_MOVE_AT_WATER_SURFACE flag in the game.
            // It seems to serve no purpose here.
            if (o->oMoveFlags
                & (OBJ_MOVE_UNDERWATER_ON_GROUND | OBJ_MOVE_AT_WATER_SURFACE | OBJ_MOVE_ON_GROUND)) {
                o->oAction++;
            }

            break;
        case BOO_CAGE_ACT_ON_GROUND:
            // Allow Mario to enter the cage once it's still on the ground.
            cur_obj_become_tangible();
            break;
    }
}
