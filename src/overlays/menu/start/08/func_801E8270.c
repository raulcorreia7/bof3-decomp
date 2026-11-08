#include "start_08.h"

MATCH s32 func_801E8270(s32 character_index, s32 record_index) {
    Character* rec;

    if ((record_index & BYTE_MASK) == 0) {
        rec = &g_Characters[character_index & BYTE_MASK];
    } else {
        rec = &g_Game.members[character_index & BYTE_MASK].chr;
    }
    rec->hp = 1;
    return -((Char_ClearStatus(character_index & BYTE_MASK, 0x4000, record_index & BYTE_MASK) & BYTE_MASK) == 0) & 3;
}
