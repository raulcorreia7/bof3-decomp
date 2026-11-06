#include "start_08.h"

MATCH s32 func_801E8088(s32 character_index, s32 record_index) {
    s32        mode;
    s32        index;
    s32        value;
    s32        result;
    Character* record;

    index = character_index & BYTE_MASK;
    mode  = record_index & BYTE_MASK;
    value = Char_RestoreHP(index, 5, mode);
    if (mode == 0) {
        record = &g_SaveData.characters[index];
    } else {
        record = (Character*)&D_80145F04[index * BATTLE_PARTY_STRIDE];
    }
    if (record->status & (STATUS_POISONED | STATUS_CONFUSED)) {
        value |= 1;
        if ((rand() % 100) < 0x1E) {
            Char_ClearStatus(character_index & BYTE_MASK, 0xA0U, record_index & BYTE_MASK);
        }
        result = value & BYTE_MASK;
    } else {
        result = value & BYTE_MASK;
    }
    return -(result == 0) & 3;
}
