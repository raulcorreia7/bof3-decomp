#include "battle_03.h"

MATCH void func_801E3A44(void) {
    PartyBattler* work;
    u8            count;

    func_801E30F8();
    work                      = g_SpadWork;
    count                     = work->word_08.byte.unk_09 - 1;
    work->word_08.byte.unk_09 = count;
    if (count == 0) {
        if (g_BattleEncounter != 0) {
            func_801E52F0(*g_BattleCurrentEnemy->unk_E8);
        } else {
            SND_PlayCue((g_BattleCurrentEnemy->kind * 2) | 0x600);
        }
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}
