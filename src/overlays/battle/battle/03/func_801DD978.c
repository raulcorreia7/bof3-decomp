#include "battle_03.h"

/* Enemy action values, one u16 per 0x118-byte enemy row. */
/* Enemy base halfwords, one u16 per 0x118-byte enemy row. */

MATCH void func_801DD978(void) {
    u8  max;
    u8  slot;
    u8  result;
    u16 min;
    u16 value;
    u16 base;
    u16 first;

    max = 0u;
    for (slot = 3u; slot < 11u; slot += 1u) {
        if (Battle_SlotIsBlocked(slot & BYTE_MASK) == 0u) {
            value = ENEMY_COMBATANT((slot & BYTE_MASK)).level;
            if (max < value) {
                max = value;
            }
        }
    }

    min    = 0xFFFFu;
    result = 0u;
    for (slot = 3u; slot < 11u; slot += 1u) {
        if (Battle_SlotIsBlocked(slot & BYTE_MASK) == 0u) {
            first = ENEMY_COMBATANT((slot & BYTE_MASK)).level;
            if (max == first) {
                base = ENEMY_COMBATANT((slot & BYTE_MASK)).hp;
                if (base <= min) {
                    min    = base;
                    result = slot;
                }
            }
        }
    }

    g_BattleTargetSelector = result;
}
