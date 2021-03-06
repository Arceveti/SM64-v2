// breakable_wall.c.inc

void bhv_wf_breakable_wall_loop(void) {
    if (gMarioStates[0].action == ACT_SHOT_FROM_CANNON) {
        cur_obj_become_tangible();
        if (obj_check_if_collided_with_object(o, gMarioObject)) {
#ifdef FIX_CANNONLESS
            create_sound_spawner(SOUND_GENERAL_WALL_EXPLOSION);
            o->oInteractType      = INTERACT_DAMAGE;
            // o->oDamageOrCoinValue = 1;
            obj_explode_and_spawn_coins(80.0f, COIN_TYPE_NONE);
            if (cur_obj_has_behavior(bhvWfBreakableWallRight)) {
                play_puzzle_jingle();
                spawn_default_star(590.0f, 2560.0f, 2650.0f);
            }
        }
    } else {
        load_object_collision_model();
    }
#else
            if (cur_obj_has_behavior(bhvWfBreakableWallRight)) play_puzzle_jingle();
            create_sound_spawner(SOUND_GENERAL_WALL_EXPLOSION);
            o->oInteractType      = INTERACT_DAMAGE;
            o->oDamageOrCoinValue = 1;
            obj_explode_and_spawn_coins(80.0f, COIN_TYPE_NONE);
        }
    } else {
        cur_obj_become_intangible();
    }
#endif
}
