#include "battle_15.h"

MATCH void func_800AD5C8(void) {
    PartyBattler* work;
    u8            count;
    u8            i;
    volatile u16* base;

    i = 0;
    if (g_BattleGeneCount[0] != 0) {
        work  = (PartyBattler*)g_SpadWork;
        count = work->word_08.byte.unk_0B;
        base  = (u16*)(&D_80148628);
        do {
            if (D_801463C4[i] == count) {
                work->unk_2E.half = base[0] + (i * 0x18 + 0x41);
                work->unk_30.half = base[1] + 0x12;
                return;
            }
            i++;
        } while (i < g_BattleGeneCount[0]);
    }
    BATTLE_WORK->unk_02--;
}
