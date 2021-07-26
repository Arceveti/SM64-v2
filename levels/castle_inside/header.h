#ifndef CASTLE_INSIDE_HEADER_H
#define CASTLE_INSIDE_HEADER_H

#include "types.h"
#include "game/paintings.h"
#include "game/moving_texture.h"

// geo
extern const GeoLayout castle_geo_star_door[];
extern const GeoLayout castle_geo_bowser_trap_door[];
extern const GeoLayout castle_geo_area_1_room_lobby[];
extern const GeoLayout castle_geo_area_1_room_back_hallway[];
extern const GeoLayout castle_geo_area_1_room_bowser_1[];
extern const GeoLayout castle_geo_area_1_room_pss[];
extern const GeoLayout castle_geo_area_1_room_bob[];
extern const GeoLayout castle_geo_area_1_room_wf[];
extern const GeoLayout castle_geo_area_1_room_jrb[];
extern const GeoLayout castle_geo_area_1_room_ccm[];
extern const GeoLayout castle_geo_area_1_door_room_lobby_fake_spiral_stairs[];
extern const GeoLayout castle_geo_area_1_door_room_lobby_back_hallway[];
extern const GeoLayout castle_geo_area_1_door_room_lobby_bowser_1[];
extern const GeoLayout castle_geo_area_1_door_room_lobby_pss[];
extern const GeoLayout castle_geo_area_1_door_room_lobby_bob[];
extern const GeoLayout castle_geo_area_1_door_room_lobby_wf[];
extern const GeoLayout castle_geo_area_1_door_room_lobby_jrb[];
extern const GeoLayout castle_geo_area_1_door_room_lobby_ccm[];
// extern const GeoLayout castle_geo_area_1_door_room_lobby_fake_spiral_stairs_2[];
extern const GeoLayout castle_geo_area_1[];
extern const GeoLayout castle_geo_clock_pendulum[];
extern const GeoLayout castle_geo_clock_minute_hand[];
extern const GeoLayout castle_geo_clock_hour_hand[];
extern const GeoLayout castle_geo_001560[];
extern const GeoLayout castle_geo_001578[];
extern const GeoLayout castle_geo_0015B8[];
extern const GeoLayout castle_geo_0015F8[];
extern const GeoLayout castle_geo_001628[];
extern const GeoLayout castle_geo_001668[];
extern const GeoLayout castle_geo_001690[];
extern const GeoLayout castle_geo_0016D8[];
extern const GeoLayout castle_geo_001740[];
extern const GeoLayout castle_geo_001798[];
extern const GeoLayout castle_geo_001800[];
extern const GeoLayout castle_geo_001858[];
extern const GeoLayout castle_geo_water_level_pillar[];
extern const GeoLayout castle_geo_001958[];
extern const GeoLayout castle_geo_001980[];
extern const GeoLayout castle_geo_0019C8[];
extern const GeoLayout castle_geo_0019F8[];
extern const GeoLayout castle_geo_001A30[];
extern const GeoLayout castle_geo_001A58[];
extern const GeoLayout castle_geo_001AB8[];
extern const GeoLayout castle_geo_001AF8[];
extern const GeoLayout castle_geo_001B48[];
extern const GeoLayout castle_geo_001BB0[];
extern const GeoLayout castle_geo_001C10[];

