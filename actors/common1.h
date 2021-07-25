#ifndef COMMON1_H
#define COMMON1_H

#include "types.h"

// blue_fish
extern const GeoLayout fish_shadow_geo[];
extern const GeoLayout fish_geo[];
extern const Gfx blue_fish_seg3_dl_0301BEC0[];
extern const Gfx blue_fish_seg3_dl_0301BFB8[];
extern const Gfx blue_fish_seg3_dl_0301C0A8[];
extern const Gfx blue_fish_seg3_dl_0301C150[];
extern const struct Animation *const blue_fish_seg3_anims_0301C2B0[];

// bowser_key
extern const GeoLayout bowser_key_geo[];
extern const GeoLayout bowser_key_cutscene_geo[];
extern const Gfx bowser_key_dl[];
extern const struct Animation *const bowser_key_seg3_anims_list[];

// butterfly
extern const GeoLayout butterfly_geo[];
extern const Gfx butterfly_seg3_dl_wing_1[];
extern const Gfx butterfly_seg3_dl_wing_2[];
extern const struct Animation *const butterfly_seg3_anims_030056B0[];

// coin
extern const GeoLayout yellow_coin_geo[];
extern const GeoLayout yellow_coin_no_shadow_geo[];
extern const GeoLayout blue_coin_geo[];
extern const GeoLayout blue_coin_no_shadow_geo[];
extern const GeoLayout red_coin_geo[];
extern const GeoLayout red_coin_no_shadow_geo[];
#ifdef IA8_30FPS_COINS
extern const GeoLayout silver_coin_geo[];
extern const GeoLayout silver_coin_no_shadow_geo[];

extern const Gfx coin_seg3_dl_yellow_0[];
extern const Gfx coin_seg3_dl_yellow_22_5[];
extern const Gfx coin_seg3_dl_yellow_45[];
extern const Gfx coin_seg3_dl_yellow_67_5[];
extern const Gfx coin_seg3_dl_yellow_90[];
extern const Gfx coin_seg3_dl_yellow_67_5_r[];
extern const Gfx coin_seg3_dl_yellow_45_r[];
extern const Gfx coin_seg3_dl_yellow_22_5_r[];

extern const Gfx coin_seg3_dl_blue_0[];
extern const Gfx coin_seg3_dl_blue_22_5[];
extern const Gfx coin_seg3_dl_blue_45[];
extern const Gfx coin_seg3_dl_blue_67_5[];
extern const Gfx coin_seg3_dl_blue_90[];
extern const Gfx coin_seg3_dl_blue_67_5_r[];
extern const Gfx coin_seg3_dl_blue_45_r[];
extern const Gfx coin_seg3_dl_blue_22_5_r[];

extern const Gfx coin_seg3_dl_red_0[];
extern const Gfx coin_seg3_dl_red_22_5[];
extern const Gfx coin_seg3_dl_red_45[];
extern const Gfx coin_seg3_dl_red_67_5[];
extern const Gfx coin_seg3_dl_red_90[];
extern const Gfx coin_seg3_dl_red_67_5_r[];
extern const Gfx coin_seg3_dl_red_45_r[];
extern const Gfx coin_seg3_dl_red_22_5_r[];

extern const Gfx coin_seg3_dl_secret_0[];
extern const Gfx coin_seg3_dl_secret_22_5[];
extern const Gfx coin_seg3_dl_secret_45[];
extern const Gfx coin_seg3_dl_secret_67_5[];
extern const Gfx coin_seg3_dl_secret_90[];
extern const Gfx coin_seg3_dl_secret_67_5_r[];
extern const Gfx coin_seg3_dl_secret_45_r[];
extern const Gfx coin_seg3_dl_secret_22_5_r[];

extern const Gfx coin_seg3_dl_yellow_front[];
extern const Gfx coin_seg3_dl_yellow_tilt_right[];
extern const Gfx coin_seg3_dl_yellow_side[];
extern const Gfx coin_seg3_dl_yellow_tilt_left[];

