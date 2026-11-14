#include "battle_15.h"

/* runs the shared panel update and sets the 0x200 flag on the
 * selected entry's flags_04: the local battler record while the
 * local count g_Battle.active_battler is under 3, otherwise the enemy battler row.
 */
/* func_8009F320 */
MATCH void Battle_HalveDamage(void) {
    Battle_MarkDamageApplied();

    if (BATTLER_IS_PLAYER(g_Battle.active_battler)) {
        g_Game.members[g_Battle.target].u.turn.action_flags.value |= COMBATANT_FLAG_DAMAGE_HALVED;
        return;
    }

    ENEMY_COMBATANT(g_Battle.target).turn.action_flags.value |= COMBATANT_FLAG_DAMAGE_HALVED;
}
