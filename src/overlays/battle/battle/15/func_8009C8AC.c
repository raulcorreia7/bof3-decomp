#include "battle_15.h"

/* FAKE: the second sample of the action-type byte is a non-volatile read through
 * g_BattleActionType_nv. Retail issues a separate %hi/%lo load for it; the
 * canonical g_BattleActionType shares the first sample's `lui` and is 12 bytes shorter.
 */

MATCH u8 func_8009C8AC(u16 required_mask) {
    u32 action_type;
    u32 slot;

    if (g_BattleCurrentEnemy->damage == 0)
        return false;

    action_type = LOBU(g_BattleActionType);
    if (action_type == BATTLE_ACTION_ABILITY) {
        if (D_801CA71C[g_BattleActionId].mask & required_mask)
            return true;
        action_type = g_BattleActionType_nv;
    }
    if (action_type == BATTLE_ACTION_ATTACK) {
        slot = LOBU(g_BattleActiveBattler);
        if (!BATTLER_IS_PLAYER(slot))
            return false;
        if (required_mask & 0x100)
            return false;
        if (D_801C90EB[g_BattlePartyBattlers[slot].stats.equipment.weapon * 0x18] & required_mask)
            return true;
    }
    return false;
}
