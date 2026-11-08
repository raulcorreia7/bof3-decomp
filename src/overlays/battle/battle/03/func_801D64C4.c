#include "battle_03.h"

MATCH u8 func_801D64C4(u8 battler_index) {
    u16 flags;

    if (BATTLER_IS_PLAYER(battler_index)) {
        if (g_BattleActionLock != 0u) {
            flags = g_Game.members[battler_index].u.turn.action_flags.volatile_value;
            if ((flags & 0x10u) == 0u) {
                return 1u;
            }
        }
    } else {
        if (g_BattleActionLock != 0u) {
            flags = ENEMY_COMBATANT(battler_index).turn.action_flags.volatile_value;
            if ((flags & 0x10u) == 0u) {
                return 1u;
            }
        }
    }

    return Battle_SlotIsBlocked(battler_index) != 0u;
}
