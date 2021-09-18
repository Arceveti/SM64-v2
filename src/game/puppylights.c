/// Puppylights 2.0 by Fazana. What happened to 1.0? Tragic accident.
/**
Intended for use with manipulating existing Lights1 structs for objects in real time.
Can support static lights that are loaded with the level, or lights created by objects.

Puppylights is generally intended to be used with things that don't directly use lights to colour
themselves. Inside the main function, you can pass through a colour to override the default light
but it will not be affected by environmental tinting. If you wish for an object to emit a light,
simply set the object flag OBJ_FLAG_EMIT_LIGHT and set some values to o->puppylight.

For easy light modification, you can call set_light_properties, so set all the attributes of any
given loaded puppylight struct. Objects will ignore x, y, z, active and room, as it will set all
of these automatically. It will force the PUPPYLIGHT_DYNAMIC flag, too.

If you're introducing a static light in the level script with PUPPYLIGHT_NODE, ensure it's contained
inside the respective area node it's going to be inside, otherwise it will not show up. If you do not
use rooms in your level, or if you wish for this light to be seen from any room, use -1 for that param.

If you have visual debug enabled, light nodes will show up as magenta in the world. They will be
shaped and rotated correctly, for accurate representation of their properties.
**/

#include <ultra64.h>
#include "types.h"
#include "puppylights.h"
#include "area.h"
#include "engine/math_util.h"
#include "engine/colors.h"
#include "string.h"
#include "object_fields.h"
#include "object_constants.h"
#include "camera.h"
#include "boot/memory.h"
#include "print.h"
#include "debug_box.h"
#include "object_list_processor.h"
#include "level_update.h"
#include "engine/surface_collision.h"
#include "surface_terrains.h"

#ifdef PUPPYLIGHTS

Lights1 gLevelLight;                         // Existing ambient light in the area. Will be set by the level script, though can always be changed afterwards if desired.
Bool8 levelAmbient     = FALSE;
Lights1 *sLightBase;                         // The base value where lights are written to when worked with.
// Default lights default lights
Lights1 sDefaultLights = gdSPDefLights1(DEFAULT_LIGHT_AMB, DEFAULT_LIGHT_AMB, DEFAULT_LIGHT_AMB,
                                        DEFAULT_LIGHT_COL, DEFAULT_LIGHT_COL, DEFAULT_LIGHT_COL,
                                        DEFAULT_LIGHT_DIR, DEFAULT_LIGHT_DIR, DEFAULT_LIGHT_DIR);
u16 gNumLights         = 0;                  // How many lights are loaded.
u16 gDynLightStart     = 0;                  // Where the dynamic lights will start.
struct PuppyLight *gPuppyLights[MAX_LIGHTS]; // This contains all the loaded data.
struct MemoryPool *gLightsPool;              // The memory pool where the above is stored.

// Runs after an area load, allocates the dynamic light slots.
void puppylights_allocate(void) {
    s32 numAllocate = MIN((MAX_LIGHTS - gNumLights), MAX_LIGHTS_DYNAMIC);
    s32 i;
    gDynLightStart = gNumLights;
    if (numAllocate <= 0) return; // If this happens you've allocated too many static lights and therefore cucked dynamic.
    // Now it has the number it wants, it will allocate this many extra lights, intended for dynamic lights.
    for ((i = 0); (i < numAllocate); (i++)) {
        gPuppyLights[gNumLights] = mem_pool_alloc(gLightsPool, sizeof(struct PuppyLight));
        if (gPuppyLights[gNumLights] == NULL) return;
        gPuppyLights[gNumLights]->flags  = 0x0;
        gPuppyLights[gNumLights]->active = FALSE;
        gNumLights++;
    }
}

extern Mat4 gMatStack[32];

