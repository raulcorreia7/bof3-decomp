#include "battle_15.h"

/* sets bit 0x100 in the damage status row for the active battler.
 */
MATCH void func_800A1704(void) {
    u8 battler;

    func_800A3F28();
    battler = LOBU(g_BattleActiveBattler);
    if (BATTLER_IS_PLAYER(battler)) {
        g_BattlePartyBattlers[battler].turn.action_flags.value |= 0x100;
        return;
    }
    ENEMY_COMBATANT(battler).turn.action_flags.value |= 0x100;
}
