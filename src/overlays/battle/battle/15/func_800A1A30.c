#include "battle_15.h"

/* sets bit 0x10000 in the damage status row for the active battler.
 */
MATCH void func_800A1A30(void) {
    u32 battler;

    func_800A3F28();
    battler = LOBU(g_BattleActiveBattler);
    if (BATTLER_IS_PLAYER(battler)) {
        g_BattlePartyBattlers[battler].turn.damage_flags.value |= COMBATANT_FLAG_DAMAGE_IMMUNE;
        return;
    }
    ENEMY_COMBATANT(battler).turn.damage_flags.value |= COMBATANT_FLAG_DAMAGE_IMMUNE;
}
