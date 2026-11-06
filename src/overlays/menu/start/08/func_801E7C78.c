#include "start_08.h"

MATCH s32 func_801E7C78(s32 caster_index, s32 target_index, s32 use_battle_record) {
    s32 result;

    if (Char_ClearStatus(target_index & 0xFF, 0xA0U, use_battle_record & 0xFF) & 0xFF) {
        result = 1;
    } else {
        result = 4;
    }

    return result;
}
