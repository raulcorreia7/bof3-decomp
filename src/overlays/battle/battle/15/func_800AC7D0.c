#include "battle_15.h"

MATCH s32 func_800AC7D0(s32 entry_id) {
    s32 index;
    s32 offset;

    index = 0;
    while ((u32)(index & BYTE_MASK) < BATTLE_ENTRY_COUNT) {
        offset = (index & BYTE_MASK) * BATTLE_ENTRY_STRIDE;
        if (g_Actors[index & BYTE_MASK].unk_06 == BATTLE_ENTRY_TYPE && g_Actors[index & BYTE_MASK].fish_row == (entry_id & BYTE_MASK)) {
            return index & BYTE_MASK;
        }
        index++;
    }
    return 0xFF;
}
