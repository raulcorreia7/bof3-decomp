#include "battle_15.h"

/* sets bit 0x8000 in the damage status row for the active battler.
 */
MATCH void func_800A1414(void) {
    u32 battler;

    func_800A3F28();
    battler = LOBU(g_BattleActiveBattler);
    if (BATTLER_IS_PLAYER(battler)) {
        g_Game.members[battler].u.turn.damage_flags.value |= COMBATANT_FLAG_REPRISAL;
        return;
    }
    ENEMY_COMBATANT(battler).turn.damage_flags.value |= COMBATANT_FLAG_REPRISAL;
}
