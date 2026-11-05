#include "boss050_16.h"

MATCH void func_800C1A08(void) {
    PartyBattler* temp_s0;

    temp_s0                     = ((PartyBattler*)g_SpadWork);
    ((PartyBattler*)g_SpadWork) = D_801EC2E0->target.party;
    func_801E52F0((*g_BattleCurrentEnemy->unk_E8 + 4) & 0xFFFF);
    Actor_SelectScript(2U);
    ((PartyBattler*)g_SpadWork) = temp_s0;
    temp_s0->step_01 += 1;
}
