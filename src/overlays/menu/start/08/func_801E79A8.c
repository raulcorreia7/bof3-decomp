#include "start_08.h"

MATCH s32 func_801E79A8(s32 character_index, s32 quarter_limit, s32 record_index) {
    s32        result;
    u16        step;
    Character* rec;

    rec  = &g_Characters[character_index & BYTE_MASK];
    step = (rec->stats.intellect + 0x64) * 0x28 / 100;

    if (Char_RestoreHp(quarter_limit & BYTE_MASK, step & HALF_MASK, record_index & BYTE_MASK) & BYTE_MASK) {
        result = 1;
    } else {
        result = 4;
    }

    return result;
}
