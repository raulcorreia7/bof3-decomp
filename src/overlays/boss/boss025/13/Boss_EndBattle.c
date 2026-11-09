#include "boss025_13.h"

MATCH void Boss_EndBattle(void) {
    if (g_Battle.boss_flags & 0x1) {
        func_800AC870(1, (PartyMember*)g_BattleEnemyBattlers, 0);
    }
    func_800AC844(1);
    if (g_Battle.boss_flags & 0x2) {
        func_800AC870(2, (PartyMember*)D_801EB748, 0);
    }
    func_800AC844(2);
}
