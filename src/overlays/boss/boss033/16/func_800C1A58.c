#include "boss033_16.h"

MATCH void func_800C1A58(void) {
    u8 timer;

    timer                                              = ((PartyBattler*)g_SpadWork)->word_08.byte.timer_0A - 1;
    ((PartyBattler*)g_SpadWork)->word_08.byte.timer_0A = timer;
    if (!(timer & 0xFF)) {
        func_801E52F0(*g_BattleCurrentEnemy->unk_E8);
        func_801E52F0((*g_BattleCurrentEnemy->unk_E8 + 4) & 0xFFFF);
        ((PartyBattler*)g_SpadWork)->unk_02 += 1;
    }
}
