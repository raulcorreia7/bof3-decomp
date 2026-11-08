#include "battle_03.h"

MATCH u8 func_801E2D90(u8 slot_offset) {
    u8  result;
    u16 best;
    u8  slot;
    u16 value;

    result = 0u;
    best   = 10000u;
    for (slot = 0u; slot < BATTLE_PARTY_CHARACTERS_COUNT; slot++) {
        if (Battle_SlotIsBlocked(slot) == 0u) {
            value = g_BattlePartyBattlers[slot].chr.hp;
            if (value < best) {
                best   = value;
                result = slot;
            }
        }
    }

    return result;
}
