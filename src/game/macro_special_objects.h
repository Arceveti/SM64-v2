#pragma once

#include <PR/ultratypes.h>

#include "types.h"

Angle convert_rotation(Angle inRotation);

void spawn_macro_abs_yrot_2params(ModelID32 model, const BehaviorScript *behavior, s16 x, s16 y, s16 z, Angle ry, s16 params);
void spawn_macro_abs_yrot_param1( ModelID32 model, const BehaviorScript *behavior, s16 x, s16 y, s16 z, Angle ry, s16 params);
void spawn_macro_abs_special(     ModelID32 model, const BehaviorScript *behavior, s16 x, s16 y, s16 z, s16 unkA, s16 unkB, s16 unkC);

void spawn_macro_objects(          s32 areaIndex, MacroObject    *macroObjList);
void spawn_macro_objects_hardcoded(s32 areaIndex, MacroObject    *macroObjList);
void spawn_special_objects(        s32 areaIndex, Collision   **specialObjList);
#ifdef NO_SEGMENTED_MEMORY
u32 get_special_objects_size(Collision *data);
#endif
