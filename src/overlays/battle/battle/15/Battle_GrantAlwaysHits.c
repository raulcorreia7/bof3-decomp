#include "battle_15.h"

/* sets bit 0x100 in the damage status row for the active battler.
 */
/* func_800A1704 */
MATCH void Battle_GrantAlwaysHits(void) {
    u8 battler;

    Battle_MarkDamageApplied();
    battler = LOBU(g_Battle.active_battler);
    if (BATTLER_IS_PLAYER(battler)) {
        g_Game.members[battler].u.turn.action_flags.value |= COMBATANT_FLAG_ALWAYS_HITS;
        return;
    }
    ENEMY_COMBATANT(battler).turn.action_flags.value |= COMBATANT_FLAG_ALWAYS_HITS;
}
