#include "battle_03.h"

MATCH u8 func_801E2CA4(void) {
    u8  result;
    u16 best;
    u8  slot;
    u16 value;

    result = 0u;
    best   = 0xFFFFu;
    for (slot = 3u; slot < 11u; slot++) {
        if (Battle_SlotIsBlocked(slot) == 0u) {
            value = ENEMY_COMBATANT(slot).hp;
            if (value < best) {
                best   = value;
                result = slot;
            }
        }
    }

    return result;
}
