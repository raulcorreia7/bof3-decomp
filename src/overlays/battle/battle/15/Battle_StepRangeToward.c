#include "battle_15.h"

/* func_800AF3A0 */
MATCH void Battle_StepRangeToward(VECTOR pos, s16 step) {
    BattleRange* work;
    BattleRange* store;
    SVECTOR      normal;
    s32          vec[3];

    work   = SELF(BattleRange);
    vec[0] = ((s32)work->range_x >> 9) - 0x4000;
    vec[1] = ((s32)work->range_y >> 9) - 0x4000;
    vec[2] = ((s16)work->unk3E) >> 1;
    pos.vx -= vec[0];
    pos.vy -= vec[1];
    pos.vz -= vec[2];
    VectorNormalS(&pos, &normal);

    store = SELF(BattleRange);
    store->range_x += ((normal.vx * step) >> 3);
    store->range_y += ((normal.vy * step) >> 3);
    store->unk3E += ((normal.vz * step) >> 11);
}
