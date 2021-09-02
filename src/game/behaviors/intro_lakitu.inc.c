/**
 * @file intro_lakitu.inc.c
 * This file implements lakitu's behvaior during the intro cutscene.
 * It's also used during the ending cutscene.
 */


/**
 * Add the camera's position to `offset`, rotate the point to be relative to the camera's focus, then
 * set lakitu's location.
 */
void intro_lakitu_set_offset_from_camera(struct Object *o, Vec3f offset) {
    f32 dist;
    Vec3a focusAngles;
    Angle offsetPitch, offsetYaw;
    vec3f_add(offset, gCamera->pos);
    vec3f_get_dist_and_angle(gCamera->pos, gCamera->focus, &dist, &focusAngles[0],                &focusAngles[1]);
    vec3f_get_dist_and_angle(gCamera->pos,         offset, &dist, &offsetPitch,                   &offsetYaw);
    vec3f_set_dist_and_angle(gCamera->pos,         offset,  dist, (focusAngles[0] + offsetPitch), (focusAngles[1] + offsetYaw));
    vec3f_copy(&o->oPosVec, offset);
}

void intro_lakitu_set_focus(struct Object *o, Vec3f newFocus) {
    Vec3f origin;
    Angle pitch, yaw;
    // newFocus is an offset from lakitu's origin, not a point in the world.
    vec3f_set(origin, 0.0f, 0.0f, 0.0f);
    vec3f_get_angle(origin, newFocus, &pitch, &yaw);
    o->oFaceAnglePitch = pitch;
    o->oFaceAngleYaw   = yaw;
}

/**
 * Move lakitu along the spline `offset`, relative to the camera, and face him towards the corresponding
 * location along the spline `focus`.
 */
s32 intro_lakitu_set_pos_and_focus(struct Object *o, struct CutsceneSplinePoint offset[], struct CutsceneSplinePoint focus[]) {
    Vec3f newOffset, newFocus;
    s32 splineFinished = FALSE;
    s16 splineSegment  = o->oIntroLakituSplineSegment;
    if (move_point_along_spline(newFocus, offset, &splineSegment, &(o->oIntroLakituSplineSegmentProgress))
     || move_point_along_spline(newOffset, focus, &splineSegment, &(o->oIntroLakituSplineSegmentProgress))) splineFinished = TRUE;
    o->oIntroLakituSplineSegment = splineSegment;
    intro_lakitu_set_offset_from_camera(o, newOffset);
    intro_lakitu_set_focus(             o, newFocus );
    return splineFinished;
}

