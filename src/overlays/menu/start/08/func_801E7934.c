#include "start_08.h"

MATCH s32 func_801E7934(u8 character_index, u8 target_index, u8 record_index) {
    s32 value;
    u16 amount;
    u8  updated;
    s32 result;

    value   = g_Characters[character_index].stats.intellect;
    amount  = (value + 0x64) / 5;
    updated = Char_RestoreHP(target_index, amount, record_index) & 0xFF;
    result  = 4;
    if (updated) {
        result = 1;
    }
    return result;
}
