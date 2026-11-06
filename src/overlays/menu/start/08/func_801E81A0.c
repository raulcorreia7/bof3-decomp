#include "start_08.h"

MATCH s32 func_801E81A0(u8 character_index, u8 record_index) {
    return (Char_ClearStatus(character_index, STATUS_POISONED, record_index) & BYTE_MASK) == 0 ? 3 : 0;
}
