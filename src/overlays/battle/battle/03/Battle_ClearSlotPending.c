#include "battle_03.h"

MATCH void Battle_ClearSlotPending(u32 slot) {
    u16* pending_bits = &D_801463C2;

    *pending_bits &= ~(1u << slot);
}
