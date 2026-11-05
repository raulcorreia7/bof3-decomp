#include "battle_03.h"

/* func_801DB6F4 */
MATCH u8 Battle_FindSelectableSlotBackward(u8 slot) {
    s8 index;
    s8 wrap;
    u8 candidate;

    if (BATTLER_IS_PLAYER(slot)) {
        for (index = slot; index >= 0; index--) {
            candidate = index;
            if (!Battle_SlotIsBlocked(candidate)) {
                return candidate;
            }
        }
        wrap = slot;
        for (index = 2; wrap < index; index--) {
            candidate = index;
            if (!Battle_SlotIsBlocked(candidate)) {
                return candidate;
            }
        }
        return 0xFF;
    }
    for (index = slot; index >= 3; index--) {
        candidate = index;
        if (!Battle_SlotIsBlocked(candidate)) {
            return candidate;
        }
    }
    wrap = slot;
    for (index = 10; wrap < index; index--) {
        candidate = index;
        if (!Battle_SlotIsBlocked(candidate)) {
            return candidate;
        }
    }
    return 0xFF;
}
