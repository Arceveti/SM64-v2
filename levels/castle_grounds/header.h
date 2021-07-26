#ifndef CASTLE_GROUNDS_HEADER_H
#define CASTLE_GROUNDS_HEADER_H

#include "types.h"
#include "game/moving_texture.h"

// geo
extern const GeoLayout castle_grounds_geo_flag[];
extern const GeoLayout castle_grounds_geo_tower[];
extern const GeoLayout castle_grounds_geo_vcutm_grill[];
extern const GeoLayout castle_grounds_geo_cannon_grill[];
extern const GeoLayout castle_grounds_geo_00073C[];

// leveldata
extern const Gfx castle_grounds_seg7_dl_castle[];
extern const Gfx castle_grounds_seg7_dl_grounds[];
extern const Gfx castle_grounds_seg7_dl_tower[];
extern const Gfx castle_grounds_seg7_dl_fence[];
extern const Gfx castle_grounds_seg7_dl_tree_shadows[];
extern const Gfx castle_grounds_seg7_dl_windows_and_peach_window[];
extern const Gfx castle_grounds_seg7_dl_moat_grills[];
extern const Gfx castle_grounds_seg7_dl_cannon_grill[];
extern const Gfx castle_grounds_seg7_dl_cannon_platform[];
extern const Gfx castle_grounds_seg7_dl_door_frame_and_carpet_outside[];
extern const Gfx castle_grounds_seg7_dl_0700C670[];
extern const Gfx castle_grounds_seg7_dl_0700C6A8[];
extern const Gfx castle_grounds_seg7_dl_0700C6E8[];
extern const Gfx castle_grounds_seg7_dl_0700C728[];
extern const Gfx castle_grounds_seg7_dl_0700C768[];
extern const struct Animation *const castle_grounds_seg7_anims_flags[];
extern const Gfx castle_grounds_seg7_dl_peach_letter[];
extern const Gfx castle_grounds_seg7_us_dl_peach_signature[];
extern const Collision castle_grounds_seg7_collision_level[];
extern const MacroObject castle_grounds_seg7_macro_objs[];
extern const Collision castle_grounds_seg7_collision_moat_grills[];
extern const Collision castle_grounds_seg7_collision_cannon_grill[];
extern const struct MovtexQuadCollection castle_grounds_movtex_water[];
extern Movtex castle_grounds_movtex_tris_waterfall[];
extern const Gfx castle_grounds_dl_waterfall[];

// script
extern const LevelScript level_castle_grounds_entry[];

#endif
