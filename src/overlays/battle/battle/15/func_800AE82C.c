#include "battle_15.h"

MATCH void func_800AE82C(void) {
    PartyBattler* work;
    PartyBattler* row_work;
    PartyBattler* tail_work;
    u32           slot;
    u8            count;
    s32           value;

    work         = BATTLE_WORK;
    count        = work->unk_09 - 1;
    work->unk_09 = count;
    if (count == 0) {
        row_work = BATTLE_WORK;
        slot     = row_work->unk_0B;
        if (slot < BATTLE_PARTY_SLOT_COUNT) {
            row_work->x.raw = g_BattlePartyBattlers[slot].x.raw;
            row_work->y.raw = g_BattlePartyBattlers[row_work->unk_0B].y.raw;
            value           = g_BattlePartyBattlers[row_work->unk_0B].z.raw;
        } else {
            row_work->x.raw = ENEMY_COMBATANT(row_work->unk_0B).x;
            row_work->y.raw = ENEMY_COMBATANT(row_work->unk_0B).y;
            value           = ENEMY_COMBATANT(row_work->unk_0B).z.raw;
        }
        row_work->z.raw = value;
        func_800AF764();
        tail_work         = BATTLE_WORK;
        tail_work->unk_10 = -0xE;
        tail_work->unk_09 = 0;
        tail_work->unk_2E.half -= 0x18;
        tail_work->unk_30.half -= tail_work->timer;
        BATTLE_WORK->timer = 1;
        BATTLE_WORK->mode += 1;
    }
}
