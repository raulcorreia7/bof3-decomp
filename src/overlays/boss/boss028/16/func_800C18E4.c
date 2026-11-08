#include "boss028_16.h"
#include "game/enemy.h"

MATCH void func_800C18E4(void) {
    ((PartyMember*)g_Task)->unk_09 = ENCOUNTER_ENEMIES[g_BattleCurrentEnemy->kind].unk_84[2];
    func_801E2314(2);
    ((PartyMember*)g_Task)->header.step++;
}
