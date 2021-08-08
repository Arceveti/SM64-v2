#ifndef COMMON0_H
#define COMMON0_H

#include "types.h"

// amp
extern const GeoLayout dAmpGeo[];
extern const Gfx dAmpElectricityDl[];
extern const Gfx dAmpEyeDl[];
extern const Gfx dAmpMouthDl[];
extern const Gfx dAmpBodyDl[];
extern const struct Animation *const dAmpAnimsList[];

// blue_coin_switch
extern const GeoLayout blue_coin_switch_geo[];
extern const Gfx blue_coin_switch_seg8_sub_dl_sides[];
extern const Gfx blue_coin_switch_seg8_sub_dl_top[];
extern const Gfx blue_coin_switch_seg8_dl_08000E08[];
extern const Collision blue_coin_switch_seg8_collision_switch[];

// bobomb
extern const GeoLayout black_bobomb_geo[];
extern const GeoLayout bobomb_buddy_geo[];
extern const Gfx bobomb_seg8_dl_08022AC0[];
extern const Gfx bobomb_seg8_dl_08022B08[];
extern const Gfx bobomb_seg8_dl_eyes[];
extern const Gfx bobomb_seg8_dl_eyes_blink[];
extern const Gfx bobomb_seg8_sub_dl_body_black[];
extern const Gfx bobomb_seg8_sub_dl_body_pink[];
extern const Gfx bobomb_seg8_dl_body_black[];
extern const Gfx bobomb_seg8_dl_body_pink[];
extern const Gfx bobomb_seg8_dl_08023270[];
extern const Gfx bobomb_seg8_dl_08023378[];
extern const Gfx bobomb_seg8_dl_08023480[];
extern const struct Animation *const bobomb_seg8_anims_0802396C[];

// bowling_ball
extern const GeoLayout bowling_ball_geo[];
extern const GeoLayout bowling_ball_track_geo[];

// breakable_box
extern const GeoLayout breakable_box_geo[];
extern const GeoLayout breakable_box_small_geo[];
extern const Gfx breakable_box_seg8_dl_end[];
extern const Gfx breakable_box_seg8_dl_begin[];
extern const Gfx breakable_box_seg8_dl_crazy_box[];
extern const Gfx breakable_box_seg8_dl_cork_box[];
extern const Collision breakable_box_seg8_collision_breakable_box[];

// cannon_barrel
extern const GeoLayout cannon_barrel_geo[];
extern const Gfx cannon_barrel_seg8_dl_08006408[];
extern const Gfx cannon_barrel_seg8_dl_080064C0[];
extern const Gfx cannon_barrel_seg8_dl_08006660[];

// cannon_base
extern const GeoLayout cannon_base_geo[];
extern const Gfx cannon_base_seg8_dl_08005658[];
extern const Gfx cannon_base_seg8_dl_080056D0[];
extern const Gfx cannon_base_seg8_dl_080057F8[];

// cannon_lid
extern const Gfx cannon_lid_seg8_dl_08004898[];
extern const Gfx cannon_lid_seg8_dl_080048E0[];
extern const Collision cannon_lid_seg8_collision_closed[];

// checkerboard_platform
extern const GeoLayout checkerboard_platform_geo[];
extern const Gfx checkerboard_platform_seg8_dl_sides[];
extern const Gfx checkerboard_platform_seg8_dl_surface[];
extern const Gfx checkerboard_platform_seg8_dl_0800D680[];
extern const Collision checkerboard_platform_seg8_collision_platform[];

// chuckya
extern const GeoLayout chuckya_geo[];
extern const Gfx chuckya_seg8_dl_08009FF8[];
extern const Gfx chuckya_seg8_dl_0800A068[];
extern const Gfx chuckya_seg8_dl_0800A160[];
extern const Gfx chuckya_seg8_dl_0800A1D0[];
extern const Gfx chuckya_seg8_dl_0800A2C8[];
extern const Gfx chuckya_seg8_dl_0800A338[];
extern const Gfx chuckya_seg8_dl_0800A3F0[];
extern const Gfx chuckya_seg8_dl_0800A428[];
extern const Gfx chuckya_seg8_dl_0800A4D8[];
extern const Gfx chuckya_seg8_dl_0800A510[];
extern const Gfx chuckya_seg8_dl_0800A5C0[];
extern const Gfx chuckya_seg8_dl_0800A5F8[];
extern const Gfx chuckya_seg8_dl_0800A700[];
extern const Gfx chuckya_seg8_dl_0800A758[];
extern const Gfx chuckya_seg8_dl_0800A870[];
extern const Gfx chuckya_seg8_dl_0800A8D0[];
extern const Gfx chuckya_seg8_dl_0800A958[];
extern const Gfx chuckya_seg8_dl_0800A998[];
extern const Gfx chuckya_seg8_dl_0800AB70[];
extern const Gfx chuckya_seg8_dl_0800ABE8[];
extern const struct Animation *const chuckya_seg8_anims_0800C070[];

