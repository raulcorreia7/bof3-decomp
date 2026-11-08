#include "battle_03.h"

MATCH void func_801DCEF8(u32 battler_index) {
    s32 value;

    battler_index &= BYTE_MASK;
    if (BATTLER_IS_PLAYER(battler_index)) {
        if (HAS_STATUS(g_Game.members[battler_index], STATUS_POISONED)) {
            value                                          = (g_Game.members[battler_index].chr.hp + 5) / 10;
            g_Game.members[battler_index].u.turn.hp_change = value;
        }
    } else {
        if ((ENEMY_COMBATANT(battler_index).status & STATUS_POISONED) != 0u) {
            value                                         = (ENEMY_COMBATANT(battler_index).hp + 5) / 10;
            ENEMY_COMBATANT(battler_index).turn.hp_change = value;
        }
    }
}
