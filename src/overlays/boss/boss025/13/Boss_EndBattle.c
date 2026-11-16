#include "boss025_13.h"

MATCH void Boss_EndBattle(void) {
    if (g_Battle.boss_flags & 0x1) {
        Battle_CopyActorEntry(1, (PartyMember*)g_BattleEnemyBattlers, 0);
    }
    Battle_ShowActorEntry(1);
    if (g_Battle.boss_flags & 0x2) {
        Battle_CopyActorEntry(2, (PartyMember*)D_801EB748, 0);
    }
    Battle_ShowActorEntry(2);
}
