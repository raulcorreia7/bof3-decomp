#include "boss025_13.h"

MATCH void func_800C1E34(void) {
    if ((D_801462EC & 0x2800) != 0x800) {
        if (g_BattleCurrentEnemy->turn.damage_flags.value & COMBATANT_FLAG_DEFENDING) {
            Battle_RequestEnemyScript(8);
        } else {
            Battle_RequestEnemyScript(0);
        }
    } else {
        Actor_RequestScript(0xC);
    }
    func_801E30F8();
    g_Task->header.mode++;
}
