#include "battle_15.h"

/* sets bit 0x10000 in the damage status row for the active battler.
 */
/* func_800A1A30 */
MATCH void Battle_GrantDamageImmunity(void) {
    u32 battler;

    Battle_MarkDamageApplied();
    battler = LOBU(g_Battle.active_battler);
    if (BATTLER_IS_PLAYER(battler)) {
        g_Game.members[battler].u.turn.damage_flags.value |= COMBATANT_FLAG_DAMAGE_IMMUNE;
        return;
    }
    ENEMY_COMBATANT(battler).turn.damage_flags.value |= COMBATANT_FLAG_DAMAGE_IMMUNE;
}
