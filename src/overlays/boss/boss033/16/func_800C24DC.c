#include "boss033_16.h"

MATCH void func_800C24DC(void) {
    PartyMember* saved;
    s32          index;

    index                                     = g_Battle.active_battler - 3;
    g_BattleEnemyBattlers[index].header.flags = g_BattleEnemyBattlers[index].header.flags & 0xBF;
    saved                                     = ((PartyMember*)g_Task);
    ((PartyMember*)g_Task)                    = g_BattleEffectBattler;
    Script_Select(0U);
    ((PartyMember*)g_Task) = saved;
    Effect_Reset();
}
