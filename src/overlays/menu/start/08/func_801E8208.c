#include "start_08.h"

MATCH s32 func_801E8208(u8 character_index, u8 use_battle_copy) {
    return (Char_ClearStatus(character_index, 0x100, use_battle_copy) & BYTE_MASK) == 0 ? 3 : 0;
}
