#include "boss050_16.h"

MATCH void func_800C1A08(void) {
    PartyBattler* temp_s0;

    temp_s0                 = ((PartyBattler*)g_Task);
    ((PartyBattler*)g_Task) = D_801EC2E0->target.party;
    func_801E52F0((*g_BattleCurrentEnemy->unk_E8 + 4) & 0xFFFF);
    Actor_SelectScript(2U);
    ((PartyBattler*)g_Task) = temp_s0;
    temp_s0->header.mode += 1;
}
