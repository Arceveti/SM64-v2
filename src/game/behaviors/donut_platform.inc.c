// static Vec3s sDonutPlatformPositions[] = {
//     { 0x0B4C, 0xF7D7, 0x19A4 }, { 0xF794, 0x08A3, 0xFFA9 }, { 0x069C, 0x09D8, 0xFFE0 },
//     { 0x05CF, 0x09D8, 0xFFE0 }, { 0x0502, 0x09D8, 0xFFE0 }, { 0x054C, 0xF7D7, 0x19A4 },
//     { 0x0A7F, 0xF7D7, 0x19A4 }, { 0x09B2, 0xF7D7, 0x19A4 }, { 0x06E6, 0xF7D7, 0x19A4 },
//     { 0x0619, 0xF7D7, 0x19A4 }, { 0xEFB5, 0xF7D7, 0x19A4 }, { 0x00E6, 0xF7D7, 0x19A4 },
//     { 0x0019, 0xF7D7, 0x19A4 }, { 0xFF4D, 0xF7D7, 0x19A4 }, { 0xF081, 0xF7D7, 0x19A4 },
//     { 0xE34F, 0xF671, 0x197A }, { 0xEEE8, 0xF7D7, 0x19A4 }, { 0xE74F, 0xF7D7, 0x197A },
//     { 0xE683, 0xF7D7, 0x197A }, { 0xE5B6, 0xF7D7, 0x197A }, { 0xEE83, 0xF4A4, 0x19A4 },
//     { 0xE41C, 0xF671, 0x197A }, { 0xE4E9, 0xF671, 0x197A }, { 0xECE9, 0xF4A4, 0x19A4 },
//     { 0xEDB6, 0xF4A4, 0x19A4 }, { 0xFC3F, 0x0A66, 0xFF45 }, { 0x00EF, 0x04CD, 0xFF53 },
//     { 0x0022, 0x04CD, 0xFF53 }, { 0xFF57, 0x04CD, 0xFF53 }, { 0xFB73, 0x0A66, 0xFF45 },
//     { 0xFD0C, 0x0A66, 0xFF45 },
// };
static Vec3s sDonutPlatformPositions[] = {
    {  2892, -2089,  6564 }, { -2156,  2211,  -87 }, {  1692,  2520,   -32 },
    {  1487,  2520,   -32 }, {  1282,  2520,  -32 }, {  1356, -2089,  6564 },
    {  2687, -2089,  6564 }, {  2482, -2089, 6564 }, {  1766, -2089,  6564 },
    {  1561, -2089,  6564 }, { -4171, -2089, 6564 }, {   230, -2089,  6564 },
    {    25, -2089,  6564 }, {  -179, -2089, 6564 }, { -3967, -2089,  6564 },
    { -7345, -2447,  6522 }, { -4376, -2089, 6564 }, { -6321, -2089,  6522 },
    { -6525, -2089,  6522 }, { -6730, -2089, 6522 }, { -4477, -2908,  6564 },
    { -7140, -2447,  6522 }, { -6935, -2447, 6522 }, { -4887, -2908,  6564 },
    { -4682, -2908,  6564 }, {  -961,  2662, -187 }, {   239,  1229,  -173 },
    {    34,  1229,  -173 }, {  -169,  1229, -173 }, { -1165,  2662,  -187 },
    {  -756,  2662,  -187 },
};

void bhv_donut_platform_spawner_update(void) {
    s32 i;
    s32 platformFlag;
    Vec3f d;
    f32 marioSqDist;
    for (((i = 0), (platformFlag = 1)); (i < 31); ((i++), (platformFlag = (platformFlag << 1)))) {
        if (!(o->oDonutPlatformSpawnerSpawnedPlatforms & platformFlag)) {
            //! vec3f/s diff
            d[0] = gMarioObject->oPosX - sDonutPlatformPositions[i][0];
            d[1] = gMarioObject->oPosY - sDonutPlatformPositions[i][1];
            d[2] = gMarioObject->oPosZ - sDonutPlatformPositions[i][2];
            marioSqDist = (sqr(d[0]) + sqr(d[1]) + sqr(d[2]));
            // dist > 1000 and dist < 2000
            if ((marioSqDist > 1000000.0f) && (marioSqDist < 4000000.0f)) {
                if (spawn_object_relative(i, sDonutPlatformPositions[i][0],
                                             sDonutPlatformPositions[i][1],
                                             sDonutPlatformPositions[i][2],
                                             o, MODEL_RR_DONUT_PLATFORM, bhvDonutPlatform) != NULL) {
                    o->oDonutPlatformSpawnerSpawnedPlatforms |= platformFlag;
                }
            }
        }
    }
}

void bhv_donut_platform_update(void) {
    if ((o->oTimer != 0) && ((o->oMoveFlags & OBJ_MOVE_MASK_ON_GROUND) || (o->oDistanceToMario > 2500.0f))) {
        o->parentObj->oDonutPlatformSpawnerSpawnedPlatforms = o->parentObj->oDonutPlatformSpawnerSpawnedPlatforms & ((1 << o->oBehParams2ndByte) ^ 0xFFFFFFFF);
        if (o->oDistanceToMario > 2500.0f) {
            obj_mark_for_deletion(o);
        } else {
            obj_explode_and_spawn_coins(150.0f, COIN_TYPE_YELLOW);
            create_sound_spawner(SOUND_GENERAL_DONUT_PLATFORM_EXPLOSION);
        }
    } else {
        if (o->oGravity == 0.0f) {
            if (gMarioObject->platform == o) {
                cur_obj_shake_y(4.0f);
                if (o->oTimer > 15) o->oGravity = -0.1f;
            } else {
                cur_obj_set_pos_to_home();
                o->oTimer = 0;
            }
        } else {
            cur_obj_update_floor_and_walls();
            cur_obj_move_standard(78);
        }
        load_object_collision_model();
    }
}
