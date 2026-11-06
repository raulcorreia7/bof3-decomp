#include "battle_15.h"

MATCH s32 func_800AC704(s32 entry_id) {
    s32 index;
    s32 offset;

    index = 0;
    while ((index & BYTE_MASK) < 8U) {
        offset = (index & BYTE_MASK) * 136;
        if (MEM_PTR(u8, 0x800E4050u)[offset] == (entry_id & BYTE_MASK)) {
            return index & BYTE_MASK;
        }
        index++;
    }
    return 255;
}
