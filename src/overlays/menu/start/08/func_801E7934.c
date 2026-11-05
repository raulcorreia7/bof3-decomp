#include "start_08.h"

MATCH s32 func_801E7934(u8 character_index, u8 intellect_step, u8 record_index) {
    s32 value;
    u16 step;
    u8  updated;
    s32 result;

    value   = g_Characters[character_index].stats.intellect;
    step    = (value + 0x64) / 5;
    updated = Char_RestoreHp(intellect_step, step, record_index) & BYTE_MASK;
    result  = 4;
    if (updated) {
        result = 1;
    }
    return result;
}
