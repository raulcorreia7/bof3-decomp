#include "boss025_13.h"

MATCH void func_800C1AA0(void) {
    if (g_BattleEncounter == 25) {
        if (D_80146322 != 0) {
            g_BattleCurrentEnemy->turn.damage_flags.value &= ~COMBATANT_FLAG_DEFENDING;
        }
        g_BattleActionType = BATTLE_ACTION_ATTACK;
    }
}
