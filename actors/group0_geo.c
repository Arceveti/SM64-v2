#include <ultra64.h>
#include "sm64.h"
#include "geo_commands.h"

#include "make_const_nonconst.h"

#include "common1.h"
#include "group0.h"

#include "bubble/geo.inc.c"
#include "walk_smoke/geo.inc.c"
#include "burn_smoke/geo.inc.c"
#include "stomp_smoke/geo.inc.c"
#include "water_wave/geo.inc.c"
#include "sparkle/geo.inc.c"
#include "water_splash/geo.inc.c"
#include "sparkle_animation/geo.inc.c"
// #undef LAYER_OPAQUE
// #undef LAYER_ALPHA
// #define LAYER_OPAQUE LAYER_SILHOUETTE_OPAQUE
// #define LAYER_ALPHA  LAYER_SILHOUETTE_ALPHA
// #define geo_mirror_mario_set_alpha geo_vanish_mario_set_alpha
#include "mario/geo.inc.c"
// #undef LAYER_OPAQUE
// #undef LAYER_ALPHA
// #define LAYER_OPAQUE 0x1
// #define LAYER_ALPHA  0x4
