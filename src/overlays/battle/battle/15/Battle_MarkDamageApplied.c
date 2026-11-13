#include "battle_15.h"

/* FAKE: LOBU reads the volatile g_Battle.target as a plain byte; the volatile load
 * would need an extra mask for the index arithmetic. */

/* sets the battler-dirty flag, then marks the active battler's
 * damage-status row present and clears its pending-select bit: player rows
 * below index 3, enemy rows above.
 */
/* func_800A3F28 */
MATCH void Battle_MarkDamageApplied(void) {
    u32           battler_index;
    volatile u16* pFlag;
    u16           flag;

    pFlag         = &g_Battle.state;
    flag          = *pFlag;
    battler_index = LOBU(g_Battle.target);
    *pFlag        = flag | BATTLE_STATE_DAMAGE_APPLIED;
    if (BATTLER_IS_PLAYER(battler_index)) {
        g_Game.members[battler_index].u.turn.damage_flags.volatile_value |= COMBATANT_FLAG_DAMAGE_ROW_PRESENT;
        g_Game.members[g_Battle.target].u.turn.target_flags &= ~BATTLE_HIT_HP;
    } else {
        ENEMY_COMBATANT(battler_index).turn.damage_flags.volatile_value |= COMBATANT_FLAG_DAMAGE_ROW_PRESENT;
        ENEMY_COMBATANT(g_Battle.target).turn.target_flags &= ~0x1u;
    }
}
