#include "battle_15.h"

MATCH s32 func_800AF4A0(BattleRange* target, s32 step, s32 angle_offset) {
    BattleRange* work;
    s32          angle;

    work  = (BattleRange*)g_Task;
    angle = (ratan2(target->range_axis_38 - work->range_axis_38, target->range_axis_34 - work->range_axis_34) +
             angle_offset) &
            0xFFF;
    ((BattleRange*)g_Task)->range_axis_34 += FIXED_MUL(rcos(angle), step);
    ((BattleRange*)g_Task)->range_axis_38 += FIXED_MUL(rsin(angle), step);
    return angle;
}
