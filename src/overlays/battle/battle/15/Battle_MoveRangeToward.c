#include "battle_15.h"

/* func_800AF2B4 */
MATCH void Battle_MoveRangeToward(BattleRange* target, s32 step) {
    BattleRange* work;
    BattleRange* store;
    s16          out[3];
    s32          vec[8];
    s32          amount;

    work   = (BattleRange*)g_Task;
    vec[0] = (s32)(target->range_axis_34 - work->range_axis_34) >> 9;
    vec[1] = (s32)(target->range_axis_38 - work->range_axis_38) >> 9;
    vec[2] = ((s16)target->unk3E - (s16)work->unk3E) >> 1;
    VectorNormalS((VECTOR*)vec, (SVECTOR*)out);
    amount = (s16)step;
    store  = (BattleRange*)g_Task;
    store->range_axis_34 += (out[0] * amount) >> 3;
    store->range_axis_38 += (out[1] * amount) >> 3;
    store->unk3E += (out[2] * amount) >> 11;
}
