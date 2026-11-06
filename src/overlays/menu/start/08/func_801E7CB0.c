#include "start_08.h"

MATCH s32 func_801E7CB0(s32 caster_index, u8 target_index, u8 use_battle_record) {
    s32 result;

    result = Char_RestoreHP(target_index, 0, use_battle_record);
    result |= Char_ClearStatus(target_index, 0xA0, use_battle_record);
    result &= 0xFF;
    if (result == 0) {
        return 4;
    }
    return 1;
}
