#include "battle_15.h"

/* sets bit 0x1000 in the damage status row's +0x04 flag word for the
 * active battler, then forwards the selection state to Battle_RescaleStats.
 */
MATCH void func_800A2120(void) {
    u32 battler;

    Battle_MarkDamageApplied();
    battler = LOBU(g_Battle.active_battler);
    if (BATTLER_IS_PLAYER(battler)) {
        g_Game.members[battler].u.turn.action_flags.value |= COMBATANT_FLAG_SELECTION_BONUS;
    } else {
        ENEMY_COMBATANT(battler).turn.action_flags.value |= COMBATANT_FLAG_SELECTION_BONUS;
    }
    Battle_RescaleStats(g_Battle.target);
}
