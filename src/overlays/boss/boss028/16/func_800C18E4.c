#include "boss028_16.h"
#include "game/enemy.h"

MATCH void func_800C18E4(void) {
    ((PartyBattler*)g_SpadWork)->word_08.byte.unk_09 = ENCOUNTER_ENEMIES[g_BattleCurrentEnemy->kind].unk_84[2];
    func_801E2314(2);
    ((PartyBattler*)g_SpadWork)->unk_02++;
}
