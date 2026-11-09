#include "engine/slus/slus.h"

/* reads the scratchpad record. */
MATCH u16 Actor_ReadState(void) {
    Actor* record;
    u8*    entry;
    u32    value;
    s32    result;

    record = g_Task;
    if (record->unk_4A == 1) {
        value = record->script_pc;
        if (((u16)value >> 1) == record->unk_49) {
            result = 2;
        } else {
            entry = record->script + (u16)value;
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
