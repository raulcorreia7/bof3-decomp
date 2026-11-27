#include "battle_15.h"

MATCH s32 func_800AF4A0(BattleRange* target, s32 step, s32 angle_offset) {
    BattleRange* work;
    s32          angle;

    work  = SELF(BattleRange);
    angle = (ratan2(target->range_y - work->range_y, target->range_x - work->range_x) + angle_offset) & 0xFFF;
    SELF(BattleRange)->range_x += FIXED_MUL(rcos(angle), step);
    SELF(BattleRange)->range_y += FIXED_MUL(rsin(angle), step);
    return angle;
}
