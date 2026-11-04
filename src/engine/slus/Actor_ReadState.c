#include "engine/slus/slus.h"

/* reads the scratchpad work record: with mode byte +0x4A == 1 it returns 2 when half the entry index
 * (+0x58) matches the filter byte (+0x49), else the length of the indexed stream entry at +0x50; otherwise the raw
 * index halfword.
 */
/* func_8015CA9C */
MATCH u16 Actor_ReadState(void) {
    Actor* record;
    u8*    entry;
    u32    value;
    s32    result;

    record = g_SpadWork;
    if (record->unk_4A == 1) {
        value = record->script_pc;
        if (((u16)value >> 1) == record->unk_49) {
            result = 2;
        } else {
            entry = record->source_50 + (u16)value;
            if (*entry >= 0x80) {
                result = (entry[1] << 1) + 2;
            } else {
                result = value + 2;
            }
        }
    } else {
        result = record->script_pc;
    }
    return result;
}
