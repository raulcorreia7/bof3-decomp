#include "battle_15.h"

MATCH s32 func_800AF550(s32 target_x, s32 target_y, s32 step, s32 angle_offset) {
    BattleRange* work;
    s32          angle;

    work  = SELF(BattleRange);
    angle = ratan2(target_y - work->range_y, target_x - work->range_x) + angle_offset;
    angle &= 0xFFF;
    /* The scratchpad cell is re-read for each step: the GTE calls can replace
     * the work pointer, so retail reloads it per access. */
    SELF(BattleRange)->range_x += FIXED_MUL(rcos(angle), step);
    SELF(BattleRange)->range_y += FIXED_MUL(rsin(angle), step);
    return angle;
}
