#include "battle_15.h"

MATCH s32 func_800AF550(s32 target_x, s32 target_y, s32 step, s32 angle_offset) {
    BattleRange* work;
    s32          angle;

    work  = (BattleRange*)g_Task;
    angle = ratan2(target_y - work->range_axis_38, target_x - work->range_axis_34) + angle_offset;
    angle &= 0xFFF;
    /* The scratchpad cell is re-read for each step: the GTE calls can replace
     * the work pointer, so retail reloads it per access. */
    ((BattleRange*)g_Task)->range_axis_34 += FIXED_MUL(rcos(angle), step);
    ((BattleRange*)g_Task)->range_axis_38 += FIXED_MUL(rsin(angle), step);
    return angle;
}
