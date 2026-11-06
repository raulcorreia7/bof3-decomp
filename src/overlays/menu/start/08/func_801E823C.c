#include "start_08.h"

MATCH s32 func_801E823C(u8 character_index, u8 use_battle_copy) {
    return (Char_ClearStatus(character_index, 0xA0, use_battle_copy) & 0xFF) == 0 ? 3 : 0;
}