extern const Gfx coin_seg3_dl_blue_front[];
extern const Gfx coin_seg3_dl_blue_tilt_right[];
extern const Gfx coin_seg3_dl_blue_side[];
extern const Gfx coin_seg3_dl_blue_tilt_left[];

extern const Gfx coin_seg3_dl_red_front[];
extern const Gfx coin_seg3_dl_red_tilt_right[];
extern const Gfx coin_seg3_dl_red_side[];
extern const Gfx coin_seg3_dl_red_tilt_left[];

extern const Gfx coin_seg3_dl_secret_front[];
extern const Gfx coin_seg3_dl_secret_tilt_right[];
extern const Gfx coin_seg3_dl_secret_side[];
extern const Gfx coin_seg3_dl_secret_tilt_left[];
#else
extern const Gfx coin_seg3_dl_03007780[];
extern const Gfx coin_seg3_dl_030077D0[];
extern const Gfx coin_seg3_dl_03007800[];
extern const Gfx coin_seg3_dl_03007828[];
extern const Gfx coin_seg3_dl_03007850[];
extern const Gfx coin_seg3_dl_03007878[];
extern const Gfx coin_seg3_dl_030078A0[];
extern const Gfx coin_seg3_dl_030078C8[];
extern const Gfx coin_seg3_dl_030078F0[];
extern const Gfx coin_seg3_dl_03007918[];
extern const Gfx coin_seg3_dl_03007940[];
extern const Gfx coin_seg3_dl_03007968[];
extern const Gfx coin_seg3_dl_03007990[];
extern const Gfx coin_seg3_dl_030079B8[];
#endif

// dirt
extern const GeoLayout dirt_animation_geo[];
extern const GeoLayout cartoon_star_geo[];
extern const Gfx dirt_seg3_dl_0302BFF8[];
extern const Gfx dirt_seg3_dl_0302C028[];
extern const Gfx dirt_seg3_dl_0302C238[];
extern const Gfx dirt_seg3_dl_0302C298[];
extern const Gfx dirt_seg3_dl_0302C2B8[];
extern const Gfx dirt_seg3_dl_0302C2D8[];
extern const Gfx dirt_seg3_dl_0302C2F8[];
extern const Gfx dirt_seg3_dl_0302C318[];
extern const Gfx dirt_seg3_dl_0302C378[];
extern const Gfx dirt_seg3_dl_0302C3B0[];
extern const Gfx dirt_seg3_dl_0302C3E8[];
extern const Gfx dirt_seg3_dl_0302C420[];
extern const Gfx dirt_seg3_dl_0302C458[];

