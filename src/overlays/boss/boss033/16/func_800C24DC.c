#include "boss033_16.h"

MATCH void func_800C24DC(void) {
    PartyMember* saved;
    s32          index;

    index                                     = g_Battle.active_battler - 3;
    g_BattleEnemyBattlers[index].header.flags = g_BattleEnemyBattlers[index].header.flags & 0xBF;
    saved                                     = (SELF(PartyMember));
    (SELF(PartyMember))                       = g_BattleEffectBattler;
    Script_Select(0U);
    (SELF(PartyMember)) = saved;
    Effect_Reset();
}