// exclamation_box
extern const GeoLayout exclamation_box_geo[];
extern const Gfx exclamation_box_seg8_dl_08018FA8[];
extern const Gfx exclamation_box_seg8_dl_08019008[];
extern const Gfx exclamation_box_seg8_dl_08019058[];
extern const Gfx exclamation_box_seg8_dl_08019220[];
extern const Gfx exclamation_box_seg8_dl_08019280[];
extern const Gfx exclamation_box_seg8_dl_080192D0[];
extern const Gfx exclamation_box_seg8_dl_red[];
extern const Gfx exclamation_box_seg8_dl_green[];
extern const Gfx exclamation_box_seg8_dl_blue[];
extern const Gfx exclamation_box_seg8_dl_yellow[];
extern const Collision exclamation_box_seg8_collision_solid[];

// exclamation_box_outline
extern const GeoLayout exclamation_box_outline_geo[];
extern const Gfx exclamation_box_outline_seg8_sub_dl_shade[];
extern const Gfx exclamation_box_outline_seg8_dl_shade_begin[];
extern const Gfx exclamation_box_outline_seg8_dl_shade_end[];
extern const Gfx exclamation_box_outline_seg8_dl_shade_red[];
extern const Gfx exclamation_box_outline_seg8_dl_shade_green[];
extern const Gfx exclamation_box_outline_seg8_dl_shade_blue[];
extern const Gfx exclamation_box_outline_seg8_dl_shade_yellow[];
extern const Gfx exclamation_box_outline_seg8_sub_dl_outline[];
extern const Gfx exclamation_box_outline_seg8_dl_outline[];
extern const Gfx exclamation_box_outline_seg8_sub_dl_exclamation_point[];
extern const Gfx exclamation_box_outline_seg8_dl_exclamation_point[];

// flyguy
extern const GeoLayout flyguy_geo[];
extern const Gfx flyguy_seg8_dl_08010840[];
extern const Gfx flyguy_seg8_dl_08010968[];
extern const Gfx flyguy_seg8_dl_08010A90[];
extern const Gfx flyguy_seg8_dl_08010B38[];
extern const Gfx flyguy_seg8_dl_08010B80[];
extern const Gfx flyguy_seg8_dl_080113A8[];
extern const Gfx flyguy_seg8_dl_08011420[];
extern const Gfx flyguy_seg8_dl_080116D0[];
extern const Gfx flyguy_seg8_dl_08011710[];
extern const struct Animation *const flyguy_seg8_anims_08011A64[];

// goomba
extern const GeoLayout goomba_geo[];
extern const Gfx goomba_seg8_sub_dl_face_model[];
extern const Gfx goomba_seg8_sub_dl_face_begin[];
extern const Gfx goomba_seg8_sub_dl_face_end[];
extern const Gfx goomba_seg8_dl_face[];
extern const Gfx goomba_seg8_dl_face_blink[];
extern const Gfx goomba_seg8_sub_dl_body[];
extern const Gfx goomba_seg8_dl_body[];
extern const Gfx goomba_seg8_dl_0801CE20[];
extern const Gfx goomba_seg8_dl_0801CF78[];
extern const Gfx goomba_seg8_dl_0801D0D0[];
extern const Gfx goomba_seg8_dl_0801D360[];
extern const Gfx goomba_seg8_dl_0801D760[];
extern const struct Animation *const goomba_seg8_anims_0801DA4C[];

// heart
extern const GeoLayout heart_geo[];
extern const Gfx heart_seg8_dl_heart[];

// koopa_shell
extern const GeoLayout koopa_shell_geo[];
// extern const GeoLayout koopa_shell2_geo[];
// extern const GeoLayout koopa_shell3_geo[];
// extern const Gfx koopa_shell_seg8_dl_08027108[];
// extern const Gfx koopa_shell_seg8_dl_08027170[];
// extern const Gfx koopa_shell_seg8_dl_08027258[];
// extern const Gfx koopa_shell_seg8_dl_080273C8[];
// extern const Gfx koopa_shell_seg8_dl_08027420[];
extern const Gfx koopa_shell_seg8_dl_top[];
extern const Gfx koopa_shell_seg8_dl_bottom[];
extern const Gfx koopa_shell_seg8_dl_edge[];
extern const Gfx koopa_shell_seg8_dl_green_koopa_shell[];

// metal_box
extern const GeoLayout metal_box_geo[];
extern const Gfx metal_box_seg8_dl_08024B18[];
extern const Gfx metal_box_dl[];
extern const Collision metal_box_seg8_collision_pushable_box[];

// purple_switch
extern const GeoLayout purple_switch_geo[];
extern const Gfx purple_switch_seg8_dl_0800C668[];
extern const Gfx purple_switch_seg8_dl_0800C6E0[];
extern const Gfx purple_switch_seg8_dl_0800C718[];
extern const Collision purple_switch_seg8_collision_purple_switch[];

// test_platform
extern const GeoLayout test_platform_geo[];
extern const Gfx unknown_seg8_dl_test_platform[];
extern const Collision unknown_seg8_collision_test_platform[];

#endif
