#include "boss033_16.h"

MATCH void func_800C24DC(void) {
    PartyMember* saved;
    s32          index;

    index                                     = g_Battle.active_battler - 3;
    g_BattleEnemyBattlers[index].header.flags = g_BattleEnemyBattlers[index].header.flags & 0xBF;
    saved                                     = ((PartyMember*)g_Task);
    ((PartyMember*)g_Task)                    = g_BattleEffectBattler;
    Actor_SelectScript(0U);
    ((PartyMember*)g_Task) = saved;
    func_801E5988();
}
