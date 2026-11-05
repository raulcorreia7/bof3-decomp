#include "boss033_16.h"

MATCH void func_800C24DC(void) {
    PartyBattler* temp_s0;
    s32           temp_v1;

    temp_v1                   = g_BattleActiveBattler - 3;
    D_801EB630[temp_v1].flags = D_801EB630[temp_v1].flags & 0xBF;
    temp_s0                   = ((PartyBattler*)g_Task);
    ((PartyBattler*)g_Task)   = D_801EB4E0;
    Actor_SelectScript(0U);
    ((PartyBattler*)g_Task) = temp_s0;
    func_801E5988();
}
