#include "battle_15.h"

MATCH s32 func_800AC704(s32 entry_id) {
    s32 index;
    s32 offset;

    index = 0;
    while ((index & 0xFF) < 8U) {
        offset = (index & 0xFF) * 136;
        if (MEM_PTR(u8, 0x800E4050u)[offset] == (entry_id & 0xFF)) {
            return index & 0xFF;
        }
        index++;
    }
    return 255;
}
