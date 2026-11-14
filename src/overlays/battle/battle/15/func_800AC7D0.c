#include "battle_15.h"

MATCH s32 func_800AC7D0(s32 entry_id) {
    s32 index;
    s32 offset;

    index = 0;
    while ((u32)(index & BYTE_MASK) < BATTLE_ENTRY_COUNT) {
        offset = (index & BYTE_MASK) * BATTLE_ENTRY_STRIDE;
        if (D_8014688E[offset] == BATTLE_ENTRY_TYPE && D_8014691A[offset] == (entry_id & BYTE_MASK)) {
            return index & BYTE_MASK;
        }
        index++;
    }
    return 0xFF;
}
