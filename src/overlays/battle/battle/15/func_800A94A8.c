#include "battle_15.h"

MATCH u8 func_800A94A8(void) {
    u8  choices[8];
    u8  count;
    u8  slot;
    s32 random_value;

    count = 0u;
    for (slot = 0u; slot < BATTLE_PARTY_CHARACTERS_COUNT; slot++) {
        if (Battle_SlotIsBlocked(slot) == 0u) {
            choices[count] = slot;
            count += 1u;
        }
    }

    random_value = rand();

    return choices[random_value % count];
}
