#include "battle_15.h"

/* func_800AF3A0 */
MATCH void Battle_MoveTaskToward(VECTOR pos, s16 step) {
    BattleWork* work;
    BattleWork* store;
    SVECTOR     normal;
    s32         vec[3];

    work   = (BattleWork*)g_Task;
    vec[0] = ((s32)work->range_axis_34 >> 9) - 0x4000;
    vec[1] = ((s32)work->range_axis_38 >> 9) - 0x4000;
    vec[2] = ((s16)work->unk_3E) >> 1;
    pos.vx -= vec[0];
    pos.vy -= vec[1];
    pos.vz -= vec[2];
    VectorNormalS(&pos, &normal);

    store = (BattleWork*)g_Task;
    store->range_axis_34 += ((normal.vx * step) >> 3);
    store->range_axis_38 += ((normal.vy * step) >> 3);
    store->unk_3E += ((normal.vz * step) >> 11);
}