// Function that iterates through each light.
void puppylights_iterate(struct PuppyLight *light, Lights1 *src, struct Object *obj, s32 flags) {
    Lights1 *tempLight;
    s32 lightPos[2];
    Vec3i lightRelative;
    Vec3i lightDir = { 0x00, 0x00, 0x00 };
    s32 i;
    RGBA32 colour, ambient;
    f64 scaleOrig;
    f32 scale, scale2;
    f64 scaleVal = 1.0f;
    Vec3f debugPos[2];
    // Relative positions of the object vs. the centre of the node.
    vec3_diff(lightRelative, light->pos[0], &obj->oPosVec);
    // If the nodes X and Z values are equal, then a check is made if the angle is a derivative of 90.
    // If so, then it will completely skip over the calculation that figures out position from rotation.
    // If it's a cylinder, then it ignores that check, simply because an equal sided cylinder will have the
    // same result no matter the yaw. If neither is true, then it simply checks if it's 180 degrees, since
    // That will just be the same as 0.
    if (light->pos[1][0] == light->pos[1][2]) {
        if (((light->yaw % 0x4000) == 0) || (light->flags & PUPPYLIGHT_SHAPE_CYLINDER)) {
            lightPos[0] = lightRelative[0];
            lightPos[1] = lightRelative[2];
            goto skippingTrig;
        }
    } else if ((light->yaw % 0x8000) == 0) {
        lightPos[0] = lightRelative[0];
        lightPos[1] = lightRelative[2];
        goto skippingTrig;
    }
    // Get the position based off the rotation of the box.
    lightPos[0] = lightRelative[2] * sins(-light->yaw) + lightRelative[0] * coss(-light->yaw);
    lightPos[1] = lightRelative[2] * coss(-light->yaw) - lightRelative[0] * sins(-light->yaw);
    skippingTrig:
#ifdef VISUAL_DEBUG
    vec3_copy(debugPos[0], light->pos[0]);
    vec3_copy(debugPos[1], light->pos[1]);
    debug_box_color(COLOR_RGBA32_DEBUG_LIGHT);
    debug_box_rot(debugPos[0], debugPos[1], light->yaw, (((light->flags & PUPPYLIGHT_SHAPE_CYLINDER) ? DEBUG_SHAPE_CYLINDER : DEBUG_SHAPE_BOX) | DEBUG_UCODE_DEFAULT));
#endif
    // Check if the object is inside the box, after correcting it for rotation.
    if ((-light->pos[1][0] <      lightPos[0]) && (     lightPos[0] < light->pos[1][0])
     && (-light->pos[1][1] < lightRelative[1]) && (lightRelative[1] < light->pos[1][1])
     && (-light->pos[1][2] <      lightPos[1]) && (     lightPos[1] < light->pos[1][2])) {
        // If so, then start making preparations to see how alongside they're in.
        // This takes the largest side of the box and multiplies the other axis to match the numbers.
        // This way, the colour value will scale correctly, no matter which side is entered.
        // Because positions are a vector, and Y is up, it means tempID needs to be multiplied
        // By 2 in order to reach the X and Z axis. Thanks SM64.
        // It will skip scaling the opposite axis if there's no need to.

        // Every axis needs to be the same as Z, so X and Y, if necessary, will be scaled to match it.
        // This is done, so that when calculating scale, it's done spherically.
        if (light->pos[1][0] != light->pos[1][2]) lightPos[0] /= ((f32)light->pos[1][0] / light->pos[1][2]);
        // Same for Y axis.
        if (light->pos[1][1] != light->pos[1][2]) lightRelative[1] /= ((f32)light->pos[1][1] / light->pos[1][2]);
        if (light->flags & PUPPYLIGHT_IGNORE_Y) {
            scaleOrig = (sqr(lightPos[0]) + sqr(lightPos[1]));
        } else {
            scaleOrig = (sqr(lightPos[0]) + sqr(lightRelative[1]) + sqr(lightPos[1]));
        }
        scaleVal = sqr(light->pos[1][2]);
        // If it's a cylinder, then bin anything outside it.
        if ((light->flags & PUPPYLIGHT_SHAPE_CYLINDER) && (scaleOrig > scaleVal)) return;
    } else {
        return;
    }
    f32 fac = (f32)(light->epicentre / 100.0f);
    tempLight = segmented_to_virtual(src);
    // Now we have a scale value and a scale factor, we can start lighting things up.
    // Convert to a percentage.
    scale = (scaleOrig / scaleVal);
    scale = CLAMP(scale, 0.0f, 1.0f);
    // Reduce scale2 by the epicentre.
    scale2 = ((scale - fac) * (1 + fac));
    scale2 = CLAMP(scale2, 0.0f, 1.0f);
    // Get the direction numbers we want by applying some maths to the relative positions. We use 64 because light directions range from -64 to 63.
    // Note: can this be optimised further? Simply squaring lightRelative and then dividing it by preScale doesn't work.
    if (light->flags & PUPPYLIGHT_DIRECTIONAL) {
        lightDir[0] = (((lightRelative[0]) * 64.0f) / light->pos[1][0]);
        lightDir[1] = (((lightRelative[1]) * 64.0f) / light->pos[1][1]);
        lightDir[2] = (((lightRelative[2]) * 64.0f) / light->pos[1][2]);
    }
    // Get direction if applicable.
    for ((i = 0); (i < 3); (i++)) {
        fac = (light->rgba[3] / 255.0f);
        // So it works by starting from the final colour, and then lerping to the original colour, by a factor of the epicentre corrected scale. Light opacity affects this further.
        colour = approach_f32_asymptotic(light->rgba[i], tempLight->l[0].l.col[i], (scale2 * fac));
        // If it's a directional light, then increase the current ambient by 50%, to give the effect better.
        // Otherwise, just normalise the brightness to keep it in line with the current ambient.
        // And now to apply the values.
        tempLight->l[0].l.col [i] = colour;
        tempLight->l[0].l.colc[i] = colour;
        // Ambient, too.
        if (!(light->flags & PUPPYLIGHT_DIRECTIONAL)) {
            ambient = approach_f32_asymptotic((light->rgba[i] / 2), tempLight->a.l.col[i], (scale * fac));
            tempLight->a.l.col [i] = ambient;
            tempLight->a.l.colc[i] = ambient;
        }
        // A slightly hacky way to offset the ambient lighting in order to prevent directional lighting from having a noticeable change in ambient brightness.
        if (flags & LIGHTFLAG_DIRECTIONAL_OFFSET) {
            ambient = (tempLight->a.l.col[i] * 2);
            ambient = approach_f32_asymptotic(MIN(ambient, 0xFF), tempLight->a.l.col[i], (scale2 * fac));
            tempLight->a.l.col [i] = ambient;
            tempLight->a.l.colc[i] = ambient;
        }
        // Apply direction. It takes the relative positions, and then multiplies them with the perspective matrix to get a correct direction.
        // Index 1 of the first dimension of gMatStack is perspective. Note that if you ever decide to cheat your way into rendering things after the game does :^)
        if (light->flags & PUPPYLIGHT_DIRECTIONAL) tempLight->l->l.dir[i] = approach_f32_asymptotic((s8)((lightDir[0] * gMatStack[1][0][i]) + (lightDir[1] * gMatStack[1][1][i]) + (lightDir[2] * gMatStack[1][2][i])), tempLight->l->l.dir[i], scale);
    }
}

