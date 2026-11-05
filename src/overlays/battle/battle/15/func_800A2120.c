#include "battle_15.h"

/* sets bit 0x1000 in the damage status row's +0x04 flag word for the
 * active battler, then forwards the selection state to func_800A9BD8.
 */
MATCH void func_800A2120(void) {
    u32 battler;

    func_800A3F28();
    battler = LOBU(g_BattleActiveBattler);
    if (BATTLER_IS_PLAYER(battler)) {
        g_BattlePartyBattlers[battler].action_flags.value |= 0x1000;
    } else {
        ENEMY_COMBATANT(battler).action_flags |= COMBATANT_FLAG_SELECTION_BONUS;
    }
    func_800A9BD8(g_BattleTarget);
}
