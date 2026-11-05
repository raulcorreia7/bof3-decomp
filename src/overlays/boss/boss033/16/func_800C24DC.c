#include "boss033_16.h"

MATCH void func_800C24DC(void) {
    PartyBattler* temp_s0;
    s32           temp_v1;

    temp_v1                     = g_BattleActingBattler - 3;
    D_801EB630[temp_v1].unk_00  = D_801EB630[temp_v1].unk_00 & 0xBF;
    temp_s0                     = ((PartyBattler*)g_SpadWork);
    ((PartyBattler*)g_SpadWork) = D_801EB4E0;
    Actor_SelectScript(0U);
    ((PartyBattler*)g_SpadWork) = temp_s0;
    func_801E5988();
}
