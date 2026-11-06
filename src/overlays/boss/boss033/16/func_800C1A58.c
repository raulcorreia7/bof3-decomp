#include "boss033_16.h"

MATCH void func_800C1A58(void) {
    u8 timer;

    timer                          = ((PartyBattler*)g_Task)->timer - 1;
    ((PartyBattler*)g_Task)->timer = timer;
    if (!(timer & 0xFF)) {
        func_801E52F0(*g_BattleCurrentEnemy->unk_E8);
        func_801E52F0((*g_BattleCurrentEnemy->unk_E8 + 4) & 0xFFFF);
        ((PartyBattler*)g_Task)->header.step += 1;
    }
}
