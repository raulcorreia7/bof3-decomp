#include "start_08.h"

MATCH s32 func_801E79A8(s32 character_index, s32 quarter_limit, s32 record_index) {
    s32        result;
    u16        step;
    Character* rec;

    rec  = &g_Characters[character_index & 0xFF];
    step = (rec->stats.intellect + 0x64) * 0x28 / 100;

    if (Char_RestoreHP(quarter_limit & 0xFF, step & 0xFFFF, record_index & 0xFF) & 0xFF) {
        result = 1;
    } else {
        result = 4;
    }

    return result;
}
