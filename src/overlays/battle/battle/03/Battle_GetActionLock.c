#include "battle_03.h"

/* func_801D64C4 */
MATCH u8 Battle_GetActionLock(u8 battler_index) {
    u16 flags;

    if (BATTLER_IS_PLAYER(battler_index)) {
        if (g_Battle.action_lock != 0u) {
            flags = g_Game.members[battler_index].u.turn.action_flags.volatile_value;
            if ((flags & 0x10u) == 0u) {
                return 1u;
            }
        }
    } else {
        if (g_Battle.action_lock != 0u) {
            flags = ENEMY_COMBATANT(battler_index).turn.action_flags.volatile_value;
            if ((flags & 0x10u) == 0u) {
                return 1u;
            }
        }
    }

    return Battle_SlotIsBlocked(battler_index) != 0u;
}
