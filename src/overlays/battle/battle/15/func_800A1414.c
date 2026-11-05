#include "battle_15.h"

/* sets bit 0x8000 in the damage status row for the active battler.
 */
MATCH void func_800A1414(void) {
    u32 battler;

    func_800A3F28();
    battler = LOBU(g_BattleActiveBattler);
    if (BATTLER_IS_PLAYER(battler)) {
        g_BattlePartyBattlers[battler].flags_124.value |= COMBATANT_FLAG_REPRISAL;
        return;
    }
    ENEMY_COMBATANT(battler).flags_100 |= COMBATANT_FLAG_REPRISAL;
}