void bhv_intro_lakitu_loop(void) {
    Vec3f offset, fromPoint, toPoint;
    Angle targetYaw;
    switch (gCurrentObject->oAction) {
        case INTRO_LAKITU_ACT_INIT:
            cur_obj_disable_rendering();
            gCurrentObject->oIntroLakituSplineSegment         = 0.0f;
            gCurrentObject->oIntroLakituSplineSegmentProgress = 0.0f;
            gCurrentObject->oIntroLakituCloud                 = spawn_object_relative_with_scale(CLOUD_BP_LAKITU_CLOUD, 0, 0, 0, 2.0f, gCurrentObject, MODEL_MIST, bhvCloud);
            gCurrentObject->oAction                           = ((gCamera->cutscene == CUTSCENE_END_WAVING) ? INTRO_LAKITU_ACT_CUTSCENE_END_WAVING_1 : INTRO_LAKITU_ACT_CUTSCENE_INTRO_1);
            break;
        case INTRO_LAKITU_ACT_CUTSCENE_INTRO_1:
            cur_obj_enable_rendering();
            if ((gCutsceneTimer > 350) && (gCutsceneTimer < 458)) {
                gCurrentObject->oPosX =  gCamera->pos[0];
                gCurrentObject->oPosY = (gCamera->pos[1] + 500.0f);
                gCurrentObject->oPosZ =  gCamera->pos[2];
            }
            if (gCutsceneTimer > 52) cur_obj_play_sound_1(SOUND_AIR_LAKITU_FLY_HIGHPRIO);
            if (intro_lakitu_set_pos_and_focus(gCurrentObject, gIntroLakituStartToPipeOffsetFromCamera, gIntroLakituStartToPipeFocus)) gCurrentObject->oAction = INTRO_LAKITU_ACT_CUTSCENE_INTRO_2;
            switch (gCurrentObject->oTimer) {
#if defined(VERSION_US) || defined(VERSION_SH)
                case 534: cur_obj_play_sound_2(SOUND_ACTION_FLYING_FAST);  break;
                case 581: cur_obj_play_sound_2(SOUND_ACTION_INTRO_UNK45E); break;
#endif
                case 73: gCurrentObject->oAnimState++; break;
                case 74: gCurrentObject->oAnimState--; break;
                case 82: gCurrentObject->oAnimState++; break;
                case 84: gCurrentObject->oAnimState--; break;
            }
#ifdef VERSION_EU
            if (gCurrentObject->oTimer == 446) cur_obj_play_sound_2(SOUND_ACTION_FLYING_FAST);
            if (gCurrentObject->oTimer == 485) cur_obj_play_sound_2(SOUND_ACTION_INTRO_UNK45E);
#endif
            break;
        case INTRO_LAKITU_ACT_CUTSCENE_INTRO_2:
#ifdef VERSION_EU
            if (gCutsceneTimer > 599) {
#else
            if (gCutsceneTimer > 720) {
#endif
                gCurrentObject->oAction                    = INTRO_LAKITU_ACT_CUTSCENE_INTRO_3;
                gCurrentObject->oIntroLakituDistToBirdsX   =  1400.0f;
                gCurrentObject->oIntroLakituDistToBirdsZ   = -4096.0f;
                gCurrentObject->oIntroLakituEndBirds1DestZ =  2048.0f;
                gCurrentObject->oIntroLakituEndBirds1DestY =  -200.0f;
                gCurrentObject->oMoveAngleYaw              = DEG(180);
                gCurrentObject->oFaceAngleYaw              = (gCurrentObject->oMoveAngleYaw + DEG(90));
                gCurrentObject->oMoveAnglePitch            =    0x800;
            }
            cur_obj_play_sound_1(SOUND_AIR_LAKITU_FLY_HIGHPRIO);
            break;
        case INTRO_LAKITU_ACT_CUTSCENE_INTRO_3:
            cur_obj_play_sound_1(SOUND_AIR_LAKITU_FLY_HIGHPRIO);
            vec3f_set(fromPoint, -1128.0f, 560.0f, 4664.0f);
            gCurrentObject->oMoveAngleYaw             += 0x200;
            approach_f32_asymptotic_bool(&gCurrentObject->oIntroLakituDistToBirdsX, 100.0f, 0.03f);
            gCurrentObject->oFaceAnglePitch            = atan2s(200.0f, (gCurrentObject->oPosY - 400.0f));
            gCurrentObject->oFaceAngleYaw              = approach_s16_asymptotic(gCurrentObject->oFaceAngleYaw, (gCurrentObject->oMoveAngleYaw + DEG(180)), 4);
            vec3f_set_dist_and_angle(fromPoint, toPoint, gCurrentObject->oIntroLakituDistToBirdsX, 0, gCurrentObject->oMoveAngleYaw);
            toPoint[1] += (150.0f * coss((s16) gCurrentObject->oIntroLakituDistToBirdsZ));
            gCurrentObject->oIntroLakituDistToBirdsZ  += gCurrentObject->oIntroLakituEndBirds1DestZ;
            approach_f32_asymptotic_bool(&gCurrentObject->oIntroLakituEndBirds1DestZ, 512.0f, 0.05f);
            toPoint[0] += gCurrentObject->oIntroLakituEndBirds1DestY;
            approach_f32_asymptotic_bool(&gCurrentObject->oIntroLakituEndBirds1DestY,   0.0f, 0.05f);
            vec3f_copy(&gCurrentObject->oPosVec, toPoint);
            if (gCurrentObject->oTimer == 31) {
                gCurrentObject->oPosY -= 158.0f;
                // Spawn white ground particles
                spawn_mist_from_global(); // yOffset?
                gCurrentObject->oPosY += 158.0f;
            }
#ifdef VERSION_EU
#define TIMER 74
#else
#define TIMER 98
#endif
            if (gCurrentObject->oTimer == TIMER) {
                obj_mark_for_deletion(gCurrentObject);
                obj_mark_for_deletion(gCurrentObject->oIntroLakituCloud);
            }
#ifndef VERSION_JP
            if (gCurrentObject->oTimer == 14) cur_obj_play_sound_2(SOUND_ACTION_INTRO_UNK45F);
#endif
            break;
        case INTRO_LAKITU_ACT_CUTSCENE_END_WAVING_1:
            cur_obj_enable_rendering();
            vec3f_set(offset, -100.0f, 100.0f, 300.0f);
            offset_rotated(toPoint, gCamera->pos, offset, sMarioCamState->faceAngle);
            vec3f_copy(&gCurrentObject->oPosVec, toPoint);
            gCurrentObject->oMoveAnglePitch = DEG(22.5);
            gCurrentObject->oMoveAngleYaw   = 0x9000; // DEG(-157.5);
            gCurrentObject->oFaceAnglePitch = (gCurrentObject->oMoveAnglePitch / 2);
            gCurrentObject->oFaceAngleYaw   =  gCurrentObject->oMoveAngleYaw;
            gCurrentObject->oAction         = INTRO_LAKITU_ACT_CUTSCENE_END_WAVING_2;
            break;
        case INTRO_LAKITU_ACT_CUTSCENE_END_WAVING_2:
            vec3f_copy(toPoint, &gCurrentObject->oPosVec);
            if (gCurrentObject->oTimer > 60) {
                approach_f32_asymptotic_bool(&gCurrentObject->oForwardVel, -10.0f, 0.05f);
                gCurrentObject->oMoveAngleYaw   += 0x78;
                gCurrentObject->oMoveAnglePitch += 0x40;
                vec3f_get_yaw(toPoint, gCamera->pos, &targetYaw);
                gCurrentObject->oFaceAngleYaw    = approach_s16_symmetric(gCurrentObject->oFaceAngleYaw, targetYaw, 0x200);
            }
            if (gCurrentObject->oTimer > 105) {
                gCurrentObject->oAction         = INTRO_LAKITU_ACT_CUTSCENE_END_WAVING_3;
                gCurrentObject->oMoveAnglePitch = 0xE00;
            }
            gCurrentObject->oFaceAnglePitch = 0x0;
            cur_obj_set_pos_via_transform();
            break;
        case INTRO_LAKITU_ACT_CUTSCENE_END_WAVING_3:
            vec3f_copy(toPoint, &gCurrentObject->oPosVec);
            approach_f32_asymptotic_bool(&gCurrentObject->oForwardVel, 60.0f, 0.05f);
            vec3f_get_yaw(toPoint, gCamera->pos, &targetYaw);
            gCurrentObject->oFaceAngleYaw   = approach_s16_symmetric(gCurrentObject->oFaceAngleYaw, targetYaw, 0x200);
            if (gCurrentObject->oTimer < 62) gCurrentObject->oMoveAngleYaw = approach_s16_asymptotic(gCurrentObject->oMoveAngleYaw, 0x1800, 0x1E);
            gCurrentObject->oMoveAnglePitch = approach_s16_symmetric(gCurrentObject->oMoveAnglePitch, -0x2000, 0x5A);
            gCurrentObject->oFaceAnglePitch = 0x0;
            cur_obj_set_pos_via_transform();
            break;
    }
}
#undef TIMER
