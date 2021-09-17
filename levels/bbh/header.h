#ifndef BBH_HEADER_H
#define BBH_HEADER_H

#include "types.h"
#include "game/moving_texture.h"

// geo
extern const GeoLayout geo_bbh_staircase_step[];
extern const GeoLayout geo_bbh_tilting_trap_platform[];
extern const GeoLayout geo_bbh_tumbling_platform_far[];
extern const GeoLayout geo_bbh_tumbling_platform_near[];
extern const GeoLayout geo_bbh_moving_bookshelf[];
extern const GeoLayout geo_bbh_mesh_elevator[];
extern const GeoLayout geo_bbh_merry_go_round[];
extern const GeoLayout geo_bbh_coffin[];
extern const GeoLayout geo_bbh_room_foyer[];
extern const GeoLayout geo_bbh_room_study[];
extern const GeoLayout geo_bbh_room_piano[];
extern const GeoLayout geo_bbh_room_bridge[];
extern const GeoLayout geo_bbh_room_back_room[];
extern const GeoLayout geo_bbh_room_library[];
extern const GeoLayout geo_bbh_room_coffins[];
extern const GeoLayout geo_bbh_room_mesh_room[];
extern const GeoLayout geo_bbh_room_attic[];
extern const GeoLayout geo_bbh_room_merry_go_round[];
extern const GeoLayout geo_bbh_room_basement_hallway[];
extern const GeoLayout geo_bbh_room_shed[];
extern const GeoLayout geo_bbh_room_outside[];
extern const GeoLayout geo_bbh_door_room_foyer_and_study[];
extern const GeoLayout geo_bbh_door_room_foyer_and_piano[];
extern const GeoLayout geo_bbh_door_room_foyer_and_bridge[];
extern const GeoLayout geo_bbh_door_room_foyer_and_back_room[];
extern const GeoLayout geo_bbh_door_room_foyer_and_library[];
extern const GeoLayout geo_bbh_door_room_foyer_and_coffins[];
extern const GeoLayout geo_bbh_door_room_foyer_and_mesh_room[];
extern const GeoLayout geo_bbh_door_room_foyer_and_outside[];
extern const GeoLayout geo_bbh_door_room_study_and_bridge[];
extern const GeoLayout geo_bbh_door_room_study_and_attic[];
extern const GeoLayout geo_bbh_000C88[];
extern const GeoLayout geo_bbh_door_room_piano_and_back_room[];
extern const GeoLayout geo_bbh_door_room_piano_and_library[];
extern const GeoLayout geo_bbh_000D68[];
extern const GeoLayout geo_bbh_door_room_back_room_and_outside[];
extern const GeoLayout geo_bbh_door_room_attic_and_outside[];
extern const GeoLayout geo_bbh_door_room_merry_go_round_and_basement_hallway[];
extern const GeoLayout geo_bbh_door_room_basement_hallway_and_shed[];
extern const GeoLayout geo_bbh_door_room_shed_and_outside[];
extern const GeoLayout geo_bbh_area_1[];

// leveldata
extern const Gfx bbh_seg7_dl_foyer_surfaces[];
extern const Gfx bbh_seg7_dl_foyer_railings[];
extern const Gfx bbh_seg7_dl_foyer_windows_and_boo_painting[];
extern const Gfx bbh_seg7_dl_foyer_lamps_glow[];
extern const Gfx bbh_seg7_dl_foyer_lamps[];
extern const Gfx bbh_seg7_dl_foyer_window_light[];
extern const Gfx bbh_seg7_dl_study_surfaces[];
extern const Gfx bbh_seg7_dl_study_windows[];
extern const Gfx bbh_seg7_dl_study_lamps_glow[];
extern const Gfx bbh_seg7_dl_study_lamps[];
extern const Gfx bbh_seg7_dl_study_window_light[];
extern const Gfx bbh_seg7_dl_piano_room_surfaces[];
extern const Gfx bbh_seg7_dl_piano_room_railings[];
extern const Gfx bbh_seg7_dl_piano_room_windows[];
extern const Gfx bbh_seg7_dl_piano_room_window_light[];
extern const Gfx bbh_seg7_dl_bridge_room_surfaces[];
extern const Gfx bbh_seg7_dl_bridge_room_railing[];
extern const Gfx bbh_seg7_dl_back_room_surfaces[];
extern const Gfx bbh_seg7_dl_library_surfaces[];
extern const Gfx bbh_seg7_dl_library_window_wood[];
extern const Gfx bbh_seg7_dl_library_window_glass[];
extern const Gfx bbh_seg7_dl_coffins_room_surfaces[];
extern const Gfx bbh_seg7_dl_coffins_room_flames_glow[];
extern const Gfx bbh_seg7_dl_mesh_room_surfaces[];
extern const Gfx bbh_seg7_dl_mesh_room_meshes[];
extern const Gfx bbh_seg7_dl_mesh_room_lights_glow[];
extern const Gfx bbh_seg7_dl_mesh_room_lamps[];
extern const Gfx bbh_seg7_dl_attic_surfaces[];
extern const Gfx bbh_seg7_dl_attic_windows[];
extern const Gfx bbh_seg7_dl_attic_window_light[];
extern const Gfx bbh_seg7_merry_go_round_room_surfaces[];
extern const Gfx bbh_seg7_merry_go_round_room_meshes[];
extern const Gfx bbh_seg7_dl_basement_hallway[];
extern const Gfx bbh_seg7_dl_shed_with_elevator[];
extern const Gfx bbh_seg7_dl_outside_surfaces[];
extern const Gfx bbh_seg7_dl_outside_cage_walls[];
extern const Gfx bbh_seg7_dl_outside_windows[];
extern const Gfx bbh_seg7_dl_outside_flames_glow[];
extern const Gfx bbh_seg7_dl_outside_lantern[];
extern const Gfx bbh_seg7_dl_staircase_step[];
extern const Gfx bbh_seg7_dl_tilting_trap_platform[];
extern const Gfx bbh_seg7_dl_tumbling_platform_far[];
extern const Gfx bbh_seg7_dl_tumbling_platform_near[];
extern const Gfx bbh_seg7_dl_moving_bookshelf[];
extern const Gfx bbh_seg7_dl_mesh_elevator[];
extern const Gfx bbh_seg7_dl_merry_go_round[];
extern const Gfx bbh_seg7_dl_coffin[];
extern const Collision bbh_seg7_collision_level[];
extern const RoomData bbh_seg7_rooms[];
extern const MacroObject bbh_seg7_macro_objs[];
extern const Collision bbh_seg7_collision_staircase_step[];
extern const Collision bbh_seg7_collision_tilt_floor_platform[];
extern const Collision bbh_seg7_collision_tumbling_bridge[];
extern const Collision bbh_seg7_collision_haunted_bookshelf[];
extern const Collision bbh_seg7_collision_mesh_elevator[];
extern const Collision bbh_seg7_collision_merry_go_round[];
extern const Collision bbh_seg7_collision_coffin[];
extern const struct MovtexQuadCollection bbh_movtex_merry_go_round_water_entrance[];
extern const struct MovtexQuadCollection bbh_movtex_merry_go_round_water_side[];

// script
extern const LevelScript level_bbh_entry[];

#endif
