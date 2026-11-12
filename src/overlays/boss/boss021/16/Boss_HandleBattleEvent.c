#include "boss021_16.h"

MATCH u8 Boss_HandleBattleEvent(u32 mode) {
    u8 slot;

    switch ((u8)mode) {
        case 3:
            for (slot = 0; slot < 3; slot++) {
                if (Battle_SlotIsBlocked(slot & BYTE_MASK) == 0) {
                    g_Game.members[slot].chr.status |= STATUS_SILENCED;
                }
            }
            for (slot = 3; slot < 11; slot++) {
                if (Battle_SlotIsBlocked(slot & BYTE_MASK) == 0) {
                    ENEMY_COMBATANT(slot & BYTE_MASK).status |= STATUS_SILENCED;
                }
            }
            break;
        case 0:
        case 1:
        case 2:
        case 4:
        case 5:
            break;
    }
    return 0;
}
