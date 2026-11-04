#include "battle_15.h"

MATCH void func_800AE82C(void) {
    PartyBattler* work;
    PartyBattler* row_work;
    PartyBattler* tail_work;
    u32           slot;
    u8            count;
    s32           value;

    work                      = BATTLE_WORK;
    count                     = work->word_08.byte.unk_09 - 1;
    work->word_08.byte.unk_09 = count;
    if (count == 0) {
        row_work = BATTLE_WORK;
        slot     = row_work->word_08.byte.unk_0B;
        if (slot < BATTLE_PARTY_SLOT_COUNT) {
            row_work->coord_x_34.raw = g_BattlePartyBattlers[slot].coord_x_34.raw;
            row_work->coord_y_38.raw = g_BattlePartyBattlers[row_work->word_08.byte.unk_0B].coord_y_38.raw;
            value                    = g_BattlePartyBattlers[row_work->word_08.byte.unk_0B].word_3C.word;
        } else {
            row_work->coord_x_34.raw = ENEMY_COMBATANT(row_work->word_08.byte.unk_0B).coord_x_34;
            row_work->coord_y_38.raw = ENEMY_COMBATANT(row_work->word_08.byte.unk_0B).coord_y_38;
            value                    = ENEMY_COMBATANT(row_work->word_08.byte.unk_0B).word_3C.word;
        }
        row_work->word_3C.word = value;
        func_800AF764();
        tail_work                      = BATTLE_WORK;
        tail_work->unk_10              = -0xE;
        tail_work->word_08.byte.unk_09 = 0;
        tail_work->unk_2E.half -= 0x18;
        tail_work->unk_30.half -= tail_work->word_08.byte.unk_0A;
        BATTLE_WORK->word_08.byte.unk_0A = 1;
        BATTLE_WORK->step_01 += 1;
    }
}
