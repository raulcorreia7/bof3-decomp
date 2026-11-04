#include "battle_15.h"

MATCH void func_800AD4D4(void) {
    volatile PartyBattler* work;
    PartyBattler*          ptr;
    u32                    first;
    u32                    second;
    u8                     remainder;
    u8                     index;

    work              = (PartyBattler*)g_SpadWork;
    first             = work->word_08.byte.unk_0B;
    second            = work->word_08.byte.unk_0B;
    remainder         = (u8)first % 6;
    work->unk_2E.half = D_80148628 + (remainder * 0x1E + 0x13);
    work->unk_30.half = (second / 3 * 16 & 0x1FE0) + (0x30 + D_8014862A);
    index             = 0;
    if (g_BattleGeneCount[0] != 0) {
        do {
            ptr = (PartyBattler*)g_SpadWork;
            if (D_801463C4[index] == ptr->word_08.byte.unk_0B) {
                ptr->unk_02 += 1;
            }
            index++;
        } while (index < g_BattleGeneCount[0]);
    }
}