// Main function. Run this in the object you wish to illuminate, and just give it its light, object pointer and any potential flags if you want to use them.
// If the object has multiple lights, then you run this for each light.
void puppylights_run(Lights1 *src, struct Object *obj, UNUSED s32 flags, RGBA32 baseColour) {
    s32 i;
    s32 numlights = 0;
    Bool32 offsetPlaced = FALSE;
    s32 lightFlags = flags;
    s32 colour;
    if (gCurrLevelNum < 4) return;
    // Checks if there's a hardset colour. Colours are only the first 3 bytes, so you can really put whatever you want in the last.
    // If there isn't a colour, then it decides whether to apply the ambient lighting, or the default lighting as the baseline.
    // Otherwise, it hardsets a colour to begin with. I don't recommend you use this, simply because it's intended to be used
    // as a hacky quick-fix for models coloured by lights. Lightcoloured models don't blend nearly as nicely as ones coloured
    // by other means.
    sLightBase = (levelAmbient ? &gLevelLight : &sDefaultLights);
    // sLightBase = (levelAmbient ? &gLevelLight : segmented_to_virtual(src));
    if (baseColour >= 0x100) {
        for ((i = 0); (i < 3); (i++)) {
            colour = (((baseColour >> (24 - (i * 8)))) & 0xFF);
            sLightBase->l[0].l.col[i]  = colour;
            sLightBase->l[0].l.colc[i] = colour;
            sLightBase->a.l.col[i]     = (colour / 2);
            sLightBase->a.l.colc[i]    = (colour / 2);
            sLightBase->l->l.dir[i]    = DEFAULT_LIGHT_DIR;
        }
    }
    memcpy(segmented_to_virtual(src), &sLightBase[0], sizeof(Lights1));
    for ((i = 0); (i < gNumLights); (i++)) {
        if ((gPuppyLights[i]->rgba[3] > 0) && (gPuppyLights[i]->active) && (gPuppyLights[i]->area == gCurrAreaIndex) && ((gPuppyLights[i]->room == -1) || (gPuppyLights[i]->room == gMarioCurrentRoom))) {
            if ((gPuppyLights[i]->flags & PUPPYLIGHT_DIRECTIONAL) && !offsetPlaced) {
                lightFlags  |= LIGHTFLAG_DIRECTIONAL_OFFSET;
                offsetPlaced = TRUE;
            } else {
                lightFlags &= ~LIGHTFLAG_DIRECTIONAL_OFFSET;
            }
            puppylights_iterate(gPuppyLights[i], src, obj, lightFlags);
            numlights++;
        }
    }
}

