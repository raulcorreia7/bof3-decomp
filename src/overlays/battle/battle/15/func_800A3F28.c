#include "battle_15.h"

/* FAKE: LOBU reads the volatile g_BattleTarget as a plain byte; the volatile load
 * would need an extra mask for the index arithmetic. */

/* sets the battler-dirty flag, then marks the active battler's
 * damage-status row present and clears its pending-select bit: player rows
 * below index 3, enemy rows above.
 */
MATCH void func_800A3F28(void) {
    u32           battler_index;
    volatile u16* pFlag;
    u16           flag;

    pFlag         = &g_BattleState;
    flag          = *pFlag;
    battler_index = LOBU(g_BattleTarget);
    *pFlag        = flag | BATTLE_STATE_DAMAGE_APPLIED;
    if (BATTLER_IS_PLAYER(battler_index)) {
        g_BattlePartyBattlers[battler_index].flags_124.volatile_value |= COMBATANT_FLAG_DAMAGE_ROW_PRESENT;
        g_BattlePartyBattlers[g_BattleTarget].unk_120 &= ~0x1u;
    } else {
        D_801EB730[battler_index - 3u].flags_00 |= COMBATANT_FLAG_DAMAGE_ROW_PRESENT;
        D_801EB72C_rows[g_BattleTarget - 3u].flag &= ~0x1u;
    }
}
