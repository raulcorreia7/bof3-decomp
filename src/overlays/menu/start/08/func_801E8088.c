#include "start_08.h"

MATCH s32 func_801E8088(s32 character_index, s32 record_index) {
    s32        mode;
    s32        index;
    s32        value;
    s32        result;
    Character* record;

    index = character_index & 0xFF;
    mode  = record_index & 0xFF;
    value = Char_RestoreHP(index, 5, mode);
    if (mode == 0) {
        record = &g_Characters[index];
    } else {
        record = (Character*)&D_80145F04[index * BATTLE_PARTY_STRIDE];
    }
    if (record->status & (STATUS_POISONED | STATUS_CONFUSED)) {
        value |= 1;
        if ((rand() % 100) < 0x1E) {
            Char_ClearStatus(character_index & 0xFF, 0xA0U, record_index & 0xFF);
        }
        result = value & 0xFF;
    } else {
        result = value & 0xFF;
    }
    return -(result == 0) & 3;
}
