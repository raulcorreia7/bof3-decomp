#include "battle_15.h"

MATCH s32 func_800A9B44(void) {
    u16 packed;
    u32 value;

    packed = g_Battle.action->unk_02;
    value  = packed;
    if ((Item_GetFlags(value >> 8, packed & BYTE_MASK) & 0x10) != 0) {
        return 0;
    }
    if ((Battle_SlotIsBlocked(g_Battle.target_selector) & BYTE_MASK) != 0) {
        if (value == 0xE || value == 0x128) {
            return 0;
        }
        return 1;
    }
    if (value == 0xE) {
        return 1;
    }
    return value == 0x128;
}