// leveldata
extern const Gfx inside_castle_seg7_dl_ccm_fake_painting_1[];
extern const Gfx inside_castle_seg7_dl_ccm_fake_painting_2[];
extern struct Painting bob_painting;
extern struct Painting ccm_painting;
extern struct Painting wf_painting;
extern struct Painting jrb_painting;
extern struct Painting lll_painting;
extern struct Painting ssl_painting;
extern struct Painting hmc_painting;
extern struct Painting ddd_painting;
extern struct Painting wdw_painting;
extern struct Painting thi_tiny_painting;
extern struct Painting ttm_painting;
extern struct Painting ttc_painting;
extern struct Painting sl_painting;
extern struct Painting thi_huge_painting;
#ifdef PSS_PAINTING
extern struct Painting pss_painting;
#endif
extern const Gfx inside_castle_seg7_dl_bowser_1_painting[];
extern const Gfx inside_castle_seg7_dl_07028FD0[];
extern const Gfx dl_castle_lobby_fence[];
extern const Gfx inside_castle_seg7_dl_0702A650[];
extern const Gfx dl_castle_lobby_wing_cap_light[];
extern const Gfx dl_castle_lobby_sun_carpet[];
extern const Gfx dl_castle_lobby_peach_window[];
extern const Gfx inside_castle_seg7_dl_area_1_back_hallway[];
extern const Gfx inside_castle_seg7_dl_bowser_1_hallway[];
extern const Vtx inside_castle_seg7_vertex_07030940[];
extern const Gfx inside_castle_seg7_dl_07031168[];
extern const Gfx inside_castle_seg7_dl_pss_room[];
extern const Gfx inside_castle_seg7_dl_pss_windows[];
extern const Gfx inside_castle_seg7_dl_pss_wall_sign[];
extern const Gfx inside_castle_seg7_dl_bob_room[];
extern const Gfx inside_castle_seg7_dl_bob_wall_signs[];
extern const Gfx inside_castle_seg7_dl_wf_room[];
extern const Gfx inside_castle_seg7_dl_wf_fence[];
extern const Gfx inside_castle_seg7_dl_wf_wall_sign[];
extern const Gfx inside_castle_seg7_dl_07036D88[];
extern const Gfx inside_castle_seg7_dl_07037988[];
extern const Gfx inside_castle_seg7_dl_07037BF8[];
extern const Gfx dl_castle_aquarium_glass[];
extern const Gfx dl_castle_aquarium_light[];
extern const Gfx dl_castle_aquarium_wall_sign[];
extern const Gfx inside_castle_seg7_dl_ccm_room[];
extern const Gfx inside_castle_seg7_dl_ccm_wall_sign[];
extern const Gfx inside_castle_seg7_dl_fake_spiral_stairs_room[];
extern const Gfx inside_castle_seg7_dl_bowser_trap_door[];
extern const Gfx inside_castle_seg7_dl_star_door[];
extern const Gfx inside_castle_seg7_dl_0703E6F0[];
extern const Gfx inside_castle_seg7_dl_07043028[];
extern const Gfx inside_castle_seg7_dl_07043B48[];
extern const Gfx inside_castle_seg7_dl_07043CD8[];
extern const Gfx inside_castle_seg7_dl_0704A0E8[];
extern const Gfx inside_castle_seg7_dl_0704A2E0[];
extern const Gfx inside_castle_seg7_dl_0704AA98[];
extern const Gfx inside_castle_seg7_dl_0704C7D8[];
extern const Gfx inside_castle_seg7_dl_07050938[];
extern const Gfx inside_castle_seg7_dl_070512F8[];
extern const Gfx inside_castle_seg7_dl_07051678[];
extern const Gfx inside_castle_seg7_dl_070519C8[];
extern const Gfx inside_castle_seg7_dl_07051B60[];
extern const Gfx inside_castle_seg7_dl_070558D0[];
extern const Gfx inside_castle_seg7_dl_070572A0[];
extern const Gfx inside_castle_seg7_dl_07057F00[];
extern const Gfx inside_castle_seg7_dl_clock_minute_hand[];
extern const Gfx inside_castle_seg7_dl_clock_hour_hand[];
extern const Gfx inside_castle_seg7_dl_0705E088[];
extern const Gfx inside_castle_seg7_dl_0705E2A0[];
extern const Gfx inside_castle_seg7_dl_0705E450[];
extern const Gfx inside_castle_seg7_dl_070616E8[];
extern const Gfx inside_castle_seg7_dl_07061C20[];
extern const Gfx inside_castle_seg7_dl_07064B78[];
extern const Gfx inside_castle_seg7_dl_07064D58[];
extern const Gfx inside_castle_seg7_dl_07066CE0[];
extern const Gfx inside_castle_seg7_dl_07066E90[];
extern const Gfx inside_castle_seg7_dl_07066FA0[];
extern const Gfx inside_castle_seg7_dl_07068850[];
extern const Gfx inside_castle_seg7_dl_water_level_pillar[];
extern const Collision inside_castle_seg7_area_1_collision[];
extern const Collision inside_castle_seg7_area_2_collision[];
extern const Collision inside_castle_seg7_area_3_collision[];
extern const Collision inside_castle_seg7_collision_ddd_warp[];
extern const Collision inside_castle_seg7_collision_ddd_warp_2[];
extern const MacroObject inside_castle_seg7_area_1_macro_objs[];
extern const MacroObject inside_castle_seg7_area_2_macro_objs[];
extern const MacroObject inside_castle_seg7_area_3_macro_objs[];
extern const u8 inside_castle_seg7_area_1_rooms[];
extern const u8 inside_castle_seg7_area_2_rooms[];
extern const u8 inside_castle_seg7_area_3_rooms[];
extern const Collision inside_castle_seg7_collision_floor_trap[];
extern const Collision inside_castle_seg7_collision_star_door[];
extern const Collision inside_castle_seg7_collision_water_level_pillar[];
extern const Trajectory *const inside_castle_seg7_trajectory_mips[];
extern const struct MovtexQuadCollection inside_castle_movtex_green_room_water[];
extern const struct MovtexQuadCollection inside_castle_movtex_moat_water[];

// script
extern const LevelScript level_castle_inside_entry[];

#endif
