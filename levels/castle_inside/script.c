#include <ultra64.h>
#include "sm64.h"
#include "behavior_data.h"
#include "model_ids.h"
#include "seq_ids.h"
#include "dialog_ids.h"
#include "segment_symbols.h"
#include "level_commands.h"

#include "game/level_update.h"

#include "levels/scripts.h"

#include "actors/common1.h"

#include "make_const_nonconst.h"
#include "levels/castle_inside/header.h"

static const LevelScript script_func_local_castle_inside_floor_1_warps[] = {
    WARP_NODE(/*id*/ 0x00, /*destLevel*/ LEVEL_CASTLE_GROUNDS,   /*destArea*/ 0x01, /*destNode*/ 0x00, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ 0x01, /*destLevel*/ LEVEL_CASTLE_GROUNDS,   /*destArea*/ 0x01, /*destNode*/ 0x01, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ 0x02, /*destLevel*/ LEVEL_CASTLE_COURTYARD, /*destArea*/ 0x01, /*destNode*/ 0x01, /*flags*/ WARP_NO_CHECKPOINT),
    OBJECT(/*model*/ MODEL_CASTLE_STAR_DOOR_8_STARS, /*pos*/ -2706,   512, -1410, /*angle*/ 0,  45, 0, /*behParam*/ 0x08000000, /*beh*/ bhvStarDoor),
    OBJECT(/*model*/ MODEL_CASTLE_STAR_DOOR_8_STARS, /*pos*/ -2598,   512, -1518, /*angle*/ 0, 225, 0, /*behParam*/ 0x08000000, /*beh*/ bhvStarDoor),
    OBJECT(/*model*/ MODEL_CASTLE_KEY_DOOR,          /*pos*/ -1100,   512, -1075, /*angle*/ 0,   0, 0, /*behParam*/ 0x01030000, /*beh*/ bhvDoorWarp),
    OBJECT(/*model*/ MODEL_CASTLE_KEY_DOOR,          /*pos*/  -944,   512, -1075, /*angle*/ 0, 180, 0, /*behParam*/ 0x01040000, /*beh*/ bhvDoorWarp),
    OBJECT(/*model*/ MODEL_CASTLE_KEY_DOOR,          /*pos*/ -1100, -1075,   922, /*angle*/ 0,   0, 0, /*behParam*/ 0x02050000, /*beh*/ bhvDoorWarp),
    OBJECT(/*model*/ MODEL_CASTLE_KEY_DOOR,          /*pos*/  -944, -1075,   922, /*angle*/ 0, 180, 0, /*behParam*/ 0x02060000, /*beh*/ bhvDoorWarp),
    WARP_NODE(         /*id*/ 0x03, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x02, /*destNode*/ 0x00, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(         /*id*/ 0x04, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x02, /*destNode*/ 0x01, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(         /*id*/ 0x05, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x03, /*destNode*/ 0x00, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(         /*id*/ 0x06, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x03, /*destNode*/ 0x01, /*flags*/ WARP_NO_CHECKPOINT),
    PAINTING_WARP_NODE(/*id*/ 0x00, /*destLevel*/ LEVEL_BOB,    /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    PAINTING_WARP_NODE(/*id*/ 0x01, /*destLevel*/ LEVEL_BOB,    /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    PAINTING_WARP_NODE(/*id*/ 0x02, /*destLevel*/ LEVEL_BOB,    /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    PAINTING_WARP_NODE(/*id*/ 0x03, /*destLevel*/ LEVEL_CCM,    /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    PAINTING_WARP_NODE(/*id*/ 0x04, /*destLevel*/ LEVEL_CCM,    /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    PAINTING_WARP_NODE(/*id*/ 0x05, /*destLevel*/ LEVEL_CCM,    /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    PAINTING_WARP_NODE(/*id*/ 0x06, /*destLevel*/ LEVEL_WF,     /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    PAINTING_WARP_NODE(/*id*/ 0x07, /*destLevel*/ LEVEL_WF,     /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    PAINTING_WARP_NODE(/*id*/ 0x08, /*destLevel*/ LEVEL_WF,     /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    PAINTING_WARP_NODE(/*id*/ 0x09, /*destLevel*/ LEVEL_JRB,    /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    PAINTING_WARP_NODE(/*id*/ 0x0A, /*destLevel*/ LEVEL_JRB,    /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    PAINTING_WARP_NODE(/*id*/ 0x0B, /*destLevel*/ LEVEL_JRB,    /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/  2013,  768, -2014, /*angle*/ 0,    0, 0, /*behParam*/ 0x000A0000, /*beh*/ bhvWarp),
    WARP_NODE(         /*id*/ 0x0A, /*destLevel*/ LEVEL_PSS,    /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/ -5513,  512, -4324, /*angle*/ 0,    0, 0, /*behParam*/ 0x300B0000, /*beh*/ bhvWarp),
    WARP_NODE(         /*id*/ 0x0B, /*destLevel*/ LEVEL_BITDW,  /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/  1963,  819,  1280, /*angle*/ 0,    0, 0, /*behParam*/ 0x050C0000, /*beh*/ bhvWarp),
    WARP_NODE(         /*id*/ 0x0C, /*destLevel*/ LEVEL_SA,     /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(         /*id*/ 0xF2, /*destLevel*/ LEVEL_TOTWC,  /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/ -1024,  512,  -650, /*angle*/ 0,    0, 0, /*behParam*/ 0x001E0000, /*beh*/ bhvInstantActiveWarp),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/ -1024,  -51,   717, /*angle*/ 0,  180, 0, /*behParam*/ 0x001F0000, /*beh*/ bhvInstantActiveWarp),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/ -1024,  900,   717, /*angle*/ 0,  180, 0, /*behParam*/ 0x00200000, /*beh*/ bhvAirborneWarp),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/ -1024,  900,   717, /*angle*/ 0,  180, 0, /*behParam*/ 0x00210000, /*beh*/ bhvAirborneDeathWarp),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/ -1024,  900,   717, /*angle*/ 0,  180, 0, /*behParam*/ 0x00220000, /*beh*/ bhvHardAirKnockBackWarp),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/ -1024,  900,   717, /*angle*/ 0,  180, 0, /*behParam*/ 0x00230000, /*beh*/ bhvDeathWarp),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/ -5513,  512, -4324, /*angle*/ 0, -135, 0, /*behParam*/ 0x00240000, /*beh*/ bhvLaunchStarCollectWarp),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/ -5513,  512, -4324, /*angle*/ 0, -135, 0, /*behParam*/ 0x00250000, /*beh*/ bhvLaunchDeathWarp),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/ -1024,  900,   717, /*angle*/ 0,    0, 0, /*behParam*/ 0x00260000, /*beh*/ bhvAirborneStarCollectWarp),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/  2816, 1200,  -256, /*angle*/ 0,   90, 0, /*behParam*/ 0x00270000, /*beh*/ bhvAirborneStarCollectWarp),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/  2816, 1200,  -256, /*angle*/ 0,  270, 0, /*behParam*/ 0x00280000, /*beh*/ bhvDeathWarp),
    WARP_NODE(/*id*/ 0x1E, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x01, /*destNode*/ 0x1E, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ 0x1F, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x01, /*destNode*/ 0x1F, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ 0x20, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x01, /*destNode*/ 0x20, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ 0x21, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x01, /*destNode*/ 0x21, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ 0x22, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x01, /*destNode*/ 0x22, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ 0x23, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x01, /*destNode*/ 0x23, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ 0x24, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x01, /*destNode*/ 0x24, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ 0x25, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x01, /*destNode*/ 0x25, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ 0x26, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x01, /*destNode*/ 0x26, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ 0x27, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x01, /*destNode*/ 0x27, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ 0x28, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x01, /*destNode*/ 0x28, /*flags*/ WARP_NO_CHECKPOINT),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/ -5422, 717,  -461, /*angle*/ 0, 270, 0, /*behParam*/ 0x00320000, /*beh*/ bhvPaintingStarCollectWarp),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/ -2304,   0, -4552, /*angle*/ 0, 180, 0, /*behParam*/ 0x00330000, /*beh*/ bhvPaintingStarCollectWarp),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/   256, 102, -4706, /*angle*/ 0, 180, 0, /*behParam*/ 0x00340000, /*beh*/ bhvPaintingStarCollectWarp),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/  4501, 717,  -230, /*angle*/ 0,  90, 0, /*behParam*/ 0x00350000, /*beh*/ bhvPaintingStarCollectWarp),
    WARP_NODE(/*id*/ 0x32, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x01, /*destNode*/ 0x32, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ 0x33, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x01, /*destNode*/ 0x33, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ 0x34, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x01, /*destNode*/ 0x34, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ 0x35, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x01, /*destNode*/ 0x35, /*flags*/ WARP_NO_CHECKPOINT),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/ -5422, 717,  -461, /*angle*/ 0, 270, 0, /*behParam*/ 0x00640000, /*beh*/ bhvPaintingDeathWarp),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/ -2304,   0, -4552, /*angle*/ 0, 180, 0, /*behParam*/ 0x00650000, /*beh*/ bhvPaintingDeathWarp),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/   256, 102, -4706, /*angle*/ 0, 180, 0, /*behParam*/ 0x00660000, /*beh*/ bhvPaintingDeathWarp),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/  4501, 717,  -230, /*angle*/ 0,  90, 0, /*behParam*/ 0x00670000, /*beh*/ bhvPaintingDeathWarp),
    WARP_NODE(/*id*/ 0x64, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x01, /*destNode*/ 0x64, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ 0x65, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x01, /*destNode*/ 0x65, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ 0x66, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x01, /*destNode*/ 0x66, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ 0x67, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x01, /*destNode*/ 0x67, /*flags*/ WARP_NO_CHECKPOINT),
    RETURN(),
};

