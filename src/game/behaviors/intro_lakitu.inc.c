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
Bool32 intro_lakitu_set_pos_and_focus(struct Object *o, struct CutsceneSplinePoint offset[], struct CutsceneSplinePoint focus[]) {
    Vec3f newOffset, newFocus;
    Bool32 splineFinished = FALSE;
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
    switch (o->oAction) {
        case INTRO_LAKITU_ACT_INIT:
            cur_obj_disable_rendering();
            o->oIntroLakituSplineSegment         = 0.0f;
            o->oIntroLakituSplineSegmentProgress = 0.0f;
            o->oIntroLakituCloud                 = spawn_object_relative_with_scale(CLOUD_BP_LAKITU_CLOUD, 0, 0, 0, 2.0f, o, MODEL_MIST, bhvCloud);
            o->oAction                           = ((gCamera->cutscene == CUTSCENE_END_WAVING) ? INTRO_LAKITU_ACT_CUTSCENE_END_WAVING_1 : INTRO_LAKITU_ACT_CUTSCENE_INTRO_1);
            break;
        case INTRO_LAKITU_ACT_CUTSCENE_INTRO_1:
            cur_obj_enable_rendering();
            if ((gCutsceneTimer > 350) && (gCutsceneTimer < 458)) vec3f_copy_y_off(&o->oPosVec, gCamera->pos, 500.0f);
            if (gCutsceneTimer > 52) cur_obj_play_sound_1(SOUND_AIR_LAKITU_FLY_HIGHPRIO);
            if (intro_lakitu_set_pos_and_focus(o, gIntroLakituStartToPipeOffsetFromCamera, gIntroLakituStartToPipeFocus)) o->oAction = INTRO_LAKITU_ACT_CUTSCENE_INTRO_2;
            switch (o->oTimer) {
#if defined(VERSION_US) || defined(VERSION_SH)
                case 534: cur_obj_play_sound_2(SOUND_ACTION_FLYING_FAST);  break;
                case 581: cur_obj_play_sound_2(SOUND_ACTION_INTRO_UNK45E); break;
#endif
                case 73: o->oAnimState++; break;
                case 74: o->oAnimState--; break;
                case 82: o->oAnimState++; break;
                case 84: o->oAnimState--; break;
            }
#ifdef VERSION_EU
            if (o->oTimer == 446) cur_obj_play_sound_2(SOUND_ACTION_FLYING_FAST);
            if (o->oTimer == 485) cur_obj_play_sound_2(SOUND_ACTION_INTRO_UNK45E);
#endif
            break;
        case INTRO_LAKITU_ACT_CUTSCENE_INTRO_2:
#ifdef VERSION_EU
            if (gCutsceneTimer > 599) {
#else
            if (gCutsceneTimer > 720) {
#endif
                o->oAction                    = INTRO_LAKITU_ACT_CUTSCENE_INTRO_3;
                o->oIntroLakituDistToBirdsX   =  1400.0f;
                o->oIntroLakituDistToBirdsZ   = -4096.0f;
                o->oIntroLakituEndBirds1DestZ =  2048.0f;
                o->oIntroLakituEndBirds1DestY =  -200.0f;
                o->oMoveAngleYaw              = DEG(180);
                o->oFaceAngleYaw              = (o->oMoveAngleYaw + DEG(90));
                o->oMoveAnglePitch            =    0x800;
            }
            cur_obj_play_sound_1(SOUND_AIR_LAKITU_FLY_HIGHPRIO);
            break;
        case INTRO_LAKITU_ACT_CUTSCENE_INTRO_3:
            cur_obj_play_sound_1(SOUND_AIR_LAKITU_FLY_HIGHPRIO);
            vec3f_set(fromPoint, -1128.0f, 560.0f, 4664.0f);
            o->oMoveAngleYaw             += 0x200;
            approach_f32_asymptotic_bool(&o->oIntroLakituDistToBirdsX, 100.0f, 0.03f);
            o->oFaceAnglePitch            = atan2s(200.0f, (o->oPosY - 400.0f));
            o->oFaceAngleYaw              = approach_s16_asymptotic(o->oFaceAngleYaw, (o->oMoveAngleYaw + DEG(180)), 4);
            vec3f_set_dist_and_angle(fromPoint, toPoint, o->oIntroLakituDistToBirdsX, 0, o->oMoveAngleYaw);
            toPoint[1] += (150.0f * coss((s16) o->oIntroLakituDistToBirdsZ));
            o->oIntroLakituDistToBirdsZ  += o->oIntroLakituEndBirds1DestZ;
            approach_f32_asymptotic_bool(&o->oIntroLakituEndBirds1DestZ, 512.0f, 0.05f);
            toPoint[0] += o->oIntroLakituEndBirds1DestY;
            approach_f32_asymptotic_bool(&o->oIntroLakituEndBirds1DestY,   0.0f, 0.05f);
            vec3f_copy(&o->oPosVec, toPoint);
            if (o->oTimer == 31) {
                o->oPosY -= 158.0f;
                // Spawn white ground particles
                spawn_mist_from_global(); // yOffset?
                o->oPosY += 158.0f;
            }
#ifdef VERSION_EU
#define TIMER 74
#else
#define TIMER 98
#endif
            if (o->oTimer == TIMER) {
                obj_mark_for_deletion(o);
                obj_mark_for_deletion(o->oIntroLakituCloud);
            }
#ifndef VERSION_JP
            if (o->oTimer == 14) cur_obj_play_sound_2(SOUND_ACTION_INTRO_UNK45F);
#endif
            break;
        case INTRO_LAKITU_ACT_CUTSCENE_END_WAVING_1:
            cur_obj_enable_rendering();
            vec3f_set(offset, -100.0f, 100.0f, 300.0f);
            offset_rotated(toPoint, gCamera->pos, offset, sMarioCamState->faceAngle);
            vec3f_copy(&o->oPosVec, toPoint);
            o->oMoveAnglePitch = DEG(22.5);
            o->oMoveAngleYaw   = 0x9000; // DEG(-157.5);
            o->oFaceAnglePitch = (o->oMoveAnglePitch / 2);
            o->oFaceAngleYaw   =  o->oMoveAngleYaw;
            o->oAction         = INTRO_LAKITU_ACT_CUTSCENE_END_WAVING_2;
            break;
        case INTRO_LAKITU_ACT_CUTSCENE_END_WAVING_2:
            vec3f_copy(toPoint, &o->oPosVec);
            if (o->oTimer > 60) {
                approach_f32_asymptotic_bool(&o->oForwardVel, -10.0f, 0.05f);
                o->oMoveAngleYaw   += 0x78;
                o->oMoveAnglePitch += 0x40;
                vec3f_get_yaw(toPoint, gCamera->pos, &targetYaw);
                o->oFaceAngleYaw    = approach_s16_symmetric(o->oFaceAngleYaw, targetYaw, 0x200);
            }
            if (o->oTimer > 105) {
                o->oAction         = INTRO_LAKITU_ACT_CUTSCENE_END_WAVING_3;
                o->oMoveAnglePitch = 0xE00;
            }
            o->oFaceAnglePitch = 0x0;
            cur_obj_set_pos_via_transform();
            break;
        case INTRO_LAKITU_ACT_CUTSCENE_END_WAVING_3:
            vec3f_copy(toPoint, &o->oPosVec);
            approach_f32_asymptotic_bool(&o->oForwardVel, 60.0f, 0.05f);
            vec3f_get_yaw(toPoint, gCamera->pos, &targetYaw);
            o->oFaceAngleYaw   = approach_s16_symmetric(o->oFaceAngleYaw, targetYaw, 0x200);
            if (o->oTimer < 62) o->oMoveAngleYaw = approach_s16_asymptotic(o->oMoveAngleYaw, 0x1800, 0x1E);
            o->oMoveAnglePitch = approach_s16_symmetric(o->oMoveAnglePitch, -0x2000, 0x5A);
            o->oFaceAnglePitch = 0x0;
            cur_obj_set_pos_via_transform();
            break;
    }
}
#undef TIMER