// door
extern const GeoLayout castle_door_geo[];
extern const GeoLayout cabin_door_geo[];
extern const GeoLayout wooden_door_geo[];
extern const GeoLayout wooden_door2_geo[];
extern const GeoLayout metal_door_geo[];
extern const GeoLayout hazy_maze_door_geo[];
extern const GeoLayout haunted_door_geo[];
extern const GeoLayout castle_door_0_star_geo[];
extern const GeoLayout castle_door_1_star_geo[];
extern const GeoLayout castle_door_3_stars_geo[];
extern const GeoLayout key_door_geo[];
extern const Gfx door_seg3_dl_03013C10[];
extern const Gfx door_seg3_dl_03013CC8[];
extern const Gfx door_seg3_dl_03013D78[];
extern const Gfx door_seg3_dl_03013E28[];
extern const Gfx door_seg3_dl_03013EA8[];
extern const Gfx door_seg3_dl_03014020[];
extern const Gfx door_seg3_dl_03014100[];
extern const Gfx door_seg3_dl_03014128[];
extern const Gfx door_seg3_dl_030141C0[];
extern const Gfx door_seg3_dl_03014218[];
extern const Gfx door_seg3_dl_03014250[];
extern const Gfx door_seg3_dl_03014280[];
extern const Gfx door_seg3_dl_030142B0[];
extern const Gfx door_seg3_dl_030142E0[];
extern const Gfx door_seg3_dl_03014310[];
extern const Gfx door_seg3_dl_03014340[];
extern const Gfx door_seg3_dl_03014470[];
extern const Gfx door_seg3_dl_030144E0[];
extern const Gfx door_seg3_dl_03014528[];
extern const Gfx door_seg3_dl_03014540[];
extern const Gfx door_seg3_dl_03014888[];
extern const Gfx door_seg3_dl_030149C0[];
extern const Gfx door_seg3_dl_03014A20[];
extern const Gfx door_seg3_dl_03014A50[];
extern const Gfx door_seg3_dl_03014A80[];
extern const Gfx door_seg3_dl_03014B30[];
extern const Gfx door_seg3_dl_03014BE0[];
extern const Gfx door_seg3_dl_03014C90[];
extern const Gfx door_seg3_dl_03014D40[];
extern const Gfx door_seg3_dl_03014EF0[];
extern const Gfx door_seg3_dl_03014F30[];
extern const Gfx door_seg3_dl_03014F68[];
extern const Gfx door_seg3_dl_03014F98[];
extern const Gfx door_seg3_dl_03015008[];
extern const Gfx door_seg3_dl_03015078[];
extern const Gfx door_seg3_dl_030150E8[];
extern const Gfx door_seg3_dl_03015158[];
extern const struct Animation *const door_seg3_anims_030156C0[];

// explosion
extern const GeoLayout explosion_geo[];
extern const Gfx explosion_seg3_sub_dl_material_model[];
extern const Gfx explosion_seg3_dl_0[];
extern const Gfx explosion_seg3_dl_1[];
extern const Gfx explosion_seg3_dl_2[];
extern const Gfx explosion_seg3_dl_3[];
extern const Gfx explosion_seg3_dl_4[];
extern const Gfx explosion_seg3_dl_5[];
extern const Gfx explosion_seg3_dl_6[];

// flame
extern const GeoLayout red_flame_shadow_geo[];
extern const GeoLayout red_flame_geo[];
extern const GeoLayout blue_flame_geo[];
extern const Gfx flame_seg3_dl_red_flame[];
extern const Gfx flame_seg3_dl_red_0[];
extern const Gfx flame_seg3_dl_red_1[];
extern const Gfx flame_seg3_dl_red_2[];
extern const Gfx flame_seg3_dl_red_3[];
extern const Gfx flame_seg3_dl_red_4[];
extern const Gfx flame_seg3_dl_red_5[];
extern const Gfx flame_seg3_dl_red_6[];
extern const Gfx flame_seg3_dl_red_7[];
extern const Gfx flame_seg3_dl_blue_flame[];
extern const Gfx flame_seg3_dl_blue_0[];
extern const Gfx flame_seg3_dl_blue_1[];
extern const Gfx flame_seg3_dl_blue_2[];
extern const Gfx flame_seg3_dl_blue_3[];
extern const Gfx flame_seg3_dl_blue_4[];
extern const Gfx flame_seg3_dl_blue_5[];
extern const Gfx flame_seg3_dl_blue_6[];
extern const Gfx flame_seg3_dl_blue_7[];

// leaves
extern const GeoLayout leaves_geo[];
extern const Gfx leaves_seg3_dl_leaf[];