static const LevelScript script_func_local_castle_inside_floor_2_warps[] = {
    OBJECT(/*model*/ MODEL_CASTLE_KEY_DOOR, /*pos*/ -1100, 512, 3021, /*angle*/ 0,   0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvDoorWarp),
    OBJECT(/*model*/ MODEL_CASTLE_KEY_DOOR, /*pos*/  -944, 512, 3021, /*angle*/ 0, 180, 0, /*behParam*/ 0x00010000, /*beh*/ bhvDoorWarp),
    WARP_NODE(/*id*/ 0x00, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x01, /*destNode*/ 0x03, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ 0x01, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x01, /*destNode*/ 0x04, /*flags*/ WARP_NO_CHECKPOINT),
    OBJECT(/*model*/ MODEL_CASTLE_STAR_DOOR_50_STARS, /*pos*/ -282, 2253, 4762, /*angle*/ 0,   0, 0, /*behParam*/ 0x32000000, /*beh*/ bhvStarDoor),
    OBJECT(/*model*/ MODEL_CASTLE_STAR_DOOR_50_STARS, /*pos*/ -128, 2253, 4762, /*angle*/ 0, 180, 0, /*behParam*/ 0x32000000, /*beh*/ bhvStarDoor),
    OBJECT(/*model*/ MODEL_CASTLE_STAR_DOOR_70_STARS, /*pos*/ -282, 3174, 3772, /*angle*/ 0,   0, 0, /*behParam*/ 0x46000000, /*beh*/ bhvStarDoor),
    OBJECT(/*model*/ MODEL_CASTLE_STAR_DOOR_70_STARS, /*pos*/ -128, 3174, 3772, /*angle*/ 0, 180, 0, /*behParam*/ 0x46000000, /*beh*/ bhvStarDoor),
    PAINTING_WARP_NODE(/*id*/ 0x18, /*destLevel*/ LEVEL_WDW, /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    PAINTING_WARP_NODE(/*id*/ 0x19, /*destLevel*/ LEVEL_WDW, /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    PAINTING_WARP_NODE(/*id*/ 0x1A, /*destLevel*/ LEVEL_WDW, /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    PAINTING_WARP_NODE(/*id*/ 0x1B, /*destLevel*/ LEVEL_THI, /*destArea*/ 0x02, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    PAINTING_WARP_NODE(/*id*/ 0x1C, /*destLevel*/ LEVEL_THI, /*destArea*/ 0x02, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    PAINTING_WARP_NODE(/*id*/ 0x1D, /*destLevel*/ LEVEL_THI, /*destArea*/ 0x02, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    PAINTING_WARP_NODE(/*id*/ 0x1E, /*destLevel*/ LEVEL_TTM, /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    PAINTING_WARP_NODE(/*id*/ 0x1F, /*destLevel*/ LEVEL_TTM, /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    PAINTING_WARP_NODE(/*id*/ 0x20, /*destLevel*/ LEVEL_TTM, /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    PAINTING_WARP_NODE(/*id*/ 0x21, /*destLevel*/ LEVEL_TTC, /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    PAINTING_WARP_NODE(/*id*/ 0x22, /*destLevel*/ LEVEL_TTC, /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    PAINTING_WARP_NODE(/*id*/ 0x23, /*destLevel*/ LEVEL_TTC, /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    PAINTING_WARP_NODE(/*id*/ 0x24, /*destLevel*/ LEVEL_SL,  /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    PAINTING_WARP_NODE(/*id*/ 0x25, /*destLevel*/ LEVEL_SL,  /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    PAINTING_WARP_NODE(/*id*/ 0x26, /*destLevel*/ LEVEL_SL,  /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    PAINTING_WARP_NODE(/*id*/ 0x27, /*destLevel*/ LEVEL_THI, /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    PAINTING_WARP_NODE(/*id*/ 0x28, /*destLevel*/ LEVEL_THI, /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    PAINTING_WARP_NODE(/*id*/ 0x29, /*destLevel*/ LEVEL_THI, /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    PAINTING_WARP_NODE(/*id*/ 0x2A, /*destLevel*/ LEVEL_RR,  /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/  3002, 2816,  5886, /*angle*/ 0,   0, 0, /*behParam*/ 0x0F0A0000, /*beh*/ bhvWarp),
    WARP_NODE(/*id*/ 0x0A, /*destLevel*/ LEVEL_WMOTR, /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/  -230, 4813, -3352, /*angle*/ 0,   0, 0, /*behParam*/ 0x0F0B0000, /*beh*/ bhvWarp),
    WARP_NODE(/*id*/ 0x0B, /*destLevel*/ LEVEL_BITS, /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/  -659, 1613,  -350, /*angle*/ 0, 180, 0, /*behParam*/ 0x00320000, /*beh*/ bhvPaintingStarCollectWarp),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/ -4693, 2157,  1828, /*angle*/ 0, 270, 0, /*behParam*/ 0x00330000, /*beh*/ bhvAirborneStarCollectWarp),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/  -675, 1400,  3870, /*angle*/ 0,   0, 0, /*behParam*/ 0x00340000, /*beh*/ bhvPaintingStarCollectWarp),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/  -205, 2918,  7300, /*angle*/ 0,   0, 0, /*behParam*/ 0x00350000, /*beh*/ bhvPaintingStarCollectWarp),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/  3538, 1766,  -400, /*angle*/ 0, 180, 0, /*behParam*/ 0x00360000, /*beh*/ bhvPaintingStarCollectWarp),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/ -4693, 2157,  1828, /*angle*/ 0, 270, 0, /*behParam*/ 0x00370000, /*beh*/ bhvAirborneStarCollectWarp),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/  3002, 2816,  5886, /*angle*/ 0,  90, 0, /*behParam*/ 0x00380000, /*beh*/ bhvLaunchStarCollectWarp),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/ -3412, 2816,  5886, /*angle*/ 0, 270, 0, /*behParam*/ 0x003A0000, /*beh*/ bhvLaunchStarCollectWarp),
    WARP_NODE(/*id*/ 0x32, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x02, /*destNode*/ 0x32, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ 0x33, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x02, /*destNode*/ 0x33, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ 0x34, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x02, /*destNode*/ 0x34, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ 0x35, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x02, /*destNode*/ 0x35, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ 0x36, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x02, /*destNode*/ 0x36, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ 0x37, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x02, /*destNode*/ 0x37, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ 0x38, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x02, /*destNode*/ 0x38, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ 0x3A, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x02, /*destNode*/ 0x3A, /*flags*/ WARP_NO_CHECKPOINT),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/  -659, 1613,  -350, /*angle*/ 0, 180, 0, /*behParam*/ 0x00640000, /*beh*/ bhvPaintingDeathWarp),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/ -4693, 2157,  1828, /*angle*/ 0, 270, 0, /*behParam*/ 0x00650000, /*beh*/ bhvDeathWarp),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/  -675, 1400,  3870, /*angle*/ 0,   0, 0, /*behParam*/ 0x00660000, /*beh*/ bhvPaintingDeathWarp),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/  -205, 2918,  7300, /*angle*/ 0,   0, 0, /*behParam*/ 0x00670000, /*beh*/ bhvPaintingDeathWarp),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/  3538, 1766,  -400, /*angle*/ 0, 180, 0, /*behParam*/ 0x00680000, /*beh*/ bhvPaintingDeathWarp),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/ -4693, 2157,  1828, /*angle*/ 0, 270, 0, /*behParam*/ 0x00690000, /*beh*/ bhvDeathWarp),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/  -230, 4813, -3352, /*angle*/ 0, 180, 0, /*behParam*/ 0x006B0000, /*beh*/ bhvLaunchDeathWarp),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/ -3412, 2816,  5886, /*angle*/ 0, 270, 0, /*behParam*/ 0x006C0000, /*beh*/ bhvLaunchDeathWarp),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/  3002, 2816,  5886, /*angle*/ 0,  90, 0, /*behParam*/ 0x006D0000, /*beh*/ bhvLaunchDeathWarp),
    WARP_NODE(/*id*/ 0x64, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x02, /*destNode*/ 0x64, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ 0x65, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x02, /*destNode*/ 0x65, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ 0x66, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x02, /*destNode*/ 0x66, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ 0x67, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x02, /*destNode*/ 0x67, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ 0x68, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x02, /*destNode*/ 0x68, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ 0x69, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x02, /*destNode*/ 0x69, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ 0x6B, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x02, /*destNode*/ 0x6B, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ 0x6C, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x02, /*destNode*/ 0x6C, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ 0x6D, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x02, /*destNode*/ 0x6D, /*flags*/ WARP_NO_CHECKPOINT),
    RETURN(),
};

static const LevelScript script_func_local_castle_inside_basement_warps[] = {
    OBJECT(/*model*/ MODEL_CASTLE_KEY_DOOR, /*pos*/ -1100, -1075, 922, /*angle*/ 0,   0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvDoorWarp),
    OBJECT(/*model*/ MODEL_CASTLE_KEY_DOOR, /*pos*/  -944, -1075, 922, /*angle*/ 0, 180, 0, /*behParam*/ 0x00010000, /*beh*/ bhvDoorWarp),
    WARP_NODE(/*id*/ 0x00, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x01, /*destNode*/ 0x05, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ 0x01, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x01, /*destNode*/ 0x06, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ 0x02, /*destLevel*/ LEVEL_CASTLE_GROUNDS, /*destArea*/ 0x01, /*destNode*/ 0x02, /*flags*/ WARP_NO_CHECKPOINT),
    OBJECT(/*model*/ MODEL_CASTLE_STAR_DOOR_30_STARS, /*pos*/ 307, -1075, 2074, /*angle*/ 0,  90, 0, /*behParam*/ 0x1E000000, /*beh*/ bhvStarDoor),
    OBJECT(/*model*/ MODEL_CASTLE_STAR_DOOR_30_STARS, /*pos*/ 307, -1075, 1920, /*angle*/ 0, 270, 0, /*behParam*/ 0x1E000000, /*beh*/ bhvStarDoor),
    PAINTING_WARP_NODE(/*id*/ 0x0C, /*destLevel*/ LEVEL_LLL, /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    PAINTING_WARP_NODE(/*id*/ 0x0D, /*destLevel*/ LEVEL_LLL, /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    PAINTING_WARP_NODE(/*id*/ 0x0E, /*destLevel*/ LEVEL_LLL, /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    PAINTING_WARP_NODE(/*id*/ 0x0F, /*destLevel*/ LEVEL_SSL, /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    PAINTING_WARP_NODE(/*id*/ 0x10, /*destLevel*/ LEVEL_SSL, /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    PAINTING_WARP_NODE(/*id*/ 0x11, /*destLevel*/ LEVEL_SSL, /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    PAINTING_WARP_NODE(/*id*/ 0x2A, /*destLevel*/ LEVEL_HMC, /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    PAINTING_WARP_NODE(/*id*/ 0x15, /*destLevel*/ LEVEL_DDD, /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    PAINTING_WARP_NODE(/*id*/ 0x16, /*destLevel*/ LEVEL_DDD, /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    PAINTING_WARP_NODE(/*id*/ 0x17, /*destLevel*/ LEVEL_DDD, /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/  4147, -1280,  1997, /*angle*/ 0,   0, 0, /*behParam*/ 0x0F180000, /*beh*/ bhvWarp),
    WARP_NODE(/*id*/ 0x18, /*destLevel*/ LEVEL_BITFS, /*destArea*/ 0x01, /*destNode*/ 0x0A, /*flags*/ WARP_NO_CHECKPOINT),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/ -1382,  -819, -4150, /*angle*/ 0, 180, 0, /*behParam*/ 0x00320000, /*beh*/ bhvPaintingStarCollectWarp),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/ -2918,  -870,  -875, /*angle*/ 0,   0, 0, /*behParam*/ 0x00330000, /*beh*/ bhvPaintingStarCollectWarp),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/  2483, -1688, -2662, /*angle*/ 0, 270, 0, /*behParam*/ 0x00340000, /*beh*/ bhvLaunchStarCollectWarp),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/  2381,  -500,  2016, /*angle*/ 0,  90, 0, /*behParam*/ 0x00350000, /*beh*/ bhvAirborneStarCollectWarp),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/  4147, -1100,  1997, /*angle*/ 0,  90, 0, /*behParam*/ 0x00360000, /*beh*/ bhvLaunchStarCollectWarp),
    WARP_NODE(/*id*/ 0x32, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x03, /*destNode*/ 0x32, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ 0x33, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x03, /*destNode*/ 0x33, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ 0x34, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x03, /*destNode*/ 0x34, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ 0x35, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x03, /*destNode*/ 0x35, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ 0x36, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x03, /*destNode*/ 0x36, /*flags*/ WARP_NO_CHECKPOINT),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/ -1382,  -819, -4150, /*angle*/ 0, 180, 0, /*behParam*/ 0x00640000, /*beh*/ bhvPaintingDeathWarp),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/ -2918,  -870,  -875, /*angle*/ 0,   0, 0, /*behParam*/ 0x00650000, /*beh*/ bhvPaintingDeathWarp),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/  2483, -1688, -2662, /*angle*/ 0, 270, 0, /*behParam*/ 0x00660000, /*beh*/ bhvLaunchDeathWarp),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/  2381,  -500,  2016, /*angle*/ 0,  90, 0, /*behParam*/ 0x00670000, /*beh*/ bhvDeathWarp),
    OBJECT(/*model*/ MODEL_NONE, /*pos*/  4147, -1100,  1997, /*angle*/ 0,  90, 0, /*behParam*/ 0x00680000, /*beh*/ bhvLaunchDeathWarp),
    WARP_NODE(/*id*/ 0x64, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x03, /*destNode*/ 0x64, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ 0x65, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x03, /*destNode*/ 0x65, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ 0x66, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x03, /*destNode*/ 0x66, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ 0x67, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x03, /*destNode*/ 0x67, /*flags*/ WARP_NO_CHECKPOINT),
    WARP_NODE(/*id*/ 0x68, /*destLevel*/ LEVEL_CASTLE, /*destArea*/ 0x03, /*destNode*/ 0x68, /*flags*/ WARP_NO_CHECKPOINT),
    RETURN(),
};

static const LevelScript script_func_local_castle_inside_basement_flames[] = {
    OBJECT(/*model*/ MODEL_RED_FLAME,  /*pos*/ -2037,  -819,  -717, /*angle*/ 0, 0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvFlame),
    OBJECT(/*model*/ MODEL_RED_FLAME,  /*pos*/ -1648,  -819,  -717, /*angle*/ 0, 0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvFlame),
    OBJECT(/*model*/ MODEL_RED_FLAME,  /*pos*/ -1648,  -819,  -102, /*angle*/ 0, 0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvFlame),
    OBJECT(/*model*/ MODEL_RED_FLAME,  /*pos*/ -1648,  -819,   512, /*angle*/ 0, 0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvFlame),
    OBJECT(/*model*/ MODEL_RED_FLAME,  /*pos*/ -2037,  -819,  -102, /*angle*/ 0, 0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvFlame),
    OBJECT(/*model*/ MODEL_RED_FLAME,  /*pos*/ -2969,  -922,   420, /*angle*/ 0, 0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvFlame),
    OBJECT(/*model*/ MODEL_RED_FLAME,  /*pos*/ -2037,  -819, -1331, /*angle*/ 0, 0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvFlame),
    OBJECT(/*model*/ MODEL_RED_FLAME,  /*pos*/ -3839, -1024, -1422, /*angle*/ 0, 0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvFlame),
    OBJECT(/*model*/ MODEL_RED_FLAME,  /*pos*/ -1929,  -819, -3615, /*angle*/ 0, 0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvFlame),
    OBJECT(/*model*/ MODEL_RED_FLAME,  /*pos*/  -834,  -819, -3615, /*angle*/ 0, 0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvFlame),
    OBJECT(/*model*/ MODEL_BLUE_FLAME, /*pos*/ -3317,  -922,  1229, /*angle*/ 0, 0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvFlame),
    OBJECT(/*model*/ MODEL_BLUE_FLAME, /*pos*/  -205,  -922,  -624, /*angle*/ 0, 0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvFlame),
    OBJECT(/*model*/ MODEL_BLUE_FLAME, /*pos*/ -2876,  -922,  1229, /*angle*/ 0, 0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvFlame),
    RETURN(),
};

const LevelScript level_castle_inside_entry[] = {
    INIT_LEVEL(),
    LOAD_YAY0(        /*seg*/ 0x07, _castle_inside_segment_7SegmentRomStart, _castle_inside_segment_7SegmentRomEnd),
    LOAD_YAY0_TEXTURE(/*seg*/ 0x09,             _inside_yay0SegmentRomStart,             _inside_yay0SegmentRomEnd),
    LOAD_YAY0(        /*seg*/ 0x06,            _group15_yay0SegmentRomStart,            _group15_yay0SegmentRomEnd),
    LOAD_RAW(         /*seg*/ 0x0D,             _group15_geoSegmentRomStart,             _group15_geoSegmentRomEnd),
    ALLOC_LEVEL_POOL(),
    MARIO(/*model*/ MODEL_MARIO, /*behParam*/ 0x00000001, /*beh*/ bhvMario),
    JUMP_LINK(script_func_global_16),
    LOAD_MODEL_FROM_GEO(MODEL_CASTLE_BOWSER_TRAP,        castle_geo_bowser_trap_door),
    LOAD_MODEL_FROM_GEO(MODEL_CASTLE_WATER_LEVEL_PILLAR, castle_geo_water_level_pillar),
    LOAD_MODEL_FROM_GEO(MODEL_CASTLE_CLOCK_MINUTE_HAND,  castle_geo_clock_minute_hand),
    LOAD_MODEL_FROM_GEO(MODEL_CASTLE_CLOCK_HOUR_HAND,    castle_geo_clock_hour_hand),
    LOAD_MODEL_FROM_GEO(MODEL_CASTLE_CLOCK_PENDULUM,     castle_geo_clock_pendulum),
    LOAD_MODEL_FROM_GEO(MODEL_CASTLE_CASTLE_DOOR,        castle_door_geo),
    LOAD_MODEL_FROM_GEO(MODEL_CASTLE_WOODEN_DOOR,        wooden_door_geo),
    LOAD_MODEL_FROM_GEO(MODEL_CASTLE_METAL_DOOR,         metal_door_geo),
    LOAD_MODEL_FROM_GEO(MODEL_CASTLE_CASTLE_DOOR_UNUSED, castle_door_geo),
    LOAD_MODEL_FROM_GEO(MODEL_CASTLE_WOODEN_DOOR_UNUSED, wooden_door_geo),
    LOAD_MODEL_FROM_GEO(MODEL_CASTLE_DOOR_0_STARS,       castle_door_0_star_geo),
    LOAD_MODEL_FROM_GEO(MODEL_CASTLE_DOOR_1_STAR,        castle_door_1_star_geo),
    LOAD_MODEL_FROM_GEO(MODEL_CASTLE_DOOR_3_STARS,       castle_door_3_stars_geo),
    LOAD_MODEL_FROM_GEO(MODEL_CASTLE_KEY_DOOR,           key_door_geo),
    // The different sets of star doors all use different model IDs, despite them all loading the same geo layout.
    // It is possible that star doors were originally going to have numbers on them, similar to the other locked doors.
    LOAD_MODEL_FROM_GEO(MODEL_CASTLE_STAR_DOOR_30_STARS, castle_geo_star_door),
    LOAD_MODEL_FROM_GEO(MODEL_CASTLE_STAR_DOOR_8_STARS,  castle_geo_star_door),
    LOAD_MODEL_FROM_GEO(MODEL_CASTLE_STAR_DOOR_50_STARS, castle_geo_star_door),
    LOAD_MODEL_FROM_GEO(MODEL_CASTLE_STAR_DOOR_70_STARS, castle_geo_star_door),

    AREA(/*index*/ 1, castle_geo_area_1),
        OBJECT(/*model*/ MODEL_NONE,       /*pos*/ -5513,  717, -4324, /*angle*/ 0,  45, 0, /*behParam*/ 0x00140000, /*beh*/ bhvCastleFloorTrap),
        OBJECT(/*model*/ MODEL_NONE,       /*pos*/  2477,  307, -2000, /*angle*/ 0,   0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvFishGroup),
        OBJECT(/*model*/ MODEL_NONE,       /*pos*/  2774,  512, -1716, /*angle*/ 0,  90, 0, /*behParam*/ 0x00000000, /*beh*/ bhvTankFishGroup),
        OBJECT(/*model*/ MODEL_NONE,       /*pos*/  3672,  512, -1307, /*angle*/ 0,  45, 0, /*behParam*/ 0x00000000, /*beh*/ bhvTankFishGroup),
        OBJECT(/*model*/ MODEL_NONE,       /*pos*/  3748,  512,   768, /*angle*/ 0, -45, 0, /*behParam*/ 0x00000000, /*beh*/ bhvTankFishGroup),
        OBJECT(/*model*/ MODEL_NONE,       /*pos*/  2778,  512,  1255, /*angle*/ 0, -90, 0, /*behParam*/ 0x00000000, /*beh*/ bhvTankFishGroup),
        OBJECT(/*model*/ MODEL_BOO_CASTLE, /*pos*/ -1000,   51, -3500, /*angle*/ 0,   0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvBooInCastle),
        OBJECT(/*model*/ MODEL_TOAD,       /*pos*/ -1671,    0,  1313, /*angle*/ 0,  83, 0, /*behParam*/ (DIALOG_133 << 24), /*beh*/ bhvToadMessage),
        OBJECT(/*model*/ MODEL_TOAD,       /*pos*/  1524,  307,   458, /*angle*/ 0, 110, 0, /*behParam*/ (DIALOG_134 << 24), /*beh*/ bhvToadMessage),
        OBJECT(/*model*/ MODEL_TOAD,       /*pos*/   596, -307, -2637, /*angle*/ 0, 152, 0, /*behParam*/ (DIALOG_135 << 24), /*beh*/ bhvToadMessage),
        JUMP_LINK(script_func_local_castle_inside_floor_1_warps),
        WARP_NODE(/*id*/ 0xF1, /*destLevel*/ LEVEL_CASTLE_GROUNDS, /*destArea*/ 0x01, /*destNode*/ 0x03, /*flags*/ WARP_NO_CHECKPOINT),
        TERRAIN(/*terrainData*/ inside_castle_seg7_area_1_collision),
        ROOMS(/*surfaceRooms*/ inside_castle_seg7_area_1_rooms),
        MACRO_OBJECTS(/*objList*/ inside_castle_seg7_area_1_macro_objs),
        SET_BACKGROUND_MUSIC(/*settingsPreset*/ 0x0001, /*seq*/ SEQ_LEVEL_INSIDE_CASTLE),
        TERRAIN_TYPE(/*terrainType*/ TERRAIN_STONE),
        //! TODO: Lobby light, room 1
    END_AREA(),

    AREA(/*index*/ 2, castle_geo_area_2),
        OBJECT(/*model*/ MODEL_CASTLE_CLOCK_MINUTE_HAND, /*pos*/  -205, 2918, 7222, /*angle*/ 0, 180, 0, /*behParam*/ 0x00000000, /*beh*/ bhvClockMinuteHand),
        OBJECT(/*model*/ MODEL_CASTLE_CLOCK_HOUR_HAND,   /*pos*/  -205, 2918, 7222, /*angle*/ 0, 180, 0, /*behParam*/ 0x00000000, /*beh*/ bhvClockHourHand),
        OBJECT(/*model*/ MODEL_CASTLE_CLOCK_PENDULUM,    /*pos*/  -205, 2611, 7140, /*angle*/ 0,   0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvDecorativePendulum),
        OBJECT(/*model*/ MODEL_LAKITU,                   /*pos*/  4231, 1408, 1600, /*angle*/ 0,   0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvCameraLakitu),
        OBJECT(/*model*/ MODEL_TOAD,                     /*pos*/  -977, 1203, 2569, /*angle*/ 0,   0, 0, /*behParam*/ (DIALOG_076 << 24), /*beh*/ bhvToadMessage),
        OBJECT(/*model*/ MODEL_TOAD,                     /*pos*/ -1584, 2253, 7157, /*angle*/ 0, 136, 0, /*behParam*/ (DIALOG_083 << 24), /*beh*/ bhvToadMessage),
        OBJECT(/*model*/ MODEL_TOAD,                     /*pos*/   837, 1203, 3020, /*angle*/ 0, 180, 0, /*behParam*/ (DIALOG_137 << 24), /*beh*/ bhvToadMessage),
        JUMP_LINK(script_func_local_castle_inside_floor_2_warps),
        WARP_NODE(/*id*/ 0xF1, /*destLevel*/ LEVEL_CASTLE_GROUNDS, /*destArea*/ 0x01, /*destNode*/ 0x03, /*flags*/ WARP_NO_CHECKPOINT),
        TERRAIN(/*terrainData*/ inside_castle_seg7_area_2_collision),
        ROOMS(/*surfaceRooms*/ inside_castle_seg7_area_2_rooms),
        MACRO_OBJECTS(/*objList*/ inside_castle_seg7_area_2_macro_objs),
        INSTANT_WARP(/*index*/ 0, /*destArea*/ 2, /*displace*/ 0, -205, 410),
        SET_BACKGROUND_MUSIC(/*settingsPreset*/ 0x0001, /*seq*/ SEQ_LEVEL_INSIDE_CASTLE),
        TERRAIN_TYPE(/*terrainType*/ TERRAIN_STONE),
    END_AREA(),

    AREA(/*index*/ 3, castle_geo_area_3),
        OBJECT(/*model*/ MODEL_CASTLE_WATER_LEVEL_PILLAR, /*pos*/  7066, -1178,  -819, /*angle*/ 0,   0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvWaterLevelPillar),
        OBJECT(/*model*/ MODEL_CASTLE_WATER_LEVEL_PILLAR, /*pos*/  7066, -1178,  -205, /*angle*/ 0,   0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvWaterLevelPillar),
        OBJECT(/*model*/ MODEL_NONE,                      /*pos*/     0,     0,     0, /*angle*/ 0,   0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvDddWarp),
        OBJECT(/*model*/ MODEL_MIPS,                      /*pos*/ -1509, -1177, -1564, /*angle*/ 0,   0, 0, /*behParam*/ 0x00000000, /*beh*/ bhvMips),
        OBJECT(/*model*/ MODEL_TOAD,                      /*pos*/  1787, -1381, -1957, /*angle*/ 0, 126, 0, /*behParam*/ (DIALOG_082 << 24), /*beh*/ bhvToadMessage),
        OBJECT(/*model*/ MODEL_TOAD,                      /*pos*/ -4048, -1381, -1334, /*angle*/ 0,  30, 0, /*behParam*/ (DIALOG_136 << 24), /*beh*/ bhvToadMessage),
        JUMP_LINK(script_func_local_castle_inside_basement_warps),
        JUMP_LINK(script_func_local_castle_inside_basement_flames),
        WARP_NODE(/*id*/ 0xF1, /*destLevel*/ LEVEL_CASTLE_GROUNDS, /*destArea*/ 0x01, /*destNode*/ 0x03, /*flags*/ WARP_NO_CHECKPOINT),
        TERRAIN(/*terrainData*/ inside_castle_seg7_area_3_collision),
        ROOMS(/*surfaceRooms*/ inside_castle_seg7_area_3_rooms),
        MACRO_OBJECTS(/*objList*/ inside_castle_seg7_area_3_macro_objs),
        SET_BACKGROUND_MUSIC(/*settingsPreset*/ 0x0001, /*seq*/ SEQ_LEVEL_INSIDE_CASTLE),
        TERRAIN_TYPE(/*terrainType*/ TERRAIN_STONE),
    END_AREA(),

    FREE_LEVEL_POOL(),
    MARIO_POS(/*area*/ 1, /*yaw*/ 180, /*pos*/ -1024, 0, 1152),
    CALL(     /*arg*/ 0, /*func*/ lvl_init_or_update),
    CALL_LOOP(/*arg*/ 1, /*func*/ lvl_init_or_update),
    CLEAR_LEVEL(),
    SLEEP_BEFORE_EXIT(/*frames*/ 1),
    EXIT(),
};
