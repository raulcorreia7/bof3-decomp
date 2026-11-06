#include "battle_03.h"

/* clears the work flag and, when the fade counter reaches its
 * threshold, clears the slot's paired flag words before running the shared
 * battle step; otherwise advances the counter.
 *
 * The non-volatile view of D_801EB4E0 is load-bearing: retail's counter store
 * sits in the return-jump delay slot, which the assembler's delay-slot
 * filling only moves for a non-volatile store.
 */
MATCH void func_801E8D04(void) {
    u32 value;

    BATTLE_ACTIVE_WORK->flags &= ~PARTY_BATTLER_FLAG_HANDLER_BUSY;
    value = BATTLE_ACTIVE_WORK->scale_x;
    if (value != 0x10000) {
        BATTLE_ACTIVE_WORK->scale_x = value + 0x2000;
        return;
    }
    BATTLE_ACTIVE_WORK->unk_48 = 0;
    g_BattlePartyBattlers[BATTLE_ACTIVE_WORK->slot].damage_flags.value &= ~0x2000;
    g_BattlePartyBattlers[BATTLE_ACTIVE_WORK->slot].action_flags.value &= 0xFFFCFFF9;
    func_801E5988();
}
