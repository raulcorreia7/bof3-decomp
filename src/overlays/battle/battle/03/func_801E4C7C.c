#include "battle_03.h"

MATCH void func_801E4C7C(void) {
    PartyBattler* work;
    u8            count;

    work  = g_SpadWork;
    count = work->word_08.byte.unk_09;
    if (count == 0) {
        if (g_BattleEncounter != 0) {
            func_801E52F0(g_BattleCurrentEnemy->unk_E8[1]);
        } else {
            SND_PlayCue((g_BattleCurrentEnemy->kind * 2) | 0x601);
        }
        work         = g_SpadWork;
        work->unk_02 = work->unk_02 + 1;
    } else {
        work->word_08.byte.unk_09 = count - 1;
    }
    func_801E3160();
}
