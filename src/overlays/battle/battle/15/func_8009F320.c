#include "battle_15.h"

/* runs the shared panel update and sets the 0x200 flag on the
 * selected entry's flags_04: the local battler record D_80145FB4 while the
 * local count g_BattleActiveBattler is under 3, otherwise the enemy record D_801EB730.
 */
MATCH void func_8009F320(void) {
    func_800A3F28();

    if (BATTLER_IS_PLAYER(g_BattleActiveBattler)) {
        g_BattlePartyBattlers[g_BattleTarget].action_flags.value |= COMBATANT_FLAG_DAMAGE_HALVED;
        return;
    }

    ENEMY_COMBATANT(g_BattleTarget).action_flags |= COMBATANT_FLAG_DAMAGE_HALVED;
}
