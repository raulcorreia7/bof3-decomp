#include "start_08.h"

MATCH s32 func_801E81D4(u8 character_index, u8 record_index) {
    return (Char_ClearStatus(character_index, 0x8, record_index) & 0xFF) == 0 ? 3 : 0;
}