// Sets and updates dynamic lights from objects.
// 0xFFFF is essentially the null ID. If the display flag is met, it will find and set an ID, otherwise it frees up the spot.
void puppylights_object_emit(struct Object *obj) {
    s32 i;
    if (gCurrLevelNum < 4) return;
    if (obj->oFlags & OBJ_FLAG_EMIT_LIGHT) {
        Vec3d d;
        vec3_diff(d, &obj->oPosVec, gMarioState->pos);
        if (vec3_sumsq(d) > vec3_sumsq(obj->puppylight.pos[1])) goto deallocate; // That's right. I used a goto. Eat your heart out xkcd.
        if (obj->oLightID == 0xFFFF) {
            Bool32 fadingExists = FALSE;
            if (ABSI(gNumLights - gDynLightStart) < MAX_LIGHTS_DYNAMIC) goto deallocate;
            for ((i = gDynLightStart); (i < MIN((gDynLightStart + MAX_LIGHTS_DYNAMIC), MAX_LIGHTS)); (i++)) {
                if (gPuppyLights[i]->active) {
                    if (gPuppyLights[i]->flags & PUPPYLIGHT_DELETE) fadingExists = TRUE;
                    continue;
                }
                memcpy(gPuppyLights[i], &obj->puppylight, sizeof(struct PuppyLight));
                gPuppyLights[i]->active = TRUE;
                gPuppyLights[i]->area   = gCurrAreaIndex;
                gPuppyLights[i]->room   = obj->oRoom;
                obj->oLightID           = i;
                goto updatepos;
            }
            // Go through all the lights again, now this time, ignore the fading light flag and overwrite them.
            if (fadingExists) {
                for ((i = gDynLightStart); (i < MIN((gDynLightStart + MAX_LIGHTS_DYNAMIC), MAX_LIGHTS)); (i++)) {
                    if ((gPuppyLights[i]->active) && !(gPuppyLights[i]->flags & PUPPYLIGHT_DELETE)) continue;
                    memcpy(gPuppyLights[i], &obj->puppylight, sizeof(struct PuppyLight));
                    gPuppyLights[i]->active = TRUE;
                    gPuppyLights[i]->area   = gCurrAreaIndex;
                    gPuppyLights[i]->room   = obj->oRoom;
                    gPuppyLights[i]->flags &= ~PUPPYLIGHT_DELETE;
                    obj->oLightID = i;
                    goto updatepos;
                }
            }
        } else {
            updatepos:
            vec3_copy(gPuppyLights[obj->oLightID]->pos[0], &obj->oPosVec);
        }
    } else {
        deallocate:
        if (obj->oLightID != 0xFFFF) {
            gPuppyLights[obj->oLightID]->active = FALSE;
            gPuppyLights[obj->oLightID]->flags  = 0x0;
        }
        obj->oLightID = 0xFFFF;
    }
}

