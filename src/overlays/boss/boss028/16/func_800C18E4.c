#include "boss028_16.h"
#include "game/enemy.h"

MATCH void func_800C18E4(void) {
    TASK(PartyMember)->unk_09 = ENCOUNTER_ENEMIES[g_BattleCurrentEnemy->type].unk_84[2];
    Battle_RequestEnemyScript(2);
    TASK(PartyMember)->header.step++;
}
