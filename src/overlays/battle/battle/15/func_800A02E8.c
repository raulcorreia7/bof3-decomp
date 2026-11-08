#include "battle_15.h"

/* when the active battler has no pending action flag, clears its
 * rule counter (for the first three battlers) and refreshes the shared battle
 * display unless the input-mask query succeeds; otherwise marks the g_BattleTargetRecord
 * record as selected.
 */
MATCH void func_800A02E8(void) {
    u32 battler;

    battler = *(u8*)&g_BattleTarget;
    if ((g_Game.members[battler].u.turn.action_flags.value &
         (COMBATANT_FLAG_DRAGON_FORM_QUEUED | COMBATANT_FLAG_DRAGON_FORM)) == 0u) {
        if (BATTLER_IS_PLAYER(battler)) {
            g_Game.members[battler].counter_137 = 0u;
        }
        if (func_800A4238(0x800) == 0u) {
            func_800A3F28();
            return;
        }
    }
    g_BattleTargetRecord->target_flags = 1;
}