// mario_cap
extern const GeoLayout marios_cap_geo[];
extern const GeoLayout marios_metal_cap_geo[];
extern const GeoLayout marios_wing_cap_geo[];
extern const GeoLayout marios_winged_metal_cap_geo[];
extern const Gfx mario_cap_seg3_dl_03022B30[];
extern const Gfx mario_cap_seg3_dl_03022B68[];
extern const Gfx mario_cap_seg3_dl_03022CC8[];
extern const Gfx mario_cap_seg3_dl_03022D10[];
extern const Gfx mario_cap_seg3_dl_03022E78[];
extern const Gfx mario_cap_seg3_dl_03022EA8[];
extern const Gfx mario_cap_seg3_dl_03022ED8[];
extern const Gfx mario_cap_seg3_dl_03022F20[];
extern const Gfx mario_cap_seg3_dl_03022F48[];
extern const Gfx mario_cap_seg3_dl_03022FF8[];
extern const Gfx mario_cap_seg3_dl_030230B0[];
extern const Gfx mario_cap_seg3_dl_03023108[];
extern const Gfx mario_cap_seg3_dl_03023160[];
extern const Gfx mario_cap_seg3_dl_03023298[];

// mist
extern const GeoLayout mist_geo[];
extern const GeoLayout white_puff_geo[];
extern const Gfx mist_seg3_dl_03000880[];
extern const Gfx mist_seg3_dl_03000920[];

// mushroom_1up
extern const GeoLayout mushroom_1up_geo[];
extern const Gfx mushroom_1up_seg3_sub_dl_0302A628[];
extern const Gfx mushroom_1up_seg3_dl_0302A660[];

// number
extern const GeoLayout number_geo[];

// pebble
extern const Gfx pebble_seg3_dl_pebble[];

// power_meter
extern const u8 *const power_meter_health_segments_lut[];
extern const Gfx dl_power_meter_base[];
extern const Gfx dl_power_meter_health_segments_begin[];
extern const Gfx dl_power_meter_health_segments_end[];

// sand
extern const Gfx sand_seg3_dl_particle[];

// star
extern const GeoLayout star_geo[];
extern const Gfx star_seg3_sub_dl_body[];
extern const Gfx star_seg3_dl_body[];
extern const Gfx star_seg3_sub_dl_eyes[];
extern const Gfx star_seg3_dl_eyes[];
#ifdef STAR_GLOW
extern const Gfx star_seg3_sub_dl_shine[];
extern const Gfx star_seg3_dl_shine[];
#endif

// transparent_star
extern const GeoLayout transparent_star_geo[];
extern const Gfx transparent_star_seg3_sub_dl_0302C560[];
extern const Gfx transparent_star_seg3_dl_0302C620[];

// tree
extern const GeoLayout bubbly_tree_geo[];
extern const GeoLayout spiky_tree_geo[];
extern const GeoLayout snow_tree_geo[];
extern const GeoLayout palm_tree_geo[];
extern const Gfx tree_seg3_sub_dl_bubbly[];
extern const Gfx tree_seg3_dl_bubbly[];
extern const Gfx tree_seg3_dl_spiky[];
extern const Gfx tree_seg3_dl_snowy_pine[];
extern const Gfx tree_seg3_dl_palm[];

// warp_collision
extern const Collision door_seg3_collision_0301CE78[];
extern const Collision lll_hexagonal_mesh_seg3_collision_0301CECC[];

// warp_pipe
extern const GeoLayout warp_pipe_geo[];
extern const Gfx warp_pipe_seg3_sub_dl_sides[];
extern const Gfx warp_pipe_seg3_dl_sides[];
extern const Gfx warp_pipe_seg3_dl_top[];
extern const Gfx warp_pipe_seg3_dl_inside[];
extern const Gfx warp_pipe_seg3_dl_top_inside[];
extern const Collision warp_pipe_seg3_collision_03009AC8[];

// white_particle
extern const GeoLayout white_particle_geo[];
extern const Gfx white_particle_dl[];

// wooden_signpost
extern const GeoLayout wooden_signpost_geo[];
extern const Gfx wooden_signpost_seg3_sub_dl_post[];
extern const Gfx wooden_signpost_seg3_dl_post[];
extern const Gfx wooden_signpost_seg3_dl_back_sides[];
extern const Gfx wooden_signpost_seg3_dl_front[];
extern const Gfx wooden_signpost_seg3_dl_sign[];
extern const Collision wooden_signpost_seg3_collision_0302DD80[];

#endif
