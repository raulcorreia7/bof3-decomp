#include "boss033_16.h"

MATCH void func_800C24DC(void) {
    PartyMember* temp_s0;
    s32          temp_v1;

    temp_v1                                     = g_BattleActiveBattler - 3;
    g_BattleEnemyBattlers[temp_v1].header.flags = g_BattleEnemyBattlers[temp_v1].header.flags & 0xBF;
    temp_s0                                     = ((PartyMember*)g_Task);
    ((PartyMember*)g_Task)                      = g_BattleEffectBattler;
    Actor_SelectScript(0U);
    ((PartyMember*)g_Task) = temp_s0;
    func_801E5988();
}
