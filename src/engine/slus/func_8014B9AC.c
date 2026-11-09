#include "engine/slus/slus.h"

/* sets bit 6 of the callback slot word for callback_slot. */
MATCH void func_8014B9AC(s32 callback_slot) {
    D_80143B40[callback_slot].state |= 0x40;
}