// A bit unorthodox, but anything to avoid having to set up data to pass through in the original function.
// Objects will completely ignore X, Y, Z and active though.
void set_light_properties(struct PuppyLight *light, s32 x, s32 y, s32 z, s32 offsetX, s32 offsetY, s32 offsetZ, Angle32 yaw, s32 epicentre, RGBA32 colour, s32 flags, RoomData room, Bool32 active) {
    light->active = active;
    vec3_set(light->pos[0], x, y, z);
    vec3_set(light->pos[1], MAX(offsetX, 10), MAX(offsetY, 10), MAX(offsetZ, 10));
    RGBA32_TO_COLORRGBA(light->rgba, colour);
    light->yaw       = yaw;
    light->area      = gCurrAreaIndex;
    light->room      = room;
    light->epicentre = epicentre;
    if (!(flags & PUPPYLIGHT_SHAPE_CYLINDER) && (flags & PUPPYLIGHT_SHAPE_CUBE)) light->flags |= PUPPYLIGHT_SHAPE_CYLINDER;
    light->flags |= (flags | PUPPYLIGHT_DYNAMIC);
}

// You can run these in objects to enable or disable their light properties.
void cur_obj_enable_light(void) {
    o->oFlags |= OBJ_FLAG_EMIT_LIGHT;
}

void cur_obj_disable_light(void) {
    o->oFlags &= ~OBJ_FLAG_EMIT_LIGHT;
    if (gPuppyLights[o->oLightID] && (o->oLightID != 0xFFFF)) gPuppyLights[o->oLightID]->flags |= PUPPYLIGHT_DELETE;
}

void obj_enable_light(struct Object *obj) {
    obj->oFlags |= OBJ_FLAG_EMIT_LIGHT;
}

void obj_disable_light(struct Object *obj) {
    obj->oFlags &= ~OBJ_FLAG_EMIT_LIGHT;
    if (gPuppyLights[obj->oLightID] && (obj->oLightID != 0xFFFF)) gPuppyLights[obj->oLightID]->flags |= PUPPYLIGHT_DELETE;
}

// This is ran during a standard area update
void delete_lights(void) {
    s32 i;
    for ((i = 0); (i < gNumLights); (i++)) {
        if (gPuppyLights[i]->active && (gPuppyLights[i]->flags & PUPPYLIGHT_DELETE)) {
            gPuppyLights[i]->pos[1][0] = approach_f32_asymptotic(gPuppyLights[i]->pos[1][0], 0, 0.15f);
            gPuppyLights[i]->pos[1][1] = approach_f32_asymptotic(gPuppyLights[i]->pos[1][1], 0, 0.15f);
            gPuppyLights[i]->pos[1][2] = approach_f32_asymptotic(gPuppyLights[i]->pos[1][2], 0, 0.15f);
            if ((gPuppyLights[i]->pos[1][0] < 1.0f) && (gPuppyLights[i]->pos[1][1] < 1.0f) && (gPuppyLights[i]->pos[1][2] < 1.0f)) {
                gPuppyLights[i]->flags &= ~PUPPYLIGHT_DELETE;
                gPuppyLights[i]->active = FALSE;
            }
        }
    }
}

#endif
